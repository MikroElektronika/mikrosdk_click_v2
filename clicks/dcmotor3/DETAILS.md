
---
# DC Motor 3 click

DC MOTOR 3 click is a mikroBUS™ add-on board with a Toshiba TB6549FG full-bridge driver for direct current motors. The IC is capable of outputting currents of up to 3.5 A with 30V, making it suitable for high-power motors

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/dcmotor3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/dc-motor-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the DcMotor3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DcMotor3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor3_cfg_setup ( dcmotor3_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR3_RETVAL dcmotor3_init ( dcmotor3_t *ctx, dcmotor3_cfg_t *cfg );

- Click Default Configuration function.
> void dcmotor3_default_cfg ( dcmotor3_t *ctx );


#### Example key functions :

- This function set the direction of rotation in the clockwise direction by sets AN pin and clear RST pin.
> void dcmotor3_clockwise ( dcmotor3_t *ctx );
 
- This function set the direction of rotation in the counter clockwise direction by clear AN pin and sets RST pin.
> void dcmotor3_counter_clockwise ( dcmotor3_t *ctx );

- This function brake the engine by sets AN and RST pins on DC Motor 3 Click board.
> void dcmotor3_short_brake ( dcmotor3_t *ctx );

## Examples Description

> This click  has four operating modes: clockwise, counter-clockwise, short brake and stop. 
> The operating mode is configured through IN1 and IN2 pins. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - GPIO,
> PWM initialization, set PWM duty cycle and PWM frequency, start PWM, enable the engine, and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor3_cfg_setup( &cfg );
    DCMOTOR3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor3_init( &dcmotor3, &cfg );

    dcmotor3_pwm_start( &dcmotor3 );
    Delay_1sec( );
    dcmotor3_enable( &dcmotor3 );
    Delay_1sec( );
}
  
```

### Application Task

> This is a example which demonstrates the use of DC Motor 3 Click board.
> DC Motor 3 Click communicates with register via PWM interface.
> It shows moving in the clockwise direction of rotation from slow to fast speed
> and moving in the counter clockwise direction of rotation from fast to slow speed.
> Results are being sent to the Usart Terminal where you can track their changes. 

```c

void application_task ( void )
{
    log_printf( &logger, "   Brake the engine  \r\n" );
    dcmotor3_short_brake( &dcmotor3 );
    Delay_1sec();

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "      Clockwise      \r\n" );
    dcmotor3_clockwise( &dcmotor3 );
    Delay_1sec();

    for ( duty_cycle = 500; duty_cycle <  dcmotor3.pwm_period; duty_cycle += 700 )
    {
        dcmotor3_set_duty_cycle ( &dcmotor3, duty_cycle );
        log_printf( &logger, " >" );
        Delay_1sec( );
    }

    log_printf( &logger, "\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   Brake the engine  \r\n" );
    dcmotor3_short_brake( &dcmotor3 );
    Delay_1sec( );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Counter Clockwise  \r\n" );
    dcmotor3_counter_clockwise( &dcmotor3 );
    Delay_1sec();
    
    for ( duty_cycle = dcmotor3.pwm_period; duty_cycle > 500; duty_cycle -= 700 )
    {
        dcmotor3_set_duty_cycle ( &dcmotor3, duty_cycle );
        log_printf( &logger, " <" );
        Delay_1sec( );
    }

    log_printf( &logger, "\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    dcmotor3_stop( &dcmotor3 );
    Delay_1sec();
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor3

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
