\mainpage Main Page

---
# LED Driver 16 Click

> LED Driver 16 Click is a compact add-on board that simplifies the control of multiple LEDs. This board features the PCA9745B, an SPI-configurable sixteen-channel constant current LED driver from NXP Semiconductors. Each LED output has an 8-bit resolution (256 steps) fixed-frequency individual PWM controller that operates at 31.25kHz with an adjustable duty cycle from 0 to 100% to allow the LED to be set to a specific brightness value. Powered through a selected mikroBUS™ power rail, either 3.3V or 5V, it provides a maximum output current of 57mA per channel and multiple built-in protection functions that protect the circuit during abnormalities.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver16_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/led-driver-16-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the LED Driver 16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LED Driver 16 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of LED Driver 16 Click board by performing 3 different types of LED control (LED PWM dimming, LED blinking, and LED curtain).

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
