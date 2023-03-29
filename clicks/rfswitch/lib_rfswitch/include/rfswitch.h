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
 * @file rfswitch.h
 * @brief This file contains API for RF Switch Click Driver.
 */

#ifndef RFSWITCH_H
#define RFSWITCH_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/*!
 * @addtogroup rfswitch RF Switch Click Driver
 * @brief API for configuring and manipulating RF Switch Click driver.
 * @{
 */

/**
 * @defgroup rfswitch_set RF Switch Registers Settings
 * @brief Settings for registers of RF Switch Click driver.
 */

/**
 * @addtogroup rfswitch_set
 * @{
 */

/**
 * @brief RF Switch description setting.
 * @details Specified setting for description of RF Switch Click driver.
 */
#define RFSWITCH_ON_PIN_STATE_HIGH                              0x01
#define RFSWITCH_ON_PIN_STATE_LOW                               0x00
#define RFSWITCH_SEL_PIN_STATE_HIGH                             0x01
#define RFSWITCH_SEL_PIN_STATE_LOW                              0x00
#define RFSWITCH_SELECT_CHANNEL_1                               0x01
#define RFSWITCH_SELECT_CHANNEL_2                               0x02

/*! @} */ // rfswitch_set

/**
 * @defgroup rfswitch_map RF Switch MikroBUS Map
 * @brief MikroBUS pin mapping of RF Switch Click driver.
 */

/**
 * @addtogroup rfswitch_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RF Switch Click to the selected MikroBUS.
 */
#define RFSWITCH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sel = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // rfswitch_map
/*! @} */ // rfswitch

/**
 * @brief RF Switch Click context object.
 * @details Context object definition of RF Switch Click driver.
 */
typedef struct
{
    digital_out_t  on;      /**< Power On. */
    digital_out_t  sel;     /**< Port Select. */

} rfswitch_t;

/**
 * @brief RF Switch Click configuration object.
 * @details Configuration object definition of RF Switch Click driver.
 */
typedef struct
{
    pin_name_t  on;         /**< Power On. */
    pin_name_t  sel;        /**< Port Select. */

} rfswitch_cfg_t;

/**
 * @brief RF Switch Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RFSWITCH_OK = 0,
    RFSWITCH_ERROR = -1

} rfswitch_return_value_t;

/*!
 * @addtogroup rfswitch RF Switch Click Driver
 * @brief API for configuring and manipulating RF Switch Click driver.
 * @{
 */

/**
 * @brief RF Switch configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rfswitch_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rfswitch_cfg_setup ( rfswitch_cfg_t *cfg );

/**
 * @brief RF Switch initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rfswitch_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rfswitch_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfswitch_init ( rfswitch_t *ctx, rfswitch_cfg_t *cfg );

/**
 * @brief RF Switch power on function.
 * @details This function is used to power up RF Switch click board.
 * @param[in] ctx : Click context object.
 * See #rfswitch_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rfswitch_power_on ( rfswitch_t *ctx );

/**
 * @brief RF Switch ON pin setting function.
 * @details This function sets the ON pin on the high level or low level
 * of RF Switch click board.
 * @param[in] ctx : Click context object.
 * See #rfswitch_t object definition for detailed explanation.
 * @param[in] enable : State of the ON pin.
 * @return Nothing.
 * @note None.
 */
void rfswitch_on_pin_set ( rfswitch_t *ctx, uint8_t enable );

/**
 * @brief RF Switch SEL pin setting function.
 * @details This function sets the SEL pin on the high level or low level
 * of RF Switch click board.
 * @param[in] ctx : Click context object.
 * See #rfswitch_t object definition for detailed explanation.
 * @param[in] enable : State of the SEL pin.
 * @return Nothing.
 * @note None.
 */
void rfswitch_sel_pin_set ( rfswitch_t *ctx, uint8_t enable );

/**
 * @brief RF Switch switch channel function.
 * @details This function toggles the SEL pin from high to low levels of
 * RF Switch click board, and vice versa, therefore changing the channel.
 * @param[in] ctx : Click context object.
 * See #rfswitch_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rfswitch_switch_channel ( rfswitch_t *ctx );

/**
 * @brief RF Switch select channel function.
 * @details This function enables users to select from channel 1 or channel 2 of the 
 * RF Switch click board.
 * @param[in] ctx : Click context object.
 * See #rfswitch_t object definition for detailed explanation.
 * @param[in] select_channel : Selected channel.
 * @return Nothing.
 * @note None.
 */
void rfswitch_select_channel ( rfswitch_t *ctx, uint8_t select_channel );

#ifdef __cplusplus
}
#endif
#endif // RFSWITCH_H

/*! @} */ // rfswitch

// ------------------------------------------------------------------------ END
