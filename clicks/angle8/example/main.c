/*!
 * @file main.c
 * @brief Angle8 Click example
 *
 * # Description
 * This example demonstrates the use of Angle 8 Click board by reading and displaying
 * the magnet's angular position in degrees.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which 
 * sets the clockwise rotation direction and cycle time to 100ms.
 *
 * ## Application Task
 * Waits for the new data ready flag and then reads the magnet's angular position in degrees
 * and displays the results on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "angle8.h"

static angle8_t angle8;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle8_cfg_t angle8_cfg;  /**< Click config object. */

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
    angle8_cfg_setup( &angle8_cfg );
    ANGLE8_MAP_MIKROBUS( angle8_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == angle8_init( &angle8, &angle8_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANGLE8_ERROR == angle8_default_cfg ( &angle8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( angle8_get_nd_pin ( &angle8 ) )
    {
        float angle = 0;
        if ( ANGLE8_OK == angle8_read_angle ( &angle8, &angle ) )
        {
            log_printf ( &logger, " Angle: %.2f Deg \r\n\n", angle );
        }
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
