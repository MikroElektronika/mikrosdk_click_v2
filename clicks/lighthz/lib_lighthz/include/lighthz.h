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
 * @file lighthz.h
 * @brief This file contains API for LightHz Click Driver.
 */

#ifndef LIGHTHZ_H
#define LIGHTHZ_H

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

/*!
 * @addtogroup lighthz LightHz Click Driver
 * @brief API for configuring and manipulating LightHz Click driver.
 * @{
 */

/**
 * @defgroup lighthz_set LightHz Settings
 * @brief Settings for LightHz Click driver.
 */

/**
 * @addtogroup lighthz_set
 * @{
 */

/**
 * @brief LightHz pin logic state setting.
 * @details Specified setting for pin logic state of LightHz Click driver.
 */
#define LIGHTHZ_PIN_STATE_LOW                   0
#define LIGHTHZ_PIN_STATE_HIGH                  1

/**
 * @brief LightHz sensitivity setting.
 * @details Specified setting for sensitivity of LightHz Click driver.
 */
#define LIGHTHZ_SENS_POWER_DOWN                 0
#define LIGHTHZ_SENS_1X                         1
#define LIGHTHZ_SENS_10X                        2
#define LIGHTHZ_SENS_100X                       3

/**
 * @brief LightHz frequency scaling setting.
 * @details Specified setting for frequency scaling of LightHz Click driver.
 */
#define LIGHTHZ_FSCALE_1                        0
#define LIGHTHZ_FSCALE_2                        1
#define LIGHTHZ_FSCALE_10                       2
#define LIGHTHZ_FSCALE_100                      3

/**
 * @brief LightHz frequency measurement setting.
 * @details Specified setting for frequency measurement of LightHz Click driver.
 */
#define LIGHTHZ_DELAY_US                        10
#define LIGHTHZ_MAX_COUNTS_PER_S                100000ul
#define LIGHTHZ_SAMPLE_COUNTS                   100

/*! @} */ // lighthz_set

/**
 * @defgroup lighthz_map LightHz MikroBUS Map
 * @brief MikroBUS pin mapping of LightHz Click driver.
 */

/**
 * @addtogroup lighthz_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LightHz Click to the selected MikroBUS.
 */
#define LIGHTHZ_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.s1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.s3 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.s2 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.s0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.freq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lighthz_map
/*! @} */ // lighthz

/**
 * @brief LightHz Click context object.
 * @details Context object definition of LightHz Click driver.
 */
typedef struct
{
    digital_out_t s1;           /**< S1 logic pin. */
    digital_out_t s3;           /**< S3 logic pin. */
    digital_out_t s2;           /**< S2 logic pin. */
    digital_out_t s0;           /**< S0 logic pin. */

    digital_in_t freq;          /**< Frequency input pin. */

} lighthz_t;

/**
 * @brief LightHz Click configuration object.
 * @details Configuration object definition of LightHz Click driver.
 */
typedef struct
{
    pin_name_t s1;              /**< S1 logic pin. */
    pin_name_t s3;              /**< S3 logic pin. */
    pin_name_t s2;              /**< S2 logic pin. */
    pin_name_t s0;              /**< S0 logic pin. */
    pin_name_t freq;            /**< Frequency input pin. */

} lighthz_cfg_t;

/**
 * @brief LightHz Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHTHZ_OK = 0,
    LIGHTHZ_ERROR = -1

} lighthz_return_value_t;

/*!
 * @addtogroup lighthz LightHz Click Driver
 * @brief API for configuring and manipulating LightHz Click driver.
 * @{
 */

/**
 * @brief LightHz configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lighthz_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lighthz_cfg_setup ( lighthz_cfg_t *cfg );

/**
 * @brief LightHz initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lighthz_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lighthz_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lighthz_init ( lighthz_t *ctx, lighthz_cfg_t *cfg );

/**
 * @brief LightHz set s0 pin function.
 * @details This function sets the s0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #lighthz_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void lighthz_set_s0_pin ( lighthz_t *ctx, uint8_t state );

/**
 * @brief LightHz set s1 pin function.
 * @details This function sets the s1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #lighthz_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void lighthz_set_s1_pin ( lighthz_t *ctx, uint8_t state );

/**
 * @brief LightHz set s2 pin function.
 * @details This function sets the s2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #lighthz_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void lighthz_set_s2_pin ( lighthz_t *ctx, uint8_t state );

/**
 * @brief LightHz set s3 pin function.
 * @details This function sets the s3 pin logic state.
 * @param[in] ctx : Click context object.
 * See #lighthz_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void lighthz_set_s3_pin ( lighthz_t *ctx, uint8_t state );

/**
 * @brief LightHz set sensitivity function.
 * @details This function sets the sensor sensitivity.
 * @param[in] ctx : Click context object.
 * See #lighthz_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - Power down,
 *                   @li @c 1 - 1X,
 *                   @li @c 2 - 10X,
 *                   @li @c 3 - 100X.
 * @return None.
 * @note None.
 */
void lighthz_set_sensitivity ( lighthz_t *ctx, uint8_t mode );

/**
 * @brief LightHz set frequency scaling function.
 * @details This function sets the sensor frequency scaling.
 * @param[in] ctx : Click context object.
 * See #lighthz_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - 1,
 *                   @li @c 1 - 2,
 *                   @li @c 2 - 10,
 *                   @li @c 3 - 100.
 * @return None.
 * @note None.
 */
void lighthz_set_frequency_scaling ( lighthz_t *ctx, uint8_t mode );

/**
 * @brief LightHz get freq pin function.
 * @details This function returns the freq pin logic state.
 * @param[in] ctx : Click context object.
 * See #lighthz_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lighthz_get_freq_pin ( lighthz_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LIGHTHZ_H

/*! @} */ // lighthz

// ------------------------------------------------------------------------ END
