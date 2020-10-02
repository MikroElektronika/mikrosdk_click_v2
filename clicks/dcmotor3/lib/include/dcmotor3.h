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
 * \brief This file contains API for DC Motor 3 Click driver.
 *
 * \addtogroup dcmotor3 DC Motor 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DCMOTOR3_H
#define DCMOTOR3_H

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
#define DCMOTOR3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.slp = MIKROBUS( mikrobus, MIKROBUS_CS ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DCMOTOR3_RETVAL  uint8_t

#define DCMOTOR3_OK           0x00
#define DCMOTOR3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define DCMOTOR3_DEF_FREQ     15000
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

    digital_out_t in1;
    digital_out_t in2;
    digital_out_t slp;

    // Modules 

    pwm_t pwm;

    // ctx variable 

    uint16_t pwm_period;
    uint32_t  pwm_freq;

} dcmotor3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t in1;
    pin_name_t in2;
    pin_name_t slp;

    // static variable 

    uint32_t  dev_pwm_freq;

} dcmotor3_cfg_t;

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
void dcmotor3_cfg_setup ( dcmotor3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param dcmotor3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DCMOTOR3_RETVAL dcmotor3_init ( dcmotor3_t *ctx, dcmotor3_cfg_t *cfg );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void dcmotor3_set_duty_cycle ( dcmotor3_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void dcmotor3_pwm_stop ( dcmotor3_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void dcmotor3_pwm_start ( dcmotor3_t *ctx );

/**
 * @brief Enable the engine function
 *
 * @param ctx  Click object.
 *
 * @description This function enable the engine by set CS pin on DC Motor 3 Click board.
 */
void dcmotor3_enable ( dcmotor3_t *ctx );

/**
 * @brief Disable the engine function
 *
 * @param ctx  Click object.
 *
 * @description This function disable the engine by clear CS pin on DC Motor 3 Click board.
 */
void dcmotor3_standby ( dcmotor3_t *ctx );

/**
 * @brief Set the direction of rotation in the counter clockwise direction function
 *
 * @param ctx  Click object.
 * 
 * @description This function set the direction of rotation in the counter clockwise direction
 * by clear AN pin and sets RST pin on DC Motor 3 Click board.
 */
void dcmotor3_counter_clockwise ( dcmotor3_t *ctx );

/**
 * @brief Set the direction of rotation in the clockwise direction function
 *
 * @param ctx  Click object.
 * 
 * @description This function set the direction of rotation in the clockwise direction
 * by sets AN pin and clear RST pin on DC Motor 3 Click board.
 */
void dcmotor3_clockwise ( dcmotor3_t *ctx );

/**
 * @brief Brake the engine function
 *
 * @param ctx  Click object.
 * 
 * @description This function brake the engine by sets AN and RST pins on DC Motor 3 Click board.
 */
void dcmotor3_short_brake ( dcmotor3_t *ctx );

/**
 * @brief Stop the engine function
 *
 * @param ctx  Click object.
 * 
 * @description This function stop the engine by sets AN and RST pins on DC Motor 3 Click board.
 */
void dcmotor3_stop ( dcmotor3_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _DCMOTOR3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
