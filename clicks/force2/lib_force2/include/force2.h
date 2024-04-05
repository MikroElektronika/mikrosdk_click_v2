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
 * @file force2.h
 * @brief This file contains API for Force 2 Click Driver.
 */

#ifndef FORCE2_H
#define FORCE2_H

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
 * @addtogroup force2 Force 2 Click Driver
 * @brief API for configuring and manipulating Force 2 Click driver.
 * @{
 */

/**
 * @defgroup force2_set Force 2 Settings
 * @brief Settings of Force 2 Click driver.
 */

/**
 * @addtogroup force2_set
 * @{
 */

/**
 * @brief Force 2 setting.
 * @details Specified setting of Force 2 Click driver.
 */
#define FORCE2_FORCE_MIN    0.0f
#define FORCE2_FORCE_MAX    15.0f
#define FORCE2_VREF         3.3f

/*! @} */ // force2_set

/**
 * @defgroup force2_map Force 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Force 2 Click driver.
 */

/**
 * @addtogroup force2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Force 2 Click to the selected MikroBUS.
 */
#define FORCE2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // force2_map
/*! @} */ // force2

/**
 * @brief Force 2 Click context object.
 * @details Context object definition of Force 2 Click driver.
 */
typedef struct
{
    analog_in_t adc;        /**< ADC module object. */

} force2_t;

/**
 * @brief Force 2 Click configuration object.
 * @details Configuration object definition of Force 2 Click driver.
 */
typedef struct
{
    pin_name_t an;          /**< Analog pin descriptor. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} force2_cfg_t;

/**
 * @brief Force 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FORCE2_OK = 0,
    FORCE2_ERROR = -1

} force2_return_value_t;

/*!
 * @addtogroup force2 Force 2 Click Driver
 * @brief API for configuring and manipulating Force 2 Click driver.
 * @{
 */

/**
 * @brief Force 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #force2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void force2_cfg_setup ( force2_cfg_t *cfg );

/**
 * @brief Force 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #force2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #force2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t force2_init ( force2_t *ctx, force2_cfg_t *cfg );

/**
 * @brief Force 2 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #force2_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t force2_read_an_pin_value ( force2_t *ctx, uint16_t *data_out );

/**
 * @brief Force 2 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #force2_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t force2_read_an_pin_voltage ( force2_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // FORCE2_H

/*! @} */ // force2

// ------------------------------------------------------------------------ END
