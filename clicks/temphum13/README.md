\mainpage Main Page
 
 

---
# TempHum 13 click

Temp&Hum 13 Click is a Click board™ which is perfectly suited for measuring the relative humidity (RH) and temperature. The Click board™ is equipped with the HTU21DF, an accurate and reliable sensor IC, packed in a miniature 3x3mm DFN package.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temphum-13-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum13 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum13 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum13_cfg_setup ( temphum13_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHUM13_RETVAL temphum13_init ( temphum13_t *ctx, temphum13_cfg_t *cfg );

- Click Default Configuration function.
> void temphum13_default_cfg ( temphum13_t *ctx );


#### Example key functions :

- This function calculates humidity.
> float temphum13_get_humidity( temphum13_t *ctx );

 
- This function calculates current temperature.
> float temphum13_get_temperature( temphum13_t *ctx );


- This function sets click measurement resolution.
> uint8_t temphum13_change_resolution( temphum13_t *ctx, uint8_t measurement_resolution );

## Examples Description

This demo shows basic TempHum13 click functionality - temperature
and humidity measurement. 

**The demo application is composed of two sections :**

### Application Init 

Initialize device and driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum13_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum13_cfg_setup( &cfg );
    TEMPHUM13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum13_init( &temphum13, &cfg );
    temphum13_default_cfg( &temphum13 );
}
  
```

### Application Task

Measure temperature and humidity values on every 0,5 seconds
and log them to UART Terminal if they are valid.

```c

void application_task ( void )
{
    temperature = temphum13_get_temperature( &temphum13 );
    humidity = temphum13_get_humidity( &temphum13 );
    
    if (temperature != 65536.0)
    {
        log_printf( &logger, "\r\n> Temperature : %.2f C", temperature );
    }

    if (humidity != 65536.0)
    {       
        log_printf( &logger, "\r\n> Humidity    : %.2f%%RH\r\n", humidity );
    } 

    Delay_ms( 500 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum13

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
