/*!
 * \file 
 * \brief PAC1921 Click example
 * 
 * # Description
 * This example showcases how to measure voltage, current or power (load) data using the 
 * PAC1921 chip. Required modules are first initialized and after used to read and
 * display the measured data. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules. Default settings
 * are written to three control/configuration registers in the default_cfg(...) function.
 * 
 * ## Application Task  
 * This function reads and displays voltage, current or power data from the chip, depending
 * on the specified measurement mode and sample count. It does so every half a second. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pac1921.h"

// ------------------------------------------------------------------ VARIABLES

static pac1921_t pac1921;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    pac1921_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pac1921_cfg_setup( &cfg );
    PAC1921_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pac1921_init( &pac1921, &cfg );
    Delay_ms( 100 );
    pac1921_default_cfg( &pac1921 );
    Delay_ms( 100 );
}

void application_task ( )
{
    float read_data;

    read_data = pac1921_get_measured_data( &pac1921, PAC1921_MEASUREMENT_MODE_V_BUS_FREE_RUN,
                                                     PAC1921_SAMPLE_RATE_512 );

    if ( pac1921.aux.measurement_mode_old == PAC1921_MEASUREMENT_MODE_V_POWER_FREE_RUN )
    {
        log_printf( &logger, " * Power: %.2f W * \r\n", read_data );
    }
    else
    {
        log_printf( &logger, " * Voltage: %.2f mV * \r\n", read_data );
    }

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
