
---
# Nano Power Click

> [Nano Power Click](https://www.mikroe.com/?pid_product=MIKROE-3035) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3035&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> 
> This example enables the device.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoPower

### Example Key Functions

- `nanopower_cfg_setup` Config Object Initialization function. 
```c
void nanopower_cfg_setup ( nanopower_cfg_t *cfg );
``` 
 
- `nanopower_init` Initialization function. 
```c
err_t nanopower_init ( nanopower_t *ctx, nanopower_cfg_t *cfg );
```

- `nanopower_default_cfg` Click Default Configuration function. 
```c
void nanopower_default_cfg ( nanopower_t *ctx );
```

- `nanopw_enable_device` This function enables and disables the device. 
```c
void nanopw_enable_device ( nanopower_t *ctx, const uint8_t state  );
```

### Application Init

> Initializes GPIO driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    nanopower_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    nanopower_cfg_setup( &cfg );
    NANOPOWER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanopower_init( &nanopower, &cfg );
}
```

### Application Task

> Turns device on for 5 seconds and than turns device off for 10 seconds,then the output voltage starts to fall.


```c
void application_task ( void )
{
    log_printf(&logger,"Device enabled\r\n");
    nanopw_enable_device( &nanopower, NANOPW_ENABLE_DEVICE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf(&logger,"Device disabled\r\n");
    nanopw_enable_device( &nanopower, NANOPW_DISABLE_DEVICE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
