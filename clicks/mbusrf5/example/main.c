/*!
 * @file main.c
 * @brief M-BUS RF 5 Click Example.
 *
 * # Description
 * This example demonstrates the use of the M-BUS RF 5 Click board in both
 * transmitter and receiver modes. The transmitter sends a predefined text 
 * message, while the receiver listens and parses incoming data packets.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger, the M-BUS RF 5 Click driver, resets the device, 
 * retrieves the firmware version, and configures the device role and settings 
 * depending on the selected mode (transmitter or receiver).
 *
 * ## Application Task
 * - In transmitter mode, sends a demo message repeatedly and waits for 
 *   confirmation events.  
 * - In receiver mode, continuously listens for incoming messages, parses, 
 *   and logs the received data.

 * ## Additional Function
 * - static err_t mbusrf5_parse_status ( mbusrf5_t *ctx )
 * - static err_t mbusrf5_parse_get ( mbusrf5_t *ctx )
 * - static err_t mbusrf5_parse_cnf ( mbusrf5_t *ctx )
 * - static err_t mbusrf5_parse_ind ( mbusrf5_t *ctx )
 * - static err_t mbusrf5_parse_event ( mbusrf5_t *ctx )
 *
 * @note
 * Ensure that two M-BUS RF 5 Click boards are available for proper demo 
 * operation: one configured as a transmitter and the other as a receiver.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mbusrf5.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_TRANSMITTER

// Text message to send to initiate communication
#define DEMO_TEXT_MESSAGE   "MIKROE - M-BUS RF 5 Click board"

static mbusrf5_t mbusrf5;
static log_t logger;

/**
 * @brief M-BUS RF 5 parse status function.
 * @details This function parses status option byte from payload and logs it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c 1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mbusrf5_parse_status ( mbusrf5_t *ctx );

/**
 * @brief M-BUS RF 5 parse get function.
 * @details This function parses GET_CNF or GETRAM_CNF option bytes from payload and logs it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c 1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mbusrf5_parse_get ( mbusrf5_t *ctx );

/**
 * @brief M-BUS RF 5 parse cnf function.
 * @details This function parses all received confirmation packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c 1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mbusrf5_parse_cnf ( mbusrf5_t *ctx );

/**
 * @brief M-BUS RF 5 parse ind function.
 * @details This function parses all received indication packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c 1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mbusrf5_parse_ind ( mbusrf5_t *ctx );

/**
 * @brief M-BUS RF 5 parse event function.
 * @details This function parses all received packets and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #mbusrf5_t object definition for detailed explanation.
 * @return @li @c 0 - Packet parsed successfully,
 *         @li @c 1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mbusrf5_parse_event ( mbusrf5_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mbusrf5_cfg_t mbusrf5_cfg;  /**< Click config object. */

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
    mbusrf5_cfg_setup( &mbusrf5_cfg );
    MBUSRF5_MAP_MIKROBUS( mbusrf5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == mbusrf5_init( &mbusrf5, &mbusrf5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, ">> Reset device.\r\n" );
    if ( MBUSRF5_ERROR == mbusrf5_reset_device ( &mbusrf5 ) )
    {
        log_error( &logger, " Reset device." );
        for ( ; ; );
    }
    mbusrf5_parse_event ( &mbusrf5 );

    log_printf( &logger, ">> Get FW version.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_get_user_setting_flash ( &mbusrf5, MBUSRF5_OPT_FW_VERSION ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }

#ifdef DEMO_TRANSMITTER
    log_printf( &logger, ">> Set device role.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_set_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_WMBUS_ROLE, MBUSRF5_WMBUS_ROLE_METER ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Get device role.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_get_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_WMBUS_ROLE ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }

    log_info( &logger, " Application Task " );

    log_printf( &logger, ">> Send message to receiver device.\r\n" );
    mbusrf5.cmd_pkt.cmd = MBUSRF5_CMD_REQ_DATAEX;
    mbusrf5.cmd_pkt.payload_len = strlen ( DEMO_TEXT_MESSAGE ) + 8;
    mbusrf5.cmd_pkt.payload[ 0 ] = MBUSRF5_OPT_WMBUS_TX_MODE;
    mbusrf5.cmd_pkt.payload[ 1 ] = 1;
    mbusrf5.cmd_pkt.payload[ 2 ] = MBUSRF5_WMBUS_TX_MODE_S;
    mbusrf5.cmd_pkt.payload[ 3 ] = MBUSRF5_OPT_WMBUS_FRAME_FORMAT;
    mbusrf5.cmd_pkt.payload[ 4 ] = 1;
    mbusrf5.cmd_pkt.payload[ 5 ] = MBUSRF5_WMBUS_FRAME_FORMAT_A;
    mbusrf5.cmd_pkt.payload[ 6 ] = MBUSRF5_OPT_WMBUS_DATA;
    mbusrf5.cmd_pkt.payload[ 7 ] = strlen ( DEMO_TEXT_MESSAGE );
    memcpy ( &mbusrf5.cmd_pkt.payload[ 8 ], DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) );
    if ( MBUSRF5_OK == mbusrf5_send_cmd ( &mbusrf5 ) )
    {
        if ( MBUSRF5_OK == mbusrf5_wait_for_event ( &mbusrf5, MBUSRF5_CMD_CNF_DATAEX, MBUSRF5_WAIT_TIME_1S ) ) 
        {
            mbusrf5_parse_event ( &mbusrf5 );
        }
    }
#else
    log_printf( &logger, ">> Set device role.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_set_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_WMBUS_ROLE, MBUSRF5_WMBUS_ROLE_GATEWAY ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Get device role.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_get_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_WMBUS_ROLE ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Set RX mode.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_set_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_WMBUS_RX_MODE, MBUSRF5_WMBUS_RX_MODE_S ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Get RX mode.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_get_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_WMBUS_RX_MODE ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Set CFG flags.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_set_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_CFG_FLAGS, MBUSRF5_CFG_FLAGS_RSSI_AND_TIMESTAMP_ENABLED ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Get CFG flags.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_get_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_CFG_FLAGS ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Enter RX mode.\r\n" );
    mbusrf5.cmd_pkt.cmd = MBUSRF5_CMD_REQ_DATARX_START;
    mbusrf5.cmd_pkt.payload_len = 0;
    if ( MBUSRF5_OK == mbusrf5_send_cmd ( &mbusrf5 ) )
    {
        if ( MBUSRF5_OK == mbusrf5_wait_for_event ( &mbusrf5, MBUSRF5_CMD_CNF_DATARX_START, MBUSRF5_WAIT_TIME_1S ) ) 
        {
            mbusrf5_parse_event ( &mbusrf5 );
        }
    }

    log_info( &logger, " Application Task " );
#endif
}

void application_task ( void ) 
{
    if ( MBUSRF5_OK == mbusrf5_read_event ( &mbusrf5 ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
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

static err_t mbusrf5_parse_status ( mbusrf5_t *ctx )
{
    err_t error_flag = MBUSRF5_OK;
    if ( MBUSRF5_OPT_STATUS == ctx->evt_pkt.payload[ 0 ] )
    {
        switch ( ctx->evt_pkt.payload[ 2 ] )
        {
            case MBUSRF5_STATUS_OK:
            {
                log_printf( &logger, "Request successfully received and processed" );
                break;
            }
            case MBUSRF5_STATUS_NOK:
            {
                log_printf( &logger, "Request not successful" );
                break;
            }
            case MBUSRF5_STATUS_INV_CONFIG:
            {
                log_printf( &logger, "The command was not configured correctly" );
                break;
            }
            case MBUSRF5_STATUS_NOT_SUPP_BY_MODULE:
            {
                log_printf( &logger, "The command is not supported by this module" );
                break;
            }
            case MBUSRF5_STATUS_INV_OPT:
            {
                log_printf( &logger, "The value specified for this option is not allowed in this context" );
                break;
            }
            case MBUSRF5_STATUS_OPT_NOT_SUPP:
            {
                log_printf( &logger, "The option is not supported by this command" );
                break;
            }
            case MBUSRF5_STATUS_NOT_SUPP_BY_ROLE:
            {
                log_printf( &logger, "The command is not supported by wM-Bus role" );
                break;
            }
            default:
            {
                log_printf( &logger, "Unknown status: 0x%.2X", ( uint16_t ) ctx->evt_pkt.payload[ 2 ] );
                error_flag = MBUSRF5_ERROR;
                break;
            }
        }
    }
    else
    {
        log_printf( &logger, "Unknown option: 0x%.2X", ( uint16_t ) ctx->evt_pkt.payload[ 0 ] );
        error_flag = MBUSRF5_ERROR;
    }
    return error_flag;
}

static err_t mbusrf5_parse_get ( mbusrf5_t *ctx )
{
    err_t error_flag = mbusrf5_parse_status ( ctx );
    log_printf( &logger, "\r\n" );
    switch ( ctx->evt_pkt.payload[ 3 ] )
    {
        case MBUSRF5_OPT_WMBUS_RX_MODE:
        {
            log_printf( &logger, "   wMBus_RxMode: " );
            if ( MBUSRF5_WMBUS_RX_MODE_S == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "S" );
            }
            else if ( MBUSRF5_WMBUS_RX_MODE_T == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "T" );
            }
            else if ( MBUSRF5_WMBUS_RX_MODE_C_T == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "C + T" );
            }
            else if ( MBUSRF5_WMBUS_RX_MODE_C == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "C" );
            }
            else
            {
                log_printf( &logger, "Unknown" );
                error_flag = MBUSRF5_ERROR;
            }
            break;
        }
        case MBUSRF5_OPT_WMBUS_ROLE:
        {
            log_printf( &logger, "   wMBus_Role: " );
            if ( MBUSRF5_WMBUS_ROLE_METER == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "Meter" );
            }
            else if ( MBUSRF5_WMBUS_ROLE_GATEWAY == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "Gateway" );
            }
            else
            {
                log_printf( &logger, "Unknown" );
                error_flag = MBUSRF5_ERROR;
            }
            break;
        }
        case MBUSRF5_OPT_UART_BAUDRATE:
        {
            log_printf( &logger, "   UART_Baudrate: " );
            if ( MBUSRF5_UART_BAUDRATE_9600 == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "9600" );
            }
            else if ( MBUSRF5_UART_BAUDRATE_115200 == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "115200" );
            }
            else if ( MBUSRF5_UART_BAUDRATE_230400 == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "230400" );
            }
            else if ( MBUSRF5_UART_BAUDRATE_460800 == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "460800" );
            }
            else if ( MBUSRF5_UART_BAUDRATE_921600 == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "921600" );
            }
            else
            {
                log_printf( &logger, "Unknown" );
                error_flag = MBUSRF5_ERROR;
            }
            break;
        }
        case MBUSRF5_OPT_TX_POWER:
        {
            log_printf( &logger, "   TxPower: " );
            if ( MBUSRF5_TX_POWER_MAX < ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "Out of range" );
                error_flag = MBUSRF5_ERROR;
            }
            else
            {
                log_printf( &logger, "+%udb", ( uint16_t ) ctx->evt_pkt.payload[ 5 ] );
            }
            break;
        }
        case MBUSRF5_OPT_CFG_FLAGS:
        {
            log_printf( &logger, "   CfgFlags: " );
            if ( MBUSRF5_CFG_FLAGS_RSSI_AND_TIMESTAMP_DISABLED == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "None" );
            }
            else if ( MBUSRF5_CFG_FLAGS_RSSI_ENABLED == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "RSSI" );
            }
            else if ( MBUSRF5_CFG_FLAGS_TIMESTAMP_ENABLED == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "Timestamp" );
            }
            else if ( MBUSRF5_CFG_FLAGS_RSSI_AND_TIMESTAMP_ENABLED == ctx->evt_pkt.payload[ 5 ] )
            {
                log_printf( &logger, "RSSI and Timestamp" );
            }
            else
            {
                log_printf( &logger, "Unknown" );
                error_flag = MBUSRF5_ERROR;
            }
            break;
        }
        case MBUSRF5_OPT_FW_VERSION:
        {
            log_printf( &logger, "   FirmwareVersion: " );
            if ( 3 == ctx->evt_pkt.payload[ 4 ] )
            {
                log_printf( &logger, "%u.%u.%u", 
                            ( uint16_t ) mbusrf5.evt_pkt.payload[ 7 ], 
                            ( uint16_t ) mbusrf5.evt_pkt.payload[ 6 ], 
                            ( uint16_t ) mbusrf5.evt_pkt.payload[ 5 ] );
            }
            else
            {
                log_printf( &logger, "Unknown" );
                error_flag = MBUSRF5_ERROR;
            }
            break;
        }
        default:
        {
            log_printf( &logger, "Unknown option: 0x%.2X", ( uint16_t ) ctx->evt_pkt.payload[ 0 ] );
            error_flag = MBUSRF5_ERROR;
            break;
        }
    }
    return error_flag;
}

static err_t mbusrf5_parse_cnf ( mbusrf5_t *ctx )
{
    err_t error_flag = MBUSRF5_OK;
    uint16_t byte_cnt = 0;

    if ( MBUSRF5_CMD_TYPE_CNF == ( ctx->evt_pkt.cmd & MBUSRF5_CMD_TYPE_MASK ) )
    {
        // Parse confirmation packet
        switch ( ctx->evt_pkt.cmd )
        {
            case MBUSRF5_CMD_CNF_DATAEX:
            {
                log_printf( &logger, " < DATAEX_CNF -> " );
                error_flag |= mbusrf5_parse_status ( ctx );
                break;
            }
            case MBUSRF5_CMD_CNF_DATARX_START:
            {
                log_printf( &logger, " < DATARX_START_CNF -> " );
                error_flag |= mbusrf5_parse_status ( ctx );
                break;
            }
            case MBUSRF5_CMD_CNF_DATARX_STOP:
            {
                log_printf( &logger, " < DATARX_STOP_CNF -> " );
                error_flag |= mbusrf5_parse_status ( ctx );
                break;
            }
            case MBUSRF5_CMD_CNF_SET:
            {
                log_printf( &logger, " < SET_CNF -> " );
                error_flag |= mbusrf5_parse_status ( ctx );
                break;
            }
            case MBUSRF5_CMD_CNF_GET:
            {
                log_printf( &logger, " < GET_CNF -> " );
                error_flag |= mbusrf5_parse_get ( ctx );
                break;
            }
            case MBUSRF5_CMD_CNF_SETRAM:
            {
                log_printf( &logger, " < SETRAM_CNF -> " );
                error_flag |= mbusrf5_parse_status ( ctx );
                break;
            }
            case MBUSRF5_CMD_CNF_GETRAM:
            {
                log_printf( &logger, " < GETRAM_CNF -> " );
                error_flag |= mbusrf5_parse_get ( ctx );
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
        if ( MBUSRF5_CMD_CNF_DATAEX == ctx->evt_pkt.cmd )
        {
            Delay_ms ( 1000 );
            log_printf( &logger, ">> Send message to receiver device.\r\n" );
            mbusrf5.cmd_pkt.cmd = MBUSRF5_CMD_REQ_DATAEX;
            mbusrf5.cmd_pkt.payload_len = strlen ( DEMO_TEXT_MESSAGE ) + 8;
            mbusrf5.cmd_pkt.payload[ 0 ] = MBUSRF5_OPT_WMBUS_TX_MODE;
            mbusrf5.cmd_pkt.payload[ 1 ] = 1;
            mbusrf5.cmd_pkt.payload[ 2 ] = MBUSRF5_WMBUS_TX_MODE_S;
            mbusrf5.cmd_pkt.payload[ 3 ] = MBUSRF5_OPT_WMBUS_FRAME_FORMAT;
            mbusrf5.cmd_pkt.payload[ 4 ] = 1;
            mbusrf5.cmd_pkt.payload[ 5 ] = MBUSRF5_WMBUS_FRAME_FORMAT_A;
            mbusrf5.cmd_pkt.payload[ 6 ] = MBUSRF5_OPT_WMBUS_DATA;
            mbusrf5.cmd_pkt.payload[ 7 ] = strlen ( DEMO_TEXT_MESSAGE );
            memcpy ( &mbusrf5.cmd_pkt.payload[ 8 ], DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) );
            error_flag |= mbusrf5_send_cmd ( &mbusrf5 );
        }
    }
    else
    {
        // Wrong packet type
        error_flag |= MBUSRF5_ERROR;
    }
    return error_flag;
}

static err_t mbusrf5_parse_ind ( mbusrf5_t *ctx )
{
    err_t error_flag = MBUSRF5_OK;
    uint16_t byte_cnt = 0;

    if ( MBUSRF5_CMD_TYPE_IND == ( ctx->evt_pkt.cmd & MBUSRF5_CMD_TYPE_MASK ) )
    {
        // Parse indication packet
        switch ( ctx->evt_pkt.cmd )
        {
            case MBUSRF5_CMD_IND_DATAEX:
            {
                log_printf( &logger, " < DATAEX_IND\r\n" );
                uint8_t offset = 0;
                if ( MBUSRF5_OPT_RSSI == ctx->evt_pkt.payload[ offset ] )
                {
                    log_printf( &logger, "   RSSI: %d\r\n", 
                                ( int16_t ) ( ( int8_t ) ctx->evt_pkt.payload[ offset + 2 ] ) );
                    offset += 3;
                }
                if ( MBUSRF5_OPT_TIMESTAMP == ctx->evt_pkt.payload[ offset ] )
                {
                    log_printf( &logger, "   Timestamp: %lu\r\n", 
                                ( ( uint32_t ) ctx->evt_pkt.payload[ offset + 2 ] << 24 ) |
                                ( ( uint32_t ) ctx->evt_pkt.payload[ offset + 3 ] << 16 ) |
                                ( ( uint32_t ) ctx->evt_pkt.payload[ offset + 4 ] << 8 ) |
                                ( ( uint32_t ) ctx->evt_pkt.payload[ offset + 5 ] << 0 ) );
                    offset += 6;
                }
                if ( MBUSRF5_OPT_WMBUS_RX_MODE == ctx->evt_pkt.payload[ offset ] )
                {
                    log_printf( &logger, "   wMBus_RxMode: " );
                    if ( MBUSRF5_WMBUS_RX_MODE_S == ctx->evt_pkt.payload[ offset + 2 ] )
                    {
                        log_printf( &logger, "S" );
                    }
                    else if ( MBUSRF5_WMBUS_RX_MODE_T == ctx->evt_pkt.payload[ offset + 2 ] )
                    {
                        log_printf( &logger, "T" );
                    }
                    else if ( MBUSRF5_WMBUS_RX_MODE_C_T == ctx->evt_pkt.payload[ offset + 2 ] )
                    {
                        log_printf( &logger, "C + T" );
                    }
                    else if ( MBUSRF5_WMBUS_RX_MODE_C == ctx->evt_pkt.payload[ offset + 2 ] )
                    {
                        log_printf( &logger, "C" );
                    }
                    else
                    {
                        log_printf( &logger, "Unknown" );
                        error_flag |= MBUSRF5_ERROR;
                    }
                    offset += 3;
                }
                else
                {
                    log_printf( &logger, "   No wMBus_RxMode in payload" );
                    error_flag |= MBUSRF5_ERROR;
                }
                log_printf( &logger, "\r\n" );

                if ( MBUSRF5_OPT_WMBUS_FRAME_FORMAT == ctx->evt_pkt.payload[ offset ] )
                {
                    log_printf( &logger, "   wMBus_FrameFormat: " );
                    if ( MBUSRF5_WMBUS_FRAME_FORMAT_A == ctx->evt_pkt.payload[ offset + 2 ] )
                    {
                        log_printf( &logger, "A" );
                    }
                    else if ( MBUSRF5_WMBUS_FRAME_FORMAT_B == ctx->evt_pkt.payload[ offset + 2 ] )
                    {
                        log_printf( &logger, "B" );
                    }
                    else
                    {
                        log_printf( &logger, "Unknown" );
                        error_flag |= MBUSRF5_ERROR;
                    }
                    offset += 3;
                }
                else
                {
                    log_printf( &logger, "   No wMBus_FrameFormat in payload" );
                    error_flag |= MBUSRF5_ERROR;
                }
                log_printf( &logger, "\r\n" );

                if ( MBUSRF5_OPT_WMBUS_DATA == ctx->evt_pkt.payload[ offset ] )
                {
                    log_printf( &logger, "   wMBus_Data length: %u\r\n", ( uint16_t ) ctx->evt_pkt.payload[ offset + 1 ] );
                    
                    log_printf( &logger, "   wMBus_Data (HEX): " );
                    for ( byte_cnt = 0; byte_cnt < ctx->evt_pkt.payload[ offset + 1 ]; byte_cnt++ )
                    {
                        log_printf( &logger, "0x%.2X ", ( uint16_t ) ctx->evt_pkt.payload[ offset + 2 + byte_cnt ] );
                    }
                    Delay_ms ( 10 );
                    uint8_t tmp = ctx->evt_pkt.payload[ ctx->evt_pkt.payload[ offset + 1 ] + offset + 2 ];
                    ctx->evt_pkt.payload[ ctx->evt_pkt.payload[ offset + 1 ] + offset + 2 ] = 0;
                    log_printf( &logger, "\r\n   wMBus_Data (STR): %s", &ctx->evt_pkt.payload[ offset + 2 ] );
                    ctx->evt_pkt.payload[ ctx->evt_pkt.payload[ offset + 1 ] + offset + 2 ] = tmp;
                }
                else
                {
                    log_printf( &logger, "   No wMBus_Data in payload" );
                    error_flag |= MBUSRF5_ERROR;
                }
                break;
            }
            case MBUSRF5_CMD_IND_RESET:
            {
                log_printf( &logger, " < RESET_IND" );
                break;
            }
            case MBUSRF5_CMD_IND_STANDBY:
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
        error_flag |= MBUSRF5_ERROR;
    }
    return error_flag;
}

static err_t mbusrf5_parse_event ( mbusrf5_t *ctx )
{
    err_t error_flag = MBUSRF5_OK;

    if ( MBUSRF5_CMD_TYPE_CNF == ( ctx->evt_pkt.cmd & MBUSRF5_CMD_TYPE_MASK ) )
    {
        error_flag |= mbusrf5_parse_cnf ( ctx );
    }
    else if ( MBUSRF5_CMD_TYPE_IND == ( ctx->evt_pkt.cmd & MBUSRF5_CMD_TYPE_MASK ) )
    {
        error_flag |= mbusrf5_parse_ind ( ctx );
    }
    else
    {
        // Error packet should not be a command request
        error_flag |= MBUSRF5_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END
