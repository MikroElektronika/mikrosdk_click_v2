
---
# WiFi 6 Click

> [WiFi 6 Click](https://www.mikroe.com/?pid_product=MIKROE-2043) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2043&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates WiFi 6 Click communication by exchanging numbered messages with the MIKROE echo server over TCP and UDP.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.WiFi6

### Example Key Functions

- `wifi6_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void wifi6_cfg_setup ( wifi6_cfg_t *cfg );
```

- `wifi6_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t wifi6_init ( wifi6_t *ctx, wifi6_cfg_t *cfg );
```

- `wifi6_default_cfg` This function resets the module, selects station mode with DHCP, starts the radio, and reads its MAC address.
```c
err_t wifi6_default_cfg ( wifi6_t *ctx );
```

- `wifi6_connect` This function sets the network password and requests connection to the specified SSID.
```c
err_t wifi6_connect ( wifi6_t *ctx, char *ssid, char *password );
```

- `wifi6_open_socket` This function opens a TCP connection or a paired UDP transmit endpoint and receive listener.
```c
err_t wifi6_open_socket ( wifi6_t *ctx, uint8_t protocol, uint16_t local_port, uint8_t *peer_ip, uint16_t peer_port );
```

- `wifi6_send` This function sends application data through the active TCP or UDP transmit endpoint.
```c
err_t wifi6_send ( wifi6_t *ctx, uint8_t *data_in, uint16_t len );
```

### Application Init

> Initializes the logger, maps the Click pins, and opens the UART with software RTS/CTS flow control.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    wifi6_cfg_t wifi6_cfg;  /**< Click config object. */

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

    // Click initialization; module startup is handled by the first task stage.
    wifi6_cfg_setup( &wifi6_cfg );
    WIFI6_MAP_MIKROBUS( wifi6_cfg, MIKROBUS_POSITION_WIFI6 );
    if ( WIFI6_OK != wifi6_init( &wifi6, &wifi6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Resets the WF121, displays its firmware and MAC address, connects to the
> configured WLAN, and waits for DHCP. It then opens a TCP connection, sends a
> numbered message, verifies its echo, and closes the connection. The same
> exchange is repeated over UDP before returning to TCP. Partial TCP responses
> are assembled; eligible application-level wait timeouts receive bounded retries.

```c
void application_task ( void )
{
    err_t error_flag;

    // Distinguish application wait expiry from a driver timeout while reading a BGAPI frame.
    app_retryable_timeout = 0;
    error_flag = wifi6_app_run_stage( &wifi6 );

    if ( ( WIFI6_OK != error_flag ) && !wifi6_app_retry( &wifi6, error_flag ) )
    {
        log_error( &logger, " Communication error: %ld | Module result: %.4X",
                   error_flag, wifi6.module_error );
        log_printf( &logger, ">>> Restarting module shortly...\r\n\r\n" );
        app_wait_ticks = 0;
        app_state = APP_STATE_RECOVERY;
    }

    Delay_ms( APP_TASK_INTERVAL_MS );
}
```

### Note

> Set APP_WIFI_SSID and APP_WIFI_PASSWORD for a 2.4 GHz WLAN with Internet access.
> Use an empty password for an open network. Set all four IO SEL jumpers to UART (positions 1-2).
> The module must run WF121 BGAPI firmware on UART2 at 115200 baud, 8 data bits, no parity,
> and one stop bit, with RTS/CTS enabled. This example uses binary BGAPI commands, not AT commands.
> Module CTS is driven through MikroBUS INT; module RTS is read through MikroBUS CS.
> Module reset is not connected to MikroBUS RST, so the driver uses a BGAPI software reset.
> Connect the logger to a UART peripheral different from the one used by WiFi 6 Click.
> The network must allow TCP and UDP traffic to 54.187.244.144:51111. A one-second pause separates
> exchanges. UDP does not guarantee delivery, and messages are unencrypted; do not send sensitive data.

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
