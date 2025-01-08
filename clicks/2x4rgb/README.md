
---
# 2x4 RGB Click

> [2x4 RGB Click](https://www.mikroe.com/?pid_product=MIKROE-6378) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6378&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of 2x4 RGB Click board by cycling through
a set of colors, gradually increasing the brightness of each LED in a sequence,
and then decreasing the brightness before moving on to the next color in the array.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.2x4RGB

### Example Key Functions

- `c2x4rgb_cfg_setup` Config Object Initialization function.
```c
void c2x4rgb_cfg_setup ( c2x4rgb_cfg_t *cfg );
```

- `c2x4rgb_init` Initialization function.
```c
err_t c2x4rgb_init ( c2x4rgb_t *ctx, c2x4rgb_logic_t logic_zero, c2x4rgb_logic_t logic_one, c2x4rgb_cfg_t *cfg );
```

- `c2x4rgb_default_cfg` Click Default Configuration function.
```c
err_t c2x4rgb_default_cfg ( c2x4rgb_t *ctx );
```

- `c2x4rgb_set_leds_intensity` This function sets the brightness and current gain level of all LEDs in the led matrix.
```c
void c2x4rgb_set_leds_intensity ( c2x4rgb_t *ctx, uint8_t brightness, uint8_t gain );
```

- `c2x4rgb_set_led_color` This function sets the color of the selected LED in the LED matrix.
```c
void c2x4rgb_set_led_color ( c2x4rgb_t *ctx, uint8_t led_num, uint32_t rgb );
```

- `c2x4rgb_write_led_matrix` This function writes the LED matrix data from the Click context object.
```c
err_t c2x4rgb_write_led_matrix ( c2x4rgb_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets
the LEDs brightness and current gain to a minimum and the color to black (all LEDs off).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c2x4rgb_cfg_t c2x4rgb_cfg;  /**< Click config object. */

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
    c2x4rgb_cfg_setup( &c2x4rgb_cfg );
    C2X4RGB_MAP_MIKROBUS( c2x4rgb_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == 
         c2x4rgb_init( &c2x4rgb, &c2x4rgb_logic_zero, &c2x4rgb_logic_one, &c2x4rgb_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( C2X4RGB_ERROR == c2x4rgb_default_cfg ( &c2x4rgb ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Cycles through a set of colors, gradually increases the brightness of each LED
in a sequence, and then decreases the brightness before moving on to the next
color in the array. The current color's name and RGB value are logged to the USB UART.

```c
void application_task ( void )
{
    static uint32_t color_num = 0;
    static int8_t led_cnt = 0;
    static int8_t brightness = 0;
    log_printf( &logger, " Color: %s [%.6LX]\r\n\n", color[ color_num ].name, color[ color_num ].rgb );
    Delay_ms ( 100 );
    c2x4rgb_set_leds_intensity ( &c2x4rgb, C2X4RGB_LED_BRIGHTNESS_MIN, C2X4RGB_LED_CURRENT_GAIN_DEFAULT );
    for ( led_cnt = C2X4RGB_LED_7; led_cnt >= C2X4RGB_LED_0; led_cnt-- )
    {
        c2x4rgb_set_led_color ( &c2x4rgb, led_cnt, color[ color_num ].rgb );
        c2x4rgb_write_led_matrix ( &c2x4rgb );
        Delay_ms ( 100 );
    }
    for ( brightness = C2X4RGB_LED_BRIGHTNESS_MIN; brightness < C2X4RGB_LED_BRIGHTNESS_MAX; brightness++ )
    {
        c2x4rgb_set_leds_intensity ( &c2x4rgb, brightness, C2X4RGB_LED_CURRENT_GAIN_DEFAULT );
        c2x4rgb_write_led_matrix ( &c2x4rgb );
        Delay_ms ( 50 );
    }
    for ( brightness = C2X4RGB_LED_BRIGHTNESS_MAX; brightness >= C2X4RGB_LED_BRIGHTNESS_MIN; brightness-- )
    {
        c2x4rgb_set_leds_intensity ( &c2x4rgb, brightness, C2X4RGB_LED_CURRENT_GAIN_DEFAULT );
        c2x4rgb_write_led_matrix ( &c2x4rgb );
        Delay_ms ( 50 );
    }
    if ( ++color_num >= C2X4RGB_NUM_COLORS )
    {
        color_num = 0;
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
