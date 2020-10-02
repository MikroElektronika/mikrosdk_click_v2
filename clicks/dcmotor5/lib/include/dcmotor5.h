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
 * \brief This file contains API for DC MOTOTR 5 Click driver.
 *
 * \addtogroup dcmotor5 DC MOTOTR 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DCMOTOR5_H
#define DCMOTOR5_H

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
#define DCMOTOR5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.snso = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.sleep = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.fault = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DCMOTOR5_RETVAL  uint8_t

#define DCMOTOR5_OK           0x00
#define DCMOTOR5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define DCMOTOR5_DEF_FREQ     20000
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

    digital_out_t sleep;
    digital_out_t in2;
    digital_out_t in1;

    // Input pins 

    digital_in_t snso;
    digital_in_t fault;
    
    // Modules 

    pwm_t pwm;

    // ctx variable 

    uint16_t pwm_period;
    uint32_t  pwm_freq;

} dcmotor5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t snso;
    pin_name_t sleep;
    pin_name_t fault;
    pin_name_t in2;

    // static variable 

    uint32_t  dev_pwm_freq;

} dcmotor5_cfg_t;

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
void dcmotor5_cfg_setup ( dcmotor5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param dcmotor5 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DCMOTOR5_RETVAL dcmotor5_init ( dcmotor5_t *ctx, dcmotor5_cfg_t *cfg );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void dcmotor5_set_duty_cycle ( dcmotor5_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void dcmotor5_pwm_stop ( dcmotor5_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void dcmotor5_pwm_start ( dcmotor5_t *ctx );

/**
 * @brief Enable the engine function
 *
 * @param ctx  Click object.
 * 
 * @description Function enables the engine by setting SLEEP ( RST ) pin on DC Motor 5 Click board.
 */
void dcmotor5_enable ( dcmotor5_t *ctx );

/**
 * @brief Disable the engine function
 *
 * @param ctx  Click object.
 * 
 * @description Function disables the engine by clearing SLEEP ( RST ) pin on DC Motor 5 Click board.
 */
void dcmotor5_standby ( dcmotor5_t *ctx );

/**
 * @brief Set the direction of rotation in the counter clockwise direction function
 *
 * @param ctx  Click object.
 * 
 * @description Function sets the direction of rotation in the counter clockwise direction
 * by clearing IN1 ( PWM ) pin and seting IN2 ( INT ) pin on DC Motor 5 Click board.
 */
void dcmotor5_counter_clockwise ( dcmotor5_t *ctx );

/**
 * @brief Set the direction of rotation in the clockwise direction function
 *
 * @param ctx  Click object.
 * 
 * @description Function sets the direction of rotation in the clockwise direction
 * by seting IN1 ( PWM ) pin and claering IN2 ( INT ) pin on DC Motor 5 Click board.
 */
void dcmotor5_clockwise ( dcmotor5_t *ctx );

/**
 * @brief Brake the engine function
 *
 * @param ctx  Click object.
 * 
 * @description Function brakes the engine by sets IN1 ( PWM ) and IN2 ( INT ) pins on DC Motor 5 Click board.
 */
void dcmotor5_short_brake ( dcmotor5_t *ctx );

/**
 * @brief Stop the engine function
 *
 * @param ctx  Click object.
 * 
 * @description Function stops the engine by clearing IN1 ( PWM ) and IN2 ( INT ) pins on DC Motor 5 Click board.
 */
void dcmotor5_stop ( dcmotor5_t *ctx );

/**
 * @brief Get fault conditions state function
 *
 * @param ctx  Click object.
 * 
 * @return fault conditions state:
 * <pre>
 *  - 0 : ok condition;
 *  - 1 : ERROR;
 * </pre>
 *
 * @description Function returns fault condition state, state of CS pin on DC Motor 5 Click board.
 */
uint8_t dcmotor5_get_fault_conditions ( dcmotor5_t *ctx );

/**
 * @brief Get sense comparator state function
 *
 * @param ctx  Click object. 
 * 
 * @return fault conditions state:
 * <pre>
 *  - 0 : drive current hits the current chopping threshold;
 *  - 1 : ERROR;
 * </pre>
 * 
 * @desription Function returns sense comparator state, state of AN pin on DC Motor 5 Click board.
 */
uint8_t dcmotor5_get_sense_comparator ( dcmotor5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _DCMOTOR5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
