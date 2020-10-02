\mainpage Main Page
 
---
# WiFi 11 click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Wifi11 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Wifi11 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void wifi11_cfg_setup ( wifi11_cfg_t *cfg ); 
 
- Initialization function.
> WIFI11_RETVAL wifi11_init ( wifi11_t *ctx, wifi11_cfg_t *cfg );

#### Example key functions :

- Device reset
> void wifi11_reset_device ( wifi11_t *ctx );
 
- Send command
> void wifi11_send_command ( wifi11_t *ctx, char *command );

- Connect to AP
> void wifi11_set_conect_to_ap( wifi11_t *ctx, char *username, char *password );

## Examples Description

> This example reads and processes data from WiFi 11 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver module and stert sends AT comands.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifi11_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wifi11_cfg_setup( &cfg );
    WIFI11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifi11_init( &wifi11, &cfg );

    Delay_ms( 200 );
    wifi11_reset_device( &wifi11 );
    Delay_ms( 5000 );
    
    log_printf( &logger, "---- Start test command ----- \r\n" );
    wifi11_send_command( &wifi11, WIFI11_CMD_AT );
    wifi11_process( );
    Delay_ms( 200 );
    wifi11_send_command( &wifi11, WIFI11_CMD_ATSV );
    wifi11_process( );
    Delay_ms( 200 );
    log_printf( &logger, "---- WiFi configuration ----- \r\n" );
    wifi11_send_command( &wifi11, WIFI11_CMD_ATPW );
    wifi11_process( );
    Delay_ms( 1000 );
    wifi11_set_conect_to_ap( &wifi11, &wifi11_net_username[ 0 ], &wifi11_net_password[ 0 ] );
    wifi11_process( );
    Delay_ms( 10000 );
    wifi11_send_command( &wifi11, WIFI11_CMD_ATW );
    wifi11_process( );
    Delay_ms( 1000 );
    log_printf( &logger, "---- TCP example (Client) ----- \r\n" );
    wifi11_send_command( &wifi11, WIFI11_CMD_ATPC );
    wifi11_process( );
    Delay_ms( 10000 );
    wifi11_send_command( &wifi11, WIFI11_CMD_ATPT );
    wifi11_process( );
    Delay_ms( 1000 );
    wifi11_send_command( &wifi11, WIFI11_CMD_ATPK );
    wifi11_process( );
    Delay_ms( 1000 );
}
  
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Wifi11

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
