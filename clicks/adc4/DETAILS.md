
---
# ADC 4 click

ADC 4 click is an advanced analog to digital multichannel converter, which can sample inputs from 16 single-ended channels or 8 differential input channel pairs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adc-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Adc4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Adc4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void adc4_cfg_setup ( adc4_cfg_t *cfg ); 
 
- Initialization function.
> ADC4_RETVAL adc4_init ( adc4_t *ctx, adc4_cfg_t *cfg );

- Click Default Configuration function.
> void adc4_default_cfg ( adc4_t *ctx );


#### Example key functions :

- Error check function
> uint8_t adc4_get_err_pin ( adc4_t *ctx );
 
- Get configuration function
> void adc4_get_config ( adc4_t *ctx, uint8_t reg_address, uint16_t *value );

- Get voltage function
> uint16_t adc4_get_voltage ( adc4_t *ctx, const float ref_voltage );

## Examples Description

> This application is a converter from analog to digital multichannel 

**The demo application is composed of two sections :**

### Application Init 

> Initializes ADC 4 driver and setups working mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adc4_cfg_setup( &cfg );
    ADC4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc4_init( &adc4, &cfg );

    Delay_ms( 100 );

    adc4_default_cfg( &adc4 );

    voltage = 0;
}
  
```

### Application Task

> Sequential read of voltage. Information about
> current voltage is logget to UART. Operation is repeated each second. Settings are set
> to calculate and convert input voltage from CH0 with external referent voltage set by VREF jumper on the click board.

```c

void application_task ( )
{
    voltage = adc4_get_voltage( &adc4, ADC4_VREF_4000MV);

    if ( adc4.sing_bit == 1 )
    {
        log_printf( &logger, "Voltage at CH0 : %d mV \r\n", voltage );
    }
    else
    {
        log_printf( &logger, "Voltage at CH0 : - %d mV \r\n", voltage );
    }

    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc4

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
