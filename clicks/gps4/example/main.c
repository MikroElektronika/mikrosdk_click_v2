/*!
 * \file 
 * \brief Gps4 Click example
 * 
 * # Description
 * This example reads and processes data from GPS4 clicks.
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
 * - gps4_process ( ) - The general process of collecting data the module sends.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gps4.h"
#include "string.h"

#define PROCESS_COUNTER 15
#define PROCESS_RX_BUFFER_SIZE 600
#define PROCESS_PARSER_BUFFER_SIZE 600

// ------------------------------------------------------------------ VARIABLES

static gps4_t gps4;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void gps4_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = gps4_generic_read( &gps4, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
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

static void parser_application ( char *rsp )
{
    char element_buf[ 200 ] = { 0 };
    
    log_printf( &logger, "\r\n-----------------------\r\n" ); 
    gps4_generic_parser( rsp, GPS4_NEMA_GPGGA, GPS4_GPGGA_LATITUDE, element_buf );
    if ( strlen( element_buf ) > 0 )
    {
        log_printf( &logger, "Latitude:  %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
        gps4_generic_parser( rsp, GPS4_NEMA_GPGGA, GPS4_GPGGA_LONGITUDE, element_buf );
        log_printf( &logger, "Longitude:  %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
        memset( element_buf, 0, sizeof( element_buf ) );
        gps4_generic_parser( rsp, GPS4_NEMA_GPGGA, GPS4_GPGGA_ALTITUDE, element_buf );
        log_printf( &logger, "Altitude: %s m", element_buf );  
    }
    else
    {
        log_printf( &logger, "Waiting for the position fix..." );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gps4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gps4_cfg_setup( &cfg );
    GPS4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gps4_init( &gps4, &cfg );

    gps4_module_wakeup( &gps4 );
    Delay_ms( 5000 );
}

void application_task ( void )
{
    gps4_process(  );
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
