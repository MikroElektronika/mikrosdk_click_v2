/*!
 * @file main.c
 * @brief 3D Hall 4 Click example
 *
 * # Description
 * This example demonstrates the use of 3D Hall 4 click board by reading
 * the magnetic field strength from 3 axes and the sensor internal temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads data from the sensor and displays them on the USB UART once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c3dhall4.h"

static c3dhall4_t c3dhall4;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall4_cfg_t c3dhall4_cfg;  /**< Click config object. */

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
    c3dhall4_cfg_setup( &c3dhall4_cfg );
    C3DHALL4_MAP_MIKROBUS( c3dhall4_cfg, MIKROBUS_1 );
    if ( C3DHALL4_OK != c3dhall4_init( &c3dhall4, &c3dhall4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL4_OK != c3dhall4_default_cfg ( &c3dhall4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    c3dhall4_data_t data_res;
    if ( C3DHALL4_OK == c3dhall4_read_data ( &c3dhall4, &data_res ) )
    {
        log_printf( &logger, " Status: 0x%.2X\r\n", ( uint16_t ) data_res.status );
        log_printf( &logger, " X data: %.1f mT\r\n", data_res.x_data );
        log_printf( &logger, " Y data: %.1f mT\r\n", data_res.y_data );
        log_printf( &logger, " Z data: %.1f mT\r\n", data_res.z_data );
        log_printf( &logger, " Chip temperature: %.2f degC\r\n\n", data_res.chip_temp );
        Delay_ms ( 1000 );
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
