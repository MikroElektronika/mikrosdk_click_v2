
---
# Rotary RGB Click

> [Rotary RGB Click](https://www.mikroe.com/?pid_product=MIKROE-6067) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6067&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : GPIO type

# Software Support

## Example Description

> This library contains the API for the Rotary RGB Click driver 
> to control LEDs states and a rotary encoder position readings.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RotaryRGB

### Example Key Functions

- `rotaryrgb_cfg_setup` Config Object Initialization function.
```c
void rotaryrgb_cfg_setup ( rotaryrgb_cfg_t *cfg );
```

- `rotaryrgb_init` Initialization function.
```c
err_t rotaryrgb_init ( rotaryrgb_t *ctx, rotaryrgb_cfg_t *cfg );
```

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

### Note

> Make sure the logic delays are defined for your system in the rotaryrgb_delays.h file.

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
