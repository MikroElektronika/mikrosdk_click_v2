\mainpage Main Page
 
---
# BATT-MAN click

BATT-MAN click is a very versatile battery operated power manager. When powered via mikroBUS™, it will charge the connected Li-Ion/Li-Po 3.7V battery, while providing the output voltage on all its outputs at the same time. The interesting feature of this device is that it can provide additional current to the connected load if the current provided from the mikroBUS™ socket is not enough.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](https://www.mikroe.com/batt-man-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : sep 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the BattMan Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BattMan Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void battman_cfg_setup ( battman_cfg_t *cfg ); 
 
- Initialization function.
> BATTMAN_RETVAL battman_init ( battman_t *ctx, battman_cfg_t *cfg );

- Click Default Configuration function.
> void battman_default_cfg ( battman_t *ctx );


#### Example key functions :

- Controls the operation of the click.
> void battman_set_enable ( battman_t *ctx, uint8_t state );
 

## Examples Description

> BATT-MAN click is a very versatile battery operated power manager. When powered via mikroBUS,
> it will charge the connected Li-Ion/Li-Po 3.7V battery, while providing the output voltage 
> on all its outputs at the same time.

**The demo application is composed of two sections :**

### Application Init 

> Initializes pin direction and logger utility and click driver. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    battman_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    battman_cfg_setup( &cfg );
    BATTMAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    battman_init( &battman, &cfg );
}
  
```

### Application Task

> Alternates between enabled and disabled state. 

```c

void application_task ( void )
{
    battman_set_enable( &battman, 1 );
    log_printf( &logger, "Click enabled.\r\n" );
    Delay_ms( 10000 );
    log_printf( &logger, "Click disabled.\r\n" );
    battman_set_enable( &battman, 0 );
    Delay_ms( 10000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BattMan

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
