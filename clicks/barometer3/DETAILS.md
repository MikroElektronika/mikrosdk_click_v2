
---
# Barometer 3 click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Barometer3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Barometer3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void barometer3_cfg_setup ( barometer3_cfg_t *cfg ); 
 
- Initialization function.
> BAROMETER3_RETVAL barometer3_init ( barometer3_t *ctx, barometer3_cfg_t *cfg );

- Click Default Configuration function.
> void barometer3_def_cfg ( barometer3_t *ctx );


#### Example key functions :

- Get Raw Measurement results
> void  barometer3_get_raw_res ( barometer3_t *ctx, uint8_t reg_adr, int32_t *raw );
 
- Get Single measurement function
> uint8_t barometer3_get_single_res ( barometer3_t *ctx, float *result );

- Get Pressure Measurement Once function
> uint8_t barometer3_meas_prs_once ( barometer3_t *ctx, float *result, uint8_t prs_osr );

## Examples Description

> This demo app measures pressure.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and configuration module for measurement.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    barometer3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    barometer3_cfg_setup( &cfg );
    BAROMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barometer3_init( &barometer3, &cfg );

    Delay_ms( 100 );

    barometer3_def_cfg( &barometer3 );
    Delay_ms( 100 );

    status_val = barometer3_meas_prs_once( &barometer3, &pressure, BAROMETER3_PM_PRC_128 );
    Delay_ms( 100 );

    if ( status_val != BAROMETER3_SUCCESS )
    {
        log_printf( &logger, "FAIL! Err. code: %d \r\n", status_val );
    }
    
    Delay_ms( 100 );
}
  
```

### Application Task

> Reads Pressure data in Pascal [ Pa ]. Results are being sent to the Usart Terminal 
> where you can track their changes. All data logs write on USB uart changes for every 1 sec.

```c

void application_task ( void )
{
    status_val = barometer3_meas_prs_once( &barometer3, &pressure, BAROMETER3_PM_PRC_128 );

    if ( status_val == BAROMETER3_SUCCESS )
    {
        log_printf( &logger, " Pressure: %.2f Pa \r\n", pressure );
        log_printf( &logger, "----------------------- \r\n" );
        Delay_ms( 1000 );
    }
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer3

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
