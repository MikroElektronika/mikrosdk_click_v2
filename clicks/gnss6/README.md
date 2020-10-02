\mainpage Main Page
 
---
# GNSS6 click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](< <CLICK_PRODUCT_PAGE_LINK> > )

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : mar 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Gnss6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gnss6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gnss6_cfg_setup ( gnss6_cfg_t *cfg ); 
 
- Initialization function.
> GNSS6_RETVAL gnss6_init ( gnss6_t *ctx, gnss6_cfg_t *cfg );


#### Example key functions :

- Generic parser function.
> gnss6_error_t gnss6_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );
 
- Wake-up module.
> void gnss6_module_wakeup ( gnss6_t *ctx );

## Examples Description

> This example reads and processes data from GNSS 6 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    gnss6_cfg_t cfg;

    //  Logger initialization.
    
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gnss6_cfg_setup( &cfg );
    GNSS6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gnss6_init( &gnss6, &cfg );
    
    gnss6_module_wakeup( &gnss6 );
    Delay_ms( 500 );
}
```

### Application Task

> Reads the received data and parses it.

```c
void application_task ( void )
{
    gnss6_process(  );
    parser_application( current_parser_buf );
}
```

## Additional Function

> gnss6_process ( ) - The general process of collecting presponce that sends a module.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gnss6

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
