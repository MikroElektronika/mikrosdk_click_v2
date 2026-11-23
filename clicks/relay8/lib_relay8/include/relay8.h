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
 * @file relay8.h
 * @brief This file contains API for Relay 8 Click Driver.
 */

#ifndef RELAY8_H
#define RELAY8_H

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
 * @addtogroup relay8 Relay 8 Click Driver
 * @brief API for configuring and manipulating Relay 8 Click driver.
 * @{
 */

/**
 * @defgroup relay8_map Relay 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Relay 8 Click driver.
 */

/**
 * @addtogroup relay8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Relay 8 Click to the selected MikroBUS.
 */
#define RELAY8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.set = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.tgl = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // relay8_map
/*! @} */ // relay8

/**
 * @brief Relay 8 Click context object.
 * @details Context object definition of Relay 8 Click driver.
 */
typedef struct
{
    digital_out_t rst;      /**< Reset pin. */
    digital_out_t set;      /**< Set pin. */
    digital_out_t tgl;      /**< Toggle pin. */

} relay8_t;

/**
 * @brief Relay 8 Click configuration object.
 * @details Configuration object definition of Relay 8 Click driver.
 */
typedef struct
{
    pin_name_t rst;         /**< Reset pin descriptor. */
    pin_name_t set;         /**< Set pin descriptor. */
    pin_name_t tgl;         /**< Toggle pin descriptor. */

} relay8_cfg_t;

/**
 * @brief Relay 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RELAY8_OK = 0,
    RELAY8_ERROR = -1

} relay8_return_value_t;

/*!
 * @addtogroup relay8 Relay 8 Click Driver
 * @brief API for configuring and manipulating Relay 8 Click driver.
 * @{
 */

/**
 * @brief Relay 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #relay8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void relay8_cfg_setup ( relay8_cfg_t *cfg );

/**
 * @brief Relay 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #relay8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #relay8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay8_init ( relay8_t *ctx, relay8_cfg_t *cfg );

/**
 * @brief Relay 8 set relay function.
 * @details This function turns the relay on by generating an active high pulse
 * on the SET pin.
 * @param[in] ctx : Click context object.
 * See #relay8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void relay8_set_relay ( relay8_t *ctx );

/**
 * @brief Relay 8 reset relay function.
 * @details This function turns the relay off by generating an active low pulse
 * on the RST pin.
 * @param[in] ctx : Click context object.
 * See #relay8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void relay8_reset_relay ( relay8_t *ctx );

/**
 * @brief Relay 8 toggle relay function.
 * @details This function turns the relay on and off by generating
 * an active high pulse on the TGL pin.
 * @param[in] ctx : Click context object.
 * See #relay8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void relay8_toggle_relay ( relay8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RELAY8_H

/*! @} */ // relay8

// ------------------------------------------------------------------------ END
