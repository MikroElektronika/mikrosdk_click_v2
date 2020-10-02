
---
# Servo click

Servo click is a 16-channel PWM servo driver with the voltage sensing circuitry. It can be used to simultaneously control 16 servo motors, each with its own programmable PWM signal.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/servo_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/servo-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Servo Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Servo Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void servo_cfg_setup ( servo_cfg_t *cfg ); 
 
- Initialization function.
> SERVO_RETVAL servo_init ( servo_t *ctx, servo_cfg_t *cfg );

- Click Default Configuration function.
> void servo_default_cfg ( servo_t *ctx );


#### Example key functions :

- This function settings Vref of Servo Clicks.
> void servo_set_vref ( servo_t *ctx, uint16_t v_ref );
 
- This function sets position.
> void servo_set_position ( servo_t *ctx, uint8_t motor, uint8_t position );

- This function reads the current value of Servo Click witch motor spends.
> uint16_t setvo_get_current ( servo_t *ctx, uint8_t channel );

## Examples Description

> This app sets servo motor at three different positions 0, 90, 180.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    servo_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    servo_cfg_setup( &cfg );
    SERVO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    servo_init( &servo, &cfg );
    
    servo_default_cfg( &servo );
}
  
```

### Application Task

> The servo motor is set at three different positions 0, 90, 180 - every two second,
> and reads current value witch motor spends in the moment when it runs to new position.

```c

void application_task ( void )
{
    uint16_t current;

    servo_set_position( &servo, SERVO_MOTOR_1, 0 );
    Delay_ms( 2000 );
    servo_set_position( &servo, SERVO_MOTOR_1, 90 );
    Delay_ms( 1000 );
    servo_set_position( &servo, SERVO_MOTOR_1, 180 );
    Delay_ms( 2000 );
    servo_set_position( &servo, SERVO_MOTOR_1, 90 );

    current = setvo_get_current( &servo, SERVO_POSITIVE_CH0 );
    log_printf( &logger, "Current - %u  mA \r\n", current );

    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Servo

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