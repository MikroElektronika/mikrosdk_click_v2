/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file c7x10g.h
 * @brief This file contains API for 7x10 G Click Driver.
 */

#ifndef C7X10G_H
#define C7X10G_H

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

#define C7X10G_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rc = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.rr = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup display_delay Display delay 
 * \{
 */
#define C7X10G_DISPLAY_DELAY_5MS  5
#define C7X10G_DISPLAY_DELAY_10MS 10
#define C7X10G_DISPLAY_DELAY_20MS 20
#define C7X10G_DISPLAY_DELAY_35MS 35
#define C7X10G_DISPLAY_DELAY_50MS 50
#define C7X10G_DISPLAY_DELAY_100MS 100
#define C7X10G_DISPLAY_DELAY_150MS 150
/** \} */

/**
 * \defgroup display_refresh_ch Display refresh (drawing character)
 * \{
 */
#define C7X10G_DISPLAY_LEFT    0x00
#define C7X10G_DISPLAY_RIGHT   0x01
#define C7X10G_DISPLAY_REFRESH 0x10
/** \} */

/**
 * \defgroup display_refresh_px Display refresh (drawing pixels)
 * \{
 */
#define C7X10G_DISPLAY_PIXEL_REFRESH 0x01
#define C7X10G_DISPLAY_PIXEL_STORAGE 0x00
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
    digital_out_t cs;
   
    // Output pins 

    digital_out_t rc;
    digital_out_t rst;
    digital_out_t rr;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} c7x10g_t;

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

    pin_name_t rc;
    pin_name_t rst;
    pin_name_t rr;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} c7x10g_cfg_t;

/**
 * @brief pixel structure definition.
 */
typedef struct
{
    uint8_t cord_x;
    uint8_t cord_y;

} c7x10g_pixel_t;

typedef enum
{
    
    C7X10G_OK = 0,
    C7X10G_ERROR = -1

} c7x10g_return_value_t;

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
void c7x10g_cfg_setup ( c7x10g_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
c7x10g_return_value_t c7x10g_init ( c7x10g_t *ctx, c7x10g_cfg_t *cfg );

/**
 * @brief Display process (function).
 *
 * @param ctx           Click object.
 * @param frame         Frame buffer (14 bytes).
 * @param disp_delay    Delay in ms per one display.
 *
 * @description Drawing the frame on the display.
 */
void c7x10g_display_process ( c7x10g_t *ctx, uint8_t *frame, uint16_t disp_delay );

/**
 * @brief Draw pixel (function).
 *
 * @param ctx       Click object.
 * @param pixel     Pixel structure (pixel coordinate forwarding).
 * @param px_delay  Delay in ms per one display.
 *
 * @description Drawing the pixel on the display.
 */
void c7x10g_draw_pixel ( c7x10g_t *ctx, c7x10g_pixel_t *pixel, uint8_t mode, uint8_t px_delay );

/**
 * @brief Draw char (function).
 *
 * @param ctx       Click object.
 * @param ch        Character from the font that is drawn on the screen.
 * @param pos       Character position (Left or Right) with refresh mode selection
 * @param ch_delay  Delay in ms per one display.
 *
 * @description Drawing the character on the display.
 */
void c7x10g_draw_char ( c7x10g_t *ctx, char ch, uint8_t pos, uint8_t ch_delay );

/**
 * @brief Draw number (function).
 *
 * @param ctx        Click object.
 * @param num        Number from the font that is drawn on the screen.(Number is from 0 to 99)
 * @param num_delay  Delay in ms per one display.
 *
 * @description Drawing the number on the display.
 */
void c7x10g_draw_number ( c7x10g_t *ctx, uint8_t num, uint16_t num_delay );

#ifdef __cplusplus
}
#endif
#endif  // _C7X10G_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
