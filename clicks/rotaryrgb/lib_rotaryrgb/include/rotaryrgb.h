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
 * @file rotaryrgb.h
 * @brief This file contains API for Rotary RGB Click Driver.
 */

#ifndef ROTARYRGB_H
#define ROTARYRGB_H

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
 * @addtogroup rotaryrgb Rotary RGB Click Driver
 * @brief API for configuring and manipulating Rotary RGB Click driver.
 * @{
 */

/**
 * @defgroup rotaryrgb_set Rotary RGB color data values.
 * @brief Color data values of Rotary RGB Click driver.
 */

/**
 * @addtogroup rotaryrgb_set
 * @{
 */

/**
 * @brief Rotary RGB color data values.
 * @details Specified setting for color data values of Rotary RGB Click driver.
 */
#define ROTARYRGB_COLOR_WHITE_100         0x002F2F2Ful
#define ROTARYRGB_COLOR_WHITE_75          0x00232323ul
#define ROTARYRGB_COLOR_WHITE_50          0x00181818ul
#define ROTARYRGB_COLOR_WHITE_25          0x000C0C0Cul
#define ROTARYRGB_COLOR_RED_100           0x00002F00ul
#define ROTARYRGB_COLOR_RED_75            0x00002300ul
#define ROTARYRGB_COLOR_RED_50            0x00001800ul
#define ROTARYRGB_COLOR_RED_25            0x00000C00ul
#define ROTARYRGB_COLOR_GREEN_100         0x002F0000ul
#define ROTARYRGB_COLOR_GREEN_75          0x00230000ul
#define ROTARYRGB_COLOR_GREEN_50          0x00180000ul
#define ROTARYRGB_COLOR_GREEN_25          0x000C0000ul
#define ROTARYRGB_COLOR_BLUE_100          0x0000002Ful
#define ROTARYRGB_COLOR_BLUE_75           0x00000023ul
#define ROTARYRGB_COLOR_BLUE_50           0x00000018ul
#define ROTARYRGB_COLOR_BLUE_25           0x0000000Cul
#define ROTARYRGB_COLOR_LIGHT_BLUE_100    0x002F002Ful
#define ROTARYRGB_COLOR_LIGHT_BLUE_75     0x00230023ul
#define ROTARYRGB_COLOR_LIGHT_BLUE_50     0x00180018ul
#define ROTARYRGB_COLOR_LIGHT_BLUE_25     0x000C000Cul
#define ROTARYRGB_COLOR_YELLOW_100        0x002F2F00ul
#define ROTARYRGB_COLOR_YELLOW_75         0x00232300ul
#define ROTARYRGB_COLOR_YELLOW_50         0x00181800ul
#define ROTARYRGB_COLOR_YELLOW_25         0x000C0C00ul
#define ROTARYRGB_COLOR_PURPLE_100        0x00002F2Ful
#define ROTARYRGB_COLOR_PURPLE_75         0x00002323ul
#define ROTARYRGB_COLOR_PURPLE_50         0x00001818ul
#define ROTARYRGB_COLOR_PURPLE_25         0x00000C0Cul
#define ROTARYRGB_COLOR_OFF               0x00000000ul

/**
 * @brief Rotary RGB led position values.
 * @details Led position values of Rotary RGB Click driver.
 */
#define ROTARYRGB_SET_LED_POS_1             1 
#define ROTARYRGB_SET_LED_POS_2             2 
#define ROTARYRGB_SET_LED_POS_3             3 
#define ROTARYRGB_SET_LED_POS_4             4 
#define ROTARYRGB_SET_LED_POS_5             5 
#define ROTARYRGB_SET_LED_POS_6             6 
#define ROTARYRGB_SET_LED_POS_7             7 
#define ROTARYRGB_SET_LED_POS_8             8 
#define ROTARYRGB_SET_LED_POS_9             9 
#define ROTARYRGB_SET_LED_POS_10            10
#define ROTARYRGB_SET_LED_POS_11            11
#define ROTARYRGB_SET_LED_POS_12            12
#define ROTARYRGB_SET_LED_POS_13            13
#define ROTARYRGB_SET_LED_POS_14            14
#define ROTARYRGB_SET_LED_POS_15            15
#define ROTARYRGB_SET_LED_POS_16            16

/*! @} */ // rotaryrgb_set

/**
 * @defgroup rotaryrgb_map Rotary RGB MikroBUS Map
 * @brief MikroBUS pin mapping of Rotary RGB Click driver.
 */

/**
 * @addtogroup rotaryrgb_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Rotary RGB Click to the selected MikroBUS.
 */
#define ROTARYRGB_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.enb    = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.di_pin = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.do_pin = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ena    = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.sw     = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rotaryrgb_map
/*! @} */ // rotaryrgb

typedef void ( *drv_logic_t ) ( void );

/**
 * @brief Rotary RGB Click context object.
 * @details Context object definition of Rotary RGB Click driver.
 */
typedef struct
{
    digital_out_t di_pin;    /**< LEDs control output pin. */

    digital_in_t enb;        /**< Rotary encoder B signal. */
    digital_in_t do_pin;     /**< LEDs control input pin. */
    digital_in_t ena;        /**< Rotary encoder A signal. */
    digital_in_t sw;         /**< Rotary encoder switch signal. */

    // Function pointers
    drv_logic_t logic_zero;
    drv_logic_t logic_one;

} rotaryrgb_t;

/**
 * @brief Rotary RGB Click configuration object.
 * @details Configuration object definition of Rotary RGB Click driver.
 */
typedef struct
{
    pin_name_t enb;       /**< Rotary encoder B signal. */
    pin_name_t do_pin;    /**< LEDs control input pin. */
    pin_name_t di_pin;    /**< LEDs control output pin. */
    pin_name_t ena;       /**< Rotary encoder A signal. */
    pin_name_t sw;        /**< Rotary encoder switch signal. */

    // Function pointers
    drv_logic_t logic_zero;
    drv_logic_t logic_one;

} rotaryrgb_cfg_t;

/**
 * @brief Rotary RGB Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ROTARYRGB_OK = 0,
    ROTARYRGB_ERROR = -1

} rotaryrgb_return_value_t;

/*!
 * @addtogroup rotaryrgb Rotary RGB Click Driver
 * @brief API for configuring and manipulating Rotary RGB Click driver.
 * @{
 */

/**
 * @brief Rotary RGB configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rotaryrgb_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rotaryrgb_cfg_setup ( rotaryrgb_cfg_t *cfg, drv_logic_t logic_zero, drv_logic_t logic_one );

/**
 * @brief Rotary RGB initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rotaryrgb_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rotaryrgb_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rotaryrgb_init ( rotaryrgb_t *ctx, rotaryrgb_cfg_t *cfg );

/**
 * @brief Rotary RGB set LED data function.
 * @details This function, using GPIO protocol, writes a desired 24-bit data 
 * of the WS2812C-2020, Intelligent control LED integrated light source
 * on the Rotary RGB Click board.
 * @param[out] ctx : Click context object.
 * See #rotaryrgb_t object definition for detailed explanation.
 * @param[in] data_in : 24-bit data to be written.
 * @return Nothing.
 * @note None.
 */
void rotaryrgb_set_led_data ( rotaryrgb_t *ctx, uint32_t data_in );

/**
 * @brief Rotary RGB set all LEDs data function.
 * @details This function, using GPIO protocol, 
 * writes a desired 16x24-bit data for all LEDs
 * of the WS2812C-2020, Intelligent control LED integrated light source
 * on the Rotary RGB Click board.
 * @param[out] ctx : Click context object.
 * See #rotaryrgb_t object definition for detailed explanation.
 * @param[in] data_in : A pointer to the 16 elements array data to be written.
 * @return Nothing.
 * @note None.
 */
void rotaryrgb_set_all_leds_data ( rotaryrgb_t *ctx, uint32_t *data_in );

/**
 * @brief Rotary RGB set all LEDs color function.
 * @details This function sets the desired color for all LEDs
 * of the WS2812C-2020, Intelligent control LED integrated light source
 * on the Rotary RGB Click board.
 * @param[out] ctx : Click context object.
 * See #rotaryrgb_t object definition for detailed explanation.
 * @param[in] led_color : LEDs color value.
 * @return Nothing.
 * @note None.
 */
void rotaryrgb_set_all_led_color ( rotaryrgb_t *ctx, uint32_t led_color );

/**
 * @brief Rotary RGB set LED position color function.
 * @details This function sets the desired color for the selected LED position
 * of the WS2812C-2020, Intelligent control LED integrated light source
 * on the Rotary RGB Click board.
 * @param[out] ctx : Click context object.
 * See #rotaryrgb_t object definition for detailed explanation.
 * @param[in] led_pos : LED position [1-16].
 * @param[in] led_color : LED color value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rotaryrgb_set_led_pos_color ( rotaryrgb_t *ctx, uint8_t led_pos, uint32_t led_color );

/**
 * @brief Rotary RGB make color function.
 * @details This function creates a color based on the input color and brightness parameters
 * of the WS2812C-2020, Intelligent control LED integrated light source
 * on the Rotary RGB Click board.
 * @param[in] red : Red color value.
 * @param[in] green : Green color value.
 * @param[in] blue : Blue color value.
 * @param[in] brightness : Brightness value.
 * @return 24-bit color data.
 * @note None.
 */
uint32_t rotaryrgb_make_color ( uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness );

/**
 * @brief Rotary RGB DI pin setting function.
 * @details This function sets the DI pin on the high level of
 * Rotary RGB click board.
 * @param[in] ctx : Click context object.
 * See #rotaryrgb_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rotaryrgb_set_state_di_pin ( rotaryrgb_t *ctx );

/**
 * @brief Rotary RGB DI pin clearing function.
 * @details This function clears the DI pin on the low level of
 * Rotary RGB click board.
 * @param[in] ctx : Click context object.
 * See #rotaryrgb_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rotaryrgb_di_pin_clear ( rotaryrgb_t *ctx );

/**
 * @brief Rotary RGB get DO pin state function.
 * @details This function reads the state of the DO pin of Rotary RGB
 * click board.
 * @param[in] ctx : Click context object.
 * See #rotaryrgb_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t rotaryrgb_get_state_do_pin ( rotaryrgb_t *ctx );

/**
 * @brief Rotary RGB get switch state function.
 * @details This function return rotary encoder switch signal, states of the SW(INT) pin
 * of the EC12D1564402 on the Rotary RGB Click board.
 * @param[in] ctx : Click context object.
 * See #rotaryrgb_t object definition for detailed explanation.
 * @return @li @c 0 - Released state,
 *         @li @c 1 - Pressed state.
 * @note None.
 */
uint8_t rotaryrgb_get_state_switch ( rotaryrgb_t *ctx );

/**
 * @brief Rotary RGB get encoder A state function.
 * @details This function return rotary encoder A signal, states of the ENA(PWM) pin
 * of the EC12D1564402 on the Rotary RGB Click board.
 * @param[in] ctx : Click context object.
 * See #rotaryrgb_t object definition for detailed explanation.
 * @return @li @c 0 - Released state,
 *         @li @c 1 - Pressed state.
 * @note None.
 */
uint8_t rotaryrgb_get_state_ena ( rotaryrgb_t *ctx );

/**
 * @brief Rotary RGB get encoder B state function.
 * @details This function return rotary encoder B signal, states of the ENB(AN) pin
 * of the EC12D1564402 on the Rotary RGB Click board.
 * @param[in] ctx : Click context object.
 * See #rotaryrgb_t object definition for detailed explanation.
 * @return @li @c 0 - Released state,
 *         @li @c 1 - Pressed state.
 * @note None.
 */
uint8_t rotaryrgb_get_state_enb ( rotaryrgb_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ROTARYRGB_H

/*! @} */ // rotaryrgb

// ------------------------------------------------------------------------ END
