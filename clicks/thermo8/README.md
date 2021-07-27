\mainpage Main Page
 
 

---
# Thermo 8 click

Thermo 8 click is a very accurate thermometer Click board™, with a very high typical measurement accuracy of ±0.25°C, and great data repeatability, with drift in the range of ±0.0625°C.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-8-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo8_cfg_setup ( thermo8_cfg_t *cfg ); 
 
- Initialization function.
> THERMO8_RETVAL thermo8_init ( thermo8_t *ctx, thermo8_cfg_t *cfg );

- Click Default Configuration function.
> void thermo8_default_cfg ( thermo8_t *ctx );


#### Example key functions :

- This function returns the temperature value in �C.
> float thermo8_get_temperature ( thermo8_t *ctx );
 
- This function sets the conversion resoult temperature step depending on the passed constant.
> void thermo8_set_resolution ( thermo8_t *ctx, uint8_t r_cfg );

- This function setting the temperature alarm levels for the lower, upper and critical alert levels.
> void thermo8_limit_set ( thermo8_t *ctx, uint8_t limit_reg_addr, float limit );

## Examples Description

> This application measures temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initialize device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo8_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    thermo8_cfg_setup( &cfg );
    THERMO8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo8_init( &thermo8, &cfg );
    Delay_ms( 100 );
    thermo8_default_cfg( &thermo8 );
}
  
```

### Application Task

> Wait for the interrupt pin to be triggered. When the
> measured temperature breaches the upper or lower limit the
> temperature value as well as the status of the breach is
> is shown on the serial port (UART).

```c

void application_task ( void )
{
    float t_data;
    char alert;
    char alert_on;

    Delay_ms( 2000 );
    alert = thermo8_ale_get( &thermo8 );

    if ( alert == 0 )
    {
        t_data  = thermo8_get_temperature( &thermo8 );
        alert_on = thermo8_get_alert_stat( &thermo8 );
    }

    if ( alert_on & THERMO8_TLOWER_REACHED )
    {
        log_printf( &logger, "Temperature under the low limit: %.2f �C \r\n", t_data );
    }

    if ( alert_on & THERMO8_TUPPER_REACHED )
    {
        log_printf( &logger, "Temperature over the high limit: %.2f �C \r\n", t_data );
    } 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo8

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
