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
 * @file ambient12.h
 * @brief This file contains API for Ambient 12 Click Driver.
 */

#ifndef AMBIENT12_H
#define AMBIENT12_H

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
 * @addtogroup ambient12 Ambient 12 Click Driver
 * @brief API for configuring and manipulating Ambient 12 Click driver.
 * @{
 */

/**
 * @defgroup ambient12_set Ambient 12 Registers Settings
 * @brief Settings for registers of Ambient 12 Click driver.
 */

/**
 * @addtogroup ambient12_set
 * @{
 */

/**
 * @brief Ambient 12 device address setting.
 * @details Specified setting for device slave address selection of
 * Ambient 12 Click driver.
 */
#define AMBIENT12_SET_DEV_ADDR           0x4D

/**
 * @brief Ambient 12 ADC setting.
 * @details Specified settings for ADC of Ambient 12 Click driver.
 */
#define AMBIENT12_ADC_RESOLUTION         0x0FFF
#define AMBIENT12_VREF_3V3               3.3

/**
 * @brief Ambient 12 ambient light constants.
 * @details Specified constants for ambient light of Ambient 12 Click driver.
 */
#define AMBIENT12_IOUT_CURRENT_H_GAIN    0.57
#define AMBIENT12_IOUT_CURRENT_M_GAIN    0.057
#define AMBIENT12_IOUT_CURRENT_L_GAIN    0.0057
#define AMBIENT12_MICROAMPER_TO_AMPER    0.000001
#define AMBIENT12_IOUT_RESISTOR          5700

/*! @} */ // ambient12_set

/**
 * @defgroup ambient12_map Ambient 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 12 Click driver.
 */

/**
 * @addtogroup ambient12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 12 Click to the selected MikroBUS.
 */
#define AMBIENT12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.gc1 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.gc2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // ambient12_map
/*! @} */ // ambient12

/**
 * @brief Ambient 12 Click gain mode setting.
 * @details Predefined enum values for gain mode values.
 */
typedef enum
{
    AMBIENT12_MODE_SHUTDOWN,
    AMBIENT12_MODE_H_GAIN,
    AMBIENT12_MODE_M_GAIN,
    AMBIENT12_MODE_L_GAIN

} ambient12_gain_mode_t;

/**
 * @brief Ambient 12 Click context object.
 * @details Context object definition of Ambient 12 Click driver.
 */
typedef struct
{
    digital_out_t  gc1;         /**< Description. */
    digital_out_t  gc2;         /**< Description. */

    analog_in_t  adc;           /**< ADC module object. */
    i2c_master_t i2c;           /**< I2C driver object. */

    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    ambient12_gain_mode_t gain_mode;

} ambient12_t;

/**
 * @brief Ambient 12 Click configuration object.
 * @details Configuration object definition of Ambient 12 Click driver.
 */
typedef struct
{
    pin_name_t  an;             /**< Analog pin descriptor. */
    pin_name_t  gc1;            /**< Description. */
    pin_name_t  gc2;            /**< Description. */
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

    analog_in_resolution_t  resolution; /**< ADC resolution. */
    float                   vref;       /**< ADC reference voltage. */

} ambient12_cfg_t;

/**
 * @brief Ambient 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT12_OK = 0,
    AMBIENT12_ERROR = -1

} ambient12_return_value_t;

/*!
 * @addtogroup ambient12 Ambient 12 Click Driver
 * @brief API for configuring and manipulating Ambient 12 Click driver.
 * @{
 */

/**
 * @brief Ambient 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient12_cfg_setup ( ambient12_cfg_t *cfg );

/**
 * @brief Ambient 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ambient12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient12_init ( ambient12_t *ctx, ambient12_cfg_t *cfg );

/**
 * @brief Ambient 12 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #ambient12_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient12_read_an_pin_value ( ambient12_t *ctx, uint16_t *data_out );

/**
 * @brief Ambient 12 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #ambient12_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t ambient12_read_an_pin_voltage ( ambient12_t *ctx, float *data_out );

/**
 * @brief Ambient 12 read raw ADC function.
 * @details This function reads raw 12-bit ADC data by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient12_t object definition for detailed explanation.
 * @param[out] raw_adc : Raw ADC read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient12_read_raw_adc ( ambient12_t *ctx, uint16_t *raw_adc );

/**
 * @brief Ambient 12 read ADC voltage function.
 * @details This function reads raw 12-bit ADC data and converts it to voltage
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ambient12_t object definition for detailed explanation.
 * @param[out] voltage : Calculated ADC voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient12_read_adc_voltage ( ambient12_t *ctx, float *voltage );

/**
 * @brief Ambient 12 set GC1 pin state function.
 * @details This function sets the GC1 pin to desired logic state.
 * @param[in] ctx : Click context object.
 * See #ambient12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ambient12_set_gc1_pin ( ambient12_t *ctx, uint8_t state );

/**
 * @brief Ambient 12 set GC2 pin state function.
 * @details This function sets the GC2 pin to desired logic state.
 * @param[in] ctx : Click context object.
 * See #ambient12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ambient12_set_gc2_pin ( ambient12_t *ctx, uint8_t state );

/**
 * @brief Ambient 12 set gain mode function.
 * @details This function sets the gain mode.
 * @param[in] ctx : Click context object.
 * See #ambient12_t object definition for detailed explanation.
 * @param[in] mode : @li @c  0 - Shutdown,
 *                   @li @c  1 - H-Gain - up to 1000 Lux,
 *                   @li @c  2 - M-Gain - up to 10000 Lux,
 *                   @li @c  3 - L-Gain - up to 100000 Lux.
 * @return None.
 * @note None.
 */
void ambient12_set_gain_mode ( ambient12_t *ctx, uint8_t mode );

/**
 * @brief Ambient 12 voltage to illuminance function.
 * @details This function calculates illuminance (lux) based on the @b voltage input.
 * @param[in] voltage : Voltage from IOUT (volts).
 * @return @li @c >=0 Illuminance in lux,
 *         @li @c <0  Gain mode error.
 * @note Gain mode must be set before this function call.
 */
int32_t ambient12_voltage_to_lux ( ambient12_t *ctx, float voltage );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT12_H

/*! @} */ // ambient12

// ------------------------------------------------------------------------ END
