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
 * @file stepdown8.h
 * @brief This file contains API for Step Down 8 Click Driver.
 */

#ifndef STEPDOWN8_H
#define STEPDOWN8_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup stepdown8 Step Down 8 Click Driver
 * @brief API for configuring and manipulating Step Down 8 Click driver.
 * @{
 */

/**
 * @defgroup stepdown8_reg Step Down 8 Registers List
 * @brief List of registers of Step Down 8 Click driver.
 */

/**
 * @addtogroup stepdown8_reg
 * @{
 */

/**
 * @brief Step Down 8 description register.
 * @details Specified register for description of Step Down 8 Click driver.
 */
#define STEPDOWN8_PFM_PWM_MODE                  0x00
#define STEPDOWN8_FORCED_PWM_MODE               0x01
#define STEPDOWN8_R1_RPROG_ADDRESS              0x00

/*! @} */ // stepdown8_reg

/**
 * @defgroup stepdown8_set Step Down 8 Registers Settings
 * @brief Settings for registers of Step Down 8 Click driver.
 */

/**
 * @addtogroup stepdown8_set
 * @{
 */

/**
 * @brief Step Down 8 description setting.
 * @details Specified setting for description of Step Down 8 Click driver.
 */

#define STEPDOWN8_R1_VALUE                      200000ul
#define STEPDOWN8_DIGIPOT_MAX_VALUE             100000ul
#define STEPDOWN8_DIGIPOT_RESOLUTION            257
#define STEPDOWN8_ROUND_TO_NEAREST_INT          0.5
#define STEPDOWN8_R10_VALUE                     10000u
#define STEPDOWN8_MAX_OUTPUT                    18
#define STEPDOWN8_MIN_OUTPUT                    3

/**
 * @brief Step Down 8 pin state setting.
 * @details Specified setting for pin state of Step Down 8 Click driver.
 */
#define STEPDOWN8_PIN_STATE_HIGH                0x01
#define STEPDOWN8_PIN_STATE_LOW                 0x00

/**
 * @brief Step Down 8 device address setting.
 * @details Specified setting for device slave address selection of
 * Step Down 8 Click driver.
 */
#define STEPDOWN8_ADDR_A2A1A0_000               0x28
#define STEPDOWN8_ADDR_A2A1A0_001               0x29
#define STEPDOWN8_ADDR_A2A1A0_010               0x2A
#define STEPDOWN8_ADDR_A2A1A0_011               0x2B
#define STEPDOWN8_ADDR_A2A1A0_100               0x2C
#define STEPDOWN8_ADDR_A2A1A0_101               0x2D
#define STEPDOWN8_ADDR_A2A1A0_110               0x2E
#define STEPDOWN8_ADDR_A2A1A0_111               0x2F

/*! @} */ // stepdown8_set

/**
 * @defgroup stepdown8_map Step Down 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Step Down 8 Click driver.
 */

/**
 * @addtogroup stepdown8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Step Down 8 Click to the selected MikroBUS.
 */
#define STEPDOWN8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sps = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepdown8_map
/*! @} */ // stepdown8

/**
 * @brief Step Down 8 Click context object.
 * @details Context object definition of Step Down 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin. */
    digital_out_t sps;          /**< Spread-Spectrum Enable. */

    // Input pins
    digital_in_t pg;            /**< Power-good output. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} stepdown8_t;

/**
 * @brief Step Down 8 Click configuration object.
 * @details Configuration object definition of Step Down 8 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin. */
    pin_name_t sps;             /**< Spread-Spectrum Enable. */
    pin_name_t pg;              /**< Power-good output. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepdown8_cfg_t;

/**
 * @brief Step Down 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPDOWN8_OK = 0,
    STEPDOWN8_ERROR = -1

} stepdown8_return_value_t;

/*!
 * @addtogroup stepdown8 Step Down 8 Click Driver
 * @brief API for configuring and manipulating Step Down 8 Click driver.
 * @{
 */

/**
 * @brief Step Down 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepdown8_cfg_setup ( stepdown8_cfg_t *cfg );

/**
 * @brief Step Down 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepdown8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepdown8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown8_init ( stepdown8_t *ctx, stepdown8_cfg_t *cfg );

/**
 * @brief Step Down 8 default configuration function.
 * @details This function executes a default configuration of Step Down 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepdown8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepdown8_default_cfg ( stepdown8_t *ctx );

/**
 * @brief Step Down 8 set EN pin state function.
 * @details This function sets a EN pin state.
 * @param[in] ctx : Click context object.
 * See #stepdown8_t object definition for detailed explanation.
 * @param[in] pin_state : State of the EN pin.
 * @return Nothing.
 * @note None.
 */
void stepdown8_set_en_pin ( stepdown8_t *ctx, uint8_t pin_state );

/**
 * @brief Step Down 8 set SPS pin state function.
 * @details This function sets a SPS pin state.
 * @param[in] ctx : Click context object.
 * See #stepdown8_t object definition for detailed explanation.
 * @param[in] pin_state : State of the SPS pin.
 * @return Nothing.
 * @note None.
 */
void stepdown8_set_sps_pin ( stepdown8_t *ctx, uint8_t pin_state );

/**
 * @brief Step Down 8 get PG pin state function.
 * @details This function is used to get state of the PG pin.
 * @param[in] ctx : Click context object.
 * See #stepdown8_t object definition for detailed explanation.
 * @return State of the PG pin.
 * @note None.
 */
uint8_t stepdown8_get_pg_state ( stepdown8_t *ctx );

/**
 * @brief Step Down 8 set wiper position.
 * @details This function sets a wiper of the potentiometer to the desired position.
 * @param[in] ctx : Click context object.
 * See #stepdown8_t object definition for detailed explanation.
 * @param[in] wiper_pos : Position of the wiper.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown8_set_wiper_pos ( stepdown8_t *ctx, uint16_t wiper_pos );

/**
 * @brief Step Down 8 set potentiometer resistance.
 * @details This function sets a resistance of the potentiometer to the desired value.
 * @param[in] ctx : Click context object.
 * See #stepdown8_t object definition for detailed explanation.
 * @param[in] resistance : Desired resistance.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown8_set_r2_resistance ( stepdown8_t *ctx, uint32_t resistance );

/**
 * @brief Step Down 8 set output voltage.
 * @details This function sets a predefined output level.
 * @param[in] ctx : Click context object.
 * See #stepdown8_t object definition for detailed explanation.
 * @param[in] voltage : Desired output voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown8_set_output ( stepdown8_t *ctx, float voltage );

#ifdef __cplusplus
}
#endif
#endif // STEPDOWN8_H

/*! @} */ // stepdown8

// ------------------------------------------------------------------------ END
