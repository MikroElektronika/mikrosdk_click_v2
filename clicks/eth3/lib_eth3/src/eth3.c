/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file eth3.c
 * @brief ETH 3 Click Driver.
 */

#include "eth3.h"
#include "eth_net.h"

/**
 * @brief ETH 3 transport settings.
 * @details Defines the dummy byte clocked out during SPI reads.
 */
#define ETH3_SPI_DUMMY                  0x00u

/**
 * @brief LAN9250 SPI register addressing.
 * @details Bit 14 advances the byte address by four after each complete register.
 */
#define ETH3_SPI_ADDR_INCREMENT         0x40u
#define ETH3_REG_SIZE                   4u

/**
 * @brief ETH 3 Ethernet/IPv4 ARP fields.
 * @details Defines the Ethernet address sizes, ARP field offsets and values used for next-hop resolution.
 */
#define ETH3_MAC_ADDR_SIZE              6u
#define ETH3_IPV4_ADDR_SIZE             4u
#define ETH3_MAC_BROADCAST_BYTE         0xFFu
#define ETH3_MAC_GROUP_BIT              0x01u
#define ETH3_FRAME_TYPE_OFFSET          ( 2u * ETH3_MAC_ADDR_SIZE )
#define ETH3_ARP_HW_ETHERNET            0x0001u
#define ETH3_ARP_OP_REQUEST             0x0001u
#define ETH3_ARP_OP_REPLY               0x0002u
#define ETH3_ARP_OPCODE_OFFSET          6u
#define ETH3_ARP_SENDER_MAC_OFFSET      8u
#define ETH3_ARP_SENDER_IP_OFFSET       14u
#define ETH3_ARP_TARGET_MAC_OFFSET      18u
#define ETH3_ARP_TARGET_IP_OFFSET       24u
#define ETH3_ARP_TYPE_MATCH_LEN         ( ETH_NET_ETH_HEADER_SIZE - ETH3_FRAME_TYPE_OFFSET + ETH3_ARP_OPCODE_OFFSET )

/**
 * @brief ETH 3 ARP and socket settings.
 * @details Defines the frame length, retry counts, poll budgets and TCP sequence number increment.
 * @note Each wait includes time spent processing frames in addition to the 1 ms polling delays.
 */
#define ETH3_ARP_FRAME_SIZE             42u
#define ETH3_ARP_RETRIES                3u
#define ETH3_ARP_POLLS                  1000u
#define ETH3_REPLY_POLLS                3000u
#define ETH3_TCP_RETRY_POLLS            1000u
#define ETH3_TCP_SEQ_STEP               64001ul

/**
 * @brief ETH 3 TCP and UDP request limits.
 * @details Defines the largest request payload the SDK transmit buffer can hold for each protocol.
 */
#define ETH3_TCP_PAYLOAD_MAX            ( ETH_NET_TX_BUF_SIZE - ETH_NET_ETH_HEADER_SIZE - \
                                          ETH_NET_IP_HEADER_SIZE - ETH_NET_TCP_HEADER_SIZE )
#define ETH3_UDP_PAYLOAD_MAX            ( ETH_NET_TX_BUF_SIZE - ETH_NET_ETH_HEADER_SIZE - \
                                          ETH_NET_IP_HEADER_SIZE - ETH_NET_UDP_HEADER_SIZE )

/**
 * @brief ETH 3 system register transfer function.
 * @details Transfers aligned DWORDs in a single auto-incrementing SPI transaction.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in] instr : LAN9250 SPI read or write instruction.
 * @param[in] reg : Byte address of the first register.
 * @param[in,out] buf : Register bytes, least significant byte first in each DWORD.
 * @param[in] len : Byte count, a nonzero multiple of four.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid register span or SPI error.
 * See #err_t definition for detailed explanation.
 * @note Use documented registers and access permissions.
 */
static err_t eth3_transfer_regs ( eth3_t *ctx, uint8_t instr, uint16_t reg, uint8_t *buf, uint16_t len );

/**
 * @brief ETH 3 16-bit network word read function.
 * @details Reads two bytes in big-endian order.
 * @param[in] bytes : Pointer to two readable bytes.
 * @return The 16-bit value in host byte order.
 * @note The input may be unaligned.
 */
static uint16_t eth3_read_u16 ( uint8_t *bytes );

/**
 * @brief ETH 3 32-bit network word read function.
 * @details Reads a TCP sequence or acknowledgment number in big-endian order.
 * @param[in] bytes : Pointer to four readable bytes.
 * @return The 32-bit value in host byte order.
 * @note The input may be unaligned.
 */
static uint32_t eth3_read_u32 ( uint8_t *bytes );

/**
 * @brief ETH 3 transport checksum validation function.
 * @details Checks the one's complement sum of the IPv4 pseudo-header and the TCP or UDP segment.
 * @param[in] ip : Validated IPv4 header containing the protocol and addresses.
 * @param[in] segment : Transport header and payload, including the received checksum.
 * @param[in] len : Transport header and payload length in bytes.
 * @return @li @c 1 - Checksum valid,
 *         @li @c 0 - Checksum invalid.
 * @note The caller handles the optional zero checksum for IPv4 UDP.
 */
static uint8_t eth3_checksum_ok ( uint8_t *ip, uint8_t *segment, uint16_t len );

/**
 * @brief ETH 3 peer segment read function.
 * @details Reads one Ethernet frame and checks the IPv4 addresses, protocol, ports, transport length and checksum.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in,out] endpoint : TCP or UDP peer and its receive frame buffer.
 * See #eth3_socket_t object definition for detailed explanation.
 * @param[out] len : Transport header and payload length in bytes, or zero if no matching segment is read.
 * @return Pointer to the transport header in the receive frame buffer, or NULL if no matching segment is read.
 * @note The pointer is valid until the frame buffer is reused.
 */
static uint8_t *eth3_peer_segment ( eth3_t *ctx, eth3_socket_t *endpoint, uint16_t *len );

/**
 * @brief ETH 3 UDP exchange function.
 * @details Sends one datagram and waits for a reply of the expected length from the configured peer.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in,out] endpoint : UDP peer, local port and receive frame buffer.
 * See #eth3_socket_t object definition for detailed explanation.
 * @param[in] request : Request payload.
 * @param[in] len : Request payload length in bytes.
 * @param[out] reply : Reply buffer with space for reply_len bytes.
 * @param[in] reply_len : Expected reply payload length in bytes.
 * @return @li @c  0 - Complete reply copied,
 *         @li @c -3 - Datagram transmission failed,
 *         @li @c -4 - No matching reply within the poll budget.
 * See #err_t definition for detailed explanation.
 * @note The reply buffer is updated only when a datagram of the expected length is received.
 */
static err_t eth3_udp_exchange ( eth3_t *ctx, eth3_socket_t *endpoint, uint8_t *request, uint16_t len,
                                 uint8_t *reply, uint16_t reply_len );

/**
 * @brief ETH 3 TCP segment send function.
 * @details Uses the SDK to send a TCP segment with the configured addresses and ports.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in] endpoint : TCP peer, local port and resolved next-hop MAC address.
 * See #eth3_socket_t object definition for detailed explanation.
 * @param[in] seq : TCP sequence number in host byte order.
 * @param[in] ack : TCP acknowledgment number in host byte order.
 * @param[in] flags : TCP control flags from ETH_NET_TCP_FLAG_*.
 * @param[in] payload : Segment payload or NULL for a control-only segment.
 * @param[in] len : Segment payload length in bytes.
 * @return Number of Ethernet frame bytes sent, or zero on error.
 * @note The caller manages the TCP connection state and retry budget.
 */
static uint16_t eth3_tcp_send ( eth3_t *ctx, eth3_socket_t *endpoint, uint32_t seq, uint32_t ack, uint8_t flags,
                                uint8_t *payload, uint16_t len );

/**
 * @brief ETH 3 TCP connection establishment function.
 * @details Sends SYN and acknowledges a valid SYN/ACK when the peer advertises enough window space for the request.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in,out] endpoint : TCP peer, initial sequence number and receive frame buffer.
 * See #eth3_socket_t object definition for detailed explanation.
 * @param[out] peer_next : Next expected peer sequence number after receiving the SYN/ACK.
 * @param[in] len : Request length in bytes used to check the peer's receive window.
 * @return @li @c  0 - Handshake ACK sent,
 *         @li @c -2 - Peer reset the handshake or no acceptable SYN/ACK arrived within the poll budget,
 *         @li @c -3 - SYN or ACK transmission failed.
 * See #err_t definition for detailed explanation.
 * @note Use peer_next after a successful handshake.
 */
static err_t eth3_tcp_connect ( eth3_t *ctx, eth3_socket_t *endpoint, uint32_t *peer_next, uint16_t len );

/**
 * @brief ETH 3 TCP exchange function.
 * @details Sends one request on an open TCP connection and collects the reply across in-order or overlapping segments.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in,out] endpoint : TCP peer, receive frame buffer and initial sequence number.
 * See #eth3_socket_t object definition for detailed explanation.
 * @param[in] peer_next : Next expected peer sequence number after connection establishment.
 * @param[in] request : Request payload.
 * @param[in] len : Request payload length in bytes.
 * @param[out] reply : Reply buffer with space for reply_len bytes.
 * @param[in] reply_len : Expected reply payload length in bytes.
 * @return @li @c  0 - Complete reply received and acknowledged,
 *         @li @c -3 - TCP frame transmission failed,
 *         @li @c -4 - Reply incomplete, too long, or timed out.
 * See #err_t definition for detailed explanation.
 * @note The reply buffer may contain partial bytes on failure.
 */
static err_t eth3_tcp_exchange ( eth3_t *ctx, eth3_socket_t *endpoint, uint32_t peer_next,
                                 uint8_t *request, uint16_t len, uint8_t *reply, uint16_t reply_len );

void eth3_cfg_setup ( eth3_cfg_t *cfg )
{
    cfg->sck     = HAL_PIN_NC;
    cfg->miso    = HAL_PIN_NC;
    cfg->mosi    = HAL_PIN_NC;
    cfg->cs      = HAL_PIN_NC;
    cfg->rst     = HAL_PIN_NC;
    cfg->pme     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = ETH3_SPI_SPEED;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->full_duplex = 1;
    memset( cfg->mac, 0, sizeof( cfg->mac ) );
    memset( cfg->ip, 0, sizeof( cfg->ip ) );
}

err_t eth3_init ( eth3_t *ctx, eth3_cfg_t *cfg )
{
    err_t error_flag = ETH3_OK;
    lan9250_cfg_t eth3_cfg;

    lan9250_cfg_setup( &eth3_cfg );
    eth3_cfg.bus.sck = cfg->sck;
    eth3_cfg.bus.miso = cfg->miso;
    eth3_cfg.bus.mosi = cfg->mosi;
    eth3_cfg.bus.cs = cfg->cs;
    eth3_cfg.bus.speed = cfg->spi_speed;
    eth3_cfg.bus.mode = cfg->spi_mode;
    eth3_cfg.eth.rst = cfg->rst;
    eth3_cfg.eth.full_duplex = cfg->full_duplex;
    memcpy( eth3_cfg.eth.mac, cfg->mac, sizeof( cfg->mac ) );
    memcpy( eth3_cfg.eth.ip, cfg->ip, sizeof( cfg->ip ) );

    ctx->eth.driver_ctx = &ctx->controller;
    ctx->eth.drv = NULL;
    ctx->controller.id_rev = 0;

    /* The SDK deselects the device while configuring the SPI bus. */
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    if ( ETH_TRANSPORT_ERROR == lan9250_configure( &ctx->eth, &ctx->bus, &eth3_cfg ) )
    {
        error_flag = ETH3_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->bus.spi, ETH3_SPI_DUMMY ) )
    {
        error_flag = ETH3_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->bus.spi, cfg->spi_mode ) )
    {
        error_flag = ETH3_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->bus.spi, cfg->spi_speed ) )
    {
        error_flag = ETH3_ERROR;
    }
    else if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->pme, cfg->pme ) )
    {
        error_flag = ETH3_ERROR;
    }
    else if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->int_pin, cfg->int_pin ) )
    {
        error_flag = ETH3_ERROR;
    }
    else
    {
        /* Release the LAN9250 from reset. */
        eth3_set_rst_pin( ctx, 1 );
    }

    return error_flag;
}

err_t eth3_default_cfg ( eth3_t *ctx )
{
    err_t error_flag = eth_transport_init( &ctx->eth, &lan9250_driver );

    if ( ETH_TRANSPORT_ERROR == error_flag )
    {
        ctx->eth.drv = NULL;
        ctx->controller.id_rev = 0;
    }
    return error_flag;
}

err_t eth3_write_reg ( eth3_t *ctx, uint16_t reg, uint32_t value )
{
    uint8_t bytes[ ETH3_REG_SIZE ];
    bytes[ 0 ] = ( uint8_t ) value;
    bytes[ 1 ] = ( uint8_t ) ( value >> 8 );
    bytes[ 2 ] = ( uint8_t ) ( value >> 16 );
    bytes[ 3 ] = ( uint8_t ) ( value >> 24 );
    return eth3_write_regs( ctx, reg, bytes, sizeof( bytes ) );
}

err_t eth3_write_regs ( eth3_t *ctx, uint16_t reg, uint8_t *data_in, uint16_t len )
{
    return eth3_transfer_regs( ctx, LAN9250_SPI_INSTR_WRITE, reg, data_in, len );
}

err_t eth3_read_reg ( eth3_t *ctx, uint16_t reg, uint32_t *value )
{
    uint8_t bytes[ ETH3_REG_SIZE ];
    err_t error_flag = eth3_read_regs( ctx, reg, bytes, sizeof( bytes ) );

    if ( ETH3_OK == error_flag )
    {
        *value = ( uint32_t ) bytes[ 0 ] | ( ( uint32_t ) bytes[ 1 ] << 8 ) |
                 ( ( uint32_t ) bytes[ 2 ] << 16 ) | ( ( uint32_t ) bytes[ 3 ] << 24 );
    }
    return error_flag;
}

err_t eth3_read_regs ( eth3_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len )
{
    return eth3_transfer_regs( ctx, LAN9250_SPI_INSTR_READ, reg, data_out, len );
}

err_t eth3_get_version ( eth3_t *ctx, uint16_t *version )
{
    uint32_t id_rev;
    err_t error_flag = eth3_read_reg( ctx, LAN9250_ID_REV, &id_rev );

    if ( ETH3_OK == error_flag )
    {
        if ( LAN9250_ID_REV_CHIP_ID_LAN9250 == ( id_rev & LAN9250_ID_REV_CHIP_ID_MASK ) )
        {
            *version = ( uint16_t ) id_rev;
        }
        else
        {
            error_flag = ETH3_ERROR;
        }
    }
    return error_flag;
}

err_t eth3_set_mac ( eth3_t *ctx, uint8_t *mac )
{
    return eth_transport_set_mac( &ctx->eth, mac );
}

err_t eth3_set_ip ( eth3_t *ctx, uint8_t *ip )
{
    return eth_transport_set_ip( &ctx->eth, ip );
}

uint16_t eth3_service_frame ( eth3_t *ctx, uint8_t *frame, uint16_t capacity )
{
    uint16_t len = eth3_read_packet( ctx, frame, capacity );

    if ( len >= ETH_NET_ETH_HEADER_SIZE )
    {
        eth_net_handle_arp( &ctx->eth, ctx->eth.mac, ctx->eth.ip, frame, len );
        eth_net_handle_icmp( &ctx->eth, ctx->eth.mac, ctx->eth.ip, frame, len );
    }
    return len;
}

err_t eth3_resolve_mac ( eth3_t *ctx, eth3_socket_t *endpoint, uint8_t *ip )
{
    uint8_t request[ ETH3_ARP_FRAME_SIZE ] = {
        ETH3_MAC_BROADCAST_BYTE, ETH3_MAC_BROADCAST_BYTE, ETH3_MAC_BROADCAST_BYTE,
        ETH3_MAC_BROADCAST_BYTE, ETH3_MAC_BROADCAST_BYTE, ETH3_MAC_BROADCAST_BYTE,
        0, 0, 0, 0, 0, 0,
        ( uint8_t ) ( ETH_NET_ETHERTYPE_ARP >> 8 ), ( uint8_t ) ETH_NET_ETHERTYPE_ARP,
        ( uint8_t ) ( ETH3_ARP_HW_ETHERNET >> 8 ), ( uint8_t ) ETH3_ARP_HW_ETHERNET,
        ( uint8_t ) ( ETH_NET_ETHERTYPE_IPV4 >> 8 ), ( uint8_t ) ETH_NET_ETHERTYPE_IPV4,
        ETH3_MAC_ADDR_SIZE, ETH3_IPV4_ADDR_SIZE,
        ( uint8_t ) ( ETH3_ARP_OP_REQUEST >> 8 ), ( uint8_t ) ETH3_ARP_OP_REQUEST
    };
    uint8_t *arp_request = &request[ ETH_NET_ETH_HEADER_SIZE ];
    uint8_t *arp;
    err_t error_flag = ETH3_ERROR;
    uint8_t retry;
    uint16_t elapsed_ms;

    memcpy( &request[ ETH3_MAC_ADDR_SIZE ], ctx->eth.mac, ETH3_MAC_ADDR_SIZE );
    memcpy( &arp_request[ ETH3_ARP_SENDER_MAC_OFFSET ], ctx->eth.mac, ETH3_MAC_ADDR_SIZE );
    memcpy( &arp_request[ ETH3_ARP_SENDER_IP_OFFSET ], ctx->eth.ip, ETH3_IPV4_ADDR_SIZE );
    memcpy( &arp_request[ ETH3_ARP_TARGET_IP_OFFSET ], ip, ETH3_IPV4_ADDR_SIZE );

    for ( retry = 0; ( retry < ETH3_ARP_RETRIES ) && ( ETH3_ERROR == error_flag ) &&
          endpoint->frame && ( endpoint->frame_size >= ETH3_ARP_FRAME_SIZE ); retry++ )
    {
        arp = &endpoint->frame[ ETH_NET_ETH_HEADER_SIZE ];
        if ( !eth3_send_packet( ctx, request, sizeof( request ) ) )
        {
            break;
        }
        for ( elapsed_ms = 0; elapsed_ms < ETH3_ARP_POLLS; elapsed_ms++ )
        {
            uint16_t frame_len = eth3_service_frame( ctx, endpoint->frame, endpoint->frame_size );

            /* Check the frame length before reading the ARP header and addresses. */
            if ( ( frame_len >= ETH3_ARP_FRAME_SIZE ) &&
                 !memcmp( &endpoint->frame[ ETH3_FRAME_TYPE_OFFSET ], &request[ ETH3_FRAME_TYPE_OFFSET ],
                          ETH3_ARP_TYPE_MATCH_LEN ) &&
                 ( ETH3_ARP_OP_REPLY == eth3_read_u16( &arp[ ETH3_ARP_OPCODE_OFFSET ] ) ) )
            {
                uint8_t target_matches = !memcmp( endpoint->frame, ctx->eth.mac, ETH3_MAC_ADDR_SIZE ) &&
                                         !memcmp( &arp[ ETH3_ARP_TARGET_MAC_OFFSET ], ctx->eth.mac, ETH3_MAC_ADDR_SIZE ) &&
                                         !memcmp( &arp[ ETH3_ARP_TARGET_IP_OFFSET ], ctx->eth.ip, ETH3_IPV4_ADDR_SIZE );
                uint8_t *sender_mac = &arp[ ETH3_ARP_SENDER_MAC_OFFSET ];
                uint8_t sender_matches = !memcmp( &arp[ ETH3_ARP_SENDER_IP_OFFSET ], ip, ETH3_IPV4_ADDR_SIZE ) &&
                                         !( sender_mac[ 0 ] & ETH3_MAC_GROUP_BIT ) &&
                                         !memcmp( sender_mac, &endpoint->frame[ ETH3_MAC_ADDR_SIZE ], ETH3_MAC_ADDR_SIZE );

                if ( target_matches && sender_matches )
                {
                    memcpy( endpoint->next_hop_mac, sender_mac, sizeof( endpoint->next_hop_mac ) );
                    error_flag = ETH3_OK;
                    break;
                }
            }
            Delay_1ms( );
        }
    }
    return error_flag;
}

err_t eth3_socket_exchange ( eth3_t *ctx, eth3_socket_t *endpoint, uint8_t *request, uint16_t len,
                             uint8_t *reply, uint16_t reply_len )
{
    err_t error_flag = ETH3_ERROR;

    if ( request && reply && len && reply_len && endpoint->frame &&
         ( endpoint->frame_size >= ETH_NET_ETH_HEADER_SIZE + ETH_NET_IP_HEADER_SIZE + ETH_NET_UDP_HEADER_SIZE ) )
    {
        if ( ( ETH_NET_IP_PROTO_UDP == endpoint->protocol ) && ( len <= ETH3_UDP_PAYLOAD_MAX ) )
        {
            error_flag = eth3_udp_exchange( ctx, endpoint, request, len, reply, reply_len );
        }
        else if ( ( ETH_NET_IP_PROTO_TCP == endpoint->protocol ) && ( len <= ETH3_TCP_PAYLOAD_MAX ) )
        {
            uint32_t peer_next = 0;

            /* Finish the handshake before allocating the exchange's local state. */
            error_flag = eth3_tcp_connect( ctx, endpoint, &peer_next, len );
            if ( ETH3_OK == error_flag )
            {
                error_flag = eth3_tcp_exchange( ctx, endpoint, peer_next, request, len, reply, reply_len );
            }
            endpoint->sequence += ETH3_TCP_SEQ_STEP;
        }
    }
    return error_flag;
}

uint16_t eth3_send_packet ( eth3_t *ctx, uint8_t *data_in, uint16_t len )
{
    uint16_t sent_len = 0;

    if ( ( len >= ETH_NET_ETH_HEADER_SIZE ) && ( len <= ETH3_FRAME_SIZE ) )
    {
        sent_len = eth_transport_send( &ctx->eth, data_in, len );
        if ( ctx->eth.bus_error )
        {
            sent_len = 0;
        }
    }
    return sent_len;
}

uint16_t eth3_read_packet ( eth3_t *ctx, uint8_t *data_out, uint16_t len )
{
    return eth_transport_receive( &ctx->eth, data_out, len );
}

uint8_t eth3_packet_available ( eth3_t *ctx )
{
    return eth_transport_available( &ctx->eth );
}

uint8_t eth3_get_link_status ( eth3_t *ctx )
{
    uint8_t link_status;

    ctx->eth.bus_error = 0;
    link_status = eth_transport_get_link_status( &ctx->eth );
    if ( ctx->eth.bus_error )
    {
        link_status = 0;
    }
    return link_status;
}

void eth3_set_rst_pin ( eth3_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->eth.reset, state );
    if ( !state )
    {
        ctx->eth.drv = NULL;
        ctx->controller.id_rev = 0;
    }
}

uint8_t eth3_get_int_pin ( eth3_t *ctx )
{
    return !!digital_in_read( &ctx->int_pin );
}

uint8_t eth3_get_pme_pin ( eth3_t *ctx )
{
    return !!digital_in_read( &ctx->pme );
}

static err_t eth3_transfer_regs ( eth3_t *ctx, uint8_t instr, uint16_t reg, uint8_t *buf, uint16_t len )
{
    uint8_t cmd[ 3 ];
    err_t error_flag = ETH3_ERROR;

    if ( buf && len && !( reg % ETH3_REG_SIZE ) && !( len % ETH3_REG_SIZE ) &&
         ( reg <= LAN9250_RESET_CTL ) && ( len <= LAN9250_RESET_CTL + ETH3_REG_SIZE - reg ) )
    {
        cmd[ 0 ] = instr;
        cmd[ 1 ] = ( uint8_t ) ( reg >> 8 ) | ETH3_SPI_ADDR_INCREMENT;
        cmd[ 2 ] = ( uint8_t ) reg;
        if ( LAN9250_SPI_INSTR_READ == instr )
        {
            error_flag = eth_transport_bus_read( &ctx->eth, cmd, sizeof( cmd ), buf, len );
        }
        else
        {
            error_flag = eth_transport_bus_write( &ctx->eth, cmd, sizeof( cmd ), buf, len );
        }
    }
    return error_flag;
}

static uint16_t eth3_read_u16 ( uint8_t *bytes )
{
    return ( ( uint16_t ) bytes[ 0 ] << 8 ) | bytes[ 1 ];
}

static uint32_t eth3_read_u32 ( uint8_t *bytes )
{
    return ( ( uint32_t ) eth3_read_u16( bytes ) << 16 ) | eth3_read_u16( bytes + 2 );
}

static uint8_t eth3_checksum_ok ( uint8_t *ip, uint8_t *segment, uint16_t len )
{
    uint32_t sum = ( uint32_t ) ip[ 9 ] + len;
    uint16_t index;

    for ( index = 12; index < 20; index += 2 )
    {
        sum += eth3_read_u16( &ip[ index ] );
    }
    while ( len >= 2u )
    {
        sum += eth3_read_u16( segment );
        segment += 2;
        len -= 2;
    }
    if ( len )
    {
        sum += ( uint32_t ) segment[ 0 ] << 8;
    }
    while ( sum >> 16 )
    {
        sum = ( sum & 0xFFFFul ) + ( sum >> 16 );
    }
    return ( 0xFFFFu == sum );
}

static uint8_t *eth3_peer_segment ( eth3_t *ctx, eth3_socket_t *endpoint, uint16_t *len )
{
    uint16_t frame_len = eth3_service_frame( ctx, endpoint->frame, endpoint->frame_size );
    uint16_t size = 0;
    uint8_t *segment = eth_net_ipv4_payload( endpoint->frame, frame_len, &size );
    uint8_t *ip = &endpoint->frame[ ETH_NET_ETH_HEADER_SIZE ];
    uint8_t *match = NULL;
    volatile uint8_t protocol = endpoint->protocol;

    *len = 0;
    if ( segment && ( size >= ETH_NET_UDP_HEADER_SIZE ) && ( ip[ 9 ] == protocol ) &&
         !memcmp( endpoint->frame, ctx->eth.mac, 6 ) && !memcmp( &ip[ 12 ], endpoint->peer_ip, 4 ) &&
         !memcmp( &ip[ 16 ], ctx->eth.ip, 4 ) &&
         ( endpoint->peer_port == eth3_read_u16( segment ) ) && ( endpoint->local_port == eth3_read_u16( segment + 2 ) ) )
    {
        if ( ETH_NET_IP_PROTO_UDP == protocol )
        {
            uint16_t udp_len = eth3_read_u16( segment + 4 );
            if ( ( udp_len >= ETH_NET_UDP_HEADER_SIZE ) && ( udp_len <= size ) &&
                 ( !eth3_read_u16( segment + 6 ) || eth3_checksum_ok( ip, segment, udp_len ) ) )
            {
                match = segment;
                *len = udp_len;
            }
        }
        else if ( size >= ETH_NET_TCP_HEADER_SIZE )
        {
            uint8_t header_len = ( segment[ 12 ] >> 4 ) * 4u;
            if ( ( header_len >= ETH_NET_TCP_HEADER_SIZE ) && ( header_len <= size ) &&
                 eth3_checksum_ok( ip, segment, size ) )
            {
                match = segment;
                *len = size;
            }
        }
    }
    return match;
}

static err_t eth3_udp_exchange ( eth3_t *ctx, eth3_socket_t *endpoint, uint8_t *request, uint16_t len,
                                 uint8_t *reply, uint16_t reply_len )
{
    err_t error_flag = ETH3_SOCKET_SEND_ERROR;
    uint16_t elapsed_ms;
    uint16_t size = 0;
    uint8_t *udp;

    if ( eth_net_send_udp( &ctx->eth, ctx->eth.mac, endpoint->next_hop_mac, endpoint->peer_ip, ctx->eth.ip,
                           endpoint->local_port, endpoint->peer_port, request, len ) )
    {
        error_flag = ETH3_SOCKET_RECEIVE_ERROR;
        for ( elapsed_ms = 0; elapsed_ms < ETH3_REPLY_POLLS; elapsed_ms++ )
        {
            udp = eth3_peer_segment( ctx, endpoint, &size );
            if ( udp && ( size - ETH_NET_UDP_HEADER_SIZE == reply_len ) )
            {
                memcpy( reply, udp + ETH_NET_UDP_HEADER_SIZE, reply_len );
                error_flag = ETH3_OK;
                break;
            }
            Delay_1ms( );
        }
    }
    return error_flag;
}

static uint16_t eth3_tcp_send ( eth3_t *ctx, eth3_socket_t *endpoint, uint32_t seq, uint32_t ack, uint8_t flags,
                                uint8_t *payload, uint16_t len )
{
    volatile uint16_t local_port = endpoint->local_port;
    volatile uint16_t peer_port = endpoint->peer_port;

    return eth_net_send_tcp( &ctx->eth, ctx->eth.mac, ctx->eth.ip, endpoint->next_hop_mac, endpoint->peer_ip,
                             local_port, peer_port, seq, ack, flags, payload, len );
}

static err_t eth3_tcp_connect ( eth3_t *ctx, eth3_socket_t *endpoint, uint32_t *peer_next, uint16_t len )
{
    uint32_t seq = endpoint->sequence;
    uint32_t next_seq = seq + 1ul;
    uint16_t elapsed_ms;
    uint16_t size = 0;
    uint8_t *tcp;
    err_t error_flag = ETH3_SOCKET_CONNECT_ERROR;

    for ( elapsed_ms = 0; elapsed_ms < ETH3_REPLY_POLLS; elapsed_ms++ )
    {
        if ( !( elapsed_ms % ETH3_TCP_RETRY_POLLS ) &&
             !eth3_tcp_send( ctx, endpoint, seq, 0, ETH_NET_TCP_FLAG_SYN, NULL, 0 ) )
        {
            error_flag = ETH3_SOCKET_SEND_ERROR;
            break;
        }
        tcp = eth3_peer_segment( ctx, endpoint, &size );
        if ( tcp && ( tcp[ 13 ] & ETH_NET_TCP_FLAG_ACK ) && ( next_seq == eth3_read_u32( tcp + 8 ) ) )
        {
            if ( tcp[ 13 ] & ETH_NET_TCP_FLAG_RST )
            {
                break;
            }
            if ( ( tcp[ 13 ] & ETH_NET_TCP_FLAG_SYN ) && !( tcp[ 13 ] & ETH_NET_TCP_FLAG_FIN ) &&
                 ( size == ( tcp[ 12 ] >> 4 ) * 4u ) && ( eth3_read_u16( tcp + 14 ) >= len ) )
            {
                *peer_next = eth3_read_u32( tcp + 4 ) + 1ul;
                error_flag = ETH3_SOCKET_SEND_ERROR;
                if ( eth3_tcp_send( ctx, endpoint, next_seq, *peer_next, ETH_NET_TCP_FLAG_ACK, NULL, 0 ) )
                {
                    error_flag = ETH3_OK;
                }
                break;
            }
        }
        Delay_1ms( );
    }
    return error_flag;
}

static err_t eth3_tcp_exchange ( eth3_t *ctx, eth3_socket_t *endpoint, uint32_t peer_next,
                                 uint8_t *request, uint16_t len, uint8_t *reply, uint16_t reply_len )
{
    uint32_t first_seq = endpoint->sequence + 1ul;
    uint32_t end_seq = first_seq + len;
    uint32_t seq;
    uint32_t acked;
    uint32_t skip;
    uint16_t acknowledged = 0;
    uint16_t filled = 0;
    uint16_t elapsed_ms;
    uint16_t size = 0;
    uint16_t payload_len;
    uint8_t *tcp;
    uint8_t header_len;
    uint8_t flags;
    uint8_t fin_sent = 0;
    uint8_t peer_fin = 0;
    uint8_t peer_reset = 0;
    err_t error_flag = ETH3_SOCKET_RECEIVE_ERROR;

    for ( elapsed_ms = 0; elapsed_ms < ETH3_REPLY_POLLS; elapsed_ms++ )
    {
        if ( !( elapsed_ms % ETH3_TCP_RETRY_POLLS ) && ( acknowledged < len ) )
        {
            if ( !eth3_tcp_send( ctx, endpoint, first_seq + acknowledged, peer_next,
                                ETH_NET_TCP_FLAG_ACK | ETH_NET_TCP_FLAG_PSH,
                                request + acknowledged, len - acknowledged ) )
            {
                error_flag = ETH3_SOCKET_SEND_ERROR;
                break;
            }
        }

        /* Keep the stream open until the full echo or the peer's FIN arrives. */
        if ( ( ( filled == reply_len ) || peer_fin ) && ( acknowledged == len ) &&
             ( !fin_sent || !( elapsed_ms % ETH3_TCP_RETRY_POLLS ) ) )
        {
            if ( !eth3_tcp_send( ctx, endpoint, end_seq, peer_next, ETH_NET_TCP_FLAG_ACK | ETH_NET_TCP_FLAG_FIN,
                                NULL, 0 ) )
            {
                error_flag = ETH3_SOCKET_SEND_ERROR;
                break;
            }
            fin_sent = 1;
        }

        tcp = eth3_peer_segment( ctx, endpoint, &size );
        Delay_1ms( );
        if ( !tcp )
        {
            continue;
        }

        flags = tcp[ 13 ];
        seq = eth3_read_u32( tcp + 4 );
        if ( ( flags & ETH_NET_TCP_FLAG_RST ) && ( seq == peer_next ) )
        {
            peer_reset = 1;
            break;
        }

        acked = eth3_read_u32( tcp + 8 ) - first_seq;
        if ( !( flags & ETH_NET_TCP_FLAG_ACK ) || ( flags & ( ETH_NET_TCP_FLAG_SYN | ETH_NET_TCP_FLAG_RST ) ) ||
             ( acked > len + fin_sent ) )
        {
            continue;
        }
        if ( acked > acknowledged )
        {
            acknowledged = ( uint16_t ) acked;
        }

        header_len = ( tcp[ 12 ] >> 4 ) * 4u;
        payload_len = size - header_len;
        if ( payload_len || ( flags & ETH_NET_TCP_FLAG_FIN ) )
        {
            /* Trim an acknowledged prefix. Repeat the last ACK for a gap. */
            skip = peer_next - seq;
            if ( !peer_fin && ( skip <= payload_len ) )
            {
                payload_len -= ( uint16_t ) skip;
                if ( payload_len > reply_len - filled )
                {
                    error_flag = ETH3_SOCKET_RECEIVE_ERROR;
                    break;
                }
                memcpy( reply + filled, tcp + header_len + ( uint16_t ) skip, payload_len );
                filled += payload_len;
                peer_next += payload_len;
                if ( flags & ETH_NET_TCP_FLAG_FIN )
                {
                    peer_next++;
                    peer_fin = 1;
                }
            }
            if ( !eth3_tcp_send( ctx, endpoint, end_seq + fin_sent, peer_next, ETH_NET_TCP_FLAG_ACK, NULL, 0 ) )
            {
                error_flag = ETH3_SOCKET_SEND_ERROR;
                break;
            }
            if ( filled == reply_len )
            {
                error_flag = ETH3_OK;
            }
        }
        if ( peer_fin && ( acknowledged > len ) )
        {
            break;
        }
    }
    if ( !peer_reset && !( peer_fin && ( acknowledged > len ) ) )
    {
        /* Release the connection if the closing exchange did not finish within the poll budget. */
        eth3_tcp_send( ctx, endpoint, first_seq + acknowledged, peer_next,
                       ETH_NET_TCP_FLAG_RST | ETH_NET_TCP_FLAG_ACK, NULL, 0 );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
