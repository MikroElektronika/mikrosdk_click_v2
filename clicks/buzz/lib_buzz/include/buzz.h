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
 * @file buzz.h
 * @brief This file contains API for BUZZ Click Driver.
 */

#ifndef BUZZ_H
#define BUZZ_H

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
 * @addtogroup buzz BUZZ Click Driver
 * @brief API for configuring and manipulating BUZZ Click driver.
 * @{
 */

/**
 * @defgroup buzz_set BUZZ PWM Settings
 * @brief Settings for configuration of BUZZ Click driver.
 */

/**
 * @addtogroup buzz_cfg
 * @{
 */

/**
 * @brief BUZZ default PWM frequency.
 * @details Specified setting for setting default PWM frequency of BUZZ Click driver.
 */
#define BUZZ_DEF_FREQ     5000

/*! @} */ // buzz_cfg

/**
 * @brief Buzz frequency.
 * @details Seting frequencies for BUZZ Click.
 */

/**
 * @addtogroup buzz_freq
 * @{
 */
#define BUZZ_NOTE_C2  65
#define BUZZ_NOTE_Db2 69
#define BUZZ_NOTE_D2  73
#define BUZZ_NOTE_Eb2 78
#define BUZZ_NOTE_E2  82
#define BUZZ_NOTE_F2  87
#define BUZZ_NOTE_Gb2 93
#define BUZZ_NOTE_G2  98
#define BUZZ_NOTE_Ab2 104
#define BUZZ_NOTE_A2  110
#define BUZZ_NOTE_Bb2 117
#define BUZZ_NOTE_B2  123
#define BUZZ_NOTE_C3  131
#define BUZZ_NOTE_Db3 139
#define BUZZ_NOTE_D3  147
#define BUZZ_NOTE_Eb3 156
#define BUZZ_NOTE_E3  165
#define BUZZ_NOTE_F3  175
#define BUZZ_NOTE_Gb3 185
#define BUZZ_NOTE_G3  196
#define BUZZ_NOTE_Ab3 208
#define BUZZ_NOTE_A3  220
#define BUZZ_NOTE_AS3 233
#define BUZZ_NOTE_B3  247
#define BUZZ_NOTE_C4  262
#define BUZZ_NOTE_Db4 277
#define BUZZ_NOTE_D4  294
#define BUZZ_NOTE_Eb4 311
#define BUZZ_NOTE_E4  330
#define BUZZ_NOTE_F4  349
#define BUZZ_NOTE_Gb4 370
#define BUZZ_NOTE_G4  392
#define BUZZ_NOTE_Ab4 415
#define BUZZ_NOTE_A4  440
#define BUZZ_NOTE_Bb4 466
#define BUZZ_NOTE_B4  494
#define BUZZ_NOTE_C5  523
#define BUZZ_NOTE_Db5 554
#define BUZZ_NOTE_D5  587
#define BUZZ_NOTE_Eb5 622
#define BUZZ_NOTE_E5  659
#define BUZZ_NOTE_F5  698
#define BUZZ_NOTE_Gb5 740
#define BUZZ_NOTE_G5  784
#define BUZZ_NOTE_Ab5 831
#define BUZZ_NOTE_A5  880
#define BUZZ_NOTE_Bb5 932
#define BUZZ_NOTE_B5  988
#define BUZZ_NOTE_C6  1047
#define BUZZ_NOTE_Db6 1109
#define BUZZ_NOTE_D6  1175
#define BUZZ_NOTE_Eb6 1245
#define BUZZ_NOTE_E6  1319
#define BUZZ_NOTE_F6  1397
#define BUZZ_NOTE_Gb6 1480
#define BUZZ_NOTE_G6  1568
#define BUZZ_NOTE_Ab6 1661
#define BUZZ_NOTE_A6  1760
#define BUZZ_NOTE_Bb6 1865
#define BUZZ_NOTE_B6  1976
#define BUZZ_NOTE_C7  2093
#define BUZZ_NOTE_Db7 2217
#define BUZZ_NOTE_D7  2349
#define BUZZ_NOTE_Eb7 2489
#define BUZZ_NOTE_E7  2637
#define BUZZ_NOTE_F7  2794
#define BUZZ_NOTE_Gb7 2960
#define BUZZ_NOTE_G7  3136
#define BUZZ_NOTE_Ab7 3322
#define BUZZ_NOTE_A7  3520
#define BUZZ_NOTE_Bb7 3729
#define BUZZ_NOTE_B7  3951
#define BUZZ_NOTE_C8  4186
#define BUZZ_NOTE_Db8 4435
#define BUZZ_NOTE_D8  4699
#define BUZZ_NOTE_Eb8 4978

/*! @} */ // buzz_freq

/**
 * @defgroup buzz_map BUZZ MikroBUS Map
 * @brief MikroBUS pin mapping of BUZZ Click driver.
 */

/**
 * @addtogroup buzz_map
 * @{
 */



/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BUZZ Click to the selected MikroBUS.
 */
#define BUZZ_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // buzz_map
/*! @} */ // buzz

/**
 * @brief BUZZ Click driver selector.
 * @details Selects target driver interface of BUZZ Click driver.
 */

/**
 * @brief BUZZ Click context object.
 * @details Context object definition of BUZZ Click driver.
 */
typedef struct 
{
    // Modules

    pwm_t pwm;                                      /**< PWM driver object. */

    // ctx variable

    uint32_t pwm_freq;                              /**< PWM frequency value. */

} buzz_t;

/**
 * @brief BUZZ Click configuration object.
 * @details Configuration object definition of BUZZ Click driver.
 */
typedef struct 
{
    // Communication gpio pins

    pin_name_t pwm;                                 /**< PWM pin. */

    // Static variable

    uint32_t dev_pwm_freq;                          /**< PWM frequency value. */

} buzz_cfg_t;

/**
 * @brief BUZZ Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BUZZ_OK = 0,
   BUZZ_ERROR = -1

} buzz_return_value_t;

/*!
 * @addtogroup buzz BUZZ Click Driver
 * @brief API for configuring and manipulating BUZZ Click driver.
 * @{
 */

/**
 * @brief BUZZ configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buzz_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buzz_cfg_setup ( buzz_cfg_t *cfg );

/**
 * @brief BUZZ initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #buzz_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buzz_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buzz_init ( buzz_t *ctx, buzz_cfg_t *cfg );

/**
 * @brief BUZZ sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #buzz_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buzz_set_duty_cycle ( buzz_t *ctx, float duty_cycle );

/**
 * @brief BUZZ stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #buzz_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buzz_pwm_stop ( buzz_t *ctx );

/**
 * @brief BUZZ start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #buzz_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buzz_pwm_start ( buzz_t *ctx );

/**
 * @brief BUZZ Play sound function.
 * @details This function plays sound on buzzer.
 * @param[out] ctx : Click context object.
 * See #buzz_t object definition for detailed explanation.
 * @param[in] freq : Buzz sound frequency.
 * @param[in] level : Buzz sound level. ( min = 1, max = 1000 )
 * @param[in] duration : Buzz sound duration in miliseconds.
 * @return Nothing.
 *
 * @note None.
 */
void buzz_play_sound ( buzz_t *ctx, uint16_t freq, uint16_t level, uint16_t duration );

#ifdef __cplusplus
}
#endif
#endif // BUZZ_H

/*! @} */ // buzz

// ------------------------------------------------------------------------ END
