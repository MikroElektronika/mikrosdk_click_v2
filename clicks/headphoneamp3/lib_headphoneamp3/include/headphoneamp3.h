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
 * @file headphoneamp3.h
 * @brief This file contains API for Headphone AMP 3 Click Driver.
 */

#ifndef HEADPHONEAMP3_H
#define HEADPHONEAMP3_H

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

/*!
 * @addtogroup headphoneamp3 Headphone AMP 3 Click Driver
 * @brief API for configuring and manipulating Headphone AMP 3 Click driver.
 * @{
 */

/**
 * @addtogroup headphoneamp3_set
 * @{
 */

/**
 * @brief Headphone AMP 3 description setting.
 * @details Specified setting for description of Headphone AMP 3 Click driver.
 */
#define HEADPHONEAMP3_ENABLE                    0x01
#define HEADPHONEAMP3_DISABLE                   0x00

/*! @} */ // headphoneamp3_set

/**
 * @defgroup headphoneamp3_map Headphone AMP 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Headphone AMP 3 Click driver.
 */

/**
 * @addtogroup headphoneamp3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Headphone AMP 3 Click to the selected MikroBUS.
 */
#define HEADPHONEAMP3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.enp = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ena = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // headphoneamp3_map
/*! @} */ // headphoneamp3

/**
 * @brief Headphone AMP 3 Click context object.
 * @details Context object definition of Headphone AMP 3 Click driver.
 */
typedef struct
{
    digital_out_t enp;     /**< Enable power pin. */
    digital_out_t ena;     /**< Enable amp pin. */

} headphoneamp3_t;

/**
 * @brief Headphone AMP 3 Click configuration object.
 * @details Configuration object definition of Headphone AMP 3 Click driver.
 */
typedef struct
{
    pin_name_t enp;    /**< Enable power pin. */
    pin_name_t ena;    /**< Enable amp pin. */

} headphoneamp3_cfg_t;

/**
 * @brief Headphone AMP 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HEADPHONEAMP3_OK = 0,
    HEADPHONEAMP3_ERROR = -1

} headphoneamp3_return_value_t;

/*!
 * @addtogroup headphoneamp3 Headphone AMP 3 Click Driver
 * @brief API for configuring and manipulating Headphone AMP 3 Click driver.
 * @{
 */

/**
 * @brief Headphone AMP 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #headphoneamp3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void headphoneamp3_cfg_setup ( headphoneamp3_cfg_t *cfg );

/**
 * @brief Headphone AMP 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #headphoneamp3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #headphoneamp3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t headphoneamp3_init ( headphoneamp3_t *ctx, headphoneamp3_cfg_t *cfg );

/**
 * @brief Headphone AMP 3 default configuration function.
 * @details This function executes a default configuration of Headphone AMP 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #headphoneamp3_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void headphoneamp3_default_cfg ( headphoneamp3_t *ctx );

/**
 * @brief Headphone AMP 3 power pin setting function.
 * @details This function sets the power pin on the selected level of
 * Headphone AMP 3 click board.
 * @param[in] ctx : Click context object.
 * See #headphoneamp3_t object definition for detailed explanation.
 * @param[in] state : State of the pin.
 * @return Nothing.
 * @note None.
 */
void headphoneamp3_enable_power ( headphoneamp3_t *ctx, uint8_t state );

/**
 * @brief Headphone AMP 3 amp pin setting function.
 * @details This function sets the amp pin on the selected level of
 * Headphone AMP 3 click board.
 * @param[in] ctx : Click context object.
 * See #headphoneamp3_t object definition for detailed explanation.
 * @param[in] state : State of the pin.
 * @return Nothing.
 * @note None.
 */
void headphoneamp3_enable_amp ( headphoneamp3_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // HEADPHONEAMP3_H

/*! @} */ // headphoneamp3

// ------------------------------------------------------------------------ END
