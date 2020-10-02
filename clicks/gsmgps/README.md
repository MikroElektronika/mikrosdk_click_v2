\mainpage Main Page
 
---
# GSMGPS click

GSM-GPS click is a mikroBUS add-on board with a SIM808 module that combines GSM/GPRS and GPS into a single device. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gsmgps_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/gsm-gps-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Gsmgps Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gsmgps Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gsmgps_cfg_setup ( gsmgps_cfg_t *cfg ); 
 
- Initialization function.
> GSMGPS_RETVAL gsmgps_init ( gsmgps_t *ctx, gsmgps_cfg_t *cfg );

- Click Default Configuration function.
> void gsmgps_default_cfg ( gsmgps_t *ctx );


#### Example key functions :

- Generic parser function.
> gsmgps_error_t gsm_gps_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );
 
- Command function.
> void gsmgps_send_command ( gsmgps_t *ctx, char *command );

- Generic read function.
> uint16_t gsmgps_generic_read ( gsmgps_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example reads and processes data from GSMGPS clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gsmgps_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gsmgps_cfg_setup( &cfg );
    GSMGPS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsmgps_init( &gsmgps, &cfg );

    gsmgps_process(  );

    gsmgps_send_command( &gsmgps, GSMGPS_SINGLE_CMD_AT );
    gsmgps_process( );
    gsmgps_send_command( &gsmgps, GSMGPS_SINGLE_CMD_ATI );
    gsmgps_process( );
    gsmgps_send_command( &gsmgps, GSMGPS_SINGLE_CMD_ATE0 );
    gsmgps_process( );
    gsmgps_send_command( &gsmgps, GSMGPS_SINGLE_CMD_CMGF );
    gsmgps_process( );
    gsmgps_send_command( &gsmgps, GSMGPS_CMD_AT_CSCS );
    gsmgps_process( );
    log_printf( &logger, "\r\n---- GSM Init done ---\r\n" );

    gsmgps_send_command( &gsmgps, GSMGPS_CMD_CGNSPWR );
    gsmgps_process(  );
    log_printf( &logger, "\r\n---- GNSS Init done ---\r\n" );

    init_flag = 0;

    Delay_ms( 2000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    gsmgps_process(  );
    
    if ( send_data_cnt == 3 )
    {
        gsmgps_send_command( &gsmgps, GSMGPS_CMD_CGNSSEQ );
        gsmgps_send_command( &gsmgps, GSMGPS_CMD_CGNSINF );
        gsmgps_process( );
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
- Click.Gsmgps

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
