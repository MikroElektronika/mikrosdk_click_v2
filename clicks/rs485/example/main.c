/*!
 * \file 
 * \brief Rs485 Click example
 * 
 * # Description
 * This example reads and processes data from RS485 clicks.
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
 * - rs485_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs485.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 1000
#define PROCESS_PARSER_BUFFER_SIZE 1000

#define TEXT_TO_SEND  "MikroE\r\n"

// ------------------------------------------------------------------ VARIABLES

//#define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITER

static rs485_t rs485;
static log_t logger;

static char current_rsp_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 
// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rs485_process ( void )
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
        rsp_size = rs485_generic_read( &rs485, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs485_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rs485_cfg_setup( &cfg );
    RS485_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs485_init( &rs485, &cfg );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER 
    rs485_process( );
#endif 

#ifdef DEMO_APP_TRANSMITER     
    rs485_process( );
    
    if ( send_data_cnt == 5 )
    {
        rs485_send_command( &rs485, TEXT_TO_SEND );
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
