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
 * \brief This file contains API for 7-SEG RGB Click driver.
 *
 * \addtogroup c7segrgb 7-SEG RGB Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C7SEGRGB_H
#define C7SEGRGB_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define C7SEGRGB_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C7SEGRGB_OK             0
#define C7SEGRGB_ERROR         -1
/** \} */

/**
 * \defgroup C7SEGRGB_variables C7SEGRGB Variables
 * \{
 */
#define C7SEGRGB_ONE            0x06
#define C7SEGRGB_TWO            0x5B
#define C7SEGRGB_THREE          0x4F
#define C7SEGRGB_FOUR           0x66
#define C7SEGRGB_FIVE           0x6D
#define C7SEGRGB_SIX            0x7D
#define C7SEGRGB_SEVEN          0x07
#define C7SEGRGB_EIGHT          0x7F
#define C7SEGRGB_NINE           0x6F
#define C7SEGRGB_ZERO           0x3F
#define C7SEGRGB_POINT          0x80
/** \} */

/**
 * @brief Function pointer for logic level one and zero
 */
typedef void ( *drv_logic_t ) ( void );

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click segments data.
 */
typedef struct
{
    uint8_t logic_lvl;
    uint8_t green;
    uint8_t red;
    uint8_t blue;

} c7segrgb_segment_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 
    digital_out_t cs;
    digital_out_t pwm;

    // Function pointers for logic zero and logic one
    drv_logic_t logic_zero;
    drv_logic_t logic_one;
    
    // Segments data array of 8 items for each segment
    c7segrgb_segment_t segments[ 8 ];

} c7segrgb_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 
    pin_name_t cs;
    pin_name_t pwm;
    
    // Function pointers for logic zero and logic one
    drv_logic_t logic_zero;
    drv_logic_t logic_one;

} c7segrgb_cfg_t;

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
void c7segrgb_cfg_setup ( c7segrgb_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c7segrgb Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t c7segrgb_init ( c7segrgb_t *ctx, c7segrgb_cfg_t *cfg );

/**
 * @brief Sets the state low of CS pin function
 *
 * @param ctx  Click object.
 * 
 * @description The function sets the state low of CS pin on 7-SEG RGB Click board.
 */
void c7segrgb_cs_low ( c7segrgb_t *ctx );

/**
 * @brief Sets the state high of CS pin function
 * 
 * @param ctx  Click object.
 *
 * @description The function sets the state high of CS pin on 7-SEG RGB Click board.
 */
void c7segrgb_cs_high ( c7segrgb_t *ctx );

/**
 * @brief Sets the state low of PWM pin function
 * 
 * @param ctx  Click object.
 *
 * @description The function sets the state low of PWM pin on 7-SEG RGB Click board.
 */
void c7segrgb_pwm_low ( c7segrgb_t *ctx );

/**
 * @brief Sets the state high of PWM pin function
 * 
 * @param ctx  Click object.
 *
 * @description The function sets the state high of PWM pin on 7-SEG RGB Click board.
 */
void c7segrgb_pwm_high ( c7segrgb_t *ctx );

/**
 * @brief Sets the character and its color function
 * 
 * @param ctx               Click object.
 * @param character         Char to be written.
 * @param green_brightness  Green color brightness.
 * @param red_brightness    Red color brightness.
 * @param blue_brightness   Blue color brightness.
 *
 * <pre> 
 *  character: 
 *        0x06 - 0
 *        0x5B - 1
 *        0x4F - 2
 *        0x66 - 3
 *        0x6D - 4
 *        0x7D - 5
 *        0x07 - 6
 *        0x7F - 7
 *        0x6F - 8
 *        0x3F - 9
 *        0x80 - .
 *  </pre> 
 * 
 * @description The function sets character and its color.
 */
void c7segrgb_set_num ( c7segrgb_t *ctx, uint8_t character, uint8_t green_brightness, 
                        uint8_t red_brightness, uint8_t blue_brightness );

/**
 * @brief Sets all segments data.
 * 
 * @param ctx  Click object.
 *
 * @description The function sets the state and color of every segment from click board object segment array data.
 */
void c7segrgb_set_seven_seg ( c7segrgb_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C7SEGRGB_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
