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
 * \brief This file contains API for Cap Extend 3 Click driver.
 *
 * \addtogroup capextend3 Cap Extend 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CAPEXTEND3_H
#define CAPEXTEND3_H

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
#define CAPEXTEND3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.to0= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.to1= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.to2= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.to3= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.to4= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CAPEXTEND3_RETVAL  uint8_t

#define CAPEXTEND3_OK           0x00
#define CAPEXTEND3_INIT_ERROR   0xFF
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

    digital_in_t to0;
    digital_in_t to1;
    digital_in_t to2;
    digital_in_t to3;
    digital_in_t to4;

} capextend3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t to0;
    pin_name_t to1;
    pin_name_t to2;
    pin_name_t to3;
    pin_name_t to4;

} capextend3_cfg_t;

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
void capextend3_cfg_setup ( capextend3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param capextend3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CAPEXTEND3_RETVAL capextend3_init ( capextend3_t *ctx, capextend3_cfg_t *cfg );

/**
 * @brief Function reads state of AN pin
 *
 * @param ctx  Click object.
 *
 * @return  state of AN pin       ( 1 ) - button 0 is off ( 0 ) - button 0 is on
 *
 */
uint8_t capextend3_touch_0 ( capextend3_t *ctx );

/**
 * @brief Function reads state of RST pin
 *
 * @param ctx  Click object.
 *
 * @return  state of RST pin       ( 1 ) - button 1 is off ( 0 ) - button 1 is on
 *
 */
uint8_t capextend3_touch_1 ( capextend3_t *ctx );

/**
 * @brief Function reads state of CS pin
 *
 * @param ctx  Click object.
 *
 * @return  state of CS pin       ( 1 ) - button 2 is off ( 0 ) - button 2 is on
 *
 */
uint8_t capextend3_touch_2 ( capextend3_t *ctx );

/**
 * @brief Function reads state of INT pin
 *
 * @param ctx  Click object.
 *
 * @return  state of INT pin       ( 1 ) - button 3 is off ( 0 ) - button 3 is on
 *
 */
uint8_t capextend3_touch_3 ( capextend3_t *ctx );

/**
 * @brief Function reads state of PWM pin
 *
 * @param ctx  Click object.
 *
 * @return  state of PWM pin       ( 1 ) - button 4 is off ( 0 ) - button 4 is on
 *
 */
uint8_t capextend3_touch_4 ( capextend3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _CAPEXTEND3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
