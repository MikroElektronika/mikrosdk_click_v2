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
 * @file eth3.h
 * @brief This file contains API for ETH 3 Click Driver.
 */

#ifndef ETH3_H
#define ETH3_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_in.h"
#include "lan9250.h"
#include "spi_specifics.h"

/*!
 * @addtogroup eth3 ETH 3 Click Driver
 * @brief API for configuring and manipulating ETH 3 Click driver.
 * @{
 */

/**
 * @defgroup eth3_set ETH 3 Settings
 * @brief Settings for ETH 3 Click driver.
 */

/**
 * @addtogroup eth3_set
 * @{
 */

/**
 * @brief ETH 3 device settings.
 * @details Defines the maximum Ethernet frame size without FCS and default SPI clock in Hz.
 */
#define ETH3_FRAME_SIZE                  LAN9250_TX_FRAME_SIZE
#define ETH3_SPI_SPEED                   1000000ul

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU.
 * Can be overwritten with @b eth3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ETH3_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define ETH3_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // eth3_set

/**
 * @defgroup eth3_map ETH 3 MikroBUS Map
 * @brief MikroBUS pin mapping of ETH 3 Click driver.
 */

/**
 * @addtogroup eth3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ETH 3 Click to the selected MikroBUS.
 */
#define ETH3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pme  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // eth3_map
/*! @} */ // eth3

/**
 * @brief ETH 3 Click context object.
 * @details Context object definition of ETH 3 Click driver.
 * @note Keep this object alive while using the driver. Pass its eth transport to the SDK eth_net helpers.
 */
typedef struct
{
    // Modules
    eth_transport_t eth;        /**< SDK Ethernet transport. */
    eth_bus_spi_t bus;          /**< SDK SPI bus object. */
    lan9250_ctx_t controller;   /**< Per-device LAN9250 state. */

    // Input pins
    digital_in_t int_pin;       /**< IRQ output from the LAN9250, active low by default. */
    digital_in_t pme;           /**< Power-management event output from the LAN9250. */

} eth3_t;

/**
 * @brief ETH 3 Click configuration object.
 * @details Configuration object definition of ETH 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Active-low chip select pin descriptor. */

    // Additional gpio pins
    pin_name_t rst;             /**< Active-low reset pin descriptor. */
    pin_name_t int_pin;         /**< Interrupt pin descriptor. */
    pin_name_t pme;             /**< Power-management event pin descriptor (AN). */

    // Static variables
    uint32_t                          spi_speed;    /**< SPI serial speed in Hz, up to 30 MHz for the READ instruction. */
    spi_master_mode_t                 spi_mode;     /**< SPI mode 0. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    // Network settings
    uint8_t mac[ 6 ];           /**< Locally assigned, unique unicast MAC address. */
    uint8_t ip[ 4 ];            /**< IPv4 address, all zero for initial DHCP discovery. */
    uint8_t full_duplex;        /**< MAC duplex must match the PHY link. 1 for full (default), 0 for half. */

} eth3_cfg_t;

/**
 * @brief ETH 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ETH3_OK = 0,
    ETH3_ERROR = -1,
    ETH3_SOCKET_CONNECT_ERROR = -2,
    ETH3_SOCKET_SEND_ERROR = -3,
    ETH3_SOCKET_RECEIVE_ERROR = -4

} eth3_return_value_t;

/**
 * @brief IPv4 peer for a short TCP or UDP exchange.
 * @details The caller supplies a reusable Ethernet receive buffer for ARP and IP frames.
 * @note Initialize sequence once and keep this object and its frame buffer alive throughout an exchange.
 */
typedef struct
{
    uint8_t protocol;           /**< ETH_NET_IP_PROTO_TCP or ETH_NET_IP_PROTO_UDP. */
    uint16_t local_port;        /**< Source port in host byte order. */
    uint8_t peer_ip[ 4 ];       /**< Peer IPv4 address. */
    uint16_t peer_port;         /**< Peer port in host byte order. */
    uint8_t next_hop_mac[ 6 ];  /**< MAC address of the on-link peer or router. */
    uint32_t sequence;          /**< Initial sequence number for the next TCP connection. */
    uint8_t *frame;             /**< Scratch Ethernet frame buffer. */
    uint16_t frame_size;        /**< Capacity of the frame buffer in bytes. */

} eth3_socket_t;

/*!
 * @addtogroup eth3 ETH 3 Click Driver
 * @brief API for configuring and manipulating ETH 3 Click driver.
 * @{
 */

/**
 * @brief ETH 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial values.
 * @param[out] cfg : Click configuration structure.
 * See #eth3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note Pins are unconnected, SPI is 1 MHz in mode 0 with active-low chip select, and addresses are zero.
 * Set a unique unicast MAC address before initialization. Set full_duplex to 0 for a half-duplex link.
 */
void eth3_cfg_setup ( eth3_cfg_t *cfg );

/**
 * @brief ETH 3 initialization function.
 * @details This function initializes all necessary pins and peripherals using
 * the SDK LAN9250 SPI transport.
 * @param[out] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eth3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call eth3_default_cfg after this function.
 */
err_t eth3_init ( eth3_t *ctx, eth3_cfg_t *cfg );

/**
 * @brief ETH 3 default configuration function.
 * @details This function resets the LAN9250, waits for readiness, verifies its ID, and configures the FIFO and MAC
 * through the SDK. It enables frame transmission and reception using the configured MAC duplex.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Communication or configuration error.
 * See #err_t definition for detailed explanation.
 * @note Discards queued frames during reset. The PHY negotiates independently of the configured MAC duplex.
 */
err_t eth3_default_cfg ( eth3_t *ctx );

/**
 * @brief ETH 3 write register function.
 * @details This function writes one 32-bit LAN9250 system register.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in] reg : DWORD-aligned register byte address.
 * @param[in] value : Register value in host byte order.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid register address or SPI error.
 * See #err_t definition for detailed explanation.
 * @note Direct changes to FIFO, reset or MAC settings affect the SDK driver.
 */
err_t eth3_write_reg ( eth3_t *ctx, uint16_t reg, uint32_t value );

/**
 * @brief ETH 3 write registers function.
 * @details This function writes consecutive 32-bit registers using the LAN9250 auto-increment mode.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in] reg : DWORD-aligned byte address of the first register.
 * @param[in] data_in : Register bytes, least significant byte first in each DWORD.
 * @param[in] len : Number of bytes to write, a nonzero multiple of four.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid register span, missing buffer or SPI error.
 * See #err_t definition for detailed explanation.
 * @note Use consecutive writable registers. Complete DWORDs may already be written on a later error.
 */
err_t eth3_write_regs ( eth3_t *ctx, uint16_t reg, uint8_t *data_in, uint16_t len );

/**
 * @brief ETH 3 read register function.
 * @details This function reads one 32-bit LAN9250 system register.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in] reg : DWORD-aligned register byte address.
 * @param[out] value : Register value in host byte order.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid register address or SPI error.
 * See #err_t definition for detailed explanation.
 * @note Reading a FIFO or clear-on-read register can change device state.
 */
err_t eth3_read_reg ( eth3_t *ctx, uint16_t reg, uint32_t *value );

/**
 * @brief ETH 3 read registers function.
 * @details This function reads consecutive 32-bit registers using the LAN9250 auto-increment mode.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in] reg : DWORD-aligned byte address of the first register.
 * @param[out] data_out : Register bytes, least significant byte first in each DWORD.
 * @param[in] len : Number of bytes to read, a nonzero multiple of four.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid register span, missing buffer or SPI error.
 * See #err_t definition for detailed explanation.
 * @note Use consecutive readable registers. Reading a FIFO or clear-on-read register can change device state.
 */
err_t eth3_read_regs ( eth3_t *ctx, uint16_t reg, uint8_t *data_out, uint16_t len );

/**
 * @brief ETH 3 version read function.
 * @details This function reads ID_REV and verifies the LAN9250 chip ID in bits 31:16.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[out] version : Silicon revision from bits 15:0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Unexpected chip ID or SPI error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eth3_get_version ( eth3_t *ctx, uint16_t *version );

/**
 * @brief ETH 3 MAC address setting function.
 * @details This function uses the SDK to program HMAC_ADDRL and HMAC_ADDRH.
 * The SDK updates the transport address only after a successful operation.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in] mac : Unique unicast MAC address, six bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call after default configuration and before starting network communication.
 */
err_t eth3_set_mac ( eth3_t *ctx, uint8_t *mac );

/**
 * @brief ETH 3 IPv4 address setting function.
 * @details This function stores the IPv4 address in the SDK transport for use by the host network software.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in] ip : IPv4 address, four bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call after default configuration or after obtaining a DHCP address.
 */
err_t eth3_set_ip ( eth3_t *ctx, uint8_t *ip );

/**
 * @brief ETH 3 network frame service function.
 * @details This function reads one Ethernet frame and uses the SDK to answer ARP and ICMP echo requests
 * for the configured IPv4 address.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[out] frame : Ethernet frame buffer.
 * @param[in] capacity : Frame buffer capacity in bytes.
 * @return Number of received bytes, or zero on error or if no frame is available.
 * @note Set the local IP address before calling this function.
 */
uint16_t eth3_service_frame ( eth3_t *ctx, uint8_t *frame, uint16_t capacity );

/**
 * @brief ETH 3 next-hop address resolution function.
 * @details This function broadcasts ARP requests for an on-link IPv4 address and saves the matching MAC address
 * in the endpoint.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in,out] endpoint : Endpoint with a caller-supplied frame buffer.
 * See #eth3_socket_t object definition for detailed explanation.
 * @param[in] ip : Four-byte IPv4 address of the local peer or gateway.
 * @return @li @c  0 - Address resolved,
 *         @li @c -1 - Send error or no matching reply within three attempts.
 * See #err_t definition for detailed explanation.
 * @note The frame buffer must hold at least a 42-byte Ethernet/IPv4 ARP reply.
 */
err_t eth3_resolve_mac ( eth3_t *ctx, eth3_socket_t *endpoint, uint8_t *ip );

/**
 * @brief ETH 3 IPv4 request and reply function.
 * @details This function sends one short request to a resolved peer and receives a UDP datagram or gathers in-order TCP bytes.
 * The TCP client opens the stream, sends the request and collects the reply before closing the connection.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in,out] endpoint : Protocol, ports, peer addresses, TCP sequence and frame buffer.
 * See #eth3_socket_t object definition for detailed explanation.
 * @param[in] request : Request payload.
 * @param[in] len : Number of request bytes, up to 346 for TCP or 358 for UDP with the SDK's 400-byte TX buffer.
 * @param[out] reply : Reply buffer. The request, reply and frame buffers must be separate.
 * @param[in] reply_len : Expected number of reply bytes.
 * @return @li @c  0 - The expected number of bytes was received,
 *         @li @c -1 - Invalid exchange parameters,
 *         @li @c -2 - TCP handshake failed,
 *         @li @c -3 - Frame transmission failed,
 *         @li @c -4 - Reply incomplete, invalid, or timed out.
 * See #err_t definition for detailed explanation.
 * @note For short request/reply protocols. The request, expected reply and frame buffer must be nonempty.
 * TCP sends one request segment with bounded retransmission. Each wait allows up to 3000 one-millisecond polls.
 * Choose a fresh source port for each exchange.
 */
err_t eth3_socket_exchange ( eth3_t *ctx, eth3_socket_t *endpoint, uint8_t *request, uint16_t len,
                             uint8_t *reply, uint16_t reply_len );

/**
 * @brief ETH 3 packet send function.
 * @details This function sends a complete Ethernet frame through the SDK LAN9250 driver.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in] data_in : Ethernet frame without FCS.
 * @param[in] len : Frame length, 14 to ETH3_FRAME_SIZE bytes.
 * @return Number of bytes sent, or zero on error.
 * @note The MAC pads short frames and appends the FCS.
 */
uint16_t eth3_send_packet ( eth3_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief ETH 3 packet receive function.
 * @details This function reads the next Ethernet frame through the SDK LAN9250 driver.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[out] data_out : Frame buffer.
 * @param[in] len : Capacity of the frame buffer in bytes.
 * @return Number of bytes copied, or zero on error or if no valid frame is available.
 * @note The SDK truncates frames larger than len and discards the remainder.
 */
uint16_t eth3_read_packet ( eth3_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief ETH 3 packet availability function.
 * @details This function reads the packet count through the SDK.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @return Number of queued frames, or zero if none are available or a bus error occurs.
 * @note Interrupt masks are not required for polling.
 */
uint8_t eth3_packet_available ( eth3_t *ctx );

/**
 * @brief ETH 3 link status function.
 * @details This function reads the PHY link status through the SDK.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @return @li @c 1 - Link up,
 *         @li @c 0 - Link down or communication error.
 * @note Link status does not establish IP connectivity.
 */
uint8_t eth3_get_link_status ( eth3_t *ctx );

/**
 * @brief ETH 3 set RST pin function.
 * @details This function sets the active-low RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @param[in] state : 0 to assert reset, 1 to release reset and resume device startup.
 * @return Nothing.
 * @note Keep CS inactive when changing RST. Call eth3_default_cfg after releasing reset to restore reception.
 */
void eth3_set_rst_pin ( eth3_t *ctx, uint8_t state );

/**
 * @brief ETH 3 interrupt pin reading function.
 * @details This function reads the logic level on the INT pin.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @return @li @c 0 - Low level,
 *         @li @c 1 - High level.
 * @note IRQ is active low by default. Enable IRQ_CFG.IRQ_EN and the required INT_EN sources to use it.
 */
uint8_t eth3_get_int_pin ( eth3_t *ctx );

/**
 * @brief ETH 3 power-management event pin reading function.
 * @details This function reads the PME output on mikroBUS AN.
 * @param[in] ctx : Click context object.
 * See #eth3_t object definition for detailed explanation.
 * @return @li @c 0 - Low level,
 *         @li @c 1 - High level.
 * @note Configure PMT_CTRL to enable the output. Open-drain operation needs an external pull-up.
 */
uint8_t eth3_get_pme_pin ( eth3_t *ctx );

/*! @} */ // eth3

#ifdef __cplusplus
}
#endif
#endif // ETH3_H

// ------------------------------------------------------------------------ END
