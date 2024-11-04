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
 * @file waterdetect3.h
 * @brief This file contains API for Water Detect 3 Click Driver.
 */

#ifndef WATERDETECT3_H
#define WATERDETECT3_H

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
 * @addtogroup waterdetect3 Water Detect 3 Click Driver
 * @brief API for configuring and manipulating Water Detect 3 Click driver.
 * @{
 */

/**
 * @addtogroup waterdetect3_set
 * @{
 */

/**
 * @brief Water Detect 3 description setting.
 * @details Specified setting for description of Water Detect 3 Click driver.
 */
#define WATERDETECT3_PIN_STATE_HIGH         0x01
#define WATERDETECT3_PIN_STATE_LOW          0x00

/*! @} */ // waterdetect3_set

/**
 * @defgroup waterdetect3_map Water Detect 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Water Detect 3 Click driver.
 */

/**
 * @addtogroup waterdetect3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Water Detect 3 Click to the selected MikroBUS.
 */
#define WATERDETECT3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // waterdetect3_map
/*! @} */ // waterdetect3

/**
 * @brief Water Detect 3 Click context object.
 * @details Context object definition of Water Detect 3 Click driver.
 */
typedef struct
{
    digital_in_t int_pin;       /**< Interrupt pin. */

} waterdetect3_t;

/**
 * @brief Water Detect 3 Click configuration object.
 * @details Configuration object definition of Water Detect 3 Click driver.
 */
typedef struct
{
    pin_name_t int_pin;    /**< Interrupt pin. */

} waterdetect3_cfg_t;

/**
 * @brief Water Detect 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WATERDETECT3_OK = 0,
    WATERDETECT3_ERROR = -1

} waterdetect3_return_value_t;

/*!
 * @addtogroup waterdetect3 Water Detect 3 Click Driver
 * @brief API for configuring and manipulating Water Detect 3 Click driver.
 * @{
 */

/**
 * @brief Water Detect 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #waterdetect3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void waterdetect3_cfg_setup ( waterdetect3_cfg_t *cfg );

/**
 * @brief Water Detect 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #waterdetect3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #waterdetect3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waterdetect3_init ( waterdetect3_t *ctx, waterdetect3_cfg_t *cfg );

/**
 * @brief Water Detect 3 interrupt pin reading function.
 * @details This function reads the state of the interrupt pin of Water Detect 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #waterdetect3_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t waterdetect3_get_int ( waterdetect3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // WATERDETECT3_H

/*! @} */ // waterdetect3

// ------------------------------------------------------------------------ END
