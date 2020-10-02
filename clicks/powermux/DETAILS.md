
---
# Power MUX click

Power MUX Click features power multiplexer that enables transition between two power supplies (such as a battery and a wall adapter), each operating at 2.8V to 5.5V and delivering up to 2A current depending on the package. This IC provides inrush current control and thermal protection to Power MUX Click, manual and auto-switching operating modes, cross-conduction blocking, and reverse-conduction blocking. Operating mode selection depends on a logic level on D0 and D1 pins.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](https://www.mikroe.com/power-mux-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the PowerMux Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for PowerMux Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void powermux_cfg_setup ( powermux_cfg_t *cfg ); 
 
- Initialization function.
> POWERMUX_RETVAL powermux_init ( powermux_t *ctx, powermux_cfg_t *cfg );


#### Example key functions :

- Function is used to disable output.
> void powermux_no_output ( powermux_t *ctx );
 
- Function is used to set the state of D0 pin.
> void powermux_set_d0 ( powermux_t *ctx, uint8_t state );

- Function is used to set the state of D1 pin.
> void powermux_set_d1 ( powermux_t *ctx, uint8_t state );

## Examples Description

> This Click features power multiplexer that enables transition between two power supplies, 
> each operating at 2.8V to 5.5V and delivering up to 2A current depending on the package. 

**The demo application is composed of two sections :**

### Application Init 

> Enables GPIO and starts write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    powermux_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----");

    //  Click initialization.

    powermux_cfg_setup( &cfg );
    POWERMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    powermux_init( &powermux, &cfg );
}
  
```

### Application Task

> This example demonstrates the use of POWER MUX 
>  click board by disabling output tor 2 seconds, then enabling
>  output from channel 1 for 5 seconds then disabling output 
>  for 2 seconds again, and repeating for output from channel 2.

```c

void application_task ( void )
{
    log_printf( &logger, "No output\r\n" );
    powermux_no_output( &powermux );
    Delay_ms( 2000 );
    log_printf( &logger, "Output from input channel 1\r\n" );
    powermux_output_input_ch_1( &powermux );
    Delay_ms( 5000 );
    log_printf( &logger, "No output\r\n" );
    powermux_no_output( &powermux );
    Delay_ms( 2000 );
    log_printf( &logger, "Output from input channel 2\r\n" );
    powermux_output_input_ch_2( &powermux );
    Delay_ms( 5000 );
    log_printf( &logger, "No output\r\n" );
    powermux_no_output( &powermux );
    Delay_ms( 2000 );
    log_printf( &logger, "auto select output channel\r\n" );
    powermux_auto_sel_input_ch( &powermux );
    Delay_ms( 5000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerMux

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
