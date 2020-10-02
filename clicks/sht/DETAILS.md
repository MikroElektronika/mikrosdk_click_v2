 
---
# SHT click

SHT click is a temperature and humidity sensing click board that carries Sensiron’s SHT3x-DIS IC. Compared to its predecessor (SHT11), SHT3x click has increased reliability and enhanced signal processing features with a high signal-to-noise ratio.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/sht_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/sht-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Sht Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Sht Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void sht_cfg_setup ( sht_cfg_t *cfg ); 
 
- Initialization function.
> SHT_RETVAL sht_init ( sht_t *ctx, sht_cfg_t *cfg );

- Click Default Configuration function.
> void sht_default_cfg ( sht_t *ctx );


#### Example key functions :

- Returns temperature measurement in single shot mode.
> float sht_temp_ss ( sht_t *ctx );
 
- Returns humidity measurement in single shot mode.
> float sht_hum_ss ( sht_t *ctx );

- Sets the heater state.
> void sht_heater_control ( sht_t *ctx, uint8_t state );

## Examples Description

> This application enables usage of the temperature and humidity sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initialize the communication interface and configure the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    sht_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    sht_cfg_setup( &cfg );
    SHT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    sht_init( &sht, &cfg );
}
  
```

### Application Task

> Temperature and humidity data is measured and read from
> the sensor. After the data has been read it is displayed
> on the serial port.

```c

void application_task ( void )
{
    //  Task implementation.

    float temperature;
    float humidity;

    Delay_ms( 1500 );

    temperature = sht_temp_ss( &sht );
    log_printf( &logger, "Temperature: %.2f C \r\n", temperature );

    Delay_ms( 200 );

    humidity = sht_hum_ss( &sht );
    log_printf( &logger, "Humidity: %.2f %% \r\n", humidity );

    Delay_ms( 200 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Sht

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
