/*!
 * @file main.c
 * @brief 6DOFIMU14 Click example
 *
 * # Description
 * This example demonstrates the use of 6DOF IMU 14 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the click board.
 *
 * ## Application Task
 * Reads accel, gyro, and temperature data and displays the results 
 * on the USB UART approximately every 500ms.
 *
 * @note
 * In the case of I2C, the example doesn't work properly on some of the 8-bit PICs (ex. PIC18F97J94).
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c6dofimu14.h"

static c6dofimu14_t c6dofimu14;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu14_cfg_t c6dofimu14_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    c6dofimu14_cfg_setup( &c6dofimu14_cfg );
    C6DOFIMU14_MAP_MIKROBUS( c6dofimu14_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu14_init( &c6dofimu14, &c6dofimu14_cfg );
    if ( ( init_flag == I2C_MASTER_ERROR ) || ( init_flag == SPI_MASTER_ERROR ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 100 );

    if ( c6dofimu14_default_cfg ( &c6dofimu14 ) != C6DOFIMU14_OK ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature;
    c6dofimu14_axis_t accel;
    c6dofimu14_axis_t gyro;
    
    c6dofimu14_get_data( &c6dofimu14, &accel, &gyro );
    c6dofimu14_get_temperature( &c6dofimu14, &temperature );
        
    log_printf( &logger, " Accel X: %d | Gyro X: %d\r\n", accel.x, gyro.x );
    log_printf( &logger, " Accel Y: %d | Gyro Y: %d\r\n", accel.y, gyro.y );
    log_printf( &logger, " Accel Z: %d | Gyro Z: %d\r\n", accel.z, gyro.z );
    log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
    log_printf( &logger, "----------------------------------\r\n");
        
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
