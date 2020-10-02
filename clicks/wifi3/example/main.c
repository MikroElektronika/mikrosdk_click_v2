/*!
 * \file 
 * \brief wifi3 Click example
 * 
 * # Description
 * This example initializes wifi connestion to a network and starts web server,
 * writes "MikroeE - Wifi3" to the client web application (for example web browser).
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Additional Function
 * Checking module and initializes connection with network, starts web server
 * 
 * ## Application Task  
 * Waits for client request (paste IP in web browser and refresh to send request),
 * writes "MikroeE - Wifi3" to client application.
 * 
 * *note:* 
 * Algorithm for communication initialization is:
 * # Turn all 3 connected click pins ON
 * # Set baud rate to 74880.
 * # Do wifi check and reset
 * # Change baud rate to 115200
 * # Set working mode
 * # Set multi or singe connection mode
 * # Connect
 * # Start communication with client/server
 * 
 * More related AT commands and their argumets format could be found on the following link:
 * https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "wifi3.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_CLIENT_SERVER

const uint8_t page_begin[] = "<html><p>";
const uint8_t page_end[] = "</p></html>";

static wifi3_t wifi3;
static log_t logger;

static uint8_t r_buf[ PROCESS_RX_BUFFER_SIZE ] = { 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

uint8_t wifi_communication_init( void )
{
    uint8_t check = 0x00;
    
    digital_out_high( &wifi3.an );
    digital_out_high( &wifi3.rst );
    digital_out_high( &wifi3.cs );
    
    check = wifi3_send_cmd( &wifi3 , &logger , &WIFI3_CHECK , NULL );
    if(!check)
        return 0;
    
    check = wifi3_send_cmd( &wifi3 , &logger , &WIFI3_RST , NULL );
    if(!check)
        return 0;
    
    // WARNING! Baud rate changes from 74880 -> 115200!!! If don't change baud, you will get garbage.
    uart_set_baud( &wifi3.uart, 115200 ); 
    
    check = wifi3_send_cmd( &wifi3 , &logger , &WIFI3_CHECK_FIRMWARE , NULL );
    if(!check)
        return 0;    
    
    check = wifi3_send_cmd( &wifi3 , &logger , &WIFI3_SET_MODE , "1" );
    if(!check)
        return 0;
    
    // Change network username and password arguments in same format
    check = wifi3_send_cmd( &wifi3 , &logger , &WIFI3_CONNECT , "\"MikroE Public\",\"mikroe.guest\"" );
    if(!check)
        return 0;
    
    check = wifi3_send_cmd( &wifi3 , &logger , &WIFI3_SET_MULTIPLE_CONNECTION , "1" );
    if(!check)
        return 0;
    
    check = wifi3_send_cmd( &wifi3 , &logger , &WIFI3_SET_SERVER_TIMEOUT , NULL );
    if(!check)
        return 0;
    
    check = wifi3_send_cmd( &wifi3 , &logger , &WIFI3_GET_IP , NULL );
    if(!check)
        return 0;
    
    check = wifi3_send_cmd( &wifi3 , &logger , &WIFI3_SET_AS_SERVER , "1,80" );
    if(!check)
        return 0;
    
    return 1;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifi3_cfg_t cfg;
    uint8_t init_pass = 0;
    
    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wifi3_cfg_setup( &cfg );
    WIFI3_MAP_MIKROBUS( cfg , MIKROBUS_1 );
    wifi3_init( &wifi3 , &cfg );
    
    // Communication initialization
    
     init_pass = wifi_communication_init( );
}

void application_task ( void )
{
    uint8_t str[ 100 ] = { 0 };
    
    strcat( str , page_begin );
    strcat( str, "MikroE - Wifi3" );
    strcat( str , page_end );
    
    wifi3_read( &wifi3 , r_buf );
    wifi3_send_cmd( &wifi3 , &logger , &WIFI3_SEND , "0,34" );
    Delay_ms( 500 );
    
    wifi3_generic_write( &wifi3 , str , strlen( str ) );
    Delay_ms( 500 );
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
