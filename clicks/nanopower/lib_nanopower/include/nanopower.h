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
 * \brief This file contains API for Nano Power Click driver.
 *
 * \addtogroup nanopower Nano Power Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NANOPOWER_H
#define NANOPOWER_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

#define NANOPW_ENABLE_DEVICE           1
#define NANOPW_DISABLE_DEVICE          0

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define NANOPOWER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.en= MIKROBUS( mikrobus, MIKROBUS_CS ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define NANOPOWER_RETVAL  uint8_t

#define NANOPOWER_OK           0x00
#define NANOPOWER_INIT_ERROR   0xFF
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
    
    digital_out_t  en;
    
} nanopower_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    
    pin_name_t  en;
    
} nanopower_cfg_t;

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
void nanopower_cfg_setup ( nanopower_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param nanopower Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
NANOPOWER_RETVAL nanopower_init ( nanopower_t *ctx, nanopower_cfg_t *cfg );

/**
 * @brief Click Enable function.
 *
 * @param ctx  Click object.
 * 
 * @param state State.
 *
 * @description This function enables the Nano Power Click.
 */
void nanopw_enable_device ( nanopower_t *ctx, const uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _NANOPOWER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
