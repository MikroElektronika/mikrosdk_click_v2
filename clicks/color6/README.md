\mainpage Main Page
 
 

---
# Color 6 click

Color 6 click is a very accurate color sensing Click board™ which features the AS73211, an XYZ true color sensor from ams.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/color-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Color6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Color6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void color6_cfg_setup ( color6_cfg_t *cfg ); 
 
- Initialization function.
> COLOR6_RETVAL color6_init ( color6_t *ctx, color6_cfg_t *cfg );

- Click Default Configuration function.
> void color6_default_cfg ( color6_t *ctx );


#### Example key functions :

- This function write one byte in register.
> void color6_write_byte ( color6_t *ctx, uint8_t reg, uint8_t r_data );
 
- This function reads one byte data from register.
> uint8_t color6_read_byte ( color6_t *ctx, uint8_t reg );

- The measurement result is available as TEMP of the output result registers.
> float color6_get_temperature ( color6_t *ctx );

## Examples Description

> Reads values from the X / Y / Z channel and 
> converts to ee (input light irradiance regarding to the photodiode�s area
> within the conversion time interval) data. 
 
**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and configuration chip for measurement. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    color6_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    color6_cfg_setup( &cfg );
    COLOR6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color6_init( &color6, &cfg );

    color6_software_reset( &color6 );
    color6_default_cfg ( &color6 );
    color6_go_to_measurement_mode( &color6 );
}

  
```

### Application Task

> Reads values from the X / Y / Z channel and 
> converts to ee (input light irradiance regarding to the photodiode�s area
> within the conversion time interval) data. 
> This data logs on USB UART every 2 seconds.

```c

void application_task ( void )
{
    x_data = color6_read_data( &color6, COLOR6_MREG_MEASUREMENT_X_CHANNEL );
    log_printf( &logger, " Channel X :  %d ", x_data );

    ee_data = color6_converting_to_ee( COLOR6_MREG_MEASUREMENT_X_CHANNEL, x_data);
    log_printf( &logger, " Ee X channel data:   %f ", ee_data );

    y_data = color6_read_data( &color6, COLOR6_MREG_MEASUREMENT_Y_CHANNEL );
    log_printf( &logger, " Channel Y :  %d ", y_data );

    ee_data = color6_converting_to_ee( COLOR6_MREG_MEASUREMENT_Y_CHANNEL, y_data);
    log_printf( &logger, " Ee Y channel data:   %f ", ee_data );

    z_data = color6_read_data( &color6, COLOR6_MREG_MEASUREMENT_Z_CHANNEL );
    log_printf( &logger, " Channel Z :  %d ", z_data );

    ee_data = color6_converting_to_ee( COLOR6_MREG_MEASUREMENT_Z_CHANNEL, z_data);
    log_printf( &logger, " Ee Z channel data:   %f ", ee_data );

    temperature = color6_getTemperature( &color6 );
    log_printf( &logger, " Temperature :  %f ", temperature );

    Delay_ms( 2000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Color6

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
