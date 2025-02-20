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
 * @file tilt5.h
 * @brief This file contains API for Tilt 5 Click Driver.
 */

#ifndef TILT5_H
#define TILT5_H

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
 * @addtogroup tilt5 Tilt 5 Click Driver
 * @brief API for configuring and manipulating Tilt 5 Click driver.
 * @{
 */

/**
 * @defgroup tilt5_set Tilt 5 Settings
 * @brief Settings of Tilt 5 Click driver.
 */

/**
 * @addtogroup tilt5_set
 * @{
 */

/**
 * @brief Tilt 5 tilt state setting.
 * @details Specified setting for tilt state of Tilt 5 Click driver.
 */
#define TILT5_STATE_IDLE        0
#define TILT5_STATE_ACTIVE      1

/*! @} */ // tilt5_set

/**
 * @defgroup tilt5_map Tilt 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Tilt 5 Click driver.
 */

/**
 * @addtogroup tilt5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Tilt 5 Click to the selected MikroBUS.
 */
#define TILT5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.out = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // tilt5_map
/*! @} */ // tilt5

/**
 * @brief Tilt 5 Click context object.
 * @details Context object definition of Tilt 5 Click driver.
 */
typedef struct
{
    digital_in_t out;           /**< Sensor output pin. */

} tilt5_t;

/**
 * @brief Tilt 5 Click configuration object.
 * @details Configuration object definition of Tilt 5 Click driver.
 */
typedef struct
{
    pin_name_t out;             /**< Sensor output pin. */

} tilt5_cfg_t;

/**
 * @brief Tilt 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TILT5_OK = 0,
    TILT5_ERROR = -1

} tilt5_return_value_t;

/*!
 * @addtogroup tilt5 Tilt 5 Click Driver
 * @brief API for configuring and manipulating Tilt 5 Click driver.
 * @{
 */

/**
 * @brief Tilt 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tilt5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tilt5_cfg_setup ( tilt5_cfg_t *cfg );

/**
 * @brief Tilt 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #tilt5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tilt5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tilt5_init ( tilt5_t *ctx, tilt5_cfg_t *cfg );

/**
 * @brief Tilt 5 get OUT pin function.
 * @details This function returns the OUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #tilt5_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t tilt5_get_out_pin ( tilt5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // TILT5_H

/*! @} */ // tilt5

// ------------------------------------------------------------------------ END
