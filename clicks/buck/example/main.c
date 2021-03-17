/*!
 * \file 
 * \brief BUCK Click example
 * 
 * # Description
 * The demo application displays frequency change and voltage 
 * regulation using a BUCK click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Buck Click board.
 * Checks if it has reached the set output voltage and sets 
 * a different frequency to the LT3976 chip every 5 sec.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck.h"

// ------------------------------------------------------------------ VARIABLES

static buck_t buck;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck_cfg_setup( &cfg );
    BUCK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck_init( &buck, &cfg );
    Delay_ms( 100 );

    buck_device_reset( &buck );
    buck_default_cfg( &buck );
}

void application_task ( void )
{
    //  Task implementation.
    if ( buck_get_power_good( &buck ) == 1 )
    {
        log_info( &logger, "----  Power good output voltage!  ----" );
    }
    Delay_ms( 1000 );

    log_info( &logger, "----  Switching frequency 400kHz!  ----" );
    buck_switch_frequency( &buck, BUCK_FREQ_400KHz );
    Delay_ms( 5000 );

    log_info( &logger, "----  Switching frequency 800kHz!  ----" );
    buck_switch_frequency( &buck, BUCK_FREQ_800KHz );
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
