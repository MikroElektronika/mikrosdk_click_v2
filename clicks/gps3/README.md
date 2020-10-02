\mainpage Main Page
 
---
# GPS3 click

GPS3 click carries Quectel’s L80 GPS module, a high-sensitivity ultra slim GPS module with a patch antenna.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gps3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/gps-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Gps3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gps3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gps3_cfg_setup ( gps3_cfg_t *cfg ); 
 
- Initialization function.
> GPS3_RETVAL gps3_init ( gps3_t *ctx, gps3_cfg_t *cfg );

- Click Default Configuration function.
> void gps3_default_cfg ( gps3_t *ctx );


#### Example key functions :

- Wake-up module.
> void gps3_module_wakeup ( gps3_t *ctx );
 
- Generic parser function.
> gps3_error_t gps3_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );

- Generic read function
> uint16_t gps3_generic_read ( gps3_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example reads and processes data from GPS3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gps3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gps3_cfg_setup( &cfg );
    GPS3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gps3_init( &gps3, &cfg );

    gps3_module_wakeup( &gps3 );
    Delay_ms( 5000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    gps3_process(  );
    parser_application( current_parser_buf );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gps3

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
