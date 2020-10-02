/*!
 * \file 
 * \brief Power MUX Click example
 * 
 * # Description
 * This Click features power multiplexer that enables transition between two power supplies, 
 * each operating at 2.8V to 5.5V and delivering up to 2A current depending on the package. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Enables GPIO and starts write log.
 * 
 * ## Application Task  
 * This example demonstrates the use of POWER MUX 
 * click board by disabling output tor 2 seconds, then enabling
 * output from channel 1 for 5 seconds then disabling output 
 * for 2 seconds again, and repeating for output from channel 2.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "powermux.h"

// ------------------------------------------------------------------ VARIABLES

static powermux_t powermux;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    powermux_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----");

    //  Click initialization.

    powermux_cfg_setup( &cfg );
    POWERMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    powermux_init( &powermux, &cfg );
}

void application_task ( void )
{
    log_printf( &logger, "No output\r\n" );
    powermux_no_output( &powermux );
    Delay_ms( 2000 );
    log_printf( &logger, "Output from input channel 1\r\n" );
    powermux_output_input_ch_1( &powermux );
    Delay_ms( 5000 );
    log_printf( &logger, "No output\r\n" );
    powermux_no_output( &powermux );
    Delay_ms( 2000 );
    log_printf( &logger, "Output from input channel 2\r\n" );
    powermux_output_input_ch_2( &powermux );
    Delay_ms( 5000 );
    log_printf( &logger, "No output\r\n" );
    powermux_no_output( &powermux );
    Delay_ms( 2000 );
    log_printf( &logger, "auto select output channel\r\n" );
    powermux_auto_sel_input_ch( &powermux );
    Delay_ms( 5000 );
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
