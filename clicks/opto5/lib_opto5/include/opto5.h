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
 * @file opto5.h
 * @brief This file contains API for Opto 5 Click Driver.
 */

#ifndef OPTO5_H
#define OPTO5_H

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
 * @addtogroup opto5 Opto 5 Click Driver
 * @brief API for configuring and manipulating Opto 5 Click driver.
 * @{
 */

/**
 * @defgroup opto5_map Opto 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Opto 5 Click driver.
 */

/**
 * @addtogroup opto5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Opto 5 Click to the selected MikroBUS.
 */
#define OPTO5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // opto5_map
/*! @} */ // opto5

/**
 * @brief Opto 5 Click context object.
 * @details Context object definition of Opto 5 Click driver.
 */
typedef struct
{
    digital_out_t  pwm;     /**< Cathode pin output. */

} opto5_t;

/**
 * @brief Opto 5 Click configuration object.
 * @details Configuration object definition of Opto 5 Click driver.
 */
typedef struct
{
    pin_name_t  pwm;    /**< Cathode pin output. */

} opto5_cfg_t;

/*!
 * @addtogroup opto5 Opto 5 Click Driver
 * @brief API for configuring and manipulating Opto 5 Click driver.
 * @{
 */

/**
 * @brief Opto 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #opto5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void opto5_cfg_setup ( opto5_cfg_t *cfg );

/**
 * @brief Opto 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #opto5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #opto5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t opto5_init ( opto5_t *ctx, opto5_cfg_t *cfg );

/**
 * @brief Opto 5 default configuration function.
 * @details This function executes a default configuration of Opto 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #opto5_t object definition for detailed explanation.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void opto5_default_cfg ( opto5_t *ctx );

/**
 * @brief Opto 5 pin setting function.
 * @details This function sets the target pin on the high level of
 * Opto 5 Click board.
 * @param[in] ctx : Click context object.
 * See #opto5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void opto5_pin_set ( opto5_t *ctx );

/**
 * @brief Opto 5 pin clearing function.
 * @details This function clears the target pin on the low level of
 * Opto 5 Click board.
 * @param[in] ctx : Click context object.
 * See #opto5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void opto5_pin_clear ( opto5_t *ctx );

/**
 * @brief Opto 5 pin toggling function.
 * @details This function toggles the target pin from high to low level of
 * Opto 5 Click board, and vice versa.
 * @param[in] ctx : Click context object.
 * See #opto5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void opto5_pin_toggle ( opto5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // OPTO5_H

/*! @} */ // opto5

// ------------------------------------------------------------------------ END
