
---
# Rotary RGB Click

> Rotary RGB Click is a compact add-on board for creating visual effects and precise position indications. This board features 16 individual RGB LEDs (WS2812B-2020) from Worldsemi and a high-quality rotary encoder (EC12D1564402) from ALPS. The WS2812B-2020 offers low driving voltage, high brightness, and excellent consistency, while the rotary encoder provides accurate 15-pulse incremental encoding with push-button functionality.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rotaryrgb_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rotary-rgb-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the Rotary RGB Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Rotary RGB Click driver.

#### Standard key functions :

- `rotaryrgb_cfg_setup` Config Object Initialization function.
```c
void rotaryrgb_cfg_setup ( rotaryrgb_cfg_t *cfg );
```

- `rotaryrgb_init` Initialization function.
```c
err_t rotaryrgb_init ( rotaryrgb_t *ctx, rotaryrgb_cfg_t *cfg );
```

#### Example key functions :

- `rotaryrgb_set_led_pos_color` This function sets the desired color for the selected LED position
```c
err_t rotaryrgb_set_led_pos_color ( rotaryrgb_t *ctx, uint8_t led_pos, uint32_t led_color );
```

- `rotaryrgb_set_all_leds_data` This function, using the GPIO protocol, writes the desired array of 16 elements of data to control all LEDs.
```c
void rotaryrgb_set_all_leds_data ( rotaryrgb_t *ctx, uint32_t *data_in );
```

- `rotaryrgb_get_state_switch` This function return rotary encoder switch signal, states of the SW(INT) pin.
```c
uint8_t rotaryrgb_get_state_switch ( rotaryrgb_t *ctx );
```

## Example Description

> This library contains the API for the Rotary RGB Click driver 
> to control LEDs states and a rotary encoder position readings.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO module and log UART.
> After the driver init, the app turn off all LEDs.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryrgb_cfg_t rotaryrgb_cfg;  /**< Click config object. */

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
    rotaryrgb_cfg_setup( &rotaryrgb_cfg, &rotaryrgb_logic_zero, &rotaryrgb_logic_one );
    ROTARYRGB_MAP_MIKROBUS( rotaryrgb_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == rotaryrgb_init( &rotaryrgb, &rotaryrgb_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    rotaryrgb_set_all_led_color( &rotaryrgb, ROTARYRGB_COLOR_OFF );
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Rotary RGB Click board.
> The demo example shows the functionality of a rotary encoder used to control RGB LEDs.
> The switch controls the application of the colors,
> and the encoder mechanism controls the state of the LEDs.

```c
void application_task ( void ) 
{
    rotaryrgb_set_led_pos_color( &rotaryrgb, led_pos % 17, demo_color_table[ led_color_sel ] );
    rotaryrgb_switch_detection( );
    rotaryrgb_encoder_mechanism( );
}
```

## Note

> Make sure the logic delays are defined for your system in the rotaryrgb_delays.h file.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RotaryRGB

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
