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
 * @file hallcurrent18.h
 * @brief This file contains API for Hall Current 18 Click Driver.
 */

#ifndef HALLCURRENT18_H
#define HALLCURRENT18_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup hallcurrent18 Hall Current 18 Click Driver
 * @brief API for configuring and manipulating Hall Current 18 Click driver.
 * @{
 */


/**
 * @defgroup hallcurrent18_set Hall Current 18 Registers Settings
 * @brief Settings for registers of Hall Current 18 Click driver.
 */

/**
 * @addtogroup hallcurrent18_set
 * @{
 */

/**
 * @brief Hall Current 18 ADC setting.
 * @details Specified settings for ADC of Hall Current 18 Click driver.
 */
#define HALLCURRENT18_ADC_RESOLUTION        0x0FFFu
#define HALLCURRENT18_VREF_3V3              3.3f
#define HALLCURRENT18_VREF_5V               5.0f
#define HALLCURRENT18_HALF_SCALE_3V3        1.65f

/**
 * @brief Hall Current 18 data values to calculate.
 * @details Specified data values to calculate of Hall Current 18 Click driver.
 */
#define HALLCURRENT18_SENSITIVITY_MV_A      33.0f
#define HALLCURRENT18_CONV_TO_MILI          1000.0f
#define HALLCURRENT18_ADC_NUM_OF_MEASURE    500u

/**
 * @brief Hall Current 18 device address setting.
 * @details Specified setting for device slave address selection of
 * Hall Current 18 Click driver.
 */
#define HALLCURRENT18_SET_DEV_ADDR          0x4D

/*! @} */ // hallcurrent18_set

/**
 * @defgroup hallcurrent18_map Hall Current 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 18 Click driver.
 */

/**
 * @addtogroup hallcurrent18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 18 Click to the selected MikroBUS.
 */
#define HALLCURRENT18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );   \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // hallcurrent18_map
/*! @} */ // hallcurrent18

/**
 * @brief Hall Current 18 Click driver selector.
 * @details Selects target driver interface of Hall Current 18 Click driver.
 */
typedef enum
{
    HALLCURRENT18_DRV_SEL_ADC,    /**< ADC driver descriptor. */
    HALLCURRENT18_DRV_SEL_I2C     /**< I2C driver descriptor. */

} hallcurrent18_drv_t;

/**
 * @brief Hall Current 18 Click context object.
 * @details Context object definition of Hall Current 18 Click driver.
 */
typedef struct
{
    analog_in_t  adc;               /**< ADC module object. */
    i2c_master_t i2c;               /**< I2C driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    float        vref;              /**< ADC reference voltage. */
    float        zero_vref;         /**< Zero reference voltage. */
    hallcurrent18_drv_t drv_sel;    /**< Master driver interface selector. */

} hallcurrent18_t;

/**
 * @brief Hall Current 18 Click configuration object.
 * @details Configuration object definition of Hall Current 18 Click driver.
 */
typedef struct
{
    pin_name_t an;     /**< Analog pin descriptor. */
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t resolution;     /**< ADC resolution. */
    float                  vref;           /**< ADC reference voltage. */
    float                  zero_vref;      /**< Zero reference voltage. */
    
    uint32_t               i2c_speed;      /**< I2C serial speed. */
    uint8_t                i2c_address;    /**< I2C slave address. */
    
    hallcurrent18_drv_t drv_sel;           /**< Master driver interface selector. */

} hallcurrent18_cfg_t;

/**
 * @brief Hall Current 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLCURRENT18_OK = 0,
    HALLCURRENT18_ERROR = -1

} hallcurrent18_return_value_t;

/*!
 * @addtogroup hallcurrent18 Hall Current 18 Click Driver
 * @brief API for configuring and manipulating Hall Current 18 Click driver.
 * @{
 */

/**
 * @brief Hall Current 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent18_cfg_setup ( hallcurrent18_cfg_t *cfg );

/**
 * @brief Hall Current 18 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent18_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #hallcurrent18_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void hallcurrent18_drv_interface_selection ( hallcurrent18_cfg_t *cfg, hallcurrent18_drv_t drv_sel );

/**
 * @brief Hall Current 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent18_init ( hallcurrent18_t *ctx, hallcurrent18_cfg_t *cfg );

/**
 * @brief Hall Current 18 default configuration function.
 * @details This function executes a default configuration of Hall Current 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #hallcurrent18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hallcurrent18_default_cfg ( hallcurrent18_t *ctx );

/**
 * @brief Hall Current 18 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #hallcurrent18_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent18_read_raw_adc ( hallcurrent18_t *ctx, uint16_t *raw_adc );

/**
 * @brief Hall Current 18 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent18_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t hallcurrent18_read_voltage ( hallcurrent18_t *ctx, float *voltage );

/**
 * @brief Hall Current 18 set vref function.
 * @details This function sets the voltage reference for Hall Current 18 click driver.
 * @param[in] ctx : Click context object.
 * See #hallcurrent18_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b hallcurrent18_init is 3.3V.
 */
err_t hallcurrent18_set_vref ( hallcurrent18_t *ctx, float vref );

/**
 * @brief Hall Current 18 get current function.
 * @details This function reads and calculate input current value
 * of the MCS1806GS-3-40-P, solated Hall-Effect Current Sensor
 * on the Hall Current 18 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent18_t object definition for detailed explanation.
 * @param[in] current : Current [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent18_read_current ( hallcurrent18_t *ctx, float *current );

/**
 * @brief Hall Current 18 set zero reference function.
 * @details This function sets the zero voltage reference
 * of the MCS1806GS-3-40-P, solated Hall-Effect Current Sensor
 * on the Hall Current 18 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent18_set_zero_ref ( hallcurrent18_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT18_H

/*! @} */ // hallcurrent18

// ------------------------------------------------------------------------ END
