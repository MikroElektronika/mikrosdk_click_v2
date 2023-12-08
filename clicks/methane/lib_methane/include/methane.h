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
 * @file methane.h
 * @brief This file contains API for Methane Click Driver.
 */

#ifndef METHANE_H
#define METHANE_H

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

/**
 * @defgroup methane_map Methane MikroBUS Map
 * @brief MikroBUS pin mapping of Methane Click driver.
 */

/**
 * @addtogroup methane_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Methane Click to the selected MikroBUS.
 */
#define METHANE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); 
  

/*! @} */ // methane_map
/*! @} */ // methane

/**
 * @brief Methane Click context object.
 * @details Context object definition of Methane Click driver.
 */
typedef struct
{
    analog_in_t  adc;       /**< ADC module object. */

} methane_t;

/**
 * @brief Methane Click configuration object.
 * @details Configuration object definition of Methane Click driver.
 */
typedef struct
{
    pin_name_t  an;     /**< Analog pin descriptor. */
  
    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} methane_cfg_t;

/**
 * @brief Methane Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   METHANE_OK = 0,
   METHANE_ERROR = -1

} methane_return_value_t;

/*!
 * @addtogroup methane Methane Click Driver
 * @brief API for configuring and manipulating Methane Click driver.
 * @{
 */

/**
 * @brief Methane configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #methane_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void methane_cfg_setup ( methane_cfg_t *cfg );

/**
 * @brief Methane initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #methane_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #methane_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t methane_init ( methane_t *ctx, methane_cfg_t *cfg );

/**
 * @brief Methane read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #methane_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t methane_read_an_pin_value ( methane_t *ctx, uint16_t *data_out );

/**
 * @brief Methane read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #methane_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t methane_read_an_pin_voltage ( methane_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // METHANE_H

/*! @} */ // methane

// ------------------------------------------------------------------------ END
