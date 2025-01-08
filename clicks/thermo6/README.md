
---
# Thermo 6 Click

> [Thermo 6 Click](https://www.mikroe.com/?pid_product=MIKROE-2769) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2769&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Demo application shows ambient temperature reading using Thermo 6 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo6

### Example Key Functions

- `thermo6_cfg_setup` Config Object Initialization function. 
```c
void thermo6_cfg_setup ( thermo6_cfg_t *cfg );
``` 
 
- `thermo6_init` Initialization function. 
```c
err_t thermo6_init ( thermo6_t *ctx, thermo6_cfg_t *cfg );
```

- `thermo6_default_cfg` Click Default Configuration function. 
```c
void thermo6_default_cfg ( thermo6_t *ctx );
```

- `thermo6_get_temperature_data` Temperature function. 
```c
float thermo6_get_temperature_data ( thermo6_t *ctx, uint8_t temp_format );
```
 
- `thermo6_get_over_temp_status` Read over-temperature status function. 
```c
uint8_t thermo6_get_over_temp_status ( thermo6_t *ctx );
```

- `thermo6_get_other_register` Set other register. 
```c
float thermo6_get_other_register ( thermo6_t *ctx, uint8_t reg );
```

### Application Init

> Configuring Clicks and log objects.
> Setting the Click in the default configuration to start the measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo6_cfg_t cfg;

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

    thermo6_cfg_setup( &cfg );
    THERMO6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo6_init( &thermo6, &cfg );

    thermo6_default_cfg( &thermo6 );
    log_info( &logger, "---- Start measurement ----");
    Delay_ms ( 1000 );
}
```

### Application Task

> It measures the temperature and logs a message about the current temperature.

```c
void application_task ( void )
{
    float temperature;

    //  Task implementation.

    temperature = thermo6_get_temperature_data( &thermo6, THERMO6_TEMP_FORMAT_CELSIUS );
    log_printf( &logger, ">> Temperature is %.3f C \r\n", temperature );

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
