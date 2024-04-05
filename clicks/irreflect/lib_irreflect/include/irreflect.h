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
 * \brief This file contains API for IR reflect Click driver.
 *
 * \addtogroup irreflect IR reflect Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRREFLECT_H
#define IRREFLECT_H

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
#define IRREFLECT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.int_pin= MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IRREFLECT_RETVAL  uint8_t

#define IRREFLECT_OK           0x00
#define IRREFLECT_INIT_ERROR   0xFF
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
    digital_in_t an;

} irreflect_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t an;
    pin_name_t int_pin;

} irreflect_cfg_t;

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
void irreflect_cfg_setup ( irreflect_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param irreflect Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
IRREFLECT_RETVAL irreflect_init ( irreflect_t *ctx, irreflect_cfg_t *cfg );

/**
 * @brief Detecting interrupt states of IR reflection from GP2S700HCP reflective photointerrupter sensor
 *
 * @param ctx  Click object.
 * @return result                    state of INT pin
 * - 0 : interrupt not detected;
 * - 1 : interrupt is detected;
 *
 * @description Function detecting interrupt states of IR reflection 
 * from GP2S700HCP reflective photointerrupter sensor
 * and returns the state of the INT pin.
 */
uint8_t irreflect_reflect_status ( irreflect_t *ctx );

/**
 * @brief Detecting states of analog pin of IR reflection from GP2S700HCP reflective photointerrupter sensor
 *
 * @param ctx  Click object.
 * @return result                    state of AN pin
 *
 * @description Function detecting states of analog pin of IR reflection
 * from GP2S700HCP reflective photointerrupter sensor
 * and returns the state of the AN pin.
 */
uint8_t irreflect_analog_status ( irreflect_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _IRREFLECT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
