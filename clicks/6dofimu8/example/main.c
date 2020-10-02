/*!
 * \file 
 * \brief c6DofImu8 Click example
 * 
 * # Description
 * This app gets three-axis gyroscope value, three-axis accelerometer value and temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device and performs a device software reset and configuration.
 * 
 * ## Application Task  
 * Waits until any new data is entered to the data registers and then reads the accelerometer,
 * gyroscope and temperature data which will be converted and calculated to the properly units every 300ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu8.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu8_t c6dofimu8;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void log_axis ( t_c6dofimu8_axis *log_data, char *ptr_unit )
{
    log_printf( &logger, "* X-axis : %lf %c \r\n", log_data->x, ptr_unit );

    log_printf( &logger, "* Y-axis : %lf %c \r\n", log_data->y, ptr_unit );

    log_printf( &logger, "* Z-axis : %lf %c \r\n", log_data->z, ptr_unit );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu8_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c6dofimu8_cfg_setup( &cfg );
    C6DOFIMU8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu8_init( &c6dofimu8, &cfg );

    Delay_ms( 500 );
    
    c6dofimu8_default_cfg( &c6dofimu8 );

    log_printf( &logger, "** 6DOF IMU 8 is initialized **\r\n" );
    Delay_ms( 300 );
}

void application_task ( void )
{
    uint8_t data_ready;
    int8_t temperature;
    t_c6dofimu8_axis  accel_data;
    t_c6dofimu8_axis  gyro_data;

    char accel_unit[ 3 ] = { ' ', 'g', 0 };
    char gyro_unit[ 5 ] = { ' ', 'd', 'p', 's', 0 };
    char temp_unit[ 4 ] = { ' ', 176, 'C', 0 };

    data_ready = c6dofimu8_get_drdy_status( &c6dofimu8, C6DOFIMU8_TEMP_DRDY_MASK | C6DOFIMU8_G_DRDY_MASK | C6DOFIMU8_XL_DRDY_MASK );
    while ( data_ready == C6DOFIMU8_EVENT_NOT_DETECTED )
    {
        data_ready = c6dofimu8_get_drdy_status( &c6dofimu8, C6DOFIMU8_TEMP_DRDY_MASK | C6DOFIMU8_G_DRDY_MASK | C6DOFIMU8_XL_DRDY_MASK );
    }

    c6dofimu8_get_data( &c6dofimu8, &accel_data, &gyro_data, &temperature );

    log_printf( &logger, "** Accelerometer values : \r\n" );
    log_axis( &accel_data, &accel_unit[ 0 ] );

    log_printf( &logger, "** Gyroscope values : \r\n" );
    log_axis( &gyro_data, &gyro_unit[ 0 ] );

    log_printf( &logger, "** Temperature value : %d %c \r\n", temperature, temp_unit );
    log_printf( &logger, "-------------------------------------------------\r\n" );

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
