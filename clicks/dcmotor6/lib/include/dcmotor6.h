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
 * \brief This file contains API for DC MOTOR 6 Click driver.
 *
 * \addtogroup dcmotor6 DC MOTOR 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DCMOTOR6_H
#define DCMOTOR6_H

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
#define DCMOTOR6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.in1= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.in2= MIKROBUS( mikrobus, MIKROBUS_RST ); 

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DCMOTOR6_RETVAL  uint8_t

#define DCMOTOR6_OK           0x00
#define DCMOTOR6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DCMOTOR6_MOTOR_DIR_CCW     1
#define DCMOTOR6_MOTOR_DIR_CW      2
#define DCMOTOR6_MOTOR_STOP        0
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

    digital_out_t in1;
    digital_out_t in2;
  

} dcmotor6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t in1;
    pin_name_t in2;

} dcmotor6_cfg_t;

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
void dcmotor6_cfg_setup ( dcmotor6_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DCMOTOR6_RETVAL dcmotor6_init ( dcmotor6_t *ctx, dcmotor6_cfg_t *cfg );

/**
 * @brief Set IN1 pin.
 *
 * @param ctx  Click object.
 * @param state   Pin state
 */
void dcmotor6_set_in1_pin ( dcmotor6_t *ctx, uint8_t state );

/**
 * @brief Set IN1 pin.
 *
* @param ctx  Click object. 
 * @param state   Pin state
 */
void dcmotor6_set_in2_pin ( dcmotor6_t *ctx, uint8_t state );

/**
 * @brief Set motor Direction.
 *
 * @param ctx  Click object.
 * @param dir   Motor direction (CCW, CW or Stop)
 */
void dcmotor6_set_direction( dcmotor6_t *ctx, uint8_t dir );

#ifdef __cplusplus
}
#endif
#endif  // _DCMOTOR6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
