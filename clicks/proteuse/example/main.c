/*!
 * @file main.c
 * @brief Proteus-e Click Example.
 *
 * # Description
 * This example demonstrates the use of Proteus-e Click board by processing data
 * from a connected BT device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, resets and configures the Click board, and reads the device info.
 *
 * ## Application Task
 * Reads and parses all the received event packets and displays them the USB UART.
 * All incoming data messages received from the connected device will be echoed back.
 *
 * ## Additional Function
 * - static err_t proteuse_parse_cnf ( proteuse_t *ctx )
 * - static err_t proteuse_parse_rsp ( proteuse_t *ctx )
 * - static err_t proteuse_parse_ind ( proteuse_t *ctx )
 * - static err_t proteuse_parse_event ( proteuse_t *ctx )
 *
 * @note
 * We recommend using the WE Bluetooth LE Terminal smartphone application for the test.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proteuse.h"

// BT device name.
#define DEVICE_NAME         "Proteus-e Click"

static proteuse_t proteuse;
static log_t logger;

/**
 * @brief Proteus-e parse cnf function.
 * @details This function parses all received confirmation packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c 1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t proteuse_parse_cnf ( proteuse_t *ctx );

/**
 * @brief Proteus-e parse ind function.
 * @details This function parses all received response packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c 1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t proteuse_parse_rsp ( proteuse_t *ctx );

/**
 * @brief Proteus-e parse ind function.
 * @details This function parses all received indication packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c 1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t proteuse_parse_ind ( proteuse_t *ctx );

/**
 * @brief Proteus-e parse event function.
 * @details This function parses all received packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #proteuse_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c 1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t proteuse_parse_event ( proteuse_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proteuse_cfg_t proteuse_cfg;  /**< Click config object. */

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
    proteuse_cfg_setup( &proteuse_cfg );
    PROTEUSE_MAP_MIKROBUS( proteuse_cfg, MIKROBUS_1 );
    if ( UART_ERROR == proteuse_init( &proteuse, &proteuse_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROTEUSE_ERROR == proteuse_default_cfg ( &proteuse ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, ">> Get device info.\r\n" );
    if ( PROTEUSE_OK == proteuse_get_user_setting ( &proteuse, PROTEUSE_SET_IDX_FS_DEVICE_INFO ) ) 
    {
        log_printf( &logger, " < OS version: 0x%.2X%.2X\r\n", 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 2 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 1 ] );
        log_printf( &logger, "   Build code: 0x%.2X%.2X%.2X%.2X\r\n", 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 6 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 5 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 4 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 3 ] );
        log_printf( &logger, "   Package variant: 0x%.2X%.2X\r\n", 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 8 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 7 ] );
        log_printf( &logger, "   Chip ID: 0x%.2X%.2X%.2X%.2X\r\n\n", 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 12 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 11 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 10 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 9 ] );
    }

    log_printf( &logger, ">> Get FW version.\r\n" );
    if ( PROTEUSE_OK == proteuse_get_user_setting ( &proteuse, PROTEUSE_SET_IDX_FS_FW_VERSION ) ) 
    {
        log_printf( &logger, " < FW version: %u.%u.%u\r\n\n", 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 3 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 2 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 1 ] );
    }

    log_printf( &logger, ">> Get BT MAC.\r\n" );
    if ( PROTEUSE_OK == proteuse_get_user_setting ( &proteuse, PROTEUSE_SET_IDX_FS_BTMAC ) ) 
    {
        log_printf( &logger, " < BT MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n\n", 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 6 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 5 ],
                    ( uint16_t ) proteuse.evt_pkt.payload[ 4 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 3 ],
                    ( uint16_t ) proteuse.evt_pkt.payload[ 2 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 1 ] );
    }

    log_printf( &logger, ">> Set device name to \"%s\".\r\n", ( char * ) DEVICE_NAME );
    if ( PROTEUSE_OK == proteuse_set_user_setting ( &proteuse, PROTEUSE_SET_IDX_RF_DEVICE_NAME, 
                                                    DEVICE_NAME, strlen ( DEVICE_NAME ) ) )
    {
        log_printf( &logger, " < Request received, settings set successfully\r\n\n" );
    }

    log_printf( &logger, ">> Get device name.\r\n" );
    if ( PROTEUSE_OK == proteuse_get_user_setting ( &proteuse, PROTEUSE_SET_IDX_RF_DEVICE_NAME ) ) 
    {
        log_printf( &logger, " < Device name: \"%s\"\r\n\n", &proteuse.evt_pkt.payload[ 1 ] );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( PROTEUSE_OK == proteuse_read_event ( &proteuse ) ) 
    {
        proteuse_parse_event ( &proteuse );
    }
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

static err_t proteuse_parse_cnf ( proteuse_t *ctx )
{
    err_t error_flag = PROTEUSE_OK;
    uint16_t byte_cnt = 0;

    if ( PROTEUSE_CMD_TYPE_CNF == ( ctx->evt_pkt.cmd & PROTEUSE_CMD_TYPE_MASK ) )
    {
        // Parse confirmation packet
        switch ( ctx->evt_pkt.cmd )
        {
            case PROTEUSE_CMD_CNF_GET_STATE:
            {
                log_printf( &logger, " < GET_STATE_CNF -> Role: 0x%.2X, Actions: 0x%.2X", 
                            ( uint16_t ) ctx->evt_pkt.payload[ 0 ], ( uint16_t ) ctx->evt_pkt.payload[ 1 ] );
                if ( ctx->evt_pkt.payload_len > 2 )
                {
                    log_printf( &logger, "\r\n   More info: " );
                    for ( byte_cnt = 2; byte_cnt < ctx->evt_pkt.payload_len; byte_cnt++ )
                    {
                        log_printf( &logger, "0x%.2X ", ( uint16_t ) ctx->evt_pkt.payload[ byte_cnt ] );
                    }
                }
                break;
            }
            case PROTEUSE_CMD_CNF_GET:
            {
                log_printf( &logger, " < GET_CNF -> " );
                switch ( ctx->evt_pkt.payload[ 0 ] )
                {
                    case PROTEUSE_CNF_GET_STATUS_OK:
                    {
                        log_printf( &logger, "Request received, read out of setting successful" );
                        break;
                    }
                    case PROTEUSE_CNF_GET_STATUS_FAILED:
                    {
                        log_printf( &logger, "Operation failed" );
                        break;
                    }
                    case PROTEUSE_CNF_GET_STATUS_NOT_PERMITTED:
                    {
                        log_printf( &logger, "Operation not permitted" );
                        break;
                    }
                    default:
                    {
                        log_printf( &logger, "Unknown status: 0x%.2X", ( uint16_t ) ctx->evt_pkt.payload[ 0 ] );
                        break;
                    }
                }
                if ( ctx->evt_pkt.payload_len > 1 )
                {
                    log_printf( &logger, "\r\n   Setting: " );
                    for ( byte_cnt = 1; byte_cnt < ctx->evt_pkt.payload_len; byte_cnt++ )
                    {
                        log_printf( &logger, "0x%.2X ", ( uint16_t ) ctx->evt_pkt.payload[ byte_cnt ] );
                    }
                }
                break;
            }
            case PROTEUSE_CMD_CNF_DATA:
            {
                log_printf( &logger, " < DATA_CNF -> " );
                switch ( ctx->evt_pkt.payload[ 0 ] )
                {
                    case PROTEUSE_CNF_DATA_STATUS_OK:
                    {
                        log_printf( &logger, "Request received, will send data now" );
                        break;
                    }
                    case PROTEUSE_CNF_DATA_STATUS_FAILED:
                    {
                        log_printf( &logger, "Operation failed" );
                        break;
                    }
                    case PROTEUSE_CNF_DATA_STATUS_NOT_PERMITTED:
                    {
                        log_printf( &logger, "Operation not permitted" );
                        break;
                    }
                    default:
                    {
                        log_printf( &logger, "Unknown status: 0x%.2X", ( uint16_t ) ctx->evt_pkt.payload[ 0 ] );
                        break;
                    }
                }
                break;
            }
            default:
            {
                log_printf( &logger, " < CMD_CNF 0x%.2X -> ", ( uint16_t ) ctx->evt_pkt.cmd );
                for ( byte_cnt = 0; byte_cnt < ctx->evt_pkt.payload_len; byte_cnt++ )
                {
                    log_printf( &logger, "0x%.2X ", ( uint16_t ) ctx->evt_pkt.payload[ byte_cnt ] );
                }
                break;
            }
        }
        log_printf( &logger, "\r\n\n" );
    }
    else
    {
        // Wrong packet type
        error_flag |= PROTEUSE_ERROR;
    }
    return error_flag;
}

static err_t proteuse_parse_rsp ( proteuse_t *ctx )
{
    err_t error_flag = PROTEUSE_OK;

    if ( PROTEUSE_CMD_TYPE_RSP == ( ctx->evt_pkt.cmd & PROTEUSE_CMD_TYPE_MASK ) )
    {
        // Parse response packet
        if ( PROTEUSE_CMD_RSP_TX_COMPLETE == ctx->evt_pkt.cmd )
        {
            log_printf( &logger, " < TX_COMPLETE_IND -> " );
            if ( ctx->evt_pkt.payload[ 0 ] )
            {
                log_printf( &logger, "Data transmission failed" );
            }
            else
            {
                log_printf( &logger, "Data transmitted successfully" );
            }
        }
        else if ( PROTEUSE_CMD_RSP_CHANNEL_OPEN == ctx->evt_pkt.cmd )
        {
            log_printf( &logger, " < CHANNEL_OPEN_RSP -> " );
            if ( ctx->evt_pkt.payload[ 0 ] )
            {
                log_printf( &logger, "Failed" );
            }
            else
            {
                log_printf( &logger, "MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X, MPS: %u", 
                            ( uint16_t ) ctx->evt_pkt.payload[ 6 ], ( uint16_t ) ctx->evt_pkt.payload[ 5 ],
                            ( uint16_t ) ctx->evt_pkt.payload[ 4 ], ( uint16_t ) ctx->evt_pkt.payload[ 3 ],
                            ( uint16_t ) ctx->evt_pkt.payload[ 2 ], ( uint16_t ) ctx->evt_pkt.payload[ 1 ],
                            ( uint16_t ) ctx->evt_pkt.payload[ 7 ] );
            }
        }
        else
        {
            log_printf( &logger, " < UNKNOWN_RSP 0x%.2X", ( uint16_t ) ctx->evt_pkt.cmd );
        }
        log_printf( &logger, "\r\n\n" );
    }
    else
    {
        // Wrong packet type
        error_flag |= PROTEUSE_ERROR;
    }
    return error_flag;
}

static err_t proteuse_parse_ind ( proteuse_t *ctx )
{
    err_t error_flag = PROTEUSE_OK;
    uint16_t byte_cnt = 0;

    if ( PROTEUSE_CMD_TYPE_IND == ( ctx->evt_pkt.cmd & PROTEUSE_CMD_TYPE_MASK ) )
    {
        // Parse indication packet
        switch ( ctx->evt_pkt.cmd )
        {
            case PROTEUSE_CMD_IND_SLEEP:
            {
                log_printf( &logger, " < SLEEP_IND -> Advertising timeout detected, will go to sleep now" );
                break;
            }
            case PROTEUSE_CMD_IND_DATA:
            {
                log_printf( &logger, " < DATA_IND -> " );
                log_printf( &logger, "MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X, RSSI: %d\r\n", 
                            ( uint16_t ) ctx->evt_pkt.payload[ 5 ], ( uint16_t ) ctx->evt_pkt.payload[ 4 ],
                            ( uint16_t ) ctx->evt_pkt.payload[ 3 ], ( uint16_t ) ctx->evt_pkt.payload[ 2 ],
                            ( uint16_t ) ctx->evt_pkt.payload[ 1 ], ( uint16_t ) ctx->evt_pkt.payload[ 0 ],
                            ( int16_t ) ( ( int8_t ) ctx->evt_pkt.payload[ 6 ] ) );
                log_printf( &logger, "   Data (HEX): " );
                for ( byte_cnt = 7; byte_cnt < ctx->evt_pkt.payload_len; byte_cnt++ )
                {
                    log_printf( &logger, "0x%.2X ", ( uint16_t ) ctx->evt_pkt.payload[ byte_cnt ] );
                }
                ctx->evt_pkt.payload[ ctx->evt_pkt.payload_len ] = 0;
                log_printf( &logger, "\r\n   Data (STR): %s", &ctx->evt_pkt.payload[ 7 ] );
                
                log_printf( &logger, "\r\n\n>> Echo back the received message." );
                ctx->cmd_pkt.cmd = PROTEUSE_CMD_REQ_DATA;
                ctx->cmd_pkt.payload_len = ctx->evt_pkt.payload_len - 7;
                memcpy ( &ctx->cmd_pkt.payload[ 0 ], &ctx->evt_pkt.payload[ 7 ], ctx->evt_pkt.payload_len - 7 );
                proteuse_send_cmd ( ctx );
                break;
            }
            case PROTEUSE_CMD_IND_CONNECT:
            {
                log_printf( &logger, " < CONNECT_IND -> " );
                if ( ctx->evt_pkt.payload[ 0 ] )
                {
                    log_printf( &logger, "Connection failed, e.g. due to a timeout" );
                }
                else
                {
                    log_printf( &logger, "MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X", 
                                ( uint16_t ) ctx->evt_pkt.payload[ 6 ], ( uint16_t ) ctx->evt_pkt.payload[ 5 ],
                                ( uint16_t ) ctx->evt_pkt.payload[ 4 ], ( uint16_t ) ctx->evt_pkt.payload[ 3 ],
                                ( uint16_t ) ctx->evt_pkt.payload[ 2 ], ( uint16_t ) ctx->evt_pkt.payload[ 1 ] );
                }
                break;
            }
            case PROTEUSE_CMD_IND_DISCONNECT:
            {
                log_printf( &logger, " < DISCONNECT_IND -> " );
                switch ( ctx->evt_pkt.payload[ 0 ] )
                {
                    case PROTEUSE_IND_DISC_REASON_TIMEOUT:
                    {
                        log_printf( &logger, "Connection timeout" );
                        break;
                    }
                    case PROTEUSE_IND_DISC_REASON_USER_TERM:
                    {
                        log_printf( &logger, "User terminated connection" );
                        break;
                    }
                    case PROTEUSE_IND_DISC_REASON_HOST_TERM:
                    {
                        log_printf( &logger, "Host terminated connection" );
                        break;
                    }
                    case PROTEUSE_IND_DISC_REASON_CONN_INTERVAL:
                    {
                        log_printf( &logger, "Connection interval unacceptable" );
                        break;
                    }
                    case PROTEUSE_IND_DISC_REASON_MIC_FAILURE:
                    {
                        log_printf( &logger, "Connection terminated due to MIC failure" );
                        break;
                    }
                    case PROTEUSE_IND_DISC_REASON_SETUP_FAILED:
                    {
                        log_printf( &logger, "Connection setup failed" );
                        break;
                    }
                    default:
                    {
                        log_printf( &logger, "Unknown reason: 0x%.2X", ( uint16_t ) ctx->evt_pkt.payload[ 0 ] );
                        break;
                    }
                }
                break;
            }
            case PROTEUSE_CMD_IND_SECURITY:
            {
                log_printf( &logger, " < SECURITY_IND -> " );
                switch ( ctx->evt_pkt.payload[ 0 ] )
                {
                    case PROTEUSE_IND_SEC_STATUS_RE_BONDED:
                    {
                        log_printf( &logger, "Encrypted link to previously bonded device established\r\n" );
                        break;
                    }
                    case PROTEUSE_IND_SEC_STATUS_BONDED:
                    {
                        log_printf( &logger, "Bonding successful, encrypted link established\r\n" );
                        break;
                    }
                    case PROTEUSE_IND_SEC_STATUS_PAIRED:
                    {
                        log_printf( &logger, "No bonding, pairing successful, encrypted link established\r\n" );
                        break;
                    }
                    default:
                    {
                        log_printf( &logger, "Unknown status: 0x%.2X", ( uint16_t ) ctx->evt_pkt.payload[ 0 ] );
                        break;
                    }
                }
                log_printf( &logger, "   MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X", 
                            ( uint16_t ) ctx->evt_pkt.payload[ 6 ], ( uint16_t ) ctx->evt_pkt.payload[ 5 ],
                            ( uint16_t ) ctx->evt_pkt.payload[ 4 ], ( uint16_t ) ctx->evt_pkt.payload[ 3 ],
                            ( uint16_t ) ctx->evt_pkt.payload[ 2 ], ( uint16_t ) ctx->evt_pkt.payload[ 1 ] );
                break;
            }
            case PROTEUSE_CMD_IND_PHY_UPDATE:
            {
                log_printf( &logger, " < PHY_UPDATE_IND -> " );
                if ( ctx->evt_pkt.payload[ 0 ] )
                {
                    log_printf( &logger, "Unsupported feature of remote device" );
                }
                else
                {
                    log_printf( &logger, "RX: %uMBit, TX: %uMBit, ", 
                                ( uint16_t ) ctx->evt_pkt.payload[ 1 ], ( uint16_t ) ctx->evt_pkt.payload[ 2 ] );
                    log_printf( &logger, "MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X", 
                                ( uint16_t ) ctx->evt_pkt.payload[ 8 ], ( uint16_t ) ctx->evt_pkt.payload[ 7 ],
                                ( uint16_t ) ctx->evt_pkt.payload[ 6 ], ( uint16_t ) ctx->evt_pkt.payload[ 5 ],
                                ( uint16_t ) ctx->evt_pkt.payload[ 4 ], ( uint16_t ) ctx->evt_pkt.payload[ 3 ] );
                }
                break;
            }
            case PROTEUSE_CMD_IND_UART_ENABLE:
            {
                log_printf( &logger, " < UART_ENABLE_IND -> UART has been re-enabled successfully" );
                break;
            }
            case PROTEUSE_CMD_IND_ERROR:
            {
                log_printf( &logger, " < ERROR_IND -> UART buffer overflow" );
                break;
            }
            default:
            {
                log_printf( &logger, " < CMD_IND 0x%.2X -> ", ( uint16_t ) ctx->evt_pkt.cmd );
                for ( byte_cnt = 0; byte_cnt < ctx->evt_pkt.payload_len; byte_cnt++ )
                {
                    log_printf( &logger, "0x%.2X ", ( uint16_t ) ctx->evt_pkt.payload[ byte_cnt ] );
                }
                break;
            }
        }
        log_printf( &logger, "\r\n\n" );
    }
    else
    {
        // Wrong packet type
        error_flag |= PROTEUSE_ERROR;
    }
    return error_flag;
}

static err_t proteuse_parse_event ( proteuse_t *ctx )
{
    err_t error_flag = PROTEUSE_OK;

    if ( PROTEUSE_CMD_TYPE_CNF == ( ctx->evt_pkt.cmd & PROTEUSE_CMD_TYPE_MASK ) )
    {
        error_flag |= proteuse_parse_cnf ( ctx );
    }
    else if ( PROTEUSE_CMD_TYPE_RSP == ( ctx->evt_pkt.cmd & PROTEUSE_CMD_TYPE_MASK ) )
    {
        error_flag |= proteuse_parse_rsp ( ctx );
    }
    else if ( PROTEUSE_CMD_TYPE_IND == ( ctx->evt_pkt.cmd & PROTEUSE_CMD_TYPE_MASK ) )
    {
        error_flag |= proteuse_parse_ind ( ctx );
    }
    else
    {
        // Error packet should not be a command request
        error_flag |= PROTEUSE_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END
