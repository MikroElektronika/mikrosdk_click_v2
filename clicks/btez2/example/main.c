/*!
 * @file main.c
 * @brief BT-EZ 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of BT-EZ 2 Click board by processing data
 * from a connected BLE device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - BTEZ2_POWER_UP:
 * Powers up the device and checks the communication.
 *  - BTEZ2_CONFIG_EXAMPLE:
 * Restores factory settings and reads the BT address and name.
 *  - BTEZ2_EXAMPLE:
 * Performs a BT terminal example by processing all data from a connected BLE device 
 * and sending back an adequate response messages.
 *
 * ## Additional Function
 * - static void btez2_clear_app_buf ( void )
 * - static void btez2_log_app_buf ( void )
 * - static err_t btez2_process ( btez2_t *ctx )
 * - static err_t btez2_wait_packet ( btez2_t *ctx, uint8_t timeout_s, uint8_t rsp_flag, uint8_t *cmd_code )
 * - static err_t btez2_power_up ( btez2_t *ctx )
 * - static err_t btez2_config_example ( btez2_t *ctx )
 * - static err_t btez2_example ( btez2_t *ctx )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "btez2.h"

// Message content
#define MESSAGE_CONTENT     "BT-EZ 2 Click board - demo example."

static btez2_t btez2;
static log_t logger;

// Application buffer size
#define APP_BUFFER_SIZE     500
#define PROCESS_BUFFER_SIZE 200

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    BTEZ2_POWER_UP = 1,
    BTEZ2_CONFIG_EXAMPLE,
    BTEZ2_EXAMPLE

} btez2_app_state_t;

static btez2_app_state_t app_state = BTEZ2_POWER_UP;

/**
 * @brief BT-EZ 2 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void btez2_clear_app_buf ( void );

/**
 * @brief BT-EZ 2 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void btez2_log_app_buf ( void );

/**
 * @brief BT-EZ 2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t btez2_process ( btez2_t *ctx );

/**
 * @brief BT-EZ 2 wait packet function.
 * @details This function waits for a packet message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @param[in] timeout_s : Timeout in seconds.
 * @param[in] rsp_flag : 1 - response packet, 0 - event packet.
 * @param[in] cmd_code : Expected command code string.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t btez2_wait_packet ( btez2_t *ctx, uint8_t timeout_s, uint8_t rsp_flag, uint8_t *cmd_code );

/**
 * @brief BT-EZ 2 power up function.
 * @details This function powers up the device and checks communication.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t btez2_power_up ( btez2_t *ctx );

/**
 * @brief BT-EZ 2 config example function.
 * @details This function restores factory settings, and reads the BT address and name.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t btez2_config_example ( btez2_t *ctx );

/**
 * @brief BT-EZ 2 example function.
 * @details This function performs a BT terminal example by processing all data from
 * a connected BLE device and sending back an adequate response messages.
 * @param[in] ctx : Click context object.
 * See #btez2_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t btez2_example ( btez2_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    btez2_cfg_t btez2_cfg;  /**< Click config object. */

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
    btez2_cfg_setup( &btez2_cfg );
    BTEZ2_MAP_MIKROBUS( btez2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == btez2_init( &btez2, &btez2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = BTEZ2_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case BTEZ2_POWER_UP:
        {
            if ( BTEZ2_OK == btez2_power_up( &btez2 ) )
            {
                app_state = BTEZ2_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BTEZ2_CONFIG_EXAMPLE:
        {
            if ( BTEZ2_OK == btez2_config_example( &btez2 ) )
            {
                app_state = BTEZ2_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BTEZ2_EXAMPLE:
        {
            btez2_example( &btez2 );
            break;
        }
        default:
        {
            log_error( &logger, " APP STATE." );
            break;
        }
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

static void btez2_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void btez2_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t btez2_process ( btez2_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = btez2_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( ( rx_size > 0 ) && ( rx_size <= APP_BUFFER_SIZE ) ) 
    {
        if ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE ) 
        {
            overflow_bytes = ( app_buf_len + rx_size ) - APP_BUFFER_SIZE;
            app_buf_len = APP_BUFFER_SIZE - rx_size;
            memmove ( app_buf, &app_buf[ overflow_bytes ], app_buf_len );
            memset ( &app_buf[ app_buf_len ], 0, overflow_bytes );
        }
        for ( rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ app_buf_len++ ] = rx_buf[ rx_cnt ];
            }
        }
        return BTEZ2_OK;
    }
    return BTEZ2_ERROR;
}

static err_t btez2_wait_packet ( btez2_t *ctx, uint8_t timeout_s, uint8_t rsp_flag, uint8_t *cmd_code ) 
{
    err_t error_flag = BTEZ2_OK;
    uint32_t timeout_cnt = 0;
    while ( ( timeout_cnt < timeout_s ) || ( BTEZ2_WAIT_TIMEOUT_INFINITE == timeout_s ) )
    {
        error_flag = btez2_read_packet( ctx );
        if ( BTEZ2_OK == error_flag )
        {
            if ( BTEZ2_PACKET_TYPE_EVENT == ctx->evt_pkt.rsp_flag )
            {
                log_printf ( &logger, " < EVENT >\r\n" );
            }
            else
            {
                log_printf ( &logger, " < RESPONSE >\r\n" );
            }
            
            if ( ( BTEZ2_PACKET_TYPE_EVENT == ctx->evt_pkt.rsp_flag ) && 
                 ( strstr( ctx->evt_pkt.command, BTEZ2_EVT_SYS_ERROR ) ) )
            {
                log_printf( &logger, "   Wrong CMD!\r\n" );
                error_flag = BTEZ2_ERROR_CMD;
                break;
            }
            else
            {
                log_printf ( &logger, "   Command: %s\r\n", ctx->evt_pkt.command );
                if ( BTEZ2_PACKET_TYPE_RESPONSE == ctx->evt_pkt.rsp_flag )
                {
                    log_printf ( &logger, "   Type: " );
                    switch ( ctx->evt_pkt.command_type )
                    {
                        case '/':
                        {
                            log_printf ( &logger, "Action\r\n" );
                            break;
                        }
                        case 'S':
                        {
                            log_printf ( &logger, "Set\r\n" );
                            break;
                        }
                        case 'G':
                        {
                            log_printf ( &logger, "Get\r\n" );
                            break;
                        }
                        case '.':
                        {
                            log_printf ( &logger, "Profile\r\n" );
                            break;
                        }
                        default:
                        {
                            log_printf ( &logger, "Unknown\r\n" );
                            break;
                        }
                    }
                    if ( ctx->evt_pkt.rsp_result )
                    {
                        log_printf( &logger, "   Result: %.4X\r\n", ctx->evt_pkt.rsp_result );
                        if ( ( ctx->evt_pkt.rsp_flag == rsp_flag ) && 
                             ( 0 == strcmp( ctx->evt_pkt.command, cmd_code ) ) )
                        { 
                            error_flag = BTEZ2_ERROR;
                            break;
                        }
                    }
                    else
                    {
                        log_printf( &logger, "   Result: OK\r\n" );
                    }
                }
                if ( strlen ( ctx->evt_pkt.payload ) )
                {
                    log_printf ( &logger, "   Payload: %s\r\n", ctx->evt_pkt.payload );
                }
                
                if ( ( ctx->evt_pkt.rsp_flag == rsp_flag ) && 
                     ( 0 == strcmp( ctx->evt_pkt.command, cmd_code ) ) )
                { 
                    error_flag = BTEZ2_OK;
                    break;
                }
            }
        }
        else
        {
            timeout_cnt++;
        }
    }
    if ( ( timeout_cnt >= timeout_s ) && ( 0 != timeout_s ) )
    {
        log_printf( &logger, " < TIMEOUT >\r\n" );
        error_flag = BTEZ2_ERROR_TIMEOUT;
    }
    log_printf( &logger, "--------------------------------\r\n" );
    return error_flag;
}

static err_t btez2_power_up ( btez2_t *ctx )
{
    err_t error_flag = BTEZ2_OK;

    log_printf( &logger, ">> Reset device.\r\n" );
    btez2_set_cmd_mode( ctx );
    btez2_reset_device( ctx );
    error_flag |= btez2_wait_packet( ctx, BTEZ2_WAIT_TIMEOUT_5S, 
                                          BTEZ2_PACKET_TYPE_EVENT, 
                                          BTEZ2_EVT_GAP_ADV_STATE_CHANGED );

    log_printf( &logger, ">> Check communication.\r\n" );
    btez2_cmd_action( ctx, BTEZ2_CMD_SYS_PING, NULL );
    error_flag |= btez2_wait_packet( ctx, BTEZ2_WAIT_TIMEOUT_5S, 
                                          BTEZ2_PACKET_TYPE_RESPONSE, 
                                          BTEZ2_CMD_SYS_PING );

    return error_flag;
}

static err_t btez2_config_example ( btez2_t *ctx )
{
    err_t error_flag = BTEZ2_OK;

    log_printf( &logger, ">> Factory reset.\r\n" );
    btez2_cmd_action( ctx, BTEZ2_CMD_SYS_FACTORY_RESET, NULL );
    error_flag |= btez2_wait_packet( ctx, BTEZ2_WAIT_TIMEOUT_5S, 
                                          BTEZ2_PACKET_TYPE_EVENT, 
                                          BTEZ2_EVT_GAP_ADV_STATE_CHANGED );
    
    log_printf( &logger, ">> Save settings.\r\n" );
    btez2_cmd_action( ctx, BTEZ2_CMD_SYS_STORE_CONFIG, NULL );
    error_flag |= btez2_wait_packet( ctx, BTEZ2_WAIT_TIMEOUT_5S, 
                                          BTEZ2_PACKET_TYPE_RESPONSE, 
                                          BTEZ2_CMD_SYS_STORE_CONFIG );
    
    log_printf( &logger, ">> Reboot.\r\n" );
    btez2_cmd_action( ctx, BTEZ2_CMD_SYS_REBOOT, NULL );
    error_flag |= btez2_wait_packet( ctx, BTEZ2_WAIT_TIMEOUT_5S, 
                                          BTEZ2_PACKET_TYPE_EVENT, 
                                          BTEZ2_EVT_GAP_ADV_STATE_CHANGED );

    log_printf( &logger, ">> Get BT address.\r\n" );
    btez2_cmd_get( ctx, BTEZ2_CMD_SYS_BT_ADDRESS, NULL );
    error_flag |= btez2_wait_packet( ctx, BTEZ2_WAIT_TIMEOUT_5S, 
                                          BTEZ2_PACKET_TYPE_RESPONSE, 
                                          BTEZ2_CMD_SYS_BT_ADDRESS );
    
    log_printf( &logger, ">> Get device name.\r\n" );
    btez2_cmd_get( ctx, BTEZ2_CMD_GAP_DEVICE_NAME, NULL );
    error_flag |= btez2_wait_packet( ctx, BTEZ2_WAIT_TIMEOUT_5S, 
                                          BTEZ2_PACKET_TYPE_RESPONSE, 
                                          BTEZ2_CMD_GAP_DEVICE_NAME );
    
    return error_flag;
}

static err_t btez2_example ( btez2_t *ctx )
{
    err_t error_flag = BTEZ2_OK;
    uint32_t timeout_cnt = 0;

    #define BT_TERMINAL_TIMEOUT_MS      60000
    #define BT_TERMINAL_MESSAGE_FREQ_MS 5000
    
    Delay_ms ( 100 );
    log_printf( &logger, ">> Waiting for a BT peer to establish connection with the Click board...\r\n" );
    error_flag |= btez2_wait_packet( ctx, BTEZ2_WAIT_TIMEOUT_INFINITE, 
                                          BTEZ2_PACKET_TYPE_EVENT, 
                                          BTEZ2_EVT_CYSPP_STATUS );
    log_printf( &logger, ">> BT peer has connected.\r\n" );
    btez2_set_data_mode( ctx );

    log_printf( &logger, ">> Waiting for data (up to 60 seconds)...\r\n" );
    for ( ; ; )
    {
        btez2_clear_app_buf( );
        if ( BTEZ2_OK == btez2_process( ctx ) )
        {
            Delay_ms ( 100 );
            timeout_cnt = 0;
            btez2_process( ctx );
            btez2_log_app_buf( );
            if ( strstr( app_buf, BTEZ2_EVT_GAP_DISCONNECTED ) )
            {
                log_printf( &logger, ">> BT peer has disconnected.\r\n" );
                btez2_set_cmd_mode( ctx );
                break;
            }
        }
        timeout_cnt++;
        if ( 0 == ( timeout_cnt % BT_TERMINAL_MESSAGE_FREQ_MS ) )
        {
            log_printf( &logger, ">> Sending \"%s\" message to connected device.\r\n", ( char * ) MESSAGE_CONTENT );
            error_flag |= btez2_generic_write ( ctx, MESSAGE_CONTENT, strlen ( MESSAGE_CONTENT ) );
            error_flag |= btez2_generic_write ( ctx, BTEZ2_PACKET_END, strlen ( BTEZ2_PACKET_END ) );
            Delay_ms ( 100 );
        }
        if ( BT_TERMINAL_TIMEOUT_MS < timeout_cnt )
        {
            btez2_set_cmd_mode( ctx );
            break;
        }
        Delay_ms ( 1 );
    }

    return error_flag;
}

// ------------------------------------------------------------------------ END
