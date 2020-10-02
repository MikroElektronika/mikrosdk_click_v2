\mainpage Main Page
 
---
# DC MOTOR 14 click

DC MOTOR 14 Click is a PWM chopper type brushed DC motor driver, labeled as TB67H450FNG.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](< https://www.mikroe.com/dc-motor-14-click > )

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Dcmotor14 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dcmotor14 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor14_cfg_setup ( dcmotor14_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR14_RETVAL dcmotor14_init ( dcmotor14_t *ctx, dcmotor14_cfg_t *cfg );

#### Example key functions :

- Set an pin state function.
> void dcmotor14_set_an_state ( dcmotor14_t *ctx, uint8_t state );
 
- Set rst pin state function.
> dcmotor14_set_rst_state ( dcmotor14_t *ctx, uint8_t state );

- Stop function.
> void dcmotor14_stop ( dcmotor14_t *ctx );

## Examples Description

> This IC includes one channel of motor output block, using a wide range of supply voltages, while delivering reasonably high current to the connected DC motors.  

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO driver and starts log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor14_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    dcmotor14_cfg_setup( &cfg );
    DCMOTOR14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor14_init( &dcmotor14, &cfg );
}
  
```

### Application Task

>  This example demonstrates the use of DC Motor 14 click by driving it forward motion for 5 seconds, than applying brakes it for 2 second, and then driving it in reverse for 5 seconds, after that, it stops for 2 second.

```c

void application_task ( void )
{
    log_printf( &logger, "The motor turns forward! \r\n" );
    dcmotor14_forward( &dcmotor14 );
    Delay_ms( 5000 );
    log_printf( &logger, "The motor brakes! \r\n" );
    dcmotor14_brake( &dcmotor14 );
    Delay_ms( 2000 );
    log_printf( &logger, "The motor turns in reverse \r\n" );
    dcmotor14_reverse( &dcmotor14 );
    Delay_ms( 5000 );
    log_printf( &logger, "The motor stops \r\n" );
    dcmotor14_stop( &dcmotor14 );
    Delay_ms( 2000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dcmotor14

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
