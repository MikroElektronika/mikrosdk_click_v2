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
 * @file magneto9.h
 * @brief This file contains API for Magneto 9 Click Driver.
 */

#ifndef MAGNETO9_H
#define MAGNETO9_H

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
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup magneto9 Magneto 9 Click Driver
 * @brief API for configuring and manipulating Magneto 9 Click driver.
 * @{
 */

/**
 * @defgroup magneto9_set Magneto 9 Registers Settings
 * @brief Settings for registers of Magneto 9 Click driver.
 */

/**
 * @addtogroup magneto9_set
 * @{
 */

/**
 * @brief Magneto 9 device address setting.
 * @details Specified setting for device slave address selection of
 * Magneto 9 Click driver.
 */
#define MAGNETO9_SET_DEV_ADDR           0x4D

/**
 * @brief Magneto 9 ADC setting.
 * @details Specified settings for ADC of Magneto 9 Click driver.
 */
#define MAGNETO9_ADC_RESOLUTION         0x0FFF
#define MAGNETO9_VREF_5V                5.0

/**
 * @brief Magneto 9 magnetic field strength constants.
 * @details Specified constants for magnetic field strength of Magneto 9 Click driver.
 */
#define MAGNETO9_QUIESCENT_VOUT         2.5
#define MAGNETO9_AN_SENSITIVITY_V_PER_G 0.009
#define MAGNETO9_GAUSS_TO_MILITESLA     0.1

/**
 * @brief Magneto 9 voltage to magnetic field strength macro.
 * @details This macro calculates magnetic field strength (militesla) based on the @b voltage input.
 * @param[in] voltage : Voltage from VOUT (volts).
 * @return Magnetic field strength in militesla.
 * @note A negative value indicates the North Pole magnetic field, whereas a positive value indicates the South Pole.
 */
#define MAGNETO9_VOLTAGE_TO_FIELD_STRENGTH( voltage )   ( ( ( voltage - MAGNETO9_QUIESCENT_VOUT ) / \
                                                            MAGNETO9_AN_SENSITIVITY_V_PER_G ) * \
                                                          MAGNETO9_GAUSS_TO_MILITESLA )

/*! @} */ // magneto9_set

/**
 * @defgroup magneto9_map Magneto 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Magneto 9 Click driver.
 */

/**
 * @addtogroup magneto9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magneto 9 Click to the selected MikroBUS.
 */
#define MAGNETO9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // magneto9_map
/*! @} */ // magneto9

/**
 * @brief Magneto 9 Click context object.
 * @details Context object definition of Magneto 9 Click driver.
 */
typedef struct
{
    digital_in_t pwm;           /**< PWM pin input. */

    analog_in_t  adc;           /**< ADC module object. */    
    i2c_master_t i2c;           /**< I2C driver object. */

    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} magneto9_t;

/**
 * @brief Magneto 9 Click configuration object.
 * @details Configuration object definition of Magneto 9 Click driver.
 */
typedef struct
{
    pin_name_t  an;             /**< Analog pin descriptor. */
    pin_name_t  pwm;            /**< PWM pin input. */
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

    analog_in_resolution_t  resolution;  /**< ADC resolution. */
    float                   vref;        /**< ADC reference voltage. */

} magneto9_cfg_t;

/**
 * @brief Magneto 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGNETO9_OK = 0,
    MAGNETO9_ERROR = -1

} magneto9_return_value_t;

/*!
 * @addtogroup magneto9 Magneto 9 Click Driver
 * @brief API for configuring and manipulating Magneto 9 Click driver.
 * @{
 */

/**
 * @brief Magneto 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magneto9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magneto9_cfg_setup ( magneto9_cfg_t *cfg );

/**
 * @brief Magneto 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #magneto9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magneto9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto9_init ( magneto9_t *ctx, magneto9_cfg_t *cfg );

/**
 * @brief Magneto 9 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #magneto9_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto9_read_an_pin_value ( magneto9_t *ctx, uint16_t *data_out );

/**
 * @brief Magneto 9 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #magneto9_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t magneto9_read_an_pin_voltage ( magneto9_t *ctx, float *data_out );

/**
 * @brief Magneto 9 read raw ADC function.
 * @details This function reads raw 12-bit ADC data by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto9_t object definition for detailed explanation.
 * @param[out] raw_adc : Raw ADC read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto9_read_raw_adc ( magneto9_t *ctx, uint16_t *raw_adc );

/**
 * @brief Magneto 9 read ADC voltage function.
 * @details This function reads raw 12-bit ADC data and converts it to voltage
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #magneto9_t object definition for detailed explanation.
 * @param[out] voltage : Calculated ADC voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneto9_read_adc_voltage ( magneto9_t *ctx, float *voltage );

/**
 * @brief Magneto 9 get PWM pin function.
 * @details This function returns the PWM pin logic state.
 * @param[in] ctx : Click context object.
 * See #magneto9_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t magneto9_get_pwm_pin ( magneto9_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // MAGNETO9_H

/*! @} */ // magneto9

// ------------------------------------------------------------------------ END
