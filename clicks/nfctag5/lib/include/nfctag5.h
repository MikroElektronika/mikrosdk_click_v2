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
 * @file nfctag5.h
 * @brief This file contains API for NFC Tag 5 Click Driver.
 */

#ifndef NFCTAG5_H
#define NFCTAG5_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup nfctag5 NFC Tag 5 Click Driver
 * @brief API for configuring and manipulating NFC Tag 5 Click driver.
 * @{
 */

/**
 * @defgroup nfctag5_reg NFC Tag 5 Registers List
 * @brief List of registers of NFC Tag 5 Click driver.
 */

/**
 * @addtogroup nfctag5_reg
 * @{
 */

/**
 * @brief NFC Tag 5 register list.
 * @details Specified register list of NFC Tag 5 Click driver.
 */
#define NFCTAG5_REG_SECTOR_SECURITY_0           0x0000
#define NFCTAG5_REG_SECTOR_SECURITY_4           0x0004
#define NFCTAG5_REG_SECTOR_SECURITY_8           0x0008
#define NFCTAG5_REG_SECTOR_SECURITY_12          0x000C
#define NFCTAG5_REG_SECTOR_SECURITY_16          0x0010
#define NFCTAG5_REG_SECTOR_SECURITY_20          0x0014
#define NFCTAG5_REG_SECTOR_SECURITY_24          0x0018
#define NFCTAG5_REG_SECTOR_SECURITY_28          0x001C
#define NFCTAG5_REG_SECTOR_SECURITY_32          0x0020
#define NFCTAG5_REG_SECTOR_SECURITY_36          0x0024
#define NFCTAG5_REG_SECTOR_SECURITY_40          0x0028
#define NFCTAG5_REG_SECTOR_SECURITY_44          0x002C
#define NFCTAG5_REG_SECTOR_SECURITY_48          0x0030
#define NFCTAG5_REG_SECTOR_SECURITY_52          0x0034
#define NFCTAG5_REG_SECTOR_SECURITY_56          0x0038
#define NFCTAG5_REG_SECTOR_SECURITY_60          0x003C
#define NFCTAG5_REG_SECTOR_SECURITY_STATUS_LSB  0x0800
#define NFCTAG5_REG_SECTOR_SECURITY_STATUS_MSB  0x0804
#define NFCTAG5_REG_I2C_PASSWORD                0x0900
#define NFCTAG5_REG_RF_PASSWORD_1               0x0904
#define NFCTAG5_REG_RF_PASSWORD_2               0x0908
#define NFCTAG5_REG_RF_PASSWORD_3               0x090C
#define NFCTAG5_REG_CONFIG                      0x0910
#define NFCTAG5_REG_UID_LSB                     0x0914
#define NFCTAG5_REG_UID_MSB                     0x0918
#define NFCTAG5_REG_IC_REF_MEM_SIZE             0x091C
#define NFCTAG5_REG_CONTROL                     0x0920

/*! @} */ // nfctag5_reg

/**
 * @defgroup nfctag5_set NFC Tag 5 Registers Settings
 * @brief Settings for registers of NFC Tag 5 Click driver.
 */

/**
 * @addtogroup nfctag5_set
 * @{
 */

/**
 * @brief NFC Tag 5 NDEF message setting.
 * @details Specified setting for NDEF message of NFC Tag 5 Click driver.
 */
#define NFCTAG5_CAPABILITY_CONTAINER_ADDRESS    0x0000
#define NFCTAG5_CAPABILITY_CONTAINER            0xE1, 0x40, 0x80, 0x01
#define NFCTAG5_NDEF_MESSAGE_START_ADDRESS      0x0004
#define NFCTAG5_TYPE_NDEF_MESSAGE               0x03
#define NFCTAG5_NDEF_RECORD_HEADER              0xD1
#define NFCTAG5_NDEF_TYPE_LENGTH                0x01
#define NFCTAG5_NDEF_URI_TYPE                   'U'
#define NFCTAG5_NDEF_MESSAGE_END_MARK           0xFE

/**
 * @brief NFC Tag 5 NDEF URI prefix list.
 * @details Specified NDEF URI prefix list of NFC Tag 5 Click driver.
 */
#define NFCTAG5_URI_PREFIX_0                    0x00    /**< N/A - no prefix               */
#define NFCTAG5_URI_PREFIX_1                    0x01    /**< http://www.                   */
#define NFCTAG5_URI_PREFIX_2                    0x02    /**< https://www.                  */
#define NFCTAG5_URI_PREFIX_3                    0x03    /**< http://                       */
#define NFCTAG5_URI_PREFIX_4                    0x04    /**< https://                      */
#define NFCTAG5_URI_PREFIX_5                    0x05    /**< tel:                          */
#define NFCTAG5_URI_PREFIX_6                    0x06    /**< mailto:                       */
#define NFCTAG5_URI_PREFIX_7                    0x07    /**< ftp://anonymous:anonymous@    */
#define NFCTAG5_URI_PREFIX_8                    0x08    /**< ftp://ftp.                    */
#define NFCTAG5_URI_PREFIX_9                    0x09    /**< ftps://                       */
#define NFCTAG5_URI_PREFIX_10                   0x0A    /**< sftp://                       */
#define NFCTAG5_URI_PREFIX_11                   0x0B    /**< smb://                        */
#define NFCTAG5_URI_PREFIX_12                   0x0C    /**< nfs://                        */
#define NFCTAG5_URI_PREFIX_13                   0x0D    /**< ftp://                        */
#define NFCTAG5_URI_PREFIX_14                   0x0E    /**< dav://                        */
#define NFCTAG5_URI_PREFIX_15                   0x0F    /**< news:                         */
#define NFCTAG5_URI_PREFIX_16                   0x10    /**< telnet://                     */
#define NFCTAG5_URI_PREFIX_17                   0x11    /**< imap:                         */
#define NFCTAG5_URI_PREFIX_18                   0x12    /**< rtsp://                       */
#define NFCTAG5_URI_PREFIX_19                   0x13    /**< urn:                          */
#define NFCTAG5_URI_PREFIX_20                   0x14    /**< pop:                          */
#define NFCTAG5_URI_PREFIX_21                   0x15    /**< sip:                          */
#define NFCTAG5_URI_PREFIX_22                   0x16    /**< sips:                         */
#define NFCTAG5_URI_PREFIX_23                   0x17    /**< tftp:                         */
#define NFCTAG5_URI_PREFIX_24                   0x18    /**< btspp://                      */
#define NFCTAG5_URI_PREFIX_25                   0x19    /**< btl2cap://                    */
#define NFCTAG5_URI_PREFIX_26                   0x1A    /**< btgoep://                     */
#define NFCTAG5_URI_PREFIX_27                   0x1B    /**< tcpobex://                    */
#define NFCTAG5_URI_PREFIX_28                   0x1C    /**< irdaobex://                   */
#define NFCTAG5_URI_PREFIX_29                   0x1D    /**< file://                       */
#define NFCTAG5_URI_PREFIX_30                   0x1E    /**< urn:epc:id:                   */
#define NFCTAG5_URI_PREFIX_31                   0x1F    /**< urn:epc:tag:                  */
#define NFCTAG5_URI_PREFIX_32                   0x20    /**< urn:epc:pat:                  */
#define NFCTAG5_URI_PREFIX_33                   0x21    /**< urn:epc:raw:                  */
#define NFCTAG5_URI_PREFIX_34                   0x22    /**< urn:epc:                      */
#define NFCTAG5_URI_PREFIX_35                   0x23    /**< urn:nfc:                      */

/**
 * @brief NFC Tag 5 User memory settings.
 * @details Specified User memory settings of NFC Tag 5 Click driver.
 */
#define NFCTAG5_USER_MEMORY_ADDRESS_MIN         0x0000
#define NFCTAG5_USER_MEMORY_ADDRESS_MAX         0x1FFF
#define NFCTAG5_MEMORY_BLOCK_SIZE               4
#define NFCTAG5_MEMORY_BLOCK_MASK               0x1FFC

/**
 * @brief NFC Tag 5 address mode selection.
 * @details Specified address mode selection of NFC Tag 5 Click driver.
 */
#define NFCTAG5_ADDRESS_MODE_CONFIG             0
#define NFCTAG5_ADDRESS_MODE_USER_MEMORY        1

/**
 * @brief NFC Tag 5 VH vref selection.
 * @details Specified VH vref selection of NFC Tag 5 Click driver.
 */
#define NFCTAG5_VH_VREF_3V3                     3.3
#define NFCTAG5_VH_VREF_5V                      5.0
#define NFCTAG5_VH_VREF                         NFCTAG5_VH_VREF_3V3

/**
 * @brief NFC Tag 5 device address setting.
 * @details Specified setting for device slave address selection of
 * NFC Tag 5 Click driver.
 */
#define NFCTAG5_DEVICE_ADDRESS_CONFIG           0x57
#define NFCTAG5_DEVICE_ADDRESS_USER_MEMORY      0x53

/*! @} */ // nfctag5_set

/**
 * @defgroup nfctag5_map NFC Tag 5 MikroBUS Map
 * @brief MikroBUS pin mapping of NFC Tag 5 Click driver.
 */

/**
 * @addtogroup nfctag5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NFC Tag 5 Click to the selected MikroBUS.
 */
#define NFCTAG5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.vh = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.busy = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nfctag5_map
/*! @} */ // nfctag5

/**
 * @brief NFC Tag 5 Click memory block union definition.
 * @details Memory block union definition of NFC Tag 5 Click driver.
 */
typedef union 
{
    uint8_t value_bytes[ 4 ];
    uint32_t value;                 /**< Little-endian. */
} nfctag5_block_t;

/**
 * @brief NFC Tag 5 Click context object.
 * @details Context object definition of NFC Tag 5 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t busy;      /**< RF Write in progress / RF Busy pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */
    analog_in_t  adc;       /**< ADC module object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} nfctag5_t;

/**
 * @brief NFC Tag 5 Click configuration object.
 * @details Configuration object definition of NFC Tag 5 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  vh;         /**< Energy harvesting analog output (Vout). */
    pin_name_t  busy;       /**< RF Write in progress / RF Busy pin. */

    uint32_t    i2c_speed;  /**< I2C serial speed. */
    uint8_t     i2c_address;/**< I2C slave address. */
    analog_in_resolution_t  resolution; /**< ADC resolution. */
    float       vref;       /**< ADC reference voltage. */

} nfctag5_cfg_t;

/**
 * @brief NFC Tag 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NFCTAG5_OK = 0,
    NFCTAG5_ERROR = -1

} nfctag5_return_value_t;

/*!
 * @addtogroup nfctag5 NFC Tag 5 Click Driver
 * @brief API for configuring and manipulating NFC Tag 5 Click driver.
 * @{
 */

/**
 * @brief NFC Tag 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nfctag5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nfctag5_cfg_setup ( nfctag5_cfg_t *cfg );

/**
 * @brief NFC Tag 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nfctag5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfctag5_init ( nfctag5_t *ctx, nfctag5_cfg_t *cfg );

/**
 * @brief NFC Tag 5 default configuration function.
 * @details This function executes a default configuration of NFC Tag 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t nfctag5_default_cfg ( nfctag5_t *ctx );

/**
 * @brief NFC Tag 5 set address mode function.
 * @details This function sets the address mode to config or user memory.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - Config,
 *                   @li @c 1 - User memory.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfctag5_set_address_mode ( nfctag5_t *ctx, uint8_t mode );

/**
 * @brief NFC Tag 5 write memory block function.
 * @details This function writes a memory block data to the selected address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @param[in] block_addr : User memory block address.
 * @param[in] block : Address of memory block to be written.
 * See #nfctag5_block_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfctag5_write_memory_block ( nfctag5_t *ctx, uint16_t block_addr, nfctag5_block_t *block );

/**
 * @brief NFC Tag 5 read memory block function.
 * @details This function reads a memory block data from the selected address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @param[in] block_addr : User memory block address.
 * @param[out] block : Address of memory block where to store read data.
 * See #nfctag5_block_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfctag5_read_memory_block ( nfctag5_t *ctx, uint16_t block_addr, nfctag5_block_t *block );

/**
 * @brief NFC Tag 5 write multiple memory block function.
 * @details This function writes multiple memory blocks starting from the selected address 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @param[in] block_addr : User memory block address.
 * @param[in] block : Array of memory block to be written.
 * See #nfctag5_block_t object definition for detailed explanation.
 * @param[in] num_blocks : Number of blocks to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfctag5_write_multiple_memory_block ( nfctag5_t *ctx, uint16_t block_addr, 
                                            nfctag5_block_t *block, uint8_t num_blocks );

/**
 * @brief NFC Tag 5 read multiple memory block function.
 * @details This function reads multiple memory blocks starting from the selected address 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @param[in] block_addr : User memory block address.
 * @param[out] block : Array of memory blocks where to store read data.
 * See #nfctag5_block_t object definition for detailed explanation.
 * @param[in] num_blocks : Number of blocks to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfctag5_read_multiple_memory_block ( nfctag5_t *ctx, uint16_t block_addr, 
                                           nfctag5_block_t *block, uint8_t num_blocks );

/**
 * @brief NFC Tag 5 write NDEF URI record function.
 * @details This function writes specific NDEF URI record to the memory address specified with 
 * NTAG5LINK_NDEF_MESSAGE_START_ADDRESS macro.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @param[in] uri_prefix : URI prefix code [0x00-0x23].
 * See #nfctag5_set group for detailed explanation.
 * @param[in] uri_data : URI data to be written.
 * @param[in] data_len : URI data length.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfctag5_write_ndef_uri_record ( nfctag5_t *ctx, uint8_t uri_prefix, uint8_t *uri_data, uint8_t data_len );

/**
 * @brief NFC Tag 5 format memory function.
 * @details This function formats the whole user memory.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfctag5_format_memory ( nfctag5_t *ctx );

/**
 * @brief NFC Tag 5 write message to memory function.
 * @details This function writes specified number of data bytes to the user memory 
 * starting from @b block_addr.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @param[in] block_addr : User memory block address.
 * @param[in] message : Array of bytes to be written.
 * @param[in] message_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfctag5_write_message_to_memory ( nfctag5_t *ctx, uint16_t block_addr, uint8_t *message, uint16_t message_len );

/**
 * @brief NFC Tag 5 read message from memory function.
 * @details This function reads specified number of data bytes from the user memory 
 * starting from @b block_addr.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @param[in] block_addr : User memory block address.
 * @param[out] message : Array of bytes where to store read data.
 * @param[in] message_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfctag5_read_message_from_memory ( nfctag5_t *ctx, uint16_t block_addr, uint8_t *message, uint16_t message_len );

/**
 * @brief NFC Tag 5 read AN pin value function.
 * @details This function reads results of AD conversion of the VH pin.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfctag5_read_vh_pin_value ( nfctag5_t *ctx, uint16_t *data_out );

/**
 * @brief NFC Tag 5 read VH pin voltage level function.
 * @details This function reads results of AD conversion of the VH pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t nfctag5_read_vh_pin_voltage ( nfctag5_t *ctx, float *data_out );

/**
 * @brief NFC Tag 5 get busy pin function.
 * @details This function returns the BUSY pin logic state.
 * @param[in] ctx : Click context object.
 * See #nfctag5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nfctag5_get_busy_pin ( nfctag5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // NFCTAG5_H

/*! @} */ // nfctag5

// ------------------------------------------------------------------------ END
