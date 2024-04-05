/*!
 * @file main.c
 * @brief IoT ExpressLink Click Example.
 *
 * # Description
 * This example demonstrates the use of IoT ExpressLink click board by bridging the USB UART
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
 * - static void iotexpresslink_clear_app_buf ( void )
 * - static err_t iotexpresslink_process ( uart_t *uart )
 * - static err_t iotexpresslink_read_response ( iotexpresslink_t *ctx )
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
#include "iotexpresslink.h"

#define PROCESS_BUFFER_SIZE 500

// Enter valid WiFi credentials below
#define WIFI_SSID   "MikroE Public"     // WiFi SSID
#define WIFI_PASS   "mikroe.guest"      // WiFi Password

static iotexpresslink_t iotexpresslink;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief IoT ExpressLink clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void iotexpresslink_clear_app_buf ( void );

/**
 * @brief IoT ExpressLink data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #iotexpresslink_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t iotexpresslink_process ( iotexpresslink_t *ctx ) ;

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
static err_t iotexpresslink_read_response ( iotexpresslink_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    iotexpresslink_cfg_t iotexpresslink_cfg;  /**< Click config object. */

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
    iotexpresslink_cfg_setup( &iotexpresslink_cfg );
    IOTEXPRESSLINK_MAP_MIKROBUS( iotexpresslink_cfg, MIKROBUS_1 );
    if ( UART_ERROR == iotexpresslink_init( &iotexpresslink, &iotexpresslink_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "Reset device\r\n\n" );
    iotexpresslink_reset_device ( &iotexpresslink );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "Factory reset\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_FACTORY_RESET );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Vendor model\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_CONF_CHECK );
    strcat ( app_buf, IOTEXPRESSLINK_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK_CONF_KEY_ABOUT );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    
    log_printf( &logger, "Thing name\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_CONF_CHECK );
    strcat ( app_buf, IOTEXPRESSLINK_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK_CONF_KEY_THING_NAME );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    
    log_printf( &logger, "WiFi SSID\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_CONF );
    strcat ( app_buf, IOTEXPRESSLINK_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK_CONF_KEY_SSID );
    strcat ( app_buf, IOTEXPRESSLINK_CMD_SIGN_EQUAL );
    strcat ( app_buf, WIFI_SSID );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    
    log_printf( &logger, "WiFi Password\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_CONF );
    strcat ( app_buf, IOTEXPRESSLINK_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK_CONF_KEY_PASSPHRASE );
    strcat ( app_buf, IOTEXPRESSLINK_CMD_SIGN_EQUAL );
    strcat ( app_buf, WIFI_PASS );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    
    log_printf( &logger, "Try to connect\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_CONNECT );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    
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
        uart_write ( &iotexpresslink.uart, app_buf, app_buf_len );
        iotexpresslink_clear_app_buf( );
    }
    app_buf_len = uart_read( &iotexpresslink.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &logger.uart, app_buf, app_buf_len );
        iotexpresslink_clear_app_buf( );
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

static void iotexpresslink_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t iotexpresslink_process ( iotexpresslink_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = iotexpresslink_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = app_buf_len;
        if ( ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) && ( app_buf_len > 0 ) ) 
        {
            buf_cnt = PROCESS_BUFFER_SIZE - ( ( app_buf_len + rx_size ) - PROCESS_BUFFER_SIZE );
            memmove ( app_buf, &app_buf[ PROCESS_BUFFER_SIZE - buf_cnt ], buf_cnt );
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ buf_cnt++ ] = rx_buf[ rx_cnt ];
                if ( app_buf_len < PROCESS_BUFFER_SIZE )
                {
                    app_buf_len++;
                }
            }
        }
        return IOTEXPRESSLINK_OK;
    }
    return IOTEXPRESSLINK_ERROR;
}

static err_t iotexpresslink_read_response ( iotexpresslink_t *ctx ) 
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 30000;
    memset( app_buf, 0, PROCESS_BUFFER_SIZE );
    app_buf_len = 0;
    iotexpresslink_process( ctx );
    while ( ( 0 == strstr( app_buf, IOTEXPRESSLINK_RSP_OK ) ) &&
            ( 0 == strstr( app_buf, IOTEXPRESSLINK_RSP_ERR ) ) )
    {
        iotexpresslink_process( ctx );
        if ( timeout_cnt++ > timeout )
        {
            iotexpresslink_clear_app_buf( );
            return IOTEXPRESSLINK_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    iotexpresslink_process( ctx );
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s\r\n", app_buf );
    }
    if ( strstr( app_buf, IOTEXPRESSLINK_RSP_OK ) )
    {
        iotexpresslink_clear_app_buf( );
        return IOTEXPRESSLINK_OK;
    }
    else if ( strstr( app_buf, IOTEXPRESSLINK_RSP_ERR ) )
    {
        iotexpresslink_clear_app_buf( );
        return IOTEXPRESSLINK_ERROR_CMD;
    }
    iotexpresslink_clear_app_buf( );
    return IOTEXPRESSLINK_ERROR_UNKNOWN;
}

// ------------------------------------------------------------------------ END
