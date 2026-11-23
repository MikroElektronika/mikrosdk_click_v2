
---
# Relay 8 Click

> [Relay 8 Click](https://www.mikroe.com/?pid_product=MIKROE-7132) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7132&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Sep 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Relay 8 Click board by switching
the relay output between the on and the off state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Relay8

### Example Key Functions

- `relay8_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void relay8_cfg_setup ( relay8_cfg_t *cfg );
```

- `relay8_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t relay8_init ( relay8_t *ctx, relay8_cfg_t *cfg );
```

- `relay8_set_relay` This function turns the relay on by generating an active high pulse on the SET pin.
```c
void relay8_set_relay ( relay8_t *ctx );
```

- `relay8_reset_relay` This function turns the relay off by generating an active low pulse on the RST pin.
```c
void relay8_reset_relay ( relay8_t *ctx );
```

- `relay8_toggle_relay` This function turns the relay on and off by generating an active high pulse on the TGL pin.
```c
void relay8_toggle_relay ( relay8_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    relay8_cfg_t relay8_cfg;  /**< Click config object. */

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
    relay8_cfg_setup( &relay8_cfg );
    RELAY8_MAP_MIKROBUS( relay8_cfg, MIKROBUS_POSITION_RELAY8 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == relay8_init( &relay8, &relay8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Turns the relay on and off using the set and the reset control lines, then
turns it on and off again using the toggle control line, and displays the
relay state on the USB UART. Each state is held for 2 seconds.

```c
void application_task ( void ) 
{
    relay8_set_relay ( &relay8 );
    log_printf( &logger, " Relay ON - set\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    relay8_reset_relay ( &relay8 );
    log_printf( &logger, " Relay OFF - reset\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    relay8_toggle_relay ( &relay8 );
    log_printf( &logger, " Relay ON - toggle\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    relay8_toggle_relay ( &relay8 );
    log_printf( &logger, " Relay OFF - toggle\r\n\n" );
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
