 
---
# Buck 8 click

Buck 8 click is a high efficiency, wide voltage range, and high current synchronous step down (buck) DC-DC converter, featuring two enhanced modes that can be used to drive lighter loads with increased efficiency. 

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/buck8_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/buck-8-click>)

---


#### Click library 

- **Author**        : Kaarina Perendic
- **Date**          : nov 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Buck8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buck8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck8_cfg_setup ( buck8_cfg_t *cfg ); 
 
- Initialization function.
> BUCK8_RETVAL buck8_init ( buck8_t *ctx, buck8_cfg_t *cfg );

- Click Default Configuration function.
> void buck8_default_cfg ( buck8_t *ctx );


#### Example key functions :

- Get state of pin
> uint8_t buck8_get_state ( buck8_t *ctx );
 
- Function settings mode 
> void buck8_set_power_mode ( buck8_t *ctx, uint8_t mode );

## Examples Description

> Demo application shows basic usage of BUCK 8 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck8_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck8_cfg_setup( &cfg );
    BUCK8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck8_init( &buck8, &cfg );

    buck8_default_cfg( &buck8 );
}
```

### Application Task

> Logs the message to USBUART if the voltase is greater 
> than the maximum setpoint value.

```c
void application_task ( void )
{
    uint8_t pg_state;

    //  Task implementation.
    
    pg_state = buck8_get_state( &buck8 );
    if ( pg_state != 0 )
    {
        log_info( &logger, "---- Max range !!! ----" );
    }
    Delay_1sec();
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck8

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
