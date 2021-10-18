/*!
 * \file 
 * \brief FiberOpt Click example
 * 
 * # Description
 * This application is an add-on for fiber-optical communication.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes UART driver and makes an initial log.
 * 
 * ## Application Task  
 * Example can either check if new data byte is received in rx buffer (ready for reading),
 * if ready than reads one byte from rx buffer and displays on USART terminal, or transmit message every 2 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fiberopt.h"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static fiberopt_t fiberopt;
static log_t logger;

static char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fiberopt_cfg_t cfg;

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

    fiberopt_cfg_setup( &cfg );
    FIBEROPT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fiberopt_init( &fiberopt, &cfg );

    log_printf( &logger, "Initialized \r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    char tmp;
    
    //  Task implementation.
    
#ifdef DEMO_APP_RECEIVER

       // RECEIVER - UART polling

       tmp =  fiberopt_generic_single_read( &fiberopt );
       log_printf( &logger, "%c" , &tmp );
#endif
#ifdef DEMO_APP_TRANSMITER

       // TRANSMITER - TX each 2 sec
       
       fiberopt_generic_multi_write( &fiberopt, demo_message, 9 );
       Delay_ms( 2000 );
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
