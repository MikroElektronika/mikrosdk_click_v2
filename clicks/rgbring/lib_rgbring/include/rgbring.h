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
 * @file rgbring.h
 * @brief This file contains API for RGB Ring Click Driver.
 */

#ifndef RGBRING_H
#define RGBRING_H

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
 * @addtogroup rgbring RGB Ring Click Driver
 * @brief API for configuring and manipulating RGB Ring Click driver.
 * @{
 */

/**
 * @defgroup rgbring_set RGB Ring Settings
 * @brief Settings of RGB Ring Click driver.
 */

/**
 * @addtogroup rgbring_set
 * @{
 */

/**
 * @brief RGB Ring LED selection values.
 * @details Specified LED selection values of RGB Ring Click driver.
 */
#define RGBRING_LED_0                       0
#define RGBRING_LED_1                       1
#define RGBRING_LED_2                       2
#define RGBRING_LED_3                       3
#define RGBRING_LED_4                       4
#define RGBRING_LED_5                       5
#define RGBRING_LED_6                       6
#define RGBRING_LED_7                       7
#define RGBRING_NUM_LEDS                    8

/**
 * @brief RGB Ring 24-bit RGB color codes.
 * @details Specified 24-bit RGB color codes of RGB Ring Click driver.
 */
#define RGBRING_COLOR_BLACK                 0x000000ul
#define RGBRING_COLOR_WHITE                 0xFFFFFFul
#define RGBRING_COLOR_RED                   0xFF0000ul
#define RGBRING_COLOR_LIME                  0x00FF00ul
#define RGBRING_COLOR_BLUE                  0x0000FFul
#define RGBRING_COLOR_YELLOW                0xFFFF00ul
#define RGBRING_COLOR_CYAN                  0x00FFFFul
#define RGBRING_COLOR_MAGENTA               0xFF00FFul
#define RGBRING_COLOR_SILVER                0xC0C0C0ul
#define RGBRING_COLOR_GRAY                  0x808080ul
#define RGBRING_COLOR_MAROON                0x800000ul
#define RGBRING_COLOR_OLIVE                 0x808000ul
#define RGBRING_COLOR_GREEN                 0x008000ul
#define RGBRING_COLOR_PURPLE                0x800080ul
#define RGBRING_COLOR_TEAL                  0x008080ul
#define RGBRING_COLOR_NAVY                  0x000080ul
#define RGBRING_NUM_COLORS                  16
#define RGBRING_SIZE_COLOR_NAME             32

/**
 * @brief RGB Ring button state setting.
 * @details Specified setting for button state of RGB Ring Click driver.
 */
#define RGBRING_BUTTON_PRESSED              0
#define RGBRING_BUTTON_RELESED              1

/*! @} */ // rgbring_set

/**
 * @defgroup rgbring_map RGB Ring MikroBUS Map
 * @brief MikroBUS pin mapping of RGB Ring Click driver.
 */

/**
 * @addtogroup rgbring_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RGB Ring Click to the selected MikroBUS.
 */
#define RGBRING_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.din = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // rgbring_map
/*! @} */ // rgbring

/**
 * @brief Function pointer for logic level one and zero.
 * @details Function pointer definition of RGB Ring Click driver.
 */
typedef void ( *rgbring_logic_t ) ( void );

/**
 * @brief RGB Ring Click RGB color object.
 * @details RGB color object definition of RGB Ring Click driver.
 */
typedef struct
{
    uint32_t rgb;                   /**< 24-bit RGB level: 0xRRGGBB. */
    uint8_t name[ RGBRING_SIZE_COLOR_NAME ];   /**< Color name */
    
} rgbring_color_t;

/**
 * @brief RGB Ring Click led object.
 * @details LED object definition of RGB Ring Click driver.
 */
typedef struct
{
    uint8_t red;                    /**< Red level: 0 to 255. */
    uint8_t green;                  /**< Green level: 0 to 255. */
    uint8_t blue;                   /**< Blue level: 0 to 255. */

} rgbring_led_t;

/**
 * @brief RGB Ring Click context object.
 * @details Context object definition of RGB Ring Click driver.
 */
typedef struct
{
    digital_out_t din;          /**< Data pin. */

    digital_in_t int_pin;       /**< Interrupt pin - button state (active low). */

    rgbring_logic_t logic_zero; /**< Function pointer for logic zero. */
    rgbring_logic_t logic_one;  /**< Function pointer for logic one. */
    
    rgbring_led_t led_matrix[ RGBRING_NUM_LEDS ];   /**< 8 LEDs ring matrix. */

} rgbring_t;

/**
 * @brief RGB Ring Click configuration object.
 * @details Configuration object definition of RGB Ring Click driver.
 */
typedef struct
{
    pin_name_t din;             /**< Data pin. */
    pin_name_t int_pin;         /**< Interrupt pin - button state (active low). */

} rgbring_cfg_t;

/**
 * @brief RGB Ring Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RGBRING_OK = 0,
    RGBRING_ERROR = -1

} rgbring_return_value_t;

/*!
 * @addtogroup rgbring RGB Ring Click Driver
 * @brief API for configuring and manipulating RGB Ring Click driver.
 * @{
 */

/**
 * @brief RGB Ring configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rgbring_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rgbring_cfg_setup ( rgbring_cfg_t *cfg );

/**
 * @brief RGB Ring initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rgbring_t object definition for detailed explanation.
 * @param[in] logic_zero : Function pointer for logic zero.
 * @param[in] logic_one : Function pointer for logic one.
 * @param[in] cfg : Click configuration structure.
 * See #rgbring_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rgbring_init ( rgbring_t *ctx, rgbring_logic_t logic_zero, rgbring_logic_t logic_one, rgbring_cfg_t *cfg );

/**
 * @brief RGB Ring default configuration function.
 * @details This function executes a default configuration of RGB Ring Click board.
 * @param[in] ctx : Click context object.
 * See #rgbring_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rgbring_default_cfg ( rgbring_t *ctx );

/**
 * @brief RGB Ring write LEDs function.
 * @details This function writes data to a desired number of LEDs starting from
 * the LED 0 by using DIN pin.
 * @param[in] ctx : Click context object.
 * See #rgbring_t object definition for detailed explanation.
 * @param[in] leds : LEDs data to be written.
 * See #rgbring_led_t object definition for detailed explanation.
 * @param[in] num_leds : Number of LEDs to be written (up to 8 leds).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rgbring_write_leds ( rgbring_t *ctx, rgbring_led_t *leds, uint8_t num_leds );

/**
 * @brief RGB Ring write LED matrix function.
 * @details This function writes the LED matrix data from the Click context object.
 * @param[in] ctx : Click context object.
 * See #rgbring_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rgbring_write_led_matrix ( rgbring_t *ctx );

/**
 * @brief RGB Ring set LED color function.
 * @details This function sets the color of the selected LED in the LED matrix.
 * @param[in] ctx : Click context object.
 * See #rgbring_t object definition for detailed explanation.
 * @param[in] led_num : LED number (0 to 7).
 * @param[in] rgb : 24-bit RGB color (in a format RRGGBB).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the LED matrix to the Click board. In order for this change
 * to take effect you will need to call the rgbring_write_led_matrix function afterward.
 */
void rgbring_set_led_color ( rgbring_t *ctx, uint8_t led_num, uint32_t rgb );

/**
 * @brief RGB Ring set LEDs color function.
 * @details This function sets the color of all LEDs in the LED matrix to the selected level.
 * @param[in] ctx : Click context object.
 * See #rgbring_t object definition for detailed explanation.
 * @param[in] rgb : 24-bit RGB color (in a format RRGGBB).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function doesn't write the LED matrix to the Click board. In order for this change
 * to take effect you will need to call the rgbring_write_led_matrix function afterward.
 */
void rgbring_set_leds_color ( rgbring_t *ctx, uint32_t rgb );

/**
 * @brief RGB Ring get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #rgbring_t object definition for detailed explanation.
 * @return @li @c 0 - Button pressed,
 *         @li @c 1 - Button released.
 * @note None.
 */
uint8_t rgbring_get_int_pin ( rgbring_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RGBRING_H

/*! @} */ // rgbring

// ------------------------------------------------------------------------ END
