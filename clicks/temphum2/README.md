\mainpage Main Page
 
 

---
# Temp&Hum 2 click

Temp&Hum 2 click is a smart temperature and humidity sensor click board™, packed with features, that allow easy and simple integration into any design that requires accurate and reliable humidity and temperature measurements.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temp-hum-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum2_cfg_setup ( temphum2_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHUM2_RETVAL temphum2_init ( temphum2_t *ctx, temphum2_cfg_t *cfg );

- Click Default Configuration function.
> void temphum2_default_cfg ( temphum2_t *ctx );


#### Example key functions :

- This function for reads Eletronic ID
> void temhum2_get_eletronic_id ( temphum2_t *ctx, uint8_t *electronic_id );
 
- Functions for set measurement mode
> void temphum2_set_mode ( uint8_t select_mode, uint8_t speed_mode );

- Functions for mesurement
> void temphum2_get_measurement ( temphum2_t *ctx, float *data_buffer );

## Examples Description

> This application measures temperature and humidity. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init, set work mode and Heater

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg ); 
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum2_cfg_setup( &cfg );
    TEMPHUM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum2_init( &temphum2, &cfg );

    temphum2_default_cfg( &temphum2 );
}
  
```

### Application Task

> Reads temperature and humidity and logs values on usbuart for every 500ms. 

```c

void application_task ( void )
{
    float data_buffer[ 2 ];
    
    temphum2_get_measurement( &temphum2, &data_buffer[ 0 ] );
    
    log_printf( &logger, " --- Temperature : %.2f C \r\n ", data_buffer[ 0 ] );
    log_printf( &logger, " --- Humidity : %.2f RH \r\n ", data_buffer[ 1 ] );
    
    Delay_ms( 500 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum2

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
