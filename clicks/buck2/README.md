\mainpage Main Page
  
---
# Buck 2 click

Buck 2 click is a powerful step down DC-DC switching regulator. It gives a high precision regulated voltage at its output and it can handle an ample amount of current.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/buck2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/buck-2-click>)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Buck2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buck2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck2_cfg_setup ( buck2_cfg_t *cfg ); 
 
- Initialization function.
> BUCK2_RETVAL buck2_init ( buck2_t *ctx, buck2_cfg_t *cfg );

- Click Default Configuration function.
> void buck2_default_cfg ( buck2_t *ctx );


#### Example key functions :

- Function settings output voltage
> void buck2_set_output_voltage ( buck2_t *ctx , uint8_t voltage );
 
- Function reads state PG pin
> uint8_t buck2_get_power_good ( buck2_t *ctx  );

- Function settings chip mode
> void buck2_set_power_mode ( buck2_t *ctx, uint8_t mode );

## Examples Description

> The demo application displays output voltage change.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck2_cfg_setup( &cfg );
    BUCK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck2_init( &buck2, &cfg );

    buck2_default_cfg( &buck2 );
}
```

### Application Task

> Sets a different range of input voltages 
> every 2 s and checks if it has reached the set output voltage.

```c
void application_task ( void )
{
    uint8_t pg_state;

    pg_state = buck2_get_power_good( &buck2 );
    if ( pg_state != 0 )
    {
        log_info( &logger, "---- Power good output voltage ----" );
    }

    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_3300mV );
    Delay_ms( 3000 );
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_2500mV );
    Delay_ms( 3000 );
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_1800mV );
    Delay_ms( 3000 );
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_1500mV );
    Delay_ms( 3000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck2

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
