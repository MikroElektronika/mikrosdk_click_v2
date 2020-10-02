/*!
 * \file 
 * \brief 6DofImu7 Click example
 * 
 * # Description
 * This example showcases how to initialize and configure the logger and click modules and read
 * and display temperature measurements and axis data from the gyroscope and accelerometer.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function reads and displays accelerometer, gyroscope and temperature data every second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu7.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu7_t c6dofimu7;
static log_t logger;
static c6dofimu7_axis_t gyro;
static c6dofimu7_axis_t accel;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    c6dofimu7_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c6dofimu7_cfg_setup( &cfg );
    C6DOFIMU7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu7_init( &c6dofimu7, &cfg );
    c6dofimu7_default_cfg( &c6dofimu7 );
}

void application_task ( )
{
    float temperature;

    c6dofimu7_get_gyro_data( &c6dofimu7, &gyro, C6DOFIMU7_GYRO_SENSITIVITY );

    log_printf( &logger, " * Gyro_X: %.5f * \r\n", gyro.x_axis );
    log_printf( &logger, " * Gyro_Y: %.5f * \r\n", gyro.y_axis );
    log_printf( &logger, " * Gyro_Z: %.5f * \r\n", gyro.z_axis );
    log_printf( &logger, " ---------------------------- \r\n" );

    c6dofimu7_get_accel_data( &c6dofimu7, &accel, C6DOFIMU7_ACCEL_SENSITIVITY );

    log_printf( &logger, " * Accel_X: %.5f * \r\n", accel.x_axis );
    log_printf( &logger, " * Accel_Y: %.5f * \r\n", accel.y_axis );
    log_printf( &logger, " * Accel_Z: %.5f * \r\n", accel.z_axis );
    log_printf( &logger, " ---------------------------- \r\n" );

    temperature = c6dofimu7_get_temp_data( &c6dofimu7, C6DOFIMU7_TEMPERATURE_SENSITIVITY,
                                                       C6DOFIMU7_TEMPERATURE_OFFSET );

    log_printf( &logger, " * Temperature: %.5f C * \r\n\r\n", temperature );
    Delay_ms( 1000 );
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
