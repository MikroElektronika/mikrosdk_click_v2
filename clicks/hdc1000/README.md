\mainpage Main Page
 
 

---
# HDC1000 click

HDC1000 Click is a humidity and temperature measurement click board carrying the HDC1000 sensor. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hdc1000_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hdc1000-click)

---


#### Click library 

- **Author**        : Mihajlo Djordevic
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the HDC1000 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HDC1000 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hdc1000_cfg_setup ( hdc1000_cfg_t *cfg ); 
 
- Initialization function.
> HDC1000_RETVAL hdc1000_init ( hdc1000_t *ctx, hdc1000_cfg_t *cfg );

- Click Default Configuration function.
> void hdc1000_default_cfg ( hdc1000_t *ctx );

#### Example key functions :

- This function executes default configuration for HDC1000 click.
> hdc1000_default_cfg( &hdc1000 );
 
- This function gets temperature data from the HDC1000 sensor.
> hdc1000_get_temperature_data( &hdc1000 );

- This function gets humidity data from the HDC1000 sensor.
> hdc1000_get_humidity_data( &hdc1000 );

## Examples Description

>
> Demo application code is used for measuring temperature and humidity.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> AppInit is used for Logger and Click initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hdc1000_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "---- Application Init ---- \r\n\n" );

    //  Click initialization.

    hdc1000_cfg_setup( &cfg );
    HDC1000_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hdc1000_init( &hdc1000, &cfg );
    
    hdc1000_default_cfg( &hdc1000 );
    log_printf( &logger, "---- Start measurement ---- \r\n\n" );
    Delay_ms ( 1000 );
    
}
  
```

### Application Task

>
> This is an example which demonstrates the usage of HDC1000 Click board.
> HDC1000 measure temperature and humidity, and calculate dewpoint value from the HDC1000 sensor.
> 

```c

void application_task ( void )
{
    temperature = hdc1000_get_temperature_data( &hdc1000 );
    log_printf( &logger, " Temperature : %f C \r\n", temperature );
    
    humidity = hdc1000_get_humidity_data( &hdc1000 );
    log_printf( &logger, " Humidity : %f % \r\n", humidity );

    log_printf( &logger, "----------------------------------- \r\n" );

    Delay_ms ( 3000 );
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HDC1000

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
