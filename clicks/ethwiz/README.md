
---
# ETH WIZ Click

> [ETH WIZ Click](https://www.mikroe.com/?pid_product=MIKROE-1718) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1718&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example exchanges messages with the MIKROE TCP/UDP echo server.
> It uses the W5500 module and the mikroSDK SPI Ethernet transport in MACRAW mode for DHCP,
> then switches W5500 socket 0 to TCP or UDP for each echo exchange.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- MikroSDK.Conversions
- MikroSDK.Ethernet.Net
- Click.ETHWIZ

### Example Key Functions

- `ethwiz_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void ethwiz_cfg_setup ( ethwiz_cfg_t *cfg );
```

- `ethwiz_init` This function initializes all necessary pins and peripherals using the SDK W5500 SPI transport.
```c
err_t ethwiz_init ( ethwiz_t *ctx, ethwiz_cfg_t *cfg );
```

- `ethwiz_default_cfg` This function uses the SDK to reset the W5500, verify VERSIONR, program network addresses and open socket 0 in MACRAW mode.
```c
err_t ethwiz_default_cfg ( ethwiz_t *ctx );
```

- `ethwiz_socket_open` This function replaces socket 0 with a TCP client or UDP socket and waits until it is ready.
```c
err_t ethwiz_socket_open ( ethwiz_t *ctx, ethwiz_socket_t *endpoint );
```

- `ethwiz_socket_send` This function writes a payload to the configured peer and waits for the W5500 SENDOK interrupt.
```c
err_t ethwiz_socket_send ( ethwiz_t *ctx, uint8_t *buffer, uint16_t len );
```

- `ethwiz_socket_receive` This function reads available payload from the configured peer without waiting for data to arrive.
```c
err_t ethwiz_socket_receive ( ethwiz_t *ctx, ethwiz_socket_t *endpoint, uint8_t *buffer, uint16_t capacity, uint16_t *received );
```

### Application Init

> Initializes the UART logger and the Click driver. Logs the W5500 version
> and starts monitoring the Ethernet link.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ethwiz_cfg_t ethwiz_cfg;  /**< Click config object. */

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
    ethwiz_cfg_setup( &ethwiz_cfg );
    ETHWIZ_MAP_MIKROBUS( ethwiz_cfg, MIKROBUS_POSITION_ETHWIZ );
    memcpy( ethwiz_cfg.mac, local_mac, sizeof( local_mac ) );

    if ( ETHWIZ_ERROR == ethwiz_init( &ethwiz, &ethwiz_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ETHWIZ_ERROR == ethwiz_default_cfg( &ethwiz ) )
    {
        log_error( &logger, " W5500 configuration. Check the SPI connection." );
        for ( ; ; );
    }

    uint8_t version = 0;
    if ( ( ETHWIZ_ERROR == ethwiz_get_version( &ethwiz, &version ) ) || ( ETHWIZ_VERSION != version ) )
    {
        log_error( &logger, " Could not verify the W5500 version." );
        for ( ; ; );
    }
    log_printf( &logger, "W5500 version: 0x%.2X", ( uint16_t ) version );
    log_printf( &logger, "\r\nWaiting for Ethernet link...\r\n" );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> On the first Ethernet link, obtains the IPv4 address, subnet mask, and
> gateway through DHCP. Sends numbered messages, accumulates partial TCP
> replies, and prints matching echoes. Closes the socket before switching
> protocols.

```c
void application_task ( void )
{
    uint8_t current_link = ethwiz_get_link_status( &ethwiz );

    if ( current_link != last_link )
    {
        if ( current_link )
        {
            log_info( &logger, " Link up." );
        }
        else
        {
            log_info( &logger, " Link down." );
        }
        last_link = current_link;
    }

    /* DHCP and the switch to hardware sockets happen once, on the first link. */
    if ( current_link && !network_configured )
    {
        echo_ready = ethwiz_app_configure_network( );
        network_configured = 1;
    }
    if ( current_link && echo_ready )
    {
        ethwiz_app_exchange_echo( );
        Delay_ms( APP_ECHO_INTERVAL_MS );
    }
    else
    {
        Delay_ms( APP_LINK_POLL_MS );
    }
}
```

### Note

> Connect an Ethernet cable and set local_mac to a unique
> locally administered address. The network must provide DHCP and permit TCP
> and UDP to 54.187.244.144 on port 51111. DHCP runs once on the first link
> and does not renew the lease. If no address is obtained, the example skips
> the echo exchanges until reset.

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
