\mainpage Main Page
 
---
# Surface temp 2 click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the SurfaceTemp2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SurfaceTemp2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void surfacetemp2_cfg_setup ( surfacetemp2_cfg_t *cfg ); 
 
- Initialization function.
> SURFACETEMP2_RETVAL surfacetemp2_init ( surfacetemp2_t *ctx, surfacetemp2_cfg_t *cfg );

#### Example key functions :

- Get Temperature function
> float surfacetemp2_get_temperature ( surfacetemp2_t *ctx );
 
- Set Critical Temperature Threshold function
> void surfacetemp2_set_crit_trsh ( surfacetemp2_t *ctx, float trsh );

- Get CT pin state function
> uint8_t surfacetemp2_get_ct_pin ( surfacetemp2_t *ctx );

## Examples Description

> This demo app shows capabilities of Surface temp 2 Click.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver and sets up the device. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    surfacetemp2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    surfacetemp2_cfg_setup( &cfg );
    SURFACETEMP2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    surfacetemp2_init( &surfacetemp2, &cfg );

    setup_val = SURFACETEMP2_CFG_FLT_Q_4 | SURFACETEMP2_CFG_CT_MODE | SURFACETEMP2_CFG_RES_16;
    surfacetemp2_setup ( &surfacetemp2, setup_val );
    surfacetemp2_set_high_trsh( &surfacetemp2, 40.00 );
    surfacetemp2_set_low_trsh( &surfacetemp2, 10.00 );
    surfacetemp2_set_crit_trsh( &surfacetemp2, 70.00 );
    surfacetemp2_set_hys_val( &surfacetemp2, 5 );
    log_printf( &logger, "--- Initialized! --- \r\n" );
    log_printf( &logger, "-------------------- \r\n" );
    Delay_ms( 1000 );
}
  
```

### Application Task

> This example shows capabilities of Surface temp 2 Click
> board by reading temperature and displaying the 
> results via USART terminal.

```c

void application_task ( void )
{
    temperature = surfacetemp2_get_temperature( &surfacetemp2 );
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    Delay_ms( 2000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.SurfaceTemp2

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
