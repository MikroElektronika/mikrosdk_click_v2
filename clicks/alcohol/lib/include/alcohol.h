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
 * @file alcohol.h
 * @brief This file contains API for Alcohol Click Driver.
 */

#ifndef ALCOHOL_H
#define ALCOHOL_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_in.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup alcohol Alcohol Click Driver
 * @brief API for configuring and manipulating Alcohol Click driver.
 * @{
 */

/**
 * @defgroup alcohol_map Alcohol MikroBUS Map
 * @brief MikroBUS pin mapping of Alcohol Click driver.
 */

/**
 * @addtogroup alcohol_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Alcohol Click to the selected MikroBUS.
 */
#define ALCOHOL_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // alcohol_map
/*! @} */ // alcohol

/**
 * @brief Alcohol Click context object.
 * @details Context object definition of Alcohol Click driver.
 */
typedef struct {
    analog_in_t  adc;       /**< ADC module object. */

} alcohol_t;

/**
 * @brief Alcohol Click configuration object.
 * @details Configuration object definition of Alcohol Click driver.
 */
typedef struct {
    pin_name_t  an;     /**< Analog pin descriptor. */


    analog_in_resolution_t resolution;     /**< ADC resolution. */
    float vref;           /**< ADC reference voltage. */

} alcohol_cfg_t;

/**
 * @brief Alcohol Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum {
   ALCOHOL_OK = 0,
   ALCOHOL_ERROR = -1

} alcohol_return_value_t;

/*!
 * @addtogroup alcohol Alcohol Click Driver
 * @brief API for configuring and manipulating Alcohol Click driver.
 * @{
 */

/**
 * @brief Alcohol configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #alcohol_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void alcohol_cfg_setup ( alcohol_cfg_t *cfg );

/**
 * @brief Alcohol initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #alcohol_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #alcohol_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t alcohol_init ( alcohol_t *ctx, alcohol_cfg_t *cfg );

/**
 * @brief Alcohol read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #alcohol_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t alcohol_read_an_pin_value ( alcohol_t *ctx, uint16_t *data_out );

/**
 * @brief Alcohol read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #alcohol_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t alcohol_read_an_pin_voltage ( alcohol_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // ALCOHOL_H

/*! @} */ // alcohol

// ------------------------------------------------------------------------ END
