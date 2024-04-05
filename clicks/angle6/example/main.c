/*!
 * @file main.c
 * @brief Angle6 Click example
 *
 * # Description
 * This example demonstrates the use of Angle 6 click board by reading and displaying
 * the magnet's angular position in degrees.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which 
 * sets the rotation direction to clockwise.
 *
 * ## Application Task
 * Reads the magnet's angular position in degrees and displays the results on the USB UART
 * approximately every 100ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "angle6.h"

static angle6_t angle6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle6_cfg_t angle6_cfg;  /**< Click config object. */

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
    angle6_cfg_setup( &angle6_cfg );
    ANGLE6_MAP_MIKROBUS( angle6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == angle6_init( &angle6, &angle6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANGLE6_ERROR == angle6_default_cfg ( &angle6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float angle = 0;
    if ( ANGLE6_OK == angle6_read_angle ( &angle6, &angle ) )
    {
        log_printf ( &logger, " Angle: %.2f Deg \r\n\n", angle );
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
