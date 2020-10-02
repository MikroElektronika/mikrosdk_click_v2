\mainpage Main Page
 
 

---
# Thermo 4  click

THERMO 4 click carries the LM75A digital temperature sensor and thermal watchdog. The sensor has the range from −55 °C to +125 °C.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo4_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/thermo-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo4_cfg_setup ( thermo4_cfg_t *cfg ); 
 
- Initialization function.
> THERMO4_RETVAL thermo4_init ( thermo4_t *ctx, thermo4_cfg_t *cfg );

- Click Default Configuration function.
> void thermo4_default_cfg ( thermo4_t *ctx );


#### Example key functions :

- This function reads temperature values in Celsius format.
> float thermo4_read_temperature_c ( thermo4_t *ctx );
 
- This function reads temperature values in Farenheit format.
> float thermo4_read_temperature_f ( thermo4_t *ctx );

- This function is used to reset the sensor.
> void thermo4_reset ( thermo4_t *ctx );

## Examples Description

> This demo example returns temperature values in three different format.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    
    //  Click initialization.
    
    thermo4_cfg_setup( &cfg );
    THERMO4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo4_init( &thermo4, &cfg );
    log_info( &logger, "---- Application Init ----" );
}
  
```

### Application Task

> Returns temperature values from the sensor.

```c

void application_task ( void )
{
    temp_in_celsius = thermo4_read_temperature_c( thermo4 );
    temp_in_faren = thermo4_read_temperature_f( thermo4 );
    temp_in_kelvin = thermo4_read_temperature_k( thermo );
    
    log_printf(" Temperature celsius : %f %c\r\n", temp_in_celsius, deg_cel);
    log_printf(" Temperature farenheit : %f %c\r\n", temp_in_faren, deg_far);
    log_printf(" Temperature kelvin : %f K\r\n", temp_in_kelvin);
    
    Delay_ms( 1000 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo4

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
