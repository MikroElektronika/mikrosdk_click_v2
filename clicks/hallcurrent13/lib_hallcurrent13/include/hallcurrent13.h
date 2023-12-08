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
 * @file hallcurrent13.h
 * @brief This file contains API for Hall Current 13 Click Driver.
 */

#ifndef HALLCURRENT13_H
#define HALLCURRENT13_H

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
#include "drv_analog_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup hallcurrent13 Hall Current 13 Click Driver
 * @brief API for configuring and manipulating Hall Current 13 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent13_set Hall Current 13 Settings
 * @brief Settings for Hall Current 13 Click driver.
 */

/**
 * @addtogroup hallcurrent13_set
 * @{
 */

/**
 * @brief Hall Current 13 Current calculation values.
 * @details Specified Current calculation values for ADC of Hall Current 13 Click driver.
 */
#define HALLCURRENT13_SENSITIVITY_V_TO_A    0.1
#define HALLCURRENT13_ZERO_CURRENT_OFFSET   0.1
#define HALLCURRENT13_NUM_CONVERSIONS       100

/**
 * @brief Hall Current 13 ADC setting.
 * @details Specified settings for ADC of Hall Current 13 Click driver.
 */
#define HALLCURRENT13_ADC_RESOLUTION        0x0FFF
#define HALLCURRENT13_VREF_3V3              3.3
#define HALLCURRENT13_VREF_5V               5.0

/**
 * @brief Hall Current 13 device address setting.
 * @details Specified setting for device slave address selection of
 * Hall Current 13 Click driver.
 */
#define HALLCURRENT13_SET_DEV_ADDR      0x4D

/*! @} */ // hallcurrent13_set

/**
 * @defgroup hallcurrent13_map Hall Current 13 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 13 Click driver.
 */

/**
 * @addtogroup hallcurrent13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 13 Click to the selected MikroBUS.
 */
#define HALLCURRENT13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // hallcurrent13_map
/*! @} */ // hallcurrent13

/**
 * @brief Hall Current 13 Click driver selector.
 * @details Selects target driver interface of Hall Current 13 Click driver.
 */
typedef enum
{
    HALLCURRENT13_DRV_SEL_ADC,              /**< ADC driver descriptor. */
    HALLCURRENT13_DRV_SEL_I2C               /**< I2C driver descriptor. */

} hallcurrent13_drv_t;

/**
 * @brief Hall Current 13 Click context object.
 * @details Context object definition of Hall Current 13 Click driver.
 */
typedef struct
{
    analog_in_t         adc;                /**< ADC module object. */
    i2c_master_t        i2c;                /**< I2C driver object. */

    uint8_t             slave_address;      /**< Device slave address (used for I2C driver). */
    pin_name_t          chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    float               vref;               /**< ADC reference voltage. */
    hallcurrent13_drv_t drv_sel;            /**< Master driver interface selector. */

} hallcurrent13_t;

/**
 * @brief Hall Current 13 Click configuration object.
 * @details Configuration object definition of Hall Current 13 Click driver.
 */
typedef struct
{
    pin_name_t              an;             /**< Analog pin descriptor. */
    pin_name_t              scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t              sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */
    
    uint32_t                i2c_speed;      /**< I2C serial speed. */
    uint8_t                 i2c_address;    /**< I2C slave address. */
    
    hallcurrent13_drv_t drv_sel;            /**< Master driver interface selector. */

} hallcurrent13_cfg_t;

/**
 * @brief Hall Current 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLCURRENT13_OK = 0,
    HALLCURRENT13_ERROR = -1

} hallcurrent13_return_value_t;

/*!
 * @addtogroup hallcurrent13 Hall Current 13 Click Driver
 * @brief API for configuring and manipulating Hall Current 13 Click driver.
 * @{
 */

/**
 * @brief Hall Current 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent13_cfg_setup ( hallcurrent13_cfg_t *cfg );

/**
 * @brief Hall Current 13 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent13_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #hallcurrent13_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void hallcurrent13_drv_interface_selection ( hallcurrent13_cfg_t *cfg, hallcurrent13_drv_t drv_sel );

/**
 * @brief Hall Current 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent13_init ( hallcurrent13_t *ctx, hallcurrent13_cfg_t *cfg );

/**
 * @brief Hall Current 13 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #hallcurrent13_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent13_read_raw_adc ( hallcurrent13_t *ctx, uint16_t *raw_adc );

/**
 * @brief Hall Current 13 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent13_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t hallcurrent13_read_voltage ( hallcurrent13_t *ctx, float *voltage );

/**
 * @brief Hall Current 13 set vref function.
 * @details This function sets the voltage reference for Hall Current 13 click driver.
 * @param[in] ctx : Click context object.
 * See #hallcurrent13_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b hallcurrent13_init is 3.3V.
 */
err_t hallcurrent13_set_vref ( hallcurrent13_t *ctx, float vref );

/**
 * @brief Hall Current 13 read current function.
 * @details This function reads the input current level [A] based on @b HALLCURRENT13_NUM_CONVERSIONS 
 * of voltage measurements.
 * @param[in] ctx : Click context object.
 * See #hallcurrent13_t object definition for detailed explanation.
 * @param[out] current : Input current level [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For better accuracy, set the voltage reference by using the @b hallcurrent13_set_vref function,
 * and increase the number of conversions by modifying the @b HALLCURRENT13_NUM_CONVERSIONS macro.
 */
err_t hallcurrent13_read_current ( hallcurrent13_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT13_H

/*! @} */ // hallcurrent13

// ------------------------------------------------------------------------ END
