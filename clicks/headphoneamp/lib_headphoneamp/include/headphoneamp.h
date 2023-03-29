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
 * @file headphoneamp.h
 * @brief This file contains API for Headphone AMP Click Driver.
 */

#ifndef HEADPHONEAMP_H
#define HEADPHONEAMP_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
    


/*!
 * @addtogroup headphoneamp Headphone AMP Click Driver
 * @brief API for configuring and manipulating Headphone AMP Click driver.
 * @{
 */

/**
 * @addtogroup headphoneamp_set
 * @{
 */

/**
 * @brief Headphone AMP description volume setting.
 * @details Specified setting for description of Headphone AMP Click driver.
 */
#define HEADPHONEAMP_SOUND_VOLUME_NEG_33_dB                  0
#define HEADPHONEAMP_SOUND_VOLUME_NEG_30_dB                  1
#define HEADPHONEAMP_SOUND_VOLUME_NEG_27_dB                  2
#define HEADPHONEAMP_SOUND_VOLUME_NEG_24_dB                  3
#define HEADPHONEAMP_SOUND_VOLUME_NEG_21_dB                  4
#define HEADPHONEAMP_SOUND_VOLUME_NEG_18_dB                  5
#define HEADPHONEAMP_SOUND_VOLUME_NEG_15_dB                  6
#define HEADPHONEAMP_SOUND_VOLUME_NEG_12_dB                  7
#define HEADPHONEAMP_SOUND_VOLUME_NEG_9_dB                   8 
#define HEADPHONEAMP_SOUND_VOLUME_NEG_6_dB                   9 
#define HEADPHONEAMP_SOUND_VOLUME_NEG_3_dB                  10
#define HEADPHONEAMP_SOUND_VOLUME_NEG_0_dB                  11
#define HEADPHONEAMP_SOUND_VOLUME_POS_3_dB                  12
#define HEADPHONEAMP_SOUND_VOLUME_POS_6_dB                  13
#define HEADPHONEAMP_SOUND_VOLUME_POS_9_dB                  14
#define HEADPHONEAMP_SOUND_VOLUME_POS_12_dB                 15

/*! @} */ // headphoneamp_set

/**
 * @defgroup headphoneamp_map Headphone AMP MikroBUS Map
 * @brief MikroBUS pin mapping of Headphone AMP Click driver.
 */

/**
 * @addtogroup headphoneamp_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Headphone AMP Click to the selected MikroBUS.
 */
#define HEADPHONEAMP_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.shdn = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.ud = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // headphoneamp_map
/*! @} */ // headphoneamp

/**
 * @brief Headphone AMP Click context object.
 * @details Context object definition of Headphone AMP Click driver.
 */
typedef struct
{
    digital_out_t  shdn;    /**< Shutdown pin.       */
    digital_out_t  clk;     /**< Clock pin.          */
    digital_out_t  ud;      /**< Volume Control pin. */

} headphoneamp_t;

/**
 * @brief Headphone AMP Click configuration object.
 * @details Configuration object definition of Headphone AMP Click driver.
 */
typedef struct
{
    pin_name_t  shdn;     /**< Shutdown pin.       */
    pin_name_t  clk;      /**< Clock pin.          */
    pin_name_t  ud;       /**< Volume Control pin. */

} headphoneamp_cfg_t;

/**
 * @brief Headphone AMP Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   HEADPHONEAMP_OK = 0,
   HEADPHONEAMP_ERROR = -1

} headphoneamp_return_value_t;

/*!
 * @addtogroup headphoneamp Headphone AMP Click Driver
 * @brief API for configuring and manipulating Headphone AMP Click driver.
 * @{
 */

/**
 * @brief Headphone AMP configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #headphoneamp_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void headphoneamp_cfg_setup ( headphoneamp_cfg_t *cfg );

/**
 * @brief Headphone AMP initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #headphoneamp_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #headphoneamp_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t headphoneamp_init ( headphoneamp_t *ctx, headphoneamp_cfg_t *cfg );

/**
 * @brief Headphone AMP default configuration function.
 * @details This function executes a default configuration of Headphone AMP
 * click board.
 * @param[in] ctx : Click context object.
 * See #headphoneamp_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t headphoneamp_default_cfg ( headphoneamp_t *ctx );

/**
 * @brief Headphone AMP shutdown function.
 * @details This function set the amplifier bias circuitry shutdown 
 * of the LM4811 Dual 105mW Headphone Amplifier 
 * with Digital Volume Control and Shutdown Mode 
 * on the Headphone AMP click board™.
 * @param[in] ctx : Click context object.
 * See #headphoneamp_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t headphoneamp_shutdown ( headphoneamp_t *ctx );

/**
 * @brief Headphone AMP power up function.
 * @details This function performs power-up sequence 
 * of the LM4811 Dual 105mW Headphone Amplifier with Digital Volume Control and Shutdown Mode 
 * on the Headphone AMP click board™.
 * @param[in] ctx : Click context object.
 * See #headphoneamp_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t headphoneamp_power_up ( headphoneamp_t *ctx );

/**
 * @brief Headphone AMP set sound volume down function.
 * @details This function set sound volume down 
 * on of the LM4811 Dual 105mW Headphone Amplifier 
 * with Digital Volume Control and Shutdown Mode 
 * on the Headphone AMP click board™.
 * @param[in] ctx : Click context object.
 * See #headphoneamp_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t headphoneamp_volume_down ( headphoneamp_t *ctx );

/**
 * @brief Headphone AMP set sound volume up function.
 * @details This function set sound volume up 
 * on of the LM4811 Dual 105mW Headphone Amplifier 
 * with Digital Volume Control and Shutdown Mode 
 * on the Headphone AMP click board™.
 * @param[in] ctx : Click context object.
 * See #headphoneamp_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t headphoneamp_volume_up ( headphoneamp_t *ctx );

/**
 * @brief Headphone AMP set sound volume function.
 * @details This function sets a desired sound volume
 * on of the LM4811 Dual 105mW Headphone Amplifier 
 * with Digital Volume Control and Shutdown Mode 
 * on the Headphone AMP click board™.
 * @param[in] ctx : Click context object.
 * See #headphoneamp_t object definition for detailed explanation.
 * @param[in] sound_volume : Desired sound volume from -33 dB to 12 dB.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t headphoneamp_set_sound_volume ( headphoneamp_t *ctx, uint8_t sound_volume );

#ifdef __cplusplus
}
#endif
#endif // HEADPHONEAMP_H

/*! @} */ // headphoneamp

// ------------------------------------------------------------------------ END
