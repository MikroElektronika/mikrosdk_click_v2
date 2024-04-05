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
 * \brief This file contains API for 10x10 RGB Click driver.
 *
 * \addtogroup c10x10rgb 10x10 RGB Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C10X10RGB_H
#define C10X10RGB_H

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
#define C10X10RGB_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.di_pin = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.do_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

#define SELECT_INVERT( pos , x ) ( ( pos == 0 ) ? x : ( 8 - x ) )
#define SELECT_ROTATE( pos , x , y ) ( ( pos == 0 ) ? ( 10 * y + x ) : ( 10 * x + y ) )
#define SELECT_INV_BYTE_POS( rotate, x ) ( ( ( rotate & 0x11 ) == 0x11 || ( rotate & 0x11 ) == 0x00 ) ? x : ( 9 - x ) )

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C10X10RGB_RETVAL                uint8_t

#define C10X10RGB_OK                    0x00
#define C10X10RGB_INIT_ERROR            0xFF
/** \} */

/**
 * \defgroup ctrl_cfg Control & Configuration
 * \{
 */
#define LOGIC_ONE                       0x01
#define LOGIC_ZERO                      0x00

#define NUM_DATA_BITS                   24
#define NUM_MATRIX_BYTE                 100
#define NUX_MAX_CHAR                    40

#define COLOR_DEFAULT                   0x00000000
#define BG_COLOR_DEFAULT                0x00000000
#define ROTATE_DEFAULT                  0x00       

#define C10X10RGB_BYTE_ROTATE_H_UP      0x00
#define C10X10RGB_BYTE_ROTATE_H_DOWN    0x01
#define C10X10RGB_BYTE_ROTATE_V_RIGHT   0x11
#define C10X10RGB_BYTE_ROTATE_V_LEFT    0x10

#define C10X10RGB_SCROLL_ROTATE_H       0x00 
#define C10X10RGB_SCROLL_ROTATE_V       0x11 

#define C10X10RGB_CTRL_PIN_LOW          0x00       
#define C10X10RGB_CTRL_PIN_HIGH         0x01 
/** \} */

/**
 * \defgroup colors Colors
 * \{
 */
#define C10X10RGB_COLOR_WHITE_100       0x002F2F2F
#define C10X10RGB_COLOR_WHITE_75        0x00232323
#define C10X10RGB_COLOR_WHITE_50        0x00181818
#define C10X10RGB_COLOR_WHITE_25        0x000C0C0C

#define C10X10RGB_COLOR_RED_100         0x00002F00
#define C10X10RGB_COLOR_RED_75          0x00002300
#define C10X10RGB_COLOR_RED_50          0x00001800
#define C10X10RGB_COLOR_RED_25          0x00000C00

#define C10X10RGB_COLOR_GREEN_100       0x002F0000
#define C10X10RGB_COLOR_GREEN_75        0x00230000
#define C10X10RGB_COLOR_GREEN_50        0x00180000
#define C10X10RGB_COLOR_GREEN_25        0x000C0000

#define C10X10RGB_COLOR_BLUE_100        0x0000002F
#define C10X10RGB_COLOR_BLUE_75         0x00000023
#define C10X10RGB_COLOR_BLUE_50         0x00000018
#define C10X10RGB_COLOR_BLUE_25         0x0000000C

#define C10X10RGB_COLOR_LIGHT_BLUE_100  0x002F002F
#define C10X10RGB_COLOR_LIGHT_BLUE_75   0x00230023
#define C10X10RGB_COLOR_LIGHT_BLUE_50   0x00180018
#define C10X10RGB_COLOR_LIGHT_BLUE_25   0x000C000C

#define C10X10RGB_COLOR_YELLOW_100      0x002F2F00
#define C10X10RGB_COLOR_YELLOW_75       0x00232300
#define C10X10RGB_COLOR_YELLOW_50       0x00181800
#define C10X10RGB_COLOR_YELLOW_25       0x000C0C00

#define C10X10RGB_COLOR_PURPLE_100      0x00002F2F
#define C10X10RGB_COLOR_PURPLE_75       0x00002323
#define C10X10RGB_COLOR_PURPLE_50       0x00001818
#define C10X10RGB_COLOR_PURPLE_25       0x00000C0C

#define C10X10RGB_COLOR_OFF             0x00000000
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef void ( *drv_logic_t ) ( void );

/**
 * @brief Byte object definition.
 */
typedef struct
{
    char data_byte;
    uint32_t color;
    uint32_t bg_color;
    uint8_t rotate;

} c10x10rgb_byte_t;

/**
 * @brief Update line object definition.
 */
typedef struct
{
    uint8_t new_data;
    uint8_t rotate;
    uint8_t line_pos;
    uint32_t color;
    uint32_t bg_color;

} drv_update_line_t;

/**
 * @brief Scroll buffer object definition.
 */
typedef struct
{
    c10x10rgb_byte_t buffer[ 200 ];
    uint8_t len;
    
} drv_scroll_buf_t;
 
/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 
    digital_out_t di_pin;

    // Input pins 
    digital_in_t do_pin;

    // Function pointers
    drv_logic_t logic_zero;
    drv_logic_t logic_one;
    
    uint32_t matrix[ NUM_MATRIX_BYTE ];

} c10x10rgb_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 
    pin_name_t di_pin;
    pin_name_t do_pin;

    // Function pointers
    drv_logic_t logic_zero;
    drv_logic_t logic_one;

} c10x10rgb_cfg_t;

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
void c10x10rgb_cfg_setup ( c10x10rgb_cfg_t *cfg, drv_logic_t logic_zero, drv_logic_t logic_one );

/**
 * @brief Initialization function.
 * @param c10x10rgb Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C10X10RGB_RETVAL c10x10rgb_init ( c10x10rgb_t *ctx, c10x10rgb_cfg_t *cfg );

/**
 * @brief Write data function.
 * 
 * @param c10x10rgb     Click object.
 * @param w_data        Write data.
 * 
 * @description This function writes data to the click module using the GPIO protocol.
 */
void c10x10rgb_write_data ( c10x10rgb_t *ctx, uint32_t w_data );

/**
 * @brief Fill screen function.
 * 
 * @param c10x10rgb     Click object.
 * @param screen_color  Screen color value.
 * 
 * @description This function fills the whole display with the value: { screen_color }.
 */
void c10x10rgb_fill_screen ( c10x10rgb_t *ctx, uint32_t screen_color );

/**
 * @brief Make color function.
 * 
 * @param red          Red color value.
 * @param green        Green color value.
 * @param blue         Blue color value.
 * @param brightness   Brightness value.
 * 
 * @description This function creates a color based on the input color and brightness
 *              parameters. 
 */
uint32_t c10x10rgb_make_color ( uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness );

/**
 * @brief Display image function.
 * 
 * @param c10x10rgb     Click object.
 * @param demo_image    Demo image address.
 * 
 * @description This function displays an image from the specified demo_image address.
 */
void c10x10rgb_display_image ( c10x10rgb_t *ctx, const uint32_t *demo_image );

/**
 * @brief Display byte function.
 * 
 * @param c10x10rgb     Click object.
 * @param data_obj      Data object pointer.
 * 
 * @description This function displays the specified byte.
 */
void c10x10rgb_display_byte ( c10x10rgb_t *ctx, c10x10rgb_byte_t *data_obj );

/**
 * @brief Display string function.
 * 
 * @param c10x10rgb     Click object.
 * @param data_obj      Data object pointer.
 * @param len           Length value (up to 18 characters).
 * @param speed_ms      Millisecond speed value.
 * 
 * @description This function displays the specified string.
 */
void c10x10rgb_display_string ( c10x10rgb_t *ctx, c10x10rgb_byte_t *data_obj, 
                                uint8_t len, uint16_t speed_ms );

/**
 * @brief Demo rainbow function.
 * 
 * @param c10x10rgb     Click object.
 * @param brightness    Brightness value.
 * @param speed_ms      Millisecond speed value.
 * 
 * @description This function displays a "rainbow" on the display.
 */
void c10x10rgb_demo_rainbow ( c10x10rgb_t *ctx, uint8_t brightness, uint16_t speed_ms );

#ifdef __cplusplus
}
#endif
#endif  // _C10X10RGB_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
