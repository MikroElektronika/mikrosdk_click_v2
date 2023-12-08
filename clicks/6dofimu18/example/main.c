/*!
 * @file main.c
 * @brief 6DOF IMU 18 Click example
 *
 * # Description
 * This library contains API for 6DOF IMU 18 Click driver. 
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
 * This example demonstrates the use of the 6DOF IMU 18 Click board by 
 * measuring and displaying acceleration and gyroscope data for X-axis, 
 * Y-axis, and Z-axis as well as temperature in degrees Celsius.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "c6dofimu18.h"

static c6dofimu18_t c6dofimu18;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu18_cfg_t c6dofimu18_cfg;  /**< Click config object. */

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
    c6dofimu18_cfg_setup( &c6dofimu18_cfg );
    C6DOFIMU18_MAP_MIKROBUS( c6dofimu18_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu18_init( &c6dofimu18, &c6dofimu18_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    uint8_t id = 0;
    c6dofimu18_reg_read( &c6dofimu18, C6DOFIMU18_BANK0_SEL, C6DOFIMU18_REG_WHO_AM_I, &id, 1);
    log_printf( &logger, " Device ID : 0x%.2X \r\n", ( uint16_t ) id );
    if ( C6DOFIMU18_WHO_AM_I_VALUE != id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    if ( C6DOFIMU18_OK != c6dofimu18_default_cfg ( &c6dofimu18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( c6dofimu18_get_int1_state( &c6dofimu18) )
    {       
        c6dofimu18_data_t accel_data;
        c6dofimu18_data_t gyro_data;
        float temp_data;
        uint32_t tmst_data;
        
        c6dofimu18_get_data_from_register( &c6dofimu18, &temp_data, &accel_data, &gyro_data, &tmst_data );
        log_printf( &logger, " TEMP: %.2f \r\n", temp_data );
        log_printf( &logger, " GYRO: x:%d y:%d z:%d \r\n", gyro_data.data_x,gyro_data.data_y,gyro_data.data_z );
        log_printf( &logger, " ACCEL: x:%d y:%d z:%d \r\n", accel_data.data_x,accel_data.data_y,accel_data.data_z );
        log_printf( &logger, "========================== \r\n" );
        Delay_ms( 1000 );
    }    
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
