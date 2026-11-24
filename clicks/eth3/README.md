
---
# ETH 3 Click

> [ETH 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2850) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2850&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example exchanges messages with the MIKROE TCP/UDP echo server.
> The LAN9250 exchanges Ethernet frames over SPI. The MCU obtains an IPv4 address through DHCP
> and uses the mikroSDK network helpers to send alternating TCP and UDP echo requests.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- MikroSDK.Conversions
- MikroSDK.Ethernet.Net
- Click.ETH3

### Example Key Functions

- `eth3_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void eth3_cfg_setup ( eth3_cfg_t *cfg );
```

- `eth3_init` This function initializes all necessary pins and peripherals using the SDK LAN9250 SPI transport.
```c
err_t eth3_init ( eth3_t *ctx, eth3_cfg_t *cfg );
```

- `eth3_default_cfg` This function resets the LAN9250, waits for readiness, verifies its ID, and configures the FIFO and MAC through the SDK.
```c
err_t eth3_default_cfg ( eth3_t *ctx );
```

- `eth3_get_link_status` This function reads the PHY link status through the SDK.
```c
uint8_t eth3_get_link_status ( eth3_t *ctx );
```

- `eth3_resolve_mac` This function broadcasts ARP requests for an on-link IPv4 address and saves the matching MAC address in the endpoint.
```c
err_t eth3_resolve_mac ( eth3_t *ctx, eth3_socket_t *endpoint, uint8_t *ip );
```

- `eth3_socket_exchange` This function sends one short request to a resolved peer and receives a UDP datagram or gathers in-order TCP bytes.
```c
err_t eth3_socket_exchange ( eth3_t *ctx, eth3_socket_t *endpoint, uint8_t *request, uint16_t len, uint8_t *reply, uint16_t reply_len );
```

### Application Init

> Initializes the UART logger and the Click driver. Logs the LAN9250 silicon revision
> and starts monitoring the Ethernet link.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eth3_cfg_t eth3_cfg;  /**< Click config object. */

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
    eth3_cfg_setup( &eth3_cfg );
    ETH3_MAP_MIKROBUS( eth3_cfg, MIKROBUS_POSITION_ETH3 );
    memcpy( eth3_cfg.mac, local_mac, sizeof( local_mac ) );

    if ( ETH3_ERROR == eth3_init( &eth3, &eth3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( ETH3_ERROR == eth3_default_cfg( &eth3 ) )
    {
        log_error( &logger, " LAN9250 configuration. Check the SPI connection." );
        for ( ; ; );
    }

    uint16_t version = 0;
    if ( ETH3_ERROR == eth3_get_version( &eth3, &version ) )
    {
        log_error( &logger, " Could not verify the LAN9250 revision." );
        for ( ; ; );
    }
    log_printf( &logger, "LAN9250 revision: 0x%.4X", version );
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
    uint8_t current_link = eth3_get_link_status( &eth3 );

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
        echo_ready = eth3_app_configure_network( );
        network_configured = 1;
    }
    if ( current_link && echo_ready )
    {
        uint16_t elapsed_ms;

        eth3_app_exchange_echo( );
        for ( elapsed_ms = 0; elapsed_ms < APP_ECHO_INTERVAL_MS; elapsed_ms++ )
        {
            eth3_service_frame( &eth3, rx_buf, sizeof( rx_buf ) );
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

> Connect to an Ethernet switch that negotiates full duplex and set local_mac to a unique
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
