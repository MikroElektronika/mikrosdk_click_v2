\mainpage Main Page
 
 

---
# Pressure 6 click

Pressure 6 Click features a simple, yet highly accurate and reliable pressure sensor labeled as BM1386GLV, produced by ROHM. This sensor is a piezo-resistive pressure sensor with internal thermal compensation, which greatly simplifies the pressure reading.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Pressure6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> The library initializes and defines the I2C bus driver and drivers that and  offers 
> a choice for writing data in register and read data from register.
> The library includes function for read Temperature and Pressure data.

#### Standard key functions :

- Config Object Initialization function.
> void pressure6_cfg_setup ( pressure6_cfg_t *cfg ); 
 
- Initialization function.
> PRESSURE6_RETVAL pressure6_init ( pressure6_t *ctx, pressure6_cfg_t *cfg );

- Click Default Configuration function.
> void pressure6_default_cfg ( pressure6_t *ctx );


#### Example key functions :

- This function gets the temperature data from the sensor.
> uint8_t pressure6_get_temperature( pressure6_t *ctx );
 
- This function turns the sensor on.
> void pressure6_power_on( pressure6_t *ctx );

- This function gets pressure data from the sensor.
> uint16_t pressure6_get_pressure( pressure6_t *ctx );

## Examples Description

> The example gets the pressure and temperature values from the sensors and logs on terminal.

**The demo application is composed of two sections :**

### Application Init 

> Driver initialization and powering ON procedure to wake up the sensor and seting up the measurement mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure6_cfg_t cfg;

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

    pressure6_cfg_setup( &cfg );
    PRESSURE6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure6_init( &pressure6, &cfg );
}
  
```

### Application Task

> Read Pressure data and Temperature data and logs data to USBUART every 1 sec.

```c

void application_task ( void )
{
    //  Task implementation.
    
    pressure6_waiting_for_new_data( &pressure6 );
    Pressure = pressure6_get_pressure( &pressure6 );
    Temperature = pressure6_get_temperature( &pressure6 );

    log_printf( &logger, "Pressure: %u\r\n", pressure);
    log_printf( &logger, "Temperature: %u\r\n", temperature);

    Delay_ms( 1000 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure6

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
