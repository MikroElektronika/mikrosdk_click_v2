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
 * \brief This file contains API for DC MOTOR  Click driver.
 *
 * \addtogroup dcmotor DC MOTOR  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DCMOTOR_H
#define DCMOTOR_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define DCMOTOR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg. slp = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg. sl1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg. sl2 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg. flt = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DCMOTOR_RETVAL  uint8_t

#define DCMOTOR_OK           0x00
#define DCMOTOR_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define DCMOTOR_DEF_FREQ     20000
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

    digital_out_t  slp;
    digital_out_t  sl1;
    digital_out_t  sl2;

    // Input pins 

    digital_in_t  flt;
    
    // Modules 

    pwm_t pwm;

    // ctx variable 

    uint16_t pwm_period;
    uint32_t  pwm_freq;

} dcmotor_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t  slp;
    pin_name_t  sl1;
    pin_name_t  sl2;
    pin_name_t  flt;

    // static variable 

    uint32_t  dev_pwm_freq;

} dcmotor_cfg_t;

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
void dcmotor_cfg_setup ( dcmotor_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param dcmotor Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DCMOTOR_RETVAL dcmotor_init ( dcmotor_t *ctx, dcmotor_cfg_t *cfg );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void dcmotor_set_duty_cycle ( dcmotor_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void dcmotor_pwm_stop ( dcmotor_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void dcmotor_pwm_start ( dcmotor_t *ctx );

/**
 * @brief Enable the motor function.
 *
 * @param ctx  Click object.
 *
 * @description This function enable the motor.
 */
 void dcmotor_enable ( dcmotor_t *ctx );

 /**
 * @brief Set sleep mode function.
 *
 * @param ctx  Click object.
 *
 * @description This function set sleep mode the motor.
 */
 void dcmotor_sleep_mode ( dcmotor_t *ctx );

 /**
 * @brief Select left direction, fast decay function.
 *
 * @param ctx  Click object.
 *
 * @description Function select left direction, fast decay speed.
 */
 void dcmotor_left_direction_fast ( dcmotor_t *ctx );

 /**
 * @brief Select right direction, fast decay function.
 *
 * @param ctx  Click object.
 *
 * @description Function select right direction, fast decay speed.
 */
 void dcmotor_right_direction_fast ( dcmotor_t *ctx );

 /**
 * @brief Select left direction, slow decay function.
 *
 * @param ctx  Click object.
 *
 * @description Function select left direction, slow decay speed.
 */
void dcmotor_left_direction_slow ( dcmotor_t *ctx );

 /**
 * @brief Select right direction, slow decay function.
 *
 * @param ctx  Click object.
 *
 * @description Function select right direction, slow decay speed.
 */
 void dcmotor_right_direction_slow ( dcmotor_t *ctx );

 /**
 * @brief Get diagnostic function.
 *
 * @param ctx  Click object.
 *
 * @description Function get diagnostic by return state of pin.
 */
 uint8_t dcmotor_get_diagnostic ( dcmotor_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _DCMOTOR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
