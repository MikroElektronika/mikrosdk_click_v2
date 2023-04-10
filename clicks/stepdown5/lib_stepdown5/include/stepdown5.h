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
 * @file stepdown5.h
 * @brief This file contains API for Step Down 5 Click Driver.
 */

#ifndef STEPDOWN5_H
#define STEPDOWN5_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup stepdown5 Step Down 5 Click Driver
 * @brief API for configuring and manipulating Step Down 5 Click driver.
 * @{
 */

/**
 * @defgroup stepdown5_set Step Down 5 Registers Settings
 * @brief Settings for registers of Step Down 5 Click driver.
 */

/**
 * @addtogroup stepdown5_set
 * @{
 */

/**
 * @brief Step Down 5 description setting.
 * @details Specified setting for description of Step Down 5 Click driver.
 */
#define STEPDOWN5_PFM_PWM_MODE                  0x00
#define STEPDOWN5_FORCED_PWM_MODE               0x01
#define STEPDOWN5_R1_RPROG_ADDRESS              0x00
#define STEPDOWN5_R2_RPROG_ADDRESS              0x10

/**
 * @brief Step Down 5 calculation setting.
 * @details Specified setting for calculation of Step Down 5 Click driver.
 */
#define STEPDOWN5_DIGIPOT_MAX_VALUE             100000ul
#define STEPDOWN5_DIGIPOT_RESOLUTION            257
#define STEPDOWN5_ROUND_TO_NEAREST_INT          0.5

/**
 * @brief Step Down 5 output voltage setting.
 * @details Specified setting for output voltage of Step Down 5 Click driver.
 */
#define STEPDOWN5_OUTPUT_0V6                    1
#define STEPDOWN5_OUTPUT_1V5                    2
#define STEPDOWN5_OUTPUT_2V5                    3
#define STEPDOWN5_OUTPUT_3V3                    4
#define STEPDOWN5_OUTPUT_5V                     5

/**
 * @brief Step Down 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Step Down 5 Click driver.
 */
#define STEPDOWN5_ADDR_A2A1A0_000               0x28
#define STEPDOWN5_ADDR_A2A1A0_001               0x29
#define STEPDOWN5_ADDR_A2A1A0_010               0x2A
#define STEPDOWN5_ADDR_A2A1A0_011               0x2B
#define STEPDOWN5_ADDR_A2A1A0_100               0x2C
#define STEPDOWN5_ADDR_A2A1A0_101               0x2D
#define STEPDOWN5_ADDR_A2A1A0_110               0x2E
#define STEPDOWN5_ADDR_A2A1A0_111               0x2F

/*! @} */ // stepdown5_set

/**
 * @defgroup stepdown5_map Step Down 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Step Down 5 Click driver.
 */

/**
 * @addtogroup stepdown5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Step Down 5 Click to the selected MikroBUS.
 */
#define STEPDOWN5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.md = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepdown5_map
/*! @} */ // stepdown5

/**
 * @brief Step Down 5 Click context object.
 * @details Context object definition of Step Down 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t md;           /**< Power-good output. */

    // Input pins
    digital_in_t pg;            /**< Mode pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} stepdown5_t;

/**
 * @brief Step Down 5 Click configuration object.
 * @details Configuration object definition of Step Down 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t md;              /**< Mode pin. */
    pin_name_t pg;              /**< Power-good output. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepdown5_cfg_t;

/**
 * @brief Step Down 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPDOWN5_OK = 0,
    STEPDOWN5_ERROR = -1

} stepdown5_return_value_t;

/*!
 * @addtogroup stepdown5 Step Down 5 Click Driver
 * @brief API for configuring and manipulating Step Down 5 Click driver.
 * @{
 */

/**
 * @brief Step Down 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepdown5_cfg_setup ( stepdown5_cfg_t *cfg );

/**
 * @brief Step Down 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepdown5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepdown5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown5_init ( stepdown5_t *ctx, stepdown5_cfg_t *cfg );

/**
 * @brief Step Down 5 default configuration function.
 * @details This function executes a default configuration of Step Down 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepdown5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepdown5_default_cfg ( stepdown5_t *ctx );

/**
 * @brief Step Down 5 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown5_generic_write ( stepdown5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Step Down 5 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown5_generic_read ( stepdown5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Step Down 5 mode selection function.
 * @details This function sets a desired mode of the PWM.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown5_cfg_t object definition for detailed explanation.
 * @param[in] mode : PWM/Sync mode.
 * @return Nothing.
 * @note None.
 */
void stepdown5_set_mode ( stepdown5_t *ctx, uint8_t mode );

/**
 * @brief Step Down 5 get PG pin state function.
 * @details This function is used to get state of the PG pin.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown5_cfg_t object definition for detailed explanation.
 * @return State of the PG pin.
 * @note None.
 */
uint8_t stepdown5_get_pg_state ( stepdown5_t *ctx );

/**
 * @brief Step Down 5 set wiper 0 position.
 * @details This function sets a wiper of the potentiometer 0 to the desired position.
 * @param[in] ctx : Click context object.
 * See #stepdown5_t object definition for detailed explanation.
 * @param[in] wiper_0_pos : Position of the wiper.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown5_set_wiper_0_pos ( stepdown5_t *ctx, uint16_t wiper_0_pos );

/**
 * @brief Step Down 5 set wiper 1 position.
 * @details This function sets a wiper of the potentiometer 1 to the desired position.
 * @param[in] ctx : Click context object.
 * See #stepdown5_t object definition for detailed explanation.
 * @param[in] wiper_1_pos : Position of the wiper.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown5_set_wiper_1_pos ( stepdown5_t *ctx, uint16_t wiper_1_pos );

/**
 * @brief Step Down 5 set potentiometer 0 resistance.
 * @details This function sets a resistance of the potentiometer 0 to the desired value.
 * @param[in] ctx : Click context object.
 * See #stepdown5_t object definition for detailed explanation.
 * @param[in] resistance : Desired resistance.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown5_set_r1_resistance ( stepdown5_t *ctx, uint32_t resistance );

/**
 * @brief Step Down 5 set potentiometer 1 resistance.
 * @details This function sets a resistance of the potentiometer 1 to the desired value.
 * @param[in] ctx : Click context object.
 * See #stepdown5_t object definition for detailed explanation.
 * @param[in] resistance : Desired resistance.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown5_set_r2_resistance ( stepdown5_t *ctx, uint32_t resistance );

/**
 * @brief Step Down 5 set output voltage.
 * @details This function sets a predefined output level.
 * @param[in] ctx : Click context object.
 * See #stepdown5_t object definition for detailed explanation.
 * @param[in] voltage : Desired output voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown5_set_output ( stepdown5_t *ctx, uint8_t voltage );

#ifdef __cplusplus
}
#endif
#endif // STEPDOWN5_H

/*! @} */ // stepdown5

// ------------------------------------------------------------------------ END
