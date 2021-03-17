/*!
 * \file 
 * \brief Altitude4 Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the Altitude 4 click module. The
 * click has a sensor that measures: altitude, pressure and temperature. No additional equipment
 * or special configuration is required in order for this demo to work.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function initializes the sensor data object through the read_sensor(...) function and
 * then prints altitude, pressure and temperature values in the UART console. It does so every
 * second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "altitude4.h"

// ------------------------------------------------------------------ VARIABLES

static altitude4_t altitude4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    altitude4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    altitude4_cfg_setup( &cfg );
    ALTITUDE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    altitude4_init( &altitude4, &cfg );
    Delay_ms( 500 );
}

void application_task ( void )
{
    altitude4_sensor_t sensor_data;
    
    altitude4_read_sensor( &altitude4, &sensor_data );
    
    log_printf( &logger, " * Altitude: %.2f m\r\n", sensor_data.altitude );
    log_printf( &logger, " * Pressure: %.2f mBar\r\n", sensor_data.pressure );
    log_printf( &logger, " * Temperature: %.2f C\r\n", sensor_data.temperature );
    log_printf( &logger, " -------------------------\r\n" );

    Delay_1sec( );
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
