\mainpage Main Page
 
---
# Ambient 9 click

Ambient 9 Click is a compact add-on board that contains an integrated ambient light sensing and proximity detector with IR LED in an optical module. This board features the APDS-9160-003, digital ALS, and IR sensing, an IR LED, and a complete proximity sensing solution from Broadcom Limited, that is fit to be used under a small aperture of the devices cover windows. It has a wide dynamic range, the proximity detection feature operates well from bright sunlight to dark rooms, and both the PS and ALS functions independently provides maximum flexibility in applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient9_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/ambient-9-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ambient9_cfg_setup ( ambient9_cfg_t *cfg ); 
 
- Initialization function.
> AMBIENT9_RETVAL ambient9_init ( ambient9_t *ctx, ambient9_cfg_t *cfg );

#### Example key functions :

- Generic function for reading ALS data from senso
> uint32_t ambient9_als_data ( ambient9_t *ctx );
 
- Generic function for reading proximity data from sensor
> uint16_t ambient9_proxy_data ( ambient9_t *ctx );

- Function for enabeling sensor for ALS or proximity
> void ambient9_enable_data ( ambient9_t *ctx, uint8_t als_ps );

## Examples Description

> This application collects data from the sensor and then logs it.

**The demo application is composed of two sections :**

### Application Init 

> Reads device status if it's power on and part ID, then enables one of two sensor reading values.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient9_cfg_t cfg;

    uint8_t status_data;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ambient9_cfg_setup( &cfg );
    AMBIENT9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient9_init( &ambient9, &cfg );

    ambient9_generic_read( &ambient9, AMBIENT9_REG_PART_ID, &status_data, 1 );
    if ( AMBIENT9_PART_ID_VAL != status_data )
    {
        log_printf( &logger, " *****  ERROR!  ***** \r\n" );
        for( ; ; );
    }
    ambient9_generic_read( &ambient9, AMBIENT9_REG_MAIN_STATUS, &status_data, 1 );
    if ( AMBIENT9_POWER_ON == ( status_data & AMBIENT9_POWER_ON ) )
    {
        log_printf( &logger, " *****  ERROR!  ***** \r\n" );
        for( ; ; );
    }
    
    dev_mode = AMBIENT9_PROXY;
    ambient9_enable_data( &ambient9, dev_mode );  

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
    Delay_ms( 500 );
}
  
```

### Application Task

> Read one of two sleceted sensor values every 100ms.

```c

void application_task ( void )
{
    uint16_t proxy_data;
    uint32_t als_data;

    if ( AMBIENT9_ALS == dev_mode )
    {
        als_data = ambient9_als_data( &ambient9 );
        log_printf( &logger, " - ALS data: %ld \r\n", als_data );
    }
    else if ( AMBIENT9_PROXY == dev_mode )
    {
        proxy_data = ambient9_proxy_data( &ambient9 );
        log_printf( &logger, " - Proximity data: %d \r\n", proxy_data );
    }
    Delay_ms( 100 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient9

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
