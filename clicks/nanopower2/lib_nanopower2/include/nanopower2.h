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
 * \brief This file contains API for Nano Power 2 Click driver.
 *
 * \addtogroup nanopower2 Nano Power 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NANOPOWER2_H
#define NANOPOWER2_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
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
#define NANOPOWER2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.out= MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define NANOPOWER2_OK           0
#define NANOPOWER2_ERROR       -1
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
    digital_in_t out;

} nanopower2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{

    pin_name_t out;

} nanopower2_cfg_t;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void nanopower2_cfg_setup ( nanopower2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param nanopower2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t nanopower2_init ( nanopower2_t *ctx, nanopower2_cfg_t *cfg );

/**
 * @brief Click Check Output function.
 *
 * @param ctx  Click object.
 *
 * @details This function checks the output of the Nano Power 2 Click.
 *
 * @returns Out pin value
 */
uint8_t nanopower2_check_output ( nanopower2_t* ctx );

#ifdef __cplusplus
}
#endif
#endif  // _NANOPOWER2_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
