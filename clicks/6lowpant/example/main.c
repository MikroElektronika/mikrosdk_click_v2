/*!
 * @file main.c
 * @brief 6LoWPAN T Click example
 *
 * # Description
 * This example demonstrates the use of 6LoWPAN T Click by sending and receiving
 * numbered text messages between two boards using IEEE 802.15.4 data frames.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and driver, verifies the radio configuration and identification,
 * selects the transmitter or receiver role, and displays the channel and PAN identifier.
 *
 * ## Application Task
 * The transmitter broadcasts a text message and four-byte packet counter once per second.
 * The receiver displays the received counter, text, source address, RSSI, and raw correlation.
 *
 * @note
 * Use two 6LoWPAN T Click boards: select APP_MODE as C6LOWPANT_MODE_TX on one and C6LOWPANT_MODE_RX on the other.
 * Both boards must use the same channel and PAN identifier. Defaults are channel 20 (2450 MHz), PAN 0x1234,
 * 250 kbps, and 0 dBm. Broadcast frames use hardware CRC but do not request acknowledgments.
 * The first four payload bytes carry a big-endian counter; APP_TEXT_MESSAGE supports up to 112 characters.
 * RSSI is an estimate using a reference-design offset. Correlation is a raw value from 0 to 127, not a percentage.
 * This example demonstrates the radio link only; IPv6/6LoWPAN networking requires a separate protocol stack.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c6lowpant.h"

#ifndef MIKROBUS_POSITION_6LOWPANT
    #define MIKROBUS_POSITION_6LOWPANT MIKROBUS_1
#endif

/** Radio role: use one transmitter and one receiver with matching channel and PAN settings. */
#define APP_MODE                    C6LOWPANT_MODE_TX

/** Number of big-endian counter bytes preceding the text in each radio payload. */
#define APP_PACKET_COUNTER_SIZE     4
#define APP_RECEIVER_ADDRESS        0x0002
#define APP_TX_INTERVAL_MS          1000
#define APP_RX_POLL_DELAY_MS        10
#define APP_RX_ERROR_DELAY_MS       100

/** Text sent after the counter; the terminating null byte is not transmitted. */
#define APP_TEXT_MESSAGE            "Hello from 6LoWPAN T Click!"

#if ( APP_MODE != C6LOWPANT_MODE_TX ) && ( APP_MODE != C6LOWPANT_MODE_RX )
    #error "APP_MODE must be C6LOWPANT_MODE_TX or C6LOWPANT_MODE_RX."
#endif

static c6lowpant_t c6lowpant;      /**< Click driver context. */
static log_t logger;               /**< UART logger context. */

void application_init ( void )
{
    log_cfg_t log_cfg;                 /**< Logger config object. */
    c6lowpant_cfg_t c6lowpant_cfg;     /**< Click config object. */

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
    c6lowpant_cfg_setup( &c6lowpant_cfg );
    C6LOWPANT_MAP_MIKROBUS( c6lowpant_cfg, MIKROBUS_POSITION_6LOWPANT );
    if ( SPI_MASTER_ERROR == c6lowpant_init( &c6lowpant, &c6lowpant_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C6LOWPANT_OK != c6lowpant_default_cfg ( &c6lowpant ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    uint8_t chip_id;    /**< Radio identification byte. */
    uint8_t version;    /**< Radio silicon revision. */

    if ( C6LOWPANT_OK != c6lowpant_get_id( &c6lowpant, &chip_id, &version ) )
    {
        log_error( &logger, " Identification read." );
        for ( ; ; );
    }

    // Ensure the complete text and counter fit without truncating the transmitted message.
    if ( strlen( APP_TEXT_MESSAGE ) + APP_PACKET_COUNTER_SIZE > C6LOWPANT_MAX_PAYLOAD_SIZE )
    {
        log_error( &logger, " Text message exceeds the packet payload size." );
        for ( ; ; );
    }

#if ( APP_MODE == C6LOWPANT_MODE_RX )
    // Give the receiving board its own short address; the transmitter uses the default address 0x0001.
    if ( C6LOWPANT_OK != c6lowpant_set_address( &c6lowpant, C6LOWPANT_DEFAULT_PAN_ID, APP_RECEIVER_ADDRESS ) )
    {
        log_error( &logger, " Receiver address." );
        for ( ; ; );
    }
#endif
    if ( C6LOWPANT_OK != c6lowpant_set_mode( &c6lowpant, APP_MODE ) )
    {
        log_error( &logger, " Set radio mode." );
        for ( ; ; );
    }

    log_printf( &logger, " Chip ID: 0x%.2X | Revision: 0x%.2X\r\n", ( uint16_t ) chip_id, ( uint16_t ) version );
    log_printf( &logger, " Channel: %u (%u MHz) | PAN ID: 0x%.4X\r\n",
                ( uint16_t ) C6LOWPANT_DEFAULT_CHANNEL,
                ( uint16_t ) ( C6LOWPANT_CHANNEL_FREQUENCY_BASE +
                               C6LOWPANT_CHANNEL_FREQUENCY_STEP *
                               ( C6LOWPANT_DEFAULT_CHANNEL - C6LOWPANT_CHANNEL_MIN ) ),
                C6LOWPANT_DEFAULT_PAN_ID );
#if ( APP_MODE == C6LOWPANT_MODE_TX )
    log_printf( &logger, " Mode: Transmitter | Broadcast, no acknowledgment\r\n" );
#else
    log_printf( &logger, " Mode: Receiver\r\n" );
    log_printf( &logger, " Waiting for packets from the transmitter...\r\n" );
#endif

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
#if ( APP_MODE == C6LOWPANT_MODE_TX )
    static uint32_t packet_count = 0;  /**< Counter assigned to each attempted transmission; resets at startup. */
    uint8_t tx_data[ C6LOWPANT_MAX_PAYLOAD_SIZE ];  /**< Counter followed by the text bytes. */
    uint8_t tx_len = APP_PACKET_COUNTER_SIZE + strlen( APP_TEXT_MESSAGE );
    err_t error_flag;

    // Use explicit byte order so different MCU families decode the same packet number.
    tx_data[ 0 ] = ( uint8_t ) ( packet_count >> 24 );
    tx_data[ 1 ] = ( uint8_t ) ( packet_count >> 16 );
    tx_data[ 2 ] = ( uint8_t ) ( packet_count >> 8 );
    tx_data[ 3 ] = ( uint8_t ) packet_count;
    memcpy( &tx_data[ APP_PACKET_COUNTER_SIZE ], APP_TEXT_MESSAGE, strlen( APP_TEXT_MESSAGE ) );

    error_flag = c6lowpant_send_packet( &c6lowpant, C6LOWPANT_BROADCAST_ADDR, tx_data, tx_len );
    if ( C6LOWPANT_OK == error_flag )
    {
        log_printf( &logger, " TX packet #%lu sent: %s\r\n\r\n", packet_count, ( char * ) APP_TEXT_MESSAGE );
    }
    else if ( C6LOWPANT_CHANNEL_BUSY == error_flag )
    {
        log_printf( &logger, " TX packet #%lu not sent: Channel busy.\r\n\r\n", packet_count );
    }
    else if ( C6LOWPANT_TIMEOUT == error_flag )
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
    uint8_t rx_data[ C6LOWPANT_MAX_PAYLOAD_SIZE + 1 ];
    uint32_t packet_count;                /**< Counter extracted from the received payload. */
    c6lowpant_packet_info_t packet_info;  /**< Address, length, and link measurements. */
    err_t error_flag;

    error_flag = c6lowpant_receive_packet( &c6lowpant, rx_data, C6LOWPANT_MAX_PAYLOAD_SIZE, &packet_info );
    if ( C6LOWPANT_OK == error_flag )
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
    else if ( C6LOWPANT_FRAME_ERROR == error_flag )
    {
        log_error( &logger, " Invalid frame or receive FIFO overflow. Packet discarded." );
    }
    else if ( C6LOWPANT_NO_DATA != error_flag )
    {
        log_error( &logger, " Packet reception." );
        Delay_ms( APP_RX_ERROR_DELAY_MS );
    }
    Delay_ms( APP_RX_POLL_DELAY_MS );
#endif
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
