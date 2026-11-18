
---
# WiFi 10 Click

> [WiFi 10 Click](https://www.mikroe.com/?pid_product=MIKROE-3432) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3432&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example connects WiFi 10 Click to a Wi-Fi access point, obtains an IPv4 address using DHCP,
> and exchanges numbered messages with a configurable TCP and UDP echo server.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- MikroSDK.Conversions
- Click.WiFi10

### Example Key Functions

- `wifi10_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void wifi10_cfg_setup ( wifi10_cfg_t *cfg );
```

- `wifi10_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t wifi10_init ( wifi10_t *ctx, wifi10_cfg_t *cfg );
```

- `wifi10_default_cfg` This function executes a default configuration of WiFi 10 Click board.
```c
err_t wifi10_default_cfg ( wifi10_t *ctx );
```

- `wifi10_connect` This function joins the configured open or WPA2-PSK access point.
```c
err_t wifi10_connect ( wifi10_t *ctx, char *ssid, char *password, uint8_t auth );
```

- `wifi10_dhcp` This function requests an IPv4 address from DHCP after association.
```c
err_t wifi10_dhcp ( wifi10_t *ctx, wifi10_ip_cfg_t *ip );
```

- `wifi10_socket_open` This function opens an IPv4 TCP or UDP socket and returns its firmware handle.
```c
err_t wifi10_socket_open ( wifi10_t *ctx, uint8_t type, int32_t *handle );
```

### Application Init

> Initializes the logger and driver GPIO/SPI interface.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wifi10_cfg_t wifi10_cfg;  /**< Click config object. */
    err_t result;

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
    wifi10_cfg_setup( &wifi10_cfg );
    WIFI10_MAP_MIKROBUS( wifi10_cfg, MIKROBUS_POSITION_WIFI10 );
    result = wifi10_init( &wifi10, &wifi10_cfg );
    if ( ( SPI_MASTER_ERROR == result ) || ( WIFI10_ERROR == result ) )
    {
        wifi10_stop( "Communication init", result );
    }

    remote_address = wifi10_parse_ipv4( REMOTE_IP );
    if ( 0ul == remote_address )
    {
        log_error( &logger, " Invalid REMOTE_IP. Use a nonzero IPv4 address in dotted-decimal format." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\r\n" );
}
```

### Application Task

> Starts hosted firmware, joins Wi-Fi, obtains an IPv4 address via DHCP, and verifies TCP and UDP echoes.
> Retries a TCP connect response timeout once and a UDP echo timeout up to twice.

```c
void application_task ( void )
{
    wifi10_ip_cfg_t ip;
    err_t result = WIFI10_OK;

    switch ( app_state )
    {
        case WIFI10_POWER_UP:
        {
            result = wifi10_default_cfg( &wifi10 );
            if ( WIFI10_OK != result )
            {
                wifi10_stop( "Firmware setup", result );
            }
            log_printf( &logger, "Firmware: 0x%.2X%.2X%.2X%.2X\r\n",
                        ( uint16_t ) ( wifi10.state.firmware_version >> 24 ),
                        ( uint16_t ) ( ( wifi10.state.firmware_version >> 16 ) & 0xFFul ),
                        ( uint16_t ) ( ( wifi10.state.firmware_version >> 8 ) & 0xFFul ),
                        ( uint16_t ) ( wifi10.state.firmware_version & 0xFFul ) );
            log_printf( &logger, "MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",
                        ( uint16_t ) wifi10.state.mac[ 0 ], ( uint16_t ) wifi10.state.mac[ 1 ],
                        ( uint16_t ) wifi10.state.mac[ 2 ], ( uint16_t ) wifi10.state.mac[ 3 ],
                        ( uint16_t ) wifi10.state.mac[ 4 ], ( uint16_t ) wifi10.state.mac[ 5 ] );
            app_state = WIFI10_CONFIGURE_CONNECTION;
            log_printf( &logger, "\r\n>>> APP STATE - CONFIGURE CONNECTION <<<\r\n\r\n" );
            break;
        }
        case WIFI10_CONFIGURE_CONNECTION:
        {
            log_info( &logger, " Connecting to access point..." );
            result = wifi10_connect( &wifi10, WIFI_SSID, WIFI_PASSWORD, WIFI_AUTH );
            if ( WIFI10_OK != result )
            {
                if ( ( WIFI10_ERROR_TIMEOUT == result ) && wifi10.state.associated )
                {
                    wifi10_stop( "WPA2 handshake", result );
                }
                else
                {
                    wifi10_stop( "Wi-Fi association", result );
                }
            }
            log_info( &logger, " Associated. Waiting for DHCP..." );
            result = wifi10_dhcp( &wifi10, &ip );
            if ( WIFI10_OK != result )
            {
                wifi10_stop( "DHCP", result );
            }
            log_printf( &logger, "IPv4: %u.%u.%u.%u\r\n",
                        ( uint16_t ) ( ip.address >> 24 ),
                        ( uint16_t ) ( ( ip.address >> 16 ) & 0xFFul ),
                        ( uint16_t ) ( ( ip.address >> 8 ) & 0xFFul ),
                        ( uint16_t ) ( ip.address & 0xFFul ) );
            app_state = WIFI10_EXAMPLE;
            log_printf( &logger, "\r\n>>> APP STATE - EXAMPLE <<<\r\n" );
            break;
        }
        case WIFI10_EXAMPLE:
        {
            result = wifi10_example( WIFI10_SOCKET_TCP );
            if ( WIFI10_ERROR_TIMEOUT == result )
            {
                if ( tcp_connect_retried )
                {
                    wifi10_stop( "TCP connect retry", result );
                }

                tcp_connect_retried = 1;
                log_warning( &logger, " TCP connect response timed out. Resetting the module for one retry." );
                // Reset clears the outstanding socket command before the example opens another socket.
                result = wifi10_hw_reset( &wifi10 );
                if ( WIFI10_OK != result )
                {
                    wifi10_stop( "Hardware reset", result );
                }
                app_state = WIFI10_POWER_UP;
                log_printf( &logger, "\r\n>>> APP STATE - POWER UP <<<\r\n\r\n" );
                break;
            }
            tcp_connect_retried = 0;
            wifi10_example( WIFI10_SOCKET_UDP );
            pause_count = 0;
            app_state = WIFI10_WAIT;
            break;
        }
        case WIFI10_WAIT:
        {
            result = wifi10_process( &wifi10 );
            if ( WIFI10_OK != result )
            {
                wifi10_stop( "Firmware event", result );
            }
            if ( 0u == wifi10.state.connected )
            {
                wifi10_stop( "Wi-Fi disconnected", WIFI10_ERROR_DISCONNECTED );
            }
            Delay_ms( ECHO_PAUSE_POLL_MS );
            pause_count++;
            if ( pause_count >= ECHO_PAUSE_POLLS )
            {
                app_state = WIFI10_EXAMPLE;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}
```

### Note

> Set WIFI_SSID, WIFI_PASSWORD, and WIFI_AUTH for a 2.4 GHz access point.
> WPA2 accepts 8-63 printable ASCII characters or a 64-digit hexadecimal key.
> For an open network, select WIFI10_AUTH_OPEN and use an empty password.
> Set REMOTE_IP in dotted-decimal format and REMOTE_PORT for a TCP and UDP echo server.
> Set COMM SEL to SPI and use QCA4004 hosted firmware with ABI 1.

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
