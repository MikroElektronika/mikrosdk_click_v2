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
 * @file piezodriver.h
 * @brief This file contains API for Piezo Driver Click Driver.
 */

#ifndef PIEZODRIVER_H
#define PIEZODRIVER_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup piezodriver Piezo Driver Click Driver
 * @brief API for configuring and manipulating Piezo Driver Click driver.
 * @{
 */

/**
 * @defgroup piezodriver_cfg Piezo Driver PWM Settings
 * @brief Settings for configuration of Piezo Driver Click driver.
 */

/**
 * @addtogroup piezodriver_cfg
 * @{
 */

/**
 * @brief Piezo Driver default PWM frequency.
 * @details Specified setting for default PWM frequency of Piezo Driver Click driver.
 */
#define PIEZODRIVER_DEF_FREQ                5000

/**
 * @brief Piezo Driver notes.
 * @details Specified notes and their frequency of Piezo Driver Click driver.
 */
#define PIEZODRIVER_NOTE_C2                 65
#define PIEZODRIVER_NOTE_DB2                69
#define PIEZODRIVER_NOTE_D2                 73
#define PIEZODRIVER_NOTE_EB2                78
#define PIEZODRIVER_NOTE_E2                 82
#define PIEZODRIVER_NOTE_F2                 87
#define PIEZODRIVER_NOTE_GB2                93
#define PIEZODRIVER_NOTE_G2                 98
#define PIEZODRIVER_NOTE_AB2                104
#define PIEZODRIVER_NOTE_A2                 110
#define PIEZODRIVER_NOTE_BB2                117
#define PIEZODRIVER_NOTE_B2                 123
#define PIEZODRIVER_NOTE_C3                 131
#define PIEZODRIVER_NOTE_DB3                139
#define PIEZODRIVER_NOTE_D3                 147
#define PIEZODRIVER_NOTE_EB3                156
#define PIEZODRIVER_NOTE_E3                 165
#define PIEZODRIVER_NOTE_F3                 175
#define PIEZODRIVER_NOTE_GB3                185
#define PIEZODRIVER_NOTE_G3                 196
#define PIEZODRIVER_NOTE_AB3                208
#define PIEZODRIVER_NOTE_A3                 220
#define PIEZODRIVER_NOTE_AS3                233
#define PIEZODRIVER_NOTE_B3                 247
#define PIEZODRIVER_NOTE_C4                 262
#define PIEZODRIVER_NOTE_DB4                277
#define PIEZODRIVER_NOTE_D4                 294
#define PIEZODRIVER_NOTE_EB4                311
#define PIEZODRIVER_NOTE_E4                 330
#define PIEZODRIVER_NOTE_F4                 349
#define PIEZODRIVER_NOTE_GB4                370
#define PIEZODRIVER_NOTE_G4                 392
#define PIEZODRIVER_NOTE_AB4                415
#define PIEZODRIVER_NOTE_A4                 440
#define PIEZODRIVER_NOTE_BB4                466
#define PIEZODRIVER_NOTE_B4                 494
#define PIEZODRIVER_NOTE_C5                 523
#define PIEZODRIVER_NOTE_DB5                554
#define PIEZODRIVER_NOTE_D5                 587
#define PIEZODRIVER_NOTE_EB5                622
#define PIEZODRIVER_NOTE_E5                 659
#define PIEZODRIVER_NOTE_F5                 698
#define PIEZODRIVER_NOTE_GB5                740
#define PIEZODRIVER_NOTE_G5                 784
#define PIEZODRIVER_NOTE_AB5                831
#define PIEZODRIVER_NOTE_A5                 880
#define PIEZODRIVER_NOTE_BB5                932
#define PIEZODRIVER_NOTE_B5                 988
#define PIEZODRIVER_NOTE_C6                 1047
#define PIEZODRIVER_NOTE_DB6                1109
#define PIEZODRIVER_NOTE_D6                 1175
#define PIEZODRIVER_NOTE_EB6                1245
#define PIEZODRIVER_NOTE_E6                 1319
#define PIEZODRIVER_NOTE_F6                 1397
#define PIEZODRIVER_NOTE_GB6                1480
#define PIEZODRIVER_NOTE_G6                 1568
#define PIEZODRIVER_NOTE_AB6                1661
#define PIEZODRIVER_NOTE_A6                 1760
#define PIEZODRIVER_NOTE_BB6                1865
#define PIEZODRIVER_NOTE_B6                 1976
#define PIEZODRIVER_NOTE_C7                 2093
#define PIEZODRIVER_NOTE_DB7                2217
#define PIEZODRIVER_NOTE_D7                 2349
#define PIEZODRIVER_NOTE_EB7                2489
#define PIEZODRIVER_NOTE_E7                 2637
#define PIEZODRIVER_NOTE_F7                 2794
#define PIEZODRIVER_NOTE_GB7                2960
#define PIEZODRIVER_NOTE_G7                 3136
#define PIEZODRIVER_NOTE_AB7                3322
#define PIEZODRIVER_NOTE_A7                 3520
#define PIEZODRIVER_NOTE_BB7                3729
#define PIEZODRIVER_NOTE_B7                 3951
#define PIEZODRIVER_NOTE_C8                 4186
#define PIEZODRIVER_NOTE_DB8                4435
#define PIEZODRIVER_NOTE_D8                 4699
#define PIEZODRIVER_NOTE_EB8                4978

/*! @} */ // piezodriver_cfg

/**
 * @defgroup piezodriver_map Piezo Driver MikroBUS Map
 * @brief MikroBUS pin mapping of Piezo Driver Click driver.
 */

/**
 * @addtogroup piezodriver_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Piezo Driver Click to the selected MikroBUS.
 */
#define PIEZODRIVER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); 
    
/*! @} */ // piezodriver_map
/*! @} */ // piezodriver

/**
 * @brief Piezo Driver Click context object.
 * @details Context object definition of Piezo Driver Click driver.
 */
typedef struct
{
    // Modules
    pwm_t pwm;                 /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;         /**< PWM frequency value. */

} piezodriver_t;

/**
 * @brief Piezo Driver Click configuration object.
 * @details Configuration object definition of Piezo Driver Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;            /**< PWM pin. */

    // Static variable
    uint32_t dev_pwm_freq;     /**< PWM frequency value. */

} piezodriver_cfg_t;

/**
 * @brief Piezo Driver Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PIEZODRIVER_OK = 0,
    PIEZODRIVER_ERROR = -1

} piezodriver_return_value_t;

/*!
 * @addtogroup piezodriver Piezo Driver Click Driver
 * @brief API for configuring and manipulating Piezo Driver Click driver.
 * @{
 */

/**
 * @brief Piezo Driver configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #piezodriver_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void piezodriver_cfg_setup ( piezodriver_cfg_t *cfg );

/**
 * @brief Piezo Driver initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #piezodriver_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #piezodriver_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezodriver_init ( piezodriver_t *ctx, piezodriver_cfg_t *cfg );

/**
 * @brief Piezo Driver default configuration function.
 * @details This function executes a default configuration of Piezo Driver
 * click board.
 * @param[in] ctx : Click context object.
 * See #piezodriver_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t piezodriver_default_cfg ( piezodriver_t *ctx );

/**
 * @brief Piezo Driver sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #piezodriver_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezodriver_set_duty_cycle ( piezodriver_t *ctx, float duty_cycle );

/**
 * @brief Piezo Driver stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #piezodriver_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezodriver_pwm_stop ( piezodriver_t *ctx );

/**
 * @brief Piezo Driver start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #piezodriver_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t piezodriver_pwm_start ( piezodriver_t *ctx );

/**
 * @brief Piezo Driver play sound function.
 * @details This function is used to play sound on the buzzer.
 * @param[in] ctx : Click object.
 * See #piezodriver_t object definition for detailed explanation.
 * @param[in] freq : Buzz sound frequency.
 * @param[in] level : Buzz sound level. ( min = 0, max = 100 )
 * @param[in] duration : Buzz sound duration in miliseconds.
 * @return Nothing.
 * @note None.
 */
void piezodriver_play_sound ( piezodriver_t *ctx, uint16_t freq, uint8_t level, uint16_t duration );

#ifdef __cplusplus
}
#endif
#endif // PIEZODRIVER_H

/*! @} */ // piezodriver

// ------------------------------------------------------------------------ END
