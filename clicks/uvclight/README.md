\mainpage Main Page
 
---
# UVC Light click

UVC Light Click is Click board™ with ultraviolet LEDs with 275nm wavelength which can be complemented with UVC Click for measuring exact dose of UV radiation. UVC radiation refers to wavelengths shorter than 280 nm. Because of the spectral sensitivity of DNA, only the UVC region demonstrates significant germicidal properties. As evident by multiple research studies and reports, when biological organisms are exposed to deep UV light in the range of 200 nm to 300 nm it is absorbed by DNA, RNA, and proteins. With two 0.7W (1.4W combined power) UVC Light Click is a perfect solution as a small surface disinfection tool.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uvclight_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uvc-light-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the UvcLight Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for UvcLight Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void uvclight_cfg_setup ( uvclight_cfg_t *cfg ); 
 
- Initialization function.
> UVCLIGHT_RETVAL uvclight_init ( uvclight_t *ctx, uvclight_cfg_t *cfg );


#### Example key functions :

- This function starts PWM module.
> void uvclight_pwm_start ( uvclight_t *ctx );
 
- This function sets the PWM duty cycle.
> void uvclight_set_duty_cycle ( uvclight_t *ctx, pwm_data_t duty_cycle );

- This function stops PWM module.
> void uvclight_pwm_stop ( uvclight_t *ctx );

## Examples Description

> This click has ultraviolet LEDs with 275nm wavelength. UVC radiation refers to wavelengths 
> shorter than 280 nm. Because of the spectral sensitivity of DNA, only the UVC region 
> demonstrates significant germicidal properties.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uvclight_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    uvclight_cfg_setup( &cfg );
    UVCLIGHT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uvclight_init( &uvclight, &cfg );

    uvclight_pwm_start( &uvclight );
    Delay_ms( 100 );
}
  
```

### Application Task

> Increases and decreases the pwm duty cycle.

```c

void application_task ( void )
{
    log_printf( &logger, "Increasing PWM duty cycle...\r\n" );
    
    for ( duty_cycle = 0; duty_cycle < 1.0; duty_cycle += 0.1 )
    {
        uvclight_set_duty_cycle ( &uvclight, duty_cycle );
        Delay_ms( 100 );
    }

    Delay_ms( 500 );
    
    log_printf( &logger, "Decreasing PWM duty cycle...\r\n" );
    for ( duty_cycle = 1.0; duty_cycle >= 0; duty_cycle-= 0.1 )
    {
        uvclight_set_duty_cycle ( &uvclight, duty_cycle );
        Delay_ms( 100 );
    }
    log_printf( &logger, "-------------------------------\r\n" );

    Delay_ms( 500 );
} 

```

## Note

> CAUTION! High intensity UV Light - avoid eye and skin exposure. Avoid looking direclty at light!

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.UvcLight

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
