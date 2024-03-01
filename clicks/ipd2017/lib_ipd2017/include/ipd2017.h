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
 * @file ipd2017.h
 * @brief This file contains API for IPD 2017 Click Driver.
 */

#ifndef IPD2017_H
#define IPD2017_H

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
 * @addtogroup ipd2017 IPD 2017 Click Driver
 * @brief API for configuring and manipulating IPD 2017 Click driver.
 * @{
 */

/**
 * @addtogroup ipd2017_set
 * @{
 */

/**
 * @brief IPD 2017 description setting.
 * @details Specified setting for description of IPD 2017 Click driver.
 */
#define IPD2017_NONE_PIN_MASK           0x00
#define IPD2017_OUT1_PIN_MASK           0x01
#define IPD2017_OUT2_PIN_MASK           0x02
#define IPD2017_OUT3_PIN_MASK           0x04
#define IPD2017_OUT4_PIN_MASK           0x08
#define IPD2017_ALL_PIN_MASK            0x0F

/**
 * @brief IPD 2017 pin state setting.
 * @details Specified setting for pin state of IPD 2017 Click driver.
 */
#define IPD2017_PIN_STATE_HIGH          0x01
#define IPD2017_PIN_STATE_LOW           0x00

/*! @} */ // ipd2017_set

/**
 * @defgroup ipd2017_map IPD 2017 MikroBUS Map
 * @brief MikroBUS pin mapping of IPD 2017 Click driver.
 */

/**
 * @addtogroup ipd2017_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IPD 2017 Click to the selected MikroBUS.
 */
#define IPD2017_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in3 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.in4 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ipd2017_map
/*! @} */ // ipd2017

/**
 * @brief IPD 2017 Click context object.
 * @details Context object definition of IPD 2017 Click driver.
 */
typedef struct
{
    digital_out_t in1;      /**< Input pin for channel 1. */
    digital_out_t in2;      /**< Input pin for channel 2. */
    digital_out_t in3;      /**< Input pin for channel 3. */
    digital_out_t in4;      /**< Input pin for channel 4. */

    uint8_t state;          /**< State of the Output pins. */

} ipd2017_t;

/**
 * @brief IPD 2017 Click configuration object.
 * @details Configuration object definition of IPD 2017 Click driver.
 */
typedef struct
{
    pin_name_t in1;     /**< Input pin for channel 1. */
    pin_name_t in2;     /**< Input pin for channel 2. */
    pin_name_t in3;     /**< Input pin for channel 3. */
    pin_name_t in4;     /**< Input pin for channel 4. */

} ipd2017_cfg_t;

/**
 * @brief IPD 2017 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IPD2017_OK = 0,
    IPD2017_ERROR = -1

} ipd2017_return_value_t;

/*!
 * @addtogroup ipd2017 IPD 2017 Click Driver
 * @brief API for configuring and manipulating IPD 2017 Click driver.
 * @{
 */

/**
 * @brief IPD 2017 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ipd2017_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ipd2017_cfg_setup ( ipd2017_cfg_t *cfg );

/**
 * @brief IPD 2017 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ipd2017_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ipd2017_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipd2017_init ( ipd2017_t *ctx, ipd2017_cfg_t *cfg );

/**
 * @brief IPD 2017 pin setting function.
 * @details This function is used to set all pins to the high level of
 * IPD 2017 click board.
 * @param[in] ctx : Click context object.
 * See #ipd2017_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void ipd2017_all_pins_set ( ipd2017_t *ctx );

/**
 * @brief IPD 2017 pin clearing function.
 * @details This function is usedd to set all pins to the low level of
 * IPD 2017 click board.
 * @param[in] ctx : Click context object.
 * See #ipd2017_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void ipd2017_all_pins_clear ( ipd2017_t *ctx );

/**
 * @brief IPD 2017 set output level function.
 * @details This function is used to set output level state.
 * @param[out] ctx : Click context object.
 * See #ipd2017_t object definition for detailed explanation.
 * @param[in] out_sel : Selected output channel.
 * @param[in] state : State of the selected output channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipd2017_set_out_level ( ipd2017_t *ctx, uint8_t out_sel, uint8_t state );

/**
 * @brief IPD 2017 get output level function.
 * @details This function is used to get output level state.
 * @param[out] ctx : Click context object.
 * See #ipd2017_t object definition for detailed explanation.
 * @return State of the output pins.
 * @note None.
 */
uint8_t ipd2017_get_out_state ( ipd2017_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // IPD2017_H

/*! @} */ // ipd2017

// ------------------------------------------------------------------------ END
