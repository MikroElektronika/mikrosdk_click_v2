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
 * @file current11.h
 * @brief This file contains API for Current 11 Click Driver.
 */

#ifndef CURRENT11_H
#define CURRENT11_H

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
 * @addtogroup current11 Current 11 Click Driver
 * @brief API for configuring and manipulating Current 11 Click driver.
 * @{
 */

/**
 * @defgroup current11_set Current 11 Registers Settings
 * @brief Settings for registers of Current 11 Click driver.
 */

/**
 * @addtogroup current11_set
 * @{
 */

/**
 * @brief Current 11 Current calculation values.
 * @details Specified Current calculation values for ADC of Current 11 Click driver.
 */
#define CURRENT11_SENSITIVITY_V_G           0.006f
#define CURRENT11_COUPLING_FACTOR_G_A       4.66f
#define CURRENT11_NUM_CONVERSIONS           200
#define CURRENT11_SENSOR_OUT_DIVIDER_2      2.0f
#define CURRENT11_SENSOR_VREF               2.5f

/**
 * @brief Current 11 ADC setting.
 * @details Specified settings for ADC of Current 11 Click driver.
 */
#define CURRENT11_ADC_RESOLUTION            0x0FFF
#define CURRENT11_VREF_3V3                  3.3f
#define CURRENT11_VREF_5V                   5.0f

/**
 * @brief Current 11 device address setting.
 * @details Specified setting for device slave address selection of
 * Current 11 Click driver.
 */
#define CURRENT11_SET_DEV_ADDR              0x4D

/*! @} */ // current11_set

/**
 * @defgroup current11_map Current 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Current 11 Click driver.
 */

/**
 * @addtogroup current11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current 11 Click to the selected MikroBUS.
 */
#define CURRENT11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // current11_map
/*! @} */ // current11

/**
 * @brief Current 11 Click driver selector.
 * @details Selects target driver interface of Current 11 Click driver.
 */
typedef enum
{
    CURRENT11_DRV_SEL_ADC,          /**< ADC driver descriptor. */
    CURRENT11_DRV_SEL_I2C           /**< I2C driver descriptor. */

} current11_drv_t;

/**
 * @brief Current 11 Click context object.
 * @details Context object definition of Current 11 Click driver.
 */
typedef struct
{
    analog_in_t  adc;               /**< ADC module object. */
    i2c_master_t i2c;               /**< I2C driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    float        vref;              /**< ADC reference voltage. */
    current11_drv_t drv_sel;        /**< Master driver interface selector. */

    float        zero_curr_offset;  /**< Voltage offset for zero current value. */

} current11_t;

/**
 * @brief Current 11 Click configuration object.
 * @details Configuration object definition of Current 11 Click driver.
 */
typedef struct
{
    pin_name_t an;                  /**< Analog pin descriptor. */
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t resolution;      /**< ADC resolution. */
    float                  vref;            /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;       /**< I2C serial speed. */
    uint8_t                i2c_address;     /**< I2C slave address. */
    
    current11_drv_t drv_sel;                /**< Master driver interface selector. */

} current11_cfg_t;

/**
 * @brief Current 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENT11_OK = 0,
    CURRENT11_ERROR = -1

} current11_return_value_t;

/*!
 * @addtogroup current11 Current 11 Click Driver
 * @brief API for configuring and manipulating Current 11 Click driver.
 * @{
 */

/**
 * @brief Current 11 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #current11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void current11_cfg_setup ( current11_cfg_t *cfg );

/**
 * @brief Current 11 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #current11_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #current11_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void current11_drv_interface_sel ( current11_cfg_t *cfg, current11_drv_t drv_sel );

/**
 * @brief Current 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #current11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #current11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current11_init ( current11_t *ctx, current11_cfg_t *cfg );

/**
 * @brief Current 11 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #current11_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current11_read_raw_adc ( current11_t *ctx, uint16_t *raw_adc );

/**
 * @brief Current 11 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #current11_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t current11_read_voltage ( current11_t *ctx, float *voltage );

/**
 * @brief Current 11 set vref function.
 * @details This function sets the voltage reference for Current 11 Click driver.
 * @param[in] ctx : Click context object.
 * See #current11_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b current11_init is 3.3V.
 */
err_t current11_set_vref ( current11_t *ctx, float vref );

/**
 * @brief Current 11 calibrate offset function.
 * @details This function calibrates the zero current offset value.
 * @param[in] ctx : Click context object.
 * See #current11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when no current flows through the sensor.
 */
err_t current11_calibrate_offset ( current11_t *ctx );

/**
 * @brief Current 11 read current function.
 * @details This function reads the input current level [A] based on @b CURRENT11_NUM_CONVERSIONS 
 * of voltage measurements.
 * @param[in] ctx : Click context object.
 * See #current11_t object definition for detailed explanation.
 * @param[out] current : Input current level [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For better accuracy, set the voltage reference by using the @b current11_set_vref function,
 * increase the number of conversions by modifying the @b CURRENT11_NUM_CONVERSIONS macro, 
 * and adjust the @b CURRENT11_COUPLING_FACTOR_G_A value.
 */
err_t current11_read_current ( current11_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // CURRENT11_H

/*! @} */ // current11

// ------------------------------------------------------------------------ END
