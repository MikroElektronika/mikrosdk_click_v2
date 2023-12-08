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
 * @file hallcurrent825a.h
 * @brief This file contains API for Hall Current 8 25A Click Driver.
 */

#ifndef HALLCURRENT825A_H
#define HALLCURRENT825A_H

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
 * @addtogroup hallcurrent825a Hall Current 8 25A Click Driver
 * @brief API for configuring and manipulating Hall Current 8 25A Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent825a_map Hall Current 8 25A MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 8 25A Click driver.
 */

/**
 * @addtogroup hallcurrent825a_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 8 25A Click to the selected MikroBUS.
 */
#define HALLCURRENT825A_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.oc1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.oc2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hallcurrent825a_map
/*! @} */ // hallcurrent825a

/**
 * @brief Hall Current 8 25A Click context object.
 * @details Context object definition of Hall Current 8 25A Click driver.
 */
typedef struct
{
    digital_in_t oc1;       /**< OCD threshold of channel 1. */
    digital_in_t oc2;       /**< OCD threshold of channel 2. */

    analog_in_t  adc;       /**< ADC module object. */
    
    float offset;           /**< Calibration offset voltage. */

} hallcurrent825a_t;

/**
 * @brief Hall Current 8 25A Click configuration object.
 * @details Configuration object definition of Hall Current 8 25A Click driver.
 */
typedef struct
{
    pin_name_t  an;     /**< Analog pin descriptor. */
    pin_name_t  oc1;    /**< OCD threshold of channel 1. */
    pin_name_t  oc2;    /**< OCD threshold of channel 2. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} hallcurrent825a_cfg_t;

/**
 * @brief Hall Current 8 25A Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   HALLCURRENT825A_OK = 0,
   HALLCURRENT825A_ERROR = -1

} hallcurrent825a_return_value_t;

/*!
 * @addtogroup hallcurrent825a Hall Current 8 25A Click Driver
 * @brief API for configuring and manipulating Hall Current 8 25A Click driver.
 * @{
 */

/**
 * @brief Hall Current 8 25A configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent825a_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent825a_cfg_setup ( hallcurrent825a_cfg_t *cfg );

/**
 * @brief Hall Current 8 25A initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent825a_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent825a_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent825a_init ( hallcurrent825a_t *ctx, hallcurrent825a_cfg_t *cfg );

/**
 * @brief Hall Current 8 25A read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #hallcurrent825a_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent825a_read_pin_value ( hallcurrent825a_t *ctx, uint16_t *data_out );

/**
 * @brief Hall Current 8 25A read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent825a_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t hallcurrent825a_read_pin_volt ( hallcurrent825a_t *ctx, float *data_out );

/**
 * @brief Hall Current 8 25A calibration function.
 * @details This function sets the calibration value into the offset data from context object of
 * the TLI4971 high precision coreless current sensor
 * on Hall Current 8 25A Click board.
 * @param[in] ctx : Click context object.
 * See #hallcurrent825a_t object definition for detailed explanation.
 * @return @li @c     0 - Success,
 *         @li @c    -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 *
 * @note Function delay is approximately 500 ms.
 */
err_t hallcurrent825a_calibration ( hallcurrent825a_t *ctx );

/**
 * @brief Hall Current 8 25A read voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent825a_t object definition for detailed explanation.
 * @param[out] avr_voltage : Average voltage level of the analog pin [V].
 * @return @li @c     0 - Success,
 *         @li @c    -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 *
 * @note Function delay is approximately 500 ms.
 */
err_t hallcurrent825a_get_voltage ( hallcurrent825a_t *ctx, float *avr_voltage );

/**
 * @brief Hall Current 8 25A get current level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional current level.
 * @param[in] ctx : Click context object.
 * See #hallcurrent825a_t object definition for detailed explanation.
 * @param[out] current : Average current level of the analog pin [A].
 * @return @li @c     0 - Success,
 *         @li @c    -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 *
 * @note Function delay is approximately 500 ms.
 */
err_t hallcurrent825a_get_current ( hallcurrent825a_t *ctx, float *current );

/**
 * @brief Hall Current 8 25A get state of OC1 function.
 * @details This function gets the state of the OC1 pin 
 * which detects overcurrent of the 201.6 [A] ( 120 [A] * 1.68 )
 * of the TLI4971 high precision coreless current sensor 
 * on the Hall Current 8 25A Click board.
 * @param[out] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @return @li @c 0x00 - Overcurrent detected,
 *         @li @c 0x01 - OK.
 * 
 * @note None.
 */
uint8_t hallcurrent825a_get_odc1 ( hallcurrent825a_t *ctx );

/**
 * @brief Hall Current 8 25A get state of OC2 function.
 * @details This function gets the state of the OC2 pin 
 * which detects overcurrent of the 98.4 [A] ( 120 [A] * 0.82 ) 
 * of the TLI4971 high precision coreless current sensor 
 * on the Hall Current 8 25A Click board.
 * @param[out] ctx : Click context object.
 * See #daq3_t object definition for detailed explanation.
 * @return @li @c 0x00 - Overcurrent detected,
 *         @li @c 0x01 - OK.
 * 
 * @note None.
 */
uint8_t hallcurrent825a_get_odc2 ( hallcurrent825a_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT825A_H

/*! @} */ // hallcurrent825a

// ------------------------------------------------------------------------ END
