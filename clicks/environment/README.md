
---
# Environment Click

> [Environment Click](https://www.mikroe.com/?pid_product=MIKROE-2467) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2467&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> Example demonstrates use of the Environment Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Environment

### Example Key Functions

- `environment _cfg_setup` Config Object Initialization function. 
```c
void environment _cfg_setup ( environment _cfg_t *cfg );
``` 
 
- `environment _init` Initialization function. 
```c
err_t environment _init ( environment _t *ctx, environment _cfg_t *cfg );
```

- `environment _default_cfg` Click Default Configuration function. 
```c
void environment _default_cfg ( environment _t *ctx );
```

- `environment_get_gas_resistance` Function gets gas resistance value from BME680 chip. 
```c
uint32_t environment_get_gas_resistance ( environment_t *ctx );
```
 
- `environment_get_pressure` Function gets pressure value  of BME680 chip. 
```c
float environment_get_pressure ( environment_t *ctx );
```

- `environment_get_humidity` Function get humidity value of BME680 chip. 
```c
float environment_get_humidity ( environment_t *ctx );
```

### Application Init

> Initialize driver and sets default configuration for BME680 chip.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    environment_cfg_t cfg;

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

    environment_cfg_setup( &cfg );
    ENVIRONMENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    environment_init( &environment , &cfg );
    environment_default_cfg( &environment );
}
```

### Application Task

> This is an example which demonstrates the use of Environment Click board.

```c
void application_task ( void )
{
    //  Task implementation.

    temperature = environment_get_temperature( &environment);
    log_printf( &logger, " Temperature : %f%c", temperature, deg_cel[0]);

    humidity = environment_get_humidity( &environment );
    log_printf( &logger, "      Humidity : %f%%", humidity);

    pressure = environment_get_pressure( &environment );
    log_printf( &logger, "      Pressure : %.3fmbar", pressure);

    gas = environment_get_gas_resistance( &environment );
    log_printf( &logger, "      Gas Resistance : %ld\r\n", gas);

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
