\mainpage Main Page
 
 

---
# DC MOTOR 7 click

DC MOTOR 7 click is a dual brushed DC motor driving Click board™, featuring the advanced PWM chopper-type integrated DC motor driver, labeled as TB67H400AFTG.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/dcmotor7_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/dc-motor-7-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the DcMotor7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DcMotor7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor7_cfg_setup ( dcmotor7_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR7_RETVAL dcmotor7_init ( dcmotor7_t *ctx, dcmotor7_cfg_t *cfg );

- Default Configuration 
> void dcmotor7_default_cfg ( dcmotor7_t *ctx );

#### Example key functions :

- Functions for set port
> void dcmotor7_set_port ( dcmotor7_t *ctx, uint8_t port, uint8_t value );
 
- Function for setting the motor in stand mode
> void dcmotor7_go_to_stand_by_mode ( dcmotor7_t *ctx, uint8_t motor );

- Function for set PWM value for motor B
> void dcmotor7_set_pwm_motor_b ( dcmotor7_t *ctx, uint8_t state );

## Examples Description

> This application is a dual brushed DC motor driving.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init, enabled all output port, sets H-Bridge operation mode and Motor Digital tblk

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor7_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor7_cfg_setup( &cfg );
    DCMOTOR7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor7_init( &dcmotor7, &cfg );

    dcmotor7_default_cfg( &dcmotor7 );
}
  
```

### Application Task

> Set the motor A and the motor B to rotate clockwise and in the Counte clockwise direction, 
> and between the change of direction, the motor stops the motor. 

```c

void application_task ( void )
{
    dcmotor7_set_motor( &dcmotor7, DCMOTOR7_MOTOR_A, 0, 1 );
    dcmotor7_set_motor( &dcmotor7, DCMOTOR7_MOTOR_B, 0, 1 );
    Delay_ms( 500 );
    
    dcmotor7_motor_stop( &dcmotor7, DCMOTOR7_MOTOR_A );
    dcmotor7_motor_stop( &dcmotor7, DCMOTOR7_MOTOR_B );
    Delay_ms( 2000 );
    
    dcmotor7_set_motor( &dcmotor7, DCMOTOR7_MOTOR_A, 1, 0 );
    dcmotor7_set_motor( &dcmotor7, DCMOTOR7_MOTOR_B, 1, 0 );
    Delay_ms( 500 );
    
    dcmotor7_motor_stop( &dcmotor7, DCMOTOR7_MOTOR_A );
    dcmotor7_motor_stop( &dcmotor7, DCMOTOR7_MOTOR_B );
    Delay_ms( 2000 );
} 

```

## Note

> VM input - 10 V (min) to 47 V (max)

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor7

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
