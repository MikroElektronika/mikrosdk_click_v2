
---
# Power MUX Click

> [Power MUX Click](https://www.mikroe.com/?pid_product=MIKROE-4109) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4109&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mikroe Team
- **Date**          : Sep 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This Click features power multiplexer that enables transition between two power supplies, 
> each operating at 2.8V to 5.5V and delivering up to 2A current depending on the package.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerMUX

### Example Key Functions

- `powermux_cfg_setup` Config Object Initialization function.
```c
void powermux_cfg_setup ( powermux_cfg_t *cfg );
```

- `powermux_init` Initialization function.
```c
err_t powermux_init ( powermux_t *ctx, powermux_cfg_t *cfg );
```

- `powermux_default_cfg` Click Default Configuration function.
```c
void powermux_default_cfg ( powermux_t *ctx );
```

- `powermux_int_pin_read` Power MUX pin reading function.
```c
uint8_t powermux_int_pin_read ( powermux_t *ctx );
```

- `powermux_set_mode` Power MUX mode set function.
```c
void powermux_set_mode ( powermux_t *ctx, uint8_t mode );
```

### Application Init

> Enables GPIO and starts write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;
    powermux_cfg_t powermux_cfg;

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
    powermux_cfg_setup( &powermux_cfg );
    POWERMUX_MAP_MIKROBUS( powermux_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == powermux_init( &powermux, &powermux_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    powermux_default_cfg ( &powermux );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes power inputs every 3 seconds and displays the currently set mode on the USB UART.

```c
void application_task ( void ) 
{
    log_printf( &logger, " OUTPUT : IN1\r\n\n" );
    powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_1_ON );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " OUTPUT : IN2\r\n\n" );
    powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_2_ON );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " OUTPUT : OFF\r\n\n" );
    powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_OFF );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " OUTPUT : AUTO\r\n\n" );
    powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_AUTO );
    Delay_ms ( 1000 );
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
