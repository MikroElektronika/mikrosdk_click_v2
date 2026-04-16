/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file oledw2.h
 * @brief This file contains API for OLED W 2 Click Driver.
 */

#ifndef OLEDW2_H
#define OLEDW2_H

#ifdef __cplusplus
extern "C"{
#endif

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
#include "spi_specifics.h"

/*!
 * @addtogroup oledw2 OLED W 2 Click Driver
 * @brief API for configuring and manipulating OLED W 2 Click driver.
 * @{
 */

/**
 * @defgroup oledw2_cmd OLED W 2 Commands List
 * @brief List of commands of OLED W 2 Click driver.
 */

/**
 * @addtogroup oledw2_cmd
 * @{
 */

/**
 * @brief OLED W 2 commands list.
 * @details Specified commands list of OLED W 2 Click driver.
 */
#define OLEDW2_CMD_SET_LOW_COLUMN                       0x00
#define OLEDW2_CMD_SET_HIGH_COLUMN                      0x10
#define OLEDW2_CMD_SET_MEMORY_MODE                      0x20
#define OLEDW2_CMD_SET_COLUMN_ADDR                      0x21
#define OLEDW2_CMD_SET_PAGE_ADDR                        0x22
#define OLEDW2_CMD_RIGHT_HORIZONTAL_SCROLL              0x26
#define OLEDW2_CMD_LEFT_HORIZONTAL_SCROLL               0x27
#define OLEDW2_CMD_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define OLEDW2_CMD_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A
#define OLEDW2_CMD_DEACTIVATE_SCROLL                    0x2E
#define OLEDW2_CMD_ACTIVATE_SCROLL                      0x2F
#define OLEDW2_CMD_SET_START_LINE                       0x40
#define OLEDW2_CMD_SET_CONTRAST                         0x81
#define OLEDW2_CMD_SET_CHARGE_PUMP                      0x8D
#define OLEDW2_CMD_SET_SEG_REMAP_0                      0xA0
#define OLEDW2_CMD_SET_SEG_REMAP_1                      0xA1
#define OLEDW2_CMD_SET_VERTICAL_SCROLL_AREA             0xA3
#define OLEDW2_CMD_ENTIRE_DISPLAY_RESUME                0xA4
#define OLEDW2_CMD_ENTIRE_DISPLAY_ON                    0xA5
#define OLEDW2_CMD_SET_NORMAL_DISPLAY                   0xA6
#define OLEDW2_CMD_SET_INVERT_DISPLAY                   0xA7
#define OLEDW2_CMD_SET_MULTIPLEX_RATIO                  0xA8
#define OLEDW2_CMD_SET_DISPLAY_OFF                      0xAE
#define OLEDW2_CMD_SET_DISPLAY_ON                       0xAF
#define OLEDW2_CMD_SET_PAGE_START                       0xB0
#define OLEDW2_CMD_SET_COM_SCAN_INC                     0xC0
#define OLEDW2_CMD_SET_COM_SCAN_DEC                     0xC8
#define OLEDW2_CMD_SET_DISPLAY_OFFSET                   0xD3
#define OLEDW2_CMD_SET_DISPLAY_CLOCK_DIV                0xD5
#define OLEDW2_CMD_SET_PRECHARGE                        0xD9
#define OLEDW2_CMD_SET_COM_PINS                         0xDA
#define OLEDW2_CMD_SET_VCOM_DESELECT                    0xDB
#define OLEDW2_CMD_NOP                                  0xE3

/*! @} */ // oledw2_cmd

/**
 * @defgroup oledw2_set OLED W 2 Registers Settings
 * @brief Settings for registers of OLED W 2 Click driver.
 */

/**
 * @addtogroup oledw2_set
 * @{
 */

/**
 * @brief OLED W 2 resolution setting.
 * @details Specified setting for display resolution of OLED W 2 Click driver.
 */
#define OLEDW2_RES_WIDTH                                128
#define OLEDW2_RES_HEIGHT                               32

/**
 * @brief OLED W 2 position and coordinates setting.
 * @details Specified setting for display position and coordinates of OLED W 2 Click driver.
 */
#define OLEDW2_POS_WIDTH_MIN                            0
#define OLEDW2_POS_WIDTH_MAX                            ( OLEDW2_RES_WIDTH - 1 )
#define OLEDW2_POS_HEIGHT_MIN                           0
#define OLEDW2_POS_HEIGHT_MAX                           ( OLEDW2_RES_HEIGHT - 1 )
#define OLEDW2_POS_PAGE_MIN                             0
#define OLEDW2_POS_PAGE_MAX                             ( OLEDW2_RES_HEIGHT / 8 - 1 )

/**
 * @brief OLED W 2 font setting.
 * @details Specified setting for font of OLED W 2 Click driver.
 */
#define OLEDW2_FONT_ASCII_OFFSET                        32

/**
 * @brief OLED W 2 rotation setting.
 * @details Specified setting for rotation of OLED W 2 Click driver.
 */
#define OLEDW2_ROTATION_0                               0
#define OLEDW2_ROTATION_180                             1

/**
 * @brief OLED W 2 contrast setting.
 * @details Specified setting for contrast of OLED W 2 Click driver.
 */
#define OLEDW2_CONTRAST_MIN                             0x00
#define OLEDW2_CONTRAST_DEFAULT                         0x9F
#define OLEDW2_CONTRAST_MAX                             0xFF

/**
 * @brief OLED W 2 scroll setting.
 * @details Specified setting for scroll of OLED W 2 Click driver.
 */
#define OLEDW2_SCROLL_FRAMES_5                          0x00
#define OLEDW2_SCROLL_FRAMES_64                         0x01
#define OLEDW2_SCROLL_FRAMES_128                        0x02
#define OLEDW2_SCROLL_FRAMES_256                        0x03
#define OLEDW2_SCROLL_FRAMES_3                          0x04
#define OLEDW2_SCROLL_FRAMES_4                          0x05
#define OLEDW2_SCROLL_FRAMES_25                         0x06
#define OLEDW2_SCROLL_FRAMES_2                          0x07
#define OLEDW2_SCROLL_VERT_OFFSET_MIN                   0x01
#define OLEDW2_SCROLL_VERT_OFFSET_MAX                   0x3F

/**
 * @brief OLED W 2 default setting.
 * @details Specified setting for default of OLED W 2 Click driver.
 */
#define OLEDW2_DEF_CLOCK_DIV                            0x80
#define OLEDW2_DEF_DISPLAY_OFFSET                       0x00
#define OLEDW2_DEF_CHARGE_PUMP_ENABLE                   0x14
#define OLEDW2_DEF_COM_PINS                             0x02
#define OLEDW2_DEF_PRECHARGE                            0x22
#define OLEDW2_DEF_VCOM_DESELECT                        0x30

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b oledw2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define OLEDW2_SET_DATA_SAMPLE_EDGE                     SET_SPI_DATA_SAMPLE_EDGE
#define OLEDW2_SET_DATA_SAMPLE_MIDDLE                   SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // oledw2_set

/**
 * @defgroup oledw2_map OLED W 2 MikroBUS Map
 * @brief MikroBUS pin mapping of OLED W 2 Click driver.
 */

/**
 * @addtogroup oledw2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of OLED W 2 Click to the selected MikroBUS.
 */
#define OLEDW2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dc   = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // oledw2_map
/*! @} */ // oledw2

/**
 * @brief OLED W 2 Click font object.
 * @details Font object definition of OLED W 2 Click driver.
 */
typedef struct
{
    const uint8_t *font_buf;        /**< Pointer to font array. */ 
    uint8_t width;                  /**< Font width. */ 
    uint8_t height;                 /**< Font height. */ 

} oledw2_font_t;

/**
 * @brief OLED W 2 Click context object.
 * @details Context object definition of OLED W 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset signal pin (active low). */
    digital_out_t dc;               /**< Display data/command control pin (1-data, 0-command). */
    digital_out_t cs;               /**< Display chip select pin. */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t chip_select;         /**< Chip select pin descriptor (used for SPI driver). */

    oledw2_font_t font;             /**< Font setting. */ 
    uint8_t rotation;               /**< Screen rotation settings. */

} oledw2_t;

/**
 * @brief OLED W 2 Click configuration object.
 * @details Configuration object definition of OLED W 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset signal pin (active low). */
    pin_name_t dc;                  /**< Display data/command control pin (1-data, 0-command). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} oledw2_cfg_t;

/**
 * @brief OLED W 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    OLEDW2_OK = 0,
    OLEDW2_ERROR = -1

} oledw2_return_value_t;

/*!
 * @addtogroup oledw2 OLED W 2 Click Driver
 * @brief API for configuring and manipulating OLED W 2 Click driver.
 * @{
 */

/**
 * @brief OLED W 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #oledw2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void oledw2_cfg_setup ( oledw2_cfg_t *cfg );

/**
 * @brief OLED W 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #oledw2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_init ( oledw2_t *ctx, oledw2_cfg_t *cfg );

/**
 * @brief OLED W 2 default configuration function.
 * @details This function executes a default configuration of OLED W 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t oledw2_default_cfg ( oledw2_t *ctx );

/**
 * @brief OLED W 2 write cmd function.
 * @details This function writes a command byte by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_write_cmd ( oledw2_t *ctx, uint8_t cmd );

/**
 * @brief OLED W 2 write data function.
 * @details This function writes a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written (8-bit array).
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_write_data ( oledw2_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief OLED W 2 disable device function.
 * @details This function disables the device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void oledw2_disable_device ( oledw2_t *ctx );

/**
 * @brief OLED W 2 enable device function.
 * @details This function enables the device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void oledw2_enable_device ( oledw2_t *ctx );

/**
 * @brief OLED W 2 reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void oledw2_reset_device ( oledw2_t *ctx );

/**
 * @brief OLED W 2 enter cmd mode function.
 * @details This function enters the command mode by setting the DC pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void oledw2_enter_cmd_mode ( oledw2_t *ctx );

/**
 * @brief OLED W 2 enter data mode function.
 * @details This function enters the data mode by setting the DC pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void oledw2_enter_data_mode ( oledw2_t *ctx );

/**
 * @brief OLED W 2 set font function.
 * @details This function sets the active font size.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] font_sel : @li @c 0 - 5x7 font,
 *                       @li @c 1 - 6x8 font,
 *                       @li @c 2 - 8x16 font.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void oledw2_set_font ( oledw2_t *ctx, uint8_t font_sel );

/**
 * @brief OLED W 2 set rotation function.
 * @details This function sets the display rotation.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] rotation : @li @c 0 - Normal,
 *                       @li @c 1 - Rotated by 180 degrees,
 * @return None.
 * @note None.
 */
void oledw2_set_rotation ( oledw2_t *ctx, uint8_t rotation );

/**
 * @brief OLED W 2 set column function.
 * @details This function sets column address for page addressing mode.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] column : 0 to OLEDW2_POS_WIDTH_MAX.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Non.
 */
err_t oledw2_set_column ( oledw2_t *ctx, uint8_t column );

/**
 * @brief OLED W 2 set page function.
 * @details This function sets page address for page addressing mode.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] page : 0 to OLEDW2_POS_PAGE_MAX.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Non.
 */
err_t oledw2_set_page ( oledw2_t *ctx, uint8_t page );

/**
 * @brief OLED W 2 fill screen function.
 * @details This function fills the screen.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_fill_screen ( oledw2_t *ctx );

/**
 * @brief OLED W 2 clear screen function.
 * @details This function clears the screen.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_clear_screen ( oledw2_t *ctx );

/**
 * @brief OLED W 2 write char function.
 * @details This function writes a single ASCII character on the selected position in configured font size.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] page : Display page 0 to OLEDW2_POS_PAGE_MAX.
 * @param[in] position : Text position 0 to OLEDW2_RES_WIDTH / ctx->font.width.
 * @param[in] data_in : ASCII(32-126) char to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_write_char ( oledw2_t *ctx, uint8_t page, uint8_t position, uint8_t data_in );

/**
 * @brief OLED W 2 write string function.
 * @details This function writes a text string starting from the selected position in configured font size.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] page : Display page 0 to OLEDW2_POS_PAGE_MAX.
 * @param[in] position : Text position 0 to OLEDW2_RES_WIDTH / ctx->font.width.
 * @param[in] data_in : ASCII(32-126) string to write (must end with \0).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_write_string ( oledw2_t *ctx, uint8_t page, uint8_t position, uint8_t *data_in );

/**
 * @brief OLED W 2 draw picture function.
 * @details This function draws a picture.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] image : Image array.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_draw_picture ( oledw2_t *ctx, const uint8_t *image );

/**
 * @brief OLED W 2 set contrast function.
 * @details This function sets the display contrast level (0 to 255).
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] value : Contrast value to be set (0 to 255).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_set_contrast ( oledw2_t *ctx, uint8_t value );

/**
 * @brief OLED W 2 scroll right function.
 * @details This function scrolls the display to the right.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] start_page : Start page for scrolling.
 * @param[in] end_page : End page for scrolling.
 * @param[in] num_frames : Number of frames (scrolling speed), see OLEDW2_SCROLL_FRAMES_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_scroll_right ( oledw2_t *ctx, uint8_t start_page, uint8_t end_page, uint8_t num_frames );

/**
 * @brief OLED W 2 scroll left function.
 * @details This function scrolls the display to the left.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] start_page : Start page for scrolling.
 * @param[in] end_page : End page for scrolling.
 * @param[in] num_frames : Number of frames (scrolling speed), see OLEDW2_SCROLL_FRAMES_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_scroll_left ( oledw2_t *ctx, uint8_t start_page, uint8_t end_page, uint8_t num_frames );

/**
 * @brief OLED W 2 scroll diag right function.
 * @details This function scrolls the display to diagonal up-right direction.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] start_page : Start page for scrolling.
 * @param[in] end_page : End page for scrolling.
 * @param[in] num_frames : Number of frames (scrolling speed), see OLEDW2_SCROLL_FRAMES_x macros.
 * @param[in] vert_offset : Vertical scrolling offset, see OLEDW2_SCROLL_VERT_OFFSET_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_scroll_diag_right ( oledw2_t *ctx, uint8_t start_page, uint8_t end_page, uint8_t num_frames, uint8_t vert_offset );

/**
 * @brief OLED W 2 scroll diag left function.
 * @details This function scrolls the display to diagonal up-left direction.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @param[in] start_page : Start page for scrolling.
 * @param[in] end_page : End page for scrolling.
 * @param[in] num_frames : Number of frames (scrolling speed), see OLEDW2_SCROLL_FRAMES_x macros.
 * @param[in] vert_offset : Vertical scrolling offset, see OLEDW2_SCROLL_VERT_OFFSET_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_scroll_diag_left ( oledw2_t *ctx, uint8_t start_page, uint8_t end_page, uint8_t num_frames, uint8_t vert_offset );

/**
 * @brief OLED W 2 stop scroll function.
 * @details This function stops display scrolling.
 * @param[in] ctx : Click context object.
 * See #oledw2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t oledw2_stop_scroll ( oledw2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // OLEDW2_H

/*! @} */ // oledw2

// ------------------------------------------------------------------------ END
