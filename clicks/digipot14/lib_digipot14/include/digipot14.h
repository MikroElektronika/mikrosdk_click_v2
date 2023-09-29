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
 * @file digipot14.h
 * @brief This file contains API for DIGI POT 14 Click Driver.
 */

#ifndef DIGIPOT14_H
#define DIGIPOT14_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup digipot14 DIGI POT 14 Click Driver
 * @brief API for configuring and manipulating DIGI POT 14 Click driver.
 * @{
 */

/**
 * @defgroup digipot14_reg DIGI POT 14 Registers List
 * @brief List of registers of DIGI POT 14 Click driver.
 */

/**
 * @addtogroup digipot14_reg
 * @{
 */

/**
 * @brief DIGI POT 14 description register.
 * @details Specified register for description of DIGI POT 14 Click driver.
 */
#define DIGIPOT14_VOLATILE_REG_WRA                  0x00
#define DIGIPOT14_VOLATILE_REG_WRB                  0x01
#define DIGIPOT14_VOLATILE_REG_ACR                  0x10
#define DIGIPOT14_NON_VOLATILE_REG_IVRA             0x00
#define DIGIPOT14_NON_VOLATILE_REG_IVRB             0x01

/*! @} */ // digipot14_reg

/**
 * @defgroup digipot14_set DIGI POT 14 Registers Settings
 * @brief Settings for registers of DIGI POT 14 Click driver.
 */

/**
 * @addtogroup digipot14_set
 * @{
 */

/**
 * @brief DIGI POT 14 Access Control Register values setting.
 * @details Specified setting for Access Control Register values of DIGI POT 14 Click driver.
 */
#define DIGIPOT14_VOLATILE_REG_WRITE                0x80
#define DIGIPOT14_NON_VOLATILE_REG_WRITE            0x00
#define DIGIPOT14_DISABLE_SHUT_DOWN                 0x40
#define DIGIPOT14_ENABLE_SHUT_DOWN                  0x00
#define DIGIPOT14_NON_VOLATILE_WR_IN_PROGRESS       0x20
#define DIGIPOT14_NON_VOLATILE_WR_NOT_IN_PROGRESS   0x00

#define DIGIPOT14_MAX_RESISTANCE_KOHM               100.0
#define DIGIPOT14_MAX_POSITION                      255
#define DIGIPOT14_MAX_POSITION_NUM                  256.0
#define DIGIPOT14_MIN_POSITION                      0

/**
 * @brief DIGI POT 14 device address setting.
 * @details Specified setting for device slave address selection of
 * DIGI POT 14 Click driver.
 */
#define DIGIPOT14_DEVICE_ADDRESS_000                0x50
#define DIGIPOT14_DEVICE_ADDRESS_001                0x51
#define DIGIPOT14_DEVICE_ADDRESS_010                0x52
#define DIGIPOT14_DEVICE_ADDRESS_011                0x53
#define DIGIPOT14_DEVICE_ADDRESS_100                0x54
#define DIGIPOT14_DEVICE_ADDRESS_101                0x55
#define DIGIPOT14_DEVICE_ADDRESS_110                0x56
#define DIGIPOT14_DEVICE_ADDRESS_111                0x57

/*! @} */ // digipot14_set

/**
 * @defgroup digipot14_map DIGI POT 14 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI POT 14 Click driver.
 */

/**
 * @addtogroup digipot14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI POT 14 Click to the selected MikroBUS.
 */
#define DIGIPOT14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // digipot14_map
/*! @} */ // digipot14

/**
 * @brief DIGI POT 14 Click context object.
 * @details Context object definition of DIGI POT 14 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} digipot14_t;

/**
 * @brief DIGI POT 14 Click configuration object.
 * @details Configuration object definition of DIGI POT 14 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} digipot14_cfg_t;

/**
 * @brief DIGI POT 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIPOT14_OK = 0,
    DIGIPOT14_ERROR = -1

} digipot14_return_value_t;

/*!
 * @addtogroup digipot14 DIGI POT 14 Click Driver
 * @brief API for configuring and manipulating DIGI POT 14 Click driver.
 * @{
 */

/**
 * @brief DIGI POT 14 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digipot14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digipot14_cfg_setup ( digipot14_cfg_t *cfg );

/**
 * @brief DIGI POT 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #digipot14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digipot14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot14_init ( digipot14_t *ctx, digipot14_cfg_t *cfg );

/**
 * @brief DIGI POT 14 default configuration function.
 * @details This function executes a default configuration of DIGI POT 14
 * click board.
 * @param[in] ctx : Click context object.
 * See #digipot14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t digipot14_default_cfg ( digipot14_t *ctx );

/**
 * @brief DIGI POT 14 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot14_generic_write ( digipot14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief DIGI POT 14 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot14_generic_read ( digipot14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief DIGI POT 14 register write function.
 * @details This function writes a data byte into 
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot14_reg_write ( digipot14_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DIGI POT 14 register reading function.
 * @details This function reads a data byte from 
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot14_reg_read ( digipot14_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DIGI POT 14 set the wiper position of potentiometer A function.
 * @details This function sets the wiper position of the A potentiometer.
 * @param[in] ctx : Click context object.
 * See #digipot14_t object definition for detailed explanation.
 * @param[in] ctx : Click context object.
 * See #digipot14_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot14_set_pot_a_wiper ( digipot14_t *ctx, uint8_t wiper_pos );

/**
 * @brief DIGI POT 14 set the wiper position of potentiometer B function.
 * @details This function sets the wiper position of the B potentiometer.
 * @param[in] ctx : Click context object.
 * See #digipot14_t object definition for detailed explanation.
 * @param[in] ctx : Click context object.
 * See #digipot14_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot14_set_pot_b_wiper ( digipot14_t *ctx, uint8_t wiper_pos );

#ifdef __cplusplus
}
#endif
#endif // DIGIPOT14_H

/*! @} */ // digipot14

// ------------------------------------------------------------------------ END
