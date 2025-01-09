
---
# WiFi 9 Click

> [WiFi 9 Click](https://www.mikroe.com/?pid_product=MIKROE-3666) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3666&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This application showcases capability of the WiFi 9 Click board. 
It initializes device, connects to local WiFi. Creates TCP server, waits for connection, 
and logs every message it receives from clients and returns back those messages as an echo response.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Wifi9

### Example Key Functions

- `wifi9_cfg_setup` Config Object Initialization function.
```c
void wifi9_cfg_setup ( wifi9_cfg_t *cfg ); 
```

- `wifi9_init` Initialization function.
```c
err_t wifi9_init ( wifi9_t *ctx, wifi9_cfg_t *cfg );
```

- `wifi9_select_uart` Switch to a command or binary uart
```c
void wifi9_select_uart ( wifi9_t *ctx, uint8_t uart_select );
```

- `wifi9_reset_device` Module reset.
```c
void wifi9_reset_device ( wifi9_t *ctx );
```

- `wifi9_send_command` Send Command function.
```c
void wifi9_send_command ( wifi9_t *ctx, uint8_t *command );
```

### Application Init

> Initializes driver and wifi communication, then connects to the desired WiFi network
and creates TCP server on the IP address assigned to the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    wifi9_cfg_t cfg;

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
    wifi9_cfg_setup( &cfg );
    WIFI9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifi9_init( &wifi9, &cfg );

    wifi9_reset_device( &wifi9 );
    wifi9_select_uart( &wifi9, WIFI9_SELECT_CMD_UART );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    wifi9_process( );
    wifi9_clear_app_buf( );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "---- System Info ----\r\n" );
    log_printf( &logger, "---------------------\r\n" );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_FIRMWARE );
    wifi9_rsp_check( WIFI9_CMD_GET_SYSTEM_FIRMWARE );
    wifi9_log_app_buf( );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_MAC_ADDR );
    wifi9_rsp_check( WIFI9_CMD_GET_SYSTEM_MAC_ADDR );
    wifi9_log_app_buf( );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_SERIAL_NUM );
    wifi9_rsp_check( WIFI9_CMD_GET_SYSTEM_SERIAL_NUM );
    wifi9_log_app_buf( );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_RADIO_VER );
    wifi9_rsp_check( WIFI9_CMD_GET_SYSTEM_RADIO_VER );
    wifi9_log_app_buf( );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_BOOTL_VER );
    wifi9_rsp_check( WIFI9_CMD_GET_SYSTEM_BOOTL_VER );
    wifi9_log_app_buf( );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_HW_REV );
    wifi9_rsp_check( WIFI9_CMD_GET_SYSTEM_HW_REV );
    wifi9_log_app_buf( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "---- Start NETCAT app ----\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "\r\nSet Station to ON status: " );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_WLAN_STATE_STA_ON );
    wifi9_rsp_check( WIFI9_CMD_SET_WLAN_STATE );
    wifi9_log_app_buf( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "\r\nSet Station SSID and PASSWORD: " );
    strcpy( app_buf, WIFI9_CMD_SET_WLAN_CFG_STA );
    strcat( app_buf, " \"" );
    strcat( app_buf, EXAMPLE_SSID );
    strcat( app_buf, "\" \"" );
    strcat( app_buf, EXAMPLE_PASSWORD );
    strcat( app_buf, "\" 4" );
    wifi9_send_command( &wifi9, app_buf );
    wifi9_rsp_check( WIFI9_CMD_SET_WLAN_CFG );
    wifi9_log_app_buf( );
    Delay_ms ( 500 );
    
    log_printf( &logger, "\r\nTurn ON - Netcat module: " );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_NETCAT_STATE_ON );
    wifi9_rsp_check( WIFI9_CMD_SET_NETCAT_STATE );
    wifi9_log_app_buf( );
    Delay_ms ( 500 );
    
    log_printf( &logger, "\r\nExclude Netcat authentication: " );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_NETCAT_AUTH_OFF );
    wifi9_rsp_check( WIFI9_CMD_SET_NETCAT_AUTH );
    wifi9_log_app_buf( );
    Delay_ms ( 500 );
    
    log_printf( &logger, "\r\nSet the Netcat module server port: " );
    strcpy( app_buf, WIFI9_CMD_SET_NETCAT_CFG_SERVER );
    strcat( app_buf, " " );
    strcat( app_buf, EXAMPLE_SERVER_PORT );
    wifi9_send_command( &wifi9, app_buf );
    wifi9_rsp_check( WIFI9_CMD_SET_NETCAT_CFG );
    wifi9_log_app_buf( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "\r\nWaiting for an IP address assignment from DHCP server...\r\n" );
    for ( ; ; )
    {
        log_printf( &logger, "\r\nGet IP address: " );
        wifi9_send_command( &wifi9, WIFI9_CMD_GET_NET_CFG_STA );
        wifi9_rsp_check( WIFI9_CMD_GET_NET_CFG );
        wifi9_log_app_buf( );
        if ( !strstr ( app_buf, "0.0.0.0" ) )
        {
            break;
        }
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    wifi9_clear_app_buf( );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "\r\nNow you can connect to the TCP server listed above via a TCP client app\r\n" );  
    log_printf( &logger, "The module is transferred to BIN-UART - for data collection\r\n" );

    wifi9_select_uart( &wifi9, WIFI9_SELECT_BIN_UART );
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
}
```

### Application Task

> All data received from the TCP clients will be logger to USB UART and echoed back to the clients.

```c
void application_task ( void )
{
    wifi9_process( );
    if ( app_buf_len )
    {
        wifi9_log_app_buf( );
        wifi9_generic_write( &wifi9, app_buf, app_buf_len );
        wifi9_clear_app_buf( );
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
