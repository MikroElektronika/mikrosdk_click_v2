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
 * @file eeprom12.h
 * @brief This file contains API for EEPROM 12 Click Driver.
 */

#ifndef EEPROM12_H
#define EEPROM12_H

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
 * @addtogroup eeprom12 EEPROM 12 Click Driver
 * @brief API for configuring and manipulating EEPROM 12 Click driver.
 * @{
 */

/**
 * @defgroup eeprom12_reg EEPROM 12 Registers List
 * @brief List of registers of EEPROM 12 Click driver.
 */

/**
 * @addtogroup eeprom12_reg
 * @{
 */

/**
 * @brief EEPROM 12 description register.
 * @details Specified register for description of EEPROM 12 Click driver.
 */
#define EEPROM12_REG_IDENTIFICATION_PAGE         0x0000u
#define EEPROM12_REG_IDENTIFICATION_PAGE_LOCK    0x0200u
#define EEPROM12_REG_CONFIG_DEVICE_ADDRESS       0xC000u

/*! @} */ // eeprom12_reg

/**
 * @defgroup eeprom12_set EEPROM 12 Registers Settings
 * @brief Settings for registers of EEPROM 12 Click driver.
 */

/**
 * @addtogroup eeprom12_set
 * @{
 */

/**
 * @brief EEPROM 12 description setting.
 * @details Specified setting for description of EEPROM 12 Click driver.
 */
#define EEPROM12_MEMORY_ADDRESS_MIN              0x0000u
#define EEPROM12_MEMORY_ADDRESS_MAX              0x7FFFu
#define EEPROM12_PAGE_SIZE                       64
#define EEPROM12_PAGE_MAX                        512

/**
 * @brief EEPROM 12 configurable device address register data values.
 * @details CDA register data values of EEPROM 12 Click driver.
 */
#define EEPROM12_CDA_DAL_BIT_MASK                 0x01
#define EEPROM12_CDA_CEA_BIT_MASK                 0x07

/**
 * @brief EEPROM 12 default chip enable address.
 * @details Default chip enable address of EEPROM 12 Click driver.
 */
#define EEPROM12_DEFAULT_CHIP_ENABLE_ADDRESS     0x00

/**
 * @brief EEPROM 12 device address setting.
 * @details Specified setting for device slave address selection of
 * EEPROM 12 Click driver.
 */
#define EEPROM12_DEVICE_ADDRESS_MEMORY           0x50
#define EEPROM12_DEVICE_ADDRESS_PAGE             0x58

/*! @} */ // eeprom12_set

/**
 * @defgroup eeprom12_map EEPROM 12 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 12 Click driver.
 */

/**
 * @addtogroup eeprom12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 12 Click to the selected MikroBUS.
 */
#define EEPROM12_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.wc  = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // eeprom12_map
/*! @} */ // eeprom12

/**
 * @brief EEPROM 12 Click context object.
 * @details Context object definition of EEPROM 12 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wc;         /**< Write control pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */
    
    uint8_t chip_en_addr;     /* Chip enable address */

} eeprom12_t;

/**
 * @brief EEPROM 12 Click configuration object.
 * @details Configuration object definition of EEPROM 12 Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t wc;             /**< Write control pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} eeprom12_cfg_t;

/**
 * @brief EEPROM 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EEPROM12_OK = 0,
    EEPROM12_ERROR = -1

} eeprom12_return_value_t;

/*!
 * @addtogroup eeprom12 EEPROM 12 Click Driver
 * @brief API for configuring and manipulating EEPROM 12 Click driver.
 * @{
 */

/**
 * @brief EEPROM 12 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom12_cfg_setup ( eeprom12_cfg_t *cfg );

/**
 * @brief EEPROM 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom12_init ( eeprom12_t *ctx, eeprom12_cfg_t *cfg );

/**
 * @brief EEPROM 12 write enable function.
 * @details This function disable hardware write protection of the entire memory 
 * of the M24256E-FMN6TP, 256-Kbit serial I²C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void eeprom12_write_enable ( eeprom12_t *ctx );

/**
 * @brief EEPROM 12 write disable function.
 * @details This function enable hardware write protection of the entire memory  
 * of the M24256E-FMN6TP, 256-Kbit serial I²C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void eeprom12_write_disable ( eeprom12_t *ctx );

/**
 * @brief EEPROM 12 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom12_generic_write ( eeprom12_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 12 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom12_generic_read ( eeprom12_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief EEPROM 12 memory write function.
 * @details This function writes a desired number of data bytes 
 * starting from the selected memory address
 * of the M24256E-FMN6TP, 256-Kbit serial I²C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @param[in] mem_addr : Start memory address (0x0000-0x7FFF).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom12_memory_write ( eeprom12_t *ctx, uint16_t mem_addr, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 12 memory read function.
 * @details This function reads a desired number of data bytes 
 * starting from the selected memory address
 * of the M24256E-FMN6TP, 256-Kbit serial I²C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @param[in] mem_addr : Start memory address (0x0000-0x7FFF).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom12_memory_read ( eeprom12_t *ctx, uint16_t mem_addr, uint8_t *data_out, uint8_t len );

/**
 * @brief EEPROM 12 memory page write function.
 * @details This function writes a desired number of data bytes 
 * starting from the selected memory page address
 * of the M24256E-FMN6TP, 256-Kbit serial I²C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @param[in] page_addr : Start memory page address (0x0000-0x0200).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom12_memory_page_write ( eeprom12_t *ctx, uint16_t page_addr, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 12 memory page read function.
 * @details This function reads a desired number of data bytes 
 * starting from the selected memory page address
 * of the M24256E-FMN6TP, 256-Kbit serial I²C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @param[in] page_addr : Start memory page address (0x0000-0x01FF).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom12_memory_page_read ( eeprom12_t *ctx, uint16_t page_addr, uint8_t *data_out, uint8_t len );

/**
 * @brief EEPROM 12 identification page write function.
 * @details This function writes a desired number of data bytes 
 * starting from the selected identification page address
 * of the M24256E-FMN6TP, 256-Kbit serial I²C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @param[in] id_page_addr : Start identification page address (0x00-0x3F).
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note If the identification page is locked, the data bytes transferred 
 * during the write identification page instruction are not acknowledged (NoACK).
 */
err_t eeprom12_id_page_write ( eeprom12_t *ctx, uint16_t id_page_addr, uint8_t *data_in );

/**
 * @brief EEPROM 12 identification page read function.
 * @details This function reads a desired number of data bytes 
 * starting from the selected identification page address
 * of the M24256E-FMN6TP, 256-Kbit serial I²C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @param[in] id_page_addr : Start identification page address (0x00-0x3F).
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note If the identification page is locked, the data bytes transferred 
 * during the write identification page instruction are not acknowledged (NoACK).
 */
err_t eeprom12_id_page_read ( eeprom12_t *ctx, uint16_t id_page_addr, uint8_t *data_out );

/**
 * @brief EEPROM 12 configuate device address function.
 * @details This function writes a configurable device address register
 * of the M24256E-FMN6TP, 256-Kbit serial I²C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @param[in] cda : Configurable device address bits (0x00-0x07).
 * @param[in] dal : Device address lock bit:
 *         @li @c 0x00 - Configurable device address can be modified,
 *         @li @c 0x01 - Configurable device address cannot be modified.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Updating the DAL bit from 0 to 1 is an irreversible action: 
 * the C2,C1,C0 and DAL bits cannot be updated any more. If the write control input (WC) is driven high or 
 * if the DAL bit is set to 1, the write configurable device address command is not executed 
 * and the accompanying data byte is not acknowledged.
 */
err_t eeprom12_config_dev_addr ( eeprom12_t *ctx, uint8_t cda, uint8_t dal );

/**
 * @brief EEPROM 12 read lock status function.
 * @details This function reads a lock status
 * of the M24256E-FMN6TP, 256-Kbit serial I²C bus EEPROM with configurable device address 
 * and preprogrammed device address on the EEPROM 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #eeprom12_t object definition for detailed explanation.
 * @param[out] lock_status : 
 *         @li @c 0x00 - Unlocked, configurable device address can be modified,
 *         @li @c 0x01 - Locked, configurable device address cannot be modified.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom12_read_lock_status ( eeprom12_t *ctx, uint8_t *lock_status );

#ifdef __cplusplus
}
#endif
#endif // EEPROM12_H

/*! @} */ // eeprom12

// ------------------------------------------------------------------------ END
