/*!
 * \file 
 * \brief Pressure6 Click example
 * 
 * # Description
 * This app returns the value of pressure on the sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver initialization and powering ON procedure to wake up the sensor and seting up the measurement mode.
 * 
 * ## Application Task  
 * Read Pressure data and Temperature data and logs data to USBUART every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure6.h"

// ------------------------------------------------------------------ VARIABLES

static pressure6_t pressure6;
static log_t logger;
static uint16_t pressure;
static uint8_t  temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pressure6_cfg_setup( &cfg );
    PRESSURE6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure6_init( &pressure6, &cfg );
    pressure6_default_cfg( &pressure6 );
    log_printf( &logger, "--- Start measurement ---" );
}

void application_task ( void )
{
    //  Task implementation.
    
    pressure6_waiting_for_new_data( &pressure6 );
    pressure = pressure6_get_pressure( &pressure6 );
    temperature = pressure6_get_temperature( &pressure6 );

    log_printf( &logger, "Pressure: %d\r\n", pressure);
    log_printf( &logger, "Temperature: %d\r\n", temperature);

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
