/*!
 * \file 
 * \brief Gyro4 Click example
 * 
 * # Description
 * This application is a two-axis MEMS gyroscope for optical image stabilization.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI device
 * 
 * ## Application Task  
 * Checks for data ready interrupt, gets axes and temperature data and logs those values
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gyro4.h"

// ------------------------------------------------------------------ VARIABLES

static gyro4_t gyro4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro4_cfg_t cfg;
    uint8_t initialize_flag;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gyro4_cfg_setup( &cfg );
    GYRO4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gyro4_init( &gyro4, &cfg );

    Delay_ms( 500 );
    initialize_flag = gyro4_initialize( &gyro4 );
    if ( initialize_flag == 1 )
    {
        log_printf( &logger, "> App init fail \r\n" );
    }
    else if ( initialize_flag == 0 )
    {
        log_printf( &logger, "> App init done \r\n" );
    }
}

void application_task ( )
{
    uint8_t int_flag;
    float x_axis;
    float y_axis;
    float die_temperature;
    char degrees_celsius[ 4 ] = { ' ', 176, 'C', 0x00 };
    char degrees_per_second[ 5 ] = { ' ', 176, '/', 's', 0x00 };

    int_flag = gyro4_int_get( &gyro4 );
    while ( int_flag == 1 )
    {
        int_flag = gyro4_int_get( &gyro4 );
    }
    
    gyro4_get_temperature( &gyro4, &die_temperature );
    gyro4_get_axes( &gyro4, &x_axis, &y_axis );

    log_printf( &logger, "\r\n" );
    log_printf( &logger, "> Die temperature : %.2f %c \r\n", die_temperature, degrees_celsius );
    log_printf( &logger, "> X axis : %.2f %c \r\n", x_axis, degrees_per_second );
    log_printf( &logger, "> Y axis : %.2f %c \r\n", y_axis, degrees_per_second );

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
