/*!
 * @file main.c
 * @brief Color 20 Click example
 *
 * # Description
 * This example demonstrates the use of the Color 20 Click board by reading
 * and displaying the ambient light levels in the red, green, blue, and infrared (IR) spectrum.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Color 20 Click driver, then applies the default configuration.
 *
 * ## Application Task
 * Reads and displays the red, green, blue (in lux), and IR raw values every 200 ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "color20.h"

static color20_t color20;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color20_cfg_t color20_cfg;  /**< Click config object. */

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
    color20_cfg_setup( &color20_cfg );
    COLOR20_MAP_MIKROBUS( color20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color20_init( &color20, &color20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR20_ERROR == color20_default_cfg ( &color20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float red = 0;
    float green = 0;
    float blue = 0;
    uint16_t ir_data = 0;
    if ( COLOR20_OK == color20_get_data ( &color20, &red, &green, &blue, &ir_data ) )
    {
        log_printf ( &logger, " Red: %.1f lux\r\n", red );
        log_printf ( &logger, " Green: %.1f lux\r\n", green );
        log_printf ( &logger, " Blue: %.1f lux\r\n", blue );
        log_printf ( &logger, " IR Data: %u\r\n\n", ir_data );
        Delay_ms ( 200 );
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
