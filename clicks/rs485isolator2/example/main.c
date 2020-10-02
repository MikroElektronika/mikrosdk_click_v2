/*!
 * \file 
 * \brief Rs485Isolator2 Click example
 * 
 * # Description
 * This example reads and processes data from RS485 Isolator 2 clicks.
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
 * - rs485isolator2_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs485isolator2.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

#define TRANSIVER
//#define RECIEVER

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITER

static rs485isolator2_t rs485isolator2;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

const unsigned char message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rs485isolator2_process ( void )
{
    int16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while( process_cnt != 0 )
    {
        rsp_size = rs485isolator2_generic_read( &rs485isolator2, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
    rs485isolator2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rs485isolator2_cfg_setup( &cfg );
    RS485ISOLATOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs485isolator2_init( &rs485isolator2, &cfg );

    Delay_ms( 200 );
}

void application_task ( void )
{
    #ifdef TRANSIVER
    
    rs485isolator2_set_de_pin( &rs485isolator2, RS485ISOLATOR2_ENABLE_DE );

    rs485isolator2_send_bit_by_bit ( &rs485isolator2, message );
    
    log_printf( &logger, " test\r\n" );

    rs485isolator2_set_de_pin( &rs485isolator2, RS485ISOLATOR2_DISABLE_DE );
        
    Delay_ms( 2000 );
    
    #endif
     
    #ifdef RECIEVER
    
    rs485isolator2_set_re_pin( &rs485isolator2, RS485ISOLATOR2_ENABLE_RE );

    rs485isolator2_process(  );
    
    log_printf( &logger, " test\r\n" );

    rs485isolator2_set_re_pin( &rs485isolator2, RS485ISOLATOR2_DISABLE_RE );
     
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
