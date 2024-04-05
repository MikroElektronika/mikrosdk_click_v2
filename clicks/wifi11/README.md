\mainpage Main Page
 
---
# WiFi 11 click

WiFi 11 Click is a compact add-on board that contains a WiFi and Bluetooth module that has dual bands for WiFi communication. This board features the BW16, a low-power dual bands Wireless LAN (WLAN) and Bluetooth Low Energy SoC module from Ai-Thinker.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/wifi11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/wifi-11-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Wifi11 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Wifi11 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void wifi11_cfg_setup ( wifi11_cfg_t *cfg ); 
 
- Initialization function.
> WIFI11_RETVAL wifi11_init ( wifi11_t *ctx, wifi11_cfg_t *cfg );

- Device reset function.
> void wifi11_reset_device ( wifi11_t *ctx );

#### Example key functions :

- Send command function.
> void wifi11_send_cmd ( wifi11_t *ctx, char *cmd );
 
- Create TCP/UDP server function.
> void wifi11_create_tcp_udp_server ( wifi11_t *ctx, uint8_t mode, uint16_t port );

- Connect to AP function.
> void wifi11_connect_to_ap ( wifi11_t *ctx, char *ssid, char *password );

## Examples Description

> This example reads and processes data from WiFi 11 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and powers up the module, then connects to the desired AP
> and creates TCP and UDP servers on the desired local port.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifi11_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wifi11_cfg_setup( &cfg );
    WIFI11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifi11_init( &wifi11, &cfg );
    Delay_ms ( 100 );
    
    wifi11_reset_device( &wifi11 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // dummy read
    wifi11_process( );
    wifi11_clear_app_buf( );
    
    log_printf( &logger, "\r\n ---- Common commands ---- \r\n" );
    Delay_ms ( 500 );
    
    // Test AT command ready
    wifi11_send_cmd( &wifi11, WIFI11_CMD_AT );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms ( 500 );

    // Query version info
    wifi11_send_cmd( &wifi11, WIFI11_CMD_ATSV );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    log_printf( &logger, "\r\n ---- WiFi commands ---- \r\n" );
    Delay_ms ( 500 );
    
    // Set WiFi mode - Station
    wifi11_send_cmd_with_parameter( &wifi11, WIFI11_CMD_ATPW, "1" );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // Connect to AP
    wifi11_connect_to_ap( &wifi11, AP_SSID, AP_PASSWORD );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // Wifi information
    wifi11_send_cmd( &wifi11, WIFI11_CMD_ATW );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    log_printf( &logger, "\r\n ---- TCP/IP commands ---- \r\n" );
    Delay_ms ( 500 );
    
    // Create TCP Server
    wifi11_create_tcp_udp_server( &wifi11, WIFI11_TCP_MODE, LOCAL_PORT );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // Create UDP Server
    wifi11_create_tcp_udp_server( &wifi11, WIFI11_UDP_MODE, LOCAL_PORT );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // Enable auto receive data mode
    wifi11_send_cmd_with_parameter( &wifi11, WIFI11_CMD_ATPK, "1" );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // Check network connection status
    wifi11_send_cmd( &wifi11, WIFI11_CMD_ATPI );
    app_error_flag = wifi11_rsp_check( );
    wifi11_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    log_printf( &logger, "\r\n ---- Please connect to the TCP/UDP server listed above via" );
    log_printf( &logger, " a TCP/UDP client ---- \r\n" ); 
}
  
```

### Application Task

> Logs all the received data and module's responses on the USB UART.

```c

void application_task ( void )
{
    wifi11_process( );
    wifi11_log_app_buf( );
} 

```

## Note

> In order for the example to work, user needs to set the AP SSID, password, and Local port
> on which the TCP and UDP servers will be created.
> Enter valid data for the following macros: AP_SSID, AP_PASSWORD and LOCAL_PORT.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Wifi11

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
