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
 * @file nfctag.h
 * @brief This file contains API for NFC Tag Click Driver.
 */

#ifndef NFCTAG_H
#define NFCTAG_H

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

/*!
 * @addtogroup nfctag NFC Tag Click Driver
 * @brief API for configuring and manipulating NFC Tag Click driver.
 * @{
 */

/**
 * @defgroup nfctag_reg NFC Tag File List
 * @brief File identifiers and offsets of NFC Tag Click driver.
 */

/**
 * @addtogroup nfctag_reg
 * @{
 */

/**
 * @brief NFC Tag file identifiers.
 * @details M24SR64-Y application files selected through the Select command.
 */
#define NFCTAG_FILE_SYSTEM                  0xE101u
#define NFCTAG_FILE_CC                      0xE103u
#define NFCTAG_FILE_NDEF                    0x0001u

/**
 * @brief NFC Tag system file offsets.
 * @details Byte offsets within the system file of NFC Tag Click.
 */
#define NFCTAG_SYSTEM_I2C_PROTECT           0x0002u
#define NFCTAG_SYSTEM_WATCHDOG              0x0003u
#define NFCTAG_SYSTEM_GPO                   0x0004u
#define NFCTAG_SYSTEM_RF_ENABLE             0x0006u
#define NFCTAG_SYSTEM_UID                   0x0008u

/*! @} */ // nfctag_reg

/**
 * @defgroup nfctag_set NFC Tag Settings
 * @brief Command, memory, and pin settings of NFC Tag Click driver.
 */

/**
 * @addtogroup nfctag_set
 * @{
 */

/**
 * @brief NFC Tag command settings.
 * @details M24SR64-Y I2C session and APDU instruction values.
 */
#define NFCTAG_CMD_GET_SESSION              0x26
#define NFCTAG_CMD_SELECT                   0xA4
#define NFCTAG_CMD_READ_BINARY              0xB0
#define NFCTAG_CMD_UPDATE_BINARY            0xD6
#define NFCTAG_CLA_STANDARD                 0x00
#define NFCTAG_CLA_EXTENDED                 0xA2

/**
 * @brief NFC Tag frame settings.
 * @details CRC-A, I-block, and waiting time extension settings.
 * Responses are read after a fixed 10 ms delay, repeated by the WTX multiplier.
 * At most eight WTX requests are accepted per command.
 */
#define NFCTAG_PCB_I_BLOCK                  0x02
#define NFCTAG_PCB_WTX                      0xF2
#define NFCTAG_BLOCK_INVALID                0xFF
#define NFCTAG_CRC_INITIAL                  0x6363u
#define NFCTAG_CRC_POLYNOMIAL               0x8408u
#define NFCTAG_CRC_SIZE                     2
#define NFCTAG_RESPONSE_OVERHEAD            5
#define NFCTAG_WTX_SIZE                     4
#define NFCTAG_WTX_MAX                      0x0B
#define NFCTAG_WTX_RETRIES                  8
#define NFCTAG_TRANSFER_MAX                 246
#define NFCTAG_FRAME_SIZE                   254

/**
 * @brief NFC Tag response status settings.
 * @details ReadBinary accepts SW1 = 0x90; SW2 is unspecified for successful reads.
 * Other implemented commands require status 0x9000.
 */
#define NFCTAG_STATUS_OK                    0x9000u
#define NFCTAG_STATUS_READ_OK               0x9000u
#define NFCTAG_STATUS_SW1_MASK              0xFF00u
#define NFCTAG_STATUS_SECURITY              0x6982u
#define NFCTAG_STATUS_FILE_NOT_FOUND        0x6A82u

/**
 * @brief NFC Tag memory and NDEF record sizes.
 * @details The 8192-byte Type 4 file includes a two-byte big-endian NLEN.
 * Record overhead excludes NLEN. Text uses UTF-8 with language code "en".
 */
#define NFCTAG_NDEF_FILE_SIZE               8192u
#define NFCTAG_NLEN_SIZE                    2
#define NFCTAG_UID_SIZE                     7
#define NFCTAG_CC_SIZE                      15
#define NFCTAG_CC_NDEF_TYPE                 0x04
#define NFCTAG_CC_TLV_LENGTH                0x06
#define NFCTAG_CC_ACCESS_FREE               0x00
#define NFCTAG_NDEF_TEXT_MAX_LENGTH         240
#define NFCTAG_NDEF_TEXT_OVERHEAD           7
#define NFCTAG_NDEF_URI_MAX_LENGTH          248
#define NFCTAG_NDEF_URI_OVERHEAD            5
#define NFCTAG_NDEF_BUFFER_SIZE             256

/**
 * @brief NFC Tag NDEF text and URI record settings.
 * @details Short, single-record NDEF messages without Type 2 TLV or terminator bytes.
 */
#define NFCTAG_NDEF_RECORD_HEADER           0xD1
#define NFCTAG_NDEF_TEXT_TYPE               0x54
#define NFCTAG_NDEF_URI_TYPE                0x55
#define NFCTAG_NDEF_URI_PREFIX_NONE         0x00

/**
 * @brief NFC Tag pin settings.
 * @details RF-DIS is active high. GPO is open drain and active low.
 * Factory GPO configuration 0x11 indicates an open RF or I2C session.
 */
#define NFCTAG_RF_ENABLE                    0
#define NFCTAG_RF_DISABLE                   1
#define NFCTAG_GPO_ACTIVE                   0
#define NFCTAG_GPO_INACTIVE                 1
#define NFCTAG_GPO_SESSION_OPEN             0x11

/**
 * @brief NFC Tag device address setting.
 * @details Seven-bit I2C address; wire address bytes are 0xAC and 0xAD.
 */
#define NFCTAG_DEVICE_ADDRESS               0x56

/*! @} */ // nfctag_set

/**
 * @defgroup nfctag_map NFC Tag MikroBUS Map
 * @brief MikroBUS pin mapping of NFC Tag Click driver.
 */

/**
 * @addtogroup nfctag_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NFC Tag Click to the selected MikroBUS.
 */
#define NFCTAG_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.dis = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gpo = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nfctag_map
/*! @} */ // nfctag

/**
 * @brief NFC Tag UID read stages.
 * @details Stage reported by the NFC Tag UID read function when an operation fails.
 */
typedef enum
{
    NFCTAG_UID_STAGE_OK = 0,
    NFCTAG_UID_STAGE_SESSION,
    NFCTAG_UID_STAGE_APPLICATION,
    NFCTAG_UID_STAGE_FILE,
    NFCTAG_UID_STAGE_READ,
    NFCTAG_UID_STAGE_RELEASE,
    NFCTAG_UID_STAGE_BUFFER

} nfctag_uid_stage_t;

/**
 * @brief NFC Tag Click context object.
 * @details Context object definition of NFC Tag Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t dis;          /**< RF disable pin (active high). */

    // Input pins
    digital_in_t gpo;           /**< Configurable GPO pin (active low). */

    // Software I2C
    digital_in_t scl_in;        /**< SCL input object for reading the bus level. */
    digital_in_t sda_in;        /**< SDA input object for reading the bus level. */
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional pin descriptor for I2C driver. */
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    // Protocol state
    uint8_t block_number;       /**< Next I-block number; 0xFF requires session release. */
    uint8_t session_active;     /**< I2C session acquired by this context: 0 or 1. */
    uint16_t last_status;       /**< Last valid SW1/SW2; zero if no status was received. */
    nfctag_uid_stage_t uid_stage; /**< Failed UID read stage, or NFCTAG_UID_STAGE_OK. */

} nfctag_t;

/**
 * @brief NFC Tag Click configuration object.
 * @details Configuration object definition of NFC Tag Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t dis;             /**< RF disable pin (active high). */
    pin_name_t gpo;             /**< Configurable GPO pin (active low). */

    uint8_t    i2c_address;     /**< Seven-bit I2C slave address. */

} nfctag_cfg_t;

/**
 * @brief NFC Tag Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NFCTAG_OK = 0,
    NFCTAG_ERROR = -1,          /**< Invalid argument, I2C/GPIO error, or verification mismatch. */
    NFCTAG_TIMEOUT = -2,        /**< SCL release or waiting time extension limit reached. */
    NFCTAG_CRC_ERROR = -3,      /**< Response CRC is invalid. */
    NFCTAG_RESPONSE_ERROR = -4, /**< Unexpected PCB, block number, WTX multiplier, or missing read payload. */
    NFCTAG_DEVICE_ERROR = -5    /**< Device rejected the command; inspect ctx->last_status. */

} nfctag_return_value_t;

/**
 * @brief NFC Tag NDEF write stages.
 * @details Stage reported by the NFC Tag NDEF write functions when an operation fails.
 */
typedef enum
{
    NFCTAG_NDEF_STAGE_OK = 0,
    NFCTAG_NDEF_STAGE_INVALID_TEXT,
    NFCTAG_NDEF_STAGE_DATA_READ,
    NFCTAG_NDEF_STAGE_BLOCK_WRITE,
    NFCTAG_NDEF_STAGE_VERIFY_READ,
    NFCTAG_NDEF_STAGE_VERIFY_COMPARE,
    NFCTAG_NDEF_STAGE_RELEASE,
    NFCTAG_NDEF_STAGE_INVALID_URI,
    NFCTAG_NDEF_STAGE_SESSION,
    NFCTAG_NDEF_STAGE_SELECT,
    NFCTAG_NDEF_STAGE_CAPABILITY

} nfctag_ndef_stage_t;

/*!
 * @addtogroup nfctag NFC Tag Click Driver
 * @brief API for configuring and manipulating NFC Tag Click driver.
 * @{
 */

/**
 * @brief NFC Tag configuration object setup function.
 * @details This function sets the default I2C address and marks all pins as unconnected.
 * @param[out] cfg : Click configuration structure.
 * See #nfctag_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note Map the pins before initializing the driver.
 */
void nfctag_cfg_setup ( nfctag_cfg_t *cfg );

/**
 * @brief NFC Tag initialization function.
 * @details This function initializes SCL and SDA for software I2C and configures RF-DIS and GPO.
 * @param[out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nfctag_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - GPIO initialization error.
 * See #err_t definition for detailed explanation.
 * @note Drives RF-DIS low to enable RF communication. Software I2C uses fixed 10 us delays
 * and switches SCL and SDA to input mode to let the board pull-ups raise the lines.
 * Use the SCL and SDA pins exclusively for this driver.
 */
err_t nfctag_init ( nfctag_t *ctx, nfctag_cfg_t *cfg );

/**
 * @brief NFC Tag default configuration function.
 * @details This function enables RF communication on NFC Tag Click, clears a stale I2C token,
 * and checks that the NDEF Tag Application can be selected.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c Negative - Error.
 * See #nfctag_return_value_t definition for detailed explanation.
 * @note Keep the NFC reader away during initialization. The driver attempts to release
 * the I2C session after selecting the application, even if selection fails.
 */
err_t nfctag_default_cfg ( nfctag_t *ctx );

/**
 * @brief NFC Tag get session function.
 * @details This function acquires an NFC Tag Click I2C session and initializes the I-block number.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c Negative - I2C error, session already open, or token release required.
 * See #nfctag_return_value_t definition for detailed explanation.
 * @note An active RF session causes the device to reject this command.
 * If the transfer fails, the function attempts to restore the bus and returns the transfer error.
 * Select the application and a file before accessing memory. Release the session afterward.
 */
err_t nfctag_get_session ( nfctag_t *ctx );

/**
 * @brief NFC Tag release I2C function.
 * @details This function releases the NFC Tag Click I2C token so the RF reader can access the tag.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c Negative - GPIO error or bus could not be released.
 * See #nfctag_return_value_t definition for detailed explanation.
 * @note Uses the M24SR64-Y datasheet section 7.4 token release sequence, independent
 * of the EEPROM watchdog setting.
 * The driver generates START with GPIO, holds SCL low for 100 ms, then releases
 * SCL and SDA in order through input mode to generate STOP.
 * After a transport error, a 100 ms delay precedes release to allow an EEPROM write to finish.
 * Call after transport errors before starting another session.
 */
err_t nfctag_release_i2c ( nfctag_t *ctx );

/**
 * @brief NFC Tag select application function.
 * @details This function selects the NFC Tag Click NDEF Tag Application (D2760000850101).
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c Negative - Error.
 * See #nfctag_return_value_t definition for detailed explanation.
 * @note Requires an acquired I2C session.
 */
err_t nfctag_select_application ( nfctag_t *ctx );

/**
 * @brief NFC Tag select file function.
 * @details This function selects the NFC Tag Click system, capability container, or NDEF file.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] file_id : File identifier. See NFCTAG_FILE_* macros.
 * @return @li @c 0 - Success,
 *         @li @c Negative - Error.
 * See #nfctag_return_value_t definition for detailed explanation.
 * @note Requires the NDEF application to be selected.
 */
err_t nfctag_select_file ( nfctag_t *ctx, uint16_t file_id );

/**
 * @brief NFC Tag read binary function.
 * @details This function reads bytes from the selected NFC Tag Click file using standard ReadBinary.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] offset : Byte offset in the selected file.
 * @param[out] data_out : Output buffer containing at least len bytes.
 * @param[in] len : Number of bytes, from 1 to NFCTAG_TRANSFER_MAX.
 * @return @li @c 0 - Success,
 *         @li @c Negative - Error; output buffer is unchanged.
 * See #nfctag_return_value_t definition for detailed explanation.
 * @note Requires an acquired session and selected file. NDEF payload reads are limited by NLEN.
 * The device checks the selected file bounds and access rights.
 */
err_t nfctag_read_binary ( nfctag_t *ctx, uint16_t offset, uint8_t *data_out, uint8_t len );

/**
 * @brief NFC Tag extended read binary function.
 * @details This function reads bytes from the selected NFC Tag Click NDEF file,
 * including bytes beyond the current message length.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] offset : NDEF file byte offset, from 0 to 8191.
 * @param[out] data_out : Output buffer containing at least len bytes.
 * @param[in] len : Number of bytes, from 1 to NFCTAG_TRANSFER_MAX.
 * @return @li @c 0 - Success,
 *         @li @c Negative - Error; output buffer is unchanged.
 * See #nfctag_return_value_t definition for detailed explanation.
 * @note Requires an acquired session and selected NDEF file. Access rights still apply.
 * The read must not extend beyond the 8192-byte file.
 */
err_t nfctag_read_binary_ext ( nfctag_t *ctx, uint16_t offset, uint8_t *data_out, uint8_t len );

/**
 * @brief NFC Tag update binary function.
 * @details This function writes bytes to the selected NFC Tag Click file and waits for the final command response.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] offset : Byte offset in the selected file.
 * @param[in] data_in : Input buffer containing at least len bytes.
 * @param[in] len : Number of bytes, from 1 to NFCTAG_TRANSFER_MAX.
 * @return @li @c 0 - Success,
 *         @li @c Negative - Error.
 * See #nfctag_return_value_t definition for detailed explanation.
 * @note Requires an acquired session and selected file. File bounds and protection apply.
 * Writing the NDEF file directly requires the caller to manage its two-byte NLEN.
 * A transport error does not prove that EEPROM was unchanged.
 */
err_t nfctag_update_binary ( nfctag_t *ctx, uint16_t offset, uint8_t *data_in, uint8_t len );

/**
 * @brief NFC Tag get UID function.
 * @details This function reads the seven-byte NFC Tag Click UID using its own I2C session.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[out] uid : Output buffer of NFCTAG_UID_SIZE bytes.
 * @return @li @c 0 - Success,
 *         @li @c Negative - Error.
 * See #nfctag_return_value_t definition for detailed explanation.
 * @note The UID starts at offset 0x0008 in the system file. Call with no active I2C session.
 * The driver attempts to release its session before returning. The context reports the failed
 * operation in uid_stage and the tag response status in last_status.
 */
err_t nfctag_get_uid ( nfctag_t *ctx, uint8_t *uid );

/**
 * @brief NFC Tag write NDEF text function.
 * @details This function stores one short UTF-8 Text record in NFC Tag Click user EEPROM
 * and verifies the stored data through I2C readback.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] text : Null-terminated UTF-8 string, at most NFCTAG_NDEF_TEXT_MAX_LENGTH bytes.
 * @param[out] stage : Failure stage for diagnostics, or NFCTAG_NDEF_STAGE_OK on success. May be NULL.
 * @return @li @c 0 - Success,
 *         @li @c Negative - Error.
 * See #nfctag_return_value_t definition for detailed explanation.
 * @note Uses language code "en" and requires the standard NDEF file with read and write access.
 * If the record differs, the driver clears NLEN before writing and commits it after payload readback.
 * A failed write can leave NLEN zero. The driver attempts to release its I2C session before returning.
 */
err_t nfctag_write_ndef_text ( nfctag_t *ctx, char *text, nfctag_ndef_stage_t *stage );

/**
 * @brief NFC Tag write NDEF URI function.
 * @details This function stores a complete URI as an NDEF URI record in NFC Tag Click user EEPROM
 * and verifies the stored data through I2C readback.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] uri : Nonempty null-terminated URI, at most NFCTAG_NDEF_URI_MAX_LENGTH bytes.
 * @param[out] stage : Failure stage for diagnostics, or NFCTAG_NDEF_STAGE_OK on success. May be NULL.
 * @return @li @c 0 - Success,
 *         @li @c Negative - Error.
 * See #nfctag_return_value_t definition for detailed explanation.
 * @note Uses URI prefix code 0 to store the complete URI and requires the standard NDEF file
 * with read and write access. If the record differs, the driver clears NLEN before writing
 * and commits it after payload readback. A failed write can leave NLEN zero.
 * The driver attempts to release its I2C session before returning.
 */
err_t nfctag_write_ndef_uri ( nfctag_t *ctx, char *uri, nfctag_ndef_stage_t *stage );

/**
 * @brief NFC Tag set RF disable function.
 * @details This function drives the NFC Tag Click active-high RF-DIS input connected to mikroBUS RST.
 * @param[in] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] state : NFCTAG_RF_ENABLE (0) or NFCTAG_RF_DISABLE (1).
 * @return Nothing.
 * @note RF-DIS is not a device reset and does not release an I2C session.
 */
void nfctag_set_rf_disable ( nfctag_t *ctx, uint8_t state );

/**
 * @brief NFC Tag get GPO function.
 * @details This function reads the NFC Tag Click active-low GPO pin on mikroBUS INT directly through GPIO.
 * @param[in] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @return @li @c 0 - Active,
 *         @li @c 1 - Inactive.
 * @note Meaning depends on the EEPROM GPO setting. The factory value 0x11 indicates
 * an open session, not RF field strength or confirmation that an NDEF record was read.
 */
uint8_t nfctag_get_gpo ( nfctag_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // NFCTAG_H

/*! @} */ // nfctag

// ------------------------------------------------------------------------ END
