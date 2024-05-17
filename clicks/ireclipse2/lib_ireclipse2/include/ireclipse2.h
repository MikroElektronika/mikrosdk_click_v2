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
 * @file ireclipse2.h
 * @brief This file contains API for IR Eclipse 2 Click Driver.
 */

#ifndef IRECLIPSE2_H
#define IRECLIPSE2_H

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
 * @addtogroup ireclipse2 IR Eclipse 2 Click Driver
 * @brief API for configuring and manipulating IR Eclipse 2 Click driver.
 * @{
 */

/**
 * @addtogroup ireclipse2_set
 * @{
 */

/**
 * @brief IR Eclipse 2 description setting.
 * @details Specified setting for description of IR Eclipse 2 Click driver.
 */
#define IRECLIPSE2_STATE_NO_ECLIPSE            0
#define IRECLIPSE2_STATE_ECLIPSE               1

/*! @} */ // ireclipse2_set

/**
 * @defgroup ireclipse2_map IR Eclipse 2 MikroBUS Map
 * @brief MikroBUS pin mapping of IR Eclipse 2 Click driver.
 */

/**
 * @addtogroup ireclipse2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Eclipse 2 Click to the selected MikroBUS.
 */
#define IRECLIPSE2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ireclipse2_map
/*! @} */ // ireclipse2

/**
 * @brief IR Eclipse 2 Click context object.
 * @details Context object definition of IR Eclipse 2 Click driver.
 */
typedef struct
{
    digital_out_t en;        /**< Enable pin. */

    digital_in_t int_pin;    /**< Eclipse state detection pin. */

} ireclipse2_t;

/**
 * @brief IR Eclipse 2 Click configuration object.
 * @details Configuration object definition of IR Eclipse 2 Click driver.
 */
typedef struct
{
    pin_name_t en;         /**< Enable pin. */
    pin_name_t int_pin;    /**< Eclipse state detection pin. */

} ireclipse2_cfg_t;

/**
 * @brief IR Eclipse 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IRECLIPSE2_OK = 0,
    IRECLIPSE2_ERROR = -1

} ireclipse2_return_value_t;

/*!
 * @addtogroup ireclipse2 IR Eclipse 2 Click Driver
 * @brief API for configuring and manipulating IR Eclipse 2 Click driver.
 * @{
 */

/**
 * @brief IR Eclipse 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ireclipse2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ireclipse2_cfg_setup ( ireclipse2_cfg_t *cfg );

/**
 * @brief IR Eclipse 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ireclipse2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ireclipse2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ireclipse2_init ( ireclipse2_t *ctx, ireclipse2_cfg_t *cfg );

/**
 * @brief IR Eclipse 2 enable function.
 * @details This function enables the transmitter of the photo-microsensor
 * of IR Eclipse 2 click board.
 * @param[in] ctx : Click context object.
 * See #ireclipse2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void ireclipse2_enable ( ireclipse2_t *ctx );

/**
 * @brief IR Eclipse 2 disable function.
 * @details This function disables the transmitter of the photo-microsensor
 * of IR Eclipse 2 click board.
 * @param[in] ctx : Click context object.
 * See #ireclipse2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void ireclipse2_disable ( ireclipse2_t *ctx );

/**
 * @brief IR Eclipse 2 get state function.
 * @details This function detecting eclipse states
 * of IR Eclipse 2 click board.
 * @param[in] ctx : Click context object.
 * See #ireclipse2_t object definition for detailed explanation.
 * @return @li @c 0 - Eclipse not detected,
 *         @li @c 1 - Eclipse is detected.
 * @note None.
 */
uint8_t ireclipse2_get_state ( ireclipse2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // IRECLIPSE2_H

/*! @} */ // ireclipse2

// ------------------------------------------------------------------------ END
