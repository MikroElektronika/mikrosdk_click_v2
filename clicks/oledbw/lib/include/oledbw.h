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
 * \file oledbw.h
 *
 * \brief This file contains API for OLED BW Click driver.
 *
 * \addtogroup oledbw OLED BW Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _OLEDBW_H_
#define _OLEDBW_H_

#include "drv_digital_out.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup settings Display Settings
 * \{
 */
#define OLEDBW_LCDWIDTH                              96
#define OLEDBW_LCDHEIGHT                             39
#define OLEDBW_DISPLAYOFF                            0xAE
#define OLEDBW_SETDISPLAYCLOCKDIV                    0xD5
#define OLEDBW_SETMULTIPLEX                          0xA8
#define OLEDBW_SETDISPLAYOFFSET                      0xD3
#define OLEDBW_SETSTARTLINE                          0x40
#define OLEDBW_CHARGEPUMP                            0x8D
#define OLEDBW_SETSEGMENTREMAP                       0xA1
#define OLEDBW_SEGREMAP                              0xA0
#define OLEDBW_COMSCANDEC                            0xC8
#define OLEDBW_SETCOMPINS                            0xDA
#define OLEDBW_SETCONTRAST                           0x81
#define OLEDBW_SETPRECHARGE                          0xD9
#define OLEDBW_SETVCOMDETECT                         0xDB
#define OLEDBW_DISPLAYALLON_RESUME                   0xA4
#define OLEDBW_NORMALDISPLAY                         0xA6
#define OLEDBW_DISPLAYON                             0xAF
#define OLEDBW_DISPLAYALLON                          0xA5
#define OLEDBW_INVERTDISPLAY                         0xA7
#define OLEDBW_SETLOWCOLUMN                          0x00
#define OLEDBW_SETHIGHCOLUMN                         0x10
#define OLEDBW_MEMORYMODE                            0x20
#define OLEDBW_COLUMNADDR                            0x21
#define OLEDBW_PAGEADDR                              0x22
#define OLEDBW_COMSCANINC                            0xC0
#define OLEDBW_EXTERNALVCC                           0x1
#define OLEDBW_SWITCHCAPVCC                          0x2
#define OLEDBW_ACTIVATE_SCROLL                       0x2F
#define OLEDBW_DEACTIVATE_SCROLL                     0x2E
#define OLEDBW_SET_VERTICAL_SCROLL_AREA              0xA3
#define OLEDBW_RIGHT_HORIZONTAL_SCROLL               0x26
#define OLEDBW_LEFT_HORIZONTAL_SCROLL                0x27
#define OLEDBW_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL  0x29
#define OLEDBW_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL   0x2A
/** \} */

/**
 * \defgroup data_mode Data Mode
 * \{
 */
#define OLEDBW_COMMAND  0x3C
#define OLEDBW_DATA     0x3D
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define OLEDBW_MASTER_I2C 0
#define OLEDBW_MASTER_SPI 1
/** \} */

/**
 * \defgroup error Error
 * \{
 */

/**
 * \defgroup error_type Error Type
 * \{
 */
#define OLEDBW_RETVAL  uint8_t
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OLEDBW_OK                       0x00
#define OLEDBW_INIT_ERROR               0xFF
#define OLEDBW_INVALID_DATA_MODE        0xFE
#define OLEDBW_INVALID_DRIVER_SELECTOR  0xFD
/** \} */

/** \} */ //  End error group

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define OLEDBW_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST  ); \
    cfg.dc  = MIKROBUS( mikrobus, MIKROBUS_PWM  ); \
    cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS   ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK  ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.sdi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL  ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA  )
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup types Types
 * \{
 */

typedef uint8_t  oledbw_drv_select_t;

typedef uint8_t  oledbw_data_t;
typedef uint8_t  oledbw_data_mode_t;

typedef const uint8_t  oledbw_resources_t;

typedef OLEDBW_RETVAL ( * oledbw_master_write_t )( struct oledbw_s *,
                                                   oledbw_data_t,
                                                   oledbw_data_mode_t );
/**
 * @brief Communication type.
 */
typedef uint8_t  oledbw_select_t;

/**
 * @brief Click context object definition.
 */
typedef struct oledbw_s
{
    //  Click mikrobus DRV objects.
    digital_out_t  cs;
    digital_out_t  rst;
    digital_out_t  dc;

    // Modules 
    spi_master_t   spi;
    i2c_master_t   i2c;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;

    //  Click send function pointer.
    oledbw_master_write_t  send;
    oledbw_select_t master_sel;

} oledbw_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Used mikrobus pins.
    pin_name_t  rst;
    pin_name_t  dc;
    pin_name_t  cs;
    pin_name_t  sck;
    pin_name_t  sdi;
    pin_name_t  scl;
    pin_name_t  sda;
    pin_name_t  miso;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;
    
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    /**
     * Click driver selector.
     * 0 - SPI driver. (default)
     * 1 - I2C driver.
     */
    oledbw_select_t  sel;

} oledbw_cfg_t;

/** \} */ //  End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public Function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Configuration Object Setup function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to
 * initial state.
 *
 * @note All used pins will be initialized to unconnected state.
 *       SPI driver will be activated as default driver.
 */
void
oledbw_cfg_setup( oledbw_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns 0x00 - Ok,
 *          0xFF - Init error,
 *          0xFD - Invalid driver selector.
 *
 * @description This function initializes all necessary peripherals and pins.
 */
OLEDBW_RETVAL
oledbw_init( oledbw_t *ctx, oledbw_cfg_t *cfg );

/**
 * @brief Send function.
 *
 * @param ctx  Click object.
 * @param tx_data  Data to be sent.
 * @param data_mode  0x3C - Command,
 *                   0x3D - Data.
 *
 * @returns 0x00 - Ok,
 *          0xFE - Invalid data mode.
 *
 * @description This function sends commands or data to OLED B click.
 */
OLEDBW_RETVAL
oledbw_send( oledbw_t *ctx, oledbw_data_t tx_data,
             oledbw_data_mode_t data_mode );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function configures OLED B click to default state.
 */
void
oledbw_default_cfg( oledbw_t *ctx );

/**
 * @brief Page Setting function.
 *
 * @param ctx  Click object.
 * @param page_addr  Page address.
 *
 * @description This function sets page address for page addressing mode.
 */
void
oledbw_set_page( oledbw_t *ctx, oledbw_data_t page_addr );

/**
 * @brief Column Setting function.
 *
 * @param ctx  Click object.
 * @param col_addr  Column address.
 *
 * @description This function sets column address for page addressing mode.
 */
void
oledbw_set_column( oledbw_t *ctx, oledbw_data_t col_addr );

/**
 * @brief Display Picture function.
 *
 * @param ctx  Click object.
 * @param pic  Resource code.
 *
 * @description This function allows user to display picture for page
 * addressing mode.
 */
void
oledbw_display_picture( oledbw_t *ctx, oledbw_resources_t *pic );

/**
 * @brief Contrast Setting function.
 *
 * @param ctx  Click object.
 * @param value  Contrast value to be set.
 *
 * @description This function sets the display contrast level (0 to 255).
 */
void
oledbw_set_contrast( oledbw_t *ctx, oledbw_data_t value );

/**
 * @brief Scroll Right function.
 *
 * @param ctx  Click object.
 * @param start_page_addr  Start page address.
 * @param end_page_addr  End page address.
 *
 * @description This function scrolls the display to the right.
 */
void
oledbw_scroll_right( oledbw_t *ctx, oledbw_data_t start_page_addr,
                     oledbw_data_t end_page_addr );

/**
 * @brief Scroll Left function.
 *
 * @param ctx  Click object.
 * @param start_page_addr  Start page address.
 * @param end_page_addr  End page address.
 *
 * @description This function scrolls the display to the left.
 */
void
oledbw_scroll_left( oledbw_t *ctx, oledbw_data_t start_page_addr,
                    oledbw_data_t end_page_addr );

/**
 * @brief Scroll Diagonally Right function.
 *
 * @param ctx  Click object.
 * @param start_page_addr  Start page address.
 * @param end_page_addr  End page address.
 *
 * @description This function scrolls the display diagonally to the right.
 */
void
oledbw_scroll_diag_right( oledbw_t *ctx, oledbw_data_t start_page_addr,
                          oledbw_data_t end_page_addr );

/**
 * @brief Scroll Diagonally Left function.
 *
 * @param ctx  Click object.
 * @param start_page_addr  Start page address.
 * @param end_page_addr  End page address.
 *
 * @description This function scrolls the display diagonally to the left.
 */
void
oledbw_scroll_diag_left( oledbw_t *ctx, oledbw_data_t start_page_addr,
                         oledbw_data_t end_page_addr );

/**
 * @brief Stop Scrolling function.
 *
 * @param ctx  Click object.
 *
 * @description This function allows user to stop the scrolling motion.
 */
void
oledbw_stop_scroll( oledbw_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  //  _OLEDBW_H_

/** \} */ //  End public_function group
/// \}    //  End oledbw group
/*! @} */
// ------------------------------------------------------------------------ END
