\mainpage Main Page

---
# WiFi BLE click

WiFi BLE click is a Click board™ which provides WiFi and BT/BLE connectivity for any embedded application.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/wifible_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/wifi-ble-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the WifiBle Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for WifiBle Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void wifible_cfg_setup ( wifible_cfg_t *cfg ); 
 
- Initialization function.
> WIFIBLE_RETVAL wifible_init ( wifible_t *ctx, wifible_cfg_t *cfg );

#### Example key functions :

- Power module.
> void wifible_module_power ( wifible_t *ctx, uint8_t power_state );
 
- Generic read function.
> uint16_t wifible_generic_read ( wifible_t *ctx, char *data_buf, uint16_t max_len );

- GFunction for send command.
> void wifible_send_command ( wifible_t *ctx, char *command );

## Examples Description

> This example reads and processes data from WiFi BLE clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver, power init and info module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifible_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wifible_cfg_setup( &cfg );
    WIFIBLE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifible_init( &wifible, &cfg );

    //  MODULE POWER ON
    
    wifible_module_power( &wifible, 1 );
    Delay_ms( 2000 );

    wifible_process( );
    
    //  MODULE INIT AND INFO
    
    wifible_send_command( &wifible, AT );
    wifible_process( );
    
    log_printf( &logger, "---- AT ---- \r\n " );
    wifible_send_command( &wifible, AT );
    wifible_process( );

    log_printf( &logger, "---- ATE ---- \r\n " );
    wifible_send_command( &wifible, ATE );
    wifible_process( );

    log_printf( &logger, "---- AT_GMR ---- \r\n " );
    wifible_send_command( &wifible, AT_GMR );
    wifible_process( );
    
    log_printf( &logger, "---- AT_UART ---- \r\n " );
    wifible_send_command( &wifible, AT_UART_CUR );
    wifible_process( ); 

    log_printf( &logger, "----- START EXAMPLE ----- \r\n" );
}
  
```

### Application Task

> Connected to TCP and BLE server, and reads data.

```c

void application_task ( void )
{
#ifdef WIRELESS_CONNECTION
    wifi_tcp_server( );
#endif    

#ifdef BLUETOOTH_CONNECTION
    ble_i_beacon( );
#endif    
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.WifiBle

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
