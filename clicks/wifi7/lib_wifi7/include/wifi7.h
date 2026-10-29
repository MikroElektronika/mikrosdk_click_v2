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
 * @file wifi7.h
 * @brief This file contains API for WiFi 7 Click Driver.
 */

#ifndef WIFI7_H
#define WIFI7_H

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
#include "wifi7_types.h"
#include "spi_specifics.h"

/*!
 * @addtogroup wifi7 WiFi 7 Click Driver
 * @brief API for configuring and manipulating WiFi 7 Click driver.
 * @{
 */

/**
 * @defgroup wifi7_set WiFi 7 Registers Settings
 * @brief Settings for registers of WiFi 7 Click driver.
 */

/**
 * @addtogroup wifi7_set
 * @{
 */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU.
 * Can be overwritten with @b wifi7_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define WIFI7_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define WIFI7_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // wifi7_set

/**
 * @defgroup wifi7_map WiFi 7 MikroBUS Map
 * @brief MikroBUS pin mapping of WiFi 7 Click driver.
 */

/**
 * @addtogroup wifi7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of WiFi 7 Click to the selected MikroBUS.
 */
#define WIFI7_MAP_MIKROBUS( cfg, mikrobus )         \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK );   \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS );     \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // wifi7_map
/*! @} */ // wifi7

/**
 * @brief WiFi 7 Click context object.
 * @details Context object definition of WiFi 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;                               /**< Active-high module CHIP_EN output. */
    digital_out_t rst;                              /**< Active-low module RESET_N output. */

    // Input pins
    digital_in_t int_pin;                           /**< Active-low module interrupt input. */

    // Modules
    spi_master_t spi;                               /**< SPI driver object. */

    pin_name_t chip_select;                         /**< SPI chip-select pin descriptor. */

    // Driver state
    wifi7_nm_state_t device_state;                  /**< Host bus and firmware initialization state. */
    uint8_t ch_num;                                 /**< Access-point count from the last successful scan. */
    wifi7_socket_t sockets[ WIFI7_MAX_SOCKET ];     /**< Allocated socket slots and pending receive buffers. */
    uint16_t session_id;                            /**< Last allocated socket session identifier. */
    uint8_t socket_init;                            /**< 1 after socket bookkeeping initialization. */
    wifi7_app_wifi_cb_t app_wifi_cb;                /**< Application Wi-Fi event callback, or NULL. */
    wifi7_app_socket_cb_t app_socket_cb;            /**< Application socket event callback, or NULL. */

} wifi7_t;

/**
 * @brief WiFi 7 Click configuration object.
 * @details Configuration object definition of WiFi 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                                    /**< Master input - slave output pin descriptor for SPI. */
    pin_name_t mosi;                                    /**< Master output - slave input pin descriptor for SPI. */
    pin_name_t sck;                                     /**< SPI clock pin descriptor. */
    pin_name_t cs;                                      /**< Active-low SPI chip-select pin descriptor. */

    // Additional gpio pins
    pin_name_t en;                                      /**< Active-high module enable pin descriptor. */
    pin_name_t rst;                                     /**< Active-low module reset pin descriptor. */
    pin_name_t int_pin;                                 /**< Active-low module interrupt pin descriptor. */

    // static variable
    uint32_t spi_speed;                                 /**< SPI clock in Hz; 1 MHz default, limited by the driver. */
    spi_master_mode_t spi_mode;                         /**< SPI mode; this driver requires SPI_MASTER_MODE_0. */
    spi_master_chip_select_polarity_t cs_polarity;      /**< Must be SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW. */

} wifi7_cfg_t;

/**
 * @brief WiFi 7 internal HIF dispatcher callback type.
 * @details This callback receives the validated address and payload length of a Wi-Fi or IP firmware message.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] u8_op_code : Firmware opcode.
 * @param[in] u16_data_size : Payload length after the HIF prefix, in bytes.
 * @param[in] u32_addr : Firmware address of the first payload byte.
 * @return Nothing.
 * @note Used only by the internal dispatchers. Read payload bytes before releasing the firmware message.
 */
typedef void ( *wifi7_hif_call_back_t ) ( wifi7_t *ctx, uint8_t u8_op_code, uint16_t u16_data_size, uint32_t u32_addr );

/**
 * @brief WiFi 7 internal host interface context.
 * @details Shared message ownership, receive bounds, and group dispatcher pointers.
 */
typedef struct
{
    uint8_t u8_hif_rx_done;                     /**< 1 while the current receive message needs acknowledgement. */
    uint8_t rx_error;                           /**< 1 after a receive copy or acknowledgement failure. */
    uint32_t u32_rx_addr;                       /**< Start address of the current complete HIF message. */
    uint32_t u32_rx_size;                       /**< Complete HIF message length including its prefix, bytes. */
    wifi7_hif_call_back_t pf_wifi_cb;           /**< Internal Wi-Fi message dispatcher. */
    wifi7_hif_call_back_t pf_ip_cb;             /**< Internal socket message dispatcher. */

} wifi7_hif_context_t;

/*!
 * @addtogroup wifi7 WiFi 7 Click Driver
 * @brief API for configuring and manipulating WiFi 7 Click driver.
 * @{
 */

/**
 * @brief WiFi 7 configuration object setup function.
 * @details This function initializes the Click configuration structure with unconnected pins and default SPI
 * settings.
 * @param[out] cfg : Click configuration structure.
 * See #wifi7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The SPI defaults are 1000000 Hz, mode 0, and active-low chip select. Map all required pins before
 * initialization.
 */
void wifi7_cfg_setup ( wifi7_cfg_t *cfg );

/**
 * @brief WiFi 7 initialization function.
 * @details This function opens SPI and initializes CHIP_EN, RESET_N, and the active-low interrupt input.
 * @param[out] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #wifi7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use mode 0, active-low chip select, and a nonzero speed up to WIFI7_SPI_MAX_SPEED Hz. The module remains
 * disabled until wifi7_default_cfg is called; application callbacks are cleared.
 */
err_t wifi7_init ( wifi7_t *ctx, wifi7_cfg_t *cfg );

/**
 * @brief WiFi 7 default configuration function.
 * @details This function sequences CHIP_EN and RESET_N, initializes the SPI protocol, boots firmware, checks
 * compatibility, and enables module interrupts.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Incompatible firmware.
 * See #err_t definition for detailed explanation.
 * @note Call after wifi7_init. This resets all socket slots and scan results. Call wifi7_socket_init again before
 * socket operations; Wi-Fi association is requested separately with wifi7_connect.
 */
err_t wifi7_default_cfg ( wifi7_t *ctx );

/**
 * @brief WiFi 7 generic writing function.
 * @details This function writes raw SPI bytes with chip select asserted for the duration of this transfer.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] data_in : Source buffer containing at least len bytes.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Driver-level operation. The caller supplies a valid buffer and complete SPI framing; this function does not
 * wake the module.
 */
err_t wifi7_generic_write ( wifi7_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief WiFi 7 generic reading function.
 * @details This function clocks raw SPI bytes into the supplied buffer using the configured default transmit byte.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[out] data_out : Destination buffer with capacity for len bytes.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Driver-level operation. Chip select is released after the transfer. This function does not wake the module
 * or parse a response.
 */
err_t wifi7_generic_read ( wifi7_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief WiFi 7 register writing function.
 * @details This function writes a 32-bit register through the WINC SPI command protocol with bounded retries.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] addr : Register address.
 * @param[in] data_in : 32-bit value to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Clockless registers at addresses up to 0x30 use internal-write commands. Other register accesses require
 * the module clocks to be enabled.
 */
err_t wifi7_reg_write ( wifi7_t *ctx, uint32_t addr, uint32_t data_in );

/**
 * @brief WiFi 7 register reading function.
 * @details This function reads a 32-bit register through the WINC SPI command protocol and decodes its byte order.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] addr : Register address.
 * @param[out] data_out : Destination for the 32-bit register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note A NULL destination is rejected. Addresses up to 0xFF use clockless internal-read commands; other registers
 * require enabled module clocks.
 */
err_t wifi7_reg_read ( wifi7_t *ctx, uint32_t addr, uint32_t *data_out );

/**
 * @brief WiFi 7 block reading function.
 * @details This function reads a block of module memory using the extended SPI DMA read command.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] addr : Module memory start address.
 * @param[out] data_buf : Destination buffer with capacity for buf_len bytes.
 * @param[in] buf_len : Number of bytes to read; must be greater than zero.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The module must be awake. A one-byte request reads an internal two-byte temporary buffer and returns only
 * the requested byte.
 */
err_t wifi7_block_read ( wifi7_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_len );

/**
 * @brief WiFi 7 block writing function.
 * @details This function writes a block of module memory and checks the SPI DMA completion response.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] addr : Module memory start address.
 * @param[in] data_buf : Source buffer containing at least buf_len bytes.
 * @param[in] buf_len : Number of bytes to write; must be greater than zero.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The module must be awake. A one-byte request reads and preserves the adjacent byte required by the SPI
 * hardware workaround.
 */
err_t wifi7_block_write ( wifi7_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_len );

/**
 * @brief WiFi 7 host driver initialization function.
 * @details This function configures WINC SPI framing, validates the chip family, starts normal firmware, and
 * registers the Wi-Fi event dispatcher.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Incompatible firmware.
 * See #err_t definition for detailed explanation.
 * @note Normally called by wifi7_default_cfg after hardware reset. The firmware must accept host driver 19.5.4;
 * success does not indicate Wi-Fi association.
 */
err_t wifi7_init_drv ( wifi7_t *ctx );

/**
 * @brief WiFi 7 chip identification function.
 * @details This function reads chip and RF revision registers and normalizes the identifier to the WINC1500 family.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return Normalized chip identifier, or 0 on a communication error.
 * @note Driver-level operation requiring enabled module clocks. The returned identifier can differ from the raw
 * chip-ID register.
 */
uint32_t wifi7_chip_id ( wifi7_t *ctx );

/**
 * @brief WiFi 7 firmware version reading function.
 * @details This function wakes the module and reads its firmware revision record, build date, and build time.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[out] fw_version : Destination firmware revision record.
 * See #wifi7_m2m_rev_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call after firmware startup. The build strings are terminated by the driver; only a successful return makes
 * the record valid.
 */
err_t wifi7_get_full_firmware_version ( wifi7_t *ctx, wifi7_m2m_rev_t *fw_version );

/**
 * @brief WiFi 7 network connection function.
 * @details This function submits a station connection request using the supplied SSID, authentication, and RF
 * channel.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] pc_ssid : SSID buffer containing u8_ssid_len bytes.
 * @param[in] u8_ssid_len : SSID length from 1 to 32 bytes, excluding any terminator.
 * @param[in] u8_sec_type : WIFI7_M2M_WIFI_SEC_OPEN or WIFI7_M2M_WIFI_SEC_WPA_PSK.
 * See #wifi7_m2m_sec_type_t object definition for detailed explanation.
 * @param[in] pv_auth_info : NULL for open networks; a terminated 8-63 character passphrase or 64 hexadecimal PSK
 * digits.
 * @param[in] u16_ch : Channel 1-14, or WIFI7_M2M_WIFI_CH_ALL to scan all channels.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Credentials are not saved to module flash. Poll wifi7_handle_events for association and DHCP callbacks;
 * successful submission does not establish the network connection.
 */
err_t wifi7_connect ( wifi7_t *ctx, char *pc_ssid, uint8_t u8_ssid_len, wifi7_m2m_sec_type_t u8_sec_type, void *pv_auth_info,
                      uint16_t u16_ch );

/**
 * @brief WiFi 7 connection information request function.
 * @details This function requests the current SSID, authentication type, IPv4 address, MAC address, RSSI, and RF
 * channel.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The WIFI7_M2M_WIFI_RESP_CONN_INFO event supplies a wifi7_m2m_conn_info_t payload valid only during the
 * application callback.
 */
err_t wifi7_get_connection_info ( wifi7_t *ctx );

/**
 * @brief WiFi 7 scan result request function.
 * @details This function requests one access-point record from the most recent successful scan.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] scan_index : Zero-based result index less than ctx->ch_num.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Wait for WIFI7_M2M_WIFI_RESP_SCAN_DONE before requesting results. WIFI7_M2M_WIFI_RESP_SCAN_RESULT supplies
 * wifi7_m2m_wifiscan_result_t during the callback.
 */
err_t wifi7_req_scan_result ( wifi7_t *ctx, uint8_t scan_index );

/**
 * @brief WiFi 7 network scanning function.
 * @details This function requests an active scan on one RF channel or all supported channels.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] channel : Channel 1-14, or WIFI7_M2M_WIFI_CH_ALL.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Wait for WIFI7_M2M_WIFI_RESP_SCAN_DONE before another scan. A successful scan updates ctx->ch_num with the number
 * of discovered access points.
 */
err_t wifi7_request_scan ( wifi7_t *ctx, uint8_t channel );

/**
 * @brief WiFi 7 event processing function.
 * @details This function polls the active-low INT pin and dispatches at most one pending Wi-Fi or socket firmware
 * message.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call frequently from the main loop after initialization; never call recursively from a callback. One
 * receive message can invoke several callbacks. Success also means no event was pending.
 */
err_t wifi7_handle_events ( wifi7_t *ctx );

/**
 * @brief WiFi 7 socket initialization function.
 * @details This function initializes local socket slots and registers the internal IP event dispatcher once per
 * module initialization.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return Nothing.
 * @note Call after wifi7_default_cfg and before allocating sockets. Set ctx->app_socket_cb to receive completion
 * events; calling again while initialized does not clear active sockets.
 */
void wifi7_socket_init ( wifi7_t *ctx );

/**
 * @brief WiFi 7 socket allocation function.
 * @details This function reserves a local slot and assigns a nonzero session identifier without sending a firmware
 * command.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] u16_domain : WIFI7_AF_INET for IPv4.
 * @param[in] u8_type : WIFI7_SOCK_STREAM for TCP or WIFI7_SOCK_DGRAM for UDP.
 * @param[in] u8_flags : Must be zero; TLS and raw socket modes are not implemented.
 * @return @li @c 0..10 - Allocated socket descriptor,
 *         @li @c -1 - Invalid parameters, driver not ready, or no free slot.
 * See #err_t definition for detailed explanation.
 * @note TCP descriptors are 0-6 and UDP descriptors are 7-10. Call wifi7_socket_init first; allocation alone does
 * not bind or connect a socket.
 */
err_t wifi7_socket_create ( wifi7_t *ctx, uint16_t u16_domain, uint8_t u8_type, uint8_t u8_flags );

/**
 * @brief WiFi 7 socket binding function.
 * @details This function submits a request to associate a local IPv4 address and port with an allocated TCP or UDP
 * socket.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] sock : Allocated socket descriptor.
 * @param[in] pstr_addr : Pointer to wifi7_sockaddr_in_t cast to wifi7_sockaddr_t; address and port use network byte
 * order.
 * @param[in] u8_addr_len : Size of wifi7_sockaddr_in_t in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Set sin_family to WIFI7_AF_INET and use address zero for any local interface. WIFI7_SOCKET_MSG_BIND reports the
 * firmware result through wifi7_socket_bind_msg_t.
 */
err_t wifi7_socket_bind ( wifi7_t *ctx, int8_t sock, wifi7_sockaddr_t *pstr_addr, uint8_t u8_addr_len );

/**
 * @brief WiFi 7 socket listening function.
 * @details This function requests passive listening on a bound TCP socket.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] sock : Allocated and successfully bound TCP socket descriptor.
 * @param[in] backlog : Pending connection queue limit passed to firmware.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Wait for successful WIFI7_SOCKET_MSG_BIND before listening. WIFI7_SOCKET_MSG_LISTEN reports status;
 * WIFI7_SOCKET_MSG_ACCEPT
 * supplies a new client descriptor that the application must close when finished.
 */
int8_t wifi7_socket_listen ( wifi7_t *ctx, int8_t sock, uint8_t backlog );

/**
 * @brief WiFi 7 socket connection function.
 * @details This function submits an IPv4 peer connection request for an allocated socket.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] sock : Allocated socket descriptor.
 * @param[in] pstr_addr : Pointer to wifi7_sockaddr_in_t cast to wifi7_sockaddr_t; peer address and port use network
 * byte order.
 * @param[in] u8_addr_len : Size of wifi7_sockaddr_in_t in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For a TCP client, wait for WIFI7_SOCKET_MSG_CONNECT with s8_error equal to zero before sending. A successful
 * return confirms submission only.
 */
err_t wifi7_socket_connect ( wifi7_t *ctx, int8_t sock, wifi7_sockaddr_t *pstr_addr, uint8_t u8_addr_len );

/**
 * @brief WiFi 7 socket transmission function.
 * @details This function copies the payload into module memory and submits a socket send request.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] sock : Allocated socket descriptor with a configured peer.
 * @param[in] pv_send_buffer : Source payload buffer; its contents are copied during this call.
 * @param[in] u16_send_length : Payload length from 1 to WIFI7_SOCKET_BUFFER_MAX_LENGTH bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Wait for WIFI7_SOCKET_MSG_SEND and inspect the int16_t byte count or negative firmware error. The source buffer
 * can be reused after submission; use wifi7_socket_send_to for an explicit UDP destination.
 */
err_t wifi7_socket_send ( wifi7_t *ctx, int8_t sock, void *pv_send_buffer, uint16_t u16_send_length );

/**
 * @brief WiFi 7 UDP transmission function.
 * @details This function copies a datagram into module memory and submits it to the specified IPv4 destination.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] sock : Allocated UDP socket descriptor.
 * @param[in] pv_send_buffer : Source datagram buffer; its contents are copied during this call.
 * @param[in] u16_send_length : Payload length from 1 to WIFI7_SOCKET_BUFFER_MAX_LENGTH bytes.
 * @param[in] pstr_dest_addr : Pointer to wifi7_sockaddr_in_t cast to wifi7_sockaddr_t; destination address and port
 * use network byte order.
 * @param[in] u8_addr_len : Size of wifi7_sockaddr_in_t in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note WIFI7_SOCKET_MSG_SENDTO reports an int16_t byte count or negative firmware error. Bind a local UDP port and queue
 * reception before sending when expecting a reply.
 */
err_t wifi7_socket_send_to ( wifi7_t *ctx, int8_t sock, void *pv_send_buffer, uint16_t u16_send_length,
                             wifi7_sockaddr_t *pstr_dest_addr, uint8_t u8_addr_len );

/**
 * @brief WiFi 7 TCP reception function.
 * @details This function retains the caller's buffer and requests TCP reception through WIFI7_SOCKET_MSG_RECV.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] sock : Allocated TCP socket descriptor.
 * @param[out] pv_recv_buf : Receive buffer retained until completion or successful socket closure.
 * @param[in] u16_buf_len : Receive buffer capacity in bytes; must be greater than zero.
 * @param[in] u32_timeoutmsec : Firmware receive timeout in milliseconds; zero waits indefinitely.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Only one receive request can be pending per socket. Consume each callback chunk before returning; reissue
 * only when u16_remaining_size is zero. Positive sizes are bytes, zero is peer closure, and negative sizes are
 * firmware errors.
 */
err_t wifi7_socket_receive ( wifi7_t *ctx, int8_t sock, void *pv_recv_buf, uint16_t u16_buf_len, uint32_t u32_timeoutmsec );

/**
 * @brief WiFi 7 UDP reception function.
 * @details This function retains the caller's buffer and requests one datagram through WIFI7_SOCKET_MSG_RECVFROM.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] sock : Allocated and successfully bound UDP socket descriptor.
 * @param[out] pv_recv_buf : Receive buffer retained until completion or successful socket closure.
 * @param[in] u16_buf_len : Receive buffer capacity in bytes; must be greater than zero.
 * @param[in] u32_timeoutmsec : Firmware receive timeout in milliseconds; zero waits indefinitely.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Only one receive request can be pending. A datagram can produce several callbacks using the same buffer;
 * consume each chunk and reissue when u16_remaining_size is zero. str_remote_addr identifies the sender.
 */
err_t wifi7_socket_receive_from ( wifi7_t *ctx, int8_t sock, void *pv_recv_buf, uint16_t u16_buf_len,
                                  uint32_t u32_timeoutmsec );

/**
 * @brief WiFi 7 socket closing function.
 * @details This function submits firmware closure and releases the local socket slot when submission succeeds.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] sock : Allocated TCP or UDP socket descriptor.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note There is no close-completion callback. Successful submission also releases a pending receive buffer. A
 * failed HIF transfer can require wifi7_default_cfg and wifi7_socket_init before further socket operations.
 */
err_t wifi7_socket_close ( wifi7_t *ctx, int8_t sock );

/**
 * @brief WiFi 7 network disconnection function.
 * @details This function submits a station disconnection request to the module.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Poll wifi7_handle_events for WIFI7_M2M_WIFI_RESP_CON_STATE_CHANGED. A successful return confirms submission only.
 */
err_t wifi7_disconnect ( wifi7_t *ctx );

/**
 * @brief WiFi 7 signal strength request function.
 * @details This function requests the currently associated access point's received signal strength.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note WIFI7_M2M_WIFI_RESP_CURRENT_RSSI supplies a pointer to an int8_t RSSI value in dBm. The callback payload is valid
 * only until the callback returns.
 */
err_t wifi7_request_rssi ( wifi7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // WIFI7_H

/*! @} */ // wifi7

// ------------------------------------------------------------------------ END
