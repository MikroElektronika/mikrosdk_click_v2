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
 * @file charger26.h
 * @brief This file contains API for Charger 26 Click Driver.
 */

#ifndef CHARGER26_H
#define CHARGER26_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/*!
 * @addtogroup charger26 Charger 26 Click Driver
 * @brief API for configuring and manipulating Charger 26 Click driver.
 * @{
 */

/**
 * @addtogroup charger26_set
 * @{
 */

/**
 * @brief Charger 26 description setting.
 * @details Specified setting for description of Charger 26 Click driver.
 */
#define CHARGER26_PIN_STATE_HIGH                0x01
#define CHARGER26_PIN_STATE_LOW                 0x00

/**
 * @brief Charger 26 vout selection setting.
 * @details Specified setting for vout voltage of Charger 26 Click driver.
 */
#define CHARGER26_SELV_4V1_REG_POINT            0x00
#define CHARGER26_SELV_4V2_REG_POINT            0x01

/**
 * @brief Charger 26 iout selection setting.
 * @details Specified setting for iout current of Charger 26 Click driver.
 */
#define CHARGER26_SELI_100_MA_MAX_REG           0x00
#define CHARGER26_SELI_500_MA_MAX_REG           0x01

/**
 * @brief Charger 26 output enable setting.
 * @details Specified setting for output enabling  of Charger 26 Click driver.
 */
#define CHARGER26_ENABLE_OUTPUT                 0x01
#define CHARGER26_DISABLE_OUTPUT                0x00


/*! @} */ // charger26_set

/**
 * @defgroup charger26_map Charger 26 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 26 Click driver.
 */

/**
 * @addtogroup charger26_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 26 Click to the selected MikroBUS.
 */
#define CHARGER26_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.vsel = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.isel = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.chg  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger26_map
/*! @} */ // charger26

/**
 * @brief Charger 26 Click context object.
 * @details Context object definition of Charger 26 Click driver.
 */
typedef struct
{
    digital_out_t vsel;     /**< Voltage output selection pin. */
    digital_out_t en;       /**< Device enable pin. */
    digital_out_t isel;     /**< Current output selection pin. */

    digital_in_t chg;       /**< Charging indicator pin. */

} charger26_t;

/**
 * @brief Charger 26 Click configuration object.
 * @details Configuration object definition of Charger 26 Click driver.
 */
typedef struct
{
    pin_name_t vsel;        /**< Voltage output selection pin. */
    pin_name_t en;          /**< Device enable pin. */
    pin_name_t isel;        /**< Current output selection pin. */
    pin_name_t chg;         /**< Charging indicator pin. */

} charger26_cfg_t;

/**
 * @brief Charger 26 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER26_OK = 0,
    CHARGER26_ERROR = -1

} charger26_return_value_t;

/*!
 * @addtogroup charger26 Charger 26 Click Driver
 * @brief API for configuring and manipulating Charger 26 Click driver.
 * @{
 */

/**
 * @brief Charger 26 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger26_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger26_cfg_setup ( charger26_cfg_t *cfg );

/**
 * @brief Charger 26 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #charger26_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger26_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger26_init ( charger26_t *ctx, charger26_cfg_t *cfg );

/**
 * @brief Charger 26 default configuration function.
 * @details This function executes a default configuration of Charger 26
 * click board.
 * @param[in] ctx : Click context object.
 * See #charger26_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void charger26_default_cfg ( charger26_t *ctx );

/**
 * @brief Charger 26 select charger voltage function.
 * @details This function is used to set charging voltage of Charger 26
 * click board.
 * @param[in] ctx : Click context object.
 * See #charger26_t object definition for detailed explanation.
 * @param[in] iout_sel : Charging current selection.
 * @return Nothing.
 * @note None.
 */
void charger26_set_vsel ( charger26_t *ctx, uint8_t vout_sel );

/**
 * @brief Charger 26 select charger current function.
 * @details This function is used to set charging current of Charger 26
 * click board.
 * @param[in] ctx : Click context object.
 * See #charger26_t object definition for detailed explanation.
 * @param[in] iout_sel : Charging current selection.
 * @return Nothing.
 * @note None.
 */
void charger26_set_isel ( charger26_t *ctx, uint8_t iout_sel );

/**
 * @brief Charger 26 enable charger output function.
 * @details This function is used to set output of Charger 26
 * click board.
 * @param[in] ctx : Click context object.
 * See #charger26_t object definition for detailed explanation.
 * @param[in] output_state : Output state.
 * @return Nothing.
 * @note None.
 */
void charger26_enable_output ( charger26_t *ctx, uint8_t output_state );

/**
 * @brief Charger 26 chg pin reading function.
 * @details This function reads the state of the chg pin of Charger 26
 * click board.
 * @param[in] ctx : Click context object.
 * See #charger26_t object definition for detailed explanation.
 * @return @li @c 0 - Battery is charging,
 *         @li @c 1 - Battery isn't charging.
 * @note None.
 */
uint8_t charger26_get_chg_state ( charger26_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CHARGER26_H

/*! @} */ // charger26

// ------------------------------------------------------------------------ END
