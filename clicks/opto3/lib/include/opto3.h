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
  cfg.ou1= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.ou2= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.in1= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.in2= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OPTO3_RETVAL     uint8_t
#define OPTO3_STATE      uint8_t
#define OPTO3_SWITCH     uint8_t

#define OPTO3_OK           0x00
#define OPTO3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup opto_state Opto state
 * \{
 */
 #define OPTO3_HIGH            0x01
 #define OPTO3_LOW             0x00
/** \} */

/**
 * \defgroup opto_switch Opto switch
 * \{
 */
 #define OPTO3_ON             0x01
 #define OPTO3_OFF            0x00
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

    digital_out_t ou1;
    digital_out_t ou2;

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

    pin_name_t ou1;
    pin_name_t ou2;
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
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void opto3_cfg_setup ( opto3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param opto3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
OPTO3_RETVAL opto3_init ( opto3_t *ctx, opto3_cfg_t *cfg );

/**
 * @brief Gets input
 *
 * @param ctx  Click object.
 *
 * @description This function gets input from pin 1.
 */
OPTO3_STATE opto3_get_in1 ( opto3_t *ctx );

/**
 * @brief Gets input
 *
 * @param ctx  Click object.
 *
 * @description This function gets input from pin 2.
 */
 OPTO3_STATE opto3_get_in2 ( opto3_t *ctx );

 /**
 * @brief Gets output
 *
 * @param ctx  Click object.
 *
 * @param state  Pin state 
 * @description This function sets output pin 1.
 */
 void opto3_set_out1 ( opto3_t *ctx, OPTO3_SWITCH state );

 /**
 * @brief Gets output
 *
 * @param ctx  Click object.
 *
 * @param state  Pin state 
 * @description This function sets output pin 2.
 */
 void opto3_set_out2 ( opto3_t *ctx, OPTO3_SWITCH state );


#ifdef __cplusplus
}
#endif
#endif  // _OPTO3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
