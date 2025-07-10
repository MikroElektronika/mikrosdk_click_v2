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
 * @file charger24.h
 * @brief This file contains API for Charger 24 Click Driver.
 */

#ifndef CHARGER24_H
#define CHARGER24_H

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
 * @addtogroup charger24 Charger 24 Click Driver
 * @brief API for configuring and manipulating Charger 24 Click driver.
 * @{
 */

/**
 * @defgroup charger24_set Charger 24 Settings
 * @brief Settings of Charger 24 Click driver.
 */

/**
 * @addtogroup charger24_set
 * @{
 */

/**
 * @brief Charger 24 charging state setting.
 * @details Specified setting for charging state of Charger 24 Click driver.
 */
#define CHARGER24_STATE_NO_INPUT        0
#define CHARGER24_STATE_CHARGING        1
#define CHARGER24_STATE_CHARGE_DONE     2

/*! @} */ // charger24_set

/**
 * @defgroup charger24_map Charger 24 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 24 Click driver.
 */

/**
 * @addtogroup charger24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 24 Click to the selected MikroBUS.
 */
#define CHARGER24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.iok = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.dsb = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dis = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.stat = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger24_map
/*! @} */ // charger24

/**
 * @brief Charger 24 Click context object.
 * @details Context object definition of Charger 24 Click driver.
 */
typedef struct
{
    digital_out_t dsb;          /**< Disable reverse boost converted (active high). */
    digital_out_t dis;          /**< Disable charging (active high). */

    digital_in_t iok;           /**< Charger input valid pin (active low). */
    digital_in_t stat;          /**< Status indication pin (active low). */

} charger24_t;

/**
 * @brief Charger 24 Click configuration object.
 * @details Configuration object definition of Charger 24 Click driver.
 */
typedef struct
{
    pin_name_t iok;             /**< Charger input valid pin (active low). */
    pin_name_t dsb;             /**< Disable reverse boost converted (active high). */
    pin_name_t dis;             /**< Disable charging (active high). */
    pin_name_t stat;            /**< Status indication pin (active low). */

} charger24_cfg_t;

/**
 * @brief Charger 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER24_OK = 0,
    CHARGER24_ERROR = -1

} charger24_return_value_t;

/*!
 * @addtogroup charger24 Charger 24 Click Driver
 * @brief API for configuring and manipulating Charger 24 Click driver.
 * @{
 */

/**
 * @brief Charger 24 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger24_cfg_setup ( charger24_cfg_t *cfg );

/**
 * @brief Charger 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #charger24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger24_init ( charger24_t *ctx, charger24_cfg_t *cfg );

/**
 * @brief Charger 24 enable boost function.
 * @details This function enables the reverse boost converter on the Charger 24 Click board.
 * @param[in] ctx : Click context object.
 * See #charger24_t object definition for detailed explanation.
 * @note None.
 */
void charger24_enable_boost ( charger24_t *ctx );

/**
 * @brief Charger 24 disable boost function.
 * @details This function disables the reverse boost converter on the Charger 24 Click board.
 * @param[in] ctx : Click context object.
 * See #charger24_t object definition for detailed explanation.
 * @note None.
 */
void charger24_disable_boost ( charger24_t *ctx );

/**
 * @brief Charger 24 enable charging function.
 * @details This function enables battery charging on the Charger 24 Click board.
 * @param[in] ctx : Click context object.
 * See #charger24_t object definition for detailed explanation.
 * @note None.
 */
void charger24_enable_charging ( charger24_t *ctx );

/**
 * @brief Charger 24 disable charging function.
 * @details This function disables battery charging on the Charger 24 Click board.
 * @param[in] ctx : Click context object.
 * See #charger24_t object definition for detailed explanation.
 * @note None.
 */
void charger24_disable_charging ( charger24_t *ctx );

/**
 * @brief Charger 24 get STAT pin function.
 * @details This function returns the logic state of the STAT pin.
 * @param[in] ctx : Click context object.
 * See #charger24_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t charger24_get_stat_pin ( charger24_t *ctx );

/**
 * @brief Charger 24 get IOK pin function.
 * @details This function returns the logic state of the IOK pin.
 * @param[in] ctx : Click context object.
 * See #charger24_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t charger24_get_iok_pin ( charger24_t *ctx );

/**
 * @brief Charger 24 get status function.
 * @details This function checks the battery charging status by polling the STAT pin.
 * @param[in] ctx : Click context object.
 * See #charger24_t object definition for detailed explanation.
 * @return @li @c CHARGER24_STATE_NO_INPUT    - No input power,
 *         @li @c CHARGER24_STATE_CHARGE_DONE - Charging complete,
 *         @li @c CHARGER24_STATE_CHARGING    - Charging in progress.
 * @note None.
 */
uint8_t charger24_get_status ( charger24_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CHARGER24_H

/*! @} */ // charger24

// ------------------------------------------------------------------------ END
