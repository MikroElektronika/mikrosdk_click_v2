
---
# Motion 4 click

Motion 4 Click is a long distance PaPIR's motion sensor with plastic lense and controllable output. This Click board features EKMC1603111, a PIR motion sensor from Panasonic Corporation which can be used as human motion detector and is able to detect movement up to 12m with 170uA current consumption.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](https://www.mikroe.com/motion-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Motion4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Motion4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void motion4_cfg_setup ( motion4_cfg_t *cfg ); 
 
- Initialization function.
> MOTION4_RETVAL motion4_init ( motion4_t *ctx, motion4_cfg_t *cfg );

#### Example key functions :

- This function for reading int pin status.
> uint8_t motion4_get_int ( motion4_t *ctx );

## Examples Description

> This application motion detector sensitive only to live bodies.

**The demo application is composed of two sections :**

### Application Init 

> Maps pins and enables device

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    motion4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    motion4_cfg_setup( &cfg );
    MOTION4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    motion4_init( &motion4, &cfg );
}
  
```

### Application Task

> Waiting for motion to be detected

```c

void application_task ( void )
{
    uint8_t int_status;

    int_status = motion4_get_int( &motion4 );

    if ( int_status != MOTION4_INTERRUPT_NOT_DETECT )
    {
        log_printf( &logger, "Motion detected\r\n" );
        while ( int_status != MOTION4_INTERRUPT_NOT_DETECT )
        {
            int_status = motion4_get_int( &motion4 );
        }
       log_printf( &logger, "Motion wait \r\n" );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Motion4

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
