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
 * \brief This file contains API for Keylock Click driver.
 *
 * \addtogroup keylock Keylock Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef KEYLOCK_H
#define KEYLOCK_H

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
#define KEYLOCK_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.out1= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.out2= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.out3= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define KEYLOCK_RETVAL            uint8_t

#define KEYLOCK_OK                0x00
#define KEYLOCK_INIT_ERROR        0xFF
/** \} */

/**
 * \defgroup key_position Key Position
 * \{
 */
#define KEYLOCK_KEY_POS_1         1
#define KEYLOCK_KEY_POS_2         2
#define KEYLOCK_KEY_POS_3         3
/** \} */

/**
 * \defgroup error_flag Error Flag
 * \{
 */
#define KEYLOCK_ERROR_FLAG        0
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
    // Input pins 

    digital_in_t out1;
    digital_in_t out2;
    digital_in_t out3;

} keylock_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t out1;
    pin_name_t out2;
    pin_name_t out3;

} keylock_cfg_t;

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
void keylock_cfg_setup ( keylock_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param keylock Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
KEYLOCK_RETVAL keylock_init ( keylock_t *ctx, keylock_cfg_t *cfg );

/**
 * @brief Checks pin state.
 *
 * @param ctx Click object.
 * @param pin 8-bit data that defines which pins state should be checked.
 * 
 * @returns value that represent the state of a chosen pin or an error flag if pin is not chosen corectly.
 *
 * @description Function is used to check the state of the pin chosen by the user.
 *
 * @note In order for function to work properly use: 
 *       - 1 : To check AN pin state
 *       - 2 : To check PWM pin state
 *       - 3 : To check INT pin state
 *       - Any other value will cause function to return an error flag.
 */
uint8_t keylock_check_pin ( keylock_t *ctx, uint8_t pin );

/**
 * @brief Gets key position.
 *
 * @param ctx Click object.
 * 
 * @returns value that represent the current position of the key.
 *
 * @description Function is used to check in which position the key currently is.
 */
uint8_t keylock_get_position ( keylock_t *ctx );

/**
 * @brief Checks AN pin state.
 *
 * @param ctx Click object.
 * 
 * @returns 0 pin State is not set.
 * @returns 1 Pin State is set.
 *
 * @description Function checks the state of AN pin.
 */
uint8_t keylock_check_an_state ( keylock_t *ctx );

/**
 * @brief Checks PWM pin state.
 *
 * @param ctx Click object.
 * 
 * @returns 0 pin State is not set.
 * @returns 1 Pin State is set.
 *
 * @description Function checks the state of PWM pin.
 */
uint8_t keylock_check_pwm_state ( keylock_t *ctx );

/**
 * @brief Checks INT pin state.
 *
 * @param ctx Click object.
 * 
 * @returns 0 pin State is not set.
 * @returns 1 Pin State is set.
 *
 * @description Function checks the state of INT pin.
 */
uint8_t keylock_check_int_state ( keylock_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _KEYLOCK_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
