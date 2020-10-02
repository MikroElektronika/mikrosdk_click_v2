/*!
 * \file 
 * \brief 3g Click example
 * 
 * # Description
 * This example reads and processes data from 3G clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and power module.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - c3g_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c3g.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

#define AT_COMMAND        "AT" 
#define ATE0_COMMAND      "ATE0" 
#define AT_IFC_COMMAND    "AT+IFC=2,2" 
#define AT_CMGF_COMMAND   "AT+CMGF=1"
#define ATH_COMMAND        "ATH" 

// ------------------------------------------------------------------ VARIABLES

static c3g_t c3g;
static log_t logger;

static char data_buf[ 20 ] = "12.2";
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void c3g_process ( void )
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
        rsp_size = c3g_generic_read( &c3g, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
    log_printf( &logger, "%s\r\n", current_parser_buf );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3g_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3g_cfg_setup( &cfg );
    C3G_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3g_init( &c3g, &cfg );

    c3g_module_power( &c3g, true );

    c3g_process( );

    c3g_send_command( &c3g, AT_COMMAND );
    c3g_send_command( &c3g, AT_COMMAND );
    c3g_send_command( &c3g, AT_COMMAND );
    c3g_send_command( &c3g, ATE0_COMMAND );
    c3g_send_command( &c3g, AT_IFC_COMMAND );
    c3g_send_command( &c3g, AT_CMGF_COMMAND );
}

void application_task ( void )
{
    c3g_process( );
    
    if ( send_data_cnt == 3 )
    {
       c3g_send_command( &c3g, ATH_COMMAND );
       c3g_process( );
       send_data_cnt = 0;
    }
    send_data_cnt++;
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
