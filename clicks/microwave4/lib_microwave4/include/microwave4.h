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
 * @file microwave4.h
 * @brief This file contains API for Microwave 4 Click Driver.
 */

#ifndef MICROWAVE4_H
#define MICROWAVE4_H

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
 * @addtogroup microwave4 Microwave 4 Click Driver
 * @brief API for configuring and manipulating Microwave 4 Click driver.
 * @{
 */

/**
 * @defgroup microwave4_set Microwave 4 Registers Settings
 * @brief Settings for registers of Microwave 4 Click driver.
 */

/**
 * @addtogroup microwave4_set
 * @{
 */

/**
 * @brief Microwave 4 description setting.
 * @details Specified setting for description of Microwave 4 Click driver.
 */

/**
 * @brief Microwave 4 ADC setting.
 * @details Specified settings for ADC of Microwave 4 Click driver.
 */
#define MICROWAVE4_ADC_RESOLUTION    0x0FFF
#define MICROWAVE4_VREF_3V3          3.3
#define MICROWAVE4_VREF_5V           5.0

/**
 * @brief Microwave 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Microwave 4 Click driver.
 */
#define MICROWAVE4_SET_DEV_ADDR      0x4D

/*! @} */ // microwave4_set

/**
 * @defgroup microwave4_map Microwave 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Microwave 4 Click driver.
 */

/**
 * @addtogroup microwave4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Microwave 4 Click to the selected MikroBUS.
 */
#define MICROWAVE4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // microwave4_map
/*! @} */ // microwave4

/**
 * @brief Microwave 4 Click driver selector.
 * @details Selects target driver interface of Microwave 4 Click driver.
 */
typedef enum
{
    MICROWAVE4_DRV_SEL_ADC,       /**< ADC driver descriptor. */
    MICROWAVE4_DRV_SEL_I2C        /**< I2C driver descriptor. */

} microwave4_drv_t;

/**
 * @brief Microwave 4 Click context object.
 * @details Context object definition of Microwave 4 Click driver.
 */
typedef struct
{
    analog_in_t  adc;                               /**< ADC module object. */
    i2c_master_t i2c;                               /**< I2C driver object. */

    uint8_t      slave_address;                     /**< Device slave address (used for I2C driver). */
    float        vref;                              /**< ADC reference voltage. */
    microwave4_drv_t drv_sel;                       /**< Master driver interface selector. */

} microwave4_t;

/**
 * @brief Microwave 4 Click configuration object.
 * @details Configuration object definition of Microwave 4 Click driver.
 */
typedef struct
{
    pin_name_t an;                                  /**< Analog pin descriptor. */
    pin_name_t scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t resolution;              /**< ADC resolution. */
    float                  vref;                    /**< ADC reference voltage. */
    
    uint32_t               i2c_speed;               /**< I2C serial speed. */
    uint8_t                i2c_address;             /**< I2C slave address. */
    
    microwave4_drv_t drv_sel;                       /**< Master driver interface selector. */

} microwave4_cfg_t;

/**
 * @brief Microwave 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MICROWAVE4_OK = 0,
    MICROWAVE4_ERROR = -1

} microwave4_return_value_t;

/*!
 * @addtogroup microwave4 Microwave 4 Click Driver
 * @brief API for configuring and manipulating Microwave 4 Click driver.
 * @{
 */

/**
 * @brief Microwave 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #microwave4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void microwave4_cfg_setup ( microwave4_cfg_t *cfg );

/**
 * @brief Microwave 4 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #microwave4_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #microwave4_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void microwave4_drv_interface_sel ( microwave4_cfg_t *cfg, microwave4_drv_t drv_sel );

/**
 * @brief Microwave 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #microwave4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #microwave4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t microwave4_init ( microwave4_t *ctx, microwave4_cfg_t *cfg );

/**
 * @brief Microwave 4 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #microwave4_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t microwave4_read_raw_adc ( microwave4_t *ctx, uint16_t *raw_adc );

/**
 * @brief Microwave 4 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #microwave4_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t microwave4_read_voltage ( microwave4_t *ctx, float *voltage );

/**
 * @brief Microwave 4 set vref function.
 * @details This function sets the voltage reference for Microwave 4 click driver.
 * @param[in] ctx : Click context object.
 * See #microwave4_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b microwave4_init is 3.3V.
 */
err_t microwave4_set_vref ( microwave4_t *ctx, float vref );

#ifdef __cplusplus
}
#endif
#endif // MICROWAVE4_H

/*! @} */ // microwave4

// ------------------------------------------------------------------------ END
