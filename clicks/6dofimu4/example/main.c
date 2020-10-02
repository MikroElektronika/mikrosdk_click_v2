/*!
 * \file 
 * \brief c6DofImu4 Click example
 * 
 * # Description
 * This application measures gyroscopic, accelerometer, and temperature data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C interface and performs a device reset and configurations.
 * 
 * ## Application Task  
 * Waits until data is ready and then reads the all data registers,
  accelerometer, gyroscope and temperature data, and shows results to the uart terminal every 500ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu4.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu4_t c6dofimu4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c6dofimu4_cfg_setup( &cfg );
    C6DOFIMU4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu4_init( &c6dofimu4, &cfg );
    c6dofimu4_reset( &c6dofimu4 );

    c6dofimu4_default_cfg( &c6dofimu4 );
    Delay_ms( 200 );

    log_printf( &logger, "** 6DOF IMU 4 is initialized **\r\n" );
}

void application_task ( void )
{
    c6dofimu4_axis_t  accel_data;
    c6dofimu4_axis_t  gyro_data;
    uint8_t data_ready;
    int8_t temperature;

    data_ready = c6dofimu4_get_status( &c6dofimu4, C6DOFIMU4_DATA_RDY_INT_MASK );

    while ( data_ready != C6DOFIMU4_DATA_RDY_INT_OCCURED )
    {
        data_ready = c6dofimu4_get_status( &c6dofimu4, C6DOFIMU4_DATA_RDY_INT_MASK );
    }
    
    c6dofimu4_get_data( &c6dofimu4, &accel_data, &gyro_data, &temperature );
    
    log_printf( &logger,"** Accelerometer values :\r\n" );
    log_printf( &logger, "* X-axis : %.2lf g ", accel_data.x );
    log_printf( &logger, "* Y-axis : %.2lf g ", accel_data.y );
    log_printf( &logger, "* Z-axis : %.2lf g ", accel_data.z );
    log_printf( &logger,"\r\n" );
    
    log_printf( &logger,"** Gyroscope values :\r\n" );
    log_printf( &logger, "* X-axis : %.2lf dps ", gyro_data.x );
    log_printf( &logger, "* Y-axis : %.2lf dps ", gyro_data.y );
    log_printf( &logger, "* Z-axis : %.2lf dps ", gyro_data.z );
    log_printf( &logger,"\r\n" );
    
    log_printf( &logger, "** Temperature value : %d C\r\n", temperature );
    log_printf( &logger,"------------------------------------------------- \r\n" );
    
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
