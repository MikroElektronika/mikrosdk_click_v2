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
 * @file stepdown6.h
 * @brief This file contains API for Step Down 6 Click Driver.
 */

#ifndef STEPDOWN6_H
#define STEPDOWN6_H

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
 * @addtogroup stepdown6 Step Down 6 Click Driver
 * @brief API for configuring and manipulating Step Down 6 Click driver.
 * @{
 */

/**
 * @defgroup stepdown6_reg Step Down 6 Registers List
 * @brief List of registers of Step Down 6 Click driver.
 */

/**
 * @addtogroup stepdown6_reg
 * @{
 */

/**
 * @brief Step Down 6 description register.
 * @details Specified register for description of Step Down 6 Click driver.
 */
#define STEPDOWN6_REG_BUCK1_CTRL1               0x00
#define STEPDOWN6_REG_BUCK1_CTRL2               0x01
#define STEPDOWN6_REG_BUCK1_CTRL3               0x02
#define STEPDOWN6_REG_BUCK2_CTRL1               0x03
#define STEPDOWN6_REG_BUCK2_CTRL2               0x04
#define STEPDOWN6_REG_BUCK2_CTRL3               0x05
#define STEPDOWN6_REG_BUCK3_CTRL1               0x06
#define STEPDOWN6_REG_BUCK3_CTRL2               0x07
#define STEPDOWN6_REG_BUCK3_CTRL3               0x08
#define STEPDOWN6_REG_BUCK4_CTRL1               0x09
#define STEPDOWN6_REG_BUCK4_CTRL2               0x0A
#define STEPDOWN6_REG_BUCK4_CTRL3               0x0B
#define STEPDOWN6_REG_SYSTEM_CTRL1              0x0C
#define STEPDOWN6_REG_SYSTEM_CTRL2              0x0D
#define STEPDOWN6_REG_SYSTEM_CTRL3              0x0E
#define STEPDOWN6_REG_SYSTEM_CTRL4              0x0F
#define STEPDOWN6_REG_SYSTEM_CTRL5              0x10
#define STEPDOWN6_REG_SYSTEM_CTRL6              0x11
#define STEPDOWN6_REG_STATUS                    0x12
#define STEPDOWN6_REG_SYSTEM_CTRL7              0x13

/*! @} */ // stepdown6_reg

/**
 * @defgroup stepdown6_set Step Down 6 Registers Settings
 * @brief Settings for registers of Step Down 6 Click driver.
 */

/**
 * @addtogroup stepdown6_set
 * @{
 */

/**
 * @brief Step Down 6 description setting.
 * @details Specified setting for description of Step Down 6 Click driver.
 */

/**
 * @brief Step Down 6 Control 1 register setting.
 * @details Specified setting for Control 1 register of Step Down 6 Click driver.
 */
#define STEPDOWN6_SOFT_START_DLY_0_MS           0x00
#define STEPDOWN6_SOFT_START_DLY_1_MS           0x10
#define STEPDOWN6_SOFT_START_DLY_2_MS           0x20
#define STEPDOWN6_SOFT_START_DLY_3_MS           0x30
#define STEPDOWN6_SOFT_ADD_DLY_100_US           0x08
#define STEPDOWN6_SOFT_START_CFG0               0x00
#define STEPDOWN6_SOFT_START_CFG1               0x01
#define STEPDOWN6_SOFT_START_CFG2               0x02
#define STEPDOWN6_SOFT_START_CFG3               0x03
#define STEPDOWN6_SOFT_START_CFG4               0x04
#define STEPDOWN6_SOFT_START_CFG5               0x05
#define STEPDOWN6_SOFT_START_CFG6               0x06
#define STEPDOWN6_SOFT_START_CFG7               0x07

/**
 * @brief Step Down 6 Control 2 register setting.
 * @details Specified setting for Control 2 register of Step Down 6 Click driver.
 */
#define STEPDOWN6_VOUT_LIMIT_FB_EN              0x80
#define STEPDOWN6_VOUT_LIMIT_I2C_EN             0x00
#define STEPDOWN6_MODE_AUTO_PWM                 0x00
#define STEPDOWN6_MODE_FORCED_PWM               0x40
#define STEPDOWN6_CURRENT_LIM_1A                0x00
#define STEPDOWN6_CURRENT_LIM_2A                0x10
#define STEPDOWN6_CURRENT_LIM_3A                0x20
#define STEPDOWN6_CURRENT_LIM_4A                0x30
#define STEPDOWN6_VOUT_OVP_EN                   0x08
#define STEPDOWN6_PH_DELAY_0                    0x00
#define STEPDOWN6_PH_DELAY_90                   0x02
#define STEPDOWN6_PH_DELAY_180                  0x04
#define STEPDOWN6_PH_DELAY_270                  0x06
#define STEPDOWN6_VOUT_DIS_EN                   0x01

/**
 * @brief Step Down 6 Control 3 register setting.
 * @details Specified setting for Control 3 register of Step Down 6 Click driver.
 */
#define STEPDOWN6_VOUT_SELECT                   0x80
#define STEPDOWN6_VOUT_REF                      0x7F

/**
 * @brief Step Down 6 System control 1 register setting.
 * @details Specified setting for System control 1 register of Step Down 6 Click driver.
 */
#define STEPDOWN6_EN1_OUTPUT                    0x80
#define STEPDOWN6_EN2_OUTPUT                    0x40
#define STEPDOWN6_EN3_OUTPUT                    0x20
#define STEPDOWN6_EN4_OUTPUT                    0x10
#define STEPDOWN6_UVLO_TH_3V5                   0x00
#define STEPDOWN6_UVLO_TH_4V5                   0x02
#define STEPDOWN6_UVLO_TH_5V8                   0x04
#define STEPDOWN6_UVLO_TH_8V5                   0x06

/**
 * @brief Step Down 6 System control 2 register setting.
 * @details Specified setting for System control 2 register of Step Down 6 Click driver.
 */
#define STEPDOWN6_FREQ_533_HZ                   0x00
#define STEPDOWN6_FREQ_800_HZ                   0x40
#define STEPDOWN6_FREQ_1060_HZ                  0x80
#define STEPDOWN6_FREQ_1600_HZ                  0xC0
#define STEPDOWN6_SHUTDOWN_DELAY_EN             0x20

/**
 * @brief Step Down 6 System control 3 register setting.
 * @details Specified setting for System control 3 register of Step Down 6 Click driver.
 */
#define STEPDOWN6_PG_DELAY_200_US               0x00
#define STEPDOWN6_PG_DELAY_5_MS                 0x04
#define STEPDOWN6_PG_DELAY_25_MS                0x08
#define STEPDOWN6_PG_DELAY_75_MS                0x0C
#define STEPDOWN6_PG_DELAY_200_MS               0x10
#define STEPDOWN6_PARALLEL_2_EN                 0x02
#define STEPDOWN6_PARALLEL_1_EN                 0x01

/**
 * @brief Step Down 6 Output selection setting.
 * @details Specified setting for Output selection of Step Down 6 Click driver.
 */
#define STEPDOWN6_SELECT_VOUT1                  0x00
#define STEPDOWN6_SELECT_VOUT2                  0x01
#define STEPDOWN6_SELECT_VOUT3                  0x02
#define STEPDOWN6_SELECT_VOUT4                  0x03

/**
 * @brief Step Down 6 Pin state setting.
 * @details Specified setting for Pin state of Step Down 6 Click driver.
 */
#define STEPDOWN6_PIN_STATE_HIGH                0x01
#define STEPDOWN6_PIN_STATE_LOW                 0x00

/**
 * @brief Step Down 6 Calculation setting.
 * @details Specified setting for Calculation of Step Down 6 Click driver.
 */
#define STEPDOWN6_MIN_VOUT_VAL                  550
#define STEPDOWN6_MAX_VOUT_VAL                  1820
#define STEPDOWN6_INCREMENT_VOUT_VAL            10

/**
 * @brief Step Down 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Step Down 6 Click driver.
 */
#define STEPDOWN6_DEVICE_ADDRESS                0x68

/*! @} */ // stepdown6_set

/**
 * @defgroup stepdown6_map Step Down 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Step Down 6 Click driver.
 */

/**
 * @addtogroup stepdown6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Step Down 6 Click to the selected MikroBUS.
 */
#define STEPDOWN6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // stepdown6_map
/*! @} */ // stepdown6

/**
 * @brief Step Down 6 Click context object.
 * @details Context object definition of Step Down 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} stepdown6_t;

/**
 * @brief Step Down 6 Click configuration object.
 * @details Configuration object definition of Step Down 6 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepdown6_cfg_t;

/**
 * @brief Step Down 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPDOWN6_OK = 0,
    STEPDOWN6_ERROR = -1

} stepdown6_return_value_t;

/*!
 * @addtogroup stepdown6 Step Down 6 Click Driver
 * @brief API for configuring and manipulating Step Down 6 Click driver.
 * @{
 */

/**
 * @brief Step Down 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepdown6_cfg_setup ( stepdown6_cfg_t *cfg );

/**
 * @brief Step Down 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepdown6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepdown6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown6_init ( stepdown6_t *ctx, stepdown6_cfg_t *cfg );

/**
 * @brief Step Down 6 default configuration function.
 * @details This function executes a default configuration of Step Down 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepdown6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepdown6_default_cfg ( stepdown6_t *ctx );

/**
 * @brief Step Down 6 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown6_generic_write ( stepdown6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Step Down 6 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown6_generic_read ( stepdown6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Step Down 6 set EN pin state function.
 * @details This function is used to set state of the EN pin.
 * @param[in] ctx : Click context object.
 * See #stepdown6_t object definition for detailed explanation.
 * @param[in] pin_state : State of the EN pin.
 * @return Nothing.
 * @note None.
 */
void stepdown6_set_en_pin ( stepdown6_t *ctx, uint8_t pin_state );

/**
 * @brief Step Down 6 Register writing function.
 * @details This function writes a data byte into
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown6_write_reg ( stepdown6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Step Down 6 Register reading function.
 * @details This function reads a data byte from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown6_read_reg ( stepdown6_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Step Down 6 Set output voltage function.
 * @details This function sets the selected voltage output of the selected channel.
 * @param[in] ctx : Click context object.
 * See #stepdown6_t object definition for detailed explanation.
 * @param[in] out_sel : Output voltage selection.
 * @param[in] out_val : Output voltage value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Value of the output voltage can be set in ranges from 550 mV to 1820 mV.
 */
err_t stepdown6_set_out_voltage ( stepdown6_t *ctx, uint8_t out_sel, uint16_t out_val );

#ifdef __cplusplus
}
#endif
#endif // STEPDOWN6_H

/*! @} */ // stepdown6

// ------------------------------------------------------------------------ END
