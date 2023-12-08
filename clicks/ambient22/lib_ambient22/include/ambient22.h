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
 * @file ambient22.h
 * @brief This file contains API for Ambient 22 Click Driver.
 */

#ifndef AMBIENT22_H
#define AMBIENT22_H

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
 * @addtogroup ambient22 Ambient 22 Click Driver
 * @brief API for configuring and manipulating Ambient 22 Click driver.
 * @{
 */

/**
 * @defgroup ambient22_reg Ambient 22 Registers List
 * @brief List of registers of Ambient 22 Click driver.
 */

/**
 * @addtogroup ambient22_reg
 * @{
 */

/**
 * @brief Ambient 22 register list.
 * @details Specified register list of Ambient 22 Click driver.
 */
#define AMBIENT22_REG_RESULT                    0x00
#define AMBIENT22_REG_CONFIGURATION             0x01
#define AMBIENT22_REG_LOW_LIMIT                 0x02
#define AMBIENT22_REG_HIGH_LIMIT                0x03
#define AMBIENT22_REG_MANUFACTURER_ID           0x7E
#define AMBIENT22_REG_DEVICE_ID                 0x7F

/*! @} */ // ambient22_reg

/**
 * @defgroup ambient22_set Ambient 22 Registers Settings
 * @brief Settings for registers of Ambient 22 Click driver.
 */

/**
 * @addtogroup ambient22_set
 * @{
 */

/**
 * @brief Ambient 22 configuration setting.
 * @details Specified setting for configuration of Ambient 22 Click driver.
 */
#define AMBIENT22_CONFIG_RN_AUTO_SCALE          0xC000u
#define AMBIENT22_CONFIG_RN_MASK                0xF000u
#define AMBIENT22_CONFIG_CT_100_mS              0x0000u
#define AMBIENT22_CONFIG_CT_800_mS              0x0800u
#define AMBIENT22_CONFIG_CT_MASK                0x0800u
#define AMBIENT22_CONFIG_M_SHUTDOWN             0x0000u
#define AMBIENT22_CONFIG_M_SINGLE               0x0200u
#define AMBIENT22_CONFIG_M_CONTINUOUS           0x0400u
#define AMBIENT22_CONFIG_M_MASK                 0x0600u
#define AMBIENT22_CONFIG_OVF_MASK               0x0100u
#define AMBIENT22_CONFIG_CRF_MASK               0x0080u
#define AMBIENT22_CONFIG_FH_MASK                0x0040u
#define AMBIENT22_CONFIG_FL_MASK                0x0020u
#define AMBIENT22_CONFIG_L_TRANSPARENT          0x0000u
#define AMBIENT22_CONFIG_L_LATCH                0x0010u
#define AMBIENT22_CONFIG_L_MASK                 0x0010u
#define AMBIENT22_CONFIG_POL_LOW                0x0000u
#define AMBIENT22_CONFIG_POL_HIGH               0x0008u
#define AMBIENT22_CONFIG_POL_MASK               0x0008u
#define AMBIENT22_CONFIG_ME_MASK                0x0004u
#define AMBIENT22_CONFIG_FC_ONE                 0x0000u
#define AMBIENT22_CONFIG_FC_TWO                 0x0001u
#define AMBIENT22_CONFIG_FC_FOUR                0x0002u
#define AMBIENT22_CONFIG_FC_EIGHT               0x0003u
#define AMBIENT22_CONFIG_FC_MASK                0x0003u

/**
 * @brief Ambient 22 lux calculation setting.
 * @details Specified setting for lux calculation of Ambient 22 Click driver.
 */
#define AMBIENT22_RESULT_EXP                    0xF000u
#define AMBIENT22_RESULT_FRACT                  0x0FFFu
#define AMBIENT22_RESULT_MIN                    0x0000u
#define AMBIENT22_RESULT_MAX                    0xBFFFu
#define AMBIENT22_RESULT_LUX_PER_LSB            0.02f

/**
 * @brief Ambient 22 device ID setting.
 * @details Specified setting for device ID of Ambient 22 Click driver.
 */
#define AMBIENT22_MANUFACTURER_ID               0x5449u
#define AMBIENT22_DEVICE_ID                     0x3001u

/**
 * @brief Ambient 22 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 22 Click driver.
 */
#define AMBIENT22_DEVICE_ADDRESS_0              0x44
#define AMBIENT22_DEVICE_ADDRESS_1              0x45

/*! @} */ // ambient22_set

/**
 * @defgroup ambient22_map Ambient 22 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 22 Click driver.
 */

/**
 * @addtogroup ambient22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 22 Click to the selected MikroBUS.
 */
#define AMBIENT22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ambient22_map
/*! @} */ // ambient22

/**
 * @brief Ambient 22 Click context object.
 * @details Context object definition of Ambient 22 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;           /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} ambient22_t;

/**
 * @brief Ambient 22 Click configuration object.
 * @details Configuration object definition of Ambient 22 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;             /**< Interrupt pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} ambient22_cfg_t;

/**
 * @brief Ambient 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT22_OK = 0,
    AMBIENT22_ERROR = -1

} ambient22_return_value_t;

/*!
 * @addtogroup ambient22 Ambient 22 Click Driver
 * @brief API for configuring and manipulating Ambient 22 Click driver.
 * @{
 */

/**
 * @brief Ambient 22 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient22_cfg_setup ( ambient22_cfg_t *cfg );

/**
 * @brief Ambient 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ambient22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient22_init ( ambient22_t *ctx, ambient22_cfg_t *cfg );

/**
 * @brief Ambient 22 default configuration function.
 * @details This function executes a default configuration of Ambient 22
 * click board.
 * @param[in] ctx : Click context object.
 * See #ambient22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ambient22_default_cfg ( ambient22_t *ctx );

/**
 * @brief Ambient 22 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient22_write_register ( ambient22_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Ambient 22 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient22_read_register ( ambient22_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Ambient 22 check communication function.
 * @details This function checks the communication by reading and verifying the manufacturer
 * and device identification numbers.
 * @param[in] ctx : Click context object.
 * See #ambient22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient22_check_communication ( ambient22_t *ctx );

/**
 * @brief Ambient 22 read lux function.
 * @details This function checks for a conversion ready flag bit and then reads
 * the ambient light level in lux.
 * @param[in] ctx : Click context object.
 * See #ambient22_t object definition for detailed explanation.
 * @param[out] lux : Ambient light level in lux.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient22_read_lux ( ambient22_t *ctx, float *lux );

/**
 * @brief Ambient 22 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #ambient22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ambient22_get_int_pin ( ambient22_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT22_H

/*! @} */ // ambient22

// ------------------------------------------------------------------------ END
