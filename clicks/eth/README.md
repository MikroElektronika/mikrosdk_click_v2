
---
# ETH Click

> [ETH Click](https://www.mikroe.com/?pid_product=MIKROE-5548) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5548&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example exchanges messages with the MIKROE TCP/UDP echo server.
> The ENC28J60 exchanges Ethernet frames over SPI. The MCU obtains an IPv4 address through DHCP
> and uses the mikroSDK network helpers to send alternating TCP and UDP echo requests.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- MikroSDK.Conversions
- MikroSDK.Ethernet.Net
- Click.ETH

### Example Key Functions

- `eth_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void eth_cfg_setup ( eth_cfg_t *cfg );
```

- `eth_init` This function initializes all necessary pins and peripherals using the SDK ENC28J60 SPI transport.
```c
err_t eth_init ( eth_t *ctx, eth_cfg_t *cfg );
```

- `eth_default_cfg` This function resets the ENC28J60, verifies EREVID, sets the buffers and MAC address, programs the MAC and PHY for the selected duplex mode, and enables reception of valid unicast and broadcast frames.
```c
err_t eth_default_cfg ( eth_t *ctx );
```

- `eth_get_link_status` This function reads the PHY link status through the SDK.
```c
uint8_t eth_get_link_status ( eth_t *ctx );
```

- `eth_resolve_mac` This function broadcasts ARP requests for an on-link IPv4 address and saves the matching MAC address in the endpoint.
```c
err_t eth_resolve_mac ( eth_t *ctx, eth_socket_t *endpoint, uint8_t *ip );
```

- `eth_socket_exchange` This function sends one short request to a resolved peer and receives a UDP datagram or gathers in-order TCP bytes. The TCP client opens the stream, sends the request and collects the reply before closing the connection.
```c
err_t eth_socket_exchange ( eth_t *ctx, eth_socket_t *endpoint, uint8_t *request, uint16_t len,
                            uint8_t *reply, uint16_t reply_len );
```

### Application Init

> Initializes the UART logger and the Click driver. Logs the ENC28J60 silicon revision
> and starts monitoring the Ethernet link.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eth_cfg_t eth_cfg;  /**< Click config object. */

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
    eth_cfg_setup( &eth_cfg );
    ETH_MAP_MIKROBUS( eth_cfg, MIKROBUS_POSITION_ETH );
    memcpy( eth_cfg.mac, local_mac, sizeof( local_mac ) );

    if ( ETH_ERROR == eth_init( &eth, &eth_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( ETH_ERROR == eth_default_cfg( &eth ) )
    {
        log_error( &logger, " ENC28J60 configuration. Check the SPI connection." );
        for ( ; ; );
    }

    uint8_t version = 0;
    if ( ( ETH_ERROR == eth_get_version( &eth, &version ) ) || !version || ( version > ETH_REVISION_MASK ) )
    {
        log_error( &logger, " Could not verify the ENC28J60 revision." );
        for ( ; ; );
    }
    log_printf( &logger, "ENC28J60 revision: 0x%.2X", ( uint16_t ) version );
    log_printf( &logger, "\r\nWaiting for Ethernet link...\r\n" );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> On the first Ethernet link, obtains the IPv4 address, subnet mask, and
> gateway through DHCP. Sends numbered messages, accumulates partial TCP
> replies, and prints matching echoes. Uses a new source port for each exchange.

```c
void application_task ( void )
{
    uint8_t current_link = eth_get_link_status( &eth );

    if ( current_link != last_link )
    {
        if ( current_link )
        {
            log_info( &logger, " Link up." );
        }
        else
        {
            next_hop_known = 0;
            log_info( &logger, " Link down." );
        }
        last_link = current_link;
    }

    /* Acquire the demonstration lease once, on the first link. */
    if ( current_link && !network_configured )
    {
        echo_ready = eth_app_configure_network( );
        network_configured = 1;
    }
    if ( current_link && echo_ready )
    {
        uint16_t elapsed_ms;

        eth_app_exchange_echo( );
        for ( elapsed_ms = 0; elapsed_ms < APP_ECHO_INTERVAL_MS; elapsed_ms++ )
        {
            eth_service_frame( &eth, rx_buf, sizeof( rx_buf ) );
            Delay_ms( 1 );
        }
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
