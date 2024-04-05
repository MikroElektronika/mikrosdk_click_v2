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
 * @file audioamp9.h
 * @brief This file contains API for AudioAmp 9 Click Driver.
 */

#ifndef AUDIOAMP9_H
#define AUDIOAMP9_H

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
 * @addtogroup audioamp9 AudioAmp 9 Click Driver
 * @brief API for configuring and manipulating AudioAmp 9 Click driver.
 * @{
 */

/**
 * @brief AudioAmp 9 gain level setting.
 * @details Specified setting for gain level of AudioAmp 9 Click driver.
 */
#define AUDIOAMP9_GAIN_LEVEL1           0x01
#define AUDIOAMP9_GAIN_LEVEL2           0x02
#define AUDIOAMP9_GAIN_LEVEL3           0x03
#define AUDIOAMP9_GAIN_LEVEL4           0x04

/*! @} */ // audioamp9_set

/**
 * @defgroup audioamp9_map AudioAmp 9 MikroBUS Map
 * @brief MikroBUS pin mapping of AudioAmp 9 Click driver.
 */

/**
 * @addtogroup audioamp9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AudioAmp 9 Click to the selected MikroBUS.
 */
#define AUDIOAMP9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.mut = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.shd = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.g0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.g1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // audioamp9_map
/*! @} */ // audioamp9

/**
 * @brief AudioAmp 9 Click context object.
 * @details Context object definition of AudioAmp 9 Click driver.
 */
typedef struct
{
    digital_out_t mut;     /**< Mute pin. */
    digital_out_t shd;     /**< Shutdown pin. */
    digital_out_t g0;      /**< Gain 0 pin. */
    digital_out_t g1;      /**< Gain 1 pin. */

} audioamp9_t;

/**
 * @brief AudioAmp 9 Click configuration object.
 * @details Configuration object definition of AudioAmp 9 Click driver.
 */
typedef struct
{
    pin_name_t mut;      /**< Mute pin. */
    pin_name_t shd;      /**< Shutdown pin. */
    pin_name_t g0;       /**< Gain 0 pin. */
    pin_name_t g1;       /**< Gain 1 pin. */

} audioamp9_cfg_t;

/**
 * @brief AudioAmp 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AUDIOAMP9_OK = 0,
    AUDIOAMP9_ERROR = -1

} audioamp9_return_value_t;

/*!
 * @addtogroup audioamp9 AudioAmp 9 Click Driver
 * @brief API for configuring and manipulating AudioAmp 9 Click driver.
 * @{
 */

/**
 * @brief AudioAmp 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #audioamp9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void audioamp9_cfg_setup ( audioamp9_cfg_t *cfg );

/**
 * @brief AudioAmp 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #audioamp9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #audioamp9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp9_init ( audioamp9_t *ctx, audioamp9_cfg_t *cfg );

/**
 * @brief AudioAmp 9 default configuration function.
 * @details This function executes a default configuration of AudioAmp 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #audioamp9_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void audioamp9_default_cfg ( audioamp9_t *ctx );

/**
 * @brief AudioAmp 9 shutdown on function.
 * @details This function turns on the shutdown mode of AudioAmp 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #audioamp9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void audioamp9_shutdown_on ( audioamp9_t *ctx );

/**
 * @brief AudioAmp 9 shutdown off function.
 * @details This function turns off the shutdown mode of AudioAmp 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #audioamp9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void audioamp9_shutdown_off ( audioamp9_t *ctx );

/**
 * @brief AudioAmp 9 mute on function.
 * @details This function turns on the mute mode of AudioAmp 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #audioamp9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void audioamp9_mute_on ( audioamp9_t *ctx );

/**
 * @brief AudioAmp 9 mute off function.
 * @details This function turns off the mute mode of AudioAmp 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #audioamp9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void audioamp9_mute_off ( audioamp9_t *ctx );

/**
 * @brief AudioAmp 9 set gain level 1 function.
 * @details This function turns on gain level 1 of AudioAmp 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #audioamp9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void audioamp9_set_gain1 ( audioamp9_t *ctx );

/**
 * @brief AudioAmp 9 set gain level 2 function.
 * @details This function turns on gain level 2 of AudioAmp 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #audioamp9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void audioamp9_set_gain2 ( audioamp9_t *ctx );

/**
 * @brief AudioAmp 9 set gain level 3 function.
 * @details This function turns on gain level 3 of AudioAmp 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #audioamp9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void audioamp9_set_gain3 ( audioamp9_t *ctx );

/**
 * @brief AudioAmp 9 set gain level 4 function.
 * @details This function turns on gain level 4 of AudioAmp 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #audioamp9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void audioamp9_set_gain4 ( audioamp9_t *ctx );

/**
 * @brief AudioAmp 9 set gain function.
 * @details This function sets a specific gain level of AudioAmp 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #audioamp9_t object definition for detailed explanation.
 * @param[in] gain_level : Selected gain level.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp9_set_gain_level ( audioamp9_t *ctx, uint8_t gain_level );

#ifdef __cplusplus
}
#endif
#endif // AUDIOAMP9_H

/*! @} */ // audioamp9

// ------------------------------------------------------------------------ END
