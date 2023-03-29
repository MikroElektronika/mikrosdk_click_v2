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
 * \brief This file contains API for Power Reset Click driver.
 *
 * \addtogroup powerreset Power Reset Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef POWERRESET_H
#define POWERRESET_H

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
#define POWERRESET_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.sta= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.rst= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define POWERRESET_RETVAL  uint8_t
#define powerreset_state_t uint8_t

#define POWERRESET_OK           0x00
#define POWERRESET_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup state State
 * \{
 */
#define POWERRESET_ACTIVE         1
#define POWERRESET_INACTIVE       0
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

    digital_in_t sta;
    digital_in_t rst;

} powerreset_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t sta;
    pin_name_t rst;

} powerreset_cfg_t;

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
void powerreset_cfg_setup ( powerreset_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param powerreset Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
POWERRESET_RETVAL powerreset_init ( powerreset_t *ctx, powerreset_cfg_t *cfg );

/**
 * @brief Power Check function.
 *
 * @param ctx  Click object.
 * 
 * @returns 0 - inactive, 1 - active state
 *
 * @description This function returns a state of the PWR pin.
 */
powerreset_state_t powerreset_get_pwr( powerreset_t *ctx );

 /**
 * @brief Reset Check function.
 *
 * @param ctx  Click object.
 * 
 * @returns 0 - inactive, 1 - active state
 *
 * @description This function returns a state of the RST pin.
 */
powerreset_state_t powerreset_get_rst( powerreset_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _POWERRESET_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
