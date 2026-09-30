
---
# 4D - display Click

> [4D - display Click](https://www.mikroe.com/?pid_product=MIKROE-3044) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3044&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of 4D - display Click with a ViSi-Genie display.
> The Start switch enables a simulated speed sweep from 0 to 300 and back to 0,
> shown on the slider, gauge, digits, and speed indicators.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.4Ddisplay

### Example Key Functions

- `c4ddisplay_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void c4ddisplay_cfg_setup ( c4ddisplay_cfg_t *cfg );
```

- `c4ddisplay_init` This function initializes the UART, reset pin, and protocol state.
```c
err_t c4ddisplay_init ( c4ddisplay_t *ctx, c4ddisplay_cfg_t *cfg );
```

- `c4ddisplay_default_cfg` This function resets the display and confirms communication by setting maximum brightness.
```c
err_t c4ddisplay_default_cfg ( c4ddisplay_t *ctx );
```

- `c4ddisplay_write_object` This function writes a 16-bit value to a display object and waits for acknowledgment.
```c
err_t c4ddisplay_write_object ( c4ddisplay_t *ctx, uint8_t object, uint8_t index, uint16_t value );
```

- `c4ddisplay_read_object` This function requests an object value and validates the matching object report.
```c
err_t c4ddisplay_read_object ( c4ddisplay_t *ctx, uint8_t object, uint8_t index, uint16_t *value );
```

- `c4ddisplay_read_event` This function returns the oldest queued touch event or reads a new event from the UART.
```c
err_t c4ddisplay_read_event ( c4ddisplay_t *ctx, c4ddisplay_event_t *event );
```

### Application Init

> Initializes the logger, maps the Click pins, and opens the display UART at 115200 baud.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    c4ddisplay_cfg_t c4ddisplay_cfg;    /**< Click config object. */

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

    // The first task call resets the display and configures the demo objects.
    c4ddisplay_cfg_setup( &c4ddisplay_cfg );
    C4DDISPLAY_MAP_MIKROBUS( c4ddisplay_cfg, MIKROBUS_POSITION_4DDISPLAY );
    if ( C4DDISPLAY_OK != c4ddisplay_init( &c4ddisplay, &c4ddisplay_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Resets and configures the display, initializes its objects, and turns on the Ready LED.
> Polls the Start switch and updates the speed display while the switch is enabled.
> Stopping clears the speed indicators. Communication errors restart display initialization.

```c
void application_task ( void )
{
    err_t error_flag;

    if ( app_ready )
    {
        error_flag = c4ddisplay_app_update( &c4ddisplay );
    }
    else
    {
        error_flag = c4ddisplay_app_start( &c4ddisplay );
    }

    if ( C4DDISPLAY_OK != error_flag )
    {
        log_error( &logger, " Display communication: %ld", error_flag );
        app_ready = 0;
        Delay_ms( 1000 );
    }
    Delay_ms( 100 );
}
```

### Note

> Create a Workshop4 ViSi-Genie project for the connected display, using the standard
> serial protocol at 115200 baud, 8 data bits, no parity, and one stop bit (not multidrop).
> Make Form0 the startup form and place these objects on it, keeping the indexes shown:
> - Dipswitch0: two positions, value 0 for Stop and 1 for Start.
> - Slider0 and Coolgauge0: minimum 0 and maximum 300.
> - Leddigits0: four digits and one decimal place; the host sends 3000 to display 300.0.
> - Led0: Start status; Led1: Ready status. Both use 0 for off and 1 for on.
> - Userled0: Fast (speed >= 200); Userled1: Medium (speed >= 100);
>   Userled2: Slow (speed > 0). These indicators also use values 0 and 1.
>
> Set initial values to zero. Leave form and object event handlers empty, including
> OnChanged and OnChanging: no automatic reports or object links are needed, as the
> host polls Dipswitch0 and writes the other objects. Labels and positions may be changed.
> Compile and program the display project with a suitable 4D Systems programming adapter.
> Copy its generated graphics files to a microSD card formatted for the selected display,
> then insert the card before power-up. The Click board does not create or upload the UI.
> Wait for Ready before enabling Start. Use a separate UART for the logger.
> Select a suitable 5 V supply with PWR SEL and connect the display with power removed.

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
