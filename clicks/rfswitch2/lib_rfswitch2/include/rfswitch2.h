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
 * @file rfswitch2.h
 * @brief This file contains API for RF Switch 2 Click Driver.
 */

#ifndef RFSWITCH2_H
#define RFSWITCH2_H

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
 * @addtogroup rfswitch2 RF Switch 2 Click Driver
 * @brief API for configuring and manipulating RF Switch 2 Click driver.
 * @{
 */

/**
 * @defgroup rfswitch2_set RF Switch 2 Settings
 * @brief Settings of RF Switch 2 Click driver.
 */

/**
 * @addtogroup rfswitch2_set
 * @{
 */

/**
 * @brief RF Switch 2 switch mode selection setting.
 * @details Specified setting for switch mode selection of RF Switch 2 Click driver.
 */
#define RFSWITCH2_MODE_ALL_OFF       0
#define RFSWITCH2_MODE_RF1_ON        1
#define RFSWITCH2_MODE_RF2_ON        2
#define RFSWITCH2_MODE_RF3_ON        3
#define RFSWITCH2_MODE_RF4_ON        4

/*! @} */ // rfswitch2_set

/**
 * @defgroup rfswitch2_map RF Switch 2 MikroBUS Map
 * @brief MikroBUS pin mapping of RF Switch 2 Click driver.
 */

/**
 * @addtogroup rfswitch2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RF Switch 2 Click to the selected MikroBUS.
 */
#define RFSWITCH2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.v1_pin = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.v2_pin = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.v3_pin = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // rfswitch2_map
/*! @} */ // rfswitch2

/**
 * @brief RF Switch 2 Click context object.
 * @details Context object definition of RF Switch 2 Click driver.
 */
typedef struct
{
    digital_out_t v1_pin;       /**< Digital control logic pin 1. */
    digital_out_t v2_pin;       /**< Digital control logic pin 2. */
    digital_out_t v3_pin;       /**< Digital control logic pin 3. */

} rfswitch2_t;

/**
 * @brief RF Switch 2 Click configuration object.
 * @details Configuration object definition of RF Switch 2 Click driver.
 */
typedef struct
{
    pin_name_t v1_pin;          /**< Digital control logic pin 1. */
    pin_name_t v2_pin;          /**< Digital control logic pin 2. */
    pin_name_t v3_pin;          /**< Digital control logic pin 3. */

} rfswitch2_cfg_t;

/**
 * @brief RF Switch 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RFSWITCH2_OK = 0,
    RFSWITCH2_ERROR = -1

} rfswitch2_return_value_t;

/*!
 * @addtogroup rfswitch2 RF Switch 2 Click Driver
 * @brief API for configuring and manipulating RF Switch 2 Click driver.
 * @{
 */

/**
 * @brief RF Switch 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rfswitch2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rfswitch2_cfg_setup ( rfswitch2_cfg_t *cfg );

/**
 * @brief RF Switch 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rfswitch2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rfswitch2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfswitch2_init ( rfswitch2_t *ctx, rfswitch2_cfg_t *cfg );

/**
 * @brief RF Switch 2 set mode function.
 * @details This function sets the RF switch mode by setting V1, V2, and V3 pins logic state.
 * @param[in] ctx : Click context object.
 * See #rfswitch2_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - ALL OFF,
                     @li @c 1 - RF1 ON,
                     @li @c 2 - RF2 ON,
                     @li @c 3 - RF3 ON,
                     @li @c 4 - RF4 ON.
 * @return None.
 * @note None.
 */
void rfswitch2_set_mode ( rfswitch2_t *ctx, uint8_t mode );

#ifdef __cplusplus
}
#endif
#endif // RFSWITCH2_H

/*! @} */ // rfswitch2

// ------------------------------------------------------------------------ END
