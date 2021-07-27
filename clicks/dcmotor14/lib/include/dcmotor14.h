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
 * \brief This file contains API for DC MOTOR 14 Click driver.
 *
 * \addtogroup dcmotor14 DC MOTOR 14 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DCMOTOR14_H
#define DCMOTOR14_H

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
#define DCMOTOR14_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.in1= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.in2= MIKROBUS( mikrobus, MIKROBUS_RST )

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DCMOTOR14_RETVAL  uint8_t

#define DCMOTOR14_OK           0x00
#define DCMOTOR14_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup 
 * \{
 */
#define DCMOTOR14_HIGH                   1
#define DCMOTOR14_LOW                    0
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

} dcmotor14_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t in1;
    pin_name_t in2;

} dcmotor14_cfg_t;

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
void dcmotor14_cfg_setup ( dcmotor14_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DCMOTOR14_RETVAL dcmotor14_init ( dcmotor14_t *ctx, dcmotor14_cfg_t *cfg );

/**
 * @brief Set an pin state function.
 *
 * @param ctx  Click object.
 * @param  state  0 - an pin cleared / 1 - an pin set
 *
 * @description This function is used to set or clear an pin.
 */
void dcmotor14_set_an_state ( dcmotor14_t *ctx, uint8_t state );

/**
 * @brief Set rst pin state function.
 *
 * @param ctx  Click object.
 * @param  state  0 - rst pin cleared / 1 - rst pin set
 *
 * @description This function is used to set or clear rst pin.
 */
void dcmotor14_set_rst_state ( dcmotor14_t *ctx, uint8_t state );

/**
 * @brief Stop function.
 *
 * @param ctx  Click object.
 * 
 * @description This function is used to stop the motor and put the device into standby mode after 1 ms.
 */
void dcmotor14_stop ( dcmotor14_t *ctx );

/**
 * @brief Forward function
 *
 * @param ctx  Click object.
 * 
 * @description This functio is used to drive the motor forward.
 */
void dcmotor14_forward ( dcmotor14_t *ctx );

/**
 * @brief Reverse function
 *
 * @param ctx  Click object.
 * 
 * @description This functio is used to drive the motor in reverse.
 */
void dcmotor14_reverse ( dcmotor14_t *ctx );

/**
 * @brief Brake function
 *
 * @param ctx  Click object.
 * 
 * @description This functio is used to brake the motor.
 */
void dcmotor14_brake ( dcmotor14_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _DCMOTOR14_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
