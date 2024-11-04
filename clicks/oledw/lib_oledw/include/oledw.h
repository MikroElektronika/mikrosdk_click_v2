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
 * @file oledw.h
 * @brief This file contains API for OLED W Click Driver.
 */

#ifndef _OLEDW_H_
#define _OLEDW_H_

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
#define OLEDW_LCDWIDTH                              96
#define OLEDW_LCDHEIGHT                             39
#define OLEDW_DISPLAYOFF                            0xAE
#define OLEDW_SETDISPLAYCLOCKDIV                    0xD5
#define OLEDW_SETMULTIPLEX                          0xA8
#define OLEDW_SETDISPLAYOFFSET                      0xD3
#define OLEDW_SETSTARTLINE                          0x40
#define OLEDW_CHARGEPUMP                            0x8D
#define OLEDW_SETSEGMENTREMAP                       0xA1
#define OLEDW_SEGREMAP                              0xA0
#define OLEDW_COMSCANDEC                            0xC8
#define OLEDW_SETCOMPINS                            0xDA
#define OLEDW_SETCONTRAST                           0x81
#define OLEDW_SETPRECHARGE                          0xD9
#define OLEDW_SETVCOMDETECT                         0xDB
#define OLEDW_DISPLAYALLON_RESUME                   0xA4
#define OLEDW_NORMALDISPLAY                         0xA6
#define OLEDW_DISPLAYON                             0xAF
#define OLEDW_DISPLAYALLON                          0xA5
#define OLEDW_INVERTDISPLAY                         0xA7
#define OLEDW_SETLOWCOLUMN                          0x00
#define OLEDW_SETHIGHCOLUMN                         0x10
#define OLEDW_MEMORYMODE                            0x20
#define OLEDW_COLUMNADDR                            0x21
#define OLEDW_PAGEADDR                              0x22
#define OLEDW_COMSCANINC                            0xC0
#define OLEDW_EXTERNALVCC                           0x1
#define OLEDW_SWITCHCAPVCC                          0x2
#define OLEDW_ACTIVATE_SCROLL                       0x2F
#define OLEDW_DEACTIVATE_SCROLL                     0x2E
#define OLEDW_SET_VERTICAL_SCROLL_AREA              0xA3
#define OLEDW_RIGHT_HORIZONTAL_SCROLL               0x26
#define OLEDW_LEFT_HORIZONTAL_SCROLL                0x27
#define OLEDW_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL  0x29
#define OLEDW_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL   0x2A
/** \} */

/**
 * \defgroup data_mode Data Mode
 * \{
 */
#define OLEDW_COMMAND  0x3C
#define OLEDW_DATA     0x3D
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define OLEDW_MASTER_I2C 0
#define OLEDW_MASTER_SPI 1
/** \} */

/**
 * \defgroup error Error
 * \{
 */

/**
 * \defgroup error_type Error Type
 * \{
 */
#define err_t  uint8_t
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OLEDW_OK                       0x00
#define OLEDW_INIT_ERROR               0xFF
#define OLEDW_INVALID_DATA_MODE        0xFE
#define OLEDW_INVALID_DRIVER_SELECTOR  0xFD
/** \} */

/** \} */ //  End error group

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define OLEDW_MAP_MIKROBUS( cfg, mikrobus ) \
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

typedef uint8_t  oledw_drv_select_t;

typedef uint8_t  oledw_data_t;
typedef uint8_t  oledw_data_mode_t;

typedef const uint8_t  oledw_resources_t;

typedef err_t ( *oledw_master_write_t )( struct oledw_s *, oledw_data_t, oledw_data_mode_t );
/**
 * @brief Communication type.
 */
typedef uint8_t  oledw_select_t;

/**
 * @brief Click context object definition.
 */
typedef struct oledw_s
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
    oledw_master_write_t  send;
    oledw_select_t master_sel;

} oledw_t;

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
    oledw_select_t  sel;

} oledw_cfg_t;

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
 * @details This function initializes Click configuration structure to
 * initial state.
 * @param[in] cfg  Click configuration structure.
 * @returns Nothing.
 * 
 * @note All used pins will be initialized to unconnected state.
 *       SPI driver will be activated as default driver.
 */
void oledw_cfg_setup( oledw_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param[in] ctx  Click object.
 * @param[in] cfg  Click configuration structure.
 *
 * @returns 0x00 - Ok,
 *          0xFF - Init error,
 *          0xFD - Invalid driver selector.
 *
 * @details This function initializes all necessary peripherals and pins.
 */
err_t oledw_init( oledw_t *ctx, oledw_cfg_t *cfg );

/**
 * @brief Send function.
 * @details This function sends commands or data to OLED W Click.
 * @param[in] ctx  Click object.
 * @param[in] tx_data  Data to be sent.
 * @param[in] data_mode  0x3C - Command,
 *                   0x3D - Data.
 *
 * @returns 0x00 - Ok,
 *          0xFE - Invalid data mode.
 *
 */
err_t oledw_send( oledw_t *ctx, oledw_data_t tx_data, oledw_data_mode_t data_mode );

/**
 * @brief Click Default Configuration function.
 * @details This function configures OLED W Click to default state.
 * @param[in] ctx  Click object.
 * 
 * @returns Nothing.
 */
void oledw_default_cfg( oledw_t *ctx );

/**
 * @brief Page Setting function.
 * @details This function sets page address for page addressing mode.
 * @param[in] ctx  Click object.
 * @param[in] page_addr  Page address.
 * 
 * @returns Nothing.
 */
void oledw_set_page( oledw_t *ctx, oledw_data_t page_addr );

/**
 * @brief Column Setting function.
 * @details This function sets column address for page addressing mode.
 * @param[in] ctx  Click object.
 * @param[in] col_addr  Column address.
 *
 * @returns Nothing.
 */
void oledw_set_column( oledw_t *ctx, oledw_data_t col_addr );

/**
 * @brief Display Picture function.
 * @details This function allows user to display picture for page
 * addressing mode.
 * @param[in] ctx  Click object.
 * @param[in] pic  Resource code.
 *
 * @returns Nothing.
 */ 
void oledw_display_picture( oledw_t *ctx, oledw_resources_t *pic );

/**
 * @brief Contrast Setting function.
 * @details This function sets the display contrast level (0 to 255).
 * @param[in] ctx  Click object.
 * @param[in] value  Contrast value to be set.
 *
 * @returns Nothing.
 */
void oledw_set_contrast( oledw_t *ctx, oledw_data_t value );

/**
 * @brief Scroll Right function.
 * @details This function scrolls the display to the right.
 * @param[in] ctx  Click object.
 * @param[in] start_page_addr  Start page address.
 * @param[in] end_page_addr  End page address.
 * 
 * @returns Nothing.
 */
void oledw_scroll_right( oledw_t *ctx, oledw_data_t start_page_addr, oledw_data_t end_page_addr );

/**
 * @brief Scroll Left function.
 * @details This function scrolls the display to the left.
 * @param[in] ctx  Click object.
 * @param[in] start_page_addr  Start page address.
 * @param[in] end_page_addr  End page address.
 * 
 * @returns Nothing.
 */
void oledw_scroll_left( oledw_t *ctx, oledw_data_t start_page_addr, oledw_data_t end_page_addr );

/**
 * @brief Scroll Diagonally Right function.
 * @details This function scrolls the display diagonally to the right.
 * @param[in] ctx  Click object.
 * @param[in] start_page_addr  Start page address.
 * @param[in] end_page_addr  End page address.
 *
 * @returns Nothing.
 */
void oledw_scroll_diag_right( oledw_t *ctx, oledw_data_t start_page_addr, oledw_data_t end_page_addr );

/**
 * @brief Scroll Diagonally Left function.
 * @details This function scrolls the display diagonally to the left.
 * @param[in] ctx  Click object.
 * @param[in] start_page_addr  Start page address.
 * @param[in] end_page_addr  End page address.
 * 
 * @returns Nothing.
 */
void oledw_scroll_diag_left( oledw_t *ctx, oledw_data_t start_page_addr, oledw_data_t end_page_addr );

/**
 * @brief Stop Scrolling function.
 * @details This function allows user to stop the scrolling motion.
 * @param[in] ctx  Click object.
 *
 * @returns Nothing.
 */
void oledw_stop_scroll( oledw_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // OLEDW_H

/*! @} */ // oledw

// ------------------------------------------------------------------------ END
