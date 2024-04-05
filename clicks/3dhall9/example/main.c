/*!
 * @file main.c
 * @brief 3DHall9 Click example
 *
 * # Description
 * This example demonstrates the use of 3D Hall 9 click board by reading the magnetic
 * flux density from 3 axes as well as the angles between axes and the sensor temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and the click board.
 *
 * ## Application Task
 * Reads the new data from the sensor approximately every 300ms and displays 
 * the measurement values on the USB UART.  
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c3dhall9.h"

static c3dhall9_t c3dhall9;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall9_cfg_t c3dhall9_cfg;  /**< Click config object. */

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
    c3dhall9_cfg_setup( &c3dhall9_cfg );
    C3DHALL9_MAP_MIKROBUS( c3dhall9_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c3dhall9_init( &c3dhall9, &c3dhall9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL9_ERROR == c3dhall9_default_cfg ( &c3dhall9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    c3dhall9_data_t sensor_data;
    
    if ( C3DHALL9_OK == c3dhall9_read_data ( &c3dhall9, &sensor_data ) )
    {
        log_printf( &logger, " X-axis: %.1f Gauss\r\n", sensor_data.x_axis );
        log_printf( &logger, " Y-axis: %.1f Gauss\r\n", sensor_data.y_axis );
        log_printf( &logger, " Z-axis: %.1f Gauss\r\n", sensor_data.z_axis );
        log_printf( &logger, " Angle XY: %.1f Degrees\r\n", sensor_data.angle_xy );
        log_printf( &logger, " Angle XZ: %.1f Degrees\r\n", sensor_data.angle_xz );
        log_printf( &logger, " Angle YZ: %.1f Degrees\r\n", sensor_data.angle_yz );
        log_printf( &logger, " Temperature: %.2f Celsius\r\n\n", sensor_data.temperature );
        Delay_ms ( 300 );
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
