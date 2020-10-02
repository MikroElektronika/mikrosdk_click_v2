
 

---
# ProxFusion click

ProxFusion click is a multifunctional capacitive and Hall-effect sensor device. This click can detect touch by using two onboard sensor pads, and it can sense a rotation angle of a magnetic field, parallel with the surface of the click board.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proxfusion_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/proxfusion-click>)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the ProxFusion Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ProxFusion Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proxfusion_cfg_setup ( proxfusion_cfg_t *cfg ); 
 
- Initialization function.
> PROXFUSION_RETVAL proxfusion_init ( proxfusion_t *ctx, proxfusion_cfg_t *cfg );

- Click Default Configuration function.
> void proxfusion_default_cfg ( proxfusion_t *ctx );


#### Example key functions :

- Touch event
> uint8_t proxfusion_get_touch ( proxfusion_t *ctx );
 
- Sets system register
> void proxfusion_set_system_reg ( proxfusion_t *ctx, uint8_t cfg );

- Selecting events
> void proxfusion_set_event_reg ( proxfusion_t *ctx, uint8_t cfg );

## Examples Description

> This demo-app reads and displays touch events using ProxFusion click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    proxfusion_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    proxfusion_cfg_setup( &cfg );
    PROXFUSION_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proxfusion_init( &proxfusion, &cfg );

    proxfusion_default_cfg( &proxfusion );
    Delay_ms( 1500 );
    log_info( &logger, "- It waits for a new touch press event. " );
} 
```

### Application Task

> Checks if a new touch event occurred and prints(logs) event message on usbuart.

```c
void application_task ( void )
{
    uint8_t touch;

    //  Task implementation.

    touch = proxfusion_get_touch( &proxfusion );

    if ( ( touch == 1 ) || ( touch == 2 ) )
    {
        log_printf( &logger, "** Touch %d is pressed..\r\n", touch );
    }
    else if ( touch == 3 )
    {
        log_printf( &logger, "** All the touch is pressed..\r\n" );
    }

    Delay_100ms();
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ProxFusion

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
