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
 * @file brushless12.h
 * @brief This file contains API for Brushless 12 Click Driver.
 */

#ifndef BRUSHLESS12_H
#define BRUSHLESS12_H

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
 * @addtogroup brushless12 Brushless 12 Click Driver
 * @brief API for configuring and manipulating Brushless 12 Click driver.
 * @{
 */

/**
 * @defgroup brushless12_set Brushless 12 pins setting flags.
 * @brief Pins setting flags for Brushless 12 Click driver.
 */
#define BRUSHLESS12_ENABLE          1
#define BRUSHLESS12_DISABLE         0
#define BRUSHLESS12_START           1
#define BRUSHLESS12_BRAKE           0
#define BRUSHLESS12_DIR_FORWARD     1
#define BRUSHLESS12_DIR_REVERSE     0

/**
 * @addtogroup brushless12_set
 * @{
 */

/*! @} */ // brushless12_set

/**
 * @defgroup brushless12_map Brushless 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 12 Click driver.
 */

/**
 * @addtogroup brushless12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 12 Click to the selected MikroBUS.
 */
#define BRUSHLESS12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.brk = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // brushless12_map
/*! @} */ // brushless12

/**
 * @brief Brushless 12 Click context object.
 * @details Context object definition of Brushless 12 Click driver.
 */
typedef struct
{
    digital_out_t  brk;      /**< Description. */
    digital_out_t  en;       /**< Description. */
    digital_out_t  dir;      /**< Description. */

} brushless12_t;

/**
 * @brief Brushless 12 Click configuration object.
 * @details Configuration object definition of Brushless 12 Click driver.
 */
typedef struct
{
    pin_name_t  brk;         /**< Description. */
    pin_name_t  en;          /**< Description. */
    pin_name_t  dir;         /**< Description. */

} brushless12_cfg_t;

/**
 * @brief Brushless 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS12_OK = 0,
    BRUSHLESS12_ERROR = -1

} brushless12_return_value_t;

/*!
 * @addtogroup brushless12 Brushless 12 Click Driver
 * @brief API for configuring and manipulating Brushless 12 Click driver.
 * @{
 */

/**
 * @brief Brushless 12 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless12_cfg_setup ( brushless12_cfg_t *cfg );

/**
 * @brief Brushless 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless12_init ( brushless12_t *ctx, brushless12_cfg_t *cfg );

/**
 * @brief Brushless 12 default configuration function.
 * @details This function executes a default configuration of Brushless 12
 * click board.
 * @param[in] ctx : Click context object.
 * See #brushless12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless12_default_cfg ( brushless12_t *ctx );

/**
 * @brief Brushless 12 set BRK pin state function.
 * @details This function sets the BRK pin to the desired state.
 * @param[in] ctx : Click context object.
 * See #brushless12_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void brushless12_set_brake ( brushless12_t *ctx, uint8_t state );

/**
 * @brief Brushless 12 set F/R pin state function.
 * @details This function sets the F/R pin to the desired state.
 * @param[in] ctx : Click context object.
 * See #brushless12_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void brushless12_set_direction ( brushless12_t *ctx, uint8_t state );

/**
 * @brief Brushless 12 set EN pin state function.
 * @details This function sets the EN pin to the desired state.
 * @param[in] ctx : Click context object.
 * See #brushless12_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void brushless12_set_enable ( brushless12_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS12_H

/*! @} */ // brushless12

// ------------------------------------------------------------------------ END
