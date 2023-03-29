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
 * @file current9.h
 * @brief This file contains API for Current 9 Click Driver.
 */

#ifndef CURRENT9_H
#define CURRENT9_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup current9 Current 9 Click Driver
 * @brief API for configuring and manipulating Current 9 Click driver.
 * @{
 */

/**
 * @defgroup current9_set Current 9 Settings
 * @brief Settings of Current 9 Click driver.
 */

/**
 * @addtogroup current9_set
 * @{
 */

/**
 * @brief Current 9 Current calculation values.
 * @details Specified Current calculation values for ADC of Current 9 Click driver.
 */
#define CURRENT9_SENSITIVITY_V_TO_A         0.1333
#define CURRENT9_ZERO_CURRENT_OFFSET        0.500
#define CURRENT9_NUM_CONVERSIONS            200
#define CURRENT9_SENSOR_OUT_DIVIDER_2       2.0
#define CURRENT9_90PCT_VCC                  4.5

/**
 * @brief Current 9 ADC setting.
 * @details Specified settings for ADC of Current 9 Click driver.
 */
#define CURRENT9_ADC_RESOLUTION             0x0FFF
#define CURRENT9_VREF_3V3                   3.3
#define CURRENT9_VREF_5V                    5.0

/**
 * @brief Current 9 device address setting.
 * @details Specified setting for device slave address selection of
 * Current 9 Click driver.
 */
#define CURRENT9_SET_DEV_ADDR               0x4D

/*! @} */ // current9_set

/**
 * @defgroup current9_map Current 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Current 9 Click driver.
 */

/**
 * @addtogroup current9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current 9 Click to the selected MikroBUS.
 */
#define CURRENT9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // current9_map
/*! @} */ // current9

/**
 * @brief Current 9 Click driver selector.
 * @details Selects target driver interface of Current 9 Click driver.
 */
typedef enum
{
    CURRENT9_DRV_SEL_ADC,           /**< ADC driver descriptor. */
    CURRENT9_DRV_SEL_I2C            /**< I2C driver descriptor. */

} current9_drv_t;

/**
 * @brief Current 9 Click context object.
 * @details Context object definition of Current 9 Click driver.
 */
typedef struct
{
    analog_in_t  adc;               /**< ADC module object. */
    i2c_master_t i2c;               /**< I2C driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    float        vref;              /**< ADC reference voltage. */
    current9_drv_t drv_sel;         /**< Master driver interface selector. */

} current9_t;

/**
 * @brief Current 9 Click configuration object.
 * @details Configuration object definition of Current 9 Click driver.
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
    
    current9_drv_t drv_sel;         /**< Master driver interface selector. */

} current9_cfg_t;

/**
 * @brief Current 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENT9_OK = 0,
    CURRENT9_ERROR = -1

} current9_return_value_t;

/*!
 * @addtogroup current9 Current 9 Click Driver
 * @brief API for configuring and manipulating Current 9 Click driver.
 * @{
 */

/**
 * @brief Current 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #current9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void current9_cfg_setup ( current9_cfg_t *cfg );

/**
 * @brief Current 9 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #current9_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #current9_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void current9_drv_interface_selection ( current9_cfg_t *cfg, current9_drv_t drv_sel );

/**
 * @brief Current 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #current9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #current9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current9_init ( current9_t *ctx, current9_cfg_t *cfg );

/**
 * @brief Current 9 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #current9_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current9_read_raw_adc ( current9_t *ctx, uint16_t *raw_adc );

/**
 * @brief Current 9 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #current9_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t current9_read_voltage ( current9_t *ctx, float *voltage );

/**
 * @brief Current 9 set vref function.
 * @details This function sets the voltage reference for Current 9 click driver.
 * @param[in] ctx : Click context object.
 * See #current9_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b current9_init is 3.3V.
 */
err_t current9_set_vref ( current9_t *ctx, float vref );

/**
 * @brief Current 9 read current function.
 * @details This function reads the input current level [A] based on @b CURRENT9_NUM_CONVERSIONS 
 * of voltage measurements.
 * @param[in] ctx : Click context object.
 * See #current9_t object definition for detailed explanation.
 * @param[out] current : Input current level [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For better accuracy, set the voltage reference by using the @b current9_set_vref function,
 * increase the number of conversions by modifying the @b CURRENT9_NUM_CONVERSIONS macro, 
 * and adjust the @b CURRENT9_ZERO_CURRENT_OFFSET voltage value.
 */
err_t current9_read_current ( current9_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // CURRENT9_H

/*! @} */ // current9

// ------------------------------------------------------------------------ END
