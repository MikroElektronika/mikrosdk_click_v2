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
 * @file vedasl917ext.h
 * @brief This file contains API for Veda SL917 EXT Click Driver.
 */

#ifndef VEDASL917EXT_H
#define VEDASL917EXT_H

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
#include "spi_specifics.h"

/*!
 * @addtogroup vedasl917ext Veda SL917 EXT Click Driver
 * @brief API for configuring and manipulating Veda SL917 EXT Click driver.
 * @{
 */

/**
 * @defgroup vedasl917ext_reg Veda SL917 EXT Registers List
 * @brief List of registers of Veda SL917 EXT Click driver.
 */

/**
 * @addtogroup vedasl917ext_reg
 * @{
 */

/**
 * @brief Veda SL917 EXT SPI interface registers.
 * @details Specified register addresses for SPI interrupt status and mode control.
 */
#define VEDASL917EXT_REG_INTERRUPT          0x00
#define VEDASL917EXT_REG_SPI_MODE           0x08

/**
 * @brief Veda SL917 EXT bootloader registers.
 * @details Specified memory addresses for the interrupt mask and host interface registers.
 */
#define VEDASL917EXT_MEM_INT_MASK           0x41050000ul
#define VEDASL917EXT_MEM_HOST_IN            0x41050034ul
#define VEDASL917EXT_MEM_HOST_OUT           0x4105003Cul

/*! @} */ // vedasl917ext_reg

/**
 * @defgroup vedasl917ext_set Veda SL917 EXT Registers Settings
 * @brief Settings for registers and commands of Veda SL917 EXT Click driver.
 */

/**
 * @addtogroup vedasl917ext_set
 * @{
 */

/**
 * @brief Veda SL917 EXT NCP commands.
 * @details Specified identifiers for WLAN requests and the card ready indication.
 */
#define VEDASL917EXT_CMD_OPERMODE           0x0010
#define VEDASL917EXT_CMD_BAND               0x0011
#define VEDASL917EXT_CMD_INIT               0x0012
#define VEDASL917EXT_CMD_SCAN               0x0013
#define VEDASL917EXT_CMD_JOIN               0x0014
#define VEDASL917EXT_CMD_DISCONNECT         0x0019
#define VEDASL917EXT_CMD_IPV4               0x0041
#define VEDASL917EXT_CMD_SOCKET_OPEN        0x0042
#define VEDASL917EXT_CMD_SOCKET_CLOSE       0x0043
#define VEDASL917EXT_CMD_MAC_ADDRESS        0x004A
#define VEDASL917EXT_EVT_SOCKET_CLOSED      0x0062
#define VEDASL917EXT_CMD_CARD_READY         0x0089
#define VEDASL917EXT_CMD_PSK                0x00A5
#define VEDASL917EXT_CMD_FEATURE            0x00C8
#define VEDASL917EXT_CMD_FW_VERSION         0x00E0

/**
 * @brief Veda SL917 EXT SPI and WLAN frame settings.
 * @details Specified clock rates in Hz, WLAN queue, interrupt flags, and frame sizes in bytes.
 */
#define VEDASL917EXT_SPI_DEFAULT_SPEED      1000000ul
#define VEDASL917EXT_SPI_MAX_SPEED          25000000ul
#define VEDASL917EXT_QUEUE_WLAN             4
#define VEDASL917EXT_INT_BUFFER_FULL        0x01
#define VEDASL917EXT_INT_RX_PENDING         0x08
#define VEDASL917EXT_FRAME_DESC_SIZE        16
#define VEDASL917EXT_FRAME_MAX_PAYLOAD      4095
#define VEDASL917EXT_RX_BUFFER_SIZE         1024

/**
 * @brief Veda SL917 EXT Wi-Fi scan settings.
 * @details Specified address, SSID, and scan record sizes, result limit, and channel selection values.
 */
#define VEDASL917EXT_MAC_SIZE               6
#define VEDASL917EXT_SSID_SIZE              32
#define VEDASL917EXT_SCAN_MAX_AP            11
#define VEDASL917EXT_SCAN_HEADER_SIZE       8
#define VEDASL917EXT_SCAN_RECORD_SIZE       46
#define VEDASL917EXT_SCAN_ALL_CHANNELS      0
#define VEDASL917EXT_SCAN_LAST_CHANNEL      14

/**
 * @brief Veda SL917 EXT station and socket settings.
 * @details Specified station authentication modes, socket types, and socket buffer limits.
 */
#define VEDASL917EXT_WIFI_OPEN              0
#define VEDASL917EXT_WIFI_WPA2              2
#define VEDASL917EXT_IPV4_SIZE              4
#define VEDASL917EXT_SOCKET_TCP             0
#define VEDASL917EXT_SOCKET_UDP             1
#define VEDASL917EXT_SOCKET_TX_MAX          512

/**
 * @brief Bounded polling limits.
 * @details Counts of polls separated by fixed one-millisecond delays.
 * SPI transfers and processing add to the elapsed time.
 */
#define VEDASL917EXT_SPI_INIT_POLLS         100
#define VEDASL917EXT_SPI_BUSY_POLLS         100
#define VEDASL917EXT_TOKEN_POLLS            1000
#define VEDASL917EXT_BOOT_POLLS             4000
#define VEDASL917EXT_COMMAND_POLLS          3000
#define VEDASL917EXT_SCAN_POLLS             15000
#define VEDASL917EXT_JOIN_POLLS             30000
#define VEDASL917EXT_DHCP_POLLS             30000
#define VEDASL917EXT_SOCKET_OPEN_POLLS      30000

/**
 * @brief Default WLAN-only station configuration.
 * @details Uses the WiSeConnect Si917 NCP memory, crystal, and RF switch settings.
 * Power saving and GPIO sleep handshaking remain disabled.
 */
#define VEDASL917EXT_FEATURE_OPEN           0x00000001ul
#define VEDASL917EXT_FEATURE_PSK            0x00000002ul
#define VEDASL917EXT_FEATURE_AGGREGATION    0x00000004ul
#define VEDASL917EXT_FEATURE_NEW_STATUS     0x00010000ul
#define VEDASL917EXT_TCPIP_DHCP             0x00000004ul
#define VEDASL917EXT_TCPIP_DNS              0x00000100ul
#define VEDASL917EXT_TCPIP_EXT_VALID        0x80000000ul
#define VEDASL917EXT_TCPIP_HOST_CLOSE       0x00010000ul
#define VEDASL917EXT_CUSTOM_EXT_VALID       0x80000000ul
#define VEDASL917EXT_EXT_NCP_MEMORY         0x00300000ul
#define VEDASL917EXT_EXT_XTAL               0x00400000ul
#define VEDASL917EXT_EXT_RF_SWITCH          0x20000000ul

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b vedasl917ext_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define VEDASL917EXT_SET_DATA_SAMPLE_EDGE   SET_SPI_DATA_SAMPLE_EDGE
#define VEDASL917EXT_SET_DATA_SAMPLE_MIDDLE SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // vedasl917ext_set

/**
 * @defgroup vedasl917ext_map Veda SL917 EXT MikroBUS Map
 * @brief MikroBUS pin mapping of Veda SL917 EXT Click driver.
 */

/**
 * @addtogroup vedasl917ext_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Veda SL917 EXT Click to the selected MikroBUS.
 */
#define VEDASL917EXT_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wake = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // vedasl917ext_map
/*! @} */ // vedasl917ext

/**
 * @brief Veda SL917 EXT Click context object.
 * @details Context object definition of Veda SL917 EXT Click driver.
 * @note Command and receive storage is shared and replaced by the next transfer.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Active-low POC_IN reset. */
    digital_out_t wake;             /**< Active-high wake / bootloader bypass. */

    // Input pins
    digital_in_t slp;               /**< UULP_VBAT_GPIO_0: low asleep, high awake when enabled by firmware. */
    digital_in_t int_pin;           /**< Host interrupt, configured active high at boot. */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */
    pin_name_t chip_select;         /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t ready;                  /**< 1 after default configuration; 0 when initialization is required. */
    uint8_t boot_version;           /**< Bootloader version byte from BOARD READY. */
    uint16_t last_status;           /**< Last bootloader word or matching firmware response status. */
    uint16_t rx_command;            /**< Most recently received command identifier. */
    uint16_t rx_status;             /**< Most recently received firmware status. */
    uint16_t rx_length;             /**< Payload bytes stored in rx_buffer. */
    uint8_t rx_queue;               /**< Most recently received queue identifier. */
    uint8_t scan_count;             /**< Valid scan records cached in rx_buffer. */
    uint8_t rx_buffer[ VEDASL917EXT_RX_BUFFER_SIZE ]; /**< Shared request and receive buffer. */

} vedasl917ext_t;

/**
 * @brief Veda SL917 EXT Click configuration object.
 * @details Configuration object definition of Veda SL917 EXT Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t slp;                 /**< Module sleep status input on AN. */
    pin_name_t rst;                 /**< POC_IN reset output on RST. */
    pin_name_t wake;                /**< Module wake output on PWM. */
    pin_name_t int_pin;             /**< Module interrupt input on INT. */

    // static variable
    uint32_t                          spi_speed;   /**< SPI serial speed, up to 25 MHz in low-speed mode. */
    spi_master_mode_t                 spi_mode;    /**< SPI master mode, use SPI_MASTER_MODE_0. */
    spi_master_chip_select_polarity_t cs_polarity; /**< Use active-low chip select. */

} vedasl917ext_cfg_t;

/**
 * @brief Veda SL917 EXT Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    VEDASL917EXT_OK = 0,
    VEDASL917EXT_NO_RESPONSE = 1,
    VEDASL917EXT_ERROR = -1,
    VEDASL917EXT_TIMEOUT = -2,
    VEDASL917EXT_PROTOCOL_ERROR = -3,
    VEDASL917EXT_FIRMWARE_ERROR = -4,
    VEDASL917EXT_BUFFER_ERROR = -5,
    VEDASL917EXT_NOT_READY = -6,
    VEDASL917EXT_DISCONNECTED = -7,
    VEDASL917EXT_SOCKET_CLOSED = -8,
    VEDASL917EXT_NO_TCP_SERVER = -9

} vedasl917ext_return_value_t;

/**
 * @brief Veda SL917 EXT firmware version object.
 * @details Decoded fields from the nine-byte full firmware version response.
 */
typedef struct
{
    uint8_t chip_id;                /**< Chip identifier. */
    uint8_t rom_id;                 /**< ROM identifier. */
    uint8_t major;                  /**< Major release. */
    uint8_t minor;                  /**< Minor release. */
    uint8_t security;               /**< Security version. */
    uint8_t patch;                  /**< Patch release. */
    uint8_t customer_id;            /**< Customer identifier. */
    uint16_t build;                 /**< Little-endian build number. */

} vedasl917ext_version_t;

/**
 * @brief Veda SL917 EXT scanned access point object.
 * @details Decoded record from a completed scan; SSID storage includes a terminator.
 */
typedef struct
{
    uint8_t channel;                /**< RF channel. */
    uint8_t security;               /**< Firmware security mode code. */
    int16_t rssi;                   /**< Received signal strength in dBm. */
    uint8_t network_type;           /**< Firmware network type code. */
    char ssid[ VEDASL917EXT_SSID_SIZE + 1 ]; /**< SSID, at most 32 bytes followed by zero. */
    uint8_t bssid[ VEDASL917EXT_MAC_SIZE ];  /**< Access point MAC address. */

} vedasl917ext_ap_t;

/**
 * @brief Veda SL917 EXT IPv4 client socket object.
 * @details Context object definition for a TCP or UDP socket and its remote endpoint.
 */
typedef struct
{
    uint16_t id;                    /**< Firmware socket identifier. Zero is a valid identifier. */
    uint16_t port;                  /**< Remote port in host byte order. */
    uint8_t address[ VEDASL917EXT_IPV4_SIZE ]; /**< Remote IPv4 octets in network order. */
    uint8_t type;                   /**< TCP or UDP socket type. */
    uint8_t open;                   /**< 1 if the host owns an open firmware socket. */

} vedasl917ext_socket_t;

/*!
 * @addtogroup vedasl917ext Veda SL917 EXT Click Driver
 * @brief API for configuring and manipulating Veda SL917 EXT Click driver.
 * @{
 */

/**
 * @brief Veda SL917 EXT configuration object setup function.
 * @details This function initializes Click configuration structure to initial values.
 * @param[out] cfg : Click configuration structure.
 * See #vedasl917ext_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note All used pins will be set to unconnected state.
 */
void vedasl917ext_cfg_setup ( vedasl917ext_cfg_t *cfg );

/**
 * @brief Veda SL917 EXT initialization function.
 * @details This function initializes all necessary pins and peripherals used for this Click board.
 * @param[out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vedasl917ext_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Peripheral initialization error.
 * See #err_t definition for detailed explanation.
 * @note Leaves reset asserted and WAKE low. SLP is a host input.
 */
err_t vedasl917ext_init ( vedasl917ext_t *ctx, vedasl917ext_cfg_t *cfg );

/**
 * @brief Veda SL917 EXT default configuration function.
 * @details This function resets the NCP, initializes SPI, boots the existing flash image, waits for CARD READY,
 * and configures a WLAN-only 2.4 GHz station with the module's IPv4 stack.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Transport, bootloader, firmware, or response error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Requires Silicon Labs SiWN917 NCP firmware. Does not program flash.
 * WAKE is kept low during boot to permit host bootloader commands. All waits are bounded.
 * A failed operation leaves ready cleared; call this function again explicitly to recover.
 */
err_t vedasl917ext_default_cfg ( vedasl917ext_t *ctx );

/**
 * @brief Veda SL917 EXT hardware reset function.
 * @details This function holds POC_IN low for 100 ms, releases it, and waits 100 ms before SPI access.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @return Nothing.
 * @note Invalidates configuration and cached results. Keeps CS inactive and WAKE low.
 */
void vedasl917ext_reset ( vedasl917ext_t *ctx );

/**
 * @brief Veda SL917 EXT SPI register write function.
 * @details This function writes a single byte to the selected SPI interface register.
 * @param[in] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] reg : SPI register address, 0x00 to 0x3F.
 * @param[in] data_in : Byte to write.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Argument, transport, or protocol error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Requires initialized NCP SPI framing.
 */
err_t vedasl917ext_write_reg ( vedasl917ext_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Veda SL917 EXT SPI register read function.
 * @details This function reads a single byte from the selected SPI interface register after checking the command
 * response and start token.
 * @param[in] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] reg : SPI register address, 0x00 to 0x3F.
 * @param[out] data_out : Destination byte.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Argument, transport, or protocol error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Requires initialized NCP SPI framing.
 */
err_t vedasl917ext_read_reg ( vedasl917ext_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Veda SL917 EXT memory write function.
 * @details This function writes bytes through the NCP AHB memory interface using a little-endian address.
 * @param[in] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] address : 32-bit memory address.
 * @param[in] data_in : Input buffer containing len bytes.
 * @param[in] len : Transfer size, 1 to 65535 bytes.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Argument, transport, or protocol error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Used for bootloader registers, not an automatic flash programming operation.
 */
err_t vedasl917ext_write_mem ( vedasl917ext_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len );

/**
 * @brief Veda SL917 EXT memory read function.
 * @details This function reads bytes through the NCP AHB memory interface after the start token.
 * @param[in] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] address : 32-bit memory address.
 * @param[out] data_out : Output buffer with room for len bytes.
 * @param[in] len : Transfer size, 1 to 65535 bytes.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Argument, transport, or protocol error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Requires initialized NCP SPI framing.
 */
err_t vedasl917ext_read_mem ( vedasl917ext_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len );

/**
 * @brief Veda SL917 EXT firmware version function.
 * @details This function requests and decodes the full NCP firmware version.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[out] version : Decoded version.
 * See #vedasl917ext_version_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Driver error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Requires default configuration. Replaces cached scan results.
 */
err_t vedasl917ext_get_fw_version ( vedasl917ext_t *ctx, vedasl917ext_version_t *version );

/**
 * @brief Veda SL917 EXT MAC address function.
 * @details This function reads the station MAC address from firmware.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[out] mac : Destination with room for six bytes.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Driver error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Requires default configuration. Replaces cached scan results.
 */
err_t vedasl917ext_get_mac_address ( vedasl917ext_t *ctx, uint8_t *mac );

/**
 * @brief Veda SL917 EXT Wi-Fi scan function.
 * @details This function performs an active foreground scan and caches up to eleven firmware scan records.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] channel : 0 for all permitted channels, or a single channel from 1 to 14.
 * @return @li @c  0 - Completed scan, including a valid empty result,
 *         @li @c <0 - Driver error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Requires default configuration. Firmware regulatory settings determine permitted channels.
 * Does not associate with an access point. Read ctx->scan_count then call vedasl917ext_get_scan_result.
 * Timeout does not cancel firmware work; the driver requires default configuration before another command.
 */
err_t vedasl917ext_scan ( vedasl917ext_t *ctx, uint8_t channel );

/**
 * @brief Veda SL917 EXT scan result function.
 * @details This function decodes one cached scan record without accessing SPI.
 * @param[in] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] index : Zero-based index less than ctx->scan_count.
 * @param[out] result : Decoded access point information.
 * See #vedasl917ext_ap_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid index, pointer, or expired scan results.
 * See #err_t definition for detailed explanation.
 * @note Results remain valid until the next command or hardware reset.
 */
err_t vedasl917ext_get_scan_result ( vedasl917ext_t *ctx, uint8_t index, vedasl917ext_ap_t *result );

/**
 * @brief Veda SL917 EXT Wi-Fi join function.
 * @details This function scans for the selected SSID, configures the passphrase for WPA2, and joins the network.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] ssid : Null-terminated SSID, 1 to 32 bytes.
 * @param[in] security : VEDASL917EXT_WIFI_OPEN or VEDASL917EXT_WIFI_WPA2.
 * @param[in] passphrase : Null-terminated WPA2 passphrase, 8 to 63 bytes. Use NULL or an empty string for open Wi-Fi.
 * @return @li @c  0 - Associated,
 *         @li @c <0 - Argument, transport, response, or firmware error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Requires default configuration. Credentials are sent to the module for the current session.
 */
err_t vedasl917ext_join ( vedasl917ext_t *ctx, char *ssid, uint8_t security, char *passphrase );

/**
 * @brief Veda SL917 EXT DHCP function.
 * @details This function requests a DHCP lease and reads the station's IPv4 address.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[out] address : Destination for four IPv4 octets in network order.
 * @return @li @c  0 - Address assigned,
 *         @li @c <0 - Driver or firmware error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Call after a successful join.
 */
err_t vedasl917ext_dhcp ( vedasl917ext_t *ctx, uint8_t *address );

/**
 * @brief Veda SL917 EXT IPv4 client socket open function.
 * @details This function connects a TCP client or opens a UDP client for the selected remote endpoint.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[out] socket : Socket object.
 * See #vedasl917ext_socket_t object definition for detailed explanation.
 * @param[in] type : VEDASL917EXT_SOCKET_TCP or VEDASL917EXT_SOCKET_UDP.
 * @param[in] address : Remote IPv4 octets in network order.
 * @param[in] port : Remote port in host byte order.
 * @param[in] local_port : Local port in host byte order, or 0 for a firmware-assigned port.
 * @return @li @c  0 - Socket opened,
 *         @li @c -9 - Firmware reported no TCP listener at the remote endpoint,
 *         @li Other negative values - Driver or firmware error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Use one client socket at a time after DHCP succeeds. Reopen sockets after a module reset.
 * A no-listener response leaves the station ready for another socket command.
 */
err_t vedasl917ext_socket_open ( vedasl917ext_t *ctx, vedasl917ext_socket_t *socket, uint8_t type,
                                 uint8_t *address, uint16_t port, uint16_t local_port );

/**
 * @brief Veda SL917 EXT socket send function.
 * @details This function submits one TCP payload or UDP datagram to the module.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] socket : Open client socket.
 * See #vedasl917ext_socket_t object definition for detailed explanation.
 * @param[in] buffer : Payload to send.
 * @param[in] len : Payload length, 1 to VEDASL917EXT_SOCKET_TX_MAX bytes.
 * @return @li @c  0 - Frame submitted,
 *         @li @c <0 - Driver error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note Success indicates SPI submission. Delivery is confirmed separately by the application.
 */
err_t vedasl917ext_socket_send ( vedasl917ext_t *ctx, vedasl917ext_socket_t *socket, uint8_t *buffer, uint16_t len );

/**
 * @brief Veda SL917 EXT socket receive function.
 * @details This function reads one TCP chunk or one UDP datagram. UDP packets from other peers are ignored.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in] socket : Open client socket.
 * See #vedasl917ext_socket_t object definition for detailed explanation.
 * @param[out] buffer : Destination for the received payload.
 * @param[in] capacity : Destination capacity in bytes.
 * @param[out] received : Number of bytes copied, zero on error.
 * @param[in] polls : Maximum number of receive polls, each separated by a delay of about 1 ms.
 * @return @li @c  0 - Payload received,
 *         @li @c <0 - Driver, timeout, capacity, or link error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 * @note This function does not send a receive command. A wait timeout alone leaves the socket open.
 */
err_t vedasl917ext_socket_recv ( vedasl917ext_t *ctx, vedasl917ext_socket_t *socket, uint8_t *buffer,
                                 uint16_t capacity, uint16_t *received, uint16_t polls );

/**
 * @brief Veda SL917 EXT socket close function.
 * @details This function releases the firmware socket.
 * @param[in,out] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @param[in,out] socket : Open client socket.
 * See #vedasl917ext_socket_t object definition for detailed explanation.
 * @return @li @c  0 - Socket closed,
 *         @li @c <0 - Driver or firmware error.
 * See #vedasl917ext_return_value_t definition for detailed explanation.
 */
err_t vedasl917ext_socket_close ( vedasl917ext_t *ctx, vedasl917ext_socket_t *socket );

/**
 * @brief Veda SL917 EXT interrupt pin reading function.
 * @details This function reads the physical host interrupt level.
 * @param[in] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @return Pin level, 0 or 1.
 * @note Default configuration selects active-high interrupts.
 */
uint8_t vedasl917ext_get_int_pin ( vedasl917ext_t *ctx );

/**
 * @brief Veda SL917 EXT sleep status pin reading function.
 * @details This function reads the module's SLEEP_IND_FROM_DEV signal on mikroBUS AN.
 * @param[in] ctx : Click context object.
 * See #vedasl917ext_t object definition for detailed explanation.
 * @return Pin level, 0 or 1.
 * @note When firmware enables this indication, low means asleep and high means awake.
 * This driver does not enable low-power modes.
 */
uint8_t vedasl917ext_get_slp_pin ( vedasl917ext_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // VEDASL917EXT_H

/*! @} */ // vedasl917ext

// ------------------------------------------------------------------------ END
