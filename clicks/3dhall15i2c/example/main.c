/*!
 * @file main.c
 * @brief 3D Hall 15 I2C Click example
 *
 * # Description
 * This example demonstrates the use of 3D Hall 15 I2C Click board by reading the magnetic
 * flux density from 3 axes, and the angle and magnitude between X and Y axes  
 * as well as the sensor internal temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads data from the sensor approximately every 100ms and displays the measurement
 * values on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c3dhall15i2c.h"

static c3dhall15i2c_t c3dhall15i2c;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall15i2c_cfg_t c3dhall15i2c_cfg;  /**< Click config object. */

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
    c3dhall15i2c_cfg_setup( &c3dhall15i2c_cfg );
    C3DHALL15I2C_MAP_MIKROBUS( c3dhall15i2c_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c3dhall15i2c_init( &c3dhall15i2c, &c3dhall15i2c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL15I2C_ERROR == c3dhall15i2c_default_cfg ( &c3dhall15i2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    c3dhall15i2c_data_t sensor_data;
    if ( C3DHALL15I2C_OK == c3dhall15i2c_read_data ( &c3dhall15i2c, &sensor_data ) )
    {
        log_printf( &logger, " X-axis: %.2f mT\r\n", sensor_data.x );
        log_printf( &logger, " Y-axis: %.2f mT\r\n", sensor_data.y );
        log_printf( &logger, " Z-axis: %.2f mT\r\n", sensor_data.z );
        log_printf( &logger, " Angle: %.1f deg\r\n", sensor_data.angle );
        log_printf( &logger, " Magnitude: %.1f\r\n", sensor_data.magnitude );
        log_printf( &logger, " Temperature: %.1f degC\r\n\n", sensor_data.temperature );
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
