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
 * \brief This file contains API for BI HALL Click driver.
 *
 * \addtogroup bihall BI HALL Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BIHALL_H
#define BIHALL_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define BIHALL_MAP_MIKROBUS( cfg, mikrobus )     \
  cfg.int_pin= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BIHALL_RETVAL  uint8_t

#define BIHALL_OK           0x00
#define BIHALL_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup det_mag_field Detecting south & north pole magnetic field
 * \{
 */

#define BIHALL_MAG_POLE_NORTH    0
#define BIHALL_MAG_POLE_SOUTH    1
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

    digital_in_t int_pin;

} bihall_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t int_pin;

} bihall_cfg_t;

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
 * @description This function initializes click configuration
 * structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void bihall_cfg_setup ( bihall_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param bihall Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins
 * and peripherals used for this click.
 */
BIHALL_RETVAL bihall_init ( bihall_t *ctx, bihall_cfg_t *cfg );

/**
 * @brief Detecting south & north pole magnetic fields status function.
 *
 * @param ctx  Click object.
 * 
 * @return State of INT pin:
 * <pre > 0 : north pole magnetic fields; </pre>
 * <pre > 1 : south pole magnetic fields; </pre>
 *
 * @description This function detecting 
 * south & north pole magnetic fields status
 * and returns the state of the INT pin.
 * INT pin can be configured to show are data registers
 * updated with the new values or not.
 */
uint8_t bihall_det_mag_field ( bihall_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _BIHALL_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
