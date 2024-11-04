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
 * \brief This file contains API for Key Lock 2 Click driver.
 *
 * \addtogroup keylock2 Key Lock 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef KEYLOCK2_H
#define KEYLOCK2_H

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
#define KEYLOCK2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.in3 = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define KEYLOCK2_RETVAL          uint8_t

#define KEYLOCK2_OK                 0x00
#define KEYLOCK2_INIT_ERROR         0xFF
/** \} */

/**
 * \defgroup pins Pins
 * \{
 */
#define KEYLOCK2_STATE_RST_PIN       0x01
#define KEYLOCK2_STATE_PWM_PIN       0x02
#define KEYLOCK2_STATE_INT_PIN       0x03
/** \} */

/**
 * \defgroup position Position
 * \{
 */
#define KEYLOCK2_POSITION_1          0x01
#define KEYLOCK2_POSITION_2          0x02
#define KEYLOCK2_POSITION_3          0x03
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

    digital_in_t in1;
    digital_in_t in2;
    digital_in_t in3;

} keylock2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t in1;
    pin_name_t in2;
    pin_name_t in3;

} keylock2_cfg_t;

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
void keylock2_cfg_setup ( keylock2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param keylock2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for
 * this Click.
 */
KEYLOCK2_RETVAL keylock2_init ( keylock2_t *ctx, keylock2_cfg_t *cfg );

/**
 * @brief Get Pin State.
 *
 * @param ctx  Click object.
 *
 * @description This function gets states of pins in1, in2 and in3 on Key Lock 2 Click.
 */
uint8_t keylock2_get_pin_state ( keylock2_t *ctx, uint8_t pin );

/**
 * @brief Get Pin State.
 *
 * @param ctx  Click object.
 *
 * @description This function gets Position (First, Second, Third) of pins 
 * in1, in2 and in3 on Key Lock 2 Click.
 */
uint8_t keylock2_get_position ( keylock2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _KEYLOCK2_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
