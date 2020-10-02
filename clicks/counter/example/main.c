/*!
 * \file 
 * \brief Counter Click example
 * 
 * # Description
 * Measuring RPM and speed of DC motor shafts
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and chip init
 * 
 * ## Application Task  
 * This application reads data from CNTR.
 * The CNTR is a software configurable 8, 16, 24 or 32-bit up/down counter which
 * counts the up/down pulses resulting from the quadrature clocks applied at the
 * A and B inputs, or alternatively, in non-quadrature mode, pulses applied at
 * the A input.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "counter.h"

// ------------------------------------------------------------------ VARIABLES

static counter_t counter;
static log_t logger;

static uint8_t count;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    counter_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    counter_cfg_setup( &cfg );
    COUNTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    counter_init( &counter, &cfg );

    counter_default_cfg( &counter );
    Delay_ms( 300 );
}

void application_task ( void )
{
    count = counter_read_cntr( &counter );
    log_printf( &logger, " %d\r\n",  count );
    Delay_ms( 500 );
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
