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
 * \brief This file contains API for Hall Switch Click driver.
 *
 * \addtogroup hallswitch Hall Switch Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HALLSWITCH_H
#define HALLSWITCH_H

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
#define HALLSWITCH_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.np= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.sp= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HALLSWITCH_RETVAL  uint8_t

#define HALLSWITCH_OK           0x00
#define HALLSWITCH_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup hall_switch  Hall_Switch
 * \{
 */
#define HALLSWITCH_POLE_ACTIVE        0x00
#define HALLSWITCH_POLE_NO_ACTIVE  0x01
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

    digital_out_t np;
    digital_out_t sp;

} hallswitch_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t np;
    pin_name_t sp;

} hallswitch_cfg_t;

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
void hallswitch_cfg_setup ( hallswitch_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param hallswitch Click object.
 *
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HALLSWITCH_RETVAL hallswitch_init ( hallswitch_t *ctx, hallswitch_cfg_t *cfg );

/**
 * @brief Function for turn on and turn off N Pole
 *
 * @param ctx  Click object.
 *
 * @description This function setst N pole
 */
void hallswitch_set_npole ( hallswitch_t *ctx, uint8_t state );

/**
 * @brief Function for turn on and turn off S Pole

 * @param ctx  Click object.
 *
 * @description This function sets S pole
 */
void hallswitch_set_spole ( hallswitch_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _HALLSWITCH_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
