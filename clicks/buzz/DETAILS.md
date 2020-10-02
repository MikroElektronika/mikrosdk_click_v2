
---
# Buzz click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Aug 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Buzz Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buzz Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buzz_cfg_setup ( buzz_cfg_t *cfg ); 
 
- Initialization function.
> BUZZ_RETVAL buzz_init ( buzz_t *ctx, buzz_cfg_t *cfg );


#### Example key functions :

- This function play sound on buzzer.
> void buzz_play_sound ( buzz_t *ctx, uint16_t freq, uint8_t level, uint8_t duration );
 
- This function stop sound on buzzer.
> void buzz_stop_sound ( buzz_t *ctx );

## Examples Description

> 
>  Application demonstrates the use of BUZZ Click board and SDK 2 on the exemple using two additional functions that are coded to play different melodies.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initializes GPIO and LOG structures, set PWM pin as ouput and start write log.
> Initialization driver enable's - GPIO and configures the appropriate MCU pin for sound generation.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buzz_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buzz_cfg_setup( &cfg );
    BUZZ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buzz_init( &buzz, &cfg );

    buzz_pwm_start( &buzz );
}
  
```

### Application Task

>
> This is an example which demonstrates the use of BUZZ Click board
> 

```c

void application_task ( void )
{
   melody1_play( ); 
   Delay_1sec( );
   melody2_play( ); 
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buzz

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
