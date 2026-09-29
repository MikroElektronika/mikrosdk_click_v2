/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file radiation.h
 * @brief This file contains API for Radiation Click Driver.
 */

#ifndef RADIATION_H
#define RADIATION_H

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
 * @addtogroup radiation Radiation Click Driver
 * @brief API for configuring and manipulating Radiation Click driver.
 * @{
 */

/**
 * @defgroup radiation_set Radiation Settings
 * @brief Settings of Radiation Click driver.
 */

/**
 * @addtogroup radiation_set
 * @{
 */

/**
 * @brief Radiation pin logic state setting.
 * @details Specified setting for pin logic state of Radiation Click driver.
 */
#define RADIATION_PIN_STATE_LOW             0
#define RADIATION_PIN_STATE_HIGH            1

/**
 * @brief Radiation pulse counting setting.
 * @details Specified setting for pulse counting of Radiation Click driver.
 */
#define RADIATION_POLLS_PER_MS              45
#define RADIATION_ONE_MINUTE_MS             60000

/**
 * @brief Radiation dose rate calculation setting.
 * @details Specified setting for dose rate calculation of Radiation Click driver.
 */
#define RADIATION_CPM_PER_USV_H             5.0f

/*! @} */ // radiation_set

/**
 * @defgroup radiation_map Radiation MikroBUS Map
 * @brief MikroBUS pin mapping of Radiation Click driver.
 */

/**
 * @addtogroup radiation_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Radiation Click to the selected MikroBUS.
 */
#define RADIATION_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // radiation_map
/*! @} */ // radiation

/**
 * @brief Radiation Click context object.
 * @details Context object definition of Radiation Click driver.
 */
typedef struct
{
    digital_in_t int_pin;       /**< Radiation pulse output pin (active high). */

} radiation_t;

/**
 * @brief Radiation Click configuration object.
 * @details Configuration object definition of Radiation Click driver.
 */
typedef struct
{
    pin_name_t int_pin;         /**< Radiation pulse output pin descriptor. */

} radiation_cfg_t;

/**
 * @brief Radiation Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RADIATION_OK = 0,
    RADIATION_ERROR = -1

} radiation_return_value_t;

/*!
 * @addtogroup radiation Radiation Click Driver
 * @brief API for configuring and manipulating Radiation Click driver.
 * @{
 */

/**
 * @brief Radiation configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #radiation_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void radiation_cfg_setup ( radiation_cfg_t *cfg );

/**
 * @brief Radiation initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[in] ctx : Click context object.
 * See #radiation_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #radiation_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t radiation_init ( radiation_t *ctx, radiation_cfg_t *cfg );

/**
 * @brief Radiation INT pin read function.
 * @details This function reads the logic state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #radiation_t object definition for detailed explanation.
 * @return INT pin logic state.
 * @note None.
 */
uint8_t radiation_int_pin_read ( radiation_t *ctx );

/**
 * @brief Radiation count pulses function.
 * @details This function counts the sensor output pulses during the selected measurement window.
 * @param[in] ctx : Click context object.
 * See #radiation_t object definition for detailed explanation.
 * @param[in] window_ms : Measurement window duration in milliseconds.
 * @param[out] pulse_cnt : Number of pulses detected during the measurement window.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t radiation_count_pulses ( radiation_t *ctx, uint32_t window_ms, uint32_t *pulse_cnt );

#ifdef __cplusplus
}
#endif
#endif // RADIATION_H

/*! @} */ // radiation

// ------------------------------------------------------------------------ END
