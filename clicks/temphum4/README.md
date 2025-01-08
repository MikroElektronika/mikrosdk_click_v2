
---
# Temp&Hum 4 Click

> [TempHum 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2938) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2938&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application reads temperature and humidity data from the module.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Temp&Hum4

### Example Key Functions

- `temphum4_cfg_setup` Config Object Initialization function. 
```c
void temphum4_cfg_setup ( temphum4_cfg_t *cfg );
``` 
 
- `temphum4_init` Initialization function. 
```c
err_t temphum4_init ( temphum4_t *ctx, temphum4_cfg_t *cfg );
```

- `temphum4_default_cfg` Click Default Configuration function. 
```c
void temphum4_default_cfg ( temphum4_t *ctx );
```

- `temphum4_get_temperature` Function returns temperature value from the module. 
```c
float temphum4_get_temperature ( temphum4_t *ctx );
```
 
- `temphum4_get_humidity` Function returns humidity value from the sensor. 
```c
float temphum4_get_humidity ( temphu4_t *ctx );
```

- `temphum4_get_manifacturer_id` Function returns manufacturer's ID from the module. 
```c
uint16_t temphum4_get_manifacturer_id ( temphum4_t *ctx );
```

### Application Init


> Initializes module and sets required pins to ACTIVE state, sets the default 
> configuration for interrupts and measurement and sets the minimum / maximum values for
> Temperature and Humidity readings. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum4_cfg_t cfg;

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

    temphum4_cfg_setup( &cfg );
    TEMPHUM4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum4_init( &temphum4, &cfg );
    
    temphum4_default_cfg( &temphum4 );

    log_info( &logger, "---Temp&Hum 4 Configured---" );
}
```

### Application Task

> Reads the temperature and humidity values and logs them every 500 ms.

```c
void application_task ( void )
{
    float temperature;
    float humidity;
    
    temperature = temphum4_get_temperature( &temphum4 );
    log_printf( &logger, " Temperature : %f C \r\n", temperature );
    humidity = temphum4_get_humidity( &temphum4 );
    log_printf( &logger, " Humidity : %f %% \r\n", humidity );
    Delay_ms ( 500 );
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
