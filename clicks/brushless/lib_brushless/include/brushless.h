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
 * \brief This file contains API for Brushless Click driver.
 *
 * \addtogroup brushless Brushless Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BRUSHLESS_H
#define BRUSHLESS_H

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
#include "drv_analog_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define BRUSHLESS_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.dir     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BRUSHLESS_RETVAL  uint8_t

#define BRUSHLESS_OK           0x00
#define BRUSHLESS_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define BRUSHLESS_DEF_FREQ     5000
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Analog data type 
 */
typedef  uint16_t brushless_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t dir;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    pwm_t pwm;
    analog_in_t adc;

    // ctx variable 

    uint32_t pwm_freq;

} brushless_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    pin_name_t an_pin;
    
    // Additional gpio pins 

    pin_name_t dir;
    pin_name_t int_pin;

    // static variable 

    uint32_t              dev_pwm_freq;
 
    analog_in_resolution_t  resolution;
    float                 vref;

} brushless_cfg_t;

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
void brushless_cfg_setup ( brushless_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BRUSHLESS_RETVAL brushless_init ( brushless_t *ctx, brushless_cfg_t *cfg );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void brushless_set_duty_cycle ( brushless_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void brushless_pwm_stop ( brushless_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void brushless_pwm_start ( brushless_t *ctx );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function read ADC data.
 */
brushless_data_t brushless_generic_read ( brushless_t *ctx );

/**
 * @brief Spin motor clockwise function.
 *
 * @param ctx        Click object.
 *
 * @description This function sets the spin direction of the motor to clockwise.
 */
void brushless_spin_clockwise ( brushless_t *ctx );

/**
 * @brief Spin motor counter clockwise function.
 *
 * @param ctx        Click object.
 *
 * @description This function sets the spin direction of the motor to counter clockwise.
 */
void brushless_spin_counter_clockwise ( brushless_t *ctx );

/**
 * @brief Read rotation speed sensor output function.
 *
 * @param ctx        Click object.
 *
 * @description This function reads the digital input of the INT pin.
 */
uint8_t brushless_read_rotation_speed_sensor_output ( brushless_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BRUSHLESS_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
