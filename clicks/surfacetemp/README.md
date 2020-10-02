\mainpage Main Page
 
---
# Surface temp click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the SurfaceTemp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SurfaceTemp Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void surfacetemp_cfg_setup ( surfacetemp_cfg_t *cfg ); 
 
- Initialization function.
> SURFACETEMP_RETVAL surfacetemp_init ( surfacetemp_t *ctx, surfacetemp_cfg_t *cfg );

#### Example key functions :

- Getting temperature value
> float surfacetemp_get_temperature ( surfacetemp_t *ctx );
 
- Setting hysteresis value
> uint8_t surfacetemp_set_hysteresis ( surfacetemp_t *ctx, uint8_t hysteresis );

- Device initialization
> uint8_t surfacetemp_setup ( surfacetemp_t *ctx );

## Examples Description

> This application demo measures temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver, click board and sets thresholds.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    surfacetemp_cfg_t cfg;

    uint8_t status;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- System Init ----" );

    //  Click initialization.

    surfacetemp_cfg_setup( &cfg );
    SURFACETEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    surfacetemp_init( &surfacetemp, &cfg );

    status = surfacetemp_setup( &surfacetemp );

    surfacetemp_set_high_threshold( &surfacetemp, 40.00 );
    surfacetemp_set_low_threshold( &surfacetemp, 10.00 );
    surfacetemp_set_critical_threshold( &surfacetemp, 70.00 );
    surfacetemp_set_hysteresis( &surfacetemp, 0 );

    if ( status == 0 )
    {
        log_printf( &logger, "--- INIT DONE --- \r\n" );
    }
    else
    {
        log_printf( &logger, "--- INIT ERROR --- \r\n" );
        for( ; ; );
    }
}
  
```

### Application Task

> Reads temperature value and value log on the USBUART.

```c

void application_task ( void )
{
    float temperature;

    temperature = surfacetemp_get_temperature( &surfacetemp );
    log_printf( &logger, "> Temperature : %.2f \r\n", temperature );
    Delay_ms( 1500 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.SurfaceTemp

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
