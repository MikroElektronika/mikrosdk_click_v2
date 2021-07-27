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
 * @file buzz2.h
 * @brief This file contains API for BUZZ 2 Click Driver.
 */

#ifndef BUZZ2_H
#define BUZZ2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup buzz2 BUZZ 2 Click Driver
 * @brief API for configuring and manipulating BUZZ 2 Click driver.
 * @{
 */

/**
 * @defgroup buzz2_set BUZZ 2 PWM Settings
 * @brief Settings for configuration of BUZZ 2 Click driver.
 */

/**
 * @addtogroup buzz2_cfg
 * @{
 */

/**
 * @brief BUZZ 2 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of BUZZ 2 Click driver.
 */
#define BUZZ2_DEF_FREQ     5000

/*! @} */ // buzz2_cfg

/**
 * @brief BUZZ 2 default frequency.
 * @details Setting frequencies for BUZZ 2 Click.
 */
    
/**
 * @addtogroup buzz2_freq
 * @{
 */
#define BUZZ2_NOTE_C2                65
#define BUZZ2_NOTE_Db2               69
#define BUZZ2_NOTE_D2                73
#define BUZZ2_NOTE_Eb2               78
#define BUZZ2_NOTE_E2                82
#define BUZZ2_NOTE_F2                87
#define BUZZ2_NOTE_Gb2               93
#define BUZZ2_NOTE_G2                98
#define BUZZ2_NOTE_Ab2              104
#define BUZZ2_NOTE_A2               110
#define BUZZ2_NOTE_Bb2              117
#define BUZZ2_NOTE_B2               123
#define BUZZ2_NOTE_C3               131
#define BUZZ2_NOTE_Db3              139
#define BUZZ2_NOTE_D3               147
#define BUZZ2_NOTE_Eb3              156
#define BUZZ2_NOTE_E3               165
#define BUZZ2_NOTE_F3               175
#define BUZZ2_NOTE_Gb3              185
#define BUZZ2_NOTE_G3               196
#define BUZZ2_NOTE_Ab3              208
#define BUZZ2_NOTE_A3               220
#define BUZZ2_NOTE_AS3              233
#define BUZZ2_NOTE_B3               247
#define BUZZ2_NOTE_C4               262
#define BUZZ2_NOTE_Db4              277
#define BUZZ2_NOTE_D4               294
#define BUZZ2_NOTE_Eb4              311
#define BUZZ2_NOTE_E4               330
#define BUZZ2_NOTE_F4               349
#define BUZZ2_NOTE_Gb4              370
#define BUZZ2_NOTE_G4               392
#define BUZZ2_NOTE_Ab4              415
#define BUZZ2_NOTE_A4               440
#define BUZZ2_NOTE_Bb4              466
#define BUZZ2_NOTE_B4               494
#define BUZZ2_NOTE_C5               523
#define BUZZ2_NOTE_Db5              554
#define BUZZ2_NOTE_D5               587
#define BUZZ2_NOTE_Eb5              622
#define BUZZ2_NOTE_E5               659
#define BUZZ2_NOTE_F5               698
#define BUZZ2_NOTE_Gb5              740
#define BUZZ2_NOTE_G5               784
#define BUZZ2_NOTE_Ab5              831
#define BUZZ2_NOTE_A5               880
#define BUZZ2_NOTE_Bb5              932
#define BUZZ2_NOTE_B5               988
#define BUZZ2_NOTE_C6              1047
#define BUZZ2_NOTE_Db6             1109
#define BUZZ2_NOTE_D6              1175
#define BUZZ2_NOTE_Eb6             1245
#define BUZZ2_NOTE_E6              1319
#define BUZZ2_NOTE_F6              1397
#define BUZZ2_NOTE_Gb6             1480
#define BUZZ2_NOTE_G6              1568
#define BUZZ2_NOTE_Ab6             1661
#define BUZZ2_NOTE_A6              1760
#define BUZZ2_NOTE_Bb6             1865
#define BUZZ2_NOTE_B6              1976
#define BUZZ2_NOTE_C7              2093
#define BUZZ2_NOTE_Db7             2217
#define BUZZ2_NOTE_D7              2349
#define BUZZ2_NOTE_Eb7             2489
#define BUZZ2_NOTE_E7              2637
#define BUZZ2_NOTE_F7              2794
#define BUZZ2_NOTE_Gb7             2960
#define BUZZ2_NOTE_G7              3136
#define BUZZ2_NOTE_Ab7             3322
#define BUZZ2_NOTE_A7              3520
#define BUZZ2_NOTE_Bb7             3729
#define BUZZ2_NOTE_B7              3951
#define BUZZ2_NOTE_C8              4186
#define BUZZ2_NOTE_Db8             4435
#define BUZZ2_NOTE_D8              4699
#define BUZZ2_NOTE_Eb8             4978
/*! @} */ // buzz2_freq

/**
 * @defgroup buzz2_map BUZZ 2 MikroBUS Map
 * @brief MikroBUS pin mapping of BUZZ 2 Click driver.
 */

/**
 * @addtogroup buzz2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BUZZ 2 Click to the selected MikroBUS.
 */
#define BUZZ2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // buzz2_map
/*! @} */ // buzz2

/**
 * @brief BUZZ 2 Click driver selector.
 * @details Selects target driver interface of BUZZ 2 Click driver.
 */

/**
 * @brief BUZZ 2 Click context object.
 * @details Context object definition of BUZZ 2 Click driver.
 */
typedef struct
{
    // Modules

    pwm_t pwm;                                      /**< PWM driver object. */

    // ctx variable

    uint32_t pwm_freq;                              /**< PWM frequency value. */

} buzz2_t;

/**
 * @brief BUZZ 2 Click configuration object.
 * @details Configuration object definition of BUZZ 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t pwm;                                 /**< PWM pin. */

    // Static variable

    uint32_t dev_pwm_freq;                          /**< PWM frequency value. */

} buzz2_cfg_t;

/**
 * @brief BUZZ 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BUZZ2_OK = 0,
   BUZZ2_ERROR = -1

} buzz2_return_value_t;

/*!
 * @addtogroup buzz2 BUZZ 2 Click Driver
 * @brief API for configuring and manipulating BUZZ 2 Click driver.
 * @{
 */

/**
 * @brief BUZZ 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buzz2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buzz2_cfg_setup ( buzz2_cfg_t *cfg );

/**
 * @brief BUZZ 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buzz2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buzz2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buzz2_init ( buzz2_t *ctx, buzz2_cfg_t *cfg );

/**
 * @brief BUZZ 2 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #buzz2_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty_cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */

err_t buzz2_set_duty_cycle ( buzz2_t *ctx, float duty_cycle );

/**
 * @brief Play sound function.
 * @details This function plays sound on buzzer.
 * @param[out] ctx  Click object.
 * @param[in] freq  Buzz sound frequency.
 * @param[in] level  Buzz sound level. ( min = 1, max = 1000 )
 * @param[in] duration  Buzz sound duration in miliseconds.
 * @return Nothing.
 *
 */
void buzz2_play_sound ( buzz2_t *ctx, uint16_t freq, uint16_t level, uint16_t duration );

/**
 * @brief BUZZ 2 stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #buzz2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */

err_t buzz2_pwm_stop ( buzz2_t *ctx );

/**
 * @brief BUZZ 2 start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #buzz2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t buzz2_pwm_start ( buzz2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BUZZ2_H

/*! @} */ // buzz2

// ------------------------------------------------------------------------ END
