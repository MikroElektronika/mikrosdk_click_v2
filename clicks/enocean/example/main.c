/*!
 * \file 
 * \brief Enocean Click example
 * 
 * # Description
 * This example reads and processes data from EnOcean clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - enocean_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "enocean.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static enocean_t enocean;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

uint8_t rx_buffer[ 512 ] = {0};
uint8_t data_buffer[ 512 ] = {0};

enocean_packet_t  response;
uint16_t  response_size_cnt;
uint8_t  rsp_check;

uint8_t batton;
uint8_t flag;
// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void log_example( )
{
    if ( flag == 1 )
    {
        flag = 0;

        switch ( batton )
        {
            case 0xd :
            {
                log_printf( &logger, "* Button is released *\r\n" );

            break;
            }
            case 0x50 :
            {
                log_printf( &logger, "* Button 1 is pressed *\r\n" );
            break;
            }
            case 0x70 :
            {
                log_printf( &logger, "* Button 2 is pressed *\r\n" );
            break;
            }
            case 0x10 :
            {
                log_printf( &logger, "* Button 3 is pressed *\r\n" );
            break;
            }
            case 0x30 :
            {
                log_printf( &logger, "* Button 4 is pressed *\r\n" );
            break;
            }
            case 0x17 :
            {
                log_printf( &logger, "* Buttons 2 and 3 are pressed *\r\n" );
            break;
            }
            case 0x35 :
            {
                log_printf( &logger, "* Buttons 1 and 4 are pressed *\r\n" );
            break;
            }
            default :
            {
            break;
            }
        }
    }
}

static void enocean_process ( void )
{
    int16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = enocean_generic_read( &enocean, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
              if ( uart_rx_buffer[ 0 ] == 0x55 )
                {
                    flag = 1;

                    batton = uart_rx_buffer[ 7 ];
                }
      
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
    enocean_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    enocean_cfg_setup( &cfg );
    ENOCEAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean_init( &enocean, &cfg );

    Delay_ms( 500 );
    enocean_aux( &enocean, &rx_buffer[0], ENOCEAN2_RX_BUFFER_SIZE, &data_buffer[0], ENOCEAN2_RX_BUFFER_SIZE );
}

void application_task ( void )
{
    enocean_process(  );

    log_example( );

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
