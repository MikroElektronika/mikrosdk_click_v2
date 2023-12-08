/*!
 * @file main.c
 * @brief Angle 10 Click Example.
 *
 * # Description
 * This example demonstrates the use of Angle 10 click board by reading and displaying
 * the magnet's angular position in degrees and analog voltage output.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the magnet's angular position in degrees and analog voltage output 
 * and displays the results on the USB UART approximately every 500ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "angle10.h"

static angle10_t angle10;   /**< Angle 10 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle10_cfg_t angle10_cfg;  /**< Click config object. */

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
    angle10_cfg_setup( &angle10_cfg );
    ANGLE10_MAP_MIKROBUS( angle10_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == angle10_init( &angle10, &angle10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage, angle;
    if ( ANGLE10_OK == angle10_read_voltage ( &angle10, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f V\r\n", voltage );
    }
    if ( ANGLE10_OK == angle10_get_angle ( &angle10, &angle ) )
    {
        log_printf ( &logger, " Angle: %.2f Degrees\r\n\n", angle );
    }
    Delay_ms( 500 );
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
