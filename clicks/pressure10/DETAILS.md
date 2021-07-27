
---
# Pressure 10 click

Pressure 10 Click features a digital interface barometric pressure sensor, based on piezoresistive bridge, labeled as HSPPAD042A, from ALPS Electric. It can use both SPI and I2C communication protocols, allowing it to be interfaced with a broad range of MCUs. Besides the pressure readings, this Click board™ also offers very accurate temperature reading, which is required for the pressure readings compensation and can be used in a wide range of battery-powered and portable applications thanks to its very low power consumption. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure10_click.png">
</p>

[click Product page](https://www.mikroe.com/pressure-10-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure10 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pressure10 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pressure10_cfg_setup ( pressure10_cfg_t *cfg ); 
 
- Initialization function.
> PRESSURE10_RETVAL pressure10_init ( pressure10_t *ctx, pressure10_cfg_t *cfg );

- Click Default Configuration function.
> void pressure10_default_cfg ( pressure10_t *ctx );


#### Example key functions :

- Send command.
> void pressure10_send_cmd ( pressure10_t *ctx, uint8_t cmd );
 
- Check communication.
> uint8_t pressure10_check_communication ( pressure10_t *ctx );

- Get status function.
> void pressure10_get_status( pressure10_t *ctx, pressure10_status_t *status_obj );

## Examples Description

> Pressure 10 Click features a digital interface barometric pressure sensor, based on 
> piezoresistive bridge. It can use both SPI and I2C communication protocols, allowing 
> it to be interfaced with a broad range of MCUs. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, checks the communication and configures the module for measurement.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure10_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pressure10_cfg_setup( &cfg );
    PRESSURE10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure10_init( &pressure10, &cfg );

    check_com = pressure10_check_communication( &pressure10 );
    if ( check_com == 0 )
    {
        log_printf( &logger, ">> Communication [OK]\r\n" );
    }
    else
    {
        log_printf( &logger, ">> Communication [ERROR]\r\n" );
        for( ; ; );
    }

    pressure10_default_cfg ( &pressure10 );
    log_printf( &logger, "----------------------------\r\n" );
}
  
```

### Application Task

> Reads the pressure and temperature data every 1500ms and displays the results on the USB UART.

```c

void application_task ( void )
{
    float temperature;
    float pressure;

    pressure = pressure10_get_pressure( &pressure10 );
    temperature = pressure10_get_temperature( &pressure10 );

    log_printf( &logger, ">> Temperature: %.2f C\r\n", temperature );

    log_printf( &logger, "----------------------------\r\n" );

    log_printf( &logger, ">> Pressure: %.2f mBar\r\n", pressure );

    log_printf( &logger, "----------------------------\r\n" );

    Delay_ms( 1500 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure10

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
