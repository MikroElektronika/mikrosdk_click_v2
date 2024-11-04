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
 * \brief This file contains API for eINK 2.00 inch Click driver.
 *
 * \addtogroup eink eINK 2.00 inch Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EINK_H
#define EINK_H

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

#define EINK_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.dc    = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.bsy   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EINK_OK                                             0
#define EINK_ERROR                                         -1
/** \} */

/**
 * \defgroup display_resolution  Display resolution
 * \{
 */
#define EINK_DISPLAY_WIDTH                                  72
#define EINK_DISPLAY_HEIGHT                                 172
#define EINK_DISPLAY_RESOLUTION                             3096
/** \} */

/**
 * \defgroup display_communication  Display Communication
 * \{
 */
#define EINK_COMMUNICATION_SPI                              0
#define EINK_COMMUNICATION_I2C                              1
/** \} */

/**
 * \defgroup fill_screen_color  Fill screen color
 * \{
 */
#define EINK_SCREEN_COLOR_WHITE                             0xFF
#define EINK_SCREEN_COLOR_BLACK                             0x00
#define EINK_SCREEN_COLOR_LIGHT_GREY                        0xAA
#define EINK_SCREEN_COLOR_DARK_GREY                         0x55

#define EINK_FO_HORIZONTAL                                  0x00
#define EINK_FO_VERTICAL                                    0x01
#define EINK_FO_VERTICAL_COLUMN                             0x02
/** \} */

/**
 * \defgroup display_commands  Display Commands
 * \{
 */ 
#define EINK_CMD_DRIVER_OUTPUT_CONTROL                      0x01
#define EINK_CMD_GATE_VOLTAGE_CONTROL                       0x03
#define EINK_CMD_SOURCE_VOLTAGE_CONTROL                     0x04
#define EINK_CMD_DISPLAY_CONTROL                            0x07
#define EINK_CMD_NONOVERLAP_PERIOD                          0x0B
#define EINK_CMD_GATE_SCAN_START_POSITION                   0x0F
#define EINK_CMD_DEEP_SLEEP_MODE                            0x10
#define EINK_CMD_DATA_ENTRY_MODE_SETTING                    0x11
#define EINK_CMD_SW_RESET                                   0x12
#define EINK_CMD_TEMPERATURE_SENSOR_CONTROL                 0x1A
#define EINK_CMD_TEMPERATURE_LOAD                           0x1D
#define EINK_CMD_MASTER_ACTIVATION                          0x20
#define EINK_CMD_DISPLAY_UPDATE_CONTROL_1                   0x21
#define EINK_CMD_DISPLAY_UPDATE_CONTROL_2                   0x22
#define EINK_CMD_WRITE_RAM                                  0x24
#define EINK_CMD_VCOM_SENSE                                 0x28
#define EINK_CMD_VCOM_SENSE_DURATION                        0x29
#define EINK_CMD_VCOM_PROG_OTP                              0x2A
#define EINK_CMD_WRITE_VCOM_REGISTER                        0x2C
#define EINK_CMD_OTP_WAVEFORM_SETTINGS                      0x30
#define EINK_CMD_WRITE_LUT_REGISTER                         0x32
#define EINK_CMD_OTP_PROGRAM                                0x36
#define EINK_CMD_OTP_SELECTION                              0x37
#define EINK_CMD_SET_DUMMY_LINE_PERIOD                      0x3A
#define EINK_CMD_SET_GATE_TIME                              0x3B
#define EINK_CMD_BORDER_WAVEFORM_CONTROL                    0x3C
#define EINK_CMD_SET_RAM_X_ADDRESS_START_END_POSITION       0x44
#define EINK_CMD_SET_RAM_Y_ADDRESS_START_END_POSITION       0x45
#define EINK_CMD_SET_RAM_X_ADDRESS_COUNTER                  0x4E
#define EINK_CMD_SET_RAM_Y_ADDRESS_COUNTER                  0x4F
#define EINK_CMD_BOOSTER_FEEDBACK_SELECTION                 0xF0
#define EINK_CMD_TERMINATE_FRAME_READ_WRITE                 0xFF
/** \} */

/**
 * \defgroup Slave Address  slave_address
 * \{
 */
#define EINK_DEVICE_SLAVE_ADDRESS_000                       0x28
#define EINK_DEVICE_SLAVE_ADDRESS_001                       0x29
#define EINK_DEVICE_SLAVE_ADDRESS_010                       0x2A
#define EINK_DEVICE_SLAVE_ADDRESS_011                       0x2B
#define EINK_DEVICE_SLAVE_ADDRESS_100                       0x2C
#define EINK_DEVICE_SLAVE_ADDRESS_101                       0x2D 
#define EINK_DEVICE_SLAVE_ADDRESS_110                       0x2E
#define EINK_DEVICE_SLAVE_ADDRESS_111                       0x2F
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct
{
    const uint8_t *p_font;
    uint16_t      color;
    uint8_t       orientation;
    uint16_t      first_char;
    uint16_t      last_char;
    uint16_t      height;

} eink200inch_font_t;

typedef struct
{
    uint16_t x;
    uint16_t y;

} eink_cordinate_t;

typedef struct 
{
    uint8_t x_start;
    uint8_t y_start; 
    uint8_t x_end;
    uint8_t y_end;
    
} eink_xy_t;

typedef struct 
{
    uint8_t text_x;
    uint8_t text_y;
    uint8_t n_char;

} eink_text_set_t;

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
    
    eink200inch_font_t dev_font;
    eink_cordinate_t dev_cord;
#ifndef IMAGE_MODE_ONLY
    uint8_t p_frame[EINK_DISPLAY_RESOLUTION];
#endif
} eink_t;

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
    
    eink200inch_font_t font_cfg;

} eink_cfg_t;

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
 * @details This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void eink_cfg_setup ( eink_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
err_t eink_init ( eink_t *ctx, eink_cfg_t *cfg );

/**
 * @brief Sending a command
 *
 * @param ctx          Click object.
 * @param command      The command to be sent
 */
void eink_send_cmd ( eink_t *ctx, uint8_t command );

/**
 * @brief Sending data
 *
 * @param ctx          Click object.
 * @param c_data       The data to be sent
 */
void eink_send_data ( eink_t *ctx, uint8_t c_data );

/**
 * @brief Reset chip
 * 
 * @param ctx          Click object.
 */
void eink_reset( eink_t *ctx );

/**
 * @brief Sleep mode
 * 
 * @param ctx          Click object.
 */
void eink_sleep_mode ( eink_t *ctx );

/**
 * @brief Configuration display
 *
 * @param ctx          Click object.
 */
void eink_start_config ( eink_t *ctx );

/**
 * @brief Set LUT table
 *
 * @param ctx       Click object.
 * @param lut       Lut table
 * @param n_bytes   Number of bytes in Lut table
 *
 * @Note Changing the "lut table" can change the display's performance.
 */
void eink_set_lut ( eink_t *ctx, const uint8_t *lut, uint8_t n_bytes );

/**
 * @brief Setting pointers in memory
 *
 * @param ctx       Click object.
 * @param x         x position
 * @param y         y position
 */
void eink_set_mem_pointer ( eink_t *ctx, uint8_t x, uint8_t y );

/**
 * @brief Setting area in memory
 *
 * @param ctx       Click object.
 * @param xy        Struct object.
 */
void eink_set_mem_area ( eink_t *ctx, eink_xy_t *xy );

/**
 * @brief Update dispaly
 * 
 * @param ctx       Click object.
 */
void eink_update_display ( eink_t *ctx );

/**
 * @brief Function that fills the screen
 *
 * @param ctx        Click object.
 * @param color      The color to which the screen will be colored
 *
 * Options :
       EINK_SCREEN_COLOR_WHITE
       EINK_SCREEN_COLOR_BLACK
       EINK_SCREEN_COLOR_LIGHT_GREY
       EINK_SCREEN_COLOR_DARK_GREY
 */
void eink_fill_screen ( eink_t *ctx, uint8_t color );

/**
 * @brief Displays image
 *
 * @param ctx       Click object.
 * @param image       Buffer containing the image
 *
 * @details The image can be built from VTFT or image2lcd programs, and image type must be monochrome bmp.
 */
void eink_display_image ( eink_t *ctx, const uint8_t* image_buffer );

/**
 * @brief Draw text on the screen
 *
 * @param ctx         Click object.
 * @param text        Text buffer
 * @param text_set    Struct object.
 *
 */
void eink_text ( eink_t *ctx, uint8_t *text, eink_text_set_t *text_set );

/**
 * @brief Set text font
 *
 * @param ctx             Click object.
 * @param cfg_font        Struct object.
 */
void eink_set_font ( eink_t *ctx, eink200inch_font_t *cfg_font );

#ifdef __cplusplus
}
#endif
#endif  // _EINK_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
