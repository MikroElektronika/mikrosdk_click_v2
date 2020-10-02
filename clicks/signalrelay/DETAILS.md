
 

---
# Signal Realy click

Signal Relay click can be used for ON/OFF control in various devices. It carries four ultra-small GV5-1 PCB relays from Omron and runs on a 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/signalrelay_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/signal-relay-click>)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the SignalRealy Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SignalRealy Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void signalrelay_cfg_setup ( signalrelay_cfg_t *cfg ); 
 
- Initialization function.
> SIGNALRELAY_RETVAL signalrelay_init ( signalrelay_t *ctx, signalrelay_cfg_t *cfg );

- Click Default Configuration function.
> void signalrelay_default_cfg ( signalrelay_t *ctx );


#### Example key functions :

- Relays state
> void signalrelay_relay_state( signalrelay_t *ctx, uint8_t relay, uint8_t state );

## Examples Description

> Demo application is used to shows basic controls Signal Relay click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration. 
 
```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    signalrelay_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----");

    //  Click initialization.

    signalrelay_cfg_setup( &cfg );
    SIGNALRELAY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    signalrelay_init( &signalrelay, &cfg );

    signalrelay_default_cfg ( &signalrelay );
}
  
```

### Application Task

> Alternately sets relays to ON-OFF state...

```c

void application_task ( void )
{
    uint8_t cnt;

    //  Task implementation.

    for ( cnt = 1; cnt <= 4; cnt++ )
    {
        log_info( &logger, " *** Relay [ %d ] ON ", cnt );
        signalrelay_relay_state( &signalrelay, cnt, SIGNALRELAY_STATE_ON );
        Delay_ms( 200 );
        log_info( &logger, " *** Relay [ %d ] OFF ", cnt );
        signalrelay_relay_state( &signalrelay, cnt, SIGNALRELAY_STATE_OFF );
        Delay_ms( 200 );
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.SignalRealy

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
