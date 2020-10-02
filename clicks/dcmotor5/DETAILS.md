 
---
# DC MOTOTR 5 click

DC MOTOR 5 click carries the DRV8701 brushed DC motor gate driver from Texas Instruments.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/dcmotor5_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/dc-motor-5-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the DcMotor5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DcMotor5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor5_cfg_setup ( dcmotor5_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR5_RETVAL dcmotor5_init ( dcmotor5_t *ctx, dcmotor5_cfg_t *cfg );

- Click Default Configuration function.
> void dcmotor5_default_cfg ( dcmotor5_t *ctx );


#### Example key functions :

- Function brakes the engine by sets IN1 ( PWM ) and IN2 ( INT ) pins on DC Motor 5 Click board.
> void dcmotor5_short_brake ( dcmotor5_t *ctx );
 
- Function stops the engine by clearing IN1 ( PWM ) and IN2 ( INT ) pins on DC Motor 5 Click board.
> void dcmotor5_stop ( dcmotor5_t *ctx );

- Function disables the engine by clearing SLEEP ( RST ) pin on DC Motor 5 Click board.
> void dcmotor5_enable ( dcmotor5_t *ctx );

## Examples Description

> This applciation enables usage of brushed DC motor gate driver.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - GPIO,
> PWM initialization, set PWM duty cycle and PWM frequency, start PWM, enable the engine,
> and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor5_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor5_cfg_setup( &cfg );
    DCMOTOR5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor5_init( &dcmotor5, &cfg );

    dcmotor5_pwm_start( &dcmotor5 );

    log_printf( &logger, "---------------------\r\n" );

    log_printf( &logger, "  Enable the engine  \r\n" );

    dcmotor5_enable( &dcmotor5 );

    Delay_1sec( );

    log_printf( &logger, "---------------------\r\n" );
}
  
```

### Application Task

> This is a example which demonstrates the use of DC Motor 5 Click board. 
> DC Motor 5 Click communicates with register via PWM interface. 
> It shows moving in the clockwise direction of rotation from slow to fast speed
> and moving in the counter clockwise direction of rotation from fast to slow speed.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    //  Task implementation.
  
    log_printf( &logger, "   Brake the engine  \r\n" );
    dcmotor5_short_brake( &dcmotor5 );
    Delay_1sec( );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "      Clockwise      \r\n" );
    dcmotor5_clockwise( &dcmotor5 );
    Delay_1sec( );

    for ( duty_cycle = 500; duty_cycle < 3000; duty_cycle += 250 )
    {
        dcmotor5_set_duty_cycle( &dcmotor5, duty_cycle );
        log_printf( &logger, " >" );
        Delay_1sec( );
    }

    log_printf( &logger, "\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   Brake the engine  \r\n" );
    dcmotor5_short_brake( &dcmotor5 );
    Delay_1sec( );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Counter Clockwise  \r\n" );
    dcmotor5_counter_clockwise( &dcmotor5 );
    Delay_1sec( );

    for ( duty_cycle = 3000; duty_cycle > 500; duty_cycle -= 250 )
    {
        dcmotor5_set_duty_cycle( &dcmotor5, duty_cycle );
        log_printf( &logger, " <" );
        Delay_1sec( );
    }

    log_printf( &logger, "\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    dcmotor5_stop( &dcmotor5 );
    Delay_1sec( );

}

```
 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor5

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