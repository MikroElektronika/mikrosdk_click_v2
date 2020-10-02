\mainpage Main Page

---
# Environment click

Environment click measures temperature, relative humidity, pressure and VOC (Volatile Organic compounds gases). The click carries the BME680 environmental sensor from Bosch. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/enviroment_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/environment-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Environment Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Environment Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void environment _cfg_setup ( environment _cfg_t *cfg ); 
 
- Initialization function.
> ENVIRONMENT_RETVAL environment _init ( environment _t *ctx, environment _cfg_t *cfg );

- Click Default Configuration function.
> void environment _default_cfg ( environment _t *ctx );


#### Example key functions :

- Function gets gas resistance value from BME680 chip.
> uint32_t environment_get_gas_resistance( environment_t *ctx );
 
- Function gets pressure value  of BME680 chip.
> float environment_get_pressure( environment_t *ctx );

- Function get humidity value of BME680 chip.
> float environment_get_humidity( environment_t *ctx );

## Examples Description

> Example demonstrates use of the Environment click board.

**The demo application is composed of two sections :**

### Application Init 

> Initialize driver and sets default configuration for BME680 chip.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    environment_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
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

    Delay_ms( 2000 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Environment

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
