/*!
 * \file 
 * \brief Altitude2 Click example
 * 
 * # Description
 * This demo demonstrates the use of Altitude 2 Click to measure temperature, altitude and pressure.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver and performs the device reset,
 * after which the calibration coefficients be read.
 * Determines the ratio value for temperature and pressure measurements.
 * Calibration coefficients are necessary to read after the device reset
 * 
 * ## Application Task  
 * Gets temperature data in celsius value and pressure data in mbar value.
 * Gets the calculated altitude value in meters which depends on the temperature and pressure measurements.
 * Logs results on USBUART and repeats operation every 300 ms.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "altitude2.h"

// ------------------------------------------------------------------ VARIABLES

static altitude2_t altitude2;
static log_t logger;
float temperature;
float pressure;
float altitude;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    altitude2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    altitude2_cfg_setup( &cfg );
    ALTITUDE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    altitude2_init( &altitude2, &cfg );
    Delay_ms( 500 );
    altitude2_reset( &altitude2 );
    // Delay_ms( 500 );
    
    altitude2_set_ratio ( &altitude2, ALTITUDE2_RATIO_2048, ALTITUDE2_RATIO_2048 );
    log_printf( &logger, "Altitude 2 is initialized\r\n" );
    Delay_ms( 200 );
}

void application_task ( void )
{
    altitude2_read_data( &altitude2, &temperature, &pressure, &altitude );

    log_printf( &logger, "Temperature is: %.2f Celsius\r\n", temperature );
    log_printf( &logger, "Pressure is: %.2f mbar\r\n", pressure );
    log_printf( &logger, "Altitude is: %.2f m\r\n", altitude );

    Delay_ms( 300 );
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
