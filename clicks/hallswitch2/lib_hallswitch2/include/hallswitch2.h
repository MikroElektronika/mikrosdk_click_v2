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
 * @file hallswitch2.h
 * @brief This file contains API for Hall Switch 2 Click Driver.
 */

#ifndef HALLSWITCH2_H
#define HALLSWITCH2_H

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
 * @addtogroup hallswitch2 Hall Switch 2 Click Driver
 * @brief API for configuring and manipulating Hall Switch 2 Click driver.
 * @{
 */

/**
 * @defgroup hallswitch2_set Hall Switch 2 setting.
 * @brief Specified settings for Hall Switch 2 Click driver.
 */

/**
 * @addtogroup hallswitch2_set
 * @{
 */

/**
 * @brief Hall Switch 2 switch state values.
 * @details Specified switch state values of Hall Switch 2 Click driver.
 */
#define HALLSWITCH2_NO_MAGNET_DETECTED       0
#define HALLSWITCH2_S_POLE_DETECTED          1
#define HALLSWITCH2_N_POLE_DETECTED          2

/*! @} */ // hallswitch2_set

/**
 * @defgroup hallswitch2_map Hall Switch 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Switch 2 Click driver.
 */

/**
 * @addtogroup hallswitch2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Switch 2 Click to the selected MikroBUS.
 */
#define HALLSWITCH2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.n = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.s = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hallswitch2_map
/*! @} */ // hallswitch2

/**
 * @brief Hall Switch 2 Click context object.
 * @details Context object definition of Hall Switch 2 Click driver.
 */
typedef struct
{
    digital_in_t  n;        /**< North pole pin. */
    digital_in_t  s;        /**< South pole pin. */

} hallswitch2_t;

/**
 * @brief Hall Switch 2 Click configuration object.
 * @details Configuration object definition of Hall Switch 2 Click driver.
 */
typedef struct
{
    pin_name_t  n;          /**< North pole pin. */
    pin_name_t  s;          /**< South pole pin. */

} hallswitch2_cfg_t;

/**
 * @brief Hall Switch 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLSWITCH2_OK = 0,
    HALLSWITCH2_ERROR = -1

} hallswitch2_return_value_t;

/*!
 * @addtogroup hallswitch2 Hall Switch 2 Click Driver
 * @brief API for configuring and manipulating Hall Switch 2 Click driver.
 * @{
 */

/**
 * @brief Hall Switch 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallswitch2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallswitch2_cfg_setup ( hallswitch2_cfg_t *cfg );

/**
 * @brief Hall Switch 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hallswitch2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallswitch2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch2_init ( hallswitch2_t *ctx, hallswitch2_cfg_t *cfg );

/**
 * @brief Hall Switch 2 check state function.
 * @details This function checks the S and N pin states, which indicates a magnetic field poles.
 * @param[in] ctx : Click context object.
 * See #hallswitch2_t object definition for detailed explanation.
 * @return @li @c 0 - No magnet detected,
 *         @li @c 1 - South pole detected,
 *         @li @c 2 - North pole detected.
 * @note None.
 */
uint8_t hallswitch2_check_state ( hallswitch2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HALLSWITCH2_H

/*! @} */ // hallswitch2

// ------------------------------------------------------------------------ END
