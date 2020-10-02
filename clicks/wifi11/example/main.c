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
 * Initializes driver module and stert sends AT comands.
 * 
 * ## Additional Function
 * - wifi11_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "wifi11.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

static wifi11_t wifi11;
static log_t logger;

#define WIFI11_CMD_AT     "AT"
#define WIFI11_CMD_ATSV   "ATSV"
#define WIFI11_CMD_ATPW   "ATPW=3"
#define WIFI11_CMD_ATW    "ATW?"
#define WIFI11_CMD_ATPC   "ATPC=0,10.101.22.181,1234"
#define WIFI11_CMD_ATPT   "ATPT=12,1:Hello world!"
#define WIFI11_CMD_ATPK   "ATPK=1"

static char wifi11_net_username[ 20 ] =   "MikroE Public";
static char wifi11_net_password[ 20 ] =   "mikroe.guest";

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void wifi11_process ( void )
{
    int16_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    
    rsp_size = wifi11_generic_read( &wifi11, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size > 0 )
    {  
        // Validation of the received data
        for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
        {
            if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
            {
                uart_rx_buffer[ check_buf_cnt ] = 13;
            }
        }
        log_printf( &logger, "%s \r\n", uart_rx_buffer );
        
        // Clear RX buffer
        memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
    } 
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifi11_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wifi11_cfg_setup( &cfg );
    WIFI11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifi11_init( &wifi11, &cfg );

    Delay_ms( 200 );
    wifi11_reset_device( &wifi11 );
    Delay_ms( 5000 );
    
    log_printf( &logger, "---- Start test command ----- \r\n" );
    wifi11_send_command( &wifi11, WIFI11_CMD_AT );
    wifi11_process( );
    Delay_ms( 200 );
    wifi11_send_command( &wifi11, WIFI11_CMD_ATSV );
    wifi11_process( );
    Delay_ms( 200 );
    log_printf( &logger, "---- WiFi configuration ----- \r\n" );
    wifi11_send_command( &wifi11, WIFI11_CMD_ATPW );
    wifi11_process( );
    Delay_ms( 1000 );
    wifi11_set_conect_to_ap( &wifi11, &wifi11_net_username[ 0 ], &wifi11_net_password[ 0 ] );
    wifi11_process( );
    Delay_ms( 10000 );
    wifi11_send_command( &wifi11, WIFI11_CMD_ATW );
    wifi11_process( );
    Delay_ms( 1000 );
    log_printf( &logger, "---- TCP example (Client) ----- \r\n" );
    wifi11_send_command( &wifi11, WIFI11_CMD_ATPC );
    wifi11_process( );
    Delay_ms( 10000 );
    wifi11_send_command( &wifi11, WIFI11_CMD_ATPT );
    wifi11_process( );
    Delay_ms( 1000 );
    wifi11_send_command( &wifi11, WIFI11_CMD_ATPK );
    wifi11_process( );
    Delay_ms( 1000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; );
}

// ------------------------------------------------------------------------ END
