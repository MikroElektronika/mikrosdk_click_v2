\mainpage Main Page
 
---
# STSPIN250 click

STSPIN250 click is a brushed DC motor driver with the current limiting and current sensing. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stspin250_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/stspin250-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Stspin250 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Stspin250 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void stspin250_cfg_setup ( stspin250_cfg_t *cfg ); 
 
- Initialization function.
> STSPIN250_RETVAL stspin250_init ( stspin250_t *ctx, stspin250_cfg_t *cfg );

- Click Default Configuration function.
> void stspin250_default_cfg ( stspin250_t *ctx );


#### Example key functions :

- This function regulates Direction control pin state. It controls direction
- of the current.
> void stspin250_set_ph ( stspin250_t *ctx, uint8_t state );
 
- This function regulates enable pin state.
> void stspin250_enable ( stspin250_t *ctx, uint8_t state);

- This function regulates reset pin state.
> void stspin250_reset ( stspin250_t *ctx );

## Examples Description

> his application enables usage of brushed DC motor driver with the current limiting and current sensing.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init, PWM init and enable device


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    stspin250_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    stspin250_cfg_setup( &cfg );
    STSPIN250_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stspin250_init( &stspin250, &cfg );

    stspin250_enable( &stspin250, STSPIN250_DEVICE_ENABLE );
    stspin250_set_duty_cycle ( &stspin250, duty_cycle );

    stspin250_pwm_start( &stspin250 );
}
  
```

### Application Task

> Changes the PWM dutyCycle and controls the motor speed.
> You can change the direction of the motor rotation by setting PH to 0 or 1. 

```c

void application_task ( void )
{
    //  Task implementation.


    duty_cycle += 250;
    stspin250_set_duty_cycle ( &stspin250, duty_cycle );
    if ( duty_cycle > 40000 )
    {
        duty_cycle = 0;
        stspin250_pwm_stop( &stspin250 );
        Delay_ms( 2000 );
        stspin250_pwm_start( &stspin250 );
    }
	stspin250_set_ph( &stspin250 ,1 );
    Delay_ms( 200 );

    Delay_100ms( );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Stspin250

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
