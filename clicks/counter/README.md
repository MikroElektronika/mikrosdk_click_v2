\mainpage Main Page
 
 

---
# Counter click

Counter click carries an LS7366R 32-bit quadrature counter. The top of the board has a pinout for interfacing with incremental encoders. The interface has ENCA and ENCB pins, along with ENCI, which is a programmable index.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/counter_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/counter-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Counter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Counter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void counter_cfg_setup ( counter_cfg_t *cfg ); 
 
- Initialization function.
> COUNTER_RETVAL counter_init ( counter_t *ctx, counter_cfg_t *cfg );

- Click Default Configuration function.
> void counter_default_cfg ( counter_t *ctx );


#### Example key functions :

- This function reads CNTR, using click object.
> uint8_t counter_read_cntr ( counter_t *ctx );
 
- This function reads STR, using click object.
> uint8_t counter_read_str ( counter_t *ctx );

- This function reads OTR, using click object.
> uint8_t counter_read_otr ( counter_t *ctx );

## Examples Description

> Measuring RPM and speed of DC motor shafts


**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and chip init


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    counter_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    counter_cfg_setup( &cfg );
    COUNTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    counter_init( &counter, &cfg );

    counter_default_cfg( &counter );
    Delay_ms( 300 );
}
  
```

### Application Task

> This application reads data from CNTR.
> The CNTR is a software configurable 8, 16, 24 or 32-bit up/down counter which
> counts the up/down pulses resulting from the quadrature clocks applied at the
> A and B inputs, or alternatively, in non-quadrature mode, pulses applied at the A input.


```c

void application_task ( void )
{
    count = counter_read_cntr( &counter );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Counter

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
