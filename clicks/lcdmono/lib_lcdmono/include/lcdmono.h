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
 * \brief This file contains API for LCD Mono Click driver.
 *
 * \addtogroup lcdmono LCD Mono Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LCDMONO_H
#define LCDMONO_H

#include "drv_digital_out.h"
#include "drv_spi_master.h"
#include "generic_pointer.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define LCDMONO_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.com   = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LCDMONO_OK                      0
#define LCDMONO_ERROR                  -1
/** \} */

/**
 * \defgroup display_resolution  Display resolution
 * \{
 */
#define LCDMONO_DISPLAY_WIDTH           128
#define LCDMONO_DISPLAY_HEIGHT          128
#define LCDMONO_DISPLAY_RESOLUTIONS     2307
/** \} */

/**
 * \defgroup lcd_color  LCD color
 * \{
 */
#define LCDMONO_COLOR_WHITE             0x00
#define LCDMONO_COLOR_BLACK             0x01
/** \} */

/**
 * \defgroup text_and_mode  Text and mode
 * \{
 */
#define LCDMONO_REFRESH_DISPLAY_END     0x01
#define LCDMONO_CHECK_NEW_TEXT          0x00
#define LCDMONO_REFRESH_TEXT_BUFFER     0x10
/** \} */

/**
 * \defgroup display_flag  Display flag
 * \{
 */
#define LCDMONO_CMD_DISPLAY_FLAG        0x80
#define LCDMONO_CMD_CLEAR_FLAG          0x20
#define LCDMONO_DUMMY_BYTE              0x00
/** \} */

/**
 * \defgroup power_state  Power state
 * \{
 */
#define LCDMONO_POWER_ON                1
#define LCDMONO_POWER_OFF               0
/** \} */

/** \} */ // End group macro
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct
{
    uint8_t * __generic_ptr this_font;
    uint16_t first_char;
    uint16_t last_char;
    uint16_t height;

} lcdmono_font_t;

typedef struct
{
    uint16_t x;
    uint16_t y;

} lcdmono_coordinate_t;

typedef struct
{
    // Draw Text
    uint8_t len;             // Number of characters in the text
    uint16_t start_cord_x;   // X position of the text
    uint16_t start_cord_y;   // Y position of the text
    uint8_t bg_color;        // Background color

} lcdmono_text_settings_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins
    digital_out_t com;

    // Modules
    spi_master_t spi;
    pin_name_t chip_select;

    uint8_t lcd_frame[ 2307 ];
    uint8_t lcd_frame_color;

    lcdmono_font_t lcd_font;
    lcdmono_coordinate_t lcd_cord;
    lcdmono_text_settings_t tx_set;

} lcdmono_t;

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
    pin_name_t com;

    // Static variable
    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    uint8_t dev_lcd_frame_color;

} lcdmono_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void lcdmono_cfg_setup ( lcdmono_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param lcdmono Click object.
 * @param cfg Click configuration structure.
 *
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t lcdmono_init ( lcdmono_t *ctx, lcdmono_cfg_t *cfg );

/**
 * @brief Send line data package
 *
 * @param ctx        Click object.
 * @param addr       Line address [from 1 to 128]
 * @param tx_data    16 bytes[128 bits] data
 *
 * @details Function just adding a command to display update and 2 x Dummy data at the end
 */
void lcdmono_send_line_package ( lcdmono_t *ctx, uint8_t addr, uint8_t * __generic_ptr tx_data );

/**
 * @brief Clear display
 *
 * @param ctx          Click object.
 */
void lcdmono_clear ( lcdmono_t *ctx );

/**
 * @brief Displays draw frame
 *
 * @param ctx              Click object.
 * @param frame_data       Buffer the frame data [ or image ]
 *
 * @note
 * The image can be built from VTFT or image2lcd programs
 * The image type monochrome bmp 128x128px
 */
void lcdmono_draw_frame ( lcdmono_t *ctx, uint8_t * __generic_ptr frame_data );

/**
 * @brief Draw text on the screen
 *
 * @param ctx         Click object.
 * @param text_buf    Text buffer
 * @param tx_set      Text settings - Structure for settings text
 * @param end_mode    Mode
 *
 * Mode options:
 *   - REFRESH_TEXT_BUFFER  - Reset the main frame buffer.
 *   - CHECK_NEW_TEXT       - Insert text into the main frame buffer - no update display
 *   - REFRESH_DISPLAY_END  - Insert text into the main frame buffer - with the update display
 */
void lcdmono_draw_text ( lcdmono_t *ctx, uint8_t * __generic_ptr text_buf, lcdmono_text_settings_t *tx_set, uint8_t end_mode );

/**
 * @brief Set font
 *
 * @param ctx              Click object.
 * @param dev_lcd_font     Select new active font
 */
void lcdmono_set_font ( lcdmono_t *ctx, lcdmono_font_t *dev_lcd_font );

/**
 * @brief Display Power State
 *
 * @param ctx      Click object.
 * @param ctrl     Power on or power off display
 */
void lcdmono_display_power ( lcdmono_t *ctx, uint8_t ctrl );

/**
 * @brief Reset procedure
 *
 * @param ctx         Click object.
 */
void lcdmono_display_reset ( lcdmono_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // LCDMONO_H

/** \} */ // End public_function group
/// \}    // End click Driver group
/*! @} */
// ------------------------------------------------------------------------ END
