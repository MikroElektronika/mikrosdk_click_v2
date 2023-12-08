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
 * @file watchdog.h
 * @brief This file contains API for Watchdog Click Driver.
 */

#ifndef WATCHDOG_H
#define WATCHDOG_H

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
 * @addtogroup watchdog Watchdog Click Driver
 * @brief API for configuring and manipulating Watchdog Click driver.
 * @{
 */

/**
 * @defgroup watchdog_set Watchdog Registers Settings
 * @brief Settings for registers of Watchdog Click driver.
 */

/**
 * @addtogroup watchdog_set
 * @{
 */

/**
 * @brief Watchdog description setting.
 * @details Specified setting for description of Watchdog Click driver.
 */
#define WATCHDOG_SETUP_TIME_MODE_0                                 0x00
#define WATCHDOG_SETUP_TIME_MODE_1                                 0x01
#define WATCHDOG_SETUP_TIME_MODE_DISABLE                           0x02
#define WATCHDOG_SETUP_TIME_MODE_2                                 0x03

/*! @} */ // watchdog_set

/**
 * @defgroup watchdog_map Watchdog MikroBUS Map
 * @brief MikroBUS pin mapping of Watchdog Click driver.
 */

/**
 * @addtogroup watchdog_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Watchdog Click to the selected MikroBUS.
 */
#define WATCHDOG_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.s0 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.s1 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wdi = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.wdo = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // watchdog_map
/*! @} */ // watchdog

/**
 * @brief Watchdog Click context object.
 * @details Context object definition of Watchdog Click driver.
 */
typedef struct
{
    digital_out_t  s0;      /**< Logic Set Pin 0. */
    digital_out_t  s1;      /**< Logic Set Pin 1. */
    digital_out_t  wdi;     /**< Watchdog Input. */
    digital_in_t   wdo;     /**< Watchdog Output. */

} watchdog_t;

/**
 * @brief Watchdog Click configuration object.
 * @details Configuration object definition of Watchdog Click driver.
 */
typedef struct
{
    pin_name_t  s0;     /**< Logic Set Pin 0. */
    pin_name_t  s1;     /**< Logic Set Pin 1. */
    pin_name_t  wdi;    /**< Watchdog Input. */
    pin_name_t  wdo;    /**< Watchdog Output. */

} watchdog_cfg_t;

/**
 * @brief Watchdog Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   WATCHDOG_OK = 0,
   WATCHDOG_ERROR = -1

} watchdog_return_value_t;

/*!
 * @addtogroup watchdog Watchdog Click Driver
 * @brief API for configuring and manipulating Watchdog Click driver.
 * @{
 */

/**
 * @brief Watchdog configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #watchdog_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void watchdog_cfg_setup ( watchdog_cfg_t *cfg );

/**
 * @brief Watchdog initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #watchdog_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #watchdog_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t watchdog_init ( watchdog_t *ctx, watchdog_cfg_t *cfg );

/**
 * @brief Watchdog default configuration function.
 * @details This function executes a default configuration of Watchdog
 * click board.
 * @param[in] ctx : Click context object.
 * See #watchdog_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t watchdog_default_cfg ( watchdog_t *ctx );


/**
 * @brief Set S0 ( RST ) pin state function.
 * @details The function set the state of the S0 ( RST ) 
 * to configure a valid window watchdog ratio
 * of the TPS3430 Window Watchdog Timer with Programmable Reset Delay
 * on the Watchdog click board.
 * @param[out] ctx : Click context object.
 * See #watchdog_t object definition for detailed explanation.
 * @param set0_state
 * - 0 : Low state.
 * - 1 : High state.
 *
 * @return Nothing.
 */
void watchdog_set_set0 ( watchdog_t *ctx, uint8_t set0_state );

/**
 * @brief Set S1 ( CS ) pin state function.
 * @details The function set the state of the S1 ( CS )
 * to configure a valid window watchdog ratio
 * of the TPS3430 Window Watchdog Timer with Programmable Reset Delay
 * on the Watchdog click board.
 * @param[out] ctx : Click context object.
 * See #watchdog_t object definition for detailed explanation.
 * @param set1_state
 * - 0 : Low state.
 * - 1 : High state.
 *
 * @return Nothing.
 */
void watchdog_set_set1 ( watchdog_t *ctx, uint8_t set1_state );

/**
 * @brief Set WDI ( PWM ) pin state function.
 * @details The function set the state of the WDI ( PWM )
 * which is used to send a pulse
 * to the TPS3430 Window Watchdog Timer with Programmable Reset Delay
 * on the Watchdog click board.
 * @param[out] ctx : Click context object.
 * See #watchdog_t object definition for detailed explanation.
 * @param wdi_state
 * - 0 : Low state.
 * - 1 : High state.
 *
 * @return Nothing.
 */
void watchdog_set_wdi ( watchdog_t *ctx, uint8_t wdi_state );

/**
 * @brief Get WDO ( INT ) pin state function.
 * @details The function check the state of the WDO ( INT )
 * which is the pulse sending indicator in the watchdog timeout occurs
 * to the TPS3430 Window Watchdog Timer with Programmable Reset Delay
 * on the Watchdog click board.
 * @param[in] ctx : Click context object.
 * See #watchdog_t object definition for detailed explanation.
 * @return @li @c 0 - Fault,
 *         @li @c 1 - Correct Operation.
 */
uint8_t watchdog_get_wdo ( watchdog_t *ctx );

/**
 * @brief Send pulse function.
 * @details The function sends a pulse with the desired pulse duration
 * to the TPS3430 Window Watchdog Timer with Programmable Reset Delay
 * on the Watchdog click board.
 * @param[in] ctx : Click context object.
 * See #watchdog_t object definition for detailed explanation.
 * @param[in] p_duration_ms : The desired pulse duration time in milliseconds.
 * @return Nothing.
 *
 * @note Minimum WDI pulse duration is 50 microseconds.
 */
void watchdog_send_pulse ( watchdog_t *ctx, uint16_t p_duration_ms );

/**
 * @brief Set the watchdog time function.
 * @details The function set the desired watchdog operating mode
 * of the TPS3430 Window Watchdog Timer with Programmable Reset Delay
 * on the Watchdog click board.
 * @param[in] ctx : Click context object.
 * See #watchdog_t object definition for detailed explanation.
 * @param[in] setup_time_mode : Mode in witch Watchdog Click bord is working.  
 * @return Nothing.
 * 
 * @note For more information on Timing Requirements, 
 * please see the TPS3430 datasheet.
 */
void watchdog_setup_time ( watchdog_t *ctx, uint8_t setup_time_mode );


#ifdef __cplusplus
}
#endif
#endif // WATCHDOG_H

/*! @} */ // watchdog

// ------------------------------------------------------------------------ END
