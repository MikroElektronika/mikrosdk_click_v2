
---
# ESP8684 Click

> [ESP8684 Click](https://www.mikroe.com/?pid_product=MIKROE-5803) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5803&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example connects to the desired WiFi network and then
  connects to the TCP/UDP server, writes then reads data to and from it.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ESP8684

### Example Key Functions

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
