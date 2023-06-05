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
 * \brief This file contains API for RGB Driver Click driver.
 *
 * \addtogroup rgbdriver RGB Driver Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RGBDRIVER_H
#define RGBDRIVER_H

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
#define RGBDRIVER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RGBDRIVER_RETVAL  uint8_t

#define RGBDRIVER_OK           0x00
#define RGBDRIVER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup color_set Color Set
 * \{
 */

#define RGBDRIVER_COLOR_RED_HIGH_INTENSITY       0x7F8040
#define RGBDRIVER_COLOR_ORANGE_HIGH_INTENSITY    0x7F8240
#define RGBDRIVER_COLOR_YELLOW_HIGH_INTENSITY    0x7F9440
#define RGBDRIVER_COLOR_GREEN_HIGH_INTENSITY     0x609F40
#define RGBDRIVER_COLOR_BLUE_HIGH_INTENSITY      0x60805F
#define RGBDRIVER_COLOR_WHITE_HIGH_INTENSITY     0x7F9F5F
#define RGBDRIVER_COLOR_PURPLE_HIGH_INTENSITY    0x78805C

#define RGBDRIVER_COLOR_RED_LOW_INTENSITY       0x618040
#define RGBDRIVER_COLOR_ORANGE_LOW_INTENSITY    0x6A8140
#define RGBDRIVER_COLOR_YELLOW_LOW_INTENSITY    0x6A8540
#define RGBDRIVER_COLOR_GREEN_LOW_INTENSITY     0x608140
#define RGBDRIVER_COLOR_BLUE_LOW_INTENSITY      0x608041
#define RGBDRIVER_COLOR_WHITE_LOW_INTENSITY     0x618141
#define RGBDRIVER_COLOR_PURPLE_LOW_INTENSITY    0x658044

#define RGBDRIVER_COLOR_OFF       0x000000
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
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} rgbdriver_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} rgbdriver_cfg_t;

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
void rgbdriver_cfg_setup ( rgbdriver_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RGBDRIVER_RETVAL rgbdriver_init ( rgbdriver_t *ctx, rgbdriver_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for RGB Driver click.
 */
RGBDRIVER_RETVAL rgbdriver_default_cfg ( rgbdriver_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void rgbdriver_generic_write ( rgbdriver_t *ctx, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function set RGB color.
 *
 * @param ctx          Click object.
 * @param red          Red led.
 * @param green        Green led. 
 * @param blue         Blue led.
 *
 * @description This function sets the color of the rgb LEDs through the parameters for red, green and blue.
 */
void rgbdriver_set_rgb_color ( rgbdriver_t *ctx, uint8_t red, uint8_t green, uint8_t blue );

/**
 * @brief Function set color.
 *
 * @param ctx          Click object.
 * @param color        Red led.
 *
 * @description This function sets the color.
 * 
 * @note 
 * Set color:
 *    RED,
 *    GREEN,
 *    BLUE,
 *    YELLOW,
 *    WHITE,
 *    PURPLE,
 *    ORANGE and OFF.
 */
void rgbdriver_set_color ( rgbdriver_t *ctx, uint32_t color );

/**
 * @brief Shut down function.
 *
 * @param ctx          Click object.
 *
 * @description This function shut down device.
 */
void rgbdriver_shut_down ( rgbdriver_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _RGBDRIVER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
