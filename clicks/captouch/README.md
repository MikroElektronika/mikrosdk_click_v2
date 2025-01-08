
---
# Cap Touch Click

> [Cap Touch Click](https://www.mikroe.com/?pid_product=MIKROE-2888) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2888&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

>  Demo application is used to shows basic controls Cap Touch Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CapTouch

### Example Key Functions

- `captouch_cfg_setup` Config Object Initialization function. 
```c
void captouch_cfg_setup ( captouch_cfg_t *cfg );
``` 
 
- `captouch_init` Initialization function. 
```c
err_t captouch_init ( captouch_t *ctx, captouch_cfg_t *cfg );
```

- `captouch_default_cfg` Click Default Configuration function. 
```c
void captouch_default_cfg ( captouch_t *ctx );
```

- `captouch_set_mode` Select mode. 
```c
void captouch_set_mode ( captouch_t *ctx, uint8_t mode );
```
 
- `captouch_get_touch` Get touch state. 
```c
uint8_t captouch_get_touch ( captouch_t *ctx );
```

### Application Init

> Configuring Clicks and log objects.
> Settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    captouch_cfg_t cfg;

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

    captouch_cfg_setup( &cfg );
    CAPTOUCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    captouch_init( &captouch, &cfg );

    captouch_default_cfg( &captouch );
}
```

### Application Task

> Checks for a new touch event. If so, prints the message to USBUART.

```c
void application_task ( void )
{
    uint8_t touch;

    //  Task implementation.

    touch = captouch_get_touch( &captouch );
    if ( touch != 0 )
    {
        log_printf( &logger, "-- New Touch\r\n" );
        Delay_ms ( 200 );
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
