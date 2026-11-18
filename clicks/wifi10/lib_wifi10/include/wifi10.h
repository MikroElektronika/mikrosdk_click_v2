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
 * @file wifi10.h
 * @brief This file contains API for WiFi 10 Click Driver.
 */

#ifndef WIFI10_H
#define WIFI10_H

#ifdef __cplusplus
extern "C" {
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

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup wifi10 WiFi 10 Click Driver
 * @brief API for configuring and manipulating WiFi 10 Click driver.
 * @{
 */

/**
 * @defgroup wifi10_reg WiFi 10 Registers List
 * @brief List of registers of WiFi 10 Click driver.
 */

/**
 * @addtogroup wifi10_reg
 * @{
 */

/**
 * @brief WiFi 10 SPI internal registers.
 * @details Byte addresses for mailbox transfers, host register access, and SPI interrupt control.
 */
#define WIFI10_REG_DMA_SIZE             0x0100u
#define WIFI10_REG_WRITE_SPACE          0x0200u
#define WIFI10_REG_READ_AVAILABLE       0x0300u
#define WIFI10_REG_CONFIG               0x0400u
#define WIFI10_REG_STATUS               0x0500u
#define WIFI10_REG_HOST_SIZE            0x0600u
#define WIFI10_REG_HOST_CONFIG          0x0700u
#define WIFI10_REG_HOST_READ            0x0800u
#define WIFI10_REG_HOST_WRITE           0x0A00u
#define WIFI10_REG_INT_CAUSE            0x0C00u
#define WIFI10_REG_INT_ENABLE           0x0D00u
#define WIFI10_REG_WRITE_WATERMARK      0x1300u
#define WIFI10_REG_LOOKAHEAD_1          0x1400u
#define WIFI10_REG_LOOKAHEAD_2          0x1500u

/*! @} */ // wifi10_reg

/**
 * @defgroup wifi10_set WiFi 10 Registers Settings
 * @brief Settings for registers of WiFi 10 Click driver.
 */

/**
 * @addtogroup wifi10_set
 * @{
 */

/**
 * @brief WiFi 10 host transport settings.
 * @details Default SPI clock in Hz, padded HTC frame buffer capacity in bytes, and endpoint count.
 */
#define WIFI10_SPI_DEFAULT_SPEED        1000000ul
#define WIFI10_FRAME_SIZE               1664u
#define WIFI10_ENDPOINT_COUNT           6u

/**
 * @brief WiFi 10 station authentication settings.
 * @details Open and WPA2 Personal authentication modes, SSID and ASCII passphrase limits, and the length
 * of a precomputed hexadecimal WPA2 key. Input lengths exclude the null terminator.
 */
#define WIFI10_AUTH_OPEN                0u
#define WIFI10_AUTH_WPA2_PSK            1u
#define WIFI10_SSID_MAX_LENGTH          32u
#define WIFI10_PASSWORD_MAX_LENGTH      63u
#define WIFI10_PMK_HEX_LENGTH           64u

/**
 * @brief WiFi 10 IPv4 socket settings.
 * @details TCP and UDP socket types, socket count, maximum send size, and per-socket receive capacity in bytes.
 */
#define WIFI10_SOCKET_TCP               1u
#define WIFI10_SOCKET_UDP               2u
#define WIFI10_MAX_SOCKETS              2u
#define WIFI10_MAX_PAYLOAD              1460u
#define WIFI10_RX_CAPACITY              1600u

/**
 * @brief WiFi 10 polling timeouts.
 * @details Delay budgets in milliseconds for firmware startup, association or TCP connect, DHCP, and command replies.
 * SPI transfers add execution time.
 */
#define WIFI10_BOOT_TIMEOUT             15000ul
#define WIFI10_CONNECT_TIMEOUT          30000ul
#define WIFI10_DHCP_TIMEOUT             60000ul
#define WIFI10_COMMAND_TIMEOUT          10000ul

/**
 * @brief WiFi 10 pin states.
 * @details Logic levels for digital pins.
 */
#define WIFI10_PIN_STATE_LOW            0u
#define WIFI10_PIN_STATE_HIGH           1u

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU.
 * Apply after initialization if the MCU requires a different sampling point.
 */
#define WIFI10_SET_DATA_SAMPLE_EDGE     SET_SPI_DATA_SAMPLE_EDGE
#define WIFI10_SET_DATA_SAMPLE_MIDDLE   SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // wifi10_set

/**
 * @defgroup wifi10_map WiFi 10 MikroBUS Map
 * @brief MikroBUS pin mapping of WiFi 10 Click driver.
 */

/**
 * @addtogroup wifi10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of WiFi 10 Click to the selected MikroBUS.
 */
#define WIFI10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.fet = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.iot = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwd = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // wifi10_map
/*! @} */ // wifi10

/**
 * @brief WiFi 10 IPv4 configuration.
 * @details Addresses use host numeric order: 192.168.1.2 is 0xC0A80102.
 */
typedef struct
{
    uint32_t address;          /**< Assigned IPv4 address. */
    uint32_t subnet;           /**< Subnet mask. */
    uint32_t gateway;          /**< Default gateway. */

} wifi10_ip_cfg_t;

/**
 * @brief WiFi 10 socket state.
 * @details Internal storage for one IPv4 socket; application code must not modify it.
 */
typedef struct
{
    int32_t handle;                        /**< Firmware handle, zero when unused. */
    uint8_t type;                          /**< TCP or UDP. */
    uint8_t connected;                     /**< 1 after a successful TCP connect response. */
    uint8_t closed;                        /**< 1 after a peer close event. */
    uint8_t rx_pending;                    /**< 1 when a received UDP datagram or TCP bytes are buffered. */
    uint16_t rx_length;                    /**< Buffered payload size. */
    uint16_t rx_offset;                    /**< Next unread TCP byte. */
    uint32_t peer_address;                 /**< Sender IPv4 address for a UDP datagram. */
    uint16_t peer_port;                    /**< Sender port for a UDP datagram. */
    uint8_t rx_buf[ WIFI10_RX_CAPACITY ];  /**< Received socket bytes. */

} wifi10_socket_t;

/**
 * @brief WiFi 10 protocol state.
 * @details Internal state, cleared during hardware reset.
 */
typedef struct
{
    err_t fault;                                    /**< Sticky transport/protocol fault; reset required when nonzero. */
    char *protocol_fault;                           /**< Read-only name of the stage that detected a protocol fault. */
    uint16_t protocol_detail;                       /**< Interrupt status, frame length, or credit count for that fault. */
    uint8_t ready;                                  /**< 1 after a compatible WMI ready event. */
    uint8_t channel_list_ready;                     /**< 1 after a valid reply to the channel list request. */
    uint8_t station_auth;                           /**< Authentication mode of the station profile. */
    uint8_t associated;                             /**< 1 after the access point accepts association. */
    uint8_t connected;                              /**< 1 after association and any required WPA2 handshake. */
    uint8_t disconnect_reason;                      /**< Last firmware disconnect reason. */
    uint8_t credit_init;                            /**< 1 after the firmware publishes credit counters. */
    uint8_t credits[ WIFI10_ENDPOINT_COUNT ];       /**< Available transmit credits. */
    uint8_t reported[ WIFI10_ENDPOINT_COUNT ];      /**< Wrapping in-band credit totals. */
    uint8_t borrowed[ WIFI10_ENDPOINT_COUNT ];      /**< Out-of-band credits already consumed from reports. */
    uint8_t sequence[ WIFI10_ENDPOINT_COUNT ];      /**< Per-endpoint transmit sequence. */
    uint32_t firmware_version;                      /**< Version reported by firmware. */
    uint32_t abi_version;                           /**< Firmware interface version. */
    uint8_t mac[ 6 ];                               /**< Station MAC address reported by firmware. */
    uint16_t command_error;                         /**< Rejected WMI command identifier. */
    uint8_t command_reason;                         /**< Firmware command rejection code. */
    uint8_t response_pending;                       /**< 1 while a socket command is outstanding. */
    uint8_t response_ready;                         /**< 1 after its matching response. */
    uint8_t dhcp_start;                             /**< 1 while a DHCP start reply may omit IPv4 settings. */
    uint32_t response_type;                         /**< Expected socket command type. */
    int32_t expected_handle;                        /**< Expected socket handle; zero for open/global commands. */
    int32_t response_handle;                        /**< Socket handle returned by firmware. */
    int32_t response_result;                        /**< Command status decoded from the matching firmware reply. */
    wifi10_ip_cfg_t ip;                             /**< Most recent IPv4 configuration. */
    wifi10_socket_t sockets[ WIFI10_MAX_SOCKETS ];  /**< Allocated IPv4 socket slots. */

} wifi10_state_t;

/**
 * @brief WiFi 10 Click configuration object.
 * @details Configuration object definition of WiFi 10 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI. */
    pin_name_t sck;                                 /**< SPI clock pin descriptor. */
    pin_name_t cs;                                  /**< Active-low chip select; boot strap HM1 must be high. */

    // Additional gpio pins
    pin_name_t fet;                                 /**< Low enables the module's 3.3 V supply. */
    pin_name_t iot;                                 /**< IOT_MODE_EN; held high in hosted SPI mode. */
    pin_name_t pwd;                                 /**< Active-low CHIP_PWD_L reset. */
    pin_name_t int_pin;                             /**< Module HSPI_INT input; never driven by this driver. */

    // static variable
    uint32_t spi_speed;                             /**< SPI clock in Hz; default 1 MHz. */
    spi_master_mode_t spi_mode;                     /**< Use SPI_MASTER_MODE_3. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Use active-low chip select. */

} wifi10_cfg_t;

/**
 * @brief WiFi 10 Click context object.
 * @details Polling driver for QCA4004 hosted firmware with ABI 1.
 * @note Use static storage. Call APIs from one execution context; APIs are not reentrant.
 * The host uses fixed buffers and supports two IPv4 sockets, open/WPA2-PSK station mode, and DHCP.
 * Firmware must already be installed in module flash. Flash programming, TLS, AP mode, and IPv6 are not implemented.
 */
typedef struct
{
    // Output pins
    digital_out_t fet;                    /**< Active-low module power control. */
    digital_out_t iot;                    /**< Hosted-mode enable output. */
    digital_out_t pwd;                    /**< Active-low module reset output. */

    // Input pins
    digital_in_t int_pin;                 /**< Module interrupt input. */

    // Modules
    spi_master_t spi;                     /**< SPI driver object. */
    pin_name_t chip_select;               /**< SPI chip-select pin descriptor. */
    wifi10_cfg_t cfg;                     /**< Saved pin and SPI settings for reset. */
    uint8_t spi_open;                     /**< 1 after the SPI peripheral is opened. */
    wifi10_state_t state;                 /**< Firmware, connection, and socket state. */
    uint8_t tx_buf[ WIFI10_FRAME_SIZE ];  /**< Outgoing HTC frame and padding. */
    uint8_t rx_buf[ WIFI10_FRAME_SIZE ];  /**< Incoming HTC frame and padding. */

} wifi10_t;

/**
 * @brief WiFi 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WIFI10_OK = 0,
    WIFI10_ERROR = -1,
    WIFI10_ERROR_TIMEOUT = -2,
    WIFI10_ERROR_PROTOCOL = -3,
    WIFI10_ERROR_COMMAND = -4,
    WIFI10_ERROR_DISCONNECTED = -5,
    WIFI10_ERROR_BUFFER = -6,
    WIFI10_ERROR_FIRMWARE = -7,
    WIFI10_ERROR_CLOSED = -8

} wifi10_return_value_t;

/*!
 * @addtogroup wifi10 WiFi 10 Click Driver
 * @brief API for configuring and manipulating WiFi 10 Click driver.
 * @{
 */

/**
 * @brief WiFi 10 configuration object setup function.
 * @details Initializes the configuration with 1 MHz SPI mode 3 and active-low chip select.
 * @param[out] cfg : Click configuration structure.
 * See #wifi10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note All used pins will be set to unconnected state.
 */
void wifi10_cfg_setup ( wifi10_cfg_t *cfg );

/**
 * @brief WiFi 10 initialization function.
 * @details Initializes GPIO, resets the module with SCK undriven, then opens the SPI peripheral.
 * @param[out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #wifi10_cfg_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Peripheral or pin initialization error.
 * See #err_t definition for detailed explanation.
 * @note Call once on a new context, then call wifi10_default_cfg.
 * Use 3.3 V logic, a 5 V board supply, and the COMM SEL jumper in the SPI position.
 */
err_t wifi10_init ( wifi10_t *ctx, wifi10_cfg_t *cfg );

/**
 * @brief WiFi 10 hardware reset function.
 * @details Closes SPI, resets the module with the hosted SPI straps set, and reopens SPI.
 * Clears the protocol state and invalidates every socket handle.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Peripheral or pin error.
 * See #err_t definition for detailed explanation.
 * @note Call wifi10_default_cfg after reset. No flash write is performed.
 */
err_t wifi10_hw_reset ( wifi10_t *ctx );

/**
 * @brief WiFi 10 default configuration function.
 * @details Starts hosted firmware, sets the 2.4 GHz PHY, enables socket offload, and checks the WMI channel list.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @return @li @c 0 - Firmware and host initialized,
 *         @li @c <0 - Transport, timeout, protocol, or incompatible firmware error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note Call after init or hardware reset. Startup does not associate or write nonvolatile configuration.
 * Timeouts are polling delay budgets; SPI transactions add execution time.
 */
err_t wifi10_default_cfg ( wifi10_t *ctx );

/**
 * @brief WiFi 10 write register function.
 * @details Writes one 16-bit SPI internal register using big-endian framing.
 * @param[in] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] reg : SPI internal register address.
 * @param[in] value : Register value.
 * @return @li @c 0 - Success,
 *         @li @c -1 - SPI error.
 * See #err_t definition for detailed explanation.
 * @note This is not a firmware memory or WiFi command interface.
 */
err_t wifi10_write_reg ( wifi10_t *ctx, uint16_t reg, uint16_t value );

/**
 * @brief WiFi 10 read register function.
 * @details Reads one 16-bit SPI internal register using big-endian framing.
 * @param[in] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] reg : SPI internal register address.
 * @param[out] value : Register value, updated only on success.
 * @return @li @c 0 - Success,
 *         @li @c -1 - SPI error.
 * See #err_t definition for detailed explanation.
 * @note Keep raw register access separate from active socket operations.
 */
err_t wifi10_read_reg ( wifi10_t *ctx, uint16_t reg, uint16_t *value );

/**
 * @brief WiFi 10 event processing function.
 * @details Polls firmware status and processes at most one received frame, including transmit credits.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @return @li @c 0 - Poll completed, including when no frame was available,
 *         @li @c <0 - Error; inspect state.fault for a reset-required failure.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note Call frequently between API calls and consume received bytes promptly.
 * Buffer overflow is reported explicitly. No incoming socket payload is silently truncated.
 */
err_t wifi10_process ( wifi10_t *ctx );

/**
 * @brief WiFi 10 station connection function.
 * @details Configures an open or WPA2-PSK station and lets the firmware select the access point.
 * For a WPA2 passphrase, the host derives the key from the passphrase and SSID before sending it to the module.
 * Waits for association and any required WPA2 handshake. The wait continues if the firmware reports no network
 * during discovery and keeps trying to associate.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] ssid : Network name, 1-32 bytes.
 * @param[in] password : WPA2 passphrase of 8-63 printable ASCII bytes or a 64-digit hexadecimal key.
 * Use an empty string for an open network.
 * @param[in] auth : WIFI10_AUTH_OPEN or WIFI10_AUTH_WPA2_PSK.
 * @return @li @c 0 - Associated and ready for IP configuration,
 *         @li @c <0 - Invalid parameters, rejection, disconnect, transport, or timeout error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note Call wifi10_dhcp after a successful connection.
 * Credentials remain volatile and are not logged. A command timeout requires hardware reset.
 */
err_t wifi10_connect ( wifi10_t *ctx, char *ssid, char *password, uint8_t auth );

/**
 * @brief WiFi 10 station disconnect function.
 * @details Disconnects the station and waits for the firmware disconnect event.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @return @li @c 0 - Disconnected,
 *         @li @c <0 - Command, transport, or timeout error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note Close sockets before disconnecting.
 */
err_t wifi10_disconnect ( wifi10_t *ctx );

/**
 * @brief WiFi 10 DHCP function.
 * @details Starts DHCP and queries the firmware for the IPv4 configuration if the start reply omits it.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[out] ip : IPv4 configuration, updated only on success.
 * See #wifi10_ip_cfg_t object definition for detailed explanation.
 * @return @li @c 0 - Nonzero IPv4 address obtained,
 *         @li @c <0 - Disconnect, command, transport, or timeout error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note Requires station association. Address values are in host numeric order. A timeout requires hardware reset.
 */
err_t wifi10_dhcp ( wifi10_t *ctx, wifi10_ip_cfg_t *ip );

/**
 * @brief WiFi 10 socket open function.
 * @details Opens an IPv4 TCP or UDP socket.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] type : WIFI10_SOCKET_TCP or WIFI10_SOCKET_UDP.
 * @param[out] handle : Firmware socket handle, updated only on success.
 * @return @li @c 0 - Socket opened,
 *         @li @c <0 - No slot, command, transport, or timeout error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note Up to WIFI10_MAX_SOCKETS may be open simultaneously.
 */
err_t wifi10_socket_open ( wifi10_t *ctx, uint8_t type, int32_t *handle );

/**
 * @brief WiFi 10 TCP socket connection function.
 * @details Connects an open TCP socket to a remote IPv4 endpoint.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] handle : Open TCP socket handle.
 * @param[in] address : Remote IPv4 address in host numeric order.
 * @param[in] port : Remote port, 1-65535.
 * @return @li @c 0 - Connected,
 *         @li @c <0 - Invalid socket, command, transport, or timeout error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note A host timeout does not cancel the firmware command; reset before reuse.
 */
err_t wifi10_socket_connect ( wifi10_t *ctx, int32_t handle, uint32_t address, uint16_t port );

/**
 * @brief WiFi 10 TCP send function.
 * @details Transfers 1-WIFI10_MAX_PAYLOAD bytes to the module for an established TCP socket.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] handle : Connected TCP socket handle.
 * @param[in] payload : Bytes to send.
 * @param[in] length : Number of bytes.
 * @return @li @c 0 - Complete frame transferred to the module,
 *         @li @c <0 - Socket, transport, credit, or timeout error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note Success does not confirm delivery to the peer. Larger streams require multiple calls.
 */
err_t wifi10_socket_send ( wifi10_t *ctx, int32_t handle, uint8_t *payload, uint16_t length );

/**
 * @brief WiFi 10 UDP send function.
 * @details Transfers one 1-WIFI10_MAX_PAYLOAD byte UDP datagram to the module.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] handle : Open UDP socket handle.
 * @param[in] payload : Bytes to send.
 * @param[in] length : Datagram size.
 * @param[in] address : Destination IPv4 address in host numeric order.
 * @param[in] port : Destination port, 1-65535.
 * @return @li @c 0 - Complete frame transferred to the module,
 *         @li @c <0 - Socket, transport, credit, or timeout error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note Success does not confirm delivery to the peer.
 */
err_t wifi10_socket_sendto ( wifi10_t *ctx, int32_t handle, uint8_t *payload, uint16_t length,
                             uint32_t address, uint16_t port );

/**
 * @brief WiFi 10 socket receive function.
 * @details Polls for socket bytes; TCP preserves unread bytes and UDP preserves datagram boundaries.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] handle : Open socket handle.
 * @param[out] payload : Destination byte buffer.
 * @param[in] capacity : Buffer capacity in bytes, at least one.
 * @param[out] received : Bytes copied; set to zero before polling.
 * @param[in] timeout : Maximum polling delay budget in milliseconds; zero performs one poll.
 * @return @li @c 0 - Bytes or a zero-length UDP datagram received,
 *         @li @c -2 - No payload before the polling limit,
 *         @li @c -6 - UDP buffer too small; datagram retained,
 *         @li @c -8 - TCP peer closed and buffered bytes consumed,
 *         @li @c <0 - Other driver error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note Receive timeout is safe to retry. Other command timeouts require reset.
 * UDP sender information is retained in the matching state.sockets entry.
 */
err_t wifi10_socket_recv ( wifi10_t *ctx, int32_t handle, uint8_t *payload, uint16_t capacity,
                           uint16_t *received, uint32_t timeout );

/**
 * @brief WiFi 10 socket close function.
 * @details Closes a socket, waits for the matching firmware response, and releases its receive buffer.
 * @param[in,out] ctx : Click context object.
 * See #wifi10_t object definition for detailed explanation.
 * @param[in] handle : Open socket handle.
 * @return @li @c 0 - Closed,
 *         @li @c <0 - Invalid handle, command, transport, or timeout error.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note Also releases a socket already closed by the TCP peer.
 */
err_t wifi10_socket_close ( wifi10_t *ctx, int32_t handle );

#ifdef __cplusplus
}
#endif
#endif // WIFI10_H

/*! @} */ // wifi10

// ------------------------------------------------------------------------ END
