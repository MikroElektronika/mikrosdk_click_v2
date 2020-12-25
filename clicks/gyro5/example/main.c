/*!
 * \file 
 * \brief Gyro5 Click example
 * 
 * # Description
 * This application shows temperature and gyroscope axes values
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO pins, I2C and LOG modules.
 * 
 * ## Application Task  
 * Checks data ready INT, gets temperature and axes data and LOGs those values
 * 
 * \author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gyro5.h"

// ------------------------------------------------------------------ VARIABLES

static gyro5_t gyro5;
static log_t logger;

uint8_t data_ready_flag;
float temperature_value;

float x_axis_value;
float y_axis_value;
float z_axis_value;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gyro5_cfg_setup( &cfg );
    GYRO5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gyro5_init( &gyro5, &cfg );
    gyro5_default_cfg ( &gyro5 );
    Delay_ms( 1000 );
    
    log_printf( &logger, "      Gyro 5 Click\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( void )
{
    //  Task implementation.
    
    data_ready_flag = gyro5_int_status( &gyro5, GYRO5_INT_DATA_RDY );
    
    if ( data_ready_flag == GYRO5_STATUS_INT_DATA_RDY )
    {
        gyro5_get_temperature( &gyro5, &temperature_value );
        Delay_ms( 10 );
        gyro5_get_axes(  &gyro5, &x_axis_value, &y_axis_value, &z_axis_value );
        Delay_ms( 10 );
        log_printf( &logger, " Temperature = %.2f C\r\n", temperature_value );
        log_printf( &logger, " X axis = %.2f \r\n", x_axis_value );
        log_printf( &logger, " Y axis = %.2f \r\n", y_axis_value );
        log_printf( &logger, " Z axis = %.2f \r\n", z_axis_value );
        log_printf( &logger, "------------------------\r\n" );
        Delay_ms( 2000 );
    }
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
