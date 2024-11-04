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
 * \brief This file contains API for DC Motor 4 Click driver.
 *
 * \addtogroup dcmotor4 DC Motor 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DCMOTOR4_H
#define DCMOTOR4_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define DCMOTOR4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DCMOTOR4_RETVAL  uint8_t

#define DCMOTOR4_OK           0x00
#define DCMOTOR4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define DCMOTOR4_DEF_FREQ    10000
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

    digital_out_t dir;
    digital_out_t en;

    // Input pins 

    digital_in_t flt;
    
    // Modules 

    pwm_t pwm;

    // ctx variable 

    uint32_t  pwm_freq;

} dcmotor4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t dir;
    pin_name_t en;
    pin_name_t flt;

    // static variable 

    uint32_t  dev_pwm_freq;

} dcmotor4_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void dcmotor4_cfg_setup ( dcmotor4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param dcmotor4 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
DCMOTOR4_RETVAL dcmotor4_init ( dcmotor4_t *ctx, dcmotor4_cfg_t *cfg );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void dcmotor4_set_duty_cycle ( dcmotor4_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void dcmotor4_pwm_stop ( dcmotor4_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void dcmotor4_pwm_start ( dcmotor4_t *ctx );

/**
 * @brief Run clockwise.
 *
 * @param ctx  Click object.
 *
 * @description This function runs clockwise.
 */
void dcmotor4_run_clockwise ( dcmotor4_t *ctx );

/**
 * @brief Run counter clockwise.
 *
 * @param ctx  Click object.
 *
 * @description This function run counter clockwise.
 */
void dcmotor4_run_counter_clockwise ( dcmotor4_t *ctx );

/**
 * @brief Enable motor.
 *
 * @param ctx  Click object.
 *
 * @description This function enables motor.
 */
void dcmotor4_enable_motor ( dcmotor4_t *ctx );

/**
 * @brief Disable motor.
 *
 * @param ctx  Click object.
 *
 * @description This function disables motor.
 */
void dcmotor4_disable_motor ( dcmotor4_t *ctx );

/**
 * @brief Get diagnostic.
 *
 * @param ctx  Click object.
 *
 * @description This function gets diagnostic.
 */
uint8_t dcmotor4_get_diagnostic ( dcmotor4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _DCMOTOR4_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
