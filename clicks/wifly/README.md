
---
# WiFly Click

> [WiFly Click](https://www.mikroe.com/?pid_product=MIKROE-1937) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1937&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates WiFly Click communication by exchanging numbered
> messages with the MIKROE echo server over TCP and UDP.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.WiFly

### Example Key Functions

- `wifly_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void wifly_cfg_setup ( wifly_cfg_t *cfg );
```

- `wifly_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t wifly_init ( wifly_t *ctx, wifly_cfg_t *cfg );
```

- `wifly_default_cfg` This function resets the module and configures manual association, DHCP, and UART data transfer.
```c
err_t wifly_default_cfg ( wifly_t *ctx );
```

- `wifly_connect` This function sets the SSID and passphrase, joins the network, and waits for DHCP.
```c
err_t wifly_connect ( wifly_t *ctx, char *ssid, char *password );
```

- `wifly_open_socket` This function configures the peer and opens a TCP connection or enables UDP data transfer.
```c
err_t wifly_open_socket ( wifly_t *ctx, uint8_t protocol, char *peer_ip, uint16_t peer_port, uint16_t local_port );
```

- `wifly_send` This function queues application bytes for the active TCP or UDP data session.
```c
err_t wifly_send ( wifly_t *ctx, uint8_t *data_in, uint16_t len );
```

### Application Init

> Initializes the logger, maps the Click pins, and opens the UART at 9600 baud.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;       /**< Logger config object. */
    wifly_cfg_t wifly_cfg;   /**< Click config object. */

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

    // Module configuration is performed by the first task stage.
    wifly_cfg_setup( &wifly_cfg );
    WIFLY_MAP_MIKROBUS( wifly_cfg, MIKROBUS_POSITION_WIFLY );
    if ( WIFLY_OK != wifly_init( &wifly, &wifly_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Resets and configures the RN-131, displays its firmware and MAC address, and connects to Wi-Fi.
> It opens a TCP connection, sends a numbered message, verifies the echo, and closes the connection.
> The same exchange is repeated over UDP, with a two-second pause between transports.
> A protocol change rejoins the WLAN to apply the new network settings.

```c
void application_task ( void )
{
    err_t error_flag;

    error_flag = wifly_app_run_stage( &wifly );
    if ( WIFLY_OK != error_flag )
    {
        log_error( &logger, " Communication error: %ld", error_flag );
        log_printf( &logger, ">>> Restarting module shortly...\r\n\r\n" );
        app_wait_ticks = 0;
        app_state = APP_STATE_RECOVERY;
    }
    Delay_ms( 10 );
}
```

### Note

> Configure `APP_WIFI_SSID` and `APP_WIFI_PASSWORD` for a 2.4 GHz WLAN.
> The network must allow TCP and UDP traffic to `54.187.244.144:51111`.

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
