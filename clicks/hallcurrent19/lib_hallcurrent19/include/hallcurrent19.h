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
 * @file hallcurrent19.h
 * @brief This file contains API for Hall Current 19 Click Driver.
 */

#ifndef HALLCURRENT19_H
#define HALLCURRENT19_H

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
 * @addtogroup hallcurrent19 Hall Current 19 Click Driver
 * @brief API for configuring and manipulating Hall Current 19 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent19_set Hall Current 19 Registers Settings
 * @brief Settings for registers of Hall Current 19 Click driver.
 */

/**
 * @addtogroup hallcurrent19_set
 * @{
 */

/**
 * @brief Hall Current 19 Current calculation values.
 * @details Specified Current calculation values for ADC of Hall Current 19 Click driver.
 */
#define HALLCURRENT19_SENSITIVITY_V_TO_A        0.1
#define HALLCURRENT19_ZERO_CURRENT_OFFSET       0.5
#define HALLCURRENT19_NUM_CONVERSIONS           1000
#define HALLCURRENT19_OUTPUT_VOLTAGE            3.0f

/**
 * @brief Hall Current 19 Over Current Detection values.
 * @details Specified Over Current Detection Hall Current 19 Click driver.
 */
#define HALLCURRENT19_OCD_ACTIVE                0
#define HALLCURRENT19_OCD_INACTIVE              1

/*! @} */ // hallcurrent19_set

/**
 * @defgroup hallcurrent19_map Hall Current 19 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 19 Click driver.
 */

/**
 * @addtogroup hallcurrent19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 19 Click to the selected MikroBUS.
 */
#define HALLCURRENT19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.oc2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.oc1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hallcurrent19_map
/*! @} */ // hallcurrent19

/**
 * @brief Hall Current 19 Click context object.
 * @details Context object definition of Hall Current 19 Click driver.
 */
typedef struct
{
    digital_in_t oc2;       /**< Over Current Detection 2. */
    digital_in_t oc1;       /**< Over Current Detection 1. */

    analog_in_t adc;        /**< ADC module object. */

    float zero_vref;        /**< Zero current voltage reference. */

} hallcurrent19_t;

/**
 * @brief Hall Current 19 Click configuration object.
 * @details Configuration object definition of Hall Current 19 Click driver.
 */
typedef struct
{
    pin_name_t an;          /**< Analog pin descriptor. */
    pin_name_t oc2;         /**< Over Current Detection 2. */
    pin_name_t oc1;         /**< Over Current Detection 1. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} hallcurrent19_cfg_t;

/**
 * @brief Hall Current 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLCURRENT19_OK = 0,
    HALLCURRENT19_ERROR = -1

} hallcurrent19_return_value_t;

/*!
 * @addtogroup hallcurrent19 Hall Current 19 Click Driver
 * @brief API for configuring and manipulating Hall Current 19 Click driver.
 * @{
 */

/**
 * @brief Hall Current 19 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent19_cfg_setup ( hallcurrent19_cfg_t *cfg );

/**
 * @brief Hall Current 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent19_init ( hallcurrent19_t *ctx, hallcurrent19_cfg_t *cfg );

/**
 * @brief Hall Current 19 default configuration function.
 * @details This function executes a default configuration of Hall Current 19
 * Click board.
 * @param[in] ctx : Click context object.
 * See #hallcurrent19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hallcurrent19_default_cfg ( hallcurrent19_t *ctx );

/**
 * @brief Hall Current 19 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #hallcurrent19_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent19_read_an_pin_value ( hallcurrent19_t *ctx, uint16_t *data_out );

/**
 * @brief Hall Current 19 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent19_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t hallcurrent19_read_voltage ( hallcurrent19_t *ctx, float *data_out );

/**
 * @brief Hall Current 19 get over current detection 1 state function.
 * @details This function is used to get state of the overcurrent 1 detection
 * of the Hall Current 19 Click board.
 * @param[in] ctx : Click context object.
 * See #hallcurrent19_t object definition for detailed explanation.
 * @return @li @c 0 - OCD active, current over 7A,
 *         @li @c 1 - OCD inactive.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t hallcurrent19_get_oc1 ( hallcurrent19_t *ctx );

/**
 * @brief Hall Current 19 get over current detection 2 state function.
 * @details This function is used to get state of the overcurrent 2 detection
 * of the Hall Current 19 Click board.
 * @param[in] ctx : Click context object.
 * See #hallcurrent19_t object definition for detailed explanation.
 * @return @li @c 0 - OCD active, current over 17.5A,
 *         @li @c 1 - OCD inactive.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t hallcurrent19_get_oc2 ( hallcurrent19_t *ctx );

/**
 * @brief Hall Current 19 set zero reference function.
 * @details This function sets the zero voltage reference
 * of the Hall Current 19 Click board.
 * @param[in] ctx : Click context object.
 * See #hallcurrent19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent19_set_zero_ref ( hallcurrent19_t *ctx );

/**
 * @brief Hall Current 19 get current function.
 * @details This function reads and calculate input current value
 * of the Hall Current 19 Click board.
 * @param[in] ctx : Click context object.
 * See #hallcurrent19_t object definition for detailed explanation.
 * @param[in] current : Current [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent19_get_current ( hallcurrent19_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT19_H

/*! @} */ // hallcurrent19

// ------------------------------------------------------------------------ END
