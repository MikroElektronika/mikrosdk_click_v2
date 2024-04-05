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
 * \brief This file contains API for DC Motor 2 Click driver.
 *
 * \addtogroup dcmotor2 DC Motor 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DCMOTOR2_H
#define DCMOTOR2_H

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
#define DCMOTOR2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.slp = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DCMOTOR2_RETVAL  uint8_t

#define DCMOTOR2_OK           0x00
#define DCMOTOR2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define DCMOTOR2_DEF_FREQ     160000
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

    digital_out_t in2;
    digital_out_t in1;
    digital_out_t slp;
    
    // Modules 

    pwm_t pwm;

    // ctx variable 

    uint32_t  pwm_freq;

} dcmotor2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t in2;
    pin_name_t in1;
    pin_name_t slp;

    // static variable 

    uint32_t  dev_pwm_freq;

} dcmotor2_cfg_t;

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
void dcmotor2_cfg_setup ( dcmotor2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param dcmotor2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DCMOTOR2_RETVAL dcmotor2_init ( dcmotor2_t *ctx, dcmotor2_cfg_t *cfg );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void dcmotor2_set_duty_cycle ( dcmotor2_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void dcmotor2_pwm_stop ( dcmotor2_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void dcmotor2_pwm_start ( dcmotor2_t *ctx );

/**
 * @brief Enable motor.
 *
 * @param ctx  Click object.
 *
 * @description This function sends a high digital output on the SLP pin and enables the motor.
 */
void dcmotor2_enable_motor ( dcmotor2_t *ctx );

/**
 * @brief Disable motor.
 *
 * @param ctx  Click object.
 *
 * @description This function sends a low digital output on the SLP pin and disables the motor.
 */
void dcmotor2_disable_motor ( dcmotor2_t *ctx );

/**
 * @brief Spin motor clockwise.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the IN1/IN2 pins to 1/0 and makes the motor spin clockwise.
 */
void dcmotor2_spin_clockwise ( dcmotor2_t *ctx );

/**
 * @brief Spin motor counter clockwise.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the IN1/IN2 pins to 0/1 and makes the motor spin counter
 *              clockwise.
 */
void dcmotor2_spin_counter_clockwise ( dcmotor2_t *ctx );

/**
 * @brief Pull motor brake.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the IN1/IN2 pins to 1/1 and forces the motor to break.
 */
void dcmotor2_pull_brake ( dcmotor2_t *ctx );

/**
 * @brief Stop motor clockwise.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the IN1/IN2 pins to 0/0 and stops the motor completely.
 */
void dcmotor2_stop_motor ( dcmotor2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _DCMOTOR2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
