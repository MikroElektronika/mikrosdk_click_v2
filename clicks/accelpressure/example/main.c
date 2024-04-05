/*!
 * @file main.c
 * @brief AccelPressure Click example
 *
 * # Description
 * This library contains API for the AccelPressure Click driver.
 * The library initializes and defines the I2C drivers to 
 * write and read data from registers, as well as the default configuration 
 * for reading the accelerator, pressure, and temperature data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the AccelPressure Click board.
 * Measures and displays acceleration data for the X-axis, Y-axis, and Z-axis [mg],
 * pressure [mBar], and temperature [degree Celsius] data.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accelpressure.h"

static accelpressure_t accelpressure;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accelpressure_cfg_t accelpressure_cfg;  /**< Click config object. */

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
    accelpressure_cfg_setup( &accelpressure_cfg );
    ACCELPRESSURE_MAP_MIKROBUS( accelpressure_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == accelpressure_init( &accelpressure, &accelpressure_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCELPRESSURE_ERROR == accelpressure_default_cfg ( &accelpressure ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "_________________\r\n" );
}

void application_task ( void ) 
{
    accelpressure_axes_t acc_axis;
    float pressure = 0, temperature = 0;
    if ( ACCELPRESSURE_OK == accelpressure_get_axes_data( &accelpressure, &acc_axis ) )
    {
        log_printf( &logger, " Accel X: %.2f mg\r\n", acc_axis.x );
        log_printf( &logger, " Accel Y: %.2f mg\r\n", acc_axis.y );
        log_printf( &logger, " Accel Z: %.2f mg\r\n", acc_axis.z );
    }
    log_printf( &logger, "_________________\r\n" );
    Delay_ms ( 100 );

    if ( ACCELPRESSURE_OK == accelpressure_get_pressure( &accelpressure, &pressure ) )
    {
        log_printf( &logger, " Pressure: %.2f mbar\r\n", pressure );
    }
    Delay_ms ( 100 );

    if ( ACCELPRESSURE_OK == accelpressure_get_temperature( &accelpressure, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f mbar\r\n", temperature );
    }
    log_printf( &logger, "_________________\r\n" );
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
