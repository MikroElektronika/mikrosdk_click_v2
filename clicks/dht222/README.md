\mainpage Main Page
 
---
# DHT22 2 click

DHT22 2 click is used for measuring the environmental temperature and relative humidity. It uses the CM2322 sensor, with very accurate thermal and humidity measuring capabilities. It can use either 1-Wire or I2C protocol to communicate with the integrated circuit.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dht222_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/dht22-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Dht222 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dht222 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dht222_cfg_setup ( dht222_cfg_t *cfg ); 
 
- Initialization function.
> DHT222_RETVAL dht222_init ( dht222_t *ctx, dht222_cfg_t *cfg );


#### Example key functions :

- The function calculate the temperature data from sensor data reading from the sensor AM2322. 
> uint16_t dht222_get_temperature ( dht222_t *ctx );
 
- The 16-bit humidity data should be divided by 10 to obtain the exact percentage of humidity [ % RH ].
> uint16_t dht222_get_humidity ( dht222_t *ctx );

- Function read 16-bit data from 8-bit register address.
> uint16_t dht222_read_data ( dht222_t *ctx, uint8_t address );

## Examples Description

> DHT22 2 click is used for measuring the environmental temperature and relative humidity. 
> The calibration coefficient is saved in the OTP memory of an integrated MCU. The integrated 
> MCU also provides I2C or 1-Wire interface, selectable by the onboard SMD jumper selectors. 
> The operating voltage can also be selected by the onboard SMD jumper.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C and start write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dht222_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "---- Application Init ----" );

    //  Click initialization.

    dht222_cfg_setup( &cfg );
    DHT222_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dht222_init( &dht222, &cfg );

    Delay_ms( 500 );
}
  
```

### Application Task

> This is a example which demonstrates the use of DHT22 2 Click board.
> DHT22 2 Click communicates with register via I2C protocol read data from register,
> measured temperature and humidity data from the AM2322 sensor.
> Convert temperature data to degrees Celsius [ �C ] and
> humidity data to percentarg [ % ].
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 5 sec.

```c

void application_task ( void )
{
    temperature = dht222_get_temperature( &dht222 );

    Delay_1sec( );

    humidity = dht222_get_humidity( &dht222 );

    dht222_display_temp_hum( );

    Delay_ms( 5000 );
}

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dht222

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
