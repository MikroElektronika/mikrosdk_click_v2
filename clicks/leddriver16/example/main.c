/*!
 * @file main.c
 * @brief LED Driver 16 Click example
 *
 * # Description
 * This example demonstrates the use of LED Driver 16 click board by performing
 * 3 different types of LED control (LED PWM dimming, LED blinking, and LED curtain).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Performs 3 different types of LED control examples. Each example repeats 5 times before
 * switching to another. The name of the currently set example will be displayed on the USB UART accordingly.
 * - Example 1:
 * LED PWM dimming - starts with min PWM duty cycle and increases it to max, then decreases
 * it to min duty cycle in a loop with a 5ms delay on duty change.
 * - Example 2:
 * LED blinking - toggles all LEDs state from ON to OFF and vice-versa with a 500ms delay in between.
 * - Example 3:
 * LED curtain - turns ON the LEDs one by one from LED0 to LED15 with a 100ms delay on transition
 * to the next LED.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "leddriver16.h"

static leddriver16_t leddriver16;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver16_cfg_t leddriver16_cfg;  /**< Click config object. */

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
    leddriver16_cfg_setup( &leddriver16_cfg );
    LEDDRIVER16_MAP_MIKROBUS( leddriver16_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == leddriver16_init( &leddriver16, &leddriver16_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER16_ERROR == leddriver16_default_cfg ( &leddriver16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t example_repeat_num = 5;
    uint8_t repeat_cnt = 0;
    log_printf( &logger, " LED PWM dimming\r\n\n" );
    leddriver16_set_led_state ( &leddriver16, LEDDRIVER16_LED_CHANNEL_ALL, LEDDRIVER16_LEDOUT_PWM_ALL );
    while ( repeat_cnt < example_repeat_num )
    {
        uint8_t pwm_duty = LEDDRIVER16_PWM_DUTY_MIN;
        while ( pwm_duty < LEDDRIVER16_PWM_DUTY_MAX )
        {
            leddriver16_set_led_pwm ( &leddriver16, LEDDRIVER16_LED_CHANNEL_ALL, pwm_duty );
            Delay_ms ( 5 );
            pwm_duty++;
        }
        while ( pwm_duty > LEDDRIVER16_PWM_DUTY_MIN )
        {
            leddriver16_set_led_pwm ( &leddriver16, LEDDRIVER16_LED_CHANNEL_ALL, pwm_duty );
            Delay_ms ( 5 );
            pwm_duty--;
        }
        Delay_ms ( 100 );
        repeat_cnt++;
    }
    
    log_printf( &logger, " LED blinking\r\n\n" );
    repeat_cnt = 0;
    leddriver16_set_led_state ( &leddriver16, LEDDRIVER16_LED_CHANNEL_ALL, LEDDRIVER16_LEDOUT_OFF );
    while ( repeat_cnt < example_repeat_num )
    {
        leddriver16_set_led_state ( &leddriver16, LEDDRIVER16_LED_CHANNEL_ALL, LEDDRIVER16_LEDOUT_ON );
        Delay_ms ( 500 );
        leddriver16_set_led_state ( &leddriver16, LEDDRIVER16_LED_CHANNEL_ALL, LEDDRIVER16_LEDOUT_OFF );
        Delay_ms ( 500 );
        repeat_cnt++;
    }
    
    log_printf( &logger, " LED curtain\r\n\n" );
    repeat_cnt = 0;
    leddriver16_set_led_state ( &leddriver16, LEDDRIVER16_LED_CHANNEL_ALL, LEDDRIVER16_LEDOUT_OFF );
    while ( repeat_cnt < example_repeat_num )
    {
        uint8_t led_cnt = 0;
        while ( led_cnt < 16 )
        {
            leddriver16_set_led_state ( &leddriver16, LEDDRIVER16_LED_CHANNEL_0 << led_cnt, LEDDRIVER16_LEDOUT_ON );
            Delay_ms ( 100 );
            leddriver16_set_led_state ( &leddriver16, LEDDRIVER16_LED_CHANNEL_0 << led_cnt, LEDDRIVER16_LEDOUT_OFF );
            led_cnt++;
        }
        Delay_ms ( 500 );
        repeat_cnt++;
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
