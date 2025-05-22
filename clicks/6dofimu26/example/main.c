/*!
 * @file main.c
 * @brief 6DOF IMU 26 Click example
 *
 * # Description
 * This example demonstrates the use of the 6DOF IMU 26 Click board, which provides 
 * 3-axis accelerometer and 3-axis gyroscope measurements, as well as temperature data. 
 * The example initializes the device and continuously logs sensor readings.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and configures the 6DOF IMU 26 Click board. Sets up SPI 
 * communication and applies the default configuration.
 *
 * ## Application Task
 * Continuously reads and logs acceleration (g), gyroscope (dps), and temperature (degC) 
 * values from the sensor.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c6dofimu26.h"

static c6dofimu26_t c6dofimu26;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu26_cfg_t c6dofimu26_cfg;  /**< Click config object. */

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
    c6dofimu26_cfg_setup( &c6dofimu26_cfg );
    C6DOFIMU26_MAP_MIKROBUS( c6dofimu26_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c6dofimu26_init( &c6dofimu26, &c6dofimu26_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C6DOFIMU26_ERROR == c6dofimu26_default_cfg ( &c6dofimu26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    c6dofimu26_data_t meas_data;
    if ( C6DOFIMU26_OK == c6dofimu26_get_data ( &c6dofimu26, &meas_data ) )
    {
        log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
        log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
        log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
        log_printf( &logger, " Gyro X: %.1f dps\r\n", meas_data.gyro.x );
        log_printf( &logger, " Gyro Y: %.1f dps\r\n", meas_data.gyro.y );
        log_printf( &logger, " Gyro Z: %.1f dps\r\n", meas_data.gyro.z );
        log_printf( &logger, " Temperature: %.2f degC\r\n\n", meas_data.temperature );
        Delay_ms ( 100 );
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
