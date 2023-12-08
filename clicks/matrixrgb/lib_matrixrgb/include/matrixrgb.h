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
 * \brief This file contains API for Matrix RGB Click driver.
 *
 * \addtogroup matrixrgb Matrix RGB Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MATRIXRGB_H
#define MATRIXRGB_H

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
#include "drv_spi_master.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define MATRIXRGB_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.slp   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.rdy   = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MATRIXRGB_RETVAL  uint8_t

#define MATRIXRGB_OK           0x00
#define MATRIXRGB_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup font_alignment Font Alignment 
 * \{
 */
#define MATRIXRGB_FONT_HORIZONTAL                 0
#define MATRIXRGB_FONT_VERTICAL                   1
#define MATRIXRGB_FONT_VERTICAL_COLUMN            2
/** \} */

/**
 * \defgroup pattern Pattern 
 * \{
 */
#define MATRIXRGB_PATTERN_1_MAP_5MM               0x00
#define MATRIXRGB_PATTERN_1_MAP_6MM               0x01
#define MATRIXRGB_PATTERN_2H_MAP_5MM              0x02
#define MATRIXRGB_PATTERN_2H_MAP_6MM              0x03
#define MATRIXRGB_PATTERN_2V_MAP_5MM              0x04
#define MATRIXRGB_PATTERN_2V_MAP_6MM              0x05
#define MATRIXRGB_PATTERN_3H_MAP_5MM              0x06
#define MATRIXRGB_PATTERN_3H_MAP_6MM              0x07
#define MATRIXRGB_PATTERN_3V_MAP_5MM              0x08
#define MATRIXRGB_PATTERN_3V_MAP_6MM              0x09
#define MATRIXRGB_PATTERN_4H_MAP_5MM              0x0A
#define MATRIXRGB_PATTERN_4H_MAP_6MM              0x0B
#define MATRIXRGB_PATTERN_4V_MAP_5MM              0x0C
#define MATRIXRGB_PATTERN_4V_MAP_6MM              0x0D
#define MATRIXRGB_PATTERN_4S_MAP_5MM              0x0E
#define MATRIXRGB_PATTERN_4S_MAP_6MM              0x0F
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
    uint8_t  *p_font;
    uint16_t color;
    uint8_t  orientation;
    uint16_t first_char;
    uint16_t last_char;
    uint16_t height;

} matrixrgb_font_t;

typedef struct 
{
    uint16_t pixel_width;
    uint16_t pixel_height;
    uint16_t ram_size;
    
} matrixrgb_pixel_t;

typedef struct 
{
    uint16_t x_cord;
    uint16_t y_cord;

} matrixrgb_cord_t;

typedef struct
{
    // Output pins 

    digital_out_t rst;
    digital_out_t slp;
    digital_out_t cs;

    // Input pins 

    digital_in_t rdy;
    
    // Modules 

    spi_master_t spi;
    matrixrgb_font_t device_font;
    matrixrgb_pixel_t device_pixel;
    matrixrgb_cord_t device_font_cord;
    uint16_t device_pattern_delay;
    pin_name_t chip_select;

} matrixrgb_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t slp;
    pin_name_t rdy;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;
    matrixrgb_font_t dev_font;

} matrixrgb_cfg_t;

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
void matrixrgb_cfg_setup ( matrixrgb_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param matrixrgb Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MATRIXRGB_RETVAL matrixrgb_init ( matrixrgb_t *ctx, matrixrgb_cfg_t *cfg );

/**
 * @brief Click Pattern settings ( Default Configuration ) function.
 *
 * @param ctx               Click object.
 * @param pattern_type      Pattern type of display. 
 * @param pattern_delay_us  Choose time for delay.
 * 
 * @description This function executes default configuration for Matrix RGB click.
 */
void matrixrgb_pattern_settings ( matrixrgb_t *ctx, uint8_t pattern_type, uint16_t pattern_delay_us );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void matrixrgb_generic_transfer 
( 
    matrixrgb_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Hard reset of the Matrix RGB click
 *
 * @param ctx          Click object.
 *
 * @description Function takes 300 ms.
 */
void matrixrgb_device_reset ( matrixrgb_t *ctx );

/**
 * @brief Firmware Initialization
 *
 * @param ctx          Click object.
 * @param pattern_id   Panel Pattern ID - more info inside firmware documentation
 *
 * @description This function mus be executed right after driver initialization.
 */
uint8_t matrixrgb_device_settings ( matrixrgb_t *ctx, uint8_t pattern_id );

/**
 * @brief Set Power
 *
 * @param ctx           Click object.
 * @param power_state   Power State (0 - OFF / 1 - ON)
 *
 */
void matrixrgb_set_power ( matrixrgb_t *ctx, uint8_t power_state );

/**
 * @brief Set Brightness
 *
 * @param ctx           Click object.
 * @param brightness    Brightness intensity
 *
 * @warning
 * In case of high brightness level flickering may appears due to fact
 * that this is software brightness implementation.
 */
void matrixrgb_set_brightness ( matrixrgb_t *ctx, uint8_t brightness );

/**
 * @brief Write Pixel
 *
 * @param ctx           Click object.
 * @param x             horizontal position
 * @param y             vertical position
 * @param color         pixel color
 *
 * @return 
 * 0 OK / 1 Error
 * 
 * @note 
 * Error may appear in case of wrong X or Y positions.
 */
uint8_t matrixrgb_write_pixel ( matrixrgb_t *ctx, uint16_t x, uint16_t y, uint16_t color );

/**
 * @brief Fill Screen
 *
 * @param ctx           Click object.
 * @param color         color screen color
 *
 */
void matrixrgb_fill_screen ( matrixrgb_t *ctx, uint16_t color );

/**
 * @brief Draw Image on Panel
 *
 * @param ctx                Click object.
 * @param device_img         Pointer to image array
 *
 * @note
 * Image must be in RGB565 format LSB first.
 */
void matrixrgb_draw_image ( matrixrgb_t *ctx, const uint8_t *device_img );

/**
 * @brief Set Font Function
 *
 * @param ctx           Click object.
 * @param font_cfg      Pointer on structure
 *
 * @description  Must be called before write text function to adjust text related properties.
 */
void matrixrgb_set_font ( matrixrgb_t *ctx, matrixrgb_font_t *font_cfg );

/**
 * @brief Writes Text
 *
 * 
 * @param ctx           Click object. 
 * @param text          
 * @param x             Horizontal offset
 * @param y             Vertical offset
 *
 * @return 
 * 0 OK / 1 Error
 *
 * @description Writing starts at provided offset
 *
 * @note 
 * Error may appear in case of wrong X or Y positions.
 */
uint8_t matrixrgb_write_text ( matrixrgb_t *ctx, char *text, uint16_t x, uint16_t y );


#ifdef __cplusplus
}
#endif
#endif  // _MATRIXRGB_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
