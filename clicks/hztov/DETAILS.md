
---
# HZ to V click

HZ to V click is a device that can converts input frequency of the signal with virtually any wave shape to a DC voltage output, with a level proportional to the input frequency. It has a linear response, and by applying a signal with the frequency between 10Hz to 10kHz on its input, the Click board™ will generate a DC voltage, ranging from 0V to 3.3V. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hztov_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/hz-to-v-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the HzToV Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HzToV Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hztov_cfg_setup ( hztov_cfg_t *cfg ); 
 
- Initialization function.
> HZTOV_RETVAL hztov_init ( hztov_t *ctx, hztov_cfg_t *cfg );

- Click Default Configuration function.
> void hztov_default_cfg ( hztov_t *ctx );


#### Example key functions :

- This function sets the PWM frequency to required value, changing the output voltage.
> void hztov_set_output_voltage ( hztov_t *ctx, hztov_cfg_t *cfg, uint16_t voltage )
 
- This function sets the PWM duty cycle.
> void hztov_set_duty_cycle ( hztov_t *ctx, pwm_data_t duty_cycle )

- This function starts PWM module.
> void hztov_pwm_start ( hztov_t *ctx )

## Examples Description

> This click accepts a signal with the frequency within a range between 10Hz and 10kHz 
> on the input and generates DC voltage with the level corresponding to the input frequency, 
> ranging from 0V to 10V, with a highly linear response. This signal is further passed through 
> the operational amplifier, in order to scale it down to a level acceptable by the MCU.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - GPIO and PWM initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hztov_cfg_setup( &cfg );
    HZTOV_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hztov_init( &hztov, &cfg );
}
  
```

### Application Task

> Alternates between different output voltages.

```c

void application_task ( void )
{
    hztov_set_output_voltage( &hztov, &cfg, 5000 );        //5 V output
    Delay_ms( 3000 );
    hztov_set_output_voltage( &hztov, &cfg, 2500 );        //2.5 V output
    Delay_ms( 3000 );
    hztov_set_output_voltage( &hztov, &cfg, 1000 );        //1 V output
    Delay_ms( 3000 );
    hztov_set_output_voltage( &hztov, &cfg, 500 );         //0.5 V output
    Delay_ms( 3000 );
}  

```

## Note

> Output voltage may vary, depending on the offset potentiometer on board the click.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HzToV

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
