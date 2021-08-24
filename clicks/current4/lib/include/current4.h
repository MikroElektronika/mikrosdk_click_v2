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
 * @file current4.h
 * @brief This file contains API for Current 4 Click Driver.
 */

#ifndef CURRENT4_H
#define CURRENT4_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup current4 Current 4 Click Driver
 * @brief API for configuring and manipulating Current 4 Click driver.
 * @{
 */

/**
 * @defgroup current4_reg Current 4 Registers List
 * @brief List of registers of Current 4 Click driver.
 */

/**
 * @defgroup current4_set Current 4 Registers Settings
 * @brief Settings for registers of Current 4 Click driver.
 */

/**
 * @defgroup current4_map Current 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Current 4 Click driver.
 */

/**
 * @addtogroup current4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current 4 Click to the selected MikroBUS.
 */
#define CURRENT4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); 

/*! @} */ // current4_map
/*! @} */ // current4

/**
 * @brief Current 4 Click context object.
 * @details Context object definition of Current 4 Click driver.
 */
typedef struct
{
    analog_in_t  adc; /**< ADC module object. */
    float ic_vref;    /**< Voltage on REF pin 0 or 
                           2.5 depends on VREF SEL. */  

} current4_t;

/**
 * @brief Current 4 Click configuration object.
 * @details Configuration object definition of Current 4 Click driver.
 */
typedef struct
{
    pin_name_t  an;     /**< Analog pin descriptor. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} current4_cfg_t;

/**
 * @brief Current 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   CURRENT4_OK = 0,
   CURRENT4_ERROR = -1

} current4_return_value_t;

/*!
 * @addtogroup current4 Current 4 Click Driver
 * @brief API for configuring and manipulating Current 4 Click driver.
 * @{
 */

/**
 * @brief Current 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #current4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void current4_cfg_setup ( current4_cfg_t *cfg );

/**
 * @brief Current 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #current4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #current4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current4_init ( current4_t *ctx, current4_cfg_t *cfg );

/**
 * @brief Read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #current4_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current4_read_an_pin_value ( current4_t *ctx, uint16_t *data_out );

/**
 * @brief Read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #current4_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t current4_read_an_pin_voltage ( current4_t *ctx, float *data_out );

/**
 * @brief Read load current.
 * @details This function reads voltage on AN pin and 
 *          calculates the load current.
 * @param[in] ctx : Click context object.
 * See #current4_t object definition for detailed explanation.
 * @param[out] load_current : Output load current [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t current4_read_load_current ( current4_t *ctx, float *load_current );

#ifdef __cplusplus
}
#endif
#endif // CURRENT4_H

/*! @} */ // current4

// ------------------------------------------------------------------------ END
