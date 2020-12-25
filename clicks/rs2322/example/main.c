/*!
 * \file 
 * \brief Rs2322 Click example
 * 
 * # Description
 * This example reads and processes data from RS232 2 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - rs2322_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs2322.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 500

#define TEXT_TO_SEND  "MikroE\r\n"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static rs2322_t rs2322;
static log_t logger;

static char current_rsp_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 
// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rs2322_process ( void )
{
    int16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_rsp_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = rs2322_generic_read( &rs2322, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            
            log_printf( &logger, "%s\r\n", uart_rx_buffer );
            
            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_rsp_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
    log_printf( &logger, "%s\r\n", current_rsp_buf );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs2322_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rs2322_cfg_setup( &cfg );
    RS2322_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs2322_init( &rs2322, &cfg );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs2322_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITER
    rs2322_process( );
    
    if ( send_data_cnt == 5 )
    {
        rs2322_send_command( &rs2322, TEXT_TO_SEND );
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
    }
#endif    
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
