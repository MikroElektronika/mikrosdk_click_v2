/*!
 * @file main.c
 * @brief 3DHall8 Click example
 *
 * # Description
 * This application shows capability of 3D Hall 8 Click board. 
 * It configures device and reads sensor data. Sensor is capeable 
 * of reading magnetic flux density from 3 axes and temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of device communication and application log 
 * and configures device.
 *
 * ## Application Task
 * Reads data from the device and logs it in span of 500ms.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c3dhall8.h"

static c3dhall8_t c3dhall8;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall8_cfg_t c3dhall8_cfg;  /**< Click config object. */
    uint8_t rx_data;

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    c3dhall8_cfg_setup( &c3dhall8_cfg );
    C3DHALL8_MAP_MIKROBUS( c3dhall8_cfg, MIKROBUS_1 );
    err_t init_flag = c3dhall8_init( &c3dhall8, &c3dhall8_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger," > Setting configuration...\r\n" );
    c3dhall8_default_cfg ( &c3dhall8 ); 

    log_info( &logger, " Application Task " );
    log_printf( &logger, "**************************************\r\n" );
    Delay_ms( 1000 );
}

void application_task ( void ) 
{
    c3dhall8_data_t sens_data;
    c3dhall8_read_sensor_data( &c3dhall8, &sens_data );
    
    log_printf( &logger, "> X[mT]: %.2f\r\n> Y[mT]: %.2f\r\n> Z[mT]: %.2f \r\n> Temperature[C]: %.2f\r\n", 
                sens_data.x_axis, sens_data.y_axis, sens_data.z_axis, sens_data.temperature );
    float magnetic_match = c3dhall8_get_xyz_magnetic_matching( &c3dhall8, sens_data );
    log_printf( &logger, "> XYZ magnetic matching: %.2f\r\n", magnetic_match );
    log_printf( &logger, "**************************************\r\n" );

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
