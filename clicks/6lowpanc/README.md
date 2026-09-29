
---
# 6LoWPAN C Click

> [6LoWPAN C Click](https://www.mikroe.com/?pid_product=MIKROE-2219) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2219&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of 6LoWPAN C Click by sending and receiving
numbered text messages between two boards using IEEE 802.15.4 data frames.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.6LoWPANC

### Example Key Functions

- `c6lowpanc_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void c6lowpanc_cfg_setup ( c6lowpanc_cfg_t *cfg );
```

- `c6lowpanc_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t c6lowpanc_init ( c6lowpanc_t *ctx, c6lowpanc_cfg_t *cfg );
```

- `c6lowpanc_default_cfg` This function resets and configures 6LoWPAN C Click for 250 kbps data frames on channel 20.
```c
err_t c6lowpanc_default_cfg ( c6lowpanc_t *ctx );
```

- `c6lowpanc_set_mode` This function selects 6LoWPAN C Click transmitter standby or continuous reception.
```c
err_t c6lowpanc_set_mode ( c6lowpanc_t *ctx, uint8_t mode );
```

- `c6lowpanc_send_packet` This function sends a short-address 6LoWPAN C Click data frame after clear-channel assessment.
```c
err_t c6lowpanc_send_packet ( c6lowpanc_t *ctx, uint16_t destination, uint8_t *data_in, uint8_t len );
```

- `c6lowpanc_receive_packet` This function reads and validates one 6LoWPAN C Click short-address data frame.
```c
err_t c6lowpanc_receive_packet ( c6lowpanc_t *ctx, uint8_t *data_out, uint8_t capacity, c6lowpanc_packet_info_t *info );
```

### Application Init

> Initializes the logger and driver, verifies the radio configuration and identification,
selects the transmitter or receiver role, and displays the channel and PAN identifier.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                 /**< Logger config object. */
    c6lowpanc_cfg_t c6lowpanc_cfg;     /**< Click config object. */

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
    c6lowpanc_cfg_setup( &c6lowpanc_cfg );
    C6LOWPANC_MAP_MIKROBUS( c6lowpanc_cfg, MIKROBUS_POSITION_6LOWPANC );
    if ( SPI_MASTER_ERROR == c6lowpanc_init( &c6lowpanc, &c6lowpanc_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C6LOWPANC_OK != c6lowpanc_default_cfg ( &c6lowpanc ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    uint8_t chip_id;    /**< Radio identification byte. */
    uint8_t version;    /**< Radio silicon revision. */

    if ( C6LOWPANC_OK != c6lowpanc_get_id( &c6lowpanc, &chip_id, &version ) )
    {
        log_error( &logger, " Identification read." );
        for ( ; ; );
    }

    // Ensure the complete text and counter fit without truncating the transmitted message.
    if ( strlen( APP_TEXT_MESSAGE ) + APP_PACKET_COUNTER_SIZE > C6LOWPANC_MAX_PAYLOAD_SIZE )
    {
        log_error( &logger, " Text message exceeds the packet payload size." );
        for ( ; ; );
    }

#if ( APP_MODE == C6LOWPANC_MODE_RX )
    // Give the receiving board its own short address; the transmitter uses the default address 0x0001.
    if ( C6LOWPANC_OK != c6lowpanc_set_address( &c6lowpanc, C6LOWPANC_DEFAULT_PAN_ID, APP_RECEIVER_ADDRESS ) )
    {
        log_error( &logger, " Receiver address." );
        for ( ; ; );
    }
#endif
    if ( C6LOWPANC_OK != c6lowpanc_set_mode( &c6lowpanc, APP_MODE ) )
    {
        log_error( &logger, " Set radio mode." );
        for ( ; ; );
    }

    log_printf( &logger, " Chip ID: 0x%.2X | Revision: 0x%.2X\r\n", ( uint16_t ) chip_id, ( uint16_t ) version );
    log_printf( &logger, " Channel: %u (%u MHz) | PAN ID: 0x%.4X\r\n",
                ( uint16_t ) C6LOWPANC_DEFAULT_CHANNEL,
                ( uint16_t ) ( C6LOWPANC_CHANNEL_FREQUENCY_BASE +
                               C6LOWPANC_CHANNEL_FREQUENCY_STEP *
                               ( C6LOWPANC_DEFAULT_CHANNEL - C6LOWPANC_CHANNEL_MIN ) ),
                C6LOWPANC_DEFAULT_PAN_ID );
#if ( APP_MODE == C6LOWPANC_MODE_TX )
    log_printf( &logger, " Mode: Transmitter | Broadcast, no acknowledgment\r\n" );
#else
    log_printf( &logger, " Mode: Receiver\r\n" );
    log_printf( &logger, " Waiting for packets from the transmitter...\r\n" );
#endif

    log_info( &logger, " Application Task " );
}
```

### Application Task

> The transmitter broadcasts a text message and four-byte packet counter once per second.
The receiver displays the received counter, text, source address, RSSI, and raw correlation.

```c
void application_task ( void )
{
#if ( APP_MODE == C6LOWPANC_MODE_TX )
    static uint32_t packet_count = 0;  /**< Counter assigned to each attempted transmission; resets at startup. */
    uint8_t tx_data[ C6LOWPANC_MAX_PAYLOAD_SIZE ];  /**< Counter followed by the text bytes. */
    uint8_t tx_len = APP_PACKET_COUNTER_SIZE + strlen( APP_TEXT_MESSAGE );
    err_t error_flag;

    // Use explicit byte order so different MCU families decode the same packet number.
    tx_data[ 0 ] = ( uint8_t ) ( packet_count >> 24 );
    tx_data[ 1 ] = ( uint8_t ) ( packet_count >> 16 );
    tx_data[ 2 ] = ( uint8_t ) ( packet_count >> 8 );
    tx_data[ 3 ] = ( uint8_t ) packet_count;
    memcpy( &tx_data[ APP_PACKET_COUNTER_SIZE ], APP_TEXT_MESSAGE, strlen( APP_TEXT_MESSAGE ) );

    error_flag = c6lowpanc_send_packet( &c6lowpanc, C6LOWPANC_BROADCAST_ADDR, tx_data, tx_len );
    if ( C6LOWPANC_OK == error_flag )
    {
        log_printf( &logger, " TX packet #%lu sent: %s\r\n\r\n", packet_count, ( char * ) APP_TEXT_MESSAGE );
    }
    else if ( C6LOWPANC_CHANNEL_BUSY == error_flag )
    {
        log_printf( &logger, " TX packet #%lu not sent: Channel busy.\r\n\r\n", packet_count );
    }
    else if ( C6LOWPANC_TIMEOUT == error_flag )
    {
        log_error( &logger, " Packet transmission timeout." );
    }
    else
    {
        log_error( &logger, " Packet transmission." );
    }
    packet_count++;
    Delay_ms( APP_TX_INTERVAL_MS );
#else
    uint8_t rx_data[ C6LOWPANC_MAX_PAYLOAD_SIZE + 1 ];
    uint32_t packet_count;                /**< Counter extracted from the received payload. */
    c6lowpanc_packet_info_t packet_info;  /**< Address, length, and link measurements. */
    err_t error_flag;

    error_flag = c6lowpanc_receive_packet( &c6lowpanc, rx_data, C6LOWPANC_MAX_PAYLOAD_SIZE, &packet_info );
    if ( C6LOWPANC_OK == error_flag )
    {
        if ( packet_info.length >= APP_PACKET_COUNTER_SIZE )
        {
            packet_count = ( ( uint32_t ) rx_data[ 0 ] << 24 ) |
                           ( ( uint32_t ) rx_data[ 1 ] << 16 ) |
                           ( ( uint32_t ) rx_data[ 2 ] << 8 ) |
                           ( uint32_t ) rx_data[ 3 ];
            rx_data[ packet_info.length ] = '\0';
            log_printf( &logger, " RX packet #%lu: %s\r\n", packet_count,
                        ( char * ) &rx_data[ APP_PACKET_COUNTER_SIZE ] );
            log_printf( &logger, " Source: 0x%.4X | RSSI: %d dBm | Correlation: %u\r\n\r\n",
                        packet_info.source, packet_info.rssi, ( uint16_t ) packet_info.correlation );
        }
        else
        {
            log_error( &logger, " Invalid counter payload." );
        }
    }
    else if ( C6LOWPANC_FRAME_ERROR == error_flag )
    {
        log_error( &logger, " Invalid frame or receive FIFO overflow. Packet discarded." );
    }
    else if ( C6LOWPANC_NO_DATA != error_flag )
    {
        log_error( &logger, " Packet reception." );
        Delay_ms( APP_RX_ERROR_DELAY_MS );
    }
    Delay_ms( APP_RX_POLL_DELAY_MS );
#endif
}
```

### Note

> Use two 6LoWPAN C Click boards: select APP_MODE as C6LOWPANC_MODE_TX on one and C6LOWPANC_MODE_RX on the other.
Both boards must use the same channel and PAN identifier. Defaults are channel 20 (2450 MHz), PAN 0x1234,
250 kbps, and 0 dBm. Broadcast frames use hardware CRC but do not request acknowledgments.
The first four payload bytes carry a big-endian counter; APP_TEXT_MESSAGE supports up to 112 characters.
RSSI is an estimate using a reference-design offset. Correlation is a raw value from 0 to 127, not a percentage.
This example demonstrates the radio link only; IPv6/6LoWPAN networking requires a separate protocol stack.

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
