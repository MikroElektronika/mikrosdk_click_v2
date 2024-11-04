\mainpage Main Page
 
---
# Weather Click

> Weather Click carries BME280 integrated environmental unit from Bosch.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/weather_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/weather-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : okt 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Weather Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Weather Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This demo-app shows the temperature, pressure and humidity measurement using Weather Click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
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

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Weather

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
