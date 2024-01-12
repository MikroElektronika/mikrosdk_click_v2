/*!
 * @file main.c
 * @brief 6DOF IMU 16 Click example
 *
 * # Description
 * This example demonstrates the use of 6DOF IMU 16 click board by reading and displaying 
 * the accelerometer and gyroscope data (X, Y, and Z axis).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver performs the click default configuration, 
 * and checks communication by reading device ID.
 *
 * ## Application Task
 * Reading the accelerometer and gyroscope measurements, results are displayed on the USB UART every second.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "c6dofimu16.h"

static c6dofimu16_t c6dofimu16;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu16_cfg_t c6dofimu16_cfg;  /**< Click config object. */

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
    c6dofimu16_cfg_setup( &c6dofimu16_cfg );
    C6DOFIMU16_MAP_MIKROBUS( c6dofimu16_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu16_init( &c6dofimu16, &c6dofimu16_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C6DOFIMU16_ERROR == c6dofimu16_default_cfg ( &c6dofimu16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint8_t dev_id = 0;
    c6dofimu16_reg_read( &c6dofimu16, C6DOFIMU16_REG_WHO_AM_I, &dev_id );
    if ( C6DOFIMU16_DEVICE_ID != dev_id )
    {
        log_error( &logger, " Communication error " );
        for ( ; ; );
    }
    log_printf( &logger, " Device ID: 0x%.2X \r\n", ( uint16_t ) dev_id );

    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    c6dofimu16_axis_t accel_data;
    c6dofimu16_axis_t gyro_data;

    c6dofimu16_get_accel_data( &c6dofimu16, &accel_data );
    c6dofimu16_get_gyro_data( &c6dofimu16, &gyro_data );
    log_printf( &logger, " Accel data | Gyro data \r\n" );
    log_printf( &logger, " X: %.2f g  | %.2f dps \r\n", accel_data.x_data, gyro_data.x_data );
    log_printf( &logger, " Y: %.2f g  | %.2f dps \r\n", accel_data.y_data, gyro_data.y_data );
    log_printf( &logger, " Z: %.2f g  | %.2f dps \r\n", accel_data.z_data, gyro_data.z_data );
    Delay_ms( 1000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
