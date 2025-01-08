
---
# Wifi ESP Click

> [WiFi ESP Click](https://www.mikroe.com/?pid_product=MIKROE-2542) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2542&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example connects to the desired WiFi network and then
> creates web server on the IP address assigned to the Click board.
> The user can connect to the server via web browser.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.WifiEsp

### Example Key Functions

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

### Application Init

> Initializes driver and wifi communication, then connects to the desired WiFi network
> and creates web server on the IP address assigned to the Click board.

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
> The Click board will respond by sending a page content to the client.

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
