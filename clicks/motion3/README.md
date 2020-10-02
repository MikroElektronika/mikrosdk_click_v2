\mainpage Main Page
 
---
# Motion 3 click

Motion 3 Click is a Click board™ based on EKMC1606112, PIR motion sensor from Panasonic Corporation that's used as human motion detector. Also featured on Motion 3 Click bord is TLP241A photorelay from Toshiba that is used to provide a reinforced galvanic isolation for the external signals used to drive some external high power electronic equipment when motion is detected.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](https://www.mikroe.com/motion-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Motion3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Motion3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void motion3_cfg_setup ( motion3_cfg_t *cfg ); 
 
- Initialization function.
> MOTION3_RETVAL motion3_init ( motion3_t *ctx, motion3_cfg_t *cfg );

- Click Default Configuration function.
> void motion3_default_cfg ( motion3_t *ctx );


#### Example key functions :

- This function for reading int pin status.
> uint8_t motion3_get_int ( motion3_t *ctx );
 

## Examples Description

> This application motion detector sensitive only to live bodies.

**The demo application is composed of two sections :**

### Application Init 

> Maps pins and enables device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    motion3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    motion3_cfg_setup( &cfg );
    MOTION3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    motion3_init( &motion3, &cfg );
}
  
```

### Application Task

> Waiting for motion to be detected.

```c

void application_task ( void )
{
    uint8_t int_status;

    int_status = motion3_get_int( &motion3 );

    if ( int_status != MOTION3_INTERRUPT_NOT_DETECT )
    {
        log_printf( &logger, "Motion detected \r\n" );
        while ( int_status != MOTION3_INTERRUPT_NOT_DETECT )
        {
            int_status = motion3_get_int( &motion3 );
        }
        log_printf( &logger, "Motion wait \r\n" );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Motion3

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
