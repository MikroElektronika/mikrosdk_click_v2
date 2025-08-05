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
 * @file powermux3.h
 * @brief This file contains API for Power MUX 3 Click Driver.
 */

#ifndef POWERMUX3_H
#define POWERMUX3_H

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
 * @addtogroup powermux3 Power MUX 3 Click Driver
 * @brief API for configuring and manipulating Power MUX 3 Click driver.
 * @{
 */

/**
 * @defgroup powermux3_map Power MUX 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Power MUX 3 Click driver.
 */

/**
 * @addtogroup powermux3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Power MUX 3 Click to the selected MikroBUS.
 */
#define POWERMUX3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.shd = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // powermux3_map
/*! @} */ // powermux3

/**
 * @brief Power MUX 3 Click context object.
 * @details Context object definition of Power MUX 3 Click driver.
 */
typedef struct
{
    digital_out_t shd;      /**< Shutdown pin (active low). */
    digital_out_t en;       /**< Channel enable pin (active high). */

} powermux3_t;

/**
 * @brief Power MUX 3 Click configuration object.
 * @details Configuration object definition of Power MUX 3 Click driver.
 */
typedef struct
{
    pin_name_t shd;         /**< Shutdown pin (active low). */
    pin_name_t en;          /**< Channel enable pin (active high). */

} powermux3_cfg_t;

/**
 * @brief Power MUX 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    POWERMUX3_OK = 0,
    POWERMUX3_ERROR = -1

} powermux3_return_value_t;

/*!
 * @addtogroup powermux3 Power MUX 3 Click Driver
 * @brief API for configuring and manipulating Power MUX 3 Click driver.
 * @{
 */

/**
 * @brief Power MUX 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #powermux3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void powermux3_cfg_setup ( powermux3_cfg_t *cfg );

/**
 * @brief Power MUX 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #powermux3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #powermux3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powermux3_init ( powermux3_t *ctx, powermux3_cfg_t *cfg );

/**
 * @brief Power MUX 3 enable device function.
 * @details This function enables the device by setting the SHD pin to HIGH
 * on the Power MUX 3 Click board.
 * @param[in] ctx : Click context object.
 * See #powermux3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void powermux3_enable_device ( powermux3_t *ctx );

/**
 * @brief Power MUX 3 disable device function.
 * @details This function disables the device by setting the SHD pin to LOW
 * on the Power MUX 3 Click board.
 * @param[in] ctx : Click context object.
 * See #powermux3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void powermux3_disable_device ( powermux3_t *ctx );

/**
 * @brief Power MUX 3 enable output function.
 * @details This function enables the output by setting the EN pin to HIGH
 * on the Power MUX 3 Click board.
 * @param[in] ctx : Click context object.
 * See #powermux3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void powermux3_enable_output ( powermux3_t *ctx );

/**
 * @brief Power MUX 3 disable output function.
 * @details This function disables the output by setting the EN pin to LOW
 * on the Power MUX 3 Click board.
 * @param[in] ctx : Click context object.
 * See #powermux3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void powermux3_disable_output ( powermux3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // POWERMUX3_H

/*! @} */ // powermux3

// ------------------------------------------------------------------------ END
