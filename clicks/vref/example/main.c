/*!
 * @file main.c
 * @brief VREF Click example
 *
 * # Description
 * This example demonstrates the use of the VREF Click board by enabling and disabling
 * its 2.5V reference output periodically. The application toggles the output every
 * 3 seconds and logs the current state via UART.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and configures the VREF Click driver.
 *
 * ## Application Task
 * Alternately enables and disables the voltage reference output with a 3-second delay,
 * displaying the output state on the UART terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "vref.h"

static vref_t vref;     /**< VREF Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vref_cfg_t vref_cfg;  /**< Click config object. */

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
    vref_cfg_setup( &vref_cfg );
    VREF_MAP_MIKROBUS( vref_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == vref_init( &vref, &vref_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " VREF Output: Enabled\r\n" );
    vref_enable_output ( &vref );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " VREF Output: Disabled\r\n\n" );
    vref_disable_output ( &vref );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
