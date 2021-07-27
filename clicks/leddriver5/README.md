\mainpage Main Page
 
---
# Led Driver 5 click

LED Driver 5 click is a Click board™ capable of driving an array of high-power LEDs with constant current, up to 1.5A. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-driver-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the LedDriver5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LedDriver5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void leddriver5_cfg_setup ( leddriver5_cfg_t *cfg ); 
 
- Initialization function.
> LEDDRIVER5_RETVAL leddriver5_init ( leddriver5_t *ctx, leddriver5_cfg_t *cfg );

- Click Default Configuration function.
> void leddriver5_default_cfg ( leddriver5_t *ctx );


#### Example key functions :

- Generic sets PWM duty cycle.
> void leddriver5_set_duty_cycle ( leddriver5_t *ctx, pwm_data_t duty_cycle );
 
- Stop PWM module.
> void leddriver5_pwm_stop ( leddriver5_t *ctx );

- Start PWM module
> void leddriver5_pwm_start ( leddriver5_t *ctx );

## Examples Description

> The application is a capable of driving an array of high-power LEDs. 

**The demo application is composed of two sections :**

### Application Init 

>Initialization driver init and pwm init 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    leddriver5_cfg_setup( &cfg );
    LEDDRIVER5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver5_init( &leddriver5, &cfg );

    leddriver5_pwm_start( &leddriver5 );
}

  
```

### Application Task

>Controls the brightness of the LED using PWM

```c

void application_task ( void )
{
    for ( duty_cycle = 0.1; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        leddriver5_set_duty_cycle ( &leddriver5, duty_cycle );
        Delay_ms( 500 );
    }
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver5

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
