/*!
 * @file main.c
 * @brief ETH WIZ Click example
 *
 * # Description
 * This example exchanges messages with the MIKROE TCP/UDP echo server.
 * It uses the W5500 module and the mikroSDK SPI Ethernet transport in MACRAW mode for DHCP,
 * then switches W5500 socket 0 to TCP or UDP for each echo exchange.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the UART logger and the Click driver. Logs the W5500 version
 * and starts monitoring the Ethernet link.
 *
 * ## Application Task
 * On the first Ethernet link, obtains the IPv4 address, subnet mask, and
 * gateway through DHCP. Sends numbered messages, accumulates partial TCP
 * replies, and prints matching echoes. Closes the socket before switching
 * protocols.
 *
 * @note
 * Connect an Ethernet cable and set local_mac to a unique
 * locally administered address. The network must provide DHCP and permit TCP
 * and UDP to 54.187.244.144 on port 51111. DHCP runs once on the first link
 * and does not renew the lease. If no address is obtained, the example skips
 * the echo exchanges until reset.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ethwiz.h"
#include "eth_net.h"
#include "conversions.h"

#ifndef MIKROBUS_POSITION_ETHWIZ
    #define MIKROBUS_POSITION_ETHWIZ MIKROBUS_1
#endif

/** Remote IPv4 address and port of the MIKROE TCP/UDP echo service. */
#define APP_SERVER_IP                  54, 187, 244, 144
#define APP_SERVER_PORT                51111u

/** First local port. Each echo exchange advances the port, wrapping back to this value. */
#define APP_LOCAL_PORT                 50000u

/** Echo message prefix and buffer capacity for a decimal uint32_t counter and CRLF. */
#define APP_TEXT_MESSAGE               "Hello from ETH WIZ Click! Packet: "
#define APP_TEXT_MESSAGE_LENGTH        ( sizeof( APP_TEXT_MESSAGE ) - 1u )
#define APP_PACKET_COUNTER_DIGITS      10u
#define APP_MESSAGE_LINE_END_SIZE      2u
#define APP_MESSAGE_SIZE               ( APP_TEXT_MESSAGE_LENGTH + APP_PACKET_COUNTER_DIGITS + \
                                         APP_MESSAGE_LINE_END_SIZE + 1u )

/** Echo reply wait, pause between exchanges and idle link poll interval in milliseconds. */
#define APP_ECHO_WAIT_MS               3000u
#define APP_ECHO_INTERVAL_MS           1000u
#define APP_LINK_POLL_MS               100u

/** Size in bytes of the buffer shared by DHCP frame reception and echo replies. */
#define APP_RX_SIZE                    700u

/** DHCP send attempts, reply wait in milliseconds and transaction ID seed. */
#define APP_DHCP_RETRIES               5u
#define APP_DHCP_WAIT_MS               2000u
#define APP_DHCP_XID_SEED              0x39017623ul

/** Size of the BOOTP header and DHCP magic cookie, followed by DHCP option identifiers. */
#define APP_DHCP_FIXED_SIZE            240u
#define APP_DHCP_OPTION_PAD            0u
#define APP_DHCP_OPTION_SUBNET         1u
#define APP_DHCP_OPTION_ROUTER         3u
#define APP_DHCP_OPTION_END            255u

static ethwiz_t ethwiz;   /**< ETH WIZ Click driver context. */
static log_t logger;      /**< Example logger context. */

/** Locally administered MAC address. */
static uint8_t local_mac[ 6 ] = { 0x02, 0xDE, 0xAD, 0xBE, 0xEF, 0x05 };
static uint8_t local_ip[ 4 ];      /**< IPv4 address assigned by DHCP. */
static uint8_t local_subnet[ 4 ];  /**< Subnet mask received from DHCP. */
static uint8_t local_gateway[ 4 ]; /**< Router address received from DHCP. */

static uint8_t last_link = 0;          /**< Previous PHY link status. */
static uint8_t network_configured = 0; /**< First-link network setup has already been attempted. */
static uint8_t echo_ready = 0;         /**< Echo exchanges may run after successful network setup. */

/** Echo server address and port, plus the protocol and local port for the next exchange. */
static ethwiz_socket_t echo_endpoint = { W5500_Sn_MR_TCP, APP_LOCAL_PORT, { APP_SERVER_IP }, APP_SERVER_PORT };
static uint32_t app_packet_count = 1u; /**< Number appended to the next echo request. */
static uint8_t rx_buf[ APP_RX_SIZE ];  /**< Buffer shared by incoming DHCP frames and echo replies. */

/**
 * @brief ETH WIZ IPv4 address logging function.
 * @details This function prints a four-byte IPv4 address in dotted decimal.
 * @param[in] ip : Four-byte IPv4 address.
 * @return Nothing.
 * @note None.
 */
static void ethwiz_app_log_ip ( uint8_t *ip );

/**
 * @brief ETH WIZ network configuration function.
 * @details This function obtains and applies the IPv4 address, subnet mask and gateway through DHCP.
 * @return @li @c 1 - IPv4 configured and the required route settings are present,
 *         @li @c 0 - Configuration failed or the route is missing.
 * @note Called once when the Ethernet link first comes up.
 */
static uint8_t ethwiz_app_configure_network ( void );

/**
 * @brief ETH WIZ echo exchange function.
 * @details This function opens the socket, sends a numbered message, waits for the echo and closes the socket.
 * @return Nothing.
 * @note The next exchange uses the other protocol and a new source port.
 */
static void ethwiz_app_exchange_echo ( void );

/**
 * @brief ETH WIZ echo reply wait function.
 * @details This function polls the active socket, accumulates TCP chunks and checks each UDP datagram separately.
 * @param[in] message : Transmitted message.
 * @param[in] message_len : Number of sent bytes without the string terminator.
 * @return Nothing.
 * @note Logs the reply and advances the packet counter after the reply matches the transmitted bytes.
 */
static void ethwiz_app_wait_echo ( char *message, uint16_t message_len );

/**
 * @brief ETH WIZ DHCP address acquisition function.
 * @details This function acquires IPv4 settings with the SDK DHCP helpers, bounded by the configured reply wait and retries.
 * @return @li @c 1 - Address obtained,
 *         @li @c 0 - No address obtained.
 * @note Socket 0 must be in MACRAW mode. The example acquires a lease once.
 */
static uint8_t ethwiz_app_dhcp_obtain_ip ( void );

/**
 * @brief ETH WIZ DHCP route read function.
 * @details This function extracts the subnet mask and first router from a validated DHCP ACK.
 * @param[in] pkt : Ethernet frame with the validated ACK.
 * @param[in] len : Frame length in bytes.
 * @param[out] subnet : Four-byte subnet mask.
 * @param[out] gateway : Four-byte router address, zero if absent.
 * @return @li @c 1 - Subnet mask present,
 *         @li @c 0 - Subnet mask absent.
 * @note Call after eth_net_handle_dhcp accepts the ACK.
 */
static uint8_t ethwiz_app_dhcp_read_route ( uint8_t *pkt, uint16_t len, uint8_t *subnet, uint8_t *gateway );

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

static void ethwiz_app_log_ip ( uint8_t *ip )
{
    log_printf( &logger, "%u.%u.%u.%u", ( uint16_t ) ip[ 0 ], ( uint16_t ) ip[ 1 ],
                                        ( uint16_t ) ip[ 2 ], ( uint16_t ) ip[ 3 ] );
}

static uint8_t ethwiz_app_configure_network ( void )
{
    uint8_t index;
    uint8_t off_subnet = 0;
    uint8_t zero_ip[ 4 ] = { 0 };
    uint8_t ready = ethwiz_app_dhcp_obtain_ip( );
    if ( !ready )
    {
        log_error( &logger, " DHCP failed. Check the network and reset the application." );
    }
    else
    {
        for ( index = 0; index < sizeof( local_ip ); index++ )
        {
            if ( ( local_ip[ index ] ^ echo_endpoint.peer_ip[ index ] ) & local_subnet[ index ] )
            {
                off_subnet = 1;
                break;
            }
        }
        if ( !memcmp( local_ip, zero_ip, sizeof( local_ip ) ) ||
             !memcmp( local_subnet, zero_ip, sizeof( local_subnet ) ) ||
             ( off_subnet && !memcmp( local_gateway, zero_ip, sizeof( local_gateway ) ) ) )
        {
            log_error( &logger, " No route to the echo server. Check the DHCP subnet mask and gateway." );
            ready = 0;
        }
        else if ( ( ETHWIZ_ERROR == ethwiz_set_ip( &ethwiz, local_ip ) ) ||
                  ( ETHWIZ_ERROR == ethwiz_set_route( &ethwiz, local_subnet, local_gateway ) ) )
        {
            log_error( &logger, " IPv4 configuration." );
            ready = 0;
        }
        else
        {
            log_printf( &logger, "DHCP address: " );
            ethwiz_app_log_ip( local_ip );
            log_printf( &logger, "\r\nSubnet: " );
            ethwiz_app_log_ip( local_subnet );
            log_printf( &logger, "\r\nGateway: " );
            ethwiz_app_log_ip( local_gateway );
            log_printf( &logger, "\r\nEcho server: " );
            ethwiz_app_log_ip( echo_endpoint.peer_ip );
            log_printf( &logger, ":%u\r\n", ( uint16_t ) echo_endpoint.peer_port );
        }
    }
    return ready;
}

static void ethwiz_app_exchange_echo ( void )
{
    char message[ APP_MESSAGE_SIZE ] = APP_TEXT_MESSAGE;
    char *counter_text = &message[ APP_TEXT_MESSAGE_LENGTH ];
    char *protocol = "TCP";
    uint16_t message_len;

    uint32_to_str( app_packet_count, counter_text );
    l_trim( counter_text );
    r_trim( counter_text );
    strcat( message, "\r\n" );
    message_len = ( uint16_t ) strlen( message );

    if ( W5500_Sn_MR_UDP == echo_endpoint.protocol )
    {
        protocol = "UDP";
    }
    log_printf( &logger, "\r\n>>> Open %s socket ", protocol );
    ethwiz_app_log_ip( echo_endpoint.peer_ip );
    log_printf( &logger, ":%u.\r\n", ( uint16_t ) echo_endpoint.peer_port );

    if ( ETHWIZ_ERROR == ethwiz_socket_open( &ethwiz, &echo_endpoint ) )
    {
        log_error( &logger, " Echo socket could not be opened." );
    }
    else if ( ETHWIZ_ERROR == ethwiz_socket_send( &ethwiz, ( uint8_t * ) message, message_len ) )
    {
        log_error( &logger, " Echo message could not be sent." );
    }
    else
    {
        log_printf( &logger, ">>> TX: %s", message );
        ethwiz_app_wait_echo( message, message_len );
    }

    if ( ETHWIZ_ERROR == ethwiz_socket_close( &ethwiz ) )
    {
        log_error( &logger, " Echo socket could not be closed. Reset the application to reinitialize." );
        echo_ready = 0;
    }
    if ( W5500_Sn_MR_TCP == echo_endpoint.protocol )
    {
        echo_endpoint.protocol = W5500_Sn_MR_UDP;
    }
    else
    {
        echo_endpoint.protocol = W5500_Sn_MR_TCP;
    }
    /* Use a new source port so delayed replies cannot match the next exchange. */
    if ( ++echo_endpoint.local_port < APP_LOCAL_PORT )
    {
        echo_endpoint.local_port = APP_LOCAL_PORT;
    }
}

static void ethwiz_app_wait_echo ( char *message, uint16_t message_len )
{
    uint16_t elapsed_ms;
    uint16_t received;
    uint16_t filled = 0;

    for ( elapsed_ms = 0; elapsed_ms < APP_ECHO_WAIT_MS; elapsed_ms++ )
    {
        if ( ETHWIZ_ERROR == ethwiz_socket_receive( &ethwiz, &echo_endpoint, &rx_buf[ filled ],
                                                      message_len - filled, &received ) )
        {
            log_error( &logger, " Echo receive failed or the peer closed the socket." );
            break;
        }

        filled += received;
        if ( message_len == filled )
        {
            if ( !memcmp( rx_buf, message, message_len ) )
            {
                rx_buf[ filled ] = 0;
                log_printf( &logger, "<<< Echo: %s", ( char * ) rx_buf );
                app_packet_count++;
                break;
            }
            if ( W5500_Sn_MR_TCP == echo_endpoint.protocol )
            {
                log_error( &logger, " TCP reply did not match the sent message." );
                break;
            }
        }
        if ( W5500_Sn_MR_UDP == echo_endpoint.protocol )
        {
            filled = 0;
        }
        Delay_ms( 1 );
    }
    if ( APP_ECHO_WAIT_MS == elapsed_ms )
    {
        log_error( &logger, " Timed out waiting for a matching echo." );
    }
}

static uint8_t ethwiz_app_dhcp_obtain_ip ( void )
{
    static uint8_t dhcp_offered_ip[ 4 ];
    static uint8_t dhcp_server_ip[ 4 ];
    static uint8_t dhcp_src_ip[ 4 ];
    uint8_t dhcp_state = ETH_NET_DHCP_MSG_DISCOVER;
    uint8_t obtained = 0;
    uint8_t retry;
    uint8_t result;
    uint16_t elapsed_ms;
    uint16_t rx_len;
    uint8_t leased_ip[ 4 ];
    uint8_t offered_ip[ 4 ];
    uint8_t server_ip[ 4 ];
    uint8_t subnet[ 4 ];
    uint8_t gateway[ 4 ];
    uint32_t dhcp_xid;

    /* Follow the SDK example: derive the demonstration transaction ID from the configured MAC. */
    dhcp_xid = APP_DHCP_XID_SEED ^ ( ( ( uint32_t ) local_mac[ 2 ] << 24 ) |
                                     ( ( uint32_t ) local_mac[ 3 ] << 16 ) |
                                     ( ( uint32_t ) local_mac[ 4 ] << 8 ) | local_mac[ 5 ] );

    log_info( &logger, " Acquiring a DHCP address..." );
    for ( retry = 0; ( retry < APP_DHCP_RETRIES ) && !obtained; retry++ )
    {
        if ( !ethwiz_get_link_status( &ethwiz ) ||
             !eth_net_dhcp_send( &ethwiz.eth, dhcp_state, local_mac, dhcp_src_ip,
                                 dhcp_offered_ip, dhcp_server_ip, dhcp_xid ) )
        {
            break;
        }
        for ( elapsed_ms = 0; elapsed_ms < APP_DHCP_WAIT_MS; elapsed_ms++ )
        {
            rx_len = ethwiz_read_packet( &ethwiz, rx_buf, sizeof( rx_buf ) );
            /* Keep later offers from changing the server selected for our REQUEST. */
            memcpy( server_ip, dhcp_server_ip, sizeof( server_ip ) );
            result = eth_net_handle_dhcp( rx_buf, rx_len, local_mac, dhcp_xid,
                                          offered_ip, server_ip, leased_ip );
            if ( ( ETH_NET_DHCP_OFFER == result ) && ( ETH_NET_DHCP_MSG_DISCOVER == dhcp_state ) )
            {
                memcpy( dhcp_offered_ip, offered_ip, sizeof( dhcp_offered_ip ) );
                memcpy( dhcp_server_ip, server_ip, sizeof( dhcp_server_ip ) );
                dhcp_state = ETH_NET_DHCP_MSG_REQUEST;
                break;
            }
            else if ( ( ETH_NET_DHCP_ACK == result ) && ( ETH_NET_DHCP_MSG_REQUEST == dhcp_state ) )
            {
                if ( ethwiz_app_dhcp_read_route( rx_buf, rx_len, subnet, gateway ) )
                {
                    memcpy( local_ip, leased_ip, sizeof( local_ip ) );
                    memcpy( local_subnet, subnet, sizeof( local_subnet ) );
                    memcpy( local_gateway, gateway, sizeof( local_gateway ) );
                    obtained = 1;
                }
                else
                {
                    log_error( &logger, " DHCP ACK did not include a usable subnet mask." );
                }
                break;
            }
            else if ( ( ETH_NET_DHCP_NAK == result ) && ( ETH_NET_DHCP_MSG_REQUEST == dhcp_state ) )
            {
                dhcp_state = ETH_NET_DHCP_MSG_DISCOVER;
                memset( dhcp_offered_ip, 0, sizeof( dhcp_offered_ip ) );
                memset( dhcp_server_ip, 0, sizeof( dhcp_server_ip ) );
                break;
            }
            Delay_ms( 1 );
        }
    }
    return obtained;
}

static uint8_t ethwiz_app_dhcp_read_route ( uint8_t *pkt, uint16_t len, uint8_t *subnet, uint8_t *gateway )
{
    uint16_t ip_payload_len;
    uint8_t *udp = eth_net_ipv4_payload( pkt, len, &ip_payload_len );
    uint16_t udp_len;
    uint16_t offset = ETH_NET_UDP_HEADER_SIZE + APP_DHCP_FIXED_SIZE;
    uint8_t option;
    uint8_t option_len;
    uint8_t subnet_found = 0;

    memset( gateway, 0, 4 );
    if ( udp && ( ip_payload_len >= offset ) )
    {
        /* The SDK validates the ACK. Bound these additional options by the UDP length. */
        udp_len = ( ( uint16_t ) udp[ 4 ] << 8 ) | udp[ 5 ];
        while ( ( offset < udp_len ) && ( udp_len <= ip_payload_len ) )
        {
            option = udp[ offset++ ];
            if ( APP_DHCP_OPTION_END == option )
            {
                break;
            }
            if ( APP_DHCP_OPTION_PAD == option )
            {
                continue;
            }
            if ( offset == udp_len )
            {
                break;
            }
            option_len = udp[ offset++ ];
            if ( option_len > ( udp_len - offset ) )
            {
                break;
            }
            if ( ( APP_DHCP_OPTION_SUBNET == option ) && ( 4 == option_len ) )
            {
                memcpy( subnet, &udp[ offset ], 4 );
                subnet_found = 1;
            }
            else if ( ( APP_DHCP_OPTION_ROUTER == option ) && ( option_len >= 4 ) && !( option_len % 4 ) )
            {
                memcpy( gateway, &udp[ offset ], 4 );
            }
            offset += option_len;
        }
    }
    return subnet_found;
}

// ------------------------------------------------------------------------ END
