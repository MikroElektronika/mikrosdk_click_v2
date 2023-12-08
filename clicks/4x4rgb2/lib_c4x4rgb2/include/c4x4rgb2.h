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
 * @file c4x4rgb2.h
 * @brief This file contains API for 4x4 RGB 2 Click Driver.
 */

#ifndef C4X4RGB2_H
#define C4X4RGB2_H

#ifdef __cplusplus
extern "C"{
#endif

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
#include "spi_specifics.h"

/*!
 * @addtogroup c4x4rgb2 4x4 RGB 2 Click Driver
 * @brief API for configuring and manipulating 4x4 RGB 2 Click driver.
 * @{
 */

/**
 * @defgroup c4x4rgb2_set 4x4 RGB 2 Settings
 * @brief Settings of 4x4 RGB 2 Click driver.
 */

/**
 * @addtogroup c4x4rgb2_set
 * @{
 */

/**
 * @brief 4x4 RGB 2 LED frame setting.
 * @details Specified LED frame setting of 4x4 RGB 2 Click driver.
 */
#define C4X4RGB2_FRAME_START                0x00
#define C4X4RGB2_FRAME_END                  0xFF

/**
 * @brief 4x4 RGB 2 LED selection values.
 * @details Specified LED selection values of 4x4 RGB 2 Click driver.
 */
#define C4X4RGB2_LED_0                      0
#define C4X4RGB2_LED_1                      1
#define C4X4RGB2_LED_2                      2
#define C4X4RGB2_LED_3                      3
#define C4X4RGB2_LED_4                      4
#define C4X4RGB2_LED_5                      5
#define C4X4RGB2_LED_6                      6
#define C4X4RGB2_LED_7                      7
#define C4X4RGB2_LED_8                      8
#define C4X4RGB2_LED_9                      9
#define C4X4RGB2_LED_10                     10
#define C4X4RGB2_LED_11                     11
#define C4X4RGB2_LED_12                     12
#define C4X4RGB2_LED_13                     13
#define C4X4RGB2_LED_14                     14
#define C4X4RGB2_LED_15                     15
#define C4X4RGB2_NUM_LEDS                   16

/**
 * @brief 4x4 RGB 2 LED brightness setting.
 * @details Specified LED brightness setting of 4x4 RGB 2 Click driver.
 */
#define C4X4RGB2_LED_BRIGHTNESS_MIN         0
#define C4X4RGB2_LED_BRIGHTNESS_DEFAULT     1
#define C4X4RGB2_LED_BRIGHTNESS_MAX         31
#define C4X4RGB2_LED_BRIGHTNESS_MASK        0xE0

/**
 * @brief 4x4 RGB 2 24-bit RGB color codes.
 * @details Specified 24-bit RGB color codes of 4x4 RGB 2 Click driver.
 */
#define C4X4RGB2_COLOR_BLACK                0x000000ul
#define C4X4RGB2_COLOR_WHITE                0xFFFFFFul
#define C4X4RGB2_COLOR_RED                  0xFF0000ul
#define C4X4RGB2_COLOR_LIME                 0x00FF00ul
#define C4X4RGB2_COLOR_BLUE                 0x0000FFul
#define C4X4RGB2_COLOR_YELLOW               0xFFFF00ul
#define C4X4RGB2_COLOR_CYAN                 0x00FFFFul
#define C4X4RGB2_COLOR_MAGENTA              0xFF00FFul
#define C4X4RGB2_COLOR_SILVER               0xC0C0C0ul
#define C4X4RGB2_COLOR_GRAY                 0x808080ul
#define C4X4RGB2_COLOR_MAROON               0x800000ul
#define C4X4RGB2_COLOR_OLIVE                0x808000ul
#define C4X4RGB2_COLOR_GREEN                0x008000ul
#define C4X4RGB2_COLOR_PURPLE               0x800080ul
#define C4X4RGB2_COLOR_TEAL                 0x008080ul
#define C4X4RGB2_COLOR_NAVY                 0x000080ul
#define C4X4RGB2_NUM_COLORS                 16
#define C4X4RGB2_SIZE_COLOR_NAME            32

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c4x4rgb2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C4X4RGB2_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define C4X4RGB2_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c4x4rgb2_set

/**
 * @defgroup c4x4rgb2_map 4x4 RGB 2 MikroBUS Map
 * @brief MikroBUS pin mapping of 4x4 RGB 2 Click driver.
 */

/**
 * @addtogroup c4x4rgb2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 4x4 RGB 2 Click to the selected MikroBUS.
 */
#define C4X4RGB2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );

/*! @} */ // c4x4rgb2_map
/*! @} */ // c4x4rgb2

/**
 * @brief 4x4 RGB 2 Click RGB color object.
 * @details RGB color object definition of 4x4 RGB 2 Click driver.
 */
typedef struct
{
    uint32_t rgb;                   /**< 24-bit RGB level: 0xRRGGBB. */
    uint8_t name[ C4X4RGB2_SIZE_COLOR_NAME ];   /**< Color name */
    
} c4x4rgb2_color_t;

/**
 * @brief 4x4 RGB 2 Click led object.
 * @details LED object definition of 4x4 RGB 2 Click driver.
 */
typedef struct
{
    uint8_t brightness;             /**< Brightness level: 0 to 31. */
    uint8_t red;                    /**< Red level: 0 to 255. */
    uint8_t green;                  /**< Green level: 0 to 255. */
    uint8_t blue;                   /**< Blue level: 0 to 255. */

} c4x4rgb2_led_t;

/**
 * @brief 4x4 RGB 2 Click context object.
 * @details Context object definition of 4x4 RGB 2 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;               /**< SPI driver object. */
    
    c4x4rgb2_led_t led_matrix[ C4X4RGB2_NUM_LEDS ]; /**< 4x4 LED matrix. */

} c4x4rgb2_t;

/**
 * @brief 4x4 RGB 2 Click configuration object.
 * @details Configuration object definition of 4x4 RGB 2 Click driver.
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

} c4x4rgb2_cfg_t;

/**
 * @brief 4x4 RGB 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C4X4RGB2_OK = 0,
    C4X4RGB2_ERROR = -1

} c4x4rgb2_return_value_t;

/*!
 * @addtogroup c4x4rgb2 4x4 RGB 2 Click Driver
 * @brief API for configuring and manipulating 4x4 RGB 2 Click driver.
 * @{
 */

/**
 * @brief 4x4 RGB 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c4x4rgb2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c4x4rgb2_cfg_setup ( c4x4rgb2_cfg_t *cfg );

/**
 * @brief 4x4 RGB 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c4x4rgb2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c4x4rgb2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4x4rgb2_init ( c4x4rgb2_t *ctx, c4x4rgb2_cfg_t *cfg );

/**
 * @brief 4x4 RGB 2 default configuration function.
 * @details This function executes a default configuration of 4x4 RGB 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #c4x4rgb2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c4x4rgb2_default_cfg ( c4x4rgb2_t *ctx );

/**
 * @brief 4x4 RGB 2 write leds function.
 * @details This function writes data to a desired number of leds starting from
 * the LED 0 by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c4x4rgb2_t object definition for detailed explanation.
 * @param[in] leds : LEDs data to be written.
 * See #c4x4rgb2_led_t object definition for detailed explanation.
 * @param[in] num_leds : Number of LEDs to be written (up to 16 leds).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4x4rgb2_write_leds ( c4x4rgb2_t *ctx, c4x4rgb2_led_t *leds, uint8_t num_leds );

/**
 * @brief 4x4 RGB 2 write led matrix function.
 * @details This function writes the led matrix data from the click context object.
 * @param[in] ctx : Click context object.
 * See #c4x4rgb2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c4x4rgb2_write_led_matrix ( c4x4rgb2_t *ctx );

/**
 * @brief 4x4 RGB 2 set led brightness function.
 * @details This function sets the brightness of the selected led in the led matrix.
 * @param[in] ctx : Click context object.
 * See #c4x4rgb2_t object definition for detailed explanation.
 * @param[in] led_num : LED number (0 to 15).
 * @param[in] brightness : Brightness level (0 to 31).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the led matrix to the click board. In order for this change
 * to take effect you will need to call the c4x4rgb2_write_led_matrix function afterward.
 */
void c4x4rgb2_set_led_brightness ( c4x4rgb2_t *ctx, uint8_t led_num, uint8_t brightness );

/**
 * @brief 4x4 RGB 2 set all leds brightness function.
 * @details This function sets the brightness of all leds in the led matrix to the selected level.
 * @param[in] ctx : Click context object.
 * See #c4x4rgb2_t object definition for detailed explanation.
 * @param[in] brightness : Brightness level (0 to 31).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the led matrix to the click board. In order for this change
 * to take effect you will need to call the c4x4rgb2_write_led_matrix function afterward.
 */
void c4x4rgb2_set_all_leds_brightness ( c4x4rgb2_t *ctx, uint8_t brightness );

/**
 * @brief 4x4 RGB 2 set led color function.
 * @details This function sets the color of the selected led in the led matrix.
 * @param[in] ctx : Click context object.
 * See #c4x4rgb2_t object definition for detailed explanation.
 * @param[in] led_num : LED number (0 to 15).
 * @param[in] rgb : 24-bit RGB color (in a format RRGGBB).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the led matrix to the click board. In order for this change
 * to take effect you will need to call the c4x4rgb2_write_led_matrix function afterward.
 */
void c4x4rgb2_set_led_color ( c4x4rgb2_t *ctx, uint8_t led_num, uint32_t rgb );

/**
 * @brief 4x4 RGB 2 set all leds color function.
 * @details This function sets the color of all leds in the led matrix to the selected level.
 * @param[in] ctx : Click context object.
 * See #c4x4rgb2_t object definition for detailed explanation.
 * @param[in] rgb : 24-bit RGB color (in a format RRGGBB).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the led matrix to the click board. In order for this change
 * to take effect you will need to call the c4x4rgb2_write_led_matrix function afterward.
 */
void c4x4rgb2_set_all_leds_color ( c4x4rgb2_t *ctx, uint32_t rgb );

#ifdef __cplusplus
}
#endif
#endif // C4X4RGB2_H

/*! @} */ // c4x4rgb2

// ------------------------------------------------------------------------ END
