
---
# Pressure 5 Click

> [Pressure 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3566) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3566&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example performs temperature & pressure measurement every 2 seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure5

### Example Key Functions

- `pressure5_cfg_setup` Config Object Initialization function. 
```c
void pressure5_cfg_setup ( pressure5_cfg_t *cfg );
``` 
 
- `pressure5_init` Initialization function. 
```c
err_t pressure5_init ( pressure5_t *ctx, pressure5_cfg_t *cfg );
```

- `pressure5_default_cfg` Click Default Configuration function. 
```c
void pressure5_default_cfg ( pressure5_t *ctx );
```

- `pressure5_update_coefficient` This function allows you to update the calibration coefficient. 
```c
void pressure5_update_coefficient ( pressure5_t *ctx );
```
 
- `pressure5_get_temperature_data` This function gets temperature in Celsius. 
```c
float pressure5_get_temperature_data ( pressure5_t *ctx );
```

- `pressure5_get_pressure_data` This function gets pressure in mBar. 
```c
float pressure5_get_pressure_data ( pressure5_t *ctx );
```

### Application Init

> Initialize driver init, test comunication, software reset, update
> coefficient and configuration module for start measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure5_cfg_t cfg;
    uint8_t tmp;
err_t init_ret;

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

    pressure5_cfg_setup( &cfg );
    PRESSURE5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure5_init( &pressure5, &cfg );
    pressure5_default_cfg( &pressure5 );
}
```

### Application Task

> Reads Pressure data in [mBar] and Temperature data in [C] and logs data every seconds.

```c
void application_task ( void )
{
    //  Task implementation.

    temperature = pressure5_get_temperature_data( &pressure5 );
    log_printf( &logger, "Temperature: %.2f C\r\n", temperature );
    pressure = pressure5_get_pressure_data( &pressure5 );
    log_printf( &logger, "Pressure: %.2f mBar\r\n ", pressure );
    log_printf( &logger, "\r\n" );
    
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
