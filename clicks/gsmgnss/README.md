\mainpage Main Page
 
---
# GSM GNSS click

GSM/GNSS click combines GPS/GLONASS location tracking with GSM module capability for mobile communication.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gsmgnss_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/gsm-gnss-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : apr 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the GsmGnss Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for GsmGnss Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gsmgnss_cfg_setup ( gsmgnss_cfg_t *cfg ); 
 
- Initialization function.
> GSMGNSS_RETVAL gsmgnss_init ( gsmgnss_t *ctx, gsmgnss_cfg_t *cfg );

- Click Default Configuration function.
> void gsmgnss_default_cfg ( gsmgnss_t *ctx );


#### Example key functions :

- Generic read function.
> uint16_t gsmgnss_generic_read ( gsmgnss_t *ctx, char *data_buf, uint16_t max_len );
 
- Generic parser function.
> gsmgnss_error_t gsm_gnss_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );

- This function sends comamnd.
> void gsmgnss_send_command ( gsmgnss_t *ctx, char *command );

## Examples Description

> This example reads and processes data from GSM GNSS clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gsmgnss_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gsmgnss_cfg_setup( &cfg );
    GSMGNSS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsmgnss_init( &gsmgnss, &cfg );

    gsmgnss_module_wakeup( &gsmgnss );

    Delay_ms( 2000 );

    gsmgnss_process(  );

    gsmgnss_send_command( &gsmgnss, GSMGNSS_SINGLE_CMD_AT );
    gsmgnss_process( );
    gsmgnss_send_command( &gsmgnss, GSMGNSS_SINGLE_CMD_ATI );
    gsmgnss_process( );
    gsmgnss_send_command( &gsmgnss, GSMGNSS_SINGLE_CMD_ATE0 );
    gsmgnss_process( );
    gsmgnss_send_command( &gsmgnss, GSMGNSS_SINGLE_CMD_IFC );
    gsmgnss_process( );
    gsmgnss_send_command( &gsmgnss, GSMGNSS_SINGLE_CMD_CMGF );
    gsmgnss_process(  );
    log_printf( &logger, "\r\n---- GSM Init done ---\r\n" );
    
    gsmgnss_send_command( &gsmgnss, GSMGNSS_SINGLE_CMD_QGNSSC );
    gsmgnss_process(  );
    log_printf( &logger, "\r\n---- GNSS Init done ---\r\n" );

    init_flag = 0;

    Delay_ms( 3000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    gsmgnss_process(  );
    
    if ( send_data_cnt == 3 )
    {
        gsmgnss_send_command( &gsmgnss, GSMGNSS_SINGLE_CMD_QGNSSRD );
        gsmgnss_process( );
        parser_application( current_parser_buf );
       send_data_cnt = 0;
    }
    send_data_cnt++;
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.GsmGnss

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
