/*!
 * \file 
 * \brief Enocean3 Click example
 * 
 * # Description
 * This example reads and processes data from EnOcean 3 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes UART interface and interrupt.
 * 
 * ## Application Task  
 * Always checks does response packet ready, and if is ready calls a function
  to get response packet and makes a decide what will be performed, depending on the received response.

 * 
 * ## Additional Function
 * - enocean3_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "enocean3.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static enocean3_t enocean3;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

enocean3_packet_t  response;
uint16_t  response_size_cnt;
uint8_t  rsp_check;

uint8_t batton;
uint8_t flag;
// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void enocean3_process ( void )
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
        rsp_size = enocean3_generic_read( &enocean3, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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

void make_response( enocean3_packet_t *rsp, uint16_t *rsp_length_size )
{
    uint16_t rsp_cnt;

    for ( rsp_cnt = 0; rsp_cnt < rsp->data_length; rsp_cnt++ )
    {
        response.data_buff[ rsp_cnt ] = rsp->data_buff[ rsp_cnt ];
    }
    
    response.data_length = rsp->data_length;
    response.opt_length  = rsp->opt_length;
    response.packet_type = rsp->packet_type;
    response_size_cnt      = *rsp_length_size;
}

void log_response( )
{
    uint16_t rsp_cnt;
    char text_resp[ 10 ];

    if ( rsp_check == 1 )
    {
        log_printf( &logger, "OPCODE + PARAM : ", rsp_check );
        rsp_check = 0;
    }

    for ( rsp_cnt = 0; rsp_cnt < response.data_length; rsp_cnt++ )
    {
        log_printf( &logger, "0x%x", response.data_buff[ rsp_cnt ] );
        log_printf( &logger, text_resp, text_resp );
        log_printf( &logger, " " );
    }
    
    if ( response_size_cnt == 1 )
    {
        log_printf( &logger, "" );
        rsp_check = 1;
    }
}

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
            case 0x30 :
            {
                log_printf( &logger, "* Button 3 is pressed *\r\n" );
            break;
            }
            case 0x50 :
            {
                log_printf( &logger, "* Button 5 is pressed *\r\n" );
            break;
            }
            case 0x70 :
            {
                log_printf( &logger, "* Button 7 is pressed *\r\n" );
            break;
            }
            case 0x15 :
            {
                log_printf( &logger, "* Buttons 1 and 5 are pressed *\r\n" );
            break;
            }
            case 0x17 :
            {
                log_printf( &logger, "* Buttons 1 and 7 are pressed *\r\n" );
            break;
            }
            case 0x35 :
            {
                log_printf( &logger, "* Buttons 3 and 5 are pressed *\r\n" );
            break;
            }
            case 0x37 :
            {
                log_printf( &logger, "* Buttons 3 and 7 are pressed *\r\n" );
            break;
            }
            default :
            {
            break;
            }
        }
    }
}   

void check_response( )
{
    uint8_t response_ready;

    response_ready = enocean3_response_ready( &enocean3 );

    if ( response_ready == ENOCEAN3_RESPONSE_READY )
    {
        log_example( );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    enocean3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    enocean3_cfg_setup( &cfg );
    ENOCEAN3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean3_init( &enocean3, &cfg );

    Delay_ms( 500 );

    enocean3_response_handler_set( &enocean3, &make_response );
    rsp_check = 1;
}

void application_task ( void )
{
    enocean3_process( );

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
