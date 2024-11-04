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
 * \brief This file contains API for Opto 3 Click driver.
 *
 * \addtogroup opto3 Opto 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OPTO3_H
#define OPTO3_H

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
#define OPTO3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.out1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.out2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OPTO3_OK                0
#define OPTO3_ERROR            -1
/** \} */

/**
 * \defgroup opto_state Opto state
 * \{
 */
 #define OPTO3_HIGH             0x01
 #define OPTO3_LOW              0x00
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
    digital_out_t out1;
    digital_out_t out2;

    // Input pins 
    digital_in_t in1;
    digital_in_t in2;

} opto3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 
    pin_name_t out1;
    pin_name_t out2;
    pin_name_t in1;
    pin_name_t in2;

} opto3_cfg_t;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void opto3_cfg_setup ( opto3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t opto3_init ( opto3_t *ctx, opto3_cfg_t *cfg );

/**
 * @brief Get input 1
 *
 * @param ctx  Click object.
 *
 * @details This function gets input 1 pin state.
 */
uint8_t opto3_get_in1 ( opto3_t *ctx );

/**
 * @brief Get input 2
 *
 * @param ctx  Click object.
 *
 * @details This function gets input 2 pin state.
 */
uint8_t opto3_get_in2 ( opto3_t *ctx );

/**
 * @brief Set output 1
 *
 * @param ctx  Click object.
 *
 * @param state  Pin state 
 * @details This function sets output 1 pin state.
 */
void opto3_set_out1 ( opto3_t *ctx, uint8_t state );

/**
 * @brief Set output 2
 *
 * @param ctx  Click object.
 *
 * @param state  Pin state 
 * @details This function sets output 2 pin state.
 */
void opto3_set_out2 ( opto3_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _OPTO3_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
