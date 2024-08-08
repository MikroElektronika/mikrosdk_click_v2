/*!
 * @file main.c
 * @brief Button 3 Click example
 *
 * # Description
 * This example demonstrates the use of Button 3 click board by toggling a button
 * LED and its switch state on a button press.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Toggles a button LED and its switch state on a button press and displays the state
 * on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "button3.h"

static button3_t button3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    button3_cfg_t button3_cfg;  /**< Click config object. */

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
    button3_cfg_setup( &button3_cfg );
    BUTTON3_MAP_MIKROBUS( button3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == button3_init( &button3, &button3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUTTON3_ERROR == button3_default_cfg ( &button3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf ( &logger, " Press button to change switch state\r\n\n" );
    log_printf ( &logger, " RED SWITCH OFF\r\n\n" );
    log_printf ( &logger, " GREEN SWITCH OFF\r\n\n" );
    log_printf ( &logger, " BLUE SWITCH OFF\r\n\n" );
}

void application_task ( void ) 
{
    static uint8_t red_switch_state = BUTTON3_SWITCH_OFF;
    static uint8_t green_switch_state = BUTTON3_SWITCH_OFF;
    static uint8_t blue_switch_state = BUTTON3_SWITCH_OFF;
    uint8_t switch_state = BUTTON3_SWITCH_OFF;

    if ( BUTTON3_PIN_STATE_LOW == button3_get_int_pin ( &button3 ) )
    {
        if ( ( BUTTON3_OK == button3_get_red_button ( &button3, &switch_state ) ) && 
             ( BUTTON3_BUTTON_PRESSED == switch_state ) )
        {
            button3_toggle_red_led ( &button3 );
            red_switch_state ^= BUTTON3_SWITCH_ON;
            if ( BUTTON3_SWITCH_ON == red_switch_state )
            {
                log_printf ( &logger, " RED SWITCH ON\r\n\n" );
            }
            else
            {
                log_printf ( &logger, " RED SWITCH OFF\r\n\n" );
            }
        }
        if ( ( BUTTON3_OK == button3_get_green_button ( &button3, &switch_state ) ) && 
             ( BUTTON3_BUTTON_PRESSED == switch_state ) )
        {
            button3_toggle_green_led ( &button3 );
            green_switch_state ^= BUTTON3_SWITCH_ON;
            if ( BUTTON3_SWITCH_ON == green_switch_state )
            {
                log_printf ( &logger, " GREEN SWITCH ON\r\n\n" );
            }
            else
            {
                log_printf ( &logger, " GREEN SWITCH OFF\r\n\n" );
            }
        }
        if ( ( BUTTON3_OK == button3_get_blue_button ( &button3, &switch_state ) ) && 
             ( BUTTON3_BUTTON_PRESSED == switch_state ) )
        {
            button3_toggle_blue_led ( &button3 );
            blue_switch_state ^= BUTTON3_SWITCH_ON;
            if ( BUTTON3_SWITCH_ON == blue_switch_state )
            {
                log_printf ( &logger, " BLUE SWITCH ON\r\n\n" );
            }
            else
            {
                log_printf ( &logger, " BLUE SWITCH OFF\r\n\n" );
            }
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
