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
 * @file efuse8.h
 * @brief This file contains API for eFuse 8 Click Driver.
 */

#ifndef EFUSE8_H
#define EFUSE8_H

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
 * @addtogroup efuse8 eFuse 8 Click Driver
 * @brief API for configuring and manipulating eFuse 8 Click driver.
 * @{
 */

/**
 * @defgroup efuse8_reg eFuse 8 Registers List
 * @brief List of registers of eFuse 8 Click driver.
 */

/**
 * @addtogroup efuse8_reg
 * @{
 */

/**
 * @brief eFuse 8 register list.
 * @details Specified register list of eFuse 8 Click driver.
 */
#define EFUSE8_REG_WIPER_VOLATILE           0x00
#define EFUSE8_REG_WIPER_NONVOLATILE        0x02
#define EFUSE8_REG_TCON                     0x04
#define EFUSE8_REG_STATUS                   0x05
#define EFUSE8_REG_EEPROM_START             0x06
#define EFUSE8_REG_EEPROM_END               0x0F

/*! @} */ // efuse8_reg

/**
 * @defgroup efuse8_set eFuse 8 Registers Settings
 * @brief Settings for registers of eFuse 8 Click driver.
 */

/**
 * @addtogroup efuse8_set
 * @{
 */

/**
 * @brief eFuse 8 TCON register setting.
 * @details Specified setting for TCON register of eFuse 8 Click driver.
 */
#define EFUSE8_TCON_DEFAULT                 0x1FF

/**
 * @brief eFuse 8 wiper position setting.
 * @details Specified setting for wiper position of eFuse 8 Click driver.
 */
#define EFUSE8_WIPER_MIN                    0
#define EFUSE8_WIPER_MID_SCALE              128
#define EFUSE8_WIPER_MAX                    229
#define EFUSE8_WIPER_RESOLUTION             256

/**
 * @brief eFuse 8 command setting.
 * @details Specified setting for command of eFuse 8 Click driver.
 */
#define EFUSE8_CMD_WRITE_DATA               0x00
#define EFUSE8_CMD_INCREMENT                0x01
#define EFUSE8_CMD_DECREMENT                0x02
#define EFUSE8_CMD_READ_DATA                0x03
#define EFUSE8_CMD_REG_SHIFT                4
#define EFUSE8_CMD_OP_SHIFT                 2
#define EFUSE8_CMD_REG_MASK                 0x0F
#define EFUSE8_CMD_OP_MASK                  0x03
#define EFUSE8_DATA_MSB_SHIFT               8
#define EFUSE8_DATA_MSB_MASK                0x01
#define EFUSE8_DATA_LSB_MASK                0xFF

/**
 * @brief eFuse 8 resistance constants setting.
 * @details Specified setting for resistance constants of eFuse 8 Click driver.
 */
#define EFUSE8_RAB_OHM                      5000
#define EFUSE8_RW_OHM                       75

/**
 * @brief eFuse 8 current limit setting.
 * @details Specified setting for current limit of eFuse 8 Click driver.
 */
#define EFUSE8_ILIM_CONST_OHM_MA            4834000
#define EFUSE8_ILIM_MIN_MA                  950
#define EFUSE8_ILIM_MAX_MA                  8000

/**
 * @brief eFuse 8 reverse current blocking setting.
 * @details Specified setting for reverse current blocking of eFuse 8 Click driver.
 */
#define EFUSE8_RCB_DISABLE                  0
#define EFUSE8_RCB_ENABLE                   1

/**
 * @brief eFuse 8 supply setting.
 * @details Specified setting for supply of eFuse 8 Click driver.
 */
#define EFUSE8_SUPPLY_NOT_GOOD              0
#define EFUSE8_SUPPLY_GOOD                  1

/**
 * @brief eFuse 8 device address setting.
 * @details Specified setting for device slave address selection of
 * eFuse 8 Click driver.
 */
#define EFUSE8_DEVICE_ADDRESS_0             0x2E
#define EFUSE8_DEVICE_ADDRESS_1             0x2F

/*! @} */ // efuse8_set

/**
 * @defgroup efuse8_map eFuse 8 MikroBUS Map
 * @brief MikroBUS pin mapping of eFuse 8 Click driver.
 */

/**
 * @addtogroup efuse8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of eFuse 8 Click to the selected MikroBUS.
 */
#define EFUSE8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pgd = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.ren = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // efuse8_map
/*! @} */ // efuse8

/**
 * @brief eFuse 8 Click context object.
 * @details Context object definition of eFuse 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ren;                          /**< Reverse current blocking pin. */

    // Input pins
    digital_in_t pgd;                           /**< Supply good pin. */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} efuse8_t;

/**
 * @brief eFuse 8 Click configuration object.
 * @details Configuration object definition of eFuse 8 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t pgd;                             /**< Supply good pin descriptor. */
    pin_name_t ren;                             /**< Reverse current blocking pin descriptor. */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} efuse8_cfg_t;

/**
 * @brief eFuse 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EFUSE8_OK = 0,
    EFUSE8_ERROR = -1

} efuse8_return_value_t;

/*!
 * @addtogroup efuse8 eFuse 8 Click Driver
 * @brief API for configuring and manipulating eFuse 8 Click driver.
 * @{
 */

/**
 * @brief eFuse 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #efuse8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void efuse8_cfg_setup ( efuse8_cfg_t *cfg );

/**
 * @brief eFuse 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #efuse8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #efuse8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse8_init ( efuse8_t *ctx, efuse8_cfg_t *cfg );

/**
 * @brief eFuse 8 default configuration function.
 * @details This function executes a default configuration of eFuse 8
 * Click board.
 * @param[in] ctx : Click context object.
 * See #efuse8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t efuse8_default_cfg ( efuse8_t *ctx );

/**
 * @brief eFuse 8 write data function.
 * @details This function writes a single data word to the 
 * selected register address.
 * @param[in] ctx : Click context object.
 * See #efuse8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data word to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse8_write_data ( efuse8_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief eFuse 8 read data function.
 * @details This function reads a single data word from the 
 * selected register address.
 * @param[in] ctx : Click context object.
 * See #efuse8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse8_read_data ( efuse8_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief eFuse 8 set wiper function.
 * @details This function sets the volatile wiper position.
 * @param[in] ctx : Click context object.
 * See #efuse8_t object definition for detailed explanation.
 * @param[in] wiper : Wiper position.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse8_set_wiper ( efuse8_t *ctx, uint16_t wiper );

/**
 * @brief eFuse 8 get wiper function.
 * @details This function reads the volatile wiper position.
 * @param[in] ctx : Click context object.
 * See #efuse8_t object definition for detailed explanation.
 * @param[out] wiper : Pointer to the output wiper position [0-256].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse8_get_wiper ( efuse8_t *ctx, uint16_t *wiper );

/**
 * @brief eFuse 8 set current limit function.
 * @details This function sets the overcurrent threshold by
 * calculating the required wiper position.
 * @param[in] ctx : Click context object.
 * See #efuse8_t object definition for detailed explanation.
 * @param[in] ilim_ma : Current limit in milliamperes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse8_set_current_limit ( efuse8_t *ctx, uint16_t ilim_ma );

/**
 * @brief eFuse 8 get current limit function.
 * @details This function reads the wiper position and calculates 
 * the overcurrent threshold.
 * @param[in] ctx : Click context object.
 * See #efuse8_t object definition for detailed explanation.
 * @param[out] ilim_ma : Pointer to the output current limit in milliamperes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse8_get_current_limit ( efuse8_t *ctx, uint16_t *ilim_ma );

/**
 * @brief eFuse 8 set REN function.
 * @details This function sets the REN pin logic state.
 * @param[in] ctx : Click context object.
 * See #efuse8_t object definition for detailed explanation.
 * @param[in] state : REN pin logic state.
 * @return Nothing.
 * @note None.
 */
void efuse8_set_ren ( efuse8_t *ctx, uint8_t state );

/**
 * @brief eFuse 8 get PGD pin function.
 * @details This function reads the PGD pin logic state.
 * @param[in] ctx : Click context object.
 * See #efuse8_t object definition for detailed explanation.
 * @return PGD pin logic state.
 * @note None.
 */
uint8_t efuse8_get_pgd_pin ( efuse8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EFUSE8_H

/*! @} */ // efuse8

// ------------------------------------------------------------------------ END
