/*!
 * @file main.c
 * @brief 3DHall10 Click example
 *
 * # Description
 * This example demonstrates the use of 3D Hall 10 click board by reading the magnetic
 * flux density from 3 axes, and the angle and magnitude between X and Y axes  
 * as well as the sensor internal temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the conversion complete interrupt and then reads the new data from the sensor 
 * approximately every 100ms and displays the measurement values on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c3dhall10.h"

static c3dhall10_t c3dhall10;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall10_cfg_t c3dhall10_cfg;  /**< Click config object. */

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
    c3dhall10_cfg_setup( &c3dhall10_cfg );
    C3DHALL10_MAP_MIKROBUS( c3dhall10_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c3dhall10_init( &c3dhall10, &c3dhall10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL10_ERROR == c3dhall10_default_cfg ( &c3dhall10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    while ( c3dhall10_get_alert_pin ( &c3dhall10 ) );
    
    c3dhall10_data_t sensor_data;
    if ( C3DHALL10_OK == c3dhall10_read_data ( &c3dhall10, &sensor_data ) )
    {
        log_printf( &logger, " X-axis: %.1f mT\r\n", sensor_data.x_axis );
        log_printf( &logger, " Y-axis: %.1f mT\r\n", sensor_data.y_axis );
        log_printf( &logger, " Z-axis: %.1f mT\r\n", sensor_data.z_axis );
        log_printf( &logger, " Angle: %.1f Degrees\r\n", sensor_data.angle );
        log_printf( &logger, " Magnitude: %u\r\n", sensor_data.magnitude );
        log_printf( &logger, " Temperature: %.2f Celsius\r\n\n", sensor_data.temperature );
    }
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
