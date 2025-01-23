/*!
 * @file main.c
 * @brief BT840 Click Example.
 *
 * # Description
 * This example demonstrates the use of BT840 Click board by processing data
 * from a connected BT device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - BT840_POWER_UP:
 * Powers up the device and reads the system information.
 *  - BT840_CONFIG_EXAMPLE:
 * Sets the BT device name.
 *  - BT840_EXAMPLE:
 * Performs a BT terminal example by processing all data from a connected BT device 
 * and sending back an adequate response messages.
 *
 * ## Additional Function
 * - static void bt840_clear_app_buf ( void )
 * - static void bt840_log_app_buf ( void )
 * - static err_t bt840_process ( bt840_t *ctx )
 * - static err_t bt840_read_response ( bt840_t *ctx, uint8_t *rsp )
 * - static err_t bt840_power_up ( bt840_t *ctx )
 * - static err_t bt840_config_example ( bt840_t *ctx )
 * - static err_t bt840_example ( bt840_t *ctx )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "bt840.h"
#include "generic_pointer.h"

// Message content
#define MESSAGE_CONTENT     "BT840 Click board - demo example."

// Local device name.
#define DEVICE_NAME         "BT840 Click"

static bt840_t bt840;
static log_t logger;

// Application buffer size
#define APP_BUFFER_SIZE     600
#define PROCESS_BUFFER_SIZE 200

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    BT840_POWER_UP = 1,
    BT840_CONFIG_EXAMPLE,
    BT840_EXAMPLE

} bt840_app_state_t;

static bt840_app_state_t app_state = BT840_POWER_UP;

/**
 * @brief BT840 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void bt840_clear_app_buf ( void );

/**
 * @brief BT840 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void bt840_log_app_buf ( void );

/**
 * @brief BT840 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bt840_process ( bt840_t *ctx );

/**
 * @brief BT840 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bt840_read_response ( bt840_t *ctx, uint8_t *rsp );

/**
 * @brief BT840 power up function.
 * @details This function powers up the device, and reads the system information.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bt840_power_up ( bt840_t *ctx );

/**
 * @brief BT840 config example function.
 * @details This function sets the BT device name.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bt840_config_example ( bt840_t *ctx );

/**
 * @brief BT840 example function.
 * @details This function performs a BT terminal example by processing all data from
 * a connected BT device and sending back an adequate response messages.
 * @param[in] ctx : Click context object.
 * See #bt840_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bt840_example ( bt840_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bt840_cfg_t bt840_cfg;  /**< Click config object. */

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
    bt840_cfg_setup( &bt840_cfg );
    BT840_MAP_MIKROBUS( bt840_cfg, MIKROBUS_1 );
    if ( UART_ERROR == bt840_init( &bt840, &bt840_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = BT840_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case BT840_POWER_UP:
        {
            if ( BT840_OK == bt840_power_up( &bt840 ) )
            {
                app_state = BT840_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BT840_CONFIG_EXAMPLE:
        {
            if ( BT840_OK == bt840_config_example( &bt840 ) )
            {
                app_state = BT840_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BT840_EXAMPLE:
        {
            bt840_example( &bt840 );
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

static void bt840_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void bt840_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t bt840_process ( bt840_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = bt840_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return BT840_OK;
    }
    return BT840_ERROR;
}

static err_t bt840_read_response ( bt840_t *ctx, uint8_t *rsp ) 
{
    #define READ_RESPONSE_TIMEOUT_MS 30000
    uint32_t timeout_cnt = 0;
    bt840_clear_app_buf ( );
    bt840_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, BT840_RSP_FAIL ) ) )
    {
        bt840_process( ctx );
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            bt840_log_app_buf( );
            bt840_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return BT840_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    bt840_process( ctx );
    bt840_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return BT840_OK;
    }
    return BT840_ERROR_CMD;
}

static err_t bt840_power_up ( bt840_t *ctx )
{
    err_t error_flag = BT840_OK;
    
    log_printf( &logger, ">>> Reset device.\r\n" );
    bt840_set_cmd_mode( &bt840 );
    bt840_reset_device( &bt840 );
    bt840_wakeup_device( &bt840 );
    while ( BT840_OK == bt840_process( ctx ) )
    {
        bt840_log_app_buf( );
        bt840_clear_app_buf ( );
    }
    log_printf( &logger, "--------------------------------\r\n" );

    log_printf( &logger, ">>> Factory reset.\r\n" );
    bt840_cmd_run( &bt840, BT840_CMD_DEFAULT_RESET );
    error_flag |= bt840_read_response( &bt840, BT840_RSP_OK );

    log_printf( &logger, ">>> Check communication.\r\n" );
    bt840_cmd_run( &bt840, BT840_CMD_AT );
    error_flag |= bt840_read_response( &bt840, BT840_RSP_OK );

    log_printf( &logger, ">>> Get software version.\r\n" );
    bt840_cmd_get( ctx, BT840_CMD_GET_SW_VERSION );
    error_flag |= bt840_read_response( ctx, BT840_RSP_OK );

    log_printf( &logger, ">>> Get MAC address.\r\n" );
    bt840_cmd_get( ctx, BT840_CMD_GET_MAC );
    error_flag |= bt840_read_response( ctx, BT840_RSP_OK );

    return error_flag;
}

static err_t bt840_config_example ( bt840_t *ctx )
{
    err_t error_flag = BT840_OK;

    log_printf( &logger, ">>> Set device name to \"%s\".\r\n", ( char * ) DEVICE_NAME );
    bt840_cmd_set( ctx, BT840_CMD_DEVICE_NAME, DEVICE_NAME );
    error_flag |= bt840_read_response( ctx, BT840_RSP_OK );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">>> Save settings.\r\n" );
    bt840_cmd_set( &bt840, BT840_CMD_SAVE_SETTINGS, "1" );
    error_flag |= bt840_read_response( ctx, BT840_RSP_OK );
    
    log_printf( &logger, ">>> Reboot.\r\n" );
    bt840_cmd_run( ctx, BT840_CMD_RESET );
    error_flag |= bt840_read_response( ctx, BT840_RSP_OK );
    
    return error_flag;
}

static err_t bt840_example ( bt840_t *ctx )
{
    err_t error_flag = BT840_OK;
    uint32_t timeout_cnt = 0;
    uint8_t data_len = 0;
    uint8_t byte_cnt = 0;
    uint8_t * __generic_ptr start_ptr = NULL;

    #define BT_TERMINAL_TIMEOUT_MS      60000
    #define BT_TERMINAL_MESSAGE_FREQ_MS 5000
    #define TERMINATION_CMD             "END"
    #define TERMINATION_RESPONSE        "END command received, the connection will be terminated in a few seconds."
    #define TERMINATION_TIMEOUT         "Timeout, closing the connection in a few seconds."
    #define NEW_LINE_STRING             "\r\n"
    
    log_printf( &logger, ">>> Waiting for a BT peer to establish connection with the Click board...\r\n" );
    for ( ; ; )
    {
        bt840_clear_app_buf( );
        if ( BT840_OK == bt840_process( ctx ) )
        {
            Delay_ms ( 200 );
            bt840_process( ctx );
            bt840_log_app_buf( );
            if ( strstr( app_buf, BT840_RSP_CONNECTED ) )
            {
                log_printf( &logger, "--------------------------------\r\n" );
                log_printf( &logger, ">>> BT peer has connected.\r\n" );
                bt840_set_data_mode( &bt840 );
                break;
            }
        }
    }

    log_printf( &logger, ">>> Waiting for data (up to 60 seconds)...\r\n" );
    log_printf( &logger, ">>> Connection will be terminated if the Click receives an \"END\" string.\r\n" );
    for ( ; ; )
    {
        bt840_clear_app_buf( );
        if ( BT840_OK == bt840_process( ctx ) )
        {
            Delay_ms ( 100 );
            timeout_cnt = 0;
            bt840_process( ctx );
            bt840_log_app_buf( );
            start_ptr = strstr( app_buf, BT840_RSP_RECEIVE );
            if ( start_ptr )
            {
                start_ptr += strlen ( BT840_RSP_RECEIVE );
                data_len = *start_ptr;
                log_printf( &logger, "<<< Received data (HEX): " );
                for ( byte_cnt = 0; byte_cnt < data_len; byte_cnt++ )
                {
                    log_printf( &logger, "0x%.2X ", *( start_ptr + byte_cnt + 1 ) );
                }
                log_printf( &logger, "\r\n" );
                log_printf( &logger, "<<< Received data (STR): %s", ( start_ptr + 1 ) );
                log_printf( &logger, "--------------------------------\r\n" );
            }
            if ( strstr( app_buf, TERMINATION_CMD ) )
            {
                log_printf( &logger, ">>> Terminating connection on demand.\r\n" );
                data_len = strlen ( TERMINATION_RESPONSE ) + strlen ( NEW_LINE_STRING );
                bt840_generic_write ( ctx, &data_len, 1 );
                bt840_generic_write ( ctx, TERMINATION_RESPONSE, strlen ( TERMINATION_RESPONSE ) );
                bt840_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
                Delay_ms ( 100 );
                error_flag |= bt840_read_response( ctx, BT840_RSP_SEND );

                log_printf( &logger, ">>> Disconnecting BT peer.\r\n" );
                bt840_set_cmd_mode( &bt840 );
                bt840_cmd_set( ctx, BT840_CMD_DISCONNECT, "1" );
                error_flag |= bt840_read_response( ctx, BT840_RSP_DISCONNECTED );
                break;
            }
            else if ( strstr( app_buf, BT840_RSP_DISCONNECTED ) )
            {
                log_printf( &logger, ">>> BT peer has disconnected.\r\n" );
                break;
            }
        }
        timeout_cnt++;
        if ( 0 == ( timeout_cnt % BT_TERMINAL_MESSAGE_FREQ_MS ) )
        {
            log_printf( &logger, ">>> Sending \"%s\" message to connected device.\r\n", ( char * ) MESSAGE_CONTENT );
            data_len = strlen ( MESSAGE_CONTENT ) + strlen ( NEW_LINE_STRING );
            bt840_generic_write ( ctx, &data_len, 1 );
            bt840_generic_write ( ctx, MESSAGE_CONTENT, strlen ( MESSAGE_CONTENT ) );
            bt840_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
            Delay_ms ( 100 );
            error_flag |= bt840_read_response( ctx, BT840_RSP_SEND );
        }
        if ( BT_TERMINAL_TIMEOUT_MS < timeout_cnt )
        {
            log_printf( &logger, ">>> Terminating connection due to 60s timeout expiration.\r\n" );
            data_len = strlen ( TERMINATION_TIMEOUT ) + strlen ( NEW_LINE_STRING );
            bt840_generic_write ( ctx, &data_len, 1 );
            bt840_generic_write ( ctx, TERMINATION_TIMEOUT, strlen ( TERMINATION_TIMEOUT ) );
            bt840_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
            Delay_ms ( 100 );
            error_flag |= bt840_read_response( ctx, BT840_RSP_SEND );

            log_printf( &logger, ">>> Disconnecting BT peer.\r\n" );
            bt840_set_cmd_mode( &bt840 );
            bt840_cmd_set( ctx, BT840_CMD_DISCONNECT, "1" );
            error_flag |= bt840_read_response( ctx, BT840_RSP_DISCONNECTED );
            break;
        }
        Delay_ms ( 1 );
    }

    log_printf( &logger, ">>> Reboot.\r\n" );
    bt840_cmd_run( ctx, BT840_CMD_RESET );
    error_flag |= bt840_read_response( ctx, BT840_RSP_OK );
    
    return error_flag;
}

// ------------------------------------------------------------------------ END
