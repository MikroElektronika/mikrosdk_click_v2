
---
# CC3100 Click

> [CC3100 Click](https://www.mikroe.com/?pid_product=MIKROE-2336) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2336&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : SPI/UART type

# Software Support

## Example Description

> This example demonstrates CC3100 Click Wi-Fi communication by exchanging numbered messages
with the MIKROE echo server over TCP and UDP.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CC3100

### Example Key Functions

- `cc3100_cfg_setup` This function initializes the configuration of CC3100 Click with SPI and 115200-baud UART defaults.
```c
void cc3100_cfg_setup ( cc3100_cfg_t *cfg );
```

- `cc3100_init` This function initializes the selected peripheral and control pins of CC3100 Click.
```c
err_t cc3100_init ( cc3100_t *ctx, cc3100_cfg_t *cfg );
```

- `cc3100_default_cfg` This function configures CC3100 Click for station operation with DHCP and manual WLAN connection.
```c
err_t cc3100_default_cfg ( cc3100_t *ctx );
```

- `cc3100_connect` This function requests a CC3100 Click connection to an open or WPA/WPA2-Personal WLAN.
```c
err_t cc3100_connect ( cc3100_t *ctx, char *ssid, char *password, uint8_t security );
```

- `cc3100_open_socket` This function creates one nonblocking IPv4 TCP or UDP socket on CC3100 Click.
```c
err_t cc3100_open_socket ( cc3100_t *ctx, uint8_t protocol, uint16_t local_port, uint8_t *peer_ip, uint16_t peer_port );
```

- `cc3100_send` This function sends application data to the peer configured for the CC3100 Click socket.
```c
err_t cc3100_send ( cc3100_t *ctx, uint8_t *data_in, uint16_t len );
```

### Application Init

> Initializes the logger and CC3100 Click driver, maps the Click pins, and selects SPI or UART.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cc3100_cfg_t cc3100_cfg;  /**< Click config object. */

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
    cc3100_cfg_setup( &cc3100_cfg );
    CC3100_MAP_MIKROBUS( cc3100_cfg, MIKROBUS_POSITION_CC3100 );
    cc3100_drv_interface_sel( &cc3100_cfg, APP_DRIVER_INTERFACE );
    if ( CC3100_OK != cc3100_init( &cc3100, &cc3100_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Starts the network processor, displays its firmware and MAC address, joins the configured WLAN,
and waits for DHCP. It then alternates numbered TCP and UDP echo exchanges with
54.187.244.144:51111, closing each socket before switching protocols. It assembles partial TCP
responses and restarts the network processor after communication errors.

```c
void application_task ( void )
{
    err_t error_flag = cc3100_app_run_stage( &cc3100 );
    if ( error_flag < 0 )
    {
        cc3100_app_handle_error( &cc3100, error_flag );
    }
    Delay_ms( APP_TASK_INTERVAL_MS );
}
```

### Note

> Set APP_WIFI_SSID and APP_WIFI_PASSWORD for a 2.4 GHz WLAN with Internet access.
The example uses the echo service at 54.187.244.144:51111; the network must allow TCP and UDP.
A one-second non-blocking pause separates exchanges when the protocol changes. UDP does not
guarantee delivery, and the test messages are unencrypted; do not send sensitive data.
Select SPI or UART with APP_DRIVER_INTERFACE and set J1A/J2A to 1-2 for SPI or 2-3 for UART.
UART uses 115200 baud, 8 data bits, no parity, one stop bit, and software CTS/RTS flow control.
Connect the logger to a UART peripheral different from the one used by CC3100 Click.

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
