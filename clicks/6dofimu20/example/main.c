/*!
 * @file main.c
 * @brief 6DOF IMU 20 Click example
 *
 * # Description
 * This library contains API for 6DOF IMU 20 Click driver. 
 * The library initializes and defines the I2C and SPI bus drivers to 
 * write and read data from registers, as well as the default 
 * configuration for reading gyroscope and accelerator data, and temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver after that resets the device and 
 * performs default configuration and reads the device id.
 *
 * ## Application Task
 * This example demonstrates the use of the 6DOF IMU 20 Click board by 
 * measuring and displaying acceleration and gyroscope data for X-axis, 
 * Y-axis, and Z-axis as well as temperature in degrees Celsius.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "c6dofimu20.h"

static c6dofimu20_t c6dofimu20;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu20_cfg_t c6dofimu20_cfg;  /**< Click config object. */

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
    c6dofimu20_cfg_setup( &c6dofimu20_cfg );
    C6DOFIMU20_MAP_MIKROBUS( c6dofimu20_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu20_init( &c6dofimu20, &c6dofimu20_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    uint8_t chip_id;
    
    c6dofimu20_get_id( &c6dofimu20, &chip_id );
    if ( C6DOFIMU20_CHIP_ID != chip_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( C6DOFIMU20_ERROR == c6dofimu20_default_cfg ( &c6dofimu20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    c6dofimu20_data_t accel_data;
    c6dofimu20_data_t gyro_data;
    uint16_t data_rdy;
    float temperature;
    c6dofimu20_get_reg( &c6dofimu20, C6DOFIMU20_REG_STATUS, &data_rdy );
    if ( C6DOFIMU20_STATUS_DRDY_ACC_FLAG & data_rdy )
    {
        c6dofimu20_get_acc_data( &c6dofimu20, &accel_data );
        log_printf( &logger, " Accel: X: %d, Y: %d, Z: %d \r\n", accel_data.data_x, accel_data.data_y, accel_data.data_z ); 
    }
    if ( C6DOFIMU20_STATUS_DRDY_GYR_FLAG & data_rdy )
    {
        c6dofimu20_get_gyr_data( &c6dofimu20, &gyro_data );
        log_printf( &logger, " Gyro: X: %d, Y: %d, Z: %d \r\n", gyro_data.data_x, gyro_data.data_y, gyro_data.data_z ); 
    }
    if ( C6DOFIMU20_STATUS_DRDY_TEMP_FLAG & data_rdy )
    {
        c6dofimu20_get_temperature( &c6dofimu20, &temperature );
        log_printf( &logger, " Temperature: %.2f degC \r\n", temperature );
    }
    log_printf( &logger, " - - - - - - - - - - - - - - - - - - - - - - - - \r\n" ); 
    Delay_ms( 500 );
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
