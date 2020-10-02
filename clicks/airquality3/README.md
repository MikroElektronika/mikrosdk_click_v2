\mainpage Main Page
 
 

---
# Air quality 3 click

Air quality 3 click is the air quality measurement device, which is able to output both equivalent CO2 levels and total volatile organic compounds (TVOC) concentration in the indoor environment. 

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/airquality3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/air-quality-3-click>)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the AirQuality3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AirQuality3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void airquality3_cfg_setup ( airquality3_cfg_t *cfg ); 
 
- Initialization function.
> AIRQUALITY3_RETVAL airquality3_init ( airquality3_t *ctx, airquality3_cfg_t *cfg );

- Click Default Configuration function.
> void airquality3_default_cfg ( airquality3_t *ctx );


#### Example key functions :

- Get CO2 and TVOC data
> uint8_t airquality3_get_co2_and_tvoc ( airquality3_t *ctx, airquality3_air_data_t *air_data );
 
- Temperature and humidity data settings
> void airquality3_set_environment_data ( airquality3_t *ctx, uint32_t env_data ); 

-  Function for settings sensor drive mode and interrupts.
> void airquality3_set_measurement_mode ( airquality3_t *ctx, uint8_t mode );

## Examples Description

> The demo application shows air quality measurement.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.
> Call the procedure the wakeup function of the chip.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    airquality3_cfg_setup( &cfg );
    AIRQUALITY3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality3_init( &airquality3, &cfg );

    // Wake-up click procedure

    airquality3_set_power( &airquality3, AIRQUALITY3_POWER_STATE_ON );
    airquality3_hardware_reset( &airquality3 );
    airquality3_app_function( &airquality3, AIRQUALITY3_APP_START );

    airquality3_default_cfg( &airquality3 );

    Delay_ms( 500 );
    log_info( &logger, "---- Start measurement ----" );
}
```

### Application Task

> Reads CO2 and TVOC value in the air and logs this data on the USBUART.

```c
void application_task ( void )
{
    airquality3_air_data_t air_data;

    //  Task implementation.

    airquality3_get_co2_and_tvoc ( &airquality3, &air_data );
    log_printf( &logger, "\r\n---- AirQuality data ----\r\n" );
    log_printf( &logger, ">> CO2 data is %d ppm.\r\n", air_data.co2 );
    log_printf( &logger, ">> TVOC data is %d ppb.\r\n", air_data.tvoc );

    Delay_1sec();
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality3

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
