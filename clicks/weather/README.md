
---
# Weather Click

> [Weather Click](https://www.mikroe.com/?pid_product=MIKROE-1978) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1978&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : okt 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This demo-app shows the temperature, pressure and humidity measurement using Weather Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Weather

### Example Key Functions

- `weather_cfg_setup` Config Object Initialization function.
```c
void weather_cfg_setup ( weather_cfg_t *cfg ); 
```

- `weather_init` Initialization function.
```c
err_t weather_init ( weather_t *ctx, weather_cfg_t *cfg );
```

- `weather_default_cfg` Click Default Configuration function.
```c
err_t weather_default_cfg ( weather_t *ctx );
```

- `weather_get_ambient_data` Use this function to read the temperature, pressure and humidity data
```c
err_t weather_get_ambient_data( weather_t *ctx, weather_data_t *weather_data );
```

- `weather_get_device_id` You can use this function as a check on Click communication with your MCU.
```c
err_t weather_get_device_id ( weather_t *ctx, uint8_t *device_id );
```

- `weather_measurement_cfg` Use this function to set up new settings
```c
err_t weather_measurement_cfg ( weather_t *ctx, weather_measurement_cfg_t *cfg );
```

### Application Init

> Configuring Clicks and log objects.
> Setting the Click in the default configuration to start the measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    weather_cfg_t weather_cfg;

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
    weather_cfg_setup( &weather_cfg );
    WEATHER_MAP_MIKROBUS( weather_cfg, MIKROBUS_1 );
    if ( WEATHER_OK != weather_init( &weather, &weather_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( WEATHER_OK != weather_default_cfg ( &weather ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
} 
```

### Application Task

> Reads Temperature data, Relative Humidity data and Pressure data, and displays them on USB UART every 1500ms.

```c
void application_task ( void )
{
    weather_data_t weather_data;

    if ( WEATHER_OK == weather_get_ambient_data( &weather, &weather_data ) )
    {
        log_printf( &logger, " \r\n ---- Weather data ----- \r\n" );
        log_printf( &logger, "[PRESSURE]: %.2f mBar.\n\r", weather_data.pressure );
        log_printf( &logger, "[TEMPERATURE]: %.2f C.\n\r", weather_data.temperature );
        log_printf( &logger, "[HUMIDITY]: %.2f %%.\n\r", weather_data.humidity );

        Delay_ms ( 1000 );
        Delay_ms ( 500 );
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
