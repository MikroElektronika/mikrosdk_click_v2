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
 * @file c10x10rgb2.h
 * @brief This file contains API for 10x10 RGB 2 Click Driver.
 */

#ifndef C10X10RGB2_H
#define C10X10RGB2_H

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
 * @addtogroup c10x10rgb2 10x10 RGB 2 Click Driver
 * @brief API for configuring and manipulating 10x10 RGB 2 Click driver.
 * @{
 */

/**
 * @defgroup c10x10rgb2_set 10x10 RGB 2 Settings
 * @brief Settings of 10x10 RGB 2 Click driver.
 */

/**
 * @addtogroup c10x10rgb2_set
 * @{
 */

/**
 * @brief 10x10 RGB 2 LED frame setting.
 * @details Specified LED frame setting of 10x10 RGB 2 Click driver.
 */
#define C10X10RGB2_FRAME_START                  0x00
#define C10X10RGB2_FRAME_END                    0xFF

/**
 * @brief 10x10 RGB 2 LED selection values.
 * @details Specified LED selection values of 10x10 RGB 2 Click driver.
 */
#define C10X10RGB2_LED_0                        0
#define C10X10RGB2_LED_1                        1
#define C10X10RGB2_LED_2                        2
#define C10X10RGB2_LED_3                        3
#define C10X10RGB2_LED_4                        4
#define C10X10RGB2_LED_5                        5
#define C10X10RGB2_LED_6                        6
#define C10X10RGB2_LED_7                        7
#define C10X10RGB2_LED_8                        8
#define C10X10RGB2_LED_9                        9
#define C10X10RGB2_LED_10                       10
#define C10X10RGB2_LED_11                       11
#define C10X10RGB2_LED_12                       12
#define C10X10RGB2_LED_13                       13
#define C10X10RGB2_LED_14                       14
#define C10X10RGB2_LED_15                       15
#define C10X10RGB2_LED_16                       16
#define C10X10RGB2_LED_17                       17
#define C10X10RGB2_LED_18                       18
#define C10X10RGB2_LED_19                       19
#define C10X10RGB2_LED_20                       20
#define C10X10RGB2_LED_21                       21
#define C10X10RGB2_LED_22                       22
#define C10X10RGB2_LED_23                       23
#define C10X10RGB2_LED_24                       24
#define C10X10RGB2_LED_25                       25
#define C10X10RGB2_LED_26                       26
#define C10X10RGB2_LED_27                       27
#define C10X10RGB2_LED_28                       28
#define C10X10RGB2_LED_29                       29
#define C10X10RGB2_LED_30                       30
#define C10X10RGB2_LED_31                       31
#define C10X10RGB2_LED_32                       32
#define C10X10RGB2_LED_33                       33
#define C10X10RGB2_LED_34                       34
#define C10X10RGB2_LED_35                       35
#define C10X10RGB2_LED_36                       36
#define C10X10RGB2_LED_37                       37
#define C10X10RGB2_LED_38                       38
#define C10X10RGB2_LED_39                       39
#define C10X10RGB2_LED_40                       40
#define C10X10RGB2_LED_41                       41
#define C10X10RGB2_LED_42                       42
#define C10X10RGB2_LED_43                       43
#define C10X10RGB2_LED_44                       44
#define C10X10RGB2_LED_45                       45
#define C10X10RGB2_LED_46                       46
#define C10X10RGB2_LED_47                       47
#define C10X10RGB2_LED_48                       48
#define C10X10RGB2_LED_49                       49
#define C10X10RGB2_LED_50                       50
#define C10X10RGB2_LED_51                       51
#define C10X10RGB2_LED_52                       52
#define C10X10RGB2_LED_53                       53
#define C10X10RGB2_LED_54                       54
#define C10X10RGB2_LED_55                       55
#define C10X10RGB2_LED_56                       56
#define C10X10RGB2_LED_57                       57
#define C10X10RGB2_LED_58                       58
#define C10X10RGB2_LED_59                       59
#define C10X10RGB2_LED_60                       60
#define C10X10RGB2_LED_61                       61
#define C10X10RGB2_LED_62                       62
#define C10X10RGB2_LED_63                       63
#define C10X10RGB2_LED_64                       64
#define C10X10RGB2_LED_65                       65
#define C10X10RGB2_LED_66                       66
#define C10X10RGB2_LED_67                       67
#define C10X10RGB2_LED_68                       68
#define C10X10RGB2_LED_69                       69
#define C10X10RGB2_LED_70                       70
#define C10X10RGB2_LED_71                       71
#define C10X10RGB2_LED_72                       72
#define C10X10RGB2_LED_73                       73
#define C10X10RGB2_LED_74                       74
#define C10X10RGB2_LED_75                       75
#define C10X10RGB2_LED_76                       76
#define C10X10RGB2_LED_77                       77
#define C10X10RGB2_LED_78                       78
#define C10X10RGB2_LED_79                       79
#define C10X10RGB2_LED_80                       80
#define C10X10RGB2_LED_81                       81
#define C10X10RGB2_LED_82                       82
#define C10X10RGB2_LED_83                       83
#define C10X10RGB2_LED_84                       84
#define C10X10RGB2_LED_85                       85
#define C10X10RGB2_LED_86                       86
#define C10X10RGB2_LED_87                       87
#define C10X10RGB2_LED_88                       88
#define C10X10RGB2_LED_89                       89
#define C10X10RGB2_LED_90                       90
#define C10X10RGB2_LED_91                       91
#define C10X10RGB2_LED_92                       92
#define C10X10RGB2_LED_93                       93
#define C10X10RGB2_LED_94                       94
#define C10X10RGB2_LED_95                       95
#define C10X10RGB2_LED_96                       96
#define C10X10RGB2_LED_97                       97
#define C10X10RGB2_LED_98                       98
#define C10X10RGB2_LED_99                       99
#define C10X10RGB2_NUM_LEDS                     100

/**
 * @brief 10x10 RGB 2 LED brightness setting.
 * @details Specified LED brightness setting of 10x10 RGB 2 Click driver.
 */
#define C10X10RGB2_LED_BRIGHTNESS_MIN           0
#define C10X10RGB2_LED_BRIGHTNESS_DEFAULT       1
#define C10X10RGB2_LED_BRIGHTNESS_MAX           31
#define C10X10RGB2_LED_BRIGHTNESS_MASK          0xE0

/**
 * @brief 10x10 RGB 2 24-bit RGB color codes.
 * @details Specified 24-bit RGB color codes of 10x10 RGB 2 Click driver.
 */
#define C10X10RGB2_COLOR_BLACK                  0x000000ul
#define C10X10RGB2_COLOR_WHITE                  0xFFFFFFul
#define C10X10RGB2_COLOR_RED                    0xFF0000ul
#define C10X10RGB2_COLOR_LIME                   0x00FF00ul
#define C10X10RGB2_COLOR_BLUE                   0x0000FFul
#define C10X10RGB2_COLOR_YELLOW                 0xFFFF00ul
#define C10X10RGB2_COLOR_CYAN                   0x00FFFFul
#define C10X10RGB2_COLOR_MAGENTA                0xFF00FFul
#define C10X10RGB2_COLOR_SILVER                 0xC0C0C0ul
#define C10X10RGB2_COLOR_GRAY                   0x808080ul
#define C10X10RGB2_COLOR_MAROON                 0x800000ul
#define C10X10RGB2_COLOR_OLIVE                  0x808000ul
#define C10X10RGB2_COLOR_GREEN                  0x008000ul
#define C10X10RGB2_COLOR_PURPLE                 0x800080ul
#define C10X10RGB2_COLOR_TEAL                   0x008080ul
#define C10X10RGB2_COLOR_NAVY                   0x000080ul

/**
 * @brief 10x10 RGB 2 text ASCII byte rotation.
 * @details Specified text ASCII byte rotation of 10x10 RGB 2 Click driver.
 */
#define C10X10RGB2_ROTATION_V_0                 0x00
#define C10X10RGB2_ROTATION_V_180               0x01
#define C10X10RGB2_ROTATION_H_0                 0x10
#define C10X10RGB2_ROTATION_H_180               0x11

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c10x10rgb2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C10X10RGB2_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define C10X10RGB2_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c10x10rgb2_set

/**
 * @defgroup c10x10rgb2_map 10x10 RGB 2 MikroBUS Map
 * @brief MikroBUS pin mapping of 10x10 RGB 2 Click driver.
 */

/**
 * @addtogroup c10x10rgb2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 10x10 RGB 2 Click to the selected MikroBUS.
 */
#define C10X10RGB2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );

/*! @} */ // c10x10rgb2_map
/*! @} */ // c10x10rgb2

/**
 * @brief 10x10 RGB 2 Click led object.
 * @details LED object definition of 10x10 RGB 2 Click driver.
 */
typedef struct
{
    uint8_t brightness;             /**< Brightness level: 0 to 31. */
    uint8_t red;                    /**< Red level: 0 to 255. */
    uint8_t green;                  /**< Green level: 0 to 255. */
    uint8_t blue;                   /**< Blue level: 0 to 255. */

} c10x10rgb2_led_t;

/**
 * @brief 10x10 RGB 2 Click pen object.
 * @details Pen object definition of 10x10 RGB 2 Click driver.
 */
typedef struct
{
    uint32_t txt_rgb;               /**< Text 24-bit RGB level: 0xRRGGBB. */
    uint32_t bg_rgb;                /**< Background 24-bit RGB level: 0xRRGGBB. */
    uint8_t rotation;               /**< ASCII byte rotation. */

} c10x10rgb2_pen_t;

/**
 * @brief 10x10 RGB 2 Click context object.
 * @details Context object definition of 10x10 RGB 2 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    c10x10rgb2_led_t led_matrix[ C10X10RGB2_NUM_LEDS ]; /**< 10x10 LED matrix. */

    c10x10rgb2_pen_t pen;           /**< Text pen configuration. */

} c10x10rgb2_t;

/**
 * @brief 10x10 RGB 2 Click configuration object.
 * @details Configuration object definition of 10x10 RGB 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */

    // static variable
    uint32_t            spi_speed;  /**< SPI serial speed. */
    spi_master_mode_t   spi_mode;   /**< SPI master mode. */

} c10x10rgb2_cfg_t;

/**
 * @brief 10x10 RGB 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C10X10RGB2_OK = 0,
    C10X10RGB2_ERROR = -1

} c10x10rgb2_return_value_t;

/*!
 * @addtogroup c10x10rgb2 10x10 RGB 2 Click Driver
 * @brief API for configuring and manipulating 10x10 RGB 2 Click driver.
 * @{
 */

/**
 * @brief 10x10 RGB 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c10x10rgb2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c10x10rgb2_cfg_setup ( c10x10rgb2_cfg_t *cfg );

/**
 * @brief 10x10 RGB 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c10x10rgb2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c10x10rgb2_init ( c10x10rgb2_t *ctx, c10x10rgb2_cfg_t *cfg );

/**
 * @brief 10x10 RGB 2 default configuration function.
 * @details This function executes a default configuration of 10x10 RGB 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c10x10rgb2_default_cfg ( c10x10rgb2_t *ctx );

/**
 * @brief 10x10 RGB 2 write leds function.
 * @details This function writes data to a desired number of leds starting from
 * the LED 0 by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] leds : LEDs data to be written.
 * See #c10x10rgb2_led_t object definition for detailed explanation.
 * @param[in] num_leds : Number of LEDs to be written (up to 100 leds).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c10x10rgb2_write_leds ( c10x10rgb2_t *ctx, c10x10rgb2_led_t *leds, uint16_t num_leds );

/**
 * @brief 10x10 RGB 2 write led matrix function.
 * @details This function writes the led matrix data from the click context object.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c10x10rgb2_write_led_matrix ( c10x10rgb2_t *ctx );

/**
 * @brief 10x10 RGB 2 set led brightness function.
 * @details This function sets the brightness of the selected led in the led matrix.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] led_num : LED number (0 to 99).
 * @param[in] brightness : Brightness level (0 to 31).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the led matrix to the click board. In order for this change
 * to take effect you will need to call the c10x10rgb2_write_led_matrix function afterward.
 */
void c10x10rgb2_set_led_brightness ( c10x10rgb2_t *ctx, uint16_t led_num, uint8_t brightness );

/**
 * @brief 10x10 RGB 2 set leds brightness function.
 * @details This function sets the brightness of all leds in the led matrix to the selected level.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] brightness : Brightness level (0 to 31).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the led matrix to the click board. In order for this change
 * to take effect you will need to call the c10x10rgb2_write_led_matrix function afterward.
 */
void c10x10rgb2_set_leds_brightness ( c10x10rgb2_t *ctx, uint8_t brightness );

/**
 * @brief 10x10 RGB 2 set led color function.
 * @details This function sets the color of the selected led in the led matrix.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] led_num : LED number (0 to 99).
 * @param[in] rgb : 24-bit RGB color (in a format RRGGBB).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the led matrix to the click board. In order for this change
 * to take effect you will need to call the c10x10rgb2_write_led_matrix function afterward.
 */
void c10x10rgb2_set_led_color ( c10x10rgb2_t *ctx, uint16_t led_num, uint32_t rgb );

/**
 * @brief 10x10 RGB 2 set leds color function.
 * @details This function sets the color of all leds in the led matrix to the selected level.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] rgb : 24-bit RGB color (in a format RRGGBB).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the led matrix to the click board. In order for this change
 * to take effect you will need to call the c10x10rgb2_write_led_matrix function afterward.
 */
void c10x10rgb2_set_leds_color ( c10x10rgb2_t *ctx, uint32_t rgb );

/**
 * @brief 10x10 RGB 2 make color function.
 * @details This function creates a 24-bit RGB color based on the RGB input parameters.
 * @param[in] red : Red color byte.
 * @param[in] green : Green color byte.
 * @param[in] blue : Blue color byte.
 * @param[in] rgb_pct : Percent of RGB color (1-100).
 * @return 24-bit RGB color (in a format RRGGBB).
 * @note None.
 */
uint32_t c10x10rgb2_make_color ( uint8_t red, uint8_t green, uint8_t blue, uint8_t rgb_pct );

/**
 * @brief 10x10 RGB 2 color wheel function.
 * @details This function creates a 24-bit RGB color based on the color wheel input parameters.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] wheel_pos : Color wheel position (modulo 255).
 * @param[in] rgb_pct : Percent of RGB color (1-100).
 * @return 24-bit RGB color (in a format RRGGBB).
 * @note None.
 */
uint32_t c10x10rgb2_color_wheel ( uint8_t wheel_pos, uint8_t rgb_pct );

/**
 * @brief 10x10 RGB 2 fill screen function.
 * @details This function fills the entire screen with the specified color.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] rgb : 24-bit RGB color (in a format RRGGBB).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c10x10rgb2_fill_screen ( c10x10rgb2_t *ctx, uint32_t rgb );

/**
 * @brief 10x10 RGB 2 set pen function.
 * @details This function sets the pen configuration for text writing.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] txt_rgb : Text 24-bit RGB level: 0xRRGGBB.
 * @param[in] bg_rgb : Background 24-bit RGB level: 0xRRGGBB.
 * @param[in] rotation : ASCII byte rotation:
                         @li @c 0x00 - Vertical 0 - Normal,
 *                       @li @c 0x01 - Vertical 180 - XY mirrored,
 *                       @li @c 0x10 - Horizontal 0 - XY exchanged, X mirrored,
 *                       @li @c 0x11 - Horizontal 180 - XY exchanged, Y mirrored.
 * @return None.
 * @note None.
 */
void c10x10rgb2_set_pen ( c10x10rgb2_t *ctx, uint32_t txt_rgb, uint32_t bg_rgb, uint8_t rotation );

/**
 * @brief 10x10 RGB 2 write char function.
 * @details This function writes a single ASCII character in a 8x8 font size.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] data_in : ASCII(32-122) char to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c10x10rgb2_write_char ( c10x10rgb2_t *ctx, uint8_t data_in );

/**
 * @brief 10x10 RGB 2 write char function.
 * @details This function writes a text string in a 8x8 font size by scrolling characters to the left side.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] data_in : ASCII(32-122) string to write (must end with \0).
 * @param[in] speed_ms : Screen refresh delay in milliseconds which presents a scrolling speed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c10x10rgb2_write_string ( c10x10rgb2_t *ctx, uint8_t *data_in, uint16_t speed_ms );

/**
 * @brief 10x10 RGB 2 draw picture function.
 * @details This function draws a 10x10px picture on the screen.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] image : 10x10 image in a 24-bit RGB color format (RRGGBB).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c10x10rgb2_draw_picture ( c10x10rgb2_t *ctx, const uint32_t *image );

/**
 * @brief 10x10 RGB 2 demo rainbow function.
 * @details This function performs a colorfull "rainbow" demo for a desired period.
 * @param[in] ctx : Click context object.
 * See #c10x10rgb2_t object definition for detailed explanation.
 * @param[in] rgb_pct : Percent of RGB color (1-100).
 * @param[in] upd_rate_ms : Screen update delay in milliseconds.
 * @param[in] upd_num : Number of screen updates.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c10x10rgb2_demo_rainbow ( c10x10rgb2_t *ctx, uint8_t rgb_pct, uint16_t upd_rate_ms, uint16_t upd_num );

#ifdef __cplusplus
}
#endif
#endif // C10X10RGB2_H

/*! @} */ // c10x10rgb2

// ------------------------------------------------------------------------ END
