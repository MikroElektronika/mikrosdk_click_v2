\mainpage Main Page
 
 

---
# ADC 8 click

ADC 8 Click is a high precision, low-power, 16-bit analog-to-digital converter (ADC), based around the ADS1115 IC. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc8_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/adc-8-click>)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Adc8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Adc8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void adc8_cfg_setup ( adc8_cfg_t *cfg ); 
 
- Initialization function.
> ADC8_RETVAL adc8_init ( adc8_t *ctx, adc8_cfg_t *cfg );

- Click Default Configuration function.
> void adc8_default_cfg ( adc8_t *ctx );


#### Example key functions :

- Get [Package] Diff channel voltage
> void adc8_get_diff_channel( adc8_t *ctx, adc8_diff_volt_t *volt );
 
- Get [Package] Single channel voltage
> void adc8_get_single_channel( adc8_t *ctx, adc8_single_volt_t *volt );

- Get interrupt pin state
> uint8_t adc8_get_interrupt_state( adc8_t *ctx );

## Examples Description

> The demo app shows voltage measurement across all singles and different channels.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    adc8_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adc8_cfg_setup( &cfg );
    ADC8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc8_init( &adc8, &cfg );

    adc8_default_cfg( &adc8 );
    log_info( &logger, "---- ADC start ----" );
}
```

### Application Task

> Reads voltage from each channel one by one and the voltage difference 
> between specified channels.

```c
void application_task ( void )
{
    adc8_single_volt_t single_volt;
    adc8_diff_volt_t diff_volt;

    log_printf( &logger, "\r\n-----------------------------------" );

    // Single channel
    adc8_get_single_channel( &adc8, &single_volt );

    log_printf( &logger, "\r\n>>> SINGLE CHANNEL <<<<\r\n" );
    log_printf( &logger, "- CH 0: %.2f\r\n", single_volt.ch_0 );
    log_printf( &logger, "- CH 1: %.2f\r\n", single_volt.ch_1 );
    log_printf( &logger, "- CH 2: %.2f\r\n", single_volt.ch_2 );
    log_printf( &logger, "- CH 3: %.2f\r\n", single_volt.ch_3 );

    // Diff channel

    adc8_get_diff_channel( &adc8, &diff_volt );

    log_printf( &logger, "\r\n>>> DIFF CHANNEL <<<<\r\n" );
    log_printf( &logger, "- CH(0-1): %.2f\r\n", diff_volt.ch_0_1 );
    log_printf( &logger, "- CH(0-3): %.2f\r\n", diff_volt.ch_0_3 );
    log_printf( &logger, "- CH(1-3): %.2f\r\n", diff_volt.ch_1_3 );
    log_printf( &logger, "- CH(2-3): %.2f\r\n", diff_volt.ch_2_3 );

    Delay_ms( 1000 );
}
```

## Note

> On the input channel AIN0, AIN1, AIN2 and AIN3 sets maximum voltage 
> GND - 0.3V < VIN > VDD + 0.3V

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc8

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
