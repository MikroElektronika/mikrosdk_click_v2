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
 * @file twowireeth.c
 * @brief Two-Wire ETH Click Driver.
 */

#include "twowireeth.h"
#include "eth_net.h"

/**
 * @brief Two-Wire ETH transport settings.
 * @details Defines the dummy byte clocked out during SPI reads.
 */
#define TWOWIREETH_SPI_DUMMY                  0x00u

/**
 * @brief LAN8651 unprotected TC6 control transactions.
 * @details Each SPI transaction carries a header and up to four register words. The extra
 * word provides clocks for the last response because SDO lags SDI by one word.
 */
#define TWOWIREETH_REG_SIZE                   4u
#define TWOWIREETH_CTRL_BURST                 ( 4u * TWOWIREETH_REG_SIZE )
#define TWOWIREETH_CTRL_OVERHEAD              ( 2u * TWOWIREETH_REG_SIZE )
#define TWOWIREETH_CTRL_READ                  0ul
#define TWOWIREETH_MMS_MISC                   0x0Au
#define TWOWIREETH_DEVID                      0x0094u
#define TWOWIREETH_DEVID_MODEL_MASK           0x000FFFF0ul
#define TWOWIREETH_DEVID_MODEL                0x00086510ul
#define TWOWIREETH_DEVID_REV_MASK             0x0Ful

/**
 * @brief Two-Wire ETH factory MAC address settings.
 * @details The AT24MAC402 SOT23 uses 7-bit I2C address 0x58 for extended memory. Its six-byte EUI-48 starts at 0x9A.
 */
#define TWOWIREETH_EUI_I2C_ADDR               0x58u
#define TWOWIREETH_EUI_OFFSET                 0x9Au

/**
 * @brief Two-Wire ETH Ethernet/IPv4 ARP fields.
 * @details Defines the Ethernet address sizes, ARP field offsets and values used for next-hop resolution.
 */
#define TWOWIREETH_MAC_ADDR_SIZE              6u
#define TWOWIREETH_IPV4_ADDR_SIZE             4u
#define TWOWIREETH_MAC_BROADCAST_BYTE         0xFFu
#define TWOWIREETH_MAC_GROUP_BIT              0x01u
#define TWOWIREETH_FRAME_TYPE_OFFSET          ( 2u * TWOWIREETH_MAC_ADDR_SIZE )
#define TWOWIREETH_ARP_HW_ETHERNET            0x0001u
#define TWOWIREETH_ARP_OP_REQUEST             0x0001u
#define TWOWIREETH_ARP_OP_REPLY               0x0002u
#define TWOWIREETH_ARP_OPCODE_OFFSET          6u
#define TWOWIREETH_ARP_SENDER_MAC_OFFSET      8u
#define TWOWIREETH_ARP_SENDER_IP_OFFSET       14u
#define TWOWIREETH_ARP_TARGET_MAC_OFFSET      18u
#define TWOWIREETH_ARP_TARGET_IP_OFFSET       24u
#define TWOWIREETH_ARP_TYPE_MATCH_LEN         ( ETH_NET_ETH_HEADER_SIZE - TWOWIREETH_FRAME_TYPE_OFFSET + \
                                                 TWOWIREETH_ARP_OPCODE_OFFSET )

/**
 * @brief Two-Wire ETH ARP and socket settings.
 * @details Defines the frame length, retry counts, poll budgets and TCP sequence number increment.
 * @note Each wait includes time spent processing frames in addition to the 1 ms polling delays.
 */
#define TWOWIREETH_ARP_FRAME_SIZE             42u
#define TWOWIREETH_ARP_RETRIES                3u
#define TWOWIREETH_ARP_POLLS                  1000u
#define TWOWIREETH_REPLY_POLLS                3000u
#define TWOWIREETH_TCP_RETRY_POLLS            1000u
#define TWOWIREETH_TCP_SEQ_STEP               64001ul

/**
 * @brief Two-Wire ETH TCP and UDP request limits.
 * @details Defines the largest request payload the SDK transmit buffer can hold for each protocol.
 */
#define TWOWIREETH_TCP_PAYLOAD_MAX            ( ETH_NET_TX_BUF_SIZE - ETH_NET_ETH_HEADER_SIZE - \
                                                 ETH_NET_IP_HEADER_SIZE - ETH_NET_TCP_HEADER_SIZE )
#define TWOWIREETH_UDP_PAYLOAD_MAX            ( ETH_NET_TX_BUF_SIZE - ETH_NET_ETH_HEADER_SIZE - \
                                                 ETH_NET_IP_HEADER_SIZE - ETH_NET_UDP_HEADER_SIZE )

/**
 * @brief Two-Wire ETH system register transfer function.
 * @details Transfers consecutive register words using unprotected TC6 control bursts.
 * @param[in] ctx : Click context object.
 * See #twowireeth_t object definition for detailed explanation.
 * @param[in] command : TWOWIREETH_CTRL_READ or LAN8651_CTRL_HDR_WNR.
 * @param[in] mms : Memory map selector.
 * @param[in] reg : Index of the first register within that map.
 * @param[in,out] buf : Register bytes, most significant byte first in each word.
 * @param[in] len : Byte count, a nonzero multiple of four.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid register span or SPI error.
 * See #err_t definition for detailed explanation.
 * @note Use documented registers and access permissions.
 */
static err_t twowireeth_transfer_regs ( twowireeth_t *ctx, uint32_t command, uint8_t mms, uint16_t reg,
                                        uint8_t *buf, uint16_t len );

/**
 * @brief Two-Wire ETH 16-bit network word read function.
 * @details Reads two bytes in big-endian order.
 * @param[in] bytes : Pointer to two readable bytes.
 * @return The 16-bit value in host byte order.
 * @note The input may be unaligned.
 */
static uint16_t twowireeth_read_u16 ( uint8_t *bytes );

/**
 * @brief Two-Wire ETH 32-bit network word read function.
 * @details Decodes a big-endian register word or TCP sequence or acknowledgment number.
 * @param[in] bytes : Pointer to four readable bytes.
 * @return The 32-bit value in host byte order.
 * @note The input may be unaligned.
 */
static uint32_t twowireeth_read_u32 ( uint8_t *bytes );

/**
 * @brief Two-Wire ETH transport checksum validation function.
 * @details Checks the one's complement sum of the IPv4 pseudo-header and the TCP or UDP segment.
 * @param[in] ip : Validated IPv4 header containing the protocol and addresses.
 * @param[in] segment : Transport header and payload, including the received checksum.
 * @param[in] len : Transport header and payload length in bytes.
 * @return @li @c 1 - Checksum valid,
 *         @li @c 0 - Checksum invalid.
 * @note The caller handles the optional zero checksum for IPv4 UDP.
 */
static uint8_t twowireeth_checksum_ok ( uint8_t *ip, uint8_t *segment, uint16_t len );

/**
 * @brief Two-Wire ETH peer segment read function.
 * @details Reads one Ethernet frame and checks the IPv4 addresses, protocol, ports, transport length and checksum.
 * @param[in] ctx : Click context object.
 * See #twowireeth_t object definition for detailed explanation.
 * @param[in,out] endpoint : TCP or UDP peer and its receive frame buffer.
 * See #twowireeth_socket_t object definition for detailed explanation.
 * @param[out] len : Transport header and payload length in bytes, or zero if no matching segment is read.
 * @return Pointer to the transport header in the receive frame buffer, or NULL if no matching segment is read.
 * @note The pointer is valid until the frame buffer is reused.
 */
static uint8_t *twowireeth_peer_segment ( twowireeth_t *ctx, twowireeth_socket_t *endpoint, uint16_t *len );

/**
 * @brief Two-Wire ETH UDP exchange function.
 * @details Sends one datagram and waits for a reply of the expected length from the configured peer.
 * @param[in] ctx : Click context object.
 * See #twowireeth_t object definition for detailed explanation.
 * @param[in,out] endpoint : UDP peer, local port and receive frame buffer.
 * See #twowireeth_socket_t object definition for detailed explanation.
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
static err_t twowireeth_udp_exchange ( twowireeth_t *ctx, twowireeth_socket_t *endpoint, uint8_t *request, uint16_t len,
                                       uint8_t *reply, uint16_t reply_len );

/**
 * @brief Two-Wire ETH TCP segment send function.
 * @details Uses the SDK to send a TCP segment with the configured addresses and ports.
 * @param[in] ctx : Click context object.
 * See #twowireeth_t object definition for detailed explanation.
 * @param[in] endpoint : TCP peer, local port and resolved next-hop MAC address.
 * See #twowireeth_socket_t object definition for detailed explanation.
 * @param[in] seq : TCP sequence number in host byte order.
 * @param[in] ack : TCP acknowledgment number in host byte order.
 * @param[in] flags : TCP control flags from ETH_NET_TCP_FLAG_*.
 * @param[in] payload : Segment payload or NULL for a control-only segment.
 * @param[in] len : Segment payload length in bytes.
 * @return Number of Ethernet frame bytes sent, or zero on error.
 * @note The caller manages the TCP connection state and retry budget.
 */
static uint16_t twowireeth_tcp_send ( twowireeth_t *ctx, twowireeth_socket_t *endpoint, uint32_t seq, uint32_t ack,
                                      uint8_t flags, uint8_t *payload, uint16_t len );

/**
 * @brief Two-Wire ETH TCP connection establishment function.
 * @details Sends SYN and acknowledges a valid SYN/ACK when the peer advertises enough window space for the request.
 * @param[in] ctx : Click context object.
 * See #twowireeth_t object definition for detailed explanation.
 * @param[in,out] endpoint : TCP peer, initial sequence number and receive frame buffer.
 * See #twowireeth_socket_t object definition for detailed explanation.
 * @param[out] peer_next : Next expected peer sequence number after receiving the SYN/ACK.
 * @param[in] len : Request length in bytes used to check the peer's receive window.
 * @return @li @c  0 - Handshake ACK sent,
 *         @li @c -2 - Peer reset the handshake or no acceptable SYN/ACK arrived within the poll budget,
 *         @li @c -3 - SYN or ACK transmission failed.
 * See #err_t definition for detailed explanation.
 * @note Use peer_next after a successful handshake.
 */
static err_t twowireeth_tcp_connect ( twowireeth_t *ctx, twowireeth_socket_t *endpoint, uint32_t *peer_next, uint16_t len );

/**
 * @brief Two-Wire ETH TCP exchange function.
 * @details Sends one request on an open TCP connection and collects the reply across in-order or overlapping segments.
 * @param[in] ctx : Click context object.
 * See #twowireeth_t object definition for detailed explanation.
 * @param[in,out] endpoint : TCP peer, receive frame buffer and initial sequence number.
 * See #twowireeth_socket_t object definition for detailed explanation.
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
static err_t twowireeth_tcp_exchange ( twowireeth_t *ctx, twowireeth_socket_t *endpoint, uint32_t peer_next,
                                       uint8_t *request, uint16_t len, uint8_t *reply, uint16_t reply_len );

void twowireeth_cfg_setup ( twowireeth_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->irq  = HAL_PIN_NC;

    cfg->spi_speed   = TWOWIREETH_SPI_SPEED;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->plca_enable = 0;
    cfg->plca_node_id = 0;
    cfg->plca_node_count = TWOWIREETH_PLCA_NODES;
    memset( cfg->mac, 0, sizeof( cfg->mac ) );
    memset( cfg->ip, 0, sizeof( cfg->ip ) );
}

err_t twowireeth_init ( twowireeth_t *ctx, twowireeth_cfg_t *cfg )
{
    err_t error_flag = TWOWIREETH_OK;
    lan8651_cfg_t twowireeth_cfg;
    i2c_master_config_t i2c_cfg;
    err_t i2c_status;
    uint8_t zero_mac[ TWOWIREETH_MAC_ADDR_SIZE ] = { 0 };

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    lan8651_cfg_setup( &twowireeth_cfg );
    twowireeth_cfg.bus.sck = cfg->sck;
    twowireeth_cfg.bus.miso = cfg->miso;
    twowireeth_cfg.bus.mosi = cfg->mosi;
    twowireeth_cfg.bus.cs = cfg->cs;
    twowireeth_cfg.bus.speed = cfg->spi_speed;
    twowireeth_cfg.bus.mode = cfg->spi_mode;
    twowireeth_cfg.eth.rst = cfg->rst;
    twowireeth_cfg.eth.full_duplex = 0;
    twowireeth_cfg.plca_enable = cfg->plca_enable;
    twowireeth_cfg.plca_node_id = cfg->plca_node_id;
    twowireeth_cfg.plca_node_count = cfg->plca_node_count;
    memcpy( twowireeth_cfg.eth.mac, cfg->mac, sizeof( cfg->mac ) );
    memcpy( twowireeth_cfg.eth.ip, cfg->ip, sizeof( cfg->ip ) );

    // Give the SDK a LAN8651 state object for this Click instance.
    ctx->eth.driver_ctx = &ctx->controller;
    ctx->eth.drv = NULL;
    ctx->eth.bus = NULL;
    ctx->eth.bus_ops = NULL;
    ctx->controller.phy_id = 0;

    /* The SDK deselects the device while configuring the SPI bus. */
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    i2c_status = i2c_master_open( &ctx->i2c, &i2c_cfg );
    if ( I2C_MASTER_ERROR == i2c_status )
    {
        error_flag = TWOWIREETH_ERROR;
    }
    else if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, I2C_MASTER_SPEED_STANDARD ) )
    {
        error_flag = TWOWIREETH_ERROR;
    }
    else if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, TWOWIREETH_EUI_I2C_ADDR ) )
    {
        error_flag = TWOWIREETH_ERROR;
    }
    // Use the factory MAC when cfg->mac is all zero, before configuring the SDK transport.
    else if ( !memcmp( cfg->mac, zero_mac, sizeof( zero_mac ) ) &&
              ( I2C_MASTER_ERROR == twowireeth_read_factory_mac( ctx, twowireeth_cfg.eth.mac ) ) )
    {
        error_flag = TWOWIREETH_ERROR;
    }
    else if ( ETH_TRANSPORT_ERROR == lan8651_configure( &ctx->eth, &ctx->bus, &twowireeth_cfg ) )
    {
        error_flag = TWOWIREETH_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->bus.spi, TWOWIREETH_SPI_DUMMY ) )
    {
        error_flag = TWOWIREETH_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->bus.spi, cfg->spi_mode ) )
    {
        error_flag = TWOWIREETH_ERROR;
    }
    else if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->bus.spi, cfg->spi_speed ) )
    {
        error_flag = TWOWIREETH_ERROR;
    }
    else if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->irq, cfg->irq ) )
    {
        error_flag = TWOWIREETH_ERROR;
    }
    else
    {
        /* A high RST releases reset and routes CS from the host to the LAN8651. */
        twowireeth_set_rst_pin( ctx, 1 );
    }

    if ( TWOWIREETH_ERROR == error_flag )
    {
        /* The SDK binds the bus after opening SPI and before setting up the reset pin. */
        if ( ctx->eth.bus == &ctx->bus )
        {
            spi_master_close( &ctx->bus.spi );
            ctx->eth.bus = NULL;
            ctx->eth.bus_ops = NULL;
        }
        if ( I2C_MASTER_ERROR != i2c_status )
        {
            i2c_master_close( &ctx->i2c );
        }
    }
    return error_flag;
}

err_t twowireeth_default_cfg ( twowireeth_t *ctx )
{
    err_t error_flag = eth_transport_init( &ctx->eth, &lan8651_driver );

    if ( ETH_TRANSPORT_ERROR == error_flag )
    {
        // Clear the SDK driver pointer so a failed startup leaves packet I/O disabled.
        ctx->eth.drv = NULL;
        ctx->controller.phy_id = 0;
    }
    return error_flag;
}

err_t twowireeth_write_reg ( twowireeth_t *ctx, uint8_t mms, uint16_t reg, uint32_t value )
{
    uint8_t bytes[ TWOWIREETH_REG_SIZE ];
    bytes[ 0 ] = ( uint8_t ) ( value >> 24 );
    bytes[ 1 ] = ( uint8_t ) ( value >> 16 );
    bytes[ 2 ] = ( uint8_t ) ( value >> 8 );
    bytes[ 3 ] = ( uint8_t ) value;
    return twowireeth_write_regs( ctx, mms, reg, bytes, sizeof( bytes ) );
}

err_t twowireeth_write_regs ( twowireeth_t *ctx, uint8_t mms, uint16_t reg, uint8_t *data_in, uint16_t len )
{
    return twowireeth_transfer_regs( ctx, LAN8651_CTRL_HDR_WNR, mms, reg, data_in, len );
}

err_t twowireeth_read_reg ( twowireeth_t *ctx, uint8_t mms, uint16_t reg, uint32_t *value )
{
    uint8_t bytes[ TWOWIREETH_REG_SIZE ];
    err_t error_flag = twowireeth_read_regs( ctx, mms, reg, bytes, sizeof( bytes ) );

    if ( TWOWIREETH_OK == error_flag )
    {
        *value = twowireeth_read_u32( bytes );
    }
    return error_flag;
}

err_t twowireeth_read_regs ( twowireeth_t *ctx, uint8_t mms, uint16_t reg, uint8_t *data_out, uint16_t len )
{
    return twowireeth_transfer_regs( ctx, TWOWIREETH_CTRL_READ, mms, reg, data_out, len );
}

err_t twowireeth_get_version ( twowireeth_t *ctx, uint16_t *version )
{
    uint32_t device_id;
    err_t error_flag = twowireeth_read_reg( ctx, TWOWIREETH_MMS_MISC, TWOWIREETH_DEVID, &device_id );

    if ( TWOWIREETH_OK == error_flag )
    {
        if ( TWOWIREETH_DEVID_MODEL == ( device_id & TWOWIREETH_DEVID_MODEL_MASK ) )
        {
            *version = ( uint16_t ) ( device_id & TWOWIREETH_DEVID_REV_MASK );
        }
        else
        {
            error_flag = TWOWIREETH_ERROR;
        }
    }
    return error_flag;
}

err_t twowireeth_read_factory_mac ( twowireeth_t *ctx, uint8_t *mac )
{
    uint8_t offset = TWOWIREETH_EUI_OFFSET;
    return i2c_master_write_then_read( &ctx->i2c, &offset, 1, mac, TWOWIREETH_MAC_ADDR_SIZE );
}

err_t twowireeth_set_mac ( twowireeth_t *ctx, uint8_t *mac )
{
    return eth_transport_set_mac( &ctx->eth, mac );
}

err_t twowireeth_set_ip ( twowireeth_t *ctx, uint8_t *ip )
{
    return eth_transport_set_ip( &ctx->eth, ip );
}

uint16_t twowireeth_service_frame ( twowireeth_t *ctx, uint8_t *frame, uint16_t capacity )
{
    uint16_t len = twowireeth_read_packet( ctx, frame, capacity );

    if ( len >= ETH_NET_ETH_HEADER_SIZE )
    {
        // Service local ARP and ping requests while polling for an exchange reply.
        eth_net_handle_arp( &ctx->eth, ctx->eth.mac, ctx->eth.ip, frame, len );
        eth_net_handle_icmp( &ctx->eth, ctx->eth.mac, ctx->eth.ip, frame, len );
    }
    return len;
}

err_t twowireeth_resolve_mac ( twowireeth_t *ctx, twowireeth_socket_t *endpoint, uint8_t *ip )
{
    // Broadcast the Ethernet frame and leave the unknown target MAC zero in the ARP payload.
    uint8_t request[ TWOWIREETH_ARP_FRAME_SIZE ] = {
        TWOWIREETH_MAC_BROADCAST_BYTE, TWOWIREETH_MAC_BROADCAST_BYTE, TWOWIREETH_MAC_BROADCAST_BYTE,
        TWOWIREETH_MAC_BROADCAST_BYTE, TWOWIREETH_MAC_BROADCAST_BYTE, TWOWIREETH_MAC_BROADCAST_BYTE,
        0, 0, 0, 0, 0, 0,
        ( uint8_t ) ( ETH_NET_ETHERTYPE_ARP >> 8 ), ( uint8_t ) ETH_NET_ETHERTYPE_ARP,
        ( uint8_t ) ( TWOWIREETH_ARP_HW_ETHERNET >> 8 ), ( uint8_t ) TWOWIREETH_ARP_HW_ETHERNET,
        ( uint8_t ) ( ETH_NET_ETHERTYPE_IPV4 >> 8 ), ( uint8_t ) ETH_NET_ETHERTYPE_IPV4,
        TWOWIREETH_MAC_ADDR_SIZE, TWOWIREETH_IPV4_ADDR_SIZE,
        ( uint8_t ) ( TWOWIREETH_ARP_OP_REQUEST >> 8 ), ( uint8_t ) TWOWIREETH_ARP_OP_REQUEST
    };
    uint8_t *arp_request = &request[ ETH_NET_ETH_HEADER_SIZE ];
    uint8_t *arp;
    err_t error_flag = TWOWIREETH_ERROR;
    uint8_t retry;
    uint16_t elapsed_ms;

    memcpy( &request[ TWOWIREETH_MAC_ADDR_SIZE ], ctx->eth.mac, TWOWIREETH_MAC_ADDR_SIZE );
    memcpy( &arp_request[ TWOWIREETH_ARP_SENDER_MAC_OFFSET ], ctx->eth.mac, TWOWIREETH_MAC_ADDR_SIZE );
    memcpy( &arp_request[ TWOWIREETH_ARP_SENDER_IP_OFFSET ], ctx->eth.ip, TWOWIREETH_IPV4_ADDR_SIZE );
    memcpy( &arp_request[ TWOWIREETH_ARP_TARGET_IP_OFFSET ], ip, TWOWIREETH_IPV4_ADDR_SIZE );

    for ( retry = 0; ( retry < TWOWIREETH_ARP_RETRIES ) && ( TWOWIREETH_ERROR == error_flag ) &&
          endpoint->frame && ( endpoint->frame_size >= TWOWIREETH_ARP_FRAME_SIZE ); retry++ )
    {
        arp = &endpoint->frame[ ETH_NET_ETH_HEADER_SIZE ];
        if ( !twowireeth_send_packet( ctx, request, sizeof( request ) ) )
        {
            break;
        }
        for ( elapsed_ms = 0; elapsed_ms < TWOWIREETH_ARP_POLLS; elapsed_ms++ )
        {
            uint16_t frame_len = twowireeth_service_frame( ctx, endpoint->frame, endpoint->frame_size );

            /* Match the EtherType, ARP address types and address sizes before checking the reply addresses. */
            if ( ( frame_len >= TWOWIREETH_ARP_FRAME_SIZE ) &&
                 !memcmp( &endpoint->frame[ TWOWIREETH_FRAME_TYPE_OFFSET ], &request[ TWOWIREETH_FRAME_TYPE_OFFSET ],
                          TWOWIREETH_ARP_TYPE_MATCH_LEN ) &&
                 ( TWOWIREETH_ARP_OP_REPLY == twowireeth_read_u16( &arp[ TWOWIREETH_ARP_OPCODE_OFFSET ] ) ) )
            {
                uint8_t target_matches = !memcmp( endpoint->frame, ctx->eth.mac, TWOWIREETH_MAC_ADDR_SIZE ) &&
                                         !memcmp( &arp[ TWOWIREETH_ARP_TARGET_MAC_OFFSET ], ctx->eth.mac,
                                                  TWOWIREETH_MAC_ADDR_SIZE ) &&
                                         !memcmp( &arp[ TWOWIREETH_ARP_TARGET_IP_OFFSET ], ctx->eth.ip,
                                                  TWOWIREETH_IPV4_ADDR_SIZE );
                uint8_t *sender_mac = &arp[ TWOWIREETH_ARP_SENDER_MAC_OFFSET ];
                uint8_t sender_matches = !memcmp( &arp[ TWOWIREETH_ARP_SENDER_IP_OFFSET ], ip, TWOWIREETH_IPV4_ADDR_SIZE ) &&
                                         !( sender_mac[ 0 ] & TWOWIREETH_MAC_GROUP_BIT ) &&
                                         !memcmp( sender_mac, &endpoint->frame[ TWOWIREETH_MAC_ADDR_SIZE ],
                                                  TWOWIREETH_MAC_ADDR_SIZE );

                if ( target_matches && sender_matches )
                {
                    memcpy( endpoint->next_hop_mac, sender_mac, sizeof( endpoint->next_hop_mac ) );
                    error_flag = TWOWIREETH_OK;
                    break;
                }
            }
            Delay_1ms( );
        }
    }
    return error_flag;
}

err_t twowireeth_socket_exchange ( twowireeth_t *ctx, twowireeth_socket_t *endpoint, uint8_t *request, uint16_t len,
                                   uint8_t *reply, uint16_t reply_len )
{
    err_t error_flag = TWOWIREETH_ERROR;

    if ( request && reply && len && reply_len && endpoint->frame &&
         ( endpoint->frame_size >= ETH_NET_ETH_HEADER_SIZE + ETH_NET_IP_HEADER_SIZE + ETH_NET_UDP_HEADER_SIZE ) )
    {
        if ( ( ETH_NET_IP_PROTO_UDP == endpoint->protocol ) && ( len <= TWOWIREETH_UDP_PAYLOAD_MAX ) )
        {
            error_flag = twowireeth_udp_exchange( ctx, endpoint, request, len, reply, reply_len );
        }
        else if ( ( ETH_NET_IP_PROTO_TCP == endpoint->protocol ) && ( len <= TWOWIREETH_TCP_PAYLOAD_MAX ) )
        {
            uint32_t peer_next = 0;

            /* The handshake supplies the first expected sequence number from the peer. */
            error_flag = twowireeth_tcp_connect( ctx, endpoint, &peer_next, len );
            if ( TWOWIREETH_OK == error_flag )
            {
                error_flag = twowireeth_tcp_exchange( ctx, endpoint, peer_next, request, len, reply, reply_len );
            }
            // Use a fresh initial sequence number for the next connection attempt.
            endpoint->sequence += TWOWIREETH_TCP_SEQ_STEP;
        }
    }
    return error_flag;
}

uint16_t twowireeth_send_packet ( twowireeth_t *ctx, uint8_t *data_in, uint16_t len )
{
    uint16_t sent_len = 0;

    if ( ( len >= ETH_NET_ETH_HEADER_SIZE ) && ( len <= TWOWIREETH_FRAME_SIZE ) )
    {
        ctx->eth.bus_error = 0;
        if ( eth_transport_send( &ctx->eth, data_in, len ) && !ctx->eth.bus_error )
        {
            // Return the caller's frame length. The SDK's transmit count can include padding.
            sent_len = len;
        }
    }
    return sent_len;
}

uint16_t twowireeth_read_packet ( twowireeth_t *ctx, uint8_t *data_out, uint16_t len )
{
    return eth_transport_receive( &ctx->eth, data_out, len );
}

uint8_t twowireeth_packet_available ( twowireeth_t *ctx )
{
    return eth_transport_available( &ctx->eth );
}

uint8_t twowireeth_get_link_status ( twowireeth_t *ctx )
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

void twowireeth_set_rst_pin ( twowireeth_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->eth.reset, state );
    if ( !state )
    {
        // Invalidate the transport until default configuration runs again.
        ctx->eth.drv = NULL;
        ctx->controller.phy_id = 0;
    }
}

uint8_t twowireeth_get_int_pin ( twowireeth_t *ctx )
{
    return !!digital_in_read( &ctx->irq );
}

static err_t twowireeth_transfer_regs ( twowireeth_t *ctx, uint32_t command, uint8_t mms, uint16_t reg,
                                        uint8_t *buf, uint16_t len )
{
    uint8_t tx_buf[ TWOWIREETH_CTRL_OVERHEAD + TWOWIREETH_CTRL_BURST ] = { 0 };
    uint8_t rx_buf[ TWOWIREETH_CTRL_OVERHEAD + TWOWIREETH_CTRL_BURST ];
    uint16_t size;
    uint32_t header;
    uint32_t parity;
    err_t error_flag = TWOWIREETH_ERROR;

    if ( buf && len && !( len % TWOWIREETH_REG_SIZE ) &&
         ( ( mms <= LAN8651_MMS_PHY_VS_PLCA ) || ( TWOWIREETH_MMS_MISC == mms ) ) &&
         ( ( uint32_t ) reg + len / TWOWIREETH_REG_SIZE <= 0x10000ul ) )
    {
        while ( len )
        {
            size = len;
            if ( size > TWOWIREETH_CTRL_BURST )
            {
                size = TWOWIREETH_CTRL_BURST;
            }
            /* AID stays clear for auto-increment. LEN encodes the number of words minus one. */
            header = command | ( ( uint32_t ) mms << LAN8651_CTRL_HDR_MMS_SHIFT ) |
                     ( ( uint32_t ) reg << LAN8651_CTRL_HDR_ADDR_SHIFT ) |
                     ( ( ( uint32_t ) size / TWOWIREETH_REG_SIZE - 1u ) << 1 );
            // Fold the header bits and set bit 0 for odd parity.
            parity = header ^ ( header >> 16 );
            parity ^= parity >> 8;
            parity ^= parity >> 4;
            parity ^= parity >> 2;
            parity ^= parity >> 1;
            tx_buf[ 0 ] = ( uint8_t ) ( header >> 24 );
            tx_buf[ 1 ] = ( uint8_t ) ( header >> 16 );
            tx_buf[ 2 ] = ( uint8_t ) ( header >> 8 );
            tx_buf[ 3 ] = ( uint8_t ) ( header | ( ( parity ^ 1u ) & 1u ) );

            if ( LAN8651_CTRL_HDR_WNR == command )
            {
                memcpy( &tx_buf[ TWOWIREETH_REG_SIZE ], buf, size );
            }
            /* SDO echoes the header one word later, followed by read data or the write echo. */
            error_flag = eth_transport_bus_transfer( &ctx->eth, tx_buf, rx_buf, size + TWOWIREETH_CTRL_OVERHEAD );
            if ( ETH_TRANSPORT_ERROR == error_flag )
            {
                break;
            }
            // A rejected command can return an altered header. Writes also echo the transmitted words.
            if ( memcmp( &rx_buf[ TWOWIREETH_REG_SIZE ], tx_buf, TWOWIREETH_REG_SIZE ) ||
                 ( ( LAN8651_CTRL_HDR_WNR == command ) && memcmp( &rx_buf[ TWOWIREETH_CTRL_OVERHEAD ], buf, size ) ) )
            {
                error_flag = TWOWIREETH_ERROR;
                break;
            }
            if ( TWOWIREETH_CTRL_READ == command )
            {
                memcpy( buf, &rx_buf[ TWOWIREETH_CTRL_OVERHEAD ], size );
            }
            // Register indices advance in words and the buffer advances in bytes.
            reg += size / TWOWIREETH_REG_SIZE;
            buf += size;
            len -= size;
        }
    }
    return error_flag;
}

static uint16_t twowireeth_read_u16 ( uint8_t *bytes )
{
    return ( ( uint16_t ) bytes[ 0 ] << 8 ) | bytes[ 1 ];
}

static uint32_t twowireeth_read_u32 ( uint8_t *bytes )
{
    return ( ( uint32_t ) twowireeth_read_u16( bytes ) << 16 ) | twowireeth_read_u16( bytes + 2 );
}

static uint8_t twowireeth_checksum_ok ( uint8_t *ip, uint8_t *segment, uint16_t len )
{
    uint32_t sum = ( uint32_t ) ip[ 9 ] + len;
    uint16_t index;

    // Complete the pseudo-header sum with the IPv4 source and destination addresses.
    for ( index = 12; index < 20; index += 2 )
    {
        sum += twowireeth_read_u16( &ip[ index ] );
    }
    while ( len >= 2u )
    {
        sum += twowireeth_read_u16( segment );
        segment += 2;
        len -= 2;
    }
    if ( len )
    {
        // Pad an odd final byte with zero for the checksum calculation.
        sum += ( uint32_t ) segment[ 0 ] << 8;
    }
    while ( sum >> 16 )
    {
        sum = ( sum & 0xFFFFul ) + ( sum >> 16 );
    }
    return ( 0xFFFFu == sum );
}

static uint8_t *twowireeth_peer_segment ( twowireeth_t *ctx, twowireeth_socket_t *endpoint, uint16_t *len )
{
    uint16_t frame_len = twowireeth_service_frame( ctx, endpoint->frame, endpoint->frame_size );
    uint16_t size = 0;
    uint8_t *segment = eth_net_ipv4_payload( endpoint->frame, frame_len, &size );
    uint8_t *ip = &endpoint->frame[ ETH_NET_ETH_HEADER_SIZE ];
    uint8_t *match = NULL;
    volatile uint8_t protocol = endpoint->protocol;

    *len = 0;
    // A reply comes from the configured peer port and is addressed to this exchange's local port.
    if ( segment && ( size >= ETH_NET_UDP_HEADER_SIZE ) && ( ip[ 9 ] == protocol ) &&
         !memcmp( endpoint->frame, ctx->eth.mac, 6 ) && !memcmp( &ip[ 12 ], endpoint->peer_ip, 4 ) &&
         !memcmp( &ip[ 16 ], ctx->eth.ip, 4 ) &&
         ( endpoint->peer_port == twowireeth_read_u16( segment ) ) &&
         ( endpoint->local_port == twowireeth_read_u16( segment + 2 ) ) )
    {
        if ( ETH_NET_IP_PROTO_UDP == protocol )
        {
            uint16_t udp_len = twowireeth_read_u16( segment + 4 );
            // IPv4 UDP permits a zero checksum. Validate any checksum the peer supplies.
            if ( ( udp_len >= ETH_NET_UDP_HEADER_SIZE ) && ( udp_len <= size ) &&
                 ( !twowireeth_read_u16( segment + 6 ) || twowireeth_checksum_ok( ip, segment, udp_len ) ) )
            {
                match = segment;
                *len = udp_len;
            }
        }
        else if ( size >= ETH_NET_TCP_HEADER_SIZE )
        {
            uint8_t header_len = ( segment[ 12 ] >> 4 ) * 4u;
            if ( ( header_len >= ETH_NET_TCP_HEADER_SIZE ) && ( header_len <= size ) &&
                 twowireeth_checksum_ok( ip, segment, size ) )
            {
                match = segment;
                *len = size;
            }
        }
    }
    return match;
}

static err_t twowireeth_udp_exchange ( twowireeth_t *ctx, twowireeth_socket_t *endpoint, uint8_t *request, uint16_t len,
                                       uint8_t *reply, uint16_t reply_len )
{
    err_t error_flag = TWOWIREETH_SOCKET_SEND_ERROR;
    uint16_t elapsed_ms;
    uint16_t size = 0;
    uint8_t *udp;

    if ( eth_net_send_udp( &ctx->eth, ctx->eth.mac, endpoint->next_hop_mac, endpoint->peer_ip, ctx->eth.ip,
                           endpoint->local_port, endpoint->peer_port, request, len ) )
    {
        error_flag = TWOWIREETH_SOCKET_RECEIVE_ERROR;
        for ( elapsed_ms = 0; elapsed_ms < TWOWIREETH_REPLY_POLLS; elapsed_ms++ )
        {
            udp = twowireeth_peer_segment( ctx, endpoint, &size );
            if ( udp && ( size - ETH_NET_UDP_HEADER_SIZE == reply_len ) )
            {
                memcpy( reply, udp + ETH_NET_UDP_HEADER_SIZE, reply_len );
                error_flag = TWOWIREETH_OK;
                break;
            }
            Delay_1ms( );
        }
    }
    return error_flag;
}

static uint16_t twowireeth_tcp_send ( twowireeth_t *ctx, twowireeth_socket_t *endpoint, uint32_t seq, uint32_t ack,
                                      uint8_t flags, uint8_t *payload, uint16_t len )
{
    volatile uint16_t local_port = endpoint->local_port;
    volatile uint16_t peer_port = endpoint->peer_port;

    return eth_net_send_tcp( &ctx->eth, ctx->eth.mac, ctx->eth.ip, endpoint->next_hop_mac, endpoint->peer_ip,
                             local_port, peer_port, seq, ack, flags, payload, len );
}

static err_t twowireeth_tcp_connect ( twowireeth_t *ctx, twowireeth_socket_t *endpoint, uint32_t *peer_next, uint16_t len )
{
    uint32_t seq = endpoint->sequence;
    // SYN consumes one sequence number. The peer must acknowledge the next number.
    uint32_t next_seq = seq + 1ul;
    uint16_t elapsed_ms;
    uint16_t size = 0;
    uint8_t *tcp;
    err_t error_flag = TWOWIREETH_SOCKET_CONNECT_ERROR;

    for ( elapsed_ms = 0; elapsed_ms < TWOWIREETH_REPLY_POLLS; elapsed_ms++ )
    {
        if ( !( elapsed_ms % TWOWIREETH_TCP_RETRY_POLLS ) &&
             !twowireeth_tcp_send( ctx, endpoint, seq, 0, ETH_NET_TCP_FLAG_SYN, NULL, 0 ) )
        {
            error_flag = TWOWIREETH_SOCKET_SEND_ERROR;
            break;
        }
        tcp = twowireeth_peer_segment( ctx, endpoint, &size );
        if ( tcp && ( tcp[ 13 ] & ETH_NET_TCP_FLAG_ACK ) && ( next_seq == twowireeth_read_u32( tcp + 8 ) ) )
        {
            if ( tcp[ 13 ] & ETH_NET_TCP_FLAG_RST )
            {
                break;
            }
            // Require a SYN/ACK with room in the receive window for the entire request.
            if ( ( tcp[ 13 ] & ETH_NET_TCP_FLAG_SYN ) && !( tcp[ 13 ] & ETH_NET_TCP_FLAG_FIN ) &&
                 ( size == ( tcp[ 12 ] >> 4 ) * 4u ) && ( twowireeth_read_u16( tcp + 14 ) >= len ) )
            {
                *peer_next = twowireeth_read_u32( tcp + 4 ) + 1ul;
                error_flag = TWOWIREETH_SOCKET_SEND_ERROR;
                if ( twowireeth_tcp_send( ctx, endpoint, next_seq, *peer_next, ETH_NET_TCP_FLAG_ACK, NULL, 0 ) )
                {
                    error_flag = TWOWIREETH_OK;
                }
                break;
            }
        }
        Delay_1ms( );
    }
    return error_flag;
}

static err_t twowireeth_tcp_exchange ( twowireeth_t *ctx, twowireeth_socket_t *endpoint, uint32_t peer_next,
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
    err_t error_flag = TWOWIREETH_SOCKET_RECEIVE_ERROR;

    for ( elapsed_ms = 0; elapsed_ms < TWOWIREETH_REPLY_POLLS; elapsed_ms++ )
    {
        // Use the acknowledged byte count to select the remainder of the request on a retry.
        if ( !( elapsed_ms % TWOWIREETH_TCP_RETRY_POLLS ) && ( acknowledged < len ) )
        {
            if ( !twowireeth_tcp_send( ctx, endpoint, first_seq + acknowledged, peer_next,
                                       ETH_NET_TCP_FLAG_ACK | ETH_NET_TCP_FLAG_PSH,
                                       request + acknowledged, len - acknowledged ) )
            {
                error_flag = TWOWIREETH_SOCKET_SEND_ERROR;
                break;
            }
        }

        /* Send FIN once the request is acknowledged and the reply is complete or the peer has closed. */
        if ( ( ( filled == reply_len ) || peer_fin ) && ( acknowledged == len ) &&
             ( !fin_sent || !( elapsed_ms % TWOWIREETH_TCP_RETRY_POLLS ) ) )
        {
            if ( !twowireeth_tcp_send( ctx, endpoint, end_seq, peer_next, ETH_NET_TCP_FLAG_ACK | ETH_NET_TCP_FLAG_FIN, NULL, 0 ) )
            {
                error_flag = TWOWIREETH_SOCKET_SEND_ERROR;
                break;
            }
            fin_sent = 1;
        }

        tcp = twowireeth_peer_segment( ctx, endpoint, &size );
        Delay_1ms( );
        if ( !tcp )
        {
            continue;
        }

        flags = tcp[ 13 ];
        seq = twowireeth_read_u32( tcp + 4 );
        if ( ( flags & ETH_NET_TCP_FLAG_RST ) && ( seq == peer_next ) )
        {
            peer_reset = 1;
            break;
        }

        // Convert the ACK to a request-relative byte count. FIN consumes one sequence number.
        acked = twowireeth_read_u32( tcp + 8 ) - first_seq;
        if ( !( flags & ETH_NET_TCP_FLAG_ACK ) || ( flags & ( ETH_NET_TCP_FLAG_SYN | ETH_NET_TCP_FLAG_RST ) ) ||
             ( acked > len + fin_sent ) )
        {
            continue;
        }
        if ( acked > acknowledged )
        {
            acknowledged = ( uint16_t ) acked;
        }

        // The TCP data offset counts 32-bit words, including any TCP options.
        header_len = ( tcp[ 12 ] >> 4 ) * 4u;
        payload_len = size - header_len;
        if ( payload_len || ( flags & ETH_NET_TCP_FLAG_FIN ) )
        {
            /* Skip bytes already copied to the reply buffer and repeat the last ACK for a gap. */
            skip = peer_next - seq;
            if ( !peer_fin && ( skip <= payload_len ) )
            {
                payload_len -= ( uint16_t ) skip;
                if ( payload_len > reply_len - filled )
                {
                    error_flag = TWOWIREETH_SOCKET_RECEIVE_ERROR;
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
            if ( !twowireeth_tcp_send( ctx, endpoint, end_seq + fin_sent, peer_next, ETH_NET_TCP_FLAG_ACK, NULL, 0 ) )
            {
                error_flag = TWOWIREETH_SOCKET_SEND_ERROR;
                break;
            }
            if ( filled == reply_len )
            {
                error_flag = TWOWIREETH_OK;
            }
        }
        if ( peer_fin && ( acknowledged > len ) )
        {
            break;
        }
    }
    if ( !peer_reset && !( peer_fin && ( acknowledged > len ) ) )
    {
        /* Send a best-effort RST when the peer has not completed the close. */
        twowireeth_tcp_send( ctx, endpoint, first_seq + acknowledged, peer_next,
                             ETH_NET_TCP_FLAG_RST | ETH_NET_TCP_FLAG_ACK, NULL, 0 );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
