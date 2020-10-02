\mainpage Main Page
 
 

---
# Hall Switch click

Hall Switch click is a magnetic field activated dual-relay Click board™. Hall Switch click has two high-quality relays, which are activated by the Hall-effect sensor: when the north pole magnetic field is introduced to the sensor, one of the relays will be activated; when the south pole magnetic field is introduced to the sensor, the other relay will be activated.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallswitch_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/hall-switch-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the HallSwitch Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HallSwitch Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hallswitch_cfg_setup ( hallswitch_cfg_t *cfg ); 
 
- Initialization function.
> HALLSWITCH_RETVAL hallswitch_init ( hallswitch_t *ctx, hallswitch_cfg_t *cfg );

- Click Default Configuration function.
> void hallswitch_default_cfg ( hallswitch_t *ctx );


#### Example key functions :

- Function for turn on and turn off N Pole
> void hallswitch_set_npole ( hallswitch_t *ctx, uint8_t state );
 
-Function for turn on and turn off S Pole
> void hallswitch_set_spole ( hallswitch_t *ctx,uint8_t state );

## Examples Description

> The application sets sensor magnetic pole

**The demo application is composed of two sections :**

### Application Init 

> Initializes Driver init and turn OFF S pole and N pole

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallswitch_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    hallswitch_cfg_setup( &cfg );
    HALLSWITCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallswitch_init( &hallswitch, &cfg );

    hallswitch_set_npole( &hallswitch, HALLSWITCH_POLE_NO_ACTIVE );
    hallswitch_set_spole( &hallswitch, HALLSWITCH_POLE_NO_ACTIVE );
}
  
```

### Application Task

>  Turns S and N on and off every 500 msInitializes Driver init and turn OFF S pole and N pole

```c

void application_task()
{
    hallswitch_set_npole( &hallswitch, HALLSWITCH_POLE_ACTIVE );
    Delay_ms( 500 );
    hallswitch_set_spole( &hallswitch, HALLSWITCH_POLE_ACTIVE );
    Delay_ms( 500 );
    hallswitch_set_npole( &hallswitch, HALLSWITCH_POLE_NO_ACTIVE );
    Delay_ms( 500 );
    hallswitch_set_spole( &hallswitch, HALLSWITCH_POLE_NO_ACTIVE );
    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HallSwitch

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
