
---
# WiFi 7 Click

> [WiFi 7 Click](https://www.mikroe.com/?pid_product=MIKROE-2046) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2046&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example exchanges numbered messages with the MIKROE echo server over TCP and UDP.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- MikroSDK.Conversions
- Click.WiFI7

### Example Key Functions

- `wifi7_cfg_setup` This function initializes the Click configuration structure with unconnected pins and default SPI settings.
```c
void wifi7_cfg_setup ( wifi7_cfg_t *cfg );
```

- `wifi7_init` This function opens SPI and initializes CHIP_EN, RESET_N, and the active-low interrupt input.
```c
err_t wifi7_init ( wifi7_t *ctx, wifi7_cfg_t *cfg );
```

- `wifi7_default_cfg` This function sequences CHIP_EN and RESET_N, initializes the SPI protocol, boots firmware, checks compatibility, and enables module interrupts.
```c
err_t wifi7_default_cfg ( wifi7_t *ctx );
```

- `wifi7_connect` This function submits a station connection request using the supplied SSID, authentication, and RF channel.
```c
err_t wifi7_connect ( wifi7_t *ctx, char *pc_ssid, uint8_t u8_ssid_len, wifi7_m2m_sec_type_t u8_sec_type, void *pv_auth_info,
                      uint16_t u16_ch );
```

- `wifi7_handle_events` This function polls the active-low INT pin and dispatches at most one pending Wi-Fi or socket firmware message.
```c
err_t wifi7_handle_events ( wifi7_t *ctx );
```

- `wifi7_socket_bind` This function submits a request to associate a local IPv4 address and port with an allocated TCP or UDP socket.
```c
err_t wifi7_socket_bind ( wifi7_t *ctx, int8_t sock, wifi7_sockaddr_t *pstr_addr, uint8_t u8_addr_len );
```

### Application Init

> Initializes the logger and SPI interface, resets the module, checks firmware compatibility,
> reports the firmware version, and requests a connection to the configured Wi-Fi network.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    wifi7_cfg_t wifi7_cfg;

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

    wifi7_cfg_setup( &wifi7_cfg );
    WIFI7_MAP_MIKROBUS( wifi7_cfg, MIKROBUS_POSITION_WIFI7 );
    if ( WIFI7_OK != wifi7_init( &wifi7, &wifi7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    err_t result = wifi7_default_cfg( &wifi7 );
    if ( result != WIFI7_OK )
    {
        if ( result == WIFI7_ERROR_FW_VERSION )
        {
            log_error( &logger, " Firmware incompatible with WINC15x0 driver 19.5.4." );
        }
        else
        {
            log_error( &logger, " Module initialization failed. Check power, pins, and firmware." );
        }
        for ( ; ; );
    }
    wifi7.app_wifi_cb   = wifi7_wifi_cb;
    wifi7.app_socket_cb = wifi7_socket_cb;
    wifi7_socket_init( &wifi7 );

    wifi7_m2m_rev_t fw_version;
    if ( WIFI7_OK != wifi7_get_full_firmware_version( &wifi7, &fw_version ) )
    {
        log_error( &logger, " Firmware version read failed." );
        for ( ; ; );
    }
    log_printf( &logger, "Firmware: %u.%u.%u\r\n",
                ( uint16_t ) fw_version.u8_firmware_major, ( uint16_t ) fw_version.u8_firmware_minor,
                ( uint16_t ) fw_version.u8_firmware_patch );
    log_printf( &logger, "Build: %s %s\r\n", ( char * ) fw_version.build_date, ( char * ) fw_version.build_time );

    remote_addr.sin_family = WIFI7_AF_INET;
    remote_addr.sin_port = ( uint16_t ) ( ( ( uint16_t ) APP_SERVER_PORT << 8 ) |
                                          ( ( uint16_t ) APP_SERVER_PORT >> 8 ) );
    memcpy( &remote_addr.sin_addr.s_addr, app_server_ip, sizeof( app_server_ip ) );
    local_addr.sin_family = WIFI7_AF_INET;
    local_addr.sin_port = ( uint16_t ) ( ( ( uint16_t ) APP_LOCAL_PORT << 8 ) |
                                         ( ( uint16_t ) APP_LOCAL_PORT >> 8 ) );
    local_addr.sin_addr.s_addr = 0;
    /* Count characters explicitly; string-literal sizeof differs on mikroC. */
    if ( WIFI7_OK != wifi7_connect( &wifi7, MAIN_WLAN_SSID, ( uint8_t ) strlen( MAIN_WLAN_SSID ),
                                    MAIN_WLAN_AUTH, MAIN_WLAN_PSK, WIFI7_M2M_WIFI_CH_ALL ) )
    {
        log_error( &logger, " Connection request failed." );
        for ( ; ; );
    }
    log_info( &logger, " Connecting..." );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Processes module events and waits for DHCP. It opens a TCP connection, sends a numbered
> message, verifies its echo, and closes the socket. The exchange then repeats over UDP.
> Partial TCP responses and firmware receive chunks are assembled before checking the complete echo.
> Missing UDP echoes retransmit the same message; TCP receive retries keep the accumulated bytes.

```c
void application_task ( void )
{
    if ( demo_failed )
    {
        Delay_100ms( );
        return;
    }
    if ( WIFI7_OK != wifi7_handle_events( &wifi7 ) )
    {
        log_error( &logger, " Module event handling failed. Restart the example." );
        demo_failed = 1;
        return;
    }
    if ( demo_failed )
    {
        return;
    }
    if ( WIFI7_OK != wifi7_app_run_stage( &wifi7 ) )
    {
        demo_failed = 1;
    }
    Delay_10ms( );
}
```

### Note

> Set MAIN_WLAN_SSID and MAIN_WLAN_PSK for a 2.4 GHz WPA/WPA2 personal network with Internet access.
> The network must allow TCP and UDP traffic to 54.187.244.144:51111.
> UDP binds local port 50000. Module events continue to be processed during the pause between exchanges.
> The module must have WINC15x0 firmware compatible with host driver 19.5.4.
> This example does not update firmware or save credentials to module flash.
> Wait counters measure task calls; driver processing and logging add to the elapsed time.
> A connection wait limit, exhausted echo retries, or communication failure stops the example until restart.

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
