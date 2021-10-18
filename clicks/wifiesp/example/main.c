/*!
 * \file 
 * \brief wifiesp Click example
 * 
 * # Description
 * This example connects to the desired WiFi network and then
 * creates web server on the IP address assigned to the click board.
 * The user can connect to the server via web browser.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wifi communication, then connects to the desired WiFi network
 * and creates web server on the IP address assigned to the click board.
 * 
 * ## Application Task  
 * Waits for the client request (paste IP address in your web browser and 
 * refresh to send a request).
 * The click board will respond by sending a page content to the client.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "wifiesp.h"
#include "string.h"
#include "conversions.h"

#define APP_OK                                      0
#define APP_ERROR_DRIVER                    -1
#define APP_ERROR_OVERFLOW               -2
#define APP_ERROR_TIMEOUT                 -3

#define RSP_OK                                  "OK"
#define RSP_READY_FOR_SEND             ">"
#define RSP_SEND_OK                         "SEND OK"
#define RSP_ERROR                             "ERROR"

#define PROCESS_BUFFER_SIZE                 610

// ------------------------------------------------------------------ VARIABLES

uint8_t page[ ] = "<a href=\"https://www.mikroe.com/\">MikroElektronika</a>\
<h1 style=\"color:red;\">WiFi ESP click board</h1>";
uint8_t page_len[ 5 ];
uint8_t send_buf[ 10 ];
static uint8_t link_id[ 2 ] = { 0 };

static wifiesp_t wifiesp;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]  = { 0 };
static int32_t app_buf_len                  = 0;
static int32_t app_buf_cnt                  = 0;

static err_t app_error_flag;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void wifiesp_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static void wifiesp_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    wifiesp_clear_app_buf(  );
}

static err_t wifiesp_process ( void )
{
    err_t return_flag = APP_ERROR_DRIVER;
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = wifiesp_generic_read( &wifiesp, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    { 
        int32_t buf_cnt = 0;
        return_flag = APP_OK;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            wifiesp_clear_app_buf(  );
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
                buf_cnt--;
                app_buf_len--;
            }
        }
    } 

    return return_flag;
}

static err_t wifiesp_rsp_check ( char * response )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 50000;
    err_t error_flag = wifiesp_process(  );
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, response ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
    {
        error_flag = wifiesp_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        
        if ( timeout_cnt > timeout )
        {
            wifiesp_clear_app_buf(  );
            return APP_ERROR_TIMEOUT;
        }
        
        Delay_us( 100 );
    }
    if ( strcmp( response, WIFIESP_RECEIVE ) == 0 )
    {
        Delay_1ms( );
        wifiesp_process(  );
        link_id[ 0 ] = app_buf[ strstr( app_buf, response ) - &app_buf[ 0 ] + 5 ];
    }
    wifiesp_log_app_buf();
    
    return APP_OK;
}

static void wifiesp_error_check( err_t error_flag )
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
    log_printf( &logger, "\r\n-----------------------------------\r\n" );
}

void wifi_communication_init( void )
{
    wifiesp_process(  ); // dummy read
    wifiesp_clear_app_buf(  );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_CHECK, NULL );
    app_error_flag = wifiesp_rsp_check( RSP_OK );
    wifiesp_error_check( app_error_flag );
    Delay_ms( 500 );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_RST, NULL );
    app_error_flag = wifiesp_rsp_check( RSP_OK );
    wifiesp_error_check( app_error_flag );
    Delay_ms( 500 );
    wifiesp_process(  );
    wifiesp_clear_app_buf();
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_CHECK_FIRMWARE, NULL );
    app_error_flag = wifiesp_rsp_check( RSP_OK );
    wifiesp_error_check( app_error_flag );
    Delay_ms( 500 );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_SET_MODE, "1" );
    app_error_flag = wifiesp_rsp_check( RSP_OK );
    wifiesp_error_check( app_error_flag );
    Delay_ms( 500 );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_CONNECT, "\"MikroE Public\",\"mikroe.guest\"" );
    app_error_flag = wifiesp_rsp_check( RSP_OK );
    wifiesp_error_check( app_error_flag );
    Delay_ms( 500 );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_SET_MULTIPLE_CONNECTION, "1" );
    app_error_flag = wifiesp_rsp_check( RSP_OK );
    wifiesp_error_check( app_error_flag );
    Delay_ms( 500 );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_SET_AS_SERVER, "1,80" );
    app_error_flag = wifiesp_rsp_check( RSP_OK );
    wifiesp_error_check( app_error_flag );
    Delay_ms( 500 );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_CHECK_SERVER_TIMEOUT, NULL );
    app_error_flag = wifiesp_rsp_check( RSP_OK );
    wifiesp_error_check( app_error_flag );
    Delay_ms( 500 );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_GET_IP, NULL );
    app_error_flag = wifiesp_rsp_check( RSP_OK );
    wifiesp_error_check( app_error_flag );
    Delay_ms( 500 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifiesp_cfg_t cfg;
    
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

    wifiesp_cfg_setup( &cfg );
    WIFIESP_MAP_MIKROBUS( cfg , MIKROBUS_1 );
    wifiesp_init( &wifiesp , &cfg );
    wifiesp_default_cfg( &wifiesp );
    Delay_ms( 1000 );
    
    // Communication initialization
    
    wifi_communication_init( );
    
    uint16_to_str ( strlen( page ), page_len );
    str_cut_chr ( page_len, ' ' );
    
    log_info( &logger, "Please connect to the IP address listed above.\r\n" );
}

void application_task ( void )
{
    app_error_flag = wifiesp_rsp_check( WIFIESP_RECEIVE );
    Delay_ms( 100 );
    if ( app_error_flag == APP_OK ) 
    {
        strcpy ( send_buf, link_id );
        strcat ( send_buf, "," );
        strcat ( send_buf, page_len );
        str_cut_chr ( send_buf, ' ' );
        wifiesp_send_cmd( &wifiesp, WIFIESP_SEND, send_buf );
        app_error_flag = wifiesp_rsp_check( RSP_READY_FOR_SEND );
        Delay_ms( 100 );
        wifiesp_generic_write( &wifiesp, page, strlen( page ) );
        app_error_flag = wifiesp_rsp_check( RSP_SEND_OK );
        wifiesp_error_check( app_error_flag );
        wifiesp_send_cmd( &wifiesp, WIFIESP_CLOSE, link_id );
        app_error_flag = wifiesp_rsp_check( RSP_OK );
        wifiesp_error_check( app_error_flag );
        Delay_ms( 100 );
    }
}

void main ( void )
{
    
    application_init( );
    
    for ( ; ; )
    {
        application_task ( void );
    }
}


// ------------------------------------------------------------------------ END
