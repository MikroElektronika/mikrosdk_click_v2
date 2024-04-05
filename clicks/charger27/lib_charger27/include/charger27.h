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
 * @file charger27.h
 * @brief This file contains API for Charger 27 Click Driver.
 */

#ifndef CHARGER27_H
#define CHARGER27_H

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
 * @addtogroup charger27 Charger 27 Click Driver
 * @brief API for configuring and manipulating Charger 27 Click driver.
 * @{
 */

/**
 * @addtogroup charger27_set
 * @{
 */

/**
 * @brief Charger 27 charge or discharge mode selection.
 * @details Charge or discharge mode selection of Charger 27 Click driver.
 */
#define CHARGER27_MODE_CHARGE         0
#define CHARGER27_MODE_DISCHARGE      1

/**
 * @brief Charger 27 valid input supply indicator.
 * @details Valid input supply indicator of Charger 27 Click driver.
 */
#define CHARGER27_AOK_ERROR           0
#define CHARGER27_AOK_GOOD_SOURCE     1

/**
 * @brief Charger 27 charging completion indicator.
 * @details Charging completion indicator of Charger 27 Click driver.
 */
#define CHARGER27_CHG_CHARGE          0
#define CHARGER27_CHG_COMPL_OR_SUS    1

/*! @} */ // charger27_set

/**
 * @defgroup charger27_map Charger 27 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 27 Click driver.
 */

/**
 * @addtogroup charger27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 27 Click to the selected MikroBUS.
 */
#define CHARGER27_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.aok = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.md  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.chg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger27_map
/*! @} */ // charger27

/**
 * @brief Charger 27 Click context object.
 * @details Context object definition of Charger 27 Click driver.
 */
typedef struct
{
    digital_out_t md;     /**< Charge or discharge mode selection. */

    digital_in_t aok;     /**< Valid input supply indicator. */
    digital_in_t chg;     /**< Charging completion indicator. */

} charger27_t;

/**
 * @brief Charger 27 Click configuration object.
 * @details Configuration object definition of Charger 27 Click driver.
 */
typedef struct
{
    pin_name_t aok;    /**< Valid input supply indicator. */
    pin_name_t md;     /**< Charge or discharge mode selection. */
    pin_name_t chg;    /**< Charging completion indicator. */

} charger27_cfg_t;

/**
 * @brief Charger 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER27_OK = 0,
    CHARGER27_ERROR = -1

} charger27_return_value_t;

/*!
 * @addtogroup charger27 Charger 27 Click Driver
 * @brief API for configuring and manipulating Charger 27 Click driver.
 * @{
 */

/**
 * @brief Charger 27 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger27_cfg_setup ( charger27_cfg_t *cfg );

/**
 * @brief Charger 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #charger27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger27_init ( charger27_t *ctx, charger27_cfg_t *cfg );

/**
 * @brief Charger 27 checks valid input supply indicator function.
 * @details This function checks valid input supply indicator state
 * of the MP2639B, 1S Cell Li-ion or Li-polymer Switching Charger 
 * Compatible with Wide Input Range and Integrated Programmable OTG 
 * on the Charger 27 click board.
 * @param[in] ctx : Click context object.
 * See #charger27_t object definition for detailed explanation.
 * @return Valid input supply indicator state:
 *         @li @c 0 - The input voltage error,
 *         @li @c 1 - The input voltage is recognized as a good source.
 * @note None.
 */
uint8_t charger27_check_input_supply ( charger27_t *ctx );

/**
 * @brief Charger 27 sets the operating mode function.
 * @details This function is used for the charge or discharge mode selection
 * of the MP2639B, 1S Cell Li-ion or Li-polymer Switching Charger 
 * Compatible with Wide Input Range and Integrated Programmable OTG 
 * on the Charger 27 click board.
 * @param[in] ctx : Click context object.
 * See #charger27_t object definition for detailed explanation.
 * @param[in] mode : Charge or discharge mode selection [0-1].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger27_set_mode ( charger27_t *ctx, uint8_t mode );

/**
 * @brief Charger 27 checks charging completion indicator function.
 * @details This function checks the charging completion indicator state
 * of the MP2639B, 1S Cell Li-ion or Li-polymer Switching Charger 
 * Compatible with Wide Input Range and Integrated Programmable OTG 
 * on the Charger 27 click board.
 * @param[in] ctx : Click context object.
 * See #charger27_t object definition for detailed explanation.
 * @return Valid input supply indicator state:
 *         @li @c 0 - Charge mode,
 *         @li @c 1 - Charging has completed or is suspended.
 * @note None.
 */
uint8_t charger27_check_chg_completion ( charger27_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CHARGER27_H

/*! @} */ // charger27

// ------------------------------------------------------------------------ END
