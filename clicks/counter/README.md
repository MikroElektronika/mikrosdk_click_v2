
---
# Counter Click

> [Counter Click](https://www.mikroe.com/?pid_product=MIKROE-1917) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1917&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application measures the speed and the position of the DC motor shafts.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Counter

### Example Key Functions

- `counter_cfg_setup` Config Object Initialization function. 
```c
void counter_cfg_setup ( counter_cfg_t *cfg );
``` 
 
- `counter_init` Initialization function. 
```c
err_t counter_init ( counter_t *ctx, counter_cfg_t *cfg );
```

- `counter_default_cfg` Click Default Configuration function. 
```c
void counter_default_cfg ( counter_t *ctx );
```

- `counter_read_cntr` This function reads CNTR, using Click object. 
```c
int32_t counter_read_cntr ( counter_t *ctx );
```
 
- `counter_read_str` This function reads STR, using Click object. 
```c
uint8_t counter_read_str ( counter_t *ctx );
```

- `counter_read_otr` This function reads OTR, using Click object. 
```c
int32_t counter_read_otr ( counter_t *ctx );
```

### Application Init

> Initializes driver init and chip init


```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    counter_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    counter_cfg_setup( &cfg );
    COUNTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    counter_init( &counter, &cfg );

    counter_default_cfg( &counter );
    Delay_ms ( 300 );
}
```

### Application Task

> Reads data from the CNTR register and calculates the speed of the motor in Rad/s.
> All data is being displayed on the USB UART terminal where you can track their changes.
> The CNTR is a software configurable 8, 16, 24 or 32-bit up/down counter which
> counts the up/down pulses resulting from the quadrature clocks applied at the
> A and B inputs, or alternatively, in non-quadrature mode, pulses applied at the A input.


```c
void application_task ( void )
{
    count = counter_read_cntr( &counter );
    log_printf( &logger, "Counter: %ld\r\n",  count );
    speed = ( float ) ( count - count_old ) / 3600.0;
    speed *= 6.283185;
    log_printf( &logger, "Speed: %.4f Rad/s\r\n",  speed );
    count_old = count;
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Note

> An appropriate motor with optical encoder needs to be connected to the Click board.

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
