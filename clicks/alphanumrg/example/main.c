/*!
 * \file 
 * \brief AlphaNumRG Click example
 * 
 * # Description
 * This example showcases the initialization and configuration of the logger and click modules
 * and shows how to display characters and numbers on both LED segments of the click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function sets the time interval at which the symbols are displayed on the LED 
 * segments and shows a few characters and numbers.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "alphanumrg.h"

// ------------------------------------------------------------------ VARIABLES

static alphanumrg_t alphanumrg;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    alphanumrg_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    alphanumrg_cfg_setup( &cfg );
    ALPHANUMRG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    alphanumrg_init( &alphanumrg, &cfg );
    Delay_100ms( );
}

void application_task ( )
{
    alphanumrg_set_display_interval( &alphanumrg, 1000 );

    aplhanumrg_write_character( &alphanumrg, 'M', 'E' );
    aplhanumrg_write_character( &alphanumrg, '@', '?' );

    alphanumrg_write_number( &alphanumrg, 0,  1 );
    alphanumrg_write_number( &alphanumrg, 1,  2 );
    alphanumrg_write_number( &alphanumrg, 2,  3 );
    alphanumrg_write_number( &alphanumrg, 3,  4 );
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
