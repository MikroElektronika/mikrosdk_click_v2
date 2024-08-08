/*!
 * @file main.c
 * @brief 6DOF IMU 23 Click example
 *
 * # Description
 * This library contains API for 6DOF IMU 23 Click driver.
 * The library initializes and defines the SPI bus drivers 
 * to write and read data. The library also includes a function for reading 
 * accelerometer and gyroscope X-axis, Y-axis, and Z-axis data as well as the internal
 * temperature data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of SPI module, log UART and enable the device.
 *
 * ## Application Task
 * This example demonstrates the use of the 6DOF IMU 23 Click board.
 * Measures and displays acceleration and gyroscope data for X-axis, Y-axis, and Z-axis, and
 * the internal temperature data.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c6dofimu23.h"

static c6dofimu23_t c6dofimu23;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu23_cfg_t c6dofimu23_cfg;  /**< Click config object. */

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
    c6dofimu23_cfg_setup( &c6dofimu23_cfg );
    C6DOFIMU23_MAP_MIKROBUS( c6dofimu23_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c6dofimu23_init( &c6dofimu23, &c6dofimu23_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C6DOFIMU23_ERROR == c6dofimu23_default_cfg ( &c6dofimu23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float temperature = 0;
    c6dofimu23_axis_t acc_axis, gyro_axis;
    if ( ( C6DOFIMU23_OK == c6dofimu23_get_accel_data( &c6dofimu23, &acc_axis ) ) &&
         ( C6DOFIMU23_OK == c6dofimu23_get_gyro_data( &c6dofimu23, &gyro_axis ) ) &&
         ( C6DOFIMU23_OK == c6dofimu23_get_temperature( &c6dofimu23, &temperature ) ) )
    {
        log_printf( &logger, " Accel X: %.2f g | Gyro X: %.2f dps\r\n", acc_axis.x, gyro_axis.x );
        log_printf( &logger, " Accel Y: %.2f g | Gyro Y: %.2f dps\r\n", acc_axis.y, gyro_axis.y );
        log_printf( &logger, " Accel Z: %.2f g | Gyro Z: %.2f dps\r\n", acc_axis.z, gyro_axis.z );
        log_printf( &logger, " Internal temperature: %.2f degC\r\n", temperature );
        log_printf( &logger, " ----------------------------------\r\n" );
    }
    Delay_ms ( 100 );
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
