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



#ifndef WIFI8_T
#define WIFI8_T

#include "stdint.h"

#define M2M_STA_CMD_BASE 40/*!< The base value of all the Host configuration commands opcodes.*/
#define M2M_CONFIG_CMD_BASE 1/*!< The base value of all the Station mode host commands opcodes.*/
#define M2M_AP_CMD_BASE 70/*!< The base value of all the Access Point mode host commands opcodes.*/
#define M2M_SERVER_CMD_BASE 100/*!< The base value of all the Power Save mode host commands codes.*/
#define M2M_GEN_CMD_BASE 105/*!< The base value of additional host wifi command opcodes. 
Usage restrictions (eg STA mode only) should always be made clear at the API layer in any case.*/

/**********************
 * OTA GROUP requests
 */
#define M2M_OTA_CMD_BASE 100
#define WIFI8_CMD_INTERNAL_WRITE 0xc3
#define WIFI8_CMD_INTERNAL_READ 0xc4
#define WIFI8_CMD_DMA_EXT_WRITE 0xc7
#define WIFI8_CMD_DMA_EXT_READ 0xc8
#define WIFI8_CMD_SINGLE_WRITE 0xc9
#define WIFI8_CMD_SINGLE_READ 0xca
#define WIFI8_CMD_RESET 0xcf

#define WIFI8_SPI_RESP_RETRY_COUNT (10)
#define WIFI8_SPI_RETRY_COUNT (10)
#define WIFI8_DATA_PKT_SZ_256 256
#define WIFI8_DATA_PKT_SZ_512 512
#define WIFI8_DATA_PKT_SZ_1K 1024
#define WIFI8_DATA_PKT_SZ_4K (4 * 1024)
#define WIFI8_DATA_PKT_SZ_8K (8 * 1024)
#define WIFI8_DATA_PKT_SZ WIFI8_DATA_PKT_SZ_8K

#define PROGRAM_START 0x26961735ul
#define BOOT_SUCCESS 0x10add09eul
#define BOOT_START 0x12345678ul

#define NBIT31 (0x80000000ul)
#define NBIT30 (0x40000000ul)
#define NBIT29 (0x20000000ul)
#define NBIT28 (0x10000000ul)
#define NBIT27 (0x08000000ul)
#define NBIT26 (0x04000000ul)
#define NBIT25 (0x02000000ul)
#define NBIT24 (0x01000000ul)
#define NBIT23 (0x00800000ul)
#define NBIT22 (0x00400000ul)
#define NBIT21 (0x00200000ul)
#define NBIT20 (0x00100000ul)
#define NBIT19 (0x00080000ul)
#define NBIT18 (0x00040000ul)
#define NBIT17 (0x00020000ul)
#define NBIT16 (0x00010000ul)
#define NBIT15 (0x00008000ul)
#define NBIT14 (0x00004000ul)
#define NBIT13 (0x00002000ul)
#define NBIT12 (0x00001000ul)
#define NBIT11 (0x00000800ul)
#define NBIT10 (0x00000400ul)
#define NBIT9 (0x00000200ul)
#define NBIT8 (0x00000100ul)
#define NBIT7 (0x00000080ul)
#define NBIT6 (0x00000040ul)
#define NBIT5 (0x00000020ul)
#define NBIT4 (0x00000010ul)
#define NBIT3 (0x00000008ul)
#define NBIT2 (0x00000004ul)
#define NBIT1 (0x00000002ul)
#define NBIT0 (0x00000001ul)

#define NMI_PERIPH_REG_BASE 0x1000
#define NMI_CHIPID (NMI_PERIPH_REG_BASE)
#define rNMI_GP_REG_0 (0x149c)
#define rNMI_GP_REG_1 (0x14A0)
#define rNMI_GLB_RESET (0x1400)
#define rNMI_BOOT_RESET_MUX (0x1118)
#define NMI_STATE_REG (0x108c)
#define BOOTROM_REG (0xc000cul)
#define NMI_REV_REG (0x207acul) /*Also, Used to load ATE firmware from SPI Flash and to ensure that it is running too*/
#define M2M_WAIT_FOR_HOST_REG (0x207bcul)
#define M2M_FINISH_INIT_STATE 0x02532636ul
#define M2M_FINISH_BOOT_ROM 0x10add09eul
#define M2M_START_FIRMWARE 0xef522f61ul
#define M2M_START_PS_FIRMWARE 0x94992610ul

#define M2M_ATE_FW_START_VALUE (0x3C1CD57Dul) /*Also, Change this value in boot_firmware if it will be changed here*/
#define M2M_ATE_FW_IS_UP_VALUE (0xD75DC1C3ul) /*Also, Change this value in ATE (Burst) firmware if it will be changed here*/

#define REV_2B0 (0x2B0)
#define REV_B0 (0x2B0)
#define REV_3A0 (0x3A0)
#define CHIP_ID_3000D (0x3000D0ul)

#define GET_CHIPID() nmi_get_chipid()
#define ISNMC1000(id) (((id & 0xfffff000ul) == 0x100000ul) ? 1 : 0)
#define ISNMC1500(id) (((id & 0xfffff000ul) == 0x150000ul) ? 1 : 0)
#define ISNMC3400(id) (((id & 0xfff0f000ul) == 0x300000ul) ? 1 : 0)
#define REV(id) (((id)&0x00000ffful))
#define EFUSED_MAC(value) (value & 0xffff0000ul)

#define rHAVE_SDIO_IRQ_GPIO_BIT (NBIT0)
#define rHAVE_USE_PMU_BIT (NBIT1)
#define rHAVE_SLEEP_CLK_SRC_RTC_BIT (NBIT2)
#define rHAVE_SLEEP_CLK_SRC_XO_BIT (NBIT3)
#define rHAVE_EXT_PA_INV_TX_RX (NBIT4)
#define rHAVE_LEGACY_RF_SETTINGS (NBIT5)
#define rHAVE_LOGS_DISABLED_BIT (NBIT6)
#define rHAVE_ETHERNET_MODE_BIT (NBIT7)

#define NMI_GLB_RESET_0 (NMI_PERIPH_REG_BASE + 0x400)
#define NMI_INTR_REG_BASE (NMI_PERIPH_REG_BASE + 0xa00)
#define NMI_PIN_MUX_0 (NMI_PERIPH_REG_BASE + 0x408)
#define NMI_INTR_ENABLE (NMI_INTR_REG_BASE)
#define GET_UINT32(X, Y) (X[0 + Y] + ((uint32_t)X[1 + Y] << 8) + ((uint32_t)X[2 + Y] << 16) + ((uint32_t)X[3 + Y] << 24))

/* Selection of HIF_INFO
*/
#define M2M_HIF_INFO_SHIFT (0)
#define M2M_HIF_INFO_MASK (0xffff)
/* Subdivision of HIF_INFO
*/
#define M2M_HIF_BLOCK_SHIFT (14)
#define M2M_HIF_BLOCK_MASK (0x3)
#define M2M_HIF_LEVEL_SHIFT (0)
#define M2M_HIF_LEVEL_MASK (0x3fff)
/* Subdivision of HIF_LEVEL
*/
#define M2M_HIF_MAJOR_SHIFT (8)
#define M2M_HIF_MAJOR_MASK (0x3f)
#define M2M_HIF_MINOR_SHIFT (0)
#define M2M_HIF_MINOR_MASK (0xff)

#define M2M_GET_HIF_INFO(hif_ver) ((uint16_t)(((hif_ver) >> M2M_HIF_INFO_SHIFT) & M2M_HIF_INFO_MASK))
#define M2M_GET_HIF_BLOCK(hif_info) ((uint8_t)(((hif_info) >> M2M_HIF_BLOCK_SHIFT) & M2M_HIF_BLOCK_MASK))
#define M2M_GET_HIF_LEVEL(hif_info) ((uint16_t)(((hif_info) >> M2M_HIF_LEVEL_SHIFT) & M2M_HIF_LEVEL_MASK))
#define M2M_GET_HIF_MAJOR(hif_info) ((uint8_t)(((hif_info) >> M2M_HIF_MAJOR_SHIFT) & M2M_HIF_MAJOR_MASK))
#define M2M_GET_HIF_MINOR(hif_info) ((uint8_t)(((hif_info) >> M2M_HIF_MINOR_SHIFT) & M2M_HIF_MINOR_MASK))

#define M2M_MAKE_HIF_INFO(hif_level) (                                    \
    (((uint16_t)(hif_level)&M2M_HIF_LEVEL_MASK) << M2M_HIF_LEVEL_SHIFT) | \
    (((uint16_t)M2M_HIF_BLOCK_VALUE & M2M_HIF_BLOCK_MASK) << M2M_HIF_BLOCK_SHIFT))

#define M2M_AUTH_1X_USER_LEN_MAX 100
#define M2M_AUTH_1X_PASSWORD_LEN_MAX 256

#define M2M_HIF_BLOCK_VALUE (2)/*!< Drv/Fw blocking compatibility check.*/
#define M2M_HIF_MAJOR_VALUE (1)/*!< Drv/Fw major compatibility check.*/
#define M2M_HIF_MINOR_VALUE (4)/*!< Drv/Fw minor compatibility check.*/

#define TCP_SOCK_MAX (7)/*!< Maximum number of simultaneous TCP sockets.*/

#define UDP_SOCK_MAX 4/*!< Maximum number of simultaneous UDP sockets.*/

#define RAW_SOCK_MAX 1
#define MAX_SOCKET (TCP_SOCK_MAX + UDP_SOCK_MAX + RAW_SOCK_MAX)

#define SOCKET_BUFFER_SIZE 1472

#define TLS_RECORD_HEADER_LENGTH (5)
#define ETHERNET_HEADER_OFFSET (34)
#define ETHERNET_HEADER_LENGTH (14)
#define TCP_IP_HEADER_LENGTH (40)
#define UDP_IP_HEADER_LENGTH (28)

#define IP_PACKET_OFFSET (ETHERNET_HEADER_LENGTH + ETHERNET_HEADER_OFFSET - M2M_HIF_HDR_OFFSET)

#define TCP_TX_PACKET_OFFSET (IP_PACKET_OFFSET + TCP_IP_HEADER_LENGTH)
#define UDP_TX_PACKET_OFFSET (IP_PACKET_OFFSET + UDP_IP_HEADER_LENGTH)
#define SSL_TX_PACKET_OFFSET (TCP_TX_PACKET_OFFSET + TLS_RECORD_HEADER_LENGTH)

#define SOCKET_REQUEST(ctx, req_id, req_args, req_size, req_payload, req_payload_size, req_payload_offset) \
    hif_send(ctx, M2M_REQ_GROUP_IP, req_id, req_args, req_size, req_payload, req_payload_size, req_payload_offset)

#define SSL_FLAGS_ACTIVE NBIT0

#define M2M_802_1X_UNENCRYPTED_USERNAME_FLAG 0x80 /*!< Flag to indicate that the 802.1x user-name 
    should be sent (unencrypted) in the initial EAP identity response. Intended for use with EAP-TLS only.*/
#define M2M_802_1X_PREPEND_DOMAIN_FLAG 0x40/*!< Flag to indicate that the 802.1x domain name should be prepended to the user-name:
    "Domain\Username". If the flag is not set then domain name is appended to the user-name:
    "Username@Domain". (Note that the '@' or '\' must be included in the domain name.)*/
#define M2M_802_1X_MSCHAP2_FLAG 0x01/*!< Flag to indicate 802.1x MsChapV2 credentials: domain/user-name/password.*/

#define SOCKET_CMD_BIND 0x41
#define SOCKET_CMD_LISTEN 0x42
#define SOCKET_CMD_ACCEPT 0x43
#define SOCKET_CMD_CONNECT 0x44
#define SOCKET_CMD_SEND 0x45
#define SOCKET_CMD_RECV 0x46
#define SOCKET_CMD_SENDTO 0x47
#define SOCKET_CMD_RECVFROM 0x48
#define SOCKET_CMD_CLOSE 0x49
#define SOCKET_CMD_DNS_RESOLVE 0x4A
#define SOCKET_CMD_SSL_CONNECT 0x4B
#define SOCKET_CMD_SSL_SEND 0x4C
#define SOCKET_CMD_SSL_RECV 0x4D
#define SOCKET_CMD_SSL_CLOSE 0x4E
#define SOCKET_CMD_SET_SOCKET_OPTION 0x4F
#define SOCKET_CMD_SSL_CREATE 0x50
#define SOCKET_CMD_SSL_SET_SOCK_OPT 0x51
#define SOCKET_CMD_PING 0x52
#define SOCKET_CMD_SSL_CONNECT_ALPN 0x53
#define SOCKET_CMD_RAW_SET_SOCK_OPT 0x54
#define PING_ERR_SUCCESS 0
#define PING_ERR_DEST_UNREACH 1
#define PING_ERR_TIMEOUT 2
#define HOSTNAME_MAX_SIZE 100
#define AF_INET 2
#define SOCK_ERR_NO_ERROR 0
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOCK_RAW 3
#define SOCKET_FLAGS_SSL 0x01
#define SOCKET_FLAGS_IPPROTO_RAW 0x02
#define RAW_SOCK_ID (TCP_SOCK_MAX + UDP_SOCK_MAX)

#define _htons(A) (uint16_t)((((uint16_t)(A)) << 8) | (((uint16_t)(A)) >> 8))

/*! Retain endianness of 32bit word (In the case that Host is LE) */
#define NM_BSP_B_L_32(x) (x)
/*! Retain endianness of 16bit word (In the case that Host is LE) */
#define NM_BSP_B_L_16(x) (x)

#define NMI_PERIPH_REG_BASE 0x1000
#define NMI_CHIPID (NMI_PERIPH_REG_BASE)
#define NMI_PIN_MUX_0 (NMI_PERIPH_REG_BASE + 0x408)
#define NMI_INTR_ENABLE (NMI_INTR_REG_BASE)

#define NMI_SPI_REG_BASE 0xe800
#define NMI_SPI_CTL (NMI_SPI_REG_BASE)
#define NMI_SPI_MASTER_DMA_ADDR (NMI_SPI_REG_BASE + 0x4)
#define NMI_SPI_MASTER_DMA_COUNT (NMI_SPI_REG_BASE + 0x8)
#define NMI_SPI_SLAVE_DMA_ADDR (NMI_SPI_REG_BASE + 0xc)
#define NMI_SPI_SLAVE_DMA_COUNT (NMI_SPI_REG_BASE + 0x10)
#define NMI_SPI_TX_MODE (NMI_SPI_REG_BASE + 0x20)
#define NMI_SPI_PROTOCOL_CONFIG (NMI_SPI_REG_BASE + 0x24)
#define NMI_SPI_INTR_CTL (NMI_SPI_REG_BASE + 0x2c)

#define NMI_SPI_PROTOCOL_OFFSET (NMI_SPI_PROTOCOL_CONFIG - NMI_SPI_REG_BASE)

#define NMI_GLB_RESET_0 (NMI_PERIPH_REG_BASE + 0x400)
#define NMI_INTR_REG_BASE (NMI_PERIPH_REG_BASE + 0xa00)
#define NMI_PIN_MUX_0 (NMI_PERIPH_REG_BASE + 0x408)
#define NMI_INTR_ENABLE (NMI_INTR_REG_BASE)

/*SPI and I2C only*/
#define CORT_HOST_COMM (0x14)
#define HOST_CORT_COMM (0x0e)
#define WAKE_CLK_REG (0x1)
#define CLOCKS_EN_REG (0x13)

#define TIMEOUT (2000)
#define WAKEUP_TRIALS (4)

#define NMI_AHB_DATA_MEM_BASE 0x30000ul
#define NMI_AHB_SHARE_MEM_BASE 0xd0000ul      

#define WIFI_HOST_RCV_CTRL_0 (0x1070)
#define WIFI_HOST_RCV_CTRL_1 (0x1084)
#define WIFI_HOST_RCV_CTRL_2 (0x1078)
#define WIFI_HOST_RCV_CTRL_3 (0x106c)
#define WIFI_HOST_RCV_CTRL_4 (0x150400ul)

#define INTERRUPT_CORTUS_0_3000D0 (0x10a8)
#define INTERRUPT_CORTUS_1_3000D0 (0x10ac)
#define INTERRUPT_CORTUS_2_3000D0 (0x10b0)
#define INTERRUPT_CORTUS_3_3000D0 (0x10b4)

#define M2M_HIF_MAX_PACKET_SIZE (1600 - 4)
#define M2M_HIF_HDR_OFFSET (sizeof(wifi8_hif_hdr_t) + 4)

/*!< The base value of all the OTA mode host commands opcodes.
 * The OTA messages have their own group so op codes can extended from 1 to M2M_MAX_GRP_NUM_REQ.
*/
#define SOCKET_BUFFER_MAX_LENGTH 1400
#define M2M_MAX_GRP_NUM_REQ (127)

#define SOCKET_CMD_RAW_SET_SOCK_OPT 0x54

/*
    Special codes for managing HIF restriction to OTA rollback/switch only
*/
#define HIF_OTA_RB_ONLY 0xFFFF
#define HIFCODE_OTA_RB ((M2M_REQ_GROUP_OTA << 8) | M2M_OTA_REQ_ROLLBACK)
#define HIFCODE_OTA_SW ((M2M_REQ_GROUP_OTA << 8) | M2M_OTA_REQ_SWITCH_FIRMWARE)
/*
    Codes for new HIF messages (since last HIF major increase).
    Only need ones which are host->winc.
    Each entry is formed of ((GroupId << 8) | OpCode)
*/
#define HIFCODE_SSL_WRITECERT ((M2M_REQ_GROUP_SSL << 8) | M2M_SSL_REQ_WRITE_OWN_CERTS)
#define HIFCODE_WIFI_PASSIVESCAN ((M2M_REQ_GROUP_WIFI << 8) | M2M_WIFI_REQ_PASSIVE_SCAN)
#define HIFCODE_WIFI_CONN ((M2M_REQ_GROUP_WIFI << 8) | M2M_WIFI_REQ_CONN)
#define HIFCODE_WIFI_CONN_PARAM ((M2M_REQ_GROUP_WIFI << 8) | M2M_WIFI_IND_CONN_PARAM)
#define HIFCODE_WIFI_DELETE_CRED ((M2M_REQ_GROUP_WIFI << 8) | M2M_WIFI_REQRSP_DELETE_APID)
#define HIFCODE_WIFI_START_PROV_MODE ((M2M_REQ_GROUP_WIFI << 8) | M2M_WIFI_REQ_START_PROVISION_MODE)
#define HIFCODE_WIFI_ENABLE_AP ((M2M_REQ_GROUP_WIFI << 8) | M2M_WIFI_REQ_ENABLE_AP)
#define HIFCODE_IP_RAW_SOCK_OPT ((M2M_REQ_GROUP_IP << 8) | SOCKET_CMD_RAW_SET_SOCK_OPT)

#define NMI_PERIPH_REG_BASE 0x1000
#define NMI_CHIPID (NMI_PERIPH_REG_BASE)
#define NMI_PIN_MUX_0 (NMI_PERIPH_REG_BASE + 0x408)
#define NMI_INTR_ENABLE (NMI_INTR_REG_BASE)

#define NMI_SPI_REG_BASE 0xe800
#define NMI_SPI_CTL (NMI_SPI_REG_BASE)
#define NMI_SPI_MASTER_DMA_ADDR (NMI_SPI_REG_BASE + 0x4)
#define NMI_SPI_MASTER_DMA_COUNT (NMI_SPI_REG_BASE + 0x8)
#define NMI_SPI_SLAVE_DMA_ADDR (NMI_SPI_REG_BASE + 0xc)
#define NMI_SPI_SLAVE_DMA_COUNT (NMI_SPI_REG_BASE + 0x10)
#define NMI_SPI_TX_MODE (NMI_SPI_REG_BASE + 0x20)
#define NMI_SPI_PROTOCOL_CONFIG (NMI_SPI_REG_BASE + 0x24)
#define NMI_SPI_INTR_CTL (NMI_SPI_REG_BASE + 0x2c)

#define NMI_SPI_PROTOCOL_OFFSET (NMI_SPI_PROTOCOL_CONFIG - NMI_SPI_REG_BASE)

#define SPI_BASE NMI_SPI_REG_BASE

#define SPI_RESP_RETRY_COUNT (10)
#define SPI_RETRY_COUNT (10)
#define DATA_PKT_SZ_256 256
#define DATA_PKT_SZ_512 512
#define DATA_PKT_SZ_1K 1024
#define DATA_PKT_SZ_4K (4 * 1024)
#define DATA_PKT_SZ_8K (8 * 1024)
#define DATA_PKT_SZ DATA_PKT_SZ_8K

/*
    List of new HIF messages (since last HIF major increase).
    Only need to list ones which are host->winc.
    Additionally, entry 0 used to indicate OTA RB/SW only.
*/
#define NEW_HIF_LIST                  \
    HIF_OTA_RB_ONLY,                  \
        HIFCODE_SSL_WRITECERT,        \
        HIFCODE_WIFI_PASSIVESCAN,     \
        HIFCODE_WIFI_CONN,            \
        HIFCODE_WIFI_CONN_PARAM,      \
        HIFCODE_WIFI_DELETE_CRED,     \
        HIFCODE_WIFI_START_PROV_MODE, \
        HIFCODE_WIFI_ENABLE_AP,       \
        HIFCODE_IP_RAW_SOCK_OPT

#define WIFI_1X_TLS_HS_FLAGS_PEER_AUTH NBIT1
#define WIFI_1X_TLS_HS_FLAGS_PEER_CERTTIMECHECK NBIT2
#define WIFI_1X_TLS_HS_FLAGS_REQUIRE_TIME NBIT3
#define WIFI_1X_TLS_HS_FLAGS_SESSION_CACHING NBIT4
#define WIFI_1X_TLS_HS_FLAGS_SPECIFY_ROOTCERT NBIT6

#define WIFI_1X_TLS_HS_FLAGS_DEFAULT ( \
    WIFI_1X_TLS_HS_FLAGS_PEER_AUTH | WIFI_1X_TLS_HS_FLAGS_PEER_CERTTIMECHECK | WIFI_1X_TLS_HS_FLAGS_SESSION_CACHING)

#define HIF_BLACKLIST_SZ (sizeof(gau16_hif_blacklist) / sizeof(gau16_hif_blacklist[0]))

#define WEP_104_KEY_SIZE ((uint8_t)13)

#define PSK_CALC_LEN 40

#define M2M_MAC_ADDRES_LEN 6

#define MAX_TRX_CFG_SZ 8
#define M2M_CRED_ENCRYPT_FLAG 0x02
#define M2M_WIFI_CONN_BSSID_FLAG 0x01
#define M2M_CRED_STORE_FLAG 0x01

#define M2M_OTA_CMD_BASE 100
#define M2M_MAX_GRP_NUM_REQ (127)
#define WEP_40_KEY_SIZE ((uint8_t)5)
#define WEP_104_KEY_SIZE ((uint8_t)13)
#define WEP_40_KEY_STRING_SIZE ((uint8_t)10)
#define WEP_104_KEY_STRING_SIZE ((uint8_t)26)
#define WEP_KEY_MAX_INDEX ((uint8_t)4)
#define M2M_SCAN_DEFAULT_NUM_SLOTS (2)
#define M2M_SCAN_DEFAULT_SLOT_TIME (20)
#define M2M_SCAN_DEFAULT_PASSIVE_SLOT_TIME (300)
#define M2M_SCAN_DEFAULT_NUM_PROBE (2)
#define M2M_FASTCONNECT_DEFAULT_RSSI_THRESH (-45)

#define NM_BUS_MAX_TRX_SZ 256

#define M2M_MAX_SSID_LEN 33

#define WEP_104_KEY_STRING_SIZE ((uint8_t)26)

#define M2M_MAX_PSK_LEN 65

typedef enum
{
    M2M_WIFI_CH_1 = ((uint8_t)1),/*!< Channel 1. */
    M2M_WIFI_CH_2,/*!< Channel 2. */
    M2M_WIFI_CH_3,/*!< Channel 3. */
    M2M_WIFI_CH_4,/*!< Channel 4. */
    M2M_WIFI_CH_5,/*!< Channel 5. */
    M2M_WIFI_CH_6,/*!< Channel 6. */
    M2M_WIFI_CH_7,/*!< Channel 7. */
    M2M_WIFI_CH_8,/*!< Channel 8. */
    M2M_WIFI_CH_9,/*!< Channel 9. */
    M2M_WIFI_CH_10,/*!< Channel 10. */
    M2M_WIFI_CH_11,/*!< Channel 11. */
    M2M_WIFI_CH_12,/*!< Channel 12. */
    M2M_WIFI_CH_13,/*!< Channel 13. */
    M2M_WIFI_CH_14,/*!< Channel 14. */
    M2M_WIFI_CH_ALL = ((uint8_t)255)
} wifi8_m2m_scan_ch_t;

typedef enum
{
    M2M_WIFI_SEC_INVALID = 0,/*!< Invalid security type. */
    M2M_WIFI_SEC_OPEN,/*!< Wi-Fi network is not secured. */
    M2M_WIFI_SEC_WPA_PSK,/*!< Wi-Fi network is secured with WPA/WPA2 personal(PSK). */
    M2M_WIFI_SEC_WEP,/*!< Security type WEP (40 or 104) OPEN OR SHARED. */
    M2M_WIFI_SEC_802_1X,/*!< Wi-Fi network is secured with WPA/WPA2 Enterprise.IEEE802.1x. */
    M2M_WIFI_NUM_AUTH_TYPES/*!< Upper limit for enum value. */
} wifi8_m2m_sec_type_t;

typedef enum
{
    M2M_WIFI_DISCONNECTED = 0,/*!< Wi-Fi state is disconnected. */
    M2M_WIFI_CONNECTED,/*!< Wi-Fi state is connected. */
    M2M_WIFI_ROAMED,/*!< Wi-Fi state is roamed to new AP. */
    M2M_WIFI_UNDEF = 0xff/*!< Undefined Wi-Fi State. */
} wifi8_m2m_conn_state_t;

typedef enum
{
    M2M_WIFI_REQ_CONNECT = M2M_STA_CMD_BASE,/*!< Request to connect with a specified AP. 
    This command is deprecated in favour of @ref M2M_WIFI_REQ_CONN.*/
    M2M_WIFI_REQ_DEFAULT_CONNECT,/*!< Request to connect with a cached AP. */
    M2M_WIFI_RESP_DEFAULT_CONNECT,/*!< Response for the default connect.*/
    M2M_WIFI_REQ_DISCONNECT,/*!< Request to disconnect from the AP. */
    M2M_WIFI_RESP_CON_STATE_CHANGED,/*!< Response to indicate a change in the connection state. */
    M2M_WIFI_REQ_SLEEP,/*!< Request to sleep. */
    M2M_WIFI_REQ_WPS_SCAN,/*!< Request to WPS scan. */
    M2M_WIFI_REQ_WPS,/*!< Request to start WPS. */
    M2M_WIFI_REQ_START_WPS,/*!< This command is for internal use by the WINC and should not be used by the host driver. */
    M2M_WIFI_REQ_DISABLE_WPS,/*!< Request to disable WPS. */
    M2M_WIFI_REQ_DHCP_CONF,/*!< Response to indicate the obtained IP address.*/
    M2M_WIFI_RESP_IP_CONFIGURED,/*!< This command is for internal use by the WINC and should not be used by the host driver. */
    M2M_WIFI_RESP_IP_CONFLICT,/*!< Response to indicate a conflict in obtained IP address. The user should re attempt the DHCP request. */
    M2M_WIFI_REQ_ENABLE_MONITORING,/*!< Request to enable monitor mode. */
    M2M_WIFI_REQ_DISABLE_MONITORING,/*!< Request to disable monitor mode. */
    M2M_WIFI_RESP_WIFI_RX_PACKET,/*!< Response to indicate a packet was received in monitor mode. */
    M2M_WIFI_REQ_SEND_WIFI_PACKET,/*!< Request to send a packet in monitor mode. */
    M2M_WIFI_REQ_LSN_INT,/*!< Request to set the listen interval. */
    M2M_WIFI_REQ_DOZE,/*!< Request to doze */
    M2M_WIFI_REQ_GET_PRNG,/*!< Request PRNG. */
    M2M_WIFI_RESP_GET_PRNG,/*!< Response for PRNG. */
    M2M_WIFI_REQ_CONN,/*!< New command to connect with AP. This replaces M2M_WIFI_REQ_CONNECT. 
    (Firmware continues to handle M2M_WIFI_REQ_CONNECT for backwards compatibility purposes.)*/
    M2M_WIFI_IND_CONN_PARAM,/*!< Provide extra information (such as Enterprise client certificate) required for connection. */
    M2M_WIFI_MAX_STA_ALL
} wifi8_m2m_sta_cmd_t;

typedef enum
{
    M2M_WIFI_REQ_RESTART = M2M_CONFIG_CMD_BASE,/*!< Restart the WINC MAC layer, it's doesn't restart the IP layer. */
    M2M_WIFI_REQ_SET_MAC_ADDRESS,/*!< Set the WINC mac address (not possible for production effused boards). */
    M2M_WIFI_REQ_CURRENT_RSSI,/*!< Request the current connected AP RSSI. */
    M2M_WIFI_RESP_CURRENT_RSSI,/*!< Response to M2M_WIFI_REQ_CURRENT_RSSI with the RSSI value. */
    M2M_WIFI_REQ_RESTRICT_BLE,/*!< Request restrict ble.  */
    M2M_WIFI_REQ_UNRESTRICT_BLE,/*!< Request unrestrict ble.    */
    M2M_WIFI_REQ_GET_CONN_INFO,/*!< Request connection information. */
    M2M_WIFI_RESP_CONN_INFO,/*!< Response to M2M_WIFI_REQ_GET_CONN_INFO with the connection information. */
    M2M_WIFI_REQ_SET_DEVICE_NAME,/*!< Request to set WINC device name property. */
    M2M_WIFI_REQ_START_PROVISION_MODE_LEGACY,/*!< Request to start provisioning mode. */
    M2M_WIFI_RESP_PROVISION_INFO,/*!< Response to the host with the provisioning information.*/
    M2M_WIFI_REQ_STOP_PROVISION_MODE,/*!< Request to stop provision mode. */
    M2M_WIFI_REQ_SET_SYS_TIME,/*!< Request to set system time. */
    M2M_WIFI_REQ_ENABLE_SNTP_CLIENT, /*!< Request to enable the simple network time protocol to 
    get the time from the Internet. This is required for security purposes. */
    M2M_WIFI_REQ_DISABLE_SNTP_CLIENT,/*!< Request to disable the simple network time protocol for applications that do not need it. */
    M2M_WIFI_RESP_MEMORY_RECOVER,/*!< Reserved for debugging */
    M2M_WIFI_REQ_CUST_INFO_ELEMENT,/*!< Request to add custom information to the Beacons IE. */
    M2M_WIFI_REQ_SCAN,/*!< Request scan command. */
    M2M_WIFI_RESP_SCAN_DONE,/*!< Response to notify scan complete. */
    M2M_WIFI_REQ_SCAN_RESULT,/*!< Request for scan results. */
    M2M_WIFI_RESP_SCAN_RESULT,/*!< Response to provide the scan results.  */
    M2M_WIFI_REQ_SET_SCAN_OPTION,/*!< Request to set scan options "slot time, slot number .. etc".   */
    M2M_WIFI_REQ_SET_SCAN_REGION,/*!< Request to set scan region. */
    M2M_WIFI_REQ_SET_POWER_PROFILE,/*!< Request to set the Power Profile. */
    M2M_WIFI_REQ_SET_TX_POWER,/*!< Request to set the TX Power. */
    M2M_WIFI_REQ_SET_BATTERY_VOLTAGE,/*!< Request to set the Battery Voltage. */
    M2M_WIFI_REQ_SET_ENABLE_LOGS,/*!< Request to enable logs. */
    M2M_WIFI_REQ_GET_SYS_TIME,/*!< Request to get system time. */
    M2M_WIFI_RESP_GET_SYS_TIME,/*!< Response to retrieve the system time. */
    M2M_WIFI_REQ_SEND_ETHERNET_PACKET,/*!< Request to send Ethernet packet in bypass mode. */
    M2M_WIFI_RESP_ETHERNET_RX_PACKET,/*!< Response to receive an Ethernet packet in bypass mode. */
    M2M_WIFI_REQ_SET_MAC_MCAST,/*!< Request to set multicast filters. */
    M2M_WIFI_REQ_BLE_API_SEND,/*!< Request to send an Encapsulated BLE API MSG */
    M2M_WIFI_RESP_BLE_API_RECV,/*!< Response to receive an Encapsulated BLE API MSG */
    M2M_WIFI_REQ_SET_GAIN_TABLE,/*!< Request to use Gain table from Flash */
    M2M_WIFI_RESP_SET_GAIN_TABLE,/*!< Response to fail to use Gain table from Flash */
    M2M_WIFI_REQ_PASSIVE_SCAN,/*!< Request a passive scan. */
    M2M_WIFI_REQ_CONFIG_SNTP,/*!< Configure NTP servers. */
    M2M_WIFI_REQ_START_PROVISION_MODE,/*!< Request to start provisioning mode. */

    /* This enum is now 'full' in the sense that (M2M_WIFI_REQ_START_PROVISION_MODE+1) == M2M_STA_CMD_BASE. 
     * Any new config values should be placed in tenuM2mGenCmd. */
    M2M_WIFI_MAX_CONFIG_ALL
} wifi8_m2m_config_cmd_t;

typedef enum
{
    SOCKET_MSG_BIND = 1,/*!< Bind socket event.*/
    SOCKET_MSG_LISTEN, /*!< Listen socket event.*/
    SOCKET_MSG_DNS_RESOLVE,/*!< DNS Resolution event.*/
    SOCKET_MSG_ACCEPT,/*!< Accept socket event.*/
    SOCKET_MSG_CONNECT,/*!< Connect socket event.*/
    SOCKET_MSG_RECV,/*!< Receive socket event.*/
    SOCKET_MSG_SEND,/*!< Send socket event.*/
    SOCKET_MSG_SENDTO,/*!< Sendto socket event.*/
    SOCKET_MSG_RECVFROM/*!< Recvfrom socket event.*/
} wifi8_socket_callback_msg_t;

typedef enum
{
    M2M_WIFI_REQRSP_DELETE_APID = M2M_GEN_CMD_BASE,/*!< Request/response to delete security credentials 
    from WINC flash. (Processing matches @ref tenuM2mConfigCmd.) */
    M2M_WIFI_REQ_ROAMING,/*!< Request to enable/disable wifi roaming.(Processing matches @ref tenuM2mConfigCmd.)*/
    M2M_WIFI_MAX_GEN_ALL
} wifi8_m2m_gen_cmd_t;

typedef enum
{
    M2M_WIFI_REQ_ENABLE_AP_LEGACY = M2M_AP_CMD_BASE,/*!< Request to enable AP mode. */
    M2M_WIFI_REQ_DISABLE_AP,/*!< Request to disable AP mode. */
    M2M_WIFI_REQ_ENABLE_AP,/*!< Request to enable AP mode. */
    M2M_WIFI_MAX_AP_ALL,
} wifi8_m2m_ap_cmd_t;

typedef enum
{
    SSID_MODE_VISIBLE = 0,/*!< SSID is visible to others. */
    SSID_MODE_HIDDEN/*!< SSID is hidden. */
} wifi8_m2m_ssid_mode_t;

typedef enum
{
    WIFI_STATE_DEINIT,/*!< Wifi is not initialized */
    WIFI_STATE_INIT,/*!< Wifi has been initialized. WINC flash access is possible via m2m_flash APIs. */
    WIFI_STATE_START,/*!< Wifi has started */
} wifi8_wifi_state_t;

/**
 * @brief WiFi 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WIFI8_OK = 0,
    WIFI8_ERROR = -1

} wifi8_return_value_t;

typedef enum
{
    M2M_WIFI_MODE_NORMAL = ((uint8_t)1),/*!< Customer firmware.*/
    M2M_WIFI_MODE_CONFIG,/*!< Production test firmware.*/
    M2M_WIFI_MODE_ETHERNET,/*!< Ethernet Mode*/
    M2M_WIFI_MODE_MAX
} wifi8_m2m_wifi_mode_t;

typedef enum
{
    M2M_REQ_GROUP_MAIN = 0,
    M2M_REQ_GROUP_WIFI,
    M2M_REQ_GROUP_IP,
    M2M_REQ_GROUP_HIF,
    M2M_REQ_GROUP_OTA,
    M2M_REQ_GROUP_SSL,
    M2M_REQ_GROUP_SIGMA,
    M2M_REQ_GROUP_INTERNAL
} wifi8_m2m_req_group_t;

typedef enum
{
    M2M_REQ_CONFIG_PKT,
    M2M_REQ_DATA_PKT = 0x80 /*BIT7*/
} wifi8_m2m_reqpkt_t;

typedef enum
{
    M2M_SSL_REQ_CERT_VERIF,
    M2M_SSL_REQ_ECC,
    M2M_SSL_RESP_ECC,
    M2M_SSL_RSV,
    M2M_SSL_REQ_WRITE_OWN_CERTS,
    M2M_SSL_REQ_SET_CS_LIST,
    M2M_SSL_RESP_SET_CS_LIST,
    M2M_SSL_RESP_WRITE_OWN_CERTS,
    M2M_SSL_REQ_SET_CERT_VERIF_MODE
} wifi8_m2m_ssl_cmd_t;

typedef enum
{
    NM_STATE_DEINIT,/*!< WINC is not initialized */
    NM_STATE_INIT,/*!< WINC has been initialized. SPI flash access is possible. */
    NM_STATE_START,/*!< WINC has started */
} wifi8_nm_state_t;

typedef enum
{
    M2M_OTA_REQ_NOTIF_SET_URL = M2M_OTA_CMD_BASE,/*!< Reserved. Do not use.*/
    M2M_OTA_REQ_NOTIF_CHECK_FOR_UPDATE,/*!< Reserved. Do not use.*/
    M2M_OTA_REQ_NOTIF_SCHED,/*!< Reserved. Do not use.*/
    M2M_OTA_REQ_START_UPDATE,/*!< Request to start an OTA update.*/
    M2M_OTA_REQ_SWITCH_FIRMWARE,/*!< Request to switch firmware.*/
    M2M_OTA_REQ_ROLLBACK,/*!< Request to perform an OTA rollback.*/
    M2M_OTA_REQ_ABORT,/*!< Request to abort OTA.*/
    M2M_OTA_RESP_NOTIF_UPDATE_INFO,/*!< Reserved. Do not use.*/
    M2M_OTA_RESP_UPDATE_STATUS,/*!< Response to indicate the OTA update status. */
    M2M_OTA_REQ_TEST,/*!< Reserved. Do not use.*/
    M2M_OTA_MAX_ALL,
} wifi8_m2m_ota_cmd_t;

typedef enum
{
    M2M_WIFI_REQ_CLIENT_CTRL = M2M_SERVER_CMD_BASE,/*!< Currently not supported.*/
    M2M_WIFI_RESP_CLIENT_INFO,/*!< Currently not supported.*/
    M2M_WIFI_REQ_SERVER_INIT,/*!< Currently not supported.*/
    M2M_WIFI_MAX_SERVER_ALL
} wifi8_m2m_server_cmd_t;

typedef enum
{
    WIFI_CRED_DONTSAVE,/*!< Credentials will not be stored in WINC flash. */
    WIFI_CRED_SAVE_UNENCRYPTED,/*!< Credentials will be stored unencrypted in WINC flash. */
    WIFI_CRED_SAVE_ENCRYPTED/*!< Credentials will be stored encrypted in WINC flash.
            The encryption is not secure; it is merely intended to prevent sensitive information
            being leaked by an opportunistic read of WINC flash contents.
            The encryption keys involve WINC efuse contents, so WINC efuses should not be written
            while this option is in use. */
} wifi8_cred_store_option_t;

typedef enum
{
    WIFI_1X_BYPASS_SERVER_AUTH,
    /*!< Server authentication for 802.1x connections. Values are of type int.\n
        0: Authenticate server; Default, Recommended.\n
        1: Bypass server authentication.\n*/
    WIFI_1X_TIME_VERIF_MODE,
    /*!< Mode for checking expiry of server certificate chain.
        Values are of type @ref tenuTlsCertExpSettings.
        Default is @ref TLS_CERT_EXP_CHECK_EN_IF_SYS_TIME.*/
    WIFI_1X_SESSION_CACHING,
    /*!< TLS session caching on/off for 802.1x connections. Values are of type int.\n
        0: Session caching off.\n
        1: Session caching on; Default.\n
        Note that the WINC implementation of PEAPv0 does not support session caching; this setting is ignored for PEAPv0 methods.*/
    WIFI_1X_SPECIFIC_ROOTCERT,
    /*!< SHA1 digest of subject name of the root certificate to be used during server authentication. Values are:\n
        20-byte arrays: authentication is limited to this particular root certificate; Recommended\n
        0-byte array: authentication can succeed with any certificate in the WINC root certificate store; Default.\n*/
} wifi8_1x_option_t;

typedef enum
{
    TLS_CERT_EXP_CHECK_DISABLE,/*!< Certificate expiry is not checked. Server authentication does not depend on expiry of certificates.*/
    TLS_CERT_EXP_CHECK_ENABLE,/*!< Certificate expiry is checked and current time is required. 
    Server authentication fails if a certificate has expired or the current time is unknown.*/
    TLS_CERT_EXP_CHECK_EN_IF_SYS_TIME /*!< Certificate expiry is only checked if current time is known. 
    Server authentication fails if a certificate has expired; passes if the current time is unknown.*/
} wifi8_tls_cert_exp_settings_t;

typedef struct
{
    uint8_t u8_flags;
    /*!< 802.1x-specific flags:
            @ref m2m_802_1x_mschap2_flag
            @ref m2m_802_1x_tls_flag
            @ref m2m_802_1x_unencrypted_username_flag
            @ref m2m_802_1x_prepend_domain_flag
    */
    uint8_t u8_domain_length;
    /*!< length of domain. (offset of domain, within au81x_auth_details, understood to be 0.) */
    uint8_t u8_user_name_length;
    /*!< length of user_name. (offset of user_name, within au81x_auth_details, understood to be u8_domain_length.) */
    uint8_t u8_hdr_length;
    /*!< length of header (offset of au81x_auth_details within wifi8_m2m_wifi1x_hdr_t).
        legacy implementations may have 0 here, in which case header is 12 bytes.
        the unusual placing of this field is in order to hit a zero in legacy implementations. */
    uint16_t u16_private_key_offset;
    /*!< offset within au81x_auth_details of private_key/password. */
    uint16_t u16_private_key_length;
    /*!< length of private_key/password. in the case of private_key, this is the length of the modulus. */
    uint16_t u16_certificate_offset;
    /*!< offset within au81x_auth_details of certificate. */
    uint16_t u16_certificate_length;
    /*!< length of certificate. */
    uint8_t au8_tls_specific_root_name_sha1[20];
    /*!< sha1 digest of subject name to identify specific root certificate for phase 1 server verification. */
    uint32_t u32_tls_cs_bmp;
    /*!< bitmap of tls ciphersuites supported.
        set to 0 by driver. the firmware uses whichever set of ciphersuites is active (via @ref
        m2m_ssl_set_active_ciphersuites) when m2m_wifi_connect_1x_* is called. */
    uint32_t u32_tls_hs_flags;
    /*!< tls handshake flags for phase 1. */
    uint32_t u32_rsv;
    /*!< reserved, set to 0. */
    uint8_t au81x_auth_details[];
    /*!< placeholder for concatenation of domain, user_name, private_key/password, certificate.
            certificate (for 1x tls only) is sent over hif separately from the other parameters. */
} wifi8_m2m_wifi1x_hdr_t;

typedef struct
{
    uint8_t *pu8_domain;
    /*!< pointer to domain of authentication server (printable ascii), including '@' or '\'
            separator character as appropriate. use null if there is no domain information.
            the domain will be either prepended or appended to the user_name, depending on the
            setting of field b_prepend_domain. \n
            example 1: if [domain] is "@my_domain" and b_prepend_domain is false, then the eap
            identity response is "[user_name]@my_domain". \n
            example 2: if [domain] is "my_domain\" and b_prepend_domain is true, then the eap
            identity response is "my_domain\[user_name]". */
    uint8_t *pu8_user_name;
    /*!< pointer to user_name (ascii).
            this will be sent (encrypted) in the tunneled eap identity response (if applicable)
            and used during mscha_pv2 authentication. if b_unencrypted_user_name is true then it will
            also be sent (unencrypted) in the initial eap identity response. */
    uint8_t *pu8_password;
    /*!< pointer to mscha_pv2 password (ascii).
            this will be used during mscha_pv2 authentication. */
    uint16_t u16_domain_len;
    /*!< length of domain (in ascii characters), including '@' or '\' separator character as
            appropriate.
            permitted values are such that u16_domain_len + u16_user_name_len is between 0 and
            @ref m2m_auth_1x_user_len_max. */
    uint16_t u16_user_name_len;
    /*!< length of user_name (in ascii characters).
            permitted values are such that u16_domain_len + u16_user_name_len is between 0 and
            @ref m2m_auth_1x_user_len_max. */
    uint16_t u16_password_len;
    /*!< length of password (in ascii characters).
            permitted values are between 0 and @ref m2m_auth_1x_password_len_max. */
    uint8_t b_unencrypted_user_name;
    /*!< determines whether user_name or "anonymous" is sent (unencrypted) in the initial eap
            identity response. domain is sent in both cases. \n
            true: user_name is sent in the initial eap identity response (not recommended).
            false: "anonymous" is sent in the initial eap identity response. this setting is
            recommended for tunneled methods. mscha_pv2 is always a tunneled method. */
    uint8_t b_prepend_domain;
    /*!< determines whether domain is prepended or appended to user_name in eap identity responses.
            true: domain is prepended to user_name - [domain][user_name].
            false: domain is appended to user_name - [user_name][domain]. */
} wifi8_auth1x_mschap2_t;

typedef struct
{
    uint16_t sa_family;
    uint8_t sa_data[14];
} wifi8_sockaddr_t;

typedef struct
{
    uint8_t *data_buf;
    uint8_t *head;
    int length;
} wifi8_socket_buffer_t;

typedef struct
{
    uint32_t s_addr;/*!< network byte order representation of the i_pv4 address. for example,
    the address "192.168.0.10" is represented as 0x0a00a8c0. */
} wifi8_in_addr_t;

typedef struct 
{
    uint16_t sin_family;
    uint16_t sin_port;
    wifi8_in_addr_t sin_addr;
    uint8_t sin_zero[8];
} wifi8_sockaddr_in_t;

typedef struct
{
    uint8_t *pu8_buffer;
    int16_t s16_buffer_size;
    uint16_t u16_remaining_size;
    wifi8_sockaddr_in_t str_remote_addr;
} wifi8_socket_recv_msg_t;

typedef struct
{
    uint8_t state;
    int8_t parent;
    wifi8_socket_recv_msg_t recv_msg;
    wifi8_socket_buffer_t buffer;
    wifi8_sockaddr_t _last_sendto_addr;
} wifi8_socket_info_t;

typedef struct
{
    uint8_t au8ssid[M2M_MAX_SSID_LEN];/*!< AP SSID */
    uint8_t u8_listen_channel;/*!< wi-fi rf channel which the ap will operate on */
    uint8_t u8_key_indx;/*!< wep key index */
    uint8_t u8_key_sz;/*!< WEP key size */
    uint8_t au8_wep_key[WEP_104_KEY_STRING_SIZE + 1];/*!< WEP key */
    uint8_t u8_sec_type;/*!< security type: open or wep */
    uint8_t u8_ssid_hide;/*!< ssid status "hidden(1)/visible(0)" */
    uint8_t au8dhcp_server_ip[4];/*!< ap dhcp server address */
    uint8_t __pad24__[3];/*!< padding bytes for forcing alignment */
} wifi8_m2m_ap_config_t;

typedef struct
{
    uint8_t *pu8_bssid;
    uint8_t *pu8_ssid;
    uint8_t u8_ssid_len;
    wifi8_m2m_scan_ch_t enu_channel;
} wifi8_network_id_t;

typedef struct
{
    uint16_t u16_firmware_hif_info; /* fw hif info */
    uint8_t u8_firmware_major;     /* version major number */
    uint8_t u8_firmware_rsvd;      /* reserved */
    uint8_t u8_firmware_minor;     /* version minor */
    uint8_t u8_firmware_patch;     /* patch number */
    uint8_t build_date[12];       // 12 bytes
    uint8_t build_time[9];        // 9 bytes
} wifi8_m2m_rev_t;

typedef struct
{
    uint16_t u16_family;
    uint16_t u16_port;
    uint32_t u32ip_addr;
} wifi8_sock_addr_t;

typedef struct
{
    int8_t sock;
    uint8_t u8_void;
    uint16_t u16_data_size;
    wifi8_sock_addr_t str_addr;
    uint16_t u16_session_id;
    uint16_t u16_void;
} wifi8_send_cmd_t;

typedef struct
{
    uint32_t u32_mac_efuse_mib;
    uint32_t u32_firmware_ota_rev;
} wifi8_gp_regs_t;

typedef struct
{
    uint8_t u8_frame_type;/*!< it must use values from tenu_wifi_frame_type. */
    uint8_t u8_frame_subtype;/*!< it must use values from tenu_sub_types. */
    uint8_t u8_service_class;/*!< service class from wi-fi header. */
    uint8_t u8_priority;/*!< priority from wi-fi header. */
    uint8_t u8_header_length;/*!< frame header length. */
    uint8_t u8_cipher_type;/*!< encryption type for the rx packet. */
    uint8_t au8_src_mac_address[6];/*!< zero means do not filter source address. */
    uint8_t au8_dst_mac_address[6];/*!< zero means do not filter destination address. */
    uint8_t au8bssid[6];/*!< zero means do not filter bssid. */
    uint16_t u16_data_length;/*!< data payload length (header excluded). */
    uint16_t u16_frame_length;/*!< total frame length (header + data). */
    uint32_t u32_data_rate_kbps;/*!< data rate in kbps. */
    int8_t s8rssi;/*!< rssi.  */
    uint8_t __pad24__[3];/*!< padding bytes for forcing 4-byte alignment */
} wifi8_m2m_wifi_rx_packet_info_t;

typedef struct
{
    uint8_t u8_curr_state;/*!< current wi-fi connection state */
    uint8_t u8_err_code;/*!< error type */
    uint8_t __pad16__[2];/*!< padding bytes for forcing 4-byte alignment */
} wifi8_m2m_wifi_state_changed_t;

typedef struct
{
    uint8_t u8_numof_ch;/*!< number of found a_ps */
    int8_t s8_scan_state;/*!< scan status */
    uint8_t __pad16__[2];/*!< padding bytes for forcing 4-byte alignment */
} wifi8_m2m_scan_done_t;

typedef struct
{
    uint8_t u8_auth_type;/*!< Network authentication type. */
    uint8_t u8_ch;/*!< RF Channel for the AP. */
    uint8_t au8ssid[M2M_MAX_SSID_LEN];/*!< SSID obtained from WPS. */
    uint8_t au8psk[M2M_MAX_PSK_LEN];/*!< PSK for the network obtained from WPS. */

#define __PADDING_TSTR_M2MWPS_INFO_ (4 - ((2 + M2M_MAX_SSID_LEN + M2M_MAX_PSK_LEN) % 4))
    uint8_t __PAD__[__PADDING_TSTR_M2MWPS_INFO_];
} wifi8_m2m_wps_info_t;

typedef struct
{
    uint8_t u8index;/*!< ap index in the scan result list.  */
    uint8_t s8rssi;/*!< ap signal strength. */
    uint8_t u8_auth_type;/*!< ap authentication type. */
    uint8_t u8ch;/*!< ap rf channel. */
    uint8_t au8bssid[6];/*!< BSSID of the AP. */
    uint8_t au8ssid[M2M_MAX_SSID_LEN];/*!< AP SSID. */
    uint8_t _pad8_;/*!< padding bytes for forcing 4-byte alignment */
} wifi8_m2m_wifiscan_result_t;

typedef struct
{
    int8_t sock;
    uint8_t u8_back_log;
    uint16_t u16_session_id;
} wifi8_listen_cmd_t;

typedef struct
{
    int8_t status;/*!< the result of the bind operation. holding a value of zero for a successful bind or otherwise
     * a negative error code corresponding to @ref socket_error_code. */
} wifi8_socket_bind_msg_t;

typedef struct
{
    wifi8_sock_addr_t str_addr;
    int8_t sock;
    uint8_t u8_void;
    uint16_t u16_session_id;
} wifi8_bind_cmd_t;

typedef struct
{
    int8_t ssl_sock;
    uint8_t __pad24__[3];
} wifi8_ssl_socket_create_cmd_t;

typedef struct
{
    uint32_t u32_timeoutmsec;
    int8_t sock;
    uint8_t u8_void;
    uint16_t u16_session_id;
    uint16_t u16_buf_len;
} wifi8_recv_cmd_t;

typedef struct
{
    int8_t sock;
    int8_t s8_status;
    uint16_t u16_session_id;
} wifi8_listen_reply_t;

typedef struct
{
    int8_t sock;
    uint8_t u8_dummy;
    uint16_t u16_session_id;
} wifi8_close_cmd_t;

typedef struct
{
    uint8_t *pu8_user_buffer;
    uint16_t u16_user_buffer_size;
    uint16_t u16_session_id;
    uint16_t u16_data_offset;
    uint8_t b_is_used;
    uint8_t u8ssl_flags;
    uint8_t b_is_recv_pending;
    uint8_t u8_alpn_status;
    uint8_t u8_err_source;
    uint8_t u8_err_code;
} wifi8_socket_t;

typedef struct
{
    int8_t sock;
    int8_t s8_status;
    uint16_t u16_session_id;
} wifi8_bind_reply_t;

typedef struct
{
    int8_t status; /*!< holding a value of zero for a successful listen or otherwise 
    a negative error code corresponding to @ref socket_error_code.*/
} wifi8_socket_listen_msg_t;

typedef struct
{
    int8_t sock;/*!< on a successful @ref accept operation, the return information is the socket id for the accepted 
    connection with the remote peer.otherwise a negative error code is returned to indicate failure of the accept operation.*/
    wifi8_sockaddr_in_t str_addr;/*!< socket address structure for the remote peer.*/
} wifi8_socket_accept_msg_t;

typedef struct
{
    int8_t sock;
    int8_t s8_error;/*!< 0 for successful connection, in which case u16_app_data_offset is valid. 
    negative for failed connection, in which case u8_error_type and u8_error_detail may give more info.*/
    union {
        uint16_t u16_app_data_offset;/*!< in further packet send requests the host interface should 
        put the user applicationdata at this offset in the allocated shared data packet.*/
        struct
        {
            uint8_t u8_err_source;/*!< 0: no detail; 1: tls alert received from peer; 2: tls alert generated locally*/
            uint8_t u8_err_code;/*!< for tls alerts, this is the alert id.*/
        };
    };
} wifi8_connect_reply_t;

typedef struct
{
    wifi8_connect_reply_t str_conn_reply;
    uint8_t u8_app_protocol_idx;/*!< 1-based index of application-layer protocol negotiated during tls handshake.*/
    uint8_t __pad24__[3];
} wifi8_connect_alpn_reply_t;

typedef struct
{
    int8_t sock;/*!< socket id referring to the socket passed to the connect function call.*/
    int8_t s8_error;/*!< connect error code. holding a value of zero for a successful connect or 
    otherwise a negative error code corresponding to the type of error.*/
} wifi8_socket_connect_msg_t;

typedef struct
{
    uint8_t u8_key_indx;
    uint8_t u8_key_sz;
    uint8_t au8_wep_key[WEP_104_KEY_STRING_SIZE + 1]; // NULL terminated
    uint8_t __pad24__[3];
} wifi8_m2m_wifi_wep_params_t;

typedef struct
{
    uint8_t au8_def_router_ip[4];/*!< ap default router address*/
    uint8_t au8dns_server_ip[4];/*!< ap dns server address */
    uint8_t au8_subnet_mask[4];/*!< network subnet mask */
} wifi8_m2m_ap_config_ext_t;

typedef struct
{
    wifi8_m2m_ap_config_t str_ap_config;/*!< configuration parameters for the wi_fi ap.*/
    wifi8_m2m_ap_config_ext_t str_ap_config_ext;/*!< additional configuration parameters for the wi_fi ap.*/
} wifi8_m2m_ap_mode_config_t;

typedef struct
{
    wifi8_m2m_ap_config_t str_ap_config;/*!< configuration parameters for the wi_fi ap.  */
    char ac_http_server_domain_name[64];/*!< the device domain name for http provisioning.*/
    uint8_t u8_enable_redirect;/*!< a flag to enable/disable http redirect feature for the http provisioning server. 
    if the redirect is enabled, all http traffic (http://url) from the device associated with winc ap will be 
    redirected to the http provisioning web page.*/
    wifi8_m2m_ap_config_ext_t str_ap_config_ext; /*!< additional configuration parameters for the wi_fi ap.*/
    uint8_t __pad24__[3];
} wifi8_m2m_provision_mode_config_t;

typedef struct
{
    uint8_t u8_key_index;/*!< wep key index. */
    uint8_t u8_key_len;/*!< WEP Key Size. */
    uint8_t au8_wep_key[WEP_104_KEY_SIZE];/*!< WEP Key represented in bytes (padded with 0's if WEP-40). */
    uint8_t u8_rsv;/*!< reserved for future use. set to 0. */
} wifi8_m2m_wifi_wep_t;

typedef struct
{
    uint8_t u8_index;/*!< index of the desired scan result */
    uint8_t __pad24__[3];/*!< padding bytes for forcing 4-byte alignment */
} wifi8_m2m_req_scan_result_t;

typedef struct
{
    uint8_t u8_ch_num;/*!< the wi-fi rf channel number */
    uint8_t __pad24__[3];/*!< padding bytes for forcing 4-byte alignment */
} wifi8_m2m_scan_t;

typedef struct
{
    uint8_t u8_passphrase_len;/*!< Length of passphrase (8 to 63) or 64 if au8Passphrase contains ASCII representation of PSK. */
    uint8_t au8_passphrase[M2M_MAX_PSK_LEN - 1];/*!< Passphrase, or ASCII representation of PSK if u8PassphraseLen is 64. */
    uint8_t au8_psk[PSK_CALC_LEN];/*!< PSK calculated by firmware. Driver sets this to 0. */
    uint8_t u8_psk_calculated;/*!< flag used by firmware to avoid unnecessary recalculation of psk. driver sets this to 0. */
    uint8_t au8_rsv[2];/*!< reserved for future use. set to 0. */
} wifi8_m2m_wifi_psk_t;

typedef struct
{
    uint8_t *pu8_psk;/*!< pointer to psk, represented as an ascii string (64 characters, representing 32 bytes). 
            must be null if passphrase is provided instead. */
    uint8_t *pu8_passphrase;/*!< pointer to passphrase (printable ascii). must be null if psk is provided instead. */
    uint8_t u8_passphrase_len;/*!< length of passphrase. permitted values are between 8 and 63. this field is ignored if pu8_passphrase == null. */
} wifi8_auth_psk_t;

typedef struct
{
    uint8_t *pu8_wep_key;/*!< pointer to wep key, represented as an ascii string.(10 or 26 characters, representing 5 or 13 bytes.) */
    uint8_t u8_key_sz;/*!< size of wep key string. permitted values are @ref wep_40_key_string_size or @ref wep_104_key_string_size. */
    uint8_t u8_key_indx;/*!< wep key index in the range 1 to 4. */
} wifi8_auth_wep_t;

typedef struct
{
    uint16_t u16_cred_size;
    /*!< total buf_len of connect credentials, not including wifi8_m2m_conn_cred_hdr_t: wifi8_m2m_conn_cred_cmn_t auth details (variable buf_len)*/
    uint8_t u8_cred_store_flags;/*!< credential storage options represented with flags:
            @ref m2m_cred_store_flag
            @ref m2m_cred_encrypt_flag
            @ref m2m_cred_is_stored_flag
                                    @ref m2m_cred_is_encrypted_flag*/
    uint8_t u8_channel;/*!< wi-fi channel(s) on which to attempt connection. */
} wifi8_m2m_conn_cred_hdr_t;

typedef struct
{
    uint8_t u8_ssid_len;/*!< SSID length. */
    uint8_t au8_ssid[M2M_MAX_SSID_LEN - 1];/*!< SSID. */
    uint8_t u8_options;/*!< Common flags: @ref M2M_WIFI_CONN_BSSID_FLAG*/
    uint8_t au8_bssid[M2M_MAC_ADDRES_LEN];/*!< BSSID to restrict on, or all 0 if @ref M2M_WIFI_CONN_BSSID_FLAG is not set in u8Options. */
    uint8_t u8_auth_type;/*!< connection auth type. see @ref wifi8_m2m_sec_type_t. */
    uint8_t au8_rsv[3];/*!< reserved for future use. set to 0. */
} wifi8_m2m_conn_cred_cmn_t;

typedef struct
{
    uint8_t u8_key_indx;/*!< wep key index.*/
    uint8_t u8_key_sz;/*!< Wep key Size.*/
    uint8_t au8_wep_key[WEP_104_KEY_STRING_SIZE + 1];/*!< WEP Key represented as a NULL terminated ASCII string.*/
    uint8_t __pad24__[3];/*!< padding bytes to keep the structure word-aligned.*/
} wifi8_m2m_wifi_wep_params_legacy_1_2_t;

typedef union {
    uint8_t au8psk[M2M_MAX_PSK_LEN];/*!< pre-shared key in case of wpa-personal security.*/
    wifi8_m2m_wifi_wep_params_legacy_1_2_t str_wep_info;/*!< wep key parameters in case of wep security.*/
} wifi8_m2m_wifi_auth_legacy_1_2_t;

typedef struct
{
    wifi8_m2m_conn_cred_hdr_t str_conn_cred_hdr;/*!< credentials header. */
    wifi8_m2m_conn_cred_cmn_t str_conn_cred_cmn;/*!< credentials common section, including auth type and ssid. */
} wifi8_m2m_wifi_conn_hdr_t;

typedef struct
{
    wifi8_m2m_wifi_auth_legacy_1_2_t uni_auth;/*!< union holding all possible authentication parameters corresponding the current security types.*/
    uint8_t u8_sec_type;/*!< wi-fi network security type. see @ref wifi8_m2m_sec_type_t for supported security types.*/
    uint8_t __pad__[2];/*!< padding bytes for forcing 4-byte alignment*/
} wifi8_m2m_wifi_sec_info_legacy_1_2_t;

typedef struct
{
    wifi8_m2m_wifi_sec_info_legacy_1_2_t str_sec;/*!< security parameters for authenticating with the ap.*/
    uint16_t u16_ch;/*!< rf channel for the target ssid as enumerated in wifi8_m2m_scan_ch_t.*/
    uint8_t au8ssid[M2M_MAX_SSID_LEN];/*!< ssid of the desired ap. it must be null terminated string.*/
    uint8_t u8_no_save_cred; /*!< set to '1' to prevent winc from saving authentication info (psk, wep key, 801.1x password) on winc flash.*/
} wifi8_m2m_wifi_connect_legacy_1_2_t;

typedef struct
{
    uint16_t u16_max_trx_sz; /*!< maximum transfer buf_len. must be >= 16 bytes*/
} wifi8_nm_bus_capabilities_t;

typedef struct
{
    char ac_host_name[HOSTNAME_MAX_SIZE];
    uint32_t u32_host_ip;
} wifi8_dns_reply_t;

typedef struct
{
    wifi8_sock_addr_t str_remote_addr;
    int16_t s16_recv_status;
    uint16_t u16_data_offset;
    int8_t sock;
    uint8_t u8_void;
    uint16_t u16_session_id;
} wifi8_recv_reply_t;

typedef struct
{
    int8_t sock;
    uint8_t u8_void;
    int16_t s16_sent_bytes;
    uint16_t u16_session_id;
    uint16_t u16_void;
} wifi8_send_reply_t;

typedef struct
{
    uint32_t u32ip_addr;
    uint32_t u32_cmd_private;
    uint32_t u32rtt;
    uint16_t u16_success;
    uint16_t u16_fail;
    uint8_t u8_error_code;
    uint8_t __pad24__[3];
} wifi8_ping_reply_t;

typedef struct
{
    wifi8_sock_addr_t str_addr;
    int8_t s_listen_sock;
    int8_t s_connected_sock;
    uint16_t u16_void;
} wifi8_accept_reply_t;

typedef struct
{
    wifi8_sock_addr_t str_addr;
    int8_t sock;
    uint8_t u8_ssl_flags;
    uint16_t u16_session_id;
} wifi8_connect_cmd_t;

typedef struct
{
    char ac_ssid[M2M_MAX_SSID_LEN]; /*!< ap connection ssid name  */
    uint8_t u8_sec_type; /*!< security type */
    uint8_t au8ip_addr[4]; /*!< connection ip address */
    uint8_t au8mac_address[6]; /*!< mac address of the peer wi-fi station */
    uint8_t s8rssi; /*!< connection rssi signal */
    uint8_t __pad24__[3]; /*!< padding bytes for forcing 4-byte alignment */
} wifi8_m2m_conn_info_t;

typedef struct
{
    uint32_t u32_static_ip; /*!< the static ip assigned to the device. */
    uint32_t u32_gateway; /*!< ip of the default internet gateway. */
    uint32_t u32dns; /*!< ip for the dns server. */
    uint32_t u32_subnet_mask; /*!< subnet mask for the local area network. */
    uint32_t u32_dhcp_lease_time; /*!< dhcp lease time in sec. this field is is ignored in static ip configuration.*/
} wifi8_m2mip_config_t;

typedef struct
{
    uint8_t au8ssid[M2M_MAX_SSID_LEN]; /*!< provisioned ssid. */
    uint8_t au8_password[M2M_MAX_PSK_LEN]; /*!< provisioned password. */
    uint8_t u8_sec_type; /*!< wifi security type. */
    uint8_t u8_status; /*!< provisioning status. to be checked before reading the provisioning information. it may be
        - wifi8_ok   : provision successful.
        - m2m_fail      : provision failed.
    */
} wifi8_m2m_provision_info_t;

typedef struct
{
    int8_t s8_error_code;
    /*!<
        default connect error code. possible values are:
        - m2m_default_conn_empty_list
        - m2m_default_conn_scan_mismatch
    */
    uint8_t __pad24__[3];
} wifi8_m2m_default_conn_resp_t;

typedef struct
{
    uint16_t u16_len;
    /*!< length of the message */
    uint8_t data_msg[0xFF]; //lint !e43
    /*!< payload of the message */
} wifi8_m2m_ble_api_msg_t;

typedef struct
{
    /*!< return buffer address */
    uint8_t *pu8_rng_buff;
    /*!< prng buf_len requested */
    uint16_t u16_prng_size;
    /*!< prng pads */
    uint8_t __pad16__[2];
} wifi8_prng_t;

typedef struct
{
    int8_t s8_error_code; /*!< error code.  */
    uint8_t __pad24__[3]; /*!< padding bytes for forcing 4-byte alignment */
} wifi8_m2m_gain_table_rsp_t;

typedef struct
{
    int8_t s8_error_code;
    /*!<
        generic success/error code. possible values are:
        - @ref wifi8_ok
        - @ref wifi8_error
    */
    uint8_t __pad24__[3];
} wifi8_m2m_generic_resp_t;

typedef struct
{
    uint8_t u8_gain_table; /*!< gain table offset.  */
    uint8_t __pad24___[3];  /*!< padding bytes for forcing 4-byte alignment */
} wifi8_m2m_gain_table_t;

typedef struct
{
    uint8_t u8_gid;      /*!< group id */
    uint8_t u8_opcode;   /*!< op code */
    uint16_t u16_length; /*!< payload length */
} wifi8_hif_hdr_t;

typedef struct
{
    uint16_t u16_year; /*!< year */
    uint8_t u8_month; /*!< month */
    uint8_t u8_day; /*!< day */
    uint8_t u8_hour; /*!< hour */
    uint8_t u8_minute; /*!< minutes */
    uint8_t u8_second; /*!< seconds */

#define __padding_tstr_system_time_ (4 - (7 % 4))
    /*!< padding for @ref wifi8_system_time_t structure. */
    uint8_t __pad__[__padding_tstr_system_time_];
    /*!< structure padding. */
} wifi8_system_time_t;

typedef void (*wifi8_app_wifi_cb_t)(uint8_t u8_msg_type, void *pv_msg);
typedef void (*wifi8_app_mon_cb_t)(wifi8_m2m_wifi_rx_packet_info_t *pstr_wifi_rx_packet, uint8_t *pu8_payload, uint16_t u16_payload_size);
typedef void (*wifi8_app_socket_cb_t)(int8_t sock, uint8_t u8_msg, void *pv_msg);
typedef void (*wifi8_app_resolve_cb_t)(uint8_t *pu8_domain_name, uint32_t u32_server_ip);
typedef void (*wifi8_ping_cb_t)(uint32_t u32ip_addr, uint32_t u32rtt, uint8_t u8_error_code);
typedef void (*wifi8_app_eth_cb_t)(uint8_t u8_msg_type, void *pv_msg, void *pv_ctrl_buf);

typedef struct
{
    wifi8_app_wifi_cb_t pf_app_wifi_cb;  /*!< callback for wifi notifications. */
    wifi8_app_eth_cb_t pf_app_eth_cb;    /*!< callback for ethernet interface. */
    uint8_t *au8eth_rcv_buf;     /*!< pointer to receive buffer of ethernet packet */
    uint16_t u16eth_rcv_buf_size; /*!< size of receive buffer for ethernet packet */
    uint8_t u8_ethernet_enable;  /*!< enable ethernet mode flag */
} wifi8_eth_init_param_t;

typedef struct
{
    wifi8_app_wifi_cb_t pf_app_wifi_cb;         /*!< callback for wi-fi notifications. */
    wifi8_app_mon_cb_t pf_app_mon_cb;           /*!< callback for monitoring interface. */
    wifi8_eth_init_param_t str_eth_init_param; /*!< structure to hold ethernet interface parameters. */
    uint8_t gain_table_index;           /*!< gain table index to be used to configure the wi_fi and ble gains. */
    uint8_t __pad16__[2];             /*!< padding bytes for forcing 4-byte alignment */
} wifi8_init_param_t;

#endif
