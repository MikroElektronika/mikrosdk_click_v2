

---
# PWM click

PWM click is a simple solution for controlling 16 PWM outputs through a single I2C interface. You can use it to control anything from a simple LED strip to a complex robot with a multitude of moving parts.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pwm_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/pwm-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Pwm Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pwm Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pwm_cfg_setup ( pwm_cfg_t *cfg ); 
 
- Initialization function.
> PWM_RETVAL pwm_init ( pwm_t *ctx, pwm_cfg_t *cfg );

- Click Default Configuration function.
> void pwm_default_cfg ( pwm_t *ctx );


#### Example key functions :

- Channel state function.
> void pwm_channel_state ( pwm_t *ctx, uint8_t chann_id, uint8_t state );
 
- Set channel raw function.
> void pwm_set_channel_raw ( pwm_t *ctx, uint8_t chann_id, uint16_t raw_off_set, uint16_t raw_dc );

- Set all channels raw function.
> void pwm_set_all_raw ( pwm_t *ctx, uint16_t raw_dc );

## Examples Description

> 
> This is an example that shows some of the functions that PWM click has.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initalizes I2C driver, enables output, configures device, sets prescaling,
> configures output and makes an initial log.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pwm_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    pwm_cfg_setup( &cfg );
    PWM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwm_init( &pwm, &cfg );
    Delay_ms( 100 );
    
    pwm_set_output( &pwm, PWM_DISABLE  );
    pwm_dev_config( &pwm, &config );
    pwm_set_pre_scale( &pwm, 0x04 );
    pwm_dev_config( &pwm, &config  );
    pwm_output_config( &pwm,  &config1 );
    Delay_ms( 100 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " PWM  Click \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
}
  
```

### Application Task

>
> Initalizes I2C driver, enables output, configures device, sets prescaling,
> configures output and makes an initial log.
> 

```c

void application_task ( void )
{
    uint16_t raw_dc;
    uint8_t chann_id;
    uint8_t duty_cycle;
    chann_id = 0;
    
    log_printf( &logger, "Channel 0 false state \r\n " );
    pwm_channel_state( &pwm, chann_id, 0 );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 2000 );
    
    log_printf( &logger, "Channel 0 set raw  \r\n" );
    for ( raw_dc = 0; raw_dc < PWM_MAX_RESOLUTION; raw_dc += 256 )
    {
        pwm_set_channel_raw( &pwm, chann_id, 0, raw_dc );
        log_printf( &logger, " >\r\n" );
        Delay_ms( 500 );
    }
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "Channel 0 set  \r\n" );
    for ( duty_cycle = 0; duty_cycle < 100; duty_cycle += 10 )
    {
        pwm_set_channel_raw( &pwm, chann_id, 0, duty_cycle );
        log_printf( &logger, " > \r\n" );
        Delay_ms( 500 );
    }
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "All Channels raw set  \r\n" );
    for ( raw_dc = 0; raw_dc < PWM_MAX_RESOLUTION; raw_dc += 256 )
    {
        pwm_set_all_raw( &pwm, raw_dc );
        log_printf( &logger, " >\r\n" );
        Delay_ms( 500 );
    }
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "All Channels set  \r\n" );
    for ( duty_cycle = 0; duty_cycle < 100; duty_cycle += 10 )
    {
        pwm_set_all( &pwm, duty_cycle );
        log_printf( &logger, " >\r\n" );
        Delay_ms( 500 );
    }
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "All Channels false state \r\n " );
    pwm_all_chann_state( &pwm, 0 );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 2000 );
} 

```

## Note


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pwm

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
