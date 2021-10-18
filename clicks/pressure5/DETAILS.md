

---
# Pressure 5 click

Pressure 5 click is a barometric pressure measurement Click board™, which features the BMP388, an accurate absolute barometric pressure sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pressure5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pressure5_cfg_setup ( pressure5_cfg_t *cfg ); 
 
- Initialization function.
> PRESSURE5_RETVAL pressure5_init ( pressure5_t *ctx, pressure5_cfg_t *cfg );

- Click Default Configuration function.
> void pressure5_default_cfg ( pressure5_t *ctx );


#### Example key functions :

- This function allows you to update the calibration coefficient.
> void pressure5_update_coefficient(pressure5_t *ctx);
 
- This function gets temperature in Celsius.
> float pressure5_get_temperature_data(pressure5_t *ctx);


- This function gets pressure in mBar.
> float pressure5_get_pressure_data(pressure5_t *ctx);

## Examples Description

> This example performs temperature & pressure measurement every 2 seconds.

**The demo application is composed of two sections :**

### Application Init 

> Initialize driver init, test comunication, software reset, update
> coefficient and configuration module for start measurement.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure5_cfg_t cfg;
    uint8_t tmp;
    PRESSURE5_RETVAL init_ret;

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

    pressure5_cfg_setup( &cfg );
    PRESSURE5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure5_init( &pressure5, &cfg );
    pressure5_default_cfg( &pressure5 );
}
  
```

### Application Task

> Reads Pressure data in [mBar] and Temperature data in [C] and logs data every seconds.

```c

void application_task ( void )
{
    //  Task implementation.

    temperature = pressure5_get_temperature_data( &pressure5 );
    log_printf( &logger, "Temperature: %.2f C\r\n", temperature );
    pressure = pressure5_get_pressure_data( &pressure5 );
    log_printf( &logger, "Pressure: %.2f mBar\r\n ", pressure );
    log_printf( &logger, "\r\n" );
    
    Delay_ms( 1000 );
}


```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure5

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
