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
 * @file leddriver12.h
 * @brief This file contains API for LED Driver 12 Click Driver.
 */

#ifndef LEDDRIVER12_H
#define LEDDRIVER12_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup leddriver12 LED Driver 12 Click Driver
 * @brief API for configuring and manipulating LED Driver 12 Click driver.
 * @{
 */

/**
 * @defgroup leddriver12_reg LED Driver 12 Registers List
 * @brief List of registers of LED Driver 12 Click driver.
 */

/**
 * @addtogroup leddriver12_reg
 * @{
 */

/**
 * @brief LED Driver 12 register list.
 * @details Specified register list of LED Driver 12 Click driver.
 */
#define LEDDRIVER12_REG_INPUT0                      0x00
#define LEDDRIVER12_REG_INPUT1                      0x01
#define LEDDRIVER12_REG_PSC0                        0x02
#define LEDDRIVER12_REG_PWM0                        0x03
#define LEDDRIVER12_REG_PSC1                        0x04
#define LEDDRIVER12_REG_PWM1                        0x05
#define LEDDRIVER12_REG_LS0                         0x06
#define LEDDRIVER12_REG_LS1                         0x07
#define LEDDRIVER12_REG_LS2                         0x08
#define LEDDRIVER12_REG_LS3                         0x09

/*! @} */ // leddriver12_reg

/**
 * @defgroup leddriver12_set LED Driver 12 Registers Settings
 * @brief Settings for registers of LED Driver 12 Click driver.
 */

/**
 * @addtogroup leddriver12_set
 * @{
 */

/**
 * @brief LED Driver 12 Control register setting.
 * @details Specified setting for Control register of LED Driver 12 Click driver.
 */
#define LEDDRIVER12_AUTO_INCREMENT_BIT              0x10

/**
 * @brief LED Driver 12 LED Selector registers setting.
 * @details Specified setting for LED Selector registers of LED Driver 12 Click driver.
 */
#define LEDDRIVER12_LED_OFF                         0x00
#define LEDDRIVER12_LED_ON                          0x01
#define LEDDRIVER12_LED_PWM0                        0x02
#define LEDDRIVER12_LED_PWM1                        0x03
#define LEDDRIVER12_LED0                            0x00
#define LEDDRIVER12_LED1                            0x01
#define LEDDRIVER12_LED2                            0x02
#define LEDDRIVER12_LED3                            0x03
#define LEDDRIVER12_LED4                            0x04
#define LEDDRIVER12_LED5                            0x05
#define LEDDRIVER12_LED6                            0x06
#define LEDDRIVER12_LED7                            0x07
#define LEDDRIVER12_LED8                            0x08
#define LEDDRIVER12_LED9                            0x09
#define LEDDRIVER12_LED10                           0x0A
#define LEDDRIVER12_LED11                           0x0B
#define LEDDRIVER12_LED12                           0x0C
#define LEDDRIVER12_LED13                           0x0D
#define LEDDRIVER12_LED14                           0x0E
#define LEDDRIVER12_LED15                           0x0F
#define LEDDRIVER12_LED0_TO_3                       0x00
#define LEDDRIVER12_LED4_TO_7                       0x01
#define LEDDRIVER12_LED8_TO_11                      0x02
#define LEDDRIVER12_LED12_TO_15                     0x03
#define LEDDRIVER12_ALL_LEDS                        0xFF

/**
 * @brief LED Driver 12 PWM setting.
 * @details Specified setting for PWMregisters of LED Driver 12 Click driver.
 */
#define LEDDRIVER12_BLINK_PERIOD_MAX                1.68421
#define LEDDRIVER12_BLINK_PERIOD_MIN                0.00657
#define LEDDRIVER12_BLINK_PERIOD_ONE_SECOND         1.0
#define LEDDRIVER12_BLINK_PERIOD_HALF_SECOND        0.5
#define LEDDRIVER12_DUTY_CYCLE_MAX                  0xFF
#define LEDDRIVER12_DUTY_CYCLE_HALF                 0x80
#define LEDDRIVER12_DUTY_CYCLE_QUARTER              0x40
#define LEDDRIVER12_DUTY_CYCLE_MIN                  0x00

/**
 * @brief LED Driver 12 device address setting.
 * @details Specified setting for device slave address selection of
 * LED Driver 12 Click driver.
 */
#define LEDDRIVER12_DEV_ADDR_A2A1A0_000             0x60
#define LEDDRIVER12_DEV_ADDR_A2A1A0_001             0x61
#define LEDDRIVER12_DEV_ADDR_A2A1A0_010             0x62
#define LEDDRIVER12_DEV_ADDR_A2A1A0_011             0x63
#define LEDDRIVER12_DEV_ADDR_A2A1A0_100             0x64
#define LEDDRIVER12_DEV_ADDR_A2A1A0_101             0x65
#define LEDDRIVER12_DEV_ADDR_A2A1A0_110             0x66
#define LEDDRIVER12_DEV_ADDR_A2A1A0_111             0x67

/*! @} */ // leddriver12_set

/**
 * @defgroup leddriver12_map LED Driver 12 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Driver 12 Click driver.
 */

/**
 * @addtogroup leddriver12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Driver 12 Click to the selected MikroBUS.
 */
#define LEDDRIVER12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // leddriver12_map
/*! @} */ // leddriver12

/**
 * @brief LED Driver 12 Click context object.
 * @details Context object definition of LED Driver 12 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (Active LOW). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} leddriver12_t;

/**
 * @brief LED Driver 12 Click configuration object.
 * @details Configuration object definition of LED Driver 12 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;            /**< Reset pin (Active LOW). */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} leddriver12_cfg_t;

/**
 * @brief LED Driver 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDDRIVER12_OK = 0,
    LEDDRIVER12_ERROR = -1

} leddriver12_return_value_t;

/*!
 * @addtogroup leddriver12 LED Driver 12 Click Driver
 * @brief API for configuring and manipulating LED Driver 12 Click driver.
 * @{
 */

/**
 * @brief LED Driver 12 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #leddriver12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void leddriver12_cfg_setup ( leddriver12_cfg_t *cfg );

/**
 * @brief LED Driver 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #leddriver12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_init ( leddriver12_t *ctx, leddriver12_cfg_t *cfg );

/**
 * @brief LED Driver 12 default configuration function.
 * @details This function executes a default configuration of LED Driver 12
 * click board.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t leddriver12_default_cfg ( leddriver12_t *ctx );

/**
 * @brief LED Driver 12 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_generic_write ( leddriver12_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief LED Driver 12 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_generic_read ( leddriver12_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief LED Driver 12 write register function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_write_register ( leddriver12_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LED Driver 12 read register function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_read_register ( leddriver12_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LED Driver 12 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void leddriver12_set_rst_pin ( leddriver12_t *ctx, uint8_t state );

/**
 * @brief LED Driver 12 set led config function.
 * @details This function sets the specified LED config.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[in] led_number : LED number [0-15 or 0xFF for all LEDs].
 * @param[in] led_cfg : LED config: @li @c 0 - LED OFF,
 *                                  @li @c 1 - LED ON,
 *                                  @li @c 2 - LED to PWM 0,
 *                                  @li @c 3 - LED to PWM 1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_set_led_config ( leddriver12_t *ctx, uint8_t led_number, uint8_t led_cfg );

/**
 * @brief LED Driver 12 set led port config function.
 * @details This function sets the specified LED port config.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[in] led_port_number : LED port number: @li @c 0 - LEDs 0 to 3,
 *                                               @li @c 1 - LEDs 4 to 7,
 *                                               @li @c 2 - LEDs 8 to 11,
 *                                               @li @c 3 - LEDs 12 to 15.
 * @param[in] led_cfg : LED config: @li @c 0 - LED OFF,
 *                                  @li @c 1 - LED ON,
 *                                  @li @c 2 - LED to PWM 0,
 *                                  @li @c 3 - LED to PWM 1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_set_led_port_config ( leddriver12_t *ctx, uint8_t led_port_number, uint8_t led_cfg );

/**
 * @brief LED Driver 12 read input 0 function.
 * @details This function reads the input 0 register which contains the status of LEDs 0 to 7.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[out] data_out : Input 0 register status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_read_input_0 ( leddriver12_t *ctx, uint8_t *data_out );

/**
 * @brief LED Driver 12 read input 1 function.
 * @details This function reads the input 1 register which contains the status of LEDs 8 to 15.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[out] data_out : Input 1 register status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_read_input_1 ( leddriver12_t *ctx, uint8_t *data_out );

/**
 * @brief LED Driver 12 set blink period pwm 0 function.
 * @details This function sets the blink period of PWM 0 function.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[in] blink_period : Blink period in seconds (MAX: 1.68421, MIN: 0.00657).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_set_blink_period_pwm_0 ( leddriver12_t *ctx, float blink_period );

/**
 * @brief LED Driver 12 set blink period pwm 1 function.
 * @details This function sets the blink period of PWM 1 function.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[in] blink_period : Blink period in seconds (MAX: 1.68421, MIN: 0.00657).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_set_blink_period_pwm_1 ( leddriver12_t *ctx, float blink_period );

/**
 * @brief LED Driver 12 set duty cycle pwm 0 function.
 * @details This function sets the duty cycle of PWM 0.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle value [0x00-0xFF].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_set_duty_cycle_pwm_0 ( leddriver12_t *ctx, uint8_t duty_cycle );

/**
 * @brief LED Driver 12 set duty cycle pwm 1 function.
 * @details This function sets the duty cycle of PWM 1.
 * @param[in] ctx : Click context object.
 * See #leddriver12_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle value [0x00-0xFF].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver12_set_duty_cycle_pwm_1 ( leddriver12_t *ctx, uint8_t duty_cycle );

#ifdef __cplusplus
}
#endif
#endif // LEDDRIVER12_H

/*! @} */ // leddriver12

// ------------------------------------------------------------------------ END
