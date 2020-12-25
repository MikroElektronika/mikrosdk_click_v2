\mainpage Main Page
 
---
# Angle 2 click

Angle 2 click is a magnetic rotational sensor which relies on the ultra-fast MA700 angular sensor IC. Due to a high data output rate of 500kHz, the MA700 IC is able to provide a reliable absolute angular positional data at speeds up to 100,000 RPM.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/angle2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/angle-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Angle2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Angle2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void angle2_cfg_setup ( angle2_cfg_t *cfg ); 
 
- Initialization function.
> ANGLE2_RETVAL angle2_init ( angle2_t *ctx, angle2_cfg_t *cfg );

- Click Default Configuration function.
> void angle2_default_cfg ( angle2_t *ctx );


#### Example key functions :

- This function reads angle data from the click module.
> double angle2_get_angle ( angle2_t *ctx );
 
- This function reads angle and time index data from the click module.
> double angle2_get_angle_with_time_index ( angle2_t *ctx, uint8_t *time_index );

- This function sets the zero scale value.
> void angle2_set_zero_scale ( angle2_t *ctx, double zero_deg );

## Examples Description

> This example showcases how to configure and use the Angle 2 click. This click senses
  the magnetic field along the horizontal plane using an array of Hal effect sensors.
  The module uses advanced Spinaxis technology based on a direct angle sampling app-
  roach in order to provide reliable data quickly. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the click and logger modules. Additional con-
  figuring is done in the default_cfg(...) function. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    angle2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms( 100 );

    //  Click initialization.

    angle2_cfg_setup( &cfg );
    ANGLE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle2_init( &angle2, &cfg );

    Delay_ms( 300 );
    angle2_default_cfg( &angle2 );
    Delay_ms( 200 );

    log_printf( &logger, " * Angle 2 initialized * \r\n" );
}
  
```

### Application Task

> This function reads angle data from the click module and displays that data using the
  UART console every 200 miliseconds.

```c

void application_task ( void )
{
    double angle;

    angle = angle2_get_angle( &angle2 );

    log_printf( &logger, " Angle: %.2f deg\r\n", angle );

    Delay_ms( 200 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle2

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
