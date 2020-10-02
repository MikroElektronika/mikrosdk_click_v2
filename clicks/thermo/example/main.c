/*!
 * \file 
 * \brief Thermo Click example
 * 
 * # Description
 * This application collects data from the sensor, calculates it, and then logs
 * the results.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and star write log.
 * 
 * ## Application Task  
 * Temperature measured by the thermocouple is converter by MAX31855 sensor 
 * and the results are logged. Displayed temperature is in degrees Celsius.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo.h"

// ------------------------------------------------------------------ VARIABLES

static thermo_t thermo;
static log_t logger;

static float temperature;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void display_error_msg ( )
{
    log_printf( &logger, "       ERROR       \r\n" );

    if ( thermo_short_circuited_vcc( &thermo ) )
    {
        log_printf( &logger, "Short-circuted to Vcc\r\n" );
    }
    if ( thermo_short_circuited_gnd( &thermo ) )
    {
        log_printf( &logger, "Short-circuted to GND\r\n" );
    }
    if ( thermo_check_connections( &thermo ) )
    {
        log_printf( &logger, "No Connections\r\n" );
    }

}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo_cfg_t cfg;

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    thermo_cfg_setup( &cfg );
    THERMO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo_init( &thermo, &cfg );

    if ( thermo_check_fault( &thermo ) )
    {
        display_error_msg();
    }
    else
    {
        log_printf( &logger, "Status OK\r\n" );
    }
}

void application_task ( void )
{
    temperature = thermo_get_temperature( &thermo );

    log_printf( &logger, "Temperature : %f\r\n", temperature );

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
