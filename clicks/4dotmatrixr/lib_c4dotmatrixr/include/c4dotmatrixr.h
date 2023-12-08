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
 * \brief This file contains API for c4Dot-matrix r Click driver.
 *
 * \addtogroup c4dotmatrixr c4Dot-matrix r Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C4DOTMATRIXR_H
#define C4DOTMATRIXR_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define C4DOTMATRIXR_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM );
  
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C4DOTMATRIXR_RETVAL  uint8_t

#define C4DOTMATRIXR_OK           0x00
#define C4DOTMATRIXR_INIT_ERROR   0xFF
/** \} */

#define C4DOT_IODIRA              0x00
#define C4DOT_IODIRB              0x01
#define C4DOT_IPOLA               0x02
#define C4DOT_IPOLB               0x03
#define C4DOT_GPINTENA            0x04
#define C4DOT_GPINTENB            0x05
#define C4DOT_DEFVALA             0x06
#define C4DOT_DEFVALB             0x07
#define C4DOT_INTCONA             0x08
#define C4DOT_INTCONB             0x09
#define C4DOT_IOCON               0x0A
#define C4DOT_GPPUA               0x0C
#define C4DOT_GPPUB               0x0D
#define C4DOT_INTFA               0x0E
#define C4DOT_INTFB               0x0F
#define C4DOT_INTCAPA             0x10
#define C4DOT_INTCAPB             0x11
#define C4DOT_GPIOA               0x12
#define C4DOT_GPIOB               0x13
#define C4DOT_OLATA               0x14
#define C4DOT_OLATB               0x15

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

    digital_out_t rst;
    digital_out_t cs;
    digital_out_t pwm;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} c4dotmatrixr_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t cs;
    pin_name_t pwm;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} c4dotmatrixr_cfg_t;

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
void c4dotmatrixr_cfg_setup ( c4dotmatrixr_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c4dotmatrixr Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C4DOTMATRIXR_RETVAL c4dotmatrixr_init ( c4dotmatrixr_t *ctx, c4dotmatrixr_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for c4dotmatrixr click.
 */
void c4dotmatrixr_default_cfg ( c4dotmatrixr_t *ctx );

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
void c4dotmatrixr_generic_write ( c4dotmatrixr_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void c4dotmatrixr_generic_read ( c4dotmatrixr_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief 4DotMatrix Char Write.
 *
 * 
 * @param ctx          Click object.
 * @param char_num     Number of char to write.
 * @param char_value   Value to write to char.
 *
 * Writes charValue to the character on the position of charNum.
 * 0 is the rightmost character, and 3 is the leftmost one.
 * Character value can go from 0 to 127. Values in the range from 32 to 126
 * represent the corresponding ASCII characters. Refer to the OSRAM SLx2016
 * datasheet for a complete list of character values that can be written.
 * 
 * @description This function will do nothing in case of bad charNum or charValue.
 */
void c4dot_write_char ( c4dotmatrixr_t *ctx, uint8_t char_num, uint8_t char_value );

/**
 * @brief 4DotMatrix Char 0 Write.
 *
 * 
 * @param ctx          Click object.
 * @param char_value   Value to write to char.
 *
 * Writes charValue to character 0, the rightmost character.
 * Character value can go from 0 to 127. Values in the range from 32 to 126
 * represent the corresponding ASCII characters. Refer to the OSRAM SLx2016
 * datasheet for a complete list of character values that can be written.
 * 
 * @description This function will do nothing in case of bad charValue.
 */
void c4dot_write_char0 ( c4dotmatrixr_t *ctx, uint8_t char_value );

/**
 * @brief 4DotMatrix Char 1 Write.
 *
 * 
 * @param ctx          Click object.
 * @param char_value   Value to write to char.
 *
 * Writes charValue to character 0, the rightmost character.
 * Character value can go from 0 to 127. Values in the range from 32 to 126
 * represent the corresponding ASCII characters. Refer to the OSRAM SLx2016
 * datasheet for a complete list of character values that can be written.
 * 
 * @description This function will do nothing in case of bad charValue.
 */
void c4dot_write_char1 ( c4dotmatrixr_t *ctx, uint8_t char_value );

/**
 * @brief 4DotMatrix Char 2 Write.
 *
 * 
 * @param ctx          Click object.
 * @param char_value   Value to write to char.
 *
 * Writes charValue to character 0, the rightmost character.
 * Character value can go from 0 to 127. Values in the range from 32 to 126
 * represent the corresponding ASCII characters. Refer to the OSRAM SLx2016
 * datasheet for a complete list of character values that can be written.
 * 
 * @description This function will do nothing in case of bad charValue.
 */
void c4dot_write_char2 ( c4dotmatrixr_t *ctx, uint8_t char_value );

/**
 * @brief 4DotMatrix Char 3 Write.
 *
 * 
 * @param ctx          Click object.
 * @param char_value   Value to write to char.
 *
 * Writes charValue to character 0, the rightmost character.
 * Character value can go from 0 to 127. Values in the range from 32 to 126
 * represent the corresponding ASCII characters. Refer to the OSRAM SLx2016
 * datasheet for a complete list of character values that can be written.
 * 
 * @description This function will do nothing in case of bad charValue.
 */
void c4dot_write_char3 ( c4dotmatrixr_t *ctx, uint8_t char_value);

/**
 * @brief 4DotMatrix Text Write.
 *
 * 
 * @param ctx             Click object.
 * @param text_to_write   Text to write to character display.
 *
 * 
 * @description This function Writes up to four characters from textToWrite to the display characters.
 */
void c4dot_write_text ( c4dotmatrixr_t *ctx, uint8_t *text_to_write );

/**
 * @brief 4DotMatrix Int Write.
 *
 * 
 * @param ctx           Click object.
 * @param int_to_write  Integer to write to character display.
 * @param int_base      Numeral system base.
 * 
 * @description This function Writes up to four characters from textToWrite to the display characters.
 */
void c4dot_write_int ( c4dotmatrixr_t *ctx, int16_t int_to_write, uint8_t int_base );

/**
 * @brief 4DotMatrix Binary Int Write.
 *
 * 
 * @param ctx           Click object.
 * @param int_to_write  Integer to write to character display.
 * 
 * Writes intToWrite as a binary integer to the character display.
 * Obviously, only the lowest four digits will be shown.
 * If the given number is negative, '-' will be shown if there is space left.
 */
void c4dot_write_int_bin ( c4dotmatrixr_t *ctx, int16_t int_to_write );

/**
 * @brief 4DotMatrix Octal Int Write.
 *
 * 
 * @param ctx           Click object.
 * @param int_to_write  Integer to write to character display.
 * 
 * Writes intToWrite as a binary integer to the character display.
 * Obviously, only the lowest four digits will be shown.
 * If the given number is negative, '-' will be shown if there is space left.
 */
void c4dot_write_int_oct ( c4dotmatrixr_t *ctx, int16_t int_to_write );

/**
 * @brief 4DotMatrix Decimal Int Write.
 *
 * 
 * @param ctx           Click object.
 * @param int_to_write  Integer to write to character display.
 * 
 * Writes intToWrite as a binary integer to the character display.
 * Obviously, only the lowest four digits will be shown.
 * If the given number is negative, '-' will be shown if there is space left.
 */
void c4dot_write_int_dec ( c4dotmatrixr_t *ctx, int16_t int_to_write);

/**
 * @brief 4DotMatrix Hexadecimal Int Write.
 *
 * 
 * @param ctx           Click object.
 * @param int_to_write  Integer to write to character display.
 * 
 * Writes intToWrite as a binary integer to the character display.
 * Obviously, only the lowest four digits will be shown.
 * If the given number is negative, '-' will be shown if there is space left.
 */
void c4dot_write_int_hex ( c4dotmatrixr_t *ctx, int16_t int_to_write );

/**
 * @brief 4DotMatrix Display Clear.
 *
 * 
 * @param ctx           Click object.
 * 
 * @description This function clears all four display characters.
 */
void c4dot_clear_display ( c4dotmatrixr_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C4DOTMATRIXR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
