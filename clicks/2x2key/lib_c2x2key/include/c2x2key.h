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
 * \brief This file contains API for 2x2 key Click driver.
 *
 * \addtogroup c2x2key 2x2 key Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C2X2KEY_H
#define C2X2KEY_H

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
#define C2X2KEY_MAP_MIKROBUS( cfg, mikrobus )    \
  cfg.t1o  = MIKROBUS( mikrobus, MIKROBUS_AN );  \
  cfg.t2o  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.t3o  = MIKROBUS( mikrobus, MIKROBUS_CS );  \
  cfg.t4o  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.tint = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C2X2KEY_RETVAL  uint8_t

#define C2X2KEY_OK           0x00
#define C2X2KEY_INIT_ERROR   0xFF
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

    digital_in_t t1o;
    digital_in_t t2o;
    digital_in_t t3o;
    digital_in_t t4o;
    digital_in_t tint;

} c2x2key_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t t1o;
    pin_name_t t2o;
    pin_name_t t3o;
    pin_name_t t4o;
    pin_name_t tint;

} c2x2key_cfg_t;

/** \} */ // End types group

// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */ 
 

/** \} */ // End constants group

// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


/** \} */ // End variable group

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
void c2x2key_cfg_setup ( c2x2key_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c2x2key Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C2X2KEY_RETVAL c2x2key_init ( c2x2key_t *ctx, c2x2key_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 2x2 key click.
 */
void c2x2key_default_cfg ( c2x2key_t *ctx );

/**
 * @brief Taster 1 state function.
 *
 * @param ctx  Click object.
 * 
 * @return     
 * - 1 : Key 1 pressed
 * - 0 : Key 1 is not pressed
 * 
 * @description This function gets state of T1O pin on 2X2_Key Click board.
 */
uint8_t c2x2key_t1_state ( c2x2key_t *ctx );

/**
 * @brief Taster 2 state function.
 *
 * @param ctx  Click object.
 * 
 * @return     
 * - 1 : Key 2 pressed
 * - 0 : Key 2 is not pressed
 * 
 * @description This function gets state of T2O pin on 2X2_Key Click board.
 */
uint8_t c2x2key_t2_state ( c2x2key_t *ctx );

/**
 * @brief Taster 3 state function.
 *
 * @param ctx  Click object.
 * 
 * @return     
 * - 1 : Key 3 pressed
 * - 0 : Key 3 is not pressed
 * 
 * @description This function gets state of T3O pin on 2X2_Key Click board.
 */
uint8_t c2x2key_t3_state ( c2x2key_t *ctx );

/**
 * @brief Taster 4 state function.
 *
 * @param ctx  Click object.
 * 
 * @return     
 * - 1 : Key 4 pressed
 * - 0 : Key 4 is not pressed
 * 
 * @description This function gets state of T4O pin on 2X2_Key Click board.
 */
uint8_t c2x2key_t4_state ( c2x2key_t *ctx );

/**
 * @brief Taster Pressed function.
 *
 * @param ctx  Click object.
 * 
 * @return     
 * - 1 : Any key pressed
 * - 0 : Any key is not pressed
 * 
 * @description This function gets state of TINT pin on 2X2_Key Click board.
 */
uint8_t c2x2key_taster_pressed ( c2x2key_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C2X2KEY_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
