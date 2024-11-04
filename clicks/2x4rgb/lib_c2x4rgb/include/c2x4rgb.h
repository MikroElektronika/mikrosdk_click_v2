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
 * @file c2x4rgb.h
 * @brief This file contains API for 2x4 RGB Click Driver.
 */

#ifndef C2X4RGB_H
#define C2X4RGB_H

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

/*!
 * @addtogroup c2x4rgb 2x4 RGB Click Driver
 * @brief API for configuring and manipulating 2x4 RGB Click driver.
 * @{
 */

/**
 * @defgroup c2x4rgb_set 2x4 RGB Settings
 * @brief Settings of 2x4 RGB Click driver.
 */

/**
 * @addtogroup c2x4rgb_set
 * @{
 */

/**
 * @brief 2x4 RGB LED selection values.
 * @details Specified LED selection values of 2x4 RGB Click driver.
 */
#define C2X4RGB_LED_0                       0
#define C2X4RGB_LED_1                       1
#define C2X4RGB_LED_2                       2
#define C2X4RGB_LED_3                       3
#define C2X4RGB_LED_4                       4
#define C2X4RGB_LED_5                       5
#define C2X4RGB_LED_6                       6
#define C2X4RGB_LED_7                       7
#define C2X4RGB_NUM_LEDS                    8

/**
 * @brief 2x4 RGB LED brightness setting.
 * @details Specified LED brightness setting of 2x4 RGB Click driver.
 */
#define C2X4RGB_LED_BRIGHTNESS_MIN          0
#define C2X4RGB_LED_BRIGHTNESS_DEFAULT      0
#define C2X4RGB_LED_BRIGHTNESS_MAX          15
/**
 * @brief 2x4 RGB LED current gain setting.
 * @details Specified LED current gain setting of 2x4 RGB Click driver.
 */
#define C2X4RGB_LED_CURRENT_GAIN_MIN        0
#define C2X4RGB_LED_CURRENT_GAIN_DEFAULT    0
#define C2X4RGB_LED_CURRENT_GAIN_MAX        15

/**
 * @brief 2x4 RGB 24-bit RGB color codes.
 * @details Specified 24-bit RGB color codes of 2x4 RGB Click driver.
 */
#define C2X4RGB_COLOR_BLACK                 0x000000ul
#define C2X4RGB_COLOR_WHITE                 0xFFFFFFul
#define C2X4RGB_COLOR_RED                   0xFF0000ul
#define C2X4RGB_COLOR_LIME                  0x00FF00ul
#define C2X4RGB_COLOR_BLUE                  0x0000FFul
#define C2X4RGB_COLOR_YELLOW                0xFFFF00ul
#define C2X4RGB_COLOR_CYAN                  0x00FFFFul
#define C2X4RGB_COLOR_MAGENTA               0xFF00FFul
#define C2X4RGB_COLOR_SILVER                0xC0C0C0ul
#define C2X4RGB_COLOR_GRAY                  0x808080ul
#define C2X4RGB_COLOR_MAROON                0x800000ul
#define C2X4RGB_COLOR_OLIVE                 0x808000ul
#define C2X4RGB_COLOR_GREEN                 0x008000ul
#define C2X4RGB_COLOR_PURPLE                0x800080ul
#define C2X4RGB_COLOR_TEAL                  0x008080ul
#define C2X4RGB_COLOR_NAVY                  0x000080ul
#define C2X4RGB_NUM_COLORS                  16
#define C2X4RGB_SIZE_COLOR_NAME             32

/*! @} */ // c2x4rgb_set

/**
 * @defgroup c2x4rgb_map 2x4 RGB MikroBUS Map
 * @brief MikroBUS pin mapping of 2x4 RGB Click driver.
 */

/**
 * @addtogroup c2x4rgb_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 2x4 RGB Click to the selected MikroBUS.
 */
#define C2X4RGB_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.din = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // c2x4rgb_map
/*! @} */ // c2x4rgb

/**
 * @brief Function pointer for logic level one and zero.
 * @details Function pointer definition of 2x4 RGB Click driver.
 */
typedef void ( *c2x4rgb_logic_t ) ( void );

/**
 * @brief 2x4 RGB Click RGB color object.
 * @details RGB color object definition of 2x4 RGB Click driver.
 */
typedef struct
{
    uint32_t rgb;                   /**< 24-bit RGB level: 0xRRGGBB. */
    uint8_t name[ C2X4RGB_SIZE_COLOR_NAME ];   /**< Color name */
    
} c2x4rgb_color_t;

/**
 * @brief 2x4 RGB Click led object.
 * @details LED object definition of 2x4 RGB Click driver.
 */
typedef struct
{
    uint8_t current_gain;           /**< Current gain level: 0 to 15. */
    uint8_t brightness;             /**< Brightness level: 0 to 15. */
    uint8_t red;                    /**< Red level: 0 to 255. */
    uint8_t green;                  /**< Green level: 0 to 255. */
    uint8_t blue;                   /**< Blue level: 0 to 255. */

} c2x4rgb_led_t;

/**
 * @brief 2x4 RGB Click context object.
 * @details Context object definition of 2x4 RGB Click driver.
 */
typedef struct
{
    digital_out_t din;          /**< Data pin. */

    c2x4rgb_logic_t logic_zero; /**< Function pointer for logic zero. */
    c2x4rgb_logic_t logic_one;  /**< Function pointer for logic one. */
    
    c2x4rgb_led_t led_matrix[ C2X4RGB_NUM_LEDS ];   /**< 2x4 LED matrix. */

} c2x4rgb_t;

/**
 * @brief 2x4 RGB Click configuration object.
 * @details Configuration object definition of 2x4 RGB Click driver.
 */
typedef struct
{
    pin_name_t din;             /**< Data pin. */

} c2x4rgb_cfg_t;

/**
 * @brief 2x4 RGB Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C2X4RGB_OK = 0,
    C2X4RGB_ERROR = -1

} c2x4rgb_return_value_t;

/*!
 * @addtogroup c2x4rgb 2x4 RGB Click Driver
 * @brief API for configuring and manipulating 2x4 RGB Click driver.
 * @{
 */

/**
 * @brief 2x4 RGB configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c2x4rgb_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c2x4rgb_cfg_setup ( c2x4rgb_cfg_t *cfg );

/**
 * @brief 2x4 RGB initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c2x4rgb_t object definition for detailed explanation.
 * @param[in] logic_zero : Function pointer for logic zero.
 * @param[in] logic_one : Function pointer for logic one.
 * @param[in] cfg : Click configuration structure.
 * See #c2x4rgb_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x4rgb_init ( c2x4rgb_t *ctx, c2x4rgb_logic_t logic_zero, c2x4rgb_logic_t logic_one, c2x4rgb_cfg_t *cfg );

/**
 * @brief 2x4 RGB default configuration function.
 * @details This function executes a default configuration of 2x4 RGB Click board.
 * @param[in] ctx : Click context object.
 * See #c2x4rgb_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c2x4rgb_default_cfg ( c2x4rgb_t *ctx );

/**
 * @brief 2x4 RGB write LEDs function.
 * @details This function writes data to a desired number of LEDs starting from
 * the LED 0 by using DIN pin.
 * @param[in] ctx : Click context object.
 * See #c2x4rgb_t object definition for detailed explanation.
 * @param[in] leds : LEDs data to be written.
 * See #c2x4rgb_led_t object definition for detailed explanation.
 * @param[in] num_leds : Number of LEDs to be written (up to 8 leds).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x4rgb_write_leds ( c2x4rgb_t *ctx, c2x4rgb_led_t *leds, uint8_t num_leds );

/**
 * @brief 2x4 RGB write LED matrix function.
 * @details This function writes the LED matrix data from the Click context object.
 * @param[in] ctx : Click context object.
 * See #c2x4rgb_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c2x4rgb_write_led_matrix ( c2x4rgb_t *ctx );

/**
 * @brief 2x4 RGB set LED intensity function.
 * @details This function sets the brightness and current gain level of the selected LED in the LED matrix.
 * @param[in] ctx : Click context object.
 * See #c2x4rgb_t object definition for detailed explanation.
 * @param[in] led_num : LED number (0 to 7).
 * @param[in] brightness : Brightness level (0 to 15).
 * @param[in] gain : Current gain level (0 to 15).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the LED matrix to the Click board. In order for this change
 * to take effect you will need to call the c2x4rgb_write_led_matrix function afterward.
 */
void c2x4rgb_set_led_intensity ( c2x4rgb_t *ctx, uint8_t led_num, uint8_t brightness, uint8_t gain );

/**
 * @brief 2x4 RGB set LEDs intensity function.
 * @details This function sets the brightness and current gain level of all LEDs in the led matrix.
 * @param[in] ctx : Click context object.
 * See #c2x4rgb_t object definition for detailed explanation.
 * @param[in] brightness : Brightness level (0 to 15).
 * @param[in] gain : Current gain level (0 to 15).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the LED matrix to the Click board. In order for this change
 * to take effect you will need to call the c2x4rgb_write_led_matrix function afterward.
 */
void c2x4rgb_set_leds_intensity ( c2x4rgb_t *ctx, uint8_t brightness, uint8_t gain );

/**
 * @brief 2x4 RGB set LED color function.
 * @details This function sets the color of the selected LED in the LED matrix.
 * @param[in] ctx : Click context object.
 * See #c2x4rgb_t object definition for detailed explanation.
 * @param[in] led_num : LED number (0 to 7).
 * @param[in] rgb : 24-bit RGB color (in a format RRGGBB).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the LED matrix to the Click board. In order for this change
 * to take effect you will need to call the c2x4rgb_write_led_matrix function afterward.
 */
void c2x4rgb_set_led_color ( c2x4rgb_t *ctx, uint8_t led_num, uint32_t rgb );

/**
 * @brief 2x4 RGB set LEDs color function.
 * @details This function sets the color of all LEDs in the LED matrix to the selected level.
 * @param[in] ctx : Click context object.
 * See #c2x4rgb_t object definition for detailed explanation.
 * @param[in] rgb : 24-bit RGB color (in a format RRGGBB).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the LED matrix to the Click board. In order for this change
 * to take effect you will need to call the c2x4rgb_write_led_matrix function afterward.
 */
void c2x4rgb_set_leds_color ( c2x4rgb_t *ctx, uint32_t rgb );

#ifdef __cplusplus
}
#endif
#endif // C2X4RGB_H

/*! @} */ // c2x4rgb

// ------------------------------------------------------------------------ END
