/*!
 * \file 
 * \brief Gyro3 Click example
 * 
 * # Description
 * This example shows values of the 3 axis from the gyroscope module.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver, basic device configuration, I2C interface, LOG interface and GPIO pins.
 * 
 * ## Application Task  
 * Checks if new data is available on all three axes, If yes then reads and logs their values.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gyro3.h"

// ------------------------------------------------------------------ VARIABLES

static gyro3_t gyro3;
static log_t logger;

static uint8_t status_register;
static float x_axis;
static float y_axis;
static float z_axis;

static const char degrees_celsius[ 3 ] = { ' ', 'C', 0 };
static const char degrees_per_second[ 7 ] = { ' ', 'd', 'e', 'g', '/', 's', 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gyro3_cfg_setup( &cfg );
    GYRO3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gyro3_init( &gyro3, &cfg );
    gyro3_default_cfg( &gyro3 );
}

void application_task ( void )
{
    //  Task implementation.

    gyro3_get_status( &gyro3, &status_register );

    if ( ( status_register & GYRO3_ZYX_NEW_DATA_MASK ) == GYRO3_ZYX_NEW_DATA_MASK )
    {

        gyro3_get_axes( &gyro3, &x_axis, &y_axis, &z_axis, GYRO3_MEAS_RANGE_2000 );

        log_printf( &logger, "\r\nx_axis : %.2f %s\t", x_axis, degrees_per_second );
        log_printf( &logger, "y_axis : %.2f %s\t", y_axis, degrees_per_second );
        log_printf( &logger, "z_axis : %.2f %s\r\n", z_axis, degrees_per_second );
        
    }

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
