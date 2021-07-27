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

#define C4X4RGB_OK                  0x00
#define C4X4RGB_INIT_ERROR          0xFF
/** \} */


/**
 * \defgroup control_pin Control pin select macro
 * \{
 */
#define C4X4RGB_CTRL_PIN_IN1        1
#define C4X4RGB_CTRL_PIN_IN2        2
/** \} */


/**
 * \defgroup color  Color
 * \{
 */
#define C4X4RGB_COLOR_WHITE         0x001F1F1F
#define C4X4RGB_COLOR_RED           0x001F0000
#define C4X4RGB_COLOR_GREEN         0x00001F00
#define C4X4RGB_COLOR_BLUE          0x0000001F
#define C4X4RGB_COLOR_LIGHT_BLUE    0x00001F1F
#define C4X4RGB_COLOR_YELLOW        0x001F1F00
#define C4X4RGB_COLOR_PURPLE        0x001F001F
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Function pointer for logic level one and zero
 */
typedef void ( *drv_logic_t ) ( void );
 
/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t in1;
    digital_out_t in2;
    digital_out_t out;
    
    digital_out_t ctrl_pin;

    // Function pointers

    drv_logic_t logic_zero;
    drv_logic_t logic_one;

    
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
    
    uint8_t ctrl_pin;

    // Function pointers

    drv_logic_t logic_zero;
    drv_logic_t logic_one;

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
 * @details This function initializes click configuration structure to init state.
 *
 * @param cfg  Click configuration structure.
 * @param logic_zero  Function pointer for logic zero
 * @param logic_one  Function pointer for logic one
 * @param select_ctrl_pin  Macro selecting control pin
 * @note All used pins will be set to unconnected state.
 */
void c4x4rgb_cfg_setup ( c4x4rgb_cfg_t *cfg, drv_logic_t logic_zero, drv_logic_t logic_one, uint8_t select_ctrl_pin );

/**
 * @brief Initialization function.
 * @details This function initializes all necessary pins and peripherals used for this click.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 */
C4X4RGB_RETVAL c4x4rgb_init ( c4x4rgb_t *ctx, c4x4rgb_cfg_t *cfg );

/**
 * @brief Function for setting color color of one diode.
 * @details This function allows to set color of one diode.
 *
 * @param ctx            Click object.
 * @param diode_num      Desired diode to control
 * @param diode_color    Desiered color
 * 
 *  @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t c4x4rgb_set_diode ( c4x4rgb_t *ctx, uint32_t diode_num, uint32_t diode_color );

/**
 * @brief Function for filling color of ever diode.
 * @details This function sets every diode on selected color.
 *
 * @param ctx            Click object.
 * @param fill_color    Desiered color
 * @param fill_delay    Delay between changeing diode color.
 */
void c4x4rgb_fill_screen ( c4x4rgb_t *ctx, uint32_t fill_color, uint16_t fill_delay );

#ifdef __cplusplus
}
#endif
#endif  // _C4X4RGB_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
