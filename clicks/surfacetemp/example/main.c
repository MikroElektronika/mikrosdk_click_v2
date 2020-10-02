/*!
 * \file 
 * \brief SurfaceTemp Click example
 * 
 * # Description
 * This application demo measures temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver, click board and sets thresholds.
 * 
 * ## Application Task  
 * Reads temperature value and value log on the USBUART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "surfacetemp.h"

// ------------------------------------------------------------------ VARIABLES

static surfacetemp_t surfacetemp;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    surfacetemp_cfg_t cfg;

    uint8_t status;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    surfacetemp_cfg_setup( &cfg );
    SURFACETEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    surfacetemp_init( &surfacetemp, &cfg );

    status = surfacetemp_setup( &surfacetemp );

    surfacetemp_set_high_threshold( &surfacetemp, 40.00 );
    surfacetemp_set_low_threshold( &surfacetemp, 10.00 );
    surfacetemp_set_critical_threshold( &surfacetemp, 70.00 );
    surfacetemp_set_hysteresis( &surfacetemp, 0 );

    if ( status == 0 )
    {
        log_printf( &logger, "--- INIT DONE --- \r\n" );
    }
    else
    {
        log_printf( &logger, "--- INIT ERROR --- \r\n" );
        for( ; ; );
    }
}

void application_task ( void )
{
    float temperature;

    temperature = surfacetemp_get_temperature( &surfacetemp );
    log_printf( &logger, "> Temperature : %.2f \r\n", temperature );
    Delay_ms( 1500 );
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
