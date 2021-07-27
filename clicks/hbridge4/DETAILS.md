
---
# H-Bridge 4 click

H-Bridge 4 Click is a Click board™ that contains the AP1010AEN, which is a two channel H-Bridge motor driver compatible with a motor operating voltage up to 18V and can drive two DC motors or one stepper motor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the HBridge4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HBridge4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hbridge4_cfg_setup ( hbridge4_cfg_t *cfg ); 
 
- Initialization function.
> HBRIDGE4_RETVAL hbridge4_init ( hbridge4_t *ctx, hbridge4_cfg_t *cfg );

#### Example key functions :

- Enable the device function
> void hbridge4_enable ( hbridge4_t *ctx, uint8_t state );
 
- Set IN1 function
> void hbridge4_set_in1 ( hbridge4_t *ctx, uint8_t state );

- Motor A standby function
> void hbridge4_motor_a_standby ( hbridge4_t *ctx );

## Examples Description

> This application is used to turn on DC or Stepper motors.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables GPIO and also starts write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    hbridge4_cfg_setup( &cfg );
    HBRIDGE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge4_init( &hbridge4, &cfg );

    hbridge4_enable( &hbridge4, 1 );
    Delay_ms( 100 );
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, " H-Bridge 4 click \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}
  
```

### Application Task

> This example demonstrates the use of H-Bridge 4 click board by putting A motor
> in standby mode, then spining it in clockwise direction and applying brake function, and then
> spining it in counter-clockwise direction and applying brake function again.

```c

void application_task ( )
{
    log_printf( &logger, "The motor A is in standby mode \r\n" );
    hbridge4_motor_a_standby( &hbridge4 );
    Delay_ms( 100 );
    log_printf( &logger, "The motor A turns clockwise \r\n" );
    hbridge4_motor_acw( &hbridge4 );
    Delay_ms( 2000 );
    log_printf( &logger, "The motor A applies brake \r\n" );
    hbridge4_motor_a_brake( &hbridge4 );
    Delay_ms( 1000 );
    log_printf( &logger, "The motor A turns counter-clockwise \r\n" );
    hbridge4_motor_accw( &hbridge4 );
    Delay_ms( 2000 );
    log_printf( &logger, "The motor A applies brake \r\n" );
    hbridge4_motor_a_brake( &hbridge4 );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge4

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
