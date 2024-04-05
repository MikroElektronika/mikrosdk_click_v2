\mainpage Main Page

---
# ESP8684 click

> ESP8664 Click is a compact add-on board that contains a wireless combo module. This board features the ESP8684-MINI-1, a highly integrated WiFi, and a Bluetooth 5 module from Espressif Systems. It simultaneously supports BSS in Station mode, SoftAP mode, Station + SoftAP mode, and promiscuous mode. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/esp8684_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/esp8684-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : UART type


# Software Support

We provide a library for the ESP8684 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ESP8684 Click driver.

#### Standard key functions :

- `esp8684_cfg_setup` Config Object Initialization function.
```c
void esp8684_cfg_setup ( esp8684_cfg_t *cfg );
```

- `esp8684_init` Initialization function.
```c
err_t esp8684_init ( esp8684_t *ctx, esp8684_cfg_t *cfg );
```

- `esp8684_default_cfg` Click Default Configuration function.
```c
void esp8684_default_cfg ( esp8684_t *ctx );
```

#### Example key functions :

- `esp8684_send_cmd` ESP8684 send command with arguments function.
```c
void esp8684_send_cmd ( esp8684_t *ctx, uint8_t *cmd, uint8_t *args );
```

- `esp8684_send_query_cmd` ESP8684 send query command function.
```c
void esp8684_send_query_cmd ( esp8684_t *ctx, uint8_t *cmd );
```

- `esp8684_connect_to_network` ESP8684 connect to network function.
```c
void esp8684_connect_to_network ( esp8684_t* ctx, uint8_t *ssid, uint8_t *password );
```

## Example Description

> This example connects to the desired WiFi network and then
  connects to the TCP/UDP server, writes then reads data to and from it.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wifi communication, then connects to the desired WiFi network
  and sends data to the TCP/UDP server.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    esp8684_cfg_t esp8684_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    esp8684_cfg_setup( &esp8684_cfg );
    ESP8684_MAP_MIKROBUS( esp8684_cfg, MIKROBUS_1 );
    if ( UART_ERROR == esp8684_init( &esp8684, &esp8684_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    esp8684_default_cfg( &esp8684 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    esp8684_process( );
    esp8684_clear_app_buf( );
    
    esp8684_send_cmd( &esp8684, ESP8684_CMD_AT, NULL );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    esp8684_send_cmd( &esp8684, ESP8684_CMD_RST, NULL );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_READY );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    esp8684_process( );
    esp8684_clear_app_buf();
    
    esp8684_send_cmd( &esp8684, ESP8684_CMD_GMR, NULL );
    app_error_flag = esp8684_rsp_check( ESP8684_RSP_OK );
    esp8684_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // Communication initialization
    esp8684_con_device_to_network ( );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writes and reads data from TCP/UDP server, processes all incoming data 
  and displays them on the USB UART.

```c
void application_task ( void ) 
{
    log_printf( &logger, "Sending and reading data from the TCP/UDP server \r\n" );
    esp8684_send_data( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ESP8684

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
