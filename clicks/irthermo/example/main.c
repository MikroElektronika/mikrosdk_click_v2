/*!
 * \file 
 * \brief IrThermo Click example
 * 
 * # Description
 * This application collects data from the sensor, and logs the results.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes IrThermo 3V3 Driver.
 * 
 * ## Application Task  
 * Reading Ambient Temperature and displaying the value periodically.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irthermo.h"

// ------------------------------------------------------------------ VARIABLES

static irthermo_t irthermo;
static log_t logger;

static float measured_temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    irthermo_cfg_t cfg;

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    irthermo_cfg_setup( &cfg );
    IRTHERMO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irthermo_init( &irthermo, &cfg );
}

void application_task ( void )
{
    measured_temperature = irthrm3v3_get_t_ambient( &irthermo );
    log_printf( &logger, "Ambient Temperature: %.2f\r\n", measured_temperature );
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
