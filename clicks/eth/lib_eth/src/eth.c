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
 * @file eth.c
 * @brief ETH Click Driver.
 */

#include "eth.h"
#include "eth_net.h"

/**
 * @brief ETH transport settings.
 * @details Defines the dummy byte clocked out during SPI reads.
 */
#define ETH_SPI_DUMMY                   0x00u

/**
 * @brief ETH control register addressing.
 * @details Defines the bank and offset fields and the register addresses used by the SPI access functions.
 */
#define ETH_REG_OFFSET_MASK             0x1Fu
#define ETH_BANK_SHIFT                  5u
#define ETH_BANK_MASK                   0x03u
#define ETH_BANK_UNKNOWN                0xFFu
#define ETH_REG_EIE                     0x1Bu
#define ETH_REG_ECON1                   0x1Fu
#define ETH_REG_MACON1                  0x40u
#define ETH_REG_MIRDH                   0x59u
#define ETH_REG_MAADR5                  0x60u
#define ETH_REG_MAADR2                  0x65u
#define ETH_REG_MISTAT                  0x6Au
#define ETH_REG_EREVID                  0x72u

/**
 * @brief ETH Ethernet/IPv4 ARP fields.
 * @details Defines the Ethernet address sizes, ARP field offsets and values used for next-hop resolution.
 */
#define ETH_MAC_ADDR_SIZE               6u
#define ETH_IPV4_ADDR_SIZE              4u
#define ETH_MAC_BROADCAST_BYTE          0xFFu
#define ETH_MAC_GROUP_BIT               0x01u
#define ETH_FRAME_TYPE_OFFSET           ( 2u * ETH_MAC_ADDR_SIZE )
#define ETH_ARP_HW_ETHERNET             0x0001u
#define ETH_ARP_OP_REQUEST              0x0001u
#define ETH_ARP_OP_REPLY                0x0002u
#define ETH_ARP_OPCODE_OFFSET           6u
#define ETH_ARP_SENDER_MAC_OFFSET       8u
#define ETH_ARP_SENDER_IP_OFFSET        14u
#define ETH_ARP_TARGET_MAC_OFFSET       18u
#define ETH_ARP_TARGET_IP_OFFSET        24u
#define ETH_ARP_TYPE_MATCH_LEN          ( ETH_NET_ETH_HEADER_SIZE - ETH_FRAME_TYPE_OFFSET + ETH_ARP_OPCODE_OFFSET )

/**
 * @brief ETH ARP and socket settings.
 * @details Defines the frame length, retry counts, poll budgets and TCP sequence number increment.
 * @note Each wait includes time spent processing frames in addition to the 1 ms polling delays.
 */
#define ETH_ARP_FRAME_SIZE              42u
#define ETH_ARP_RETRIES                 3u
#define ETH_ARP_POLLS                   1000u
#define ETH_REPLY_POLLS                 3000u
#define ETH_TCP_RETRY_POLLS             1000u
#define ETH_TCP_SEQ_STEP                64001ul

/**
 * @brief ETH TCP and UDP request limits.
 * @details Defines the largest request payload the SDK transmit buffer can hold for each protocol.
 */
#define ETH_TCP_PAYLOAD_MAX             ( ETH_NET_TX_BUF_SIZE - ETH_NET_ETH_HEADER_SIZE - \
                                        ETH_NET_IP_HEADER_SIZE - ETH_NET_TCP_HEADER_SIZE )
#define ETH_UDP_PAYLOAD_MAX             ( ETH_NET_TX_BUF_SIZE - ETH_NET_ETH_HEADER_SIZE - \
                                        ETH_NET_IP_HEADER_SIZE - ETH_NET_UDP_HEADER_SIZE )

/**
 * @brief ETH control register bank selection function.
 * @details Selects the bank encoded in a register address and shares the bank cache with the SDK.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in] reg : Encoded control register address.
 * @return @li @c  0 - Bank selected or register common to all banks,
 *         @li @c -1 - SPI error.
 * See #err_t definition for detailed explanation.
 * @note A failed bank change forces a fresh selection on the next access.
 */
static err_t eth_select_bank ( eth_t *ctx, uint8_t reg );

/**
 * @brief ETH 16-bit network word read function.
 * @details Reads two bytes in big-endian order.
 * @param[in] bytes : Pointer to two readable bytes.
 * @return The 16-bit value in host byte order.
 * @note The input may be unaligned.
 */
static uint16_t eth_read_u16 ( uint8_t *bytes );

/**
 * @brief ETH 32-bit network word read function.
 * @details Reads a TCP sequence or acknowledgment number in big-endian order.
 * @param[in] bytes : Pointer to four readable bytes.
 * @return The 32-bit value in host byte order.
 * @note The input may be unaligned.
 */
static uint32_t eth_read_u32 ( uint8_t *bytes );

/**
 * @brief ETH transport checksum validation function.
 * @details Checks the one's complement sum of the IPv4 pseudo-header and the TCP or UDP segment.
 * @param[in] ip : Validated IPv4 header containing the protocol and addresses.
 * @param[in] segment : Transport header and payload, including the received checksum.
 * @param[in] len : Transport header and payload length in bytes.
 * @return @li @c 1 - Checksum valid,
 *         @li @c 0 - Checksum invalid.
 * @note The caller handles the optional zero checksum for IPv4 UDP.
 */
static uint8_t eth_checksum_ok ( uint8_t *ip, uint8_t *segment, uint16_t len );

/**
 * @brief ETH peer segment read function.
 * @details Reads one Ethernet frame and checks the IPv4 addresses, protocol, ports, transport length and checksum.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in,out] endpoint : TCP or UDP peer and its receive frame buffer.
 * See #eth_socket_t object definition for detailed explanation.
 * @param[out] len : Transport header and payload length in bytes, or zero if no matching segment is read.
 * @return Pointer to the transport header in the receive frame buffer, or NULL if no matching segment is read.
 * @note The pointer is valid until the frame buffer is reused.
 */
static uint8_t *eth_peer_segment ( eth_t *ctx, eth_socket_t *endpoint, uint16_t *len );

/**
 * @brief ETH UDP exchange function.
 * @details Sends one datagram and waits for a reply of the expected length from the configured peer.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in,out] endpoint : UDP peer, local port and receive frame buffer.
 * See #eth_socket_t object definition for detailed explanation.
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
static err_t eth_udp_exchange ( eth_t *ctx, eth_socket_t *endpoint, uint8_t *request, uint16_t len,
                                uint8_t *reply, uint16_t reply_len );

/**
 * @brief ETH TCP segment send function.
 * @details Uses the SDK to send a TCP segment with the configured addresses and ports.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in] endpoint : TCP peer, local port and resolved next-hop MAC address.
 * See #eth_socket_t object definition for detailed explanation.
 * @param[in] seq : TCP sequence number in host byte order.
 * @param[in] ack : TCP acknowledgment number in host byte order.
 * @param[in] flags : TCP control flags from ETH_NET_TCP_FLAG_*.
 * @param[in] payload : Segment payload or NULL for a control-only segment.
 * @param[in] len : Segment payload length in bytes.
 * @return Number of Ethernet frame bytes sent, or zero on error.
 * @note The caller manages the TCP connection state and retry budget.
 */
static uint16_t eth_tcp_send ( eth_t *ctx, eth_socket_t *endpoint, uint32_t seq, uint32_t ack, uint8_t flags,
                               uint8_t *payload, uint16_t len );

/**
 * @brief ETH TCP connection establishment function.
 * @details Sends SYN and acknowledges a valid SYN/ACK when the peer advertises enough window space for the request.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in,out] endpoint : TCP peer, initial sequence number and receive frame buffer.
 * See #eth_socket_t object definition for detailed explanation.
 * @param[out] peer_next : Next expected peer sequence number after receiving the SYN/ACK.
 * @param[in] len : Request length in bytes used to check the peer's receive window.
 * @return @li @c  0 - Handshake ACK sent,
 *         @li @c -2 - Peer reset the handshake or no acceptable SYN/ACK arrived within the poll budget,
 *         @li @c -3 - SYN or ACK transmission failed.
 * See #err_t definition for detailed explanation.
 * @note Use peer_next after a successful handshake.
 */
static err_t eth_tcp_connect ( eth_t *ctx, eth_socket_t *endpoint, uint32_t *peer_next, uint16_t len );

/**
 * @brief ETH TCP exchange function.
 * @details Sends one request on an open TCP connection and collects the reply across in-order or overlapping segments.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in,out] endpoint : TCP peer, receive frame buffer and initial sequence number.
 * See #eth_socket_t object definition for detailed explanation.
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
static err_t eth_tcp_exchange ( eth_t *ctx, eth_socket_t *endpoint, uint32_t peer_next,
                                uint8_t *request, uint16_t len, uint8_t *reply, uint16_t reply_len );

void eth_cfg_setup ( eth_cfg_t *cfg )
{
    cfg->sck     = HAL_PIN_NC;
    cfg->miso    = HAL_PIN_NC;
    cfg->mosi    = HAL_PIN_NC;
    cfg->cs      = HAL_PIN_NC;
    cfg->rst     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = ETH_SPI_SPEED;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->full_duplex = 0;
    memset( cfg->mac, 0, sizeof( cfg->mac ) );
    memset( cfg->ip, 0, sizeof( cfg->ip ) );
}

err_t eth_init ( eth_t *ctx, eth_cfg_t *cfg )
{
    err_t error_flag = ETH_OK;
    enc28j60_cfg_t eth_cfg;

    enc28j60_cfg_setup( &eth_cfg );
    eth_cfg.bus.sck = cfg->sck;
    eth_cfg.bus.miso = cfg->miso;
    eth_cfg.bus.mosi = cfg->mosi;
    eth_cfg.bus.cs = cfg->cs;
    eth_cfg.bus.speed = cfg->spi_speed;
    eth_cfg.bus.mode = cfg->spi_mode;
    eth_cfg.eth.rst = cfg->rst;
    eth_cfg.eth.full_duplex = cfg->full_duplex;
    memcpy( eth_cfg.eth.mac, cfg->mac, sizeof( cfg->mac ) );
    memcpy( eth_cfg.eth.ip, cfg->ip, sizeof( cfg->ip ) );

    ctx->eth.driver_ctx = &ctx->controller;
    ctx->eth.drv = NULL;
    ctx->controller.current_bank = ETH_BANK_UNKNOWN;

    /* The SDK deselects the device while configuring the SPI bus. */
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    if ( ETH_TRANSPORT_ERROR == enc28j60_configure( &ctx->eth, &ctx->bus, &eth_cfg ) )
    {
        error_flag = ETH_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->bus.spi, ETH_SPI_DUMMY ) )
    {
        error_flag = ETH_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->bus.spi, cfg->spi_mode ) )
    {
        error_flag = ETH_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->bus.spi, cfg->spi_speed ) )
    {
        error_flag = ETH_ERROR;
    }
    else if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->int_pin, cfg->int_pin ) )
    {
        error_flag = ETH_ERROR;
    }
    else
    {
        /* Release the ENC28J60 from reset. */
        eth_set_rst_pin( ctx, 1 );
    }

    return error_flag;
}

err_t eth_default_cfg ( eth_t *ctx )
{
    err_t error_flag = eth_transport_init( &ctx->eth, &enc28j60_driver );

    if ( ETH_TRANSPORT_ERROR == error_flag )
    {
        ctx->eth.drv = NULL;
        ctx->controller.current_bank = ETH_BANK_UNKNOWN;
    }
    return error_flag;
}

err_t eth_write_reg ( eth_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t cmd = ENC28J60_WCR_CMD | ( reg & ETH_REG_OFFSET_MASK );
    err_t error_flag = eth_select_bank( ctx, reg );

    if ( ETH_OK == error_flag )
    {
        error_flag = eth_transport_bus_write( &ctx->eth, &cmd, 1, &data_in, 1 );
        if ( ETH_REG_ECON1 == ( reg & ETH_REG_OFFSET_MASK ) )
        {
            ctx->controller.current_bank = ETH_BANK_UNKNOWN;
            if ( ETH_OK == error_flag )
            {
                ctx->controller.current_bank = data_in & ETH_BANK_MASK;
            }
        }
    }
    return error_flag;
}

err_t eth_write_regs ( eth_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = ETH_OK;
    uint8_t index;

    if ( len > ETH_REG_OFFSET_MASK + 1u - ( reg & ETH_REG_OFFSET_MASK ) )
    {
        error_flag = ETH_ERROR;
    }
    for ( index = 0; ( index < len ) && ( ETH_OK == error_flag ); index++ )
    {
        error_flag = eth_write_reg( ctx, reg + index, data_in[ index ] );
    }
    return error_flag;
}

err_t eth_read_reg ( eth_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t cmd = ENC28J60_RCR_CMD | ( reg & ETH_REG_OFFSET_MASK );
    uint8_t reply[ 2 ];
    uint8_t len = 1;
    err_t error_flag = eth_select_bank( ctx, reg );

    if ( ETH_OK == error_flag )
    {
        /* MAC and MII reads clock out a dummy byte before the register value. */
        if ( ( ( reg >= ETH_REG_MACON1 ) && ( reg <= ETH_REG_MIRDH ) ) ||
             ( ( reg >= ETH_REG_MAADR5 ) && ( reg <= ETH_REG_MAADR2 ) ) || ( ETH_REG_MISTAT == reg ) )
        {
            len = 2;
        }
        error_flag = eth_transport_bus_read( &ctx->eth, &cmd, 1, reply, len );
        if ( ETH_OK == error_flag )
        {
            *data_out = reply[ len - 1u ];
        }
    }
    return error_flag;
}

err_t eth_read_regs ( eth_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = ETH_OK;
    uint8_t index;

    if ( len > ETH_REG_OFFSET_MASK + 1u - ( reg & ETH_REG_OFFSET_MASK ) )
    {
        error_flag = ETH_ERROR;
    }
    for ( index = 0; ( index < len ) && ( ETH_OK == error_flag ); index++ )
    {
        error_flag = eth_read_reg( ctx, reg + index, &data_out[ index ] );
    }
    return error_flag;
}

err_t eth_get_version ( eth_t *ctx, uint8_t *version )
{
    return eth_read_reg( ctx, ETH_REG_EREVID, version );
}

err_t eth_set_mac ( eth_t *ctx, uint8_t *mac )
{
    return eth_transport_set_mac( &ctx->eth, mac );
}

err_t eth_set_ip ( eth_t *ctx, uint8_t *ip )
{
    return eth_transport_set_ip( &ctx->eth, ip );
}

uint16_t eth_service_frame ( eth_t *ctx, uint8_t *frame, uint16_t capacity )
{
    uint16_t len = eth_read_packet( ctx, frame, capacity );

    if ( len >= ETH_NET_ETH_HEADER_SIZE )
    {
        eth_net_handle_arp( &ctx->eth, ctx->eth.mac, ctx->eth.ip, frame, len );
        eth_net_handle_icmp( &ctx->eth, ctx->eth.mac, ctx->eth.ip, frame, len );
    }
    return len;
}

err_t eth_resolve_mac ( eth_t *ctx, eth_socket_t *endpoint, uint8_t *ip )
{
    uint8_t request[ ETH_ARP_FRAME_SIZE ] = {
        ETH_MAC_BROADCAST_BYTE, ETH_MAC_BROADCAST_BYTE, ETH_MAC_BROADCAST_BYTE,
        ETH_MAC_BROADCAST_BYTE, ETH_MAC_BROADCAST_BYTE, ETH_MAC_BROADCAST_BYTE,
        0, 0, 0, 0, 0, 0,
        ( uint8_t ) ( ETH_NET_ETHERTYPE_ARP >> 8 ), ( uint8_t ) ETH_NET_ETHERTYPE_ARP,
        ( uint8_t ) ( ETH_ARP_HW_ETHERNET >> 8 ), ( uint8_t ) ETH_ARP_HW_ETHERNET,
        ( uint8_t ) ( ETH_NET_ETHERTYPE_IPV4 >> 8 ), ( uint8_t ) ETH_NET_ETHERTYPE_IPV4,
        ETH_MAC_ADDR_SIZE, ETH_IPV4_ADDR_SIZE,
        ( uint8_t ) ( ETH_ARP_OP_REQUEST >> 8 ), ( uint8_t ) ETH_ARP_OP_REQUEST
    };
    uint8_t *arp_request = &request[ ETH_NET_ETH_HEADER_SIZE ];
    uint8_t *arp;
    err_t error_flag = ETH_ERROR;
    uint8_t retry;
    uint16_t elapsed_ms;

    memcpy( &request[ ETH_MAC_ADDR_SIZE ], ctx->eth.mac, ETH_MAC_ADDR_SIZE );
    memcpy( &arp_request[ ETH_ARP_SENDER_MAC_OFFSET ], ctx->eth.mac, ETH_MAC_ADDR_SIZE );
    memcpy( &arp_request[ ETH_ARP_SENDER_IP_OFFSET ], ctx->eth.ip, ETH_IPV4_ADDR_SIZE );
    memcpy( &arp_request[ ETH_ARP_TARGET_IP_OFFSET ], ip, ETH_IPV4_ADDR_SIZE );

    for ( retry = 0; ( retry < ETH_ARP_RETRIES ) && ( ETH_ERROR == error_flag ) &&
          endpoint->frame && ( endpoint->frame_size >= ETH_ARP_FRAME_SIZE ); retry++ )
    {
        arp = &endpoint->frame[ ETH_NET_ETH_HEADER_SIZE ];
        if ( !eth_send_packet( ctx, request, sizeof( request ) ) )
        {
            break;
        }
        for ( elapsed_ms = 0; elapsed_ms < ETH_ARP_POLLS; elapsed_ms++ )
        {
            /* Match EtherType, hardware/protocol types and sizes, then check the ARP reply endpoints. */
            if ( ( eth_service_frame( ctx, endpoint->frame, endpoint->frame_size ) >= ETH_ARP_FRAME_SIZE ) &&
                 !memcmp( &endpoint->frame[ ETH_FRAME_TYPE_OFFSET ], &request[ ETH_FRAME_TYPE_OFFSET ],
                          ETH_ARP_TYPE_MATCH_LEN ) &&
                 ( ETH_ARP_OP_REPLY == eth_read_u16( &arp[ ETH_ARP_OPCODE_OFFSET ] ) ) &&
                 !memcmp( endpoint->frame, ctx->eth.mac, ETH_MAC_ADDR_SIZE ) &&
                 !memcmp( &arp[ ETH_ARP_TARGET_MAC_OFFSET ], ctx->eth.mac, ETH_MAC_ADDR_SIZE ) &&
                 !memcmp( &arp[ ETH_ARP_TARGET_IP_OFFSET ], ctx->eth.ip, ETH_IPV4_ADDR_SIZE ) &&
                 !memcmp( &arp[ ETH_ARP_SENDER_IP_OFFSET ], ip, ETH_IPV4_ADDR_SIZE ) &&
                 !( arp[ ETH_ARP_SENDER_MAC_OFFSET ] & ETH_MAC_GROUP_BIT ) &&
                 !memcmp( &arp[ ETH_ARP_SENDER_MAC_OFFSET ], &endpoint->frame[ ETH_MAC_ADDR_SIZE ], ETH_MAC_ADDR_SIZE ) )
            {
                memcpy( endpoint->next_hop_mac, &arp[ ETH_ARP_SENDER_MAC_OFFSET ], sizeof( endpoint->next_hop_mac ) );
                error_flag = ETH_OK;
                break;
            }
            Delay_1ms( );
        }
    }
    return error_flag;
}

err_t eth_socket_exchange ( eth_t *ctx, eth_socket_t *endpoint, uint8_t *request, uint16_t len,
                            uint8_t *reply, uint16_t reply_len )
{
    err_t error_flag = ETH_ERROR;

    if ( request && reply && len && reply_len && endpoint->frame &&
         ( endpoint->frame_size >= ETH_NET_ETH_HEADER_SIZE + ETH_NET_IP_HEADER_SIZE + ETH_NET_UDP_HEADER_SIZE ) )
    {
        if ( ( ETH_NET_IP_PROTO_UDP == endpoint->protocol ) && ( len <= ETH_UDP_PAYLOAD_MAX ) )
        {
            error_flag = eth_udp_exchange( ctx, endpoint, request, len, reply, reply_len );
        }
        else if ( ( ETH_NET_IP_PROTO_TCP == endpoint->protocol ) && ( len <= ETH_TCP_PAYLOAD_MAX ) )
        {
            uint32_t peer_next = 0;

            /* Finish the handshake before allocating the exchange's local state. */
            error_flag = eth_tcp_connect( ctx, endpoint, &peer_next, len );
            if ( ETH_OK == error_flag )
            {
                error_flag = eth_tcp_exchange( ctx, endpoint, peer_next, request, len, reply, reply_len );
            }
            endpoint->sequence += ETH_TCP_SEQ_STEP;
        }
    }
    return error_flag;
}

uint16_t eth_send_packet ( eth_t *ctx, uint8_t *data_in, uint16_t len )
{
    uint16_t sent_len = 0;

    if ( ( len >= ETH_NET_ETH_HEADER_SIZE ) && ( len <= ETH_FRAME_SIZE ) )
    {
        sent_len = eth_transport_send( &ctx->eth, data_in, len );
        if ( ctx->eth.bus_error )
        {
            sent_len = 0;
        }
    }
    return sent_len;
}

uint16_t eth_read_packet ( eth_t *ctx, uint8_t *data_out, uint16_t len )
{
    return eth_transport_receive( &ctx->eth, data_out, len );
}

uint8_t eth_packet_available ( eth_t *ctx )
{
    return eth_transport_available( &ctx->eth );
}

uint8_t eth_get_link_status ( eth_t *ctx )
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

void eth_set_rst_pin ( eth_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->eth.reset, state );
    if ( !state )
    {
        ctx->eth.drv = NULL;
        ctx->controller.current_bank = ETH_BANK_UNKNOWN;
    }
}

uint8_t eth_get_int_pin ( eth_t *ctx )
{
    return !!digital_in_read( &ctx->int_pin );
}

static err_t eth_select_bank ( eth_t *ctx, uint8_t reg )
{
    uint8_t bank = reg >> ETH_BANK_SHIFT;
    uint8_t cmd = ENC28J60_BFC_CMD | ETH_REG_ECON1;
    uint8_t mask = ETH_BANK_MASK;
    err_t error_flag = ETH_OK;

    if ( bank > ETH_BANK_MASK )
    {
        error_flag = ETH_ERROR;
    }
    else if ( ( ( reg & ETH_REG_OFFSET_MASK ) < ETH_REG_EIE ) && ( bank != ctx->controller.current_bank ) )
    {
        ctx->controller.current_bank = ETH_BANK_UNKNOWN;
        error_flag = eth_transport_bus_write( &ctx->eth, &cmd, 1, &mask, 1 );
        if ( ( ETH_OK == error_flag ) && bank )
        {
            cmd = ENC28J60_BFS_CMD | ETH_REG_ECON1;
            error_flag = eth_transport_bus_write( &ctx->eth, &cmd, 1, &bank, 1 );
        }
        if ( ETH_OK == error_flag )
        {
            ctx->controller.current_bank = bank;
        }
    }
    return error_flag;
}

static uint16_t eth_read_u16 ( uint8_t *bytes )
{
    return ( ( uint16_t ) bytes[ 0 ] << 8 ) | bytes[ 1 ];
}

static uint32_t eth_read_u32 ( uint8_t *bytes )
{
    return ( ( uint32_t ) eth_read_u16( bytes ) << 16 ) | eth_read_u16( bytes + 2 );
}

static uint8_t eth_checksum_ok ( uint8_t *ip, uint8_t *segment, uint16_t len )
{
    uint32_t sum = ( uint32_t ) ip[ 9 ] + len;
    uint16_t index;

    for ( index = 12; index < 20; index += 2 )
    {
        sum += eth_read_u16( &ip[ index ] );
    }
    while ( len >= 2u )
    {
        sum += eth_read_u16( segment );
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

static uint8_t *eth_peer_segment ( eth_t *ctx, eth_socket_t *endpoint, uint16_t *len )
{
    uint16_t frame_len = eth_service_frame( ctx, endpoint->frame, endpoint->frame_size );
    uint16_t size = 0;
    uint8_t *segment = eth_net_ipv4_payload( endpoint->frame, frame_len, &size );
    uint8_t *ip = &endpoint->frame[ ETH_NET_ETH_HEADER_SIZE ];
    uint8_t *match = NULL;
    volatile uint8_t protocol = endpoint->protocol;

    *len = 0;
    if ( segment && ( size >= ETH_NET_UDP_HEADER_SIZE ) && ( ip[ 9 ] == protocol ) &&
         !memcmp( endpoint->frame, ctx->eth.mac, 6 ) && !memcmp( &ip[ 12 ], endpoint->peer_ip, 4 ) &&
         !memcmp( &ip[ 16 ], ctx->eth.ip, 4 ) &&
         ( endpoint->peer_port == eth_read_u16( segment ) ) && ( endpoint->local_port == eth_read_u16( segment + 2 ) ) )
    {
        if ( ETH_NET_IP_PROTO_UDP == protocol )
        {
            uint16_t udp_len = eth_read_u16( segment + 4 );
            if ( ( udp_len >= ETH_NET_UDP_HEADER_SIZE ) && ( udp_len <= size ) &&
                 ( !eth_read_u16( segment + 6 ) || eth_checksum_ok( ip, segment, udp_len ) ) )
            {
                match = segment;
                *len = udp_len;
            }
        }
        else if ( size >= ETH_NET_TCP_HEADER_SIZE )
        {
            uint8_t header_len = ( segment[ 12 ] >> 4 ) * 4u;
            if ( ( header_len >= ETH_NET_TCP_HEADER_SIZE ) && ( header_len <= size ) &&
                 eth_checksum_ok( ip, segment, size ) )
            {
                match = segment;
                *len = size;
            }
        }
    }
    return match;
}

static err_t eth_udp_exchange ( eth_t *ctx, eth_socket_t *endpoint, uint8_t *request, uint16_t len,
                                uint8_t *reply, uint16_t reply_len )
{
    err_t error_flag = ETH_SOCKET_SEND_ERROR;
    uint16_t elapsed_ms;
    uint16_t size = 0;
    uint8_t *udp;

    if ( eth_net_send_udp( &ctx->eth, ctx->eth.mac, endpoint->next_hop_mac, endpoint->peer_ip, ctx->eth.ip,
                           endpoint->local_port, endpoint->peer_port, request, len ) )
    {
        error_flag = ETH_SOCKET_RECEIVE_ERROR;
        for ( elapsed_ms = 0; elapsed_ms < ETH_REPLY_POLLS; elapsed_ms++ )
        {
            udp = eth_peer_segment( ctx, endpoint, &size );
            if ( udp && ( size - ETH_NET_UDP_HEADER_SIZE == reply_len ) )
            {
                memcpy( reply, udp + ETH_NET_UDP_HEADER_SIZE, reply_len );
                error_flag = ETH_OK;
                break;
            }
            Delay_1ms( );
        }
    }
    return error_flag;
}

static uint16_t eth_tcp_send ( eth_t *ctx, eth_socket_t *endpoint, uint32_t seq, uint32_t ack, uint8_t flags,
                               uint8_t *payload, uint16_t len )
{
    volatile uint16_t local_port = endpoint->local_port;
    volatile uint16_t peer_port = endpoint->peer_port;

    return eth_net_send_tcp( &ctx->eth, ctx->eth.mac, ctx->eth.ip, endpoint->next_hop_mac, endpoint->peer_ip,
                             local_port, peer_port, seq, ack, flags, payload, len );
}

static err_t eth_tcp_connect ( eth_t *ctx, eth_socket_t *endpoint, uint32_t *peer_next, uint16_t len )
{
    uint32_t seq = endpoint->sequence;
    uint32_t next_seq = seq + 1ul;
    uint16_t elapsed_ms;
    uint16_t size = 0;
    uint8_t *tcp;
    err_t error_flag = ETH_SOCKET_CONNECT_ERROR;

    for ( elapsed_ms = 0; elapsed_ms < ETH_REPLY_POLLS; elapsed_ms++ )
    {
        if ( !( elapsed_ms % ETH_TCP_RETRY_POLLS ) &&
             !eth_tcp_send( ctx, endpoint, seq, 0, ETH_NET_TCP_FLAG_SYN, NULL, 0 ) )
        {
            error_flag = ETH_SOCKET_SEND_ERROR;
            break;
        }
        tcp = eth_peer_segment( ctx, endpoint, &size );
        if ( tcp && ( tcp[ 13 ] & ETH_NET_TCP_FLAG_ACK ) && ( next_seq == eth_read_u32( tcp + 8 ) ) )
        {
            if ( tcp[ 13 ] & ETH_NET_TCP_FLAG_RST )
            {
                break;
            }
            if ( ( tcp[ 13 ] & ETH_NET_TCP_FLAG_SYN ) && !( tcp[ 13 ] & ETH_NET_TCP_FLAG_FIN ) &&
                 ( size == ( tcp[ 12 ] >> 4 ) * 4u ) && ( eth_read_u16( tcp + 14 ) >= len ) )
            {
                *peer_next = eth_read_u32( tcp + 4 ) + 1ul;
                error_flag = ETH_SOCKET_SEND_ERROR;
                if ( eth_tcp_send( ctx, endpoint, next_seq, *peer_next, ETH_NET_TCP_FLAG_ACK, NULL, 0 ) )
                {
                    error_flag = ETH_OK;
                }
                break;
            }
        }
        Delay_1ms( );
    }
    return error_flag;
}

static err_t eth_tcp_exchange ( eth_t *ctx, eth_socket_t *endpoint, uint32_t peer_next,
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
    err_t error_flag = ETH_SOCKET_RECEIVE_ERROR;

    for ( elapsed_ms = 0; elapsed_ms < ETH_REPLY_POLLS; elapsed_ms++ )
    {
        if ( !( elapsed_ms % ETH_TCP_RETRY_POLLS ) && ( acknowledged < len ) )
        {
            if ( !eth_tcp_send( ctx, endpoint, first_seq + acknowledged, peer_next,
                                ETH_NET_TCP_FLAG_ACK | ETH_NET_TCP_FLAG_PSH,
                                request + acknowledged, len - acknowledged ) )
            {
                error_flag = ETH_SOCKET_SEND_ERROR;
                break;
            }
        }

        /* Keep the stream open until the full echo or the peer's FIN arrives. */
        if ( ( ( filled == reply_len ) || peer_fin ) && ( acknowledged == len ) &&
             ( !fin_sent || !( elapsed_ms % ETH_TCP_RETRY_POLLS ) ) )
        {
            if ( !eth_tcp_send( ctx, endpoint, end_seq, peer_next, ETH_NET_TCP_FLAG_ACK | ETH_NET_TCP_FLAG_FIN,
                                NULL, 0 ) )
            {
                error_flag = ETH_SOCKET_SEND_ERROR;
                break;
            }
            fin_sent = 1;
        }

        tcp = eth_peer_segment( ctx, endpoint, &size );
        Delay_1ms( );
        if ( !tcp )
        {
            continue;
        }

        flags = tcp[ 13 ];
        seq = eth_read_u32( tcp + 4 );
        if ( ( flags & ETH_NET_TCP_FLAG_RST ) && ( seq == peer_next ) )
        {
            peer_reset = 1;
            break;
        }

        acked = eth_read_u32( tcp + 8 ) - first_seq;
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
                    error_flag = ETH_SOCKET_RECEIVE_ERROR;
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
            if ( !eth_tcp_send( ctx, endpoint, end_seq + fin_sent, peer_next, ETH_NET_TCP_FLAG_ACK, NULL, 0 ) )
            {
                error_flag = ETH_SOCKET_SEND_ERROR;
                break;
            }
            if ( filled == reply_len )
            {
                error_flag = ETH_OK;
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
        eth_tcp_send( ctx, endpoint, first_seq + acknowledged, peer_next,
                      ETH_NET_TCP_FLAG_RST | ETH_NET_TCP_FLAG_ACK, NULL, 0 );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
