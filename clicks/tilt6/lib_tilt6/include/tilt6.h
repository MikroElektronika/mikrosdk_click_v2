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
 * @file tilt6.h
 * @brief This file contains API for Tilt 6 Click Driver.
 */

#ifndef TILT6_H
#define TILT6_H

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
 * @addtogroup tilt6 Tilt 6 Click Driver
 * @brief API for configuring and manipulating Tilt 6 Click driver.
 * @{
 */

/**
 * @defgroup tilt6_set Tilt 6 Settings
 * @brief Settings of Tilt 6 Click driver.
 */

/**
 * @addtogroup tilt6_set
 * @{
 */

/**
 * @brief Tilt 6 tilt state setting.
 * @details Specified setting for tilt state of Tilt 6 Click driver.
 */
#define TILT6_STATE_IDLE        0
#define TILT6_STATE_LEFT_TILT   1
#define TILT6_STATE_RIGHT_TILT  2

/*! @} */ // tilt6_set

/**
 * @defgroup tilt6_map Tilt 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Tilt 6 Click driver.
 */

/**
 * @addtogroup tilt6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Tilt 6 Click to the selected MikroBUS.
 */
#define TILT6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.out1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.out2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // tilt6_map
/*! @} */ // tilt6

/**
 * @brief Tilt 6 Click context object.
 * @details Context object definition of Tilt 6 Click driver.
 */
typedef struct
{
    digital_in_t out1;          /**< Sensor output 1 pin (left tilt). */
    digital_in_t out2;          /**< Sensor output 2 pin (right tilt). */

} tilt6_t;

/**
 * @brief Tilt 6 Click configuration object.
 * @details Configuration object definition of Tilt 6 Click driver.
 */
typedef struct
{
    pin_name_t out1;            /**< Sensor output 1 pin (left tilt). */
    pin_name_t out2;            /**< Sensor output 2 pin (right tilt). */

} tilt6_cfg_t;

/**
 * @brief Tilt 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TILT6_OK = 0,
    TILT6_ERROR = -1

} tilt6_return_value_t;

/*!
 * @addtogroup tilt6 Tilt 6 Click Driver
 * @brief API for configuring and manipulating Tilt 6 Click driver.
 * @{
 */

/**
 * @brief Tilt 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tilt6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tilt6_cfg_setup ( tilt6_cfg_t *cfg );

/**
 * @brief Tilt 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #tilt6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tilt6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tilt6_init ( tilt6_t *ctx, tilt6_cfg_t *cfg );

/**
 * @brief Tilt 6 get OUT1 pin function.
 * @details This function returns the OUT1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #tilt6_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t tilt6_get_out1_pin ( tilt6_t *ctx );

/**
 * @brief Tilt 6 get OUT2 pin function.
 * @details This function returns the OUT2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #tilt6_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t tilt6_get_out2_pin ( tilt6_t *ctx );

/**
 * @brief Tilt 6 get tilt state function.
 * @details This function returns the tilt switch state.
 * @param[in] ctx : Click context object.
 * See #tilt6_t object definition for detailed explanation.
 * @return @li @c 0 - IDLE,
 *         @li @c 1 - Left tilt,
 *         @li @c 2 - Right tilt.
 * @note None.
 */
uint8_t tilt6_get_tilt_state ( tilt6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // TILT6_H

/*! @} */ // tilt6

// ------------------------------------------------------------------------ END
