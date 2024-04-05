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
 * @file eeprom11.h
 * @brief This file contains API for EEPROM 11 Click Driver.
 */

#ifndef EEPROM11_H
#define EEPROM11_H

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
 * @addtogroup eeprom11 EEPROM 11 Click Driver
 * @brief API for configuring and manipulating EEPROM 11 Click driver.
 * @{
 */

/**
 * @defgroup eeprom11_reg EEPROM 11 Registers List
 * @brief List of registers of EEPROM 11 Click driver.
 */

/**
 * @addtogroup eeprom11_reg
 * @{
 */

/**
 * @brief EEPROM 11 description register.
 * @details Specified register for description of EEPROM 11 Click driver.
 */
#define EEPROM11_SET_WP_BLOCK0              0x31
#define EEPROM11_SET_WP_BLOCK1              0x34
#define EEPROM11_SET_WP_BLOCK2              0x35
#define EEPROM11_SET_WP_BLOCK3              0x30
#define EEPROM11_CLEAR_ALL_WP               0x33
#define EEPROM11_READ_SWP0                  0x31
#define EEPROM11_READ_SWP1                  0x34
#define EEPROM11_READ_SWP2                  0x35
#define EEPROM11_READ_SWP3                  0x30
#define EEPROM11_SET_PAGE_ADDR_0            0x36
#define EEPROM11_SET_PAGE_ADDR_1            0x37
#define EEPROM11_READ_PAGE_ADDR             0x36

/*! @} */ // eeprom11_reg

/**
 * @defgroup eeprom11_set EEPROM 11 Registers Settings
 * @brief Settings for registers of EEPROM 11 Click driver.
 */

/**
 * @addtogroup eeprom11_set
 * @{
 */

/**
 * @brief EEPROM 11 device address setting.
 * @details Specified setting for device slave address selection of
 * EEPROM 11 Click driver.
 */
#define EEPROM11_DEVICE_ADDRESS_0           0x50
#define EEPROM11_DEVICE_ADDRESS_1           0x51
#define EEPROM11_DEVICE_ADDRESS_2           0x52
#define EEPROM11_DEVICE_ADDRESS_3           0x53
#define EEPROM11_DEVICE_ADDRESS_4           0x54
#define EEPROM11_DEVICE_ADDRESS_5           0x55
#define EEPROM11_DEVICE_ADDRESS_6           0x56
#define EEPROM11_DEVICE_ADDRESS_7           0x57
/*! @} */ // eeprom11_set

/**
 * @defgroup eeprom11_map EEPROM 11 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 11 Click driver.
 */

/**
 * @addtogroup eeprom11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 11 Click to the selected MikroBUS.
 */
#define EEPROM11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // eeprom11_map
/*! @} */ // eeprom11

/**
 * @brief EEPROM 11 Click context object.
 * @details Context object definition of EEPROM 11 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} eeprom11_t;

/**
 * @brief EEPROM 11 Click configuration object.
 * @details Configuration object definition of EEPROM 11 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} eeprom11_cfg_t;

/**
 * @brief EEPROM 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EEPROM11_OK = 0,
    EEPROM11_ERROR = -1

} eeprom11_return_value_t;

/*!
 * @addtogroup eeprom11 EEPROM 11 Click Driver
 * @brief API for configuring and manipulating EEPROM 11 Click driver.
 * @{
 */

/**
 * @brief EEPROM 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom11_cfg_setup ( eeprom11_cfg_t *cfg );

/**
 * @brief EEPROM 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #eeprom11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom11_init ( eeprom11_t *ctx, eeprom11_cfg_t *cfg );

/**
 * @brief EEPROM 11 default configuration function.
 * @details This function executes a default configuration of EEPROM 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #eeprom11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t eeprom11_default_cfg ( eeprom11_t *ctx );

/**
 * @brief EEPROM 11 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom11_generic_write ( eeprom11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 11 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom11_generic_read ( eeprom11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief EEPROM 11 page write function.
 * @details This function is used write page ( 16 bits ) into the selected address.
 * @param[in] ctx : Click context object.
 * See #eeprom11_t object definition for detailed explanation.
 * @param[in] address : Start address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom11_page_write ( eeprom11_t *ctx, uint8_t address, uint8_t *data_in );

/**
 * @brief EEPROM 11 page clear function.
 * @details This function is used clear page ( 16 bits ) starting from the selected address.
 * @param[in] ctx : Click context object.
 * See #eeprom11_t object definition for detailed explanation.
 * @param[in] address : Start address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom11_clear_page ( eeprom11_t *ctx, uint8_t address );

/**
 * @brief EEPROM 11 set write protection function.
 * @details This function is used set write protection of selected bock.
 * @param[in] ctx : Click context object.
 * See #eeprom11_t object definition for detailed explanation.
 * @param[in] block_addr : Selected block address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom11_set_wp ( eeprom11_t *ctx, uint8_t block_addr );

/**
 * @brief EEPROM 11 clear write protection function.
 * @details This function is used clear write protection of selected bock.
 * @param[in] ctx : Click context object.
 * See #eeprom11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom11_clear_wp ( eeprom11_t *ctx );

/**
 * @brief EEPROM 11 set page address function.
 * @details This function is used to select page address.
 * @param[in] ctx : Click context object.
 * See #eeprom11_t object definition for detailed explanation.
 * @param[in] page_addr : Selected page address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom11_set_page_addr ( eeprom11_t *ctx, uint8_t page_addr );

#ifdef __cplusplus
}
#endif
#endif // EEPROM11_H

/*! @} */ // eeprom11

// ------------------------------------------------------------------------ END
