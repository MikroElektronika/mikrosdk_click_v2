/*!
 * @file main.c
 * @brief 3D Hall 14 Click example
 *
 * # Description
 * This example demonstrates the use of 3D Hall 14 Click board by reading
 * the magnetic field strength from 3 axes and the sensor internal temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads data from the sensor and displays them on the USB UART every 200ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c3dhall14.h"

static c3dhall14_t c3dhall14;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall14_cfg_t c3dhall14_cfg;  /**< Click config object. */

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
    c3dhall14_cfg_setup( &c3dhall14_cfg );
    C3DHALL14_MAP_MIKROBUS( c3dhall14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c3dhall14_init( &c3dhall14, &c3dhall14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL14_ERROR == c3dhall14_default_cfg ( &c3dhall14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float x_axis = 0;
    float y_axis = 0;
    float z_axis = 0;
    float temperature = 0;
    if ( C3DHALL14_OK == c3dhall14_get_magnetic_flux ( &c3dhall14, &x_axis, &y_axis, &z_axis ) )
    {
        log_printf( &logger, " X-axis: %.1f uT\r\n", x_axis );
        log_printf( &logger, " Y-axis: %.1f uT\r\n", y_axis );
        log_printf( &logger, " Z-axis: %.1f uT\r\n", z_axis );
    }
    if ( C3DHALL14_OK == c3dhall14_get_temperature ( &c3dhall14, &temperature ) )
    {
        log_printf( &logger, " Internal temperature: %.2f C\r\n\n", temperature );
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
