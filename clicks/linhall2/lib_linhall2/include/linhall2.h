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
 * @file linhall2.h
 * @brief This file contains API for LIN Hall 2 Click Driver.
 */

#ifndef LINHALL2_H
#define LINHALL2_H

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
 * @addtogroup linhall2 LIN Hall 2 Click Driver
 * @brief API for configuring and manipulating LIN Hall 2 Click driver.
 * @{
 */

/**
 * @defgroup linhall2_set LIN Hall 2 Registers Settings
 * @brief Settings for registers of LIN Hall 2 Click driver.
 */

/**
 * @addtogroup linhall2_set
 * @{
 */

/**
 * @brief LIN Hall 2 description setting.
 * @details Specified setting for description of LIN Hall 2 Click driver.
 */
#define LINHALL2_VOLTAGE_AT_0_MT                1.65f
#define LINHALL2_SENSITIVITY                    0.015f

/**
 * @brief LIN Hall 2 EN pin setting.
 * @details Specified setting for EN pin states of LIN Hall 2 Click driver.
 */
#define LINHALL2_ENABLE_DEVICE                  0x01
#define LINHALL2_DISABLE_DEVICE                 0x00

/*! @} */ // linhall2_set

/**
 * @defgroup linhall2_map LIN Hall 2 MikroBUS Map
 * @brief MikroBUS pin mapping of LIN Hall 2 Click driver.
 */

/**
 * @addtogroup linhall2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LIN Hall 2 Click to the selected MikroBUS.
 */
#define LINHALL2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // linhall2_map
/*! @} */ // linhall2

/**
 * @brief LIN Hall 2 Click context object.
 * @details Context object definition of LIN Hall 2 Click driver.
 */
typedef struct
{
    digital_out_t en;                   /**< Enable pin. */

    analog_in_t adc;                    /**< ADC module object. */

} linhall2_t;

/**
 * @brief LIN Hall 2 Click configuration object.
 * @details Configuration object definition of LIN Hall 2 Click driver.
 */
typedef struct
{
    pin_name_t an;                      /**< Analog pin descriptor. */
    pin_name_t en;                      /**< Enable pin. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} linhall2_cfg_t;

/**
 * @brief LIN Hall 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LINHALL2_OK = 0,
    LINHALL2_ERROR = -1

} linhall2_return_value_t;

/*!
 * @addtogroup linhall2 LIN Hall 2 Click Driver
 * @brief API for configuring and manipulating LIN Hall 2 Click driver.
 * @{
 */

/**
 * @brief LIN Hall 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #linhall2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void linhall2_cfg_setup ( linhall2_cfg_t *cfg );

/**
 * @brief LIN Hall 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #linhall2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #linhall2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t linhall2_init ( linhall2_t *ctx, linhall2_cfg_t *cfg );

/**
 * @brief LIN Hall 2 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #linhall2_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t linhall2_read_an_pin_value ( linhall2_t *ctx, uint16_t *data_out );

/**
 * @brief LIN Hall 2 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #linhall2_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t linhall2_read_an_pin_voltage ( linhall2_t *ctx, float *data_out );

/**
 * @brief LIN Hall 2 set EN pin state function.
 * @details This function is used to set EN pin state of the LIN Hall 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #linhall2_t object definition for detailed explanation.
 * @param[in] pin_state : State of the EN pin state.
 * @return Nothing.
 * @note None.
 */
void linhal2_set_en_pin ( linhall2_t *ctx, uint8_t pin_state );

/**
 * @brief LIN Hall 2 read flux density function.
 * @details This function reads magnetic flux density in mT.
 * @param[in] ctx : Click context object.
 * See #linhall2_t object definition for detailed explanation.
 * @param[out] data_out : Magnetic flux density in mT.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t linhal2_get_flux_density ( linhall2_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // LINHALL2_H

/*! @} */ // linhall2

// ------------------------------------------------------------------------ END
