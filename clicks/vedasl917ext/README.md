
---
# Veda SL917 EXT Click

> [Veda SL917 EXT Click](https://www.mikroe.com/?pid_product=MIKROE-6488) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6488&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Veda SL917 EXT Click board by exchanging
> numbered messages with an echo server over TCP and UDP.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- MikroSDK.Conversions
- Click.VedaSL917EXT

### Example Key Functions

- `vedasl917ext_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void vedasl917ext_cfg_setup ( vedasl917ext_cfg_t *cfg );
```

- `vedasl917ext_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t vedasl917ext_init ( vedasl917ext_t *ctx, vedasl917ext_cfg_t *cfg );
```

- `vedasl917ext_default_cfg` This function resets the NCP, initializes SPI, boots the existing flash image, waits for CARD READY, and configures a WLAN-only 2.4 GHz station with the module's IPv4 stack.
```c
err_t vedasl917ext_default_cfg ( vedasl917ext_t *ctx );
```

- `vedasl917ext_join` This function scans for the selected SSID, configures the passphrase for WPA2, and joins the network.
```c
err_t vedasl917ext_join ( vedasl917ext_t *ctx, char *ssid, uint8_t security, char *passphrase );
```

- `vedasl917ext_socket_send` This function submits one TCP payload or UDP datagram to the module.
```c
err_t vedasl917ext_socket_send ( vedasl917ext_t *ctx, vedasl917ext_socket_t *socket, uint8_t *buffer, uint16_t len );
```

- `vedasl917ext_socket_recv` This function reads one TCP chunk or one UDP datagram. UDP packets from other peers are ignored.
```c
err_t vedasl917ext_socket_recv ( vedasl917ext_t *ctx, vedasl917ext_socket_t *socket, uint8_t *buffer, uint16_t capacity, uint16_t *received, uint16_t polls );
```

### Application Init

> Initializes the driver and performs the Click default configuration.
> Displays the firmware version and MAC address. Joins the configured Wi-Fi network and obtains an IPv4 address.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vedasl917ext_cfg_t vedasl917ext_cfg;  /**< Click config object. */

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
    vedasl917ext_cfg_setup( &vedasl917ext_cfg );
    VEDASL917EXT_MAP_MIKROBUS( vedasl917ext_cfg, MIKROBUS_POSITION_VEDASL917EXT );
    if ( SPI_MASTER_ERROR == vedasl917ext_init( &vedasl917ext, &vedasl917ext_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    err_t error_flag = vedasl917ext_default_cfg( &vedasl917ext );
    if ( VEDASL917EXT_OK != error_flag )
    {
        vedasl917ext_stop( "Default configuration", error_flag, vedasl917ext.last_status );
    }

    vedasl917ext_version_t version;
    error_flag = vedasl917ext_get_fw_version( &vedasl917ext, &version );
    if ( VEDASL917EXT_OK != error_flag )
    {
        vedasl917ext_stop( "Firmware version read", error_flag, vedasl917ext.last_status );
    }
    log_printf( &logger, "Firmware: %u.%u.%u, build %u\r\n",
                ( uint16_t ) version.major, ( uint16_t ) version.minor, ( uint16_t ) version.patch, version.build );

    uint8_t mac[ VEDASL917EXT_MAC_SIZE ];
    error_flag = vedasl917ext_get_mac_address( &vedasl917ext, mac );
    if ( VEDASL917EXT_OK != error_flag )
    {
        vedasl917ext_stop( "MAC address read", error_flag, vedasl917ext.last_status );
    }
    log_printf( &logger, "MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",
                ( uint16_t ) mac[ 0 ], ( uint16_t ) mac[ 1 ], ( uint16_t ) mac[ 2 ],
                ( uint16_t ) mac[ 3 ], ( uint16_t ) mac[ 4 ], ( uint16_t ) mac[ 5 ] );

    if ( ( VEDASL917EXT_WIFI_WPA2 == APP_WLAN_AUTH ) && ( 0 == app_psk[ 0 ] ) )
    {
        log_error( &logger, " Set APP_WLAN_PSK for the configured WPA2 network." );
        for ( ; ; );
    }
    log_printf( &logger, "Joining Wi-Fi: %s\r\n", app_ssid );
    error_flag = vedasl917ext_join( &vedasl917ext, app_ssid, APP_WLAN_AUTH, app_psk );
    if ( VEDASL917EXT_OK != error_flag )
    {
        vedasl917ext_stop( "Wi-Fi join", error_flag, vedasl917ext.last_status );
    }

    uint8_t address[ VEDASL917EXT_IPV4_SIZE ];
    log_info( &logger, " Associated. Waiting for DHCP..." );
    error_flag = vedasl917ext_dhcp( &vedasl917ext, address );
    if ( VEDASL917EXT_OK != error_flag )
    {
        vedasl917ext_stop( "DHCP", error_flag, vedasl917ext.last_status );
    }
    log_printf( &logger, "IPv4: %u.%u.%u.%u\r\n", ( uint16_t ) address[ 0 ], ( uint16_t ) address[ 1 ],
                ( uint16_t ) address[ 2 ], ( uint16_t ) address[ 3 ] );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sends a message over TCP and verifies the echo. Repeats the exchange over UDP,
> then waits before starting the next pair of exchanges.
> If the firmware reports no TCP listener, logs the status and attempts UDP.

```c
void application_task ( void )
{
    vedasl917ext_echo( VEDASL917EXT_SOCKET_TCP );
    vedasl917ext_echo( VEDASL917EXT_SOCKET_UDP );
    Delay_ms( APP_ECHO_PAUSE_MS );
}
```

### Note

> Set APP_WLAN_SSID, APP_WLAN_AUTH, and APP_WLAN_PSK for your 2.4 GHz network.
> Set APP_SERVER_IP and APP_SERVER_PORT if you use a different echo server.

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
