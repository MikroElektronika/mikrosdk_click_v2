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
 * \brief This file contains API for eINK 213 Inch Click driver.
 *
 * \addtogroup eink_213inch eINK 213 Inch Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EINK213INCH_H
#define EINK213INCH_H

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

#define EINK213INCH_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.dc = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.bsy = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EINK213INCH_RETVAL  uint8_t

#define EINK213INCH_OK           0x00
#define EINK213INCH_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup display_resolution Display resolution
 * \{
 */
#define EINK213_DISPLAY_WIDTH          128
#define EINK213_DISPLAY_HEIGHT         250
#define EINK213_DISPLAY_RESOLUTIONS   4000
/** \} */

/**
 * \defgroup display_communication Display Communication
 * \{
 */
#define EINK213_COMMUNICATION_SPI        0
#define EINK213_COMMUNICATION_I2C        1
/** \} */

/**
 * \defgroup fill_screen_color Fill screen color
 * \{
 */
#define EINK213_SCREEN_COLOR_WHITE        0xFF
#define EINK213_SCREEN_COLOR_BLACK        0x00
#define EINK213_SCREEN_COLOR_LIGHT_GREY   0xAA
#define EINK213_SCREEN_COLOR_DARK_GREY    0x55

#define EINK213_FO_HORIZONTAL             0x00
#define EINK213_FO_VERTICAL               0x01
#define EINK213_FO_VERTICAL_COLUMN        0x02
/** \} */

/**
 * \defgroup display_commands Display Commands
 * \{
 */
#define EINK213_CMD_DRIVER_OUTPUT_CONTROL                       0x01
#define EINK213_CMD_BOOSTER_SOFT_START_CONTROL                  0x0C
#define EINK213_CMD_GATE_SCAN_START_POSITION                    0x0F
#define EINK213_CMD_DEEP_SLEEP_MODE                             0x10
#define EINK213_CMD_DATA_ENTRY_MODE_SETTING                     0x11
#define EINK213_CMD_SW_RESET                                    0x12
#define EINK213_CMD_TEMPERATURE_SENSOR_CONTROL                  0x1A
#define EINK213_CMD_MASTER_ACTIVATION                           0x20
#define EINK213_CMD_DISPLAY_UPDATE_CONTROL_1                    0x21
#define EINK213_CMD_DISPLAY_UPDATE_CONTROL_2                    0x22
#define EINK213_CMD_WRITE_RAM                                   0x24
#define EINK213_CMD_WRITE_VCOM_REGISTER                         0x2C
#define EINK213_CMD_WRITE_LUT_REGISTER                          0x32
#define EINK213_CMD_SET_DUMMY_LINE_PERIOD                       0x3A
#define EINK213_CMD_SET_GATE_TIME                               0x3B
#define EINK213_CMD_BORDER_WAVEFORM_CONTROL                     0x3C
#define EINK213_CMD_SET_RAM_X_ADDRESS_START_END_POSITION        0x44
#define EINK213_CMD_SET_RAM_Y_ADDRESS_START_END_POSITION        0x45
#define EINK213_CMD_SET_RAM_X_ADDRESS_COUNTER                   0x4E
#define EINK213_CMD_SET_RAM_Y_ADDRESS_COUNTER                   0x4F
#define EINK213_CMD_TERMINATE_FRAME_READ_WRITE                  0xFF
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct 
{
    const uint8_t    *p_font;
    uint16_t         color;
    uint8_t          orientation;
    uint16_t         first_char;
    uint16_t         last_char;
    uint16_t         height;

} eink_213inch_font_t;

typedef struct 
{
    uint16_t x;
    uint16_t y;  

} eink_213inch_cord_t;

typedef struct 
{
    uint16_t x_start;
    uint16_t y_start;
    uint16_t x_end;
    uint16_t y_end;

} eink_213inch_xy_t;

typedef struct 
{
    uint8_t n_char;
    uint16_t text_x; 
    uint16_t text_y;

} eink_213inch_set_text_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t cs;
    digital_out_t rst;
    digital_out_t dc;

    // Input pins 

    digital_in_t bsy;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

#ifndef IMAGE_MODE_ONLY
    uint8_t frame[ 4000 ];
#endif

    eink_213inch_font_t dev_font;
    eink_213inch_cord_t dev_cord; 

} eink_213inch_t;

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
    pin_name_t dc;
    pin_name_t bsy;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} eink_213inch_cfg_t;

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
void eink_213inch_cfg_setup ( eink_213inch_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
EINK213INCH_RETVAL eink_213inch_init ( eink_213inch_t *ctx, eink_213inch_cfg_t *cfg );

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
void eink_213inch_generic_transfer ( eink_213inch_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Function for sending a command
 *
 * @param ctx          Click object.
 * @param command      The command to be sent
 */
void eink_213_send_command ( eink_213inch_t *ctx, uint8_t command );

/**
 * @brief Function for sending data
 *
 * @param ctx          Click object.
 * @param c_data       The data to be sent
 */
void eink_213_send_data ( eink_213inch_t *ctx, uint8_t c_data );

/**
 * @brief Function for reset chip
 * 
 * @param ctx          Click object.
 */
void eink_213_reset ( eink_213inch_t *ctx );

/**
 * @brief Function for go to sleep mode
 * 
 * @param ctx          Click object. 
 */
void eink_213_sleep_mode ( eink_213inch_t *ctx );

/**
 * @brief Set LUT table
 *
 * @param ctx          Click object.
 * @param lut          Lut table
 * @param n_bytes      Number of bytes in Lut table
 *
 * @Note Changing the "lut table" can change the display's performance.
 */
void eink_213_set_lut ( eink_213inch_t *ctx, const uint8_t *lut, uint8_t n_bytes );

/**
 * @brief Start configuration display
 * 
 * @param ctx          Click object.
 */
void eink_213_start_config ( eink_213inch_t *ctx );

/**
 * @brief Function for setting pointers in memory
 *
 * @param ctx          Click object.
 * @param x            x position
 * @param y            y position
 */
void eink_213_set_memory_pointer ( eink_213inch_t *ctx, uint16_t x, uint16_t y );

/**
 * @brief Function for setting area in memory
 * 
 * @param ctx          Click object.
 * @param xy           Struct object
 */
void eink_213_set_memory_area( eink_213inch_t *ctx, eink_213inch_xy_t *xy );

/**
 * @brief Functions for update display
 * 
 * @param ctx          Click object.
 */
void eink_213_update_display ( eink_213inch_t *ctx );

/**
 * @brief Function that fills the screen
 *
 * @param ctx          Click object.
 * @param color        The color to which the screen will be colored
 *
 * @note Options :
      EINK213_SCREEN_COLOR_WHITE
      EINK213_SCREEN_COLOR_BLACK
      EINK213_SCREEN_COLOR_LIGHT_GREY
      EINK213_SCREEN_COLOR_DARK_GREY
 */
void eink_213_fill_screen ( eink_213inch_t *ctx, uint8_t color );

/**
 * @brief Display image function
 *
 * @param ctx          Click object.
 * @param image       Buffer containing the image
 *
 * @description The image can be built from VTFT or image2lcd programs
 * @note  The image type must be monochrome bmp
 */
void eink_213_display_image ( eink_213inch_t *ctx, const uint8_t* image_buffer );

/**
 * @brief Function for draw text on the screen
 *
 * @param ctx          Click object. 
 * @param text         Text buffer
 * @param text_set     Struct object
 *
 */
void eink_213_text ( eink_213inch_t *ctx, char *text, eink_213inch_set_text_t *text_set );

/**
 * @brief Set font function
 *
 * @param ctx                Click object.
 * @param cfg_font           Struct object
 */
void eink_213_set_font ( eink_213inch_t *ctx, eink_213inch_font_t *cfg_font );

#ifdef __cplusplus
}
#endif
#endif  // _EINK213INCH_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
