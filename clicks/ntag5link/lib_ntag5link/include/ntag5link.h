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
 * @file ntag5link.h
 * @brief This file contains API for NTAG 5 Link Click Driver.
 */

#ifndef NTAG5LINK_H
#define NTAG5LINK_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup ntag5link NTAG 5 Link Click Driver
 * @brief API for configuring and manipulating NTAG 5 Link Click driver.
 * @{
 */

/**
 * @defgroup ntag5link_reg NTAG 5 Link Registers List
 * @brief List of registers of NTAG 5 Link Click driver.
 */

/**
 * @addtogroup ntag5link_reg
 * @{
 */

/**
 * @brief NTAG 5 Link configuration memory organization.
 * @details Specified configuration memory organization of NTAG 5 Link Click driver.
 */
#define NTAG5LINK_CONFIG_SIGNATURE              0x1000
#define NTAG5LINK_CONFIG_HEADER                 0x1008
#define NTAG5LINK_CONFIG_ID                     0x1009
#define NTAG5LINK_CONFIG_NFC_GCH                0x100C
#define NTAG5LINK_CONFIG_NFC_CCH                0x100D
#define NTAG5LINK_CONFIG_NFC_AUTH_LIMIT         0x100E
#define NTAG5LINK_CONFIG_NFC_KH0                0x1010
#define NTAG5LINK_CONFIG_NFC_KP0                0x1011
#define NTAG5LINK_CONFIG_NFC_KH1                0x1012
#define NTAG5LINK_CONFIG_NFC_KP1                0x1013
#define NTAG5LINK_CONFIG_NFC_KH2                0x1014
#define NTAG5LINK_CONFIG_NFC_KP2                0x1015
#define NTAG5LINK_CONFIG_NFC_KH3                0x1016
#define NTAG5LINK_CONFIG_NFC_KP3                0x1017
#define NTAG5LINK_CONFIG_KEY_0                  0x1020
#define NTAG5LINK_CONFIG_KEY_1                  0x1024
#define NTAG5LINK_CONFIG_KEY_2                  0x1028
#define NTAG5LINK_CONFIG_KEY_3                  0x102C
#define NTAG5LINK_CONFIG_I2C_KH                 0x1030
#define NTAG5LINK_CONFIG_I2C_PP_AND_PPC         0x1031
#define NTAG5LINK_CONFIG_I2C_AUTH_LIMIT         0x1032
#define NTAG5LINK_CONFIG_I2C_PWD_0              0x1033
#define NTAG5LINK_CONFIG_I2C_PWD_1              0x1034
#define NTAG5LINK_CONFIG_I2C_PWD_2              0x1035
#define NTAG5LINK_CONFIG_I2C_PWD_3              0x1036
#define NTAG5LINK_CONFIG_CONFIG                 0x1037
#define NTAG5LINK_CONFIG_SYNC_DATA_BLOCK        0x1038
#define NTAG5LINK_CONFIG_PWM_GPIO_CONFIG        0x1039
#define NTAG5LINK_CONFIG_PWM0_ON_OFF            0x103A
#define NTAG5LINK_CONFIG_PWM1_ON_OFF            0x103B
#define NTAG5LINK_CONFIG_WDT_CFG_AND_SRAM_COPY  0x103C
#define NTAG5LINK_CONFIG_EH_AND_ED_CONFIG       0x103D
#define NTAG5LINK_CONFIG_I2C_SLAVE_MASTER_CFG   0x103E
#define NTAG5LINK_CONFIG_SEC_SRAM_AND_PP_AREA_1 0x103F
#define NTAG5LINK_CONFIG_SRAM_DEFAULT           0x1045
#define NTAG5LINK_CONFIG_AFI                    0x1055
#define NTAG5LINK_CONFIG_DSFID                  0x1056
#define NTAG5LINK_CONFIG_EAS_ID                 0x1057
#define NTAG5LINK_CONFIG_NFC_PP_AREA_0_AND_PPC  0x1058
#define NTAG5LINK_CONFIG_NFC_LOCK_BLOCK         0x106A
#define NTAG5LINK_CONFIG_I2C_LOCK_BLOCK         0x108A
#define NTAG5LINK_CONFIG_NFC_SECTION_LOCK       0x1092
#define NTAG5LINK_CONFIG_I2C_SECTION_LOCK       0x1094
#define NTAG5LINK_CONFIG_I2C_PWD_0_AUTH         0x1096
#define NTAG5LINK_CONFIG_I2C_PWD_1_AUTH         0x1097
#define NTAG5LINK_CONFIG_I2C_PWD_2_AUTH         0x1098
#define NTAG5LINK_CONFIG_I2C_PWD_3_AUTH         0x1099

/**
 * @brief NTAG 5 Link session register list.
 * @details Specified session register list of NTAG 5 Link Click driver.
 */
#define NTAG5LINK_SESSION_REG_STATUS            0x10A0
#define NTAG5LINK_SESSION_REG_CONFIG            0x10A1
#define NTAG5LINK_SESSION_REG_SYNC_DATA_BLOCK   0x10A2
#define NTAG5LINK_SESSION_REG_PWM_GPIO_CONFIG   0x10A3
#define NTAG5LINK_SESSION_REG_PWM0_ON_OFF       0x10A4
#define NTAG5LINK_SESSION_REG_PWM1_ON_OFF       0x10A5
#define NTAG5LINK_SESSION_REG_WDT_CONFIG        0x10A6
#define NTAG5LINK_SESSION_REG_EH_CONFIG         0x10A7
#define NTAG5LINK_SESSION_REG_ED_CONFIG         0x10A8
#define NTAG5LINK_SESSION_REG_I2C_SLAVE_CONFIG  0x10A9
#define NTAG5LINK_SESSION_REG_RESET_GEN         0x10AA
#define NTAG5LINK_SESSION_REG_ED_INTR_CLEAR     0x10AB
#define NTAG5LINK_SESSION_REG_I2C_MASTER_CONFIG 0x10AC
#define NTAG5LINK_SESSION_REG_I2C_MASTER_STATUS 0x10AD
#define NTAG5LINK_SESSION_REG_BYTE_0            0x00
#define NTAG5LINK_SESSION_REG_BYTE_1            0x01
#define NTAG5LINK_SESSION_REG_BYTE_2            0x02
#define NTAG5LINK_SESSION_REG_BYTE_3            0x03

/*! @} */ // ntag5link_reg

/**
 * @defgroup ntag5link_set NTAG 5 Link Registers Settings
 * @brief Settings for registers of NTAG 5 Link Click driver.
 */

/**
 * @addtogroup ntag5link_set
 * @{
 */

/**
 * @brief NTAG 5 Link memory organization.
 * @details Specified memory organization of NTAG 5 Link Click driver.
 */
#define NTAG5LINK_USER_MEMORY_ADDRESS_MIN       0x0000
#define NTAG5LINK_USER_MEMORY_ADDRESS_MAX       0x01FF
#define NTAG5LINK_CONFIG_MEMORY_ADDRESS_MIN     0x1000
#define NTAG5LINK_CONFIG_MEMORY_ADDRESS_MAX     0x109F
#define NTAG5LINK_SESSION_REG_ADDRESS_MIN       0x10A0
#define NTAG5LINK_SESSION_REG_ADDRESS_MAX       0x10AF
#define NTAG5LINK_MEMORY_BLOCK_SIZE             4

/**
 * @brief NTAG 5 Link CONFIG registers setting.
 * @details Specified setting for CONFIG registers of NTAG 5 Link Click driver.
 */
#define NTAG5LINK_CONFIG_0_SRAM_COPY_ENABLE     0x80
#define NTAG5LINK_CONFIG_0_EH_LOW_FIELD_STR     0x08
#define NTAG5LINK_CONFIG_0_EH_HIGH_FIELD_STR    0x0C
#define NTAG5LINK_CONFIG_0_LOCK_SESSION_REG     0x02
#define NTAG5LINK_CONFIG_0_AUTO_STANDBY_MODE_EN 0x01
#define NTAG5LINK_CONFIG_1_EH_ARBITER_MODE_EN   0x80
#define NTAG5LINK_CONFIG_1_USE_CASE_I2C_SLAVE   0x00
#define NTAG5LINK_CONFIG_1_USE_CASE_I2C_MASTER  0x10
#define NTAG5LINK_CONFIG_1_USE_CASE_GPIO_PWM    0x20
#define NTAG5LINK_CONFIG_1_USE_CASE_3_STATE     0x30
#define NTAG5LINK_CONFIG_1_ARBITER_NORMAL_MODE  0x00
#define NTAG5LINK_CONFIG_1_ARBITER_SRAM_MIRROR  0x04
#define NTAG5LINK_CONFIG_1_ARBITER_SRAM_PT      0x08
#define NTAG5LINK_CONFIG_1_ARBITER_SRAM_PHDC    0x0C
#define NTAG5LINK_CONFIG_1_SRAM_ENABLE          0x02
#define NTAG5LINK_CONFIG_1_PT_TRANSFER_I2C_NFC  0x00
#define NTAG5LINK_CONFIG_1_PT_TRANSFER_NFC_I2C  0x01
#define NTAG5LINK_CONFIG_2_GPIO1_IN_DISABLE     0x00
#define NTAG5LINK_CONFIG_2_GPIO1_IN_PULL_UP     0x40
#define NTAG5LINK_CONFIG_2_GPIO1_IN_ENABLE      0x80
#define NTAG5LINK_CONFIG_2_GPIO1_IN_PULL_DOWN   0xC0
#define NTAG5LINK_CONFIG_2_GPIO0_IN_DISABLE     0x00
#define NTAG5LINK_CONFIG_2_GPIO0_IN_PULL_UP     0x10
#define NTAG5LINK_CONFIG_2_GPIO0_IN_ENABLE      0x20
#define NTAG5LINK_CONFIG_2_GPIO0_IN_PULL_DOWN   0x30
#define NTAG5LINK_CONFIG_2_EXT_CMD_SUPPORT      0x08
#define NTAG5LINK_CONFIG_2_LOCK_BLK_CMD_SUPPORT 0x04
#define NTAG5LINK_CONFIG_2_GPIO1_HIGH_SLEW_RATE 0x02
#define NTAG5LINK_CONFIG_2_GPIO0_HIGH_SLEW_RATE 0x01

/**
 * @brief NTAG 5 Link NDEF message setting.
 * @details Specified setting for NDEF message of NTAG 5 Link Click driver.
 */
#define NTAG5LINK_CAPABILITY_CONTAINER_ADDRESS  0x0000
#define NTAG5LINK_CAPABILITY_CONTAINER          0xE1, 0x40, 0x80, 0x01
#define NTAG5LINK_NDEF_MESSAGE_START_ADDRESS    0x0001
#define NTAG5LINK_TYPE_NDEF_MESSAGE             0x03
#define NTAG5LINK_NDEF_RECORD_HEADER            0xD1
#define NTAG5LINK_NDEF_TYPE_LENGTH              0x01
#define NTAG5LINK_NDEF_URI_TYPE                 'U'
#define NTAG5LINK_NDEF_MESSAGE_END_MARK         0xFE

/**
 * @brief NTAG 5 Link NDEF URI prefix list.
 * @details Specified NDEF URI prefix list of NTAG 5 Link Click driver.
 */
#define NTAG5LINK_URI_PREFIX_0                  0x00     /**< N/A - no prefix               */
#define NTAG5LINK_URI_PREFIX_1                  0x01     /**< http://www.                   */
#define NTAG5LINK_URI_PREFIX_2                  0x02     /**< https://www.                  */
#define NTAG5LINK_URI_PREFIX_3                  0x03     /**< http://                       */
#define NTAG5LINK_URI_PREFIX_4                  0x04     /**< https://                      */
#define NTAG5LINK_URI_PREFIX_5                  0x05     /**< tel:                          */
#define NTAG5LINK_URI_PREFIX_6                  0x06     /**< mailto:                       */
#define NTAG5LINK_URI_PREFIX_7                  0x07     /**< ftp://anonymous:anonymous@    */
#define NTAG5LINK_URI_PREFIX_8                  0x08     /**< ftp://ftp.                    */
#define NTAG5LINK_URI_PREFIX_9                  0x09     /**< ftps://                       */
#define NTAG5LINK_URI_PREFIX_10                 0x0A     /**< sftp://                       */
#define NTAG5LINK_URI_PREFIX_11                 0x0B     /**< smb://                        */
#define NTAG5LINK_URI_PREFIX_12                 0x0C     /**< nfs://                        */
#define NTAG5LINK_URI_PREFIX_13                 0x0D     /**< ftp://                        */
#define NTAG5LINK_URI_PREFIX_14                 0x0E     /**< dav://                        */
#define NTAG5LINK_URI_PREFIX_15                 0x0F     /**< news:                         */
#define NTAG5LINK_URI_PREFIX_16                 0x10     /**< telnet://                     */
#define NTAG5LINK_URI_PREFIX_17                 0x11     /**< imap:                         */
#define NTAG5LINK_URI_PREFIX_18                 0x12     /**< rtsp://                       */
#define NTAG5LINK_URI_PREFIX_19                 0x13     /**< urn:                          */
#define NTAG5LINK_URI_PREFIX_20                 0x14     /**< pop:                          */
#define NTAG5LINK_URI_PREFIX_21                 0x15     /**< sip:                          */
#define NTAG5LINK_URI_PREFIX_22                 0x16     /**< sips:                         */
#define NTAG5LINK_URI_PREFIX_23                 0x17     /**< tftp:                         */
#define NTAG5LINK_URI_PREFIX_24                 0x18     /**< btspp://                      */
#define NTAG5LINK_URI_PREFIX_25                 0x19     /**< btl2cap://                    */
#define NTAG5LINK_URI_PREFIX_26                 0x1A     /**< btgoep://                     */
#define NTAG5LINK_URI_PREFIX_27                 0x1B     /**< tcpobex://                    */
#define NTAG5LINK_URI_PREFIX_28                 0x1C     /**< irdaobex://                   */
#define NTAG5LINK_URI_PREFIX_29                 0x1D     /**< file://                       */
#define NTAG5LINK_URI_PREFIX_30                 0x1E     /**< urn:epc:id:                   */
#define NTAG5LINK_URI_PREFIX_31                 0x1F     /**< urn:epc:tag:                  */
#define NTAG5LINK_URI_PREFIX_32                 0x20     /**< urn:epc:pat:                  */
#define NTAG5LINK_URI_PREFIX_33                 0x21     /**< urn:epc:raw:                  */
#define NTAG5LINK_URI_PREFIX_34                 0x22     /**< urn:epc:                      */
#define NTAG5LINK_URI_PREFIX_35                 0x23     /**< urn:nfc:                      */

/**
 * @brief NTAG 5 Link device address setting.
 * @details Specified setting for device slave address selection of
 * NTAG 5 Link Click driver.
 */
#define NTAG5LINK_DEVICE_ADDRESS                0x54

/*! @} */ // ntag5link_set

/**
 * @defgroup ntag5link_map NTAG 5 Link MikroBUS Map
 * @brief MikroBUS pin mapping of NTAG 5 Link Click driver.
 */

/**
 * @addtogroup ntag5link_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NTAG 5 Link Click to the selected MikroBUS.
 */
#define NTAG5LINK_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.hpd = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ed = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ntag5link_map
/*! @} */ // ntag5link


/**
 * @brief NTAG 5 Link Click memory block union definition.
 * @details Memory block union definition of NTAG 5 Link Click driver.
 */
typedef union 
{
    uint8_t value_bytes[ 4 ];
    uint32_t value;                 /**< Little-endian. */
} ntag5link_block_t;

/**
 * @brief NTAG 5 Link Click context object.
 * @details Context object definition of NTAG 5 Link Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t hpd;              /**< Hard power down pin. */

    // Input pins
    digital_in_t  ed;               /**< Event detection pin. */

    // Modules
    i2c_master_t  i2c;              /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} ntag5link_t;

/**
 * @brief NTAG 5 Link Click configuration object.
 * @details Configuration object definition of NTAG 5 Link Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  hpd;                /**< Hard power down pin. */
    pin_name_t  ed;                 /**< Event detection pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} ntag5link_cfg_t;

/**
 * @brief NTAG 5 Link Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NTAG5LINK_OK = 0,
    NTAG5LINK_ERROR = -1

} ntag5link_return_value_t;

/*!
 * @addtogroup ntag5link NTAG 5 Link Click Driver
 * @brief API for configuring and manipulating NTAG 5 Link Click driver.
 * @{
 */

/**
 * @brief NTAG 5 Link configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ntag5link_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ntag5link_cfg_setup ( ntag5link_cfg_t *cfg );

/**
 * @brief NTAG 5 Link initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ntag5link_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ntag5link_init ( ntag5link_t *ctx, ntag5link_cfg_t *cfg );

/**
 * @brief NTAG 5 Link default configuration function.
 * @details This function executes a default configuration of NTAG 5 Link
 * click board.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ntag5link_default_cfg ( ntag5link_t *ctx );

/**
 * @brief NTAG 5 Link write memory block function.
 * @details This function writes a memory block data to the selected address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @param[in] block_addr : User or config memory block address.
 * @param[in] block : Address of memory block to be written.
 * See #ntag5link_block_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ntag5link_write_memory_block ( ntag5link_t *ctx, uint16_t block_addr, ntag5link_block_t *block );

/**
 * @brief NTAG 5 Link read memory block function.
 * @details This function reads a memory block data from the selected address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @param[in] block_addr : User or config memory block address.
 * @param[out] block : Address of memory block where to store read data.
 * See #ntag5link_block_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ntag5link_read_memory_block ( ntag5link_t *ctx, uint16_t block_addr, ntag5link_block_t *block );

/**
 * @brief NTAG 5 Link write multiple memory block function.
 * @details This function writes multiple memory blocks starting from the selected address 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @param[in] block_addr : User or config memory block address.
 * @param[in] block : Array of memory block to be written.
 * See #ntag5link_block_t object definition for detailed explanation.
 * @param[in] num_blocks : Number of blocks to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ntag5link_write_multiple_memory_block ( ntag5link_t *ctx, uint16_t block_addr, 
                                              ntag5link_block_t *block, uint8_t num_blocks );

/**
 * @brief NTAG 5 Link read multiple memory block function.
 * @details This function reads multiple memory blocks starting from the selected address 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @param[in] block_addr : User or config memory block address.
 * @param[out] block : Array of memory blocks where to store read data.
 * See #ntag5link_block_t object definition for detailed explanation.
 * @param[in] num_blocks : Number of blocks to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ntag5link_read_multiple_memory_block ( ntag5link_t *ctx, uint16_t block_addr, 
                                             ntag5link_block_t *block, uint8_t num_blocks );

/**
 * @brief NTAG 5 Link write session register function.
 * @details This function writes specified data to the selected session register.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @param[in] block_addr : Session register block address.
 * @param[in] byte_num : Register byte number in a block [0-3].
 * @param[in] mask : Mask of bits to be overwritten.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ntag5link_write_session_register ( ntag5link_t *ctx, uint16_t block_addr, uint8_t byte_num, 
                                         uint8_t mask, uint8_t data_in );

/**
 * @brief NTAG 5 Link read session register function.
 * @details This function reads data from the selected session register.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @param[in] block_addr : Session register block address.
 * @param[in] byte_num : Register byte number in a block [0-3].
 * @param[out] data_out : Output data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ntag5link_read_session_register ( ntag5link_t *ctx, uint16_t block_addr, uint8_t byte_num, uint8_t *data_out );

/**
 * @brief NTAG 5 Link write NDEF URI record function.
 * @details This function writes specific NDEF URI record to the memory address specified with 
 * NTAG5LINK_NDEF_MESSAGE_START_ADDRESS macro.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @param[in] uri_prefix : URI prefix code [0x00-0x23].
 * See #ntag5link_set group for detailed explanation.
 * @param[in] uri_data : URI data to be written.
 * @param[in] data_len : URI data length.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ntag5link_write_ndef_uri_record ( ntag5link_t *ctx, uint8_t uri_prefix, uint8_t *uri_data, uint8_t data_len );

/**
 * @brief NTAG 5 Link format memory function.
 * @details This function formats the whole user memory.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ntag5link_format_memory ( ntag5link_t *ctx );

/**
 * @brief NTAG 5 Link write message to memory function.
 * @details This function writes specified number of data bytes to the user memory 
 * starting from @b block_addr.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @param[in] block_addr : User memory block address.
 * @param[in] message : Array of bytes to be written.
 * @param[in] message_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ntag5link_write_message_to_memory ( ntag5link_t *ctx, uint16_t block_addr, uint8_t *message, uint16_t message_len );

/**
 * @brief NTAG 5 Link read message from memory function.
 * @details This function reads specified number of data bytes from the user memory 
 * starting from @b block_addr.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @param[in] block_addr : User memory block address.
 * @param[out] message : Array of bytes where to store read data.
 * @param[in] message_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ntag5link_read_message_from_memory ( ntag5link_t *ctx, uint16_t block_addr, uint8_t *message, uint16_t message_len );

/**
 * @brief NTAG 5 Link get event detection pin function.
 * @details This function returns the event detection (ED) pin logic state.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ntag5link_get_event_detection_pin ( ntag5link_t *ctx );

/**
 * @brief NTAG 5 Link enable device function.
 * @details This function enables the device by setting HPD pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ntag5link_enable_device ( ntag5link_t *ctx );

/**
 * @brief NTAG 5 Link disable device function.
 * @details This function disables the device by setting HPD pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ntag5link_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ntag5link_disable_device ( ntag5link_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // NTAG5LINK_H

/*! @} */ // ntag5link

// ------------------------------------------------------------------------ END
