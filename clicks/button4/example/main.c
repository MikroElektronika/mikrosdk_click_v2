/*!
 * @file main.c
 * @brief Button 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Button 4 Click board by initializing
 * the device and detecting the button state changes. It logs whether the button
 * is pressed (active) or released (reset).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Button 4 Click driver.
 *
 * ## Application Task
 * Monitors the button state and logs whether the button is active (pressed) or 
 * reset (released) when a state change is detected.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "button4.h"

static button4_t button4;   /**< Button 4 Click driver object. */
static log_t logger;        /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    button4_cfg_t button4_cfg;  /**< Click config object. */

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
    button4_cfg_setup( &button4_cfg );
    BUTTON4_MAP_MIKROBUS( button4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == button4_init( &button4, &button4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t button_state_old = BUTTON4_BUTTON_RESET;
    uint8_t button_state = button4_get_out_pin ( &button4 );
    if ( button_state_old != button_state )
    {
        button_state_old = button_state;
        if ( BUTTON4_BUTTON_ACTIVE == button_state )
        {
            log_printf ( &logger, " BUTTON ACTIVE\r\n\n" );
        }
        else
        {
            log_printf ( &logger, " BUTTON RESET\r\n\n" );
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
