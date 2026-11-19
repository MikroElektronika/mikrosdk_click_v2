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
 * @file ethwiz.h
 * @brief This file contains API for ETH WIZ Click Driver.
 */

#ifndef ETHWIZ_H
#define ETHWIZ_H

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
#include "w5500.h"
#include "spi_specifics.h"

/*!
 * @addtogroup ethwiz ETH WIZ Click Driver
 * @brief API for configuring and manipulating ETH WIZ Click driver.
 * @{
 */

/**
 * @defgroup ethwiz_set ETH WIZ Settings
 * @brief Settings for ETH WIZ Click driver.
 */

/**
 * @addtogroup ethwiz_set
 * @{
 */

/**
 * @brief ETH WIZ device settings.
 * @details Defines the expected W5500 version, maximum MACRAW frame size without FCS, and default SPI clock in Hz.
 */
#define ETHWIZ_VERSION                   0x04u
#define ETHWIZ_FRAME_SIZE                W5500_FRAME_SIZE
#define ETHWIZ_SPI_SPEED                 1000000ul

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b ethwiz_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ETHWIZ_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ETHWIZ_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // ethwiz_set

/**
 * @defgroup ethwiz_map ETH WIZ MikroBUS Map
 * @brief MikroBUS pin mapping of ETH WIZ Click driver.
 */

/**
 * @addtogroup ethwiz_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ETH WIZ Click to the selected MikroBUS.
 */
#define ETHWIZ_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ethwiz_map
/*! @} */ // ethwiz

/**
 * @brief ETH WIZ Click context object.
 * @details Context object definition of ETH WIZ Click driver.
 * @note Keep this object alive while using the driver. The transport must remain
 * the first member for the SDK callbacks. Use eth with the SDK eth_net helpers;
 * initialize and reset the device through the Click API.
 */
typedef struct
{
    // Modules
    eth_transport_t eth;        /**< SDK Ethernet transport; must be the first member. */
    eth_bus_spi_t bus;          /**< SDK SPI bus object. */
    w5500_ctx_t controller;     /**< Per-device W5500 state. */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Status flags
    uint8_t tx_fault;           /**< Latched MACRAW send fault cleared by default configuration. */

} ethwiz_t;

/**
 * @brief ETH WIZ Click configuration object.
 * @details Configuration object definition of ETH WIZ Click driver.
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
    spi_master_mode_t                 spi_mode;     /**< SPI mode 0 or 3. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    // Network settings
    uint8_t mac[ 6 ];           /**< Locally assigned, unique unicast MAC address. */
    uint8_t ip[ 4 ];            /**< IPv4 address; all zero for initial DHCP discovery. */

} ethwiz_cfg_t;

/**
 * @brief ETH WIZ Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ETHWIZ_OK = 0,
    ETHWIZ_ERROR = -1

} ethwiz_return_value_t;

/**
 * @brief IPv4 endpoint for W5500 hardware socket 0.
 * @details Stores the protocol, local port and remote IPv4 endpoint for socket 0.
 * @note Ports are in host byte order. Use the same endpoint for opening and receiving.
 */
typedef struct
{
    uint8_t protocol;           /**< W5500_Sn_MR_TCP or W5500_Sn_MR_UDP. */
    uint16_t local_port;        /**< Source port. */
    uint8_t peer_ip[ 4 ];       /**< Peer IPv4 address. */
    uint16_t peer_port;         /**< Peer port. */

} ethwiz_socket_t;

/*!
 * @addtogroup ethwiz ETH WIZ Click Driver
 * @brief API for configuring and manipulating ETH WIZ Click driver.
 * @{
 */

/**
 * @brief ETH WIZ configuration object setup function.
 * @details This function initializes Click configuration structure to initial values.
 * @param[out] cfg : Click configuration structure.
 * See #ethwiz_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note Pins are unconnected, SPI is 1 MHz in mode 0 with active-low chip select, and addresses are zero.
 * Set a unique unicast MAC address before initialization.
 */
void ethwiz_cfg_setup ( ethwiz_cfg_t *cfg );

/**
 * @brief ETH WIZ initialization function.
 * @details This function initializes all necessary pins and peripherals using
 * the SDK W5500 SPI transport.
 * @param[out] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ethwiz_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call ethwiz_default_cfg after this function.
 */
err_t ethwiz_init ( ethwiz_t *ctx, ethwiz_cfg_t *cfg );

/**
 * @brief ETH WIZ default configuration function.
 * @details This function uses the SDK to reset the W5500, verify VERSIONR,
 * program network addresses and open socket 0 in MACRAW mode.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Communication or configuration error.
 * See #err_t definition for detailed explanation.
 * @note Resets existing sessions and clears the MACRAW transmit fault on success.
 * Use the SDK eth_net helpers with ctx->eth while socket 0 is in MACRAW mode.
 */
err_t ethwiz_default_cfg ( ethwiz_t *ctx );

/**
 * @brief ETH WIZ write register function.
 * @details This function writes one byte using the W5500 variable length SPI mode.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] reg : 16-bit register offset within the selected block.
 * @param[in] block : Shifted W5500_BSB_* block selector from w5500.h.
 * @param[in] data_in : Value to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Direct socket or network register changes can invalidate transport state.
 */
err_t ethwiz_write_reg ( ethwiz_t *ctx, uint16_t reg, uint8_t block, uint8_t data_in );

/**
 * @brief ETH WIZ write registers function.
 * @details This function writes sequential bytes under one chip select assertion.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] reg : 16-bit start offset within the selected block.
 * @param[in] block : Shifted W5500_BSB_* block selector from w5500.h.
 * @param[in] data_in : Input buffer.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Direct socket or network register changes can invalidate transport state.
 */
err_t ethwiz_write_regs ( ethwiz_t *ctx, uint16_t reg, uint8_t block, uint8_t *data_in, uint16_t len );

/**
 * @brief ETH WIZ read register function.
 * @details This function reads one byte using the W5500 variable length SPI mode.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] reg : 16-bit register offset within the selected block.
 * @param[in] block : Shifted W5500_BSB_* block selector from w5500.h.
 * @param[out] data_out : Output value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ethwiz_read_reg ( ethwiz_t *ctx, uint16_t reg, uint8_t block, uint8_t *data_out );

/**
 * @brief ETH WIZ read registers function.
 * @details This function reads sequential bytes under one chip select assertion.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] reg : 16-bit start offset within the selected block.
 * @param[in] block : Shifted W5500_BSB_* block selector from w5500.h.
 * @param[out] data_out : Output buffer.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ethwiz_read_regs ( ethwiz_t *ctx, uint16_t reg, uint8_t block, uint8_t *data_out, uint16_t len );

/**
 * @brief ETH WIZ version read function.
 * @details This function reads the one-byte VERSIONR register.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[out] version : Device version, expected to equal ETHWIZ_VERSION.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ethwiz_get_version ( ethwiz_t *ctx, uint8_t *version );

/**
 * @brief ETH WIZ MAC address setting function.
 * @details This function uses the SDK to write SHAR.
 * The SDK updates the transport address only after a successful operation.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] mac : Unique unicast MAC address, six bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call after default configuration and before starting network communication.
 */
err_t ethwiz_set_mac ( ethwiz_t *ctx, uint8_t *mac );

/**
 * @brief ETH WIZ IPv4 address setting function.
 * @details This function uses the SDK to write SIPR.
 * The SDK updates the transport address only after a successful operation.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] ip : IPv4 address, four bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call after default configuration or after obtaining a DHCP address.
 */
err_t ethwiz_set_ip ( ethwiz_t *ctx, uint8_t *ip );

/**
 * @brief ETH WIZ IPv4 route setting function.
 * @details This function writes the subnet mask and gateway and enables hardware IPv4 ping replies.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] subnet : Four-byte IPv4 subnet mask.
 * @param[in] gateway : Four-byte IPv4 gateway address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call after setting the IPv4 address and before opening a hardware socket. Reapply after a reset.
 */
err_t ethwiz_set_route ( ethwiz_t *ctx, uint8_t *subnet, uint8_t *gateway );

/**
 * @brief ETH WIZ hardware socket opening function.
 * @details This function replaces socket 0 with a TCP client or UDP socket and waits until it is ready.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] endpoint : Local port, peer and protocol.
 * See #ethwiz_socket_t object definition for detailed explanation.
 * @return @li @c  0 - Socket ready,
 *         @li @c -1 - Communication or socket error, including connect timeout.
 * See #err_t definition for detailed explanation.
 * @note Opening the socket closes any previous connection or MACRAW socket. Call ethwiz_default_cfg
 * before using the raw frame APIs again. Close the socket if opening fails.
 */
err_t ethwiz_socket_open ( ethwiz_t *ctx, ethwiz_socket_t *endpoint );

/**
 * @brief ETH WIZ hardware socket closing function.
 * @details This function attempts a graceful TCP disconnect for an active connection, then forces closure if needed.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @return @li @c  0 - Socket closed,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ethwiz_socket_close ( ethwiz_t *ctx );

/**
 * @brief ETH WIZ hardware socket send function.
 * @details This function writes a payload to the configured peer and waits for the W5500 SENDOK interrupt.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] buffer : Payload bytes.
 * @param[in] len : Payload length, from 1 to 1460 bytes.
 * @return @li @c  0 - W5500 confirmed the send,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Close the socket after a failed send before attempting another transfer.
 */
err_t ethwiz_socket_send ( ethwiz_t *ctx, uint8_t *buffer, uint16_t len );

/**
 * @brief ETH WIZ hardware socket receive function.
 * @details This function reads available payload from the configured peer without waiting for data to arrive.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] endpoint : Same endpoint passed when opening the socket.
 * @param[out] buffer : Payload buffer.
 * @param[in] capacity : Maximum bytes to copy.
 * @param[out] received : Copied bytes, zero when no matching payload is available.
 * @return @li @c  0 - Poll completed,
 *         @li @c -1 - Error or socket closed.
 * See #err_t definition for detailed explanation.
 * @note TCP data may arrive in parts. UDP datagrams from other peers or larger than capacity are discarded.
 */
err_t ethwiz_socket_receive ( ethwiz_t *ctx, ethwiz_socket_t *endpoint, uint8_t *buffer,
                               uint16_t capacity, uint16_t *received );

/**
 * @brief ETH WIZ packet send function.
 * @details This function sends a complete Ethernet frame through the SDK W5500 driver.
 * The SDK checks free buffer space, waits for SENDOK and clears events by writing one to the corresponding Sn_IR bits.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] data_in : Ethernet frame without FCS.
 * @param[in] len : Frame length, 14 to ETHWIZ_FRAME_SIZE bytes.
 * @return Number of bytes sent, or zero on error.
 * @note Socket 0 must be in MACRAW mode. A failed hardware transmission latches the transmit
 * fault. Call ethwiz_default_cfg to reset the controller and clear it.
 */
uint16_t ethwiz_send_packet ( ethwiz_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief ETH WIZ packet receive function.
 * @details This function reads the next Ethernet frame through the SDK W5500 driver.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[out] data_out : Frame buffer.
 * @param[in] len : Capacity of the frame buffer in bytes.
 * @return Number of bytes copied, or zero on error, if no frame is available or tx_fault is set.
 * @note Socket 0 must be in MACRAW mode. The SDK truncates frames larger than len and discards the remainder.
 */
uint16_t ethwiz_read_packet ( ethwiz_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief ETH WIZ packet availability function.
 * @details This function polls the SDK socket 0 receive status.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @return @li @c 1 - Frame waiting,
 *         @li @c 0 - No frame available.
 * @note Socket 0 must be in MACRAW mode. Interrupt masks are not required for polling.
 */
uint8_t ethwiz_packet_available ( ethwiz_t *ctx );

/**
 * @brief ETH WIZ link status function.
 * @details This function reads the PHY link status through the SDK.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @return @li @c 1 - Link up,
 *         @li @c 0 - Link down or communication error.
 * @note Link status does not establish IP connectivity.
 */
uint8_t ethwiz_get_link_status ( ethwiz_t *ctx );

/**
 * @brief ETH WIZ set RST pin function.
 * @details This function sets the active-low RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @param[in] state : 0 to assert reset, 1 to release reset and route mikroBUS CS to the W5500.
 * @return Nothing.
 * @note Call after ethwiz_init and keep CS inactive when changing RST. Hold RST low for at least
 * 500 us for a hardware reset. After releasing reset, call ethwiz_default_cfg before resuming Ethernet communication.
 */
void ethwiz_set_rst_pin ( ethwiz_t *ctx, uint8_t state );

/**
 * @brief ETH WIZ interrupt pin reading function.
 * @details This function reads the active-low INT pin.
 * @param[in] ctx : Click context object.
 * See #ethwiz_t object definition for detailed explanation.
 * @return @li @c 0 - Interrupt asserted,
 *         @li @c 1 - Interrupt inactive.
 * @note Interrupt masks must be configured before using the pin for notification.
 */
uint8_t ethwiz_get_int_pin ( ethwiz_t *ctx );

/*! @} */ // ethwiz

#ifdef __cplusplus
}
#endif
#endif // ETHWIZ_H

// ------------------------------------------------------------------------ END
