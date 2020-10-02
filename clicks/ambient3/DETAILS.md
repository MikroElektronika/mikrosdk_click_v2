
---
# Ambient 3 click

Ambient 3 Click is calibrated XYZ chromatic smart lighting director, providing the measurement data in digital format over the I2C interface. It utilizes the AS7225, a miniature light sensor with UART and I2C interfaces. Packed in a small casing, this sensor can provide calibrated for life nano-optic sensor providing direct CIE1931 XYZ and CIE 1976 u’v’ coordinate mapping.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/ambient3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ambient-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ambient3_cfg_setup ( ambient3_cfg_t *cfg ); 
 
- Initialization function.
> AMBIENT3_RETVAL ambient3_init ( ambient3_t *ctx, ambient3_cfg_t *cfg );

- Click Default Configuration function.
> void ambient3_default_cfg ( ambient3_t *ctx );

#### Example key functions :

- This function reads device temperature.
> uint8_t ambient3_get_device_temperature( ambient3_t *ctx );

- This function reads data in LUX value.
> float ambient3_get_data_in_LUX( ambient3_t *ctx );

- This function reads floating point register.
> float ambient3_read_floating_point_register( ambient3_t *ctx, uint8_t reg );

## Examples Description

> This application is calibrated XYZ chromatic smart lighting director, 
> providing the measurement data in digital format over the I2C interface.
> Initializes I2C module and sets INT pin as INPUT and RST pin as OUTPUT

**The demo application is composed of two sections :**

### Application Init 

> Driver init and reset chip

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ambient3_cfg_setup( &cfg );
    AMBIENT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient3_init( &ambient3, &cfg );
    ambient3_default_cfg( &ambient3 );
}
  
```

### Application Task

> Reads the device temperature, daylight at LUX and logs data to USBUART every 1 sec.

```c

void application_task ( )
{
    temperature = ambient3_get_device_temperature( &ambient3 );
    log_printf( &logger, " - Device temperature : %d\r\n", temperature );

    data_lux = ambient3_get_data_in_lux( &ambient3 );
    log_printf( &logger, " - Light in LUX : %.2f\r\n", data_lux );
    
    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient3

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
