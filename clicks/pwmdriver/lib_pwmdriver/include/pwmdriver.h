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
 * \brief This file contains API for Pwm Driver Click driver.
 *
 * \addtogroup pwmdriver Pwm Driver Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PWMDRIVER_H
#define PWMDRIVER_H

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
#define PWMDRIVER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PWMDRIVER_RETVAL  uint8_t

#define PWMDRIVER_OK           0x00
#define PWMDRIVER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define PWMDRIVER_DEF_FREQ     20000
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

    uint16_t pwm_period;
    uint32_t pwm_freq;

} pwmdriver_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;


    // static variable 

    uint32_t  dev_pwm_freq;

} pwmdriver_cfg_t;

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
void pwmdriver_cfg_setup ( pwmdriver_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PWMDRIVER_RETVAL pwmdriver_init ( pwmdriver_t *ctx, pwmdriver_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for PwmDriver click.
 */
void pwmdriver_default_cfg ( pwmdriver_t *ctx );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void pwmdriver_set_duty_cycle ( pwmdriver_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void pwmdriver_pwm_stop ( pwmdriver_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void pwmdriver_pwm_start ( pwmdriver_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PWMDRIVER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
