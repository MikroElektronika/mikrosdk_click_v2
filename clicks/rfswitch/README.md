\mainpage Main Page
 
---
# RF Switch click

RF Switch Click is a Click board™ equipped with the MASWSS0115, a GaAs PHEMT MMIC single-pole, double-throw (SPDT) switch developed by Macom for switching between small signal components such as filter banks, single-band LNAs, converters, etc. The MASWSS0115 is ideally suited for applications where a very small size and low cost are required.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rfswitch_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/rf-switch-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the RfSwitch Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for RfSwitch Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rfswitch_cfg_setup ( rfswitch_cfg_t *cfg ); 
 
- Initialization function.
> RFSWITCH_RETVAL rfswitch_init ( rfswitch_t *ctx, rfswitch_cfg_t *cfg );


#### Example key functions :

- The function switching signal to RF channel 1 or 2 of the RF Switch click board.
> void rfswitch_select_channel ( rfswitch_t *ctx, uint8_t select_channel );

## Examples Description

> This Click is a switch between small signal components such as filter banks, single-band LNAs,
> converters, etc. It can be used for low power, low loss requirements in all systems operating
> up to 3 GHz, including PCS, GSM, DCS, Bluetooth, and other receive chain applications.  

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - GPIO, sets CS and PWM pins as output 
> and initializes write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rfswitch_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    rfswitch_cfg_setup( &cfg );
    RFSWITCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rfswitch_init( &rfswitch, &cfg );

    selected_port = 1;
}
  
```

### Application Task

> This is a example which demonstrates the use of RF Switch Click board.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    if ( selected_port == 1 ) 
    {
        rfswitch_select_channel( &rfswitch, RFSWITCH_SELECT_CHANNEL_1 );
        log_printf( &logger, "  Switch to RF Port 1  \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
    }
    else if ( selected_port == 2 ) 
    {
        rfswitch_select_channel(  &rfswitch, RFSWITCH_SELECT_CHANNEL_2 );
        log_printf( &logger, "  Switch to RF Port 2  \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
    }
}

```
 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.RfSwitch

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
