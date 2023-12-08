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
 * @file hallcurrent14.h
 * @brief This file contains API for Hall Current 14 Click Driver.
 */

#ifndef HALLCURRENT14_H
#define HALLCURRENT14_H

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
 * @addtogroup hallcurrent14 Hall Current 14 Click Driver
 * @brief API for configuring and manipulating Hall Current 14 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent14_set Hall Current 14 Registers Settings
 * @brief Settings for registers of Hall Current 14 Click driver.
 */

/**
 * @addtogroup hallcurrent14_set
 * @{
 */

/**
 * @brief Hall Current 14 Current calculation values.
 * @details Specified Current calculation values for ADC of Hall Current 14 Click driver.
 */
#define HALLCURRENT14_SENSITIVITY_V_TO_A        0.08
#define HALLCURRENT14_ZERO_CURRENT_OFFSET       0.5
#define HALLCURRENT14_NUM_CONVERSIONS           1000

/**
 * @brief Hall Current 14 ADC setting.
 * @details Specified settings for ADC of Hall Current 14 Click driver.
 */
#define HALLCURRENT14_ADC_RESOLUTION            0x0FFF
#define HALLCURRENT14_VREF_5V                   5.0

/**
 * @brief Hall Current 14 device address setting.
 * @details Specified setting for device slave address selection of
 * Hall Current 14 Click driver.
 */
#define HALLCURRENT14_SET_DEV_ADDR              0x4D

/*! @} */ // hallcurrent14_set

/**
 * @defgroup hallcurrent14_map Hall Current 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 14 Click driver.
 */

/**
 * @addtogroup hallcurrent14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 14 Click to the selected MikroBUS.
 */
#define HALLCURRENT14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // hallcurrent14_map
/*! @} */ // hallcurrent14

/**
 * @brief Hall Current 14 Click driver selector.
 * @details Selects target driver interface of Hall Current 14 Click driver.
 */
typedef enum
{
    HALLCURRENT14_DRV_SEL_ADC,      /**< ADC driver descriptor. */
    HALLCURRENT14_DRV_SEL_I2C       /**< I2C driver descriptor. */

} hallcurrent14_drv_t;

/**
 * @brief Hall Current 14 Click context object.
 * @details Context object definition of Hall Current 14 Click driver.
 */
typedef struct
{
    analog_in_t  adc;               /**< ADC module object. */
    i2c_master_t i2c;               /**< I2C driver object. */

    uint8_t     slave_address;      /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    float       vref;               /**< ADC reference voltage. */
    hallcurrent14_drv_t drv_sel;    /**< Master driver interface selector. */

} hallcurrent14_t;

/**
 * @brief Hall Current 14 Click configuration object.
 * @details Configuration object definition of Hall Current 14 Click driver.
 */
typedef struct
{
    pin_name_t  an;                 /**< Analog pin descriptor. */
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */
    
    uint32_t                i2c_speed;      /**< I2C serial speed. */
    uint8_t                 i2c_address;    /**< I2C slave address. */
    
    hallcurrent14_drv_t drv_sel;    /**< Master driver interface selector. */

} hallcurrent14_cfg_t;

/**
 * @brief Hall Current 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLCURRENT14_OK = 0,
    HALLCURRENT14_ERROR = -1

} hallcurrent14_return_value_t;

/*!
 * @addtogroup hallcurrent14 Hall Current 14 Click Driver
 * @brief API for configuring and manipulating Hall Current 14 Click driver.
 * @{
 */

/**
 * @brief Hall Current 14 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent14_cfg_setup ( hallcurrent14_cfg_t *cfg );

/**
 * @brief Hall Current 14 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent14_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #hallcurrent14_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void hallcurrent14_drv_interface_selection ( hallcurrent14_cfg_t *cfg, hallcurrent14_drv_t drv_sel );

/**
 * @brief Hall Current 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent14_init ( hallcurrent14_t *ctx, hallcurrent14_cfg_t *cfg );

/**
 * @brief Hall Current 14 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #hallcurrent14_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent14_read_raw_adc ( hallcurrent14_t *ctx, uint16_t *raw_adc );

/**
 * @brief Hall Current 14 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent14_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t hallcurrent14_read_voltage ( hallcurrent14_t *ctx, float *voltage );

/**
 * @brief Hall Current 14 set vref function.
 * @details This function sets the voltage reference for Hall Current 14 click driver.
 * @param[in] ctx : Click context object.
 * See #hallcurrent14_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b hallcurrent14_init is 5V.
 */
err_t hallcurrent14_set_vref ( hallcurrent14_t *ctx, float vref );

/**
 * @brief Hall Current 14 read current function.
 * @details This function reads the input current level [A] based on @b HALLCURRENT14_NUM_CONVERSIONS 
 * of voltage measurements.
 * @param[in] ctx : Click context object.
 * See #hallcurrent14_t object definition for detailed explanation.
 * @param[out] current : Input current level [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note For better accuracy, set the voltage reference by using the @b hallcurrent14_set_vref function,
 * and increase the number of conversions by modifying the @b HALLCURRENT14_NUM_CONVERSIONS macro.
 */
err_t hallcurrent14_read_current ( hallcurrent14_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT14_H

/*! @} */ // hallcurrent14

// ------------------------------------------------------------------------ END
