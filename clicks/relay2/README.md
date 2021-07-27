\mainpage Main Page
 
 

---
# Relay 2 click

Relay 2 click is a dual relay click board™, equipped with two single-pole solid state relays (SSR), built with the patented OptoMOS® technology.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/relay2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/relay-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Relay2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Relay2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void relay2_cfg_setup ( relay2_cfg_t *cfg ); 
 
- Initialization function.
> RELAY2_RETVAL relay2_init ( relay2_t *ctx, relay2_cfg_t *cfg );

#### Example key functions :

- Config Object Initialization function.
> This function initializes click configuration structure to init state.
 
- Initialization function.
> his function initializes all necessary pins and peripherals used for this       click.

- Click Default Configuration function.
> This function executes default configuration for Relay 2 click.

- relay2_relay2Control
> Controls the Relay 2 pin

- relay2_relay2Control
> Controls the Relay 1 pin

## Examples Description

> The application is composed of three sections :

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    relay2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    relay2_cfg_setup( &cfg );
    RELAY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    relay2_init( &relay2, &cfg );
    log_info( &logger, "---- App Init Done ----" );
}
```

### Application Task

> Turns relays on and off.

```c
void application_task ( void )
{
    relay2_relay2_control(&relay2, 1 );
    relay2_relay1_control(&relay2, 1 );
    
    Delay_ms( 1000 );
    
    relay2_relay2_control(&relay2, 0 );
    relay2_relay1_control(&relay2, 0 );
    
    Delay_ms( 1000 );

}  
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Relay2

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
