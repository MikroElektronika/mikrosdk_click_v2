\mainpage Main Page
 
---
# Nano GPS 2 click

Nano GPS 2 Click features the smallest GPS module with an integrated patch antenna, the ORG1510-MK05 a module from OriginGPS.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nanogps2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/nano-gps-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the NanoGps2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for NanoGps2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void nanogps2_cfg_setup ( nanogps2_cfg_t *cfg ); 
 
- Initialization function.
> NANOGPS2_RETVAL nanogps2_init ( nanogps2_t *ctx, nanogps2_cfg_t *cfg );

#### Example key functions :

- Set EN pin.
> void nanogps2_set_en_pin_state ( nanogps2_t *ctx, uint8_t state );
 
- Send command.
> void nanogps2_send_cmd ( nanogps2_t *ctx, uint8_t *cmd );

- Generic parser function.
> nanogps2_error_t nanogps2_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );

## Examples Description

> This example reads and processes data from Nano GPS 2 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    nanogps2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    nanogps2_cfg_setup( &cfg );
    NANOGPS2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanogps2_init( &nanogps2, &cfg );

    nanogps2_set_fon_pin_state( &nanogps2, 0 );
    nanogps2_set_wkp_pin_state( &nanogps2, 1 );
    nanogps2_set_en_pin_state( &nanogps2, 1 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    nanogps2_process( );
    parser_application( current_parser_buf );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoGps2

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
