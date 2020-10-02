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
 * \brief This file contains API for Opto 2 Click driver.
 *
 * \addtogroup opto2 Opto 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OPTO2_H
#define OPTO2_H

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
#define OPTO2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.in4= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.in3= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.in2= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.in1= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OPTO2_RETVAL  uint8_t

#define OPTO2_OK           0x00
#define OPTO2_INIT_ERROR   0xFF
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

    digital_in_t in4;
    digital_in_t in3;
    digital_in_t in2;
    digital_in_t in1;

} opto2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t in4;
    pin_name_t in3;
    pin_name_t in2;
    pin_name_t in1;

} opto2_cfg_t;

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
void opto2_cfg_setup ( opto2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param opto2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
OPTO2_RETVAL opto2_init ( opto2_t *ctx, opto2_cfg_t *cfg );

/**
 * @brief OUT1 Check function.
 *
 * @param ctx  Click object.
 *
 * @description This function checks the state of OUT1 pin.
 */
uint8_t opto2_check_out1 ( opto2_t *ctx );

/**
 * @brief OUT2 Check function.
 *
 * @param ctx  Click object.
 *
 * @description This function checks the state of OUT2 pin.
 */
uint8_t opto2_check_out2 ( opto2_t *ctx );

/**
 * @brief OUT3 Check function.
 *
 * @param ctx  Click object.
 *
 * @description This function checks the state of OUT3 pin..
 */
uint8_t opto2_check_out3 ( opto2_t *ctx );

/**
 * @brief OUT4 Check function.
 *
 * @param ctx  Click object.
 *
 * @description This function checks the state of OUT4 pin..
 */
uint8_t opto2_check_out4 ( opto2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _OPTO2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
