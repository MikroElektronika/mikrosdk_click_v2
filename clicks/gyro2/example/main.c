/*!
 * \file 
 * \brief Gyro2 Click example
 * 
 * # Description
 * This application enables usage of 3 angular movement and velocity sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize the communication interface and configure the click board.  
 * 
 * ## Application Task  
 * Read the x,y,z and temperature data from the click board and display the resoults on the serial port.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gyro2.h"

// ------------------------------------------------------------------ VARIABLES

static gyro2_t gyro2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro2_cfg_t cfg;
    uint8_t temp;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gyro2_cfg_setup( &cfg );
    GYRO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    Delay_ms(3000);

    gyro2_init( &gyro2, &cfg );

    temp = gyro2_default_cfg( &gyro2 );

    if ( temp == 1 )
    {
        log_printf( &logger, "Gyro 2 present\r\n" );
    }
    else if ( temp == 2 )
    {
        log_printf( &logger, "Error\r\n" );
    }
    Delay_ms(100);
}

void application_task ( void )
{
    //  Task implementation.

    int16_t axis_data[ 3 ];
    uint8_t temperature;

    gyro2_get_axisraw( &gyro2, axis_data );
    gyro2_calc_axis( axis_data );

    log_printf( &logger, "x: %d \r\ny: %d \r\nz: %d \r\n", axis_data[ 0 ], axis_data[ 1 ], axis_data[ 2 ] );

    temperature = gyro2_read_temperature( &gyro2 );

    log_printf( &logger, "Temperature: %d C\r\n ++ \r\n", temperature );

    Delay_ms(2000);
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
