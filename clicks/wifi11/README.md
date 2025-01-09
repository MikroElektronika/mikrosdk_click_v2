
---
# WiFi 11 Click

> [WiFi 11 Click](https://www.mikroe.com/?pid_product=MIKROE-4245) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4245&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from WiFi 11 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Wifi11

### Example Key Functions

- `wifi11_cfg_setup` Config Object Initialization function. 
```c
void wifi11_cfg_setup ( wifi11_cfg_t *cfg );
``` 
 
- `wifi11_init` Initialization function. 
```c
err_t wifi11_init ( wifi11_t *ctx, wifi11_cfg_t *cfg );
```

- `wifi11_reset_device` Device reset function. 
```c
void wifi11_reset_device ( wifi11_t *ctx );
```

- `wifi11_send_cmd` Send command function. 
```c
void wifi11_send_cmd ( wifi11_t *ctx, char *cmd );
```
 
- `wifi11_create_tcp_udp_server` Create TCP/UDP server function. 
```c
void wifi11_create_tcp_udp_server ( wifi11_t *ctx, uint8_t mode, uint16_t port );
```

- `wifi11_connect_to_ap` Connect to AP function. 
```c
void wifi11_connect_to_ap ( wifi11_t *ctx, char *ssid, char *password );
```

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

### Note

> In order for the example to work, user needs to set the AP SSID, password, and Local port
> on which the TCP and UDP servers will be created.
> Enter valid data for the following macros: AP_SSID, AP_PASSWORD and LOCAL_PORT.

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
