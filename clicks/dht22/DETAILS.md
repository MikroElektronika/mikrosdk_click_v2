
# DHT22 click

DHT22 click is a temperature and humidity measurement board carrying the sensor of the same name.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/dht22_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/dht22-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Dht22 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dht22 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dht22_cfg_setup ( dht22_cfg_t *cfg ); 
 
- Initialization function.
> DHT22_RETVAL dht22_init ( dht22_t *ctx, dht22_cfg_t *cfg );

#### Example key functions :

- Sends start signal to the sensor function.
> void dht22_start_signal ( dht22_t *ctx );
 
- Release the bus to wait the sensor response signal function.
> uint8_t dht22_check_sensor_response ( dht22_t *ctx );

- Reading data from the sensor function.
> uint32_t dht22_get_sensor_data ( dht22_t *ctx );

## Examples Description

> It’s a low cost reliable solution that communicates with the target board     microcontroller through a single Serial Data Line.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - GPIO and start write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    dht22_cfg_setup( &cfg );
    DHT22_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dht22_init( &dht22, &cfg );
}
  
```

### Application Task

> This is a example which demonstrates the use of DHT22 Click board. 

```c

void application_task ( void )
{
    cs_output( &dht22, &cfg );

    dht22_start_signal( &dht22 );

    
    cs_input( &dht22, &cfg );

    if ( dht22_check_sensor_response( &dht22 ) )
    {
        sensor_data = dht22_get_sensor_data( &dht22 );

        if ( sensor_data != 0 )
        {
            temperature = dht22_calculate_temperature( &dht22, sensor_data );

            humidity = dht22_calculate_humidity( &dht22, sensor_data );

            dht22_display_temp_hum( );
        }
    }
    Delay_1sec( );
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dht22

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
