\mainpage Main Page
 
 

---
# Current 2 click

Current 2 click is an accurate current sensing Click board™ suitable for a very accurate measurement of the current through the load.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/current2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/current-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the current2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for current2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void current2_cfg_setup ( current2_cfg_t *cfg ); 
 
- Initialization function.
> CURRENT2_RETVAL current2_init ( current2_t *ctx, current2_cfg_t *cfg );

#### Example key functions :

- Get ADC function
> uint16_t current2_get_adc ( current2_t *ctx );
 
- Get Averaged ADC function
> uint16_t current2_get_average_adc ( current2_t *ctx, uint8_t n_samp );

- Get Current function
> uint16_t current2_get_current ( current2_t *ctx, uint8_t n_sample );

## Examples Description

> This application measures current.

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI interface in Mode 0

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    current2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    current2_cfg_setup( &cfg );
    CURRENT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    current2_init( &current, &cfg );
    Delay_ms( 300 );
    log_printf( &logger, "Current 2 is initialized \r\n \r\n" );
}
  
```

### Application Task

> Reads the current averaged result of 20 samples and
> gets this result in a proper value [mA]. Repeats the current reading every 500ms.

```c

void application_task ( void )
{
    uint16_t tmp;

    tmp = current2_get_current( &current, 20 );

    log_printf( &logger, "Current : %d mA \r\n", tmp );

    Delay_ms( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.current2

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
