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
 * @file buzz3.h
 * @brief This file contains API for Buzz 3 Click Driver.
 */

#ifndef BUZZ3_H
#define BUZZ3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup buzz3 Buzz 3 Click Driver
 * @brief API for configuring and manipulating Buzz 3 Click driver.
 * @{
 */

/**
 * @defgroup buzz3_set Buzz 3 PWM Settings
 * @brief Settings for configuration of Buzz 3 Click driver.
 */

/**
 * @addtogroup buzz3_cfg
 * @{
 */

/**
 * @brief Buzz 3 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Buzz 3 Click driver.
 */
#define BUZZ3_DEF_FREQ     500

/**
 * @brief Buzz 3 note frequency.
 * @details Specified note frequency of Buzz 3 Click driver.
 */
#define BUZZ3_NOTE_C2                65
#define BUZZ3_NOTE_Db2               69
#define BUZZ3_NOTE_D2                73
#define BUZZ3_NOTE_Eb2               78
#define BUZZ3_NOTE_E2                82
#define BUZZ3_NOTE_F2                87
#define BUZZ3_NOTE_Gb2               93
#define BUZZ3_NOTE_G2                98
#define BUZZ3_NOTE_Ab2              104
#define BUZZ3_NOTE_A2               110
#define BUZZ3_NOTE_Bb2              117
#define BUZZ3_NOTE_B2               123
#define BUZZ3_NOTE_C3               131
#define BUZZ3_NOTE_Db3              139
#define BUZZ3_NOTE_D3               147
#define BUZZ3_NOTE_Eb3              156
#define BUZZ3_NOTE_E3               165
#define BUZZ3_NOTE_F3               175
#define BUZZ3_NOTE_Gb3              185
#define BUZZ3_NOTE_G3               196
#define BUZZ3_NOTE_Ab3              208
#define BUZZ3_NOTE_A3               220
#define BUZZ3_NOTE_AS3              233
#define BUZZ3_NOTE_B3               247
#define BUZZ3_NOTE_C4               262
#define BUZZ3_NOTE_Db4              277
#define BUZZ3_NOTE_D4               294
#define BUZZ3_NOTE_Eb4              311
#define BUZZ3_NOTE_E4               330
#define BUZZ3_NOTE_F4               349
#define BUZZ3_NOTE_Gb4              370
#define BUZZ3_NOTE_G4               392
#define BUZZ3_NOTE_Ab4              415
#define BUZZ3_NOTE_A4               440
#define BUZZ3_NOTE_Bb4              466
#define BUZZ3_NOTE_B4               494
#define BUZZ3_NOTE_C5               523
#define BUZZ3_NOTE_Db5              554
#define BUZZ3_NOTE_D5               587
#define BUZZ3_NOTE_Eb5              622
#define BUZZ3_NOTE_E5               659
#define BUZZ3_NOTE_F5               698
#define BUZZ3_NOTE_Gb5              740
#define BUZZ3_NOTE_G5               784
#define BUZZ3_NOTE_Ab5              831
#define BUZZ3_NOTE_A5               880
#define BUZZ3_NOTE_Bb5              932
#define BUZZ3_NOTE_B5               988
#define BUZZ3_NOTE_C6              1047
#define BUZZ3_NOTE_Db6             1109
#define BUZZ3_NOTE_D6              1175
#define BUZZ3_NOTE_Eb6             1245
#define BUZZ3_NOTE_E6              1319
#define BUZZ3_NOTE_F6              1397
#define BUZZ3_NOTE_Gb6             1480
#define BUZZ3_NOTE_G6              1568
#define BUZZ3_NOTE_Ab6             1661
#define BUZZ3_NOTE_A6              1760
#define BUZZ3_NOTE_Bb6             1865
#define BUZZ3_NOTE_B6              1976
#define BUZZ3_NOTE_C7              2093
#define BUZZ3_NOTE_Db7             2217
#define BUZZ3_NOTE_D7              2349
#define BUZZ3_NOTE_Eb7             2489
#define BUZZ3_NOTE_E7              2637
#define BUZZ3_NOTE_F7              2794
#define BUZZ3_NOTE_Gb7             2960
#define BUZZ3_NOTE_G7              3136
#define BUZZ3_NOTE_Ab7             3322
#define BUZZ3_NOTE_A7              3520
#define BUZZ3_NOTE_Bb7             3729
#define BUZZ3_NOTE_B7              3951
#define BUZZ3_NOTE_C8              4186
#define BUZZ3_NOTE_Db8             4435
#define BUZZ3_NOTE_D8              4699
#define BUZZ3_NOTE_Eb8             4978

/**
 * @brief Buzz 3 gain mode settings.
 * @details Specified setting for gain mode of Buzz 3 Click driver.
 */
#define BUZZ3_OP_MODE_GAIN_x0      0x00
#define BUZZ3_OP_MODE_GAIN_x1      0x01
#define BUZZ3_OP_MODE_GAIN_x2      0x02
#define BUZZ3_OP_MODE_GAIN_x3      0x03

/*! @} */ // buzz3_cfg

/**
 * @defgroup buzz3_map Buzz 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Buzz 3 Click driver.
 */

/**
 * @addtogroup buzz3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buzz 3 Click to the selected MikroBUS.
 */
#define BUZZ3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.en1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en2 = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // buzz3_map
/*! @} */ // buzz3

/**
 * @brief Buzz 3 Click driver selector.
 * @details Selects target driver interface of Buzz 3 Click driver.
 */

/**
 * @brief Buzz 3 Click context object.
 * @details Context object definition of Buzz 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en1;       /**< Charge Pump Mode Pin 1. */
    digital_out_t en2;       /**< Charge Pump Mode Pin 2. */

    // Modules
    pwm_t pwm;               /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;       /**< PWM frequency value. */

} buzz3_t;

/**
 * @brief Buzz 3 Click configuration object.
 * @details Configuration object definition of Buzz 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;          /**< PWM pin. */

    // Additional gpio pins
    pin_name_t en1;          /**< Charge Pump Mode Pin 1. */
    pin_name_t en2;          /**< Charge Pump Mode Pin 2. */

    // Static variable
    uint32_t dev_pwm_freq;   /**< PWM frequency value. */

} buzz3_cfg_t;

/**
 * @brief Buzz 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUZZ3_OK = 0,
    BUZZ3_ERROR = -1

} buzz3_return_value_t;

/*!
 * @addtogroup buzz3 Buzz 3 Click Driver
 * @brief API for configuring and manipulating Buzz 3 Click driver.
 * @{
 */

/**
 * @brief Buzz 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buzz3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buzz3_cfg_setup ( buzz3_cfg_t *cfg );

/**
 * @brief Buzz 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buzz3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buzz3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t buzz3_init ( buzz3_t *ctx, buzz3_cfg_t *cfg );

/**
 * @brief Buzz 3 default configuration function.
 * @details This function executes a default configuration of Buzz 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #buzz3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t buzz3_default_cfg ( buzz3_t *ctx );

/**
 * @brief Buzz 3 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #buzz3_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t buzz3_set_duty_cycle ( buzz3_t *ctx, float duty_cycle );

/**
 * @brief Buzz 3 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[out] ctx : Click context object.
 * See #buzz3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t buzz3_pwm_stop ( buzz3_t *ctx );

/**
 * @brief Buzz 3 start PWM module.
 * @details This function starts the PWM module output.
 * @param[out] ctx : Click context object.
 * See #buzz3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t buzz3_pwm_start ( buzz3_t *ctx );

/**
 * @brief Buzz 3 set gain operating mode function.
 * @details The function set gain operating mode of the PAM8904 piezo sounder driver 
 * with integrated charge pump boost converter on Buzz 3 click board.
 * @param[out] ctx : Click context object.
 * See #buzz3_t object definition for detailed explanation.
 * @param[out] op_mode : charge pump mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t buzz3_set_gain_operating_mode ( buzz3_t *ctx, uint8_t op_mode );

/**
 * @brief Buzz 3 play sound function.
 * @details This function plays sound on buzzer.
 * @param[out] ctx : Click object.
 * @param[in] freq : Buzz sound frequency.
 * @param[in] duration : Buzz sound duration in miliseconds.
 * @return Nothing.
 */
void buzz3_play_sound ( buzz3_t *ctx, uint16_t freq, uint16_t duration );

#ifdef __cplusplus
}
#endif
#endif // BUZZ3_H

/*! @} */ // buzz3

// ------------------------------------------------------------------------ END
