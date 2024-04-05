
---
# Wifi ESP click

> WiFi ESP click carries the ESP-WROOM-02 module that integrates ESP8266EX.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/wifiesp_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/wifi-esp-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the WifiEsp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for WifiEsp Click driver.

#### Standard key functions :

- `wifiesp_cfg_setup` Config Object Initialization function.
```c
void wifiesp_cfg_setup ( wifiesp_cfg_t *cfg ); 
```

- `wifiesp_init` Initialization function.
```c
err_t wifiesp_init ( wifiesp_t *ctx, wifiesp_cfg_t *cfg );
```

- `wifiesp_default_cfg` Click Default Configuration function.
```c
void wifiesp_default_cfg ( wifiesp_t *ctx );
```

#### Example key functions :

- `wifiesp_send_cmd` Sends AT command to the module.
```c
void wifiesp_send_cmd( wifiesp_t* ctx, uint8_t* cmd, uint8_t* args );
```

- `wifiesp_generic_write` Generic write function.
```c
void wifiesp_generic_write ( wifiesp_t *ctx, char *data_buf, uint16_t len );
```

- `wifiesp_generic_read` Generic read function.
```c
int32_t wifiesp_generic_read ( wifiesp_t *ctx, char *data_buf, int32_t max_len );
```

## Example Description

> This example connects to the desired WiFi network and then
> creates web server on the IP address assigned to the click board.
> The user can connect to the server via web browser.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wifi communication, then connects to the desired WiFi network
> and creates web server on the IP address assigned to the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifiesp_cfg_t cfg;
    
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

    // Click initialization.
    wifiesp_cfg_setup( &cfg );
    WIFIESP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifiesp_init( &wifiesp, &cfg );
    wifiesp_default_cfg( &wifiesp );
    Delay_ms ( 1000 );
    
    // Communication initialization
    wifi_communication_init( );
    
    uint16_to_str ( strlen( page ), page_len );
    wifiesp_str_cut_chr ( page_len, ' ' );
    
    log_info( &logger, "Please connect to the IP address listed above.\r\n" );
}
  
```

### Application Task

> Waits for the client request (paste IP address in your web browser and 
> refresh to send a request).
> The click board will respond by sending a page content to the client.

```c

void application_task ( void )
{
    if ( WIFIESP_OK == wifiesp_rsp_check( WIFIESP_RECEIVE ) ) 
    {
        link_id[ 0 ] = *( strstr( app_buf, WIFIESP_RECEIVE ) + 5 );
        strcpy ( send_buf, link_id );
        strcat ( send_buf, "," );
        strcat ( send_buf, page_len );
        wifiesp_str_cut_chr ( send_buf, ' ' );
        wifiesp_log_app_buf( );
        wifiesp_clear_app_buf( );
        Delay_ms ( 100 );
        wifiesp_process( );
        wifiesp_log_app_buf( );
        wifiesp_send_cmd( &wifiesp, WIFIESP_SEND, send_buf );
        app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_READY_FOR_SEND );
        wifiesp_log_app_buf( );
        Delay_ms ( 100 );
        wifiesp_generic_write( &wifiesp, page, strlen( page ) );
        app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_SEND_OK );
        wifiesp_error_check( app_error_flag );
        wifiesp_send_cmd( &wifiesp, WIFIESP_CLOSE, link_id );
        app_error_flag = wifiesp_rsp_check( WIFIESP_RSP_OK );
        wifiesp_error_check( app_error_flag );
        wifiesp_clear_app_buf( );
        
        wifiesp_process( );
        wifiesp_log_app_buf( );
        wifiesp_clear_app_buf( );
        uart_clear ( &wifiesp.uart );
        Delay_ms ( 100 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.WifiEsp

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
