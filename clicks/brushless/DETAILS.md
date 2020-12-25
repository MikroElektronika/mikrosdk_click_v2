
---
# Brushless click

<Brushless click carries Toshiba's TB6575FNG IC for driving 3-phase full-wave Brushless DC motors — which are ideal for powering flying drones. The click is able to safely drive external motors with up to 32V/2A. The board features three pairs of onboard screw terminals. VBAT is for connecting an external 7-32V DC power supply.>

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/brushless_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/brushless>)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type

# Software Support

We provide a library for the Brushless Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Brushless Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void brushless_cfg_setup ( brushless_cfg_t *cfg ); 
 
- Initialization function.
> BRUSHLESS_RETVAL brushless_init ( brushless_t *ctx, brushless_cfg_t *cfg );

- Click Default Configuration function.
> void brushless_default_cfg ( brushless_t *ctx );


#### Example key functions :

- This function sets the spin direction of the motor to clockwise.
> void brushless_spin_clockwise ( brushless_t *ctx );
 
- This function sets the spin direction of the motor to counter clockwise.
> void brushless_spin_counter_clockwise ( brushless_t *ctx );

- This function reads the digital input of the INT pin.
> uint8_t brushless_read_rotation_speed_sensor_output ( brushless_t *ctx );

## Examples Description

> This example showcases how to initialize and use the Brushless click. The click has a bru-
> shless motor driver which controls the work of the motor through the BLDC terminal. In order
> for this example to work a motor and a power supply are needed. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    brushless_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_100ms( );

    //  Click initialization.

    brushless_cfg_setup( &cfg );
    BRUSHLESS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_100ms( );
    brushless_init( &brushless, &cfg );
    brushless_pwm_start( &brushless );
    Delay_1sec( );
}
  
```

### Application Task

> This function drives the motor in both directions increasing and decreasing the speed of the motor.

```c

void application_task ( )
{    
    clockwise( );
    counter_clockwise( );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless

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
