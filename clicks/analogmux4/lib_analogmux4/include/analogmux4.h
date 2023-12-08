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
 * @file analogmux4.h
 * @brief This file contains API for Analog MUX 4 Click Driver.
 */

#ifndef ANALOGMUX4_H
#define ANALOGMUX4_H

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
 * @addtogroup analogmux4 Analog MUX 4 Click Driver
 * @brief API for configuring and manipulating Analog MUX 4 Click driver.
 * @{
 */

/**
 * @defgroup analogmux4_set Analog MUX 4 Registers Settings
 * @brief Settings for registers of Analog MUX 4 Click driver.
 */

/**
 * @addtogroup analogmux4_set
 * @{
 */

/**
 * @brief Analog MUX 4 ADC channel number.
 * @details Specified ADC channel numbers of Analog MUX 4 Click driver.
 */
#define ANALOGMUX4_CHANNEL_0                0x00
#define ANALOGMUX4_CHANNEL_1                0x01
#define ANALOGMUX4_CHANNEL_2                0x02
#define ANALOGMUX4_CHANNEL_3                0x03
#define ANALOGMUX4_CHANNEL_4                0x04
#define ANALOGMUX4_CHANNEL_5                0x05
#define ANALOGMUX4_CHANNEL_6                0x06
#define ANALOGMUX4_CHANNEL_7                0x07

/*! @} */ // analogmux4_set

/**
 * @defgroup analogmux4_map Analog MUX 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Analog MUX 4 Click driver.
 */

/**
 * @addtogroup analogmux4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Analog MUX 4 Click to the selected MikroBUS.
 */
#define ANALOGMUX4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.a2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.a0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.a1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // analogmux4_map
/*! @} */ // analogmux4

/**
 * @brief Analog MUX 4 Click context object.
 * @details Context object definition of Analog MUX 4 Click driver.
 */
typedef struct
{
    digital_out_t  a0;     /**< Address line 0. */
    digital_out_t  en;     /**< Enable input. */
    digital_out_t  a2;     /**< Address line 2. */
    digital_out_t  a1;     /**< Address line 1. */

    analog_in_t  adc;      /**< ADC module object. */

} analogmux4_t;

/**
 * @brief Analog MUX 4 Click configuration object.
 * @details Configuration object definition of Analog MUX 4 Click driver.
 */
typedef struct
{
    pin_name_t  an;     /**< Analog pin descriptor. */
    pin_name_t  a0;     /**< Address line 0. */
    pin_name_t  en;     /**< Enable input. */
    pin_name_t  a2;     /**< Address line 2. */
    pin_name_t  a1;     /**< Address line 1. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} analogmux4_cfg_t;

/**
 * @brief Analog MUX 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ANALOGMUX4_OK = 0,
    ANALOGMUX4_ERROR = -1

} analogmux4_return_value_t;

/*!
 * @addtogroup analogmux4 Analog MUX 4 Click Driver
 * @brief API for configuring and manipulating Analog MUX 4 Click driver.
 * @{
 */

/**
 * @brief Analog MUX 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #analogmux4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void analogmux4_cfg_setup ( analogmux4_cfg_t *cfg );

/**
 * @brief Analog MUX 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #analogmux4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #analogmux4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t analogmux4_init ( analogmux4_t *ctx, analogmux4_cfg_t *cfg );

/**
 * @brief Analog MUX 4 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #analogmux4_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t analogmux4_read_an_pin_value ( analogmux4_t *ctx, uint16_t *data_out );

/**
 * @brief Analog MUX 4 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #analogmux4_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t analogmux4_read_an_pin_voltage ( analogmux4_t *ctx, float *data_out );

/**
 * @brief Analog MUX 4 enable input function.
 * @details This function enables analog inputs.
 * @param[in] ctx : Click context object.
 * See #analogmux4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void analogmux4_enable_input ( analogmux4_t *ctx );

/**
 * @brief Analog MUX 4 disable input function.
 * @details This function disables analog inputs.
 * @param[in] ctx : Click context object.
 * See #analogmux4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void analogmux4_disable_input ( analogmux4_t *ctx );

/**
 * @brief Analog MUX 4 set input channel function.
 * @details This function sets the analog input channel.
 * @param[in] ctx : Click context object.
 * See #analogmux4_t object definition for detailed explanation.
 * @param[in] channel : Channel selection [0-7].
 * @return None.
 * @note None.
 */
void analogmux4_set_input_channel ( analogmux4_t *ctx, uint8_t channel );

#ifdef __cplusplus
}
#endif
#endif // ANALOGMUX4_H

/*! @} */ // analogmux4

// ------------------------------------------------------------------------ END
