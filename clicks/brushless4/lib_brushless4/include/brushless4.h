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
 * \brief This file contains API for Brushless 4 Click driver.
 *
 * \addtogroup brushless4 Brushless 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BRUSHLESS4_H
#define BRUSHLESS4_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define BRUSHLESS4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.fg  = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BRUSHLESS4_RETVAL  uint8_t

#define BRUSHLESS4_OK           0x00
#define BRUSHLESS4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define BRUSHLESS4_DEF_FREQ     20000
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

    // Input pins 

    digital_in_t fg;
    
    // Modules 

    pwm_t pwm;

    // ctx variable 

    uint16_t pwm_period;
    uint32_t  pwm_freq;

    uint8_t num_of_poles;
    uint8_t num_of_slots;
    uint16_t slots_poles;

} brushless4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t fg;

    // static variable 

    uint32_t  dev_pwm_freq;

} brushless4_cfg_t;

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
void brushless4_cfg_setup ( brushless4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param brushless4 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BRUSHLESS4_RETVAL brushless4_init ( brushless4_t *ctx, brushless4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Brushless 4 click.
 */
void brushless4_default_cfg ( brushless4_t *ctx );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void brushless4_set_duty_cycle ( brushless4_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void brushless4_pwm_stop ( brushless4_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void brushless4_pwm_start ( brushless4_t *ctx );

/**
 * @brief Setting the number of poles and number of slots.
 *
 * @param ctx   Click object.
 * @param poles Number of poles.
 * @param slots Number of slots.
 *
 * @description This function is used for setting the number of poles and number of slots.
 */
void brushless4_motor_parameters ( brushless4_t *ctx , uint8_t poles, uint8_t slots );

/**
 * @brief Calculation of speed.
 *
 * @param ctx           Click object.
 * @param pulse_sample  Number of samples.
 * 
 * @returns Rotor speed.
 *
 * @description This function calculate the speed out of number of samples acumulated over a period of time. 
 * @note: Motor parameters must be set.
 */
uint16_t brushless4_get_speed ( brushless4_t *ctx, uint16_t pulse_sample );

/**
 * @brief Set the state of the PWM pin.
 *
 * @param ctx     Click object.
 * @param state   Desired state to be set.
 *
 * @description This function sets the state of the PWM pin.
 */
void brushless4_pwm_pin ( brushless4_t *ctx, uint8_t state );

/**
 * @brief The state of the interrupt pin.
 *
 * @param ctx  Click object.
 * @returns    State of the fg pin. 
 *
 * @description This function gets the state of the fg pin.
 */
uint8_t brushless4_fg_get ( brushless4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BRUSHLESS4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
