\mainpage Main Page
 
---
# RNG click

RNG Click is a random number generator (RNG) is a device that generates a sequence of numbers or symbols that cannot be reasonably predicted better than by a random chance. This Click board™ is true hardware random-number generator (HRNG), which generate genuinely random numbers.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](https://www.mikroe.com/rng-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Rng Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rng Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rng_cfg_setup ( rng_cfg_t *cfg ); 
 
- Initialization function.
> RNG_RETVAL rng_init ( rng_t *ctx, rng_cfg_t *cfg );

- Click Default Configuration function.
> void rng_default_cfg ( rng_t *ctx );


#### Example key functions :

- This function gets voltage in millivolts.
> float rng_get_voltage ( rng_t *ctx );
 
- This function sets configuration.
> void rng_set_config ( rng_t *ctx, uint16_t conf_data );

- This function sets desired vref.
> void rng_set_vref ( rng_t *ctx, uint16_t vref_mv );

## Examples Description

> This click is a random number generator. The device contain potentiometer which control voltage
> so it generates a sequence of numbers or symbols that cannot be reasonably predicted better 
> by a random chance. Random number generators have applications in gambling, statistical sampling,
> computer simulation, cryptography, completely randomized design, and various other areas. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver, set configuration and voltage reference. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rng_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rng_cfg_setup( &cfg );
    RNG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rng_init( &rng, &cfg );

    rng_default_cfg( &rng );
}
  
```

### Application Task

> Measures voltage every seconds.

```c

void application_task ( void )
{
    float voltage;

    voltage = rng_get_voltage( &rng );

    log_printf( &logger, "Voltage value: %.2f mV\r\n", voltage );
    log_printf( &logger, "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \r\n" );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rng

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
