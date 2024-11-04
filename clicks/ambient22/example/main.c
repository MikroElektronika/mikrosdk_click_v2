/*!
 * @file main.c
 * @brief Ambient 22 Click example
 *
 * # Description
 * This example demonstrates the use of Ambient 22 Click board by measuring
 * the ambient light level in lux.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Waits for the data ready interrupt, then reads the ambient light level
 * in lux and displays the results on the USB UART. By default, the data
 * ready interrupt triggers every 800ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient22.h"

static ambient22_t ambient22;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient22_cfg_t ambient22_cfg;  /**< Click config object. */

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
    ambient22_cfg_setup( &ambient22_cfg );
    AMBIENT22_MAP_MIKROBUS( ambient22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient22_init( &ambient22, &ambient22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT22_ERROR == ambient22_default_cfg ( &ambient22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float lux;
    // Wait for a data ready interrupt
    while ( ambient22_get_int_pin ( &ambient22 ) );
    
    if ( AMBIENT22_OK == ambient22_read_lux ( &ambient22, &lux ) )
    {
        log_printf( &logger, " Ambient light: %.2f lux\r\n\n", lux );
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
