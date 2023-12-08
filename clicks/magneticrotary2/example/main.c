/*!
 * @file main.c
 * @brief MagneticRotary2 Click example
 *
 * # Description
 * This example demonstrates the use of Magnetic Rotary 2 click board by reading and displaying
 * the magnet's angular position in degrees.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads the magnet's angular position in degrees every 100ms and displays the results on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magneticrotary2.h"

static magneticrotary2_t magneticrotary2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary2_cfg_t magneticrotary2_cfg;  /**< Click config object. */

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
    magneticrotary2_cfg_setup( &magneticrotary2_cfg );
    MAGNETICROTARY2_MAP_MIKROBUS( magneticrotary2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneticrotary2_init( &magneticrotary2, &magneticrotary2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY2_ERROR == magneticrotary2_default_cfg ( &magneticrotary2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float angle = 0;
    
    if ( MAGNETICROTARY2_OK == magneticrotary2_get_angle ( &magneticrotary2, &angle ) )
    {
        log_printf( &logger, " Angle: %.2f degrees\r\n\n", angle );
        Delay_ms ( 100 );
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
