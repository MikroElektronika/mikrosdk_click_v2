/*!
 * @file main.c
 * @brief Angle 9 Click example
 *
 * # Description
 * This example demonstrates the use of Angle 9 click board by reading and displaying
 * the magnet's angular position in degrees, field strength in gauss, and the internal
 * sensor temperature in degrees celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the magnet's angular position in degrees, magnetic field strength in gauss,
 * and the internal sensor temperature in degrees celsius and displays the results
 * on the USB UART approximately every 100ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "angle9.h"

static angle9_t angle9;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle9_cfg_t angle9_cfg;  /**< Click config object. */

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
    angle9_cfg_setup( &angle9_cfg );
    ANGLE9_MAP_MIKROBUS( angle9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == angle9_init( &angle9, &angle9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float angle = 0;
    float int_temp = 0;
    uint16_t field_str = 0;
    if ( ANGLE9_OK == angle9_read_angle ( &angle9, &angle ) )
    {
        log_printf ( &logger, " Angle: %.1f deg\r\n", angle );
        if ( ANGLE9_OK == angle9_read_field_strength ( &angle9, &field_str ) )
        {
            log_printf ( &logger, " Field strength: %u Gauss\r\n", field_str );
        }
        if ( ANGLE9_OK == angle9_read_temperature ( &angle9, &int_temp ) )
        {
            log_printf ( &logger, " Internal temperature: %.2f degC\r\n\n", int_temp );
        }
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
