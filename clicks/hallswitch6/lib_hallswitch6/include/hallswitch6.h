/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file hallswitch6.h
 * @brief This file contains API for Hall Switch 6 Click Driver.
 */

#ifndef HALLSWITCH6_H
#define HALLSWITCH6_H

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
 * @addtogroup hallswitch6 Hall Switch 6 Click Driver
 * @brief API for configuring and manipulating Hall Switch 6 Click driver.
 * @{
 */

/**
 * @defgroup hallswitch6_set Hall Switch 6 Settings
 * @brief Settings of Hall Switch 6 Click driver.
 */

/**
 * @addtogroup hallswitch6_set
 * @{
 */

/**
 * @brief Hall Switch 6 pin logic state setting.
 * @details Specified setting for pin logic state of Hall Switch 6 Click driver.
 */
#define HALLSWITCH6_PIN_STATE_LOW       0
#define HALLSWITCH6_PIN_STATE_HIGH      1

/**
 * @brief Hall Switch 6 magnetic pole setting.
 * @details Specified setting for magnetic pole of Hall Switch 6 Click driver.
 */
#define HALLSWITCH6_NO_MAGNET           0
#define HALLSWITCH6_SOUTH_POLE          1
#define HALLSWITCH6_NORTH_POLE          2
#define HALLSWITCH6_POLE_UNINIT         0xFF

/*! @} */ // hallswitch6_set

/**
 * @defgroup hallswitch6_map Hall Switch 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Switch 6 Click driver.
 */

/**
 * @addtogroup hallswitch6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Switch 6 Click to the selected MikroBUS.
 */
#define HALLSWITCH6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.ot1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.ot2 = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // hallswitch6_map
/*! @} */ // hallswitch6

/**
 * @brief Hall Switch 6 Click context object.
 * @details Context object definition of Hall Switch 6 Click driver.
 */
typedef struct
{
    digital_in_t ot1;         /**< Output1 pin (positive flux). */
    digital_in_t ot2;         /**< Output2 pin (negative flux). */

} hallswitch6_t;

/**
 * @brief Hall Switch 6 Click configuration object.
 * @details Configuration object definition of Hall Switch 6 Click driver.
 */
typedef struct
{
    pin_name_t ot1;           /**< Output1 pin (positive flux). */
    pin_name_t ot2;           /**< Output2 pin (negative flux). */

} hallswitch6_cfg_t;

/**
 * @brief Hall Switch 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLSWITCH6_OK = 0,
    HALLSWITCH6_ERROR = -1

} hallswitch6_return_value_t;

/*!
 * @addtogroup hallswitch6 Hall Switch 6 Click Driver
 * @brief API for configuring and manipulating Hall Switch 6 Click driver.
 * @{
 */

/**
 * @brief Hall Switch 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallswitch6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallswitch6_cfg_setup ( hallswitch6_cfg_t *cfg );

/**
 * @brief Hall Switch 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hallswitch6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallswitch6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch6_init ( hallswitch6_t *ctx, hallswitch6_cfg_t *cfg );

/**
 * @brief Hall Switch 6 get OUT1 pin function.
 * @details This function reads the state of the OUT1 pin, which goes LOW
 * when positive flux exceeds the BOP threshold.
 * @param[in] ctx : Click context object.
 * See #hallswitch6_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t hallswitch6_get_out1_pin ( hallswitch6_t *ctx );

/**
 * @brief Hall Switch 6 get OUT2 pin function.
 * @details This function reads the state of the OUT2 pin, which goes LOW
 * when negative flux exceeds the BOP threshold.
 * @param[in] ctx : Click context object.
 * See #hallswitch6_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t hallswitch6_get_out2_pin ( hallswitch6_t *ctx );

/**
 * @brief Hall Switch 6 get magnetic pole function.
 * @details This function reads both output pins and returns which magnetic
 * pole is currently detected, if any.
 * @param[in] ctx : Click context object.
 * See #hallswitch6_t object definition for detailed explanation.
 * @return @li @c 0 - No magnet in range,
 *         @li @c 1 - South pole detected on OUT1,
 *         @li @c 2 - North pole detected on OUT2.
 * @note None.
 */
uint8_t hallswitch6_get_pole ( hallswitch6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HALLSWITCH6_H

/*! @} */ // hallswitch6

// ------------------------------------------------------------------------ END
