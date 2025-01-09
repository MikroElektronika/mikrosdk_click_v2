
---
# LED Driver 16 Click

> [LED Driver 16 Click](https://www.mikroe.com/?pid_product=MIKROE-5534) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5534&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of LED Driver 16 Click board by performing 3 different types of LED control (LED PWM dimming, LED blinking, and LED curtain).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver16

### Example Key Functions

- `leddriver16_cfg_setup` Config Object Initialization function.
```c
void leddriver16_cfg_setup ( leddriver16_cfg_t *cfg );
```

- `leddriver16_init` Initialization function.
```c
err_t leddriver16_init ( leddriver16_t *ctx, leddriver16_cfg_t *cfg );
```

- `leddriver16_default_cfg` Click Default Configuration function.
```c
err_t leddriver16_default_cfg ( leddriver16_t *ctx );
```

- `leddriver16_set_led_state` This function sets the output state for the specified LEDs.
```c
err_t leddriver16_set_led_state ( leddriver16_t *ctx, uint16_t led_ch_mask, uint8_t state );
```

- `leddriver16_set_led_pwm` This function sets the PWM duty cycle for the specified LEDs.
```c
err_t leddriver16_set_led_pwm ( leddriver16_t *ctx, uint16_t led_ch_mask, uint8_t duty_cycle );
```

- `leddriver16_set_led_iref` This function sets the gain settings for output current for the specified LEDs.
```c
err_t leddriver16_set_led_iref ( leddriver16_t *ctx, uint16_t led_ch_mask, uint8_t iref );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
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
```

### Application Task

> Performs 3 different types of LED control examples. Each example repeats 5 times before
switching to another. The name of the currently set example will be displayed on the USB UART accordingly.
- Example 1:
LED PWM dimming - starts with min PWM duty cycle and increases it to max, then decreases
it to min duty cycle in a loop with a 5ms delay on duty change.
- Example 2:
LED blinking - toggles all LEDs state from ON to OFF and vice-versa with a 500ms delay in between.
- Example 3:
LED curtain - turns ON the LEDs one by one from LED0 to LED15 with a 100ms delay on transition
to the next LED.

```c
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
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
