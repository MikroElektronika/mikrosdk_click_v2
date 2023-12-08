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
 * @file microwave6.h
 * @brief This file contains API for Microwave 6 Click Driver.
 */

#ifndef MICROWAVE6_H
#define MICROWAVE6_H

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
 * @addtogroup microwave6 Microwave 6 Click Driver
 * @brief API for configuring and manipulating Microwave 6 Click driver.
 * @{
 */

/**
 * @defgroup microwave6_set Microwave 6 Registers Settings
 * @brief Settings for registers of Microwave 6 Click driver.
 */

/**
 * @addtogroup microwave6_set
 * @{
 */

/**
 * @brief Microwave 6 ADC setting.
 * @details Specified settings for ADC of Microwave 6 Click driver.
 */
#define MICROWAVE6_ADC_RESOLUTION    0x0FFF
#define MICROWAVE6_VREF_3V3          3.3
#define MICROWAVE6_VREF_5V           5.0

/**
 * @brief Microwave 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Microwave 6 Click driver.
 */
#define MICROWAVE6_SET_DEV_ADDR      0x4D

/*! @} */ // microwave6_set

/**
 * @defgroup microwave6_map Microwave 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Microwave 6 Click driver.
 */

/**
 * @addtogroup microwave6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Microwave 6 Click to the selected MikroBUS.
 */
#define MICROWAVE6_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // microwave6_map
/*! @} */ // microwave6

/**
 * @brief Microwave 6 Click driver selector.
 * @details Selects target driver interface of Microwave 6 Click driver.
 */
typedef enum
{
    MICROWAVE6_DRV_SEL_ADC,       /**< ADC driver descriptor. */
    MICROWAVE6_DRV_SEL_I2C        /**< I2C driver descriptor. */

} microwave6_drv_t;

/**
 * @brief Microwave 6 Click context object.
 * @details Context object definition of Microwave 6 Click driver.
 */
typedef struct
{
    analog_in_t  adc;              /**< ADC module object. */
    i2c_master_t i2c;              /**< I2C driver object. */
                                   
    uint8_t      slave_address;    /**< Device slave address (used for I2C driver). */
    float        vref;             /**< ADC reference voltage. */
    microwave6_drv_t drv_sel;      /**< Master driver interface selector. */

} microwave6_t;

/**
 * @brief Microwave 6 Click configuration object.
 * @details Configuration object definition of Microwave 6 Click driver.
 */
typedef struct
{
    pin_name_t an;     /**< Analog pin descriptor. */
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    analog_in_resolution_t resolution;     /**< ADC resolution. */
    float                  vref;           /**< ADC reference voltage. */
                                           
    uint32_t               i2c_speed;      /**< I2C serial speed. */
    uint8_t                i2c_address;    /**< I2C slave address. */
    
    microwave6_drv_t drv_sel;              /**< Master driver interface selector. */

} microwave6_cfg_t;

/**
 * @brief Microwave 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MICROWAVE6_OK = 0,
    MICROWAVE6_ERROR = -1

} microwave6_return_value_t;

/*!
 * @addtogroup microwave6 Microwave 6 Click Driver
 * @brief API for configuring and manipulating Microwave 6 Click driver.
 * @{
 */

/**
 * @brief Microwave 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #microwave6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void microwave6_cfg_setup ( microwave6_cfg_t *cfg );

/**
 * @brief Microwave 6 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #microwave6_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #microwave6_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void microwave6_drv_interface_selection ( microwave6_cfg_t *cfg, microwave6_drv_t drv_sel );

/**
 * @brief Microwave 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #microwave6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #microwave6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t microwave6_init ( microwave6_t *ctx, microwave6_cfg_t *cfg );

/**
 * @brief Microwave 6 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #microwave6_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t microwave6_read_raw_adc ( microwave6_t *ctx, uint16_t *raw_adc );

/**
 * @brief Microwave 6 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #microwave6_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t microwave6_read_voltage ( microwave6_t *ctx, float *voltage );

/**
 * @brief Microwave 6 set vref function.
 * @details This function sets the voltage reference for Microwave 6 click driver.
 * @param[in] ctx : Click context object.
 * See #microwave6_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b microwave6_init is 3.3V.
 */
err_t microwave6_set_vref ( microwave6_t *ctx, float vref );

#ifdef __cplusplus
}
#endif
#endif // MICROWAVE6_H

/*! @} */ // microwave6

// ------------------------------------------------------------------------ END
