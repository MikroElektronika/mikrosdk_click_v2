/*!
 * @file main.c
 * @brief MagneticRotary6 Click example
 *
 * # Description
 * This example demonstrates the use of Magnetic Rotary 6 click board by reading and displaying
 * the magnet's angular position in degrees measured by the bottom and top sensor dies.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which sets the magnet
 * rotation direction for the bottom die to clockwise and for the top die to counter-clockwise.
 *
 * ## Application Task
 * Reads the magnet's angular position from both sensor dies in degrees every 100ms and displays
 * the results on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magneticrotary6.h"

static magneticrotary6_t magneticrotary6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary6_cfg_t magneticrotary6_cfg;  /**< Click config object. */

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
    magneticrotary6_cfg_setup( &magneticrotary6_cfg );
    MAGNETICROTARY6_MAP_MIKROBUS( magneticrotary6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneticrotary6_init( &magneticrotary6, &magneticrotary6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY6_ERROR == magneticrotary6_default_cfg ( &magneticrotary6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float angle;
    if ( MAGNETICROTARY6_OK == magneticrotary6_get_angle ( &magneticrotary6, MAGNETICROTARY6_DIE_BOTTOM, &angle ) )
    {
        log_printf( &logger, " Angle (bottom die): %.1f degrees\r\n", angle );
    }
    if ( MAGNETICROTARY6_OK == magneticrotary6_get_angle ( &magneticrotary6, MAGNETICROTARY6_DIE_TOP, &angle ) )
    {
        log_printf( &logger, " Angle (top die): %.1f degrees\r\n\n", angle );
    }
    Delay_ms ( 100 );
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
