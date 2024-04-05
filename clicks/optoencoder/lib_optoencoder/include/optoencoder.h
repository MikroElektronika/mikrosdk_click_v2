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
 * \brief This file contains API for Opto Encoder Click driver.
 *
 * \addtogroup optoencoder Opto Encoder Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OPTOENCODER_H
#define OPTOENCODER_H

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
#define OPTOENCODER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.o1= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.o2= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OPTOENCODER_RETVAL  uint8_t

#define OPTOENCODER_OK           0x00
#define OPTOENCODER_INIT_ERROR   0xFF
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

    uint8_t rotary_flag;
    uint8_t o1_flag;
    uint8_t o2_flag;
    int16_t dev_rotation;

} optoencoder_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t o1;
    pin_name_t o2;

} optoencoder_cfg_t;

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
void optoencoder_cfg_setup ( optoencoder_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param optoencoder Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
OPTOENCODER_RETVAL optoencoder_init ( optoencoder_t *ctx, optoencoder_cfg_t *cfg );

/**
 * @brief Function for reading O1 state
 *
 * @param ctx  Click object.
 *
 * @return O1 pin state
 */
uint8_t optoencoder_get_o1 ( optoencoder_t *ctx );

/**
 * @brief Function for reading O2 state
 *
 * @param ctx  Click object.
 *
 * @return O2 pin state
 */
uint8_t optoencoder_get_o2 ( optoencoder_t *ctx );

/**
 * @brief Initialization function
 *
 * @param ctx  Click object.
 */
void optoencoder_init_dev ( optoencoder_t *ctx );

/**
 * @brief Function for reading the position of the encoder
 *
 * @param ctx  Click object.
 *
 * @return position of the encoder 
 */
int16_t optoencoder_get_position ( optoencoder_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _OPTOENCODER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
