/*!
 * @file main.c
 * @brief LEDDriver12 Click example
 *
 * # Description
 * This example demonstrates the use of LED Driver 12 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which turns OFF
 * the LEDs 0 to 7, configures LEDs 8 to 11 for PWM0, and LEDs 12 to 15 for PWM1 settings.
 * PWM0 is set at half duty cycle with a one-second blinking period, while PWM1 is configured
 * for a quarter of duty cycle with a half-second blinking period.
 *
 * ## Application Task
 * Toggles the LEDs 0-7 every 2 seconds and displays their state on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "leddriver12.h"

static leddriver12_t leddriver12;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver12_cfg_t leddriver12_cfg;  /**< Click config object. */

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
    leddriver12_cfg_setup( &leddriver12_cfg );
    LEDDRIVER12_MAP_MIKROBUS( leddriver12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == leddriver12_init( &leddriver12, &leddriver12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER12_ERROR == leddriver12_default_cfg ( &leddriver12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    leddriver12_set_led_port_config ( &leddriver12, LEDDRIVER12_LED0_TO_3, LEDDRIVER12_LED_ON );
    leddriver12_set_led_port_config ( &leddriver12, LEDDRIVER12_LED4_TO_7, LEDDRIVER12_LED_ON );
    log_printf ( &logger, " LEDs 0-7 turns ON \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    leddriver12_set_led_port_config ( &leddriver12, LEDDRIVER12_LED0_TO_3, LEDDRIVER12_LED_OFF );
    leddriver12_set_led_port_config ( &leddriver12, LEDDRIVER12_LED4_TO_7, LEDDRIVER12_LED_OFF );
    log_printf ( &logger, " LEDs 0-7 turns OFF \r\n\n" );
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
