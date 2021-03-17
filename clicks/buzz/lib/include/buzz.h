/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for Buzz 2 Click driver.
 *
 * \addtogroup buzz Buzz 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUZZ_H
#define BUZZ_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
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
/** \} */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define BUZZ_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUZZ_RETVAL  uint8_t

#define BUZZ_OK           0x00
#define BUZZ_INIT_ERROR   0xFF
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
       
    // Modules 

    pwm_t pwm;

    // ctx variable 

    uint32_t  pwm_freq;

} buzz_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;

    // static variable 

    uint32_t  dev_pwm_freq;

} buzz_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void buzz_cfg_setup ( buzz_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUZZ_RETVAL buzz_init ( buzz_t *ctx, buzz_cfg_t *cfg );

/**
 * @brief Play sound function.
 *
 * @param ctx  Click object.
 * @param freq  Buzz sound frequency.
 * @param level  Buzz sound level. ( min = 1, max = 1000 )
 * @param duration  Buzz sound duration in miliseconds.
 *
 * @description This function plays sound on buzzer.
 */
void buzz_play_sound ( buzz_t *ctx, uint16_t freq, uint16_t level, uint16_t duration );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void buzz_set_duty_cycle ( buzz_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void buzz_pwm_stop ( buzz_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void buzz_pwm_start ( buzz_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BUZZ_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
