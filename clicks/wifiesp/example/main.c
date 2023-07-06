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

#define APP_SSID                            "MikroE Public"
#define APP_PASSWORD                        "mikroe.guest"

#define PROCESS_BUFFER_SIZE                 610

// ------------------------------------------------------------------ VARIABLES

uint8_t page[ ] = "<a href=\"https://www.mikroe.com/\">MikroElektronika</a>\
<h1 style=\"color:red;\">WiFi ESP click board</h1>";
uint8_t page_len[ 10 ] = { 0 };
uint8_t send_buf[ 10 ] = { 0 };
static uint8_t link_id[ 2 ] = { 0 };

static wifiesp_t wifiesp;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]  = { 0 };
static int32_t app_buf_len                  = 0;

static err_t app_error_flag;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void wifiesp_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void wifiesp_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t wifiesp_process ( void )
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = wifiesp_generic_read( &wifiesp, rx_buf, PROCESS_BUFFER_SIZE );
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
        return WIFIESP_OK;
    }
    return WIFIESP_ERROR;
}

static err_t wifiesp_rsp_check ( char * response )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    wifiesp_clear_app_buf( );
    wifiesp_process( );
    while ( ( 0 == strstr( app_buf, response ) ) &&
            ( 0 == strstr( app_buf, WIFIESP_RSP_ERROR ) ) )
    {
        wifiesp_process( );
        if ( timeout_cnt++ > timeout )
        {
            wifiesp_clear_app_buf( );
            return WIFIESP_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms( 5 );
    wifiesp_process( );
    if ( strstr( app_buf, response ) )
    {
        return WIFIESP_OK;
    }
    else if ( strstr( app_buf, WIFIESP_RSP_ERROR ) )
    {
        return WIFIESP_ERROR_CMD;
    }
    return WIFIESP_ERROR_UNKNOWN;
}

static void wifiesp_error_check( err_t error_flag )
{
    switch ( error_flag )
    {
        case WIFIESP_OK:
        {
            wifiesp_log_app_buf( );
            break;
        }
        case WIFIESP_ERROR:
        {
            log_error( &logger, " Overflow!" );
            break;
        }
        case WIFIESP_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        case WIFIESP_ERROR_CMD:
        {
            log_error( &logger, " CMD!" );
            break;
        }
        case WIFIESP_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    log_printf( &logger, "\r\n-----------------------------------\r\n" );
    Delay_ms( 500 );
}

void wifi_communication_init( void )
{
    wifiesp_process( ); // dummy read
    wifiesp_clear_app_buf( );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_CHECK, NULL );
    app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_OK );
    wifiesp_error_check( app_error_flag );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_RESTORE, NULL );
    app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_OK );
    wifiesp_error_check( app_error_flag );
    uart_clear ( &wifiesp.uart );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_CHECK_FIRMWARE, NULL );
    app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_OK );
    wifiesp_error_check( app_error_flag );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_SET_MODE, "1" );
    app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_OK );
    wifiesp_error_check( app_error_flag );
    
    wifiesp_clear_app_buf( );
    strcpy ( app_buf, "\"" );
    strcat ( app_buf, APP_SSID );
    strcat ( app_buf, "\",\"" );
    strcat ( app_buf, APP_PASSWORD );
    strcat ( app_buf, "\"" );
    app_buf_len = strlen ( app_buf );
    wifiesp_send_cmd( &wifiesp, WIFIESP_CONNECT, app_buf );
    wifiesp_clear_app_buf ( );
    app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_OK );
    wifiesp_error_check( app_error_flag );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_SET_MULTIPLE_CONNECTION, "1" );
    app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_OK );
    wifiesp_error_check( app_error_flag );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_SET_AS_SERVER, "1,80" );
    app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_OK );
    wifiesp_error_check( app_error_flag );
    
    wifiesp_send_cmd( &wifiesp, WIFIESP_GET_IP, NULL );
    app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_OK );
    wifiesp_error_check( app_error_flag );
}

static void wifiesp_str_cut_chr ( uint8_t *str, uint8_t chr )
{
    uint16_t cnt_0 = 0;
    uint16_t cnt_1 = 0;
    for ( cnt_0 = 0; cnt_0 < strlen( str ); cnt_0++ )
    {
        if ( str[ cnt_0 ] == chr )
        {
            for ( cnt_1 = cnt_0; cnt_1 < strlen( str ); cnt_1++ )
            {
                str[ cnt_1 ] = str[ cnt_1 + 1 ];
            }
        }
    }
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

    // Click initialization.
    wifiesp_cfg_setup( &cfg );
    WIFIESP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifiesp_init( &wifiesp, &cfg );
    wifiesp_default_cfg( &wifiesp );
    Delay_ms( 1000 );
    
    // Communication initialization
    wifi_communication_init( );
    
    uint16_to_str ( strlen( page ), page_len );
    wifiesp_str_cut_chr ( page_len, ' ' );
    
    log_info( &logger, "Please connect to the IP address listed above.\r\n" );
}

void application_task ( void )
{
    if ( WIFIESP_OK == wifiesp_rsp_check( WIFIESP_RECEIVE ) ) 
    {
        link_id[ 0 ] = *( strstr( app_buf, WIFIESP_RECEIVE ) + 5 );
        strcpy ( send_buf, link_id );
        strcat ( send_buf, "," );
        strcat ( send_buf, page_len );
        wifiesp_str_cut_chr ( send_buf, ' ' );
        wifiesp_log_app_buf( );
        wifiesp_clear_app_buf( );
        Delay_ms( 100 );
        wifiesp_process( );
        wifiesp_log_app_buf( );
        wifiesp_send_cmd( &wifiesp, WIFIESP_SEND, send_buf );
        app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_READY_FOR_SEND );
        wifiesp_log_app_buf( );
        Delay_ms( 100 );
        wifiesp_generic_write( &wifiesp, page, strlen( page ) );
        app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_SEND_OK );
        wifiesp_error_check( app_error_flag );
        wifiesp_send_cmd( &wifiesp, WIFIESP_CLOSE, link_id );
        app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_OK );
        wifiesp_error_check( app_error_flag );
        wifiesp_clear_app_buf( );
        
        wifiesp_process( );
        wifiesp_log_app_buf( );
        wifiesp_clear_app_buf( );
        uart_clear ( &wifiesp.uart );
        Delay_ms( 100 );
    }
}

void main ( void )
{
    application_init( );
    
    for ( ; ; )
    {
        application_task ( );
    }
}


// ------------------------------------------------------------------------ END
