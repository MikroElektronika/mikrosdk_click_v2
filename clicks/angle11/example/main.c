/*!
 * @file main.c
 * @brief Angle 11 Click example
 *
 * # Description
 * This example demonstrates the use of Angle 11 Click board by reading and displaying
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
#include "angle11.h"

static angle11_t angle11;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle11_cfg_t angle11_cfg;  /**< Click config object. */

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
    angle11_cfg_setup( &angle11_cfg );
    ANGLE11_MAP_MIKROBUS( angle11_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == angle11_init( &angle11, &angle11_cfg ) )
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
    if ( ANGLE11_OK == angle11_read_angle ( &angle11, &angle ) )
    {
        log_printf ( &logger, " Angle: %.1f deg\r\n", angle );
        if ( ANGLE11_OK == angle11_read_field_strength ( &angle11, &field_str ) )
        {
            log_printf ( &logger, " Field strength: %u Gauss\r\n", field_str );
        }
        if ( ANGLE11_OK == angle11_read_temperature ( &angle11, &int_temp ) )
        {
            log_printf ( &logger, " Internal temperature: %.2f degC\r\n\n", int_temp );
        }
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
