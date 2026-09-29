/*!
 * @file main.c
 * @brief nRF C Click example
 *
 * # Description
 * This example demonstrates the use of nRF C Click by sending and receiving
 * text messages between two boards using acknowledged radio packets. Each
 * transmitted packet contains a four-byte counter followed by the text.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and driver, applies and verifies the default radio configuration,
 * selects the transmitter or receiver role, and displays the channel and payload size.
 *
 * ## Application Task
 * The transmitter sends a counted text message once per second and reports whether it was acknowledged.
 * The receiver extracts the counter and displays it with the received text.
 *
 * @note
 * Use two nRF C Click boards: set APP_MODE to NRFC_MODE_TX on one board and NRFC_MODE_RX on the other.
 * Both boards must use the same channel, data rate, address, CRC, and payload size.
 * The default configuration uses channel 40 (2440 MHz), 1 Mbps, 0 dBm, a five-byte address,
 * 16-bit CRC, and 32-byte payloads with automatic acknowledgment. The first four payload bytes contain
 * the counter in big-endian order, so keep APP_TEXT_MESSAGE within 28 characters.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nrfc.h"

#ifndef MIKROBUS_POSITION_NRFC
    #define MIKROBUS_POSITION_NRFC MIKROBUS_1
#endif

/** Radio role: select NRFC_MODE_TX on the transmitter and NRFC_MODE_RX on the receiver. */
#define APP_MODE                NRFC_MODE_TX

/** Number of bytes used to transmit the packet counter before the text. */
#define APP_PACKET_COUNTER_SIZE 4

/** Offset of the null-terminated text in the radio packet. */
#define APP_PACKET_TEXT_OFFSET  APP_PACKET_COUNTER_SIZE

/** Text stored after the counter in a zero-padded 32-byte radio packet. */
#define APP_TEXT_MESSAGE        "Hello from nRF C Click!"

#if ( APP_MODE != NRFC_MODE_TX ) && ( APP_MODE != NRFC_MODE_RX )
    #error "APP_MODE must be NRFC_MODE_TX or NRFC_MODE_RX."
#endif

static nrfc_t nrfc;  /**< Click driver context. */
static log_t logger;  /**< UART logger context. */

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
