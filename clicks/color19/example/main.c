/*!
 * @file main.c
 * @brief Color 19 Click example
 *
 * # Description
 * This example demonstrates the use of Color 19 Click by reading and displaying
 * the color measurement from RGBW channels and the light intensity level in lux.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Waits for a data ready interrupt then reads the color measurement from 
 * RGBW channels and the light intensity level in lux and displays the results
 * on the USB UART every 200ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "color19.h"

static color19_t color19;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color19_cfg_t color19_cfg;  /**< Click config object. */

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
    color19_cfg_setup( &color19_cfg );
    COLOR19_MAP_MIKROBUS( color19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color19_init( &color19, &color19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR19_ERROR == color19_default_cfg ( &color19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    color19_data_t color_data;

    // Wait for a data ready interrupt
    while ( color19_get_int_pin ( &color19 ) );

    if ( COLOR19_OK == color19_read_data ( &color19, &color_data ) )
    {
        log_printf ( &logger, "RED: %lu\r\n", color_data.red );
        log_printf ( &logger, "GREEN: %lu\r\n", color_data.green );
        log_printf ( &logger, "BLUE: %lu\r\n", color_data.blue );
        log_printf ( &logger, "WHITE: %lu\r\n", color_data.white );
        log_printf ( &logger, "LUX: %lu\r\n\n", color_data.lux );
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
