
---
# 2x4 RGB Click

> 2x4 RGB Click is a compact add-on board for dynamic and colorful lighting control. This board features an array of 2x4 RGB LEDs (WL-ICLED 1312121320437) from Würth Elektronik, featuring individual control of each red, green, and blue component via an integrated IC and pulse width modulation (PWM) technology. The board also includes an LSF0102 voltage translator, ensuring seamless operation with both 3.3V and 5V logic systems, and supports MIKROE’s innovative Click Snap feature for flexible installation options. With its precise color control and flexible design, 2x4 RGB Click is ideal for applications such as ambient lighting, displays, and visual indicators in various consumer electronics and industrial environments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/2x4rgb_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/2x4-rgb-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the 2x4 RGB Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 2x4 RGB Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of 2x4 RGB Click board by cycling through
a set of colors, gradually increasing the brightness of each LED in a sequence,
and then decreasing the brightness before moving on to the next color in the array.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.2x4RGB

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
