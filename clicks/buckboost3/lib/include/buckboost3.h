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
 * \brief This file contains API for Buck-Boost 3 Click driver.
 *
 * \addtogroup buckboost3 Buck-Boost 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCKBOOST3_H
#define BUCKBOOST3_H

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
#define BUCKBOOST3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.en= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.uv= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCKBOOST3_RETVAL  uint8_t

#define BUCKBOOST3_OK           0x00
#define BUCKBOOST3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup state_registers State Registers
 * \{
 */
#define BUCKBOOST3_DEVICE_ENABLE   0x01
#define BUCKBOOST3_DEVICE_DISABLE  0x00
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

    digital_out_t en;
  
    // Input pins 

    digital_in_t uv;

} buckboost3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t en;
   
    pin_name_t uv;

} buckboost3_cfg_t;

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
void buckboost3_cfg_setup ( buckboost3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buckboost3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUCKBOOST3_RETVAL buckboost3_init ( buckboost3_t *ctx, buckboost3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Buck-Boost 3 click.
 */
void buckboost3_default_cfg ( buckboost3_t *ctx );

/**
 * @brief Function for enable/disable device.
 *
 * @param ctx  Click object.
 * @param state State.
 *
 * @description This function enable/disable device.
 */
void buckboost3_enable ( buckboost3_t *ctx, uint8_t state );

/**
 * @brief Function for get Intterupt pin state.
 *
 * @param ctx  Click object.
 *
 * @return Interrupt state.
 *
 * @description This function gets intterupt pin state.
 */
uint8_t buckboost3_get_interrupt_state ( buckboost3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BUCKBOOST3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
