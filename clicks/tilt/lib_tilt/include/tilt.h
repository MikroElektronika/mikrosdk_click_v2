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
 * \brief This file contains API for Tilt Click driver.
 *
 * \addtogroup tilt Tilt Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TILT_H
#define TILT_H

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
#define TILT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.vo1= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.vo2= MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TILT_RETVAL  uint8_t

#define TILT_OK           0x00
#define TILT_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup tilt_state Tilt direction states
 * \{
 */
#define TILT_NO_DETECTION                 0
#define TILT_DETECTION                    1
#define TILT_LEFT_DETECTION               2
#define TILT_RIGHT_DETECTION              3
#define TILT_UP_DETECTION                 4
#define TILT_DOWN_DETECTION               5
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

    digital_in_t vo1;
    digital_in_t vo2;

} tilt_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t vo1;
    pin_name_t vo2;

} tilt_cfg_t;

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
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void tilt_cfg_setup ( tilt_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param tilt Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TILT_RETVAL tilt_init ( tilt_t *ctx, tilt_cfg_t *cfg );

/**
 * @brief Check the tilt left movement's direction function.
 *
 * @param ctx  Click object.
 * 
 * @return
 * - 0 : other movement direction;
 * - 1 : left movement direction;
 *
 * @description This function check the tilt left movement's direction
 * of RPI-1035 Surface Mount Type 4-Direction Detector on Tilt click board.
 */
uint8_t tilt_left ( tilt_t *ctx );

/**
 * @brief Check the tilt right movement's direction function.
 *
 * @param ctx  Click object.
 * 
 * @return
 * - 0 : other movement direction;
 * - 1 : right movement direction;
 *
 * @description This function check the tilt right movement's direction
 * of RPI-1035 Surface Mount Type 4-Direction Detector on Tilt click board.
 */
uint8_t tilt_right ( tilt_t *ctx );

/**
 * @brief Check the tilt up movement's direction function.
 *
 * @param ctx  Click object.
 * 
 * @return
 * - 0 : other movement direction;
 * - 1 : up movement direction;
 *
 * @description This function check the tilt up movement's direction
 * of RPI-1035 Surface Mount Type 4-Direction Detector on Tilt click board.
 */
uint8_t tilt_up ( tilt_t *ctx );

/**
 * @brief Check the tilt down movement's direction function.
 *
 * @param ctx  Click object.
 * 
 * @return
 * - 0 : other movement direction;
 * - 1 : down movement direction;
 *
 * @description This function check the tilt down movement's direction
 * of RPI-1035 Surface Mount Type 4-Direction Detector on Tilt click board.
 */
uint8_t tilt_down ( tilt_t *ctx );

/**
 * @brief Check the tilt movement's direction function.
 *
 * @param ctx  Click object.
 * 
 * @return
 * - 2 : left movement direction;
 * - 3 : right movement direction;
 * - 4 : up movement direction;
 * - 5 : down movement direction;
 *
 * @description This function check the tilt movement's direction:
 * left, right, up or down,
 * of RPI-1035 Surface Mount Type 4-Direction Detector on Tilt click board.
 */
uint8_t tilt_direction ( tilt_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TILT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
