/*!
 * @file main.c
 * @brief Two-Wire ETH Click example
 *
 * # Description
 * This example demonstrates raw Ethernet communication between two Click boards over a single twisted pair.
 * Both hosts run the same example and use the factory MAC address of their Click board.
 * Each frame uses EtherType 0x88B5 and carries a two-byte packet number in network byte order.
 *
 * The demo application has two sections.
 *
 * ## Application Init
 * Initializes the UART logger at 115200 baud and the LAN8651 in CSMA/CD mode.
 * Reads the MAC address from the AT24MAC402, logs it with the LAN8651 silicon revision,
 * and prepares a broadcast request.
 *
 * ## Application Task
 * Broadcasts a numbered request and polls for peer frames 500 times with a 1 ms delay per poll.
 * Each board increments the number in a peer request and replies directly to that board.
 * The sender logs each verified reply with the peer MAC address or reports a timeout.
 *
 * @note
 * Use one Click per host. Connect P to P and N to N. Close both TERM jumpers (J1 and J2)
 * on each board to terminate the two ends. Program both hosts with this example. Either host may start first.
 * Packet numbers are two bytes and wrap from 65535 to 0.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "twowireeth.h"
#include "eth_net.h"

#ifndef MIKROBUS_POSITION_TWOWIREETH
    #define MIKROBUS_POSITION_TWOWIREETH MIKROBUS_1
#endif

/**
 * @brief Ethernet frame layout for the two-board exchange.
 * @details Bytes 0-5 contain the destination MAC (broadcast for requests, unicast for replies).
 * Bytes 6-11 contain the source MAC. Bytes 12-13 contain EtherType 0x88B5, most significant byte first.
 * Bytes 14-15 contain the packet number, most significant byte first.
 * The SDK pads these 16 bytes to 60 bytes and the MAC adds the FCS.
 * The receive API returns the padded frame without the FCS.
 */
#define APP_ETHER_TYPE                 0x88B5u
#define APP_MAC_SIZE                   6u
#define APP_TYPE_OFFSET                ( 2u * APP_MAC_SIZE )

/** Poll for peer frames at 1 ms intervals between broadcasts. */
#define APP_REPLY_POLLS                500u

static twowireeth_t twowireeth;
static log_t logger;
static uint8_t request[ ETH_NET_ETH_HEADER_SIZE + 2u ];

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    twowireeth_cfg_t twowireeth_cfg;  /**< Click config object. */

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
    twowireeth_cfg_setup( &twowireeth_cfg );
    TWOWIREETH_MAP_MIKROBUS( twowireeth_cfg, MIKROBUS_POSITION_TWOWIREETH );

    if ( TWOWIREETH_ERROR == twowireeth_init( &twowireeth, &twowireeth_cfg ) )
    {
        log_error( &logger, " SPI, GPIO or factory MAC initialization failed." );
        for ( ; ; );
    }

    if ( TWOWIREETH_ERROR == twowireeth_default_cfg( &twowireeth ) )
    {
        log_error( &logger, " LAN8651 configuration. Check the SPI connection." );
        for ( ; ; );
    }

    uint16_t version = 0;
    if ( TWOWIREETH_ERROR == twowireeth_get_version( &twowireeth, &version ) )
    {
        log_error( &logger, " Could not verify the LAN8651 revision." );
        for ( ; ; );
    }
    log_printf( &logger, "LAN8651 revision 0x%.2X | Local MAC %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n", version,
                ( uint16_t ) twowireeth.eth.mac[ 0 ], ( uint16_t ) twowireeth.eth.mac[ 1 ],
                ( uint16_t ) twowireeth.eth.mac[ 2 ], ( uint16_t ) twowireeth.eth.mac[ 3 ],
                ( uint16_t ) twowireeth.eth.mac[ 4 ], ( uint16_t ) twowireeth.eth.mac[ 5 ] );

    // Reuse the Ethernet header for every request. Only the packet number changes.
    memset( request, 0xFF, APP_MAC_SIZE );
    memcpy( &request[ APP_MAC_SIZE ], twowireeth.eth.mac, APP_MAC_SIZE );
    request[ APP_TYPE_OFFSET ] = ( uint8_t ) ( APP_ETHER_TYPE >> 8 );
    request[ APP_TYPE_OFFSET + 1u ] = ( uint8_t ) APP_ETHER_TYPE;

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint16_t request_number;
    uint8_t frame[ LAN8651_MIN_FRAME_SIZE + 1u ];
    uint8_t *peer = &frame[ APP_MAC_SIZE ];
    uint16_t expected_reply;
    uint8_t replied = 0;

    request_number++;
    expected_reply = ( uint16_t ) ( request_number + 1u );
    request[ ETH_NET_ETH_HEADER_SIZE ] = ( uint8_t ) ( request_number >> 8 );
    request[ ETH_NET_ETH_HEADER_SIZE + 1u ] = ( uint8_t ) request_number;

    uint16_t sent = twowireeth_send_packet( &twowireeth, request, sizeof( request ) );
    if ( !sent )
    {
        log_error( &logger, " Request %u transmission failed.", request_number );
    }

    // Keep polling after a matching reply so this board also answers the peer's requests.
    for ( uint16_t poll = 0; poll < APP_REPLY_POLLS; poll++ )
    {
        Delay_ms( 1 );
        /* One extra receive byte distinguishes larger frames even when the SDK truncates them. */
        uint16_t received = twowireeth_read_packet( &twowireeth, frame, sizeof( frame ) );
        if ( ( received != LAN8651_MIN_FRAME_SIZE ) ||
             memcmp( &frame[ APP_TYPE_OFFSET ], &request[ APP_TYPE_OFFSET ], 2u ) ||
             !memcmp( peer, twowireeth.eth.mac, APP_MAC_SIZE ) )
        {
            continue;
        }

        uint16_t received_number = ( ( uint16_t ) frame[ ETH_NET_ETH_HEADER_SIZE ] << 8 ) |
                                   frame[ ETH_NET_ETH_HEADER_SIZE + 1u ];
        // A broadcast is a request. Address its reply directly to the original sender.
        if ( !memcmp( frame, request, APP_MAC_SIZE ) )
        {
            memcpy( frame, peer, APP_MAC_SIZE );
            memcpy( peer, twowireeth.eth.mac, APP_MAC_SIZE );
            received_number++;
            frame[ ETH_NET_ETH_HEADER_SIZE ] = ( uint8_t ) ( received_number >> 8 );
            frame[ ETH_NET_ETH_HEADER_SIZE + 1u ] = ( uint8_t ) received_number;
            if ( !twowireeth_send_packet( &twowireeth, frame, sizeof( request ) ) )
            {
                log_error( &logger, " Reply transmission failed." );
            }
        }
        else if ( sent && !replied && ( expected_reply == received_number ) &&
                  !memcmp( frame, twowireeth.eth.mac, APP_MAC_SIZE ) )
        {
            replied = 1;
            log_printf( &logger, "Request %u -> reply %u from %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",
                        request_number, expected_reply,
                        ( uint16_t ) peer[ 0 ], ( uint16_t ) peer[ 1 ], ( uint16_t ) peer[ 2 ],
                        ( uint16_t ) peer[ 3 ], ( uint16_t ) peer[ 4 ], ( uint16_t ) peer[ 5 ] );
        }
    }
    if ( sent && !replied )
    {
        log_printf( &logger, "Request %u timed out\r\n", request_number );
    }
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
