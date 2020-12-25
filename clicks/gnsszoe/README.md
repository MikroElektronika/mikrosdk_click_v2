\mainpage Main Page
 
---
# GNSS ZOE click

GNSS ZOE Click is a evaluation board for ultra small ZOE-M8Q GNSS SiP receiver from u-blox. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnsszoe_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/gnss-zoe-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Gnsszoe Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gnsszoe Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gnsszoe_cfg_setup ( gnsszoe_cfg_t *cfg ); 
 
- Initialization function.
> GNSSZOE_RETVAL gnsszoe_init ( gnsszoe_t *ctx, gnsszoe_cfg_t *cfg );

- Click Default Configuration function.
> void gnsszoe_default_cfg ( gnsszoe_t *ctx );


#### Example key functions :

- Generic read function
> void gnsszoe_generic_read ( gnsszoe_t *ctx, char *rsp )
 
- Reset module function
> void gnsszoe_module_reset ( gnsszoe_t *ctx );

- Generic parser function.
> gnsszoe_error_t gnsszoe_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );

## Examples Description

> This example reads and processes data from GNSS ZOE clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gnsszoe_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    
    //  Click initialization.

    gnsszoe_cfg_setup( &cfg );
    GNSSZOE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gnsszoe_init( &gnsszoe, &cfg );

    gnsszoe_module_reset( &gnsszoe );

    Delay_ms( 1000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    gnsszoe_process(  );
    parser_application( current_parser_buf );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gnsszoe

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
