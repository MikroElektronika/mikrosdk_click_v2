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
 * \brief This file contains API for Index Counter Click driver.
 *
 * \addtogroup indexcounter Index Counter Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef INDEXCOUNTER_H
#define INDEXCOUNTER_H

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
#define INDEXCOUNTER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.dir= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.spd= MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define INDEXCOUNTER_RETVAL  uint8_t

#define INDEXCOUNTER_OK           0x00
#define INDEXCOUNTER_INIT_ERROR   0xFF
/** \} */

#define INDEXCOUNTER_ACTIVE               1
#define INDEXCOUNTER_INACTIVE             0

#define INDEXCOUNTER_SPEED_ENABLE         1
#define INDEXCOUNTER_SPEED_DISABLE        0

#define INDEXCOUNTER_ONE_MIN_CONV_MS      60000.0

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

    digital_in_t dir;
    digital_in_t spd;

} indexcounter_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t dir;
    pin_name_t spd;

} indexcounter_cfg_t;

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
void indexcounter_cfg_setup ( indexcounter_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param indexcounter Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
INDEXCOUNTER_RETVAL indexcounter_init ( indexcounter_t *ctx, indexcounter_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Index Counter click.
 */
void indexcounter_default_cfg ( indexcounter_t *ctx );

/**
 * @brief Get state of the direction pin function
 *
 * @returns state of the direction:
 *                          - 0 : inactive;
 *                          - 1 : active state;
 *
 * @description This function returns a state of the direction DIR ( AN ) pin.
 */
uint8_t indexcounter_get_dir ( indexcounter_t *ctx );

/**
 * @brief Get state of the speed pin function
 *
 * @returns state of the speed:
 *                         - 0 : inactive;
 *                         - 1 : active state;
 *
 * @description This function returns a state of the speed SPD ( RST ) pin.
 */
uint8_t indexcounter_get_speed ( indexcounter_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _INDEXCOUNTER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
