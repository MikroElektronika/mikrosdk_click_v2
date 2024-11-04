
---
# LP WiFi Click

LP WiFi Click is a compact add-on board that represents an ultra-low-power Wi-Fi solution. This board features the DA16200, a fully integrated Wi-Fi module with ultra-low power consumption, best RF performance, and a comfortable development environment from Dialog Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lpwifi_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lp-wifi-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2021.
- **Type**          : UART type


# Software Support

We provide a library for the LPWiFi Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LPWiFi Click driver.

#### Standard key functions :

- `lpwifi_cfg_setup` Config Object Initialization function.
```c
void lpwifi_cfg_setup ( lpwifi_cfg_t *cfg );
```

- `lpwifi_init` Initialization function.
```c
err_t lpwifi_init ( lpwifi_t *ctx, lpwifi_cfg_t *cfg );
```

- `lpwifi_default_cfg` Click Default Configuration function.
```c
void lpwifi_default_cfg ( lpwifi_t *ctx );
```

#### Example key functions :

- `lpwifi_send_cmd` Send command function.
```c
void lpwifi_send_cmd ( lpwifi_t *ctx, char *cmd );
```

- `lpwifi_connect_to_ap` Connect to AP function.
```c
void lpwifi_connect_to_ap ( lpwifi_t *ctx, char *ssid, char *password );
```

- `lpwifi_factory_reset_device` Device factory reset function.
```c
void lpwifi_factory_reset_device ( lpwifi_t *ctx );
```

## Example Description

> This example reads and processes data from LP WiFi clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and powers up the module, then connects to the desired AP and creates TCP and UDP servers on the desired local port.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lpwifi_cfg_t lpwifi_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );

    // Click initialization.

    lpwifi_cfg_setup( &lpwifi_cfg );
    LPWIFI_MAP_MIKROBUS( lpwifi_cfg, MIKROBUS_1 );
    err_t init_flag = lpwifi_init( &lpwifi, &lpwifi_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    lpwifi_default_cfg( &lpwifi );
    Delay_ms ( 500 );
    
    // Initiate the communication
    lpwifi_send_cmd( &lpwifi, LPWIFI_CMD_AT );
    Delay_ms ( 1000 );
    
    // Dummy read
    lpwifi_process( );
    lpwifi_clear_app_buf( );
    
    log_printf( &logger, "\r\n --- Factory reset --- \r\n" );
    lpwifi_factory_reset_device ( &lpwifi );
    Delay_ms ( 500 );
    // Enable Echo
    lpwifi_send_cmd( &lpwifi, LPWIFI_CMD_ATE );
    app_error_flag = lpwifi_rsp_check( );
    lpwifi_error_check( app_error_flag );
    Delay_ms ( 500 );
    log_printf( &logger, " ----------------------------------------------- \r\n" );
    
    log_printf( &logger, "\r\n --- Connecting to the access point --- \r\n" );
    // Connect to AP
    lpwifi_connect_to_ap( &lpwifi, AP_SSID, AP_PASSWORD );
    app_error_flag = lpwifi_rsp_check( );
    lpwifi_error_check( app_error_flag );
    lpwifi_check_connection();
    while ( CONNECTED_TO_AP != app_connection_status )
    {
        lpwifi_check_connection();
        if ( NOT_CONNECTED_TO_AP == app_connection_status )
        {
            Delay_ms ( 500 );
            app_connection_status = WAIT_FOR_CONNECTION;

            // Connect to AP
            lpwifi_connect_to_ap( &lpwifi, AP_SSID, AP_PASSWORD );
            app_error_flag = lpwifi_rsp_check( );
            lpwifi_error_check( app_error_flag );
        }
    }
    log_printf( &logger, " ----------------------------------------------- \r\n" );
    log_printf( &logger, "\r\n --- Creating a TCP server --- \r\n" );
    // Create TCP Server
    lpwifi_create_tcp_server( &lpwifi, LOCAL_PORT );
    app_error_flag = lpwifi_rsp_check( );
    lpwifi_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    log_printf( &logger, " ----------------------------------------------- \r\n" );
    log_printf( &logger, "\r\n --- Creating a UDP socket --- \r\n" );
    // Create UDP socket
    lpwifi_create_udp_socket( &lpwifi, LOCAL_PORT );
    app_error_flag = lpwifi_rsp_check( );
    lpwifi_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    log_printf( &logger, " ----------------------------------------------- \r\n" );
    log_printf( &logger, " TCP server and UDP socket are available at: \r\n" );
    log_printf( &logger, "    SSID: \"%s\"\r\n    IP: %s\r\n    Port: %u", ( char * ) AP_SSID, 
                                                                           ( char * ) assigned_ip_address, 
                                                                         ( uint16_t ) LOCAL_PORT );
    log_printf( &logger, "\r\n ----------------------------------------------- \r\n" );
    log_printf( &logger, " You can connect to it via a TCP/UDP client." );
    log_printf( &logger, "\r\n ----------------------------------------------- \r\n" );
}

```

### Application Task

> Logs all the data received from TCP/UDP clients on the USB UART.

```c

void application_task ( void )
{
    lpwifi_process( );
    lpwifi_log_app_buf( );
}

```

## Note

> In order for the example to work, user needs to set the AP SSID, password, and Local port
> on which the TCP server and UDP socket will be created.
> Enter valid data for the following macros: AP_SSID, AP_PASSWORD and LOCAL_PORT.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LPWiFi

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
