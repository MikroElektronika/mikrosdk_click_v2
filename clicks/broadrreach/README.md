
---
# BroadR-Reach Click

> [BroadR-Reach Click](https://www.mikroe.com/?pid_product=MIKROE-2796) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2796&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of BroadR-Reach Click by exchanging numbered
text messages between two boards over UDP using the W3150A+ hardware network stack.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BroadRReach

### Example Key Functions

- `broadrreach_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void broadrreach_cfg_setup ( broadrreach_cfg_t *cfg );
```

- `broadrreach_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t broadrreach_init ( broadrreach_t *ctx, broadrreach_cfg_t *cfg );
```

- `broadrreach_default_cfg` This function resets the controller, allocates 2 KB per socket in each direction, and selects a 200 ms retry period with three retries.
```c
err_t broadrreach_default_cfg ( broadrreach_t *ctx );
```

- `broadrreach_set_network` This function writes and verifies the local MAC, IPv4, subnet mask, and gateway addresses.
```c
err_t broadrreach_set_network ( broadrreach_t *ctx, broadrreach_network_t *network );
```

- `broadrreach_open_socket` This function opens a local UDP socket and configures its destination IPv4 address and port.
```c
err_t broadrreach_open_socket ( broadrreach_t *ctx, uint8_t socket, uint16_t local_port, uint8_t *peer_ip, uint16_t peer_port );
```

- `broadrreach_send_udp` This function writes one datagram to the socket TX buffer and waits for SEND_OK or a timeout.
```c
err_t broadrreach_send_udp ( broadrreach_t *ctx, uint8_t socket, uint8_t *data_in, uint16_t len );
```

### Application Init

> Initializes the logger and driver, resets the board, verifies the controller configuration,
sets static network addresses, and opens a UDP socket for communication with the other board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    broadrreach_cfg_t broadrreach_cfg;  /**< Click config object. */

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
    broadrreach_cfg_setup( &broadrreach_cfg );
    BROADRREACH_MAP_MIKROBUS( broadrreach_cfg, MIKROBUS_POSITION_BROADRREACH );
    if ( SPI_MASTER_ERROR == broadrreach_init( &broadrreach, &broadrreach_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( BROADRREACH_OK != broadrreach_default_cfg( &broadrreach ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    if ( BROADRREACH_OK != broadrreach_set_network( &broadrreach, &app_network ) )
    {
        log_error( &logger, " Network configuration." );
        for ( ; ; );
    }
    if ( BROADRREACH_OK != broadrreach_open_socket( &broadrreach, APP_SOCKET, APP_UDP_PORT,
                                                    app_peer_ip, APP_UDP_PORT ) )
    {
        log_error( &logger, " Open UDP socket." );
        for ( ; ; );
    }
    app_socket_ready = 1;

    log_printf( &logger, " Node: %u\r\n", ( uint16_t ) APP_NODE_ID );
    log_printf( &logger, " Local IP: %u.%u.%u.%u | UDP port: %u\r\n",
                ( uint16_t ) app_network.ip[ 0 ], ( uint16_t ) app_network.ip[ 1 ],
                ( uint16_t ) app_network.ip[ 2 ], ( uint16_t ) app_network.ip[ 3 ], ( uint16_t ) APP_UDP_PORT );
    log_printf( &logger, " Peer IP: %u.%u.%u.%u | UDP port: %u\r\n",
                ( uint16_t ) app_peer_ip[ 0 ], ( uint16_t ) app_peer_ip[ 1 ],
                ( uint16_t ) app_peer_ip[ 2 ], ( uint16_t ) app_peer_ip[ 3 ], ( uint16_t ) APP_UDP_PORT );
    log_printf( &logger, " Use opposite master/slave settings and matching speeds on the two boards.\r\n\r\n" );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sends a text message containing an incrementing packet counter approximately once per second.
Displays received messages with the sender's IP address and UDP port, and recovers the socket after errors.

```c
void application_task ( void )
{
    static uint32_t packet_count = 1;
    static uint8_t tx_ticks = 0;
    uint8_t tx_data[ sizeof( APP_TEXT_MESSAGE ) + 10 ];
    uint8_t rx_data[ APP_RX_BUFFER_SIZE + 1 ];
    uint8_t packet_count_str[ 11 ];
    broadrreach_packet_t packet;
    err_t error_flag;

    // The TX buffer holds the text prefix, up to ten counter digits, and a local terminator.
    // The RX buffer has one extra byte so received payloads can be printed as C strings.
    // Poll RX every 10 ms between transmissions; hardware send waits can extend the one-second interval.
    if ( 0 == tx_ticks )
    {
        if ( !app_socket_ready )
        {
            if ( BROADRREACH_OK != broadrreach_open_socket( &broadrreach, APP_SOCKET, APP_UDP_PORT,
                                                            app_peer_ip, APP_UDP_PORT ) )
            {
                log_error( &logger, " Reopen UDP socket." );
            }
            else
            {
                app_socket_ready = 1;
            }
        }
        if ( app_socket_ready )
        {
            // Convert the counter to trimmed decimal text before appending it to the message.
            strcpy( tx_data, APP_TEXT_MESSAGE );
            uint32_to_str( packet_count, packet_count_str );
            l_trim( packet_count_str );
            r_trim( packet_count_str );
            strcat( tx_data, packet_count_str );

            // The terminating null is kept for local logging but is not sent in the UDP payload.
            error_flag = broadrreach_send_udp( &broadrreach, APP_SOCKET, tx_data, strlen( tx_data ) );
            if ( BROADRREACH_OK == error_flag )
            {
                log_printf( &logger, " TX: %s\r\n", ( char * ) tx_data );
            }
            else
            {
                if ( BROADRREACH_TIMEOUT == error_flag )
                {
                    log_printf( &logger, " TX packet #%lu timed out. Check peer power, cable, and mode settings.\r\n",
                                packet_count );
                }
                else
                {
                    log_error( &logger, " UDP transmission." );
                }
                // Closing drops any unfinished transmission before the next attempt.
                broadrreach_close_socket( &broadrreach, APP_SOCKET );
                app_socket_ready = 0;
            }
            packet_count++;
        }
        tx_ticks = 100;
    }

    if ( app_socket_ready )
    {
        error_flag = broadrreach_receive_udp( &broadrreach, APP_SOCKET, rx_data, APP_RX_BUFFER_SIZE, &packet );
        if ( BROADRREACH_OK == error_flag )
        {
            // The received length excludes the hardware header and leaves room for this local terminator.
            rx_data[ packet.length ] = '\0';
            log_printf( &logger, " RX from %u.%u.%u.%u:%u | %u bytes\r\n",
                        ( uint16_t ) packet.ip[ 0 ], ( uint16_t ) packet.ip[ 1 ],
                        ( uint16_t ) packet.ip[ 2 ], ( uint16_t ) packet.ip[ 3 ], packet.port, packet.length );
            log_printf( &logger, " %s\r\n\r\n", ( char * ) rx_data );
        }
        else if ( BROADRREACH_BUFFER_ERROR == error_flag )
        {
            log_printf( &logger, " RX datagram discarded: %u bytes exceeds the example buffer.\r\n", packet.length );
        }
        else if ( BROADRREACH_NO_DATA != error_flag )
        {
            log_error( &logger, " UDP reception. Reopening socket." );
            broadrreach_close_socket( &broadrreach, APP_SOCKET );
            app_socket_ready = 0;
        }
    }
    tx_ticks--;
    Delay_ms( 10 );
}
```

### Note

> Use two BroadR-Reach Click boards connected with a straight-through Ethernet cable.
Set APP_NODE_ID to 1 on one board and 2 on the other; both boards send and receive.
Select master on one board and slave on the other, with the same 10 or 100 Mbps speed on both.
The hardware selectors determine the PHY mode independently of APP_NODE_ID. Reset after changing them.
The example uses IP addresses 192.168.1.101 and 192.168.1.102, subnet 255.255.255.0, and UDP port 5000.
A standard PC Ethernet port cannot connect directly to a PHY operating in BroadR-Reach mode.
UDP does not guarantee delivery; a successful send confirms local transmission only.

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
