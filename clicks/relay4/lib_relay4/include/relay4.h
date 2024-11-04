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
 * @file relay4.h
 * @brief This file contains API for Relay 4 Click Driver.
 */

#ifndef RELAY4_H
#define RELAY4_H

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
 * @addtogroup relay4 Relay 4 Click Driver
 * @brief API for configuring and manipulating Relay 4 Click driver.
 * @{
 */

/**
 * @defgroup relay4_map Relay 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Relay 4 Click driver.
 */

/**
 * @addtogroup relay4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Relay 4 Click to the selected MikroBUS.
 */
#define RELAY4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rl1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rl2 = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // relay4_map
/*! @} */ // relay4

/**
 * @brief Relay 4 Click context object.
 * @details Context object definition of Relay 4 Click driver.
 */
typedef struct
{
    digital_out_t rl1;      /**< Relay 1 control pin. */
    digital_out_t rl2;      /**< Relay 2 control pin. */

} relay4_t;

/**
 * @brief Relay 4 Click configuration object.
 * @details Configuration object definition of Relay 4 Click driver.
 */
typedef struct
{
    pin_name_t rl1;         /**< Relay 1 control pin. */
    pin_name_t rl2;         /**< Relay 2 control pin. */

} relay4_cfg_t;

/**
 * @brief Relay 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RELAY4_OK = 0,
    RELAY4_ERROR = -1

} relay4_return_value_t;

/*!
 * @addtogroup relay4 Relay 4 Click Driver
 * @brief API for configuring and manipulating Relay 4 Click driver.
 * @{
 */

/**
 * @brief Relay 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #relay4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void relay4_cfg_setup ( relay4_cfg_t *cfg );

/**
 * @brief Relay 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #relay4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #relay4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay4_init ( relay4_t *ctx, relay4_cfg_t *cfg );

/**
 * @brief Relay 4 set relay1 open function.
 * @details This function sets the relay 1 to normally open state by setting the RL1 pin to low logic level.
 * @param[in] ctx : Click context object.
 * See #relay4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void relay4_set_relay1_open ( relay4_t *ctx );

/**
 * @brief Relay 4 set relay1 close function.
 * @details This function sets the relay 1 to normally close state by setting the RL1 pin to high logic level.
 * @param[in] ctx : Click context object.
 * See #relay4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void relay4_set_relay1_close ( relay4_t *ctx );

/**
 * @brief Relay 4 switch relay1 function.
 * @details This function switches the relay 1 state by toggling the RL1 pin logic level.
 * @param[in] ctx : Click context object.
 * See #relay4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void relay4_switch_relay1 ( relay4_t *ctx );

/**
 * @brief Relay 4 set relay2 open function.
 * @details This function sets the relay 2 to normally open state by setting the RL2 pin to low logic level.
 * @param[in] ctx : Click context object.
 * See #relay4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void relay4_set_relay2_open ( relay4_t *ctx );

/**
 * @brief Relay 4 set relay2 close function.
 * @details This function sets the relay 2 to normally close state by setting the RL2 pin to high logic level.
 * @param[in] ctx : Click context object.
 * See #relay4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void relay4_set_relay2_close ( relay4_t *ctx );

/**
 * @brief Relay 4 switch relay2 function.
 * @details This function switches the relay 2 state by toggling the RL2 pin logic level.
 * @param[in] ctx : Click context object.
 * See #relay4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void relay4_switch_relay2 ( relay4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RELAY4_H

/*! @} */ // relay4

// ------------------------------------------------------------------------ END
