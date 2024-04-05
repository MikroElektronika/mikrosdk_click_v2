/*!
 * @file main.c
 * @brief IoT ExpressLink 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of IoT ExpressLink 3 click board by bridging the USB UART
 * to mikroBUS UART which allows the click board to establish a connection with
 * the IoT ExpressLink over the Quick Connect demo application without an AWS account.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, resets the click board to factory default settings, reads
 * and displays the vendor model and thing name on the USB UART, sets the WiFi credentials,
 * and attempts to connect to the AWS Cloud. If the initial attempt fails and the error
 * message "Failed to access network" or "Failed to login AWS (MQTT) broker" appears,
 * check the WiFi credentials and try running the example again.
 *
 * ## Application Task
 * All data received from the USB UART will be forwarded to mikroBUS UART, and vice versa.
 * At this point you should disconnect from the UART terminal and run the Quick Connect
 * demo application.
 *
 * ## Additional Function
 * - static void iotexpresslink3_clear_app_buf ( void )
 * - static err_t iotexpresslink3_process ( iotexpresslink3_t *ctx )
 * - static err_t iotexpresslink3_read_response ( iotexpresslink3_t *ctx )
 *
 * @note
 * To run the demo, follow the below steps:
 * 1. If you opened a terminal application in the previous step, be sure to disconnect that
 *    application from the serial port. 
 * 2. Download the Quick Connect executable: 
 *    Mac: https://quickconnectexpresslinkutility.s3.us-west-2.amazonaws.com/QuickConnect_v1.9_macos.x64.tar.gz
 *    Windows: https://quickconnectexpresslinkutility.s3.us-west-2.amazonaws.com/QuickConnect_v1.9_windows.x64.zip
 *    Linux: https://quickconnectexpresslinkutility.s3.us-west-2.amazonaws.com/QuickConnect_v1.9_linux.x64.tar.gz
 * 3. Unzip the package, and follow the steps from the README file.
 * 
 * The demo will connect to IoT ExpressLink and give you an URL that you can use to visualize data
 * flowing from the device to the cloud using AT+SEND commands. The demo will run for up
 * to two minutes, and afterwards, you will be able to type AT+SEND commands yourself and
 * see the data coming in on the visualizer.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "iotexpresslink3.h"

// Enter valid WiFi credentials below
#define WIFI_SSID               "MikroE Public"     // WiFi SSID
#define WIFI_PASS               "mikroe.guest"      // WiFi Password

// Application buffer size
#define APP_BUFFER_SIZE         500
#define PROCESS_BUFFER_SIZE     200

static iotexpresslink3_t iotexpresslink3;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief IoT ExpressLink 3 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void iotexpresslink3_clear_app_buf ( void );

/**
 * @brief IoT ExpressLink 3 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #iotexpresslink3_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t iotexpresslink3_process ( iotexpresslink3_t *ctx );

/**
 * @brief IoT ExpressLink read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink_t object definition for detailed explanation.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t iotexpresslink3_read_response ( iotexpresslink3_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    iotexpresslink3_cfg_t iotexpresslink3_cfg;  /**< Click config object. */

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
    iotexpresslink3_cfg_setup( &iotexpresslink3_cfg );
    IOTEXPRESSLINK3_MAP_MIKROBUS( iotexpresslink3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == iotexpresslink3_init( &iotexpresslink3, &iotexpresslink3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "Reset device\r\n\n" );
    iotexpresslink3_reset_device ( &iotexpresslink3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "Factory reset\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK3_CMD_FACTORY_RESET );
    iotexpresslink3_send_cmd ( &iotexpresslink3, app_buf );
    iotexpresslink3_read_response ( &iotexpresslink3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Vendor model\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK3_CMD_CONF_CHECK );
    strcat ( app_buf, IOTEXPRESSLINK3_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK3_CONF_KEY_ABOUT );
    iotexpresslink3_send_cmd ( &iotexpresslink3, app_buf );
    iotexpresslink3_read_response ( &iotexpresslink3 );
    
    log_printf( &logger, "Thing name\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK3_CMD_CONF_CHECK );
    strcat ( app_buf, IOTEXPRESSLINK3_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK3_CONF_KEY_THING_NAME );
    iotexpresslink3_send_cmd ( &iotexpresslink3, app_buf );
    iotexpresslink3_read_response ( &iotexpresslink3 );
    
    log_printf( &logger, "WiFi SSID\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK3_CMD_CONF );
    strcat ( app_buf, IOTEXPRESSLINK3_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK3_CONF_KEY_SSID );
    strcat ( app_buf, IOTEXPRESSLINK3_CMD_SIGN_EQUAL );
    strcat ( app_buf, WIFI_SSID );
    iotexpresslink3_send_cmd ( &iotexpresslink3, app_buf );
    iotexpresslink3_read_response ( &iotexpresslink3 );
    
    log_printf( &logger, "WiFi Password\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK3_CMD_CONF );
    strcat ( app_buf, IOTEXPRESSLINK3_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK3_CONF_KEY_PASSPHRASE );
    strcat ( app_buf, IOTEXPRESSLINK3_CMD_SIGN_EQUAL );
    strcat ( app_buf, WIFI_PASS );
    iotexpresslink3_send_cmd ( &iotexpresslink3, app_buf );
    iotexpresslink3_read_response ( &iotexpresslink3 );
    
    log_printf( &logger, "Try to connect\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK3_CMD_CONNECT );
    iotexpresslink3_send_cmd ( &iotexpresslink3, app_buf );
    iotexpresslink3_read_response ( &iotexpresslink3 );
    
    log_info( &logger, " Application Task " );
    
    log_printf( &logger, "Now close the UART terminal and switch to the QuickConnect app\r\n" );
    Delay_ms ( 1000 );
    
    uart_set_blocking( &logger.uart, false );
}

void application_task ( void ) 
{
    app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &iotexpresslink3.uart, app_buf, app_buf_len );
        iotexpresslink3_clear_app_buf( );
    }
    app_buf_len = uart_read( &iotexpresslink3.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &logger.uart, app_buf, app_buf_len );
        iotexpresslink3_clear_app_buf( );
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

static void iotexpresslink3_clear_app_buf ( void ) 
{
    memset( app_buf, 0, APP_BUFFER_SIZE );
    app_buf_len = 0;
}

static void iotexpresslink3_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t iotexpresslink3_process ( iotexpresslink3_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = iotexpresslink3_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return IOTEXPRESSLINK3_OK;
    }
    return IOTEXPRESSLINK3_ERROR;
}


static err_t iotexpresslink3_read_response ( iotexpresslink3_t *ctx ) 
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 30000;
    iotexpresslink3_clear_app_buf ( );
    iotexpresslink3_process( ctx );
    while ( ( 0 == strstr( app_buf, IOTEXPRESSLINK3_RSP_OK ) ) &&
            ( 0 == strstr( app_buf, IOTEXPRESSLINK3_RSP_ERR ) ) )
    {
        iotexpresslink3_process( ctx );
        if ( timeout_cnt++ > timeout )
        {
            iotexpresslink3_clear_app_buf( );
            return IOTEXPRESSLINK3_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    iotexpresslink3_process( ctx );
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s\r\n", app_buf );
    }
    if ( strstr( app_buf, IOTEXPRESSLINK3_RSP_OK ) )
    {
        iotexpresslink3_clear_app_buf( );
        return IOTEXPRESSLINK3_OK;
    }
    else if ( strstr( app_buf, IOTEXPRESSLINK3_RSP_ERR ) )
    {
        iotexpresslink3_clear_app_buf( );
        return IOTEXPRESSLINK3_ERROR_CMD;
    }
    iotexpresslink3_clear_app_buf( );
    return IOTEXPRESSLINK3_ERROR_UNKNOWN;
}

// ------------------------------------------------------------------------ END
