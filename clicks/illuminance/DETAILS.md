

---
# Illuminance click

Illuminance click carries a TSL2561 light-to-digital converter with a sensor that’s designed to mimic the way humans perceive light.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/illuminance_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/illuminance-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Illuminance Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Illuminance Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void illuminance_cfg_setup ( illuminance_cfg_t *cfg ); 
 
- Initialization function.
> ILLUMINANCE_RETVAL illuminance_init ( illuminance_t *ctx, illuminance_cfg_t *cfg );

- Click Default Configuration function.
> void illuminance_default_cfg ( illuminance_t *ctx );


#### Example key functions :

- This function gets Visible & Infrared value.
> void illuminance_get_result( illuminance_t *ctx, uint16_t *value_ch0, uint16_t *value_ch1 );

 
- This function calculates lux value from the TSL2561 sensor.
> uint16_t illuminance_calculate_lux( uint16_t value_gain, uint16_t value_int,
>                                     uint16_t ch0, uint16_t ch1 );


## Examples Description

This example demonstrates basic Illuminance Click functionality - calculates
illuminance measured by sensor and logs results to UART Terminal.

**The demo application is composed of two sections :**

### Application Init 

Device and driver initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    illuminance_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    illuminance_cfg_setup( &cfg );
    ILLUMINANCE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    illuminance_init( &illuminance, &cfg );
    illuminance_default_cfg ( &illuminance );

    // Variable Initialization for this example.
    
    lux_value_old = 0;
    sensitivity = 50;
}
  
```

### Application Task

> Every second calculate illuminance and logs result to the terminal.

```c

void application_task ( void )
{
    illuminance_get_result( &illuminance, &value_ch0, &value_ch1 );

    lux_value = illuminance_calculate_lux( ILLUMINANCE_TSL2561_GAIN_0X, ILLUMINANCE_TSL2561_INTEGRATIONTIME_402MS , value_ch0, value_ch1 );
    Delay_ms( 1000 );

    if ( ( ( lux_value - lux_value_old ) > sensitivity ) && ( ( lux_value_old - lux_value ) > sensitivity ) )
    {
        log_printf( &logger, "\r\n--------------------------------" );
        log_printf( &logger, "\r\nFull  Spectrum: %u [ lux ]", lux_value );
        log_printf( &logger, "\r\nVisible  Value: %u [ lux ]", value_ch0 - value_ch1 );
        log_printf( &logger, "\r\nInfrared Value: %u [ lux ]", value_ch1 );    
        log_printf( &logger, "\r\n--------------------------------\r\n" );

        lux_value_old = lux_value;
    }
}
```

## Note

By default, integration time is set to 402ms but it may be modified
by user using illuminance_write_data() function and provided macros.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Illuminance

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
