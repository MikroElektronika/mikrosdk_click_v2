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
 * Initializes the driver and sets the driver handler.
 * 
 * ## Application Task  
 * Reads the received data and parses it on the USB UART if the response buffer is ready.
 * 
 * ## Additional Function
 * - enocean_process - The general process of collecting data the module sends.
 * - make_response - Driver handler function which stores data in the response buffer.
 * - log_response - Logs the module response on the USB UART.
 * - log_example - Logs button events on the USB UART.
 * - check_response - Checks if the response is ready and logs button events.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "enocean.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

static enocean_t enocean;
static log_t logger;

enocean_packet_t response;
uint16_t response_size_cnt;
uint8_t rsp_check = 1;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void make_response( enocean_packet_t *rsp, uint16_t *rsp_length_size )
{
    uint16_t rsp_cnt;

    for ( rsp_cnt = 0; rsp_cnt < rsp->data_length; rsp_cnt++ )
    {
        response.data_buff[ rsp_cnt ] = rsp->data_buff[ rsp_cnt ];
    }
    
    response.data_length = rsp->data_length;
    response.opt_length  = rsp->opt_length;
    response.packet_type = rsp->packet_type;
    response_size_cnt    = *rsp_length_size;
}

void log_response( )
{
    uint16_t rsp_cnt;

    if ( rsp_check == 1 )
    {
        log_printf( &logger, "OPCODE + PARAM : ", rsp_check );
        rsp_check = 0;
    }

    for ( rsp_cnt = 0; rsp_cnt < response.data_length; rsp_cnt++ )
    {
        log_printf( &logger, "0x%.2X ", ( uint16_t ) response.data_buff[ rsp_cnt ] );
    }
    
    if ( response_size_cnt == 1 )
    {
        log_printf( &logger, "\r\n" );
        rsp_check = 1;
    }
}

void log_example( )
{
    switch ( response.data_buff[ 1 ] )
    {
        case 0x00:
        {
            log_printf( &logger, "* Button is released *\r\n" );
            break;
        }
        case 0x10 :
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

void check_response( )
{
    uint8_t response_ready;

    response_ready = enocean_response_ready( &enocean );

    if ( response_ready == ENOCEAN_RESPONSE_READY )
    {
        log_example( );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    enocean_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    enocean_cfg_setup( &cfg );
    ENOCEAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean_init( &enocean, &cfg );

    Delay_ms ( 500 );
    
    enocean_response_handler_set( &enocean, &make_response );
}

void application_task ( void )
{
    enocean_uart_isr ( &enocean );
    check_response ( );
    Delay_1ms( );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
