/*!
 * @file main.c
 * @brief 6DOF IMU 28 Click example
 *
 * # Description
 * This example demonstrates the use of 6DOF IMU 28 Click board by reading and displaying 
 * the accelerometer and gyroscope data (X, Y, and Z axis) as well as a temperature measurement
 * in degrees Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Waits for a data ready indication and then reads the accelerometer, gyroscope, and temperature
 * measurements. The results are displayed on the USB UART at 7.5 Hz output data rate.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c6dofimu28.h"

static c6dofimu28_t c6dofimu28;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu28_cfg_t c6dofimu28_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    c6dofimu28_cfg_setup( &c6dofimu28_cfg );
    C6DOFIMU28_MAP_MIKROBUS( c6dofimu28_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu28_init( &c6dofimu28, &c6dofimu28_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C6DOFIMU28_ERROR == c6dofimu28_default_cfg ( &c6dofimu28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    c6dofimu28_data_t meas_data;
    if ( c6dofimu28_get_int1_pin ( &c6dofimu28 ) ) 
    {
        if ( C6DOFIMU28_OK == c6dofimu28_get_data ( &c6dofimu28, &meas_data ) )
        {
            log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
            log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
            log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
            log_printf( &logger, " Gyro X: %.1f dps\r\n", meas_data.gyro.x );
            log_printf( &logger, " Gyro Y: %.1f dps\r\n", meas_data.gyro.y );
            log_printf( &logger, " Gyro Z: %.1f dps\r\n", meas_data.gyro.z );
            log_printf( &logger, " Temperature: %.2f degC\r\n\n", meas_data.temperature );
        }
    }
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
