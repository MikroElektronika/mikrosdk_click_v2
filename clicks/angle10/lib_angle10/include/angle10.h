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
 * @file angle10.h
 * @brief This file contains API for Angle 10 Click Driver.
 */

#ifndef ANGLE10_H
#define ANGLE10_H

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

/*!
 * @addtogroup angle10 Angle 10 Click Driver
 * @brief API for configuring and manipulating Angle 10 Click driver.
 * @{
 */

/**
 * @defgroup angle10_set Angle 10 Settings
 * @brief Settings of Angle 10 Click driver.
 */

/**
 * @addtogroup angle10_set
 * @{
 */

/**
 * @brief Angle 10 angle calculation values.
 * @details Specified angle calculation values of Angle 10 Click driver.
 */
#define ANGLE10_FULL_CIRCLE         360.0
#define ANGLE10_NUM_CONVERSIONS     50

/**
 * @brief Angle 10 ADC setting.
 * @details Specified settings for ADC of Angle 10 Click driver.
 */
#define ANGLE10_VREF_3V3            3.3
#define ANGLE10_VREF_5V             5.0

/*! @} */ // angle10_set

/**
 * @defgroup angle10_map Angle 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Angle 10 Click driver.
 */

/**
 * @addtogroup angle10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Angle 10 Click to the selected MikroBUS.
 */
#define ANGLE10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // angle10_map
/*! @} */ // angle10

/**
 * @brief Angle 10 Click context object.
 * @details Context object definition of Angle 10 Click driver.
 */
typedef struct
{
    analog_in_t adc;            /**< ADC module object. */

    float       vref;           /**< ADC reference voltage. */

} angle10_t;

/**
 * @brief Angle 10 Click configuration object.
 * @details Configuration object definition of Angle 10 Click driver.
 */
typedef struct
{
    pin_name_t an;              /**< Analog pin descriptor. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float      vref;            /**< ADC reference voltage. */
    
} angle10_cfg_t;

/**
 * @brief Angle 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ANGLE10_OK = 0,
    ANGLE10_ERROR = -1

} angle10_return_value_t;

/*!
 * @addtogroup angle10 Angle 10 Click Driver
 * @brief API for configuring and manipulating Angle 10 Click driver.
 * @{
 */

/**
 * @brief Angle 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #angle10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void angle10_cfg_setup ( angle10_cfg_t *cfg );

/**
 * @brief Angle 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #angle10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #angle10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle10_init ( angle10_t *ctx, angle10_cfg_t *cfg );

/**
 * @brief Angle 10 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #angle10_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle10_read_raw_adc ( angle10_t *ctx, uint16_t *raw_adc );

/**
 * @brief Angle 10 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #angle10_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t angle10_read_voltage ( angle10_t *ctx, float *voltage );

/**
 * @brief Angle 10 set vref function.
 * @details This function sets the voltage reference for Angle 10 click driver.
 * @param[in] ctx : Click context object.
 * See #angle10_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b angle10_init is 3.3V.
 */
err_t angle10_set_vref ( angle10_t *ctx, float vref );

/**
 * @brief Angle 10 get angle function.
 * @details This function reads the magnetic angular position in degrees based on @b ANGLE10_NUM_CONVERSIONS 
 * of voltage measurements.
 * @param[in] ctx : Click context object.
 * See #angle10_t object definition for detailed explanation.
 * @param[out] angle : Angle in degrees [0-360].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t angle10_get_angle ( angle10_t *ctx, float *angle );

#ifdef __cplusplus
}
#endif
#endif // ANGLE10_H

/*! @} */ // angle10

// ------------------------------------------------------------------------ END
