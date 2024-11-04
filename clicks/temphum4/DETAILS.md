

---
# Temp&Hum 4 Click

Temp&Hum 4 Click is a smart environmental temperature and humidity sensor Click board™, packed with features which allow easy and simple integration into any design that requires accurate and reliable humidity and temperature measurements. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/temp-hum-4-click)

---


#### Click library 

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Temp&Hum4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Temp&Hum4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum4_cfg_setup ( temphum4_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHUM4_RETVAL temphum4_init ( temphum4_t *ctx, temphum4_cfg_t *cfg );

- Click Default Configuration function.
> void temphum4_default_cfg ( temphum4_t *ctx );


#### Example key functions :

- Function returns temperature value from the module.
> float temphum4_get_temperature ( temphum4_t *ctx );
 
- Function returns humidity value from the sensor.
> float temphum4_get_humidity ( temphu4_t *ctx );

- Function returns manufacturer's ID from the module.
> uint16_t temphum4_get_manifacturer_id ( temphum4_t *ctx );

## Examples Description

> This application reads temperature and humidity data from the module.

**The demo application is composed of two sections :**

### Application Init 


> Initializes module and sets required pins to ACTIVE state, sets the default 
> configuration for interrupts and measurement and sets the minimum / maximum values for
> Temperature and Humidity readings. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum4_cfg_t cfg;

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

    temphum4_cfg_setup( &cfg );
    TEMPHUM4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum4_init( &temphum4, &cfg );
    
    temphum4_default_cfg( &temphum4 );

    log_info( &logger, "---Temp&Hum 4 Configured---" );
}
```

### Application Task

> Reads the temperature and humidity values and logs them every 500 ms.

```c
void application_task ( void )
{
    float temperature;
    float humidity;
    
    temperature = temphum4_get_temperature( &temphum4 );
    log_printf( &logger, " Temperature : %f C \r\n", temperature );
    humidity = temphum4_get_humidity( &temphum4 );
    log_printf( &logger, " Humidity : %f %% \r\n", humidity );
    Delay_ms ( 500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Temp&Hum4

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
