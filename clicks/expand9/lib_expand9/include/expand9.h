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
 * @file expand9.h
 * @brief This file contains API for Expand 9 Click Driver.
 */

#ifndef EXPAND9_H
#define EXPAND9_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup expand9 Expand 9 Click Driver
 * @brief API for configuring and manipulating Expand 9 Click driver.
 * @{
 */

/**
 * @defgroup expand9_reg Expand 9 Registers List
 * @brief List of registers of Expand 9 Click driver.
 */

/**
 * @addtogroup expand9_reg
 * @{
 */

/**
 * @brief Expand 9 description register.
 * @details Specified register for description of Expand 9 Click driver.
 */
#define EXPAND9_REG_INPUT_DISABLE_B	             0x00
#define EXPAND9_REG_INPUT_DISABLE_A	             0x01
#define EXPAND9_REG_LONG_SLEW_B	                 0x02
#define EXPAND9_REG_LONG_SLEW_A                  0x03
#define EXPAND9_REG_LOW_DRIVE_B                  0x04
#define EXPAND9_REG_LOW_DRIVE_A                  0x05
#define EXPAND9_REG_PULL_UP_B                    0x06
#define EXPAND9_REG_PULL_UP_A                    0x07
#define EXPAND9_REG_PULL_DOWN_B                  0x08
#define EXPAND9_REG_PULL_DOWN_A                  0x09
#define EXPAND9_REG_OPEN_DRAIN_B                 0x0A
#define EXPAND9_REG_OPEN_DRAIN_A                 0x0B
#define EXPAND9_REG_POLARITY_B                   0x0C
#define EXPAND9_REG_POLARITY_A                   0x0D
#define EXPAND9_REG_DIR_B                        0x0E
#define EXPAND9_REG_DIR_A                        0x0F
#define EXPAND9_REG_DATA_B                       0x10
#define EXPAND9_REG_DATA_A                       0x11
#define EXPAND9_REG_INTERRUPT_MASK_B             0x12
#define EXPAND9_REG_INTERRUPT_MASK_A             0x13
#define EXPAND9_REG_SENSE_HIGH_B                 0x14
#define EXPAND9_REG_SENSE_LOW_B                  0x15
#define EXPAND9_REG_SENSE_HIGH_A                 0x16
#define EXPAND9_REG_SENSE_LOW_A                  0x17
#define EXPAND9_REG_INTERRUPT_SOURCE_B           0x18
#define EXPAND9_REG_INTERRUPT_SOURCE_A           0x19
#define EXPAND9_REG_EVENT_STATUS_B               0x1A
#define EXPAND9_REG_EVENT_STATUS_A               0x1B
#define EXPAND9_REG_LEVEL_SHIFTER_1              0x1C
#define EXPAND9_REG_LEVEL_SHIFTER_2              0x1D
#define EXPAND9_REG_CLOCK                        0x1E
#define EXPAND9_REG_MISC                         0x1F
#define EXPAND9_REG_LED_DRIVER_ENABLE_B          0x20
#define EXPAND9_REG_LED_DRIVER_ENABLE_A          0x21
#define EXPAND9_REG_DEBOUNCE_CONFIG              0x22
#define EXPAND9_REG_DEBOUNCE_ENABLE_B            0x23
#define EXPAND9_REG_DEBOUNCE_ENABLE_A            0x24
#define EXPAND9_REG_KEY_CONFIG_1                 0x25
#define EXPAND9_REG_KEY_CONFIG_2                 0x26
#define EXPAND9_REG_KEY_DATA_1                   0x27
#define EXPAND9_REG_KEY_DATA_2                   0x28
#define EXPAND9_REG_T_ON_0                       0x29
#define EXPAND9_REG_I_ON_0                       0x2A
#define EXPAND9_REG_OFF_0                        0x2B
#define EXPAND9_REG_T_ON_1                       0x2C
#define EXPAND9_REG_I_ON_1                       0x2D
#define EXPAND9_REG_OFF_1                        0x2E
#define EXPAND9_REG_T_ON_2                       0x2F
#define EXPAND9_REG_I_ON_2                       0x30
#define EXPAND9_REG_OFF_2                        0x31
#define EXPAND9_REG_T_ON_3                       0x32
#define EXPAND9_REG_I_ON_3                       0x33
#define EXPAND9_REG_OFF_3                        0x34
#define EXPAND9_REG_T_ON_4                       0x35
#define EXPAND9_REG_I_ON_4                       0x36
#define EXPAND9_REG_OFF_4                        0x37
#define EXPAND9_REG_T_RISE_4                     0x38
#define EXPAND9_REG_T_FALL_4                     0x39
#define EXPAND9_REG_T_ON_5                       0x3A
#define EXPAND9_REG_I_ON_5                       0x3B
#define EXPAND9_REG_OFF_5                        0x3C
#define EXPAND9_REG_T_RISE_5                     0x3D
#define EXPAND9_REG_T_FALL_5                     0x3E
#define EXPAND9_REG_T_ON_6                       0x3F
#define EXPAND9_REG_I_ON_6                       0x40
#define EXPAND9_REG_OFF_6                        0x41
#define EXPAND9_REG_T_RISE_6                     0x42
#define EXPAND9_REG_T_FALL_6                     0x43
#define EXPAND9_REG_T_ON_7                       0x44
#define EXPAND9_REG_I_ON_7                       0x45
#define EXPAND9_REG_OFF_7                        0x46
#define EXPAND9_REG_T_RISE_7                     0x47
#define EXPAND9_REG_T_FALL_7                     0x48
#define EXPAND9_REG_T_ON_8                       0x49
#define EXPAND9_REG_I_ON_8                       0x4A
#define EXPAND9_REG_OFF_8                        0x4B
#define EXPAND9_REG_T_ON_9                       0x4C
#define EXPAND9_REG_I_ON_9                       0x4D
#define EXPAND9_REG_OFF_9                        0x4E
#define EXPAND9_REG_T_ON_10                      0x4F
#define EXPAND9_REG_I_ON_10                      0x50
#define EXPAND9_REG_OFF_10                       0x51
#define EXPAND9_REG_T_ON_11                      0x52
#define EXPAND9_REG_I_ON_11                      0x53
#define EXPAND9_REG_OFF_11                       0x54
#define EXPAND9_REG_T_ON_12                      0x55
#define EXPAND9_REG_I_ON_12                      0x56
#define EXPAND9_REG_OFF_12                       0x57
#define EXPAND9_REG_T_RISE_12                    0x58
#define EXPAND9_REG_T_FALL_12                    0x59
#define EXPAND9_REG_T_ON_13                      0x5A
#define EXPAND9_REG_I_ON_13                      0x5B
#define EXPAND9_REG_OFF_13                       0x5C
#define EXPAND9_REG_T_RISE_13                    0x5D
#define EXPAND9_REG_T_FALL_13                    0x5E
#define EXPAND9_REG_T_ON_14                      0x5F
#define EXPAND9_REG_I_ON_14                      0x60
#define EXPAND9_REG_OFF_14                       0x61
#define EXPAND9_REG_T_RISE_14                    0x62
#define EXPAND9_REG_T_FALL_14                    0x63
#define EXPAND9_REG_T_ON_15                      0x64
#define EXPAND9_REG_I_ON_15                      0x65
#define EXPAND9_REG_OFF_15                       0x66
#define EXPAND9_REG_T_RISE_15                    0x67
#define EXPAND9_REG_T_FALL_15                    0x68
#define EXPAND9_REG_HIGH_INPUT_B                 0x69
#define EXPAND9_REG_HIGH_INPUT_A                 0x6A
#define EXPAND9_REG_RESET                        0x7D
#define EXPAND9_REG_TEST_1                       0x7E
#define EXPAND9_REG_TEST_2                       0x7F

/*! @} */ // expand9_reg

/**
 * @defgroup expand9_set Expand 9 Registers Settings
 * @brief Settings for registers of Expand 9 Click driver.
 */

/**
 * @addtogroup expand9_set
 * @{
 */

/**
 * @brief Expand 9 description setting.
 * @details Specified setting for description of Expand 9 Click driver.
 */
#define EXPAND9_CHANGE                           0x01
#define EXPAND9_FALLING                          0x02
#define EXPAND9_RISING                           0x03
#define EXPAND9_FREQ_DIV_1                       0x01
#define EXPAND9_FREQ_DIV_2                       0x02
#define EXPAND9_FREQ_DIV_3                       0x03
#define EXPAND9_FREQ_DIV_4                       0x04
#define EXPAND9_FREQ_DIV_5                       0x05
#define EXPAND9_FREQ_DIV_6                       0x06
#define EXPAND9_FREQ_DIV_7                       0x07
#define EXPAND9_LED_MODE_LINEAR                  0x00
#define EXPAND9_LED_MODE_LOGARITHMIC             0x01

/**
 * @brief Expand 9 device address setting.
 * @details Specified setting for device slave address selection of
 * Expand 9 Click driver.
 */
#define EXPAND9_SET_DEV_ADDR_GND                 0x3E
#define EXPAND9_SET_DEV_ADDR_VCC                 0x70

/*! @} */ // expand9_set

/**
 * @defgroup expand9_map Expand 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 9 Click driver.
 */

/**
 * @addtogroup expand9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 9 Click to the selected MikroBUS.
 */
#define EXPAND9_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.add = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // expand9_map
/*! @} */ // expand9

/**
 * @brief Expand 9 Click context object.
 * @details Context object definition of Expand 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  add;     /**< Address pin. */
    digital_out_t  rst;     /**< Reset pin.   */


    // Input pins
    digital_in_t  int_pin;  /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} expand9_t;

/**
 * @brief Expand 9 Click configuration object.
 * @details Configuration object definition of Expand 9 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  add;        /**< Address pin. */
    pin_name_t  rst;        /**< Reset pin.   */
    pin_name_t  int_pin;    /**< Interrupt pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} expand9_cfg_t;

/**
 * @brief Expand 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   EXPAND9_OK = 0,
   EXPAND9_ERROR = -1

} expand9_return_value_t;

/**
 * @brief Expand 9 Click direction value data.
 * @details Predefined enum values for driver direction values.
 */
typedef enum
{
   DIRECTION_INPUT = 0,
   DIRECTION_OUTPUT =  1

} expand9_direction_value_t;

/**
 * @brief Expand 9 Click channel state value data.
 * @details Predefined enum values for driver channel state values.
 */
typedef enum
{
   CH_OUTPUT_OFF = 0,
   CH_OUTPUT_ON =  1

} expand9_ch_state_value_t;

/*!
 * @addtogroup expand9 Expand 9 Click Driver
 * @brief API for configuring and manipulating Expand 9 Click driver.
 * @{
 */

/**
 * @brief Expand 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand9_cfg_setup ( expand9_cfg_t *cfg );

/**
 * @brief Expand 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_init ( expand9_t *ctx, expand9_cfg_t *cfg );

/**
 * @brief Expand 9 default configuration function.
 * @details This function executes a default configuration of Expand 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t expand9_default_cfg ( expand9_t *ctx );

/**
 * @brief Expand 9 set I2C Slave address function.
 * @details This function sets I2C address of the subordinate I2C device
 * to \p address which is targeted by read and write operations.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] slave_addr : Specified I2C slave address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note It is recommended to check return value for error.
 */
err_t expand9_set_slave_address ( expand9_t *ctx, uint8_t slave_addr );

/**
 * @brief Expand 9 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_generic_write ( expand9_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Expand 9 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_generic_read ( expand9_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Expand 9 software reset function.
 * @details This function performs software reset of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_soft_reset ( expand9_t *ctx );

/**
 * @brief Expand 9 set channel direction function.
 * @details This function sets desired direction  of the desired channel of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] direction : Direction object data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_set_ch_direction ( expand9_t *ctx, uint8_t ch_pos, expand9_direction_value_t direction );

/**
 * @brief Expand 9 set all channel output function.
 * @details This function sets output direction for all channels of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_set_all_ch_output ( expand9_t *ctx );

/**
 * @brief Expand 9 set all channel input function.
 * @details This function sets input direction for all channels of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_set_all_ch_input ( expand9_t *ctx );

/**
 * @brief Expand 9 set channel output state function.
 * @details This function sets output state of the desired channel of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] ch_pos : Desired channel position [ 0 - 15 ].
 * @param[in] ch_state : Channel state object data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_set_ch_output_state ( expand9_t *ctx, uint8_t ch_pos, expand9_ch_state_value_t ch_state );

/**
 * @brief Expand 9 get channel output state function.
 * @details This function get output state of the desired channel of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] ch_pos : Desired channel position [ 0 - 15 ].
 * @param[out] ch_state : Channel state object data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_get_ch_output_state ( expand9_t *ctx, uint8_t ch_pos, expand9_ch_state_value_t *ch_state );

/**
 * @brief Expand 9 write channel function.
 * @details This function writes a channel to either high or low 
 * if it's configured as an output. If the channel is configured as an 
 * input, this method will activate either the pull-up	or pull-down
 * resistor ( high or low respectively ) of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] ch_pos : Desired channel position [ 0 - 15 ].
 * @param[in] ch_state : Channel state object data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_write_ch (  expand9_t *ctx, uint8_t ch_pos, expand9_ch_state_value_t ch_state );

/**
 * @brief Expand 9 read channel function.
 * @details This function reads the input channel state ( high or low ) of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] ch_pos : Desired channel position [ 0 - 15 ].
 * @param[out] ch_state : Channel state object data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_read_ch ( expand9_t *ctx, uint8_t ch_pos, expand9_ch_state_value_t *ch_state );

/**
 * @brief Expand 9 LED driver configuration function.
 * @details This function rinitializes LED  driving on a channel. 
 * It must be called if you want to use the pwm or blink functions 
 * on that channel of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] ch_pos : Desired channel position [ 0 - 15 ].
 * @param[in] freq_div : LED clock frequency divider.
 * @param[in] lin_log : selects either linear or logarithmic mode on the LED drivers:
 *         @li @c  0 - Linear mode,
 *         @li @c  1 - Logarithmic mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_led_driver_config ( expand9_t *ctx, uint8_t ch_pos, uint8_t freq_div, uint8_t lin_log );

/**
 * @brief Expand 9 set intensity function.
 * @details This function can be used to control the intensity 
 * of an output channel connected to an LED of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] ch_pos : Desired channel position [ 0 - 15 ].
 * @param[in] intensity : Intensity of the LED.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_set_intensity ( expand9_t *ctx, uint8_t ch_pos, uint8_t intensity );

/**
 * @brief Expand 9 sync function.
 * @details This function resets the PWM/Blink/Fade counters, syncing any 
 * blinking LEDs of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_sync ( expand9_t *ctx );

/**
 * @brief Expand 9 sync function.
 * @details This function resets the PWM/Blink/Fade counters, syncing any 
 * blinking LEDs of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] config_val : configuring the debounce time:
 *         @li @c  0 -  0.5 ms * 1/clk,
 *         @li @c  1 -  1 ms * 1/clk,
 *         @li @c  2 -  2 ms * 1/clk,
 *         @li @c  3 -  3 ms * 1/clk,
 *         @li @c  4 -  8 ms * 1/clk,
 *         @li @c  5 - 16 ms * 1/clk,
 *         @li @c  6 - 32 ms * 1/clk,
 *         @li @c  7 - 64 ms * 1/clk.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_debounce_config ( expand9_t *ctx, uint8_t config_val );

/**
 * @brief Expand 9 enable channel interrupt function.
 * @details This function enable interrupt for desired channels of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[in] ch_pos : Desired channel position [ 0 - 15 ].
 * @param[in] rise_fall : Interrupt mode:
 *         @li @c  0x01 ( EXPAND9_CHANGE )  - Both,
 *         @li @c  0x02 ( EXPAND9_FALLING ) - Falling,
 *         @li @c  0x03 ( EXPAND9_RISING )  - Rising.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_enable_ch_interrupt ( expand9_t *ctx, uint8_t ch_pos, uint8_t rise_fall );

/**
 * @brief Expand 9 clear all interrupt function.
 * @details This function clear all interrupts of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_clear_interrupt ( expand9_t *ctx );

/**
 * @brief Expand 9 check channel interrupt function.
 * @details This function check interrupt for desired channels of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * @param[out] ch_pos : Desired channel position [ 0 - 15 ].
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand9_check_ch_interrupt ( expand9_t *ctx, uint8_t ch_pos, expand9_ch_state_value_t *int_state );

/**
 * @brief Expand 9 check interrupt pin function.
 * @details This function check interrupt pi state of the SX1509QB,
 * World’s Lowest Voltage Level Shifting GPIO with LED Driver and Keypad Engine
 * on the Expand 9 click board™.
 * @param[in] ctx : Click context object.
 * See #expand9_t object definition for detailed explanation.
 * 
 * @return @li @c 0 - INT pin state low,
 *         @li @c 1 - INT pin state high.
 *
 * @note None.
 */
uint8_t expand9_check_interrupt_pin ( expand9_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EXPAND9_H

/*! @} */ // expand9

// ------------------------------------------------------------------------ END
