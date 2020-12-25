/*!
 * \file 
 * \brief Pressure9 Click example
 * 
 * # Description
 * The demo application displays the pressure and temperature 
 * measurement using Pressure 9 click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver init, test comunication, software reset, 
 * configuration module for measurement and
 * calls the function to update calibration coefficients 
 * - this function must be called before the measurement starts.
 *
 * ## Application Task
 * Reads Temperature data in [C] and Pressure data in [mBar] and this 
 * data logs to the USB UART every 2 sec.
 *
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure9.h"

// ------------------------------------------------------------------ VARIABLES

static pressure9_t pressure9;
static log_t logger;

static uint8_t tmp;
static float temperature;
static float pressure;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure9_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pressure9_cfg_setup( &cfg );
    PRESSURE9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure9_init( &pressure9, &cfg );

    // Test comunication

    pressure9_generic_read( &pressure9, PRESSURE9_REG_PRODUCT_ID, &tmp, 1 );

    if ( tmp == PRESSURE9_PRODUCT_ID )
    {
        log_printf( &logger, "---- Comunication OK!!! ----\r\n" );
    }
    else
    {
        log_printf( &logger, "---- Comunication ERROR!!! ----\r\n" );
        for ( ; ; );
    }

    pressure9_default_cfg( &pressure9 );
    log_printf( &logger, "---- Start Measurement ----\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    pressure = pressure9_get_pressure_data( &pressure9 );
    log_printf( &logger, "-- Pressure : %.2f mBar\r\n", pressure );

    temperature = pressure9_get_temperature_data( &pressure9 );
    log_printf( &logger, "-- Temperature : %.2f °C\r\n", temperature );

    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 2000 );
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
