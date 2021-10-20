\mainpage Main Page
 
 

---
# Thermo 6 click

Thermo 6 click is a precise and versatile ambient temperature measurement click board, based on the Maxim Integrated MAX31875 temperature sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-6-click)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo6_cfg_setup ( thermo6_cfg_t *cfg ); 
 
- Initialization function.
> THERMO6_RETVAL thermo6_init ( thermo6_t *ctx, thermo6_cfg_t *cfg );

- Click Default Configuration function.
> void thermo6_default_cfg ( thermo6_t *ctx );


#### Example key functions :

- Temperature function
> float thermo6_get_temperature_data ( thermo6_t *ctx, uint8_t temp_format );
 
- Read over-temperature status function
> uint8_t thermo6_get_over_temp_status( thermo6_t *ctx );

- Set other register
> float thermo6_get_other_register( thermo6_t *ctx, uint8_t reg );

## Examples Description

> Demo application shows ambient temperature reading using Thermo 6 click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Setting the click in the default configuration to start the measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo6_cfg_t cfg;

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

    thermo6_cfg_setup( &cfg );
    THERMO6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo6_init( &thermo6, &cfg );

    thermo6_default_cfg( &thermo6 );
    log_info( &logger, "---- Start measurement ----");
    Delay_ms( 1000 );
}
```

### Application Task

> It measures the temperature and logs a message about the current temperature.

```c
void application_task ( void )
{
    float temperature;

    //  Task implementation.

    temperature = thermo6_get_temperature_data( &thermo6, THERMO6_TEMP_FORMAT_CELSIUS );
    log_printf( &logger, ">> Temperature is %.3f C \r\n", temperature );

    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo6

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
