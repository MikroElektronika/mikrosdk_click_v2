

---
# UV 3 click

UV 3 click is an advanced ultraviolet (UV) light sensor with I2C protocol interface. The click carries VEML6070 UVA light sensor designed by the CMOS process. UV 3 click runs on either 3.3V or 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uv3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uv-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Uv3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Uv3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void uv3_cfg_setup ( uv3_cfg_t *cfg ); 
 
- Initialization function.
> UV3_RETVAL uv3_init ( uv3_t *ctx, uv3_cfg_t *cfg );

- Click Default Configuration function.
> void uv3_default_cfg ( uv3_t *ctx );


#### Example key functions :

- Function enable sensor by sets shutdown mode bits as LOW to the target 8-bit CMD slave address.
> void uv3_enable_sensor ( uv3_t *ctx );
 
- Function read UV data measurements from to the two target 8-bit slave address.
> uint16_t uv3_read_measurements ( uv3_t *ctx );

- Function calculate UV risk level of VEML6070 sensor on UV 3 Click.
> uint8_t uv3_risk_level ( uint16_t uv_data );

## Examples Description

> Converts solar UV light intensity to digital data and measure UV radiation under long time solar UV exposure. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C, enable sensor and start write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uv3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    uv3_cfg_setup( &cfg );
    UV3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uv3_init( &uv3, &cfg );
    uv3_default_cfg ( &uv3 );
}

  
```

### Application Task

> This example measures the level of the UV light and logs every 2 seconds to the terminal.

```c

void application_task ( void )
{
    uv_data = uv3_read_measurements( &uv3 );

    risk_lvl = uv3_risk_level( uv_data );

    log_printf( &logger, " UV value  : %d\r\n ", uv_data );

    log_printf( &logger, " Radiation lvl : " );

    if ( risk_lvl == UV3_RAD_LOW )
    {
        log_printf( &logger, " Low\r\n " );
    }

    if ( risk_lvl == UV3_RAD_MODERATE )
    {
        log_printf( &logger, " Moderate\r\n " );
    }

    if ( risk_lvl == UV3_RAD_HIGH )
    {
        log_printf( &logger, " High\r\n " );
    }

    if ( risk_lvl == UV3_RAD_VERY_HIGH )
    {
        log_printf( &logger, " Very High\r\n " );
    }

    if ( risk_lvl == UV3_RAD_EXTREME )
    {
        log_printf( &logger, " Extreme\r\n " );
    }

    Delay_ms( 2000 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Uv3

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
