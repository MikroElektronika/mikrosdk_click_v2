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
 * \brief This file contains API for LED Driver 3 Click driver.
 *
 * \addtogroup leddriver3 LED Driver 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LEDDRIVER3_H
#define LEDDRIVER3_H

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
#define LEDDRIVER3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LEDDRIVER3_RETVAL  uint8_t

#define LEDDRIVER3_OK           0x00
#define LEDDRIVER3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup color_set Color Set
 * \{
 */
#define LEDDRIVER3_COLOR_RED      0x5F6080
#define LEDDRIVER3_COLOR_ORANGE   0x5F6280
#define LEDDRIVER3_COLOR_YELLOW   0x5F7480
#define LEDDRIVER3_COLOR_GREEN    0x407F80
#define LEDDRIVER3_COLOR_BLUE     0x40609F
#define LEDDRIVER3_COLOR_WHITE    0x5F7F9F
#define LEDDRIVER3_COLOR_PURPLE   0x58609C
#define LEDDRIVER3_COLOR_OFF      0x000000
/** \} */

/**
 * \defgroup set_timer Set Timer
 * \{
 */
#define LEDDRIVER3_TIMER_8ms      0xE1
#define LEDDRIVER3_TIMER_16ms     0xE2
#define LEDDRIVER3_TIMER_32ms     0xE4
#define LEDDRIVER3_TIMER_64ms     0xE8
#define LEDDRIVER3_TIMER_128ms    0xE0
/** \} */

/**
 * \defgroup set_intensity Set Intensity
 * \{
 */
#define LEDDRIVER3_INTENSITY_1    0x01
#define LEDDRIVER3_INTENSITY_2    0x02
#define LEDDRIVER3_INTENSITY_4    0x04
#define LEDDRIVER3_INTENSITY_8    0x08
#define LEDDRIVER3_INTENSITY_16   0x10

#define LEDDRIVER3_INCREMENT      0xA0
#define LEDDRIVER3_DECREMENT      0xC0
#define LEDDRIVER3_CONSTANT       0x20
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief RGB color value definition.
 */
typedef struct 
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} leddriver3_rgb_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} leddriver3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    i2c_master_speed_t i2c_speed;
    uint8_t i2c_address;

} leddriver3_cfg_t;

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
void leddriver3_cfg_setup ( leddriver3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param leddriver3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LEDDRIVER3_RETVAL leddriver3_init ( leddriver3_t *ctx, leddriver3_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param mode         I2C mode select.
 *
 * @description This function writes data to the desired register.
 */
void leddriver3_generic_write ( leddriver3_t *ctx, uint8_t reg, uint8_t mode );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void leddriver3_generic_read ( leddriver3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set intensity function.
 *
 * @param ctx          Click object.
 * @param intensity    Intensity of light.
 *
 * @description This function set intensity of light.
 * @note Set options:
 *        increase the light width intensity
 *        decrease the light width intensity
 *        constant the light width intensity
 */
void leddriver3_set_intensity ( leddriver3_t *ctx, uint8_t intensity );

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
void leddriver3_set_rgb_color ( leddriver3_t *ctx, leddriver3_rgb_t *rgb );

/**
 * @brief Function set color.
 *
 * @param ctx          Click object.
 * @param color        RGB color.
 *
 * @description This function sets color.
 * @note Set color:
 *        RED,
 *        GREEN,
 *        BLUE,
 *        YELLOW,
 *        WHITE,
 *        PURPLE,
 *        ORANGE and OFF.
 */
void leddriver3_set_color ( leddriver3_t *ctx, uint32_t color );

/**
 * @brief Shut down function.
 *
 * @param ctx          Click object.
 *
 * @description This function shut down device.
 */
void leddriver3_shut_down ( leddriver3_t *ctx );

/**
 * @brief Set timer function.
 *
 * @param ctx          Click object.
 * @param time         Time in ms.
 *
 * @description This function sets timer for increase or decrease light.
 */
void leddriver3_set_timer ( leddriver3_t *ctx, uint8_t time );

#ifdef __cplusplus
}
#endif
#endif  // _LEDDRIVER3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
