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
 * @file dsp.h
 * @brief This file contains API for DSP Click Driver.
 */

#ifndef DSP_H
#define DSP_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"

/*!
 * @addtogroup dsp DSP Click Driver
 * @brief API for configuring and manipulating DSP Click driver.
 * @{
 */

/**
 * @addtogroup effects
 * @{
 */ 

/**
 * @brief DSP reverb and multi-effects setting.
 * @details Specified setting for reverb and multi-effects of DSP Click driver.
 */
#define DSP_SET_EFFECT_MEDIUM                     0x00
#define DSP_SET_EFFECT_CHAMBR7B                   0x01
#define DSP_SET_EFFECT_ROOM3B                     0x02
#define DSP_SET_EFFECT_CHAMBER2                   0x03
#define DSP_SET_EFFECT_REVERS3B                   0x04
#define DSP_SET_EFFECT_GATED4B                    0x05
#define DSP_SET_EFFECT_ROOM2A                     0x06
#define DSP_SET_EFFECT_SPRING3B                   0x07
#define DSP_SET_EFFECT_PHASER1                    0x08
#define DSP_SET_EFFECT_FLANGER2                   0x09
#define DSP_SET_EFFECT_DELAY7                     0x0A
#define DSP_SET_EFFECT_CHORUS4                    0x0B
#define DSP_SET_EFFECT_EARLREF4                   0x0C
#define DSP_SET_EFFECT_AMB4                       0x0D
#define DSP_SET_EFFECT_DELAY3                     0x0E
#define DSP_SET_EFFECT_DELAY1                     0x0F

/*! @} */ // effects

/**
 * @addtogroup pin_state
 * @{
 */ 

/**
 * @brief DSP pin setting function.
 * @details Specified setting for the target pin state of DSP Click driver.
 */
#define DSP_SET_PIN_STATE_LOW                     0x00
#define DSP_SET_PIN_STATE_HIGH                    0x01

/*! @} */ // pin_state

/**
 * @addtogroup dsp_retval_t
 * @{
 */ 

/**
 * @brief DSP error code settings.
 * @details Specified setting for the error code of DSP Click driver.
 */
#define dsp_retval_t  uint8_t

#define DSP_OK                                    0x00
#define DSP_ERROR                                 0xFF

/*! @} */ // dsp_retval_t


/**
 * @defgroup dsp_map DSP MikroBUS Map
 * @brief MikroBUS pin mapping of DSP Click driver.
 */

/**
 * @addtogroup dsp_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DSP Click to the selected MikroBUS.
 */
#define DSP_MAP_MIKROBUS( cfg, mikrobus )         \
    cfg.p0 = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.p1 = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.p3 = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.p2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dsp_map
/*! @} */ // dsp

/**
 * @brief DSP Click context object.
 * @details Context object definition of DSP Click driver.
 */
typedef struct
{
    digital_out_t  p0;     /**< P0 output pin.  */
    digital_out_t  rst;    /**< Rst output pin. */
    digital_out_t  p1;     /**< P1 output pin.  */
    digital_out_t  p3;     /**< P3 output pin.  */
    digital_out_t  p2;     /**< P2 output pin.  */

} dsp_t;

/**
 * @brief DSP Click configuration object.
 * @details Configuration object definition of DSP Click driver.
 */
typedef struct
{
    pin_name_t  p0;       /**< P0 output pin.  */
    pin_name_t  rst;      /**< Rst output pin. */
    pin_name_t  p1;       /**< P1 output pin.  */
    pin_name_t  p3;       /**< P3 output pin.  */
    pin_name_t  p2;       /**< P2 output pin.  */

} dsp_cfg_t;

/*!
 * @addtogroup dsp DSP Click Driver
 * @brief API for configuring and manipulating DSP Click driver.
 * @{
 */

/**
 * @brief DSP configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dsp_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dsp_cfg_setup ( dsp_cfg_t *cfg );

/**
 * @brief DSP initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dsp_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dsp_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dsp_init ( dsp_t *ctx, dsp_cfg_t *cfg );

/**
 * @brief DSP default configuration function.
 * @details This function executes a default configuration of DSP
 * click board.
 * @param[in] ctx : Click context object.
 * See #dsp_t object definition for detailed explanation.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void dsp_default_cfg ( dsp_t *ctx );

/**
 * @brief DSP P0 pin setting function.
 * @details This function sets the P0 pin state to the desired level
 * DSP click board.
 * @param[in] ctx : Click context object.
 * See #dsp_t object definition for detailed explanation.
 * @param[in] pin_state : 
 *    @li @c 0x00 ( DSP_SET_PIN_STATE_LOW )  - Set P0 pin on the low level,
 *    @li @c 0x01 ( DSP_SET_PIN_STATE_HIGH ) - Set P0 pin on the high level.
 * @return Nothing.
 * @note None.
 */
void dsp_pin_set_p0 ( dsp_t *ctx, uint8_t pin_state );

/**
 * @brief DSP P1 pin setting function.
 * @details This function sets the P1 pin state to the desired level
 * DSP click board.
 * @param[in] ctx : Click context object.
 * See #dsp_t object definition for detailed explanation.
 * @param[in] pin_state : 
 *    @li @c 0x00 ( DSP_SET_PIN_STATE_LOW )  - Set P1 pin on the low level,
 *    @li @c 0x01 ( DSP_SET_PIN_STATE_HIGH ) - Set P1 pin on the high level.
 * @return Nothing.
 * @note None.
 */
void dsp_pin_set_p1 ( dsp_t *ctx, uint8_t pin_state );

/**
 * @brief DSP P2 pin setting function.
 * @details This function sets the P2 pin state to the desired level
 * DSP click board.
 * @param[in] ctx : Click context object.
 * See #dsp_t object definition for detailed explanation.
 * @param[in] pin_state : 
 *    @li @c 0x00 ( DSP_SET_PIN_STATE_LOW )  - Set P2 pin on the low level,
 *    @li @c 0x01 ( DSP_SET_PIN_STATE_HIGH ) - Set P2 pin on the high level.
 * @return Nothing.
 * @note None.
 */
void dsp_pin_set_p2 ( dsp_t *ctx, uint8_t pin_state );

/**
 * @brief DSP P3 pin setting function.
 * @details This function sets the P3 pin state to the desired level
 * DSP click board.
 * @param[in] ctx : Click context object.
 * See #dsp_t object definition for detailed explanation.
 * @param[in] pin_state : 
 *    @li @c 0x00 ( DSP_SET_PIN_STATE_LOW )  - Set P3 pin on the low level,
 *    @li @c 0x01 ( DSP_SET_PIN_STATE_HIGH ) - Set P3 pin on the high level.
 * @return Nothing.
 * @note None.
 */
void dsp_pin_set_p3 ( dsp_t *ctx, uint8_t pin_state );

/**
 * @brief DSP power on the device function.
 * @details This function executes power-up of the device of 
 * DSP click board.
 * @param[in] ctx : Click context object.
 * See #dsp_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void dsp_power_on ( dsp_t *ctx );

/**
 * @brief DSP reset the device function.
 * @details This function executes a hardware reset of
 * DSP click board.
 * @param[in] ctx : Click context object.
 * See #dsp_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void dsp_reset ( dsp_t *ctx );

/**
 * @brief DSP reverb and multi-effects setting function.
 * @details This function sets the reverb and multi-effects of
 * DSP click board.
 * @param[in] ctx : Click context object.
 * See #dsp_t object definition for detailed explanation.
 * @param[in] effects : The number of the desired effect ( from 0 to 15 )
 *    @li @c 0x00 ( DSP_SET_EFFECT_MEDIUM )   - Reverb, Small hall (1.5 sec.),
 *    @li @c 0x01 ( DSP_SET_EFFECT_CHAMBR7B ) - Reverb, Big hall (2.8 sec.),
 *    @li @c 0x02 ( DSP_SET_EFFECT_ROOM3B )   - Reverb, Room (1.8 sec.),
 *    @li @c 0x03 ( DSP_SET_EFFECT_CHAMBER2 ) - Reverb, Church (7 sec.),
 *    @li @c 0x04 ( DSP_SET_EFFECT_REVERS3B ) - Reverb Reverse (1.2 sec.),
 *    @li @c 0x05 ( DSP_SET_EFFECT_GATED4B )  - Reverb Gated (0.8 sec.),
 *    @li @c 0x06 ( DSP_SET_EFFECT_ROOM2A )   - Reverb Chapel (3 sec.),
 *    @li @c 0x07 ( DSP_SET_EFFECT_SPRING3B ) - Reverb Spring (2 sec.),
 *    @li @c 0x08 ( DSP_SET_EFFECT_PHASER1 )  - Phaser,
 *    @li @c 0x09 ( DSP_SET_EFFECT_FLANGER2 ) - Flanger,
 *    @li @c 0x0A ( DSP_SET_EFFECT_DELAY7 )   - Echo,
 *    @li @c 0x0B ( DSP_SET_EFFECT_CHORUS4 )  - Chorus,
 *    @li @c 0x0C ( DSP_SET_EFFECT_EARLREF4 ) - Early Reflection,
 *    @li @c 0x0D ( DSP_SET_EFFECT_AMB4 )     - Big Ambience,
 *    @li @c 0x0E ( DSP_SET_EFFECT_DELAY3 )   - Stereo Delay,
 *    @li @c 0x0F ( DSP_SET_EFFECT_DELAY1 )   - Slap-back Delay.
 * @return @li @c 0x00 ( DSP_OK )    - Ok,
 *         @li @c 0xFF ( DSP_ERROR ) - Error.
 * @note None.
 */
dsp_retval_t dsp_set_effect ( dsp_t *ctx, uint8_t effects );

#ifdef __cplusplus
}
#endif
#endif // DSP_H

/*! @} */ // dsp

// ------------------------------------------------------------------------ END
