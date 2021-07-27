
---
# PWM 2 click

PWM 2 click offers 48 independently controlled PWM channels, available over the onboard headers, perfectly suited for driving LEDs. Each channel has a 12-bit PWM register associated to it, with the addition of the 6-bit correction register, also known as the dot correction register

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pwm2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pwm-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Pwm2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pwm2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pwm2_cfg_setup ( pwm2_cfg_t *cfg ); 
 
- Initialization function.
> PWM2_RETVAL pwm2_init ( pwm2_t *ctx, pwm2_cfg_t *cfg );


#### Example key functions :

- Set channel function.
> uint8_t pwm2_set_channel ( pwm2_t *ctx, uint8_t n_channel, uint16_t width, uint8_t correction );
 
- Start PWM module.
> void pwm2_pwm_start ( pwm2_t *ctx );

- Enable frame.
> static void send_output_enable_frame ( pwm2_t *ctx );

## Examples Description

> This application send the PWM signal in one or more outputs.

**The demo application is composed of two sections :**

### Application Init 

> Configures the click board and sets all PWM channels on the click board to
> 50% duty cycle with the phase shift enabled.

```c

void application_init ( void )
{
    pwm2_cfg_t cfg;

    //  Click initialization.

    pwm2_cfg_setup( &cfg );
    PWM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwm2_init( &pwm2, &cfg );
    
    pwm2_set_duty_cycle( &pwm2, 0.5 );
    pwm2_pwm_start( &pwm2 );

    pwm2_default_cfg( &pwm2 );
    pwm2_toggle_phase_shift( &pwm2 );

    //setting all 48 PWM channels of the PWM2 click to 50% duty
    for( uint8_t cnt = 1; cnt < 49; cnt++ ) 
    {
        pwm2_set_channel( &pwm2, cnt, PWM2_50_PERCENT_DUTY, PWM2_NO_CORRECTION );
    }
}
  
```

### Application Task

> The first 10 PWM channels of PWM2 Click board are switched back and forth 
> from 25% duty cycle to 75% duty cycle every 10 seconds.

```c

void application_task ( void )
{
    for ( uint8_t cnt = 1; cnt < 10; cnt++ )
    { 
        pwm2_set_channel( &pwm2, cnt, PWM2_25_PERCENT_DUTY, PWM2_NO_CORRECTION );
    }
    Delay_ms( 10000 );
    
    for ( uint8_t cnt = 1; cnt < 10; cnt++ )
    { 
        pwm2_set_channel( &pwm2, cnt, PWM2_75_PERCENT_DUTY, PWM2_NO_CORRECTION );
    }
    Delay_ms( 10000 );
}
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pwm2

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
