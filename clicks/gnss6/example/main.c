/*!
 * \file 
 * \brief Gnss6 Click example
 * 
 * # Description
 * This example reads and processes data from GNSS 6 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - gnss6_process ( ) - The general process of collecting presponce that sends a module.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gnss6.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

static gnss6_t gnss6;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void gnss6_process ( void )
{
    uint16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = gnss6_generic_read( &gnss6, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            
            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_100ms( );
        }
    }
}

void parser_application ( char *rsp )
{
    char element_buf[ 200 ] = { 0 };
    
    log_printf( &logger, "\r\n-----------------------\r\n", element_buf ); 
    gnss6_generic_parser( rsp, GNSS6_NEMA_GPGGA, GNSS6_GPGGA_LATITUDE, element_buf );
    log_printf( &logger, "Latitude:  %s \r\n", element_buf );    
    gnss6_generic_parser( rsp, GNSS6_NEMA_GPGGA, GNSS6_GPGGA_LONGITUDE, element_buf );
    log_printf( &logger, "Longitude:  %s \r\n", element_buf );  
    gnss6_generic_parser( rsp, GNSS6_NEMA_GPGGA, GNSS6_GPGGA_ALTITUDE, element_buf );
    log_printf( &logger, "Alitude: %s \r\n", element_buf );  
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gnss6_cfg_t cfg;

    //  Logger initialization.
    
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gnss6_cfg_setup( &cfg );
    GNSS6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gnss6_init( &gnss6, &cfg );
    
    gnss6_module_wakeup( &gnss6 );
    Delay_ms( 500 );
}

void application_task ( void )
{
    gnss6_process(  );
    parser_application( current_parser_buf );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
