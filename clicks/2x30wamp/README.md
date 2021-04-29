\mainpage Main Page
 
 
---
# 2x30W Amp click

2x30W Amp click is a class-D audio amplifier with a tremendous output power, considering its size and lack of huge heatsinks, usually associated with the audio amplifiers. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/2x30wamp_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/2x30w-amp-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the c2x30wAmp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for c2x30wAmp Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c2x30wamp_cfg_setup ( c2x30wamp_cfg_t *cfg ); 
 
- Initialization function.
> C2X30WAMP_RETVAL c2x30wamp_init ( c2x30wamp_t *ctx, c2x30wamp_cfg_t *cfg );

#### Example key functions :

- Device Enable function
> void c2x30wamp_enable ( c2x30wamp_t *ctx, uint8_t state );
 
- Device Mute function
> void c2x30wamp_mute ( c2x30wamp_t *ctx, uint8_t state );

- Diagnostic Check function
> uint8_t c2x30wamp_check_diagnostic ( c2x30wamp_t *ctx );

## Examples Description

> This application is audio amplifier.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO driver and enables the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c2x30wamp_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    c2x30wamp_cfg_setup( &cfg );
    C2X30WAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c2x30wamp_init( &c2x30wamp, &cfg );

    c2x30wamp_enable( &c2x30wamp, C2X30WAMP_ENABLE );
    log_printf( &logger, "2x30W AMP is initialized \r\n" );
    Delay_ms( 200 );
}
  
```

### Application Task

> Mute output for a period of 3 seconds, then keep it unmuted for a period of 10 seconds. 
> After that, checks if over current fault, over temperature fault or too high DC offset fault occurred.

```c

void application_task ( void )
{
    c2x30wamp_mute( &c2x30wamp, C2X30WAMP_MUTE );
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "MUTE \r\n" );
    Delay_ms( 3000 );
    c2x30wamp_mute( &c2x30wamp, C2X30WAMP_UNMUTE );
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "UNMUTE \r\n" );
    Delay_ms( 10000 );

    uint8_t fault_check = c2x30wamp_check_diagnostic( &c2x30wamp );

    if ( fault_check == 0 )
    {
        log_printf( &logger, "Fault condition! \r\n" );
    }
} 

```

## Note

> When under or over voltage condition occurres the output goes to high impedance state,
> but the FAULT pin will not be asserted.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.c2x30wAmp

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
