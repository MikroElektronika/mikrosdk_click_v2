/*!
 * @file main.c
 * @brief BL653 Click Example.
 *
 * # Description
 * This example demonstrates the use of BL653 Click board by processing data
 * from a connected BT device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - BL653_POWER_UP:
 * Powers up the device and reads the system information.
 *  - BL653_CONFIG_EXAMPLE:
 * Sets the BT device name.
 *  - BL653_EXAMPLE:
 * Performs a BT terminal example by processing all data from a connected BT device 
 * and sending back an adequate response messages.
 *
 * ## Additional Function
 * - static void bl653_clear_app_buf ( void )
 * - static void bl653_log_app_buf ( void )
 * - static err_t bl653_process ( bl653_t *ctx )
 * - static err_t bl653_read_response ( bl653_t *ctx, uint8_t *rsp )
 * - static err_t bl653_power_up ( bl653_t *ctx )
 * - static err_t bl653_config_example ( bl653_t *ctx )
 * - static err_t bl653_example ( bl653_t *ctx )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "bl653.h"

// Message content
#define MESSAGE_CONTENT     "BL653 Click board - demo example."

// Local device name.
#define DEVICE_NAME         "BL653 Click"

static bl653_t bl653;
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
    BL653_POWER_UP = 1,
    BL653_CONFIG_EXAMPLE,
    BL653_EXAMPLE

} bl653_app_state_t;

static bl653_app_state_t app_state = BL653_POWER_UP;

/**
 * @brief BL653 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void bl653_clear_app_buf ( void );

/**
 * @brief BL653 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void bl653_log_app_buf ( void );

/**
 * @brief BL653 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bl653_process ( bl653_t *ctx );

/**
 * @brief BL653 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bl653_read_response ( bl653_t *ctx, uint8_t *rsp );

/**
 * @brief BL653 power up function.
 * @details This function powers up the device, and reads the system information.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bl653_power_up ( bl653_t *ctx );

/**
 * @brief BL653 config example function.
 * @details This function sets the BT device name.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bl653_config_example ( bl653_t *ctx );

/**
 * @brief BL653 example function.
 * @details This function performs a BT terminal example by processing all data from
 * a connected BT device and sending back an adequate response messages.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bl653_example ( bl653_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bl653_cfg_t bl653_cfg;  /**< Click config object. */

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
    bl653_cfg_setup( &bl653_cfg );
    BL653_MAP_MIKROBUS( bl653_cfg, MIKROBUS_1 );
    if ( UART_ERROR == bl653_init( &bl653, &bl653_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = BL653_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case BL653_POWER_UP:
        {
            if ( BL653_OK == bl653_power_up( &bl653 ) )
            {
                app_state = BL653_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BL653_CONFIG_EXAMPLE:
        {
            if ( BL653_OK == bl653_config_example( &bl653 ) )
            {
                app_state = BL653_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BL653_EXAMPLE:
        {
            bl653_example( &bl653 );
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

static void bl653_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void bl653_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t bl653_process ( bl653_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = bl653_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return BL653_OK;
    }
    return BL653_ERROR;
}

static err_t bl653_read_response ( bl653_t *ctx, uint8_t *rsp ) 
{
    #define READ_RESPONSE_TIMEOUT_MS 30000
    uint32_t timeout_cnt = 0;
    bl653_clear_app_buf ( );
    bl653_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, BL653_RSP_ERROR ) ) )
    {
        bl653_process( ctx );
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            bl653_log_app_buf( );
            bl653_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return BL653_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    bl653_process( ctx );
    bl653_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return BL653_OK;
    }
    return BL653_ERROR_CMD;
}

static err_t bl653_power_up ( bl653_t *ctx )
{
    err_t error_flag = BL653_OK;
    
    log_printf( &logger, ">>> Reset device.\r\n" );
    bl653_reset_device( &bl653 );
    while ( BL653_OK == bl653_process( ctx ) )
    {
        bl653_log_app_buf( );
        bl653_clear_app_buf ( );
    }
    log_printf( &logger, "--------------------------------\r\n" );

    log_printf( &logger, ">>> Factory reset.\r\n" );
    bl653_cmd_run( &bl653, BL653_CMD_FACTORY_RESET, NULL );
    error_flag |= bl653_read_response( &bl653, BL653_RSP_OK );

    log_printf( &logger, ">>> Check communication.\r\n" );
    bl653_cmd_run( &bl653, BL653_CMD_AT, NULL );
    error_flag |= bl653_read_response( &bl653, BL653_RSP_OK );

    log_printf( &logger, ">>> Get device type.\r\n" );
    bl653_cmd_run( ctx, BL653_CMD_GET_INFO, BL653_PARAM_DEVICE_TYPE );
    error_flag |= bl653_read_response( ctx, BL653_RSP_OK );

    log_printf( &logger, ">>> Get firmware version.\r\n" );
    bl653_cmd_run( ctx, BL653_CMD_GET_INFO, BL653_PARAM_FW_VERSION );
    error_flag |= bl653_read_response( ctx, BL653_RSP_OK );

    log_printf( &logger, ">>> Get BT address.\r\n" );
    bl653_cmd_run( ctx, BL653_CMD_GET_INFO, BL653_PARAM_BT_ADDRESS );
    error_flag |= bl653_read_response( ctx, BL653_RSP_OK );

    return error_flag;
}

static err_t bl653_config_example ( bl653_t *ctx )
{
    err_t error_flag = BL653_OK;

    log_printf( &logger, ">>> Set device name to \"%s\".\r\n", ( char * ) DEVICE_NAME );
    bl653_cmd_set( ctx, BL653_CMD_PARAM_ACCESS_STR, BL653_PARAM_ID_DEVICE_NAME, DEVICE_NAME );
    error_flag |= bl653_read_response( ctx, BL653_RSP_OK );
    
    log_printf( &logger, ">>> Save settings.\r\n" );
    bl653_cmd_run( &bl653, BL653_CMD_SAVE_SETTINGS, NULL );
    error_flag |= bl653_read_response( ctx, BL653_RSP_OK );
    
    log_printf( &logger, ">>> Reboot.\r\n" );
    bl653_cmd_run( ctx, BL653_CMD_WARM_RESET, NULL );
    error_flag |= bl653_read_response( ctx, BL653_RSP_OK );
    
    return error_flag;
}

static err_t bl653_example ( bl653_t *ctx )
{
    err_t error_flag = BL653_OK;
    uint32_t timeout_cnt = 0;

    #define BT_TERMINAL_TIMEOUT_MS      60000
    #define BT_TERMINAL_MESSAGE_FREQ_MS 5000
    #define TERMINATION_CMD             "END"
    #define TERMINATION_RESPONSE        "END command received, the connection will be terminated in a few seconds."
    #define TERMINATION_TIMEOUT         "Timeout, closing the connection in a few seconds."
    #define NEW_LINE_STRING             "\r\n"
    #define DISCONNECT_PEER             "0"

    log_printf( &logger, ">>> Waiting for a BT peer to establish connection with the Click board...\r\n" );
    for ( ; ; )
    {
        bl653_clear_app_buf( );
        if ( BL653_OK == bl653_process( ctx ) )
        {
            Delay_ms ( 200 );
            bl653_process( ctx );
            bl653_log_app_buf( );
            if ( strstr( app_buf, BL653_RSP_CONNECT ) )
            {
                log_printf( &logger, "--------------------------------\r\n" );
                log_printf( &logger, ">>> BT peer has connected.\r\n" );
                break;
            }
        }
    }

    log_printf( &logger, ">>> Waiting for data (up to 60 seconds)...\r\n" );
    log_printf( &logger, ">>> Connection will be terminated if the Click receives an \"END\" string.\r\n" );
    for ( ; ; )
    {
        bl653_clear_app_buf( );
        if ( BL653_OK == bl653_process( ctx ) )
        {
            Delay_ms ( 200 );
            timeout_cnt = 0;
            bl653_process( ctx );
            bl653_log_app_buf( );
            if ( strstr( app_buf, TERMINATION_CMD ) )
            {
                log_printf( &logger, ">>> Terminating connection on demand.\r\n" );
                bl653_generic_write ( ctx, TERMINATION_RESPONSE, strlen ( TERMINATION_RESPONSE ) );
                bl653_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
                Delay_ms ( 100 );

                log_printf( &logger, ">>> Disconnecting BT peer.\r\n" );
                // Sending 4 escape chars with at least 250ms intervening delay
                bl653_generic_write ( ctx, BL653_CMD_VSP_ESCAPE_CHAR, strlen ( BL653_CMD_VSP_ESCAPE_CHAR ) );
                Delay_ms ( 300 );
                bl653_generic_write ( ctx, BL653_CMD_VSP_ESCAPE_CHAR, strlen ( BL653_CMD_VSP_ESCAPE_CHAR ) );
                Delay_ms ( 300 );
                bl653_generic_write ( ctx, BL653_CMD_VSP_ESCAPE_CHAR, strlen ( BL653_CMD_VSP_ESCAPE_CHAR ) );
                Delay_ms ( 300 );
                bl653_generic_write ( ctx, BL653_CMD_VSP_ESCAPE_CHAR, strlen ( BL653_CMD_VSP_ESCAPE_CHAR ) );
                Delay_ms ( 300 );
                error_flag |= bl653_read_response( ctx, BL653_RSP_NO_CARRIER );
                break;
            }
            else if ( strstr( app_buf, BL653_RSP_NO_CARRIER ) )
            {
                log_printf( &logger, ">>> BT peer has disconnected.\r\n" );
                break;
            }
        }
        timeout_cnt++;
        if ( 0 == ( timeout_cnt % BT_TERMINAL_MESSAGE_FREQ_MS ) )
        {
            log_printf( &logger, ">>> Sending \"%s\" message to connected device.\r\n", ( char * ) MESSAGE_CONTENT );
            bl653_generic_write ( ctx, MESSAGE_CONTENT, strlen ( MESSAGE_CONTENT ) );
            bl653_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
            Delay_ms ( 100 );
        }
        if ( BT_TERMINAL_TIMEOUT_MS < timeout_cnt )
        {
            log_printf( &logger, ">>> Terminating connection due to 60s timeout expiration.\r\n" );
            bl653_generic_write ( ctx, TERMINATION_TIMEOUT, strlen ( TERMINATION_TIMEOUT ) );
            bl653_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
            Delay_ms ( 100 );

            log_printf( &logger, ">>> Disconnecting BT peer.\r\n" );
            // Sending 4 escape chars with at least 250ms intervening delay
            bl653_generic_write ( ctx, BL653_CMD_VSP_ESCAPE_CHAR, strlen ( BL653_CMD_VSP_ESCAPE_CHAR ) );
            Delay_ms ( 300 );
            bl653_generic_write ( ctx, BL653_CMD_VSP_ESCAPE_CHAR, strlen ( BL653_CMD_VSP_ESCAPE_CHAR ) );
            Delay_ms ( 300 );
            bl653_generic_write ( ctx, BL653_CMD_VSP_ESCAPE_CHAR, strlen ( BL653_CMD_VSP_ESCAPE_CHAR ) );
            Delay_ms ( 300 );
            bl653_generic_write ( ctx, BL653_CMD_VSP_ESCAPE_CHAR, strlen ( BL653_CMD_VSP_ESCAPE_CHAR ) );
            Delay_ms ( 300 );
            error_flag |= bl653_read_response( ctx, BL653_RSP_NO_CARRIER );
            break;
        }
        Delay_ms ( 1 );
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------ END
