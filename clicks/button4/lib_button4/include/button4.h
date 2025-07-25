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
 * @file button4.h
 * @brief This file contains API for Button 4 Click Driver.
 */

#ifndef BUTTON4_H
#define BUTTON4_H

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
 * @addtogroup button4 Button 4 Click Driver
 * @brief API for configuring and manipulating Button 4 Click driver.
 * @{
 */

/**
 * @defgroup button4_set Button 4 Settings
 * @brief Settings of Button 4 Click driver.
 */

/**
 * @addtogroup button4_set
 * @{
 */

/**
 * @brief Button 4 button state setting.
 * @details Specified setting for button state of Button 4 Click driver.
 */
#define BUTTON4_BUTTON_ACTIVE       0
#define BUTTON4_BUTTON_RESET        1

/*! @} */ // button4_set

/**
 * @defgroup button4_map Button 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Button 4 Click driver.
 */

/**
 * @addtogroup button4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Button 4 Click to the selected MikroBUS.
 */
#define BUTTON4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.out = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // button4_map
/*! @} */ // button4

/**
 * @brief Button 4 Click context object.
 * @details Context object definition of Button 4 Click driver.
 */
typedef struct
{
    digital_in_t out;           /**< Button output pin (active low). */

} button4_t;

/**
 * @brief Button 4 Click configuration object.
 * @details Configuration object definition of Button 4 Click driver.
 */
typedef struct
{
    pin_name_t out;             /**< Button output pin (active low). */

} button4_cfg_t;

/**
 * @brief Button 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUTTON4_OK = 0,
    BUTTON4_ERROR = -1

} button4_return_value_t;

/*!
 * @addtogroup button4 Button 4 Click Driver
 * @brief API for configuring and manipulating Button 4 Click driver.
 * @{
 */

/**
 * @brief Button 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #button4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void button4_cfg_setup ( button4_cfg_t *cfg );

/**
 * @brief Button 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #button4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #button4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t button4_init ( button4_t *ctx, button4_cfg_t *cfg );

/**
 * @brief Button 4 get out pin function.
 * @details This function returns the OUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #button4_t object definition for detailed explanation.
 * @return @li @c 0 - Button active,
 *         @li @c 1 - Button reset.
 * @note None.
 */
uint8_t button4_get_out_pin ( button4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BUTTON4_H

/*! @} */ // button4

// ------------------------------------------------------------------------ END
