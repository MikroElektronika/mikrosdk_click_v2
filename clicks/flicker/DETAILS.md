
# Flicker click

FLICKER click is the perfect, simple solution if you need to turn a device on and off at specific time intervals, like blinking LED commercials,alarm system lights, or any other signalling lights.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flicker_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/flicker-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Flicker Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Flicker Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void flicker_cfg_setup ( flicker_cfg_t *cfg ); 
 
- Initialization function.
> FLICKER_RETVAL flicker_init ( flicker_t *ctx, flicker_cfg_t *cfg );

- Click Default Configuration function.
> void flicker_default_cfg ( flicker_t *ctx );


#### Example key functions :

- Flicker engage function.
> void flicker_engage ( flicker_t *ctx );

## Examples Description

> This application simple solution if you need to turn a device on and off at specific time intervals. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables GPIO and also starts write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    flicker_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    flicker_cfg_setup( &cfg );
    FLICKER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flicker_init( &flicker, &cfg );
}
  
```

### Application Task

> This example demonstrates capabilities of Flicker Click board.

```c

void application_task ( void )
{
    log_printf( &logger, " *Flicker on!* r/n/" );
    flicker_engage( &flicker );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Flicker

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
