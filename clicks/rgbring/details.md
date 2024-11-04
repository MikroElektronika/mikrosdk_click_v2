
---
# RGB Ring Click

> RGB Ring Click is a compact add-on board designed for dynamic and colorful lighting applications. This board features eight RGB LEDs (WL-ICLED 1312020030000) from Würth Elektronik, incorporating integrated circuits to control color mixing precisely. This board supports individual control of each LED's red, green, and blue components with single-wire communication enabling daisy-chaining. It also features the innovative Click Snap function, allowing the main LED area to be detached for flexible use, and includes a button for interactive functionality.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rgbring_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rgb-ring-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the RGB Ring Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RGB Ring Click driver.

#### Standard key functions :

- `rgbring_cfg_setup` Config Object Initialization function.
```c
void rgbring_cfg_setup ( rgbring_cfg_t *cfg );
```

- `rgbring_init` Initialization function.
```c
err_t rgbring_init ( rgbring_t *ctx, rgbring_logic_t logic_zero, rgbring_logic_t logic_one, rgbring_cfg_t *cfg );
```

- `rgbring_default_cfg` Click Default Configuration function.
```c
err_t rgbring_default_cfg ( rgbring_t *ctx );
```

#### Example key functions :

- `rgbring_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t rgbring_get_int_pin ( rgbring_t *ctx );
```

- `rgbring_set_led_color` This function sets the color of the selected LED in the LED matrix.
```c
void rgbring_set_led_color ( rgbring_t *ctx, uint8_t led_num, uint32_t rgb );
```

- `rgbring_write_led_matrix` This function writes the LED matrix data from the Click context object.
```c
err_t rgbring_write_led_matrix ( rgbring_t *ctx );
```

## Example Description

> This example demonstrates the use of RGB Ring Click board by controling an RGB ring 
by cycling through a set of predefined colors. Each color is displayed by lighting up 
the LEDs in sequence around the ring. After the last LED is lit, the code waits for
a button press before moving on to the next color in the sequence. 
The button press triggers the transition to the next color in the array.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which sets the color to black (all LEDs off).

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rgbring_cfg_t rgbring_cfg;  /**< Click config object. */

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
    rgbring_cfg_setup( &rgbring_cfg );
    RGBRING_MAP_MIKROBUS( rgbring_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == 
         rgbring_init( &rgbring, &rgbring_logic_zero, &rgbring_logic_one, &rgbring_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( RGBRING_ERROR == rgbring_default_cfg ( &rgbring ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Controls an LED ring by cycling through colors and waits for user input to change
the ring's color. The button press is required to move to the next color in the sequence.
The current color's name and RGB value are logged to the USB UART.

```c
void application_task ( void )
{
    static uint32_t color_num = 0;
    static int8_t led_cnt = 0;

    log_printf( &logger, " Color: %s [%.6LX]\r\n", color[ color_num ].name, color[ color_num ].rgb );
    Delay_ms ( 100 );
    for ( led_cnt = RGBRING_LED_7; led_cnt >= RGBRING_LED_0; led_cnt-- )
    {
        rgbring_set_led_color ( &rgbring, led_cnt, color[ color_num ].rgb );
        rgbring_write_led_matrix ( &rgbring );
        Delay_ms ( 100 );
    }
    if ( ++color_num >= RGBRING_NUM_COLORS )
    {
        color_num = 0;
    }

    log_printf ( &logger, " Press button to change ring color\r\n\n" );
    while ( RGBRING_BUTTON_RELESED == rgbring_get_int_pin ( &rgbring ) );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RGBRing

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
