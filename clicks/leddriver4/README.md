\mainpage Main Page
 
---
# LED Driver 4 click

LED Driver 4 click is a form of a high-efficiency boost converter that is ideally suited for driving an array of white LEDs. The driver has the ability to dim the connected LED array, without producing any noise on the output. The Click board is capable of driving a LED array with up to 26V, providing a constant current to the LED segments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver4_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/led-driver-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the LedDriver4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LedDriver4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void leddriver4_cfg_setup ( leddriver4_cfg_t *cfg ); 
 
- Initialization function.
> LEDDRIVER4_RETVAL leddriver4_init ( leddriver4_t *ctx, leddriver4_cfg_t *cfg );

- Click Default Configuration function.
> void leddriver4_default_cfg ( leddriver4_t *ctx );


#### Example key functions :

- <FUNCTION_DESCRIPTION>
> <FUNCTION_DECLARATION>
 
- <FUNCTION_DESCRIPTION>
> <FUNCTION_DECLARATION>

- <FUNCTION_DESCRIPTION>
> <FUNCTION_DECLARATION>

## Examples Description

> This click has the ability to dim the connected LED array, without producing any noise on the output.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the GPIO driver and configures the PWM peripheral for controlling the LED array intensity.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    leddriver4_cfg_setup( &cfg );
    LEDDRIVER4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver4_init( &leddriver4, &cfg );

    leddriver4_pwm_start( &leddriver4 );
}
  
```

### Application Task

> Increases and decreases LED array intensity
> ( firts increases light intensity to the maximum and than decreases to the minimum ).

```c

void application_task ( void )
{
    for ( duty_cycle = 0; duty_cycle < leddriver4.pwm_period;  )
    {
        leddriver4_set_duty_cycle( &leddriver4, duty_cycle );
        Delay_ms( 20 );
        if ( duty_cycle > ( leddriver4.pwm_period - 10 ) )
        {
            break;
        }
        else
        {
            duty_cycle += 50;
        }
    }

    for ( duty_cycle = leddriver4.pwm_period; duty_cycle > 0;  )
    {
        leddriver4_set_duty_cycle( &leddriver4, duty_cycle );
        Delay_ms( 20 );
        if ( duty_cycle < 10 )
        {
            break;
        }
        else
        {
            duty_cycle -= 50;
        }
    }
    
    Delay_ms( 1000 );
}
 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver4

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
