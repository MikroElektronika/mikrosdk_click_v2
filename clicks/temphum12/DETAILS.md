
---
# Temp&Hum 12 click

Temp&Hum 12 click is a smart environmental temperature and humidity sensor Click board™, packed with features which allow easy and simple integration into any design that requires accurate and reliable humidity and temperature measurements. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum12_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/temphum-12-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum12 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum12 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum12_cfg_setup ( temphum12_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHUM12_RETVAL temphum12_init ( temphum12_t *ctx, temphum12_cfg_t *cfg );

- Click Default Configuration function.
> void temphum12_default_cfg ( temphum12 *ctx );

#### Example key functions :

- Temperature data
> float temphum12_get_temperature ( temphum12_t *ctx, uint8_t temp_in );
 
- Relative Huminidy data
> float temphum12_get_humidity ( temphum12_t *ctx );

- Interrupt state
> uint8_t temphum12_get_intrrupt_state ( temphum12_t *ctx );

## Examples Description

> This application measures temperature and humidity.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and configuration device for measurement.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum12_cfg_t cfg;
    uint16_t tmp;
    uint8_t read_reg [ 2 ];

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum12_cfg_setup( &cfg );
    TEMPHUM12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum12_init( &temphum12, &cfg );

    temphum12_default_cfg( &temphum12 );
    
    Delay_ms( 1500 );
    log_printf( &logger, "--- Start measurement ----\r\n" );
}

  
```

### Application Task

> Reads Temperature and Humidity data and this data logs to the USBUART every 1 sec.

```c

void application_task ( void )
{
    float temperature;
    float humidity;

    temperature = temphum12_get_temperature( &temphum12, TEMPHUM12_TEMP_IN_CELSIUS);

    log_printf( &logger, "Temperature: %.2f \r\n", temperature );
    Delay_1sec( );
    
    humidity = temphum12_get_humidity( &temphum12 );

    log_printf( &logger, "Humidity: %.2f \r\n", humidity );
    
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_1sec( );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum12

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
