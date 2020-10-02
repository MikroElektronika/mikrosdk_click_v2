
---
# Pwm Driver click

If you need to control DC motors with loads up to 10A, PWM driver click is the perfect solution, thanks to the Silicon Lab Si8711CC one-channel isolator. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pwmdriver_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/pwm-driver-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the PwmDriver Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for PwmDriver Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pwmdriver_cfg_setup ( pwmdriver_cfg_t *cfg ); 
 
- Initialization function.
> PWMDRIVER_RETVAL pwmdriver_init ( pwmdriver_t *ctx, pwmdriver_cfg_t *cfg );

- Click Default Configuration function.
> void pwmdriver_default_cfg ( pwmdriver_t *ctx );


#### Example key functions :

- Generic sets PWM duty cycle
> void pwmdriver_set_duty_cycle ( pwmdriver_t *ctx, pwm_data_t duty_cycle );
 
- Stop PWM module.
> void pwmdriver_pwm_stop ( pwmdriver_t *ctx );

- Start PWM module
> void pwmdriver_pwm_start ( pwmdriver_t *ctx );

## Examples Description

> This application is controls the speed DC motors.

**The demo application is composed of two sections :**

### Application Init 

>Initialization driver enables - GPIO, PWM initialization set PWM duty cycle and PWM frequency, start PWM, enable the engine, and start to write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pwmdriver_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pwmdriver_cfg_setup( &cfg );
    PWMDRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwmdriver_init( &pwmdriver, &cfg );

    pwmdriver_pwm_start( &pwmdriver );

    Delay_100ms( );
    
    log_printf( &logger, "   Initialization PWM  \r\n  " );
    pwmdriver_set_duty_cycle( &pwmdriver,duty_cycle );
    pwmdriver_pwm_start( &pwmdriver );
    Delay_1sec( );
    log_printf( &logger, "------------------------- \r\n  " );
}
  
```