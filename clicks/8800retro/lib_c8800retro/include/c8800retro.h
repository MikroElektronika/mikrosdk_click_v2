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
 * @file c8800retro.h
 * @brief This file contains API for 8800 Retro Click Driver.
 */

#ifndef C8800RETRO_H
#define C8800RETRO_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup c8800retro 8800 Retro Click Driver
 * @brief API for configuring and manipulating 8800 Retro Click driver.
 * @{
 */

/**
 * @defgroup c8800retro_reg 8800 Retro Registers List
 * @brief List of registers of 8800 Retro Click driver.
 */

/**
 * @addtogroup c8800retro_reg
 * @{
 */

/**
 * @brief 8800 Retro Register Address Map.
 * @details Specified register address map of 8800 Retro Click driver.
 */
#define C8800RETRO_REG_DIGIT_0              0x01
#define C8800RETRO_REG_DIGIT_1              0x02
#define C8800RETRO_REG_DIGIT_2              0x03
#define C8800RETRO_REG_DIGIT_3              0x04
#define C8800RETRO_REG_DIGIT_4              0x05
#define C8800RETRO_REG_DIGIT_5              0x06
#define C8800RETRO_REG_DIGIT_6              0x07
#define C8800RETRO_REG_DIGIT_7              0x08
#define C8800RETRO_REG_DECODE_MODE          0x09
#define C8800RETRO_REG_GLOBAL_INTENSITY     0x0A
#define C8800RETRO_REG_SCAN_LIMIT           0x0B
#define C8800RETRO_REG_SHUTDOWN             0x0C
#define C8800RETRO_REG_SELF_ADDRESSING      0x2D
#define C8800RETRO_REG_FEATURE              0x0E
#define C8800RETRO_REG_DISPLAY_TEST_MODE    0x0F
#define C8800RETRO_REG_DIG0_DIG1_INTENSITY  0x10
#define C8800RETRO_REG_DIG2_DIG3_INTENSITY  0x11
#define C8800RETRO_REG_DIG4_DIG5_INTENSITY  0x12
#define C8800RETRO_REG_DIG6_DIG7_INTENSITY  0x13
#define C8800RETRO_REG_DIAG_DIGIT_0         0x14
#define C8800RETRO_REG_DIAG_DIGIT_1         0x15
#define C8800RETRO_REG_DIAG_DIGIT_2         0x16
#define C8800RETRO_REG_DIAG_DIGIT_3         0x17
#define C8800RETRO_REG_DIAG_DIGIT_4         0x18
#define C8800RETRO_REG_DIAG_DIGIT_5         0x19
#define C8800RETRO_REG_DIAG_DIGIT_6         0x1A
#define C8800RETRO_REG_DIAG_DIGIT_7         0x1B
#define C8800RETRO_REG_KEYA                 0x1C
#define C8800RETRO_REG_KEYB                 0x1D

/*! @} */ // c8800retro_reg

/**
 * @defgroup c8800retro_set 8800 Retro Registers Settings
 * @brief Settings for registers of 8800 Retro Click driver.
 */

/**
 * @addtogroup c8800retro_set
 * @{
 */

/**
 * @brief 8800 Retro shutdown register settings.
 * @details Specified settings for shutdown register of 8800 Retro Click driver.
 */
#define C8800RETRO_SHUTDOWN_RESET           0x00
#define C8800RETRO_SHUTDOWN                 0x80
#define C8800RETRO_NORMAL_OPERATION_RESET   0x01
#define C8800RETRO_NORMAL_OPERATION         0x81

/**
 * @brief 8800 Retro decode mode register settings.
 * @details Specified settings for decode mode register of 8800 Retro Click driver.
 */
#define C8800RETRO_NO_DECODE                0x00
#define C8800RETRO_DECODE_0                 0x01
#define C8800RETRO_DECODE_0_2               0x07
#define C8800RETRO_DECODE_0_5               0x3F
#define C8800RETRO_DECODE_0_2_5             0x25

/**
 * @brief 8800 Retro self addressing register settings.
 * @details Specified settings for self addressing register of 8800 Retro Click driver.
 */
#define C8800RETRO_FACTORY_SET_ADDRESS      0x00
#define C8800RETRO_USER_SET_ADDRESS         0x01

/**
 * @brief 8800 Retro intensity register settings.
 * @details Specified settings for intensity register of 8800 Retro Click driver.
 */
#define C8800RETRO_INTENSITY_1              0x00
#define C8800RETRO_INTENSITY_2              0x01
#define C8800RETRO_INTENSITY_3              0x02
#define C8800RETRO_INTENSITY_4              0x03
#define C8800RETRO_INTENSITY_5              0x04
#define C8800RETRO_INTENSITY_6              0x05
#define C8800RETRO_INTENSITY_7              0x06
#define C8800RETRO_INTENSITY_8              0x07
#define C8800RETRO_INTENSITY_9              0x08
#define C8800RETRO_INTENSITY_10             0x09
#define C8800RETRO_INTENSITY_11             0x0A
#define C8800RETRO_INTENSITY_12             0x0B
#define C8800RETRO_INTENSITY_13             0x0C
#define C8800RETRO_INTENSITY_14             0x0D
#define C8800RETRO_INTENSITY_15             0x0E
#define C8800RETRO_INTENSITY_16             0x0F

/**
 * @brief 8800 Retro scan limit register settings.
 * @details Specified settings for scan limit register of 8800 Retro Click driver.
 */
#define C8800RETRO_SCAN_LIMIT_0             0x00
#define C8800RETRO_SCAN_LIMIT_0_1           0x01
#define C8800RETRO_SCAN_LIMIT_0_2           0x02
#define C8800RETRO_SCAN_LIMIT_0_3           0x03
#define C8800RETRO_SCAN_LIMIT_0_4           0x04
#define C8800RETRO_SCAN_LIMIT_0_5           0x05
#define C8800RETRO_SCAN_LIMIT_0_6           0x06
#define C8800RETRO_SCAN_LIMIT_0_7           0x07

/**
 * @brief 8800 Retro keypad flags.
 * @details Specified keypad flags of 8800 Retro Click driver.
 */
#define C8800RETRO_KEY_NONE                 0x0000
#define C8800RETRO_KEY_A1                   0x8000
#define C8800RETRO_KEY_A2                   0x4000
#define C8800RETRO_KEY_A3                   0x2000
#define C8800RETRO_KEY_A4                   0x1000
#define C8800RETRO_KEY_B1                   0x0800
#define C8800RETRO_KEY_B2                   0x0400
#define C8800RETRO_KEY_B3                   0x0200
#define C8800RETRO_KEY_B4                   0x0100
#define C8800RETRO_KEY_C1                   0x0080
#define C8800RETRO_KEY_C2                   0x0040
#define C8800RETRO_KEY_C3                   0x0020
#define C8800RETRO_KEY_C4                   0x0010
#define C8800RETRO_KEY_D1                   0x0008
#define C8800RETRO_KEY_D2                   0x0004
#define C8800RETRO_KEY_D3                   0x0002
#define C8800RETRO_KEY_D4                   0x0001

/**
 * @brief 8800 Retro scroll settings.
 * @details Specified settings for scroll mode of 8800 Retro Click driver.
 */
#define C8800RETRO_SCROLL_SPEED_SLOW        300
#define C8800RETRO_SCROLL_SPEED_MEDIUM      150
#define C8800RETRO_SCROLL_SPEED_FAST        50
#define C8800RETRO_SCROLL_HORIZONTAL_LEFT   0
#define C8800RETRO_SCROLL_HORIZONTAL_RIGHT  1
#define C8800RETRO_SCROLL_VERTICAL_UP       2
#define C8800RETRO_SCROLL_VERTICAL_DOWN     3

/**
 * @brief 8800 Retro device address setting.
 * @details Specified setting for device slave address selection of
 * 8800 Retro Click driver.
 */
#define C8800RETRO_SET_DEV_ADDR             0x00

/*! @} */ // c8800retro_set

/**
 * @defgroup c8800retro_map 8800 Retro MikroBUS Map
 * @brief MikroBUS pin mapping of 8800 Retro Click driver.
 */

/**
 * @addtogroup c8800retro_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 8800 Retro Click to the selected MikroBUS.
 */
#define C8800RETRO_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c8800retro_map
/*! @} */ // c8800retro

/**
 * @brief 8800 Retro Click context object.
 * @details Context object definition of 8800 Retro Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;                           /**< Interupt Request pin. */

    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} c8800retro_t;

/**
 * @brief 8800 Retro Click configuration object.
 * @details Configuration object definition of 8800 Retro Click driver.
 */
typedef struct
{
    pin_name_t  scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;                             /**< Interupt Request pin. */

    uint32_t  i2c_speed;                             /**< I2C serial speed. */
    uint8_t   i2c_address;                           /**< I2C slave address. */

} c8800retro_cfg_t;

/**
 * @brief 8800 Retro Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C8800RETRO_OK = 0,
    C8800RETRO_ERROR = -1

} c8800retro_return_value_t;

/*!
 * @addtogroup c8800retro 8800 Retro Click Driver
 * @brief API for configuring and manipulating 8800 Retro Click driver.
 * @{
 */

/**
 * @brief 8800 Retro configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c8800retro_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c8800retro_cfg_setup ( c8800retro_cfg_t *cfg );

/**
 * @brief 8800 Retro initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c8800retro_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c8800retro_init ( c8800retro_t *ctx, c8800retro_cfg_t *cfg );

/**
 * @brief 8800 Retro default configuration function.
 * @details This function executes a default configuration of 8800 Retro
 * click board.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c8800retro_default_cfg ( c8800retro_t *ctx );

/**
 * @brief 8800 Retro write register function.
 * @details This function writes a byte of data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c8800retro_write_reg ( c8800retro_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 8800 Retro read register function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c8800retro_read_reg ( c8800retro_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 8800 Retro clear display function.
 * @details This function clears the display by writing zeros to all digit registers.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c8800retro_clear_display ( c8800retro_t *ctx );

/**
 * @brief 8800 Retro display char function.
 * @details This function displays a single character from the predefined charset (IBM BIOS 8x8 font array).
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @param[in] char_index : 0-31,127 : Code page 437, cf. https://en.wikipedia.org/wiki/Code_page_437
 *                         32-126   : ASCII
 *                         160-255  : ISO-8859-1, cf. https://en.wikipedia.org/wiki/ISO/IEC_8859-1
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c8800retro_display_char ( c8800retro_t *ctx, uint8_t char_index );

/**
 * @brief 8800 Retro display image function.
 * @details This function displays an image (array of 8 bytes) on the LED matrix.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @param[in] p_image : Pointer to image buffer (array of 8 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c8800retro_display_image ( c8800retro_t *ctx, uint8_t *p_image );

/**
 * @brief 8800 Retro display string function.
 * @details This function scrolls a desired string on LEDs.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @param[in] scroll_mode : @li @c 0 - Horizontal left.
 *                          @li @c 1 - Horizontal right.
 *                          @li @c 2 - Vertical up.
 *                          @li @c 3 - Vertical down.
 * @param[in] scroll_speed_ms : Scroll speed in miliseconds.
 * @param[in] text : Text string (up to 32 characters).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c8800retro_display_string ( c8800retro_t *ctx, uint8_t scroll_mode, uint16_t scroll_speed_ms, uint8_t *text );

/**
 * @brief 8800 Retro get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c8800retro_get_int_pin ( c8800retro_t *ctx );

/**
 * @brief 8800 Retro clear interrupt function.
 * @details This function clears all interrupts by reading KEYA and KEYB registers.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c8800retro_clear_interrupt ( c8800retro_t *ctx );

/**
 * @brief 8800 Retro get keypad function.
 * @details This function reads KEYA and KEYB registers and stores the register's inverted value 
 * to the @b keypad variable.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @param[out] keypad : KEYx register content inverted. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Refer to 8800 Retro keypad flags definition.
 */
err_t c8800retro_get_keypad ( c8800retro_t *ctx, uint16_t *keypad );

#ifdef __cplusplus
}
#endif
#endif // C8800RETRO_H

/*! @} */ // c8800retro

// ------------------------------------------------------------------------ END
