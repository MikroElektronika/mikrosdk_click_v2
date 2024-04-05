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
 * @file dcmotor21.h
 * @brief This file contains API for DC Motor 21 Click Driver.
 */

#ifndef DCMOTOR21_H
#define DCMOTOR21_H

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
 * @addtogroup dcmotor21 DC Motor 21 Click Driver
 * @brief API for configuring and manipulating DC Motor 21 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor21_set DC Motor 21 OUT Settings
 * @brief Settings for OUT of DC Motor 21 Click driver.
 */

/**
 * @addtogroup dcmotor21_set
 * @{
 */

/**
 * @brief DC Motor 21 OUT setting.
 * @details Specified setting for OUT of DC Motor 21 Click driver.
 */
#define DCMOTOR21_OUT_LOW               0x00
#define DCMOTOR21_OUT_HIGH              0x01
#define DCMOTOR21_OUT_HIGH_Z            0x02

/*! @} */ // dcmotor21_set

/**
 * @defgroup dcmotor21_map DC Motor 21 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 21 Click driver.
 */

/**
 * @addtogroup dcmotor21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 21 Click to the selected MikroBUS.
 */
#define DCMOTOR21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.hn1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.ln1 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.hn2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ln2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dcmotor21_map
/*! @} */ // dcmotor21

/**
 * @brief DC Motor 21 Click context object.
 * @details Context object definition of DC Motor 21 Click driver.
 */
typedef struct
{
    digital_out_t  hn1;         /**< HIN1 pin. */
    digital_out_t  ln1;         /**< LIN1 pin. */
    digital_out_t  hn2;         /**< HIN2 pin. */
    digital_out_t  ln2;         /**< LIN2 pin. */

} dcmotor21_t;

/**
 * @brief DC Motor 21 Click configuration object.
 * @details Configuration object definition of DC Motor 21 Click driver.
 */
typedef struct
{
    pin_name_t  hn1;            /**< HIN1 pin. */
    pin_name_t  ln1;            /**< LIN1 pin. */
    pin_name_t  hn2;            /**< HIN2 pin. */
    pin_name_t  ln2;            /**< LIN2 pin. */

} dcmotor21_cfg_t;

/**
 * @brief DC Motor 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR21_OK = 0,
    DCMOTOR21_ERROR = -1

} dcmotor21_return_value_t;

/*!
 * @addtogroup dcmotor21 DC Motor 21 Click Driver
 * @brief API for configuring and manipulating DC Motor 21 Click driver.
 * @{
 */

/**
 * @brief DC Motor 21 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor21_cfg_setup ( dcmotor21_cfg_t *cfg );

/**
 * @brief DC Motor 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor21_init ( dcmotor21_t *ctx, dcmotor21_cfg_t *cfg );

/**
 * @brief DC Motor 21 default configuration function.
 * @details This function executes a default configuration of DC Motor 21
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor21_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void dcmotor21_default_cfg ( dcmotor21_t *ctx );

/**
 * @brief DC Motor 21 set out 1 function.
 * @details This function sets the state of output 1.
 * @param[in] ctx : Click context object.
 * See #dcmotor21_t object definition for detailed explanation.
 * @param[in] state : @li @c  0 - LOW state,
 *                    @li @c  1 - HIGH state,
 *                    @li @c  2 - HIGH-Z state.
 * @return Nothing.
 * @note None.
 */
void dcmotor21_set_out_1 ( dcmotor21_t *ctx, uint8_t state );

/**
 * @brief DC Motor 21 set out 2 function.
 * @details This function sets the state of output 2.
 * @param[in] ctx : Click context object.
 * See #dcmotor21_t object definition for detailed explanation.
 * @param[in] state : @li @c  0 - LOW state,
 *                    @li @c  1 - HIGH state,
 *                    @li @c  2 - HIGH-Z state.
 * @return Nothing.
 * @note None.
 */
void dcmotor21_set_out_2 ( dcmotor21_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR21_H

/*! @} */ // dcmotor21

// ------------------------------------------------------------------------ END
