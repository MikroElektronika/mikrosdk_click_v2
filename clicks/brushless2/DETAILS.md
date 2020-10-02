
---
# Brushless 2 click

Brushless 2 click carries the DRV10964 BLDC motor controller with an integrated output stage.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/brushless2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/brushless-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Brushless2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void brushless2_cfg_setup ( brushless2_cfg_t *cfg ); 
 
- Initialization function.
> BRUSHLESS2_RETVAL brushless2_init ( brushless2_t *ctx, brushless2_cfg_t *cfg );

#### Example key functions :

- Set the direction of rotation in the counterclockwise direction function
> void brushless2_counter_clockwise ( brushless2_t *ctx );
 
- Set the direction of rotation in the clockwise direction function
> void brushless2_clockwise ( brushless2_t *ctx );

- Get Interrupt pin state function
> uint8_t brushless2_get_interrupt_status ( brushless2_t *ctx );

## Examples Description

> This application controlled speed motor.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - GPIO,
> PWM initialization, set PWM duty cycle and PWM frequency, start PWM, enable the engine, 
> and start write log.
```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    brushless2_cfg_setup( &cfg );
    BRUSHLESS2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless2_init( &brushless2, &cfg );

    brushless2_set_duty_cycle( &brushless2, duty_cycle );
    brushless2_pwm_start( &brushless2 );
    Delay_1sec( );
    log_printf( &logger, "--------------------- \r\n" );
}
  
```

### Application Task

> This is a example which demonstrates the use of Brushless 2 Click board.
> Brushless 2 Click communicates with register via PWM interface.
> It acceleration and slowing down in the counter clockwise direction of rotation ( CCW ).
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    brushless2_counter_clockwise( &brushless2 );

    log_printf( &logger, "  Counterclockwise    \r\n" );
    log_printf( &logger, "--------------------- \r\n" );
    log_printf( &logger, "    acceleration      \r\n" );
    Delay_1sec( );
    
    for ( duty_cycle = 500; duty_cycle < 3000; duty_cycle += 250 )
    {
        brushless2_set_duty_cycle ( &brushless2, duty_cycle );
        log_printf( &logger," > \r\n" );
        Delay_1sec( );
        Delay_1sec( );
        Delay_1sec( );
    }

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    slowing down     \r\n" );
    Delay_1sec( );

    for ( duty_cycle = 3000; duty_cycle > 500; duty_cycle -= 250 )
    {
        brushless2_set_duty_cycle ( &brushless2, duty_cycle );
        log_printf( &logger," < \r\n" );
        Delay_1sec( );
        Delay_1sec( );
        Delay_1sec( );
    }

    log_printf( &logger,  "--------------------- \r\n" ); 
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless2

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
