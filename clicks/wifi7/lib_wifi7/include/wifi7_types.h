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
 * @file wifi7_types.h
 * @brief This file contains types and protocol constants for WiFi 7 Click Driver.
 * @details Public socket objects and callback payloads share this file with firmware command records.
 * @note Include wifi7.h for the application API. Wire records target the WINC15x0 19.5.4 protocol and use
 * little-endian integers, except IPv4 addresses and ports explicitly documented as network byte order.
 * Preserve protocol field order, sizes, and reserved padding; these records are transferred directly.
 */

#ifndef WIFI7_TYPES_H
#define WIFI7_TYPES_H

#include <stdint.h>

/**
 * @defgroup wifi7_types WiFi 7 Types and Constants
 * @brief Firmware constants, socket objects, and callback payloads used by WiFi 7 Click.
 * @ingroup wifi7
 */

/**
 * @addtogroup wifi7_types
 * @{
 */

#define WIFI7_FW_MAJOR                      19                              /**< Expected firmware major version. */
#define WIFI7_DRIVER_VERSION                0x1354                          /**< Packed host protocol version 19.5.4. */
/**
 * @brief Boot handshake packing versions 19.5.4 and 19.3.0.
 */
#define WIFI7_DRIVER_INFO                   0x13301354ul
/**
 * @brief Firmware compatibility error returned by startup.
 */
#define WIFI7_ERROR_FW_VERSION              -2
/**
 * @brief Maximum wake-release handshake polling iterations.
 */
#define WIFI7_WAKE_POLL_LIMIT               1000
#define WIFI7_HIF_POLL_LIMIT                1000                            /**< Maximum HIF allocation polling iterations. */
#define WIFI7_EFUSE_STATUS_REG              0x1014                          /**< eFuse loading status register. */
#define WIFI7_RF_REV_REG                    0x13F4                          /**< RF hardware revision register. */
/**
 * @brief Firmware RAM address base used for shared records.
 */
#define WIFI7_RAM_BASE                      0x30000ul
/**
 * @brief Required reserved bit in the startup configuration.
 */
#define WIFI7_HAVE_RESERVED1_BIT            WIFI7_NBIT8
#define WIFI7_SPI_MAX_SPEED                 48000000ul                      /**< Driver SPI speed limit in Hz. */
#define WIFI7_M2M_STA_CMD_BASE              40                              /**< First station command identifier. */
#define WIFI7_M2M_CONFIG_CMD_BASE           1                               /**< First configuration command identifier. */
#define WIFI7_CMD_INTERNAL_WRITE            0xC3                            /**< SPI internal-register write opcode. */
#define WIFI7_CMD_INTERNAL_READ             0xC4                            /**< SPI internal-register read opcode. */
#define WIFI7_CMD_DMA_EXT_WRITE             0xC7                            /**< SPI extended DMA write opcode. */
#define WIFI7_CMD_DMA_EXT_READ              0xC8                            /**< SPI extended DMA read opcode. */
#define WIFI7_CMD_SINGLE_WRITE              0xC9                            /**< SPI 32-bit register write opcode. */
#define WIFI7_CMD_SINGLE_READ               0xCA                            /**< SPI 32-bit register read opcode. */
#define WIFI7_CMD_RESET                     0xCF                            /**< SPI command-parser reset opcode. */
#define WIFI7_DATA_PKT_SZ_8K                ( 8 * 1024 )                    /**< 8192-byte SPI DMA packet size. */
#define WIFI7_DATA_PKT_SZ                   WIFI7_DATA_PKT_SZ_8K            /**< SPI DMA packet size in bytes. */
#define WIFI7_NBIT31                        ( 0x80000000ul )                /**< Bit 31 mask. */
#define WIFI7_NBIT8                         ( 0x00000100ul )                /**< Bit 8 mask. */
#define WIFI7_NBIT2                         ( 0x00000004ul )                /**< Bit 2 mask. */
#define WIFI7_NBIT1                         ( 0x00000002ul )                /**< Bit 1 mask. */
#define WIFI7_NBIT0                         ( 0x00000001ul )                /**< Bit 0 mask. */
#define WIFI7_NMI_PERIPH_REG_BASE           0x1000                          /**< WINC peripheral register base address. */
#define WIFI7_NMI_CHIPID                    ( WIFI7_NMI_PERIPH_REG_BASE )   /**< WINC chip identification register. */
#define WIFI7_NMI_GP_REG_1                  ( 0x14A0 )                      /**< Firmware startup configuration register. */
/**
 * @brief Pointer to the firmware shared register record.
 */
#define WIFI7_NMI_GP_REG_2                  ( 0xC0008ul )
/**
 * @brief Boot status and HIF request allocation register.
 */
#define WIFI7_NMI_STATE_REG                 ( 0x108C )
#define WIFI7_BOOTROM_REG                   ( 0xC000Cul )                   /**< Boot ROM state and firmware start register. */
/**
 * @brief Packed firmware and minimum host driver versions.
 */
#define WIFI7_NMI_REV_REG                   ( 0x207ACul )
#define WIFI7_M2M_WAIT_FOR_HOST_REG         ( 0x207BCul )                   /**< Boot ROM host-wait status register. */
#define WIFI7_M2M_FINISH_INIT_STATE         0x02532636ul                    /**< Firmware initialization-complete signature. */
#define WIFI7_M2M_FINISH_BOOT_ROM           0x10ADD09Eul                    /**< Boot ROM ready signature. */
#define WIFI7_M2M_START_FIRMWARE            0xEF522F61ul                    /**< Boot ROM command to start normal firmware. */
#define WIFI7_REV_3A0                       ( 0x3A0 )                       /**< 3A0 hardware revision value. */
/**
 * @brief Nonzero when an identifier belongs to the NMC1000 family.
 * @details Driver protocol constant used by the WINC15x0 implementation.
 */
#define WIFI7_IS_NMC1000( id )              ( ( ( id ) & 0xFFFFF000ul ) == 0x100000ul )
/**
 * @brief Nonzero when an identifier belongs to the WINC1500 family.
 * @details Driver protocol constant used by the WINC15x0 implementation.
 */
#define WIFI7_IS_NMC1500( id )              ( ( ( id ) & 0xFFFFF000ul ) == 0x150000ul )
/**
 * @brief Extract the hardware revision portion of an identifier.
 */
#define WIFI7_REV( id )                     ( ( ( id ) & 0x00000FFFul ) )
#define WIFI7_HAVE_USE_PMU_BIT              ( WIFI7_NBIT1 )                 /**< Enable PMU use in the startup configuration. */
/**
 * @brief WINC interrupt register base address.
 */
#define WIFI7_NMI_INTR_REG_BASE             ( WIFI7_NMI_PERIPH_REG_BASE + 0xA00 )
/**
 * @brief WINC interrupt output pin multiplexer register.
 */
#define WIFI7_NMI_PIN_MUX_0                 ( WIFI7_NMI_PERIPH_REG_BASE + 0x408 )
#define WIFI7_NMI_INTR_ENABLE               ( WIFI7_NMI_INTR_REG_BASE )     /**< WINC interrupt enable register. */
#define WIFI7_TCP_SOCK_MAX                  ( 7 )                           /**< Number of TCP slots; descriptors 0-6. */
#define WIFI7_UDP_SOCK_MAX                  4                               /**< Number of UDP slots; descriptors 7-10. */
/**
 * @brief Total number of host socket slots.
 */
#define WIFI7_MAX_SOCKET                    ( WIFI7_TCP_SOCK_MAX + WIFI7_UDP_SOCK_MAX )
/**
 * @brief WINC memory reservation before Ethernet headers, bytes.
 */
#define WIFI7_ETHERNET_HEADER_OFFSET        ( 34 )
#define WIFI7_ETHERNET_HEADER_LENGTH        ( 14 )                          /**< Ethernet header length in bytes. */
#define WIFI7_TCP_IP_HEADER_LENGTH          ( 40 )                          /**< TCP and IPv4 header reservation in bytes. */
#define WIFI7_UDP_IP_HEADER_LENGTH          ( 28 )                          /**< UDP and IPv4 header reservation in bytes. */
/**
 * @brief IP header offset after the HIF prefix, bytes.
 * @details Driver protocol constant used by the WINC15x0 implementation.
 */
#define WIFI7_IP_PACKET_OFFSET              ( WIFI7_ETHERNET_HEADER_LENGTH + WIFI7_ETHERNET_HEADER_OFFSET - \
                                              WIFI7_M2M_HIF_HDR_OFFSET )
/**
 * @brief TCP payload offset after the HIF prefix, bytes.
 */
#define WIFI7_TCP_TX_PACKET_OFFSET          ( WIFI7_IP_PACKET_OFFSET + WIFI7_TCP_IP_HEADER_LENGTH )
/**
 * @brief UDP payload offset after the HIF prefix, bytes.
 */
#define WIFI7_UDP_TX_PACKET_OFFSET          ( WIFI7_IP_PACKET_OFFSET + WIFI7_UDP_IP_HEADER_LENGTH )
/**
 * @brief Internal IP group request macro.
 * @details This macro submits a socket command through the shared HIF sender.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] req_id : Socket command opcode.
 * @param[in] req_args : Control record pointer, or NULL.
 * @param[in] req_size : Control record length in bytes.
 * @param[in] req_payload : Payload pointer, or NULL.
 * @param[in] req_payload_size : Payload length in bytes.
 * @param[in] req_payload_offset : Payload offset after the HIF prefix.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Driver-only helper; the referenced HIF sender is private to wifi7.c.
 */
#define WIFI7_SOCKET_REQUEST( ctx, req_id, req_args, req_size, req_payload, req_payload_size, req_payload_offset ) \
    wifi7_hif_send( ctx, WIFI7_M2M_REQ_GROUP_IP, req_id, req_args, req_size, req_payload, req_payload_size, req_payload_offset )

#define WIFI7_SOCKET_CMD_BIND               0x41                            /**< Firmware socket bind opcode. */
#define WIFI7_SOCKET_CMD_LISTEN             0x42                            /**< Firmware TCP listen opcode. */
#define WIFI7_SOCKET_CMD_ACCEPT             0x43                            /**< Firmware TCP accepted-client event opcode. */
#define WIFI7_SOCKET_CMD_CONNECT            0x44                            /**< Firmware peer connection opcode. */
#define WIFI7_SOCKET_CMD_SEND               0x45                            /**< Firmware socket send opcode. */
#define WIFI7_SOCKET_CMD_RECV               0x46                            /**< Firmware TCP receive opcode. */
#define WIFI7_SOCKET_CMD_SENDTO             0x47                            /**< Firmware UDP transmit opcode. */
#define WIFI7_SOCKET_CMD_RECVFROM           0x48                            /**< Firmware UDP receive opcode. */
#define WIFI7_SOCKET_CMD_CLOSE              0x49                            /**< Firmware socket close opcode. */
#define WIFI7_AF_INET                       2                               /**< IPv4 address family in host byte order. */
#define WIFI7_SOCK_STREAM                   1                               /**< TCP stream socket type. */
#define WIFI7_SOCK_DGRAM                    2                               /**< UDP datagram socket type. */
#define WIFI7_NMI_SPI_REG_BASE              0xE800                          /**< WINC SPI peripheral register base address. */
/**
 * @brief SPI CRC and packet-size configuration register.
 */
#define WIFI7_NMI_SPI_PROTOCOL_CONFIG       ( WIFI7_NMI_SPI_REG_BASE + 0x24 )
/**
 * @brief Clockless firmware-to-host handshake register.
 */
#define WIFI7_CORT_HOST_COMM                ( 0x10 )
/**
 * @brief Clockless host-to-firmware handshake register.
 */
#define WIFI7_HOST_CORT_COMM                ( 0x0B )
#define WIFI7_WAKE_CLK_REG                  ( 0x1 )                         /**< Clockless host wake-request register. */
#define WIFI7_CLOCKS_EN_REG                 ( 0x0F )                        /**< Clockless enabled-clocks status register. */
#define WIFI7_TIMEOUT                       ( 2000 )                        /**< Maximum startup polling iterations. */
#define WIFI7_WAKEUP_TRIALS                 ( 4 )                           /**< Maximum enabled-clock checks during wakeup. */
/**
 * @brief Firmware-to-host interrupt status and acknowledgement.
 */
#define WIFI7_WIFI_HOST_RCV_CTRL_0          ( 0x1070 )
#define WIFI7_WIFI_HOST_RCV_CTRL_1          ( 0x1084 )                      /**< Firmware-to-host receive message address. */
/**
 * @brief Host-to-firmware allocation request register.
 */
#define WIFI7_WIFI_HOST_RCV_CTRL_2          ( 0x1078 )
#define WIFI7_WIFI_HOST_RCV_CTRL_3          ( 0x106C )                      /**< Host-to-firmware submitted message address. */
#define WIFI7_WIFI_HOST_RCV_CTRL_4          ( 0x150400ul )                  /**< Host-to-firmware allocated buffer address. */
#define WIFI7_M2M_HIF_MAX_PACKET_SIZE       ( 1600 - 4 )                    /**< Maximum complete HIF message size in bytes. */
/**
 * @brief Eight-byte HIF prefix before the control record.
 */
#define WIFI7_M2M_HIF_HDR_OFFSET            ( sizeof( wifi7_hif_hdr_t ) + 4 )
/**
 * @brief Maximum send payload accepted by the driver, bytes.
 */
#define WIFI7_SOCKET_BUFFER_MAX_LENGTH      1400
#define WIFI7_SPI_RESP_RETRY_COUNT          ( 10 )                          /**< Maximum SPI response search count. */
/**
 * @brief Maximum retries for a register or DMA transaction.
 */
#define WIFI7_SPI_RETRY_COUNT               ( 10 )
#define WIFI7_M2M_MAC_ADDRES_LEN            6                               /**< MAC address length in bytes. */
#define WIFI7_M2M_MAX_SSID_LEN              33                              /**< SSID storage including one terminator byte. */
#define WIFI7_M2M_MAX_PSK_LEN               65                              /**< PSK storage including one terminator byte. */

/**
 * @brief WiFi 7 RF channel selection.
 * @details Channel values used by scan and station connection requests.
 * @note WIFI7_M2M_WIFI_CH_ALL selects all channels; individual requests use channel numbers 1-14.
 */
typedef enum
{
    WIFI7_M2M_WIFI_CH_1 = ( ( uint8_t ) 1 ),        /**< RF channel 1. */
    WIFI7_M2M_WIFI_CH_2,                            /**< RF channel 2. */
    WIFI7_M2M_WIFI_CH_3,                            /**< RF channel 3. */
    WIFI7_M2M_WIFI_CH_4,                            /**< RF channel 4. */
    WIFI7_M2M_WIFI_CH_5,                            /**< RF channel 5. */
    WIFI7_M2M_WIFI_CH_6,                            /**< RF channel 6. */
    WIFI7_M2M_WIFI_CH_7,                            /**< RF channel 7. */
    WIFI7_M2M_WIFI_CH_8,                            /**< RF channel 8. */
    WIFI7_M2M_WIFI_CH_9,                            /**< RF channel 9. */
    WIFI7_M2M_WIFI_CH_10,                           /**< RF channel 10. */
    WIFI7_M2M_WIFI_CH_11,                           /**< RF channel 11. */
    WIFI7_M2M_WIFI_CH_12,                           /**< RF channel 12. */
    WIFI7_M2M_WIFI_CH_13,                           /**< RF channel 13. */
    WIFI7_M2M_WIFI_CH_14,                           /**< RF channel 14. */
    WIFI7_M2M_WIFI_CH_ALL = ( ( uint8_t ) 255 )     /**< Scan all supported RF channels. */

} wifi7_m2m_scan_ch_t;

/**
 * @brief WiFi 7 authentication type.
 * @details Security values reported by scan and connection information callbacks.
 * @note wifi7_connect implements open and WPA/WPA2 personal authentication; WEP and 802.1X values can be reported
 * but are not accepted for connection.
 */
typedef enum
{
    WIFI7_M2M_WIFI_SEC_INVALID = 0,             /**< Invalid authentication value. */
    WIFI7_M2M_WIFI_SEC_OPEN,                    /**< Open network authentication. */
    WIFI7_M2M_WIFI_SEC_WPA_PSK,                 /**< WPA/WPA2 personal authentication. */
    WIFI7_M2M_WIFI_SEC_WEP,                     /**< Reported WEP security; connection not implemented. */
    WIFI7_M2M_WIFI_SEC_802_1X,                  /**< Reported enterprise security; connection not implemented. */
    WIFI7_M2M_WIFI_NUM_AUTH_TYPES               /**< Authentication enumeration upper bound. */

} wifi7_m2m_sec_type_t;

/**
 * @brief WiFi 7 connection state.
 * @details Firmware connection-state values supplied by wifi7_m2m_wifi_state_changed_t.
 * @note Association and DHCP address assignment are separate events.
 */
typedef enum
{
    WIFI7_M2M_WIFI_DISCONNECTED = 0,            /**< Station is disconnected. */
    WIFI7_M2M_WIFI_CONNECTED,                   /**< Station is associated; DHCP can still be pending. */
    WIFI7_M2M_WIFI_UNDEF = 0xFF                 /**< Undefined connection state. */

} wifi7_m2m_conn_state_t;

/**
 * @brief WiFi 7 station command identifiers.
 * @details WINC15x0 station command and event numbering for the 19.5.4 protocol.
 * @note Firmware command identifiers do not imply that every command has a public library API.
 */
typedef enum
{
    WIFI7_M2M_WIFI_REQ_CONNECT = WIFI7_M2M_STA_CMD_BASE,    /**< Station connection request. */
    WIFI7_M2M_WIFI_REQ_DEFAULT_CONNECT,                     /**< Cached-profile connection request. */
    WIFI7_M2M_WIFI_RESP_DEFAULT_CONNECT,                    /**< Cached-profile connection result. */
    WIFI7_M2M_WIFI_REQ_DISCONNECT,                          /**< Station disconnection request. */
    WIFI7_M2M_WIFI_RESP_CON_STATE_CHANGED,                  /**< Connection-state notification. */
    WIFI7_M2M_WIFI_REQ_SLEEP,                               /**< Power-save request. */
    WIFI7_M2M_WIFI_REQ_WPS_SCAN,                            /**< WPS scan request. */
    WIFI7_M2M_WIFI_REQ_WPS,                                 /**< WPS request or result. */
    WIFI7_M2M_WIFI_REQ_START_WPS,                           /**< Firmware-internal WPS start identifier. */
    WIFI7_M2M_WIFI_REQ_DISABLE_WPS,                         /**< WPS disable request. */
    WIFI7_M2M_WIFI_REQ_DHCP_CONF,                           /**< DHCP IPv4 configuration notification. */
    WIFI7_M2M_WIFI_RESP_IP_CONFIGURED,                      /**< Firmware-internal IP configuration identifier. */
    WIFI7_M2M_WIFI_RESP_IP_CONFLICT,                        /**< IPv4 address conflict notification. */
    WIFI7_M2M_WIFI_REQ_ENABLE_MONITORING,                   /**< Monitor-mode enable request. */
    WIFI7_M2M_WIFI_REQ_DISABLE_MONITORING,                  /**< Monitor-mode disable request. */
    WIFI7_M2M_WIFI_RESP_WIFI_RX_PACKET,                     /**< Monitor-mode received packet identifier. */
    WIFI7_M2M_WIFI_REQ_SEND_WIFI_PACKET,                    /**< Raw Wi-Fi packet transmit request. */
    WIFI7_M2M_WIFI_REQ_LSN_INT,                             /**< Listen-interval configuration request. */
    WIFI7_M2M_WIFI_REQ_DOZE,                                /**< Manual power-save doze request. */
    WIFI7_M2M_WIFI_MAX_STA_ALL                              /**< Station command enumeration upper bound. */

} wifi7_m2m_sta_cmd_t;

/**
 * @brief WiFi 7 configuration command identifiers.
 * @details WINC15x0 configuration command and event numbering for the 19.5.4 protocol.
 * @note Only the documented library requests and callbacks are implemented.
 */
typedef enum
{
    WIFI7_M2M_WIFI_REQ_RESTART = WIFI7_M2M_CONFIG_CMD_BASE,     /**< MAC-layer restart request. */
    WIFI7_M2M_WIFI_REQ_SET_MAC_ADDRESS,                         /**< MAC address configuration request. */
    WIFI7_M2M_WIFI_REQ_CURRENT_RSSI,                            /**< Current RSSI request. */
    WIFI7_M2M_WIFI_RESP_CURRENT_RSSI,                           /**< Current RSSI notification. */
    WIFI7_M2M_WIFI_REQ_GET_CONN_INFO,                           /**< Connection information request. */
    WIFI7_M2M_WIFI_RESP_CONN_INFO,                              /**< Connection information notification. */
    WIFI7_M2M_WIFI_REQ_SET_DEVICE_NAME,                         /**< Device-name configuration request. */
    WIFI7_M2M_WIFI_REQ_START_PROVISION_MODE,                    /**< Provisioning-mode start request. */
    WIFI7_M2M_WIFI_RESP_PROVISION_INFO,                         /**< Provisioning result notification. */
    WIFI7_M2M_WIFI_REQ_STOP_PROVISION_MODE,                     /**< Provisioning-mode stop request. */
    WIFI7_M2M_WIFI_REQ_SET_SYS_TIME,                            /**< System time configuration request. */
    WIFI7_M2M_WIFI_REQ_ENABLE_SNTP_CLIENT,                      /**< SNTP enable request. */
    WIFI7_M2M_WIFI_REQ_DISABLE_SNTP_CLIENT,                     /**< SNTP disable request. */
    WIFI7_M2M_WIFI_RESP_MEMORY_RECOVER,                         /**< Reserved firmware memory notification. */
    WIFI7_M2M_WIFI_REQ_CUST_INFO_ELEMENT,                       /**< Custom information-element configuration request. */
    WIFI7_M2M_WIFI_REQ_SCAN,                                    /**< Active scan request. */
    WIFI7_M2M_WIFI_RESP_SCAN_DONE,                              /**< Active scan completion notification. */
    WIFI7_M2M_WIFI_REQ_SCAN_RESULT,                             /**< One access-point scan result request. */
    WIFI7_M2M_WIFI_RESP_SCAN_RESULT,                            /**< One access-point scan result notification. */
    WIFI7_M2M_WIFI_REQ_SET_SCAN_OPTION,                         /**< Scan timing configuration request. */
    WIFI7_M2M_WIFI_REQ_SET_SCAN_REGION,                         /**< Scan region configuration request. */
    WIFI7_M2M_WIFI_REQ_SET_POWER_PROFILE,                       /**< Power profile configuration request. */
    WIFI7_M2M_WIFI_REQ_SET_TX_POWER,                            /**< Transmit-power configuration request. */
    WIFI7_M2M_WIFI_REQ_SET_BATTERY_VOLTAGE,                     /**< Battery-voltage input configuration request. */
    WIFI7_M2M_WIFI_REQ_SET_ENABLE_LOGS,                         /**< Firmware log enable request. */
    WIFI7_M2M_WIFI_REQ_GET_SYS_TIME,                            /**< System time request. */
    WIFI7_M2M_WIFI_RESP_GET_SYS_TIME,                           /**< System time notification. */
    WIFI7_M2M_WIFI_REQ_SEND_ETHERNET_PACKET,                    /**< Ethernet bypass transmit request. */
    WIFI7_M2M_WIFI_RESP_ETHERNET_RX_PACKET,                     /**< Ethernet bypass receive notification. */
    WIFI7_M2M_WIFI_REQ_SET_MAC_MCAST,                           /**< Multicast filter configuration request. */
    WIFI7_M2M_WIFI_REQ_GET_PRNG,                                /**< Random-byte request. */
    WIFI7_M2M_WIFI_RESP_GET_PRNG,                               /**< Random-byte notification. */
    WIFI7_M2M_WIFI_REQ_SCAN_SSID_LIST,                          /**< SSID-list scan request. */
    WIFI7_M2M_WIFI_REQ_SET_GAINS,                               /**< RF gain configuration request. */
    WIFI7_M2M_WIFI_REQ_PASSIVE_SCAN,                            /**< Passive scan request. */
    WIFI7_M2M_WIFI_REQ_CONG_AUTO_RATE,                          /**< Automatic rate configuration request. */
    WIFI7_M2M_WIFI_MAX_CONFIG_ALL                               /**< Configuration command enumeration upper bound. */

} wifi7_m2m_config_cmd_t;

/**
 * @brief WiFi 7 socket callback identifiers.
 * @details Event identifiers passed to wifi7_app_socket_cb_t.
 * @note WIFI7_SOCKET_MSG_DNS_RESOLVE is retained for numbering compatibility; DNS resolution is not exposed.
 */
typedef enum
{
    WIFI7_SOCKET_MSG_BIND = 1,                  /**< Bind completion; wifi7_socket_bind_msg_t. */
    WIFI7_SOCKET_MSG_LISTEN,                    /**< Listen completion; wifi7_socket_listen_msg_t. */
    WIFI7_SOCKET_MSG_DNS_RESOLVE,               /**< Reserved DNS event; no public resolver API. */
    WIFI7_SOCKET_MSG_ACCEPT,                    /**< Accepted client; wifi7_socket_accept_msg_t. */
    WIFI7_SOCKET_MSG_CONNECT,                   /**< Connection result; wifi7_socket_connect_msg_t. */
    WIFI7_SOCKET_MSG_RECV,                      /**< TCP receive chunk; wifi7_socket_recv_msg_t. */
    WIFI7_SOCKET_MSG_SEND,                      /**< Send result; pointer to int16_t byte count or error. */
    WIFI7_SOCKET_MSG_SENDTO,                    /**< UDP send result; pointer to int16_t byte count or error. */
    WIFI7_SOCKET_MSG_RECVFROM                   /**< UDP receive chunk; wifi7_socket_recv_msg_t. */

} wifi7_socket_callback_msg_t;

/**
 * @brief WiFi 7 internal Wi-Fi state.
 * @details Software states returned by the internal state mapping function.
 * @note These states describe initialization, not association or DHCP status.
 */
typedef enum
{
    WIFI7_WIFI_STATE_DEINIT,                    /**< Wi-Fi driver is not initialized. */
    WIFI7_WIFI_STATE_INIT,                      /**< Host bus is initialized; firmware has not started. */
    WIFI7_WIFI_STATE_START,                     /**< Firmware startup has completed. */

} wifi7_wifi_state_t;

/**
 * @brief WiFi 7 Click return value data.
 * @details Predefined enum values for driver return values.
 * @note WIFI7_ERROR_FW_VERSION is the additional firmware compatibility error; socket allocation returns a
 * descriptor on success.
 */
typedef enum
{
    WIFI7_OK = 0,                               /**< Operation completed or request submitted successfully. */
    WIFI7_ERROR = -1                            /**< Invalid request or communication error. */

} wifi7_return_value_t;

/**
 * @brief WiFi 7 initialization mode values.
 * @details Mode names retained by the WINC initialization interface.
 * @note This driver accepts only WIFI7_M2M_WIFI_MODE_NORMAL.
 */
typedef enum
{
    WIFI7_M2M_WIFI_MODE_NORMAL = ( ( uint8_t ) 1 ),     /**< Normal firmware startup mode used by this driver. */
    WIFI7_M2M_WIFI_MODE_CONFIG,                         /**< Compatibility mode value; not implemented. */
    WIFI7_M2M_WIFI_MODE_ETHERNET,                       /**< Compatibility Ethernet mode value; not implemented. */
    WIFI7_M2M_WIFI_MODE_MAX                             /**< Mode enumeration upper bound. */

} wifi7_m2m_wifi_mode_t;

/**
 * @brief WiFi 7 HIF request group values.
 * @details Group identifiers encoded in the host interface header.
 * @note Only the Wi-Fi and IP groups are dispatched by this library.
 */
typedef enum
{
    WIFI7_M2M_REQ_GROUP_MAIN = 0,               /**< Main firmware request group. */
    WIFI7_M2M_REQ_GROUP_WIFI,                   /**< Wi-Fi command and event group. */
    WIFI7_M2M_REQ_GROUP_IP,                     /**< Socket command and event group. */
    WIFI7_M2M_REQ_GROUP_HIF,                    /**< Host interface control group. */
    WIFI7_M2M_REQ_GROUP_OTA,                    /**< OTA compatibility group; not dispatched. */
    WIFI7_M2M_REQ_GROUP_SSL,                    /**< TLS compatibility group; not dispatched. */
    WIFI7_M2M_REQ_GROUP_CRYPTO,                 /**< Cryptography compatibility group; not dispatched. */
    WIFI7_M2M_REQ_GROUP_SIGMA,                  /**< Certification compatibility group; not dispatched. */
    WIFI7_M2M_REQ_GROUP_INTERNAL                /**< Internal compatibility group; not dispatched. */

} wifi7_m2m_req_group_t;

/**
 * @brief WiFi 7 HIF request packet flags.
 * @details Opcode flags distinguishing control requests from requests with an additional payload.
 * @note WIFI7_M2M_REQ_DATA_PKT is removed from the serialized header opcode after buffer allocation.
 */
typedef enum
{
    WIFI7_M2M_REQ_CONFIG_PKT,                   /**< Control request without the data-packet flag. */
    WIFI7_M2M_REQ_DATA_PKT = 0x80               /**< Bit 7 marks a request containing a payload. */

} wifi7_m2m_reqpkt_t;

/**
 * @brief WiFi 7 module initialization state.
 * @details State values stored in the Click context during host bus setup and firmware startup.
 * @note WIFI7_NM_STATE_START permits HIF requests; a failed submitted transfer can invalidate this state.
 */
typedef enum
{
    WIFI7_NM_STATE_DEINIT,                      /**< Module is not ready for HIF requests. */
    WIFI7_NM_STATE_INIT,                        /**< SPI is ready; firmware has not started. */
    WIFI7_NM_STATE_START,                       /**< Firmware is ready for HIF requests. */

} wifi7_nm_state_t;

/**
 * @brief WiFi 7 generic socket address.
 * @details Generic 16-byte address object used by the socket API pointer parameters.
 * @note Construct wifi7_sockaddr_in_t for IPv4 and cast its pointer when calling bind, connect, or send_to.
 */
typedef struct
{
    uint16_t sa_family;                         /**< Address family in host byte order; WIFI7_AF_INET for IPv4. */
    uint8_t sa_data[ 14 ];                      /**< Address payload; use wifi7_sockaddr_in_t for IPv4 fields. */

} wifi7_sockaddr_t;

/**
 * @brief WiFi 7 IPv4 address.
 * @details Four IPv4 octets represented in a 32-bit object.
 * @note s_addr uses network byte order; copy the four octets into its storage rather than assuming host integer
 * order.
 */
typedef struct
{
    uint32_t s_addr;                            /**< IPv4 address in network byte order. */

} wifi7_in_addr_t;

/**
 * @brief WiFi 7 IPv4 socket address.
 * @details Address structure passed to IPv4 socket requests and returned for received datagrams and accepted
 * clients.
 * @note Set sin_family to WIFI7_AF_INET. sin_port and sin_addr use network byte order; initialize sin_zero to zero.
 */
typedef struct
{
    uint16_t sin_family;                        /**< IPv4 address family in host byte order; WIFI7_AF_INET. */
    uint16_t sin_port;                          /**< TCP or UDP port in network byte order. */
    wifi7_in_addr_t sin_addr;                   /**< IPv4 address in network byte order. */
    uint8_t sin_zero[ 8 ];                      /**< Reserved compatibility bytes; initialize to zero. */

} wifi7_sockaddr_in_t;

/**
 * @brief WiFi 7 socket receive callback payload.
 * @details Metadata supplied for WIFI7_SOCKET_MSG_RECV and WIFI7_SOCKET_MSG_RECVFROM.
 * @note Consume each chunk before returning; the same caller buffer is reused. A zero remaining size ends this
 * firmware reply, not necessarily the entire TCP application message.
 */
typedef struct
{
    uint8_t *pu8_buffer;                        /**< Caller receive buffer; NULL for closure or error. */
    int16_t s16_buffer_size;                    /**< Chunk bytes; zero is closure, negative is a firmware error. */
    uint16_t u16_remaining_size;                /**< Unread bytes remaining in this firmware reply. */
    wifi7_sockaddr_in_t str_remote_addr;        /**< Sender address and port, meaningful for UDP datagrams. */

} wifi7_socket_recv_msg_t;

/**
 * @brief WiFi 7 firmware revision record.
 * @details Firmware version, minimum host version, and build information read from the module.
 * @note This is a 40-byte firmware record. Keep all reserved fields and padding; build strings are terminated by
 * wifi7_get_full_firmware_version.
 */
typedef struct
{
    uint32_t chip_id;                           /**< Hardware identifier reported by the firmware record. */
    uint8_t u8_firmware_major;                  /**< Firmware major version. */
    uint8_t u8_firmware_minor;                  /**< Firmware minor version. */
    uint8_t u8_firmware_patch;                  /**< Firmware patch version. */
    uint8_t u8_driver_major;                    /**< Minimum supported host driver major version. */
    uint8_t u8_driver_minor;                    /**< Minimum supported host driver minor version. */
    uint8_t u8_driver_patch;                    /**< Minimum supported host driver patch version. */
    uint8_t build_date[ 12 ];                   /**< Firmware build date string including terminator space. */
    uint8_t build_time[ 9 ];                    /**< Firmware build time string including terminator space. */
    uint8_t reserved;                           /**< Firmware record padding byte. */
    uint16_t svn_version;                       /**< Firmware source revision identifier. */
    uint16_t padding[ 3 ];                      /**< Reserved words including the final alignment bytes. */

} wifi7_m2m_rev_t;

/**
 * @brief WiFi 7 firmware socket address.
 * @details Eight-byte address prefix embedded in WINC socket command and reply records.
 * @note Protocol structure; preserve field order. Port and IPv4 address use network byte order.
 */
typedef struct
{
    uint16_t u16_family;                        /**< Address family in host byte order. */
    uint16_t u16_port;                          /**< TCP or UDP port in network byte order. */
    uint32_t u32ip_addr;                        /**< IPv4 address in network byte order. */

} wifi7_sock_addr_t;

/**
 * @brief WiFi 7 firmware send command.
 * @details Control record sent with a TCP payload or UDP datagram.
 * @note Protocol structure; all reserved fields are initialized to zero.
 */
typedef struct
{
    int8_t sock;                                /**< Allocated socket descriptor. */
    uint8_t u8_void;                            /**< Reserved byte; zero. */
    uint16_t u16_data_size;                     /**< Payload length in bytes. */
    wifi7_sock_addr_t str_addr;                 /**< Explicit destination for send_to requests. */
    uint16_t u16_session_id;                    /**< Host-assigned socket session identifier. */
    uint16_t u16_void;                          /**< Reserved word; zero. */

} wifi7_send_cmd_t;

/**
 * @brief WiFi 7 firmware shared register record.
 * @details Firmware address words obtained through WIFI7_NMI_GP_REG_2.
 * @note The low 16 bits of u32_firmware_ota_rev locate the running firmware revision record.
 */
typedef struct
{
    uint32_t u32_mac_efuse_mib;                 /**< Firmware MAC, eFuse, and MIB address word. */
    uint32_t u32_firmware_ota_rev;              /**< Packed firmware revision record offsets. */

} wifi7_gp_regs_t;

/**
 * @brief WiFi 7 connection-state callback payload.
 * @details Connection-state and reason bytes supplied by WIFI7_M2M_WIFI_RESP_CON_STATE_CHANGED.
 * @note The payload is valid only during the application callback.
 */
typedef struct
{
    uint8_t u8_curr_state;                      /**< Current wifi7_m2m_conn_state_t value. */
    uint8_t u8_err_code;                        /**< Firmware connection-change reason code. */
    uint8_t __pad16__[ 2 ];                     /**< Firmware alignment padding. */

} wifi7_m2m_wifi_state_changed_t;

/**
 * @brief WiFi 7 scan completion callback payload.
 * @details Result count and status supplied by WIFI7_M2M_WIFI_RESP_SCAN_DONE.
 * @note Only a zero scan status updates the context with the number of discovered access points.
 */
typedef struct
{
    uint8_t u8_numof_ch;                        /**< Number of discovered access points, despite the field name. */
    int8_t s8_scan_state;                       /**< Zero on success; nonzero firmware scan status otherwise. */
    uint8_t __pad16__[ 2 ];                     /**< Firmware alignment padding. */

} wifi7_m2m_scan_done_t;

/**
 * @brief WiFi 7 access-point scan result.
 * @details Access-point identity, security, channel, and RSSI supplied by WIFI7_M2M_WIFI_RESP_SCAN_RESULT.
 * @note The driver terminates au8ssid before invoking the application callback.
 */
typedef struct
{
    uint8_t u8index;                                /**< Zero-based access-point index in the scan results. */
    int8_t s8rssi;                                  /**< Received signal strength in dBm. */
    uint8_t u8_auth_type;                           /**< Reported wifi7_m2m_sec_type_t authentication value. */
    uint8_t u8ch;                                   /**< RF channel number. */
    uint8_t au8bssid[ 6 ];                          /**< Six-byte access-point BSSID. */
    uint8_t au8ssid[ WIFI7_M2M_MAX_SSID_LEN ];      /**< Access-point SSID with terminator space. */
    uint8_t _pad8_;                                 /**< Firmware alignment padding. */

} wifi7_m2m_wifiscan_result_t;

/**
 * @brief WiFi 7 firmware listen command.
 * @details Control record requesting passive TCP listening.
 * @note The descriptor must refer to an allocated and bound TCP socket.
 */
typedef struct
{
    int8_t sock;                                /**< TCP socket descriptor. */
    uint8_t u8_back_log;                        /**< Requested pending connection queue limit. */
    uint16_t u16_session_id;                    /**< Host-assigned socket session identifier. */

} wifi7_listen_cmd_t;

/**
 * @brief WiFi 7 bind completion callback payload.
 * @details Firmware status supplied by WIFI7_SOCKET_MSG_BIND.
 * @note A successful request return and a successful bind callback are separate results.
 */
typedef struct
{
    int8_t status;                              /**< Zero on success; negative firmware socket error otherwise. */

} wifi7_socket_bind_msg_t;

/**
 * @brief WiFi 7 firmware bind command.
 * @details Control record associating a socket with a local IPv4 address and port.
 * @note Protocol structure; the application supplies wifi7_sockaddr_in_t through the public API.
 */
typedef struct
{
    wifi7_sock_addr_t str_addr;                 /**< Local address and port. */
    int8_t sock;                                /**< Allocated TCP or UDP descriptor. */
    uint8_t u8_void;                            /**< Reserved byte; zero. */
    uint16_t u16_session_id;                    /**< Host-assigned socket session identifier. */

} wifi7_bind_cmd_t;

/**
 * @brief WiFi 7 firmware receive command.
 * @details Eight-byte receive request used by production firmware 19.5.4.
 * @note This protocol has no receive-capacity field; the host splits larger replies into caller-buffer-sized
 * chunks.
 */
typedef struct
{
    uint32_t u32_timeoutmsec;                   /**< Receive timeout in ms; 0xFFFFFFFF waits indefinitely. */
    int8_t sock;                                /**< Allocated TCP or UDP descriptor. */
    uint8_t u8_void;                            /**< Reserved byte; zero. */
    uint16_t u16_session_id;                    /**< Host-assigned socket session identifier. */

} wifi7_recv_cmd_t;

/**
 * @brief WiFi 7 firmware close command.
 * @details Control record requesting socket closure.
 * @note There is no close-completion callback in the implemented API.
 */
typedef struct
{
    int8_t sock;                                /**< Socket descriptor to close. */
    uint8_t u8_dummy;                           /**< Reserved byte; zero. */
    uint16_t u16_session_id;                    /**< Host-assigned socket session identifier. */

} wifi7_close_cmd_t;

/**
 * @brief WiFi 7 driver socket bookkeeping.
 * @details Host-only state for an allocated socket and its pending receive buffer.
 * @note Managed by the library; application code must not modify these fields.
 */
typedef struct
{
    uint8_t *pu8_user_buffer;                   /**< Receive buffer retained until completion or closure. */
    uint16_t u16_user_buffer_size;              /**< Capacity of the retained receive buffer in bytes. */
    uint16_t u16_session_id;                    /**< Nonzero session value distinguishing descriptor reuse. */
    uint16_t u16_data_offset;                   /**< Compatibility field; unused for implemented plain sockets. */
    uint8_t b_is_used;                          /**< 1 when this descriptor slot is allocated, otherwise 0. */
    uint8_t b_is_recv_pending;                  /**< 1 while a receive request or its chunks are pending. */

} wifi7_socket_t;

/**
 * @brief WiFi 7 firmware bind or listen reply.
 * @details Descriptor, completion status, and session identifier used for bind and listen events.
 * @note Session validation discards replies belonging to a previous descriptor allocation.
 */
typedef struct
{
    int8_t sock;                                /**< Socket descriptor associated with this reply. */
    int8_t s8_status;                           /**< Zero on success; negative firmware socket error otherwise. */
    uint16_t u16_session_id;                    /**< Session identifier echoed by firmware. */

} wifi7_bind_reply_t;

/**
 * @brief WiFi 7 listen completion callback payload.
 * @details Firmware status supplied by WIFI7_SOCKET_MSG_LISTEN.
 * @note Successful listening can subsequently produce WIFI7_SOCKET_MSG_ACCEPT events.
 */
typedef struct
{
    int8_t status;                              /**< Zero on success; negative firmware socket error otherwise. */

} wifi7_socket_listen_msg_t;

/**
 * @brief WiFi 7 accepted-client callback payload.
 * @details Client descriptor and remote IPv4 address supplied by WIFI7_SOCKET_MSG_ACCEPT.
 * @note The callback sock argument identifies the listening socket; this structure identifies the new client.
 */
typedef struct
{
    int8_t sock;                                /**< New TCP client descriptor, or a negative firmware error. */
    wifi7_sockaddr_in_t str_addr;               /**< Remote client address and port in network byte order. */

} wifi7_socket_accept_msg_t;

/**
 * @brief WiFi 7 firmware connection reply.
 * @details Connection status record received from the IP request group.
 * @note The application-data offset is retained for protocol layout; plain socket sends use fixed packet offsets.
 */
typedef struct
{
    int8_t sock;                                /**< Socket descriptor associated with this reply. */
    int8_t s8_error;                            /**< Zero on success; negative firmware socket error otherwise. */
    uint16_t u16_app_data_offset;               /**< Firmware application-data offset. */

} wifi7_connect_reply_t;

/**
 * @brief WiFi 7 connection completion callback payload.
 * @details Socket descriptor and firmware result supplied by WIFI7_SOCKET_MSG_CONNECT.
 * @note Wait for s8_error equal to zero before sending on a TCP client socket.
 */
typedef struct
{
    int8_t sock;                                /**< Descriptor passed to the connection request. */
    int8_t s8_error;                            /**< Zero on success; negative firmware socket error otherwise. */

} wifi7_socket_connect_msg_t;

/**
 * @brief WiFi 7 firmware scan-result request.
 * @details Control record selecting one previously discovered access point.
 * @note The index is validated against the result count stored in the Click context.
 */
typedef struct
{
    uint8_t u8_index;                           /**< Zero-based access-point result index. */
    uint8_t __pad24__[ 3 ];                     /**< Firmware alignment padding; zero. */

} wifi7_m2m_req_scan_result_t;

/**
 * @brief WiFi 7 firmware scan request.
 * @details RF channel and timeout record used for active scanning.
 * @note The public scan function submits an active scan and leaves passive_scan_time at zero.
 */
typedef struct
{
    uint8_t u8_ch_num;                          /**< Channel 1-14, or WIFI7_M2M_WIFI_CH_ALL. */
    uint8_t reserved;                           /**< Reserved byte; zero. */
    uint16_t passive_scan_time;                 /**< Passive scan timeout in ms; unused for active requests. */

} wifi7_m2m_scan_t;

/**
 * @brief WiFi 7 firmware authentication record.
 * @details 68-byte security prefix in the production firmware connection command.
 * @note Only open and WPA/WPA2 personal connection requests are implemented.
 */
typedef struct
{
    uint8_t au8_psk[ WIFI7_M2M_MAX_PSK_LEN ];       /**< Terminated passphrase or hexadecimal PSK storage. */
    uint8_t u8_sec_type;                            /**< WIFI7_M2M_WIFI_SEC_OPEN or WIFI7_M2M_WIFI_SEC_WPA_PSK. */
    uint8_t padding[ 2 ];                           /**< Firmware alignment padding; zero. */

} wifi7_m2m_wifi_sec_t;

/**
 * @brief WiFi 7 firmware station connection command.
 * @details 108-byte connection record submitted with WIFI7_M2M_WIFI_REQ_CONNECT.
 * @note Field order, sizes, and padding must match production firmware 19.5.4.
 */
typedef struct
{
    wifi7_m2m_wifi_sec_t str_sec;                   /**< Authentication type and credential storage. */
    uint16_t u16_channel;                           /**< Channel 1-14, or WIFI7_M2M_WIFI_CH_ALL. */
    uint8_t au8_ssid[ WIFI7_M2M_MAX_SSID_LEN ];     /**< Terminated SSID storage. */
    uint8_t u8_no_save_cred;                        /**< Always 1 to prevent credential writes to module flash. */
    uint8_t padding[ 4 ];                           /**< Firmware alignment padding; zero. */

} wifi7_m2m_wifi_connect_t;

/**
 * @brief WiFi 7 firmware receive reply.
 * @details Descriptor, source address, status, and payload offset read before copying received bytes.
 * @note Payload bounds and socket session are validated before application delivery.
 */
typedef struct
{
    wifi7_sock_addr_t str_remote_addr;          /**< Sender address and port. */
    int16_t s16_recv_status;                    /**< Payload byte count, zero closure, or negative error. */
    uint16_t u16_data_offset;                   /**< Payload offset from the HIF control record address. */
    int8_t sock;                                /**< Socket descriptor associated with the receive request. */
    uint8_t u8_void;                            /**< Reserved firmware byte. */
    uint16_t u16_session_id;                    /**< Session identifier echoed by firmware. */

} wifi7_recv_reply_t;

/**
 * @brief WiFi 7 firmware send reply.
 * @details Descriptor, transmitted byte count, and session value supplied for send and send_to completion.
 * @note The application receives a pointer to s16_sent_bytes during its socket callback.
 */
typedef struct
{
    int8_t sock;                                /**< Socket descriptor associated with the send request. */
    uint8_t u8_void;                            /**< Reserved firmware byte. */
    int16_t s16_sent_bytes;                     /**< Sent byte count or negative firmware socket error. */
    uint16_t u16_session_id;                    /**< Session identifier echoed by firmware. */
    uint16_t u16_void;                          /**< Reserved firmware word. */

} wifi7_send_reply_t;

/**
 * @brief WiFi 7 firmware accepted-client reply.
 * @details Remote address and descriptors supplied when a listening socket accepts a client.
 * @note The final word is the firmware application-data offset; it is ignored for plain sockets.
 */
typedef struct
{
    wifi7_sock_addr_t str_addr;                 /**< Remote client address and port. */
    int8_t s_listen_sock;                       /**< Listening TCP socket descriptor. */
    int8_t s_connected_sock;                    /**< Accepted TCP descriptor, or a negative firmware error. */
    uint16_t u16_void;                          /**< Firmware application-data offset. */

} wifi7_accept_reply_t;

/**
 * @brief WiFi 7 firmware connection command.
 * @details Control record requesting a socket peer connection.
 * @note Protocol structure; SSL/TLS operation is not exposed by this library.
 */
typedef struct
{
    wifi7_sock_addr_t str_addr;                 /**< Remote IPv4 address and port. */
    int8_t sock;                                /**< Allocated socket descriptor. */
    uint8_t u8_ssl_flags;                       /**< Zero; TLS flags are not implemented. */
    uint16_t u16_session_id;                    /**< Host-assigned socket session identifier. */

} wifi7_connect_cmd_t;

/**
 * @brief WiFi 7 connection information callback payload.
 * @details SSID, security, IPv4, MAC, signal strength, and channel supplied by WIFI7_M2M_WIFI_RESP_CONN_INFO.
 * @note The driver terminates ac_ssid before invoking the application callback.
 */
typedef struct
{
    char ac_ssid[ WIFI7_M2M_MAX_SSID_LEN ];     /**< Reported access-point SSID with terminator space. */
    uint8_t u8_sec_type;                        /**< Reported wifi7_m2m_sec_type_t authentication value. */
    uint8_t au8ip_addr[ 4 ];                    /**< Reported IPv4 address in network byte order. */
    uint8_t au8mac_address[ 6 ];                /**< Six-byte MAC address reported by firmware. */
    int8_t s8rssi;                              /**< Received signal strength in dBm. */
    uint8_t current_channel;                    /**< Current RF channel, 1-14. */
    uint8_t __pad16__[ 2 ];                     /**< Firmware alignment padding. */

} wifi7_m2m_conn_info_t;

/**
 * @brief WiFi 7 DHCP configuration callback payload.
 * @details IPv4 configuration supplied by WIFI7_M2M_WIFI_REQ_DHCP_CONF.
 * @note Address fields use network byte order. The callback object is valid only until the callback returns.
 */
typedef struct
{
    uint32_t u32_static_ip;                     /**< IPv4 address assigned by DHCP. */
    uint32_t u32_gateway;                       /**< Default gateway IPv4 address. */
    uint32_t u32dns;                            /**< Primary DNS server IPv4 address. */
    uint32_t u32_alternate_dns;                 /**< Secondary DNS server IPv4 address, if provided. */
    uint32_t u32_subnet_mask;                   /**< IPv4 subnet mask. */
    uint32_t u32_dhcp_lease_time;               /**< DHCP lease duration in seconds. */

} wifi7_m2mip_config_t;

/**
 * @brief WiFi 7 host interface header.
 * @details Four-byte firmware header carrying group, opcode, and complete message length.
 * @note WIFI7_M2M_HIF_HDR_OFFSET adds four reserved bytes to this header before the control record.
 */
typedef struct
{
    uint8_t u8_gid;                             /**< Firmware request group. */
    uint8_t u8_opcode;                          /**< Request or event opcode without the data-packet flag. */
    uint16_t u16_length;                        /**< Total HIF message length including the eight-byte prefix. */

} wifi7_hif_hdr_t;

/**
 * @brief WiFi 7 application Wi-Fi callback type.
 * @details This callback receives supported Wi-Fi notifications while wifi7_handle_events processes a firmware
 * message.
 * @param[in] u8_msg_type : Wi-Fi event identifier.
 * @param[in] pv_msg : Event-specific payload pointer described below.
 * @return Nothing.
 * @li @c WIFI7_M2M_WIFI_RESP_CON_STATE_CHANGED - #wifi7_m2m_wifi_state_changed_t.
 * @li @c WIFI7_M2M_WIFI_REQ_DHCP_CONF - #wifi7_m2mip_config_t.
 * @li @c WIFI7_M2M_WIFI_RESP_SCAN_DONE - #wifi7_m2m_scan_done_t.
 * @li @c WIFI7_M2M_WIFI_RESP_SCAN_RESULT - #wifi7_m2m_wifiscan_result_t.
 * @li @c WIFI7_M2M_WIFI_RESP_CONN_INFO - #wifi7_m2m_conn_info_t.
 * @li @c WIFI7_M2M_WIFI_RESP_CURRENT_RSSI - pointer to the first int8_t RSSI byte in dBm.
 * @li @c WIFI7_M2M_WIFI_RESP_IP_CONFLICT - pointer to uint32_t IPv4 address in network byte order.
 * @note Payload objects are valid only during the callback. Copy required values before returning; never call
 * wifi7_handle_events recursively.
 */
typedef void ( *wifi7_app_wifi_cb_t ) ( uint8_t u8_msg_type, void *pv_msg );

/**
 * @brief WiFi 7 application socket callback type.
 * @details This callback receives socket completion events while wifi7_handle_events processes the IP request
 * group.
 * @param[in] sock : Socket descriptor; the listening descriptor for WIFI7_SOCKET_MSG_ACCEPT.
 * @param[in] u8_msg : Event from wifi7_socket_callback_msg_t.
 * @param[in] pv_msg : Event payload: bind/listen/accept/connect metadata, receive metadata, or int16_t send result.
 * @return Nothing.
 * See #wifi7_socket_callback_msg_t object definition for event payload types.
 * @note Callback metadata is valid only during the call. Receive buffers belong to the caller and are reused for
 * subsequent chunks. Consume each chunk before returning and reissue reception only after u16_remaining_size
 * reaches zero.
 */
typedef void ( *wifi7_app_socket_cb_t ) ( int8_t sock, uint8_t u8_msg, void *pv_msg );

/*! @} */ // wifi7_types

#endif // WIFI7_TYPES_H

// ------------------------------------------------------------------------ END
