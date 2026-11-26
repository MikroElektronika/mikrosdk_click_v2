/*!
 * @file main.c
 * @brief Proteus-II Click Example.
 *
 * # Description
 * This example demonstrates the use of Proteus-II Click board by processing data
 * from a connected BT device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, resets and configures the Click board, and reads the device info.
 *
 * ## Application Task
 * Reads and parses all the received event packets and displays them on the USB UART.
 * All incoming data messages received from the connected device will be echoed back.
 *
 * ## Additional Function
 * - static err_t proteusii_parse_cnf ( proteusii_t *ctx )
 * - static err_t proteusii_parse_rsp ( proteusii_t *ctx )
 * - static err_t proteusii_parse_ind ( proteusii_t *ctx )
 * - static err_t proteusii_parse_event ( proteusii_t *ctx )
 *
 * @note
 * Set MODE to C for normal command mode. Use the WE Bluetooth LE Terminal
 * smartphone application and enable notifications before sending data.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proteusii.h"

#ifndef MIKROBUS_POSITION_PROTEUSII
    #define MIKROBUS_POSITION_PROTEUSII MIKROBUS_1
#endif

static proteusii_t proteusii;
static log_t logger;

/**
 * @brief Proteus-II parse cnf function.
 * @details This function parses all received confirmation packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t proteusii_parse_cnf ( proteusii_t *ctx );

/**
 * @brief Proteus-II parse rsp function.
 * @details This function parses all received response packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t proteusii_parse_rsp ( proteusii_t *ctx );

/**
 * @brief Proteus-II parse ind function.
 * @details This function parses all received indication packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t proteusii_parse_ind ( proteusii_t *ctx );

/**
 * @brief Proteus-II parse event function.
 * @details This function parses all received packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #proteusii_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t proteusii_parse_event ( proteusii_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proteusii_cfg_t proteusii_cfg;  /**< Click config object. */

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
    proteusii_cfg_setup( &proteusii_cfg );
    PROTEUSII_MAP_MIKROBUS( proteusii_cfg, MIKROBUS_POSITION_PROTEUSII );
    if ( UART_ERROR == proteusii_init( &proteusii, &proteusii_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, ">> Reset device.\r\n" );
    if ( PROTEUSII_OK == proteusii_reset_device ( &proteusii ) )
    {
        log_printf( &logger, " < OK.\r\n" );
    }
    else
    {
        log_error( &logger, " Reset device." );
        for ( ; ; );
    }

    log_printf( &logger, ">> Get device info.\r\n" );
    if ( PROTEUSII_OK == proteusii_get_user_setting ( &proteusii, PROTEUSII_SET_IDX_FS_DEVICE_INFO ) )
    {
        log_printf( &logger, " < OS version: 0x%.2X%.2X\r\n",
                    ( uint16_t ) proteusii.evt_pkt.payload[ 2 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 1 ] );
        log_printf( &logger, "   Build code: 0x%.2X%.2X%.2X%.2X\r\n",
                    ( uint16_t ) proteusii.evt_pkt.payload[ 6 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 5 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 4 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 3 ] );
        log_printf( &logger, "   Package variant: 0x%.2X%.2X\r\n",
                    ( uint16_t ) proteusii.evt_pkt.payload[ 8 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 7 ] );
        log_printf( &logger, "   Chip ID: 0x%.2X%.2X%.2X%.2X\r\n\n",
                    ( uint16_t ) proteusii.evt_pkt.payload[ 12 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 11 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 10 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 9 ] );
    }

    log_printf( &logger, ">> Get FW version.\r\n" );
    if ( PROTEUSII_OK == proteusii_get_user_setting ( &proteusii, PROTEUSII_SET_IDX_FS_FW_VERSION ) )
    {
        log_printf( &logger, " < FW version: %u.%u.%u\r\n\n",
                    ( uint16_t ) proteusii.evt_pkt.payload[ 3 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 2 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 1 ] );
    }

    log_printf( &logger, ">> Get BT MAC.\r\n" );
    if ( PROTEUSII_OK == proteusii_get_user_setting ( &proteusii, PROTEUSII_SET_IDX_FS_BTMAC ) )
    {
        log_printf( &logger, " < BT MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n\n",
                    ( uint16_t ) proteusii.evt_pkt.payload[ 6 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 5 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 4 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 3 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 2 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 1 ] );
    }

    log_printf( &logger, ">> Get device name.\r\n" );
    if ( PROTEUSII_OK == proteusii_get_user_setting ( &proteusii, PROTEUSII_SET_IDX_RF_DEVICE_NAME ) )
    {
        log_printf( &logger, " < Device name: \"%s\"\r\n\n", &proteusii.evt_pkt.payload[ 1 ] );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( PROTEUSII_OK == proteusii_read_event ( &proteusii ) )
    {
        proteusii_parse_event ( &proteusii );
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

static err_t proteusii_parse_cnf ( proteusii_t *ctx )
{
    err_t error_flag = PROTEUSII_OK;
    uint16_t byte_cnt = 0;

    if ( PROTEUSII_CMD_TYPE_CNF == ( ctx->evt_pkt.cmd & PROTEUSII_CMD_TYPE_MASK ) )
    {
        // Parse confirmation packet
        switch ( ctx->evt_pkt.cmd )
        {
            case PROTEUSII_CMD_CNF_GET_STATE:
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
            case PROTEUSII_CMD_CNF_GET:
            {
                log_printf( &logger, " < GET_CNF -> " );
                switch ( ctx->evt_pkt.payload[ 0 ] )
                {
                    case PROTEUSII_CNF_GET_STATUS_OK:
                    {
                        log_printf( &logger, "Request received, read out of setting successful" );
                        break;
                    }
                    case PROTEUSII_CNF_GET_STATUS_FAILED:
                    {
                        log_printf( &logger, "Operation failed" );
                        break;
                    }
                    case PROTEUSII_CNF_GET_STATUS_NOT_PERMITTED:
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
            case PROTEUSII_CMD_CNF_DATA:
            {
                log_printf( &logger, " < DATA_CNF -> " );
                switch ( ctx->evt_pkt.payload[ 0 ] )
                {
                    case PROTEUSII_CNF_DATA_STATUS_OK:
                    {
                        log_printf( &logger, "Request received, will send data now" );
                        break;
                    }
                    case PROTEUSII_CNF_DATA_STATUS_FAILED:
                    {
                        log_printf( &logger, "Operation failed" );
                        break;
                    }
                    case PROTEUSII_CNF_DATA_STATUS_NOT_PERMITTED:
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
        error_flag |= PROTEUSII_ERROR;
    }
    return error_flag;
}

static err_t proteusii_parse_rsp ( proteusii_t *ctx )
{
    err_t error_flag = PROTEUSII_OK;

    if ( PROTEUSII_CMD_TYPE_RSP == ( ctx->evt_pkt.cmd & PROTEUSII_CMD_TYPE_MASK ) )
    {
        // Parse response packet
        if ( PROTEUSII_CMD_RSP_TX_COMPLETE == ctx->evt_pkt.cmd )
        {
            log_printf( &logger, " < TX_COMPLETE_RSP -> " );
            if ( ctx->evt_pkt.payload[ 0 ] )
            {
                log_printf( &logger, "Data transmission failed" );
            }
            else
            {
                log_printf( &logger, "Data transmitted successfully" );
            }
        }
        else if ( PROTEUSII_CMD_RSP_CHANNEL_OPEN == ctx->evt_pkt.cmd )
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
        error_flag |= PROTEUSII_ERROR;
    }
    return error_flag;
}

static err_t proteusii_parse_ind ( proteusii_t *ctx )
{
    err_t error_flag = PROTEUSII_OK;
    uint16_t byte_cnt = 0;

    if ( PROTEUSII_CMD_TYPE_IND == ( ctx->evt_pkt.cmd & PROTEUSII_CMD_TYPE_MASK ) )
    {
        // Parse indication packet
        switch ( ctx->evt_pkt.cmd )
        {
            case PROTEUSII_CMD_IND_SLEEP:
            {
                log_printf( &logger, " < SLEEP_IND -> Advertising timeout detected, will go to sleep now" );
                break;
            }
            case PROTEUSII_CMD_IND_DATA:
            {
                // DATA_IND starts with the six-byte MAC and one-byte RSSI.
                if ( ctx->evt_pkt.payload_len < 7 )
                {
                    error_flag |= PROTEUSII_ERROR;
                    break;
                }
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
                ctx->cmd_pkt.cmd = PROTEUSII_CMD_REQ_DATA;
                ctx->cmd_pkt.payload_len = ctx->evt_pkt.payload_len - 7;
                memcpy ( &ctx->cmd_pkt.payload[ 0 ], &ctx->evt_pkt.payload[ 7 ], ctx->evt_pkt.payload_len - 7 );
                proteusii_send_cmd ( ctx );
                break;
            }
            case PROTEUSII_CMD_IND_CONNECT:
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
            case PROTEUSII_CMD_IND_DISCONNECT:
            {
                log_printf( &logger, " < DISCONNECT_IND -> " );
                switch ( ctx->evt_pkt.payload[ 0 ] )
                {
                    case PROTEUSII_IND_DISC_REASON_TIMEOUT:
                    {
                        log_printf( &logger, "Connection timeout" );
                        break;
                    }
                    case PROTEUSII_IND_DISC_REASON_USER_TERM:
                    {
                        log_printf( &logger, "User terminated connection" );
                        break;
                    }
                    case PROTEUSII_IND_DISC_REASON_HOST_TERM:
                    {
                        log_printf( &logger, "Host terminated connection" );
                        break;
                    }
                    case PROTEUSII_IND_DISC_REASON_CONN_INTERVAL:
                    {
                        log_printf( &logger, "Connection interval unacceptable" );
                        break;
                    }
                    case PROTEUSII_IND_DISC_REASON_MIC_FAILURE:
                    {
                        log_printf( &logger, "Connection terminated due to MIC failure" );
                        break;
                    }
                    case PROTEUSII_IND_DISC_REASON_SETUP_FAILED:
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
            case PROTEUSII_CMD_IND_SECURITY:
            {
                log_printf( &logger, " < SECURITY_IND -> " );
                switch ( ctx->evt_pkt.payload[ 0 ] )
                {
                    case PROTEUSII_IND_SEC_STATUS_RE_BONDED:
                    {
                        log_printf( &logger, "Encrypted link to previously bonded device established\r\n" );
                        break;
                    }
                    case PROTEUSII_IND_SEC_STATUS_BONDED:
                    {
                        log_printf( &logger, "Bonding successful, encrypted link established\r\n" );
                        break;
                    }
                    case PROTEUSII_IND_SEC_STATUS_PAIRED:
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
            case PROTEUSII_CMD_IND_PHY_UPDATE:
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
            case PROTEUSII_CMD_IND_UART_ENABLE:
            {
                log_printf( &logger, " < UART_ENABLE_IND -> UART has been re-enabled successfully" );
                break;
            }
            case PROTEUSII_CMD_IND_ERROR:
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
        error_flag |= PROTEUSII_ERROR;
    }
    return error_flag;
}

static err_t proteusii_parse_event ( proteusii_t *ctx )
{
    err_t error_flag = PROTEUSII_OK;

    if ( PROTEUSII_CMD_TYPE_CNF == ( ctx->evt_pkt.cmd & PROTEUSII_CMD_TYPE_MASK ) )
    {
        error_flag |= proteusii_parse_cnf ( ctx );
    }
    else if ( PROTEUSII_CMD_TYPE_RSP == ( ctx->evt_pkt.cmd & PROTEUSII_CMD_TYPE_MASK ) )
    {
        error_flag |= proteusii_parse_rsp ( ctx );
    }
    else if ( PROTEUSII_CMD_TYPE_IND == ( ctx->evt_pkt.cmd & PROTEUSII_CMD_TYPE_MASK ) )
    {
        error_flag |= proteusii_parse_ind ( ctx );
    }
    else
    {
        // Error packet should not be a command request
        error_flag |= PROTEUSII_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END
