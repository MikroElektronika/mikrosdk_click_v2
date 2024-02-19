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
 * @file antopwm2.h
 * @brief This file contains API for AN to PWM 2 Click Driver.
 */

#ifndef ANTOPWM2_H
#define ANTOPWM2_H

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
 * @addtogroup antopwm2 AN to PWM 2 Click Driver
 * @brief API for configuring and manipulating AN to PWM 2 Click driver.
 * @{
 */

/**
 * @defgroup antopwm2_set AN to PWM 2 Registers Settings
 * @brief Settings for registers of AN to PWM 2 Click driver.
 */

/**
 * @addtogroup antopwm2_set
 * @{
 */

/**
 * @brief AN to PWM 2 digipot register setting.
 * @details Specified setting for digipot register of AN to PWM 2 Click driver.
 */
#define ANTOPWM2_OTP_BIT                0x80
#define ANTOPWM2_STATUS_READY           0x00
#define ANTOPWM2_STATUS_TEST_FUSE       0x40
#define ANTOPWM2_STATUS_FATAL_ERROR     0x80
#define ANTOPWM2_STATUS_OTP_SUCCESS     0xC0
#define ANTOPWM2_STATUS_MASK            0xC0

/**
 * @brief AN to PWM 2 digipot setting.
 * @details Specified setting for digipot of AN to PWM 2 Click driver.
 */
#define ANTOPWM2_DIGIPOT_WIPER_MAX      0x3F
#define ANTOPWM2_DIGIPOT_R6             49900u
#define ANTOPWM2_DIGIPOT_WIPER_RES      60
#define ANTOPWM2_DIGIPOT_MAX_RES        50000u

/**
 * @brief AN to PWM 2 setting.
 * @details Specified setting of AN to PWM 2 Click driver.
 */
#define ANTOPWM2_FREQ_MAX               1000000ul
#define ANTOPWM2_FREQ_MIN               500000ul
#define ANTOPWM2_RSET_REF               50000u
#define ANTOPWM2_NDIV                   1

/**
 * @brief AN to PWM 2 device address setting.
 * @details Specified setting for device slave address selection of
 * AN to PWM 2 Click driver.
 */
#define ANTOPWM2_DEVICE_ADDRESS         0x2C

/*! @} */ // antopwm2_set

/**
 * @defgroup antopwm2_map AN to PWM 2 MikroBUS Map
 * @brief MikroBUS pin mapping of AN to PWM 2 Click driver.
 */

/**
 * @addtogroup antopwm2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AN to PWM 2 Click to the selected MikroBUS.
 */
#define ANTOPWM2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // antopwm2_map
/*! @} */ // antopwm2

/**
 * @brief AN to PWM 2 Click context object.
 * @details Context object definition of AN to PWM 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< PWM output pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} antopwm2_t;

/**
 * @brief AN to PWM 2 Click configuration object.
 * @details Configuration object definition of AN to PWM 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< PWM output pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} antopwm2_cfg_t;

/**
 * @brief AN to PWM 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ANTOPWM2_OK = 0,
    ANTOPWM2_ERROR = -1

} antopwm2_return_value_t;

/*!
 * @addtogroup antopwm2 AN to PWM 2 Click Driver
 * @brief API for configuring and manipulating AN to PWM 2 Click driver.
 * @{
 */

/**
 * @brief AN to PWM 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #antopwm2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void antopwm2_cfg_setup ( antopwm2_cfg_t *cfg );

/**
 * @brief AN to PWM 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #antopwm2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #antopwm2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t antopwm2_init ( antopwm2_t *ctx, antopwm2_cfg_t *cfg );

/**
 * @brief AN to PWM 2 set digipot function.
 * @details This function sets a digipot wiper position by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #antopwm2_t object definition for detailed explanation.
 * @param[in] wiper : Digipot wiper to be set (0-63).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t antopwm2_set_digipot ( antopwm2_t *ctx, uint8_t wiper );

/**
 * @brief AN to PWM 2 read digipot function.
 * @details This function reads a digipot wiper position and status by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #antopwm2_t object definition for detailed explanation.
 * @param[out] data_out : Output data read: B7-B6 -> status, B5-B0 -> wiper position.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t antopwm2_read_digipot ( antopwm2_t *ctx, uint8_t *data_out );

/**
 * @brief AN to PWM 2 set digipot otp function.
 * @details This function sets a digipot wiper position in OTP mode by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #antopwm2_t object definition for detailed explanation.
 * @param[in] wiper : Digipot wiper to be set (0-63).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function performs one-time programming, so afterwards no further programming is possible.
 */
err_t antopwm2_set_digipot_otp ( antopwm2_t *ctx, uint8_t wiper );

/**
 * @brief AN to PWM 2 set frequency function.
 * @details This function sets a frequency output in a range from 500kHz to 1MHz by setting
 * the digipot resistance.
 * @param[in] ctx : Click context object.
 * See #antopwm2_t object definition for detailed explanation.
 * @param[in] freq : Frequency in Hz to be set (500000-1000000).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t antopwm2_set_frequency ( antopwm2_t *ctx, uint32_t freq );

/**
 * @brief AN to PWM 2 set frequency otp function.
 * @details This function sets a frequency output in a range from 500kHz to 1MHz by setting
 * the digipot resistance in OTP mode.
 * @param[in] ctx : Click context object.
 * See #antopwm2_t object definition for detailed explanation.
 * @param[in] freq : Frequency in Hz to be set (500000-1000000).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function performs one-time programming, so afterwards no further programming is possible.
 */
err_t antopwm2_set_frequency_otp ( antopwm2_t *ctx, uint32_t freq );

/**
 * @brief AN to PWM 2 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #antopwm2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t antopwm2_get_int_pin ( antopwm2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ANTOPWM2_H

/*! @} */ // antopwm2

// ------------------------------------------------------------------------ END
