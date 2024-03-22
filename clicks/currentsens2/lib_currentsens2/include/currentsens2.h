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
 * @file currentsens2.h
 * @brief This file contains API for Current Sens 2 Click Driver.
 */

#ifndef CURRENTSENS2_H
#define CURRENTSENS2_H

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
 * @addtogroup currentsens2 Current Sens 2 Click Driver
 * @brief API for configuring and manipulating Current Sens 2 Click driver.
 * @{
 */

/**
 * @defgroup currentsens2_set Current Sens 2 Registers Settings
 * @brief Settings for registers of Current Sens 2 Click driver.
 */

/**
 * @addtogroup currentsens2_set
 * @{
 */

/**
 * @brief Current Sens 2 description setting.
 * @details Specified setting for description of Current Sens 2 Click driver.
 */
#define CURRENTSENS2_CONV_FACTOR            12.5f
#define CURRENTSENS2_NUM_CONVERSIONS        10
#define CURRENTSENS2_NUM_OF_PASSES_1        1
#define CURRENTSENS2_NUM_OF_PASSES_2        2
#define CURRENTSENS2_NUM_OF_PASSES_3        3

/*! @} */ // currentsens2_set

/**
 * @defgroup currentsens2_map Current Sens 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Current Sens 2 Click driver.
 */

/**
 * @addtogroup currentsens2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current Sens 2 Click to the selected MikroBUS.
 */
#define CURRENTSENS2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // currentsens2_map
/*! @} */ // currentsens2

/**
 * @brief Current Sens 2 Click context object.
 * @details Context object definition of Current Sens 2 Click driver.
 */
typedef struct
{
    digital_in_t int_pin;       /**< Interrupt pin. */

    analog_in_t adc;            /**< ADC module object. */

    float zero_val;             /**< Zero ampere voltage level. */
    uint8_t no_of_turns;        /**< Number of primary coil turns. */

} currentsens2_t;

/**
 * @brief Current Sens 2 Click configuration object.
 * @details Configuration object definition of Current Sens 2 Click driver.
 */
typedef struct
{
    pin_name_t an;                      /**< Analog pin descriptor. */
    pin_name_t int_pin;                 /**< Interrupt pin. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} currentsens2_cfg_t;

/**
 * @brief Current Sens 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENTSENS2_OK = 0,
    CURRENTSENS2_ERROR = -1

} currentsens2_return_value_t;

/*!
 * @addtogroup currentsens2 Current Sens 2 Click Driver
 * @brief API for configuring and manipulating Current Sens 2 Click driver.
 * @{
 */

/**
 * @brief Current Sens 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #currentsens2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void currentsens2_cfg_setup ( currentsens2_cfg_t *cfg );

/**
 * @brief Current Sens 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #currentsens2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #currentsens2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentsens2_init ( currentsens2_t *ctx, currentsens2_cfg_t *cfg );

/**
 * @brief Current Sens 2 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #currentsens2_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentsens2_read_an_pin_value ( currentsens2_t *ctx, uint16_t *data_out );

/**
 * @brief Current Sens 2 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #currentsens2_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t currentsens2_read_an_pin_vol ( currentsens2_t *ctx, float *data_out );

/**
 * @brief Current Sens 2 get int pin state function.
 * @details This function is used to read int pin state.
 * @param[in] ctx : Click context object.
 * See #currentsens2_t object definition for detailed explanation.
 * @return @li @c  0 - Pin state low,
 *         @li @c -1 - Pin state high.
 * @note None.
 */
uint8_t currentsens2_get_int_pin ( currentsens2_t *ctx );

/**
 * @brief Current Sens 2 set number of primary coil turns function.
 * @details This function is used to set number of primary coil turns function.
 * @param[in] ctx : Click context object.
 * See #currentsens2_t object definition for detailed explanation.
 * @param[in] turns : Number of primary coil turns.
 * @return Nothing.
 * @note None.
 */
void currentsens2_set_prim_turn_no ( currentsens2_t *ctx, uint8_t turns );

/**
 * @brief Current Sens 2 tare function.
 * @details This function is used to set zero ampere reference.
 * @param[in] ctx : Click context object.
 * See #currentsens2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentsens2_tare ( currentsens2_t *ctx );

/**
 * @brief Current Sens 2 read current function.
 * @details This function reads the input current level [A] based of voltage measurements.
 * @param[in] ctx : Click context object.
 * See #currentsens2_t object definition for detailed explanation.
 * @param[out] current : Input current level [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentsens2_get_current ( currentsens2_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // CURRENTSENS2_H

/*! @} */ // currentsens2

// ------------------------------------------------------------------------ END
