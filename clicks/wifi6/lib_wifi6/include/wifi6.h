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
 * @file wifi6.h
 * @brief This file contains API for WiFi 6 Click Driver.
 */

#ifndef WIFI6_H
#define WIFI6_H

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

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup wifi6 WiFi 6 Click Driver
 * @brief API for configuring and manipulating WiFi 6 Click driver.
 * @{
 */

/**
 * @defgroup wifi6_cmd WiFi 6 Commands
 * @brief BGAPI commands used by WiFi 6 Click driver.
 * @{
 */

/**
 * @brief WiFi 6 BGAPI command classes.
 * @details These macros identify the WF121 system, configuration, WLAN, TCP/IP, and endpoint classes.
 */
#define WIFI6_CLASS_SYSTEM              0x01
#define WIFI6_CLASS_CONFIG              0x02
#define WIFI6_CLASS_SME                 0x03
#define WIFI6_CLASS_TCPIP               0x04
#define WIFI6_CLASS_ENDPOINT            0x05

/**
 * @brief WiFi 6 system and configuration commands.
 * @details These macros select software reset, command checking, power management, and MAC address reading.
 */
#define WIFI6_CMD_RESET                 0x01
#define WIFI6_CMD_HELLO                 0x02
#define WIFI6_CMD_POWER_SAVE            0x03
#define WIFI6_CMD_GET_MAC               0x00

/**
 * @brief WiFi 6 WLAN commands.
 * @details These macros select radio startup, password setting, SSID connection, and station mode.
 */
#define WIFI6_CMD_WIFI_ON               0x00
#define WIFI6_CMD_SET_PASSWORD          0x05
#define WIFI6_CMD_CONNECT_SSID          0x07
#define WIFI6_CMD_SET_MODE              0x0A

/**
 * @brief WiFi 6 socket commands.
 * @details These macros select TCP/UDP endpoint creation, DHCP configuration, UDP source-port binding,
 * endpoint transmission, and endpoint closing.
 */
#define WIFI6_CMD_TCP_CONNECT           0x01
#define WIFI6_CMD_UDP_SERVER            0x02
#define WIFI6_CMD_UDP_CONNECT           0x03
#define WIFI6_CMD_IP_CONFIG             0x04
#define WIFI6_CMD_UDP_BIND              0x07
#define WIFI6_CMD_SEND                  0x00
#define WIFI6_CMD_CLOSE                 0x04

/*! @} */ // wifi6_cmd

/**
 * @defgroup wifi6_set WiFi 6 Settings
 * @brief Settings of WiFi 6 Click driver.
 * @{
 */

/**
 * @brief WiFi 6 transport identifiers.
 * @details The transport values are IP protocol numbers selecting TCP stream or UDP datagram communication.
 * WIFI6_ENDPOINT_INVALID marks an endpoint not yet allocated by the module.
 */
#define WIFI6_PROTOCOL_TCP              6
#define WIFI6_PROTOCOL_UDP              17
#define WIFI6_ENDPOINT_INVALID          0xFF

/**
 * @brief WiFi 6 communication buffer sizes.
 * @details These macros define UART ring buffers, the BGAPI frame buffer, and the application payload limit.
 * Received TCP chunks are accumulated up to WIFI6_DATA_SIZE bytes; one UDP datagram can be pending.
 */
#define WIFI6_TX_DRV_BUFFER_SIZE        64
#define WIFI6_RX_DRV_BUFFER_SIZE        512
#define WIFI6_FRAME_SIZE                512
#define WIFI6_DATA_SIZE                 255
#define WIFI6_SSID_SIZE                 32
#define WIFI6_PASSWORD_SIZE             64

/**
 * @brief WiFi 6 polling timeouts.
 * @details These macros define one-millisecond polling budgets for commands, incomplete frames,
 * and TCP/UDP endpoint activation. UART transfer time is additional.
 */
#define WIFI6_TIMEOUT_MS                5000
#define WIFI6_FRAME_TIMEOUT_MS          1000
#define WIFI6_CONNECT_TIMEOUT_MS        30000

/*! @} */ // wifi6_set

/**
 * @defgroup wifi6_map WiFi 6 MikroBUS Map
 * @brief MikroBUS pin mapping of WiFi 6 Click driver.
 * @{
 */

/**
 * @brief WiFi 6 MikroBUS pin mapping.
 * @details This macro maps WiFi 6 Click UART and flow-control pins to the selected MikroBUS.
 * @note Set all four IO SEL jumpers to UART. CTS is a module input driven by the host on INT;
 * RTS is a module output read by the host on CS. Module reset is only on the programming connector.
 */
#define WIFI6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // wifi6_map
/*! @} */ // wifi6

/**
 * @brief WiFi 6 Click firmware version object.
 * @details This object contains the firmware version received in the WF121 boot event.
 */
typedef struct
{
    uint16_t major;       /**< Major release number. */
    uint16_t minor;       /**< Minor release number. */
    uint16_t patch;       /**< Patch release number. */
    uint16_t build;       /**< Firmware build number. */

} wifi6_version_t;

/**
 * @brief WiFi 6 Click network status object.
 * @details This object contains cached WLAN and DHCP status. IPv4 addresses use dotted-decimal byte order.
 */
typedef struct
{
    uint8_t connected;    /**< Association with an access point is established. */
    uint8_t up;           /**< Network interface reports that it is ready. */
    uint8_t ip_acquired;  /**< A nonzero IPv4 address has been received. */
    uint8_t ip[ 4 ];      /**< Local IPv4 address. */
    uint8_t netmask[ 4 ]; /**< Local IPv4 subnet mask. */
    uint8_t gateway[ 4 ]; /**< Default gateway address. */

} wifi6_network_t;

/**
 * @brief WiFi 6 Click received packet object.
 * @details This object describes a received TCP stream chunk or UDP datagram from the configured peer.
 */
typedef struct
{
    uint16_t length;      /**< Number of bytes copied to the output buffer. */
    uint8_t ip[ 4 ];      /**< Remote IPv4 address. */
    uint16_t port;        /**< Remote port in host byte order. */

} wifi6_packet_t;

/**
 * @brief WiFi 6 Click context object.
 * @details Context object definition of WiFi 6 Click driver.
 */
typedef struct
{
    // Signal directions are relative to the WF121 module.
    digital_out_t cts;      /**< Active-low permission for module TX; host output on MikroBUS INT. */
    digital_in_t rts;       /**< Active-low module TX-ready signal; host input on MikroBUS CS. */
    uart_t uart;            /**< UART driver object. */

    uint8_t uart_rx_buffer[ WIFI6_RX_DRV_BUFFER_SIZE ]; /**< UART receive ring buffer. */
    uint8_t uart_tx_buffer[ WIFI6_TX_DRV_BUFFER_SIZE ]; /**< UART transmit ring buffer. */

    wifi6_version_t version; /**< Firmware version reported by the latest boot event. */
    wifi6_network_t network; /**< Cached WLAN association, interface, and IPv4 state. */
    uint8_t mac[ 6 ];        /**< Factory MAC address reported by the module. */
    uint16_t module_error;   /**< Last module result or asynchronous endpoint error. */

    // Driver-managed protocol state. Applications should use the public API instead of editing these fields.
    uint8_t ready;          /**< A valid module boot event has been received. */
    uint8_t radio_on;       /**< The radio-ready event has been received. */
    uint8_t mac_valid;      /**< A MAC address event has been received. */
    uint8_t protocol;       /**< Active TCP or UDP transport identifier. */
    uint8_t tx_endpoint;    /**< Transmit endpoint, or WIFI6_ENDPOINT_INVALID. */
    uint8_t rx_endpoint;    /**< TCP endpoint or separate UDP listener endpoint. */
    uint8_t peer_ip[ 4 ];   /**< Configured peer IPv4 address, in network byte order. */
    uint16_t peer_port;     /**< Configured peer port, in host byte order. */
    uint8_t ep_active[ 32 ]; /**< Activation state for 256 possible BGAPI endpoint identifiers. */
    uint8_t ep_closed[ 32 ]; /**< Closed state, including events received before endpoint assignment. */
    uint8_t frame[ WIFI6_FRAME_SIZE ]; /**< Shared BGAPI payload buffer for command arguments and received frames. */
    uint16_t frame_len;     /**< Payload length decoded from the BGAPI header. */
    uint8_t frame_class;    /**< BGAPI class of the most recently read frame. */
    uint8_t frame_id;       /**< Command or event identifier of the most recently read frame. */
    uint8_t frame_event;    /**< Nonzero when the most recently read frame is an asynchronous event. */
    uint8_t rx_data[ WIFI6_DATA_SIZE ]; /**< Application data queued while processing BGAPI traffic. */
    uint16_t rx_length;     /**< Number of queued application bytes. */
    uint8_t rx_pending;     /**< A TCP chunk or UDP datagram is queued for wifi6_receive. */

} wifi6_t;

/**
 * @brief WiFi 6 Click configuration object.
 * @details Configuration object definition of WiFi 6 Click driver.
 */
typedef struct
{
    pin_name_t rx_pin;           /**< Host UART RX connected to module TX. */
    pin_name_t tx_pin;           /**< Host UART TX connected to module RX. */
    pin_name_t rts;              /**< Module RTS on MikroBUS CS; host input. */
    pin_name_t cts;              /**< Module CTS on MikroBUS INT; host output. */
    uint32_t baud_rate;          /**< UART baud rate; factory firmware uses 115200. */
    uart_data_bits_t data_bit;   /**< UART data bits; factory firmware uses 8. */
    uart_parity_t parity_bit;    /**< UART parity; factory firmware uses none. */
    uart_stop_bits_t stop_bit;   /**< UART stop bits; factory firmware uses 1. */
    bool uart_blocking;          /**< UART wait for interrupt or not. */

} wifi6_cfg_t;

/**
 * @brief WiFi 6 Click return codes.
 * @details These values distinguish success, pending data, transport errors, timeouts, and module errors.
 */
typedef enum
{
    WIFI6_OK = 0,              /**< Operation completed. */
    WIFI6_NO_DATA = 1,         /**< No application data or event is currently available. */
    WIFI6_ERROR = -1,          /**< UART communication error. */
    WIFI6_TIMEOUT = -2,        /**< A bounded response or flow-control wait expired. */
    WIFI6_PROTOCOL_ERROR = -3, /**< Invalid BGAPI frame or unexpected response. */
    WIFI6_ARGUMENT_ERROR = -4, /**< Invalid parameter or operation order. */
    WIFI6_MODULE_ERROR = -5,   /**< Module reported an error; inspect module_error. */
    WIFI6_BUFFER_ERROR = -6,   /**< Frame, packet, or queued data exceeds the buffer capacity. */
    WIFI6_CLOSED = -7,         /**< The active endpoint is closing. */
    WIFI6_RESTARTED = -8       /**< An unexpected module boot occurred. */

} wifi6_return_value_t;

/*!
 * @addtogroup wifi6 WiFi 6 Click Driver
 * @brief API for configuring and manipulating WiFi 6 Click driver.
 * @{
 */

/**
 * @brief WiFi 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial values.
 * @param[out] cfg : Click configuration structure.
 * See #wifi6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note All pins are unconnected; UART defaults to 115200 baud, 8 data bits, no parity, and one stop bit.
 */
void wifi6_cfg_setup ( wifi6_cfg_t *cfg );

/**
 * @brief WiFi 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used for this Click board.
 * @param[out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #wifi6_cfg_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c !=0 - Error.
 * See #err_t definition for detailed explanation.
 * @note BGAPI reads use nonblocking UART with bounded waits. CTS pauses module output between reads.
 */
err_t wifi6_init ( wifi6_t *ctx, wifi6_cfg_t *cfg );

/**
 * @brief WiFi 6 default configuration function.
 * @details This function resets the module, selects station mode with DHCP, starts the radio,
 * and reads its MAC address.
 * @param[in] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Waits for boot, radio-ready, and MAC events. The WLAN connection is requested separately.
 */
err_t wifi6_default_cfg ( wifi6_t *ctx );

/**
 * @brief WiFi 6 module reset and readiness function.
 * @details This function uses the initial power-on boot event when available; otherwise it sends a
 * BGAPI software reset and waits for a fresh boot event.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note A valid cold-start boot event avoids a redundant reset. Hardware MCLR is not routed to MikroBUS RST.
 */
err_t wifi6_reset ( wifi6_t *ctx );

/**
 * @brief WiFi 6 WLAN connection function.
 * @details This function sets the network password and requests connection to the specified SSID.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in] ssid : Null-terminated network name, up to 32 bytes.
 * @param[in] password : Null-terminated password; use an empty string for an open network.
 * @return @li @c 0 - Connection request accepted,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Call wifi6_process until network.up and network.ip_acquired are set before opening a socket.
 */
err_t wifi6_connect ( wifi6_t *ctx, char *ssid, char *password );

/**
 * @brief WiFi 6 event processing function.
 * @details This function reads one BGAPI frame and updates cached network, endpoint, and received-data state.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Event processed,
 *         @li @c 1 - No event available,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Poll regularly. An incomplete frame uses a bounded wait; driver calls must not run concurrently.
 */
err_t wifi6_process ( wifi6_t *ctx );

/**
 * @brief WiFi 6 socket opening function.
 * @details This function opens a TCP connection or a paired UDP transmit endpoint and receive listener.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in] protocol : WIFI6_PROTOCOL_TCP or WIFI6_PROTOCOL_UDP.
 * @param[in] local_port : Nonzero UDP listening and source port; ignored for TCP.
 * @param[in] peer_ip : Remote IPv4 address in dotted-decimal byte order.
 * @param[in] peer_port : Nonzero remote TCP or UDP port.
 * @return @li @c 0 - Endpoints are ready,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note One logical socket is supported. Close it before opening another.
 * UDP uses two WF121 endpoints because a UDP client endpoint does not receive replies by itself.
 * If opening fails, reset the module before retrying to release any partially allocated endpoints.
 */
err_t wifi6_open_socket ( wifi6_t *ctx, uint8_t protocol, uint16_t local_port,
                          uint8_t *peer_ip, uint16_t peer_port );

/**
 * @brief WiFi 6 socket transmission function.
 * @details This function sends application data through the active TCP or UDP transmit endpoint.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in] data_in : Input data buffer.
 * @param[in] len : Number of bytes to send, from 1 to WIFI6_DATA_SIZE.
 * @return @li @c 0 - Data accepted by the module,
 *         @li @c 1 - Endpoint temporarily inactive; retry later,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Success does not confirm remote delivery. No terminator is added to the transmitted data.
 */
err_t wifi6_send ( wifi6_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief WiFi 6 socket reception function.
 * @details This function reads queued TCP stream bytes or one UDP datagram from the configured peer.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[out] data_out : Output data buffer.
 * @param[in] capacity : Output buffer capacity in bytes.
 * @param[out] packet : Received length and remote endpoint information.
 * See #wifi6_packet_t object definition for detailed explanation.
 * @return @li @c 0 - Data received,
 *         @li @c 1 - No data available,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note TCP messages may span reads. UDP datagrams are never truncated. No null terminator is added.
 */
err_t wifi6_receive ( wifi6_t *ctx, uint8_t *data_out, uint16_t capacity, wifi6_packet_t *packet );

/**
 * @brief WiFi 6 socket closing function.
 * @details This function closes the active TCP endpoint or both endpoints belonging to the UDP socket.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Socket closed or already closed,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Also acknowledges a remotely closed TCP endpoint so its identifier can be reused.
 */
err_t wifi6_close_socket ( wifi6_t *ctx );

/**
 * @brief WiFi 6 data writing function.
 * @details This function writes bytes over UART while respecting the module RTS signal.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in] data_in : Input data buffer.
 * @param[in] len : Number of bytes to send.
 * @return @li @c >=0 - Number of bytes written,
 *         @li @c <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note Bytes are paced because the UART ring buffer does not provide hardware RTS/CTS handshaking.
 * Do not interleave raw writes with a BGAPI command transaction.
 */
err_t wifi6_generic_write ( wifi6_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief WiFi 6 data reading function.
 * @details This function reads available UART bytes while allowing the module to transmit.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Output buffer capacity in bytes.
 * @return @li @c >=0 - Number of bytes read,
 *         @li @c <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note Raw reads consume protocol bytes; use wifi6_receive for application data after BGAPI startup.
 */
err_t wifi6_generic_read ( wifi6_t *ctx, uint8_t *data_out, uint16_t len );

#ifdef __cplusplus
}
#endif
#endif // WIFI6_H

/*! @} */ // wifi6

// ------------------------------------------------------------------------ END
