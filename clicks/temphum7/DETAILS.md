
---
# Temp&Hum 7 click

Temp&Hum 7 click is a Click board™ which is perfectly suited for measuring the relative humidity (RH) and temperature. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum7_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/temp-hum-7-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum7_cfg_setup ( temphum7_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHUM7_RETVAL temphum7_init ( temphum7_t *ctx, temphum7_cfg_t *cfg );

- Click Default Configuration function.
> void temphum7_default_cfg ( temphum7_t *ctx );


#### Example key functions :

- Relative humidity.
> float temphum7_get_relative_humidity ( temphum7_t *ctx, uint8_t mode_data );
 
- Get temerature.
> float temphum7_get_temperature ( temphum7_t *ctx, uint8_t mode_data );

- Firmware revision.
> uint8_t temphum7_get_firmware_revision ( temphum7_t *ctx );

## Examples Description

> This application measurement temperature and humidity data.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device and logger module and sets default configuration for measurements.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum7_cfg_t cfg;
    
    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART ( log_cfg );
    log_init ( &logger, &log_cfg );
    log_info ( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum7_cfg_setup ( &cfg );
    TEMPHUM7_MAP_MIKROBUS ( cfg, MIKROBUS_1 );
    temphum7_init ( &temphum7, &cfg );

    temphum7_default_cfg( &temphum7 );
} 
```

### Application Task

> Calculates and Logs temperature and relative humidity

```c
void application_task ( void )
{
    
    temperature = temphum7_get_temperature ( &temphum7, TEMPHUM7_HOLD_MASTER_MODE );
    mikrobus_printf ( "-> Temperature: %f C/r/n", temperature );

    relative_humidity = temphum7_get_relative_humidity ( &temphum7, TEMPHUM7_HOLD_MASTER_MODE );
    mikrobus_printf ( "-> Relative humidity: %f %%RH/r/n ", relative_humidity );

    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum7

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
