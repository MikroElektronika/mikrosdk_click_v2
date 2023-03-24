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
 * @file magneto11.h
 * @brief This file contains API for Magneto 11 Click Driver.
 */

#ifndef MAGNETO11_H
#define MAGNETO11_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup magneto11 Magneto 11 Click Driver
 * @brief API for configuring and manipulating Magneto 11 Click driver.
 * @{
 */

/**
 * @defgroup magneto11_reg Magneto 11 Registers List
 * @brief List of registers of Magneto 11 Click driver.
 */

/**
 * @addtogroup magneto11_reg
 * @{
 */

/**
 * @brief Magneto 11 register list.
 * @details Specified register list of Magneto 11 Click driver.
 */
#define MAGNETO11_REG_DATA_LSB              0x00
#define MAGNETO11_REG_DATA_MSB              0x01
#define MAGNETO11_REG_CONFIG                0x02
#define MAGNETO11_REG_OFFSET_LSB            0x03
#define MAGNETO11_REG_OFFSET_MSB            0x04
#define MAGNETO11_REG_SENSITIVITY           0x0B

/*! @} */ // magneto11_reg

/**
 * @defgroup magneto11_set Magneto 11 Registers Settings
 * @brief Settings for registers of Magneto 11 Click driver.
 */

/**
 * @addtogroup magneto11_set
 * @{
 */

/**
 * @brief Magneto 11 data output values.
 * @details Specified data output values of Magneto 11 Click driver.
 */
#define MAGNETO11_DATA_RESOLUTION           0x03FF
#define MAGNETO11_DATA_OCF_MASK             0x0800
#define MAGNETO11_DATA_PARITY_MASK          0x0400

/**
 * @brief Magneto 11 sensitivity values.
 * @details Specified sensitivity values of Magneto 11 Click driver.
 */
#define MAGNETO11_SENSITIVITY_RES_50mT      0x00
#define MAGNETO11_SENSITIVITY_RES_25mT      0x01
#define MAGNETO11_SENSITIVITY_RES_12p5mT    0x02
#define MAGNETO11_SENSITIVITY_RES_18p75mT   0x03
#define MAGNETO11_SENSITIVITY_RES_MASK      0x03
#define MAGNETO11_SENSITIVITY_LSB_50mT      0.09766
#define MAGNETO11_SENSITIVITY_LSB_25mT      0.04883
#define MAGNETO11_SENSITIVITY_LSB_12p5mT    0.02441
#define MAGNETO11_SENSITIVITY_LSB_18p75mT   0.03662

/**
 * @brief Magneto 11 config values.
 * @details Specified config values of Magneto 11 Click driver.
 */
#define MAGNETO11_CONFIG_SPEED_FAST         0x00
#define MAGNETO11_CONFIG_SPEED_SLOW         0x04
#define MAGNETO11_CONFIG_POLARITY_NORMAL    0x00
#define MAGNETO11_CONFIG_POLARITY_REVERSED  0x02
#define MAGNETO11_CONFIG_OP_NORMAL          0x00
#define MAGNETO11_CONFIG_OP_POWER_DOWN      0x01

/**
 * @brief Magneto 11 device address setting.
 * @details Specified setting for device slave address selection of
 * Magneto 11 Click driver.
 */
#define MAGNETO11_DEV_ADDR_GND              0x56
#define MAGNETO11_DEV_ADDR_VCC              0x57

/*! @} */ // magneto11_set

/**
 * @defgroup magneto11_map Magneto 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Magneto 11 Click driver.
 */

/**
 * @addtogroup magneto11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magneto 11 Click to the selected MikroBUS.
 */
#define MAGNETO11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // magneto11_map
/*! @} */ // magneto11

/**
 * @brief Magneto 11 Click context object.
 * @details Context object definition of Magneto 11 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} magneto11_t;

/**
 * @brief Magneto 11 Click configuration object.
 * @details Configuration object definition of Magneto 11 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} magneto11_cfg_t;

/**
 * @brief Magneto 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGNETO11_OK = 0,
    MAGNETO11_ERROR = -1

} magneto11_return_value_t;

/*!
 * @addtogroup magneto11 Magneto 11 Click Driver
 * @brief API for configuring and manipulating Magneto 11 Click driver.
 * @{
 */

/**
 * @brief Magneto 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magneto11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magneto11_cfg_setup ( magneto11_cfg_t *cfg );

/**
 * @brief Magneto 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #magneto11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magneto11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto11_init ( magneto11_t *ctx, magneto11_cfg_t *cfg );

/**
 * @brief Magneto 11 default configuration function.
 * @details This function executes a default configuration of Magneto 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #magneto11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t magneto11_default_cfg ( magneto11_t *ctx );

/**
 * @brief Magneto 11 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto11_generic_write ( magneto11_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Magneto 11 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto11_generic_read ( magneto11_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Magneto 11 get magnetic field function.
 * @details This function reads the magnetic field strength in milliTesla.
 * @param[in] ctx : Click context object.
 * See #magneto11_t object definition for detailed explanation.
 * @param[out] mag_field : Magnetic field strength in milliTesla.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto11_get_magnetic_field ( magneto11_t *ctx, float *mag_field );

/**
 * @brief Magneto 11 get offset function.
 * @details This function reads the offset register value.
 * @param[in] ctx : Click context object.
 * See #magneto11_t object definition for detailed explanation.
 * @param[out] offset : Offset register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto11_get_offset ( magneto11_t *ctx, uint16_t *offset );

/**
 * @brief Magneto 11 set config function.
 * @details This function writes specified data to the config register.
 * @param[in] ctx : Click context object.
 * See #magneto11_t object definition for detailed explanation.
 * @param[in] config : Config register value [bit 2 - speed mode, bit 1 - polarity, bit 0 - operating mode].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto11_set_config ( magneto11_t *ctx, uint8_t config );

/**
 * @brief Magneto 11 set sensitivity function.
 * @details This function writes specified data to the sensitivity register.
 * @param[in] ctx : Click context object.
 * See #magneto11_t object definition for detailed explanation.
 * @param[in] sensitivity : @li @c 0 - +-50mT,
 *                          @li @c 1 - +-25mT,
 *                          @li @c 1 - +-12.5mT,
 *                          @li @c 1 - +-18.75mT.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto11_set_sensitivity ( magneto11_t *ctx, uint8_t sensitivity );

#ifdef __cplusplus
}
#endif
#endif // MAGNETO11_H

/*! @} */ // magneto11

// ------------------------------------------------------------------------ END
