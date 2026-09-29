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
 * @file nfctag2.h
 * @brief This file contains API for NFC Tag 2 Click Driver.
 */

#ifndef NFCTAG2_H
#define NFCTAG2_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup nfctag2 NFC Tag 2 Click Driver
 * @brief API for configuring and manipulating NFC Tag 2 Click driver.
 * @{
 */

/**
 * @defgroup nfctag2_reg NFC Tag 2 Registers List
 * @brief List of registers of NFC Tag 2 Click driver.
 */

/**
 * @addtogroup nfctag2_reg
 * @{
 */

/**
 * @brief NFC Tag 2 memory block addresses.
 * @details I2C addresses of 16-byte memory blocks on NFC Tag 2 Click.
 */
#define NFCTAG2_BLOCK_SERIAL_NUMBER             0x00
#define NFCTAG2_BLOCK_USER_FIRST                0x01
#define NFCTAG2_BLOCK_USER_LAST                 0x37
#define NFCTAG2_BLOCK_DYNAMIC_LOCK              0x38
#define NFCTAG2_BLOCK_CONFIGURATION             0x3A
#define NFCTAG2_BLOCK_SRAM_FIRST                0xF8
#define NFCTAG2_BLOCK_SRAM_LAST                 0xFB
#define NFCTAG2_BLOCK_SESSION                   0xFE

/**
 * @brief NFC Tag 2 session register addresses.
 * @details Byte offsets within the session register block of NFC Tag 2 Click.
 */
#define NFCTAG2_REG_NC                          0x00
#define NFCTAG2_REG_LAST_NDEF_BLOCK             0x01
#define NFCTAG2_REG_SRAM_MIRROR_BLOCK           0x02
#define NFCTAG2_REG_WDT_LS                      0x03
#define NFCTAG2_REG_WDT_MS                      0x04
#define NFCTAG2_REG_I2C_CLOCK_STR               0x05
#define NFCTAG2_REG_NS                          0x06

/*! @} */ // nfctag2_reg

/**
 * @defgroup nfctag2_set NFC Tag 2 Registers Settings
 * @brief Settings for registers of NFC Tag 2 Click driver.
 */

/**
 * @addtogroup nfctag2_set
 * @{
 */

/**
 * @brief NFC Tag 2 control register settings.
 * @details Session control masks and field detection settings of NFC Tag 2 Click.
 */
#define NFCTAG2_NC_I2C_RESET                    0x80
#define NFCTAG2_NC_PASS_THROUGH                 0x40
#define NFCTAG2_NC_FD_OFF_MASK                  0x30
#define NFCTAG2_NC_FD_OFF_FIELD                 0x00
#define NFCTAG2_NC_FD_OFF_HALT                  0x10
#define NFCTAG2_NC_FD_OFF_NDEF_READ             0x20
#define NFCTAG2_NC_FD_OFF_DATA_TRANSFER         0x30
#define NFCTAG2_NC_FD_ON_MASK                   0x0C
#define NFCTAG2_NC_FD_ON_FIELD                  0x00
#define NFCTAG2_NC_FD_ON_START                  0x04
#define NFCTAG2_NC_FD_ON_SELECTED               0x08
#define NFCTAG2_NC_FD_ON_DATA_TRANSFER          0x0C
#define NFCTAG2_NC_SRAM_MIRROR                  0x02
#define NFCTAG2_NC_RF_WRITE_ENABLE              0x01
#define NFCTAG2_NC_DEFAULT                      0x01

/**
 * @brief NFC Tag 2 status register settings.
 * @details Session status masks of NFC Tag 2 Click. NDEF_DATA_READ clears when read.
 */
#define NFCTAG2_NS_NDEF_DATA_READ               0x80
#define NFCTAG2_NS_I2C_LOCKED                   0x40
#define NFCTAG2_NS_RF_LOCKED                    0x20
#define NFCTAG2_NS_SRAM_I2C_READY               0x10
#define NFCTAG2_NS_SRAM_RF_READY                0x08
#define NFCTAG2_NS_EEPROM_WRITE_ERROR           0x04
#define NFCTAG2_NS_EEPROM_WRITE_BUSY            0x02
#define NFCTAG2_NS_RF_FIELD_PRESENT             0x01

/**
 * @brief NFC Tag 2 default watchdog settings.
 * @details These NFC Tag 2 Click session values select the factory watchdog timeout of approximately 20 ms.
 */
#define NFCTAG2_WDT_LS_DEFAULT                  0x48
#define NFCTAG2_WDT_MS_DEFAULT                  0x08

/**
 * @brief NFC Tag 2 memory and NDEF record sizes.
 * @details Memory block, UID, and NDEF text and URI limits used by NFC Tag 2 Click driver.
 * Text overhead includes two TLV bytes, seven Text record bytes, and one terminator TLV byte.
 * URI overhead includes two TLV bytes, five URI record bytes, and one terminator TLV byte.
 */
#define NFCTAG2_BLOCK_SIZE                      16
#define NFCTAG2_UID_SIZE                        7
#define NFCTAG2_NDEF_TEXT_MAX_LENGTH            240
#define NFCTAG2_NDEF_TEXT_OVERHEAD              10
#define NFCTAG2_NDEF_URI_MAX_LENGTH             248
#define NFCTAG2_NDEF_URI_OVERHEAD               8
#define NFCTAG2_NDEF_BUFFER_SIZE                256

/**
 * @brief NFC Tag 2 NDEF text and URI record settings.
 * @details NFC Tag 2 Click writes short UTF-8 Text and URI records.
 */
#define NFCTAG2_NDEF_TLV                        0x03
#define NFCTAG2_NDEF_TERMINATOR                 0xFE
#define NFCTAG2_NDEF_RECORD_HEADER              0xD1
#define NFCTAG2_NDEF_TEXT_HEADER                NFCTAG2_NDEF_RECORD_HEADER
#define NFCTAG2_NDEF_TEXT_TYPE                  0x54
#define NFCTAG2_NDEF_URI_TYPE                   0x55
#define NFCTAG2_NDEF_URI_PREFIX_NONE            0x00

/**
 * @brief NFC Tag 2 field detection pin settings.
 * @details Active-low FD pin levels for NFC Tag 2 Click in the default field detection mode.
 */
#define NFCTAG2_FIELD_PRESENT                   0
#define NFCTAG2_FIELD_ABSENT                    1

/**
 * @brief NFC Tag 2 device address setting.
 * @details Specified setting for device slave address selection of
 * NFC Tag 2 Click driver.
 */
#define NFCTAG2_DEVICE_ADDRESS                  0x55

/*! @} */ // nfctag2_set

/**
 * @defgroup nfctag2_map NFC Tag 2 MikroBUS Map
 * @brief MikroBUS pin mapping of NFC Tag 2 Click driver.
 */

/**
 * @addtogroup nfctag2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NFC Tag 2 Click to the selected MikroBUS.
 */
#define NFCTAG2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.fd = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nfctag2_map
/*! @} */ // nfctag2

/**
 * @brief NFC Tag 2 Click context object.
 * @details Context object definition of NFC Tag 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t fd;            /**< Field detection pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} nfctag2_t;

/**
 * @brief NFC Tag 2 Click configuration object.
 * @details Configuration object definition of NFC Tag 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t fd;              /**< Field detection pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} nfctag2_cfg_t;

/**
 * @brief NFC Tag 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NFCTAG2_OK = 0,
    NFCTAG2_ERROR = -1

} nfctag2_return_value_t;

/**
 * @brief NFC Tag 2 NDEF write stages.
 * @details Stage reported by the NFC Tag 2 NDEF write functions when a transfer fails.
 */
typedef enum
{
    NFCTAG2_NDEF_STAGE_OK = 0,
    NFCTAG2_NDEF_STAGE_INVALID_TEXT,
    NFCTAG2_NDEF_STAGE_DATA_READ,
    NFCTAG2_NDEF_STAGE_BLOCK_WRITE,
    NFCTAG2_NDEF_STAGE_VERIFY_READ,
    NFCTAG2_NDEF_STAGE_VERIFY_COMPARE,
    NFCTAG2_NDEF_STAGE_LAST_BLOCK,
    NFCTAG2_NDEF_STAGE_RELEASE,
    NFCTAG2_NDEF_STAGE_INVALID_URI

} nfctag2_ndef_stage_t;

/*!
 * @addtogroup nfctag2 NFC Tag 2 Click Driver
 * @brief API for configuring and manipulating NFC Tag 2 Click driver.
 * @{
 */

/**
 * @brief NFC Tag 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nfctag2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nfctag2_cfg_setup ( nfctag2_cfg_t *cfg );

/**
 * @brief NFC Tag 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nfctag2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfctag2_init ( nfctag2_t *ctx, nfctag2_cfg_t *cfg );

/**
 * @brief NFC Tag 2 default configuration function.
 * @details This function configures NFC Tag 2 Click for EEPROM access, RF writes,
 * active-low RF field detection, and an approximately 20 ms I2C watchdog.
 * @param[in,out] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Only volatile session registers are changed. The settings follow the NC_REG
 * and watchdog defaults in NXP NT3H1101/1201 and NT3H2111/2211 datasheets, tables 13 and 14.
 * Pass-through, SRAM mirroring, and I2C soft reset are disabled. EEPROM is not modified.
 */
err_t nfctag2_default_cfg ( nfctag2_t *ctx );

/**
 * @brief NFC Tag 2 write register function.
 * @details This function writes one NFC Tag 2 Click session register using a full-byte mask.
 * @param[in] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[in] reg : Session register offset (0x00 to 0x06).
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Read-only bits are ignored by the device. Use nfctag2_update_reg to change selected bits.
 */
err_t nfctag2_write_reg ( nfctag2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief NFC Tag 2 write registers function.
 * @details This function writes consecutive NFC Tag 2 Click session registers using individual masked commands.
 * @param[in] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[in] reg : First session register offset (0x00 to 0x06).
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The range must not exceed offset 0x06. This function does not write EEPROM or SRAM blocks.
 */
err_t nfctag2_write_regs ( nfctag2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief NFC Tag 2 read register function.
 * @details This function reads one NFC Tag 2 Click session register using its block and byte addresses.
 * @param[in] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[in] reg : Session register offset (0x00 to 0x06).
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Reading NS_REG clears its NDEF_DATA_READ flag.
 */
err_t nfctag2_read_reg ( nfctag2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief NFC Tag 2 read registers function.
 * @details This function reads consecutive NFC Tag 2 Click session registers using individual read commands.
 * @param[in] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[in] reg : First session register offset (0x00 to 0x06).
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The range must not exceed offset 0x06. Reading NS_REG clears its NDEF_DATA_READ flag.
 */
err_t nfctag2_read_regs ( nfctag2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief NFC Tag 2 update register function.
 * @details This function updates selected bits of an NFC Tag 2 Click session register.
 * @param[in,out] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[in] reg : Session register offset (0x00 to 0x06).
 * @param[in] mask : Bits to update (1 selects a bit).
 * @param[in] data_in : New values for the selected bits.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note The hardware mask preserves unselected bits without a read-modify-write operation.
 */
err_t nfctag2_update_reg ( nfctag2_t *ctx, uint8_t reg, uint8_t mask, uint8_t data_in );

/**
 * @brief NFC Tag 2 read block function.
 * @details This function reads one complete 16-byte EEPROM or SRAM block from NFC Tag 2 Click.
 * @param[in,out] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[in] block : I2C block address (0x00 to 0x38, 0x3A, or 0xF8 to 0xFB).
 * @param[out] data_out : Output buffer of at least NFCTAG2_BLOCK_SIZE bytes.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note Call nfctag2_release_i2c after a memory access sequence to permit RF access.
 * I2C memory access may fail while the RF interface owns the memory.
 */
err_t nfctag2_read_block ( nfctag2_t *ctx, uint8_t block, uint8_t *data_out );

/**
 * @brief NFC Tag 2 write block function.
 * @details This function writes one complete 16-byte user EEPROM or SRAM block to NFC Tag 2 Click.
 * @param[in,out] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[in] block : I2C block address (0x01 to 0x37 or 0xF8 to 0xFB).
 * @param[in] data_in : Input buffer of at least NFCTAG2_BLOCK_SIZE bytes.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note Blocks containing the I2C address, lock bits, or permanent configuration are excluded.
 * EEPROM writes include a fixed 5 ms programming delay. Call nfctag2_release_i2c after the access sequence.
 */
err_t nfctag2_write_block ( nfctag2_t *ctx, uint8_t block, uint8_t *data_in );

/**
 * @brief NFC Tag 2 release I2C function.
 * @details This function clears the NFC Tag 2 Click I2C memory lock so the RF reader can access the tag.
 * @param[in,out] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t nfctag2_release_i2c ( nfctag2_t *ctx );

/**
 * @brief NFC Tag 2 get UID function.
 * @details This function reads the seven-byte NFC Tag 2 Click UID and releases I2C memory ownership.
 * @param[in,out] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[out] uid : Output buffer of at least NFCTAG2_UID_SIZE bytes.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note The UID occupies bytes 0 to 6 of block 0. The following SAK and ATQA bytes are excluded.
 */
err_t nfctag2_get_uid ( nfctag2_t *ctx, uint8_t *uid );

/**
 * @brief NFC Tag 2 write NDEF text function.
 * @details This function stores one short UTF-8 Text record in NFC Tag 2 Click user EEPROM
 * and verifies the stored data through I2C readback.
 * @param[in,out] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[in] text : Null-terminated UTF-8 text, up to NFCTAG2_NDEF_TEXT_MAX_LENGTH bytes excluding the terminator.
 * @param[out] stage : Failure stage for diagnostics, or NFCTAG2_NDEF_STAGE_OK on success. May be NULL.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note Replaces existing NDEF content from block 0x01 and uses language code "en".
 * Failure stages identify the operation that failed.
 * Requires default EEPROM mode. Writing does not depend on or initialize the capability container.
 * Success confirms user EEPROM storage; NFC readers still require a valid, readable Type 2 capability container.
 * Unchanged content is not rewritten. The length is published after verification, then I2C ownership is released.
 * Keep the RF reader away during programming. UID, capability container, lock bits, and configuration are preserved.
 */
err_t nfctag2_write_ndef_text ( nfctag2_t *ctx, char *text, nfctag2_ndef_stage_t *stage );

/**
 * @brief NFC Tag 2 write NDEF URI function.
 * @details This function stores a complete URI as an NDEF URI record in NFC Tag 2 Click user EEPROM
 * and verifies the stored data through I2C readback.
 * @param[in,out] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[in] uri : Null-terminated URI including its scheme, up to NFCTAG2_NDEF_URI_MAX_LENGTH bytes.
 * @param[out] stage : Failure stage for diagnostics, or NFCTAG2_NDEF_STAGE_OK on success. May be NULL.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note Uses URI prefix code 0, storing the complete URI without prefix compression.
 * Requires a valid Type 2 capability container for standard NFC reader support.
 * Writes user EEPROM only; the tag formatting, UID, capability container, lock bits, and configuration are unchanged.
 */
err_t nfctag2_write_ndef_uri ( nfctag2_t *ctx, char *uri, nfctag2_ndef_stage_t *stage );

/**
 * @brief NFC Tag 2 get field detection function.
 * @details This function reads the NFC Tag 2 Click active-low FD pin connected to mikroBUS INT.
 * @param[in,out] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @return @li @c 0 - RF field present,
 *         @li @c 1 - RF field absent.
 * @note These meanings apply to the default field detection mode. A field does not confirm a completed NDEF read.
 */
uint8_t nfctag2_get_field_detect ( nfctag2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // NFCTAG2_H

/*! @} */ // nfctag2

// ------------------------------------------------------------------------ END
