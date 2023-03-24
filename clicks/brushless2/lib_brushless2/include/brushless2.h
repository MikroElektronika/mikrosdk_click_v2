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
 * \brief This file contains API for Brushless 2 Click driver.
 *
 * \addtogroup brushless2 Brushless 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BRUSHLESS2_H
#define BRUSHLESS2_H

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
#define BRUSHLESS2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.cfg     = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.fr      = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.fgs     = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BRUSHLESS2_RETVAL  uint8_t

#define BRUSHLESS2_OK           0x00
#define BRUSHLESS2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define BRUSHLESS2_DEF_FREQ     5000
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
    
    // Output pins 

    digital_out_t fr;
    digital_out_t fgs;

    // Input pins 

    digital_in_t cfg;
    digital_in_t int_pin;
    
    // Modules 

    pwm_t pwm;

    // ctx variable 
    
    uint32_t pwm_freq;

} brushless2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t cfg;
    pin_name_t fr;
    pin_name_t fgs;
    pin_name_t int_pin;

    // static variable 

    uint32_t         dev_pwm_freq;

} brushless2_cfg_t;

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
void brushless2_cfg_setup ( brushless2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param brushless2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BRUSHLESS2_RETVAL brushless2_init ( brushless2_t *ctx, brushless2_cfg_t *cfg );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void brushless2_set_duty_cycle ( brushless2_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void brushless2_pwm_stop ( brushless2_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void brushless2_pwm_start ( brushless2_t *ctx );

/**
 * @brief Set the direction of rotation in the counterclockwise direction function
 *
 * @param ctx Click object.
 *
 * @description Function set the direction of rotation in the counterclockwise direction
 * by claer RST pin on Brushless 2 Click board.
 */
void brushless2_counter_clockwise ( brushless2_t *ctx );

/**
 * @brief Set the direction of rotation in the clockwise direction function
 *
 * @param ctx Click object.
 *
 * @description Function set the direction of rotation in the clockwise direction
 * by set RST pin on Brushless 2 Click board.
 */
void brushless2_clockwise ( brushless2_t *ctx );

/**
 * @brief Invert the direction of rotation
 *
 * @param ctx Click object.
 *
 * @description Function inverts the direction of rotation by toggling the RST pin on Brushless 2 Click board.
 */

void brushless2_invert_direction ( brushless2_t *ctx );

/**
 * @brief Get Interrupt pin state function
 *
 * @param ctx Click object.
 *
 * @return Interrupt pin state
 * - 0 : no active;
 * - 1 : active;
 *
 * @description Function get Interrupt ( INT ) pin state of Brushless 2 Click board.
 */
uint8_t brushless2_get_interrupt_status ( brushless2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BRUSHLESS2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
