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
 * @file leddriver11.h
 * @brief This file contains API for LED Driver 11 Click Driver.
 */

#ifndef LEDDRIVER11_H
#define LEDDRIVER11_H

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
#include "drv_analog_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup leddriver11 LED Driver 11 Click Driver
 * @brief API for configuring and manipulating LED Driver 11 Click driver.
 * @{
 */

/**
 * @defgroup leddriver11_set LED Driver 11 Settings
 * @brief Settings for LED Driver 11 Click driver.
 */

/**
 * @addtogroup leddriver11_set
 * @{
 */

/**
 * @brief LED Driver 11 LED current settings.
 * @details Specified LED current settings of LED Driver 11 Click driver.
 */
#define LEDDRIVER11_MAX_CURRENT             0x0000
#define LEDDRIVER11_MIN_CURRENT             0x0FFF

/**
 * @brief LED Driver 11 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of LED Driver 11 Click driver.
 */
#define LEDDRIVER11_DEF_FREQ                5000
/**
 * @brief LED Driver 11 device address setting.
 * @details Specified setting for device slave address selection of
 * LED Driver 11 Click driver.
 */
#define LEDDRIVER11_SET_DEV_ADDR            0x60

/*! @} */ // leddriver11_set

/**
 * @defgroup leddriver11_map LED Driver 11 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Driver 11 Click driver.
 */

/**
 * @addtogroup leddriver11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Driver 11 Click to the selected MikroBUS.
 */
#define LEDDRIVER11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // leddriver11_map
/*! @} */ // leddriver11

/**
 * @brief LED Driver 11 Click context object.
 * @details Context object definition of LED Driver 11 Click driver.
 */
typedef struct
{
    // Modules
    analog_in_t  adc;           /**< ADC module object. */
    i2c_master_t i2c;           /**< I2C driver object. */
    pwm_t pwm;                  /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} leddriver11_t;

/**
 * @brief LED Driver 11 Click configuration object.
 * @details Configuration object definition of LED Driver 11 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  an;                         /**< Analog pin descriptor. */
    pin_name_t pwm;                         /**< PWM pin. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float    vref;                          /**< ADC reference voltage. */
    uint32_t i2c_speed;                     /**< I2C serial speed. */
    uint8_t  i2c_address;                   /**< I2C slave address. */
    uint32_t dev_pwm_freq;                  /**< PWM frequency value. */

} leddriver11_cfg_t;

/**
 * @brief LED Driver 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDDRIVER11_OK = 0,
    LEDDRIVER11_ERROR = -1

} leddriver11_return_value_t;

/*!
 * @addtogroup leddriver11 LED Driver 11 Click Driver
 * @brief API for configuring and manipulating LED Driver 11 Click driver.
 * @{
 */

/**
 * @brief LED Driver 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #leddriver11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void leddriver11_cfg_setup ( leddriver11_cfg_t *cfg );

/**
 * @brief LED Driver 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #leddriver11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #leddriver11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver11_init ( leddriver11_t *ctx, leddriver11_cfg_t *cfg );

/**
 * @brief LED Driver 11 default configuration function.
 * @details This function executes a default configuration of LED Driver 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #leddriver11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t leddriver11_default_cfg ( leddriver11_t *ctx );

/**
 * @brief LED Driver 11 set current function.
 * @details This function sets the LEDs current via a 12-bit DAC module.
 * @param[in] ctx : Click context object.
 * See #leddriver11_t object definition for detailed explanation.
 * @param[in] curr : 12-bit DAC value.
 *         @li @c 0 - max current,
 *         @li @c 0xFFF - min current.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver11_set_current ( leddriver11_t *ctx, uint16_t curr );

/**
 * @brief LED Driver 11 read DAC memory.
 * @details This function reads all the DAC module memory.
 * @param[in] ctx : Click context object.
 * See #leddriver11_t object definition for detailed explanation.
 * @param[out] data_out : 6 bytes buffer where the read data is being stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver11_read_dac_memory( leddriver11_t *ctx, uint8_t *data_out );

/**
 * @brief LED Driver 11 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #leddriver11_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver11_read_an_pin_value ( leddriver11_t *ctx, uint16_t *data_out );

/**
 * @brief LED Driver 11 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #leddriver11_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t leddriver11_read_an_pin_voltage ( leddriver11_t *ctx, float *data_out );

/**
 * @brief LED Driver 11 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #leddriver11_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver11_set_duty_cycle ( leddriver11_t *ctx, float duty_cycle );

/**
 * @brief LED Driver 11 stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #leddriver11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver11_pwm_stop ( leddriver11_t *ctx );

/**
 * @brief LED Driver 11 start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #leddriver11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver11_pwm_start ( leddriver11_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LEDDRIVER11_H

/*! @} */ // leddriver11

// ------------------------------------------------------------------------ END
