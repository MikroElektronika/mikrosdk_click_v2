/*!
 * @file main.c
 * @brief Color 18 Click example
 *
 * # Description
 * This example demonstrates the use of Color 18 Click by reading and displaying
 * the values from all 8 modulator channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Waits for a data ready interrupt then reads data from all 8 modulator channels
 * and displays the results on the USB UART every 200ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "color18.h"

static color18_t color18;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color18_cfg_t color18_cfg;  /**< Click config object. */

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
    color18_cfg_setup( &color18_cfg );
    COLOR18_MAP_MIKROBUS( color18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color18_init( &color18, &color18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR18_ERROR == color18_default_cfg ( &color18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    color18_data_t color_data;

    // Wait for a data ready interrupt
    while ( color18_get_int_pin ( &color18 ) );

    if ( COLOR18_OK == color18_read_data ( &color18, &color_data ) )
    {
        log_printf ( &logger, "X: %u\r\n", color_data.x );
        log_printf ( &logger, "Y: %u\r\n", color_data.y );
        log_printf ( &logger, "Z: %u\r\n", color_data.z );
        log_printf ( &logger, "IR: %u\r\n", color_data.ir );
        log_printf ( &logger, "HgL: %u\r\n", color_data.hgl );
        log_printf ( &logger, "HgH: %u\r\n", color_data.hgh );
        log_printf ( &logger, "Clear: %u\r\n", color_data.clear );
        log_printf ( &logger, "Flicker: %u\r\n\n", color_data.flicker );
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
