/****************************************************************************
** Copyright (C) 2023 MikroElektronika d.o.o.
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
 * @file c7seg2.h
 * @brief This file contains API for 7-SEG 2 Click Driver.
 */

#ifndef C7SEG2_H
#define C7SEG2_H

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
 * @addtogroup c7seg2 7-SEG 2 Click Driver
 * @brief API for configuring and manipulating 7-SEG 2 Click driver.
 * @{
 */

/**
 * @defgroup c7seg2_reg 7-SEG 2 Registers List
 * @brief List of registers of 7-SEG 2 Click driver.
 */

/**
 * @addtogroup c7seg2_reg
 * @{
 */

/**
 * @brief 7-SEG 2 description register.
 * @details Specified register for description of 7-SEG 2 Click driver.
 */
#define C7SEG2_REG_DEVICE_ID                0x00
#define C7SEG2_REG_DEVICE_EN                0x01
#define C7SEG2_REG_CH_EN_LOW                0x02
#define C7SEG2_REG_CH_EN_HIGH               0x03
#define C7SEG2_REG_CONFIG                   0x04
#define C7SEG2_REG_FAULT_MASK               0x05
#define C7SEG2_REG_FAULT_INT                0x06
#define C7SEG2_REG_OPEN_LED_LOW             0x07
#define C7SEG2_REG_OPEN_LED_HIGH            0x08
#define C7SEG2_REG_CUR_LED_CS0              0x09
#define C7SEG2_REG_CUR_LED_CS1              0x0A
#define C7SEG2_REG_CUR_LED_CS2              0x0B
#define C7SEG2_REG_CUR_LED_CS3              0x0C
#define C7SEG2_REG_CUR_LED_CS4              0x0D
#define C7SEG2_REG_CUR_LED_CS5              0x0E
#define C7SEG2_REG_CUR_LED_CS6              0x0F
#define C7SEG2_REG_CUR_LED_CS7              0x10
#define C7SEG2_REG_CUR_LED_CS8              0x11
#define C7SEG2_REG_CUR_LED_CS9              0x12
#define C7SEG2_REG_CUR_LED_CS10             0x13
#define C7SEG2_REG_CUR_LED_CS11             0x14
#define C7SEG2_REG_PATTERN_SEQ_REP          0x15
#define C7SEG2_REG_PATTERN_0_DUR            0x16
#define C7SEG2_REG_PATTERN_1_DUR            0x17
#define C7SEG2_REG_PATTERN_2_DUR            0x18
#define C7SEG2_REG_PATTERN_3_DUR            0x19
#define C7SEG2_REG_PATTERN_4_DUR            0x1A
#define C7SEG2_REG_PATTERN_5_DUR            0x1B
#define C7SEG2_REG_PATTERN_6_DUR            0x1C
#define C7SEG2_REG_PATTERN_7_DUR            0x1D
#define C7SEG2_REG_PWMREG_OFFSET            0x1E
#define C7SEG2_REG_CLOCK_CONFIG             0xE0

/*! @} */ // c7seg2_reg

/**
 * @defgroup c7seg2_set 7-SEG 2 Registers Settings
 * @brief Settings for registers of 7-SEG 2 Click driver.
 */

/**
 * @addtogroup c7seg2_set
 * @{
 */

/**
 * @brief 7-SEG 2 segments setting.
 * @details Specified setting for segments of 7-SEG 2 Click driver.
 */
#define C7SEG2_SEGMENT_0                    0
#define C7SEG2_SEGMENT_1                    1
#define C7SEG2_SEGMENT_2                    2
#define C7SEG2_SEGMENTS_NUMBER              3
#define C7SEG2_SEGMENTS_DISABLED            0x0000u

/**
 * @brief 7-SEG 2 decimal point setting.
 * @details Specified setting for decimal point of 7-SEG 2 Click driver.
 */
#define C7SEG2_DP_NONE                      0
#define C7SEG2_DP_AT_SEGMENT_0              1
#define C7SEG2_DP_AT_SEGMENT_1              2
#define C7SEG2_DP_AT_SEGMENT_2              3
#define C7SEG2_DP_MASK                      0x03
#define C7SEG2_DP_PIN_MASK                  0x0010u

/**
 * @brief 7-SEG 2 refresh rate setting.
 * @details Specified setting for refresh rate of 7-SEG 2 Click driver.
 */
#define C7SEG2_REFRESH_RATE_US              7500
#define C7SEG2_REFRESH_RATE_DELAY           ( C7SEG2_REFRESH_RATE_US / 50 )

/**
 * @brief 7-SEG 2 digits and numbers setting.
 * @details Specified setting for digits and numbers of 7-SEG 2 Click driver.
 */
#define C7SEG2_DIGIT_0                      0
#define C7SEG2_DIGIT_1                      1
#define C7SEG2_DIGIT_2                      2
#define C7SEG2_DIGIT_3                      3
#define C7SEG2_DIGIT_4                      4
#define C7SEG2_DIGIT_5                      5
#define C7SEG2_DIGIT_6                      6
#define C7SEG2_DIGIT_7                      7
#define C7SEG2_DIGIT_8                      8
#define C7SEG2_DIGIT_9                      9
#define C7SEG2_DIGITS_NUMBER                10
#define C7SEG2_MAX_NUMBER                   999

/**
 * @brief 7-SEG 2 description setting.
 * @details Specified setting for description of 7-SEG 2 Click driver.
 */
#define C7SEG2_DEVICE_ID                    0x12

/**
 * @brief 7-SEG 2 device state setting.
 * @details Specified setting for device state of
 * 7-SEG 2 Click driver.
 */
#define C7SEG2_SW_RESET                     0x80
#define C7SEG2_ENABLE                       0x01

/**
 * @brief 7-SEG 2 current calculation setting.
 * @details Specified setting for current calculation selection of
 * 7-SEG 2 Click driver.
 */
#define C7SEG2_CURRENT_DEFAULT              15.0f
#define C7SEG2_CURRENT_STEP_TO_HEX          12.75f

/**
 * @brief 7-SEG 2 device address setting.
 * @details Specified setting for device slave address selection of
 * 7-SEG 2 Click driver.
 */
#define C7SEG2_DEVICE_ADDRESS               0x58

/*! @} */ // c7seg2_set

/**
 * @defgroup c7seg2_map 7-SEG 2 MikroBUS Map
 * @brief MikroBUS pin mapping of 7-SEG 2 Click driver.
 */

/**
 * @addtogroup c7seg2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 7-SEG 2 Click to the selected MikroBUS.
 */
#define C7SEG2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c7seg2_map
/*! @} */ // c7seg2

/**
 * @brief 7-SEG 2 Click context object.
 * @details Context object definition of 7-SEG 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} c7seg2_t;

/**
 * @brief 7-SEG 2 Click configuration object.
 * @details Configuration object definition of 7-SEG 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */
    
    float      current;         /**< Segments current, [mA]. */       

} c7seg2_cfg_t;

/**
 * @brief 7-SEG 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C7SEG2_OK = 0,
    C7SEG2_ERROR = -1

} c7seg2_return_value_t;

/**
 * @brief 7-SEG 2 Click segment number.
 * @details Predefined enum values for segment number values.
 */

/*!
 * @addtogroup c7seg2 7-SEG 2 Click Driver
 * @brief API for configuring and manipulating 7-SEG 2 Click driver.
 * @{
 */

/**
 * @brief 7-SEG 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c7seg2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c7seg2_cfg_setup ( c7seg2_cfg_t *cfg );

/**
 * @brief 7-SEG 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c7seg2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c7seg2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c7seg2_init ( c7seg2_t *ctx, c7seg2_cfg_t *cfg );

/**
 * @brief 7-SEG 2 software reset function.
 * @details This function is used to perform a software reset.
 * @param[in] ctx : Click context object.
 * See #c7seg2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note All the set register values will be reset to factory values after using this function.
 */
err_t c7seg2_sw_reset ( c7seg2_t *ctx );

/**
 * @brief 7-SEG 2 default configuration function.
 * @details This function executes a default configuration of 7-SEG 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #c7seg2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c7seg2_default_cfg ( c7seg2_t *ctx );

/**
 * @brief 7-SEG 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c7seg2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c7seg2_generic_write ( c7seg2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 7-SEG 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c7seg2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c7seg2_generic_read ( c7seg2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 7-SEG 2 get interrupt pin state function.
 * @details This function reads an interrupt pin state.
 * @param[in] ctx : Click context object.
 * See #c7seg2_t object definition for detailed explanation.
 * @return Interrupt pin state.
 * @note None.
 */
uint8_t c7seg2_get_int_pin ( c7seg2_t *ctx );

/**
 * @brief 7-SEG 2 I2C register writing function.
 * @details This function writes a byte of data in 
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c7seg2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c7seg2_write_reg ( c7seg2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 7-SEG 2 I2C register reading function.
 * @details This function reads a byte of data in 
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c7seg2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Data to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c7seg2_read_reg ( c7seg2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief 7-SEG 2 set segments current value function.
 * @details This function is used to set the current value of the segment's leds.
 * @param[in] ctx : Click context object.
 * See #c7seg2_t object definition for detailed explanation.
 * @param[in] current_val : Current value in mA [up to 20mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c7seg2_set_segments_current ( c7seg2_t *ctx, float current_val );

/**
 * @brief 7-SEG 2 single segment writing function.
 * @details This function is used to write a number [0..9] to a selected segment [0..2] with or w/o a decimal pointer.
 * @param[in] ctx : Click context object.
 * See #c7seg2_t object definition for detailed explanation.
 * @param[in] segment : Segment number [0..2].
 * @param[in] number : Number to be displayed [0..9].
 * @param[in] dpt : Decimal point [0..1].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c7seg2_write_segment ( c7seg2_t *ctx, uint8_t segment, uint8_t number, uint8_t dpt );

/**
 * @brief 7-SEG 2 disable segments function.
 * @details This function is used to disable channel output.
 * @param[in] ctx : Click context object.
 * See #c7seg2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c7seg2_disable_segments ( c7seg2_t *ctx );

/**
 * @brief 7-SEG 2 number writing function.
 * @details This function is used to write a number [0..999] to a selected segment [0..2] with or w/o a decimal pointer.
 * @param[in] ctx : Click context object.
 * See #c7seg2_t object definition for detailed explanation.
 * @param[in] number : Number to be displayed [0..999].
 * @param[in] dpt : Decimal point [1..3], [0] if none.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function must be called as frequently as possible in order for a number to be displayed properly.
 */
err_t c7seg2_write_number ( c7seg2_t *ctx, uint16_t number, uint8_t dpt );

#ifdef __cplusplus
}
#endif
#endif // C7SEG2_H

/*! @} */ // c7seg2

// ------------------------------------------------------------------------ END
