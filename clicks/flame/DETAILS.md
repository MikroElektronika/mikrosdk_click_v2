
# FLAME click

> Flame click is a fire detection solution. It carries a PT334-6B silicon phototransistor that’s covered in black epoxy and therefore sensitive only to infrared light.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flame_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/flame-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Flame Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Flame Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void flame_cfg_setup ( flame_cfg_t *cfg ); 
 
- Initialization function.
> FLAME_RETVAL flame_init ( flame_t *ctx, flame_cfg_t *cfg );

#### Example key functions :

- Check the flame status function.
> uint8_t flame_check_status ( flame_t *ctx );
 
- Get interrupt status.
> uint8_t flame_get_interrupt ( flame_t *ctx );

## Examples Description

> This application detects fire.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - GPIO and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    flame_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    flame_cfg_setup( &cfg );
    FLAME_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flame_init( &flame, &cfg );
}

```

### Application Task


> This is a example which demonstrates the use of Flame Click board. 

```c

void application_task ( void )
{
    //  Task implementation.

    flame_state = flame_check_status ( &flame );

    if ( ( flame_state == 1 ) && ( flame_state_old == 0) )
    {
        log_printf( &logger, "  ~  FLAME   ~ \r\n " );
       
        flame_state_old = 1;
    }

    if ( ( flame_state == 0 ) && ( flame_state_old == 1 ) )
    {
        log_printf( &logger, "   NO FLAME  \r\n " );
        flame_state_old = 0;
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Flame

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
