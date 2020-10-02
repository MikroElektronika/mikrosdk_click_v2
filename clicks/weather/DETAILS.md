
 

---
# Weather click

Weather click carries BME280 integrated environmental unit from Bosch.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/weather_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/weather-click>)

---


#### Click library 

- **Author**        : Katarina Perendic
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

- Config Object Initialization function.
> void weather_cfg_setup ( weather_cfg_t *cfg ); 
 
- Initialization function.
> WEATHER_RETVAL weather_init ( weather_t *ctx, weather_cfg_t *cfg );

- Click Default Configuration function.
> void weather_default_cfg ( weather_t *ctx );


#### Example key functions :

- Weather data
> void weather_get_ambient_data( weather_t *ctx, weather_data_t *weather_data );
 
- Measurement configuration
> void weather_measurement_cfg ( weather_t *ctx, weather_measurement_cfg_t *cfg );

- Software reset function
> void weather_software_reset ( weather_t *ctx );

## Examples Description

> This demo-app shows the temperature, pressure and humidity measurement using Weather click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Setting the click in the default configuration to start the measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    weather_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    weather_cfg_setup( &cfg );
    WEATHER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    weather_init( &weather, &cfg );

    weather_default_cfg( &weather );
} 
```

### Application Task

> Reads Temperature data, Relative Huminidy data and Pressure data, 
> this data logs to USBUART every 1500ms.

```c
void application_task ( void )
{
    weather_data_t weather_data;

    //  Task implementation.

    weather_get_ambient_data( &weather, &weather_data );

    log_printf( &logger, " \r\n ---- Weather data ----- \r\n" );
    log_printf( &logger, "[PRESSURE]: %.2f mBar.\n\r", weather_data.pressure );
    log_printf( &logger, "[TEMPERATURE]: %.2f C.\n\r", weather_data.temperature );
    log_printf( &logger, "[HUMIDITY]: %.2f %%.\n\r", weather_data.humidity );

    Delay_ms( 1500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Weather

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
