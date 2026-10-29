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
 * @file wifi7.c
 * @brief WiFi 7 Click Driver.
 * @details WINC15x0 SPI transport, firmware startup, HIF event dispatch, and asynchronous socket operations.
 */

#include "wifi7.h"

/**
 * @brief SPI default transmit byte.
 * @details Zero byte clocked on MOSI during SPI reads.
 */
#define WIFI7_DUMMY 0x00

/**
 * @brief SPI transfer and framing constants.
 */
#define WIFI7_SPI_DEFAULT_SPEED             1000000                         /**< Default SPI clock in Hz. */
#define WIFI7_SPI_CLKLESS_WRITE_MAX         0x30                            /**< Last clockless write register. */
#define WIFI7_SPI_CLKLESS_READ_MAX          0xFF                            /**< Last clockless read register. */
#define WIFI7_SPI_WORD_SIZE                 4                               /**< Register transfer size in bytes. */
#define WIFI7_SPI_DMA_MIN_SIZE              2                               /**< Minimum safe DMA transfer size. */
#define WIFI7_SPI_DMA_ACK_SIZE              3                               /**< DMA write ACK size with CRC disabled. */
#define WIFI7_SPI_DMA_CRC_ACK_SIZE          2                               /**< DMA write ACK size with CRC enabled. */
#define WIFI7_SPI_CRC_SIZE                  2                               /**< Payload CRC trailer size in bytes. */
#define WIFI7_SPI_CMD_READ_SIZE             5                               /**< Read/reset command size with CRC. */
#define WIFI7_SPI_CMD_LONG_SIZE             8                               /**< DMA/internal-write size with CRC. */
#define WIFI7_SPI_CMD_WRITE_SIZE            9                               /**< Single-write command size with CRC. */
#define WIFI7_SPI_CLKLESS_FLAG              ( 1 << 7 )                      /**< Clockless flag in the address byte. */
#define WIFI7_SPI_RESET_BYTE                0xFF                            /**< Reset command argument byte. */
#define WIFI7_SPI_CRC_INITIAL               0x7F                            /**< Initial seven-bit command CRC. */
#define WIFI7_SPI_DATA_NIBBLE_SHIFT         4                               /**< Receive marker high-nibble shift. */
#define WIFI7_SPI_DATA_NIBBLE_MASK          0x0F                            /**< Receive marker nibble mask/value. */
#define WIFI7_SPI_DATA_MARKER               0xF0                            /**< SPI payload packet marker. */
#define WIFI7_SPI_PACKET_FIRST              0x01                            /**< First packet of a split payload. */
#define WIFI7_SPI_PACKET_MIDDLE             0x02                            /**< Middle packet of a split payload. */
#define WIFI7_SPI_PACKET_LAST               0x03                            /**< Last or only payload packet. */

/**
 * @brief SPI CRC and DMA packet-size configuration.
 */
#define WIFI7_SPI_CRC_DISABLE_MASK          0x0Cul                          /**< Command/data CRC configuration bits. */
#define WIFI7_SPI_PACKET_SIZE_MASK          0x70ul                          /**< SPI DMA packet-size field mask. */
#define WIFI7_SPI_PACKET_CFG_256            ( 0 << 4 )                      /**< 256-byte DMA packet-size setting. */
#define WIFI7_SPI_PACKET_CFG_512            ( 1 << 4 )                      /**< 512-byte DMA packet-size setting. */
#define WIFI7_SPI_PACKET_CFG_1K             ( 2 << 4 )                      /**< 1024-byte DMA packet-size setting. */
#define WIFI7_SPI_PACKET_CFG_2K             ( 3 << 4 )                      /**< 2048-byte DMA packet-size setting. */
#define WIFI7_SPI_PACKET_CFG_4K             ( 4 << 4 )                      /**< 4096-byte DMA packet-size setting. */
#define WIFI7_SPI_PACKET_CFG_8K             ( 5 << 4 )                      /**< 8192-byte DMA packet-size setting. */
#define WIFI7_SPI_PACKET_SIZE_256           256                             /**< 256-byte DMA packet size. */
#define WIFI7_SPI_PACKET_SIZE_512           512                             /**< 512-byte DMA packet size. */
#define WIFI7_SPI_PACKET_SIZE_1K            1024                            /**< 1024-byte DMA packet size. */
#define WIFI7_SPI_PACKET_SIZE_2K            2048                            /**< 2048-byte DMA packet size. */
#define WIFI7_SPI_PACKET_SIZE_4K            4096                            /**< 4096-byte DMA packet size. */

/**
 * @brief Chip identification and firmware version fields.
 */
#define WIFI7_CHIP_ID_2A0                   0x1002A0ul                      /**< Unnormalized 2A0 chip identifier. */
#define WIFI7_CHIP_ID_2A1                   0x1002A1ul                      /**< Normalized 2A1 chip identifier. */
#define WIFI7_CHIP_ID_2B0                   0x1002B0ul                      /**< Unnormalized 2B0 chip identifier. */
#define WIFI7_CHIP_ID_2B1                   0x1002B1ul                      /**< Normalized 2B1 chip identifier. */
#define WIFI7_CHIP_ID_2B2                   0x1002B2ul                      /**< Normalized 2B2 chip identifier. */
#define WIFI7_RF_REV_2A0                    1                               /**< RF revision paired with 2A0 silicon. */
#define WIFI7_RF_REV_2B0                    3                               /**< RF revision paired with 2B0 silicon. */
#define WIFI7_RF_REV_2B1                    4                               /**< RF revision paired with 2B1 silicon. */
#define WIFI7_CHIP_FAMILY_MASK              0x000F0000ul                    /**< Chip family field normalization mask. */
#define WIFI7_CHIP_FAMILY_1500              0x00050000ul                    /**< WINC1500 family field value. */
#define WIFI7_FW_POINTER_MASK               0xFFFFul                        /**< Firmware revision pointer field mask. */
#define WIFI7_FW_MIN_DRIVER_SHIFT           16                              /**< Minimum host version bit offset. */
#define WIFI7_FW_MAJOR_SHIFT                8                               /**< Major version bit offset. */

/**
 * @brief Firmware interrupt and HIF message fields.
 */
#define WIFI7_IRQ_MUX_MASK                  ( ( uint32_t ) 1 << 8 )         /**< Firmware IRQ output pin mux bit. */
#define WIFI7_IRQ_ENABLE_MASK               ( ( uint32_t ) 1 << 16 )        /**< Firmware IRQ output enable bit. */
#define WIFI7_HIF_OPCODE_SHIFT              8                               /**< Opcode bit offset in the TX request. */
#define WIFI7_HIF_LENGTH_SHIFT              16                              /**< Length bit offset in the TX request. */
#define WIFI7_HIF_ADDRESS_SHIFT             2                               /**< TX address field alignment shift. */
#define WIFI7_HIF_RX_LENGTH_SHIFT           2                               /**< RX allocation length field shift. */
#define WIFI7_HIF_RX_LENGTH_MASK            0x0FFF                          /**< RX allocation length field mask. */
#define WIFI7_HIF_PADDING_MAX               4                               /**< Maximum HIF allocation padding bytes. */
#define WIFI7_HIF_GROUP_INDEX               0                               /**< HIF header request-group byte. */
#define WIFI7_HIF_OPCODE_INDEX              1                               /**< HIF header opcode byte. */
#define WIFI7_HIF_LENGTH_LOW_INDEX          2                               /**< HIF header length low byte. */
#define WIFI7_HIF_LENGTH_HIGH_INDEX         3                               /**< HIF header length high byte. */

/**
 * @brief Wi-Fi payload, socket timeout, and hexadecimal PSK limits.
 */
#define WIFI7_RSSI_MESSAGE_SIZE             4                               /**< Firmware RSSI callback record size. */
#define WIFI7_SOCKET_TIMEOUT_INFINITE       0xFFFFFFFFul                    /**< Firmware infinite receive timeout. */
#define WIFI7_PSK_MIN_LENGTH                8                               /**< Minimum WPA/WPA2 passphrase length. */
#define WIFI7_HEX_LOWERCASE_MASK            0x20                            /**< ASCII lowercase conversion bit. */
#define WIFI7_HEX_ALPHA_BIAS                0x31                            /**< Letter bias after subtracting '0'. */
#define WIFI7_HEX_ALPHA_MAX                 5                               /**< Largest letter offset, 'f' - 'a'. */
#define WIFI7_HEX_ALPHA_BASE                10                              /**< Value of hexadecimal digit A/a. */
#define WIFI7_HEX_DIGIT_MAX                 0x0F                            /**< Largest decoded hexadecimal digit. */
#define WIFI7_HEX_INVALID                   0xFF                            /**< Invalid hexadecimal character. */

/** @brief Shared SPI command CRC state: 1 after command CRC has been disabled. */
static uint8_t gu8crc_off = 0;
/** @brief Shared HIF state; limits the driver to one active Click instance. */
static wifi7_hif_context_t hif_cxt;

/**
 * @brief SPI command CRC7 syndrome table.
 * @details Lookup values used before command CRC is disabled during initialization.
 * @note Kept in read-only storage to avoid reserving 256 bytes of RAM.
 */
static const uint8_t crc7_syndrome_table[ 256 ] =
{
    0x00, 0x09, 0x12, 0x1B, 0x24, 0x2D, 0x36, 0x3F,
    0x48, 0x41, 0x5A, 0x53, 0x6C, 0x65, 0x7E, 0x77,
    0x19, 0x10, 0x0B, 0x02, 0x3D, 0x34, 0x2F, 0x26,
    0x51, 0x58, 0x43, 0x4A, 0x75, 0x7C, 0x67, 0x6E,
    0x32, 0x3B, 0x20, 0x29, 0x16, 0x1F, 0x04, 0x0D,
    0x7A, 0x73, 0x68, 0x61, 0x5E, 0x57, 0x4C, 0x45,
    0x2B, 0x22, 0x39, 0x30, 0x0F, 0x06, 0x1D, 0x14,
    0x63, 0x6A, 0x71, 0x78, 0x47, 0x4E, 0x55, 0x5C,
    0x64, 0x6D, 0x76, 0x7F, 0x40, 0x49, 0x52, 0x5B,
    0x2C, 0x25, 0x3E, 0x37, 0x08, 0x01, 0x1A, 0x13,
    0x7D, 0x74, 0x6F, 0x66, 0x59, 0x50, 0x4B, 0x42,
    0x35, 0x3C, 0x27, 0x2E, 0x11, 0x18, 0x03, 0x0A,
    0x56, 0x5F, 0x44, 0x4D, 0x72, 0x7B, 0x60, 0x69,
    0x1E, 0x17, 0x0C, 0x05, 0x3A, 0x33, 0x28, 0x21,
    0x4F, 0x46, 0x5D, 0x54, 0x6B, 0x62, 0x79, 0x70,
    0x07, 0x0E, 0x15, 0x1C, 0x23, 0x2A, 0x31, 0x38,
    0x41, 0x48, 0x53, 0x5A, 0x65, 0x6C, 0x77, 0x7E,
    0x09, 0x00, 0x1B, 0x12, 0x2D, 0x24, 0x3F, 0x36,
    0x58, 0x51, 0x4A, 0x43, 0x7C, 0x75, 0x6E, 0x67,
    0x10, 0x19, 0x02, 0x0B, 0x34, 0x3D, 0x26, 0x2F,
    0x73, 0x7A, 0x61, 0x68, 0x57, 0x5E, 0x45, 0x4C,
    0x3B, 0x32, 0x29, 0x20, 0x1F, 0x16, 0x0D, 0x04,
    0x6A, 0x63, 0x78, 0x71, 0x4E, 0x47, 0x5C, 0x55,
    0x22, 0x2B, 0x30, 0x39, 0x06, 0x0F, 0x14, 0x1D,
    0x25, 0x2C, 0x37, 0x3E, 0x01, 0x08, 0x13, 0x1A,
    0x6D, 0x64, 0x7F, 0x76, 0x49, 0x40, 0x5B, 0x52,
    0x3C, 0x35, 0x2E, 0x27, 0x18, 0x11, 0x0A, 0x03,
    0x74, 0x7D, 0x66, 0x6F, 0x50, 0x59, 0x42, 0x4B,
    0x17, 0x1E, 0x05, 0x0C, 0x33, 0x3A, 0x21, 0x28,
    0x5F, 0x56, 0x4D, 0x44, 0x7B, 0x72, 0x69, 0x60,
    0x0E, 0x07, 0x1C, 0x15, 0x2A, 0x23, 0x38, 0x31,
    0x46, 0x4F, 0x54, 0x5D, 0x62, 0x6B, 0x70, 0x79
};

/**
 * @brief WiFi 7 host bus setup function.
 * @details This function initializes WINC SPI framing and checks the normalized chip identifier before firmware
 * startup.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Success changes device_state to WIFI7_NM_STATE_INIT. Firmware has not started at this stage.
 */
static err_t wifi7_hold ( wifi7_t *ctx );

/**
 * @brief WiFi 7 firmware startup function.
 * @details This function initializes HIF bookkeeping, waits for boot ROM and firmware, checks packed version
 * compatibility, and enables interrupts.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Incompatible firmware.
 * See #err_t definition for detailed explanation.
 * @note Only success changes device_state to WIFI7_NM_STATE_START. Compatibility requires the firmware to accept the
 * 19.5.4 host protocol.
 */
static err_t wifi7_start ( wifi7_t *ctx );

/**
 * @brief Hexadecimal character decoding function.
 * @details This function converts an ASCII hexadecimal digit without changing the input buffer.
 * @param[in] ch : ASCII character to decode.
 * @return Value from 0 to 15, or 0xFF if the character is not a hexadecimal digit.
 * @note Uppercase and lowercase A-F are accepted.
 */
static uint8_t wifi7_hexchar_2_val ( uint8_t ch );

/**
 * @brief SPI CRC7 byte update function.
 * @details This function updates the seven-bit SPI command CRC using the syndrome lookup table.
 * @param[in] crc : Current seven-bit CRC value.
 * @param[in] data_val : Next command byte.
 * @return Updated seven-bit CRC value.
 * @note Used while the WINC SPI command CRC is enabled.
 */
static uint8_t wifi7_crc7_byte ( uint8_t crc, uint8_t data_val );

/**
 * @brief SPI CRC7 buffer update function.
 * @details This function updates a seven-bit CRC over the supplied sequence of command bytes.
 * @param[in] crc : Initial seven-bit CRC value.
 * @param[in] buffer : Input command buffer containing len bytes.
 * @param[in] len : Number of bytes to process.
 * @return Updated seven-bit CRC value.
 * @note The SPI command builder supplies an initial value of 0x7F.
 */
static uint8_t wifi7_crc7 ( uint8_t crc, uint8_t *buffer, uint32_t len );

/**
 * @brief WINC SPI protocol initialization function.
 * @details This function negotiates command CRC handling, disables CRC, and selects the configured SPI DMA packet
 * size.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Call after hardware reset. Both initial CRC states are tried so an already configured SPI peripheral can be
 * recognized.
 */
static err_t wifi7_nm_spi_init ( wifi7_t *ctx );

/**
 * @brief WINC SPI command encoding function.
 * @details This function serializes register, DMA, or reset command arguments and appends CRC7 when required.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] cmd : WINC SPI command opcode.
 * @param[in] adr : Register or memory address used by the selected opcode.
 * @param[in] data_in : 32-bit register write value.
 * @param[in] sz : DMA transfer length in bytes; unused by register and reset commands.
 * @param[in] clockless : 1 for a clockless internal register command, otherwise 0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Command and address bytes follow WINC SPI protocol order; this function does not read the response.
 */
static err_t wifi7_spi_cmd ( wifi7_t *ctx, uint8_t cmd, uint32_t adr, uint32_t data_in, uint32_t sz, uint8_t clockless );

/**
 * @brief WINC SPI command response function.
 * @details This function reads the command echo and status with a bounded response-byte search.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] cmd : Expected command opcode.
 * @param[in] clockless : 1 for a clockless command, otherwise 0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Reset responses include a leading byte. Clockless transfers do not require normal command/status matching.
 */
static err_t wifi7_spi_cmd_rsp ( wifi7_t *ctx, uint8_t cmd, uint8_t clockless );

/**
 * @brief WINC SPI payload reading function.
 * @details This function consumes packet response headers and reads successive SPI payload blocks.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[out] b : Destination buffer with capacity for sz bytes.
 * @param[in] sz : Payload length in bytes; must be greater than zero.
 * @param[in] clockless : 1 for a clockless register read, otherwise 0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note CRC bytes are consumed only when enabled on a normal transfer. Payload lengths are bounded by the caller.
 */
static err_t wifi7_spi_data_read ( wifi7_t *ctx, uint8_t *b, uint16_t sz, uint8_t clockless );

/**
 * @brief WINC SPI payload writing function.
 * @details This function divides a payload into configured packet sizes and emits the first, middle, or final
 * packet marker.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] b : Source buffer containing sz bytes.
 * @param[in] sz : Payload length in bytes; must be greater than zero.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The caller reads the final DMA acknowledgement. Normal initialization disables SPI CRC before DMA writes.
 */
static err_t wifi7_spi_data_write ( wifi7_t *ctx, uint8_t *b, uint16_t sz );

/**
 * @brief WINC boot ROM wait function.
 * @details This function waits for eFuse loading and boot ROM readiness, writes the host version and configuration,
 * and starts firmware.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] arg : Firmware mode; must be WIFI7_M2M_WIFI_MODE_NORMAL.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Startup and configuration polls are bounded. CHIP_EN and RESET_N must already have been released.
 */
static err_t wifi7_wait_for_bootrom ( wifi7_t *ctx, uint8_t arg );

/**
 * @brief WINC firmware readiness wait function.
 * @details This function polls WIFI7_NMI_STATE_REG for the firmware initialization signature and clears it after startup.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] arg : Firmware mode; must be WIFI7_M2M_WIFI_MODE_NORMAL.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Each poll includes two one-millisecond delays; SPI transactions add to the total wait time.
 */
static err_t wifi7_wait_for_firmware_start ( wifi7_t *ctx, uint8_t arg );

/**
 * @brief WINC host wake request function.
 * @details This function asserts host wake bits, waits for enabled clocks, and resynchronizes the SPI command
 * parser.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note WAKE is not mapped to a host GPIO on this Click; wake control uses the clockless SPI registers.
 */
static err_t wifi7_chip_wake ( wifi7_t *ctx );

/**
 * @brief WINC host wake release function.
 * @details This function waits for the firmware handshake and clears the host wake-request bits.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Success permits the firmware to manage its power state; it does not confirm entry into a particular sleep
 * mode.
 */
static err_t wifi7_chip_sleep ( wifi7_t *ctx );

/**
 * @brief WINC interrupt configuration function.
 * @details This function selects the module interrupt output and enables firmware-to-host interrupt signaling.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The application polls the active-low mikroBUS INT pin; no MCU interrupt handler is installed.
 */
static err_t wifi7_enable_interrupts ( wifi7_t *ctx );

/**
 * @brief Host interface bookkeeping initialization function.
 * @details This function clears the shared HIF receive state and internal callback pointers.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The context parameter is retained for the driver calling convention. No module transaction is performed.
 */
static err_t wifi7_hif_init ( wifi7_t *ctx );

/**
 * @brief Host interface request submission function.
 * @details This function allocates a firmware buffer, writes the HIF header, control block, and optional payload,
 * then submits the request.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] u8_gid : Firmware request group.
 * @param[in] u8_opcode : Request opcode, optionally including WIFI7_M2M_REQ_DATA_PKT.
 * @param[in] pu8_ctrl_buf : Control bytes, or NULL when the control length is zero.
 * @param[in] u16_ctrl_buf_size : Control block length in bytes.
 * @param[in] pu8_data_buf : Optional payload, or NULL when the payload length is zero.
 * @param[in] u16_data_size : Payload length in bytes.
 * @param[in] u16_data_offset : Payload offset after the HIF header; must not overlap the control block.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Submission polls are bounded. A transfer failure after waking invalidates device_state because a host
 * timeout does not cancel a firmware request. A receive callback can borrow the active HIF wake state.
 */
static err_t wifi7_hif_send ( wifi7_t *ctx, uint8_t u8_gid, uint8_t u8_opcode, uint8_t *pu8_ctrl_buf,
                              uint16_t u16_ctrl_buf_size, uint8_t *pu8_data_buf, uint16_t u16_data_size,
                              uint16_t u16_data_offset );

/**
 * @brief Host interface dispatcher registration function.
 * @details This function installs the internal Wi-Fi or IP group dispatcher.
 * @param[in] u8_grp : WIFI7_M2M_REQ_GROUP_WIFI or WIFI7_M2M_REQ_GROUP_IP.
 * @param[in] fn : Dispatcher function pointer.
 * See #wifi7_hif_call_back_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Other firmware request groups are not registered by this driver.
 */
static err_t wifi7_hif_register_cb ( uint8_t u8_grp, wifi7_hif_call_back_t fn );

/**
 * @brief Host interface message reading function.
 * @details This function validates the requested address range, copies message bytes, and optionally acknowledges
 * the final read.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] u32_addr : Start address inside the current HIF receive message.
 * @param[out] pu8_buf : Destination for u16_sz bytes; may be NULL for a zero-length final acknowledgement.
 * @param[in] u16_sz : Number of bytes to copy.
 * @param[in] is_done : 1 to release the message after this read, otherwise 0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note A zero-length final call releases unread bytes. Any read or acknowledgement failure sets the shared receive
 * error flag.
 */
static err_t wifi7_hif_receive ( wifi7_t *ctx, uint32_t u32_addr, uint8_t *pu8_buf, uint16_t u16_sz, uint8_t is_done );

/**
 * @brief Host interface receive acknowledgement function.
 * @details This function sets the firmware RX-done bit and clears local receive ownership after a successful write.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Acknowledge only after all required bytes have been copied from the shared firmware message.
 */
static err_t wifi7_hif_set_rx_done ( wifi7_t *ctx );

/**
 * @brief Internal Wi-Fi message dispatcher.
 * @details This function reads supported Wi-Fi event payloads and invokes the application Wi-Fi callback.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] u8_op_code : Firmware Wi-Fi event opcode.
 * @param[in] u16_data_size : Payload length in bytes supplied by HIF.
 * @param[in] u32_addr : Firmware address of the message payload.
 * @return Nothing.
 * @note Payload objects are local to this dispatcher and must be consumed or copied before the application callback
 * returns. HIF enforces the receive bounds.
 */
static void wifi7_m2m_wifi_cb ( wifi7_t *ctx, uint8_t u8_op_code, uint16_t u16_data_size, uint32_t u32_addr );

/**
 * @brief Internal Wi-Fi state mapping function.
 * @details This function maps the module initialization state to the corresponding Wi-Fi driver state.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return WIFI7_WIFI_STATE_DEINIT, WIFI7_WIFI_STATE_INIT, or WIFI7_WIFI_STATE_START.
 * @note An unrecognized module state is reported as WIFI7_WIFI_STATE_DEINIT.
 */
static uint8_t wifi7_m2m_wifi_get_state ( wifi7_t *ctx );

/**
 * @brief Internal Wi-Fi event processing function.
 * @details This function dispatches a pending interrupt only after firmware startup has completed.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Returns an error when the driver has not reached WIFI7_WIFI_STATE_START.
 */
static err_t wifi7_m2m_wifi_handle_events ( wifi7_t *ctx );

/**
 * @brief WiFi 7 host interface message dispatch function.
 * @details This function clears the pending interrupt, validates the message header and buffer length, dispatches
 * Wi-Fi or IP events, and acknowledges unread messages.
 * @param[in,out] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Called by wifi7_hif_handle_isr with the module awake. An inactive pending bit returns success. Unknown
 * request groups are acknowledged without a callback. Malformed messages and receive failures return an error.
 */
static err_t wifi7_hif_isr ( wifi7_t *ctx );

/**
 * @brief Host interface interrupt polling function.
 * @details This function reads the active-low INT pin, wakes the module for one pending message, and releases the
 * wake request afterward.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Success also means the interrupt input was inactive. This is called from the application loop, not an MCU
 * ISR.
 */
static err_t wifi7_hif_handle_isr ( wifi7_t *ctx );

/**
 * @brief Internal socket message dispatcher.
 * @details This function decodes bind, listen, accept, connect, send, and receive events and validates socket
 * descriptors and available session identifiers.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] u8_op_code : Firmware socket event opcode.
 * @param[in] u16_buffer_size : HIF payload length in bytes.
 * @param[in] u32_address : Firmware address of the message payload.
 * @return Nothing.
 * @note Receive errors propagate through the shared HIF state. Application callback metadata remains valid only
 * during the callback.
 */
static void wifi7_m2m_ip_cb ( wifi7_t *ctx, uint8_t u8_op_code, uint16_t u16_buffer_size, uint32_t u32_address );

/**
 * @brief Internal scan result request function.
 * @details This function validates an access-point index and submits the scan-result request.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] scan_request_index : Zero-based result index less than the number reported by the last successful scan.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The firmware result is delivered asynchronously through WIFI7_M2M_WIFI_RESP_SCAN_RESULT.
 */
static err_t wifi7_m2m_wifi_req_scan_result ( wifi7_t *ctx, uint8_t scan_request_index );

/**
 * @brief Internal active scan request function.
 * @details This function validates the RF channel and submits a zero-initialized active scan command.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] ch : Channel 1-14, or WIFI7_M2M_WIFI_CH_ALL.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The passive-scan timeout field is left at zero because this request selects an active scan.
 */
static err_t wifi7_m2m_wifi_request_scan ( wifi7_t *ctx, uint8_t ch );

/**
 * @brief Socket receive chunk delivery function.
 * @details This function copies a firmware receive payload into successive caller-buffer-sized chunks and invokes
 * the application callback for each chunk.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] sock : Validated socket descriptor for the active session.
 * @param[in,out] pstr_recv : Receive callback metadata updated for each chunk.
 * See #wifi7_socket_recv_msg_t object definition for detailed explanation.
 * @param[in] u8_socket_msg : WIFI7_SOCKET_MSG_RECV or WIFI7_SOCKET_MSG_RECVFROM.
 * @param[in] u32_start_address : Firmware address of the first payload byte.
 * @param[in] u16_read_count : Number of payload bytes to deliver.
 * @return Nothing.
 * @note The receive buffer remains pending through nonfinal chunks. The last read releases the HIF message before
 * its callback; closing or replacing the session in a callback discards the unread remainder.
 */
static void wifi7_socket_read_socket_data ( wifi7_t *ctx, int8_t sock, wifi7_socket_recv_msg_t *pstr_recv,
                                            uint8_t u8_socket_msg, uint32_t u32_start_address, uint16_t u16_read_count );

/**
 * @brief Internal station connection request function.
 * @details This function validates open or WPA/WPA2 personal authentication and submits the production firmware's
 * 108-byte connection record.
 * @param[in] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @param[in] pc_ssid : SSID buffer already validated by wifi7_connect.
 * @param[in] u8_ssid_len : SSID length from 1 to 32 bytes.
 * @param[in] u8_sec_type : WIFI7_M2M_WIFI_SEC_OPEN or WIFI7_M2M_WIFI_SEC_WPA_PSK.
 * See #wifi7_m2m_sec_type_t object definition for detailed explanation.
 * @param[in] pv_auth_info : NULL for open authentication or a terminated passphrase/hexadecimal PSK.
 * @param[in] u16_ch : Validated RF channel.
 * See #wifi7_m2m_scan_ch_t object definition for detailed explanation.
 * @param[in] u8_no_save_cred : Must be 1; credential storage is not exposed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The complete record is initialized before use, and the no-save flag is always set. Only hexadecimal digits
 * are accepted for a 64-character PSK.
 */
static err_t wifi7_m2m_wifi_connect_sc ( wifi7_t *ctx, uint8_t *pc_ssid, uint8_t u8_ssid_len, wifi7_m2m_sec_type_t u8_sec_type,
                                         void *pv_auth_info, wifi7_m2m_scan_ch_t u16_ch, uint16_t u8_no_save_cred );

void wifi7_cfg_setup ( wifi7_cfg_t *cfg )
{
    cfg->sck     = HAL_PIN_NC;
    cfg->miso    = HAL_PIN_NC;
    cfg->mosi    = HAL_PIN_NC;
    cfg->cs      = HAL_PIN_NC;
    cfg->en      = HAL_PIN_NC;
    cfg->rst     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = WIFI7_SPI_DEFAULT_SPEED;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t wifi7_init ( wifi7_t *ctx, wifi7_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    if ( ( cfg->spi_mode != SPI_MASTER_MODE_0 ) || ( cfg->spi_speed == 0 ) ||
         ( cfg->spi_speed > WIFI7_SPI_MAX_SPEED ) ||
         ( cfg->cs_polarity != SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW ) ||
         ( cfg->cs == HAL_PIN_NC ) || ( cfg->en == HAL_PIN_NC ) || ( cfg->rst == HAL_PIN_NC ) ||
         ( cfg->int_pin == HAL_PIN_NC ) )
    {
        return WIFI7_ERROR;
    }
    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) )
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, WIFI7_DUMMY ) )
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) )
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) )
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_low( &ctx->rst );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_low( &ctx->en );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    ctx->device_state = WIFI7_NM_STATE_DEINIT;
    ctx->ch_num       = 0;
    memset( ctx->sockets, 0, sizeof( ctx->sockets ) );
    ctx->session_id    = 0;
    ctx->socket_init   = 0;
    ctx->app_wifi_cb   = NULL;
    ctx->app_socket_cb = NULL;

    return SPI_MASTER_SUCCESS;
}

err_t wifi7_default_cfg ( wifi7_t *ctx )
{
    ctx->device_state = WIFI7_NM_STATE_DEINIT;
    ctx->socket_init  = 0;
    ctx->ch_num       = 0;
    memset( ctx->sockets, 0, sizeof( ctx->sockets ) );
    digital_out_low( &ctx->rst );
    digital_out_low( &ctx->en );
    Delay_10ms( );
    digital_out_high( &ctx->en );
    /* CHIP_EN must precede RESET_N by at least 5 ms. */
    Delay_10ms( );
    digital_out_high( &ctx->rst );
    Delay_10ms( );
    return wifi7_init_drv( ctx );
}

err_t wifi7_generic_write ( wifi7_t *ctx, uint8_t *data_in, uint16_t len )
{
    spi_master_select_device( ctx->chip_select );
    Delay_10us ( );
    err_t error_flag = spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t wifi7_generic_read ( wifi7_t *ctx, uint8_t *data_out, uint16_t len )
{
    spi_master_select_device( ctx->chip_select );
    Delay_10us ( );
    err_t error_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t wifi7_reg_write ( wifi7_t *ctx, uint32_t addr, uint32_t data_in )
{
    err_t result = WIFI7_OK;
    uint8_t cmd = WIFI7_CMD_SINGLE_WRITE;
    uint8_t clockless = 0;

    if ( addr <= WIFI7_SPI_CLKLESS_WRITE_MAX )
    {
        cmd = WIFI7_CMD_INTERNAL_WRITE;
        clockless = 1;
    }

    for ( uint8_t retry = WIFI7_SPI_RETRY_COUNT; retry != 0; retry-- )
    {
        if ( result != WIFI7_OK )
        {
            Delay_1ms( );
            wifi7_spi_cmd( ctx, WIFI7_CMD_RESET, 0, 0, 0, 0 );
            wifi7_spi_cmd_rsp( ctx, WIFI7_CMD_RESET, 0 );
            Delay_1ms( );
        }

        result = wifi7_spi_cmd( ctx, cmd, addr, data_in, WIFI7_SPI_WORD_SIZE, clockless );
        if ( result != WIFI7_OK )
        {
            continue;
        }

        result = wifi7_spi_cmd_rsp( ctx, cmd, clockless );
        if ( result == WIFI7_OK )
        {
            break;
        }
    }

    return result;
}

err_t wifi7_reg_read ( wifi7_t *ctx, uint32_t addr, uint32_t *data_out )
{
    err_t result = WIFI7_OK;
    uint8_t cmd = WIFI7_CMD_SINGLE_READ;
    uint8_t tmp[ WIFI7_SPI_WORD_SIZE ];
    uint8_t clockless = 0;

    if ( data_out == NULL )
    {
        return WIFI7_ERROR;
    }
    if ( addr <= WIFI7_SPI_CLKLESS_READ_MAX )
    {
        cmd = WIFI7_CMD_INTERNAL_READ;
        clockless = 1;
    }

    for ( uint8_t retry = WIFI7_SPI_RETRY_COUNT; retry != 0; retry-- )
    {
        if ( result != WIFI7_OK )
        {
            Delay_1ms( );
            wifi7_spi_cmd( ctx, WIFI7_CMD_RESET, 0, 0, 0, 0 );
            wifi7_spi_cmd_rsp( ctx, WIFI7_CMD_RESET, 0 );
            Delay_1ms( );
        }
        result = wifi7_spi_cmd( ctx, cmd, addr, 0, WIFI7_SPI_WORD_SIZE, clockless );
        if ( result != WIFI7_OK )
        {
            continue;
        }
        result = wifi7_spi_cmd_rsp( ctx, cmd, clockless );
        if ( result != WIFI7_OK )
        {
            continue;
        }
        result = wifi7_spi_data_read( ctx, tmp, WIFI7_SPI_WORD_SIZE, clockless );
        if ( result != WIFI7_OK )
        {
            continue;
        }

        *data_out = tmp[ 0 ] |
                    ( ( uint32_t ) tmp[ 1 ] << 8 ) |
                    ( ( uint32_t ) tmp[ 2 ] << 16 ) |
                    ( ( uint32_t ) tmp[ 3 ] << 24 );

        if ( result == WIFI7_OK )
        {
            break;
        }
    }

    return result;
}

err_t wifi7_block_read ( wifi7_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_len )
{
    uint8_t cmd = WIFI7_CMD_DMA_EXT_READ;
    err_t result = WIFI7_OK;
    uint8_t tmp[ WIFI7_SPI_DMA_MIN_SIZE ];
    uint8_t single_byte_workaround = 0;

    if ( ( data_buf == NULL ) || ( buf_len == 0 ) )
    {
        return WIFI7_ERROR;
    }
    if ( buf_len == 1 )
    {
        //Workaround hardware problem with single byte transfers over SPI bus
        buf_len = WIFI7_SPI_DMA_MIN_SIZE;
        single_byte_workaround = 1;
    }

    for ( uint8_t retry = WIFI7_SPI_RETRY_COUNT; retry != 0; retry-- )
    {
        if ( result != WIFI7_OK )
        {
            Delay_1ms( );
            wifi7_spi_cmd( ctx, WIFI7_CMD_RESET, 0, 0, 0, 0 );
            wifi7_spi_cmd_rsp( ctx, WIFI7_CMD_RESET, 0 );
            Delay_1ms( );
        }

        result = wifi7_spi_cmd( ctx, cmd, addr, 0, buf_len, 0 );
        if ( result != WIFI7_OK )
        {
            continue;
        }

        result = wifi7_spi_cmd_rsp( ctx, cmd, 0 );
        if ( result != WIFI7_OK )
        {
            continue;
        }

        if ( single_byte_workaround )
        {
            result = wifi7_spi_data_read( ctx, tmp, buf_len, 0 );
            if ( result == WIFI7_OK )
            {
                data_buf[ 0 ] = tmp[ 0 ];
            }
        }
        else
        {
            result = wifi7_spi_data_read( ctx, data_buf, buf_len, 0 );
        }

        if ( result == WIFI7_OK )
        {
            break;
        }
    }

    return result;
}

err_t wifi7_block_write ( wifi7_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_len )
{
    err_t result = WIFI7_OK;
    uint8_t cmd = WIFI7_CMD_DMA_EXT_WRITE;
    uint8_t response[ WIFI7_SPI_DMA_ACK_SIZE ];
    uint8_t response_len = WIFI7_SPI_DMA_ACK_SIZE;
    uint8_t pair[ WIFI7_SPI_DMA_MIN_SIZE ];

    if ( ( data_buf == NULL ) || ( buf_len == 0 ) )
    {
        return WIFI7_ERROR;
    }
    if ( buf_len == 1 )
    {
        /* Preserve the adjacent byte required by the SPI single-byte workaround. */
        if ( WIFI7_OK != wifi7_block_read( ctx, addr, pair, sizeof( pair ) ) )
        {
            return WIFI7_ERROR;
        }
        pair[ 0 ] = data_buf[ 0 ];
        data_buf = pair;
        buf_len = sizeof( pair );
    }

    for ( uint8_t retry = WIFI7_SPI_RETRY_COUNT; retry != 0; retry-- )
    {
        if ( result != WIFI7_OK )
        {
            Delay_1ms( );
            wifi7_spi_cmd( ctx, WIFI7_CMD_RESET, 0, 0, 0, 0 );
            wifi7_spi_cmd_rsp( ctx, WIFI7_CMD_RESET, 0 );
            Delay_1ms( );
        }

        result = wifi7_spi_cmd( ctx, cmd, addr, 0, buf_len, 0 );
        if ( result != WIFI7_OK )
        {
            continue;
        }

        result = wifi7_spi_cmd_rsp( ctx, cmd, 0 );
        if ( result != WIFI7_OK )
        {
            continue;
        }

        result = wifi7_spi_data_write( ctx, data_buf, buf_len );
        if ( result == WIFI7_OK )
        {
            if ( !gu8crc_off )
            {
                response_len = WIFI7_SPI_DMA_CRC_ACK_SIZE;
            }
            result = wifi7_generic_read( ctx, response, response_len );
            if ( ( result == WIFI7_OK ) &&
                 ( ( response[ response_len - 2 ] != WIFI7_CMD_INTERNAL_WRITE ) || ( response[ response_len - 1 ] != 0 ) ) )
            {
                result = WIFI7_ERROR;
            }
        }
        if ( result == WIFI7_OK )
        {
            break;
        }
    }

    return result;
}

err_t wifi7_init_drv ( wifi7_t *ctx )
{
    if ( WIFI7_OK != wifi7_hold( ctx ) )
    {
        return WIFI7_ERROR;
    }
    else
    {

        return wifi7_start( ctx );
    }
}

uint32_t wifi7_chip_id ( wifi7_t *ctx )
{
    uint32_t chipid = 0;
    uint32_t rf_rev = 0;

    if ( ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_NMI_CHIPID, &chipid ) ) ||
         ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_RF_REV_REG, &rf_rev ) ) )
    {
        return 0;
    }
    if ( chipid == WIFI7_CHIP_ID_2A0 )
    {
        if ( rf_rev != WIFI7_RF_REV_2A0 )
        {
            chipid = WIFI7_CHIP_ID_2A1;
        }
    }
    else if ( chipid == WIFI7_CHIP_ID_2B0 )
    {
        if ( rf_rev == WIFI7_RF_REV_2B1 )
        {
            chipid = WIFI7_CHIP_ID_2B1;
        }
        else if ( rf_rev != WIFI7_RF_REV_2B0 )
        {
            chipid = WIFI7_CHIP_ID_2B2;
        }
    }
    if ( WIFI7_IS_NMC1000( chipid ) )
    {
        chipid = ( chipid & ~WIFI7_CHIP_FAMILY_MASK ) | WIFI7_CHIP_FAMILY_1500;
    }
    return chipid;
}

err_t wifi7_get_full_firmware_version ( wifi7_t *ctx, wifi7_m2m_rev_t *fw_version )
{
    uint32_t reg = 0;
    wifi7_gp_regs_t strgp = { 0 };
    err_t result = WIFI7_ERROR;

    if ( ( fw_version == NULL ) || ( WIFI7_OK != wifi7_chip_wake( ctx ) ) )
    {
        return WIFI7_ERROR;
    }
    memset( fw_version, 0, sizeof( wifi7_m2m_rev_t ) );
    if ( ( WIFI7_OK == wifi7_reg_read( ctx, WIFI7_NMI_GP_REG_2, &reg ) ) && ( reg != 0 ) )
    {
        if ( WIFI7_OK == wifi7_block_read( ctx, reg | WIFI7_RAM_BASE, ( uint8_t * ) &strgp, sizeof( strgp ) ) )
        {
            reg = strgp.u32_firmware_ota_rev & WIFI7_FW_POINTER_MASK;
            if ( reg != 0 )
            {
                result = wifi7_block_read( ctx, reg | WIFI7_RAM_BASE, ( uint8_t * ) fw_version, sizeof( *fw_version ) );
                fw_version->build_date[ sizeof( fw_version->build_date ) - 1 ] = 0;
                fw_version->build_time[ sizeof( fw_version->build_time ) - 1 ] = 0;
            }
        }
    }
    if ( WIFI7_OK != wifi7_chip_sleep( ctx ) )
    {
        return WIFI7_ERROR;
    }
    return result;
}

err_t wifi7_req_scan_result ( wifi7_t *ctx, uint8_t scan_index )
{
    return wifi7_m2m_wifi_req_scan_result( ctx, scan_index );
}

err_t wifi7_request_scan ( wifi7_t *ctx, uint8_t channel )
{
    return wifi7_m2m_wifi_request_scan( ctx, channel );
}

err_t wifi7_handle_events ( wifi7_t *ctx )
{
    return wifi7_m2m_wifi_handle_events( ctx );
}

void wifi7_socket_init ( wifi7_t *ctx )
{
    if ( ctx->socket_init == 0 )
    {
        memset( ctx->sockets, 0, sizeof( ctx->sockets ) );
        wifi7_hif_register_cb( WIFI7_M2M_REQ_GROUP_IP, wifi7_m2m_ip_cb );
        ctx->socket_init = 1;
        ctx->session_id  = 0;
    }
}

err_t wifi7_socket_create ( wifi7_t *ctx, uint16_t u16_domain, uint8_t u8_type, uint8_t u8_flags )
{
    uint8_t first = 0;
    uint8_t limit = WIFI7_TCP_SOCK_MAX;
    uint8_t index;

    if ( ( ctx->socket_init == 0 ) || ( ctx->device_state != WIFI7_NM_STATE_START ) ||
         ( u16_domain != WIFI7_AF_INET ) || ( u8_flags != 0 ) )
    {
        return WIFI7_ERROR;
    }
    if ( u8_type == WIFI7_SOCK_DGRAM )
    {
        first = WIFI7_TCP_SOCK_MAX;
        limit = WIFI7_MAX_SOCKET;
    }
    else if ( u8_type != WIFI7_SOCK_STREAM )
    {
        return WIFI7_ERROR;
    }
    for ( index = first; index < limit; index++ )
    {
        if ( !ctx->sockets[ index ].b_is_used )
        {
            memset( &ctx->sockets[ index ], 0, sizeof( wifi7_socket_t ) );
            ctx->session_id++;
            if ( ctx->session_id == 0 )
            {
                ctx->session_id++;
            }
            ctx->sockets[ index ].b_is_used = 1;
            ctx->sockets[ index ].u16_session_id = ctx->session_id;
            return ( err_t ) index;
        }
    }
    return WIFI7_ERROR;
}

err_t wifi7_socket_bind ( wifi7_t *ctx, int8_t sock, wifi7_sockaddr_t *pstr_addr, uint8_t u8_addr_len )
{
    wifi7_bind_cmd_t str_bind = { 0 };

    if ( ( sock < 0 ) || ( sock >= WIFI7_MAX_SOCKET ) || ( pstr_addr == NULL ) ||
         ( u8_addr_len != sizeof( wifi7_sockaddr_in_t ) ) || !ctx->sockets[ sock ].b_is_used ||
         ( ( ( wifi7_sockaddr_in_t * ) pstr_addr )->sin_family != WIFI7_AF_INET ) )
    {
        return WIFI7_ERROR;
    }
    str_bind.sock = sock;
    memcpy( &str_bind.str_addr, pstr_addr, sizeof( str_bind.str_addr ) );
    str_bind.u16_session_id = ctx->sockets[ sock ].u16_session_id;
    return WIFI7_SOCKET_REQUEST( ctx, WIFI7_SOCKET_CMD_BIND, ( uint8_t * ) &str_bind, sizeof( str_bind ), NULL, 0, 0 );
}

int8_t wifi7_socket_listen ( wifi7_t *ctx, int8_t sock, uint8_t backlog )
{
    wifi7_listen_cmd_t str_listen = { 0 };

    if ( ( sock < 0 ) || ( sock >= WIFI7_TCP_SOCK_MAX ) || !ctx->sockets[ sock ].b_is_used )
    {
        return WIFI7_ERROR;
    }
    str_listen.sock           = sock;
    str_listen.u8_back_log    = backlog;
    str_listen.u16_session_id = ctx->sockets[ sock ].u16_session_id;
    return WIFI7_SOCKET_REQUEST( ctx, WIFI7_SOCKET_CMD_LISTEN, ( uint8_t * ) &str_listen, sizeof( str_listen ), NULL, 0, 0 );
}

err_t wifi7_socket_connect ( wifi7_t *ctx, int8_t sock, wifi7_sockaddr_t *pstr_addr, uint8_t u8_addr_len )
{
    wifi7_connect_cmd_t str_connect = { 0 };

    if ( ( sock < 0 ) || ( sock >= WIFI7_MAX_SOCKET ) || ( pstr_addr == NULL ) ||
         ( u8_addr_len != sizeof( wifi7_sockaddr_in_t ) ) || !ctx->sockets[ sock ].b_is_used ||
         ( ( ( wifi7_sockaddr_in_t * ) pstr_addr )->sin_family != WIFI7_AF_INET ) )
    {
        return WIFI7_ERROR;
    }
    str_connect.sock = sock;
    memcpy( &str_connect.str_addr, pstr_addr, sizeof( str_connect.str_addr ) );
    str_connect.u16_session_id = ctx->sockets[ sock ].u16_session_id;
    return WIFI7_SOCKET_REQUEST( ctx, WIFI7_SOCKET_CMD_CONNECT, ( uint8_t * ) &str_connect, sizeof( str_connect ), NULL, 0, 0 );
}

err_t wifi7_socket_send ( wifi7_t *ctx, int8_t sock, void *pv_send_buffer, uint16_t u16_send_length )
{
    wifi7_send_cmd_t str_send = { 0 };
    uint16_t offset = WIFI7_TCP_TX_PACKET_OFFSET;

    if ( ( sock < 0 ) || ( sock >= WIFI7_MAX_SOCKET ) || ( pv_send_buffer == NULL ) || ( u16_send_length == 0 ) ||
         ( u16_send_length > WIFI7_SOCKET_BUFFER_MAX_LENGTH ) || !ctx->sockets[ sock ].b_is_used )
    {
        return WIFI7_ERROR;
    }
    if ( sock >= WIFI7_TCP_SOCK_MAX )
    {
        offset = WIFI7_UDP_TX_PACKET_OFFSET;
    }
    str_send.sock           = sock;
    str_send.u16_data_size  = u16_send_length;
    str_send.u16_session_id = ctx->sockets[ sock ].u16_session_id;
    return WIFI7_SOCKET_REQUEST( ctx, WIFI7_SOCKET_CMD_SEND | WIFI7_M2M_REQ_DATA_PKT,
                                 ( uint8_t * ) &str_send, sizeof( str_send ), pv_send_buffer, u16_send_length, offset );
}

err_t wifi7_socket_send_to ( wifi7_t *ctx, int8_t sock, void *pv_send_buffer, uint16_t u16_send_length,
                             wifi7_sockaddr_t *pstr_dest_addr, uint8_t u8_addr_len )
{
    wifi7_send_cmd_t str_send = { 0 };

    if ( ( sock < WIFI7_TCP_SOCK_MAX ) || ( sock >= WIFI7_MAX_SOCKET ) || ( pv_send_buffer == NULL ) ||
         ( pstr_dest_addr == NULL ) || ( u8_addr_len != sizeof( wifi7_sockaddr_in_t ) ) ||
         ( u16_send_length == 0 ) || ( u16_send_length > WIFI7_SOCKET_BUFFER_MAX_LENGTH ) ||
         !ctx->sockets[ sock ].b_is_used || ( ( ( wifi7_sockaddr_in_t * ) pstr_dest_addr )->sin_family != WIFI7_AF_INET ) )
    {
        return WIFI7_ERROR;
    }
    str_send.sock           = sock;
    str_send.u16_data_size  = u16_send_length;
    str_send.u16_session_id = ctx->sockets[ sock ].u16_session_id;
    memcpy( &str_send.str_addr, pstr_dest_addr, sizeof( str_send.str_addr ) );
    return WIFI7_SOCKET_REQUEST( ctx, WIFI7_SOCKET_CMD_SENDTO | WIFI7_M2M_REQ_DATA_PKT,
                                 ( uint8_t * ) &str_send, sizeof( str_send ), pv_send_buffer, u16_send_length,
                                 WIFI7_UDP_TX_PACKET_OFFSET );
}

err_t wifi7_socket_receive ( wifi7_t *ctx, int8_t sock, void *pv_recv_buf, uint16_t u16_buf_len, uint32_t u32_timeoutmsec )
{
    wifi7_recv_cmd_t str_recv = { 0 };
    err_t result;

    if ( ( sock < 0 ) || ( sock >= WIFI7_TCP_SOCK_MAX ) || ( pv_recv_buf == NULL ) || ( u16_buf_len == 0 ) ||
         !ctx->sockets[ sock ].b_is_used || ctx->sockets[ sock ].b_is_recv_pending )
    {
        return WIFI7_ERROR;
    }
    str_recv.u32_timeoutmsec = u32_timeoutmsec;
    if ( u32_timeoutmsec == 0 )
    {
        str_recv.u32_timeoutmsec = WIFI7_SOCKET_TIMEOUT_INFINITE;
    }
    str_recv.sock           = sock;
    str_recv.u16_session_id = ctx->sockets[ sock ].u16_session_id;
    result = WIFI7_SOCKET_REQUEST( ctx, WIFI7_SOCKET_CMD_RECV, ( uint8_t * ) &str_recv, sizeof( str_recv ), NULL, 0, 0 );
    if ( result == WIFI7_OK )
    {
        ctx->sockets[ sock ].pu8_user_buffer = ( uint8_t * ) pv_recv_buf;
        ctx->sockets[ sock ].u16_user_buffer_size = u16_buf_len;
        ctx->sockets[ sock ].b_is_recv_pending = 1;
    }
    return result;
}

err_t wifi7_socket_receive_from ( wifi7_t *ctx, int8_t sock, void *pv_recv_buf, uint16_t u16_buf_len, uint32_t u32_timeoutmsec )
{
    wifi7_recv_cmd_t str_recv = { 0 };
    err_t result;

    if ( ( sock < WIFI7_TCP_SOCK_MAX ) || ( sock >= WIFI7_MAX_SOCKET ) || ( pv_recv_buf == NULL ) || ( u16_buf_len == 0 ) ||
         !ctx->sockets[ sock ].b_is_used || ctx->sockets[ sock ].b_is_recv_pending )
    {
        return WIFI7_ERROR;
    }
    str_recv.u32_timeoutmsec = u32_timeoutmsec;
    if ( u32_timeoutmsec == 0 )
    {
        str_recv.u32_timeoutmsec = WIFI7_SOCKET_TIMEOUT_INFINITE;
    }
    str_recv.sock           = sock;
    str_recv.u16_session_id = ctx->sockets[ sock ].u16_session_id;
    result = WIFI7_SOCKET_REQUEST( ctx, WIFI7_SOCKET_CMD_RECVFROM, ( uint8_t * ) &str_recv, sizeof( str_recv ), NULL, 0, 0 );
    if ( result == WIFI7_OK )
    {
        ctx->sockets[ sock ].pu8_user_buffer = ( uint8_t * ) pv_recv_buf;
        ctx->sockets[ sock ].u16_user_buffer_size = u16_buf_len;
        ctx->sockets[ sock ].b_is_recv_pending = 1;
    }
    return result;
}

err_t wifi7_socket_close ( wifi7_t *ctx, int8_t sock )
{
    wifi7_close_cmd_t str_close = { 0 };
    err_t result;

    if ( ( sock < 0 ) || ( sock >= WIFI7_MAX_SOCKET ) || !ctx->sockets[ sock ].b_is_used )
    {
        return WIFI7_ERROR;
    }
    str_close.sock           = sock;
    str_close.u16_session_id = ctx->sockets[ sock ].u16_session_id;
    result = WIFI7_SOCKET_REQUEST( ctx, WIFI7_SOCKET_CMD_CLOSE, ( uint8_t * ) &str_close, sizeof( str_close ), NULL, 0, 0 );
    if ( result == WIFI7_OK )
    {
        memset( &ctx->sockets[ sock ], 0, sizeof( wifi7_socket_t ) );
    }
    return result;
}

err_t wifi7_connect ( wifi7_t *ctx, char *pc_ssid, uint8_t u8_ssid_len, wifi7_m2m_sec_type_t u8_sec_type, void *pv_auth_info,
                      uint16_t u16_ch )
{
    if ( ( pc_ssid == NULL ) || ( u8_ssid_len == 0 ) || ( u8_ssid_len >= WIFI7_M2M_MAX_SSID_LEN ) ||
         ( ( ( u16_ch < WIFI7_M2M_WIFI_CH_1 ) || ( u16_ch > WIFI7_M2M_WIFI_CH_14 ) ) && ( u16_ch != WIFI7_M2M_WIFI_CH_ALL ) ) )
    {
        return WIFI7_ERROR;
    }
    /* Credentials are deliberately not saved to module flash. */
    return wifi7_m2m_wifi_connect_sc( ctx, ( uint8_t * ) pc_ssid, u8_ssid_len, u8_sec_type,
                                      pv_auth_info, ( wifi7_m2m_scan_ch_t ) u16_ch, 1 );
}

err_t wifi7_get_connection_info ( wifi7_t *ctx )
{
    return wifi7_hif_send( ctx, WIFI7_M2M_REQ_GROUP_WIFI, WIFI7_M2M_WIFI_REQ_GET_CONN_INFO, NULL, 0, NULL, 0, 0 );
}

err_t wifi7_disconnect ( wifi7_t *ctx )
{
    return wifi7_hif_send( ctx, WIFI7_M2M_REQ_GROUP_WIFI, WIFI7_M2M_WIFI_REQ_DISCONNECT, NULL, 0, NULL, 0, 0 );
}

err_t wifi7_request_rssi ( wifi7_t *ctx )
{
    return wifi7_hif_send( ctx, WIFI7_M2M_REQ_GROUP_WIFI, WIFI7_M2M_WIFI_REQ_CURRENT_RSSI, NULL, 0, NULL, 0, 0 );
}

static err_t wifi7_hold ( wifi7_t *ctx )
{
    if ( WIFI7_OK != wifi7_nm_spi_init( ctx ) )
    {
        return WIFI7_ERROR;
    }
    if ( !WIFI7_IS_NMC1500( wifi7_chip_id( ctx ) ) )
    {
        return WIFI7_ERROR;
    }
    ctx->device_state = WIFI7_NM_STATE_INIT;
    return WIFI7_OK;
}

static err_t wifi7_start ( wifi7_t *ctx )
{
    uint32_t revision;
    uint16_t firmware_ver;
    uint16_t required_ver;

    if ( WIFI7_OK != wifi7_hif_init( ctx ) )
    {
        return WIFI7_ERROR;
    }
    wifi7_hif_register_cb( WIFI7_M2M_REQ_GROUP_WIFI, wifi7_m2m_wifi_cb );
    if ( ( WIFI7_OK != wifi7_wait_for_bootrom( ctx, WIFI7_M2M_WIFI_MODE_NORMAL ) ) ||
         ( WIFI7_OK != wifi7_wait_for_firmware_start( ctx, WIFI7_M2M_WIFI_MODE_NORMAL ) ) ||
         ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_NMI_REV_REG, &revision ) ) )
    {
        return WIFI7_ERROR;
    }
    firmware_ver = ( uint16_t ) revision;
    required_ver = ( uint16_t ) ( revision >> WIFI7_FW_MIN_DRIVER_SHIFT );
    if ( ( firmware_ver < WIFI7_DRIVER_VERSION ) || ( required_ver > WIFI7_DRIVER_VERSION ) ||
         ( ( firmware_ver >> WIFI7_FW_MAJOR_SHIFT ) != WIFI7_FW_MAJOR ) )
    {
        return WIFI7_ERROR_FW_VERSION;
    }
    if ( WIFI7_OK != wifi7_enable_interrupts( ctx ) )
    {
        return WIFI7_ERROR;
    }
    ctx->device_state = WIFI7_NM_STATE_START;
    return WIFI7_OK;
}

static uint8_t wifi7_crc7_byte ( uint8_t crc, uint8_t data_val )
{
    return crc7_syndrome_table[ ( crc << 1 ) ^ data_val ];
}

static uint8_t wifi7_crc7 ( uint8_t crc, uint8_t *buffer, uint32_t len )
{
    while ( len-- )
    {
        crc = wifi7_crc7_byte( crc, *buffer++ );
    }

    return crc;
}

static uint8_t wifi7_hexchar_2_val ( uint8_t ch )
{
    ch -= '0';
    if ( ch <= 9 )
    {
        return ch;
    }
    ch |= WIFI7_HEX_LOWERCASE_MASK;
    ch -= WIFI7_HEX_ALPHA_BIAS;
    if ( ch <= WIFI7_HEX_ALPHA_MAX )
    {
        return ch + WIFI7_HEX_ALPHA_BASE;
    }
    return WIFI7_HEX_INVALID;
}

static err_t wifi7_spi_cmd ( wifi7_t *ctx, uint8_t cmd, uint32_t adr, uint32_t data_in, uint32_t sz, uint8_t clockless )
{
    uint8_t bc[ WIFI7_SPI_CMD_WRITE_SIZE ];
    uint8_t len = WIFI7_SPI_CMD_READ_SIZE;
    err_t result = WIFI7_OK;

    bc[ 0 ] = cmd;
    switch ( cmd )
    {
        case WIFI7_CMD_SINGLE_READ: /* single word (4 bytes) read */
        {
            bc[ 1 ] = ( uint8_t ) ( adr >> 16 );
            bc[ 2 ] = ( uint8_t ) ( adr >> 8 );
            bc[ 3 ] = ( uint8_t ) ( adr );
            len = WIFI7_SPI_CMD_READ_SIZE;
            break;
        }
        case WIFI7_CMD_INTERNAL_READ: /* internal register read */
        {
            bc[ 1 ] = ( uint8_t ) ( adr >> 8 );
            if ( clockless )
                bc[ 1 ] |= WIFI7_SPI_CLKLESS_FLAG;
            bc[ 2 ] = ( uint8_t ) adr;
            bc[ 3 ] = 0x00;
            len = WIFI7_SPI_CMD_READ_SIZE;
            break;
        }
        case WIFI7_CMD_RESET: /* reset */
        {
            bc[ 1 ] = WIFI7_SPI_RESET_BYTE;
            bc[ 2 ] = WIFI7_SPI_RESET_BYTE;
            bc[ 3 ] = WIFI7_SPI_RESET_BYTE;
            len = WIFI7_SPI_CMD_READ_SIZE;
            break;
        }
        case WIFI7_CMD_DMA_EXT_WRITE: /* dma extended write */
        case WIFI7_CMD_DMA_EXT_READ:  /* dma extended read */
        {
            bc[ 1 ] = ( uint8_t ) ( adr >> 16 );
            bc[ 2 ] = ( uint8_t ) ( adr >> 8 );
            bc[ 3 ] = ( uint8_t ) ( adr );
            bc[ 4 ] = ( uint8_t ) ( sz >> 16 );
            bc[ 5 ] = ( uint8_t ) ( sz >> 8 );
            bc[ 6 ] = ( uint8_t ) ( sz );
            len = WIFI7_SPI_CMD_LONG_SIZE;
            break;
        }
        case WIFI7_CMD_INTERNAL_WRITE: /* internal register write */
        {
            bc[ 1 ] = ( uint8_t ) ( adr >> 8 );
            if ( clockless )
                bc[ 1 ] |= WIFI7_SPI_CLKLESS_FLAG;
            bc[ 2 ] = ( uint8_t ) ( adr );
            bc[ 3 ] = ( uint8_t ) ( data_in >> 24 );
            bc[ 4 ] = ( uint8_t ) ( data_in >> 16 );
            bc[ 5 ] = ( uint8_t ) ( data_in >> 8 );
            bc[ 6 ] = ( uint8_t ) ( data_in );
            len = WIFI7_SPI_CMD_LONG_SIZE;
            break;
        }
        case WIFI7_CMD_SINGLE_WRITE: /* single word write */
        {
            bc[ 1 ] = ( uint8_t ) ( adr >> 16 );
            bc[ 2 ] = ( uint8_t ) ( adr >> 8 );
            bc[ 3 ] = ( uint8_t ) ( adr );
            bc[ 4 ] = ( uint8_t ) ( data_in >> 24 );
            bc[ 5 ] = ( uint8_t ) ( data_in >> 16 );
            bc[ 6 ] = ( uint8_t ) ( data_in >> 8 );
            bc[ 7 ] = ( uint8_t ) ( data_in );
            len = WIFI7_SPI_CMD_WRITE_SIZE;
            break;
        }
        default:
        {
            result = WIFI7_ERROR;
            break;
        }
    }

    if ( WIFI7_OK == result )
    {
        if ( !gu8crc_off )
        {
            bc[ len - 1 ] = ( wifi7_crc7( WIFI7_SPI_CRC_INITIAL, ( uint8_t * ) &bc[ 0 ], len - 1 ) ) << 1;
        }
        else
        {
            len -= 1;
        }

        if ( wifi7_generic_write( ctx, bc, len ) < 0 )
        {
            result = WIFI7_ERROR;
        }
    }

    return result;
}

static err_t wifi7_spi_cmd_rsp ( wifi7_t *ctx, uint8_t cmd, uint8_t clockless )
{
    uint8_t response = 0;
    uint8_t count;

    if ( cmd == WIFI7_CMD_RESET )
    {
        if ( WIFI7_OK != wifi7_generic_read( ctx, &response, 1 ) )
        {
            return WIFI7_ERROR;
        }
    }
    for ( count = 0; count < WIFI7_SPI_RESP_RETRY_COUNT; count++ )
    {
        if ( WIFI7_OK != wifi7_generic_read( ctx, &response, 1 ) )
        {
            return WIFI7_ERROR;
        }
        if ( ( response == cmd ) || clockless )
        {
            break;
        }
    }
    if ( count == WIFI7_SPI_RESP_RETRY_COUNT )
    {
        return WIFI7_ERROR;
    }
    for ( count = 0; count < WIFI7_SPI_RESP_RETRY_COUNT; count++ )
    {
        if ( WIFI7_OK != wifi7_generic_read( ctx, &response, 1 ) )
        {
            return WIFI7_ERROR;
        }
        if ( ( response == 0 ) || clockless )
        {
            return WIFI7_OK;
        }
    }
    return WIFI7_ERROR;
}

static err_t wifi7_spi_data_read ( wifi7_t *ctx, uint8_t *b, uint16_t sz, uint8_t clockless )
{
    int16_t retry;
    uint16_t ix, nbytes;
    uint8_t crc[ WIFI7_SPI_CRC_SIZE ];
    uint8_t rsp;

    ix = 0;
    do
    {
        if ( sz <= WIFI7_DATA_PKT_SZ )
        {
            nbytes = sz;
        }
        else
        {
            nbytes = WIFI7_DATA_PKT_SZ;
        }

        retry = 10;
        do
        {
            if ( wifi7_generic_read( ctx, &rsp, 1 ) < 0 )
            {
                return WIFI7_ERROR;
            }

            if ( ( ( rsp >> WIFI7_SPI_DATA_NIBBLE_SHIFT ) & WIFI7_SPI_DATA_NIBBLE_MASK ) == WIFI7_SPI_DATA_NIBBLE_MASK )
            {
                if ( ( rsp & WIFI7_SPI_DATA_MARKER ) == WIFI7_SPI_DATA_MARKER )
                {
                    break;
                }
            }
        } while ( retry-- );

        if ( ( retry <= 0 ) && !clockless )
        {
            return WIFI7_ERROR;
        }

        if ( wifi7_generic_read( ctx, &b[ ix ], nbytes ) < 0 )
        {
            return WIFI7_ERROR;
        }

        if ( !clockless )
        {
            if ( !gu8crc_off )
            {
                if ( wifi7_generic_read( ctx, crc, WIFI7_SPI_CRC_SIZE ) < 0 )
                {
                    return WIFI7_ERROR;
                }
            }
        }

        ix += nbytes;
        sz -= nbytes;

    } while ( sz );

    return WIFI7_OK;
}

static err_t wifi7_spi_data_write ( wifi7_t *ctx, uint8_t *b, uint16_t sz )
{
    uint16_t ix = 0;
    uint16_t nbytes;
    err_t result = WIFI7_OK;
    uint8_t cmd, order, crc[ WIFI7_SPI_CRC_SIZE ] = { 0 };

    do
    {
        if ( sz <= WIFI7_DATA_PKT_SZ )
        {
            nbytes = sz;
        }
        else
        {
            nbytes = WIFI7_DATA_PKT_SZ;
        }

        cmd = WIFI7_SPI_DATA_MARKER;
        if ( ix == 0 )
        {
            if ( sz <= WIFI7_DATA_PKT_SZ )
            {
                order = WIFI7_SPI_PACKET_LAST;
            }
            else
            {
                order = WIFI7_SPI_PACKET_FIRST;
            }
        }
        else
        {
            if ( sz <= WIFI7_DATA_PKT_SZ )
            {
                order = WIFI7_SPI_PACKET_LAST;
            }
            else
            {
                order = WIFI7_SPI_PACKET_MIDDLE;
            }
        }
        cmd |= order;
        if ( WIFI7_OK != wifi7_generic_write( ctx, &cmd, 1 ) )
        {
            result = WIFI7_ERROR;
            break;
        }

        if ( WIFI7_OK != wifi7_generic_write( ctx, &b[ ix ], nbytes ) )
        {
            result = WIFI7_ERROR;
            break;
        }

        if ( !gu8crc_off )
        {
            if ( WIFI7_OK != wifi7_generic_write( ctx, crc, WIFI7_SPI_CRC_SIZE ) )
            {
                result = WIFI7_ERROR;
                break;
            }
        }

        ix += nbytes;
        sz -= nbytes;
    } while ( sz );

    return result;
}

static err_t wifi7_nm_spi_init ( wifi7_t *ctx )
{
    uint32_t chipid;
    uint32_t reg = 0;

    gu8crc_off = 0;

    if ( wifi7_reg_read( ctx, WIFI7_NMI_SPI_PROTOCOL_CONFIG, &reg ) != WIFI7_OK )
    {
        /* Read failed. Try with CRC off. This might happen when module
        is removed but chip isn't reset*/
        gu8crc_off = 1;

        if ( wifi7_reg_read( ctx, WIFI7_NMI_SPI_PROTOCOL_CONFIG, &reg ) != WIFI7_OK )
        {
            // Read failed with both CRC on and off, something went bad
            return WIFI7_ERROR;
        }
    }
    if ( gu8crc_off == 0 )
    {
        reg &= ~WIFI7_SPI_CRC_DISABLE_MASK; /* disable crc checking */
        reg &= ~WIFI7_SPI_PACKET_SIZE_MASK;
        reg |= WIFI7_SPI_PACKET_CFG_8K;
        if ( wifi7_reg_write( ctx, WIFI7_NMI_SPI_PROTOCOL_CONFIG, reg ) != WIFI7_OK )
        {
            return WIFI7_ERROR;
        }
        gu8crc_off = 1;
    }

    if ( wifi7_reg_read( ctx, WIFI7_NMI_CHIPID, &chipid ) != WIFI7_OK )
    {
        return WIFI7_ERROR;
    }

    /* Make sure SPI max. packet buf_len fits the defined WIFI7_DATA_PKT_SZ.  */
    if ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_NMI_SPI_PROTOCOL_CONFIG, &reg ) )
    {
        return WIFI7_ERROR;
    }
    reg &= ~WIFI7_SPI_PACKET_SIZE_MASK;
    switch ( WIFI7_DATA_PKT_SZ )
    {
        case WIFI7_SPI_PACKET_SIZE_256:
            reg |= WIFI7_SPI_PACKET_CFG_256;
            break;
        case WIFI7_SPI_PACKET_SIZE_512:
            reg |= WIFI7_SPI_PACKET_CFG_512;
            break;
        case WIFI7_SPI_PACKET_SIZE_1K:
            reg |= WIFI7_SPI_PACKET_CFG_1K;
            break;
        case WIFI7_SPI_PACKET_SIZE_2K:
            reg |= WIFI7_SPI_PACKET_CFG_2K;
            break;
        case WIFI7_SPI_PACKET_SIZE_4K:
            reg |= WIFI7_SPI_PACKET_CFG_4K;
            break;
        case WIFI7_DATA_PKT_SZ_8K:
            reg |= WIFI7_SPI_PACKET_CFG_8K;
            break;
    }
    return wifi7_reg_write( ctx, WIFI7_NMI_SPI_PROTOCOL_CONFIG, reg );
}

static err_t wifi7_wait_for_bootrom ( wifi7_t *ctx, uint8_t arg )
{
    uint32_t reg = 0;
    uint32_t count;
    uint32_t config = WIFI7_HAVE_RESERVED1_BIT;

    for ( count = 0; count < WIFI7_TIMEOUT; count++ )
    {
        if ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_EFUSE_STATUS_REG, &reg ) )
        {
            return WIFI7_ERROR;
        }
        if ( reg & WIFI7_NBIT31 )
        {
            break;
        }
        Delay_1ms( );
    }
    if ( ( count == WIFI7_TIMEOUT ) || ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_M2M_WAIT_FOR_HOST_REG, &reg ) ) )
    {
        return WIFI7_ERROR;
    }
    if ( !( reg & WIFI7_NBIT0 ) )
    {
        for ( count = 0; count < WIFI7_TIMEOUT; count++ )
        {
            Delay_1ms( );
            if ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_BOOTROM_REG, &reg ) )
            {
                return WIFI7_ERROR;
            }
            if ( reg == WIFI7_M2M_FINISH_BOOT_ROM )
            {
                break;
            }
        }
        if ( count == WIFI7_TIMEOUT )
        {
            return WIFI7_ERROR;
        }
    }
    if ( arg != WIFI7_M2M_WIFI_MODE_NORMAL )
    {
        return WIFI7_ERROR;
    }
    if ( WIFI7_REV( wifi7_chip_id( ctx ) ) >= WIFI7_REV_3A0 )
    {
        config |= WIFI7_HAVE_USE_PMU_BIT;
    }
    if ( WIFI7_OK != wifi7_reg_write( ctx, WIFI7_NMI_STATE_REG, WIFI7_DRIVER_INFO ) )
    {
        return WIFI7_ERROR;
    }
    for ( count = 0; count < WIFI7_SPI_RETRY_COUNT; count++ )
    {
        if ( ( WIFI7_OK != wifi7_reg_write( ctx, WIFI7_NMI_GP_REG_1, config ) ) ||
             ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_NMI_GP_REG_1, &reg ) ) )
        {
            return WIFI7_ERROR;
        }
        if ( reg == config )
        {
            return wifi7_reg_write( ctx, WIFI7_BOOTROM_REG, WIFI7_M2M_START_FIRMWARE );
        }
        Delay_1ms( );
    }
    return WIFI7_ERROR;
}

static err_t wifi7_wait_for_firmware_start ( wifi7_t *ctx, uint8_t arg )
{
    uint32_t reg = 0;
    uint32_t count;

    if ( arg != WIFI7_M2M_WIFI_MODE_NORMAL )
    {
        return WIFI7_ERROR;
    }
    for ( count = 0; count < WIFI7_TIMEOUT; count++ )
    {
        Delay_1ms( );
        Delay_1ms( );
        if ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_NMI_STATE_REG, &reg ) )
        {
            return WIFI7_ERROR;
        }
        if ( reg == WIFI7_M2M_FINISH_INIT_STATE )
        {
            return wifi7_reg_write( ctx, WIFI7_NMI_STATE_REG, 0 );
        }
    }
    return WIFI7_ERROR;
}

static err_t wifi7_chip_sleep ( wifi7_t *ctx )
{
    uint32_t reg;
    uint16_t count;

    for ( count = 0; count < WIFI7_WAKE_POLL_LIMIT; count++ )
    {
        if ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_CORT_HOST_COMM, &reg ) )
        {
            return WIFI7_ERROR;
        }
        if ( !( reg & WIFI7_NBIT0 ) )
        {
            break;
        }
        Delay_1ms( );
    }
    if ( ( count == WIFI7_WAKE_POLL_LIMIT ) ||
         ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_WAKE_CLK_REG, &reg ) ) ||
         ( WIFI7_OK != wifi7_reg_write( ctx, WIFI7_WAKE_CLK_REG, reg & ~WIFI7_NBIT1 ) ) ||
         ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_HOST_CORT_COMM, &reg ) ) )
    {
        return WIFI7_ERROR;
    }
    return wifi7_reg_write( ctx, WIFI7_HOST_CORT_COMM, reg & ~WIFI7_NBIT0 );
}

static err_t wifi7_chip_wake ( wifi7_t *ctx )
{
    uint32_t clocks;
    uint32_t reg;
    uint8_t count;

    if ( ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_HOST_CORT_COMM, &reg ) ) ||
         ( WIFI7_OK != wifi7_reg_write( ctx, WIFI7_HOST_CORT_COMM, reg | WIFI7_NBIT0 ) ) ||
         ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_WAKE_CLK_REG, &reg ) ) ||
         ( WIFI7_OK != wifi7_reg_write( ctx, WIFI7_WAKE_CLK_REG, reg | WIFI7_NBIT1 ) ) )
    {
        return WIFI7_ERROR;
    }
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    for ( count = 0; count < WIFI7_WAKEUP_TRIALS; count++ )
    {
        if ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_CLOCKS_EN_REG, &clocks ) )
        {
            return WIFI7_ERROR;
        }
        if ( clocks & WIFI7_NBIT2 )
        {
            /* Resynchronize SPI after accessing clockless registers. */
            if ( WIFI7_OK != wifi7_spi_cmd( ctx, WIFI7_CMD_RESET, 0, 0, 0, 0 ) )
            {
                return WIFI7_ERROR;
            }
            return wifi7_spi_cmd_rsp( ctx, WIFI7_CMD_RESET, 0 );
        }
        Delay_1ms( );
        Delay_1ms( );
    }
    return WIFI7_ERROR;
}

static err_t wifi7_enable_interrupts ( wifi7_t *ctx )
{
    uint32_t reg = 0;

    if ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_NMI_PIN_MUX_0, &reg ) )
    {
        return WIFI7_ERROR;
    }
    reg |= WIFI7_IRQ_MUX_MASK;
    if ( WIFI7_OK != wifi7_reg_write( ctx, WIFI7_NMI_PIN_MUX_0, reg ) )
    {
        return WIFI7_ERROR;
    }

    if ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_NMI_INTR_ENABLE, &reg ) )
    {
        return WIFI7_ERROR;
    }
    reg |= WIFI7_IRQ_ENABLE_MASK;
    if ( WIFI7_OK != wifi7_reg_write( ctx, WIFI7_NMI_INTR_ENABLE, reg ) )
    {
        return WIFI7_ERROR;
    }
    return WIFI7_OK;
}

static err_t wifi7_hif_init ( wifi7_t *ctx )
{
    memset( &hif_cxt, 0, sizeof( hif_cxt ) );
    return WIFI7_OK;
}

static err_t wifi7_hif_send ( wifi7_t *ctx, uint8_t u8_gid, uint8_t u8_opcode, uint8_t *pu8_ctrl_buf,
                              uint16_t u16_ctrl_buf_size, uint8_t *pu8_data_buf, uint16_t u16_data_size,
                              uint16_t u16_data_offset )
{
    uint8_t header[ WIFI7_M2M_HIF_HDR_OFFSET ] = { 0 };
    uint8_t wake_owned = 0;
    uint32_t length = WIFI7_M2M_HIF_HDR_OFFSET + ( uint32_t ) u16_ctrl_buf_size;
    uint32_t reg = 0;
    uint32_t dma_addr = 0;
    uint16_t count;
    err_t result = WIFI7_ERROR;

    if ( ( ctx->device_state != WIFI7_NM_STATE_START ) ||
         ( ( u16_ctrl_buf_size != 0 ) && ( pu8_ctrl_buf == NULL ) ) ||
         ( ( u16_data_size != 0 ) && ( pu8_data_buf == NULL ) ) )
    {
        return WIFI7_ERROR;
    }
    if ( u16_data_size != 0 )
    {
        if ( u16_data_offset < u16_ctrl_buf_size )
        {
            return WIFI7_ERROR;
        }
        length = WIFI7_M2M_HIF_HDR_OFFSET + ( uint32_t ) u16_data_offset + u16_data_size;
    }
    if ( length > WIFI7_M2M_HIF_MAX_PACKET_SIZE )
    {
        return WIFI7_ERROR;
    }
    if ( !hif_cxt.u8_hif_rx_done )
    {
        if ( WIFI7_OK != wifi7_chip_wake( ctx ) )
        {
            return WIFI7_ERROR;
        }
        wake_owned = 1;
    }
    reg = ( uint32_t ) u8_gid | ( ( uint32_t ) u8_opcode << WIFI7_HIF_OPCODE_SHIFT ) | ( length << WIFI7_HIF_LENGTH_SHIFT );
    if ( ( WIFI7_OK != wifi7_reg_write( ctx, WIFI7_NMI_STATE_REG, reg ) ) ||
         ( WIFI7_OK != wifi7_reg_write( ctx, WIFI7_WIFI_HOST_RCV_CTRL_2, WIFI7_NBIT1 ) ) )
    {
        goto hif_send_exit;
    }
    for ( count = 0; count < WIFI7_HIF_POLL_LIMIT; count++ )
    {
        if ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_WIFI_HOST_RCV_CTRL_2, &reg ) )
        {
            goto hif_send_exit;
        }
        if ( !( reg & WIFI7_NBIT1 ) )
        {
            break;
        }
        Delay_1ms( );
    }
    if ( ( count == WIFI7_HIF_POLL_LIMIT ) ||
         ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_WIFI_HOST_RCV_CTRL_4, &dma_addr ) ) || ( dma_addr == 0 ) )
    {
        goto hif_send_exit;
    }
    header[ WIFI7_HIF_GROUP_INDEX ] = u8_gid;
    header[ WIFI7_HIF_OPCODE_INDEX ] = u8_opcode & ~WIFI7_M2M_REQ_DATA_PKT;
    header[ WIFI7_HIF_LENGTH_LOW_INDEX ] = ( uint8_t ) length;
    header[ WIFI7_HIF_LENGTH_HIGH_INDEX ] = ( uint8_t ) ( length >> 8 );
    if ( WIFI7_OK != wifi7_block_write( ctx, dma_addr, header, sizeof( header ) ) )
    {
        goto hif_send_exit;
    }
    if ( ( u16_ctrl_buf_size != 0 ) &&
         ( WIFI7_OK != wifi7_block_write( ctx, dma_addr + WIFI7_M2M_HIF_HDR_OFFSET, pu8_ctrl_buf, u16_ctrl_buf_size ) ) )
    {
        goto hif_send_exit;
    }
    if ( ( u16_data_size != 0 ) &&
         ( WIFI7_OK != wifi7_block_write( ctx, dma_addr + WIFI7_M2M_HIF_HDR_OFFSET + u16_data_offset,
                                          pu8_data_buf, u16_data_size ) ) )
    {
        goto hif_send_exit;
    }
    result = wifi7_reg_write( ctx, WIFI7_WIFI_HOST_RCV_CTRL_3, ( dma_addr << WIFI7_HIF_ADDRESS_SHIFT ) | WIFI7_NBIT1 );

hif_send_exit:
    /* A callback sending during chunked reception borrows the receiver's wake state. */
    if ( wake_owned && ( WIFI7_OK != wifi7_chip_sleep( ctx ) ) )
    {
        result = WIFI7_ERROR;
    }
    if ( result != WIFI7_OK )
    {
        /* A host timeout does not cancel a firmware request. Require explicit reinitialization. */
        ctx->device_state = WIFI7_NM_STATE_DEINIT;
    }
    return result;
}

static err_t wifi7_hif_receive ( wifi7_t *ctx, uint32_t u32_addr, uint8_t *pu8_buf, uint16_t u16_sz, uint8_t is_done )
{
    if ( ( u16_sz == 0 ) && is_done )
    {
        if ( WIFI7_OK == wifi7_hif_set_rx_done( ctx ) )
        {
            return WIFI7_OK;
        }
    }
    else if ( ( pu8_buf != NULL ) && ( u16_sz != 0 ) && ( u32_addr >= hif_cxt.u32_rx_addr ) &&
              ( u16_sz <= hif_cxt.u32_rx_size ) &&
              ( ( u32_addr - hif_cxt.u32_rx_addr ) <= ( hif_cxt.u32_rx_size - u16_sz ) ) )
    {
        if ( WIFI7_OK == wifi7_block_read( ctx, u32_addr, pu8_buf, u16_sz ) )
        {
            if ( !is_done || ( WIFI7_OK == wifi7_hif_set_rx_done( ctx ) ) )
            {
                return WIFI7_OK;
            }
        }
    }
    hif_cxt.rx_error = 1;
    return WIFI7_ERROR;
}

static err_t wifi7_hif_set_rx_done ( wifi7_t *ctx )
{
    uint32_t reg;

    if ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_WIFI_HOST_RCV_CTRL_0, &reg ) )
    {
        return WIFI7_ERROR;
    }
    if ( WIFI7_OK != wifi7_reg_write( ctx, WIFI7_WIFI_HOST_RCV_CTRL_0, reg | WIFI7_NBIT1 ) )
    {
        return WIFI7_ERROR;
    }
    hif_cxt.u8_hif_rx_done = 0;
    return WIFI7_OK;
}


static err_t wifi7_hif_isr ( wifi7_t *ctx )
{
    uint32_t reg;
    uint32_t address;
    uint16_t length;
    uint16_t buffer_length;
    uint8_t header[ sizeof( wifi7_hif_hdr_t ) ];

    if ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_WIFI_HOST_RCV_CTRL_0, &reg ) )
    {
        return WIFI7_ERROR;
    }
    if ( !( reg & WIFI7_NBIT0 ) )
    {
        return WIFI7_OK;
    }
    if ( ( WIFI7_OK != wifi7_reg_write( ctx, WIFI7_WIFI_HOST_RCV_CTRL_0, reg & ~WIFI7_NBIT0 ) ) ||
         ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_WIFI_HOST_RCV_CTRL_0, &reg ) ) ||
         ( WIFI7_OK != wifi7_reg_read( ctx, WIFI7_WIFI_HOST_RCV_CTRL_1, &address ) ) )
    {
        return WIFI7_ERROR;
    }
    buffer_length = ( uint16_t ) ( ( reg >> WIFI7_HIF_RX_LENGTH_SHIFT ) & WIFI7_HIF_RX_LENGTH_MASK );
    if ( ( buffer_length < WIFI7_M2M_HIF_HDR_OFFSET ) || ( address == 0 ) ||
         ( WIFI7_OK != wifi7_block_read( ctx, address, header, sizeof( header ) ) ) )
    {
        return WIFI7_ERROR;
    }
    length = ( uint16_t ) header[ WIFI7_HIF_LENGTH_LOW_INDEX ] | ( ( uint16_t ) header[ WIFI7_HIF_LENGTH_HIGH_INDEX ] << 8 );
    if ( ( length < WIFI7_M2M_HIF_HDR_OFFSET ) || ( length > buffer_length ) ||
         ( ( buffer_length - length ) > WIFI7_HIF_PADDING_MAX ) )
    {
        return WIFI7_ERROR;
    }
    hif_cxt.u32_rx_addr    = address;
    hif_cxt.u32_rx_size    = length;
    hif_cxt.u8_hif_rx_done = 1;
    hif_cxt.rx_error       = 0;
    if ( ( header[ WIFI7_HIF_GROUP_INDEX ] == WIFI7_M2M_REQ_GROUP_WIFI ) && hif_cxt.pf_wifi_cb )
    {
        hif_cxt.pf_wifi_cb( ctx, header[ WIFI7_HIF_OPCODE_INDEX ], length - WIFI7_M2M_HIF_HDR_OFFSET,
                            address + WIFI7_M2M_HIF_HDR_OFFSET );
    }
    else if ( ( header[ WIFI7_HIF_GROUP_INDEX ] == WIFI7_M2M_REQ_GROUP_IP ) && hif_cxt.pf_ip_cb )
    {
        hif_cxt.pf_ip_cb( ctx, header[ WIFI7_HIF_OPCODE_INDEX ], length - WIFI7_M2M_HIF_HDR_OFFSET,
                          address + WIFI7_M2M_HIF_HDR_OFFSET );
    }
    if ( hif_cxt.u8_hif_rx_done )
    {
        if ( WIFI7_OK != wifi7_hif_set_rx_done( ctx ) )
        {
            return WIFI7_ERROR;
        }
    }
    if ( hif_cxt.rx_error )
    {
        return WIFI7_ERROR;
    }
    return WIFI7_OK;
}

static err_t wifi7_hif_handle_isr ( wifi7_t *ctx )
{
    err_t result;

    if ( digital_in_read( &ctx->int_pin ) )
    {
        return WIFI7_OK;
    }
    if ( WIFI7_OK != wifi7_chip_wake( ctx ) )
    {
        return WIFI7_ERROR;
    }
    result = wifi7_hif_isr( ctx );
    if ( WIFI7_OK != wifi7_chip_sleep( ctx ) )
    {
        return WIFI7_ERROR;
    }
    return result;
}

static void wifi7_m2m_wifi_cb ( wifi7_t *ctx, uint8_t u8_op_code, uint16_t u16_data_size, uint32_t u32_addr )
{
    if ( u8_op_code == WIFI7_M2M_WIFI_RESP_CON_STATE_CHANGED )
    {
        wifi7_m2m_wifi_state_changed_t state;
        if ( WIFI7_OK == wifi7_hif_receive( ctx, u32_addr, ( uint8_t * ) &state, sizeof( state ), 1 ) )
        {
            if ( ctx->app_wifi_cb )
            {
                ctx->app_wifi_cb( u8_op_code, &state );
            }
        }
    }
    else if ( u8_op_code == WIFI7_M2M_WIFI_REQ_DHCP_CONF )
    {
        wifi7_m2mip_config_t ip_config;
        if ( WIFI7_OK == wifi7_hif_receive( ctx, u32_addr, ( uint8_t * ) &ip_config, sizeof( ip_config ), 1 ) )
        {
            if ( ctx->app_wifi_cb )
            {
                ctx->app_wifi_cb( u8_op_code, &ip_config );
            }
        }
    }
    else if ( u8_op_code == WIFI7_M2M_WIFI_RESP_SCAN_DONE )
    {
        wifi7_m2m_scan_done_t scan;
        if ( WIFI7_OK == wifi7_hif_receive( ctx, u32_addr, ( uint8_t * ) &scan, sizeof( scan ), 1 ) )
        {
            ctx->ch_num = 0;
            if ( scan.s8_scan_state == WIFI7_OK )
            {
                ctx->ch_num = scan.u8_numof_ch;
            }
            if ( ctx->app_wifi_cb )
            {
                ctx->app_wifi_cb( u8_op_code, &scan );
            }
        }
    }
    else if ( u8_op_code == WIFI7_M2M_WIFI_RESP_SCAN_RESULT )
    {
        wifi7_m2m_wifiscan_result_t scan_result;
        if ( WIFI7_OK == wifi7_hif_receive( ctx, u32_addr, ( uint8_t * ) &scan_result, sizeof( scan_result ), 1 ) )
        {
            scan_result.au8ssid[ WIFI7_M2M_MAX_SSID_LEN - 1 ] = 0;
            if ( ctx->app_wifi_cb )
            {
                ctx->app_wifi_cb( u8_op_code, &scan_result );
            }
        }
    }
    else if ( u8_op_code == WIFI7_M2M_WIFI_RESP_CONN_INFO )
    {
        wifi7_m2m_conn_info_t info;
        if ( WIFI7_OK == wifi7_hif_receive( ctx, u32_addr, ( uint8_t * ) &info, sizeof( info ), 1 ) )
        {
            info.ac_ssid[ WIFI7_M2M_MAX_SSID_LEN - 1 ] = 0;
            if ( ctx->app_wifi_cb )
            {
                ctx->app_wifi_cb( u8_op_code, &info );
            }
        }
    }
    else if ( u8_op_code == WIFI7_M2M_WIFI_RESP_CURRENT_RSSI )
    {
        int8_t rssi[ WIFI7_RSSI_MESSAGE_SIZE ];
        if ( WIFI7_OK == wifi7_hif_receive( ctx, u32_addr, ( uint8_t * ) rssi, sizeof( rssi ), 1 ) )
        {
            if ( ctx->app_wifi_cb )
            {
                ctx->app_wifi_cb( u8_op_code, rssi );
            }
        }
    }
    else if ( u8_op_code == WIFI7_M2M_WIFI_RESP_IP_CONFLICT )
    {
        uint32_t conflicted_ip;
        if ( WIFI7_OK == wifi7_hif_receive( ctx, u32_addr, ( uint8_t * ) &conflicted_ip, sizeof( conflicted_ip ), 1 ) )
        {
            if ( ctx->app_wifi_cb )
            {
                ctx->app_wifi_cb( u8_op_code, &conflicted_ip );
            }
        }
    }
}

static err_t wifi7_hif_register_cb ( uint8_t u8_grp, wifi7_hif_call_back_t fn )
{
    if ( u8_grp == WIFI7_M2M_REQ_GROUP_WIFI )
    {
        hif_cxt.pf_wifi_cb = fn;
    }
    else if ( u8_grp == WIFI7_M2M_REQ_GROUP_IP )
    {
        hif_cxt.pf_ip_cb = fn;
    }
    else
    {
        return WIFI7_ERROR;
    }
    return WIFI7_OK;
}

static void wifi7_m2m_ip_cb ( wifi7_t *ctx, uint8_t u8_op_code, uint16_t u16_buffer_size, uint32_t u32_address )
{
    if ( ( u8_op_code == WIFI7_SOCKET_CMD_BIND ) || ( u8_op_code == WIFI7_SOCKET_CMD_LISTEN ) )
    {
        wifi7_bind_reply_t reply;
        wifi7_socket_bind_msg_t bind_msg;
        wifi7_socket_listen_msg_t listen_msg;

        if ( WIFI7_OK != wifi7_hif_receive( ctx, u32_address, ( uint8_t * ) &reply, sizeof( reply ), 1 ) )
        {
            return;
        }
        if ( ( reply.sock < 0 ) || ( reply.sock >= WIFI7_MAX_SOCKET ) || !ctx->sockets[ reply.sock ].b_is_used ||
             ( reply.u16_session_id != ctx->sockets[ reply.sock ].u16_session_id ) )
        {
            return;
        }
        if ( ctx->app_socket_cb )
        {
            if ( u8_op_code == WIFI7_SOCKET_CMD_BIND )
            {
                bind_msg.status = reply.s8_status;
                ctx->app_socket_cb( reply.sock, WIFI7_SOCKET_MSG_BIND, &bind_msg );
            }
            else
            {
                listen_msg.status = reply.s8_status;
                ctx->app_socket_cb( reply.sock, WIFI7_SOCKET_MSG_LISTEN, &listen_msg );
            }
        }
    }
    else if ( u8_op_code == WIFI7_SOCKET_CMD_ACCEPT )
    {
        wifi7_accept_reply_t reply;
        wifi7_socket_accept_msg_t accepted = { 0 };
        int8_t sock;

        if ( WIFI7_OK != wifi7_hif_receive( ctx, u32_address, ( uint8_t * ) &reply, sizeof( reply ), 1 ) )
        {
            return;
        }
        if ( ( reply.s_listen_sock < 0 ) || ( reply.s_listen_sock >= WIFI7_TCP_SOCK_MAX ) ||
             !ctx->sockets[ reply.s_listen_sock ].b_is_used )
        {
            return;
        }
        sock = reply.s_connected_sock;
        if ( sock >= WIFI7_TCP_SOCK_MAX )
        {
            hif_cxt.rx_error = 1;
            return;
        }
        if ( sock >= 0 )
        {
            if ( ctx->sockets[ sock ].b_is_used )
            {
                hif_cxt.rx_error = 1;
                return;
            }
            memset( &ctx->sockets[ sock ], 0, sizeof( wifi7_socket_t ) );
            ctx->session_id++;
            if ( ctx->session_id == 0 )
            {
                ctx->session_id++;
            }
            ctx->sockets[ sock ].b_is_used = 1;
            ctx->sockets[ sock ].u16_session_id = ctx->session_id;
        }
        accepted.sock                     = sock;
        accepted.str_addr.sin_family      = WIFI7_AF_INET;
        accepted.str_addr.sin_port        = reply.str_addr.u16_port;
        accepted.str_addr.sin_addr.s_addr = reply.str_addr.u32ip_addr;
        if ( ctx->app_socket_cb )
        {
            ctx->app_socket_cb( reply.s_listen_sock, WIFI7_SOCKET_MSG_ACCEPT, &accepted );
        }
    }
    else if ( u8_op_code == WIFI7_SOCKET_CMD_CONNECT )
    {
        wifi7_connect_reply_t reply;
        wifi7_socket_connect_msg_t connected;

        if ( WIFI7_OK != wifi7_hif_receive( ctx, u32_address, ( uint8_t * ) &reply, sizeof( reply ), 1 ) )
        {
            return;
        }
        if ( ( reply.sock < 0 ) || ( reply.sock >= WIFI7_MAX_SOCKET ) || !ctx->sockets[ reply.sock ].b_is_used )
        {
            return;
        }
        connected.sock     = reply.sock;
        connected.s8_error = reply.s8_error;
        if ( ctx->app_socket_cb )
        {
            ctx->app_socket_cb( reply.sock, WIFI7_SOCKET_MSG_CONNECT, &connected );
        }
    }
    else if ( ( u8_op_code == WIFI7_SOCKET_CMD_RECV ) || ( u8_op_code == WIFI7_SOCKET_CMD_RECVFROM ) )
    {
        wifi7_recv_reply_t reply;
        wifi7_socket_recv_msg_t received = { 0 };
        uint8_t evt = WIFI7_SOCKET_MSG_RECV;
        int8_t sock;

        if ( WIFI7_OK != wifi7_hif_receive( ctx, u32_address, ( uint8_t * ) &reply, sizeof( reply ), 0 ) )
        {
            return;
        }
        sock = reply.sock;
        if ( ( sock < 0 ) || ( sock >= WIFI7_MAX_SOCKET ) || !ctx->sockets[ sock ].b_is_used ||
             ( reply.u16_session_id != ctx->sockets[ sock ].u16_session_id ) )
        {
            return;
        }
        if ( !ctx->sockets[ sock ].b_is_recv_pending )
        {
            hif_cxt.rx_error = 1;
            return;
        }
        if ( u8_op_code == WIFI7_SOCKET_CMD_RECVFROM )
        {
            evt = WIFI7_SOCKET_MSG_RECVFROM;
        }
        received.str_remote_addr.sin_family      = WIFI7_AF_INET;
        received.str_remote_addr.sin_port        = reply.str_remote_addr.u16_port;
        received.str_remote_addr.sin_addr.s_addr = reply.str_remote_addr.u32ip_addr;
        if ( reply.s16_recv_status > 0 )
        {
            if ( ( reply.u16_data_offset < sizeof( reply ) ) || ( reply.u16_data_offset > u16_buffer_size ) ||
                 ( ( uint16_t ) reply.s16_recv_status > u16_buffer_size - reply.u16_data_offset ) )
            {
                hif_cxt.rx_error = 1;
                return;
            }
            wifi7_socket_read_socket_data( ctx, sock, &received, evt, u32_address + reply.u16_data_offset,
                                           ( uint16_t ) reply.s16_recv_status );
        }
        else
        {
            received.s16_buffer_size = reply.s16_recv_status;
            ctx->sockets[ sock ].b_is_recv_pending = 0;
            ctx->sockets[ sock ].pu8_user_buffer = NULL;
            ctx->sockets[ sock ].u16_user_buffer_size = 0;
            if ( ( WIFI7_OK == wifi7_hif_receive( ctx, 0, NULL, 0, 1 ) ) && ctx->app_socket_cb )
            {
                ctx->app_socket_cb( sock, evt, &received );
            }
        }
    }
    else if ( ( u8_op_code == WIFI7_SOCKET_CMD_SEND ) || ( u8_op_code == WIFI7_SOCKET_CMD_SENDTO ) )
    {
        wifi7_send_reply_t reply;
        uint8_t evt = WIFI7_SOCKET_MSG_SEND;

        if ( WIFI7_OK != wifi7_hif_receive( ctx, u32_address, ( uint8_t * ) &reply, sizeof( reply ), 1 ) )
        {
            return;
        }
        if ( ( reply.sock < 0 ) || ( reply.sock >= WIFI7_MAX_SOCKET ) || !ctx->sockets[ reply.sock ].b_is_used ||
             ( reply.u16_session_id != ctx->sockets[ reply.sock ].u16_session_id ) )
        {
            return;
        }
        if ( u8_op_code == WIFI7_SOCKET_CMD_SENDTO )
        {
            evt = WIFI7_SOCKET_MSG_SENDTO;
        }
        if ( ctx->app_socket_cb )
        {
            ctx->app_socket_cb( reply.sock, evt, &reply.s16_sent_bytes );
        }
    }
}

static void wifi7_socket_read_socket_data ( wifi7_t *ctx, int8_t sock, wifi7_socket_recv_msg_t *pstr_recv,
                                            uint8_t u8_socket_msg, uint32_t u32_start_address, uint16_t u16_read_count )
{
    uint8_t *buffer = ctx->sockets[ sock ].pu8_user_buffer;
    uint16_t capacity = ctx->sockets[ sock ].u16_user_buffer_size;
    uint16_t session_id = ctx->sockets[ sock ].u16_session_id;
    uint16_t read_count;
    uint8_t is_done;

    if ( ( buffer == NULL ) || ( capacity == 0 ) )
    {
        hif_cxt.rx_error = 1;
        return;
    }
    pstr_recv->u16_remaining_size = u16_read_count;
    while ( u16_read_count != 0 )
    {
        read_count = u16_read_count;
        is_done = 1;
        if ( read_count > capacity )
        {
            read_count = capacity;
            is_done = 0;
        }
        /* Firmware 19.5.4 may return more bytes than fit in the caller's receive buffer. */
        if ( WIFI7_OK != wifi7_hif_receive( ctx, u32_start_address, buffer, read_count, is_done ) )
        {
            return;
        }
        u16_read_count -= read_count;
        u32_start_address += read_count;
        pstr_recv->pu8_buffer = buffer;
        pstr_recv->s16_buffer_size = ( int16_t ) read_count;
        pstr_recv->u16_remaining_size = u16_read_count;
        if ( is_done )
        {
            ctx->sockets[ sock ].b_is_recv_pending = 0;
            ctx->sockets[ sock ].pu8_user_buffer = NULL;
            ctx->sockets[ sock ].u16_user_buffer_size = 0;
        }
        if ( ctx->app_socket_cb )
        {
            ctx->app_socket_cb( sock, u8_socket_msg, pstr_recv );
        }
        if ( ( u16_read_count != 0 ) &&
             ( !ctx->sockets[ sock ].b_is_used || ( ctx->sockets[ sock ].u16_session_id != session_id ) ) )
        {
            /* A callback may close the socket; release the unread remainder of this HIF message. */
            wifi7_hif_receive( ctx, 0, NULL, 0, 1 );
            return;
        }
    }
}

static err_t wifi7_m2m_wifi_connect_sc ( wifi7_t *ctx, uint8_t *pc_ssid, uint8_t u8_ssid_len, wifi7_m2m_sec_type_t u8_sec_type,
                                         void *pv_auth_info, wifi7_m2m_scan_ch_t u16_ch, uint16_t u8_no_save_cred )
{
    wifi7_m2m_wifi_connect_t str_connect = { 0 };
    uint8_t *password = ( uint8_t * ) pv_auth_info;
    uint8_t length = 0;
    uint8_t index;
    err_t result;

    if ( u8_no_save_cred != 1 )
    {
        return WIFI7_ERROR;
    }
    if ( u8_sec_type == WIFI7_M2M_WIFI_SEC_WPA_PSK )
    {
        if ( password == NULL )
        {
            return WIFI7_ERROR;
        }
        while ( ( length < WIFI7_M2M_MAX_PSK_LEN ) && ( password[ length ] != 0 ) )
        {
            length++;
        }
        if ( ( length < WIFI7_PSK_MIN_LENGTH ) || ( length >= WIFI7_M2M_MAX_PSK_LEN ) )
        {
            return WIFI7_ERROR;
        }
        if ( length == WIFI7_M2M_MAX_PSK_LEN - 1 )
        {
            for ( index = 0; index < length; index++ )
            {
                if ( wifi7_hexchar_2_val( password[ index ] ) > WIFI7_HEX_DIGIT_MAX )
                {
                    return WIFI7_ERROR;
                }
            }
        }
        memcpy( str_connect.str_sec.au8_psk, password, length );
    }
    else if ( u8_sec_type != WIFI7_M2M_WIFI_SEC_OPEN )
    {
        return WIFI7_ERROR;
    }
    str_connect.str_sec.u8_sec_type = ( uint8_t ) u8_sec_type;
    str_connect.u16_channel = ( uint16_t ) u16_ch;
    memcpy( str_connect.au8_ssid, pc_ssid, u8_ssid_len );
    str_connect.u8_no_save_cred = 1;

    /* Firmware 19.5.4 uses the 108-byte legacy connection request, opcode 40. */
    result = wifi7_hif_send( ctx, WIFI7_M2M_REQ_GROUP_WIFI, WIFI7_M2M_WIFI_REQ_CONNECT,
                             ( uint8_t * ) &str_connect, sizeof( str_connect ), NULL, 0, 0 );
    memset( &str_connect, 0, sizeof( str_connect ) );
    return result;
}

static uint8_t wifi7_m2m_wifi_get_state ( wifi7_t *ctx )
{
    switch ( ctx->device_state )
    {
        case WIFI7_NM_STATE_DEINIT:
            return WIFI7_WIFI_STATE_DEINIT;
        case WIFI7_NM_STATE_INIT:
            return WIFI7_WIFI_STATE_INIT;
        case WIFI7_NM_STATE_START:
            return WIFI7_WIFI_STATE_START;
    }
    return WIFI7_WIFI_STATE_DEINIT;
}

static err_t wifi7_m2m_wifi_handle_events ( wifi7_t *ctx )
{
    err_t ret = WIFI7_ERROR;

    if ( WIFI7_WIFI_STATE_START == wifi7_m2m_wifi_get_state( ctx ) )
    {
        ret = wifi7_hif_handle_isr( ctx );
    }

    return ret;
}

static err_t wifi7_m2m_wifi_req_scan_result ( wifi7_t *ctx, uint8_t scan_request_index )
{
    wifi7_m2m_req_scan_result_t str_req_scan_rlt = { 0 };
    if ( scan_request_index >= ctx->ch_num )
    {
        return WIFI7_ERROR;
    }
    str_req_scan_rlt.u8_index = scan_request_index;
    return wifi7_hif_send( ctx, WIFI7_M2M_REQ_GROUP_WIFI, WIFI7_M2M_WIFI_REQ_SCAN_RESULT,
                           ( uint8_t * ) &str_req_scan_rlt, sizeof( str_req_scan_rlt ), NULL, 0, 0 );
}

static err_t wifi7_m2m_wifi_request_scan ( wifi7_t *ctx, uint8_t ch )
{
    if ( ( ( ch >= WIFI7_M2M_WIFI_CH_1 ) && ( ch <= WIFI7_M2M_WIFI_CH_14 ) ) || ( ch == WIFI7_M2M_WIFI_CH_ALL ) )
    {
        wifi7_m2m_scan_t strtmp = { 0 };
        strtmp.u8_ch_num = ch;
        return wifi7_hif_send( ctx, WIFI7_M2M_REQ_GROUP_WIFI, WIFI7_M2M_WIFI_REQ_SCAN, ( uint8_t * ) &strtmp,
                               sizeof( wifi7_m2m_scan_t ), NULL, 0, 0 );
    }
    else
    {
        return WIFI7_ERROR;
    }
}

// ------------------------------------------------------------------------- END
