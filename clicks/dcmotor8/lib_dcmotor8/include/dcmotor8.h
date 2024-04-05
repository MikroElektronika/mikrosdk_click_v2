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
 * \brief This file contains API for DC Motor 8 Click driver.
 *
 * \addtogroup dcmotor8 DC Motor 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DCMOTOR8_H
#define DCMOTOR8_H

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
#define DCMOTOR8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DCMOTOR8_RETVAL  uint8_t

#define DCMOTOR8_OK           0x00
#define DCMOTOR8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup enable_or_disable_the_device Enable or disable the device
 * \{
 */
#define DCMOTOR8_ENABLE       1
#define DCMOTOR8_DISABLE      0
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define DCMOTOR8_DEF_FREQ     20000
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

    digital_out_t en;
    
    // Modules 

    pwm_t pwm;

    // ctx variable 

    uint32_t  pwm_freq;

} dcmotor8_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t en;

    // static variable 

    uint32_t  dev_pwm_freq;

} dcmotor8_cfg_t;

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
void dcmotor8_cfg_setup ( dcmotor8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DCMOTOR8_RETVAL dcmotor8_init ( dcmotor8_t *ctx, dcmotor8_cfg_t *cfg );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void dcmotor8_set_duty_cycle ( dcmotor8_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void dcmotor8_pwm_stop ( dcmotor8_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void dcmotor8_pwm_start ( dcmotor8_t *ctx );

/**
 * @brief Enable function.
 *
 * @param ctx     Click object.
 * @param state   0 or 1  :  Desired state to be set to EN pin
 *
 * @description This function sets EN pin state.
 */
void dcmotor8_enable ( dcmotor8_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _DCMOTOR8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
