/*!
 * @file main.c
 * @brief EnOcean 5 Click example.
 *
 * # Description
 * This example demonstrates radio communication betweeen two EnOcean 5 Click boards.
 * The application performs a module reset, retrieves and logs device information,
 * sends text-based radio telegrams, and waits for received ERP1 messages.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and EnOcean 5 Click driver. 
 * Performs a hardware reset and reads module information including APP version, 
 * API version, and device identifiers.
 *
 * ## Application Task
 * Sends "MIKROE" and "EnOcean 5" telegrams, waits for TX_DONE events, 
 * and listens for incoming ERP1 VLD telegrams, logging their content.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "enocean5.h"

// Text messages
#define DEMO_TEXT_MESSAGE_1 "MIKROE"
#define DEMO_TEXT_MESSAGE_2 "EnOcean 5"

static enocean5_t enocean5;
static log_t logger;

/**
 * @brief EnOcean 5 parse response packet function.
 * @details This function parses a received RESPONSE-type packet and logs a
 * human-readable result along with any optional payload bytes.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @return @li @c  0 - Success (valid RESPONSE decoded),
 *         @li @c -1 - Error (wrong packet type or unknown return code).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t enocean5_parse_response ( enocean5_t *ctx );

/**
 * @brief EnOcean 5 parse event packet function.
 * @details This function parses a received EVENT-type packet and logs the
 * decoded event information (e.g., READY, TX_DONE) and associated fields.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @return @li @c  0 - Success (valid EVENT decoded),
 *         @li @c -1 - Error (wrong packet type or unknown event code).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t enocean5_parse_event ( enocean5_t *ctx );

/**
 * @brief EnOcean 5 parse generic packet function.
 * @details This function parses a received packet according to its type
 * (e.g., ERP1, RESPONSE, EVENT) and logs the decoded contents.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @return @li @c  0 - Success (packet decoded),
 *         @li @c -1 - Error (unknown/unsupported packet type or format).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t enocean5_parse_packet ( enocean5_t *ctx );

/**
 * @brief EnOcean 5 wait, read, and parse packet with timeout function.
 * @details This function waits up to @p max_time_s seconds for an incoming
 * packet, reads it, parses it, and checks whether it matches the expected
 * @p type (and, when applicable, @p cmd). For RESPONSE packets, the device
 * status byte is returned.
 * @param[in] ctx : Click context object.
 * See #enocean5_t object definition for detailed explanation.
 * @param[in] type : Expected packet type.
 * @param[in] cmd : Expected command/telegram code (ignored for some types).
 * @param[in] max_time_s : Maximum wait time in seconds.
 * @return @li @c  0 - Success (expected packet received and matched),
 *         @li @c -1 - Error (timeout or mismatch).
 * See #err_t definition for detailed explanation.
 * @note When the expected type is RESPONSE, the function returns the response
 * status byte cast to #err_t on success.
 */
static err_t enocean5_wait_packet_w_parse ( enocean5_t *ctx, uint8_t type, uint8_t cmd, uint8_t max_time_s );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    enocean5_cfg_t enocean5_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    enocean5_cfg_setup( &enocean5_cfg );
    ENOCEAN5_MAP_MIKROBUS( enocean5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == enocean5_init( &enocean5, &enocean5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf ( &logger, "\r\n>> Hardware reset.\r\n" );
    if ( ENOCEAN5_OK != enocean5_reset_device ( &enocean5 ) )
    {
        log_error( &logger, " Hardware reset." );
        for ( ; ; );
    }
    enocean5_parse_packet ( &enocean5 );

    log_printf ( &logger, "\r\n>> Get device info.\r\n" );
    if ( ENOCEAN5_OK == enocean5_read_info ( &enocean5 ) )
    {
        log_printf ( &logger, " < APP version: %u.%u.%u.%u\r\n", 
                     ( uint16_t ) enocean5.info.app_ver[ 0 ], 
                     ( uint16_t ) enocean5.info.app_ver[ 1 ], 
                     ( uint16_t ) enocean5.info.app_ver[ 2 ], 
                     ( uint16_t ) enocean5.info.app_ver[ 3 ] );
        log_printf ( &logger, "   APP description: %s\r\n", enocean5.info.app_desc );
        log_printf ( &logger, "   API version: %u.%u.%u.%u\r\n", 
                     ( uint16_t ) enocean5.info.api_ver[ 0 ], 
                     ( uint16_t ) enocean5.info.api_ver[ 1 ], 
                     ( uint16_t ) enocean5.info.api_ver[ 2 ], 
                     ( uint16_t ) enocean5.info.api_ver[ 3 ] );
        log_printf ( &logger, "   Device ID: 0x%.8LX\r\n", enocean5.info.device_id );
        log_printf ( &logger, "   Device version: 0x%.8LX\r\n", enocean5.info.device_ver );
    }
}

void application_task ( void ) 
{
    log_printf ( &logger, "\r\n>> Sending \"%s\" radio telegram.\r\n", ( char * ) DEMO_TEXT_MESSAGE_1 );
    enocean5_send_radio_message ( &enocean5, ENOCEAN5_RORG_VLD, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    enocean5_wait_packet_w_parse ( &enocean5, ENOCEAN5_PKT_TYPE_EVENT, ENOCEAN5_EVT_TX_DONE, ENOCEAN5_WAIT_TIME_5S );

    log_printf ( &logger, "\r\n>> Waiting for radio telegram.\r\n" );
    enocean5_wait_packet_w_parse ( &enocean5, ENOCEAN5_PKT_TYPE_RADIO_ERP1, ENOCEAN5_RORG_VLD, ENOCEAN5_WAIT_TIME_5S );
    Delay_ms ( 1000 );

    log_printf ( &logger, "\r\n>> Sending \"%s\" radio telegram.\r\n", ( char * ) DEMO_TEXT_MESSAGE_2 );
    enocean5_send_radio_message ( &enocean5, ENOCEAN5_RORG_VLD, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    enocean5_wait_packet_w_parse ( &enocean5, ENOCEAN5_PKT_TYPE_EVENT, ENOCEAN5_EVT_TX_DONE, ENOCEAN5_WAIT_TIME_5S );

    log_printf ( &logger, "\r\n>> Waiting for radio telegram.\r\n" );
    enocean5_wait_packet_w_parse ( &enocean5, ENOCEAN5_PKT_TYPE_RADIO_ERP1, ENOCEAN5_RORG_VLD, ENOCEAN5_WAIT_TIME_5S );
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static err_t enocean5_parse_response ( enocean5_t *ctx )
{
    err_t error_flag = ENOCEAN5_OK;
    uint16_t cnt = 0;
    if ( ENOCEAN5_PKT_TYPE_RESPONSE != ctx->rx_pkt.type )
    {
        error_flag = ENOCEAN5_ERROR;
    }
    if ( ENOCEAN5_OK == error_flag )
    {
        log_printf ( &logger, " < Response: " );
        switch ( ctx->rx_pkt.payload[ 0 ] )
        {
            case ENOCEAN5_RET_OK:
            {
                log_printf ( &logger, "OK" );
                break;
            }
            case ENOCEAN5_RET_ERROR:
            {
                log_printf ( &logger, "Error" );
                break;
            }
            case ENOCEAN5_RET_NOT_SUPPORTED:
            {
                log_printf ( &logger, "Not supported" );
                break;
            }
            case ENOCEAN5_RET_WRONG_PARAM:
            {
                log_printf ( &logger, "Wrong param" );
                break;
            }
            case ENOCEAN5_RET_OPERATION_DENIED:
            {
                log_printf ( &logger, "Operation denied" );
                break;
            }
            case ENOCEAN5_RET_LOCK_SET:
            {
                log_printf ( &logger, "Lock set" );
                break;
            }
            case ENOCEAN5_RET_BUFFER_TOO_SMALL:
            {
                log_printf ( &logger, "Buffer too small" );
                break;
            }
            case ENOCEAN5_RET_NO_FREE_BUFFER:
            {
                log_printf ( &logger, "No free buffer" );
                break;
            }
            default:
            {
                log_printf ( &logger, "Unknown[0x%.2X]", ( uint16_t ) ctx->rx_pkt.payload[ 0 ] );
                error_flag = ENOCEAN5_ERROR;
                break;
            }
        }
        log_printf ( &logger, "\r\n" );
        if ( ctx->rx_pkt.pl_len > 1 )
        {
            log_printf ( &logger, "   Payload:\r\n\t" );
            for ( cnt = 0; cnt < ( ctx->rx_pkt.pl_len - 1 ); cnt++ )
            {
                log_printf ( &logger, "%.2X ", ctx->rx_pkt.payload[ cnt + 1 ] );
            }
            log_printf ( &logger, "\r\n" );
        }
        if ( ctx->rx_pkt.pl_opt_len )
        {
            log_printf ( &logger, "   Payload Optional:\r\n\t" );
            for ( cnt = 0; cnt < ctx->rx_pkt.pl_opt_len; cnt++ )
            {
                log_printf ( &logger, "%.2X ", ctx->rx_pkt.payload_opt[ cnt ] ); 
            }
            log_printf ( &logger, "\r\n" );
        }
    }
    return error_flag;
}

static err_t enocean5_parse_event ( enocean5_t *ctx )
{
    err_t error_flag = ENOCEAN5_OK;
    if ( ENOCEAN5_PKT_TYPE_EVENT != ctx->rx_pkt.type )
    {
        error_flag = ENOCEAN5_ERROR;
    }
    if ( ENOCEAN5_OK == error_flag )
    {
        log_printf ( &logger, " < Event: " );
        switch ( ctx->rx_pkt.payload[ 0 ] )
        {
            case ENOCEAN5_EVT_READY:
            {
                log_printf ( &logger, "Ready\r\n   Wakeup Cause: " );
                switch ( ctx->rx_pkt.payload[ 1 ] )
                {
                    case ENOCEAN5_WAKEUP_VOLTAGE_DROP:
                    {
                        log_printf ( &logger, "Voltage supply drop or VDD > VON" );
                        break;
                    }
                    case ENOCEAN5_WAKEUP_HW_RESET:
                    {
                        log_printf ( &logger, "HW reset (reset pin)" );
                        break;
                    }
                    case ENOCEAN5_WAKEUP_WATCHDOG:
                    {
                        log_printf ( &logger, "Watchdog timer time-out" );
                        break;
                    }
                    case ENOCEAN5_WAKEUP_FLYWHEEL:
                    {
                        log_printf ( &logger, "Flywheel timer time-out" );
                        break;
                    }
                    case ENOCEAN5_WAKEUP_PARITY_ERROR:
                    {
                        log_printf ( &logger, "Parity error" );
                        break;
                    }
                    case ENOCEAN5_WAKEUP_MEMORY_ERROR:
                    {
                        log_printf ( &logger, "Memory error" );
                        break;
                    }
                    case ENOCEAN5_WAKEUP_INVALID_MEM_ADDR:
                    {
                        log_printf ( &logger, "Invalid memory address" );
                        break;
                    }
                    case ENOCEAN5_WAKEUP_HW_WAKEUP_PIN0:
                    {
                        log_printf ( &logger, "HW wake-up via Pin 0" );
                        break;
                    }
                    case ENOCEAN5_WAKEUP_HW_WAKEUP_PIN1:
                    {
                        log_printf ( &logger, "HW wake-up via Pin 1" );
                        break;
                    }
                    case ENOCEAN5_WAKEUP_UNKNOWN_RESET:
                    {
                        log_printf ( &logger, "Unknown reset source" );
                        break;
                    }
                    case ENOCEAN5_WAKEUP_UART:
                    {
                        log_printf ( &logger, "UART wake-up" );
                        break;
                    }
                    case ENOCEAN5_WAKEUP_SW_RESET:
                    {
                        log_printf ( &logger, "SW reset using CO_WR_RESET" );
                        break;
                    }
                    default:
                    {
                        log_printf ( &logger, "Unknown[0x%.2X]", ( uint16_t ) ctx->rx_pkt.payload[ 1 ] );
                        error_flag = ENOCEAN5_ERROR;
                        break;
                    }
                }
                log_printf ( &logger, "\r\n   Mode: " );
                if ( ctx->rx_pkt.payload_opt[ 0 ] )
                {
                    log_printf ( &logger, "Extended Security\r\n" );
                }
                else
                {
                    log_printf ( &logger, "Standard Security\r\n" );
                }
                break;
            }
            case ENOCEAN5_EVT_TX_DONE:
            {
                log_printf ( &logger, "Telegram TX has completed\r\n" );
                break;
            }
            default:
            {
                log_printf ( &logger, "Unknown[0x%.2X]\r\n", ( uint16_t ) ctx->rx_pkt.payload[ 0 ] );
                error_flag = ENOCEAN5_ERROR;
                break;
            }
        }
    }
    return error_flag;
}

static err_t enocean5_parse_packet ( enocean5_t *ctx )
{
    err_t error_flag = ENOCEAN5_OK;
    uint16_t cnt = 0;
    switch ( ctx->rx_pkt.type )
    {
        case ENOCEAN5_PKT_TYPE_RADIO_ERP1:
        {
            log_printf ( &logger, " < ERP1 Radio - " );
            switch ( ctx->rx_pkt.payload[ 0 ] )
            {
                case ENOCEAN5_RORG_VLD:
                {
                    log_printf ( &logger, "VLD telegram\r\n" );
                    log_printf ( &logger, "   Data [RAW]: " );
                    for ( cnt = 6; cnt < ctx->rx_pkt.pl_len; cnt++ )
                    {
                        log_printf ( &logger, "%.2X ", ( uint16_t ) ctx->rx_pkt.payload[ cnt - 5 ] );
                    }
                    log_printf ( &logger, "\r\n   Data [STR]: %s\r\n", &ctx->rx_pkt.payload[ 1 ] );
                    log_printf ( &logger, "   TX ID: %.2X %.2X %.2X %.2X\r\n", 
                                 ( uint16_t ) ctx->rx_pkt.payload[ ctx->rx_pkt.pl_len - 5 ],
                                 ( uint16_t ) ctx->rx_pkt.payload[ ctx->rx_pkt.pl_len - 4 ],
                                 ( uint16_t ) ctx->rx_pkt.payload[ ctx->rx_pkt.pl_len - 3 ],
                                 ( uint16_t ) ctx->rx_pkt.payload[ ctx->rx_pkt.pl_len - 2 ] );
                    log_printf ( &logger, "   Status: 0x%.2X\r\n", ctx->rx_pkt.payload[ ctx->rx_pkt.pl_len - 1 ] );
                    break;
                }
                case ENOCEAN5_RORG_RPS:
                {
                    log_printf ( &logger, "RPS telegram\r\n" );
                    log_printf ( &logger, "   Data: 0x%.2X\r\n", ctx->rx_pkt.payload[ 1 ] );
                    log_printf ( &logger, "   TX ID: %.2X %.2X %.2X %.2X\r\n", 
                                 ( uint16_t ) ctx->rx_pkt.payload[ ctx->rx_pkt.pl_len - 5 ],
                                 ( uint16_t ) ctx->rx_pkt.payload[ ctx->rx_pkt.pl_len - 4 ],
                                 ( uint16_t ) ctx->rx_pkt.payload[ ctx->rx_pkt.pl_len - 3 ],
                                 ( uint16_t ) ctx->rx_pkt.payload[ ctx->rx_pkt.pl_len - 2 ] );
                    log_printf ( &logger, "   Status: 0x%.2X\r\n", ctx->rx_pkt.payload[ ctx->rx_pkt.pl_len - 1 ] );
                    break;
                }
                default:
                {
                    log_printf ( &logger, "Unknown telegram\r\n" );
                    log_printf ( &logger, "   Data [RAW]: " );
                    for ( cnt = 0; cnt < ctx->rx_pkt.pl_len; cnt++ )
                    {
                        log_printf ( &logger, "%.2X ", ( uint16_t ) ctx->rx_pkt.payload[ cnt ] );
                    }
                    log_printf ( &logger, "\r\n" );
                    error_flag = ENOCEAN5_ERROR;
                    break;
                }
            }
            
            log_printf ( &logger, "   Num of sub-telegrams: %u\r\n", 
                         ( uint16_t ) ( ctx->rx_pkt.payload_opt[ 0 ] ) );
            log_printf ( &logger, "   Destination ID: %.2X %.2X %.2X %.2X\r\n", 
                         ( uint16_t ) ( ctx->rx_pkt.payload_opt[ 1 ] ), 
                         ( uint16_t ) ( ctx->rx_pkt.payload_opt[ 2 ] ), 
                         ( uint16_t ) ( ctx->rx_pkt.payload_opt[ 3 ] ), 
                         ( uint16_t ) ( ctx->rx_pkt.payload_opt[ 4 ] ) );
            log_printf ( &logger, "   RSSI: -%u dBm\r\n", 
                         ( uint16_t ) ( ctx->rx_pkt.payload_opt[ 5 ] ) );
            log_printf ( &logger, "   Security Level: " );
            switch ( ctx->rx_pkt.payload_opt[ 6 ] )
            {
                case ENOCEAN5_ERP1_SEC_LVL_NOT_PROC:
                {
                    log_printf ( &logger, "Telegram not processed by TCM 615" );
                    break;
                }
                case ENOCEAN5_ERP1_SEC_LVL_OBSOLETE:
                {
                    log_printf ( &logger, "Obsolete (old security concept)" );
                    break;
                }
                case ENOCEAN5_ERP1_SEC_LVL_DECR:
                {
                    log_printf ( &logger, "Telegram decrypted by TCM 615" );
                    break;
                }
                case ENOCEAN5_ERP1_SEC_LVL_AUTH:
                {
                    log_printf ( &logger, "Telegram authenticated by TCM 615" );
                    break;
                }
                case ENOCEAN5_ERP1_SEC_LVL_DECR_AUTH:
                {
                    log_printf ( &logger, "Telegram decrypted + authenticated" );
                    break;
                }
                default:
                {
                    log_printf ( &logger, "Unknown[0x%.2X]", ( uint16_t ) ctx->rx_pkt.payload_opt[ 6 ] );
                    error_flag = ENOCEAN5_ERROR;
                    break;
                }
            }
            log_printf ( &logger, "\r\n" );
            break;
        }
        case ENOCEAN5_PKT_TYPE_RESPONSE:
        {
            error_flag = enocean5_parse_response ( ctx );
            break;
        }
        case ENOCEAN5_PKT_TYPE_EVENT:
        {
            error_flag = enocean5_parse_event ( ctx );
            break;
        }
        default :
        {
            log_printf ( &logger, " < Unknown Packet\r\n" );
            log_printf ( &logger, "   Payload len: %u\r\n", ctx->rx_pkt.pl_len ); 
            log_printf ( &logger, "   Payload Optional len: %u\r\n", ( uint16_t ) ctx->rx_pkt.pl_opt_len ); 
            log_printf ( &logger, "   Type: 0x%.2X\r\n", ( uint16_t ) ctx->rx_pkt.type );
            if ( ctx->rx_pkt.pl_len )
            {
                log_printf ( &logger, "   Payload:\r\n\t" );
                for ( cnt = 0; cnt < ctx->rx_pkt.pl_len; cnt++ )
                {
                    log_printf ( &logger, "%.2X ", ctx->rx_pkt.payload[ cnt ] );
                }
                log_printf ( &logger, "\r\n" );
            }
            if ( ctx->rx_pkt.pl_opt_len )
            {
                log_printf ( &logger, "   Payload Optional:\r\n\t" );
                for ( cnt = 0; cnt < ctx->rx_pkt.pl_opt_len; cnt++ )
                {
                    log_printf ( &logger, "%.2X ", ctx->rx_pkt.payload_opt[ cnt ] ); 
                }
                log_printf ( &logger, "\r\n" );
            }
            error_flag = ENOCEAN5_ERROR;
            break;
        }
    }
    return error_flag;
}

static err_t enocean5_wait_packet_w_parse ( enocean5_t *ctx, uint8_t type, uint8_t cmd, uint8_t max_time_s )
{
    uint8_t timeout_cnt = 0;
    for ( timeout_cnt = 0; timeout_cnt < max_time_s; timeout_cnt++ )
    {
        if ( ENOCEAN5_OK == enocean5_read_packet ( ctx ) )
        {
            enocean5_parse_packet ( ctx );
            if ( ctx->rx_pkt.type == type )
            {
                if ( ENOCEAN5_PKT_TYPE_RESPONSE == ctx->rx_pkt.type )
                {
                    return ctx->rx_pkt.payload[ 0 ];
                }
                if ( ctx->rx_pkt.payload[ 0 ] == cmd )
                {
                    return ENOCEAN5_OK;
                }
            }
        }
    } 
    return ENOCEAN5_ERROR;
}

// ------------------------------------------------------------------------ END
