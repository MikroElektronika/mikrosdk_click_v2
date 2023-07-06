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
 * @file wifi8.c
 * @brief WiFi 8 Click Driver.
 */

#include "wifi8.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY 0x00


/**
 * @brief Driver variables.
 * @details Variables for helping driver functionality.
 */
static uint16_t gau16_hif_blacklist[] = { NEW_HIF_LIST };
static uint8_t gu8crc_off = 0;
static wifi8_hif_context_t hif_cxt;
static wifi8_nm_bus_capabilities_t egstr_nm_bus_capabilities = { NM_BUS_MAX_TRX_SZ };

/**
 * @brief CRC.
 * @details Matrix for CRC generation.
 */
static const uint8_t crc7_syndrome_table[256] =
{
    0x00, 0x09, 0x12, 0x1b, 0x24, 0x2d, 0x36, 0x3f,
    0x48, 0x41, 0x5a, 0x53, 0x6c, 0x65, 0x7e, 0x77,
    0x19, 0x10, 0x0b, 0x02, 0x3d, 0x34, 0x2f, 0x26,
    0x51, 0x58, 0x43, 0x4a, 0x75, 0x7c, 0x67, 0x6e,
    0x32, 0x3b, 0x20, 0x29, 0x16, 0x1f, 0x04, 0x0d,
    0x7a, 0x73, 0x68, 0x61, 0x5e, 0x57, 0x4c, 0x45,
    0x2b, 0x22, 0x39, 0x30, 0x0f, 0x06, 0x1d, 0x14,
    0x63, 0x6a, 0x71, 0x78, 0x47, 0x4e, 0x55, 0x5c,
    0x64, 0x6d, 0x76, 0x7f, 0x40, 0x49, 0x52, 0x5b,
    0x2c, 0x25, 0x3e, 0x37, 0x08, 0x01, 0x1a, 0x13,
    0x7d, 0x74, 0x6f, 0x66, 0x59, 0x50, 0x4b, 0x42,
    0x35, 0x3c, 0x27, 0x2e, 0x11, 0x18, 0x03, 0x0a,
    0x56, 0x5f, 0x44, 0x4d, 0x72, 0x7b, 0x60, 0x69,
    0x1e, 0x17, 0x0c, 0x05, 0x3a, 0x33, 0x28, 0x21,
    0x4f, 0x46, 0x5d, 0x54, 0x6b, 0x62, 0x79, 0x70,
    0x07, 0x0e, 0x15, 0x1c, 0x23, 0x2a, 0x31, 0x38,
    0x41, 0x48, 0x53, 0x5a, 0x65, 0x6c, 0x77, 0x7e,
    0x09, 0x00, 0x1b, 0x12, 0x2d, 0x24, 0x3f, 0x36,
    0x58, 0x51, 0x4a, 0x43, 0x7c, 0x75, 0x6e, 0x67,
    0x10, 0x19, 0x02, 0x0b, 0x34, 0x3d, 0x26, 0x2f,
    0x73, 0x7a, 0x61, 0x68, 0x57, 0x5e, 0x45, 0x4c,
    0x3b, 0x32, 0x29, 0x20, 0x1f, 0x16, 0x0d, 0x04,
    0x6a, 0x63, 0x78, 0x71, 0x4e, 0x47, 0x5c, 0x55,
    0x22, 0x2b, 0x30, 0x39, 0x06, 0x0f, 0x14, 0x1d,
    0x25, 0x2c, 0x37, 0x3e, 0x01, 0x08, 0x13, 0x1a,
    0x6d, 0x64, 0x7f, 0x76, 0x49, 0x40, 0x5b, 0x52,
    0x3c, 0x35, 0x2e, 0x27, 0x18, 0x11, 0x0a, 0x03,
    0x74, 0x7d, 0x66, 0x6f, 0x50, 0x59, 0x42, 0x4b,
    0x17, 0x1e, 0x05, 0x0c, 0x33, 0x3a, 0x21, 0x28,
    0x5f, 0x56, 0x4d, 0x44, 0x7b, 0x72, 0x69, 0x60,
    0x0e, 0x07, 0x1c, 0x15, 0x2a, 0x23, 0x38, 0x31,
    0x46, 0x4f, 0x54, 0x5d, 0x62, 0x6b, 0x70, 0x79
};

/**
 * @brief Initialize bus interface
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t wifi8_init_communication(wifi8_t *ctx);

/**
 * @brief First part of @ref wifi8_init_drv.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t wifi8_hold(wifi8_t *ctx);

/**
 * @brief Second part of @ref wifi8_init_drv.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t wifi8_start(wifi8_t *ctx);

/**
 * @brief Convert hexchar to value 0-15.
 * @param[in] ch : hexchar
 * @return value
 */
static uint8_t hexchar_2_val(uint8_t ch);

/**
 * @brief Convert hexstring to bytes.
 * @param[in] pu8_out : Output data.
 * @param[in] pu8_in : Input data.
 * @param[in] u8_size_out : Input data len.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t hexstr_2_bytes(uint8_t *pu8_out, uint8_t *pu8_in, uint8_t u8_size_out);

/**
 * @brief Convert data to crc.
 * @param[in] crc : Current CRC val.
 * @param[in] data_val : Data value.
 * @return CRC
 */
static uint8_t crc7_byte(uint8_t crc, uint8_t data_val);

/**
 * @brief Convert data to crc.
 * @param[in] crc : Current CRC val.
 * @param[in] buffer : Data buffer.
 * @param[in] len : Buffer len.
 * @return CRC
 */
static uint8_t crc7(uint8_t crc, uint8_t *buffer, uint32_t len);

/**
 * @brief Initialize the SPI.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t nm_spi_init(wifi8_t *ctx);

/**
 * @brief Send CMD.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] cmd : Write command.
 * @param[in] adr : Register address.
 * @param[in] data_in :Data to write.
 * @param[in] sz DMA data.
 * @param[in] clockless :Buffer size.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t spi_cmd(wifi8_t *ctx, uint8_t cmd, uint32_t adr, uint32_t data_in, uint32_t sz, uint8_t clockless);

/**
 * @brief Check send CMD.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] cmd : Write command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t spi_cmd_rsp(wifi8_t *ctx, uint8_t cmd);

/**
 * @brief Read data.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[out] b : Buffer.
 * @param[in] sz :Buffer size.
 * @param[in] clockless : Clockless command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t spi_data_read(wifi8_t *ctx, uint8_t *b, uint16_t sz, uint8_t clockless);

/**
 * @brief Write data.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] b : Buffer.
 * @param[in] sz :Buffer size.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t spi_data_write(wifi8_t *ctx, uint8_t *b, uint16_t sz);

/**
 * @brief Wait to boot rom.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] arg : Mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t wait_for_bootrom(wifi8_t *ctx, uint8_t arg);

/**
 * @brief Wait for firmware to start.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] arg : Mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t wait_for_firmware_start(wifi8_t *ctx, uint8_t arg);

/**
 * @brief Return power save to default value.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return Nothing.
 */
static void chip_idle(wifi8_t *ctx);

/**
 * @brief To Wakeup the chip.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t chip_wake(wifi8_t *ctx);

/**
 * @brief To make the chip sleep.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t chip_sleep(wifi8_t *ctx);

/**
 * @brief To enable interrupts.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t enable_interrupts(wifi8_t *ctx);

/**
 * @brief Start CPU from the device module
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t cpu_start(wifi8_t *ctx);

/**
 * @brief Write block of data.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] u32_addr : Start address.
 * @param[in] pu_buf : Pointer to the buffer holding the data to be written.
 * @param[in] u32_sz : Number of bytes to write. The buffer size must be >= u32Sz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t nm_write_block(wifi8_t *ctx, uint32_t u32_addr, uint8_t *pu_buf, uint32_t u32_sz);

/**
 * @brief Read block of data.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] u32_addr : Start address.
 * @param[in] pu_buf : Pointer to a buffer used to return the read data.
 * @param[in] u32_sz : Number of bytes to read. The buffer size must be >= u32Sz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t nm_read_block(wifi8_t *ctx, uint32_t u32_addr, uint8_t *pu_buf, uint32_t u32_sz);

/**
 * @brief To initialize HIF layer.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t hif_init(wifi8_t *ctx);

/**
 * @brief To check the compatibility of an image with the current driver.
 * @param[in] u16_hif_info : HIF info of image to be checked.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t hif_check_compatibility(uint16_t u16_hif_info);

/**
 * @brief To enable access to HIF layer, based on HIF level of Firmware.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t hif_enable_access(wifi8_t *ctx);

/**
 * @brief To check that a particular hif message is supported with the current driver/firmware pair.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] u8_gid : Group ID.
 * @param[in] u8_op_code : Operation ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t hif_check_code(wifi8_t *ctx, uint8_t u8_gid, uint8_t u8_op_code);

/**
 * @brief Send packet using host interface.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] u8_gid : Group ID.
 * @param[in] u8_opcode : Operation ID.
 * @param[in] pu8_ctrl_buf : Pointer to the Control buffer.
 * @param[in] u16_ctrl_buf_size : Control buffer size.
 * @param[in] pu8_data_buf : Packet Data offset.
 * @param[in] u16_data_size : Packet buffer Allocated by the caller.
 * @param[in] u16_data_offset : Packet buffer size (including the HIF header).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t hif_send(wifi8_t *ctx, uint8_t u8_gid, uint8_t u8_opcode, uint8_t *pu8_ctrl_buf, uint16_t u16_ctrl_buf_size,
                      uint8_t *pu8_data_buf, uint16_t u16_data_size, uint16_t u16_data_offset);

/**
 * @brief To set Callback function for every component.
 * @param[in] u8_grp : Group to which the Callback function should be set.
 * @param[in] fn : Function to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t hif_register_cb(uint8_t u8_grp, wifi8_hif_call_back_t fn);

/**
 * @brief Host interface interrupt service routine
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] u32_addr : Receive start address.
 * @param[in] pu8_buf : Pointer to receive buffer. Allocated by the caller.
 * @param[in] u16_sz : Receive buffer size.
 * @param[in] is_done : If you don't need any more packets send True otherwise send false.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t hif_receive(wifi8_t *ctx, uint32_t u32_addr, uint8_t *pu8_buf, uint16_t u16_sz, uint8_t is_done);

/**
 * @brief Set RX done.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t hif_set_rx_done(wifi8_t *ctx);

/**
 * @brief Get Hif info of images in both partitions (Firmware and Ota).
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] pu16_fw_hif_info : Pointer holding Hif info of image in the active partition.
 * @param[in] pu16_ota_hif_info : Pointer holding Hif info of image in the inactive partition.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t nm_get_hif_info(wifi8_t *ctx, uint16_t *pu16_fw_hif_info, uint16_t *pu16_ota_hif_info);

/**
 * @brief WiFi call back function
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] u8_op_code : HIF Opcode type.
 * @param[in] u16_data_size : HIF data length.
 * @param[in] u32_addr : HIF address.
 * @return Nothing.
 */
static void m2m_wifi_cb(wifi8_t *ctx, uint8_t u8_op_code, uint16_t u16_data_size, uint32_t u32_addr);

/**
 * @brief Asynchronous API that notifies the device with the Gain Table 
 * index from Flash that should use to configure the WiFi and BLE gains.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] table_idx : Index.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t m2m_wifi_ble_set_gain_table(wifi8_t *ctx, uint8_t table_idx);

/**
 * @brief Asynchronous API to enable access point (AKA "hot-spot") mode on the device.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] pstr_m2map_config : A structure holding the AP configurations.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t m2m_wifi_enable_ap(wifi8_t *ctx, wifi8_m2m_ap_config_t *pstr_m2map_config);

/**
 * @brief Asynchronous API to enable access point 
 * (AKA "hot-spot") mode on the device with extended options.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] pstr_m2map_mode_config : A structure holding the AP configurations.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t m2m_wifi_enable_ap_ext(wifi8_t *ctx, wifi8_m2m_ap_mode_config_t *pstr_m2map_mode_config);

/**
 * @brief Validate AP parameters.
 * @param[in] pstr_m2map_mode_config : A structure holding the AP configurations.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t m2m_validate_ap_parameters(wifi8_m2m_ap_mode_config_t *pstr_m2map_mode_config);

/**
 * @brief Get the wifi state.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return The function returns the current wifi state.
 */
uint8_t m2m_wifi_get_state(wifi8_t *ctx);

/**
 * @brief This function is responsible for handling interrupts received from the device firmware.
 * Applications should call this function periodically in-order to receive the events that are to
 * be handled by the callback functions implemented by the application.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t m2m_wifi_handle_events(wifi8_t *ctx);

/**
 * @brief API to set (write) options relating to Wi-Fi connection using WPA(2) Enterprise authentication.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] enu_option_name : The option to set.
 * @param[in] p_option_value : Pointer to a buffer containing 
 * the value to set. The buffer must be at least as long as OptionLen.
 * If OptionLen is 0, then pOptionValue may be NULL.
 * @param[in] option_len : The length of the option value being set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t m2m_wifi_1x_set_option(wifi8_t *ctx, wifi8_1x_option_t enu_option_name, void *p_option_value, size_t option_len);

/**
 * @brief Asynchronous API to connect to an access point using 
 * WPA(2) Enterprise authentication with MS-CHAP-V2 credentials.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] enu_cred_store_option : Option to specify whether connection details 
 * (i.e. the contents of pstrNetworkId and pstrAuth1xMschap2) are stored in device
 * flash and, if so, whether they are encrypted before storing.
 * @param[in] pstr_network_id : Structure specifying SSID/BSSID and Wi-Fi channel.
 * @param[in] pstr_auth1x_mschap2 : Structure specifying the MS-CHAP-V2 credentials.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t 
m2m_wifi_connect_1x_mschap2
(wifi8_t *ctx, wifi8_cred_store_option_t enu_cred_store_option, 
 wifi8_network_id_t *pstr_network_id, wifi8_auth1x_mschap2_t *pstr_auth1x_mschap2);

/**
 * @brief Callback function used by the NMC1000 driver to deliver messages for socket layer.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] u8_op_code : HIF Opcode type.
 * @param[in] u16_buffer_size : HIF data length.
 * @param[in] u32_address : HIF address.
 * @return Nothing.
 */
static void m2m_ip_cb(wifi8_t *ctx, uint8_t u8_op_code, uint16_t u16_buffer_size, uint32_t u32_address);

/**
 * @brief Asynchronous API to request the information of an access point discovered via scanning.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] index : Index for the requested result, 
 * the index range start from 0 till number of AP's found.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t m2m_wifi_req_scan_result(wifi8_t *ctx, uint8_t index);

/**
 * @brief Asynchronous API to request the device to scan for networks.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] ch : RF Channel ID for SCAN operation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t m2m_wifi_request_scan(wifi8_t *ctx, uint8_t ch);

/**
 * @brief Callback function used by the NMC1500 driver to deliver messages for socket layer.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] sock : Socket number.
 * @param[in] pstr_recv : Socket data.
 * @param[in] u8_socket_msg : Socket message.
 * @param[in] u32_start_address : Start address.
 * @param[in] u16_read_count : Data length.
 * @return Nothing.
 */
static void 
socket_read_socket_data
(wifi8_t *ctx, int8_t sock, wifi8_socket_recv_msg_t *pstr_recv, uint8_t u8_socket_msg,
 uint32_t u32_start_address, uint16_t u16_read_count);

/**
 * @brief Asynchronous API to connect to an access point using open authentication.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] enu_cred_store_option : Option to specify whether connection 
 * details (i.e. the contents of pstrNetworkId) are stored in device flash and, 
 * if so, whether they are encrypted before storing.
 * @param[in] pstr_network_id : Structure specifying SSID/BSSID and Wi-Fi channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t 
m2m_wifi_connect_open
(wifi8_t *ctx, wifi8_cred_store_option_t enu_cred_store_option, wifi8_network_id_t *pstr_network_id);

/**
 * @brief Asynchronous API to request connection to a specific AP 
 * with the option to save credentials in Flash.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] pc_ssid : A buffer holding the SSID corresponding to the 
 * requested AP. SSID must not contain '\0'.
 * @param[in] u8_ssid_len : Length of the given SSID (not including any NULL termination).
 * @param[in] u8_sec_type : Wi-Fi security type security 
 * for the network (see @ref wifi8_m2m_sec_type_t).
 * @param[in] pv_auth_info : Authentication parameters required for completing 
 * the connection. Its type is based on the security type.
 * @param[in] u16_ch : Wi-Fi channel number as defined in @ref wifi8_m2m_scan_ch_t enumeration.
 * @param[in] u8_no_save_cred : Option to store the access point SSID and password 
 * into the device flash memory or not.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t m2m_wifi_connect_sc(wifi8_t *ctx, uint8_t *pc_ssid, uint8_t u8_ssid_len, wifi8_m2m_sec_type_t u8_sec_type,
                                 void *pv_auth_info, wifi8_m2m_scan_ch_t u16_ch, uint16_t u8_no_save_cred);

/**
 * @brief Validates connection parameters.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] pstr_conn_hdr : Structure to sent across the HIF along with the relevant auth details.
 * @param[in] pstr_connect : Structure to sent across the HIF along with the relevant auth details.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t 
legacy_connect_prepare_msg
(wifi8_m2m_wifi_conn_hdr_t *pstr_conn_hdr, wifi8_m2m_wifi_connect_legacy_1_2_t *pstr_connect);

/**
 * @brief Validates connection parameters.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] enu_cred_store_option : Structure to sent across the HIF along with the relevant auth details.
 * @param[in] enu_auth_type : Structure to sent across the HIF along with the relevant auth details.
 * @param[in] u16_auth_size : Structure to sent across the HIF along with the relevant auth details.
 * @param[in] pstr_network_id : Structure to sent across the HIF along with the relevant auth details.
 * @param[in] pstr_wifi_conn : Structure to sent across the HIF along with the relevant auth details.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t 
m2m_wifi_connect_prepare_msg
(wifi8_cred_store_option_t enu_cred_store_option, wifi8_m2m_sec_type_t enu_auth_type,
 uint16_t u16_auth_size, wifi8_network_id_t *pstr_network_id, wifi8_m2m_wifi_conn_hdr_t *pstr_wifi_conn);

/**
 * @brief Request the current MAC address of the device (the working mac address).
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[out] pu8_mac_addr : Output MAC address buffer of 6 bytes size.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t nmi_get_mac_address(wifi8_t *ctx, uint8_t *pu8_mac_addr);

/**
 * @brief Asynchronous API for control of Wi-Fi provisioning functionality.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] pstr_m2map_config : AP configuration parameters as 
 * defined in @ref wifi8_m2m_ap_config_t configuration structure.
 * @param[in] pc_http_server_domain_name : Domain name of the HTTP Provision 
 * WEB server which others will use to load the provisioning Home page.
 * @param[in] b_enable_http_redirect :  A flag to enable/disable the HTTP redirect feature.
 * If Secure provisioning is enabled (i.e. the server  domain name uses 
 * "https" prefix) this flag is ignored (no meaning for redirect in HTTPS).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t 
m2m_wifi_start_provision_mode
(wifi8_t *ctx, wifi8_m2m_ap_config_t *pstr_m2map_config, 
 char *pc_http_server_domain_name, uint8_t b_enable_http_redirect);

/**
 * @brief Asynchronous API for control of Wi-Fi provisioning functionality with extended options.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] pstr_ap_mode_config : AP configuration parameters as defined in 
 * @ref wifi8_m2m_ap_config_t configuration structure.
 * @param[in] pc_http_server_domain_name : Domain name of the HTTP Provision 
 * WEB server which others will use to load the provisioning Home page.
 * @param[in] b_enable_http_redirect :  A flag to enable/disable the HTTP redirect feature.
 * If Secure provisioning is enabled (i.e. the server  domain name uses 
 * "https" prefix) this flag is ignored (no meaning for redirect in HTTPS).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t 
m2m_wifi_start_provision_mode_ext
(wifi8_t *ctx, wifi8_m2m_ap_mode_config_t *pstr_ap_mode_config, 
 char *pc_http_server_domain_name, uint8_t b_enable_http_redirect);

/**
 * @brief Synchronous API to retrieve the MAC address currently in use by the device.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[out] pu8_mac_addr : Pointer to a buffer in memory containing a 6-byte MAC address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t m2m_wifi_get_mac_address(wifi8_t *ctx, uint8_t *pu8_mac_addr);

/**
 * @brief Asynchronous API to connect to an access point using WPA(2) PSK authentication.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] enu_cred_store_option : Option to specify whether connection details 
 * (i.e. the contents of pstrNetworkId and pstrAuthPsk) are stored in device flash 
 * and, if so, whether they are encrypted before storing.
 * @param[in] pstr_network_id : Structure specifying SSID/BSSID and Wi-Fi channel.
 * @param[in] pstr_auth_psk : Structure specifying the Passphrase/PSK.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t 
m2m_wifi_connect_psk
(wifi8_t *ctx, wifi8_cred_store_option_t enu_cred_store_option, 
 wifi8_network_id_t *pstr_network_id, wifi8_auth_psk_t *pstr_auth_psk);

/**
 * @brief Asynchronous API to connect to an access point using WEP authentication.
 * @param[in] ctx : Click context object.
 * See #wifi8_t object definition for detailed explanation.
 * @param[in] enu_cred_store_option : Option to specify whether connection details 
 * (i.e. the contents of pstrNetworkId and pstrAuthPsk) are stored in device flash 
 * and, if so, whether they are encrypted before storing.
 * @param[in] pstr_network_id : Structure specifying SSID/BSSID and Wi-Fi channel.
 * @param[in] pstr_auth_wep : Structure specifying the WEP key.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t 
m2m_wifi_connect_wep
(wifi8_t *ctx,  wifi8_cred_store_option_t enu_cred_store_option, 
 wifi8_network_id_t *pstr_network_id, wifi8_auth_wep_t *pstr_auth_wep);

void wifi8_cfg_setup(wifi8_cfg_t *cfg)
{
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->wkp = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 1000000;
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t wifi8_init(wifi8_t *ctx, wifi8_cfg_t *cfg)
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
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

    digital_out_init(&ctx->en, cfg->en);
    digital_out_init(&ctx->rst, cfg->rst);
    digital_out_init(&ctx->wkp, cfg->wkp);
    digital_in_init(&ctx->int_pin, cfg->int_pin);
    
    ctx->hif_bl_offset = 0;
    ctx->device_state = NM_STATE_DEINIT;
    ctx->ch_num = 0;
    ctx->hs_flags = WIFI_1X_TLS_HS_FLAGS_DEFAULT;
    memset( ctx->sockets, 0 , MAX_SOCKET );
    memset( ctx->root_sha1, 0 , 20 );
    ctx->session_id = 0;
    ctx->socket_init = 0;
    ctx->ping_id = 0;
    ctx->app_wifi_cb = NULL;
    ctx->app_socket_cb = NULL;
    ctx->app_resolve_cb = NULL;
    ctx->ping_cb = NULL;

    return SPI_MASTER_SUCCESS;
}

err_t wifi8_default_cfg(wifi8_t *ctx)
{
    digital_out_high(&ctx->en);
    digital_out_low(&ctx->rst);
    Delay_100ms();
    digital_out_high(&ctx->rst);
    Delay_100ms();

    return wifi8_init_drv(ctx);
}

err_t wifi8_generic_write(wifi8_t *ctx, uint8_t *data_in, uint8_t len)
{
    spi_master_select_device(ctx->chip_select);
    Delay_10us ( );
    err_t error_flag = spi_master_write(&ctx->spi, data_in, len);
    spi_master_deselect_device(ctx->chip_select);

    return error_flag;
}

err_t wifi8_generic_read(wifi8_t *ctx, uint8_t *data_out, uint8_t len)
{
    spi_master_select_device(ctx->chip_select);
    Delay_10us ( );
    err_t error_flag = spi_master_read(&ctx->spi, data_out, len);
    spi_master_deselect_device(ctx->chip_select);

    return error_flag;
}

err_t wifi8_reg_write(wifi8_t *ctx, uint32_t addr, uint32_t data_in)
{
    err_t result = WIFI8_OK;
    uint8_t cmd = WIFI8_CMD_SINGLE_WRITE;
    uint8_t clockless = 0;
        
    if (addr <= 0x30)
    {
        cmd = WIFI8_CMD_INTERNAL_WRITE;
        clockless = 1;
    }
    
    for ( uint8_t retry = SPI_RETRY_COUNT; retry != 0; retry-- )
    {
        if (result != WIFI8_OK)
        {
            Delay_1ms();
            spi_cmd(ctx, WIFI8_CMD_RESET, 0, 0, 0, 0);
            spi_cmd_rsp(ctx, WIFI8_CMD_RESET);
            Delay_1ms();
        }

        result = spi_cmd(ctx, cmd, addr, data_in, 4, clockless);
        if (result != WIFI8_OK)
        {
            continue;
        }

        result = spi_cmd_rsp(ctx, cmd);
        if (result == WIFI8_OK)
        {
            break;
        }
    }
    
    return result;
}

err_t wifi8_reg_read(wifi8_t *ctx, uint32_t addr, uint32_t *data_out)
{
    err_t result = WIFI8_OK;
    uint8_t cmd = WIFI8_CMD_SINGLE_READ;
    uint8_t tmp[4];
    uint8_t clockless = 0;

    if (addr <= 0xff)
    {
        cmd = WIFI8_CMD_INTERNAL_READ;
        clockless = 1;
    }

    for ( uint8_t retry = SPI_RETRY_COUNT; retry != 0; retry-- )
    {
        if(result != WIFI8_OK)
        {
            Delay_1ms( );
            spi_cmd(ctx, WIFI8_CMD_RESET, 0, 0, 0, 0);
            spi_cmd_rsp(ctx, WIFI8_CMD_RESET);
            Delay_1ms( );
        }
        result = spi_cmd(ctx, cmd, addr, 0, 4, clockless);
        if (result != WIFI8_OK)
        {
            continue;
        }
        result = spi_cmd_rsp(ctx, cmd);
        if (result != WIFI8_OK)
        {
            continue;
        }
        result = spi_data_read(ctx, tmp, 4, clockless);
        if ( result != WIFI8_OK)
        {
            continue;
        }

        *data_out = tmp[0] |
                    ((uint32_t)tmp[1] << 8) |
                    ((uint32_t)tmp[2] << 16) |
                    ((uint32_t)tmp[3] << 24);

        if (result == WIFI8_OK)
        {
            break;
        }
    }

    return result;
}

err_t wifi8_block_read(wifi8_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_len)
{
    uint8_t cmd = WIFI8_CMD_DMA_EXT_READ;
    err_t result = WIFI8_OK;
    uint8_t tmp[2];
    uint8_t single_byte_workaround = 0;

    /**
        Command
    **/
    if(buf_len == 1)
    {
        //Workaround hardware problem with single byte transfers over SPI bus
        buf_len = 2;
        single_byte_workaround = 1;
    }
    
    for ( uint8_t retry = SPI_RETRY_COUNT; retry != 0; retry-- )
    {
        if(result != WIFI8_OK)
        {
            Delay_1ms();
            spi_cmd(ctx, WIFI8_CMD_RESET, 0, 0, 0, 0);
            spi_cmd_rsp(ctx, WIFI8_CMD_RESET);
            Delay_1ms();
            retry--;
        }
        
        result = spi_cmd(ctx, cmd, addr, 0, buf_len, 0);
        if(result != WIFI8_OK) 
        {
            continue;
        }

        result = spi_cmd_rsp(ctx, cmd);
        if(result != WIFI8_OK)
        {
            continue;
        }

        /**
            Data
        **/
        if(single_byte_workaround)
        {
            result = spi_data_read(ctx, tmp, buf_len, 0);
            data_buf[0] = tmp[0];
        }
        else
        {
            result = spi_data_read(ctx, data_buf, buf_len, 0);
        }

        if(result == WIFI8_OK)
        {
            break;
        }
    }

    return result;
}

err_t wifi8_block_write(wifi8_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_len)
{
    err_t result;
    uint8_t cmd = WIFI8_CMD_DMA_EXT_WRITE;
    
    /**
        Command
    **/
    if (buf_len == 1)
    {
        buf_len = 2;
    }

    for ( uint8_t retry = SPI_RETRY_COUNT; retry != 0; retry-- )
    {
        if (result != WIFI8_OK)
        {
            Delay_1ms();
            spi_cmd(ctx, WIFI8_CMD_RESET, 0, 0, 0, 0);
            spi_cmd_rsp(ctx, WIFI8_CMD_RESET);
            Delay_1ms();
        }
        
        result = spi_cmd(ctx, cmd, addr, 0, buf_len, 0);
        if (result != WIFI8_OK)
        {
            continue;
        }

        result = spi_cmd_rsp(ctx, cmd);
        if (result != WIFI8_OK)
        {
            continue;
        }

        /**
            Data
        **/
        result = spi_data_write(ctx, data_buf, buf_len);
        if (result == WIFI8_OK)
        {
            break;
        }
    }

    return result;
}

err_t wifi8_init_drv(wifi8_t *ctx)
{
    if (WIFI8_OK != wifi8_hold(ctx))
    {
        return WIFI8_ERROR;
    }
    else
    {
        
        return wifi8_start(ctx);
    }
}

uint32_t wifi8_chip_id(wifi8_t *ctx)
{
    static uint32_t chipid = 0;

    if (chipid == 0)
    {
        uint32_t rfrevid;

        if (WIFI8_OK != wifi8_reg_read(ctx, 0x1000, &chipid))
        {
            return 0;
        }

        if (WIFI8_OK != wifi8_reg_read(ctx, 0x13f4, &rfrevid))
        {
            return 0;
        }

        if (chipid == 0x1002a0ul)
        {
            if (rfrevid != 0x1)
            {
                chipid = 0x1002a1ul;
            }
        }
        else if (chipid == 0x1002b0ul)
        {
            if (rfrevid == 3)
            {
            }
            else if (rfrevid == 4)
            {
                chipid = 0x1002b1ul;
            }
            else
            {
                chipid = 0x1002b2ul;
            }
        }
        else if (chipid == 0x1000f0ul)
        {
            if (WIFI8_OK != wifi8_reg_read(ctx, 0x3b0000ul, &chipid))
            {
                return 0;
            }

            if (chipid == 0x3000d0ul)
            {
                if (rfrevid == 6)
                {
                    chipid = 0x3000d1ul;
                }
                else if (rfrevid == 2)
                {
                    chipid = 0x3000d2ul;
                }
            }
        }

        if ((chipid & 0xf00000ul) == 0x300000ul)
        {
            chipid &= ~(0x0f0000ul);
            chipid |= 0x040000ul;
        }
        else
        {
            chipid &= ~(0x0f0000ul);
            chipid |= 0x050000ul;
        }
    }

    return chipid;
}

err_t wifi8_get_full_firmware_version(wifi8_t *ctx, wifi8_m2m_rev_t *fw_version)
{
    if (WIFI8_OK == chip_wake(ctx))
    {
        uint16_t fw_hif_info = 0;
        uint32_t reg = 0;
        wifi8_gp_regs_t strgp = {0};

        memset((uint8_t *)fw_version, 0, sizeof(wifi8_m2m_rev_t));

        if (WIFI8_OK != nm_get_hif_info(ctx, &fw_hif_info, NULL))
        {
            return WIFI8_ERROR;
        }

        if (M2M_GET_HIF_BLOCK(fw_hif_info) == M2M_HIF_BLOCK_VALUE)
        {
            if (WIFI8_OK != wifi8_reg_read(ctx, rNMI_GP_REG_0, &reg))
            {
                return WIFI8_ERROR;
            }
            if (reg == 0)
            {
                return WIFI8_ERROR;
            }
            if (WIFI8_OK != wifi8_block_read(ctx, reg | 0x30000ul, (uint8_t *)&strgp, sizeof(wifi8_gp_regs_t)))
            {
                return WIFI8_ERROR;
            }
            reg = strgp.u32_firmware_ota_rev;
            reg &= 0x0000fffful;
            if (reg == 0)
            {
                return WIFI8_ERROR;
            }
            if (WIFI8_OK != wifi8_block_read(ctx, reg | 0x30000ul, (uint8_t *)fw_version, sizeof(wifi8_m2m_rev_t)))
            {
                return WIFI8_ERROR;
            }
            if (fw_hif_info != fw_version->u16_firmware_hif_info)
            {
                return WIFI8_ERROR;
            }
        }
        else
        {
            chip_sleep(ctx);
            return WIFI8_ERROR;
        }
        chip_sleep(ctx);
    }
    else
        return WIFI8_ERROR;

    return WIFI8_OK;
}

err_t wifi8_get_ota_firmware_version(wifi8_t *ctx, wifi8_m2m_rev_t *fw_version)
{
    if (WIFI8_OK == chip_wake(ctx))
    {
        uint16_t ota_hif_info = 0;
        uint32_t reg = 0;
        wifi8_gp_regs_t strgp = {0};

        memset((uint8_t *)fw_version, 0, sizeof(wifi8_m2m_rev_t));

        if (WIFI8_OK != nm_get_hif_info(ctx, NULL, &ota_hif_info))
        {
            return WIFI8_ERROR;
        }

        if (M2M_GET_HIF_BLOCK(ota_hif_info) == M2M_HIF_BLOCK_VALUE)
        {
            if (WIFI8_OK != wifi8_reg_read(ctx, rNMI_GP_REG_0, &reg))
            {
                return WIFI8_ERROR;
            }
            if (reg == 0)
            {
                return WIFI8_ERROR;
            }
            if (WIFI8_OK != wifi8_block_read(ctx, reg | 0x30000ul, (uint8_t *)&strgp, sizeof(wifi8_gp_regs_t)))
            {
                return WIFI8_ERROR;
            }
            reg = strgp.u32_firmware_ota_rev;
            reg >>= 16;
            if (reg == 0)
            {
                return WIFI8_ERROR;
            }
            if (WIFI8_OK != wifi8_block_read(ctx, reg | 0x30000ul, (uint8_t *)fw_version, sizeof(wifi8_m2m_rev_t)))
            {
                return WIFI8_ERROR;
            }
            if (ota_hif_info != fw_version->u16_firmware_hif_info)
            {
                return WIFI8_ERROR;
            }
        }
        else
        {
            chip_sleep(ctx);
            return WIFI8_ERROR;
        }
        chip_sleep(ctx);
    }
    else
    {
        return WIFI8_ERROR;
    }

    return WIFI8_OK;
}

err_t wifi8_start_ap(wifi8_t *ctx, wifi8_m2m_ap_config_t *pstr_m2m_ap_config)
{
    return m2m_wifi_enable_ap(ctx, pstr_m2m_ap_config);
}

err_t wifi8_req_scan_result(wifi8_t *ctx, uint8_t scan_index)
{
    return m2m_wifi_req_scan_result(ctx, scan_index);
}

err_t wifi8_request_scan(wifi8_t *ctx, uint8_t channel)
{
    return m2m_wifi_request_scan(ctx, channel);
}

err_t wifi8_handle_events(wifi8_t *ctx)
{
    return m2m_wifi_handle_events(ctx);
}

err_t wifi8_ble_api_send(wifi8_t *ctx, uint8_t *msg,  uint32_t len)
{
    wifi8_m2m_ble_api_msg_t ble_tx;
    ble_tx.u16_len = len;
    return hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_BLE_API_SEND | M2M_REQ_DATA_PKT,
                    (uint8_t *)&ble_tx, sizeof(wifi8_m2m_ble_api_msg_t), msg, len, sizeof(wifi8_m2m_ble_api_msg_t));
}

void wifi8_socket_init(wifi8_t *ctx)
{
    if (ctx->socket_init == 0)
    {
        memset((uint8_t *)ctx->sockets, 0,  ( (7) + 4 + 1 )  * sizeof(wifi8_socket_t));
        hif_register_cb(M2M_REQ_GROUP_IP, m2m_ip_cb);
        ctx->socket_init = 1;
        ctx->session_id = 0;
    }
}

err_t wifi8_socket_create(wifi8_t *ctx, uint16_t u16_domain, uint8_t u8_type, uint8_t u8_flags)
{
    int8_t sock = -1;
    uint8_t u8_sock_id;
    uint8_t u8_count;
    volatile wifi8_socket_t *pstr_sock;
    static volatile uint8_t u8_next_tcp_sock = 0;
    static volatile uint8_t u8_next_udp_sock = 0;


    if (u16_domain ==  2 )
    {
        if (u8_type ==  1 )
        {
            for (u8_count = 0; u8_count <  (7) ; u8_count++)
            {
                u8_sock_id = u8_next_tcp_sock;
                pstr_sock = &ctx->sockets[u8_next_tcp_sock];
                u8_next_tcp_sock = (u8_next_tcp_sock + 1) %  (7) ;
                if (!pstr_sock->b_is_used)
                {
                    sock = (int8_t)u8_sock_id;
                    memset((uint8_t *)pstr_sock, 0, sizeof(wifi8_socket_t));

                    if (u8_flags &  0x01 )
                    {
                        wifi8_ssl_socket_create_cmd_t str_ssl_create;
                        str_ssl_create.ssl_sock = sock;
                        pstr_sock->u8ssl_flags =  (0x00000001ul) ;
                        hif_send(ctx, M2M_REQ_GROUP_IP, 0x50 , (uint8_t *)&str_ssl_create, sizeof(wifi8_ssl_socket_create_cmd_t), 0, 0, 0) ;
                    }
                    break;
                }
            }
        }
        else if (u8_type ==  2 )
        {
            volatile wifi8_socket_t *pastr_udp_sockets = &ctx->sockets[ (7) ];
            for (u8_count = 0; u8_count <  4 ; u8_count++)
            {
                u8_sock_id = u8_next_udp_sock;
                pstr_sock = &pastr_udp_sockets[u8_next_udp_sock];
                u8_next_udp_sock = (u8_next_udp_sock + 1) %  4 ;
                if (!pstr_sock->b_is_used)
                {
                    sock = (int8_t)(u8_sock_id +  (7) );
                    memset((uint8_t *)pstr_sock, 0, sizeof(wifi8_socket_t));
                    break;
                }
            }
        }
        else if (u8_type ==  3 )
        {

            if (u8_flags &  0x02 )
            {
                pstr_sock = &ctx->sockets[ ( (7) + 4 ) ];
                if (!pstr_sock->b_is_used)
                {

                    sock = (int8_t) ( (7) + 4 ) ;
                    memset((uint8_t *)pstr_sock, 0, sizeof(wifi8_socket_t));
                }
            }
        }

        if (sock >= 0)
        {
            pstr_sock->b_is_used = 1;
            ++ctx->session_id;
            if (ctx->session_id == 0)
                ++ctx->session_id;

            pstr_sock->u16_session_id = ctx->session_id;
        }
    }
    return sock;
}

err_t wifi8_socket_bind(wifi8_t *ctx, int8_t sock, wifi8_sockaddr_t *pstr_addr, uint8_t u8_addr_len)
{
    if ((pstr_addr !=  ((void *)0) ) && (sock >= 0) && (ctx->sockets[sock].b_is_used == 1) && (u8_addr_len != 0))
    {
        wifi8_bind_cmd_t str_bind;

        str_bind.sock = sock;
        memcpy((uint8_t *)&str_bind.str_addr, (uint8_t *)pstr_addr, sizeof(wifi8_sock_addr_t));

        str_bind.str_addr.u16_family = str_bind.str_addr.u16_family;
        str_bind.str_addr.u16_port = str_bind.str_addr.u16_port;
        str_bind.str_addr.u32ip_addr = str_bind.str_addr.u32ip_addr;
        str_bind.u16_session_id = ctx->sockets[sock].u16_session_id;


        return  hif_send(ctx, M2M_REQ_GROUP_IP, 0x41 , (uint8_t *)&str_bind, sizeof(wifi8_bind_cmd_t), ((void *)0) , 0, 0) ;
    }
    return WIFI8_ERROR;
}

int8_t wifi8_socket_listen(wifi8_t *ctx, int8_t sock, uint8_t backlog)
{
    if (sock >= 0 && (ctx->sockets[sock].b_is_used == 1))
    {
        wifi8_listen_cmd_t str_listen;

        str_listen.sock = sock;
        str_listen.u8_back_log = backlog;
        str_listen.u16_session_id = ctx->sockets[sock].u16_session_id;

        return SOCKET_REQUEST(ctx, SOCKET_CMD_LISTEN, (uint8_t *)&str_listen, sizeof(wifi8_listen_cmd_t), NULL, 0, 0);
    }
    return WIFI8_OK;
}

err_t wifi8_socket_connect(wifi8_t *ctx, int8_t sock, wifi8_sockaddr_t *pstr_addr, uint8_t u8_addr_len)
{
    if ((sock >= 0) && (pstr_addr != NULL) && (ctx->sockets[sock].b_is_used == 1) && (u8_addr_len != 0))
    {
        wifi8_connect_cmd_t str_connect;
        uint8_t u8_cmd = SOCKET_CMD_CONNECT;
        if ((ctx->sockets[sock].u8ssl_flags) & SSL_FLAGS_ACTIVE)
        {
            u8_cmd = SOCKET_CMD_SSL_CONNECT;
            str_connect.u8_ssl_flags = ctx->sockets[sock].u8ssl_flags;
        }
        str_connect.sock = sock;
        memcpy((uint8_t *)&str_connect.str_addr, (uint8_t *)pstr_addr, sizeof(wifi8_sock_addr_t));

        str_connect.u16_session_id = ctx->sockets[sock].u16_session_id;
        return SOCKET_REQUEST(ctx, u8_cmd, (uint8_t *)&str_connect, sizeof(wifi8_connect_cmd_t), NULL, 0, 0);
    }
    return WIFI8_ERROR;
}

err_t wifi8_socket_send(wifi8_t *ctx, int8_t sock, void *pv_send_buffer, uint16_t u16_send_length)
{
    if ((sock >= 0) && (pv_send_buffer !=  ((void *)0) ) && (u16_send_length <=  1400 ) && (ctx->sockets[sock].b_is_used == 1))
    {
        uint16_t u16_data_offset;
        wifi8_send_cmd_t str_send;
        uint8_t u8_cmd;

        u8_cmd =  0x45 ;
        u16_data_offset =  ( ( (14) + (34) - (sizeof(wifi8_hif_hdr_t) + 4) ) + (40) ) ;

        str_send.sock = sock;
        str_send.u16_data_size =  (u16_send_length) ;
        str_send.u16_session_id = ctx->sockets[sock].u16_session_id;

        if (sock >=  (7) )
        {
            u16_data_offset =  ( ( (14) + (34) - (sizeof(wifi8_hif_hdr_t) + 4) ) + (28) ) ;
        }
        if (ctx->sockets[sock].u8ssl_flags &  (0x00000001ul) )
        {
            u8_cmd =  0x4C ;
            u16_data_offset = ctx->sockets[sock].u16_data_offset;
        }

        return  hif_send(ctx, M2M_REQ_GROUP_IP, u8_cmd | M2M_REQ_DATA_PKT, (uint8_t *)&str_send, sizeof(wifi8_send_cmd_t), pv_send_buffer, u16_send_length, u16_data_offset) ;
    }
    return WIFI8_ERROR;
}

err_t wifi8_socket_send_to(wifi8_t *ctx, int8_t sock, void *pv_send_buffer, uint16_t u16_send_length,
                           wifi8_sockaddr_t *pstr_dest_addr, uint8_t u8_addr_len)
{
    int16_t u16_max_length = (sock == RAW_SOCK_ID) ? (M2M_HIF_MAX_PACKET_SIZE - M2M_HIF_HDR_OFFSET - sizeof(wifi8_send_cmd_t)) : SOCKET_BUFFER_MAX_LENGTH;

    if ((sock >= 0) && (sock < MAX_SOCKET) && (pv_send_buffer != NULL) && (u16_send_length <= u16_max_length) && (ctx->sockets[sock].b_is_used == 1))
    {
        wifi8_send_cmd_t str_send_to;

        memset((uint8_t *)&str_send_to, 0, sizeof(wifi8_send_cmd_t));

        str_send_to.sock = sock;
        str_send_to.u16_data_size = NM_BSP_B_L_16(u16_send_length);
        str_send_to.u16_session_id = ctx->sockets[sock].u16_session_id;

        if (pstr_dest_addr != NULL)
        {
            wifi8_sockaddr_in_t *pstr_addr;
            pstr_addr = (void *)pstr_dest_addr;

            str_send_to.str_addr.u16_family = pstr_addr->sin_family;
            str_send_to.str_addr.u16_port = pstr_addr->sin_port;
            str_send_to.str_addr.u32ip_addr = pstr_addr->sin_addr.s_addr;
        }
        return SOCKET_REQUEST(ctx, SOCKET_CMD_SENDTO | M2M_REQ_DATA_PKT, (uint8_t *)&str_send_to, sizeof(wifi8_send_cmd_t),
                              pv_send_buffer, u16_send_length, (sock == RAW_SOCK_ID) ? IP_PACKET_OFFSET : UDP_TX_PACKET_OFFSET);
    }
    return WIFI8_ERROR;
}

err_t wifi8_socket_receive(wifi8_t *ctx, int8_t sock, void *pv_recv_buf, uint16_t u16_buf_len, uint32_t u32_timeoutmsec)
{
    if ((sock >= 0) && (pv_recv_buf != NULL) && (u16_buf_len != 0) && (ctx->sockets[sock].b_is_used == 1))
    {
        ctx->sockets[sock].pu8_user_buffer = (uint8_t *)pv_recv_buf;
        ctx->sockets[sock].u16_user_buffer_size = u16_buf_len;

        if (!ctx->sockets[sock].b_is_recv_pending)
        {
            wifi8_recv_cmd_t str_recv;
            uint8_t socket_cmd = SOCKET_CMD_RECV;

            ctx->sockets[sock].b_is_recv_pending = 1;
            if (ctx->sockets[sock].u8ssl_flags & SSL_FLAGS_ACTIVE)
            {
                socket_cmd = SOCKET_CMD_SSL_RECV;
            }

            /* Check the timeout value. */
            if (u32_timeoutmsec == 0)
            {
                str_recv.u32_timeoutmsec = 0xFFFFFFFFul;
            }
            else
            {
                str_recv.u32_timeoutmsec = NM_BSP_B_L_32(u32_timeoutmsec);
            }
            str_recv.sock = sock;
            str_recv.u16_session_id = ctx->sockets[sock].u16_session_id;
            str_recv.u16_buf_len = u16_buf_len;

            return SOCKET_REQUEST(ctx, socket_cmd, (uint8_t *)&str_recv, sizeof(wifi8_recv_cmd_t), NULL, 0, 0);
        }
    }
    return WIFI8_ERROR;
}

err_t wifi8_socket_receive_from(wifi8_t *ctx, int8_t sock, void *pv_recv_buf, uint16_t u16_buf_len, uint32_t u32_timeoutmsec)
{
    if ((sock >= 0) && (pv_recv_buf != NULL) && (u16_buf_len != 0) && (ctx->sockets[sock].b_is_used == 1))
    {
        if (ctx->sockets[sock].b_is_used)
        {
            ctx->sockets[sock].pu8_user_buffer = (uint8_t *)pv_recv_buf;
            ctx->sockets[sock].u16_user_buffer_size = u16_buf_len;

            if (!ctx->sockets[sock].b_is_recv_pending)
            {
                wifi8_recv_cmd_t str_recv;

                ctx->sockets[sock].b_is_recv_pending = 1;

                /* check the timeout value. */
                if (u32_timeoutmsec == 0)
                {
                    str_recv.u32_timeoutmsec = 0xFFFFFFFFul;
                }
                else
                {
                    str_recv.u32_timeoutmsec = NM_BSP_B_L_32(u32_timeoutmsec);
                }
                str_recv.sock = sock;
                str_recv.u16_session_id = ctx->sockets[sock].u16_session_id;
                str_recv.u16_buf_len = u16_buf_len;

                return SOCKET_REQUEST(ctx, SOCKET_CMD_RECVFROM, (uint8_t *)&str_recv, sizeof(wifi8_recv_cmd_t), NULL, 0, 0);
            }
        }
    }

    return WIFI8_ERROR;
}

err_t wifi8_socket_close(wifi8_t *ctx, int8_t sock)
{
    err_t s8_ret = WIFI8_OK;

    if (sock >= 0 && (ctx->sockets[sock].b_is_used == 1))
    {
        uint8_t u8_cmd = SOCKET_CMD_CLOSE;
        wifi8_close_cmd_t strclose;
        strclose.sock = sock;
        strclose.u16_session_id = ctx->sockets[sock].u16_session_id;

        if (ctx->sockets[sock].u8ssl_flags & SSL_FLAGS_ACTIVE)
        {
            u8_cmd = SOCKET_CMD_SSL_CLOSE;
        }
        s8_ret = SOCKET_REQUEST(ctx, u8_cmd, (uint8_t *)&strclose, sizeof(wifi8_close_cmd_t), NULL, 0, 0);
        if (s8_ret != WIFI8_OK)
        {
            s8_ret = WIFI8_ERROR;
        }
        memset((uint8_t *)&ctx->sockets[sock], 0, sizeof(wifi8_socket_t));
    }
    return s8_ret;
}

err_t wifi8_connect(wifi8_t *ctx, char *pc_ssid, uint8_t u8_ssid_len, wifi8_m2m_sec_type_t u8_sec_type, void *pv_auth_info, uint16_t u16_ch)
{
    return m2m_wifi_connect_sc(ctx, pc_ssid, strlen(pc_ssid), u8_sec_type, (char *)pv_auth_info, M2M_WIFI_CH_ALL, u16_ch);
}

err_t wifi8_get_connection_info(wifi8_t *ctx)
{
    return hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_GET_CONN_INFO, NULL, 0, NULL, 0, 0);
}

static err_t wifi8_init_communication(wifi8_t *ctx)
{
    uint32_t chipid;
    uint32_t reg = 0;

    gu8crc_off = 0;

    if (wifi8_reg_read(ctx, NMI_SPI_PROTOCOL_CONFIG, &reg) < 0)
    {
        /* Read failed. Try with CRC off. This might happen when module
        is removed but chip isn't reset*/
        gu8crc_off = 1;
        if (wifi8_reg_read(ctx, NMI_SPI_PROTOCOL_CONFIG, &reg) < 0)
        {
            // Read failed with both CRC on and off, something went bad
            return WIFI8_ERROR;
        }
    }
    if (gu8crc_off == 0)
    {
        reg &= ~0xc; /* disable crc checking */
        reg &= ~0x70;
        reg |= (0x5 << 4);

        if (wifi8_reg_write(ctx, NMI_SPI_PROTOCOL_CONFIG, reg) < 0)
        {
            return WIFI8_ERROR;
        }
        gu8crc_off = 1;
    }

    /**
        make sure can read back chip id correctly
    **/
    if (wifi8_reg_read(ctx, 0x1000, &chipid) < 0)
    {
        return WIFI8_ERROR;
    }

    uint32_t val32;

    /* Make sure SPI max. packet buf_len fits the defined DATA_PKT_SZ.  */
    wifi8_reg_read(ctx, 0xe800 + 0x24, &val32);
    val32 &= ~(0x7 << 4);
    switch (WIFI8_DATA_PKT_SZ)
    {
    case 256:
    {
        val32 |= (0 << 4);
        break;
    }
    case 512:
    {
        val32 |= (1 << 4);
        break;
    }
    case 1024:
    {
        val32 |= (2 << 4);
        break;
    }
    case 2048:
    {
        val32 |= (3 << 4);
        break;
    }
    case 4096:
    {
        val32 |= (4 << 4);
        break;
    }
    case 8192:
    {
        val32 |= (5 << 4);
        break;
    }
    }

    wifi8_reg_write(ctx, 0xe800 + 0x24, val32);

    return WIFI8_OK;
}

static err_t wifi8_hold(wifi8_t *ctx)
{
    uint32_t reg = 0;
    uint32_t wifi_id = 0;
    uint32_t ble_id = 0;
    uint32_t rf_rev = 0;

    if (WIFI8_OK != wifi8_init_communication(ctx))
    {
        return WIFI8_ERROR;
    }

    if ((WIFI8_OK != wifi8_reg_read(ctx, 0x1000, &wifi_id)) ||
        (WIFI8_OK != wifi8_reg_read(ctx, 0x13F4, &rf_rev)) ||
        (WIFI8_OK != wifi8_reg_read(ctx, 0x3B0000ul, &ble_id)))
    {
        return WIFI8_ERROR;
    }

    if (WIFI8_OK != wifi8_reg_read(ctx, NMI_SPI_PROTOCOL_CONFIG, &reg))
    {
        return WIFI8_ERROR;
    }

    if (WIFI8_OK != nm_spi_init(ctx))
    {
        return WIFI8_ERROR;
    }

    chip_idle(ctx);

    ctx->device_state = NM_STATE_INIT;

    return WIFI8_OK;
}

static err_t wifi8_start(wifi8_t *ctx)
{
    uint8_t u8mode = M2M_WIFI_MODE_NORMAL;

    wifi8_init_param_t param;

    if (WIFI8_OK != hif_init(ctx))
    {
        return WIFI8_ERROR;
    }

    hif_register_cb(M2M_REQ_GROUP_WIFI, m2m_wifi_cb);

    if (WIFI8_OK != cpu_start(ctx))
    {
        return WIFI8_ERROR;
    }

    if (WIFI8_OK != wait_for_bootrom(ctx, u8mode))
    {
        return WIFI8_ERROR;
    }

    if (WIFI8_OK != wait_for_firmware_start(ctx, u8mode))
    {
        return WIFI8_ERROR;
    }

    if (M2M_WIFI_MODE_CONFIG == u8mode)
    {
        return WIFI8_OK;
    }
    else
    {
        if (WIFI8_OK != enable_interrupts(ctx))
        {
            return WIFI8_ERROR;
        }
        ctx->device_state = NM_STATE_START;
    }

    if (WIFI8_OK == hif_enable_access(ctx))
    {
        m2m_wifi_ble_set_gain_table(ctx, param.gain_table_index);
    }

    return WIFI8_OK;
}

static uint8_t crc7_byte(uint8_t crc, uint8_t data_val)
{
    return crc7_syndrome_table[(crc << 1) ^ data_val];
}

static uint8_t crc7(uint8_t crc, uint8_t *buffer, uint32_t len)
{
    while (len--)
    {
        crc = crc7_byte(crc, *buffer++);
    }

    return crc;
}

static uint8_t hexchar_2_val(uint8_t ch)
{
    ch -= 0x30;
    if (ch <= 9)
    {
        return ch;
    }
    ch |= 0x20;
    ch -= 0x31;
    if (ch <= 5)
    {
        return ch + 10;
    }
    return 0xFF;
}

//nm_common
static err_t hexstr_2_bytes(uint8_t *pu8Out, uint8_t *pu8In, uint8_t u8SizeOut)
{
    while (u8SizeOut--)
    {
        uint8_t u8Out = hexchar_2_val(*pu8In++);
        if (u8Out > 0xF)
        {
            return WIFI8_ERROR;
        }
        *pu8Out = u8Out * 0x10;
        u8Out = hexchar_2_val(*pu8In++);
        if (u8Out > 0xF)
        {
            return WIFI8_ERROR;
        }
        *pu8Out += u8Out;
        pu8Out++;
    }
    return WIFI8_OK;
}

static err_t spi_cmd(wifi8_t *ctx, uint8_t cmd, uint32_t adr, uint32_t data_in, uint32_t sz, uint8_t clockless)
{
    uint8_t bc[9];
    uint8_t len = 5;
    err_t result = WIFI8_OK;

    bc[0] = cmd;
    switch (cmd)
    {
        case WIFI8_CMD_SINGLE_READ: /* single word (4 bytes) read */
        {
            bc[1] = (uint8_t)(adr >> 16);
            bc[2] = (uint8_t)(adr >> 8);
            bc[3] = (uint8_t)(adr);
            len = 5;
            break;
        }
        case WIFI8_CMD_INTERNAL_READ: /* internal register read */
        {
            bc[1] = (uint8_t)(adr >> 8);
            if (clockless)
                bc[1] |= (1 << 7);
            bc[2] = (uint8_t)adr;
            bc[3] = 0x00;
            len = 5;
            break;
        }
        case WIFI8_CMD_RESET: /* reset */
        {
            bc[1] = 0xff;
            bc[2] = 0xff;
            bc[3] = 0xff;
            len = 5;
            break;
        }
        case WIFI8_CMD_DMA_EXT_WRITE: /* dma extended write */
        case WIFI8_CMD_DMA_EXT_READ:  /* dma extended read */
        {
            bc[1] = (uint8_t)(adr >> 16);
            bc[2] = (uint8_t)(adr >> 8);
            bc[3] = (uint8_t)(adr);
            bc[4] = (uint8_t)(sz >> 16);
            bc[5] = (uint8_t)(sz >> 8);
            bc[6] = (uint8_t)(sz);
            len = 8;
            break;
        }
        case WIFI8_CMD_INTERNAL_WRITE: /* internal register write */
        {
            bc[1] = (uint8_t)(adr >> 8);
            if (clockless)
                bc[1] |= (1 << 7);
            bc[2] = (uint8_t)(adr);
            bc[3] = (uint8_t)(data_in >> 24);
            bc[4] = (uint8_t)(data_in >> 16);
            bc[5] = (uint8_t)(data_in >> 8);
            bc[6] = (uint8_t)(data_in);
            len = 8;
            break;
        }
        case WIFI8_CMD_SINGLE_WRITE: /* single word write */
        {
            bc[1] = (uint8_t)(adr >> 16);
            bc[2] = (uint8_t)(adr >> 8);
            bc[3] = (uint8_t)(adr);
            bc[4] = (uint8_t)(data_in >> 24);
            bc[5] = (uint8_t)(data_in >> 16);
            bc[6] = (uint8_t)(data_in >> 8);
            bc[7] = (uint8_t)(data_in);
            len = 9;
            break;
        }
        default:
        {
            result = WIFI8_ERROR;
            break;
        }
    }

    if (WIFI8_OK == result)
    {
        if (!gu8crc_off)
        {
            bc[len - 1] = (crc7(0x7f, (uint8_t *)&bc[0], len - 1)) << 1;
        }
        else
        {
            len -= 1;
        }

        if (wifi8_generic_write(ctx, bc, len) < 0)
        {
            result = WIFI8_ERROR;
        }
    }

    return result;
}

static err_t spi_cmd_rsp(wifi8_t *ctx, uint8_t cmd)
{
    uint8_t rsp;
    err_t result = WIFI8_OK;
    int8_t s8RetryCnt;

    s8RetryCnt = 10;
    do
    {
        if (WIFI8_OK != wifi8_generic_read(ctx, &rsp, 1))
        {
            return WIFI8_ERROR;
        }
    } while ((rsp != cmd) && (s8RetryCnt-- > 0));

    if (s8RetryCnt < 0)
    {
        return WIFI8_ERROR;
    }

    s8RetryCnt = 10;
    do
    {
        if (WIFI8_OK != wifi8_generic_read(ctx, &rsp, 1))
        {
            return WIFI8_ERROR;
        }
    } while ((rsp != 0x00) && (s8RetryCnt-- > 0));

    if (s8RetryCnt < 0)
    {
        return WIFI8_ERROR;
    }

    return result;
}

static err_t spi_data_read(wifi8_t *ctx, uint8_t *b, uint16_t sz, uint8_t clockless)
{
    int16_t retry, ix, nbytes;
    uint8_t crc[2];
    uint8_t rsp;

    ix = 0;
    do
    {
        if (sz <= WIFI8_DATA_PKT_SZ)
        {
            nbytes = sz;
        }
        else
        {
            nbytes = WIFI8_DATA_PKT_SZ;
        }

        retry = 10;
        do
        {
            if (wifi8_generic_read(ctx, &rsp, 1) < 0)
            {
                return WIFI8_ERROR;
            }

            if (((rsp >> 4) & 0xf) == 0xf)
            {
                if ((rsp & 0xf0) == 0xf0)
                {
                    break;
                }
            }
        } while (retry--);

        if (retry <= 0)
        {
            return WIFI8_ERROR;
        }

        if (wifi8_generic_read(ctx, &b[ix], nbytes) < 0)
        {
            return WIFI8_ERROR;
        }

        if (!clockless)
        {
            if (!gu8crc_off)
            {
                if (wifi8_generic_read(ctx, crc, 2) < 0)
                {
                    return WIFI8_ERROR;
                }
            }
        }

        ix += nbytes;
        sz -= nbytes;

    } while (sz);

    return WIFI8_OK;
}

static err_t spi_data_write(wifi8_t *ctx, uint8_t *b, uint16_t sz)
{
    int16_t ix = 0;
    uint16_t nbytes;
    err_t result = WIFI8_OK;
    uint8_t cmd, order, crc[2] = {0};

    /**
        Data
    **/
    do
    {
        if (sz <= DATA_PKT_SZ)
        {
            nbytes = sz;
        }
        else
        {
            nbytes = DATA_PKT_SZ;
        }

        /**
            Write command
        **/
        cmd = 0xf0;
        if (ix == 0)
        {
            if (sz <= DATA_PKT_SZ)
            {
                order = 0x3;
            }
            else
            {
                order = 0x1;
            }
        }
        else
        {
            if (sz <= DATA_PKT_SZ)
            {
                order = 0x3;
            }
            else
            {
                order = 0x2;
            }
        }
        cmd |= order;
        if (WIFI8_OK != wifi8_generic_write(ctx, &cmd, 1))
        {
            result = WIFI8_ERROR;
            break;
        }

        /**
            Write data
        **/
        if (WIFI8_OK != wifi8_generic_write(ctx, &b[ix], nbytes))
        {
            result = WIFI8_ERROR;
            break;
        }

        /**
            Write Crc
        **/
        if (!gu8crc_off)
        {
            if (WIFI8_OK != wifi8_generic_write(ctx, crc, 2))
            {
                result = WIFI8_ERROR;
                break;
            }
        }

        ix += nbytes;
        sz -= nbytes;
    } while (sz);

    return result;
}

static err_t nm_spi_init(wifi8_t *ctx)
{
    uint32_t chipid;
    uint32_t reg = 0;

    /**
        configure protocol
    **/
    gu8crc_off = 0;

    if (wifi8_reg_read(ctx, NMI_SPI_PROTOCOL_CONFIG, &reg) != WIFI8_OK)
    {
        /* Read failed. Try with CRC off. This might happen when module
        is removed but chip isn't reset*/
        gu8crc_off = 1;

        if (wifi8_reg_read(ctx, NMI_SPI_PROTOCOL_CONFIG, &reg) != WIFI8_OK)
        {
            // Read failed with both CRC on and off, something went bad
            return WIFI8_ERROR;
        }
    }
    if (gu8crc_off == 0)
    {
        reg &= ~0xc; /* disable crc checking */
        reg &= ~0x70;
        reg |= (0x5 << 4);
        if (wifi8_reg_write(ctx, NMI_SPI_PROTOCOL_CONFIG, reg) != WIFI8_OK)
        {
            return WIFI8_ERROR;
        }
        gu8crc_off = 1;
    }

    /**
        make sure can read back chip id correctly
    **/
    if (wifi8_reg_read(ctx, 0x1000, &chipid) != WIFI8_OK)
    {
        return WIFI8_ERROR;
    }

    /* Make sure SPI max. packet buf_len fits the defined DATA_PKT_SZ.  */
    wifi8_reg_read(ctx, SPI_BASE + 0x24, &reg);
    reg &= ~(0x7 << 4);
    switch (DATA_PKT_SZ)
    {
        case 256:
            reg |= (0 << 4);
            break;
        case 512:
            reg |= (1 << 4);
            break;
        case 1024:
            reg |= (2 << 4);
            break;
        case 2048:
            reg |= (3 << 4);
            break;
        case 4096:
            reg |= (4 << 4);
            break;
        case 8192:
            reg |= (5 << 4);
            break;
    }
    wifi8_reg_write(ctx, SPI_BASE + 0x24, reg);

    return WIFI8_OK;
}

static err_t cpu_start(wifi8_t *ctx)
{
    uint32_t reg = 0;

    if ((WIFI8_OK != wifi8_reg_write(ctx, BOOTROM_REG, 0)) ||
        (WIFI8_OK != wifi8_reg_write(ctx, NMI_STATE_REG, 0)) ||
        (WIFI8_OK != wifi8_reg_write(ctx, NMI_REV_REG, 0)))
    {
        return WIFI8_ERROR;
    }

    if (WIFI8_OK != wifi8_reg_read(ctx, 0x1118, &reg))
    {
        return WIFI8_ERROR;
    }

    reg |= NBIT0;

    if ((WIFI8_OK != wifi8_reg_write(ctx, 0x1118, reg)) ||
        (WIFI8_OK != wifi8_reg_write(ctx, 0x150014ul, 0x1)) ||
        (WIFI8_OK != wifi8_reg_read(ctx, NMI_GLB_RESET_0, &reg)))
    {
        return WIFI8_ERROR;
    }

    if ((reg & (1ul << 10)) == (1ul << 10))
    {
        reg &= ~(1ul << 10);
        if (WIFI8_OK != wifi8_reg_write(ctx, NMI_GLB_RESET_0, reg))
        {
            return WIFI8_ERROR;
        }
    }

    reg |= (1ul << 10);

    if (WIFI8_OK != wifi8_reg_write(ctx, NMI_GLB_RESET_0, reg))
    {
        return WIFI8_ERROR;
    }
    Delay_1ms();

    return WIFI8_OK;
}

static err_t wait_for_bootrom(wifi8_t *ctx, uint8_t arg)
{
    err_t ret = WIFI8_OK;
    uint32_t reg = 0, cnt = 0;
    uint32_t u32GpReg1 = 0;

    reg = 0;
    while (1)
    {
        ret = wifi8_reg_read(ctx, 0x1014, &reg); /* wait for efuse loading done */
        if (reg & 0x80000000ul)
        {
            break;
        }
        Delay_1ms(); /* Removing this can cause a bus error. */
    }
    ret = wifi8_reg_read(ctx, M2M_WAIT_FOR_HOST_REG, &reg);
    reg &= 0x1;

    /* check if waiting for the host will be skipped or not */
    if (reg == 0)
    {
        while (reg != M2M_FINISH_BOOT_ROM)
        {
            Delay_1ms();
            ret = wifi8_reg_read(ctx, BOOTROM_REG, &reg);

            if (++cnt > TIMEOUT)
            {
                return WIFI8_ERROR;
            }
        }
    }

    if (M2M_WIFI_MODE_CONFIG == arg)
    {
        wifi8_reg_write(ctx, NMI_REV_REG, M2M_ATE_FW_START_VALUE);
    }
    else if (M2M_WIFI_MODE_ETHERNET == arg)
    {
        u32GpReg1 = rHAVE_ETHERNET_MODE_BIT;
    }

    uint32_t val32 = 0;
    if (REV(wifi8_chip_id(ctx)) == REV_3A0)
    {
        val32 = u32GpReg1 | rHAVE_USE_PMU_BIT;
    }
    else
    {
        val32 = u32GpReg1;
    }

    do
    {
        wifi8_reg_write(ctx, rNMI_GP_REG_1, val32);
        if (val32 != 0)
        {
            uint32_t reg = 0;
            ret = wifi8_reg_read(ctx, rNMI_GP_REG_1, &reg);
            if (ret == WIFI8_OK)
            {
                if (reg == val32)
                    break;
            }
        }
        else
        {
            break;
        }
    } while (1);

    wifi8_reg_write(ctx, BOOTROM_REG, M2M_START_FIRMWARE);

    return ret;
}

static err_t wait_for_firmware_start(wifi8_t *ctx, uint8_t arg)
{
    uint32_t reg = 0, cnt = 0;
    volatile uint32_t regAddress = NMI_STATE_REG;
    volatile uint32_t checkValue = M2M_FINISH_INIT_STATE;

    if (M2M_WIFI_MODE_CONFIG == arg)
    {
        regAddress = NMI_REV_REG;
        checkValue = M2M_ATE_FW_START_VALUE; //M2M_ATE_FW_IS_UP_VALUE;
    }

    while (checkValue != reg)
    {
        Delay_1ms();
        Delay_1ms();

        if (WIFI8_OK != wifi8_reg_read(ctx, regAddress, &reg))
        {
            // ensure reg != checkValue
            reg = !checkValue;
        }
        if (++cnt > TIMEOUT)
        {
            return WIFI8_ERROR;
        }
    }
    if (M2M_FINISH_INIT_STATE == checkValue)
    {
        wifi8_reg_write(ctx, NMI_STATE_REG, 0);
    }

    return WIFI8_OK;
}

static void chip_idle(wifi8_t *ctx)
{
    uint32_t reg = 0;
    wifi8_reg_read(ctx, 0x1, &reg);
    if (reg & NBIT1)
    {
        reg &= ~NBIT1;
        wifi8_reg_write(ctx, 0x1, reg);
    }
}

static err_t chip_sleep(wifi8_t *ctx)
{
    uint32_t reg;

    for (;;)
    {
        if (WIFI8_OK != wifi8_reg_read(ctx, CORT_HOST_COMM, &reg))
        {
            return WIFI8_ERROR;
        }
        if ((reg & NBIT0) == 0)
        {
            break;
        }
    }

    /* Clear bit 1 */
    if (WIFI8_OK != wifi8_reg_read(ctx, CORT_HOST_COMM, &reg))
    {
        return WIFI8_ERROR;
    }
    if (reg & NBIT1)
    {
        reg &= ~NBIT1;
        if (WIFI8_OK != wifi8_reg_write(ctx, WAKE_CLK_REG, reg))
        {
            return WIFI8_ERROR;
        }
    }

    if (WIFI8_OK != wifi8_reg_read(ctx, HOST_CORT_COMM, &reg))
    {
        return WIFI8_ERROR;
    }
    if (reg & NBIT0)
    {
        reg &= ~NBIT0;
        if (WIFI8_OK != wifi8_reg_write(ctx, HOST_CORT_COMM, reg))
        {
            return WIFI8_ERROR;
        }
    }

    return WIFI8_OK;
}

static err_t chip_wake(wifi8_t *ctx)
{
    uint32_t reg = 0, clk_status_reg = 0, trials = 0;

    wifi8_reg_read(ctx, CLOCKS_EN_REG, &clk_status_reg);

    if (WIFI8_OK != wifi8_reg_read(ctx, HOST_CORT_COMM, &reg))
    {
        return WIFI8_ERROR;
    }
    if (!(reg & NBIT0))
    {
        /*USE bit 0 to indicate host wakeup*/
        if (WIFI8_OK != wifi8_reg_write(ctx, HOST_CORT_COMM, reg | NBIT0))
        {
            return WIFI8_ERROR;
        }
    }

    if (WIFI8_OK != wifi8_reg_read(ctx, WAKE_CLK_REG, &reg))
    {
        return WIFI8_ERROR;
    }
    /* Set bit 1 */
    if (!(reg & NBIT1))
    {
        if (WIFI8_OK != wifi8_reg_write(ctx, WAKE_CLK_REG, reg | NBIT1))
        {
            return WIFI8_ERROR;
        }
    }

    do
    {
        if (WIFI8_OK != wifi8_reg_read(ctx, CLOCKS_EN_REG, &clk_status_reg))
        {
            return WIFI8_ERROR;
        }

        if (clk_status_reg & NBIT2)
        {
            break;
        }
        Delay_5ms();
        trials++;
        if (trials > WAKEUP_TRIALS)
        {
            return WIFI8_ERROR;
        }
    } while (1);

    return WIFI8_OK;
}

static err_t enable_interrupts(wifi8_t *ctx)
{
    uint32_t reg = 0;
    /**
    interrupt pin mux select
    **/
    if (WIFI8_OK != wifi8_reg_read(ctx, NMI_PIN_MUX_0, &reg))
    {
        return WIFI8_ERROR;
    }
    reg |= ((uint32_t)1 << 8);
    if (WIFI8_OK != wifi8_reg_write(ctx, NMI_PIN_MUX_0, reg))
    {
        return WIFI8_ERROR;
    }
    /**
    interrupt enable
    **/
    if (WIFI8_OK != wifi8_reg_read(ctx, NMI_INTR_ENABLE, &reg))
    {
        return WIFI8_ERROR;
    }
    reg |= ((uint32_t)1 << 16);
    if (WIFI8_OK != wifi8_reg_write(ctx, NMI_INTR_ENABLE, reg))
    {
        return WIFI8_ERROR;
    }
    return WIFI8_OK;
}

static err_t hif_init(wifi8_t *ctx)
{
    memset((uint8_t *)&hif_cxt, 0, sizeof(wifi8_hif_context_t));

    return chip_sleep(ctx);
}

static err_t nm_get_hif_info(wifi8_t *ctx, uint16_t *pu16_fw_hif_info, uint16_t *pu16_ota_hif_info)
{
    uint32_t reg = 0;

    if (WIFI8_OK == wifi8_reg_read(ctx, NMI_REV_REG, &reg))
    {
        if (pu16_fw_hif_info != NULL)
        {
            *pu16_fw_hif_info = (uint16_t)reg;
        }
        if (pu16_ota_hif_info)
        {
            *pu16_ota_hif_info = (uint16_t)(reg >> 16);
        }
        return WIFI8_OK;
    }

    return WIFI8_ERROR;
}

static err_t hif_check_compatibility(uint16_t u16_hif_info)
{
    if ((M2M_GET_HIF_BLOCK(u16_hif_info) == M2M_HIF_BLOCK_VALUE) && (M2M_GET_HIF_MAJOR(u16_hif_info) == M2M_HIF_MAJOR_VALUE))
    {
        return WIFI8_OK;
    }
    return WIFI8_ERROR;
}

static err_t hif_enable_access(wifi8_t *ctx)
{
    uint16_t fw_hif_info = 0;

    if (WIFI8_OK == nm_get_hif_info(ctx, &fw_hif_info, NULL))
    {
        if (WIFI8_OK == hif_check_compatibility(fw_hif_info))
        {
            switch (M2M_GET_HIF_MINOR(fw_hif_info))
            {
            case 0:
                ctx->hif_bl_offset = 1;
                break;
            case 1:
                ctx->hif_bl_offset = 2;
                break;
            case 2:
                ctx->hif_bl_offset = 2;
                break;
            case 3:
                ctx->hif_bl_offset = 3;
                break;
            case 4:
                ctx->hif_bl_offset = 9;
                break;
            default:
                ctx->hif_bl_offset = HIF_BLACKLIST_SZ;
                break;
            }
        }
        else
        {
            ctx->hif_bl_offset = 0;
        }
    }
    else
    {
        return WIFI8_ERROR;
    }
    return WIFI8_OK;
}

static err_t hif_send(wifi8_t *ctx, uint8_t u8_gid, uint8_t u8_opcode, uint8_t *pu8_ctrl_buf, uint16_t u16_ctrl_buf_size,
                      uint8_t *pu8_data_buf, uint16_t u16_data_size, uint16_t u16_data_offset)
{
    wifi8_hif_hdr_t str_hif;
    uint32_t u32_ctrl_data_gap = u16_data_offset;

    str_hif.u8_opcode = u8_opcode & (~NBIT7);
    str_hif.u8_gid = u8_gid;
    str_hif.u16_length = M2M_HIF_HDR_OFFSET;

    if (pu8_ctrl_buf != NULL)
    {
        if (u16_ctrl_buf_size > M2M_HIF_MAX_PACKET_SIZE - M2M_HIF_HDR_OFFSET)
        {
            return WIFI8_ERROR;
        }
        str_hif.u16_length += u16_ctrl_buf_size;
        u32_ctrl_data_gap -= u16_ctrl_buf_size;
    }
    if (pu8_data_buf != NULL)
    {
        if ((uint32_t)u16_data_offset + u16_data_size > M2M_HIF_MAX_PACKET_SIZE - M2M_HIF_HDR_OFFSET)
        {
            return WIFI8_ERROR;
        }
        str_hif.u16_length += u32_ctrl_data_gap + u16_data_size;
    }
    if (hif_check_code( ctx, str_hif.u8_gid, str_hif.u8_opcode) != WIFI8_OK)
    {
        return WIFI8_ERROR;
    }
    if (str_hif.u16_length <= M2M_HIF_MAX_PACKET_SIZE)
    {
        if (chip_wake(ctx) == WIFI8_OK)
        {
            volatile uint32_t reg, dma_addr = 0;
            volatile uint16_t cnt = 0;

            reg = 0ul;
            reg |= (uint32_t)u8_gid;
            reg |= ((uint32_t)u8_opcode << 8);
            reg |= ((uint32_t)str_hif.u16_length << 16);
            if (WIFI8_OK != wifi8_reg_write(ctx, NMI_STATE_REG, reg))
            {
                return WIFI8_ERROR;
            }

            reg = 0ul;
            reg |= NBIT1;
            if (WIFI8_OK != wifi8_reg_write(ctx, WIFI_HOST_RCV_CTRL_2, reg))
            {
                return WIFI8_ERROR;
            }

            if (ISNMC3400(wifi8_chip_id(ctx)))
            {
                if (WIFI8_OK != wifi8_reg_write(ctx, INTERRUPT_CORTUS_1_3000D0, 1))
                {
                    return WIFI8_ERROR;
                }
            }

            dma_addr = 0;

            for (cnt = 0; cnt < 1000 * 5; cnt++)
            {
                if (wifi8_reg_read(ctx, WIFI_HOST_RCV_CTRL_2, (uint32_t *)&reg) != WIFI8_OK)
                {
                    break;
                }
                /*
                 * If it takes too long to get a response, the slow down to
                 * avoid back-to-back register read operations.
                 */
                if (cnt >= 1000)
                {
                    Delay_5ms();
                }
                if (!(reg & NBIT1))
                {
                    if (wifi8_reg_read(ctx, WIFI_HOST_RCV_CTRL_4, (uint32_t *)&dma_addr) != WIFI8_OK)
                    {
                        /*in case of read error clear the DMA address and return error*/
                        dma_addr = 0;
                        return WIFI8_ERROR;
                    }
                    /*in case of success break */
                    break;
                }
            }

            if (dma_addr != 0)
            {
                volatile uint32_t u32_curr_addr;
                u32_curr_addr = dma_addr;
                str_hif.u16_length = NM_BSP_B_L_16(str_hif.u16_length);
                if (WIFI8_OK != wifi8_block_write(ctx, u32_curr_addr, (uint8_t *)&str_hif, M2M_HIF_HDR_OFFSET))
                {
                    return WIFI8_ERROR;
                }
                u32_curr_addr += M2M_HIF_HDR_OFFSET;
                if (pu8_ctrl_buf != NULL)
                {
                    if (WIFI8_OK != wifi8_block_write(ctx, u32_curr_addr, pu8_ctrl_buf, u16_ctrl_buf_size))
                    {
                        return WIFI8_ERROR;
                    }
                    u32_curr_addr += u16_ctrl_buf_size;
                }
                if (pu8_data_buf != NULL)
                {
                    u32_curr_addr += u32_ctrl_data_gap;
                    if (WIFI8_OK != wifi8_block_write(ctx, u32_curr_addr, pu8_data_buf, u16_data_size))
                    {
                        return WIFI8_ERROR;
                    }
                    u32_curr_addr += u16_data_size;
                }

                reg = dma_addr << 2;

                /* Following line of code is to generate the interrupt which is not strictly needed for 3400,
                 * but has no noticeable side effects
                 */
                reg |= NBIT1;
                if (WIFI8_OK != wifi8_reg_write(ctx, WIFI_HOST_RCV_CTRL_3, reg))
                {
                    return WIFI8_ERROR;
                }

                if (ISNMC3400(wifi8_chip_id(ctx)))
                {
                    if (WIFI8_OK != wifi8_reg_write(ctx, INTERRUPT_CORTUS_2_3000D0, 1))
                        return WIFI8_ERROR;
                }
            }
            else
            {
                chip_sleep(ctx);
                return WIFI8_ERROR;
            }
        }
        else
        {
            return WIFI8_ERROR;
        }
    }
    else
    {
        return WIFI8_ERROR;
    }
    /*actual sleep ret = WIFI8_OK*/
    return chip_sleep(ctx);
}

static err_t hif_receive(wifi8_t *ctx, uint32_t u32_addr, uint8_t *pu8_buf, uint16_t u16_sz, uint8_t is_done)
{
    if ((u32_addr == 0) || (pu8_buf == NULL) || (u16_sz == 0))
    {
        if (is_done)
        {
            hif_set_rx_done(ctx);
        }
        return WIFI8_ERROR;
    }

    if (u16_sz > hif_cxt.u32_rx_size)
    {
        return WIFI8_ERROR;
    }
    if ((u32_addr < hif_cxt.u32_rx_addr) || ((u32_addr + u16_sz) > (hif_cxt.u32_rx_addr + hif_cxt.u32_rx_size)))
    {
        return WIFI8_ERROR;
    }

    /* Receive the payload */
    if (WIFI8_OK != wifi8_block_read(ctx, u32_addr, pu8_buf, u16_sz))
    {
        return WIFI8_ERROR;
    }

    /* check if this is the last packet */
    if (is_done ||
        (((hif_cxt.u32_rx_addr + hif_cxt.u32_rx_size) - (u32_addr + u16_sz)) <= 0) ||
        ((4 - ((u32_addr + u16_sz) & 3)) == ((hif_cxt.u32_rx_addr + hif_cxt.u32_rx_size) - (u32_addr + u16_sz))))
    {
        /* set RX done */
        if (WIFI8_OK != hif_set_rx_done(ctx))
        {
            return WIFI8_ERROR;
        }
    }

    return WIFI8_OK;
}

static err_t hif_set_rx_done(wifi8_t *ctx)
{
    uint32_t reg;

    enable_interrupts(ctx);

    if (ISNMC3400(wifi8_chip_id(ctx)))
    {
        if (WIFI8_OK != wifi8_reg_write(ctx, INTERRUPT_CORTUS_0_3000D0, 1))
        {
            return WIFI8_ERROR;
        }
    }
    else
    {
        if (WIFI8_OK != wifi8_reg_read(ctx, WIFI_HOST_RCV_CTRL_0, &reg))
        {
            return WIFI8_ERROR;
        }

        /* Set RX Done */
        reg |= NBIT1;
        if (WIFI8_OK != wifi8_reg_write(ctx, WIFI_HOST_RCV_CTRL_0, reg))
        {
            return WIFI8_ERROR;
        }
    }

    return WIFI8_OK;
}

static err_t hif_isr(wifi8_t *ctx)
{
    volatile err_t ret = WIFI8_OK;
    uint32_t reg;
    volatile wifi8_hif_hdr_t str_hif;

    if (WIFI8_OK == wifi8_reg_read(ctx, WIFI_HOST_RCV_CTRL_0, &reg))
    {
        if (reg & 0x1) /* New interrupt has been received */
        {
            uint16_t buf_len;

            /*Clearing RX interrupt*/
            if (wifi8_reg_read(ctx, WIFI_HOST_RCV_CTRL_0, &reg) != WIFI8_OK)
            {
                return WIFI8_ERROR;
            }

            reg &= ~NBIT0;

            if (wifi8_reg_write(ctx, WIFI_HOST_RCV_CTRL_0, reg) != WIFI8_OK)
            {
                return WIFI8_ERROR;
            }

            /* read the rx buf_len */
            if (wifi8_reg_read(ctx, WIFI_HOST_RCV_CTRL_0, &reg) != WIFI8_OK)
            {
                return WIFI8_ERROR;
            }

            hif_cxt.u8_hif_rx_done = 1;
            buf_len = (uint16_t)((reg >> 2) & 0xfff);
            if (buf_len > 0)
            {
                uint32_t address = 0;
                /**
                start bus transfer
                **/
                if (WIFI8_OK != wifi8_reg_read(ctx, WIFI_HOST_RCV_CTRL_1, &address))
                {
                    return WIFI8_ERROR;
                }
                hif_cxt.u32_rx_addr = address;
                hif_cxt.u32_rx_size = buf_len;
                ret = wifi8_block_read(ctx, address, (uint8_t *)&str_hif, sizeof(wifi8_hif_hdr_t));
                str_hif.u16_length = NM_BSP_B_L_16(str_hif.u16_length);
                if (WIFI8_OK != ret)
                {
                    return WIFI8_ERROR;
                }
                if (str_hif.u16_length != buf_len)
                {
                    if ((buf_len - str_hif.u16_length) > 4)
                    {
                        return WIFI8_ERROR;
                    }
                }

                if (M2M_REQ_GROUP_WIFI == str_hif.u8_gid)
                {
                    if (hif_cxt.pf_wifi_cb)
                    {
                        hif_cxt.pf_wifi_cb(ctx, str_hif.u8_opcode, str_hif.u16_length - M2M_HIF_HDR_OFFSET, address + M2M_HIF_HDR_OFFSET);
                    }
                    else
                    {
                        return WIFI8_ERROR;
                    }
                }
                else if (M2M_REQ_GROUP_IP == str_hif.u8_gid)
                {
                    if (hif_cxt.pf_ip_cb)
                    {
                        hif_cxt.pf_ip_cb(ctx, str_hif.u8_opcode, str_hif.u16_length - M2M_HIF_HDR_OFFSET, address + M2M_HIF_HDR_OFFSET);
                    }
                    else
                    {
                        return WIFI8_ERROR;
                    }
                }
                else if (M2M_REQ_GROUP_OTA == str_hif.u8_gid)
                {
                    if (hif_cxt.pf_ota_cb)
                    {
                        hif_cxt.pf_ota_cb(ctx, str_hif.u8_opcode, str_hif.u16_length - M2M_HIF_HDR_OFFSET, address + M2M_HIF_HDR_OFFSET);
                    }
                }
                else if (M2M_REQ_GROUP_SIGMA == str_hif.u8_gid)
                {
                    if (hif_cxt.pf_sigma_cb)
                    {
                        hif_cxt.pf_sigma_cb(ctx, str_hif.u8_opcode, str_hif.u16_length - M2M_HIF_HDR_OFFSET, address + M2M_HIF_HDR_OFFSET);
                    }
                }
                else if (M2M_REQ_GROUP_SSL == str_hif.u8_gid)
                {
                    if (hif_cxt.pf_ssl_cb)
                    {
                        hif_cxt.pf_ssl_cb(ctx, str_hif.u8_opcode, str_hif.u16_length - M2M_HIF_HDR_OFFSET, address + M2M_HIF_HDR_OFFSET);
                    }
                }
                else
                {
                    return WIFI8_ERROR;
                }

                if (hif_cxt.u8_hif_rx_done)
                {
                    if (hif_set_rx_done(ctx) != WIFI8_OK)
                    {
                        return WIFI8_ERROR;
                    }
                }
            }
            else
            {
                return WIFI8_ERROR;
            }
        }
        else
        {
            return WIFI8_ERROR;
        }
    }
    else
    {
        return WIFI8_ERROR;
    }

    return WIFI8_OK;
}

err_t hif_handle_isr(wifi8_t *ctx)
{
    hif_cxt.u8_yield = 0;

    if (!digital_in_read(&ctx->int_pin))
    {
        hif_cxt.u8_interrupt++;
    }

    while (hif_cxt.u8_interrupt && !hif_cxt.u8_yield)
    {
        hif_cxt.u8_interrupt--;
        uint8_t retries = 5;
        for ( ; ; )
        {
            if (hif_isr(ctx) == WIFI8_OK)
            {
                return WIFI8_OK;
            }
            else
            {
                retries--;
                if (!retries)
                {
                    return WIFI8_ERROR;
                }
            }
        }
    }
}

static err_t hif_check_code(wifi8_t *ctx, uint8_t u8_gid, uint8_t u8_op_code)
{
    uint8_t u8_bl_id;
    uint16_t u16_hif_code = ((uint16_t)u8_gid << 8) | u8_op_code;
    if ((u16_hif_code == HIFCODE_OTA_RB) || (u16_hif_code == HIFCODE_OTA_SW))
    {
        return WIFI8_OK;
    }
    if (ctx->hif_bl_offset == 0)
    {
        return WIFI8_ERROR;
    }

    for (u8_bl_id = ctx->hif_bl_offset; u8_bl_id < HIF_BLACKLIST_SZ; u8_bl_id++)
    {
        if (u16_hif_code == gau16_hif_blacklist[u8_bl_id])
        {
            return WIFI8_ERROR;
        }
    }
    return WIFI8_OK;
}

static void m2m_wifi_cb(wifi8_t *ctx, uint8_t u8_op_code, uint16_t u16_data_size, uint32_t u32_addr)
{
    uint8_t rx_buf[8];

    if (u8_op_code == M2M_WIFI_RESP_CON_STATE_CHANGED)
    {
        wifi8_m2m_wifi_state_changed_t str_state;
        if (hif_receive(ctx, u32_addr, (uint8_t *)&str_state, sizeof(wifi8_m2m_wifi_state_changed_t), 0) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_RESP_CON_STATE_CHANGED, &str_state);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_RESP_GET_SYS_TIME)
    {
        wifi8_system_time_t str_sys_time;
        if (hif_receive(ctx, u32_addr, (uint8_t *)&str_sys_time, sizeof(wifi8_system_time_t), 0) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_RESP_GET_SYS_TIME, &str_sys_time);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_RESP_CONN_INFO)
    {
        wifi8_m2m_conn_info_t str_conn_info;
        if (hif_receive(ctx, u32_addr, (uint8_t *)&str_conn_info, sizeof(wifi8_m2m_conn_info_t), 1) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_RESP_CONN_INFO, &str_conn_info);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_REQ_DHCP_CONF)
    {
        wifi8_m2mip_config_t str_ip_config;
        if (hif_receive(ctx, u32_addr, (uint8_t *)&str_ip_config, sizeof(wifi8_m2mip_config_t), 0) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_REQ_DHCP_CONF, (uint8_t *)&str_ip_config);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_REQ_WPS)
    {
        wifi8_m2m_wps_info_t str_wps;
        memset((uint8_t *)&str_wps, 0, sizeof(wifi8_m2m_wps_info_t));
        if (hif_receive(ctx, u32_addr, (uint8_t *)&str_wps, sizeof(wifi8_m2m_wps_info_t), 0) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_REQ_WPS, &str_wps);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_RESP_IP_CONFLICT)
    {
        uint32_t u32_conflicted_ip;
        if (hif_receive(ctx, u32_addr, (uint8_t *)&u32_conflicted_ip, sizeof(u32_conflicted_ip), 0) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_RESP_IP_CONFLICT, NULL);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_RESP_SCAN_DONE)
    {
        wifi8_m2m_scan_done_t str_state;
        if (hif_receive(ctx, u32_addr, (uint8_t *)&str_state, sizeof(wifi8_m2m_scan_done_t), 0) == WIFI8_OK)
        {
            ctx->ch_num = str_state.u8_numof_ch;
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_RESP_SCAN_DONE, &str_state);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_RESP_SCAN_RESULT)
    {
        wifi8_m2m_wifiscan_result_t str_scan_result;
        if (hif_receive(ctx, u32_addr, (uint8_t *)&str_scan_result, sizeof(wifi8_m2m_wifiscan_result_t), 0) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_RESP_SCAN_RESULT, &str_scan_result);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_RESP_CURRENT_RSSI)
    {
        if (hif_receive(ctx, u32_addr, rx_buf, 4, 0) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_RESP_CURRENT_RSSI, rx_buf);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_RESP_CLIENT_INFO)
    {
        if (hif_receive(ctx, u32_addr, rx_buf, 4, 0) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_RESP_CLIENT_INFO, rx_buf);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_RESP_PROVISION_INFO)
    {
        wifi8_m2m_provision_info_t str_prov_info;
        if (hif_receive(ctx, u32_addr, (uint8_t *)&str_prov_info, sizeof(wifi8_m2m_provision_info_t), 1) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_RESP_PROVISION_INFO, &str_prov_info);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_RESP_DEFAULT_CONNECT)
    {
        wifi8_m2m_default_conn_resp_t str_resp;
        if (hif_receive(ctx, u32_addr, (uint8_t *)&str_resp, sizeof(wifi8_m2m_default_conn_resp_t), 1) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_RESP_DEFAULT_CONNECT, &str_resp);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_REQRSP_DELETE_APID)
    {
        wifi8_m2m_generic_resp_t str_resp;
        if (hif_receive(ctx, u32_addr, (uint8_t *)&str_resp, sizeof(wifi8_m2m_generic_resp_t), 0) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_REQRSP_DELETE_APID, &str_resp);
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_RESP_BLE_API_RECV)
    {
        //Read the length
        if (hif_receive(ctx, u32_addr, rx_buf, 2, 0) == WIFI8_OK)
        {
            uint16_t u16_ble_msg_len = ((uint16_t)rx_buf[1] << 8) + rx_buf[0];
            static uint8_t ble_rx_buf[sizeof(wifi8_m2m_ble_api_msg_t) + 0xFF] = {0};
            wifi8_m2m_ble_api_msg_t *ble_rx = (wifi8_m2m_ble_api_msg_t *)ble_rx_buf;

            if (ble_rx != NULL)
            {
                ble_rx->u16_len = u16_ble_msg_len;

                //read the rest of the message
                if (hif_receive(ctx, u32_addr + 2, ble_rx->data_msg, ble_rx->u16_len, 1) == WIFI8_OK)
                {
                    if (ctx->app_wifi_cb)
                    {
                        ctx->app_wifi_cb(M2M_WIFI_RESP_BLE_API_RECV, ble_rx);
                    }
                }
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_RESP_GET_PRNG)
    {
        wifi8_prng_t str_prng;
        if (hif_receive(ctx, u32_addr, (uint8_t *)&str_prng, sizeof(wifi8_prng_t), 0) == WIFI8_OK)
        {
            if (hif_receive(ctx, u32_addr + sizeof(wifi8_prng_t), str_prng.pu8_rng_buff, str_prng.u16_prng_size, 1) == WIFI8_OK)
            {
                if (ctx->app_wifi_cb)
                {
                    ctx->app_wifi_cb(M2M_WIFI_RESP_GET_PRNG, &str_prng);
                }
            }
        }
    }
    else if (u8_op_code == M2M_WIFI_RESP_SET_GAIN_TABLE)
    {
        wifi8_m2m_gain_table_rsp_t str_gain_rsp;
        if (hif_receive(ctx, u32_addr, (uint8_t *)&str_gain_rsp, sizeof(wifi8_m2m_gain_table_rsp_t), 0) == WIFI8_OK)
        {
            if (ctx->app_wifi_cb)
            {
                ctx->app_wifi_cb(M2M_WIFI_RESP_SET_GAIN_TABLE, &str_gain_rsp);
            }
        }
    }
}

static err_t hif_register_cb(uint8_t u8_grp, wifi8_hif_call_back_t fn)
{
    switch (u8_grp)
    {
        case M2M_REQ_GROUP_IP:
            hif_cxt.pf_ip_cb = fn;
            break;
        case M2M_REQ_GROUP_WIFI:
            hif_cxt.pf_wifi_cb = fn;
            break;
        case M2M_REQ_GROUP_OTA:
            hif_cxt.pf_ota_cb = fn;
            break;
        case M2M_REQ_GROUP_HIF:
            hif_cxt.pf_hif_cb = fn;
            break;
        case M2M_REQ_GROUP_SIGMA:
            hif_cxt.pf_sigma_cb = fn;
            break;
        case M2M_REQ_GROUP_SSL:
            hif_cxt.pf_ssl_cb = fn;
            break;
        default:
            return WIFI8_ERROR;
    }
    return WIFI8_OK;
}

err_t m2m_wifi_ble_set_gain_table(wifi8_t *ctx, uint8_t table_idx)
{
    wifi8_m2m_gain_table_t str_gain_table = {0};

    str_gain_table.u8_gain_table = table_idx;

    return hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_SET_GAIN_TABLE,
                    (uint8_t *)&str_gain_table, sizeof(wifi8_m2m_gain_table_t), NULL, 0, 0);
}

static void m2m_ip_cb(wifi8_t *ctx, uint8_t u8_op_code, uint16_t u16_buffer_size, uint32_t u32_address)
{
    if (u8_op_code == SOCKET_CMD_BIND)
    {
        wifi8_bind_reply_t str_bind_reply;
        wifi8_socket_bind_msg_t str_bind;

        if (hif_receive(ctx, u32_address, (uint8_t *)&str_bind_reply, sizeof(wifi8_bind_reply_t), 0) == WIFI8_OK)
        {
            str_bind.status = str_bind_reply.s8_status;
            if (ctx->app_socket_cb)
            {
                ctx->app_socket_cb(str_bind_reply.sock, SOCKET_MSG_BIND, &str_bind);
            }
        }
    }
    else if (u8_op_code == SOCKET_CMD_LISTEN)
    {
        wifi8_listen_reply_t str_listen_reply;
        wifi8_socket_listen_msg_t str_listen;
        if (hif_receive(ctx, u32_address, (uint8_t *)&str_listen_reply, sizeof(wifi8_listen_reply_t), 0) == WIFI8_OK)
        {
            str_listen.status = str_listen_reply.s8_status;
            if (ctx->app_socket_cb)
            {
                ctx->app_socket_cb(str_listen_reply.sock, SOCKET_MSG_LISTEN, &str_listen);
            }
        }
    }
    else if (u8_op_code == SOCKET_CMD_ACCEPT)
    {
        wifi8_accept_reply_t str_accept_reply;
        wifi8_socket_accept_msg_t str_accept;
        if (hif_receive(ctx, u32_address, (uint8_t *)&str_accept_reply, sizeof(wifi8_accept_reply_t), 0) == WIFI8_OK)
        {
            if (str_accept_reply.s_connected_sock >= 0)
            {
                ctx->sockets[str_accept_reply.s_connected_sock].u8ssl_flags = 0;
                ctx->sockets[str_accept_reply.s_connected_sock].b_is_used = 1;

                /* the session id is used to distinguish different socket connections
                    by comparing the assigned session id to the one reported by the firmware*/
                ++ctx->session_id;
                if (ctx->session_id == 0)
                {
                    ++ctx->session_id;
                }

                ctx->sockets[str_accept_reply.s_connected_sock].u16_session_id = ctx->session_id;
            }
            str_accept.sock = str_accept_reply.s_connected_sock;
            str_accept.str_addr.sin_family = AF_INET;
            str_accept.str_addr.sin_port = str_accept_reply.str_addr.u16_port;
            str_accept.str_addr.sin_addr.s_addr = str_accept_reply.str_addr.u32ip_addr;
            if (ctx->app_socket_cb)
                ctx->app_socket_cb(str_accept_reply.s_listen_sock, SOCKET_MSG_ACCEPT, &str_accept);
        }
    }
    else if ((u8_op_code == SOCKET_CMD_CONNECT) || (u8_op_code == SOCKET_CMD_SSL_CONNECT) || (u8_op_code == SOCKET_CMD_SSL_CONNECT_ALPN))
    {
        wifi8_connect_alpn_reply_t str_connect_alpn_reply = {{0}};
        wifi8_socket_connect_msg_t str_conn_msg;
        uint16_t u16_hif_sz = sizeof(wifi8_connect_alpn_reply_t);
        if (u8_op_code != SOCKET_CMD_SSL_CONNECT_ALPN)
        {
            u16_hif_sz = sizeof(wifi8_connect_reply_t);
        }
        if (hif_receive(ctx, u32_address, (uint8_t *)&str_connect_alpn_reply, u16_hif_sz, 0) == WIFI8_OK)
        {
            str_conn_msg.sock = str_connect_alpn_reply.str_conn_reply.sock;
            str_conn_msg.s8_error = str_connect_alpn_reply.str_conn_reply.s8_error;
            if (str_connect_alpn_reply.str_conn_reply.s8_error == WIFI8_OK)
            {
                ctx->sockets[str_conn_msg.sock].u16_data_offset = str_connect_alpn_reply.str_conn_reply.u16_app_data_offset - M2M_HIF_HDR_OFFSET;
                ctx->sockets[str_conn_msg.sock].u8_alpn_status = str_connect_alpn_reply.u8_app_protocol_idx;
            }
            else
            {
                ctx->sockets[str_conn_msg.sock].u8_err_source = str_connect_alpn_reply.str_conn_reply.u8_err_source;
                ctx->sockets[str_conn_msg.sock].u8_err_code = str_connect_alpn_reply.str_conn_reply.u8_err_code;
            }
            if (ctx->app_socket_cb)
            {
                ctx->app_socket_cb(str_conn_msg.sock, SOCKET_MSG_CONNECT, &str_conn_msg);
            }
        }
    }
    else if (u8_op_code == SOCKET_CMD_DNS_RESOLVE)
    {
        wifi8_dns_reply_t str_dns_reply;
        if (hif_receive(ctx, u32_address, (uint8_t *)&str_dns_reply, sizeof(wifi8_dns_reply_t), 0) == WIFI8_OK)
        {
            str_dns_reply.u32_host_ip = str_dns_reply.u32_host_ip;
            if (ctx->app_resolve_cb)
            {
                ctx->app_resolve_cb((uint8_t *)str_dns_reply.ac_host_name, str_dns_reply.u32_host_ip);
            }
        }
    }
    else if ((u8_op_code == SOCKET_CMD_RECV) || (u8_op_code == SOCKET_CMD_RECVFROM) || (u8_op_code == SOCKET_CMD_SSL_RECV))
    {
        int8_t sock;
        int16_t s16_recv_status;
        wifi8_recv_reply_t str_recv_reply;
        uint16_t u16_read_size;
        wifi8_socket_recv_msg_t str_recv_msg;
        uint8_t u8_callback_msg_id = SOCKET_MSG_RECV;
        uint16_t u16_data_offset;

        if (u8_op_code == SOCKET_CMD_RECVFROM)
        {
            u8_callback_msg_id = SOCKET_MSG_RECVFROM;
        }

        /* Read RECV REPLY data structure.
        */
        u16_read_size = sizeof(wifi8_recv_reply_t);
        if (hif_receive(ctx, u32_address, (uint8_t *)&str_recv_reply, u16_read_size, 0) == WIFI8_OK)
        {
            uint16_t u16_session_id = 0;

            sock = str_recv_reply.sock;
            u16_session_id = str_recv_reply.u16_session_id;

            /* reset the socket rx pending flag.
            */
            ctx->sockets[sock].b_is_recv_pending = 0;

            s16_recv_status = NM_BSP_B_L_16(str_recv_reply.s16_recv_status);
            u16_data_offset = NM_BSP_B_L_16(str_recv_reply.u16_data_offset);
            str_recv_msg.str_remote_addr.sin_port = str_recv_reply.str_remote_addr.u16_port;
            str_recv_msg.str_remote_addr.sin_addr.s_addr = str_recv_reply.str_remote_addr.u32ip_addr;

            if (u16_session_id == ctx->sockets[sock].u16_session_id)
            {
                if ((s16_recv_status > 0) && (s16_recv_status < u16_buffer_size))
                {
                    /* skip incoming bytes until reaching the start of application data.
                    */
                    u32_address += u16_data_offset;

                    /* read the application data and deliver it to the application callback in
                    the given application buffer. if the buffer is smaller than the received data,
                    the data is passed to the application in chunks according to its buffer buf_len.
                    */
                    u16_read_size = (uint16_t)s16_recv_status;
                    socket_read_socket_data(ctx, sock, &str_recv_msg, u8_callback_msg_id, u32_address, u16_read_size);
                }
                else
                {
                    /* don't tidy up here. application must call close().
                    */
                    str_recv_msg.s16_buffer_size = s16_recv_status;
                    str_recv_msg.pu8_buffer = NULL;
                    if (ctx->app_socket_cb)
                    {
                        ctx->app_socket_cb(sock, u8_callback_msg_id, &str_recv_msg);
                    }
                }
            }
            else
            {
                if (u16_read_size < u16_buffer_size)
                {
                    hif_receive(ctx, 0, NULL, 0, 1);
                }
            }
        }
    }
    else if ((u8_op_code == SOCKET_CMD_SEND) || (u8_op_code == SOCKET_CMD_SENDTO) || (u8_op_code == SOCKET_CMD_SSL_SEND))
    {
        int8_t sock;
        int16_t s16_rcvd;
        wifi8_send_reply_t str_reply;
        uint8_t u8_callback_msg_id = SOCKET_MSG_SEND;

        if (u8_op_code == SOCKET_CMD_SENDTO)
        {
            u8_callback_msg_id = SOCKET_MSG_SENDTO;
        }

        if (hif_receive(ctx, u32_address, (uint8_t *)&str_reply, sizeof(wifi8_send_reply_t), 0) == WIFI8_OK)
        {
            uint16_t u16_session_id = 0;

            sock = str_reply.sock;
            u16_session_id = str_reply.u16_session_id;

            s16_rcvd =  (str_reply.s16_sent_bytes) ;

            if (u16_session_id == ctx->sockets[sock].u16_session_id)
            {
                if (ctx->app_socket_cb)
                {
                    ctx->app_socket_cb(sock, u8_callback_msg_id, &s16_rcvd);
                }
            }
        }
    }
    else if (u8_op_code == SOCKET_CMD_PING)
    {
        wifi8_ping_reply_t str_ping_reply;
        if (hif_receive(ctx, u32_address, (uint8_t *)&str_ping_reply, sizeof(wifi8_ping_reply_t), 1) == WIFI8_OK)
        {
            if ((ctx->ping_id == str_ping_reply.u32_cmd_private) && (ctx->ping_cb != NULL))
            {
                ctx->ping_cb(str_ping_reply.u32ip_addr, str_ping_reply.u32rtt, str_ping_reply.u8_error_code);
            }
        }
    }
}

static void socket_read_socket_data(wifi8_t *ctx, int8_t sock, wifi8_socket_recv_msg_t *pstr_recv, 
                                    uint8_t u8_socket_msg, uint32_t u32_start_address, uint16_t u16_read_count)
{
    uint32_t u32_address = u32_start_address;
    uint16_t u16_read;
    int16_t s16_diff;

    pstr_recv->u16_remaining_size = u16_read_count;
    if ((u16_read_count > 0) && (ctx->sockets[sock].pu8_user_buffer !=  ((void *)0) ) && 
        (ctx->sockets[sock].u16_user_buffer_size > 0) && (ctx->sockets[sock].b_is_used == 1))
    {
        u16_read = u16_read_count;
        s16_diff = u16_read - ctx->sockets[sock].u16_user_buffer_size;
        if (s16_diff > 0)
        {
            u16_read = ctx->sockets[sock].u16_user_buffer_size;
        }

        if (hif_receive(ctx, u32_address, ctx->sockets[sock].pu8_user_buffer, u16_read, 1) == WIFI8_OK)
        {
            pstr_recv->pu8_buffer = ctx->sockets[sock].pu8_user_buffer;
            pstr_recv->s16_buffer_size = u16_read;
            pstr_recv->u16_remaining_size -= u16_read;

            ctx->sockets[sock].u16_user_buffer_size -= u16_read;
            if (ctx->sockets[sock].u16_user_buffer_size == 0)
            {
                ctx->sockets[sock].pu8_user_buffer = NULL;
            }

            if (ctx->app_socket_cb)
            {
                ctx->app_socket_cb(sock, u8_socket_msg, pstr_recv);
            }
        }
    }
}

static err_t m2m_wifi_connect_sc(wifi8_t *ctx, uint8_t *pc_ssid, uint8_t u8_ssid_len, wifi8_m2m_sec_type_t u8_sec_type,
                                 void *pv_auth_info, wifi8_m2m_scan_ch_t u16_ch, uint16_t u8_no_save_cred)
{
    err_t s8_ret = WIFI8_ERROR;
    wifi8_network_id_t str_network_id; //{(uint8_t *)NULL, (uint8_t *)pc_ssid, u8_ssid_len, (wifi8_m2m_scan_ch_t)u16_ch};
    str_network_id.pu8_bssid = (uint8_t *)NULL;
    str_network_id.pu8_ssid = pc_ssid;
    str_network_id.u8_ssid_len = u8_ssid_len;
    str_network_id.enu_channel = u16_ch;
    wifi8_cred_store_option_t enu_cred_store_option; // = u8NoSaveCred ? WIFI_CRED_DONTSAVE : WIFI_CRED_SAVE_ENCRYPTED;

    if (u8_no_save_cred)
    {
        enu_cred_store_option = WIFI_CRED_DONTSAVE;
    }
    else
    {
        enu_cred_store_option = WIFI_CRED_SAVE_ENCRYPTED;
    }

    /* This API does not support SSIDs which contain '\0'. If there is a '\0' character within the
     * first u8SsidLen characters, then assume that the input u8SsidLen was incorrect - set length
     * to strlen(pcSsid) and continue. This is to avoid a change from the behaviour of previously
     * released drivers. */
    if (u8_ssid_len < M2M_MAX_SSID_LEN)
    {
        while (u8_ssid_len--)
        {
            if (str_network_id.pu8_ssid[u8_ssid_len] == 0)
            {
                str_network_id.u8_ssid_len = u8_ssid_len;
            }
        }
    }

    switch ((wifi8_m2m_sec_type_t)u8_sec_type)
    {
        case M2M_WIFI_SEC_OPEN:
            s8_ret = m2m_wifi_connect_open(ctx, enu_cred_store_option, &str_network_id);
            break;
        case M2M_WIFI_SEC_WPA_PSK:
            if (pv_auth_info != NULL)
            {
                wifi8_auth_psk_t str_auth_psk;
                str_auth_psk.pu8_passphrase = NULL;
                str_auth_psk.pu8_psk = NULL;
                str_auth_psk.u8_passphrase_len = 0;

                uint16_t len = strlen((uint8_t *)pv_auth_info);

                if (len == M2M_MAX_PSK_LEN - 1)
                {
                    str_auth_psk.pu8_psk = (uint8_t *)pv_auth_info;
                }
                else
                {
                    str_auth_psk.pu8_passphrase = (uint8_t *)pv_auth_info;
                    str_auth_psk.u8_passphrase_len = len;
                }
                s8_ret = m2m_wifi_connect_psk(ctx, enu_cred_store_option, &str_network_id, &str_auth_psk);
            }
            break;
        case M2M_WIFI_SEC_WEP:
            if (pv_auth_info != NULL)
            {
                wifi8_m2m_wifi_wep_params_t *pstr_wep_params = (wifi8_m2m_wifi_wep_params_t *)pv_auth_info;
                wifi8_auth_wep_t str_auth_wep; //     = {pstr_wep_params->au8_wep_key, pstr_wep_params->u8_key_sz-1, pstr_wep_params->u8_key_indx};
                str_auth_wep.pu8_wep_key = pstr_wep_params->au8_wep_key;
                str_auth_wep.u8_key_sz = pstr_wep_params->u8_key_sz - 1;
                str_auth_wep.u8_key_indx = pstr_wep_params->u8_key_indx;

                s8_ret = m2m_wifi_connect_wep(ctx, enu_cred_store_option, &str_network_id, &str_auth_wep);
            }
            break;
        default:
            break;
    }
    return s8_ret;
}

static err_t m2m_wifi_connect_psk(wifi8_t *ctx, wifi8_cred_store_option_t enu_cred_store_option, wifi8_network_id_t *pstr_network_id, wifi8_auth_psk_t *pstr_auth_psk)
{
    err_t ret = WIFI8_ERROR;

    if (pstr_auth_psk != NULL)
    {
        wifi8_m2m_wifi_conn_hdr_t str_conn_hdr;

        ret = m2m_wifi_connect_prepare_msg(enu_cred_store_option,
                                           M2M_WIFI_SEC_WPA_PSK,
                                           sizeof(wifi8_m2m_wifi_psk_t),
                                           pstr_network_id,
                                           &str_conn_hdr);

        if (ret == WIFI8_OK)
        {
            static uint8_t pstr_psk_buf[sizeof(wifi8_m2m_wifi_psk_t)];
            wifi8_m2m_wifi_psk_t *pstr_psk = (wifi8_m2m_wifi_psk_t *)pstr_psk_buf;
            if (pstr_psk == NULL)
            {
                ret = WIFI8_ERROR;
            }
            else
            {
                memset((uint8_t *)pstr_psk, 0, sizeof(wifi8_m2m_wifi_psk_t));
                if (pstr_auth_psk->pu8_psk != NULL)
                {
                    if (pstr_auth_psk->pu8_passphrase != NULL)
                    {
                        ret = WIFI8_ERROR;
                    }
                    else
                    {
                        pstr_psk->u8_passphrase_len = M2M_MAX_PSK_LEN - 1;
                        /* Use hexstr_2_bytes to verify pu8Psk input. */
                        if (WIFI8_OK != hexstr_2_bytes(pstr_psk->au8_passphrase, pstr_auth_psk->pu8_psk, pstr_psk->u8_passphrase_len / 2))
                        {
                            ret = WIFI8_ERROR;
                        }
                        memcpy(pstr_psk->au8_passphrase, pstr_auth_psk->pu8_psk, pstr_psk->u8_passphrase_len);
                    }
                }
                else if (pstr_auth_psk->pu8_passphrase != NULL)
                {
                    if (pstr_auth_psk->u8_passphrase_len > M2M_MAX_PSK_LEN - 1)
                    {
                        ret = WIFI8_ERROR;
                    }
                    else
                    {
                        pstr_psk->u8_passphrase_len = pstr_auth_psk->u8_passphrase_len;
                        memcpy(pstr_psk->au8_passphrase, pstr_auth_psk->pu8_passphrase, pstr_psk->u8_passphrase_len);
                    }
                }
                else
                    ret = WIFI8_ERROR;
                if (ret == WIFI8_OK)
                {
                    ret = hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_CONN | M2M_REQ_DATA_PKT,
                                   (uint8_t *)&str_conn_hdr, sizeof(wifi8_m2m_wifi_conn_hdr_t),
                                   (uint8_t *)pstr_psk, sizeof(wifi8_m2m_wifi_psk_t), sizeof(wifi8_m2m_wifi_conn_hdr_t));
                }
                pstr_psk = NULL;
                memset(pstr_psk_buf, 0, sizeof(wifi8_m2m_wifi_psk_t));
            }
            if (ret != WIFI8_OK)
            {
                /* Might just be that we are talking to legacy firmware - try the legacy connect message instead. */
                wifi8_m2m_wifi_connect_legacy_1_2_t str_connect_legacy;
                ret = legacy_connect_prepare_msg(&str_conn_hdr, &str_connect_legacy);
                if (ret == WIFI8_OK)
                {
                    uint8_t *pu8_psk_legacy = str_connect_legacy.str_sec.uni_auth.au8psk;
                    memcpy(pu8_psk_legacy, pstr_psk->au8_passphrase, pstr_psk->u8_passphrase_len);
                    ret = hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_CONNECT,
                                   (uint8_t *)&str_connect_legacy, sizeof(wifi8_m2m_wifi_connect_legacy_1_2_t),
                                   NULL , 0, 0);
                }
            }
        }
    }
    return ret;
}

static err_t m2m_wifi_connect_wep(wifi8_t *ctx,
                                  wifi8_cred_store_option_t enu_cred_store_option,
                                  wifi8_network_id_t *pstr_network_id,
                                  wifi8_auth_wep_t *pstr_auth_wep)
{
    err_t ret = WIFI8_ERROR;

    if ((pstr_auth_wep != NULL) && (pstr_auth_wep->pu8_wep_key != NULL) && 
        (pstr_auth_wep->u8_key_indx > 0) &&
        (pstr_auth_wep->u8_key_indx <= WEP_KEY_MAX_INDEX) && 
        ((pstr_auth_wep->u8_key_sz == WEP_104_KEY_STRING_SIZE) || (pstr_auth_wep->u8_key_sz == WEP_40_KEY_STRING_SIZE)))
    {
        wifi8_m2m_wifi_conn_hdr_t str_conn_hdr;

        ret = m2m_wifi_connect_prepare_msg(enu_cred_store_option,
                                           M2M_WIFI_SEC_WEP,
                                           sizeof(wifi8_m2m_wifi_wep_t),
                                           pstr_network_id,
                                           &str_conn_hdr);

        if (ret == WIFI8_OK)
        {
            static uint8_t pstr_wep_buf[sizeof(wifi8_m2m_wifi_wep_t)] = {0};
            wifi8_m2m_wifi_wep_t *pstr_wep = (wifi8_m2m_wifi_wep_t *)pstr_wep_buf;
            if (pstr_wep == NULL)
            {
                ret = WIFI8_ERROR;
            }
            else
            {
                pstr_wep->u8_key_index = pstr_auth_wep->u8_key_indx - 1;
                pstr_wep->u8_key_len = pstr_auth_wep->u8_key_sz / 2;
                hexstr_2_bytes(pstr_wep->au8_wep_key, (pstr_auth_wep->pu8_wep_key), pstr_wep->u8_key_len);

                ret = hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_CONN | M2M_REQ_DATA_PKT,
                               (uint8_t *)&str_conn_hdr, sizeof(wifi8_m2m_wifi_conn_hdr_t),
                               (uint8_t *)pstr_wep, sizeof(wifi8_m2m_wifi_wep_t), sizeof(wifi8_m2m_wifi_conn_hdr_t));
                memset(pstr_wep_buf, 0, sizeof(wifi8_m2m_wifi_wep_t));
            }
            if (ret != WIFI8_OK)
            {
                /* Might just be that we are talking to legacy firmware - try the legacy connect message instead. */
                wifi8_m2m_wifi_connect_legacy_1_2_t str_connect_legacy;
                ret = legacy_connect_prepare_msg(&str_conn_hdr, &str_connect_legacy);
                if (ret == WIFI8_OK)
                {
                    wifi8_m2m_wifi_wep_params_legacy_1_2_t *pstr_wep_legacy = &str_connect_legacy.str_sec.uni_auth.str_wep_info;
                    pstr_wep_legacy->u8_key_indx = pstr_auth_wep->u8_key_indx - 1;
                    pstr_wep_legacy->u8_key_sz = pstr_auth_wep->u8_key_sz;
                    memcpy(pstr_wep_legacy->au8_wep_key, pstr_auth_wep->pu8_wep_key, pstr_auth_wep->u8_key_sz);
                    ret = hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_CONNECT,
                                   (uint8_t *)&str_connect_legacy, sizeof(wifi8_m2m_wifi_connect_legacy_1_2_t),
                                   NULL, 0, 0);
                }
            }
        }
    }
    return ret;
}

static err_t m2m_wifi_connect_open(wifi8_t *ctx, wifi8_cred_store_option_t enu_cred_store_option, wifi8_network_id_t *pstr_network_id)
{
    err_t ret = WIFI8_ERROR;
    wifi8_m2m_wifi_conn_hdr_t str_conn_hdr;

    ret = m2m_wifi_connect_prepare_msg(enu_cred_store_option, M2M_WIFI_SEC_OPEN, 0, pstr_network_id, &str_conn_hdr);
    if (ret == WIFI8_OK)
    {
        ret = hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_CONN,
                       (uint8_t *)&str_conn_hdr, sizeof(str_conn_hdr),
                       NULL, 0, 0);
        if (ret != WIFI8_OK)
        {
            /* Might just be that we are talking to legacy firmware - try the legacy connect message instead. */
            wifi8_m2m_wifi_connect_legacy_1_2_t str_connect_legacy;
            ret = legacy_connect_prepare_msg(&str_conn_hdr, &str_connect_legacy);
            if (ret == WIFI8_OK)
            {
                ret = hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_CONNECT,
                               (uint8_t *)&str_connect_legacy, sizeof(wifi8_m2m_wifi_connect_legacy_1_2_t),
                               NULL, 0, 0);
            }
        }
    }
    return ret;
}

static err_t legacy_connect_prepare_msg(wifi8_m2m_wifi_conn_hdr_t *pstr_conn_hdr, wifi8_m2m_wifi_connect_legacy_1_2_t *pstr_connect)
{
    err_t s8_ret = WIFI8_ERROR;

    if (!(pstr_conn_hdr->str_conn_cred_hdr.u8_cred_store_flags & M2M_CRED_ENCRYPT_FLAG) && 
        !(pstr_conn_hdr->str_conn_cred_cmn.u8_options & M2M_WIFI_CONN_BSSID_FLAG))
    {
        memset((uint8_t *)pstr_connect, 0, sizeof(wifi8_m2m_wifi_connect_legacy_1_2_t));
        memcpy(pstr_connect->au8ssid, pstr_conn_hdr->str_conn_cred_cmn.au8_ssid, pstr_conn_hdr->str_conn_cred_cmn.u8_ssid_len);
        pstr_connect->au8ssid[pstr_conn_hdr->str_conn_cred_cmn.u8_ssid_len] = 0;
        pstr_connect->u16_ch = pstr_conn_hdr->str_conn_cred_hdr.u8_channel;
        pstr_connect->u8_no_save_cred = !(pstr_conn_hdr->str_conn_cred_hdr.u8_cred_store_flags & M2M_CRED_STORE_FLAG);
        pstr_connect->str_sec.u8_sec_type = pstr_conn_hdr->str_conn_cred_cmn.u8_auth_type;
        s8_ret = WIFI8_OK;
    }
    return s8_ret;
}

static err_t m2m_wifi_connect_prepare_msg(wifi8_cred_store_option_t enu_cred_store_option, wifi8_m2m_sec_type_t enu_auth_type,
                                          uint16_t u16_auth_size, wifi8_network_id_t *pstr_network_id, wifi8_m2m_wifi_conn_hdr_t *pstr_wifi_conn)
{
    err_t ret = WIFI8_ERROR;
    uint16_t u16_cred_size = sizeof(wifi8_m2m_conn_cred_cmn_t) + u16_auth_size;
    /* Check application params. */
    if ((pstr_network_id == NULL) ||
        (pstr_network_id->pu8_ssid == NULL) ||
        (pstr_network_id->u8_ssid_len >= M2M_MAX_SSID_LEN))
    {
        return WIFI8_ERROR;
    }

    if (pstr_wifi_conn != NULL)
    {
        wifi8_m2m_conn_cred_hdr_t *pstr_hdr = &pstr_wifi_conn->str_conn_cred_hdr;
        wifi8_m2m_conn_cred_cmn_t *pstr_cmn = &pstr_wifi_conn->str_conn_cred_cmn;

        memset((uint8_t *)pstr_wifi_conn, 0, sizeof(wifi8_m2m_wifi_conn_hdr_t));

        pstr_hdr->u16_cred_size = u16_cred_size;
        switch (enu_cred_store_option)
        {
            case WIFI_CRED_SAVE_ENCRYPTED:
                pstr_hdr->u8_cred_store_flags |= M2M_CRED_ENCRYPT_FLAG;
            // intentional fall through...
            case WIFI_CRED_SAVE_UNENCRYPTED:
                pstr_hdr->u8_cred_store_flags |= M2M_CRED_STORE_FLAG;
            // intentional fall through...
            case WIFI_CRED_DONTSAVE:
                break;
            default:
                return WIFI8_ERROR;
        }

        if (pstr_network_id->enu_channel == M2M_WIFI_CH_ALL)
        {
            pstr_hdr->u8_channel = (uint8_t)(pstr_network_id->enu_channel);
        }
        else if ((pstr_network_id->enu_channel <= M2M_WIFI_CH_14) && (pstr_network_id->enu_channel >= M2M_WIFI_CH_1))
        {
            pstr_hdr->u8_channel = (uint8_t)(pstr_network_id->enu_channel) - 1;
        }
        else
        {
            return WIFI8_ERROR;
        }

        if ((enu_auth_type == M2M_WIFI_SEC_INVALID) || (enu_auth_type >= M2M_WIFI_NUM_AUTH_TYPES))
        {
            return WIFI8_ERROR;
        }

        pstr_cmn->u8_auth_type = (uint8_t)enu_auth_type;

        pstr_cmn->u8_ssid_len = pstr_network_id->u8_ssid_len;
        memcpy(pstr_cmn->au8_ssid, pstr_network_id->pu8_ssid, pstr_network_id->u8_ssid_len);
        if (pstr_network_id->pu8_bssid != NULL)
        {
            pstr_cmn->u8_options = M2M_WIFI_CONN_BSSID_FLAG;
            memcpy(pstr_cmn->au8_bssid, pstr_network_id->pu8_bssid, M2M_MAC_ADDRES_LEN);
        }
        /* Everything is ok, set return value. */
        ret = WIFI8_OK;
    }
    return ret;
}

static uint8_t *macAddress(wifi8_t *ctx, uint8_t *mac)
{
    m2m_wifi_get_mac_address(ctx, mac);
    uint8_t tmp_mac[6], i;

    m2m_wifi_get_mac_address(ctx, tmp_mac);

    for (i = 0; i < 6; i++)
    {
        mac[i] = tmp_mac[5 - i];
    }

    return mac;
}

static err_t m2m_wifi_get_mac_address(wifi8_t *ctx, uint8_t *pu8_mac_addr)
{
    err_t ret = WIFI8_OK;
    if (WIFI8_OK == chip_wake(ctx))
    {
        ret = nmi_get_mac_address(ctx, pu8_mac_addr);
        chip_sleep(ctx);
    }

    return ret;
}

static err_t nmi_get_mac_address(wifi8_t *ctx, uint8_t *pu8_mac_addr)
{
    uint32_t u32_reg_value;
    uint8_t mac[6];
    wifi8_gp_regs_t strgp = {0};

    if (WIFI8_OK != wifi8_reg_read(ctx, rNMI_GP_REG_0, &u32_reg_value))
    {
        return WIFI8_ERROR;
    }
    if (WIFI8_OK != wifi8_block_read(ctx, u32_reg_value | 0x30000ul, (uint8_t *)&strgp, sizeof(wifi8_gp_regs_t)))
    {
        return WIFI8_ERROR;
    }

    u32_reg_value = strgp.u32_mac_efuse_mib;

    u32_reg_value &= 0x0000fffful;
    err_t ret = nm_read_block(ctx, u32_reg_value | 0x30000ul, mac, 6);
    memcpy(pu8_mac_addr, mac, 6);

    return ret;
}

static err_t m2m_wifi_start_provision_mode(wifi8_t *ctx, wifi8_m2m_ap_config_t *pstr_m2map_config, char *pc_http_server_domain_name, uint8_t b_enable_http_redirect)
{
    wifi8_m2m_ap_mode_config_t str_m2map_mode_config;

    memcpy((uint8_t *)&str_m2map_mode_config.str_ap_config, (uint8_t *)pstr_m2map_config, sizeof(wifi8_m2m_ap_config_t));

    memcpy(str_m2map_mode_config.str_ap_config_ext.au8_def_router_ip, pstr_m2map_config->au8dhcp_server_ip, 4);
    memcpy(str_m2map_mode_config.str_ap_config_ext.au8dns_server_ip, pstr_m2map_config->au8dhcp_server_ip, 4);
    str_m2map_mode_config.str_ap_config_ext.au8_subnet_mask[0] = 0;

    return m2m_wifi_start_provision_mode_ext(ctx, &str_m2map_mode_config, pc_http_server_domain_name, b_enable_http_redirect);
}

static err_t m2m_wifi_start_provision_mode_ext(wifi8_t *ctx, wifi8_m2m_ap_mode_config_t *pstr_ap_mode_config, char *pc_http_server_domain_name, uint8_t b_enable_http_redirect)
{
    err_t s8_ret = WIFI8_ERROR;

    if ((pstr_ap_mode_config != NULL))
    {
        wifi8_m2m_provision_mode_config_t str_prov_config;
        if (WIFI8_OK == m2m_validate_ap_parameters(pstr_ap_mode_config))
        {
            memcpy((uint8_t *)&str_prov_config.str_ap_config, (uint8_t *)&pstr_ap_mode_config->str_ap_config, sizeof(wifi8_m2m_ap_config_t));
            memcpy((uint8_t *)&str_prov_config.str_ap_config_ext, (uint8_t *)&pstr_ap_mode_config->str_ap_config_ext, sizeof(wifi8_m2m_ap_config_ext_t));
            if ((strlen((uint8_t *)pc_http_server_domain_name) <= 0) || (NULL == pc_http_server_domain_name))
            {
                return WIFI8_ERROR;
            }
            memcpy((uint8_t *)str_prov_config.ac_http_server_domain_name, (uint8_t *)pc_http_server_domain_name, 64);
            str_prov_config.u8_enable_redirect = b_enable_http_redirect;

            s8_ret = hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_START_PROVISION_MODE | M2M_REQ_DATA_PKT,
                             (uint8_t *)&str_prov_config, sizeof(wifi8_m2m_provision_mode_config_t), NULL, 0, 0);

            if (s8_ret == WIFI8_ERROR)
            {
                // Send again using legacy HIF message. We can use the same structure here as
                // the firmware only uses to the HIF message to determine whether or not the
                // structure contains a tstrM2MAPConfigExt structure.
                s8_ret = hif_send(ctx,
                                 M2M_REQ_GROUP_WIFI,
                                 M2M_WIFI_REQ_START_PROVISION_MODE_LEGACY | M2M_REQ_DATA_PKT,
                                 (uint8_t *)&str_prov_config,
                                 sizeof(wifi8_m2m_provision_mode_config_t),
                                 NULL,
                                 0,
                                 0);
            }
        }
    }

    return s8_ret;
}

static err_t m2m_wifi_enable_ap(wifi8_t *ctx, wifi8_m2m_ap_config_t *pstr_m2map_config)
{
    wifi8_m2m_ap_mode_config_t str_m2map_mode_config;

    memcpy((uint8_t *)&str_m2map_mode_config.str_ap_config, (uint8_t *)pstr_m2map_config, sizeof(wifi8_m2m_ap_config_t));

    memcpy(str_m2map_mode_config.str_ap_config_ext.au8_def_router_ip, (uint8_t *)pstr_m2map_config->au8dhcp_server_ip, 4);
    memcpy(str_m2map_mode_config.str_ap_config_ext.au8dns_server_ip, (uint8_t *)pstr_m2map_config->au8dhcp_server_ip, 4);
    str_m2map_mode_config.str_ap_config_ext.au8_subnet_mask[0] = 0;

    return m2m_wifi_enable_ap_ext(ctx, &str_m2map_mode_config);
}

static err_t m2m_wifi_enable_ap_ext(wifi8_t *ctx, wifi8_m2m_ap_mode_config_t *pstr_m2map_mode_config)
{
    if (WIFI8_OK == m2m_validate_ap_parameters(pstr_m2map_mode_config))
    {
        if (WIFI8_ERROR == hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_ENABLE_AP,
                                    (uint8_t *)pstr_m2map_mode_config, sizeof(wifi8_m2m_ap_mode_config_t), NULL, 0, 0))
        {
            // Send again using legacy HIF message.
            return hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_ENABLE_AP_LEGACY,
                            (uint8_t *)&pstr_m2map_mode_config->str_ap_config, sizeof(wifi8_m2m_ap_config_t), NULL, 0, 0);
        }
        else
        {
            return WIFI8_OK;
        }
    }
    else
    {
        return WIFI8_ERROR;
    }
}

static err_t m2m_validate_ap_parameters(wifi8_m2m_ap_mode_config_t *pstr_m2map_mode_config)
{
    /* Check for incoming pointer */
    if (pstr_m2map_mode_config == NULL)
    {
        return WIFI8_ERROR;
    }
    /* Check for SSID */
    if ((strlen((uint8_t *)pstr_m2map_mode_config->str_ap_config.au8ssid) <= 0) ||
        (strlen((uint8_t *)pstr_m2map_mode_config->str_ap_config.au8ssid) >= M2M_MAX_SSID_LEN))
    {
        return WIFI8_ERROR;
    }
    /* Check for Channel */
    if (pstr_m2map_mode_config->str_ap_config.u8_listen_channel > M2M_WIFI_CH_14 ||
        pstr_m2map_mode_config->str_ap_config.u8_listen_channel < M2M_WIFI_CH_1)
    {
        return WIFI8_ERROR;
    }
    /* Check for DHCP Server IP address */
    if (!(pstr_m2map_mode_config->str_ap_config.au8dhcp_server_ip[0] ||
          pstr_m2map_mode_config->str_ap_config.au8dhcp_server_ip[1]))
    {
        if (!(pstr_m2map_mode_config->str_ap_config.au8dhcp_server_ip[2]))
        {
            return WIFI8_ERROR;
        }
    }
    /* Check for Security */
    if (pstr_m2map_mode_config->str_ap_config.u8_sec_type == M2M_WIFI_SEC_OPEN)
    {
        return WIFI8_OK;
    }
    else if (pstr_m2map_mode_config->str_ap_config.u8_sec_type == M2M_WIFI_SEC_WEP)
    {
        /* Check for WEP Key index */
        if ((pstr_m2map_mode_config->str_ap_config.u8_key_indx == 0) ||
            (pstr_m2map_mode_config->str_ap_config.u8_key_indx > WEP_KEY_MAX_INDEX))
        {
            return WIFI8_ERROR;
        }
        /* Check for WEP Key buf_len */
        if ((pstr_m2map_mode_config->str_ap_config.u8_key_sz != WEP_40_KEY_STRING_SIZE) &&
            (pstr_m2map_mode_config->str_ap_config.u8_key_sz != WEP_104_KEY_STRING_SIZE))
        {
            return WIFI8_ERROR;
        }
        /* Check for WEP Key */
        if ((pstr_m2map_mode_config->str_ap_config.au8_wep_key == NULL) ||
            (strlen((uint8_t *)pstr_m2map_mode_config->str_ap_config.au8_wep_key) <= 0) ||
            (strlen((uint8_t *)pstr_m2map_mode_config->str_ap_config.au8_wep_key) > WEP_104_KEY_STRING_SIZE))
        {
            return WIFI8_ERROR;
        }
    }
    else
    {
        return WIFI8_ERROR;
    }

    return WIFI8_OK;
}

uint8_t m2m_wifi_get_state(wifi8_t *ctx)
{
    switch (ctx->device_state)
    {
        case NM_STATE_DEINIT:
            return WIFI_STATE_DEINIT;
        case NM_STATE_INIT:
            return WIFI_STATE_INIT;
        case NM_STATE_START:
            return WIFI_STATE_START;
    }
    return WIFI_STATE_DEINIT;
}

static err_t m2m_wifi_handle_events(wifi8_t *ctx)
{
    err_t ret = WIFI8_OK;

    if (WIFI_STATE_START == m2m_wifi_get_state(ctx))
    {
        ret = hif_handle_isr(ctx);
    }

    return ret;
}

static err_t m2m_wifi_1x_set_option(wifi8_t *ctx, wifi8_1x_option_t enu_option_name, void *p_option_value, size_t option_len)
{
    if ((p_option_value == NULL) && (option_len > 0))
    {
        return WIFI8_ERROR;
    }
    switch (enu_option_name)
    {
        case WIFI_1X_BYPASS_SERVER_AUTH:
            if (option_len != sizeof(int))
            {
                return WIFI8_ERROR;
            }
            switch (*(int *)p_option_value)
            {
                case 1:
                    ctx->hs_flags &= ~WIFI_1X_TLS_HS_FLAGS_PEER_AUTH;
                    break;
                case 0:
                    ctx->hs_flags |= WIFI_1X_TLS_HS_FLAGS_PEER_AUTH;
                    break;
                default:
                    return WIFI8_ERROR;
            }
            break;
        case WIFI_1X_TIME_VERIF_MODE:
            if (option_len != sizeof(wifi8_tls_cert_exp_settings_t))
            {
                return WIFI8_ERROR;
            }
            switch (*(wifi8_tls_cert_exp_settings_t *)p_option_value)
            {
                case TLS_CERT_EXP_CHECK_DISABLE:
                    ctx->hs_flags &= ~WIFI_1X_TLS_HS_FLAGS_PEER_CERTTIMECHECK;
                    ctx->hs_flags &= ~WIFI_1X_TLS_HS_FLAGS_REQUIRE_TIME;
                    break;
                case TLS_CERT_EXP_CHECK_ENABLE:
                    ctx->hs_flags |= WIFI_1X_TLS_HS_FLAGS_PEER_CERTTIMECHECK;
                    ctx->hs_flags |= WIFI_1X_TLS_HS_FLAGS_REQUIRE_TIME;
                    break;
                case TLS_CERT_EXP_CHECK_EN_IF_SYS_TIME:
                    ctx->hs_flags |= WIFI_1X_TLS_HS_FLAGS_PEER_CERTTIMECHECK;
                    ctx->hs_flags &= ~WIFI_1X_TLS_HS_FLAGS_REQUIRE_TIME;
                    break;
                default:
                    return WIFI8_ERROR;
            }
        case WIFI_1X_SESSION_CACHING:
            if (option_len != sizeof(int))
            {
                return WIFI8_ERROR;
            }
            switch (*(int *)p_option_value)
            {
                case 1:
                    ctx->hs_flags |= WIFI_1X_TLS_HS_FLAGS_SESSION_CACHING;
                    break;
                case 0:
                    ctx->hs_flags &= ~WIFI_1X_TLS_HS_FLAGS_SESSION_CACHING;
                    break;
                default:
                    return WIFI8_ERROR;
            }
        case WIFI_1X_SPECIFIC_ROOTCERT:
            switch (option_len)
            {
                case 20:
                    ctx->hs_flags |= WIFI_1X_TLS_HS_FLAGS_SPECIFY_ROOTCERT;
                    memcpy(ctx->root_sha1, (uint8_t *)p_option_value, sizeof(ctx->root_sha1));
                    break;
                case 0:
                    ctx->hs_flags &= ~WIFI_1X_TLS_HS_FLAGS_SPECIFY_ROOTCERT;
                    memset(ctx->root_sha1, 0, sizeof(ctx->root_sha1));
                default:
                    return WIFI8_ERROR;
            }
            break;
        default:
            return WIFI8_ERROR;
    }
    return WIFI8_OK;
}

static err_t m2m_wifi_connect_1x_mschap2(wifi8_t *ctx, wifi8_cred_store_option_t enu_cred_store_option, wifi8_network_id_t *pstr_network_id, wifi8_auth1x_mschap2_t *pstr_auth1x_mschap2)
{
    volatile err_t ret = WIFI8_ERROR;
    if (pstr_auth1x_mschap2 != NULL)
    {
        if (pstr_auth1x_mschap2->pu8_domain == NULL)
        {
            pstr_auth1x_mschap2->u16_domain_len = 0;
        }
        if ((pstr_auth1x_mschap2->pu8_user_name != NULL) && (pstr_auth1x_mschap2->pu8_password != NULL) && 
            ((uint32_t)(pstr_auth1x_mschap2->u16_domain_len) + pstr_auth1x_mschap2->u16_user_name_len <= M2M_AUTH_1X_USER_LEN_MAX) && 
            (pstr_auth1x_mschap2->u16_password_len <= M2M_AUTH_1X_PASSWORD_LEN_MAX))
        {
            wifi8_m2m_wifi_conn_hdr_t str_conn_hdr;
            uint16_t u16_auth_size = sizeof(wifi8_m2m_wifi1x_hdr_t) +
                                   pstr_auth1x_mschap2->u16_domain_len +
                                   pstr_auth1x_mschap2->u16_user_name_len +
                                   pstr_auth1x_mschap2->u16_password_len;

            ret = m2m_wifi_connect_prepare_msg(enu_cred_store_option,
                                               M2M_WIFI_SEC_802_1X,
                                               u16_auth_size,
                                               pstr_network_id,
                                               &str_conn_hdr);

            if (ret == WIFI8_OK)
            {
                static uint8_t pstr1x_hdr_buf[sizeof(wifi8_m2m_wifi1x_hdr_t)] = {0};
                wifi8_m2m_wifi1x_hdr_t *pstr1x_hdr = (wifi8_m2m_wifi1x_hdr_t *)pstr1x_hdr_buf;
                if (pstr1x_hdr != NULL)
                {
                    uint8_t *pu8_auth_ptr = pstr1x_hdr->au81x_auth_details;
                    memset((uint8_t *)pstr1x_hdr, 0, u16_auth_size);

                    pstr1x_hdr->u8_flags = M2M_802_1X_MSCHAP2_FLAG;
                    if (pstr_auth1x_mschap2->b_unencrypted_user_name == true)
                    {
                        pstr1x_hdr->u8_flags |= M2M_802_1X_UNENCRYPTED_USERNAME_FLAG;
                    }
                    if (pstr_auth1x_mschap2->b_prepend_domain == true)
                    {
                        pstr1x_hdr->u8_flags |= M2M_802_1X_PREPEND_DOMAIN_FLAG;
                    }

                    pstr1x_hdr->u8_hdr_length = sizeof(wifi8_m2m_wifi1x_hdr_t);
                    pstr1x_hdr->u32_tls_hs_flags = ctx->hs_flags;
                    memcpy(pstr1x_hdr->au8_tls_specific_root_name_sha1, ctx->root_sha1, sizeof(ctx->root_sha1));

                    pstr1x_hdr->u8_domain_length = 0;
                    if (pstr_auth1x_mschap2->pu8_domain != NULL)
                    {
                        pstr1x_hdr->u8_domain_length = (uint8_t)(pstr_auth1x_mschap2->u16_domain_len);
                        memcpy(pu8_auth_ptr, pstr_auth1x_mschap2->pu8_domain, pstr1x_hdr->u8_domain_length);
                        pu8_auth_ptr += pstr1x_hdr->u8_domain_length;
                    }

                    pstr1x_hdr->u8_user_name_length = (pstr_auth1x_mschap2->u16_user_name_len);
                    memcpy(pu8_auth_ptr, pstr_auth1x_mschap2->pu8_user_name, pstr1x_hdr->u8_user_name_length);
                    pu8_auth_ptr += pstr1x_hdr->u8_user_name_length;

                    pstr1x_hdr->u16_private_key_offset = pu8_auth_ptr - pstr1x_hdr->au81x_auth_details;
                    pstr1x_hdr->u16_private_key_length = pstr_auth1x_mschap2->u16_password_len;
                    memcpy(pu8_auth_ptr, pstr_auth1x_mschap2->pu8_password, pstr1x_hdr->u16_private_key_length);

                    ret = hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_CONN | M2M_REQ_DATA_PKT,
                                   (uint8_t *)&str_conn_hdr, sizeof(wifi8_m2m_wifi_conn_hdr_t),
                                   (uint8_t *)pstr1x_hdr, u16_auth_size,
                                   sizeof(wifi8_m2m_wifi_conn_hdr_t));
                    pstr1x_hdr = NULL;
                }
            }
        }
    }
    return ret;
}

static err_t m2m_wifi_req_scan_result(wifi8_t *ctx, uint8_t scan_request_index)
{
    wifi8_m2m_req_scan_result_t str_req_scan_rlt;
    str_req_scan_rlt.u8_index = scan_request_index;
    return hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_SCAN_RESULT, (uint8_t *)&str_req_scan_rlt, sizeof(wifi8_m2m_req_scan_result_t), NULL, 0, 0);
}

static err_t m2m_wifi_request_scan(wifi8_t *ctx, uint8_t ch)
{
    if (((ch >= M2M_WIFI_CH_1) && (ch <= M2M_WIFI_CH_14)) || (ch == M2M_WIFI_CH_ALL))
    {
        wifi8_m2m_scan_t strtmp;
        strtmp.u8_ch_num = ch;
        return hif_send(ctx, M2M_REQ_GROUP_WIFI, M2M_WIFI_REQ_SCAN, (uint8_t *)&strtmp, sizeof(wifi8_m2m_scan_t), NULL, 0, 0);
    }
    else
    {
        return WIFI8_ERROR;
    }
}

static err_t nm_read_block(wifi8_t *ctx, uint32_t u32_addr, uint8_t *pu_buf, uint32_t u32_sz)
{
    uint16_t u16_max_trx_sz = egstr_nm_bus_capabilities.u16_max_trx_sz - MAX_TRX_CFG_SZ;
    uint32_t off = 0;
    err_t s8_ret = WIFI8_OK;

    for (;;)
    {
        if (u32_sz <= u16_max_trx_sz)
        {
            s8_ret += wifi8_block_read(ctx, u32_addr, &pu_buf[off], (uint16_t)u32_sz);
        }
        else
        {
            s8_ret += wifi8_block_read(ctx, u32_addr, &pu_buf[off], u16_max_trx_sz);
            if (WIFI8_OK != s8_ret)
            {
                break;
            }
            u32_sz -= u16_max_trx_sz;
            off += u16_max_trx_sz;
            u32_addr += u16_max_trx_sz;
        }
    }

    return s8_ret;
}

static err_t nm_write_block(wifi8_t *ctx, uint32_t u32_addr, uint8_t *pu_buf, uint32_t u32_sz)
{
    uint16_t u16_max_trx_sz = egstr_nm_bus_capabilities.u16_max_trx_sz - MAX_TRX_CFG_SZ;
    uint32_t off = 0;
    err_t s8_ret = WIFI8_OK;

    for (;;)
    {
        if (u32_sz <= u16_max_trx_sz)
        {
            s8_ret += wifi8_block_write(ctx, u32_addr, &pu_buf[off], (uint16_t)u32_sz);
            break;
        }
        else
        {
            s8_ret += wifi8_block_write(ctx, u32_addr, &pu_buf[off], u16_max_trx_sz);
            if (WIFI8_OK != s8_ret)
            {
                break;
            }
            u32_sz -= u16_max_trx_sz;
            off += u16_max_trx_sz;
            u32_addr += u16_max_trx_sz;
        }
    }

    return s8_ret;
}

// ------------------------------------------------------------------------- END
