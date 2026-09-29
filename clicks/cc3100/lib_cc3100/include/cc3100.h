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
 * @file cc3100.h
 * @brief This file contains API for CC3100 Click Driver.
 */

#ifndef CC3100_H
#define CC3100_H

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
#include "drv_spi_master.h"
#include "drv_uart.h"
#include "spi_specifics.h"

/*!
 * @addtogroup cc3100 CC3100 Click Driver
 * @brief API for configuring and manipulating CC3100 Click driver.
 * @{
 */

/**
 * @defgroup cc3100_cmd CC3100 Commands
 * @brief SimpleLink commands used by CC3100 Click driver.
 * @{
 */

/**
 * @brief CC3100 SimpleLink command opcodes.
 * @details Define the binary device, WLAN, configuration, and IPv4 socket commands used by CC3100 Click.
 * Synchronous response opcodes are the command opcodes with bit 15 cleared.
 */
#define CC3100_CMD_STOP                  0x8473
#define CC3100_CMD_DEVICE_GET            0x8466
#define CC3100_CMD_NETCFG_SET            0x8432
#define CC3100_CMD_NETCFG_GET            0x8433
#define CC3100_CMD_WLAN_CONNECT          0x8C80
#define CC3100_CMD_WLAN_DISCONNECT       0x8C81
#define CC3100_CMD_WLAN_POLICY           0x8C86
#define CC3100_CMD_WLAN_MODE             0x8CB4
#define CC3100_CMD_SOCKET                0x9401
#define CC3100_CMD_CLOSE                 0x9402
#define CC3100_CMD_BIND                  0x9404
#define CC3100_CMD_CONNECT               0x9406
#define CC3100_CMD_SOCKET_OPTION         0x9408
#define CC3100_CMD_RECV                  0x940A
#define CC3100_CMD_RECVFROM              0x940B
#define CC3100_CMD_SEND                  0x940C
#define CC3100_CMD_SENDTO                0x940D

/**
 * @brief CC3100 SimpleLink event opcodes.
 * @details Define asynchronous device, WLAN, and socket events handled by CC3100 Click.
 */
#define CC3100_EVT_INIT                  0x0008
#define CC3100_EVT_ABORT                 0x000C
#define CC3100_EVT_FATAL                 0x0078
#define CC3100_EVT_STOP                  0x0073
#define CC3100_EVT_WLAN_CONNECTED        0x0880
#define CC3100_EVT_WLAN_DISCONNECTED     0x0881
#define CC3100_EVT_IP_ACQUIRED           0x1825
#define CC3100_EVT_IP_LOST               0x1832
#define CC3100_EVT_DHCP_TIMEOUT          0x1833
#define CC3100_EVT_SOCKET_CONNECT        0x1006
#define CC3100_EVT_SOCKET_RECV           0x100A
#define CC3100_EVT_SOCKET_RECVFROM       0x100B
#define CC3100_EVT_SOCKET_TX_FAILED      0x100E

/*! @} */ // cc3100_cmd

/**
 * @defgroup cc3100_set CC3100 Settings
 * @brief Settings for CC3100 Click driver.
 * @{
 */

/**
 * @brief CC3100 WLAN security settings.
 * @details Select open or WPA/WPA2-Personal authentication for CC3100 Click.
 * WPA3-only and enterprise networks are not supported by this driver.
 */
#define CC3100_SECURITY_OPEN             0
#define CC3100_SECURITY_WPA_WPA2         2

/**
 * @brief CC3100 socket protocol settings.
 * @details Select TCP stream or UDP datagram communication for the CC3100 Click IPv4 socket.
 */
#define CC3100_PROTOCOL_TCP              6
#define CC3100_PROTOCOL_UDP              17

/**
 * @brief CC3100 communication buffer sizes.
 * @details Define UART ring buffers, the SimpleLink response buffer, and the maximum application
 * payload per send or receive operation for CC3100 Click. Larger TCP messages require multiple calls.
 */
#define CC3100_TX_DRV_BUFFER_SIZE        256
#define CC3100_RX_DRV_BUFFER_SIZE        256
#define CC3100_RESPONSE_SIZE             512
#define CC3100_DATA_SIZE                 256
#define CC3100_SSID_SIZE                 32
#define CC3100_KEY_SIZE                  64

/**
 * @brief CC3100 response timeout.
 * @details Define the maximum polling wait in milliseconds for one CC3100 Click command response.
 * Transfer time is additional. Library waits use fixed one-millisecond delay calls.
 * @note TCP socket connection completion uses a separate, longer wait.
 */
#define CC3100_TIMEOUT_MS                5000

/**
 * @brief CC3100 data sample selection.
 * @details These macros select SPI data sampling for CC3100 Click.
 * @note Available only on Microchip PIC family devices; affects all SPI modules on the MCU.
 */
#define CC3100_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define CC3100_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // cc3100_set

/**
 * @defgroup cc3100_map CC3100 MikroBUS Map
 * @brief MikroBUS pin mapping of CC3100 Click driver.
 */

/**
 * @addtogroup cc3100_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of CC3100 Click to the selected MikroBUS.
 * @note J1A and J2A share the CS and INT pins between SPI and UART flow control.
 * Set both jumpers to positions 1-2 for SPI or 2-3 for UART before powering the board.
 */
#define CC3100_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.ncts    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.nrts    = MIKROBUS( mikrobus, MIKROBUS_INT ); \
    cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.hib     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // cc3100_map
/*! @} */ // cc3100

/**
 * @brief CC3100 Click driver interface selection.
 * @details Selects the host communication interface used by CC3100 Click.
 */
typedef enum
{
    CC3100_DRV_SEL_SPI,         /**< SPI driver descriptor (default). */
    CC3100_DRV_SEL_UART         /**< UART driver descriptor. */

} cc3100_drv_t;

/**
 * @brief CC3100 Click network status object.
 * @details Contains the latest asynchronous WLAN and DHCP state of CC3100 Click.
 * IPv4 addresses are stored in dotted-decimal byte order.
 */
typedef struct
{
    uint8_t connected;           /**< WLAN association established. */
    uint8_t ip_acquired;         /**< IPv4 address acquired. */
    uint8_t ip[ 4 ];             /**< Local IPv4 address. */
    uint8_t gateway[ 4 ];        /**< Default gateway address. */
    uint8_t dns[ 4 ];            /**< DNS server address. */

} cc3100_network_t;

/**
 * @brief CC3100 Click version object.
 * @details Contains hardware and firmware identification returned by CC3100 Click.
 */
typedef struct
{
    uint32_t chip_id;            /**< Silicon identifier. */
    uint32_t firmware[ 4 ];      /**< Firmware version components. */
    uint8_t phy[ 4 ];            /**< PHY version components. */
    uint32_t nwp[ 4 ];           /**< Network processor version components. */
    uint16_t rom;               /**< ROM version. */

} cc3100_version_t;

/**
 * @brief CC3100 Click received packet object.
 * @details Describes data received by CC3100 Click. For TCP, length is a stream chunk,
 * not a message boundary. For UDP, the source address belongs to the received datagram.
 */
typedef struct
{
    uint8_t ip[ 4 ];             /**< Remote IPv4 address. */
    uint16_t port;              /**< Remote port in host byte order. */
    uint16_t length;            /**< Number of bytes copied to the application buffer. */

} cc3100_packet_t;

/**
 * @brief CC3100 Click context object.
 * @details Context object definition of CC3100 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Active-low module reset. */
    digital_out_t hib;          /**< Active-low module hibernate control. */
    digital_out_t ncts;         /**< Module UART CTS input, driven by the host (active low). */

    // Input pins
    digital_in_t int_pin;       /**< Module host interrupt output (SPI mode). */
    digital_in_t nrts;          /**< Module UART RTS output, read by the host (active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */
    uart_t uart;               /**< UART driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

    // UART ring buffers
    uint8_t uart_tx_buffer[ CC3100_TX_DRV_BUFFER_SIZE ]; /**< UART transmit ring buffer. */
    uint8_t uart_rx_buffer[ CC3100_RX_DRV_BUFFER_SIZE ]; /**< UART receive ring buffer. */

    cc3100_drv_t drv_sel;       /**< Selected communication interface. */

    // SimpleLink state; use the public functions instead of modifying these fields.
    uint8_t ready;              /**< Startup completed and protocol synchronized. */
    uint8_t role;               /**< Current NWP role: 0 station, 1 P2P, 2 access point. */
    uint8_t rx_sequence;        /**< Expected response synchronization sequence. */
    uint8_t first_command;      /**< First SPI command still requires a settling delay. */
    uint8_t tx_credits;         /**< Available NWP transmit buffers. */
    uint8_t tx_failure;         /**< NWP socket transmission failure bitmap. */
    uint16_t response_opcode;   /**< Last decoded response opcode, or zero before receiving a header. */
    uint16_t response_length;   /**< Unpadded response payload length. */
    uint8_t response[ CC3100_RESPONSE_SIZE ]; /**< Last complete response payload. */
    int16_t module_error;       /**< Last signed status returned by the NWP. */
    int16_t socket_id;          /**< Active socket descriptor, or -1 when closed. */
    uint8_t protocol;           /**< Active socket protocol. */
    uint8_t peer_ip[ 4 ];       /**< Configured remote IPv4 address. */
    uint16_t peer_port;         /**< Configured remote port in host byte order. */
    cc3100_network_t network;   /**< Latest WLAN and IPv4 status. */

} cc3100_t;

/**
 * @brief CC3100 Click configuration object.
 * @details Configuration object definition of CC3100 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t tx_pin;          /**< Host UART transmit pin, connected to module RX. */
    pin_name_t rx_pin;          /**< Host UART receive pin, connected to module TX. */
    pin_name_t ncts;            /**< Module CTS pin descriptor (host output, UART mode). */
    pin_name_t nrts;            /**< Module RTS pin descriptor (host input, UART mode). */

    // Additional gpio pins
    pin_name_t rst;             /**< Active-low module reset pin descriptor. */
    pin_name_t hib;             /**< Active-low module hibernate pin descriptor. */
    pin_name_t int_pin;         /**< Host interrupt pin descriptor (SPI mode). */

    // SPI settings
    uint32_t                          spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity; /**< Chip select pin polarity. */

    // UART settings
    uint32_t         baud_rate;     /**< UART baud rate (115200 by default). */
    uart_data_bits_t data_bit;      /**< UART data bits (8 by default). */
    uart_parity_t    parity_bit;    /**< UART parity (none by default). */
    uart_stop_bits_t stop_bit;      /**< UART stop bits (1 by default). */

    cc3100_drv_t drv_sel;           /**< Selected communication interface (SPI by default). */

} cc3100_cfg_t;

/**
 * @brief CC3100 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CC3100_OK = 0,              /**< Operation completed. */
    CC3100_NO_DATA = 1,         /**< No event or socket data is available yet. */
    CC3100_ERROR = -1,          /**< Communication peripheral error. */
    CC3100_TIMEOUT = -2,        /**< Bounded response wait expired; reset is required. */
    CC3100_PROTOCOL_ERROR = -3, /**< Invalid or unexpected SimpleLink response. */
    CC3100_ARGUMENT_ERROR = -4, /**< Invalid parameter or unsupported configuration. */
    CC3100_MODULE_ERROR = -5,   /**< NWP rejected an operation; inspect module_error. */
    CC3100_BUFFER_ERROR = -6,   /**< Received payload exceeds the supported buffer. */
    CC3100_CLOSED = -7          /**< TCP peer closed its sending direction. */

} cc3100_return_value_t;

/*!
 * @addtogroup cc3100 CC3100 Click Driver
 * @brief API for configuring and manipulating CC3100 Click driver.
 * @{
 */

/**
 * @brief CC3100 Click configuration object setup function.
 * @details This function initializes the configuration of CC3100 Click with SPI and 115200-baud UART defaults.
 * @param[out] cfg : Click configuration structure.
 * See #cc3100_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note All pins are initially unconnected. UART defaults to 8 data bits, no parity, and one stop bit.
 */
void cc3100_cfg_setup ( cc3100_cfg_t *cfg );

/**
 * @brief CC3100 Click driver interface setup function.
 * @details This function selects the serial interface used by CC3100 Click.
 * @param[out] cfg : Click configuration structure.
 * See #cc3100_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #cc3100_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note Call before initialization. Set J1A/J2A to 1-2 for SPI or 2-3 for UART.
 */
void cc3100_drv_interface_sel ( cc3100_cfg_t *cfg, cc3100_drv_t drv_sel );

/**
 * @brief CC3100 Click initialization function.
 * @details This function initializes the selected peripheral and control pins of CC3100 Click.
 * @param[out] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #cc3100_cfg_t object definition for detailed explanation.
 * @return CC3100_OK on success, or a negative error code.
 * See #cc3100_return_value_t definition for detailed explanation.
 * @note The NWP remains disabled until reset or default configuration. UART is nonblocking internally.
 */
err_t cc3100_init ( cc3100_t *ctx, cc3100_cfg_t *cfg );

/**
 * @brief CC3100 Click reset function.
 * @details This function restarts CC3100 Click and waits for the SimpleLink initialization event.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return CC3100_OK on success, or a negative error code.
 * See #cc3100_return_value_t definition for detailed explanation.
 * @note Closes the active socket and clears cached network state without erasing saved profiles.
 */
err_t cc3100_reset ( cc3100_t *ctx );

/**
 * @brief CC3100 Click default configuration function.
 * @details This function configures CC3100 Click for station operation with DHCP and manual WLAN connection.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return CC3100_OK on success, or a negative error code.
 * See #cc3100_return_value_t definition for detailed explanation.
 * @note Waits for the NWP shutdown acknowledgement before restarting to apply settings.
 * Existing WLAN profiles are not erased.
 */
err_t cc3100_default_cfg ( cc3100_t *ctx );

/**
 * @brief CC3100 Click firmware version read function.
 * @details This function reads the CC3100 Click silicon, firmware, PHY, NWP, and ROM versions.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[out] version : Pointer to the version object.
 * See #cc3100_version_t object definition for detailed explanation.
 * @return CC3100_OK on success, or a negative error code.
 * See #cc3100_return_value_t definition for detailed explanation.
 * @note Requires successful startup.
 */
err_t cc3100_get_version ( cc3100_t *ctx, cc3100_version_t *version );

/**
 * @brief CC3100 Click MAC address read function.
 * @details This function reads the six-byte MAC address of CC3100 Click.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[out] mac : Pointer to a buffer of at least six bytes.
 * @return CC3100_OK on success, or a negative error code.
 * See #cc3100_return_value_t definition for detailed explanation.
 * @note Requires successful startup.
 */
err_t cc3100_get_mac ( cc3100_t *ctx, uint8_t *mac );

/**
 * @brief CC3100 Click WLAN connection function.
 * @details This function requests a CC3100 Click connection to an open or WPA/WPA2-Personal WLAN.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in] ssid : Null-terminated SSID, from 1 to CC3100_SSID_SIZE bytes.
 * @param[in] password : Null-terminated key, or NULL for an open network.
 * @param[in] security : CC3100_SECURITY_OPEN or CC3100_SECURITY_WPA_WPA2.
 * @return CC3100_OK on success, or a negative error code.
 * See #cc3100_return_value_t definition for detailed explanation.
 * @note Success means the request was accepted. Call cc3100_process until network.ip_acquired is set.
 * Credentials are sent to the NWP but are not added to the persistent profile list.
 */
err_t cc3100_connect ( cc3100_t *ctx, char *ssid, char *password, uint8_t security );

/**
 * @brief CC3100 Click WLAN disconnection function.
 * @details This function requests disconnection of CC3100 Click from the current WLAN.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return CC3100_OK on success, or a negative error code.
 * See #cc3100_return_value_t definition for detailed explanation.
 * @note The disconnection event clears the cached network state. Close the socket before disconnecting.
 */
err_t cc3100_disconnect ( cc3100_t *ctx );

/**
 * @brief CC3100 Click event processing function.
 * @details This function receives one pending SimpleLink frame and updates CC3100 Click network state.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return CC3100_OK for a processed event, CC3100_NO_DATA when idle, or a negative error code.
 * See #cc3100_return_value_t definition for detailed explanation.
 * @note Call regularly while idle. Once a frame starts, its reception uses a bounded wait.
 * Do not call driver functions concurrently or from an interrupt handler.
 */
err_t cc3100_process ( cc3100_t *ctx );

/**
 * @brief CC3100 Click socket open function.
 * @details This function creates one nonblocking IPv4 TCP or UDP socket on CC3100 Click.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in] protocol : CC3100_PROTOCOL_TCP or CC3100_PROTOCOL_UDP.
 * @param[in] local_port : Local UDP port; zero selects an ephemeral port. Ignored for TCP.
 * @param[in] peer_ip : Remote IPv4 address in dotted-decimal byte order.
 * @param[in] peer_port : Remote TCP or UDP port in host byte order.
 * @return CC3100_OK on success, or a negative error code.
 * See #cc3100_return_value_t definition for detailed explanation.
 * @note Requires an acquired IPv4 address. TCP also establishes a connection to the peer.
 * TCP connection completion has a 30-second polling budget after the command acknowledgement.
 * The driver supports one active socket per context.
 */
err_t cc3100_open_socket ( cc3100_t *ctx, uint8_t protocol, uint16_t local_port,
                           uint8_t *peer_ip, uint16_t peer_port );

/**
 * @brief CC3100 Click socket close function.
 * @details This function closes the active CC3100 Click socket.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return CC3100_OK on success, or a negative error code.
 * See #cc3100_return_value_t definition for detailed explanation.
 * @note Calling this function when no socket is open succeeds without sending a command.
 */
err_t cc3100_close_socket ( cc3100_t *ctx );

/**
 * @brief CC3100 Click socket send function.
 * @details This function sends application data to the peer configured for the CC3100 Click socket.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Payload length, from 1 to CC3100_DATA_SIZE bytes.
 * @return CC3100_OK when queued, CC3100_NO_DATA when NWP buffers are busy, or a negative error code.
 * See #cc3100_return_value_t definition for detailed explanation.
 * @note Success confirms submission to the NWP, not delivery to the peer. No terminator is added.
 */
err_t cc3100_send ( cc3100_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief CC3100 Click socket receive function.
 * @details This function receives a TCP stream chunk or UDP datagram from the CC3100 Click socket.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to the application receive buffer.
 * @param[in] len : Buffer capacity, from 1 to CC3100_DATA_SIZE bytes.
 * @param[out] packet : Pointer to the received packet information.
 * See #cc3100_packet_t object definition for detailed explanation.
 * @return CC3100_OK when data is received, CC3100_NO_DATA when idle, CC3100_CLOSED on TCP EOF,
 * or a negative error code. See #cc3100_return_value_t definition for detailed explanation.
 * @note No null terminator is added. TCP may split or combine messages.
 * UDP datagrams larger than len return CC3100_BUFFER_ERROR.
 */
err_t cc3100_receive ( cc3100_t *ctx, uint8_t *data_out, uint16_t len, cc3100_packet_t *packet );

/**
 * @brief CC3100 Click UART CTS control function.
 * @details This function controls the CC3100 Click module nCTS input in UART mode.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in] state : Pin level; 0 allows module transmission and 1 stops it.
 * @return Nothing.
 * @note Protocol functions manage this signal automatically. Has no effect in SPI mode.
 */
void cc3100_set_ncts ( cc3100_t *ctx, uint8_t state );

/**
 * @brief CC3100 Click UART RTS read function.
 * @details This function reads the CC3100 Click module nRTS output in UART mode.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return 0 when the module can receive data, or 1 when it cannot.
 * @note Protocol functions check this signal automatically. Returns 1 in SPI mode.
 */
uint8_t cc3100_get_nrts ( cc3100_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CC3100_H

/*! @} */ // cc3100

// ------------------------------------------------------------------------ END
