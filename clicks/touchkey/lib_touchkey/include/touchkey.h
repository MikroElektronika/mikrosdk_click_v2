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
 * \brief This file contains API for TouchKey Click driver.
 *
 * \addtogroup touchkey TouchKey Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TOUCHKEY_H
#define TOUCHKEY_H

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
#define TOUCHKEY_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.b= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.a= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.c= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.d= MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TOUCHKEY_RETVAL  uint8_t

#define TOUCHKEY_OK           0x00
#define TOUCHKEY_INIT_ERROR   0xFF
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

    digital_in_t b;
    digital_in_t a;
    digital_in_t c;
    digital_in_t d;

} touchkey_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t b;
    pin_name_t a;
    pin_name_t c;
    pin_name_t d;

} touchkey_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void touchkey_cfg_setup ( touchkey_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param touchkey Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
TOUCHKEY_RETVAL touchkey_init ( touchkey_t *ctx, touchkey_cfg_t *cfg );

/**
 * @brief Taster A pressed function.
 *
 * @param ctx  Click object.
 * @return
 *              1 : Key A pressed.
 *              0 : Key A not pressed.
 * 
 * Function gets state of "a" (RST) pin on TouchKey Click board.
 */
uint8_t touchkey_a ( touchkey_t *ctx );

/**
 * @brief Taster B pressed function.
 *
 * @param ctx  Click object.
 * @return
 *              1 : Key B pressed.
 *              0 : Key B not pressed.
 *
 * @description Function gets state of "b" (AN) pin on TouchKey Click board.
 */
uint8_t touchkey_b ( touchkey_t *ctx );

/**
 * @brief Taster C pressed function.
 *
 * @param ctx  Click object.
 * @return
 *              1 : Key C pressed.
 *              0 : Key C not pressed. 
 *
 * @description Function gets state of "c" (PWM) pin on TouchKey Click board.
 */
uint8_t touchkey_c ( touchkey_t *ctx );

/**
 * @brief Taster D pressed function.
 *
 * @param ctx  Click object.
 * @return
 *              1 : Key D pressed.
 *              0 : Key D not pressed. 
 *
 * @description Function gets state of "d" (INT) pin on TouchKey Click board.
 */
uint8_t touchkey_d ( touchkey_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _TOUCHKEY_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
