
---
# nRF C Click

> [nRF C Click](https://www.mikroe.com/?pid_product=MIKROE-1304) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1304&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of nRF C Click by sending and receiving
text messages between two boards using acknowledged radio packets. Each
transmitted packet contains a four-byte counter followed by the text.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.nRFC

### Example Key Functions

- `nrfc_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void nrfc_cfg_setup ( nrfc_cfg_t *cfg );
```

- `nrfc_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t nrfc_init ( nrfc_t *ctx, nrfc_cfg_t *cfg );
```

- `nrfc_default_cfg` This function configures nRF C Click for 1 Mbps, 0 dBm, 16-bit CRC, and fixed 32-byte packets on pipe 0.
```c
err_t nrfc_default_cfg ( nrfc_t *ctx );
```

- `nrfc_set_mode` This function selects the nRF C Click power-down, transmit standby, or receive mode.
```c
err_t nrfc_set_mode ( nrfc_t *ctx, uint8_t mode );
```

- `nrfc_send_packet` This function transmits one nRF C Click packet and waits for completion or retry exhaustion.
```c
err_t nrfc_send_packet ( nrfc_t *ctx, uint8_t *data_in, uint8_t len );
```

- `nrfc_receive_packet` This function reads one fixed-length packet from the nRF C Click receive FIFO.
```c
err_t nrfc_receive_packet ( nrfc_t *ctx, uint8_t *data_out, uint8_t *len );
```

### Application Init

> Initializes the logger and driver, applies and verifies the default radio configuration,
selects the transmitter or receiver role, and displays the channel and payload size.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nrfc_cfg_t nrfc_cfg;  /**< Click config object. */

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
    nrfc_cfg_setup( &nrfc_cfg );
    NRFC_MAP_MIKROBUS( nrfc_cfg, MIKROBUS_POSITION_NRFC );
    if ( SPI_MASTER_ERROR == nrfc_init( &nrfc, &nrfc_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    // Apply the same channel, address, packet length, and acknowledgment settings on both boards.
    if ( NRFC_ERROR == nrfc_default_cfg ( &nrfc ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    // The receiver keeps CE high; the transmitter uses a short CE pulse for each packet.
    if ( NRFC_OK != nrfc_set_mode( &nrfc, APP_MODE ) )
    {
        log_error( &logger, " Set radio mode." );
        for ( ; ; );
    }

    log_printf( &logger, " Channel: %u (%u MHz)\r\n",
                ( uint16_t ) NRFC_DEFAULT_CHANNEL, ( uint16_t ) ( 2400 + NRFC_DEFAULT_CHANNEL ) );
    log_printf( &logger, " Payload: %u bytes | Auto acknowledgment: Enabled\r\n",
                ( uint16_t ) NRFC_DEFAULT_PAYLOAD_SIZE );

#if ( APP_MODE == NRFC_MODE_TX )
    log_printf( &logger, " Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Mode: Receiver\r\n" );
    log_printf( &logger, " Waiting for packets from the transmitter...\r\n" );
#endif

    log_info( &logger, " Application Task " );
}
```

### Application Task

> The transmitter sends a counted text message once per second and reports whether it was acknowledged.
The receiver extracts the counter and displays it with the received text.

```c
void application_task ( void )
{
#if ( APP_MODE == NRFC_MODE_TX )
    static uint32_t packet_count = 0;  /**< Number of attempted packet transmissions. */
    uint8_t tx_data[ NRFC_DEFAULT_PAYLOAD_SIZE ] = { 0 };  /**< Counter and zero-padded text payload. */
    err_t error_flag;

    // Encode the counter before the text so the receiver can identify missing packets.
    tx_data[ 0 ] = ( uint8_t ) ( packet_count >> 24 );
    tx_data[ 1 ] = ( uint8_t ) ( packet_count >> 16 );
    tx_data[ 2 ] = ( uint8_t ) ( packet_count >> 8 );
    tx_data[ 3 ] = ( uint8_t ) packet_count;
    memcpy( &tx_data[ APP_PACKET_TEXT_OFFSET ], APP_TEXT_MESSAGE, strlen( APP_TEXT_MESSAGE ) );

    log_printf( &logger, " TX packet #%lu: %s\r\n", packet_count, ( char * ) APP_TEXT_MESSAGE );
    error_flag = nrfc_send_packet( &nrfc, tx_data, sizeof( tx_data ) );
    if ( NRFC_OK == error_flag )
    {
        log_printf( &logger, " TX packet #%lu acknowledged.\r\n\r\n", packet_count++ );
    }
    else if ( NRFC_MAX_RETRIES == error_flag )
    {
        log_printf( &logger, " TX packet #%lu not acknowledged. Check the receiver.\r\n\r\n",
                    packet_count );
    }
    else if ( NRFC_TIMEOUT == error_flag )
    {
        log_error( &logger, " Transmit completion timeout." );
    }
    else
    {
        log_error( &logger, " Packet transmission." );
    }
    Delay_ms( 1000 );
#else
    uint8_t rx_data[ NRFC_MAX_PAYLOAD_SIZE + 1 ];  /**< Received payload with space for the text terminator. */
    uint8_t rx_len;  /**< Number of payload bytes returned by the driver. */
    uint32_t received_count;  /**< Counter decoded from the received packet. */
    err_t error_flag;

    // Poll the FIFO so packets remain visible even after the RX interrupt has been cleared.
    error_flag = nrfc_receive_packet( &nrfc, rx_data, &rx_len );
    if ( ( NRFC_OK == error_flag ) && ( rx_len > APP_PACKET_TEXT_OFFSET ) )
    {
        // Reconstruct the big-endian counter sent by the transmitter.
        received_count = ( ( uint32_t ) rx_data[ 0 ] << 24 ) |
                          ( ( uint32_t ) rx_data[ 1 ] << 16 ) |
                          ( ( uint32_t ) rx_data[ 2 ] << 8 ) |
                          ( uint32_t ) rx_data[ 3 ];
        rx_data[ rx_len ] = 0;
        log_printf( &logger, " RX packet #%lu: %s\r\n", received_count,
                    ( char * ) &rx_data[ APP_PACKET_TEXT_OFFSET ] );
    }
    else if ( NRFC_OK == error_flag )
    {
        log_error( &logger, " Invalid received packet." );
    }
    else if ( NRFC_NO_DATA != error_flag )
    {
        log_error( &logger, " Packet reception." );
        Delay_ms( 100 );
    }
    Delay_ms( 10 );
#endif
}
```

### Note

> Use two nRF C Click boards: set APP_MODE to NRFC_MODE_TX on one board and NRFC_MODE_RX on the other.
Both boards must use the same channel, data rate, address, CRC, and payload size.
The default configuration uses channel 40 (2440 MHz), 1 Mbps, 0 dBm, a five-byte address,
16-bit CRC, and 32-byte payloads with automatic acknowledgment. The first four payload bytes contain
the counter in big-endian order, so keep APP_TEXT_MESSAGE within 28 characters.

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
