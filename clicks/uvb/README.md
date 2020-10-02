\mainpage Main Page
 
---
# UVB click

UVB Click is ultraviolet sensing board based on GUVB-C31SM sensor from GenUV, capable of measuring UV index between 0 to 16. UVB Click supports integrated functions of ultraviolet light sensors such that can be easily configured and used in user applications. Overexposure to UVB radiation not only can cause sunburn but also some forms of skin cancer, so knowing amount of UVB light can be quite important and this Click board™ is perfect solution for that task.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](https://www.mikroe.com/uvb-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Uvb Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Uvb Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void uvb_cfg_setup ( uvb_cfg_t *cfg ); 
 
- Initialization function.
> UVB_RETVAL uvb_init ( uvb_t *ctx, uvb_cfg_t *cfg );

- Click Default Configuration function.
> void uvb_default_cfg ( uvb_t *ctx );


#### Example key functions :

- This function checks communication.
> uint8_t uvb_check_communication ( uvb_t *ctx );
 
- This function gets UVB data.
> uint16_t uvb_get_uv_data ( uvb_t *ctx );

- This function configure register.
> void uvb_configuration ( uvb_t *ctx, uint8_t reg, uint8_t cfg );

## Examples Description

> This Click is ultraviolet sensing board, capable of measuring UV index between 0 to 16. 
> UVB Click supports integrated functions of ultraviolet light sensors.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init, check communication and configuration module for measurement. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uvb_cfg_t cfg;
    uint8_t check_com;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    uvb_cfg_setup( &cfg );
    UVB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uvb_init( &uvb, &cfg );

    check_com = uvb_check_communication( &uvb );
    if ( check_com == 0 )
    {
        log_printf( &logger, ">> Communication [OK]\r\n" );
    }
    else
    {
        log_printf( &logger, ">> Communication [ERROR]\r\n" );
        for( ; ; );
    }

    uvb_default_cfg ( &uvb );

    log_printf( &logger, ">> Configuration done !!!\r\n" );
    Delay_ms( 1500 );
}
  
```

### Application Task

> Reads UVB data and logs to the USBUART every 1500ms.

```c

void application_task ( void )
{
    uvb_data = uvb_get_uv_data( &uvb );

    log_printf( &logger, ">> UVB data: %d\r\n", uvb_data );

    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1500 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Uvb

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
