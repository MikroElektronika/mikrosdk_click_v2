 
---
# GNSS click

GNSS click carries Quectel’s L86 GNSS module with a patch antenna along with an external antenna connector.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnss_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Gnss Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gnss Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gnss_cfg_setup ( gnss_cfg_t *cfg ); 
 
- Initialization function.
> GNSS_RETVAL gnss_init ( gnss_t *ctx, gnss_cfg_t *cfg );

- Click Default Configuration function.
> void gnss_default_cfg ( gnss_t *ctx );


#### Example key functions :

- Wake-up module function
> void gnss_module_wakeup ( gnss_t *ctx );
 
- Generic read function.
> uint16_t gnss_generic_read ( gnss_t *ctx, char *data_buf, uint16_t max_len )

- Generic write function.
> void gnss_generic_write ( gnss_t *ctx, char *data_buf, uint16_t len );

## Examples Description

> This example reads and processes data from GNSS clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gnss_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gnss_cfg_setup( &cfg );
    GNSS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gnss_init( &gnss, &cfg );

    gnss_module_wakeup( &gnss );
   
    Delay_ms( 5000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    gnss_process(  );
    parser_application( current_parser_buf );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gnss

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
