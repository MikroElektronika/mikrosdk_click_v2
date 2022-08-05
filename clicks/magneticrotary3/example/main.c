/*!
 * @file main.c
 * @brief MagneticRotary3 Click example
 *
 * # Description
 * This example demonstrates the use of Magnetic Rotary 3 click board by reading and displaying
 * the magnet's angular position in degrees.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the magnet's angular position in degrees every 100ms and displays the results on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magneticrotary3.h"

static magneticrotary3_t magneticrotary3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary3_cfg_t magneticrotary3_cfg;  /**< Click config object. */

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
    magneticrotary3_cfg_setup( &magneticrotary3_cfg );
    MAGNETICROTARY3_MAP_MIKROBUS( magneticrotary3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneticrotary3_init( &magneticrotary3, &magneticrotary3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float angle;
    if ( MAGNETICROTARY3_OK == magneticrotary3_get_angle ( &magneticrotary3, &angle ) )
    {
        log_printf( &logger, " Angle: %.1f degrees\r\n\n", angle );
        Delay_ms ( 100 );
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
