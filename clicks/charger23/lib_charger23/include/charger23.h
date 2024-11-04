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
 * @file charger23.h
 * @brief This file contains API for Charger 23 Click Driver.
 */

#ifndef CHARGER23_H
#define CHARGER23_H

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
 * @addtogroup charger23 Charger 23 Click Driver
 * @brief API for configuring and manipulating Charger 23 Click driver.
 * @{
 */

/**
 * @defgroup charger23_set Charger 23 Settings
 * @brief Settings of Charger 23 Click driver.
 */

/**
 * @addtogroup charger23_set
 * @{
 */

/**
 * @brief Charger 23 charger state setting.
 * @details Specified setting for charger state of Charger 23 Click driver.
 */
#define CHARGER23_STATE_UNKNOWN         0
#define CHARGER23_STATE_FAULT           1
#define CHARGER23_STATE_CHARGING        2
#define CHARGER23_STATE_IDLE            3
#define CHARGER23_STATE_MASK            0x03

/*! @} */ // charger23_set

/**
 * @defgroup charger23_map Charger 23 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 23 Click driver.
 */

/**
 * @addtogroup charger23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 23 Click to the selected MikroBUS.
 */
#define CHARGER23_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.status = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger23_map
/*! @} */ // charger23

/**
 * @brief Charger 23 Click context object.
 * @details Context object definition of Charger 23 Click driver.
 */
typedef struct
{
    digital_out_t en;               /**< Enable pin (Active HIGH). */

    digital_in_t status;            /**< Status pin (Active LOW). */
    digital_in_t fault;             /**< Fault pin (Active LOW). */

} charger23_t;

/**
 * @brief Charger 23 Click configuration object.
 * @details Configuration object definition of Charger 23 Click driver.
 */
typedef struct
{
    pin_name_t status;              /**< Status pin (Active LOW). */
    pin_name_t en;                  /**< Enable pin (Active HIGH). */
    pin_name_t fault;               /**< Fault pin (Active LOW). */

} charger23_cfg_t;

/**
 * @brief Charger 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER23_OK = 0,
    CHARGER23_ERROR = -1

} charger23_return_value_t;

/*!
 * @addtogroup charger23 Charger 23 Click Driver
 * @brief API for configuring and manipulating Charger 23 Click driver.
 * @{
 */

/**
 * @brief Charger 23 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger23_cfg_setup ( charger23_cfg_t *cfg );

/**
 * @brief Charger 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #charger23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger23_init ( charger23_t *ctx, charger23_cfg_t *cfg );

/**
 * @brief Charger 23 enable device function.
 * @details This function enables the device by setting the EN pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #charger23_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void charger23_enable_device ( charger23_t *ctx );

/**
 * @brief Charger 23 disable device function.
 * @details This function disables the device by setting the EN pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #charger23_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void charger23_disable_device ( charger23_t *ctx );

/**
 * @brief Charger 23 get status pin function.
 * @details This function returns the STATUS pin logic state. The STATUS pin is pulled LOW
 * when the charger is charging a battery.
 * @param[in] ctx : Click context object.
 * See #charger23_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t charger23_get_status_pin ( charger23_t *ctx );

/**
 * @brief Charger 23 get fault pin function.
 * @details This function returns the FAULT pin logic state. The FAULT pin is pulled LOW
 * under any fault conditions.
 * @param[in] ctx : Click context object.
 * See #charger23_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t charger23_get_fault_pin ( charger23_t *ctx );

/**
 * @brief Charger 23 get charger state function.
 * @details This function returns the charger state.
 * @param[in] ctx : Click context object.
 * See #charger23_t object definition for detailed explanation.
 * @return @li @c 0 - Unknown state,
 *         @li @c 1 - Fault,
 *         @li @c 2 - Charging in one of the three modes,
 *         @li @c 3 - Charge completed with no fault (Inhibit) or Standby.
 * @note None.
 */
uint8_t charger23_get_charger_state ( charger23_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CHARGER23_H

/*! @} */ // charger23

// ------------------------------------------------------------------------ END
