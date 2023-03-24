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
 * \brief This file contains API for Stretch Click driver.
 *
 * \addtogroup stretch Stretch Click Driver
 * @{
 */


#ifndef STRETCH_H
#define STRETCH_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
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
#define STRETCH_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define STRETCH_RETVAL  uint8_t

#define STRETCH_OK           0x00
#define STRETCH_INIT_ERROR   0xFF
/** \} */

/** \} */ //  End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Analog data type 
 */
typedef  uint16_t stretch_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t pwm;
    
    // Modules 

    analog_in_t adc;

} stretch_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t an_pin;
    
    // Additional gpio pins 

    pin_name_t pwm;
   

    // static variable 

    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef     

} stretch_cfg_t;

/** \} */ // End types group

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
void stretch_cfg_setup ( stretch_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
STRETCH_RETVAL stretch_init ( stretch_t *ctx, stretch_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Stretch click.
 */
void stretch_default_cfg ( stretch_t *ctx );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function read ADC data.
 */
stretch_data_t stretch_generic_read ( stretch_t *ctx );

 /**
 * @brief Turn on the LED function
 *
 * @param ctx        Click object
 * Function turn on the LED by set PWM pin
 * on Stretch click board.
*/
void stretch_turn_on_led( stretch_t *ctx );

/**
 * @brief Turn off the LED function
 *
 * @param ctx        Click object
 * Function turn off the LED by clear PWM pin
 * on Stretch click board.
*/
void stretch_turn_off_led( stretch_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _STRETCH_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
