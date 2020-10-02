/*!
 * \file 
 * \brief 420MaR Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the 4-20 mA R click. It is a
 * simple SPI communication module that acts as a receiver in a 4-20 current loop. The click
 * reads current data and converts the analog signal to a digital 12-bit format.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function reads and displays current data every half a second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c420mar.h"

// ------------------------------------------------------------------ VARIABLES

static c420mar_t c420mar;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    c420mar_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c420mar_cfg_setup( &cfg );
    c420MAR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c420mar_init( &c420mar, &cfg );
}

void application_task ( )
{
    float current;

    current = c420mar_read_data( &c420mar );

    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " * Current: %.3f mA * \r\n", current );

    Delay_ms( 500 );
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
