\mainpage Main Page
 
---
# Barometer Click

Barometer Click carries the LPS25HB IC, which is a piezoresistive absolute pressure sensor with a measurement range from 260 to 1260 hPa.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barometer_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/barometer-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Barometer Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Barometer Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void barometer_cfg_setup ( barometer_cfg_t *cfg ); 
 
- Initialization function.
> BAROMETER_RETVAL barometer_init ( barometer_t *ctx, barometer_cfg_t *cfg );

- Click Default Configuration function.
> void barometer_default_cfg ( barometer_t *ctx );


#### Example key functions :

- Read temperature in degrees Celsius function
> float barometer_get_temperature_c ( barometer_t *ctx );
 
- Read pressure in milibars function
> float barometer_get_pressure( barometer_t *ctx );

- Check sensor status function
> uint8_t barometer_check_status ( barometer_t *ctx );

## Examples Description

> This application measures temperature and pressure data. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C, set default configuration and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    barometer_cfg_t cfg;

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

    barometer_cfg_setup( &cfg );
    BAROMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barometer_init( &barometer, &cfg );

    barometer_default_cfg( &barometer );

    // Check sensor id
    if ( barometer_check_id( &barometer ) != BAROMETER_DEVICE_ID )
    {
        log_printf( &logger, "   ERROR  \r\n " );
    }
    else
    {
        log_printf( &logger, "   Initialization  \r\n" );
    }
        
    log_printf( &logger, "-------------------------------- \r\n" );
    Delay_100ms( );
}
  
```

### Application Task

> This is a example which demonstrates the use of Barometer Click board 

```c

void application_task ( void )
{
    float temperature_c;
    float pressure;

    temperature_c = barometer_get_temperature_c( &barometer );
    Delay_100ms( );

    pressure = barometer_get_pressure( &barometer );
    Delay_100ms( );

    log_printf( &logger, " Temperature : %.2f\r\n", temperature_c );

    log_printf( &logger, " Pressure    : %.2f\r\n", pressure );
    log_printf( &logger, "-------------------------------- \r\n" );

    Delay_1sec( );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer

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
