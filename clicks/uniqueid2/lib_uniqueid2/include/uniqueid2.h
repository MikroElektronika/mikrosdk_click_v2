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
 * @file uniqueid2.h
 * @brief This file contains API for UNIQUE ID 2 Click Driver.
 */

#ifndef UNIQUEID2_H
#define UNIQUEID2_H

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
 * @addtogroup uniqueid2 UNIQUE ID 2 Click Driver
 * @brief API for configuring and manipulating UNIQUE ID 2 Click driver.
 * @{
 */

/**
 * @defgroup uniqueid2_reg UNIQUE ID 2 Registers List
 * @brief List of registers of UNIQUE ID 2 Click driver.
 */

/**
 * @addtogroup uniqueid2_reg
 * @{
 */

/**
 * @brief UNIQUE ID 2 register list.
 * @details Specified register list of UNIQUE ID 2 Click driver.
 */
#define UNIQUEID2_REG_DTI                 0xE0
#define UNIQUEID2_REG_CDA                 0xC0
#define UNIQUEID2_REG_SWP                 0xA0
#define UNIQUEID2_REG_UID                 0x00

/*! @} */ // uniqueid2_reg

/**
 * @defgroup uniqueid2_set UNIQUE ID 2 Registers Settings
 * @brief Settings for registers of UNIQUE ID 2 Click driver.
 */

/**
 * @addtogroup uniqueid2_set
 * @{
 */

/**
 * @brief UNIQUE ID 2 DTI register setting.
 * @details Specified setting for DTI register of Unique ID 2 Click driver.
 */
#define UNIQUEID2_DTI_DEFAULT             0xB1

/**
 * @brief UNIQUE ID 2 CDA register setting.
 * @details Specified setting for CDA register of Unique ID 2 Click driver.
 */
#define UNIQUEID2_CDA_C2                  0x08
#define UNIQUEID2_CDA_DAL                 0x01

/**
 * @brief UNIQUE ID 2 ID page setting.
 * @details Specified setting for ID page of Unique ID 2 Click driver.
 */
#define UNIQUEID2_SEL_ID_PAGE             0x00

/**
 * @brief UNIQUE ID 2 memory block setting.
 * @details Specified setting for memory block of Unique ID 2 Click driver.
 */
#define UNIQUEID2_BLOCK_SIZE              65536
#define UNIQUEID2_BLOCK_ADDR_MASK         0xFFFF

/**
 * @brief UNIQUE ID 2 SWP register setting.
 * @details Specified setting for SWP register of Unique ID 2 Click driver.
 */
#define UNIQUEID2_SWP_BP_QUARTER          0x00
#define UNIQUEID2_SWP_BP_HALF             0x02
#define UNIQUEID2_SWP_BP_THREE_QUARTER    0x04
#define UNIQUEID2_SWP_BP_ALL              0x06
#define UNIQUEID2_SWP_BP_MASK             0x06
#define UNIQUEID2_SWP_WPA                 0x08
#define UNIQUEID2_SWP_WPL                 0x01

/**
 * @brief UNIQUE ID 2 UID setting.
 * @details Specified setting for UID of Unique ID 2 Click driver.
 */
#define UNIQUEID2_UID_LEN                 16
#define UNIQUEID2_UID_HEADER_ST_CODE      0x20
#define UNIQUEID2_UID_HEADER_BUS_PROTOCOL 0xE0
#define UNIQUEID2_UID_HEADER_DENSITY      0x12

/**
 * @brief UNIQUE ID 2 write control setting.
 * @details Specified setting for write control of Unique ID 2 Click driver.
 */
#define UNIQUEID2_WC_WRITE_ENABLE         0x00
#define UNIQUEID2_WC_WRITE_DISABLE        0x01

/**
 * @brief UNIQUE ID 2 memory setting.
 * @details Specified setting for memory of Unique ID 2 Click driver.
 */
#define UNIQUEID2_PAGE_SIZE               256
#define UNIQUEID2_ID_PAGE_SIZE            256
#define UNIQUEID2_MEMORY_SIZE             262144
#define UNIQUEID2_PAGE_OFFSET_MASK        0xFF
#define UNIQUEID2_BLOCK_OFFSET            16
#define UNIQUEID2_BLOCK_MASK              0x03

/**
 * @brief UNIQUE ID 2 device address setting.
 * @details Specified setting for device slave address selection of
 * UNIQUE ID 2 Click driver.
 */
#define UNIQUEID2_DEVICE_ADDRESS_MEM      0x50
#define UNIQUEID2_DEVICE_ADDRESS_REG      0x58

/*! @} */ // uniqueid2_set

/**
 * @defgroup uniqueid2_map UNIQUE ID 2 MikroBUS Map
 * @brief MikroBUS pin mapping of UNIQUE ID 2 Click driver.
 */

/**
 * @addtogroup uniqueid2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UNIQUE ID 2 Click to the selected MikroBUS.
 */
#define UNIQUEID2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.wc  = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // uniqueid2_map
/*! @} */ // uniqueid2

/**
 * @brief UNIQUE ID 2 Click context object.
 * @details Context object definition of UNIQUE ID 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wc;                           /**< Write control pin. */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} uniqueid2_t;

/**
 * @brief UNIQUE ID 2 Click configuration object.
 * @details Configuration object definition of UNIQUE ID 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t wc;                              /**< Write control pin descriptor. */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} uniqueid2_cfg_t;

/**
 * @brief UNIQUE ID 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    UNIQUEID2_OK = 0,
    UNIQUEID2_ERROR = -1

} uniqueid2_return_value_t;

/*!
 * @addtogroup uniqueid2 UNIQUE ID 2 Click Driver
 * @brief API for configuring and manipulating UNIQUE ID 2 Click driver.
 * @{
 */

/**
 * @brief UNIQUE ID 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #uniqueid2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void uniqueid2_cfg_setup ( uniqueid2_cfg_t *cfg );

/**
 * @brief UNIQUE ID 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #uniqueid2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #uniqueid2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uniqueid2_init ( uniqueid2_t *ctx, uniqueid2_cfg_t *cfg );

/**
 * @brief UNIQUE ID 2 default configuration function.
 * @details This function executes a default configuration of UNIQUE ID 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #uniqueid2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t uniqueid2_default_cfg ( uniqueid2_t *ctx );

/**
 * @brief UNIQUE ID 2 write memory function.
 * @details This function writes a desired number of data bytes to the EEPROM
 * memory array starting from the selected address.
 * @param[in] ctx : Click context object.
 * See #uniqueid2_t object definition for detailed explanation.
 * @param[in] address : Start address in memory [0x00000-0x3FFFF].
 * @param[in] data_in : Pointer to the data to be written.
 * @param[in] len : Number of bytes to write (up to one page, 256 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uniqueid2_write_memory ( uniqueid2_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len );

/**
 * @brief UNIQUE ID 2 read memory function.
 * @details This function reads a desired number of data bytes from the EEPROM
 * memory array starting from the selected address.
 * @param[in] ctx : Click context object.
 * See #uniqueid2_t object definition for detailed explanation.
 * @param[in] address : Start address in memory [0x00000-0x3FFFF].
 * @param[out] data_out : Pointer to the buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uniqueid2_read_memory ( uniqueid2_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );

/**
 * @brief UNIQUE ID 2 write register function.
 * @details This function writes a single byte to the selected configuration
 * register (CDA or SWP).
 * @param[in] ctx : Click context object.
 * See #uniqueid2_t object definition for detailed explanation.
 * @param[in] reg : Register selector.
 * @param[in] data_in : Byte to be written to the register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Setting the DAL bit (CDA) or the WPL bit (SWP) from 0 to 1 is a permanent,
 * irreversible action that freezes the respective register in read-only mode.
 */
err_t uniqueid2_write_register ( uniqueid2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief UNIQUE ID 2 read register function.
 * @details This function reads the selected configuration
 * register (DTI, CDA, or SWP).
 * @param[in] ctx : Click context object.
 * See #uniqueid2_t object definition for detailed explanation.
 * @param[in] reg : Register selector.
 * @param[out] data_out : Pointer to the byte to store the register content.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uniqueid2_read_register ( uniqueid2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief UNIQUE ID 2 read ID page function.
 * @details This function reads a desired number of data bytes from the
 * identification page starting from the selected byte offset.
 * @param[in] ctx : Click context object.
 * See #uniqueid2_t object definition for detailed explanation.
 * @param[in] offset : Byte offset within the identification page [0x00-0xFF].
 * @param[out] data_out : Pointer to the buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uniqueid2_read_id_page ( uniqueid2_t *ctx, uint8_t offset, uint8_t *data_out, uint16_t len );

/**
 * @brief UNIQUE ID 2 read UID function.
 * @details This function reads the 16-byte unique identifier from the
 * identification page.
 * @param[in] ctx : Click context object.
 * See #uniqueid2_t object definition for detailed explanation.
 * @param[out] uid : Pointer to the buffer to store the UID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uniqueid2_read_uid ( uniqueid2_t *ctx, uint8_t *uid );

/**
 * @brief UNIQUE ID 2 set WC pin function.
 * @details This function sets the logic state of the write control pin.
 * @param[in] ctx : Click context object.
 * See #uniqueid2_t object definition for detailed explanation.
 * @param[in] state : Write control pin logic state.
 * @return Nothing.
 * @note None.
 */
void uniqueid2_set_wc_pin ( uniqueid2_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // UNIQUEID2_H

/*! @} */ // uniqueid2

// ------------------------------------------------------------------------ END
