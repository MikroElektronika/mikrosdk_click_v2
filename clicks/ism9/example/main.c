/*!
 * @file main.c
 * @brief ISM 9 Click Example.
 *
 * # Description
 * This example demonstrates the use of ISM 9 Click board by showing
 * the communication between two Click boards.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, resets the Click board, reads the device info, and sends
 * a message to initiate the communication with other Click board.
 *
 * ## Application Task
 * Reads and parses all the received event packets and displays them the USB UART.
 * All incoming data messages received from the connected device will be echoed back.
 *
 * ## Additional Function
 * - static err_t ism9_parse_cnf ( ism9_t *ctx )
 * - static err_t ism9_parse_ind ( ism9_t *ctx )
 * - static err_t ism9_parse_event ( ism9_t *ctx )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ism9.h"

#ifndef MIKROBUS_POSITION_ISM9
    #define MIKROBUS_POSITION_ISM9 MIKROBUS_1
#endif

// Text message to send to initiate communication
#define DEMO_TEXT_MESSAGE   "MIKROE - ISM 9 Click board"

static ism9_t ism9;
static log_t logger;

/**
 * @brief ISM 9 parse cnf function.
 * @details This function parses all received confirmation packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c 1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ism9_parse_cnf ( ism9_t *ctx );

/**
 * @brief ISM 9 parse ind function.
 * @details This function parses all received indication packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c 1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ism9_parse_ind ( ism9_t *ctx );

/**
 * @brief ISM 9 parse event function.
 * @details This function parses all received packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #ism9_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c 1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ism9_parse_event ( ism9_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ism9_cfg_t ism9_cfg;  /**< Click config object. */

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
    ism9_cfg_setup( &ism9_cfg );
    ISM9_MAP_MIKROBUS( ism9_cfg, MIKROBUS_POSITION_ISM9 );
    if ( UART_ERROR == ism9_init( &ism9, &ism9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, ">> Reset device.\r\n" );
    if ( ISM9_ERROR == ism9_reset_device ( &ism9 ) )
    {
        log_error( &logger, " Reset device." );
        for ( ; ; );
    }
    ism9_parse_event ( &ism9 );
    
    log_printf( &logger, ">> Get device info.\r\n" );
    if ( ISM9_OK == ism9_get_user_setting ( &ism9, ISM9_SET_IDX_FACTORY_SETTINGS ) ) 
    {
        log_printf( &logger, " < Serial number: 0x%.2X%.2X%.2X%.2X\r\n", 
                    ( uint16_t ) ism9.evt_pkt.payload[ 4 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 3 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 2 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 1 ] );
        log_printf( &logger, "   Hardware version: %u.%u.%u\r\n", 
                    ( uint16_t ) ism9.evt_pkt.payload[ 5 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 6 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 7 ] );
        log_printf( &logger, "   Frequency correction factor: %u\r\n",  
                    ( uint16_t ) ism9.evt_pkt.payload[ 8 ] );
    }

    log_printf( &logger, ">> Get FW version.\r\n" );
    if ( ISM9_OK == ism9_get_user_setting ( &ism9, ISM9_SET_IDX_FIRMWARE_VERSION ) ) 
    {
        log_printf( &logger, " < FW version: %u.%u.%u\r\n\n", 
                    ( uint16_t ) ism9.evt_pkt.payload[ 3 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 2 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 1 ] );
    }

    log_printf( &logger, ">> Send message to initiate communication.\r\n" );
    ism9.cmd_pkt.cmd = ISM9_CMD_REQ_DATA;
    ism9.cmd_pkt.payload_len = strlen ( DEMO_TEXT_MESSAGE );
    strcpy ( ism9.cmd_pkt.payload, DEMO_TEXT_MESSAGE );
    if ( ISM9_OK == ism9_send_cmd ( &ism9 ) )
    {
        if ( ISM9_OK == ism9_wait_for_event ( &ism9, ISM9_CMD_CNF_DATA, ISM9_WAIT_TIME_1S ) ) 
        {
            ism9_parse_event ( &ism9 );
        }
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( ISM9_OK == ism9_read_event ( &ism9 ) ) 
    {
        ism9_parse_event ( &ism9 );
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

static err_t ism9_parse_cnf ( ism9_t *ctx )
{
    err_t error_flag = ISM9_OK;
    uint16_t byte_cnt = 0;

    if ( ISM9_CMD_TYPE_CNF == ( ctx->evt_pkt.cmd & ISM9_CMD_TYPE_MASK ) )
    {
        // Parse confirmation packet
        switch ( ctx->evt_pkt.cmd )
        {
            case ISM9_CMD_CNF_GET:
            {
                log_printf( &logger, " < GET_CNF -> " );
                switch ( ctx->evt_pkt.payload[ 0 ] )
                {
                    case ISM9_CNF_GET_STATUS_OK:
                    {
                        log_printf( &logger, "Request successfully received and processed" );
                        break;
                    }
                    case ISM9_CNF_GET_STATUS_FAILED:
                    {
                        log_printf( &logger, "Request not successful" );
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
            case ISM9_CMD_CNF_DATA:
            {
                log_printf( &logger, " < DATA_CNF -> " );
                switch ( ctx->evt_pkt.payload[ 0 ] )
                {
                    case ISM9_CNF_DATA_STATUS_ACK:
                    {
                        log_printf( &logger, "ACK received or not requested" );
                        break;
                    }
                    case ISM9_CNF_DATA_STATUS_NACK:
                    {
                        log_printf( &logger, "No ACK received within a time-out " );
                        break;
                    }
                    case ISM9_CNF_DATA_STATUS_INVALID_CH:
                    {
                        log_printf( &logger, "Invalid channel selected" );
                        break;
                    }
                    case ISM9_CNF_DATA_STATUS_RADIO_CH_BUSY:
                    {
                        log_printf( &logger, "Radio channel busy (LBT)" );
                        break;
                    }
                    case ISM9_CNF_DATA_STATUS_MODULE_BUSY:
                    {
                        log_printf( &logger, "Module is currently busy" );
                        break;
                    }
                    case ISM9_CNF_DATA_STATUS_INVALID:
                    {
                        log_printf( &logger, "Invalid (payload too long)" );
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
        error_flag |= ISM9_ERROR;
    }
    return error_flag;
}

static err_t ism9_parse_ind ( ism9_t *ctx )
{
    err_t error_flag = ISM9_OK;
    uint16_t byte_cnt = 0;

    if ( ISM9_CMD_TYPE_IND == ( ctx->evt_pkt.cmd & ISM9_CMD_TYPE_MASK ) )
    {
        // Parse indication packet
        switch ( ctx->evt_pkt.cmd )
        {
            case ISM9_CMD_IND_DATAEX:
            {
                log_printf( &logger, " < DATAEX_IND -> " );
                int16_t field_str = ( ( int8_t ) ctx->evt_pkt.payload[ ctx->evt_pkt.payload_len - 1 ] );
                log_printf( &logger, "Field strength: %d\r\n", field_str );
                log_printf( &logger, "   Data (HEX): " );
                for ( byte_cnt = 0; byte_cnt < ( ctx->evt_pkt.payload_len - 1 ); byte_cnt++ )
                {
                    log_printf( &logger, "0x%.2X ", ( uint16_t ) ctx->evt_pkt.payload[ byte_cnt ] );
                }
                Delay_ms ( 10 );
                ctx->evt_pkt.payload[ ctx->evt_pkt.payload_len - 1 ] = 0;
                log_printf( &logger, "\r\n   Data (STR): %s\r\n", &ctx->evt_pkt.payload[ 0 ] );
                
                Delay_ms ( 1000 );
                log_printf( &logger, "\r\n>> Echo back the received message." );
                ctx->cmd_pkt.cmd = ISM9_CMD_REQ_DATA;
                ctx->cmd_pkt.payload_len = ctx->evt_pkt.payload_len - 1;
                memcpy ( &ctx->cmd_pkt.payload[ 0 ], &ctx->evt_pkt.payload[ 0 ], ctx->evt_pkt.payload_len - 1 );
                error_flag |= ism9_send_cmd ( ctx );
                break;
            }
            case ISM9_CMD_IND_RESET:
            {
                log_printf( &logger, " < RESET_IND" );
                break;
            }
            case ISM9_CMD_IND_STANDBY:
            {
                log_printf( &logger, " < STANDBY_IND" );
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
        error_flag |= ISM9_ERROR;
    }
    return error_flag;
}

static err_t ism9_parse_event ( ism9_t *ctx )
{
    err_t error_flag = ISM9_OK;

    if ( ISM9_CMD_TYPE_CNF == ( ctx->evt_pkt.cmd & ISM9_CMD_TYPE_MASK ) )
    {
        error_flag |= ism9_parse_cnf ( ctx );
    }
    else if ( ISM9_CMD_TYPE_IND == ( ctx->evt_pkt.cmd & ISM9_CMD_TYPE_MASK ) )
    {
        error_flag |= ism9_parse_ind ( ctx );
    }
    else
    {
        // Error packet should not be a command request
        error_flag |= ISM9_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END
