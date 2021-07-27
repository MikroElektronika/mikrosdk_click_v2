\mainpage Main Page
 
 

---
# TempHum 3 click

Temp&Hum 3 click is a smart environmental temperature and humidity sensor Click board™, packed with features which allow easy and simple integration into any design that requires accurate and reliable humidity and temperature measurements.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temp-hum-3-click)

---


#### Click library 

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum3_cfg_setup ( temphum3_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHUM3_RETVAL temphum3_init ( temphum3_t *ctx, temphum3_cfg_t *cfg );

- Click Default Configuration function.
> void temphum3_default_cfg ( temphum3_t *ctx );


#### Example key functions :

- Get temperature value
> float temphum3_get_temperature ( temphum3_t *ctx );
 
- Get humidity value
> float temphum3_get_huminidy ( temphum3_t *ctx );

- Get maximum temperature value
> float temphum3_get_max_hum ( temphum3_t *ctx );

## Examples Description

> This example gets the values of humidity and temperature. 
> It uses predefined minimum and maximum offset values for temperature and humidity.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the module and sets predefined configuration values to the sensor.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum3_cfg_setup( &cfg );
    TEMPHUM3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum3_init( &temphum3, &cfg );
    log_info( &logger, "---- Init done -----" );
    
    temphum3_default_cfg( &temphum3 );
    
    log_info( &logger, "--- Settings Temp&Hum done---" );
}
  
```

### Application Task

> Reads the temperature and huminidy and logs to the USBUART every 500 ms.

```c
void application_task ( void )
{
    float temperature;
    float humidity;

    //  Task implementation.
    
    temperature = temphum3_get_temperature( &temphum3 );
    log_printf( &logger, " Temperature : %f C \r\n", temperature );
    
    humidity = temphum3_get_humidity( &temphum3 );
    log_printf( &logger, " Humidity : %f %% \r\n", humidity );
    Delay_ms( 500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum3

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
