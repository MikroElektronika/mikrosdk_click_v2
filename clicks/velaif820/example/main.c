/*!
 * @file main.c
 * @brief Vela IF820 Click Example.
 *
 * # Description
 * This example demonstrates the use of Vela IF820 Click board by processing data
 * from a connected BT Classic device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - VELAIF820_POWER_UP:
 * Powers up the device and checks the communication.
 *  - VELAIF820_CONFIG_EXAMPLE:
 * Restores factory settings, sets BT Classic flags and reads the BT address and name.
 *  - VELAIF820_EXAMPLE:
 * Performs a BT terminal example by processing all data from a connected BT Classic device 
 * and sending back an adequate response messages.
 *
 * ## Additional Function
 * - static void velaif820_clear_app_buf ( void )
 * - static void velaif820_log_app_buf ( void )
 * - static err_t velaif820_process ( velaif820_t *ctx )
 * - static err_t velaif820_wait_packet ( velaif820_t *ctx, uint8_t timeout_s, uint8_t rsp_flag, uint8_t *cmd_code )
 * - static err_t velaif820_power_up ( velaif820_t *ctx )
 * - static err_t velaif820_config_example ( velaif820_t *ctx )
 * - static err_t velaif820_example ( velaif820_t *ctx )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 * A smartphone and the Click board must be paired in order to exchange messages with each other.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "velaif820.h"

// Message content
#define MESSAGE_CONTENT     "Vela IF820 Click board - demo example."

static velaif820_t velaif820;
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
    VELAIF820_POWER_UP = 1,
    VELAIF820_CONFIG_EXAMPLE,
    VELAIF820_EXAMPLE

} velaif820_app_state_t;

static velaif820_app_state_t app_state = VELAIF820_POWER_UP;

/**
 * @brief Vela IF820 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void velaif820_clear_app_buf ( void );

/**
 * @brief Vela IF820 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void velaif820_log_app_buf ( void );

/**
 * @brief Vela IF820 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t velaif820_process ( velaif820_t *ctx );

/**
 * @brief Vela IF820 wait packet function.
 * @details This function waits for a packet message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @param[in] timeout_s : Timeout in seconds.
 * @param[in] rsp_flag : 1 - response packet, 0 - event packet.
 * @param[in] cmd_code : Expected command code string.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t velaif820_wait_packet ( velaif820_t *ctx, uint8_t timeout_s, uint8_t rsp_flag, uint8_t *cmd_code );

/**
 * @brief Vela IF820 power up function.
 * @details This function powers up the device and checks communication.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t velaif820_power_up ( velaif820_t *ctx );

/**
 * @brief Vela IF820 config example function.
 * @details This function restores factory settings, sets BT Classic flags and reads the BT address and name.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t velaif820_config_example ( velaif820_t *ctx );

/**
 * @brief Vela IF820 example function.
 * @details This function performs a BT terminal example by processing all data from
 * a connected BT Classic device and sending back an adequate response messages.
 * @param[in] ctx : Click context object.
 * See #velaif820_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t velaif820_example ( velaif820_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    velaif820_cfg_t velaif820_cfg;  /**< Click config object. */

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
    velaif820_cfg_setup( &velaif820_cfg );
    VELAIF820_MAP_MIKROBUS( velaif820_cfg, MIKROBUS_1 );
    if ( UART_ERROR == velaif820_init( &velaif820, &velaif820_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = VELAIF820_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case VELAIF820_POWER_UP:
        {
            if ( VELAIF820_OK == velaif820_power_up( &velaif820 ) )
            {
                app_state = VELAIF820_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case VELAIF820_CONFIG_EXAMPLE:
        {
            if ( VELAIF820_OK == velaif820_config_example( &velaif820 ) )
            {
                app_state = VELAIF820_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case VELAIF820_EXAMPLE:
        {
            velaif820_example( &velaif820 );
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

static void velaif820_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void velaif820_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t velaif820_process ( velaif820_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = velaif820_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return VELAIF820_OK;
    }
    return VELAIF820_ERROR;
}

static err_t velaif820_wait_packet ( velaif820_t *ctx, uint8_t timeout_s, uint8_t rsp_flag, uint8_t *cmd_code ) 
{
    err_t error_flag = VELAIF820_OK;
    uint32_t timeout_cnt = 0;
    while ( ( timeout_cnt < timeout_s ) || ( VELAIF820_WAIT_TIMEOUT_INFINITE == timeout_s ) )
    {
        error_flag = velaif820_read_packet( ctx );
        if ( VELAIF820_OK == error_flag )
        {
            if ( VELAIF820_PACKET_TYPE_EVENT == ctx->evt_pkt.rsp_flag )
            {
                log_printf ( &logger, " < EVENT >\r\n" );
            }
            else
            {
                log_printf ( &logger, " < RESPONSE >\r\n" );
            }
            
            if ( ( VELAIF820_PACKET_TYPE_EVENT == ctx->evt_pkt.rsp_flag ) && 
                 ( strstr( ctx->evt_pkt.command, VELAIF820_EVT_SYS_ERROR ) ) )
            {
                log_printf( &logger, "   Wrong CMD!\r\n" );
                error_flag = VELAIF820_ERROR_CMD;
                break;
            }
            else if ( ( ctx->evt_pkt.rsp_flag == rsp_flag ) && 
                      ( strstr( ctx->evt_pkt.command, cmd_code ) ) )
            {
                log_printf ( &logger, "   Command: %s\r\n", ctx->evt_pkt.command );
                if ( VELAIF820_PACKET_TYPE_RESPONSE == ctx->evt_pkt.rsp_flag )
                {
                    if ( ctx->evt_pkt.rsp_result )
                    {
                        log_printf( &logger, "   Result: %.4X\r\n", ctx->evt_pkt.rsp_result );
                        error_flag = VELAIF820_ERROR;
                        break;
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
                error_flag = VELAIF820_OK;
                break;
            }
            else
            {
                log_printf ( &logger, "   Command: %s\r\n", ctx->evt_pkt.command );
                if ( VELAIF820_PACKET_TYPE_RESPONSE == ctx->evt_pkt.rsp_flag )
                {
                    if ( ctx->evt_pkt.rsp_result )
                    {
                        log_printf( &logger, "   Result: %.4X\r\n", ctx->evt_pkt.rsp_result );
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
        error_flag = VELAIF820_ERROR_TIMEOUT;
    }
    log_printf( &logger, "--------------------------------\r\n" );
    return error_flag;
}

static err_t velaif820_power_up ( velaif820_t *ctx )
{
    err_t error_flag = VELAIF820_OK;

    log_printf( &logger, ">> Reset device.\r\n" );
    velaif820_set_cmd_mode( ctx );
    velaif820_reset_device( ctx );
    error_flag |= velaif820_wait_packet( ctx, VELAIF820_WAIT_TIMEOUT_5S, 
                                              VELAIF820_PACKET_TYPE_EVENT, 
                                              VELAIF820_EVT_GAP_ADV_STATE_CHANGED );

    log_printf( &logger, ">> Check communication.\r\n" );
    velaif820_cmd_action( ctx, VELAIF820_CMD_SYS_PING, NULL );
    error_flag |= velaif820_wait_packet( ctx, VELAIF820_WAIT_TIMEOUT_5S, 
                                              VELAIF820_PACKET_TYPE_RESPONSE, 
                                              VELAIF820_CMD_SYS_PING );

    return error_flag;
}

static err_t velaif820_config_example ( velaif820_t *ctx )
{
    err_t error_flag = VELAIF820_OK;

    log_printf( &logger, ">> Factory reset.\r\n" );
    velaif820_cmd_action( ctx, VELAIF820_CMD_SYS_FACTORY_RESET, NULL );
    error_flag |= velaif820_wait_packet( ctx, VELAIF820_WAIT_TIMEOUT_5S, 
                                              VELAIF820_PACKET_TYPE_EVENT, 
                                              VELAIF820_EVT_GAP_ADV_STATE_CHANGED );
    
    #define SET_BT_CLASSIC_FLAG "T=92"
    log_printf( &logger, ">> Set BT Classic flags.\r\n" );
    velaif820_cmd_set( ctx, VELAIF820_CMD_SYS_TRANSPORT, SET_BT_CLASSIC_FLAG );
    error_flag |= velaif820_wait_packet( ctx, VELAIF820_WAIT_TIMEOUT_5S, 
                                              VELAIF820_PACKET_TYPE_RESPONSE, 
                                              VELAIF820_CMD_SYS_TRANSPORT );
    
    log_printf( &logger, ">> Save settings.\r\n" );
    velaif820_cmd_action( ctx, VELAIF820_CMD_SYS_STORE_CONFIG, NULL );
    error_flag |= velaif820_wait_packet( ctx, VELAIF820_WAIT_TIMEOUT_5S, 
                                              VELAIF820_PACKET_TYPE_RESPONSE, 
                                              VELAIF820_CMD_SYS_STORE_CONFIG );
    
    log_printf( &logger, ">> Reboot.\r\n" );
    velaif820_cmd_action( ctx, VELAIF820_CMD_SYS_REBOOT, NULL );
    error_flag |= velaif820_wait_packet( ctx, VELAIF820_WAIT_TIMEOUT_5S, 
                                              VELAIF820_PACKET_TYPE_EVENT, 
                                              VELAIF820_EVT_GAP_ADV_STATE_CHANGED );

    log_printf( &logger, ">> Get BT address.\r\n" );
    velaif820_cmd_get( ctx, VELAIF820_CMD_SYS_BT_ADDRESS, NULL );
    error_flag |= velaif820_wait_packet( ctx, VELAIF820_WAIT_TIMEOUT_5S, 
                                              VELAIF820_PACKET_TYPE_RESPONSE, 
                                              VELAIF820_CMD_SYS_BT_ADDRESS );
    
    #define GET_BT_CLASSIC_NAME "T=1"
    log_printf( &logger, ">> Get device name.\r\n" );
    velaif820_cmd_get( ctx, VELAIF820_CMD_GAP_DEVICE_NAME, GET_BT_CLASSIC_NAME );
    error_flag |= velaif820_wait_packet( ctx, VELAIF820_WAIT_TIMEOUT_5S, 
                                              VELAIF820_PACKET_TYPE_RESPONSE, 
                                              VELAIF820_CMD_GAP_DEVICE_NAME );
    
    return error_flag;
}

static err_t velaif820_example ( velaif820_t *ctx )
{
    err_t error_flag = VELAIF820_OK;
    uint32_t timeout_cnt = 0;

    #define BT_TERMINAL_TIMEOUT_MS      60000
    #define BT_TERMINAL_MESSAGE_FREQ_MS 5000
    #define TERMINATION_CMD             "END"
    #define TERMINATION_RESPONSE        "END command received, the connection will be terminated in a few seconds."
    #define TERMINATION_TIMEOUT         "Timeout, closing the connection in a few seconds."
    
    Delay_ms ( 100 );
    log_printf( &logger, ">> Waiting for a BT peer to establish connection with the Click board...\r\n" );
    error_flag |= velaif820_wait_packet( ctx, VELAIF820_WAIT_TIMEOUT_INFINITE, 
                                              VELAIF820_PACKET_TYPE_EVENT, 
                                              VELAIF820_EVT_BT_CONNECTED );
    log_printf( &logger, ">> BT peer has connected.\r\n" );
    velaif820_set_data_mode( ctx );

    log_printf( &logger, ">> Waiting for data (up to 60 seconds)...\r\n" );
    log_printf( &logger, ">> Connection will be terminated if the Click receives an \"END\" string.\r\n" );
    for ( ; ; )
    {
        velaif820_clear_app_buf( );
        if ( VELAIF820_OK == velaif820_process( ctx ) )
        {
            Delay_ms ( 100 );
            timeout_cnt = 0;
            velaif820_process( ctx );
            velaif820_log_app_buf( );
            if ( strstr( app_buf, TERMINATION_CMD ) )
            {
                log_printf( &logger, ">> Terminating connection on demand.\r\n" );
                error_flag |= velaif820_generic_write ( ctx, TERMINATION_RESPONSE, strlen ( TERMINATION_RESPONSE ) );
                error_flag |= velaif820_generic_write ( ctx, VELAIF820_PACKET_END, strlen ( VELAIF820_PACKET_END ) );
                Delay_ms ( 1000 );

                log_printf( &logger, ">> Disconnecting BT peer.\r\n" );
                velaif820_set_cmd_mode( ctx );
                error_flag |= velaif820_wait_packet( ctx, VELAIF820_WAIT_TIMEOUT_5S, 
                                                          VELAIF820_PACKET_TYPE_EVENT, 
                                                          VELAIF820_EVT_BT_DISCONNECTED );
                break;
            }
            else if ( strstr( app_buf, VELAIF820_EVT_BT_DISCONNECTED ) )
            {
                log_printf( &logger, ">> BT peer has disconnected.\r\n" );
                break;
            }
        }
        timeout_cnt++;
        if ( 0 == ( timeout_cnt % BT_TERMINAL_MESSAGE_FREQ_MS ) )
        {
            log_printf( &logger, ">> Sending \"%s\" message to connected device.\r\n", ( char * ) MESSAGE_CONTENT );
            error_flag |= velaif820_generic_write ( ctx, MESSAGE_CONTENT, strlen ( MESSAGE_CONTENT ) );
            error_flag |= velaif820_generic_write ( ctx, VELAIF820_PACKET_END, strlen ( VELAIF820_PACKET_END ) );
            Delay_ms ( 100 );
        }
        if ( BT_TERMINAL_TIMEOUT_MS < timeout_cnt )
        {
            log_printf( &logger, ">> Terminating connection due to 60s timeout expiration.\r\n" );
            error_flag |= velaif820_generic_write ( ctx, TERMINATION_TIMEOUT, strlen ( TERMINATION_TIMEOUT ) );
            error_flag |= velaif820_generic_write ( ctx, VELAIF820_PACKET_END, strlen ( VELAIF820_PACKET_END ) );
            Delay_ms ( 1000 );

            log_printf( &logger, ">> Disconnecting BT peer.\r\n" );
            velaif820_set_cmd_mode( ctx );
            error_flag |= velaif820_wait_packet( ctx, VELAIF820_WAIT_TIMEOUT_5S, 
                                                      VELAIF820_PACKET_TYPE_EVENT, 
                                                      VELAIF820_EVT_BT_DISCONNECTED );
            break;
        }
        Delay_ms ( 1 );
    }

    return error_flag;
}

// ------------------------------------------------------------------------ END
