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
 * @file vref.h
 * @brief This file contains API for VREF Click Driver.
 */

#ifndef VREF_H
#define VREF_H

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
 * @addtogroup vref VREF Click Driver
 * @brief API for configuring and manipulating VREF Click driver.
 * @{
 */

/**
 * @defgroup vref_map VREF MikroBUS Map
 * @brief MikroBUS pin mapping of VREF Click driver.
 */

/**
 * @addtogroup vref_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of VREF Click to the selected MikroBUS.
 */
#define VREF_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // vref_map
/*! @} */ // vref

/**
 * @brief VREF Click context object.
 * @details Context object definition of VREF Click driver.
 */
typedef struct
{
    digital_out_t en;       /**< Enable pin (active high). */

} vref_t;

/**
 * @brief VREF Click configuration object.
 * @details Configuration object definition of VREF Click driver.
 */
typedef struct
{
    pin_name_t en;          /**< Enable pin (active high). */

} vref_cfg_t;

/**
 * @brief VREF Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    VREF_OK = 0,
    VREF_ERROR = -1

} vref_return_value_t;

/*!
 * @addtogroup vref VREF Click Driver
 * @brief API for configuring and manipulating VREF Click driver.
 * @{
 */

/**
 * @brief VREF configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vref_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vref_cfg_setup ( vref_cfg_t *cfg );

/**
 * @brief VREF initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #vref_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vref_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vref_init ( vref_t *ctx, vref_cfg_t *cfg );

/**
 * @brief VREF Enable Output function.
 * @details This function enables VREF output by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #vref_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void vref_enable_output ( vref_t *ctx );

/**
 * @brief VREF Disable Output function.
 * @details This function disables VREF output by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #vref_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void vref_disable_output ( vref_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // VREF_H

/*! @} */ // vref

// ------------------------------------------------------------------------ END
