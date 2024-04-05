

---
# Temp Hum click

Temp&Hum Click carries ST’s HTS221 temperature and relative humidity sensor. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temp-hum-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum_cfg_setup ( temphum_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHIM_RETVAL temphum_init ( temphum_t *ctx, temphum_cfg_t *cfg );

- Click Default Configuration function.
> void temphum_default_cfg ( temphum_t *ctx );


#### Example key functions :

- Function gets temperature value in degrees Celsius [ �C ]
  and humidity value in percentage [ % ] by reading from the
  two target 8-bit register address of HTS221 sensor on Temp&Hum Click
  and converts it by performing linear interpolation on read data.
> void temphum_get_temp_hum ( temphum_t *ctx, float *temperature, float *humidity );

 
- Function get temperature value in degrees Celsius [ �C ]
  from HTS221 sensor on Temp&Hum Click.
> float temphum_get_temperature( temphum_t *ctx );

- Function get humidity value in percentage [ % ]
  from HTS221 sensor on Temp&Hum Click.
> float temphum_get_humidity( temphum_t *ctx );

## Examples Description

> This application measures temperature and humidity, with temperature in range of 0 - 60 deg.

**The demo application is composed of two sections :**

### Application Init 

>  Initialization driver enable's - I2C,
>  set default configuration and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum_cfg_t cfg;

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

    temphum_cfg_setup( &cfg );
    TEMPHIM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum_init( &temphum, &cfg );

    temphum_default_cfg( &temphum );

    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "      Temp&Hum Click      \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "       Initializing       \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    
    Delay_ms ( 100 );
}
  
```

### Application Task

> This is a example which demonstrates the use of TempAndHum Click board.
> Measured temperature and humidity data from the HTS221 sensor.
> Convert temperature data to degrees Celsius [ �C ] and humidity data to percentarg [ % ].
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on usb uart changes for every 3 sec.

```c

void application_task ( void )
{
    //  Task implementation.

    float temperature;
    float humidity;

    temperature = temphum_get_temperature( &temphum );

    humidity = temphum_get_humidity( &temphum );

    log_printf( &logger, " Temperature :  %.2f C\r\n", temperature );

    log_printf( &logger, " Humidity    : %.2f %%\r\n", humidity );

    log_printf( &logger, "--------------------------\r\n" );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum

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
