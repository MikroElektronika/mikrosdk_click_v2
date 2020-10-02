
---
# DC MOTOR 6 click

DC Motor 6 Click is a PWM chopper type brushed DC motor driver, labeled as TB67H451FNG.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page]( < https://www.mikroe.com/dc-motor-6-click > )

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Dcmotor6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dcmotor6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor6_cfg_setup ( dcmotor6_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR6_RETVAL dcmotor6_init ( dcmotor6_t *ctx, dcmotor6_cfg_t *cfg );

#### Example key functions :

- Set IN1 pin.
> void dcmotor6_set_in1_pin ( dcmotor6_t *ctx, uint8_t state );
 
- Set IN1 pin.
> void dcmotor6_set_in2_pin ( dcmotor6_t *ctx, uint8_t state );

- Set motor Direction.
> void dcmotor6_set_direction( dcmotor6_t *ctx, uint8_t dir );

## Examples Description

> This IC includes one channel of motor output block, using a wide range of supply voltages, while delivering reasonably high current to the connected DC motors.

**The demo application is composed of two sections :**

### Application Init 

> Initializes application init. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor6_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    dcmotor6_cfg_setup( &cfg );
    DCMOTOR6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor6_init( &dcmotor6, &cfg );
}
  
```

### Application Task

> Set the motor direction in clockwise and Counte clockwise direction.

```c

void application_task ( void )
{
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_DIR_CCW );
    Delay_ms( 2000 );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_STOP );
    Delay_ms( 2000 );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_DIR_CW );
    Delay_ms( 2000 );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_STOP );
    Delay_ms( 2000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dcmotor6

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
