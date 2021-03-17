\mainpage Main Page
 
---
# Brushless 5 click

Brushless 5 click is a 3 phase sensorless BLDC motor controller, with a soft-switching feature for reduced motor noise and EMI, and precise BEMF motor sensing, which eliminates the need for Hall-sensors in motor applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Brushless5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void brushless5_cfg_setup ( brushless5_cfg_t *cfg ); 
 
- Initialization function.
> BRUSHLESS5_RETVAL brushless5_init ( brushless5_t *ctx, brushless5_cfg_t *cfg );

#### Example key functions :

- Generic sets PWM duty cycle.
> void brushless5_set_duty_cycle ( brushless5_t *ctx, float duty_cycle );
 
- Stop PWM module.
> void brushless5_pwm_stop ( brushless5_t *ctx );

- Start PWM module.
> void brushless5_pwm_start ( brushless5_t *ctx );

## Examples Description

> This application demonstrates the use of Brushless 5 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the GPIO driver and configures the PWM peripheral for controlling the speed of the motor. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    brushless5_cfg_setup( &cfg );
    BRUSHLESS5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless5_init( &brushless5, &cfg );

    brushless5_pwm_start( &brushless5 );
}
  
```

### Application Task

> Increases and decreases the speed of the motor demonstrating the speed control.

```c

void application_task ( void )
{
    log_printf( &logger, " Increasing the motor speed... \r\n" );
    
    for ( duty_cycle = 0.1; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        brushless5_set_duty_cycle ( &brushless5, duty_cycle );
        log_printf( &logger," > " );
        Delay_ms( 500 );
    }

    log_printf( &logger,  "\r\n ---------------------- \r\n" ); 
    log_printf( &logger, " Slowing down... \r\n" );
    
    for ( duty_cycle = 1.0; duty_cycle > 0.09; duty_cycle -= 0.1 )
    {
        brushless5_set_duty_cycle ( &brushless5, duty_cycle );
        log_printf( &logger," < " );
        Delay_ms( 500 );
    }
    log_printf( &logger,  "\r\n ---------------------- \r\n" ); 
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless5

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
