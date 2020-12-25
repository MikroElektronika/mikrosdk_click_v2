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
 * \brief This file contains API for Driver Click driver.
 *
 * \addtogroup driver Driver Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DRIVER_H
#define DRIVER_H

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
#define DRIVER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.in1= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.in2= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.in3= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.in4= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.in5= MIKROBUS( mikrobus, MIKROBUS_INT ); \
  cfg.in6= MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.in7= MIKROBUS( mikrobus, MIKROBUS_TX )
  //RX and TX are inverted because of mapping

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DRIVER_RETVAL  uint8_t

#define DRIVER_OK           0x00
#define DRIVER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup conf  Conf
 * \{
 */
#define PULSE_WIDTH  3000
#define ENABLE_IN  0
#define DISABLE_IN  1
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

    digital_out_t in1;
    digital_out_t in2;
    digital_out_t in3;
    digital_out_t in4;
    digital_out_t in5;
    digital_out_t in6;
    digital_out_t in7;

} driver_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t in1;
    pin_name_t in2;
    pin_name_t in3;
    pin_name_t in4;
    pin_name_t in5;
    pin_name_t in6;
    pin_name_t in7;

} driver_cfg_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS

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
void driver_cfg_setup ( driver_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param driver Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DRIVER_RETVAL driver_init ( driver_t *ctx, driver_cfg_t *cfg );

/**
 * @brief IN1 Set function.
 *
 * @param ctx     Click object.
 * @param state   0 - OUT1 ON, 1 - OUT1 OFF.
 *
 * @description This function determines state of output 1 (OUT1).
 */
void driver_set_in1 ( driver_t *ctx, uint8_t state );

/**
 * @brief IN2 Set function.
 *
 * @param ctx     Click object.
 * @param state   0 - OUT2 ON, 1 - OUT2 OFF.
 *
 * @description This function determines state of output 2 (OUT2).
 */
void driver_set_in2 ( driver_t *ctx, uint8_t state );

/**
 * @brief IN3 Set function.
 *
 * @param ctx     Click object.
 * @param state   0 - OUT3 ON, 1 - OUT3 OFF.
 *
 * @description This function determines state of output 3 (OUT3).
 */
void driver_set_in3 ( driver_t *ctx, uint8_t state );

/**
 * @brief IN4 Set function
 *
 * @param state       0 - OUT4 ON, 1 - OUT4 OFF
 *
 * Function determines state of output 4 (OUT4).
 */
void driver_set_in4 ( driver_t *ctx, uint8_t state );

/**
 * @brief IN5 Set function
 *
 * @param state       0 - OUT5 ON, 1 - OUT5 OFF
 *
 * Function determines state of output 5 (OUT5).
 */
void driver_set_in5 ( driver_t *ctx, uint8_t state );

/**
 * @brief IN6 Set function
 *
 * @param state       0 - OUT6 ON, 1 - OUT6 OFF
 *
 * Function determines state of output 6 (OUT6).
 */
void driver_set_in6 ( driver_t *ctx, uint8_t state );

/**
 * @brief IN7 Set function
 *
 * @param state       0 - OUT7 ON, 1 - OUT7 OFF
 *
 * Function determines state of output 7 (OUT7).
 */
void driver_set_in7 ( driver_t *ctx, uint8_t state );


#ifdef __cplusplus
}
#endif
#endif  // _DRIVER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
