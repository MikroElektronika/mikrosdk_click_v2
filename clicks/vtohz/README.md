\mainpage Main Page
 
---
# V to Hz click

V to HZ click is a device that converts an analog voltage input signal into a pulse wave signal of a certain frequency. It has a linear response, so applying a voltage in a range of 0 to 5V on its input, will result in generating the pulse train with frequency linearly proportional to the input voltage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vtohz_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/v-to-hz-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the VtoHz Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for VtoHz Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void vtohz_cfg_setup ( vtohz_cfg_t *cfg ); 
 
- Initialization function.
> VTOHZ_RETVAL vtohz_init ( vtohz_t *ctx, vtohz_cfg_t *cfg );

#### Example key functions :

- Generic sets PWM duty cycle.
> void vtohz_set_duty_cycle ( vtohz_t *ctx, pwm_data_t duty_cycle )
 
- Stop PWM module.
> void vtohz_pwm_stop ( vtohz_t *ctx );

- Start PWM module.
> void vtohz_pwm_start ( vtohz_t *ctx );

## Examples Description
 
> This application converts an analog voltage input signal into a pulse wave signal of a certain frequency. 

**The demo application is composed of two sections :**

### Application Init 

> v2hz_setOutputFrequency - Sets the PWM duty cycle to required value, changing the output frequency. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    vtohz_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    vtohz_cfg_setup( &cfg );
    VTOHZ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vtohz_init( &vtohz, &cfg );
    
    vtohz_enable ( &vtohz );
}
  
```

### Application Task

> Alternates between different output frequencies.

```c

void application_task ( void )
{
    set_output_frequency( 1000 );        //1000 Hz output
    log_printf( &logger, "Output frequency: \t 1000 Hz\r\n" );
    Delay_ms( 5000 );
    set_output_frequency( 2000 );        //2000 Hz output
    log_printf( &logger, "Output frequency: \t 2000 Hz\r\n" );
    Delay_ms( 5000 );
    set_output_frequency( 5000 );        //5000 Hz output
    log_printf( &logger, "Output frequency: \t 5000 Hz\r\n" );
    Delay_ms( 5000 );
    set_output_frequency( 10000 );       //10000 Hz output
    log_printf( &logger, "Output frequency: \t 10000 Hz\r\n" );
    Delay_ms( 5000 );
}  

```

## Note

> Note: Output frequency may vary, depending on the offset and gain potentiometers on board the click.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.VtoHz

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
