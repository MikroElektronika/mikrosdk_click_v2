/*!
 * \file 
 * \brief Thermo6 Click example
 * 
 * # Description
 * Demo application shows ambient temperature reading using Thermo 6 click.
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Setting the click in the default configuration to start the measurement.
 * 
 * ## Application Task  
 *  It measures the temperature and logs a message about the current temperature.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo6.h"

// ------------------------------------------------------------------ VARIABLES

static thermo6_t thermo6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    thermo6_cfg_setup( &cfg );
    THERMO6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo6_init( &thermo6, &cfg );

    thermo6_default_cfg( &thermo6 );
    log_info( &logger, "---- Start measurement ----");
    Delay_ms( 1000 );
}

void application_task ( void )
{
    float temperature;

    //  Task implementation.

    temperature = thermo6_get_temperature_data( &thermo6, THERMO6_TEMP_FORMAT_CELSIUS );
    log_printf( &logger, ">> Temperature is %.3f C \r\n", temperature );

    Delay_ms( 1000 );
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
