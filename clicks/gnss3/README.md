\mainpage Main Page
 
---
# GNSS3 click

GNSS3 click carries SIMCom’s SIM33ELA standalone GNSS module with an integrated antenna (and a connector for an external one).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnss3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Gnss3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gnss3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gnss3_cfg_setup ( gnss3_cfg_t *cfg ); 
 
- Initialization function.
> GNSS3_RETVAL gnss3_init ( gnss3_t *ctx, gnss3_cfg_t *cfg );

- Click Default Configuration function.
> void gnss3_default_cfg ( gnss3_t *ctx );


#### Example key functions :

- Generic parser function.
> gnss3_error_t gnss3_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );
 
- Generic read function.
> int32_t gnss3_generic_read ( gnss3_t *ctx, char *data_buf, uint16_t max_len );

- Wake-up module.
> void gnss3_module_wakeup ( gnss3_t *ctx );

## Examples Description

> This example reads and processes data from GNSS3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gnss3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gnss3_cfg_setup( &cfg );
    GNSS3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gnss3_init( &gnss3, &cfg );

    gnss3_module_wakeup( &gnss3 );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    gnss3_process(  );
    parser_application( current_parser_buf );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gnss3

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
