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
 * \brief This file contains API for 16x9 Click driver.
 *
 * \addtogroup c16x9 16x9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C16X9_H
#define C16X9_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define C16X9_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.sdb = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C16X9_RETVAL  uint8_t

#define C16X9_OK           0x00
#define C16X9_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define C16X9_SLAVE_ADDRESS 0x74
/** \} */

/**
 * \defgroup register_page Register Page
 * \{
 */
#define C16X9_POINT_TO_PAGE_ONE    0x00
#define C16X9_POINT_TO_PAGE_TWO    0x01
#define C16X9_POINT_TO_PAGE_THREE  0x02
#define C16X9_POINT_TO_PAGE_FOUR   0x03
#define C16X9_POINT_TO_PAGE_FIVE   0x04
#define C16X9_POINT_TO_PAGE_SIX    0x05
#define C16X9_POINT_TO_PAGE_SEVEN  0x06
#define C16X9_POINT_TO_PAGE_EIGHT  0x07
#define C16X9_POINT_TO_PAGE_NINE   0x0B
/** \} */

/**
 * \defgroup functions_register Functions register
 * \{
 */
#define C16X9_REG_CONFIG            0x00
#define C16X9_REG_PICTURE_DISPLAY   0x01
#define C16X9_REG_AUTO_PLAY_CTRL1   0x02
#define C16X9_REG_AUTO_PLAY_CTRL2   0x03
#define C16X9_REG_DISPLAY_OPTION    0x05
#define C16X9_REG_AUDIO_SYNC        0x06
#define C16X9_REG_FRAME_STATE       0x07
#define C16X9_REG_BREATH_CTRL1      0x08
#define C16X9_REG_BREATH_CTRL2      0x09
#define C16X9_REG_SHUTDOWN          0x0A
#define C16X9_REG_AGC_CTRL          0x0B
#define C16X9_REG_AUDIO_ADC_RATE    0x0C
#define C16X9_REG_COMMAND           0xFD
/** \} */

/**
 * \defgroup config_register Config register
 * \{
 */
#define C16X9_CFG_PICTURE_MODE          0x00
#define C16X9_CFG_AUTO_FRAME_PLAY_MODE  0x08
/** \} */

/**
 * \defgroup auto_play_cfg Auto Play CTRL reg 1
 * \{
 */
#define C16X9_AP_CTRL1_PLAY_ENDLESS  0x00
#define C16X9_AP_CTRL1_LOOP_1        0x10
#define C16X9_AP_CTRL1_LOOP_2        0x20
#define C16X9_AP_CTRL1_LOOP_3        0x30
#define C16X9_AP_CTRL1_LOOP_4        0x40
#define C16X9_AP_CTRL1_LOOP_5        0x50
#define C16X9_AP_CTRL1_LOOP_6        0x60
#define C16X9_AP_CTRL1_LOOP_7        0x70
#define C16X9_AP_CTRL1_ALL_FRAME     0x00
#define C16X9_AP_CTRL1_FRAME_1       0x01
#define C16X9_AP_CTRL1_FRAME_2       0x02
#define C16X9_AP_CTRL1_FRAME_3       0x03
#define C16X9_AP_CTRL1_FRAME_4       0x04
#define C16X9_AP_CTRL1_FRAME_5       0x05
#define C16X9_AP_CTRL1_FRAME_6       0x06
#define C16X9_AP_CTRL1_FRAME_7       0x07
/** \} */

/**
 * \defgroup display_option Display Option Register
 * \{
 */
#define C16X9_SET_ONE_FRAME_INTENSITY  0x00
#define C16X9_SET_ALL_FRAME_INTENSITY  0x20
#define C16X9_BLINK_DISABLE  0x00
#define C16X9_BLINK_ENABLE   0x08
/** \} */

/**
 * \defgroup audio_synchronization Audio Synchronization Register
 * \{
 */
#define C16X9_AUDIO_SYNCHRONIZATION_DISABLE  0x00
#define C16X9_AUDIO_SYNCHRONIZATION_ENABLE   0x01
/** \} */

/**
 * \defgroup shutdown_reg Audio Shutdown Register
 * \{
 */
#define C16X9_SHUTDOWN_MODE     0x00
#define C16X9_NORMAL_OPERATION  0x01
/** \} */

/**
 * \defgroup agc_ctrl AGC Control Register
 * \{
 */
#define C16X9_AGC_SLOW_MODE    0x00
#define C16X9_AGC_FAST_MODE    0x10
#define C16X9_AGC_DISABLE      0x00
#define C16X9_AGC_ENABLE       0x08
#define C16X9_AGC_GAIN_0dB     0x00
#define C16X9_AGC_GAIN_3dB     0x01
#define C16X9_AGC_GAIN_6dB     0x02
#define C16X9_AGC_GAIN_9dB     0x03
#define C16X9_AGC_GAIN_12dB    0x04
#define C16X9_AGC_GAIN_15dB    0x05
#define C16X9_AGC_GAIN_18dB    0x06
#define C16X9_AGC_GAIN_21dB    0x07
/** \} */

/**
 * \defgroup select_frame Select Frame
 * \{
 */
#define C16X9_FRAME_1    0x00
#define C16X9_FRAME_2    0x01
#define C16X9_FRAME_3    0x02
#define C16X9_FRAME_4    0x03
#define C16X9_FRAME_5    0x04
#define C16X9_FRAME_6    0x05
#define C16X9_FRAME_7    0x06
#define C16X9_FRAME_8    0x07
/** \} */

/**
 * \defgroup crtl_led CTRL LED
 * \{
 */
#define C16X9_CTRL_LED        0x01
#define C16X9_CTRL_LED_BLINK  0x02
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

    digital_out_t sdb;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} c16x9_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t sdb;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} c16x9_cfg_t;

/**
 * @brief Point structure definition.
 */
typedef struct
{
    uint8_t x;    // Start coordinate x 
    uint8_t y;    // Start coordinate y 
    uint8_t pwm;  // PWM value 

}c16x9_point_t;

/**
 * @brief Image structure definition.
 */
typedef struct
{
    uint16_t buf[ 9 ];       // Image buffer
    uint8_t frame;           // Select frame
    uint8_t pwm;             // PWM value

}c16x9_image_t;

/**
 * @brief Character structure definition.
 */
typedef struct
{
    char character;          // Character 
    uint8_t frame;           // Select frame 
    uint8_t pwm;             // PWM value 

}c16x9_char_t;

/**
 * @brief Rectangle structure definition.
 */
typedef struct
{
    uint8_t x;               // Start coordinate x 
    uint8_t y;               // Start coordinate y 
    uint8_t width;           // Rectangle width 
    uint8_t height;          // Rectangle height 
    uint8_t frame;           // Select frame 
    uint8_t pwm;             // PWM value 

}c16x9_rectangle_t;

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
void c16x9_cfg_setup ( c16x9_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C16X9_RETVAL c16x9_init ( c16x9_t *ctx, c16x9_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void c16x9_generic_write ( c16x9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for control all leds.
 *
 * @param ctrl   Selects LED or BLINK control registers.
 * @param state  State to write (0 or 1) for all diodes.
 *
 * @note The function can be used to control all diodes at once
   (store on or off state or control the blink function for each LED).
 */
void c16x9_control_all ( c16x9_t *ctx, uint8_t ctrl, uint8_t state );

/**
 * @brief Functions for fill screen.
 *
 * @param ctx Click object.
 * @param pwm PWM value.
 *
 * @note The function writes PWM value for all diode in matrix.
 */
void c16x9_fill_screen ( c16x9_t *ctx, uint8_t pwm );

/**
 * @brief Function for refresh display
 *
 * @param ctx Click object.
 *
 * @note The function switches off all LEDs
 */
void c16x9_display_refresh ( c16x9_t *ctx );

/**
 * @brief Functions for draw point .
 *
 * @param ctx Click object.
 * @param point  structure for draw point
 */
void c16x9_draw_point ( c16x9_t *ctx, c16x9_point_t *point );

/**
 * @brief Image display function
 *
 * @param ctx Click object.
 * @param image  structure for draw image
 *
 * @note Function for displays the image.
 * The image consists of nine elements (nine columns that build the image).
 */
void c16x9_display_image ( c16x9_t *ctx, c16x9_image_t *image );

/**
 * @brief Function for displaying one character
 *
 * @param ctx Click object.
 * @param data_char  structure for draw char
 */
void c16x9_display_byte ( c16x9_t *ctx, c16x9_char_t *data_char );

/**
 * @brief Draw rectangle.
 *
 * @param ctx Click object.
 * @param rectangle structure for draw rectangle
 */
void c16x9_draw_rectangle( c16x9_t *ctx,  c16x9_rectangle_t *rectangle );

/**
 * @brief Interrupt pin state
 *
 * @param ctx Click object.
 * @return Interrupt pin state
 */
uint8_t c16x9_get_interrupt_state( c16x9_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C16X9_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
