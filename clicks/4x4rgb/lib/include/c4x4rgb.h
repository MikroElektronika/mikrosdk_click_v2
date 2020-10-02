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
 * \brief This file contains API for 4x4 RGB Click driver.
 *
 * \addtogroup c4x4rgb 4x4 RGB Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C4X4RGB_H
#define C4X4RGB_H

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
#define C4X4RGB_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.in1= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.in2= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.out= MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C4X4RGB_RETVAL  uint8_t

#define C4X4RGB_OK           0x00
#define C4X4RGB_INIT_ERROR   0xFF
/** \} */


/**
 * \defgroup color  Color
 * \{
 */
#define C4X4RGB_COLOR_WHITE                                 0x002F2F2F
#define C4X4RGB_COLOR_RED                                   0x002F0000
#define C4X4RGB_COLOR_GREEN                                 0x00002F00
#define C4X4RGB_COLOR_BLUE                                  0x0000002F
#define C4X4RGB_COLOR_LIGHT_BLUE                            0x00002F2F
#define C4X4RGB_COLOR_YELLOW                                0x002F2F00
#define C4X4RGB_COLOR_PURPLE                                0x002F002F
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
    digital_out_t out;
    
    uint8_t end_first; 
    uint8_t end_second;
    float first_delay;
    float second_delay;

} c4x4rgb_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t in1;
    pin_name_t in2;
    pin_name_t out;

} c4x4rgb_cfg_t;

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
void c4x4rgb_cfg_setup ( c4x4rgb_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c4x4rgb Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C4X4RGB_RETVAL c4x4rgb_init ( c4x4rgb_t *ctx, c4x4rgb_cfg_t *cfg );

/**
 * @brief Function for logic zero.
 *
 * @param ctx  Click object.
 */
void c4x4rgb_logic_zero ( c4x4rgb_t *ctx );

/**
 * @brief Function for logic one.
 *
 * @param ctx  Click object.
 */
void c4x4rgb_logic_one ( c4x4rgb_t *ctx );

/**
 * @brief Function for custom delay.
 *
 * @param delay_time     Length of delay.
 * @param delay_unit     Time unit in milliseconds or microseconds.      
 *
 * @description This function allows to enter different delay.
 */
void c4x4rgb_delay ( uint16_t delay_time, char delay_unit );  

/**
 * @brief Get device clock.
 *
 * @param ctx  Click object.
 *
 * @description This function get device clock value in MHz.
 */
void c4x4rgb_get_device_clock ( c4x4rgb_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _C4X4RGB_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
