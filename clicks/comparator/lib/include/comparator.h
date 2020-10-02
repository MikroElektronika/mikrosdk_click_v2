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
 * \brief This file contains API for Comparator Click driver.
 *
 * \addtogroup comparator Comparator Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef COMPARATOR_H
#define COMPARATOR_H

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
#define COMPARATOR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.o1 = MIKROBUS( mikrobus, MIKROBUS_AN );    \
  cfg.o2 = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define COMPARATOR_RETVAL  uint8_t

#define COMPARATOR_OK                            0x00
#define COMPARATOR_INIT_ERROR                    0xFF
/** \} */

/**
 * \defgroup cmp_state Comparator State
 * \{
 */
#define COMPARATOR_STATE_LOW                     0x00
#define COMPARATOR_STATE_HIGH                    0x01
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

    digital_in_t o1;
    digital_in_t o2;

} comparator_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t o1;
    pin_name_t o2;

} comparator_cfg_t;

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
 * @param cfg                 Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void comparator_cfg_setup ( comparator_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param comparator          Click object.
 * @param cfg                 Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
COMPARATOR_RETVAL comparator_init ( comparator_t *ctx, comparator_cfg_t *cfg );

/**
 * @brief Check state of the o1 pin function.
 *
 * @param ctx                 Click object.
 * 
 * @return State of o1 pin:
 * <pre>
 * - 0 : Low;
 * - 1 : High;
 * </pre>
 *
 * @description This function check and return state of the o1 ( AN ) pin of Comparator Click Board.
 */
uint8_t comparator_check_output_one ( comparator_t *ctx );

/**
 * @brief Check state of the o2 pin function.
 *
 * @param ctx                 Click object.
 * 
 * @return State of o1 pin:
 * <pre>
 * - 0 : Low;
 * - 1 : High;
 * </pre>
 *
 * @description This function check and return state of the o2 ( INT ) pin of Comparator Click Board.
 */
uint8_t comparator_check_output_two ( comparator_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _COMPARATOR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
