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
 * \brief This file contains API for Audio Xover Click driver.
 *
 * \addtogroup audioxover Audio Xover Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AUDIOXOVER_H
#define AUDIOXOVER_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define AUDIOXOVER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.sdn = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AUDIOXOVER_RETVAL  uint8_t

#define AUDIOXOVER_OK           0x00
#define AUDIOXOVER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup switch Switch
 * \{
 */
#define AUDIOXOVER_ENABLE      0
#define AUDIOXOVER_DISABLE     1
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

    digital_out_t sdn;

} audioxover_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t sdn;

} audioxover_cfg_t;

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
void audioxover_cfg_setup ( audioxover_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param audioxover Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AUDIOXOVER_RETVAL audioxover_init ( audioxover_t *ctx, audioxover_cfg_t *cfg );

/**
 * @brief Device power on function.
 *
 * @param ctx  Click object.
 * 
 * @description This function enables the click board by setting SDN pin to HIGH logic state.
 */
void audioxover_power_on ( audioxover_t *ctx );

/**
 * @brief Device shut down function.
 *
 * @param ctx  Click object.
 * 
 * @description This function disables the click board by setting SDN pin to LOW logic state.
 */
void audioxover_shut_down ( audioxover_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AUDIOXOVER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
