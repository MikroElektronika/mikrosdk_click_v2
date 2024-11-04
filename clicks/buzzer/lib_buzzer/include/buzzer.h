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
 * @file buzzer.h
 * @brief This file contains API for Buzzer Click Driver.
 */

#ifndef BUZZER_H
#define BUZZER_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup buzzer Buzzer Click Driver
 * @brief API for configuring and manipulating Buzzer Click driver.
 * @{
 */

/**
 * @defgroup buzzer_cfg Buzzer PWM Settings
 * @brief Settings for configuration of Buzzer Click driver.
 */

/**
 * @addtogroup buzzer_cfg
 * @{
 */

/**
 * @brief Buzzer default PWM frequency.
 * @details Specified setting for default PWM frequency of Buzzer Click driver.
 */
#define BUZZER_DEF_FREQ                     6000

/**
 * @brief Buzzer note frequency.
 * @details Specified PWM setting for note frequency of Buzzer Click driver.
 */
#define BUZZER_NOTE_C2                      65
#define BUZZER_NOTE_Db2                     69
#define BUZZER_NOTE_D2                      73
#define BUZZER_NOTE_Eb2                     78
#define BUZZER_NOTE_E2                      82
#define BUZZER_NOTE_F2                      87
#define BUZZER_NOTE_Gb2                     93
#define BUZZER_NOTE_G2                      98
#define BUZZER_NOTE_Ab2                     104
#define BUZZER_NOTE_A2                      110
#define BUZZER_NOTE_Bb2                     117
#define BUZZER_NOTE_B2                      123
#define BUZZER_NOTE_C3                      131
#define BUZZER_NOTE_Db3                     139
#define BUZZER_NOTE_D3                      147
#define BUZZER_NOTE_Eb3                     156
#define BUZZER_NOTE_E3                      165
#define BUZZER_NOTE_F3                      175
#define BUZZER_NOTE_Gb3                     185
#define BUZZER_NOTE_G3                      196
#define BUZZER_NOTE_Ab3                     208
#define BUZZER_NOTE_A3                      220
#define BUZZER_NOTE_AS3                     233
#define BUZZER_NOTE_B3                      247
#define BUZZER_NOTE_C4                      262
#define BUZZER_NOTE_Db4                     277
#define BUZZER_NOTE_D4                      294
#define BUZZER_NOTE_Eb4                     311
#define BUZZER_NOTE_E4                      330
#define BUZZER_NOTE_F4                      349
#define BUZZER_NOTE_Gb4                     370
#define BUZZER_NOTE_G4                      392
#define BUZZER_NOTE_Ab4                     415
#define BUZZER_NOTE_A4                      440
#define BUZZER_NOTE_Bb4                     466
#define BUZZER_NOTE_B4                      494
#define BUZZER_NOTE_C5                      523
#define BUZZER_NOTE_Db5                     554
#define BUZZER_NOTE_D5                      587
#define BUZZER_NOTE_Eb5                     622
#define BUZZER_NOTE_E5                      659
#define BUZZER_NOTE_F5                      698
#define BUZZER_NOTE_Gb5                     740
#define BUZZER_NOTE_G5                      784
#define BUZZER_NOTE_Ab5                     831
#define BUZZER_NOTE_A5                      880
#define BUZZER_NOTE_Bb5                     932
#define BUZZER_NOTE_B5                      988
#define BUZZER_NOTE_C6                      1047
#define BUZZER_NOTE_Db6                     1109
#define BUZZER_NOTE_D6                      1175
#define BUZZER_NOTE_Eb6                     1245
#define BUZZER_NOTE_E6                      1319
#define BUZZER_NOTE_F6                      1397
#define BUZZER_NOTE_Gb6                     1480
#define BUZZER_NOTE_G6                      1568
#define BUZZER_NOTE_Ab6                     1661
#define BUZZER_NOTE_A6                      1760
#define BUZZER_NOTE_Bb6                     1865
#define BUZZER_NOTE_B6                      1976
#define BUZZER_NOTE_C7                      2093
#define BUZZER_NOTE_Db7                     2217
#define BUZZER_NOTE_D7                      2349
#define BUZZER_NOTE_Eb7                     2489
#define BUZZER_NOTE_E7                      2637
#define BUZZER_NOTE_F7                      2794
#define BUZZER_NOTE_Gb7                     2960
#define BUZZER_NOTE_G7                      3136
#define BUZZER_NOTE_Ab7                     3322
#define BUZZER_NOTE_A7                      3520
#define BUZZER_NOTE_Bb7                     3729
#define BUZZER_NOTE_B7                      3951
#define BUZZER_NOTE_C8                      4186
#define BUZZER_NOTE_Db8                     4435
#define BUZZER_NOTE_D8                      4699
#define BUZZER_NOTE_Eb8                     4978

/**
 * @brief Buzzer note duration lenght.
 * @details Specified setting for note duration lenght of Buzzer Click driver.
 */
#define BUZZER_NOTE_LEN_WHOLE               1000
#define BUZZER_NOTE_LEN_HALF                ( BUZZER_NOTE_LEN_WHOLE / 2 )
#define BUZZER_NOTE_LEN_QUARTER             ( BUZZER_NOTE_LEN_WHOLE / 4 )
#define BUZZER_NOTE_LEN_EIGHTH              ( BUZZER_NOTE_LEN_WHOLE / 8 )
#define BUZZER_NOTE_LEN_SIXTEENTH           ( BUZZER_NOTE_LEN_WHOLE / 16 )

/**
 * @brief Buzzer volume settings.
 * @details Specified volume settings of Buzzer Click driver.
 */
#define BUZZER_VOLUME_MIN                   1
#define BUZZER_VOLUME_MAX                   100

/*! @} */ // buzzer_cfg

/**
 * @defgroup buzzer_map Buzzer MikroBUS Map
 * @brief MikroBUS pin mapping of Buzzer Click driver.
 */

/**
 * @addtogroup buzzer_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buzzer Click to the selected MikroBUS.
 */
#define BUZZER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // buzzer_map
/*! @} */ // buzzer

/**
 * @brief Buzzer Click context object.
 * @details Context object definition of Buzzer Click driver.
 */
typedef struct
{
    // Modules
    pwm_t pwm;                      /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;              /**< PWM frequency value. */

} buzzer_t;

/**
 * @brief Buzzer Click configuration object.
 * @details Configuration object definition of Buzzer Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;                 /**< PWM pin. */

    // Static variable
    uint32_t dev_pwm_freq;          /**< PWM frequency value. */

} buzzer_cfg_t;

/**
 * @brief Buzzer Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUZZER_OK = 0,
    BUZZER_ERROR = -1

} buzzer_return_value_t;

/*!
 * @addtogroup buzzer Buzzer Click Driver
 * @brief API for configuring and manipulating Buzzer Click driver.
 * @{
 */

/**
 * @brief Buzzer configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buzzer_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buzzer_cfg_setup ( buzzer_cfg_t *cfg );

/**
 * @brief Buzzer initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #buzzer_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buzzer_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buzzer_init ( buzzer_t *ctx, buzzer_cfg_t *cfg );

/**
 * @brief Buzzer sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #buzzer_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buzzer_set_duty_cycle ( buzzer_t *ctx, float duty_cycle );

/**
 * @brief Buzzer stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #buzzer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buzzer_pwm_stop ( buzzer_t *ctx );

/**
 * @brief Buzzer start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #buzzer_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buzzer_pwm_start ( buzzer_t *ctx );

/**
 * @brief Buzzer play sound function.
 * @details This function plays sound on the buzzer.
 * @param[in] ctx : Click context object.
 * See #buzzer_t object definition for detailed explanation.
 * @param[in] freq : Buzz sound frequency.
 * @param[in] level : Buzz sound level. ( min = 1, max = 100 )
 * @param[in] duration : Buzz sound duration in miliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buzzer_play_sound ( buzzer_t *ctx, uint16_t freq, uint8_t level, uint16_t duration );

#ifdef __cplusplus
}
#endif
#endif // BUZZER_H

/*! @} */ // buzzer

// ------------------------------------------------------------------------ END
