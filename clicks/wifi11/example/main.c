/*!
 * \file 
 * \brief Wifi11 Click example
 * 
 * # Description
 * This example reads and processes data from WiFi 11 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and powers up the module, then connects to the desired AP
 * and creates TCP and UDP servers on the desired local port.
 * 
 * ## Application Task  
 * Logs all the received data and module's responses on the USB UART.
 * 
 * ## Additional Function
 * - static void wifi11_clear_app_buf ( void )
 * - static void wifi11_error_check( err_t error_flag )
 * - static void wifi11_log_app_buf ( void )
 * - static err_t wifi11_rsp_check ( void )
 * - static err_t wifi11_process ( void )
 * 
 * @note 
 * In order for the example to work, user needs to set the AP SSID, password, and Local port
 * on which the TCP and UDP servers will be created.
 * Enter valid data for the following macros: AP_SSID, AP_PASSWORD and LOCAL_PORT.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "wifi11.h"
#include "string.h"

#define APP_OK                              0
#define APP_ERROR_DRIVER                    -1
#define APP_ERROR_OVERFLOW                  -2
#define APP_ERROR_TIMEOUT                   -3

#define RSP_OK                              "OK"
#define RSP_ERROR                           "ERROR"

#define AP_SSID                             ""   // Set AP SSID
#define AP_PASSWORD                         ""   // Set AP password - if the AP is OPEN remain this NULL
#define LOCAL_PORT                          1    // Set Local port on which the TCP and UDP servers will be created.

#define PROCESS_BUFFER_SIZE                 500

static wifi11_t wifi11;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]  = { 0 };
static int32_t app_buf_len                  = 0;
static int32_t app_buf_cnt                  = 0;

static err_t app_error_flag;


/**
 * @brief WiFi 11 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @note None.
 */
static void wifi11_clear_app_buf ( void );

/**
 * @brief WiFi 11 data reading function.
 * @details This function reads data from device and appends data to application buffer.
 * 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wifi11_process ( void );

/**
 * @brief WiFi 11 check for errors.
 * @details This function checks for different types of errors and logs them on UART.
 * @note None.
 */
static void wifi11_error_check( err_t error_flag );

/**
 * @brief WiFi 11 logs application buffer.
 * @details This function logs data from application buffer.
 * @note None.
 */
static void wifi11_log_app_buf ( void );

/**
 * @brief WiFi 11 response check.
 * @details This function checks for response and returns the status of response.
 * 
 * @return application status.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wifi11_rsp_check ( void );

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifi11_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wifi11_cfg_setup( &cfg );
    WIFI11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifi11_init( &wifi11, &cfg );
    Delay_ms( 100 );
    
    wifi11_reset_device( &wifi11 );
    Delay_ms( 2000 );
    
    // dummy read
    wifi11_process( );
    wifi11_clear_app_buf( );
    
    log_printf( &logger, "\r\n ---- Common commands ---- \r\n" );
    Delay_ms( 500 );
    
    // Test AT command ready
    wifi11_send_cmd( &wifi11, WIFI11_CMD_AT );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms( 500 );

    // Query version info
    wifi11_send_cmd( &wifi11, WIFI11_CMD_ATSV );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms( 500 );
    
    log_printf( &logger, "\r\n ---- WiFi commands ---- \r\n" );
    Delay_ms( 500 );
    
    // Set WiFi mode - Station
    wifi11_send_cmd_with_parameter( &wifi11, WIFI11_CMD_ATPW, "1" );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // Connect to AP
    wifi11_connect_to_ap( &wifi11, AP_SSID, AP_PASSWORD );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // Wifi information
    wifi11_send_cmd( &wifi11, WIFI11_CMD_ATW );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms( 500 );
    
    log_printf( &logger, "\r\n ---- TCP/IP commands ---- \r\n" );
    Delay_ms( 500 );
    
    // Create TCP Server
    wifi11_create_tcp_udp_server( &wifi11, WIFI11_TCP_MODE, LOCAL_PORT );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // Create UDP Server
    wifi11_create_tcp_udp_server( &wifi11, WIFI11_UDP_MODE, LOCAL_PORT );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // Enable auto receive data mode
    wifi11_send_cmd_with_parameter( &wifi11, WIFI11_CMD_ATPK, "1" );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // Check network connection status
    wifi11_send_cmd( &wifi11, WIFI11_CMD_ATPI );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms( 500 );
    
    log_printf( &logger, "\r\n ---- Please connect to the TCP/UDP server listed above via" );
    log_printf( &logger, " a TCP/UDP client ---- \r\n" );                            
}

void application_task ( void )
{
    wifi11_process( );
    wifi11_log_app_buf( );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

static void wifi11_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t wifi11_process ( void )
{
    err_t return_flag = APP_ERROR_DRIVER;
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = wifi11_generic_read( &wifi11, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    { 
        int32_t buf_cnt = 0;
        return_flag = APP_OK;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            wifi11_clear_app_buf(  );
            return_flag = APP_ERROR_OVERFLOW;
        }
        else
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }

        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ )
        {
            if ( rx_buff[ rx_cnt ] != 0 ) 
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }
        }
    } 

    return return_flag;
}

static err_t wifi11_rsp_check ( void )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 10000;
    
    err_t error_flag = wifi11_process(  );
    
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
    {
        error_flag = wifi11_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
            {
                wifi11_send_cmd( &wifi11, WIFI11_CMD_AT );
                wifi11_process(  );
                Delay_ms( 100 );
            }
            wifi11_clear_app_buf(  );
            return APP_ERROR_TIMEOUT;
        }
        
        Delay_ms( 1 );
    }
    
    wifi11_log_app_buf();
    
    return APP_OK;
}

static void wifi11_error_check( err_t error_flag )
{
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        switch ( error_flag )
        {
            case -2:
                log_error( &logger, " Overflow!" );
                break;
            case -3:
                log_error( &logger, " Timeout!" );
                break;
            default:
                break;
        }
    }
}

static void wifi11_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    
    wifi11_clear_app_buf(  );
}

// ------------------------------------------------------------------------ END
