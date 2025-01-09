
---
# Hydro Probe Click

> [Hydro Probe Click](https://www.mikroe.com/?pid_product=MIKROE-4131) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4131&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo application measures moisture.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HydroProbe

### Example Key Functions

- `hydroprobe_cfg_setup` Config Object Initialization function. 
```c
void hydroprobe_cfg_setup ( hydroprobe_cfg_t *cfg );
``` 
 
- `hydroprobe_init` Initialization function. 
```c
err_t hydroprobe_init ( hydroprobe_t *ctx, hydroprobe_cfg_t *cfg );
```

- `hydroprobe_avg_val` Get average value function. 
```c
uint16_t hydroprobe_avg_val ( hydroprobe_t *ctx );
```
 
- `hydroprobe_min_val` Get minimum value function. 
```c
uint16_t hydroprobe_min_val ( hydroprobe_t *ctx );
```

- `hydroprobe_rel_env_hum` Get Relative humidity of the environment function. 
```c
uint8_t hydroprobe_rel_env_hum ( hydroprobe_t *ctx, uint16_t dry_val, uint16_t wet_val );
```

### Application Init

> Initalizes I2C driver, prerforms calibration and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hydroprobe_cfg_t cfg;

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

    hydroprobe_cfg_setup( &cfg );
    HYDROPROBE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hydroprobe_init( &hydroprobe, &cfg );
    
    Delay_ms ( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Hydro Probe Click  \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    hydroprobe_calib( );
    log_printf( &logger, "     Calibrated      \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> This example shows the capabilities of the Hydro Probe Click by measuring 
> environment moisture content and displaying it in percent via USB UART.

```c
void application_task ( void )
{
    humy_val = hydroprobe_rel_env_hum( &hydroprobe, dry_val, wet_val );
    log_printf( &logger, "Environment moisture content: %d %% \r\n ", ( uint16_t ) humy_val );
    log_printf( &logger, "------------------------------\r\n" );
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
