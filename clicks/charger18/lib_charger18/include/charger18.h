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
 * @file charger18.h
 * @brief This file contains API for Charger 18 Click Driver.
 */

#ifndef CHARGER18_H
#define CHARGER18_H

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
 * @addtogroup charger18 Charger 18 Click Driver
 * @brief API for configuring and manipulating Charger 18 Click driver.
 * @{
 */

/**
 * @defgroup charger18_set Charger 18 Settings
 * @brief Settings for Charger 18 Click driver.
 */

/**
 * @addtogroup charger18_set
 * @{
 */

/**
 * @brief Charger 18 control state values.
 * @details Specified control state values of Charger 18 Click driver.
 */
#define CHARGER18_CONTROL_DISABLE           0
#define CHARGER18_CONTROL_ENABLE            1

/*! @} */ // charger18_set

/**
 * @defgroup charger18_map Charger 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 18 Click driver.
 */

/**
 * @addtogroup charger18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 18 Click to the selected MikroBUS.
 */
#define CHARGER18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.bon = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ien = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ldo = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.sta = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger18_map
/*! @} */ // charger18

/**
 * @brief Charger 18 Click context object.
 * @details Context object definition of Charger 18 Click driver.
 */
typedef struct
{
    digital_out_t bon;          /**< Buck ON pin. */
    digital_out_t on;           /**< ON pin. */
    digital_out_t ien;          /**< Suspend mode pin. */
    digital_out_t ldo;          /**< LDO on pin. */

    digital_in_t  sta;          /**< ON status pin. */

} charger18_t;

/**
 * @brief Charger 18 Click configuration object.
 * @details Configuration object definition of Charger 18 Click driver.
 */
typedef struct
{
    pin_name_t  bon;            /**< Buck ON pin. */
    pin_name_t  on;             /**< ON pin. */
    pin_name_t  ien;            /**< Suspend mode pin. */
    pin_name_t  ldo;            /**< LDO ON pin. */
    pin_name_t  sta;            /**< ON status pin. */

} charger18_cfg_t;

/**
 * @brief Charger 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER18_OK = 0,
    CHARGER18_ERROR = -1

} charger18_return_value_t;

/*!
 * @addtogroup charger18 Charger 18 Click Driver
 * @brief API for configuring and manipulating Charger 18 Click driver.
 * @{
 */

/**
 * @brief Charger 18 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger18_cfg_setup ( charger18_cfg_t *cfg );

/**
 * @brief Charger 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #charger18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger18_init ( charger18_t *ctx, charger18_cfg_t *cfg );

/**
 * @brief Charger 18 buck control function.
 * @details This function controls the buck regulator enable state of
 * Charger 18 Click board.
 * @param[in] ctx : Click context object.
 * See #charger18_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Disable,
 *                    @li @c 1 - Enable.
 * @return None.
 * @note The buck regulator is specified to 1.2V 200mA.
 */
void charger18_buck_control ( charger18_t *ctx, uint8_t state ); 

/**
 * @brief Charger 18 ldo control function.
 * @details This function controls the low dropout (LDO) regulator enable state of
 * Charger 18 Click board.
 * @param[in] ctx : Click context object.
 * See #charger18_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Disable,
 *                    @li @c 1 - Enable.
 * @return None.
 * @note The LDO regulator is specified to 3.3V 150mA.
 */
void charger18_ldo_control ( charger18_t *ctx, uint8_t state );

/**
 * @brief Charger 18 suspend control function.
 * @details This function controls the suspend charging mode state of
 * Charger 18 Click board.
 * @param[in] ctx : Click context object.
 * See #charger18_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Disable,
 *                    @li @c 1 - Enable.
 * @return None.
 * @note None.
 */
void charger18_suspend_control ( charger18_t *ctx, uint8_t state ); 

/**
 * @brief Charger 18 power control function.
 * @details This function controls the chip power state of
 * Charger 18 Click board.
 * @param[in] ctx : Click context object.
 * See #charger18_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Disable,
 *                    @li @c 1 - Enable.
 * @return None.
 * @note None.
 */
void charger18_power_control ( charger18_t *ctx, uint8_t state );

/**
 * @brief Charger 18 get STA pin function.
 * @details This function returns the pushbutton status (STA) pin logic state.
 * @param[in] ctx : Click context object.
 * See #charger18_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t charger18_get_sta_pin ( charger18_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CHARGER18_H

/*! @} */ // charger18

// ------------------------------------------------------------------------ END
