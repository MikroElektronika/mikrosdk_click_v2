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
 * @file analogmux5.h
 * @brief This file contains API for Analog MUX 5 Click Driver.
 */

#ifndef ANALOGMUX5_H
#define ANALOGMUX5_H

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
 * @addtogroup analogmux5 Analog MUX 5 Click Driver
 * @brief API for configuring and manipulating Analog MUX 5 Click driver.
 * @{
 */

/**
 * @addtogroup ch_select
 * @{
 */

/**
 * @brief List of Muxs of Analog MUX 5 Click driver.
 */
#define ANALOGMUX5_SEL_CH_1 0x01
#define ANALOGMUX5_SEL_CH_2 0x02
#define ANALOGMUX5_SEL_CH_3 0x03
#define ANALOGMUX5_SEL_CH_4 0x04

/*! @} */ // ch_select

/**
 * @defgroup analogmux5_map Analog MUX 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Analog MUX 5 Click driver.
 */

/**
 * @addtogroup analogmux5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Analog MUX 5 Click to the selected MikroBUS.
 */
#define ANALOGMUX5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.a0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.a1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // analogmux5_map
/*! @} */ // analogmux5

/**
 * @brief Analog MUX 5 Click context object.
 * @details Context object definition of Analog MUX 5 Click driver.
 */
typedef struct
{
    digital_out_t  en;     /**< Enable pin. */
    digital_out_t  a0;     /**< Address line 0. */
    digital_out_t  a1;     /**< Address line 1. */

    analog_in_t  adc;      /**< ADC module object. */

} analogmux5_t;

/**
 * @brief Analog MUX 5 Click configuration object.
 * @details Configuration object definition of Analog MUX 5 Click driver.
 */
typedef struct
{
    pin_name_t  an;     /**< Analog pin. */
    pin_name_t  en;     /**< Enable pin. */
    pin_name_t  a0;     /**< Address line 0. */
    pin_name_t  a1;     /**< Address line 1. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} analogmux5_cfg_t;

/**
 * @brief Analog MUX 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ANALOGMUX5_OK = 0,
    ANALOGMUX5_ERROR = -1

} analogmux5_return_value_t;

/*!
 * @addtogroup analogmux5 Analog MUX 5 Click Driver
 * @brief API for configuring and manipulating Analog MUX 5 Click driver.
 * @{
 */

/**
 * @brief Analog MUX 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #analogmux5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void analogmux5_cfg_setup ( analogmux5_cfg_t *cfg );

/**
 * @brief Analog MUX 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #analogmux5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #analogmux5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t analogmux5_init ( analogmux5_t *ctx, analogmux5_cfg_t *cfg );

/**
 * @brief Analog MUX 5 default configuration function.
 * @details This function executes a default configuration of Analog MUX 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #analogmux5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t analogmux5_default_cfg ( analogmux5_t *ctx );

/**
 * @brief Analog MUX 5 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #analogmux5_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t analogmux5_read_an_pin_value ( analogmux5_t *ctx, uint16_t *data_out );

/**
 * @brief Analog MUX 5 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #analogmux5_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t analogmux5_read_an_pin_voltage ( analogmux5_t *ctx, float *data_out );

/**
 * @brief Analog MUX 5 enable function.
 * @details This function enable all switch channels.
 * @param[in] ctx : Click context object.
 * See #analogmux5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void analogmux5_enable ( analogmux5_t *ctx );

/**
 * @brief Analog MUX 5 disable function.
 * @details This function disable all switch channels.
 * @param[in] ctx : Click context object.
 * See #analogmux5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void analogmux5_disable ( analogmux5_t *ctx );

/**
 * @brief Analog MUX 5 set channel function.
 * @details This function sets the active channel.
 * @param[in] ctx : Click context object.
 * See #analogmux5_t object definition for detailed explanation.
 * @param[in] ch_select : 
 *         @li @c 0x01 ( ANALOGMUX5_SEL_CH_1 ) - Set active channel 1,
 *         @li @c 0x02 ( ANALOGMUX5_SEL_CH_2 ) - Set active channel 2,
 *         @li @c 0x03 ( ANALOGMUX5_SEL_CH_3 ) - Set active channel 3,
 *         @li @c 0x04 ( ANALOGMUX5_SEL_CH_4 ) - Set active channel 4,
 *         
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 */
err_t analogmux5_select_ch ( analogmux5_t *ctx, uint8_t ch_select );

#ifdef __cplusplus
}
#endif
#endif // ANALOGMUX5_H

/*! @} */ // analogmux5

// ------------------------------------------------------------------------ END
