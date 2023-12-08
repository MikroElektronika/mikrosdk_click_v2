/*!
 * @file main.c
 * @brief Smart DOF 3 Click example
 *
 * # Description
 * This library contains API for Smart DOF 3 Click driver.
 * The library initializes and defines the I2C and SPI bus drivers to 
 * write and read data from registers, as well as the default 
 * configuration for reading accelerator and gyroscope data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or SPI module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Smart DOF 3 Click board™.
 * Measures and displays acceleration and gyroscope data for X-axis, Y-axis, and Z-axis.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartdof3.h"

static smartdof3_t smartdof3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartdof3_cfg_t smartdof3_cfg;  /**< Click config object. */

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
    smartdof3_cfg_setup( &smartdof3_cfg );
    SMARTDOF3_MAP_MIKROBUS( smartdof3_cfg, MIKROBUS_1 );
    err_t init_flag = smartdof3_init( &smartdof3, &smartdof3_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTDOF3_ERROR == smartdof3_default_cfg ( &smartdof3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    static smartdof3_axis_t acc_axis, gyro_axis;
    if ( ( SMARTDOF3_OK == smartdof3_get_acc_axis( &smartdof3, &acc_axis ) ) &&
         ( SMARTDOF3_OK == smartdof3_get_gyro_axis( &smartdof3, &gyro_axis ) ) )
    {
        log_printf( &logger, " Accel X: %.2f mg | Gyro X: %.2f dps\r\n", acc_axis.x, gyro_axis.x );
        log_printf( &logger, " Accel Y: %.2f mg | Gyro Y: %.2f dps\r\n", acc_axis.y, gyro_axis.y );
        log_printf( &logger, " Accel Z: %.2f mg | Gyro Z: %.2f dps\r\n", acc_axis.z, gyro_axis.z );
        log_printf( &logger, "--------------------------------------\r\n" );
    }
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
