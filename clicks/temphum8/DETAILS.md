
 

---
# Temp&Hum 8 click

Temp&Hum 8 click is based on a sensor from the popular SHT family, designed to measure temperature and humidity. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temp-hum-8-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempHum8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void temphum8_cfg_setup ( temphum8_cfg_t *cfg ); 
 
- Initialization function.
> TEMPHUM8_RETVAL temphum8_init ( temphum8_t *ctx, temphum8_cfg_t *cfg );

- Click Default Configuration function.
> void temphum8_default_cfg ( temphum8_t *ctx );


#### Example key functions :

- Temperature data
> float temphum8_get_temperature_data ( temphum8_t *ctx, uint8_t temp_format );
 
- Relative Huminidy data
> float temphum8_get_humidity_data ( temphum8_t *ctx );

- Configuration device for measurement
> void temphum8_set_cfg_register ( temphum8_t *ctx, uint8_t cfg );

## Examples Description

> This demo-app shows the temperature measurement procedure using Temp&Hum 8 click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects. 
> Setting the click in the default configuration to start the measurement, 
> and before that call function software_reset().

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum8_cfg_t cfg;

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

    temphum8_cfg_setup( &cfg );
    TEMPHUM8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum8_init( &temphum8, &cfg );

    temphum8_software_reset( &temphum8 );
    temphum8_default_cfg( &temphum8 ); 
}
```

### Application Task

> Reads ambient temperature data and Relative Huminidy data, 
> this data logs to USBUART every 1500ms.

```c
void application_task ( void )
{
    float temperature;
    float humidity;

    //  Task implementation.
    
    log_printf( &logger, "\r\n ---- Ambient data ----\r\n" );

    temperature = temphum8_get_temperature_data( &temphum8, TEMPHUM8_TEMPERATURE_IN_CELSIUS );
    log_printf( &logger, "** Temperature: %.2f °C \r\n", temperature );
    
    humidity = temphum8_get_humidity_data( &temphum8 );
    log_printf( &logger, "** Humidity: %.2f %%RH \r\n", humidity );

    Delay_ms( 1500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum8

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
