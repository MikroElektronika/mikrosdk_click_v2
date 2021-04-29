
---
# ADC 2 click

ADC 2 click carries MCP3551/3, which is a 22-bit ADC with automatic internal offset and gain calibration. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adc-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Adc2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Adc2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void adc2_cfg_setup ( adc2_cfg_t *cfg ); 
 
- Initialization function.
> ADC2_RETVAL adc2_init ( adc2_t *ctx, adc2_cfg_t *cfg );

- Click Default Configuration function.
> void adc2_default_cfg ( adc2_t *ctx );


#### Example key functions :

- Function is used to check overflow high state.
> uint8_t adc2_check_over_high ( adc2_t *ctx );
 
- Function is used to check overflow low state.
> uint8_t adc2_check_over_low ( adc2_t *ctx );

- Function is used to read specific data from ADC convertor.
> uint32_t adc2_adc_value_read ( adc2_t *ctx );

## Examples Description

> This application enables usage of the 22bit ADC.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes SPI driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adc2_cfg_setup( &cfg );
    ADC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc2_init( &adc2, &cfg );

    Delay_ms( 100 );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "    ADC 2 Click   \r\n" );
    log_printf( &logger, "------------------\r\n" );
}
  
```

### Application Task

> This is an example that shows the capabilities of the ADC 2 click

```c

void application_task ( void )
{
    uint32_t adc_val;

    //  Task implementation.

    adc_val = adc2_adc_value_read( &adc2 );

    log_printf( &logger, "Value : %d", adc_val );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc2

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