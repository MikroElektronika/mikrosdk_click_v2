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
 * @file pushbutton.h
 * @brief This file contains API for Push Button Click Driver.
 */

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

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
 * @addtogroup pushbutton Push Button Click Driver
 * @brief API for configuring and manipulating Push Button Click driver.
 * @{
 */

/**
 * @defgroup pushbutton_map Push Button MikroBUS Map
 * @brief MikroBUS pin mapping of Push Button Click driver.
 */

/**
 * @addtogroup pushbutton_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Push Button Click to the selected MikroBUS.
 */
#define PUSHBUTTON_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.out = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.clr = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pushbutton_map
/*! @} */ // pushbutton

/**
 * @brief Push Button Click context object.
 * @details Context object definition of Push Button Click driver.
 */
typedef struct
{
    digital_out_t clr;          /**< Clear output pin (active low). */

    digital_in_t out;           /**< Output pin (active high). */
    digital_in_t int_pin;       /**< Button interrupt pin (active low). */

} pushbutton_t;

/**
 * @brief Push Button Click configuration object.
 * @details Configuration object definition of Push Button Click driver.
 */
typedef struct
{
    pin_name_t out;             /**< Output pin (active high). */
    pin_name_t clr;             /**< Clear output pin (active low). */
    pin_name_t int_pin;         /**< Button interrupt pin (active low). */

} pushbutton_cfg_t;

/**
 * @brief Push Button Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PUSHBUTTON_OK = 0,
    PUSHBUTTON_ERROR = -1

} pushbutton_return_value_t;

/*!
 * @addtogroup pushbutton Push Button Click Driver
 * @brief API for configuring and manipulating Push Button Click driver.
 * @{
 */

/**
 * @brief Push Button configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pushbutton_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pushbutton_cfg_setup ( pushbutton_cfg_t *cfg );

/**
 * @brief Push Button initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pushbutton_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pushbutton_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pushbutton_init ( pushbutton_t *ctx, pushbutton_cfg_t *cfg );

/**
 * @brief Push Button clear output function.
 * @details This function clears the output by toggling the CLR pin.
 * @param[in] ctx : Click context object.
 * See #pushbutton_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void pushbutton_clear_output ( pushbutton_t *ctx );

/**
 * @brief Push Button get OUT pin function.
 * @details This function returns the OUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #pushbutton_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t pushbutton_get_out_pin ( pushbutton_t *ctx );

/**
 * @brief Push Button get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #pushbutton_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t pushbutton_get_int_pin ( pushbutton_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PUSHBUTTON_H

/*! @} */ // pushbutton

// ------------------------------------------------------------------------ END
