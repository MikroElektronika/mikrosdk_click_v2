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
 * @file recnplay2.h
 * @brief This file contains API for Rec N Play 2 Click Driver.
 */

#ifndef RECNPLAY2_H
#define RECNPLAY2_H

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
 * @addtogroup recnplay2 Rec N Play 2 Click Driver
 * @brief API for configuring and manipulating Rec N Play 2 Click driver.
 * @{
 */

/**
 * @addtogroup recnplay2_set
 * @{
 */

/**
 * @brief Rec N Play 2 description setting.
 * @details Specified setting for description of Rec N Play 2 Click driver.
 */
#define RECNPLAY2_DURATION_24S              24000

/**
 * @brief Rec N Play 2 Pin state setting.
 * @details Specified Pin state for description of Rec N Play 2 Click driver.
 */
#define RECNPLAY2_PIN_STATE_LOW             0x00
#define RECNPLAY2_PIN_STATE_HIGH            0x01

/*! @} */ // recnplay2_set

/**
 * @defgroup recnplay2_map Rec N Play 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Rec N Play 2 Click driver.
 */

/**
 * @addtogroup recnplay2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Rec N Play 2 Click to the selected MikroBUS.
 */
#define RECNPLAY2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rec = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pe = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pl = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // recnplay2_map
/*! @} */ // recnplay2

/**
 * @brief Rec N Play 2 Click context object.
 * @details Context object definition of Rec N Play 2 Click driver.
 */
typedef struct
{
    digital_out_t rec;      /**< Record pin. */
    digital_out_t pe;       /**< Edge-trigger playback pin. */
    digital_out_t pl;       /**< Level-trigger playback pin. */
} recnplay2_t;

/**
 * @brief Rec N Play 2 Click configuration object.
 * @details Configuration object definition of Rec N Play 2 Click driver.
 */
typedef struct
{
    pin_name_t rec;     /**< Record pin. */
    pin_name_t pe;      /**< Edge-trigger playback pin. */
    pin_name_t pl;      /**< Level-trigger playback pin. */

} recnplay2_cfg_t;

/**
 * @brief Rec N Play 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RECNPLAY2_OK = 0,
    RECNPLAY2_ERROR = -1

} recnplay2_return_value_t;

/*!
 * @addtogroup recnplay2 Rec N Play 2 Click Driver
 * @brief API for configuring and manipulating Rec N Play 2 Click driver.
 * @{
 */

/**
 * @brief Rec N Play 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #recnplay2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void recnplay2_cfg_setup ( recnplay2_cfg_t *cfg );

/**
 * @brief Rec N Play 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #recnplay2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #recnplay2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t recnplay2_init ( recnplay2_t *ctx, recnplay2_cfg_t *cfg );

/**
 * @brief Rec N Play 2 default configuration function.
 * @details This function executes a default configuration of Rec N Play 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #recnplay2_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void recnplay2_default_cfg ( recnplay2_t *ctx );

/**
 * @brief Rec N Play 2 REC pin setting function.
 * @details This function sets the REC pin on the selected level of
 * Rec N Play 2 click board.
 * @param[in] ctx : Click context object.
 * See #recnplay2_t object definition for detailed explanation.
 * @param[in] pin_state : Selected pin level.
 * @return Nothing.
 * @note None.
 */
void recnplay2_set_rec_pin ( recnplay2_t *ctx, uint8_t pin_state );

/**
 * @brief Rec N Play 2 Pe pin setting function.
 * @details This function sets the PE pin on the selected level of
 * Rec N Play 2 click board.
 * @param[in] ctx : Click context object.
 * See #recnplay2_t object definition for detailed explanation.
 * @param[in] pin_state : Selected pin level.
 * @return Nothing.
 * @note None.
 */
void recnplay2_set_pe_pin ( recnplay2_t *ctx, uint8_t pin_state );

/**
 * @brief Rec N Play 2 PL pin setting function.
 * @details This function sets the PL pin on the selected level of
 * Rec N Play 2 click board.
 * @param[in] ctx : Click context object.
 * See #recnplay2_t object definition for detailed explanation.
 * @param[in] pin_state : Selected pin level.
 * @return Nothing.
 * @note None.
 */
void recnplay2_set_pl_pin ( recnplay2_t *ctx, uint8_t pin_state );

/**
 * @brief Rec N Play 2 record sound function.
 * @details This function is used to record sound with
 * Rec N Play 2 click board.
 * @param[in] ctx : Click context object.
 * See #recnplay2_t object definition for detailed explanation.
 * @param[in] rec_len : Recording lenght in mS.
 * @return Nothing.
 * @note None.
 */
err_t recnplay2_record_sound ( recnplay2_t *ctx, uint16_t rec_len );

/**
 * @brief Rec N Play 2 play recorded sounds function.
 * @details This function is used to play recorded sounds with
 * Rec N Play 2 click board.
 * @param[in] ctx : Click context object.
 * See #recnplay2_t object definition for detailed explanation.
 * @param[in] rec_len : Playing time in mS.
 * @return Nothing.
 * @note None.
 */
err_t recnplay2_play_sound ( recnplay2_t *ctx, uint16_t play_len );

#ifdef __cplusplus
}
#endif
#endif // RECNPLAY2_H

/*! @} */ // recnplay2

// ------------------------------------------------------------------------ END
