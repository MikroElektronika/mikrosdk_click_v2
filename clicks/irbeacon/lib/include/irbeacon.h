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
 * \brief This file contains API for IR Beacon Click driver.
 *
 * \addtogroup irbeacon IR Beacon Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRBEACON_H
#define IRBEACON_H

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
#define IRBEACON_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.mod = MIKROBUS( mikrobus, MIKROBUS_AN ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IRBEACON_RETVAL  uint8_t

#define IRBEACON_OK           0x00
#define IRBEACON_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define IRBEACON_DEF_FREQ     5000
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

    digital_out_t mod;
    
    // Modules 

    pwm_t pwm;

    // ctx variable 

    uint16_t pwm_period;
    uint32_t  pwm_freq;

} irbeacon_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t mod;


    // static variable 

    uint32_t  dev_pwm_freq;

} irbeacon_cfg_t;

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
void irbeacon_cfg_setup ( irbeacon_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param irbeacon Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
IRBEACON_RETVAL irbeacon_init ( irbeacon_t *ctx, irbeacon_cfg_t *cfg );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void irbeacon_set_duty_cycle ( irbeacon_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void irbeacon_pwm_stop ( irbeacon_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void irbeacon_pwm_start ( irbeacon_t *ctx );

/**
 * @brief Enable MOD function
 *
 * @param ctx  Click object.
 * 
 * @description Function enables the device by seting MOD pin.
**/
void irbeacon_enable_mod ( irbeacon_t *ctx );

/**
 * @brief Disable MOD function
 *
 * @param ctx  Click object.
 * 
 * @description Function disables the device by clearing MOD pin.
**/
void irbeacon_disable_mod ( irbeacon_t *ctx );

/**
 * @brief Reset MOD function
 *
 * @param ctx  Click object.
 * 
 * @description Function resets the device.
 * @note This function has small 100ms delay.
**/
void irbeacon_reset_mod ( irbeacon_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _IRBEACON_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
