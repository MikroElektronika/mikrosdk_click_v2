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
 * @file leddriver14.h
 * @brief This file contains API for LED Driver 14 Click Driver.
 */

#ifndef LEDDRIVER14_H
#define LEDDRIVER14_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup leddriver14 LED Driver 14 Click Driver
 * @brief API for configuring and manipulating LED Driver 14 Click driver.
 * @{
 */

/**
 * @defgroup leddriver14_set LED Driver 14 Registers Settings
 * @brief Settings for registers of LED Driver 14 Click driver.
 */

/**
 * @addtogroup leddriver14_set
 * @{
 */

/**
 * @brief LED Driver 14 rset selection values.
 * @details Specified rset selection values of LED Driver 14 Click driver.
 */
#define LEDDRIVER14_RSET_1                  0
#define LEDDRIVER14_RSET_2                  1
#define LEDDRIVER14_RSET_3                  2
#define LEDDRIVER14_RSET_4                  3

/**
 * @brief LED Driver 14 rset calculation values.
 * @details Specified rset calculation values of LED Driver 14 Click driver.
 */
#define LEDDRIVER14_DIGIPOT_MAX_VALUE       50000
#define LEDDRIVER14_DIGIPOT_RESOLUTION      257
#define LEDDRIVER14_ROUND_TO_NEAREST_INT    0.5
#define LEDDRIVER14_RSET_RES_MAX            24000
#define LEDDRIVER14_RSET_RES_DEFAULT        12000
#define LEDDRIVER14_RSET1_AND_RSET3_ADDRESS 0x10

/**
 * @brief LED Driver 14 rset write protect states.
 * @details Specified rset write protect states of LED Driver 14 Click driver.
 */
#define LEDDRIVER14_WRITE_PROTECT_ENABLE    0
#define LEDDRIVER14_WRITE_PROTECT_DISABLE   1

/**
 * @brief LED Driver 14 device address setting.
 * @details Specified setting for device slave address selection of
 * LED Driver 14 Click driver.
 */
#define LEDDRIVER14_U2_ADDR_A2_GND          0x28
#define LEDDRIVER14_U2_ADDR_A2_VCC          0x2C
#define LEDDRIVER14_U3_ADDR_A2_GND          0x29
#define LEDDRIVER14_U3_ADDR_A2_VCC          0x2D

/**
 * @brief LED Driver 14 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of LED Driver 14 Click driver.
 */
#define LEDDRIVER14_DEF_FREQ                500

/*! @} */ // leddriver14_set

/**
 * @defgroup leddriver14_map LED Driver 14 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Driver 14 Click driver.
 */

/**
 * @addtogroup leddriver14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Driver 14 Click to the selected MikroBUS.
 */
#define LEDDRIVER14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // leddriver14_map
/*! @} */ // leddriver14

/**
 * @brief LED Driver 14 Click context object.
 * @details Context object definition of LED Driver 14 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  wp;              /**< Write protect pin. */

    // Input pins
    digital_in_t  int_pin;          /**< Fault flag pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */
    pwm_t pwm;                      /**< PWM driver object. */

    // I2C slave address
    uint8_t slave_address_u2;       /**< Device slave address for U2 (used for I2C driver). */
    uint8_t slave_address_u3;       /**< Device slave address for U3 (used for I2C driver). */
    uint32_t pwm_freq;              /**< PWM frequency value. */

} leddriver14_t;

/**
 * @brief LED Driver 14 Click configuration object.
 * @details Configuration object definition of LED Driver 14 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  wp;                 /**< Write protect pin. */
    pin_name_t  pwm;                /**< CR Timer setting 1 pin. */
    pin_name_t  int_pin;            /**< Fault flag pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address_u2;       /**< I2C slave address for U2. */
    uint8_t   i2c_address_u3;       /**< I2C slave address for U3. */
    uint32_t  dev_pwm_freq;         /**< PWM frequency value. */

} leddriver14_cfg_t;

/**
 * @brief LED Driver 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDDRIVER14_OK = 0,
    LEDDRIVER14_ERROR = -1

} leddriver14_return_value_t;

/*!
 * @addtogroup leddriver14 LED Driver 14 Click Driver
 * @brief API for configuring and manipulating LED Driver 14 Click driver.
 * @{
 */

/**
 * @brief LED Driver 14 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #leddriver14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void leddriver14_cfg_setup ( leddriver14_cfg_t *cfg );

/**
 * @brief LED Driver 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #leddriver14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #leddriver14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver14_init ( leddriver14_t *ctx, leddriver14_cfg_t *cfg );

/**
 * @brief LED Driver 14 default configuration function.
 * @details This function executes a default configuration of LED Driver 14
 * click board.
 * @param[in] ctx : Click context object.
 * See #leddriver14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t leddriver14_default_cfg ( leddriver14_t *ctx );

/**
 * @brief LED Driver 14 set rset function.
 * @details This function sets the resistance of the selected rset channel.
 * @param[in] ctx : Click context object.
 * See #leddriver14_t object definition for detailed explanation.
 * @param[in] rset : Rset channel [0-3].
 * @param[in] res_ohm : Resistance in Ohm [0-24000].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver14_set_rset ( leddriver14_t *ctx, uint8_t rset, uint16_t res_ohm );

/**
 * @brief LED Driver 14 rset write protect function.
 * @details This function sets the write protect pin logic state.
 * @param[in] ctx : Click context object.
 * See #leddriver14_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Enable write protect,
 *                    @li @c 1 - Disable write protect.
 * @return None.
 * @note None.
 */
void leddriver14_rset_write_protect ( leddriver14_t *ctx, uint8_t state );

/**
 * @brief LED Driver 14 get int pin function.
 * @details This function returns the int pin logic state.
 * @param[in] ctx : Click context object.
 * See #leddriver14_t object definition for detailed explanation.
 * @return @li @c 0 - Abnormality such as LED Open or the OUTx pin short circuit occured,
 *         @li @c 1 - Normal operation.
 * @note None.
 */
uint8_t leddriver14_get_int_pin ( leddriver14_t *ctx );

/**
 * @brief LED Driver 14 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #leddriver14_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver14_set_duty_cycle ( leddriver14_t *ctx, float duty_cycle );

/**
 * @brief LED Driver 14 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #leddriver14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver14_pwm_stop ( leddriver14_t *ctx );

/**
 * @brief LED Driver 14 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #leddriver14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver14_pwm_start ( leddriver14_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LEDDRIVER14_H

/*! @} */ // leddriver14

// ------------------------------------------------------------------------ END
