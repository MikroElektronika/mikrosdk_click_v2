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
 * @file ambient7.h
 * @brief This file contains API for Ambient 7 Click Driver.
 */

#ifndef AMBIENT7_H
#define AMBIENT7_H

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

/*!
 * @addtogroup ambient7 Ambient 7 Click Driver
 * @brief API for configuring and manipulating Ambient 7 Click driver.
 * @{
 */

/**
 * @defgroup ambient7_map Ambient 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Ambient 7 Click driver.
 */

/**
 * @addtogroup ambient7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ambient 7 Click to the selected MikroBUS.
 */
#define AMBIENT7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an_pin = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // ambient7_map
/*! @} */ // ambient7

/**
 * @brief Ambient 7 Click context object.
 * @details Context object definition of Ambient 7 Click driver.
 */
typedef struct
{
    analog_in_t adc;        /**< ADC module object. */

} ambient7_t;

/**
 * @brief Ambient 7 Click configuration object.
 * @details Configuration object definition of Ambient 7 Click driver.
 */
typedef struct
{
    pin_name_t an_pin;      /**< Analog pin descriptor. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} ambient7_cfg_t;

/**
 * @brief Ambient 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AMBIENT7_OK = 0,
    AMBIENT7_ERROR = -1

} ambient7_return_value_t;

/*!
 * @addtogroup ambient7 Ambient 7 Click Driver
 * @brief API for configuring and manipulating Ambient 7 Click driver.
 * @{
 */

/**
 * @brief Ambient 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ambient7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ambient7_cfg_setup ( ambient7_cfg_t *cfg );

/**
 * @brief Ambient 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ambient7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ambient7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient7_init ( ambient7_t *ctx, ambient7_cfg_t *cfg );

/**
 * @brief Ambient 7 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #ambient7_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient7_read_an_pin_value ( ambient7_t *ctx, uint16_t *data_out );

/**
 * @brief Ambient 7 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #ambient7_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t ambient7_read_an_pin_voltage ( ambient7_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // AMBIENT7_H

/*! @} */ // ambient7

// ------------------------------------------------------------------------ END
