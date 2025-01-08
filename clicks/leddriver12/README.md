
---
# LED Driver 12 Click

> [LED Driver 12 Click](https://www.mikroe.com/?pid_product=MIKROE-4977) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4977&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of LED Driver 12 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver12

### Example Key Functions

- `leddriver12_cfg_setup` Config Object Initialization function.
```c
void leddriver12_cfg_setup ( leddriver12_cfg_t *cfg );
```

- `leddriver12_init` Initialization function.
```c
err_t leddriver12_init ( leddriver12_t *ctx, leddriver12_cfg_t *cfg );
```

- `leddriver12_default_cfg` Click Default Configuration function.
```c
err_t leddriver12_default_cfg ( leddriver12_t *ctx );
```

- `leddriver12_set_led_config` This function sets the specified LED config.
```c
err_t leddriver12_set_led_config ( leddriver12_t *ctx, uint8_t led_number, uint8_t led_cfg );
```

- `leddriver12_set_led_port_config` This function sets the specified LED port config.
```c
err_t leddriver12_set_led_port_config ( leddriver12_t *ctx, uint8_t led_port_number, uint8_t led_cfg );
```

- `leddriver12_set_blink_period_pwm_0` This function sets the blink period of PWM 0 function.
```c
err_t leddriver12_set_blink_period_pwm_0 ( leddriver12_t *ctx, float blink_period );
```

### Application Init

> Initializes the driver and performs the Click default configuration which turns OFF
the LEDs 0 to 7, configures LEDs 8 to 11 for PWM0, and LEDs 12 to 15 for PWM1 settings.
PWM0 is set at half duty cycle with a one-second blinking period, while PWM1 is configured
for a quarter of duty cycle with a half-second blinking period.

```c
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
```

### Application Task

> Toggles the LEDs 0-7 every 2 seconds and displays their state on the USB UART.

```c
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
