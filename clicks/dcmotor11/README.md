\mainpage Main Page
 
 

---
# DC Motor 11 click

DC Motor 11 Click is a brushed DC motor driver with the current limiting and current sensing. It is based on the DRV8830, an integrated H-Bridge driver IC, optimized for motor driving applications.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/dcmotor11_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/dc-motor-11-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the DcMotor11 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DcMotor11 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor11_cfg_setup ( dcmotor11_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR11_RETVAL dcmotor11_init ( dcmotor11_t *ctx, dcmotor11_cfg_t *cfg );

#### Example key functions :

- Motor Control
> void dcmotor11_control ( dcmotor11_t *ctx, uint8_t dir, uint8_t speed );
 
- Get Fault
> uint8_t dcmotor11_get_fault ( dcmotor11_t *ctx );

- Interrupt state on the INT pin
> uint8_t dcmotor11_get_interrupt_state ( dcmotor11_t *ctx );

## Examples Description

> This application is motor driver with the current limiting and current sensing.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and sets first motor settings.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor11_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor11_cfg_setup( &cfg );
    DCMOTOR11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor11_init( &dcmotor11, &cfg );

   dcmotor11_get_fault( &dcmotor11 );
    
    /* Start settings */
    motor_dir = DCMOTOR11_DIRECTION_FORWARD;
    motor_speed = DCMOTOR11_VSET_480mV;
    dcmotor11_control( &dcmotor11, DCMOTOR11_DIRECTION_FORWARD, motor_speed );
}
  
```

### Application Task

> Waits for valid user input and executes functions based on set of valid commands.

```c

void application_task ( void )
{
    /* Speed increase */
    motor_speed += 4;
    if ( motor_speed >= DCMOTOR11_VSET_4820mV )
    {
        log_printf( &logger, "---- MAX SPEED ---- \r\n" );
        motor_speed = DCMOTOR11_VSET_4820mV;
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }
    else
    {
        log_printf( &logger, "---- Speed increase ---- \r\n" );
        log_printf( &logger, " MOTOR SPEED: %d \r\n", motor_speed );
        
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }

    Delay_ms( 2000 );

    /* Speed decrease */
    motor_speed -= 4;
    if ( motor_speed < DCMOTOR11_VSET_480mV )
    {
        log_printf( &logger, "---- MIN SPEED ---- \r\n" );
        motor_speed = DCMOTOR11_VSET_480mV;
    }
    else
    {
        log_printf( &logger, "---- Speed decrease ---- \r\n");
        log_printf( &logger, " MOTOR SPEED: %d \r\n", motor_speed );
        
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }

    Delay_ms( 2000 );

    /* Stop / Start */
    if( f_motor_state == 1 )
    {
        log_printf( &logger,"---- Stop Motor!!! ---- \r\n" );
        f_motor_state = 0;
        dcmotor11_stop( &dcmotor11 );
    }
    else
    {
        log_printf( &logger,"---- Start Motor ---- \r\n" );
        f_motor_state = 1;
        motor_speed = DCMOTOR11_VSET_480mV;
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }

    Delay_ms ( 2000 );

    /* Direction - Forward / Backword */
    if ( motor_dir == 2 )
    {
        log_printf( &logger,"---- Direction - [FORWARD] ---- \r\n" );
        motor_dir = 1;
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }
    else
    {
        log_printf( &logger,"---- Direction - [BACKWARD] ---- \r\n" );
        motor_dir = 2;
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor11

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
