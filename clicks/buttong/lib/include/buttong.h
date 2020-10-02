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
 * \brief This file contains API for Button G  Click driver.
 *
 * \addtogroup buttong Button G  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUTTONG_H
#define BUTTONG_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define BUTTONG_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin= MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUTTONG_RETVAL  uint8_t

#define BUTTONG_OK           0x00
#define BUTTONG_INIT_ERROR   0xFF
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

    digital_out_t pwm;

    // Input pins 

    digital_in_t int_pin;

} buttong_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t pwm;
    pin_name_t int_pin;

} buttong_cfg_t;

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
void buttong_cfg_setup ( buttong_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buttong Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUTTONG_RETVAL buttong_init ( buttong_t *ctx, buttong_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Button G  click.
 */
void buttong_default_cfg ( buttong_t *ctx );

/**
 * @brief Press state.
 *
 * @param ctx  Click object.
 * 
 * @returns    State of the pin.
 *
 * @description This function is detecting button press state.
 */
uint8_t buttong_press_button( buttong_t *ctx );

/**
 * @brief Light on.
 *
 * @param ctx  Click object.
 *
 * @description This function turns on light on the button.
 */
void buttong_turn_on_led( buttong_t *ctx );

/**
 * @brief Light off.
 *
 * @param ctx  Click object.
 *
 * @description This function turns on light off the button.
 */
void buttong_turn_off_led( buttong_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BUTTONG_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
