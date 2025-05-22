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
 * @file hallswitch5.h
 * @brief This file contains API for Hall Switch 5 Click Driver.
 */

#ifndef HALLSWITCH5_H
#define HALLSWITCH5_H

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
 * @addtogroup hallswitch5 Hall Switch 5 Click Driver
 * @brief API for configuring and manipulating Hall Switch 5 Click driver.
 * @{
 */

/**
 * @defgroup hallswitch5_set Hall Switch 5 Settings
 * @brief Settings of Hall Switch 5 Click driver.
 */

/**
 * @addtogroup hallswitch5_set
 * @{
 */

/**
 * @brief Hall Switch 5 direction setting.
 * @details Specified setting for direction of Hall Switch 5 Click driver.
 */
#define HALLSWITCH5_DIR_CW          0
#define HALLSWITCH5_DIR_CCW         1

/**
 * @brief Hall Switch 5 pin logic state setting.
 * @details Specified setting for pin logic state of Hall Switch 5 Click driver.
 */
#define HALLSWITCH5_PIN_LOW         0
#define HALLSWITCH5_PIN_HIGH        1
#define HALLSWITCH5_PIN_MASK        1

/*! @} */ // hallswitch5_set

/**
 * @defgroup hallswitch5_map Hall Switch 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Switch 5 Click driver.
 */

/**
 * @addtogroup hallswitch5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Switch 5 Click to the selected MikroBUS.
 */
#define HALLSWITCH5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.speed = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hallswitch5_map
/*! @} */ // hallswitch5

/**
 * @brief Hall Switch 5 Click context object.
 * @details Context object definition of Hall Switch 5 Click driver.
 */
typedef struct
{
    digital_in_t speed;     /**< Speed pin. */
    digital_in_t dir;       /**< Direction pin. */

} hallswitch5_t;

/**
 * @brief Hall Switch 5 Click configuration object.
 * @details Configuration object definition of Hall Switch 5 Click driver.
 */
typedef struct
{
    pin_name_t speed;       /**< Speed pin. */
    pin_name_t dir;         /**< Direction pin. */

} hallswitch5_cfg_t;

/**
 * @brief Hall Switch 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLSWITCH5_OK = 0,
    HALLSWITCH5_ERROR = -1

} hallswitch5_return_value_t;

/*!
 * @addtogroup hallswitch5 Hall Switch 5 Click Driver
 * @brief API for configuring and manipulating Hall Switch 5 Click driver.
 * @{
 */

/**
 * @brief Hall Switch 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallswitch5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallswitch5_cfg_setup ( hallswitch5_cfg_t *cfg );

/**
 * @brief Hall Switch 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hallswitch5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallswitch5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch5_init ( hallswitch5_t *ctx, hallswitch5_cfg_t *cfg );

/**
 * @brief Hall Switch 5 get speed pin function.
 * @details This function reads the state of the SPEED pin of Hall Switch 5 Click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch5_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t hallswitch5_get_speed_pin ( hallswitch5_t *ctx );

/**
 * @brief Hall Switch 5 get dir pin function.
 * @details This function reads the state of the DIR pin of Hall Switch 5 Click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch5_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t hallswitch5_get_dir_pin ( hallswitch5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HALLSWITCH5_H

/*! @} */ // hallswitch5

// ------------------------------------------------------------------------ END
