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
 * \brief This file contains API for Brushless 6 Click driver.
 *
 * \addtogroup brushless6 Brushless 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BRUSHLESS6_H
#define BRUSHLESS6_H

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
#define BRUSHLESS6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  

  //cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BRUSHLESS6_RETVAL  uint8_t

#define BRUSHLESS6_OK           0x00
#define BRUSHLESS6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define BRUSHLESS6_DEF_FREQ     500
/** \} */

/**
 * \defgroup speed  Speed
 * \{
 */
#define BRUSHLESS6_COEF                 1.0 / ( ( 1000000.0 / BRUSHLESS6_DEF_FREQ ) / 0.3048 )  
#define BRUSHLESS6_MIN_PWM_DC     BRUSHLESS6_COEF * 2000.0
#define BRUSHLESS6_INIT_DC             BRUSHLESS6_COEF * 4855.0
#define BRUSHLESS6_1MS_DC              BRUSHLESS6_MIN_PWM_DC / 0.608
#define BRUSHLESS6_2MS_DC              BRUSHLESS6_1MS_DC * 2.0
#define BRUSHLESS6_PERIOD               BRUSHLESS6_1MS_DC / 10.0
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

} brushless6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;

    // static variable 

    uint32_t  dev_pwm_freq;

} brushless6_cfg_t;

/** \} */ // End types group
 
 

/** \} */ // End constants group

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
void brushless6_cfg_setup ( brushless6_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param brushless6 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BRUSHLESS6_RETVAL brushless6_init ( brushless6_t *ctx, brushless6_cfg_t *cfg );


/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void brushless6_set_duty_cycle ( brushless6_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void brushless6_pwm_stop ( brushless6_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void brushless6_pwm_start ( brushless6_t *ctx );

/**
 * @brief GPIO Only Drivers - remove in other cases
 *
 * @param ctx  Click object.
 *
 */
void brushless6_gpio_driver_init ( brushless6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BRUSHLESS6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
