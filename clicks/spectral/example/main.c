/*!
 * \file 
 * \brief Spectral Click example
 * 
 * # Description
 * This example reads and processes data from Spectral clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, reset module, and send ( AT, GAIN and MODE ) command.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - spectral_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "spectral.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

#define SINGL_CMD_DATA    "ATDATA"
#define SINGL_CMD_AT      "AT"
#define SINGL_CMD_GAIN    "ATGAIN=2"
#define SINGL_CMD_MODE    "ATTCSMD=2"

// ------------------------------------------------------------------ VARIABLES

static spectral_t spectral;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
uint16_t read_data[ 6 ] ;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void spectral_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt = 5;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = spectral_uart_read( &spectral, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
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
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            Delay_ms( 100 );
        }
    }
}

void parser_application ( )
{
    spectral_get_data( &current_parser_buf[ 0 ], &read_data[ 0 ] );
    spectral_process( );
    
    log_printf( &logger, "\r\n-->     X value: %d \r\n", read_data[ 0 ] );    
    log_printf( &logger, "-->     Y value: %d \r\n", read_data[ 1 ] );  
    log_printf( &logger, "-->     Z value: %d \r\n", read_data[ 2 ] ); 
    log_printf( &logger, "-->     NIR value: %d \r\n", read_data[ 3 ] );
    log_printf( &logger, "-->     D value: %d \r\n", read_data[ 4 ] );
    log_printf( &logger, "-->     C value: %d \r\n", read_data[ 5 ] );

    log_printf( &logger, "________________________\r\n " );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    spectral_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---->  Spectral Click Init  <----" );

    //  Click initialization.

    spectral_cfg_setup( &cfg );
    SPECTRAL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spectral_init( &spectral, &cfg );

    spectral_module_reset( &spectral );
    Delay_ms( 500 );

    // Settings 

    spectral_send_command( &spectral, SINGL_CMD_AT );
    spectral_process( );
    spectral_send_command( &spectral, SINGL_CMD_GAIN );
    spectral_process( );
    spectral_send_command( &spectral, SINGL_CMD_MODE );
    spectral_process( );
    Delay_ms( 500 );
}

void application_task ( void )
{
    spectral_send_command( &spectral, SINGL_CMD_DATA );
    spectral_process( );
 
    parser_application(  );   
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
