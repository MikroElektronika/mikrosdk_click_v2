/*!
 * \file 
 * \brief Rs4855 Click example
 * 
 * # Description
 * This example reads and processes data from RS485 5 clicks.
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
 * - rs4855_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs4855.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

// #define TRANSIVER
#define RECIEVER

static rs4855_t rs4855;
static log_t logger;

uint8_t message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rs4855_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while( process_cnt != 0 )
    {
        rsp_size = rs4855_generic_read( &rs4855, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            
            log_printf( &logger, "%s", uart_rx_buffer );  

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

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs4855_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rs4855_cfg_setup( &cfg );
    RS4855_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4855_init( &rs4855, &cfg );

    rs4855_set_de_state( &rs4855, RS4855_PIN_STATE_HIGH );
    Delay_ms( 100 );

    #ifdef RECIEVER
        rs4855_set_re_state( &rs4855, RS4855_PIN_STATE_LOW );
        rs4855_set_de_state( &rs4855, RS4855_PIN_STATE_LOW );
    #endif

    #ifdef TRANSIVER
        rs4855_set_re_state( &rs4855, RS4855_PIN_STATE_HIGH );
        rs4855_set_de_state( &rs4855, RS4855_PIN_STATE_HIGH );
    #endif
}

void application_task ( void )
{
    #ifdef TRANSIVER
    
    rs4855_send_byte_by_byte( &rs4855, message );
        
    Delay_ms( 2000 );
    
    #endif
     
    #ifdef RECIEVER
    
    rs4855_process(  );
    log_printf( &logger, "\r\n" );
     
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
