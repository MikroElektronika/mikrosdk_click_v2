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
 * \brief This file contains API for OLED C Click driver.
 *
 * \addtogroup oledc OLED C Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OLEDC_H
#define OLEDC_H

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

#define OLEDC_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rw = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.dc = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.en = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OLEDC_RETVAL  uint8_t

#define OLEDC_OK           0x00
#define OLEDC_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup font_dir Font Direction
 * \{
 */
#define OLEDC_FO_HORIZONTAL       0x00
#define OLEDC_FO_VERTICAL         0x01
#define OLEDC_FO_VERTICAL_COLUMN  0x02
/** \} */

/**
 * \defgroup remamp_set Remamp Settings
 * \{
 */
#define OLEDC_RMP_INC_HOR         0x00
#define OLEDC_RMP_INC_VER         0x01
#define OLEDC_RMP_COLOR_NOR       0x00
#define OLEDC_RMP_COLOR_REV       0x02
#define OLEDC_RMP_SEQ_RGB         0x00
#define OLEDC_RMP_SEQ_BGR         0x04
#define OLEDC_RMP_SCAN_NOR        0x00
#define OLEDC_RMP_SCAN_REV        0x10
#define OLEDC_RMP_SPLIT_DISABLE   0x00
#define OLEDC_RMP_SPLIT_ENABLE    0x20
#define OLEDC_COLOR_65K           0x00
#define OLEDC_COLOR_262K          0x80
#define OLEDC_IMG_HEAD            0x06
/** \} */

/**
 * \defgroup dev_proper Device Properties
 * \{
 */
#define OLEDC_SCREEN_WIDTH    0x60
#define OLEDC_SCREEN_HEIGHT   0x60
#define OLEDC_SCREEN_SIZE     0x2400
#define OLEDC_ROW_OFF         0x00
#define OLEDC_COL_OFF         0x10
/** \} */

/**
 * \defgroup commands Commands
 * \{
 */
#define OLEDC_SET_COL_ADDRESS   0x15
#define OLEDC_SET_ROW_ADDRESS   0x75
#define OLEDC_WRITE_RAM         0x5C
#define OLEDC_READ_RAM          0x5D
#define OLEDC_SET_REMAP         0xA0
#define OLEDC_SET_START_LINE    0xA1
#define OLEDC_SET_OFFSET        0xA2
#define OLEDC_MODE_OFF          0xA4
#define OLEDC_MODE_ON           0xA5
#define OLEDC_MODE_NORMAL       0xA6
#define OLEDC_MODE_INVERSE      0xA7
#define OLEDC_FUNCTION          0xAB
#define OLEDC_SLEEP_ON          0xAE
#define OLEDC_SLEEP_OFF         0xAF
#define OLEDC_NOP               0xB0
#define OLEDC_SET_RESET_PRECH   0xB1
#define OLEDC_ENHANCEMENT       0xB2
#define OLEDC_CLOCK_DIV         0xB3
#define OLEDC_VSL               0xB4
#define OLEDC_GPIO              0xB5
#define OLEDC_SETSEC_PRECH      0xB6
#define OLEDC_GREY_SCALE        0xB8
#define OLEDC_LUT               0xB9
#define OLEDC_PRECH_VOL         0xBB
#define OLEDC_VCOMH             0xBE
#define OLEDC_CONTRAST          0xC1
#define OLEDC_MASTER_CONTRAST   0xC7
#define OLEDC_MUX_RATIO         0xCA
#define OLEDC_COMMAND_LOCK      0xFD
#define OLEDC_SCROLL_HOR        0x96
#define OLEDC_START_MOV         0x9E
#define OLEDC_STOP_MOV          0x9F


#define OLEDC_DEFAULT_MUX_RATIO  95
#define OLEDC_DEFAULT_START_LINE 0x80
#define OLEDC_DEFAULT_OFFSET     0x20

#define OLEDC_DEFAULT_OLED_LOCK     0x12
#define OLEDC_DEFAULT_CMD_LOCK      0xB1
#define OLEDC_DEFAULT_DIVSET        0xF1
#define OLEDC_DEFAULT_PRECHARGE     0x32
#define OLEDC_DEFAULT_VCOMH         0x05
#define OLEDC_DEFAULT_MASTER_CONT   0xCF
#define OLEDC_DEFAULT_PRECHARGE_2   0x01
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

    digital_out_t rw;
    digital_out_t rst;
    digital_out_t dc;
    digital_out_t en;
    digital_out_t cs;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;
    
    const uint8_t*   font_obj;
    uint16_t         font_color;
    uint8_t          font_orientation;
    uint16_t         font_first_char;
    uint16_t         font_last_char;
    uint16_t         font_height;
    uint16_t         x_cord;
    uint16_t         y_cord;

} oledc_t;

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

    pin_name_t rw;
    pin_name_t rst;
    pin_name_t dc;
    pin_name_t en;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} oledc_cfg_t;

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
void oledc_cfg_setup ( oledc_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param oledc Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
OLEDC_RETVAL oledc_init ( oledc_t *ctx, oledc_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for OLED C click.
 */
void oledc_default_cfg ( oledc_t *ctx );

/**
 * @brief Click Enable/Disable.
 *
 * @param ctx  Context object.
 * @param state  1 - ON / 0 - OFF.
 *
 * @description Function allows user to enable or disable the display.
 */
void oledc_enable ( oledc_t *ctx, uint8_t state );

/**
 * @brief Click Hardware Reset.
 *
 * @param ctx  Context object.
 *
 * @description Function performs a hardware reset of the click.
 */
void oledc_reset( oledc_t *ctx );

/**
 * @brief Command Send with more argument.
 *
 * @param ctx  Context object.
 * @param cmd  Command to be sent.
 * @param args  Pointer to command argument.
 * @param args_len  Argument size in bytes.
 *
 * @description Function executes a provided command.
 */
void oledc_more_arg_commands ( oledc_t *ctx, uint8_t command, uint8_t *args, uint16_t args_len );

/**
 * @brief Command Send with one argument.
 *
 * @param ctx  Context object.
 * @param cmd  Command to be sent.
 * @param args One command argument.
 *
 * @description Function executes a provided command.
 */
void oledc_one_arg_commands ( oledc_t *ctx, uint8_t command, uint8_t args );

/**
 * @brief Fill Screen.
 *
 * @param ctx  Context object.
 * @param color  RGB color.
 *
 * @description Function fills an entire screen with the provided color.
 */
void oledc_fill_screen ( oledc_t *ctx, uint16_t color );

/**
 * @brief Draw Rectangle.
 *
 * @param ctx  Context object.
 * @param col_off  Column offset from the left border of the screen.
 * @param row_off  Row offset from the top border of the screen.
 * @param col_end  Column end offset also counted from the left border.
 * @param row_end  Row offset also counted from the top border.
 * @param color  RGB color.
 *
 * @description Function allows user to draw rectangles.
 */
void oledc_rectangle( oledc_t *ctx, uint8_t col_off, uint8_t row_off, uint8_t col_end, uint8_t row_end, uint16_t color );

/**
 * @brief Draw BMP Image.
 *
 * @param ctx  Context object.
 * @param col_off  Column offset from the left border of the screen.
 * @param row_off  Row offset from the top border of the screen.
 * @param img  Pointer to bmp image.
 *
 * @description Function draws image on the screen. Provided image must be in
 * bmp format with 6 bytes header size. Providing image of any other format may
 * result in unpredictable behaviour.
 */
void oledc_image( oledc_t *ctx, const uint8_t* img, uint8_t col_off, uint8_t row_off );

/**
 * @brief Draw Text.
 *
 * @param ctx  Context object.
 * @param text  Text string.
 * @param col_off  Column offset from the left border of the screen.
 * @param row_off  Row offset from the top border of the screen.
 *
 * @description Function writes text on the screen.
 */
void oledc_text( oledc_t *ctx, uint8_t *text, uint16_t x, uint16_t y );

/**
 * @brief Font Setup.
 *
 * @param ctx  Context object.
 * @param font  Pointer to font definition.
 * @param color  Text color.
 *
 * @description Function setup the parameters needed for @c oledc_text function.
 * Before first usage of the @c oledc_text it is needed to call this function
 * and setup the all parameters.
 */
void oledc_set_font( oledc_t *ctx, const uint8_t *font_s, uint16_t color );

#ifdef __cplusplus
}
#endif
#endif  // _OLEDC_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
