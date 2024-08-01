/*!
 * @file main.c
 * @brief Button 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of Button 2 click board by toggling the button
 * LED and switch state on button press.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Toggles the button LED and switch state on button press and displays the state
 * on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "button2.h"

static button2_t button2;   /**< Button 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    button2_cfg_t button2_cfg;  /**< Click config object. */

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
    button2_cfg_setup( &button2_cfg );
    BUTTON2_MAP_MIKROBUS( button2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == button2_init( &button2, &button2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf ( &logger, " Press button to change switch state\r\n\n" );
    log_printf ( &logger, " SWITCH OFF\r\n\n" );
}

void application_task ( void ) 
{
    static uint8_t switch_state = BUTTON2_SWITCH_OFF;
    
    if ( BUTTON2_BUTTON_PRESSED == button2_get_int_pin ( &button2 ) )
    {
        button2_toggle_led ( &button2 );
        switch_state ^= BUTTON2_SWITCH_ON;
        if ( BUTTON2_SWITCH_ON == switch_state )
        {
            log_printf ( &logger, " SWITCH ON\r\n\n" );
        }
        else
        {
            log_printf ( &logger, " SWITCH OFF\r\n\n" );
        }
        Delay_ms ( 1000 );
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
