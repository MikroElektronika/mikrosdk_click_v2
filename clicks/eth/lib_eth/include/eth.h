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
 * @file eth.h
 * @brief This file contains API for ETH Click Driver.
 */

#ifndef ETH_H
#define ETH_H

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
#include "enc28j60.h"
#include "spi_specifics.h"

/*!
 * @addtogroup eth ETH Click Driver
 * @brief API for configuring and manipulating ETH Click driver.
 * @{
 */

/**
 * @defgroup eth_set ETH Settings
 * @brief Settings for ETH Click driver.
 */

/**
 * @addtogroup eth_set
 * @{
 */

/**
 * @brief ETH device settings.
 * @details Defines the silicon revision mask, maximum Ethernet frame size without FCS, and default SPI clock in Hz.
 */
#define ETH_REVISION_MASK               0x1Fu
#define ETH_FRAME_SIZE                  ENC28J60_TX_FRAME_SIZE
#define ETH_SPI_SPEED                   1000000ul

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b eth_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ETH_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define ETH_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // eth_set

/**
 * @defgroup eth_map ETH MikroBUS Map
 * @brief MikroBUS pin mapping of ETH Click driver.
 */

/**
 * @addtogroup eth_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ETH Click to the selected MikroBUS.
 */
#define ETH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // eth_map
/*! @} */ // eth

/**
 * @brief ETH Click context object.
 * @details Context object definition of ETH Click driver.
 * @note Keep this object alive while using the driver. Use eth with the SDK eth_net helpers.
 */
typedef struct
{
    // Modules
    eth_transport_t eth;        /**< SDK Ethernet transport. */
    eth_bus_spi_t bus;          /**< SDK SPI bus object. */
    enc28j60_ctx_t controller;  /**< Per-device ENC28J60 state. */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

} eth_t;

/**
 * @brief ETH Click configuration object.
 * @details Configuration object definition of ETH Click driver.
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
    pin_name_t int_pin;         /**< Active-low interrupt pin descriptor. */

    // Static variables
    uint32_t                          spi_speed;    /**< SPI serial speed in Hz. */
    spi_master_mode_t                 spi_mode;     /**< SPI mode 0. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    // Network settings
    uint8_t mac[ 6 ];           /**< Locally assigned, unique unicast MAC address. */
    uint8_t ip[ 4 ];            /**< IPv4 address, all zero for initial DHCP discovery. */
    uint8_t full_duplex;        /**< 0 for half duplex (default), 1 for a link partner fixed to full duplex. */

} eth_cfg_t;

/**
 * @brief ETH Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ETH_OK = 0,
    ETH_ERROR = -1,
    ETH_SOCKET_CONNECT_ERROR = -2,
    ETH_SOCKET_SEND_ERROR = -3,
    ETH_SOCKET_RECEIVE_ERROR = -4

} eth_return_value_t;

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

} eth_socket_t;

/*!
 * @addtogroup eth ETH Click Driver
 * @brief API for configuring and manipulating ETH Click driver.
 * @{
 */

/**
 * @brief ETH configuration object setup function.
 * @details This function initializes Click configuration structure to initial values.
 * @param[out] cfg : Click configuration structure.
 * See #eth_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note Pins are unconnected, SPI is 1 MHz in mode 0 with active-low chip select, and addresses are zero.
 * Set a unique unicast MAC address before initialization.
 */
void eth_cfg_setup ( eth_cfg_t *cfg );

/**
 * @brief ETH initialization function.
 * @details This function initializes all necessary pins and peripherals using
 * the SDK ENC28J60 SPI transport.
 * @param[out] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eth_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call eth_default_cfg after this function.
 */
err_t eth_init ( eth_t *ctx, eth_cfg_t *cfg );

/**
 * @brief ETH default configuration function.
 * @details This function resets the ENC28J60, verifies EREVID, sets the buffers and MAC address, programs
 * the MAC and PHY for the selected duplex mode, and enables reception of valid unicast and broadcast frames.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Communication or configuration error.
 * See #err_t definition for detailed explanation.
 * @note Discards queued frames during reset. Use the SDK eth_net helpers with ctx->eth after configuration.
 */
err_t eth_default_cfg ( eth_t *ctx );

/**
 * @brief ETH write register function.
 * @details This function writes one ENC28J60 control register.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in] reg : Control register address, with the bank in bits 6:5 and the offset in bits 4:0.
 * @param[in] data_in : Value to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use documented writable registers. Direct changes to buffer pointers or MAC settings affect the SDK driver.
 */
err_t eth_write_reg ( eth_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ETH write registers function.
 * @details This function writes consecutive registers in one bank, issuing a separate WCR instruction for each.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in] reg : First control register address, with the bank in bits 6:5 and the offset in bits 4:0.
 * @param[in] data_in : Input buffer.
 * @param[in] len : Number of bytes to write within the bank. Earlier writes take effect if a later write fails.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use documented writable registers. Direct changes to buffer pointers or MAC settings affect the SDK driver.
 */
err_t eth_write_regs ( eth_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ETH read register function.
 * @details This function reads one ENC28J60 control register, including the dummy byte for MAC/MII reads.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in] reg : Control register address, with the bank in bits 6:5 and the offset in bits 4:0.
 * @param[out] data_out : Output value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eth_read_reg ( eth_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief ETH read registers function.
 * @details This function reads consecutive registers in one bank, issuing a separate RCR instruction for each.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in] reg : First control register address, with the bank in bits 6:5 and the offset in bits 4:0.
 * @param[out] data_out : Output buffer.
 * @param[in] len : Number of bytes to read within the bank. Earlier bytes remain available if a later read fails.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eth_read_regs ( eth_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ETH version read function.
 * @details This function reads the silicon revision from EREVID.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[out] version : Raw EREVID value. Bits 4:0 contain the silicon revision.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eth_get_version ( eth_t *ctx, uint8_t *version );

/**
 * @brief ETH MAC address setting function.
 * @details This function uses the SDK to program MAADR1 through MAADR6.
 * The SDK updates the transport address only after a successful operation.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in] mac : Unique unicast MAC address, six bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call after default configuration and before starting network communication.
 */
err_t eth_set_mac ( eth_t *ctx, uint8_t *mac );

/**
 * @brief ETH IPv4 address setting function.
 * @details This function stores the IPv4 address in the SDK transport for use by the host network software.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in] ip : IPv4 address, four bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call after default configuration or after obtaining a DHCP address.
 */
err_t eth_set_ip ( eth_t *ctx, uint8_t *ip );

/**
 * @brief ETH network frame service function.
 * @details This function reads one Ethernet frame and uses the SDK to answer ARP and ICMP echo requests
 * for the configured IPv4 address.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[out] frame : Ethernet frame buffer.
 * @param[in] capacity : Frame buffer capacity in bytes.
 * @return Number of received bytes, or zero on error or if no frame is available.
 * @note Set the local IP address before calling this function.
 */
uint16_t eth_service_frame ( eth_t *ctx, uint8_t *frame, uint16_t capacity );

/**
 * @brief ETH next-hop address resolution function.
 * @details This function broadcasts ARP requests for an on-link IPv4 address and saves the matching MAC address
 * in the endpoint.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in,out] endpoint : Endpoint with a caller-supplied frame buffer.
 * See #eth_socket_t object definition for detailed explanation.
 * @param[in] ip : Four-byte IPv4 address of the local peer or gateway.
 * @return @li @c  0 - Address resolved,
 *         @li @c -1 - Send error or no matching reply within three attempts.
 * See #err_t definition for detailed explanation.
 * @note The frame buffer must hold at least a 42-byte Ethernet/IPv4 ARP reply.
 */
err_t eth_resolve_mac ( eth_t *ctx, eth_socket_t *endpoint, uint8_t *ip );

/**
 * @brief ETH IPv4 request and reply function.
 * @details This function sends one short request to a resolved peer and receives a UDP datagram or gathers in-order TCP bytes.
 * The TCP client opens the stream, sends the request and collects the reply before closing the connection.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in,out] endpoint : Protocol, ports, peer addresses, TCP sequence and frame buffer.
 * See #eth_socket_t object definition for detailed explanation.
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
err_t eth_socket_exchange ( eth_t *ctx, eth_socket_t *endpoint, uint8_t *request, uint16_t len,
                            uint8_t *reply, uint16_t reply_len );

/**
 * @brief ETH packet send function.
 * @details This function sends a complete Ethernet frame through the SDK ENC28J60 driver.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in] data_in : Ethernet frame without FCS.
 * @param[in] len : Frame length, 14 to ETH_FRAME_SIZE bytes.
 * @return Number of bytes sent, or zero on error.
 * @note The MAC pads short frames and appends the FCS.
 */
uint16_t eth_send_packet ( eth_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief ETH packet receive function.
 * @details This function reads the next Ethernet frame through the SDK ENC28J60 driver.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[out] data_out : Frame buffer.
 * @param[in] len : Capacity of the frame buffer in bytes.
 * @return Number of bytes copied, or zero on error or if no valid frame is available.
 * @note The SDK truncates frames larger than len and discards the remainder.
 */
uint16_t eth_read_packet ( eth_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief ETH packet availability function.
 * @details This function reads the packet count through the SDK.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @return Number of queued frames, or zero if none are available or a bus error occurs.
 * @note Interrupt masks are not required for polling.
 */
uint8_t eth_packet_available ( eth_t *ctx );

/**
 * @brief ETH link status function.
 * @details This function reads the PHY link status through the SDK.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @return @li @c 1 - Link up,
 *         @li @c 0 - Link down or communication error.
 * @note Link status does not establish IP connectivity.
 */
uint8_t eth_get_link_status ( eth_t *ctx );

/**
 * @brief ETH set RST pin function.
 * @details This function sets the active-low RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @param[in] state : 0 to assert reset, 1 to release reset and route mikroBUS CS to the ENC28J60.
 * @return Nothing.
 * @note Keep CS inactive when changing RST. Call eth_default_cfg after releasing reset to restore reception.
 */
void eth_set_rst_pin ( eth_t *ctx, uint8_t state );

/**
 * @brief ETH interrupt pin reading function.
 * @details This function reads the active-low INT pin.
 * @param[in] ctx : Click context object.
 * See #eth_t object definition for detailed explanation.
 * @return @li @c 0 - Interrupt asserted,
 *         @li @c 1 - Interrupt inactive.
 * @note Interrupt masks must be configured before using the pin for notification.
 */
uint8_t eth_get_int_pin ( eth_t *ctx );

/*! @} */ // eth

#ifdef __cplusplus
}
#endif
#endif // ETH_H

// ------------------------------------------------------------------------ END
