\mainpage Main Page
 
---
# Brushless 6 click

Brushless 6 click is designed to drive a three-phase sensorless, brushless motor, also known as the BLDC motor.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/brushless6_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/brushless-6-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Brushless6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void brushless6_cfg_setup ( brushless6_cfg_t *cfg ); 
 
- Initialization function.
> BRUSHLESS6_RETVAL brushless6_init ( brushless6_t *ctx, brushless6_cfg_t *cfg );

- Click Default Configuration function.
> void brushless6_default_cfg ( brushless6_t *ctx );


#### Example key functions :

- Start PWM module.
> void brushless4_pwm_start ( brushless4_t *ctx );
 
- Stop PWM module.
> void brushless4_pwm_stop ( brushless4_t *ctx );

- Generic sets PWM duty cycle.
> void brushless4_set_duty_cycle ( brushless4_t *ctx, pwm_data_t duty_cycle );

## Examples Description

> Brushless 6 click is designed to drive a three-phase sensorless.

**The demo application is composed of two sections :**

### Application Init 

>Intializes PWM module but also and Brushless click by executing intialization prodecure.

```c

void application_init ( void )
void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless6_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    brushless6_cfg_setup( &cfg );
    BRUSHLESS6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless6_init( &brushless6, &cfg );

    brushless6_pwm_start( &brushless6 );

}
  
```

### Application Task

>Periodicaly changes the motor speed using PWM module but also log current setting to UART.

```c

void application_task ( void )
{
    //  Task implementation.
    
    if ( duty_cycle > brushless6.pwm_period )
    {
        duty_cycle = 100;
    }
    
    brushless6_set_duty_cycle ( &brushless6, duty_cycle );
    duty_cycle += 50;
    Delay_100ms();

    brushless6_setMotor( BRUSHLESS6_SPEED1 );
    log_printf( &logger, " Speed 1 \r\n" );
    log_printf( &logger, " 13 \r\n" );
    log_printf( &logger, " 10 \r\n" );
    Delay_ms( 1000 );
  

    brushless6_set_motor( BRUSHLESS6_CCW );
    log_printf( &logger, "Direction change \r\n" );
    log_printf( &logger, "13 \r\n" );
    log_printf( &logger, "10 \r\n" );
    Delay_ms( 1000 );

} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless6

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
