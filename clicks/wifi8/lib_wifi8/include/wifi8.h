/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file wifi8.h
 * @brief This file contains API for WiFi 8 Click Driver.
 */

#ifndef WIFI8_H
#define WIFI8_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "wifi8_types.h"

/*!
 * @addtogroup wifi8 WiFi 8 Click Driver
 * @brief API for configuring and manipulating WiFi 8 Click driver.
 * @{
 */

/**
 * @defgroup wifi8_map WiFi 8 MikroBUS Map
 * @brief MikroBUS pin mapping of WiFi 8 Click driver.
 */

/**
 * @addtogroup wifi8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of WiFi 8 Click to the selected MikroBUS.
 */
#define WIFI8_MAP_MIKROBUS(cfg, mikrobus)         \
    cfg.miso = MIKROBUS(mikrobus, MIKROBUS_MISO); \
    cfg.mosi = MIKROBUS(mikrobus, MIKROBUS_MOSI); \
    cfg.sck = MIKROBUS(mikrobus, MIKROBUS_SCK);   \
    cfg.cs = MIKROBUS(mikrobus, MIKROBUS_CS);     \
    cfg.en = MIKROBUS(mikrobus, MIKROBUS_AN);     \
    cfg.rst = MIKROBUS(mikrobus, MIKROBUS_RST);   \
    cfg.wkp = MIKROBUS(mikrobus, MIKROBUS_PWM);   \
    cfg.int_pin = MIKROBUS(mikrobus, MIKROBUS_INT)

    /*! @} */ // wifi8_map
    /*! @} */ // wifi8
    
/**
 * @brief WiFi 8 Click context object.
 * @details Context object definition of WiFi 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;  /**< Description. */
    digital_out_t rst; /**< Description. */
    digital_out_t wkp; /**< Description. */

    // Input pins
    digital_in_t int_pin; /**< Description. */

    // Modules
    spi_master_t spi; /**< SPI driver object. */

    pin_name_t chip_select; /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t hif_bl_offset;
    wifi8_nm_state_t device_state;
    uint8_t ch_num;
    uint32_t hs_flags;
    wifi8_socket_t sockets[MAX_SOCKET];
    uint8_t root_sha1[20];
    uint16_t session_id;
    uint8_t socket_init;
    uint32_t ping_id;
    wifi8_app_wifi_cb_t app_wifi_cb;
    wifi8_app_socket_cb_t app_socket_cb;
    wifi8_app_resolve_cb_t app_resolve_cb;
    wifi8_ping_cb_t ping_cb;

} wifi8_t;

/**
 * @brief WiFi 8 Click configuration object.
 * @details Configuration object definition of WiFi 8 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso; /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi; /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;  /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;   /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t en;      /**< Description. */
    pin_name_t rst;     /**< Description. */
    pin_name_t wkp;     /**< Description. */
    pin_name_t int_pin; /**< Description. */

    // static variable
    uint32_t spi_speed;                            /**< SPI serial speed. */
    spi_master_mode_t spi_mode;                    /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity; /**< Chip select pin polarity. */

} wifi8_cfg_t;

typedef void (*wifi8_hif_call_back_t)(wifi8_t *ctx, uint8_t u8_op_code, uint16_t u16_data_size, uint32_t u32_addr);
typedef wifi8_sock_addr_t wifi8_uip_sock_addr_t;

typedef struct
{
    uint8_t u8_chip_mode;
    uint8_t u8_chip_sleep;
    uint8_t u8_hif_rx_done;
    uint8_t u8_interrupt;
    uint8_t u8_yield;
    uint32_t u32_rx_addr;
    uint32_t u32_rx_size;
    wifi8_hif_call_back_t pf_wifi_cb;
    wifi8_hif_call_back_t pf_ip_cb;
    wifi8_hif_call_back_t pf_ota_cb;
    wifi8_hif_call_back_t pf_sigma_cb;
    wifi8_hif_call_back_t pf_hif_cb;
    wifi8_hif_call_back_t pf_crypto_cb;
    wifi8_hif_call_back_t pf_ssl_cb;
} wifi8_hif_context_t;

/*!
 * @addtogroup wifi8 WiFi 8 Click Driver
 * @brief API for configuring and manipulating WiFi 8 Click driver.
 * @{
 */

/**
 * @brief WiFi 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #wifi8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void wifi8_cfg_setup(wifi8_cfg_t *cfg);

/**
 * @brief WiFi 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #wifi8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_init(wifi8_t *ctx, wifi8_cfg_t *cfg);

/**
 * @brief WiFi 8 default configuration function.
 * @details This function executes a default configuration of WiFi 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t wifi8_default_cfg(wifi8_t *ctx);

/**
 * @brief Generic writing function.
 * @details This function writes a desired number of data 
 * bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifi8_generic_write(wifi8_t *ctx, uint8_t *data_in, uint8_t len);

/**
 * @brief Generic reading function.
 * @details This function reads a desired number of data 
 * bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifi8_generic_read(wifi8_t *ctx, uint8_t *data_out, uint8_t len);

/**
 * @brief Write data to register address.
 * @details This function writes data to register 
 * address by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] addr : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifi8_reg_write(wifi8_t *ctx, uint32_t addr, uint32_t data_in);

/**
 * @brief Read data from register address.
 * @details This function reads data from register 
 * address by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] addr : Register address.
 * @param[out] data_out : Data to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifi8_reg_read(wifi8_t *ctx, uint32_t addr, uint32_t *data_out);

/**
 * @brief Read blocks of data from register address.
 * @details This function reads data from register 
 * address by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] addr : Register address.
 * @param[out] data_buf : Read data.
 * @param[in] buf_len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifi8_block_read(wifi8_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_len);

/**
 * @brief Write blocks of data to register address.
 * @details This function writes data to register 
 * address by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] addr : Register address.
 * @param[in] data_buf : Data to write.
 * @param[in] buf_len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wifi8_block_write(wifi8_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_len);

/**
 * @brief Synchronous API to initialize the device driver.
 * @details This function initializes the device driver by registering 
 * the callback function for the M2M_WIFI layer handling of the events
 * received, in response to the asynchronous Wi-Fi operations.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Enables funtionality of driver should be called at the 
 * start of the appliction example after communication initialization.
 */
err_t wifi8_init_drv(wifi8_t *ctx);

/**
 * @brief Get device ID.
 * @details Reads and returns device ID.
 * @param[out] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return Device ID.
 */
uint32_t wifi8_chip_id(wifi8_t *ctx);

/**
 * @brief Synchronous API to obtain the firmware version currently running on the device.
 * @details Read the firmware version currently running on the device.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[out] fw_version : Firmware object data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_get_full_firmware_version(wifi8_t *ctx, wifi8_m2m_rev_t *fw_version);

/**
 * @brief Synchronous API to obtain the firmware version of the device.
 * @details Synchronous API to obtain the firmware version of the 
 * device image that is stored in the inactive flash partition.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[out] fw_version : Firmware object data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_get_ota_firmware_version(wifi8_t *ctx, wifi8_m2m_rev_t *fw_version);

/**
 * @brie Asynchronous Wi-Fi connection function.
 * @details Asynchronous API to request connection to a specified access point.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] pc_ssid : A buffer holding the SSID corresponding to the requested AP.
 * @param[in] u8_ssid_len : Length of the given SSID (not including any NULL termination).
 * @param[in] u8_sec_type : Wi-Fi security type security for the network.
 * @param[in] pv_auth_info : Authentication parameters required for completing the connection.
 * @param[in] u16_ch : Wi-Fi channel number as defined in @ref tenuM2mScanCh enumeration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_connect(wifi8_t *ctx, char *pc_ssid, uint8_t u8_ssid_len, wifi8_m2m_sec_type_t u8_sec_type, void *pv_auth_info, uint16_t u16_ch);

/**
 * @brie Asynchronous API for retrieving the device connection status.
 * @details Requests the connection status from the device including information regarding any access
 * point to which it is currently connected, or any non-AP station that is connected to the device.
 * All information will be returned to the application via the Wi-Fi notification callback through
 * the event @ref M2M_WIFI_RESP_CONN_INFO.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_get_connection_info(wifi8_t *ctx);

/**
 * @brief Asynchronous API to enable access point (AKA "hot-spot") mode on the device.
 * @details  The WINC supports the ability to operate as an access point with the following limitations:
 * - Only 1 station may be associated at any given time.
 * - Open system and WEP are the only security suites supported.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] pstr_m2map_config : A structure holding the AP configurations.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_start_ap(wifi8_t *ctx, wifi8_m2m_ap_config_t *pstr_m2m_ap_config);

/**
 * @brief Asynchronous API to request the information of an access point discovered via scanning.
 * @details  This function allows the information of any discovered access point to be retrieved. When a
 * scan is completed, the application is informed of the number of networks (access points)
 * discovered. Calling this function with an index, N, will return the information for the Nth
 * access point. The information will be returned to the application via a
 * @b M2M_WIFI_RESP_SCAN_RESULT event.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] scan_request_index : Index for the requested result, 
 * the index range start from 0 till number of AP's found.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_req_scan_result(wifi8_t *ctx, uint8_t scan_request_index);

/**
 * @brief Asynchronous API to request the WINC to scan for networks.
 * @details  Scan statuses are delivered to the application via the Wi-Fi event callback in
 * three stages. The first step involves the event @b M2M_WIFI_RESP_SCAN_DONE which, if successful,
 * of access points via multiple calls to the asynchronous @b wifi8_req_scan_result API. For
 * @b M2M_WIFI_RESP_SCAN_RESULT.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] channel : RF Channel ID for SCAN operation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_request_scan(wifi8_t *ctx, uint8_t channel);

/**
 * @brief Synchronous event handler function.
 * @details This function is responsible for handling interrupts received from the device firmware.
 * Applications should call this function periodically in-order to receive the events that are to
 * be handled by the callback functions implemented by the application.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_handle_events(wifi8_t *ctx);

/**
 * @brief Asynchronous API to send an encapsulated BLE message.
 * @details Asynchronous API to send an encapsulated BLE message over the Wifi Host Interface.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] msg : Pointer to the start of the BLE message to transfer down to the device.
 * @param[in] len : The length of the message in octets.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_ble_api_send(wifi8_t *ctx, uint8_t *msg,  uint32_t len);

/**
 * @brief The function performs the necessary initializations for the socket library.
 * @details The function performs the necessary initializations for the socket library through the following steps:
 * - Check made to ensuring that initialization for sockets is performed only once.
 * - Zero initializations to the global socket array (socets), which holds the list of TCP sockets.
 * - Registers the socket (Host Interface)hif callback function through the call to the hif_register_cb function.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This initialization function must be invoked before any socket operation is performed.
 */
void wifi8_socket_init(wifi8_t *ctx);

/**
 * @brief Synchronous socket allocation function based on the specified socket type.
 * @details Synchronous socket allocation function based on the specified socket type. 
 * Created sockets are non-blocking and their possible types are either TCP or a UDP sockets.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] u16_domain : Socket family.
 * @param[in] u8_type :Socket type.
 * @param[in] u8_flags : Used to specify the socket creation flags.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_socket_create(wifi8_t *ctx, uint16_t u16_domain, uint8_t u8_type, uint8_t u8_flags);

/**
 * @brief Asynchronous bind function associates the provided address and local port to the socket.
 * @details The asynchronous bind function associates the provided address and local port to the
 * socket.The function can be used with both TCP and UDP sockets. Upon socket bind completion, 
 * the application will receive a @b SOCKET_MSG_BIND message in the socket callback.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] sock : Socket ID, must hold a non negative value.
 * @param[in] pstr_addr :Pointer to socket address structure.
 * @param[in] u8_addr_len : Size of the given socket address structure in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_socket_bind(wifi8_t *ctx, int8_t sock, wifi8_sockaddr_t *pstr_addr, uint8_t u8_addr_len);

/**
 * @brief Asynchronous listen function.
 * @details The asynchronous listen function, response is received through 
 * the event @b SOCKET_MSG_LISTEN in the socket callback.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] sock : Socket ID, must hold a non negative value.
 * @param[in] backlog : Not used by the current implementation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note After successfully binding a socket to an IP address and port on 
 * the system, start listening passively for incoming connections. 
 * The socket must be bound on a local port or the listen operation fails.
 */
int8_t wifi8_socket_listen(wifi8_t *ctx, int8_t sock, uint8_t backlog);

/**
 * @brief Asynchronous connect function.
 * @details The asynchronous connect function must be called after receiving
 * a valid socket ID from the @ref wifi8_socket_create function.
 * The application socket callback function is notified of the result 
 * of the connection attempt through the event @b SOCKET_MSG_CONNECT.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] sock : Socket ID, must hold a non negative value.
 * @param[in] pstr_addr : Address of the remote server.
 * @param[in] u8_addr_len : Size of the given socket address structure in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_socket_connect(wifi8_t *ctx, int8_t sock, wifi8_sockaddr_t *pstr_addr, uint8_t u8_addr_len);

/**
 * @brief Asynchronous sending function.
 * @details The asynchronous sending function, used to send data on a TCP/UDP socket.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] sock : Socket ID, must hold a non negative value.
 * @param[in] pv_send_buffer : Pointer to a buffer  holding data to be transmitted.
 * @param[in] u16_send_length : The buffer size in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Called by the application code when there is outgoing data 
 * available required to be sent on a specific socket handler.
 */
err_t wifi8_socket_send(wifi8_t *ctx, int8_t sock, void *pv_send_buffer, uint16_t u16_send_length);

/**
 * @brief Asynchronous sending function.
 * @details The asynchronous sending function, used to send data on a UDP socket.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] sock : Socket ID, must hold a non negative value.
 * @param[in] pv_send_buffer : Pointer to a buffer  holding data to be transmitted.
 * @param[in] u16_send_length : The buffer size in bytes.
 * @param[in] pstr_dest_addr : The destination address.
 * @param[in] u8_addr_len : Destination address length in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Called by the application code when there is 
 * data required to be sent on a UDP socket.
 */
err_t wifi8_socket_send_to(wifi8_t *ctx, int8_t sock, void *pv_send_buffer, uint16_t u16_send_length, wifi8_sockaddr_t *pstr_dest_addr, uint8_t u8_addr_len);

/**
 * @brief Asynchronous receive function.
 * @details The asynchronous receive function, used to retrieve data from a TCP stream.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] sock : Socket ID, must hold a non negative value.
 * @param[in] pv_recv_buf : Pointer to a buffer that will hold the received data.
 * @param[in] u16_buf_len : The buffer size in bytes.
 * @param[in] u32_timeoutmsec : Timeout for the recv function in milli-seconds. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Before calling the recv function, a successful socket connection status
 * must have been received through any of the two socket events
 * @b SOCKET_MSG_CONNECT or @b SOCKET_MSG_ACCEPT , from the socket callback.
 * Hence, indicating that the socket is already connected to a remote host.
 */
err_t wifi8_socket_receive(wifi8_t *ctx, int8_t sock, void *pv_recv_buf, uint16_t u16_buf_len, uint32_t u32_timeoutmsec);

/**
 * @brief Asynchronous receive function.
 * @details The asynchronous recvfrom function is used to retrieve data from a UDP socket.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] sock : Socket ID, must hold a non negative value.
 * @param[in] pv_recv_buf : Pointer to a buffer that will hold the received data.
 * @param[in] u16_buf_len : The buffer size in bytes.
 * @param[in] u32_timeoutmsec : Timeout for the recv function in milli-seconds. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The socket must already be bound to a local port before a call to the recvfrom function 
 * is made (i.e message @b  SOCKET_MSG_BIND is received with successful status in the socket callback).
 */
err_t wifi8_socket_receive_from(wifi8_t *ctx, int8_t sock, void *pv_recv_buf, uint16_t u16_buf_len, uint32_t u32_timeoutmsec);

/**
 * @brief Synchronous close function.
 * @details The synchronous close function, releases all the socket assigned resources.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] sock : Socket ID, must hold a non negative value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t wifi8_socket_close(wifi8_t *ctx, int8_t sock);

#ifdef __cplusplus
}
#endif
#endif // WIFI8_H

/*! @} */ // wifi8

// ------------------------------------------------------------------------ END
