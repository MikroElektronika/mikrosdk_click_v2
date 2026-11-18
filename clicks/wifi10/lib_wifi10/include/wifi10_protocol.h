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

// NXP FRDMK22 Wi-Fi QCA middleware (socket offload).
// Copyright (c) Qualcomm Atheros, Inc.
// All rights reserved.
// Redistribution and use in source and binary forms, with or without modification, are permitted (subject to
// the limitations in the disclaimer below) provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice, this list of conditions and the
//   following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
//   following disclaimer in the documentation and/or other materials provided with the distribution.
// - Neither the name of nor the names of its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE. THIS SOFTWARE IS
// PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// QCA4004 hosted SDK 3.3.6 (HTC and WMI).
// Copyright (c) 2017 Qualcomm Technologies, Inc.
// All rights reserved.
// Redistribution and use in source and binary forms, with or without modification, are permitted (subject to the
// limitations in the disclaimer below)
// provided that the following conditions are met:
// Redistributions of source code must retain the above copyright notice, this list of conditions and the following
// disclaimer.
// Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation and/or other materials provided with the
// distribution.
// Neither the name of Qualcomm Technologies, Inc. nor the names of its contributors may be used to endorse or promote
// products derived
// from this software without specific prior written permission.
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
// INCLUDING,
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY,
// OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
// USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/*!
 * @file wifi10_protocol.h
 * @brief Private QCA4004 wire constants for WiFi 10 Click.
 * @details SPI, HTC, WMI, and IPv4 socket offload values for hosted firmware.
 * @note Applications use wifi10.h. This header retains the notices for the SDK-derived implementation.
 */

#ifndef WIFI10_PROTOCOL_H
#define WIFI10_PROTOCOL_H

/** @brief QCA4004 internal and external SPI framing. */
#define WIFI10_DUMMY                        0x00u
#define WIFI10_SPI_READ                     0x8000u
#define WIFI10_SPI_INTERNAL                 0x4000u
#define WIFI10_HOST_WRITE                   0x4000u
#define WIFI10_HOST_ENABLE                  0x8000u
#define WIFI10_HOST_DONE                    0x0001u
#define WIFI10_HOST_MAX_LENGTH              32u
#define WIFI10_HOST_POLL_LIMIT              200u
#define WIFI10_CONFIG_IO_ENABLE             0x0080u
#define WIFI10_CONFIG_KEEP_AWAKE            0x0008u
#define WIFI10_SPI_IRQ_PACKET               0x0001u
#define WIFI10_SPI_IRQ_ERRORS               0x000Eu
#define WIFI10_SPI_IRQ_CPU                  0x0010u
#define WIFI10_SPI_IRQ_HOST_DONE            0x0300u
#define WIFI10_SPI_IRQ_WATERMARK            0x0400u
#define WIFI10_WRITE_SPACE_INITIAL          3163u
#define WIFI10_WRITE_OVERHEAD               5u
#define WIFI10_MAILBOX_END                  0x1000u
#define WIFI10_BLOCK_SIZE                   32u

/** @brief External registers and target diagnostic addresses. */
#define WIFI10_CPU_INT_STATUS               0x0401u
#define WIFI10_CREDIT_COUNTER               0x0420u
#define WIFI10_WINDOW_VALUE                 0x0474u
#define WIFI10_WINDOW_WRITE                 0x0478u
#define WIFI10_WINDOW_READ                  0x047Cu
#define WIFI10_HI_BOOT                      0x0042880Cul
#define WIFI10_HI_OPTIONS                   0x00428810ul
#define WIFI10_HI_REFCLK                    0x00428878ul
#define WIFI10_HI_POWER                     0x004288F0ul
#define WIFI10_REFCLK                       40000000ul
#define WIFI10_BOOT_NORMAL                  0x00000002ul
#define WIFI10_BOOT_POWER                   0x00000031ul
#define WIFI10_BOOT_OPTIONS                 0x00001250ul
#define WIFI10_ABI_MAJOR_MASK               0xFFFF0000ul
#define WIFI10_ABI_MAJOR                    0x00010000ul

/** @brief HTC framing, endpoints, and WMI header fields. */
#define WIFI10_HTC_HEADER                   6u
#define WIFI10_WMI_HEADER                   6u
#define WIFI10_WMI_META_SIZE                12u
#define WIFI10_WMI_META_OFFLOAD             0xA000u
#define WIFI10_WMI_DEVICE_MASK              0x000Fu
#define WIFI10_RX_INFO_UNSUPPORTED          0xC3u
#define WIFI10_RX_INFO2_UNSUPPORTED         0xF000u
#define WIFI10_RX_INFO3_UNSUPPORTED         0xFF00u
#define WIFI10_HTC_NEED_CREDIT              0x01u
#define WIFI10_HTC_TRAILER                  0x02u
#define WIFI10_HTC_CREDIT_RECORD            1u
#define WIFI10_EP_CONTROL                   1u
#define WIFI10_EP_DATA                      2u
#define WIFI10_DEFAULT_CREDITS              6u

/** @brief WMI command and event identifiers. */
#define WIFI10_CMD_CONNECT                  0x0001u
#define WIFI10_CMD_DISCONNECT               0x0003u
#define WIFI10_CMD_SCAN_PARAMS              0x0008u
#define WIFI10_CMD_BSS_FILTER               0x0009u
#define WIFI10_CMD_CHANNEL_LIST             0x000Eu
#define WIFI10_CMD_CHANNEL_PARAMS           0x0011u
#define WIFI10_CMD_POWER                    0x0012u
#define WIFI10_CMD_HT_CAP                   0xF01Eu
#define WIFI10_CMD_SET_PMK                  0xF028u
#define WIFI10_CMD_SOCKET                   0xF08Du
#define WIFI10_EVENT_READY                  0x1001u
#define WIFI10_EVENT_CONNECT                0x1002u
#define WIFI10_EVENT_DISCONNECT             0x1003u
#define WIFI10_EVENT_CMD_ERROR              0x1005u
#define WIFI10_EVENT_TARGET_ERROR           0x100Du
#define WIFI10_EVENT_PEER_NODE              0x101Bu
#define WIFI10_EVENT_SOCKET                 0x9016u
#define WIFI10_DISCONNECT_NO_NETWORK        0x01u
#define WIFI10_PEER_JOIN                    0x00u
#define WIFI10_PEER_EVENT_SIZE              7u

/** @brief WMI station configuration. */
#define WIFI10_WMI_NETWORK_STATION          0x01u
#define WIFI10_WMI_AUTH_OPEN                0x01u
#define WIFI10_WMI_AUTH_NONE                0x01u
#define WIFI10_WMI_AUTH_WPA2                0x10u
#define WIFI10_WMI_CRYPT_NONE               0x01u
#define WIFI10_WMI_CRYPT_AES                0x08u
#define WIFI10_WMI_IGNORE_GROUP_CIPHER      0x0004ul
#define WIFI10_WMI_FOLLOW_CHANNEL           0x0020ul
#define WIFI10_WMI_WPA_OFFLOAD              0x0040ul
#define WIFI10_WMI_MAX_PERFORMANCE          0x02u
#define WIFI10_WMI_BG_SCAN_DISABLED         0xFFFFu
#define WIFI10_WMI_SHORT_SCAN_RATIO         3u
#define WIFI10_WMI_DEFAULT_SCAN_FLAGS       0x2Fu
#define WIFI10_SCAN_PARAMS_SIZE             20u
#define WIFI10_BSS_FILTER_SIZE              8u
#define WIFI10_BSS_FILTER_NONE              0u
#define WIFI10_CHANNEL_LIST_HEADER          2u
#define WIFI10_CHANNEL_PARAMS_SIZE          6u
#define WIFI10_HT_CAP_SIZE                  7u
#define WIFI10_WMI_PHY_11G                  2u
#define WIFI10_WMI_HT_BAND_24               0u
#define WIFI10_WMI_HT_AMPDU_EXP             2u

/** @brief Socket offload command identifiers and wire sizes. */
#define WIFI10_SOCK_OPEN                    0ul
#define WIFI10_SOCK_CLOSE                   1ul
#define WIFI10_SOCK_CONNECT                 2ul
#define WIFI10_SOCK_IPCONFIG                10ul
#define WIFI10_SOCK_STACK_INIT              12ul
#define WIFI10_SOCK_OPEN_FAILED             ( -1l )
#define WIFI10_AF_INET                      2u
#define WIFI10_IPCONFIG_QUERY               0ul
#define WIFI10_IPCONFIG_DHCP                2ul
#define WIFI10_IPCONFIG_POLL_MS             100ul
#define WIFI10_SOCKET_HEADER                8u
#define WIFI10_SOCKET_RESPONSE              12u
#define WIFI10_SOCKET_ACK_SIZE              ( WIFI10_SOCKET_RESPONSE + 1u )
#define WIFI10_SOCKET_RECV_HEADER           20u
#define WIFI10_TCP_HEADROOM                 64u
#define WIFI10_UDP_HEADROOM                 44u
#define WIFI10_SOCKADDR_SIZE                8u
#define WIFI10_CONNECT_CMD_SIZE             34u
#define WIFI10_IPCONFIG_CMD_SIZE            96u
#define WIFI10_IPCONFIG_IPV4_SIZE           16u

/** @brief WMI station connection and credential payloads. */
#define WIFI10_PMK_LENGTH                   ( WIFI10_PMK_HEX_LENGTH / 2u )
#define WIFI10_PMK_CMD_SIZE                 ( WIFI10_PMK_LENGTH + 1u )
#define WIFI10_HEX_INVALID                  0xFFu
#define WIFI10_STATION_CMD_SIZE             52u

#endif // WIFI10_PROTOCOL_H
