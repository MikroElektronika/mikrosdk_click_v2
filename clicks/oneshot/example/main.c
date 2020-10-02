/*!
 * \file 
 * \brief OneShot Click example
 * 
 * # Description
 * This example shows the user how to configure and use the One Shot click. The click has a 
 * monostable monovibrator which cam generate a pulse of width between 1μs and 33.6 seconds. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules. Resistance data,
 * acquired from the AD5241, is displayed at the end of the initialization process. 
 * 
 * ## Application Task  
 * This function sets the digital output of the CS pin to low.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "oneshot.h"

// ------------------------------------------------------------------ VARIABLES

static oneshot_t oneshot;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    oneshot_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    oneshot_cfg_setup( &cfg );
    ONESHOT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oneshot_init( &oneshot, &cfg );
    Delay_100ms( );
    oneshot_default_cfg( &oneshot );

    log_printf( &logger, " * Resistance: %.3f Ohm\r\n", oneshot_get_resistance( &oneshot ) );
    Delay_100ms( );
}

void application_task ( )
{
    oneshot_digital_write_cs( &oneshot, 0 );
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
