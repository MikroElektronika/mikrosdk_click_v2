/*!
 * @file main.c
 * @brief Smart DOF 2 Click example
 *
 * # Description
 * This library contains API for Smart DOF 2 Click driver.
 * The library initializes and defines the I2C or SPI bus drivers 
 * to write and read data from registers. 
 * The library also includes a function for reading 
 * accelerometer and gyroscope X-axis, Y-axis, and Z-axis data
 * and the temperature in degrees Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or SPI module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Smart DOF 2 Click board™.
 * Measures and displays acceleration and gyroscope data for X-axis, Y-axis, and Z-axis.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartdof2.h"

static smartdof2_t smartdof2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartdof2_cfg_t smartdof2_cfg;  /**< Click config object. */

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
    smartdof2_cfg_setup( &smartdof2_cfg );
    SMARTDOF2_MAP_MIKROBUS( smartdof2_cfg, MIKROBUS_1 );
    err_t init_flag = smartdof2_init( &smartdof2, &smartdof2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTDOF2_ERROR == smartdof2_default_cfg ( &smartdof2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------------------\r\n" );
}

void application_task ( void )
{
    static smartdof2_axis_t acc_axis, gyro_axis;
    if ( SMARTDOF2_OK == smartdof2_get_acc_axis( &smartdof2, &acc_axis ) )
    {
        if ( SMARTDOF2_OK == smartdof2_get_gyro_axis( &smartdof2, &gyro_axis ) )
        {
            log_printf( &logger, " Accel X: %.2f mg | Gyro X: %.2f mdps\r\n", acc_axis.x, gyro_axis.x );
            log_printf( &logger, " Accel Y: %.2f mg | Gyro Y: %.2f mdps\r\n", acc_axis.y, gyro_axis.y );
            log_printf( &logger, " Accel Z: %.2f mg | Gyro Z: %.2f mdps\r\n", acc_axis.z, gyro_axis.z );
            log_printf( &logger, "--------------------------------------\r\n" );
        }
    }
    Delay_ms ( 1000 );
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
