/*!
 * \file 
 * \brief Pressure4 Click example
 * 
 * # Description
 * This app measure barometric pressure.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the click board.
 * 
 * ## Application Task  
 * The preassure and temperature data is read from the sensor 
 * and it is printed to the UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure4.h"

// ------------------------------------------------------------------ VARIABLES

static pressure4_t pressure4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pressure4_cfg_setup( &cfg );
    PRESSURE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure4_init( &pressure4, &cfg );

    pressure4_default_cfg( &pressure4 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    double tmp;
    double temp;

    
    tmp = pressure4_get_temperature( &pressure4 );
    log_printf( &logger, "Temperature : %lf \r\n", tmp );
    Delay_ms( 100 );
    
    temp = pressure4_get_pressure( &pressure4 );
    log_printf( &logger, "Pressure : %lf hPa \r\n", temp );
    log_printf( &logger, "========================\r\n" );

    Delay_ms( 500 );
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
