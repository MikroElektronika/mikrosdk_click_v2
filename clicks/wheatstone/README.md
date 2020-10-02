\mainpage Main Page
 
---
# Wheatstone click

Wheatstone Click is a measurement Click board™ which utilizes a Wheatstone bridge circuit onboard, in order to precisely measure the resistance of an external element. Besides the wheatstone bridge circuit, this Click board™ also utilizes MAX4208 – an ultra-low offset/drift, precision instrumentation amplifier, from Maxim Integrated.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/wheatstone_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/wheatstone-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Wheatstone Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Wheatstone Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void wheatstone_cfg_setup ( wheatstone_cfg_t *cfg ); 
 
- Initialization function.
> WHEATSTONE_RETVAL wheatstone_init ( wheatstone_t *ctx, wheatstone_cfg_t *cfg );

#### Example key functions :

- Set potentiometer ( 0 - 100k )
> void wheatstone_set_potentiometer ( wheatstone_t *ctx, uint8_t pot_value );
 
- Set ADC VREF.
> void wheatstone_set_adc_vref ( wheatstone_t *ctx, float vref );

- Set ADC resolution.
> void wheatstone_set_adc_resolution ( wheatstone_t *ctx, float res );


## Examples Description

> This single chip includes a linear charger, a synchronous Boost with dual output load management and a torch function support.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and ADC module init.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    wheatstone_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    wheatstone_cfg_setup( &cfg );
    WHEATSTONE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wheatstone_init( &wheatstone, &cfg );

    wheatstone_set_potentiometer ( &wheatstone, WHEATSTONE_DEF_POTENCIOMETER );
    wheatstone_set_adc_vref ( &wheatstone, 2048.0 );
    wheatstone_set_adc_resolution ( &wheatstone, 4096.0 );
    Delay_ms( 100 );
}
  
```

### Application Task

> Reads the ADC value and converts to voltage on the AN pin.

```c

void application_task ( void )
{
    float voltage;
    uint32_t adc_value = 0;
    
    adc_value = wheatstone_generic_read( &wheatstone );

    log_printf( &logger, "-- ADC value: %d \r\n", adc_value );
    
    voltage = wheatstone_get_voltage( &wheatstone, adc_value );

    log_printf( &logger, "-- Voltage: %.2f mV\r\n", voltage );
    
    Delay_ms( 2000 );
}  

```

## Note

> Set the ADC resolution and vref before programming.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Wheatstone

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
