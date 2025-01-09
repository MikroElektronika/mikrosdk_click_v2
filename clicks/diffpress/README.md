
---
# Diff Press Click

> [Diff Press Click](https://www.mikroe.com/?pid_product=MIKROE-3332) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3332&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo application is made for measuring differential pressure.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DiffPress

### Example Key Functions
 
- `diffpress_init` Initialization function. 
```c
err_t diffpress_init ( diffpress_t *ctx, diffpress_cfg_t *cfg );
```

- `diffpress_get_adc_data` Gets adc data function. 
```c
uint16_t diffpress_get_adc_data ( diffpress_t *ctx );
```
 
- `diffpress_get_pressure_difference` Gets pressure difference function. 
```c
float diffpress_get_pressure_difference ( diffpress_t *ctx );
```

### Application Init

> Initializes device and logger module.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    diffpress_cfg_t cfg;

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

    diffpress_cfg_setup( &cfg );
    DIFFPRESS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    diffpress_init( &diffpress, &cfg );
}
```

### Application Task

> Logs pressure difference data. 

```c
void application_task ( void )
{
    pressure_difference = diffpress_get_pressure_difference( &diffpress );

    log_printf( &logger, "-- Pressure difference  : %f kPa\r\n", pressure_difference );

    Delay_ms ( 100 );
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
