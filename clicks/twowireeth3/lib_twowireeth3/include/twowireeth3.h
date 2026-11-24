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
 * @file twowireeth3.h
 * @brief This file contains API for Two-Wire ETH 3 Click Driver.
 */

#ifndef TWOWIREETH3_H
#define TWOWIREETH3_H

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
#include "drv_i2c_master.h"
#include "lan8651.h"
#include "spi_specifics.h"

/*!
 * @addtogroup twowireeth3 Two-Wire ETH 3 Click Driver
 * @brief API for configuring and manipulating Two-Wire ETH 3 Click driver.
 * @{
 */

/**
 * @defgroup twowireeth3_set Two-Wire ETH 3 Settings
 * @brief Settings for Two-Wire ETH 3 Click driver.
 */

/**
 * @addtogroup twowireeth3_set
 * @{
 */

/**
 * @brief Two-Wire ETH 3 device settings.
 * @details Defines the frame size without FCS, default SPI clock in Hz and default PLCA node count.
 */
#define TWOWIREETH3_FRAME_SIZE                  LAN8651_TX_FRAME_SIZE
#define TWOWIREETH3_SPI_SPEED                   1000000ul
#define TWOWIREETH3_PLCA_NODES                  8u

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b twowireeth3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define TWOWIREETH3_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define TWOWIREETH3_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // twowireeth3_set

/**
 * @defgroup twowireeth3_map Two-Wire ETH 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Two-Wire ETH 3 Click driver.
 */

/**
 * @addtogroup twowireeth3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Two-Wire ETH 3 Click to the selected MikroBUS.
 */
#define TWOWIREETH3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.irq  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // twowireeth3_map
/*! @} */ // twowireeth3

/**
 * @brief Two-Wire ETH 3 Click context object.
 * @details Context object definition of Two-Wire ETH 3 Click driver.
 * @note Keep this object alive while using the driver. The SDK transport references the bus
 * and controller objects stored here. Pass the eth transport to the SDK eth_net helpers.
 */
typedef struct
{
    // Modules
    eth_transport_t eth;        /**< SDK Ethernet transport. */
    eth_bus_spi_t bus;          /**< SDK SPI bus object. */
    i2c_master_t i2c;           /**< AT24MAC402 I2C master. */
    lan8651_ctx_t controller;   /**< Per-device LAN8651 state. */

    // Input pins
    digital_in_t irq;           /**< Active-low LAN8651 interrupt output. */

} twowireeth3_t;

/**
 * @brief Two-Wire ETH 3 Click configuration object.
 * @details Configuration object definition of Two-Wire ETH 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Active-low chip select pin descriptor. */

    pin_name_t scl;             /**< EEPROM I2C clock pin descriptor. */
    pin_name_t sda;             /**< EEPROM I2C data pin descriptor. */

    // Additional gpio pins
    pin_name_t rst;             /**< Active-low reset and SPI chip-select routing pin descriptor. */
    pin_name_t irq;             /**< Interrupt pin descriptor. */

    // Static variables
    uint32_t                          spi_speed;    /**< SPI serial speed in Hz, up to 25 MHz. */
    spi_master_mode_t                 spi_mode;     /**< SPI mode 0. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    // Network settings
    uint8_t mac[ 6 ];           /**< Unique unicast MAC override. All zero selects the factory EUI-48. */
    uint8_t ip[ 4 ];            /**< Local IPv4 address for the SDK network helpers. */
    uint8_t plca_enable;        /**< 0 for CSMA/CD (default), 1 for PLCA. */
    uint8_t plca_node_id;       /**< Unique PLCA ID on the segment, 0 for the coordinator. */
    uint8_t plca_node_count;    /**< Coordinator's number of transmit opportunities per cycle (default 8). */

} twowireeth3_cfg_t;

/**
 * @brief Two-Wire ETH 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TWOWIREETH3_OK = 0,
    TWOWIREETH3_ERROR = -1,
    TWOWIREETH3_SOCKET_CONNECT_ERROR = -2,
    TWOWIREETH3_SOCKET_SEND_ERROR = -3,
    TWOWIREETH3_SOCKET_RECEIVE_ERROR = -4

} twowireeth3_return_value_t;

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

} twowireeth3_socket_t;

/*!
 * @addtogroup twowireeth3 Two-Wire ETH 3 Click Driver
 * @brief API for configuring and manipulating Two-Wire ETH 3 Click driver.
 * @{
 */

/**
 * @brief Two-Wire ETH 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial values.
 * @param[out] cfg : Click configuration structure.
 * See #twowireeth3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note Pins are unconnected, SPI is 1 MHz in mode 0 with active-low chip select, and addresses are zero.
 * The default is half-duplex CSMA/CD with the factory MAC. For PLCA, assign a unique ID to each node.
 */
void twowireeth3_cfg_setup ( twowireeth3_cfg_t *cfg );

/**
 * @brief Two-Wire ETH 3 initialization function.
 * @details This function configures the LAN8651 SPI transport, the AT24MAC402 I2C
 * interface, and the reset, interrupt and wake pins.
 * @param[out] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #twowireeth3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note An all-zero cfg->mac reads the factory MAC over I2C. Call twowireeth3_default_cfg
 * after this function to program the MAC and enable frame transmission and reception.
 */
err_t twowireeth3_init ( twowireeth3_t *ctx, twowireeth3_cfg_t *cfg );

/**
 * @brief Two-Wire ETH 3 default configuration function.
 * @details This function uses the SDK to reset the LAN8651, initialize the PHY, configure CSMA/CD or PLCA,
 * program the MAC address and enable half-duplex transmission and reception.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Communication or configuration error.
 * See #err_t definition for detailed explanation.
 * @note Call after twowireeth3_init. Reset discards queued frames.
 */
err_t twowireeth3_default_cfg ( twowireeth3_t *ctx );

/**
 * @brief Two-Wire ETH 3 write register function.
 * @details This function writes one LAN8651 register using a 32-bit TC6 word.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[in] mms : LAN8651 memory map selector.
 * @param[in] reg : 16-bit register index within the map.
 * @param[in] value : Register value in host byte order.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid register address or SPI error.
 * See #err_t definition for detailed explanation.
 * @note Keep OA_CONFIG0.PROTE cleared for compatibility with the SDK transfer format.
 */
err_t twowireeth3_write_reg ( twowireeth3_t *ctx, uint8_t mms, uint16_t reg, uint32_t value );

/**
 * @brief Two-Wire ETH 3 write registers function.
 * @details This function writes consecutive register words using TC6 auto-increment.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[in] mms : LAN8651 memory map selector.
 * @param[in] reg : Index of the first register in the map.
 * @param[in] data_in : Register bytes, most significant byte first in each four-byte word.
 * @param[in] len : Number of bytes to write, a nonzero multiple of four.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid register span, missing buffer or SPI error.
 * See #err_t definition for detailed explanation.
 * @note Uses unprotected TC6 bursts of up to four words. Earlier writes can take effect before an error.
 */
err_t twowireeth3_write_regs ( twowireeth3_t *ctx, uint8_t mms, uint16_t reg, uint8_t *data_in, uint16_t len );

/**
 * @brief Two-Wire ETH 3 read register function.
 * @details This function reads one LAN8651 register using a 32-bit TC6 word.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[in] mms : LAN8651 memory map selector.
 * @param[in] reg : 16-bit register index within the map.
 * @param[out] value : Register value in host byte order.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid register address or SPI error.
 * See #err_t definition for detailed explanation.
 * @note The SDK uses unprotected TC6 mode. Reading a clear-on-read register can change device state.
 */
err_t twowireeth3_read_reg ( twowireeth3_t *ctx, uint8_t mms, uint16_t reg, uint32_t *value );

/**
 * @brief Two-Wire ETH 3 read registers function.
 * @details This function reads consecutive register words using TC6 auto-increment.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[in] mms : LAN8651 memory map selector.
 * @param[in] reg : Index of the first register in the map.
 * @param[out] data_out : Register bytes, most significant byte first in each four-byte word.
 * @param[in] len : Number of bytes to read, a nonzero multiple of four.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid register span, missing buffer or SPI error.
 * See #err_t definition for detailed explanation.
 * @note Uses unprotected TC6 bursts of up to four words. Earlier bursts remain in the buffer on a later error.
 */
err_t twowireeth3_read_regs ( twowireeth3_t *ctx, uint8_t mms, uint16_t reg, uint8_t *data_out, uint16_t len );

/**
 * @brief Two-Wire ETH 3 version read function.
 * @details This function reads DEVID and checks the LAN8651 model number in bits 19:4.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[out] version : Silicon revision from bits 3:0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Unexpected chip ID or SPI error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t twowireeth3_get_version ( twowireeth3_t *ctx, uint16_t *version );

/**
 * @brief Two-Wire ETH 3 factory MAC address reading function.
 * @details Reads the six-byte EUI-48 from the AT24MAC402 extended memory.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[out] mac : Six factory-programmed address bytes in network order.
 * @return @li @c  0 - Success,
 *         @li @c -1 - I2C error.
 * See #err_t definition for detailed explanation.
 * @note Call after the I2C interface is configured. This function leaves the programmed MAC filter unchanged.
 */
err_t twowireeth3_read_factory_mac ( twowireeth3_t *ctx, uint8_t *mac );

/**
 * @brief Two-Wire ETH 3 MAC address setting function.
 * @details This function uses the SDK to program MAC_SAB1 and MAC_SAT1.
 * The SDK updates the transport address only after a successful operation.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[in] mac : Unique unicast MAC address, six bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call after default configuration and before starting network communication.
 */
err_t twowireeth3_set_mac ( twowireeth3_t *ctx, uint8_t *mac );

/**
 * @brief Two-Wire ETH 3 IPv4 address setting function.
 * @details This function stores the IPv4 address in the SDK transport for use by the host network software.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[in] ip : IPv4 address, four bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call after default configuration or after obtaining a DHCP address.
 */
err_t twowireeth3_set_ip ( twowireeth3_t *ctx, uint8_t *ip );

/**
 * @brief Two-Wire ETH 3 network frame service function.
 * @details This function reads one Ethernet frame and uses the SDK to answer ARP and ICMP echo requests
 * for the configured IPv4 address.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[out] frame : Ethernet frame buffer.
 * @param[in] capacity : Frame buffer capacity in bytes.
 * @return Number of received bytes, or zero on error or if no frame is available.
 * @note Set the local IP address before calling this function.
 */
uint16_t twowireeth3_service_frame ( twowireeth3_t *ctx, uint8_t *frame, uint16_t capacity );

/**
 * @brief Two-Wire ETH 3 next-hop address resolution function.
 * @details This function broadcasts ARP requests for an on-link IPv4 address and saves the matching MAC address
 * in the endpoint.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[in,out] endpoint : Endpoint with a caller-supplied frame buffer.
 * See #twowireeth3_socket_t object definition for detailed explanation.
 * @param[in] ip : Four-byte IPv4 address of the local peer or gateway.
 * @return @li @c  0 - Address resolved,
 *         @li @c -1 - Send error or no matching reply within three attempts.
 * See #err_t definition for detailed explanation.
 * @note Set the local IP address first. The frame buffer must hold at least a 42-byte Ethernet/IPv4 ARP reply.
 */
err_t twowireeth3_resolve_mac ( twowireeth3_t *ctx, twowireeth3_socket_t *endpoint, uint8_t *ip );

/**
 * @brief Two-Wire ETH 3 IPv4 request and reply function.
 * @details This function sends one short request to a resolved peer and receives a UDP datagram or gathers in-order TCP bytes.
 * The TCP client opens the stream, sends the request, collects the reply and attempts to close the connection.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[in,out] endpoint : Protocol, ports, peer addresses, TCP sequence and frame buffer.
 * See #twowireeth3_socket_t object definition for detailed explanation.
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
 * @note Configure the local IPv4 address and resolve the next-hop MAC before calling. Choose a fresh source port.
 * Size the frame buffer for the Ethernet, IPv4 and transport headers plus the largest reply segment.
 * TCP sends one request segment with bounded retransmission. Each wait allows up to 3000 polls with 1 ms delays.
 * A full TCP reply can return success even when the closing handshake times out.
 */
err_t twowireeth3_socket_exchange ( twowireeth3_t *ctx, twowireeth3_socket_t *endpoint, uint8_t *request, uint16_t len,
                                    uint8_t *reply, uint16_t reply_len );

/**
 * @brief Two-Wire ETH 3 packet send function.
 * @details This function sends a complete Ethernet frame through the SDK LAN8651 driver.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[in] data_in : Ethernet frame without FCS.
 * @param[in] len : Frame length, 14 to TWOWIREETH3_FRAME_SIZE bytes.
 * @return The requested length on success, or zero on error.
 * @note The SDK pads short frames to 60 bytes and the MAC appends the FCS. Success means the LAN8651
 * accepted the frame for transmission.
 */
uint16_t twowireeth3_send_packet ( twowireeth3_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Two-Wire ETH 3 packet receive function.
 * @details This function reads the next Ethernet frame through the SDK LAN8651 driver.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[out] data_out : Frame buffer, including any Ethernet padding.
 * @param[in] len : Capacity of the frame buffer in bytes.
 * @return Number of bytes copied, or zero on error or if no valid frame is available.
 * @note The SDK strips the FCS. It truncates frames larger than len and discards the remainder.
 */
uint16_t twowireeth3_read_packet ( twowireeth3_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Two-Wire ETH 3 packet availability function.
 * @details The SDK checks for a buffered frame or receive chunks waiting in the MAC-PHY.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @return One if a frame or receive chunks are available, otherwise zero.
 * @note A subsequent read may return zero until the entire frame has arrived.
 */
uint8_t twowireeth3_packet_available ( twowireeth3_t *ctx );

/**
 * @brief Two-Wire ETH 3 link status function.
 * @details The SDK reads configuration synchronization in CSMA/CD mode or PLCA status in PLCA mode.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @return @li @c 1 - MAC-PHY synchronized (CSMA/CD) or PLCA active,
 *         @li @c 0 - Inactive or communication error.
 * @note In CSMA/CD mode a disconnected node can still report synchronization.
 */
uint8_t twowireeth3_get_link_status ( twowireeth3_t *ctx );

/**
 * @brief Two-Wire ETH 3 set RST pin function.
 * @details This function sets the active-low RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @param[in] state : 0 to assert reset, 1 to release reset and resume device startup.
 * @return Nothing.
 * @note Keep CS inactive when changing RST. A high RST routes CS to the LAN8651. Call twowireeth3_default_cfg
 * after releasing reset to resume frame transmission and reception.
 */
void twowireeth3_set_rst_pin ( twowireeth3_t *ctx, uint8_t state );

/**
 * @brief Two-Wire ETH 3 interrupt pin reading function.
 * @details This function reads the logic level on the INT pin.
 * @param[in] ctx : Click context object.
 * See #twowireeth3_t object definition for detailed explanation.
 * @return @li @c 0 - Low level,
 *         @li @c 1 - High level.
 * @note IRQ is active low. Service pending TC6 frame or status events before waiting for a new edge.
 */
uint8_t twowireeth3_get_int_pin ( twowireeth3_t *ctx );

/*! @} */ // twowireeth3

#ifdef __cplusplus
}
#endif
#endif // TWOWIREETH3_H

// ------------------------------------------------------------------------ END
