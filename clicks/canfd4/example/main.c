/*!
 * \file 
 * \brief CanFd4 Click example
 * 
 * # Description
 * This example reads and processes data from CAN FD4 clicks.
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
 * - canfd4_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "canfd4.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

#define TRANSIVER
//#define RECIEVER

// ------------------------------------------------------------------ VARIABLES

static canfd4_t canfd4;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static char message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void canfd4_process ( void )
{
    int16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;    //kazi kaci da zabada ako je uint8_t
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = canfd4_generic_read( &canfd4, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
    canfd4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    canfd4_cfg_setup( &cfg );
    CANFD4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd4_init( &canfd4, &cfg );

    canfd4_set_dev_mode ( &canfd4, CANFD4_NORMAL_MODE );
}

void application_task ( void )
{
    #ifdef TRANSIVER
    
    canfd4_send_command( &canfd4, message );
        
    Delay_ms( 2000 );
    
    #endif
     
    #ifdef RECIEVER
    
    canfd4_process(  );
     
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
