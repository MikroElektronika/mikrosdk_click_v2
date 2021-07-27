\mainpage Main Page
 
 

---
# Temp-Hum 9 click

Temp-Hum 9 click is a smart temperature and humidity sensing click board™, packed with features that allow simple integration into any design.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temphum-9-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum9_cfg_setup ( temphum9_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHUM9_RETVAL temphum9_init ( temphum9_t *ctx, temphum9_cfg_t *cfg );

- Click Default Configuration function.
> void temphum9_default_cfg ( temphum9_t *ctx );


#### Example key functions :

- Calculating temperature
> float temphum9_get_temperature ( temphum9_t *ctx, uint8_t data );

 
- Calculating relative humidity
> temphum9_get_relative_humidity ( temphum9_t *ctx, uint8_t data );

- Calculating temperature and relative humidity
> temhum9_get_temperature_and_humidity ( *ctx  uint8_t data , float *measurement_data )

## Examples Description

> 
> Temp-Hum 9 click can measure the humidity in the range from 0 to 100 %RH and temperature in the range from -40 ℃ to +125 ℃ with a typical accuracy of ±2 %RH and ±0.2 ℃
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initializes I2C driver and sends SLEEP and WAKEUP dommands
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum9_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum9_cfg_setup( &cfg );
    TEMPHUM9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum9_init( &temphum9, &cfg );

    temphum9_send_command( &temphum9, TEMPHUM9_SLEEP );

    temphum9_sendCommand( &temphum9, TEMPHUM9_SLEEP );
    Delay_ms(500);
    temphum9_sendCommand( &temphum9, TEMPHUM9_WAKEUP );
    Delay_ms(100);
    
    log_printf( &logger, "< < < app init done > > >" );
}
  
```

### Application Task

>
> Performs simultaneous temperature and relative humidity measurements and logs both values
> 

```c

void application_task( )
{
    log_printf( &logger, " " );

    temhum9_get_temperature_and_humidity( &temphum9, TEMPHUM9_NORMAL_MODE, &measurement_data[ 0 ] );
    
    log_printf( &logger, "> > > Temperature       : %d C \r\n", text );

    log_printf( &logger, "> > > Relative humidity       : %d ", text );
    log_printf( &logger, " %% \r\n" );
    
    Delay_ms(1000);
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum9

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
