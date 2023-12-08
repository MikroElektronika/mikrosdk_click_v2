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
 * @file leddriver19.h
 * @brief This file contains API for LED Driver 19 Click Driver.
 */

#ifndef LEDDRIVER19_H
#define LEDDRIVER19_H

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
 * @addtogroup leddriver19 LED Driver 19 Click Driver
 * @brief API for configuring and manipulating LED Driver 19 Click driver.
 * @{
 */

/**
 * @defgroup leddriver19_reg LED Driver 19 Registers List
 * @brief List of registers of LED Driver 19 Click driver.
 */

/**
 * @addtogroup leddriver19_reg
 * @{
 */

/**
 * @brief LED Driver 19 description register.
 * @details Specified register for description of LED Driver 19 Click driver.
 */
#define LEDDRIVER19_REG_DEVICE_ID               0x00
#define LEDDRIVER19_REG_DEVICE_EN               0x01
#define LEDDRIVER19_REG_CH_EN_LOW               0x02
#define LEDDRIVER19_REG_CH_EN_HIGH              0x03
#define LEDDRIVER19_REG_CONFIG                  0x04
#define LEDDRIVER19_REG_FAULT_MASK              0x05
#define LEDDRIVER19_REG_FAULT_INT               0x06
#define LEDDRIVER19_REG_OPEN_LED_LOW            0x07
#define LEDDRIVER19_REG_OPEN_LED_HIGH           0x08
#define LEDDRIVER19_REG_CUR_LED_CS0             0x09
#define LEDDRIVER19_REG_CUR_LED_CS1             0x0A
#define LEDDRIVER19_REG_CUR_LED_CS2             0x0B
#define LEDDRIVER19_REG_CUR_LED_CS3             0x0C
#define LEDDRIVER19_REG_CUR_LED_CS4             0x0D
#define LEDDRIVER19_REG_CUR_LED_CS5             0x0E
#define LEDDRIVER19_REG_CUR_LED_CS6             0x0F
#define LEDDRIVER19_REG_CUR_LED_CS7             0x10
#define LEDDRIVER19_REG_CUR_LED_CS8             0x11
#define LEDDRIVER19_REG_CUR_LED_CS9             0x12
#define LEDDRIVER19_REG_CUR_LED_CS10            0x13
#define LEDDRIVER19_REG_CUR_LED_CS11            0x14
#define LEDDRIVER19_REG_PATTERN_SEQ_REP         0x15
#define LEDDRIVER19_REG_PATTERN_0_DUR           0x16
#define LEDDRIVER19_REG_PATTERN_1_DUR           0x17
#define LEDDRIVER19_REG_PATTERN_2_DUR           0x18
#define LEDDRIVER19_REG_PATTERN_3_DUR           0x19
#define LEDDRIVER19_REG_PATTERN_4_DUR           0x1A
#define LEDDRIVER19_REG_PATTERN_5_DUR           0x1B
#define LEDDRIVER19_REG_PATTERN_6_DUR           0x1C
#define LEDDRIVER19_REG_PATTERN_7_DUR           0x1D
#define LEDDRIVER19_REG_PWMREG_OFFSET           0x1E
#define LEDDRIVER19_REG_CLOCK_CONFIG            0xE0


/*! @} */ // leddriver19_reg

/**
 * @defgroup leddriver19_set LED Driver 19 Registers Settings
 * @brief Settings for registers of LED Driver 19 Click driver.
 */

/**
 * @addtogroup leddriver19_set
 * @{
 */

/**
 * @brief LED Driver 19 description setting.
 * @details Specified setting for description of LED Driver 19 Click driver.
 */
#define LEDDRIVER19_DEVICE_ID                   0x12

/**
 * @brief LED Driver 19 pin state setting.
 * @details Specified setting for pin state of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_PIN_STATE_HIGH              0x01
#define LEDDRIVER19_PIN_STATE_LOW               0x00

/**
 * @brief LED Driver 19 device state setting.
 * @details Specified setting for device state of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_SW_RESET                    0x80
#define LEDDRIVER19_ENABLE                      0x01

/**
 * @brief LED Driver 19 pattern state setting.
 * @details Specified setting for pattern state of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_PATSEL_0                    0x00
#define LEDDRIVER19_PATSEL_1                    0x01
#define LEDDRIVER19_PATSEL_2                    0x02
#define LEDDRIVER19_PATSEL_3                    0x03
#define LEDDRIVER19_PATSEL_4                    0x04
#define LEDDRIVER19_PATSEL_5                    0x05
#define LEDDRIVER19_PATSEL_6                    0x06
#define LEDDRIVER19_PATSEL_7                    0x07

/**
 * @brief LED Driver 19 channel enable setting.
 * @details Specified setting for enabling channel of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_CH_SEL_0                    0x00
#define LEDDRIVER19_CH_SEL_1                    0x01
#define LEDDRIVER19_CH_SEL_2                    0x02
#define LEDDRIVER19_CH_SEL_3                    0x03
#define LEDDRIVER19_CH_SEL_4                    0x04
#define LEDDRIVER19_CH_SEL_5                    0x05
#define LEDDRIVER19_CH_SEL_6                    0x06
#define LEDDRIVER19_CH_SEL_7                    0x07
#define LEDDRIVER19_CH_SEL_8                    0x08
#define LEDDRIVER19_CH_SEL_9                    0x09
#define LEDDRIVER19_CH_SEL_10                   0x0A
#define LEDDRIVER19_CH_SEL_11                   0x0B

/**
 * @brief LED Driver 19 config setting.
 * @details Specified setting for config of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_SHFT_EN                     0x08
#define LEDDRIVER19_SHFT_DIS                    0x00
#define LEDDRIVER19_GCTRL_EN                    0x01
#define LEDDRIVER19_GCTRL_DIS                   0x00
#define LEDDRIVER19_PATSR_RUNING                0x01
#define LEDDRIVER19_PATSR_DONE                  0x00
#define LEDDRIVER19_PATS_EN                     0x01
#define LEDDRIVER19_PATS_DIS                    0x00

/**
 * @brief LED Driver 19 interrupt masks setting.
 * @details Specified setting for interrupt masks of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_OVTP_MASK                   0x01
#define LEDDRIVER19_OPEN_MASK                   0x02
#define LEDDRIVER19_PAT_MASK                    0x04
#define LEDDRIVER19_SOF_MASK                    0x08

/**
 * @brief LED Driver 19 interrupt flags setting.
 * @details Specified setting for interrupt flags of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_OVTP                        0x01
#define LEDDRIVER19_OPEN                        0x02
#define LEDDRIVER19_PAT                         0x04
#define LEDDRIVER19_SOF                         0x08

/**
 * @brief LED Driver 19 pattern selection setting.
 * @details Specified setting for pattern selection of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_PATTERN_SEL_OFFSET          0x18

/**
 * @brief LED Driver 19 PWM mask setting.
 * @details Specified setting for PWM mask of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_PWM_MASK                    0x0FFFu

/**
 * @brief LED Driver 19 channel open state setting.
 * @details Specified setting for channel open state of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_CS0_OPEN                    0x0001u
#define LEDDRIVER19_CS1_OPEN                    0x0002u
#define LEDDRIVER19_CS2_OPEN                    0x0004u
#define LEDDRIVER19_CS3_OPEN                    0x0008u
#define LEDDRIVER19_CS4_OPEN                    0x0010u
#define LEDDRIVER19_CS5_OPEN                    0x0020u
#define LEDDRIVER19_CS6_OPEN                    0x0040u
#define LEDDRIVER19_CS7_OPEN                    0x0080u
#define LEDDRIVER19_CS8_OPEN                    0x0100u
#define LEDDRIVER19_CS9_OPEN                    0x0200u
#define LEDDRIVER19_CS10_OPEN                   0x0400u
#define LEDDRIVER19_CS11_OPEN                   0x0800u

/**
 * @brief LED Driver 19 channel selection setting.
 * @details Specified setting for channel selection of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_CS0_ENABLE                  0x0001u
#define LEDDRIVER19_CS1_ENABLE                  0x0002u
#define LEDDRIVER19_CS2_ENABLE                  0x0004u
#define LEDDRIVER19_CS3_ENABLE                  0x0008u
#define LEDDRIVER19_CS4_ENABLE                  0x0010u
#define LEDDRIVER19_CS5_ENABLE                  0x0020u
#define LEDDRIVER19_CS6_ENABLE                  0x0040u
#define LEDDRIVER19_CS7_ENABLE                  0x0080u
#define LEDDRIVER19_CS8_ENABLE                  0x0100u
#define LEDDRIVER19_CS9_ENABLE                  0x0200u
#define LEDDRIVER19_CS10_ENABLE                 0x0400u
#define LEDDRIVER19_CS11_ENABLE                 0x0800u
#define LEDDRIVER19_CS_ENABLE_ALL               0x0FFFu

/**
 * @brief LED Driver 19 calculation setting.
 * @details Specified setting for calculation selection of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_PWM_VAL_CONVERSION          40.95f
#define LEDDRIVER19_CURRENT_STEP_TO_MA          0.07843f
#define LEDDRIVER19_CURRENT_STEP_TO_HEX         12.75f

/**
 * @brief LED Driver 19 device address setting.
 * @details Specified setting for device slave address selection of
 * LED Driver 19 Click driver.
 */
#define LEDDRIVER19_DEVICE_ADDRESS_0            0x58
#define LEDDRIVER19_DEVICE_ADDRESS_1            0x59
#define LEDDRIVER19_DEVICE_ADDRESS_2            0x5A
#define LEDDRIVER19_DEVICE_ADDRESS_3            0x5B

/*! @} */ // leddriver19_set

/**
 * @defgroup leddriver19_map LED Driver 19 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Driver 19 Click driver.
 */

/**
 * @addtogroup leddriver19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Driver 19 Click to the selected MikroBUS.
 */
#define LEDDRIVER19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // leddriver19_map
/*! @} */ // leddriver19

/**
 * @brief LED Driver 19 Click context object.
 * @details Context object definition of LED Driver 19 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} leddriver19_t;

/**
 * @brief LED Driver 19 Click configuration object.
 * @details Configuration object definition of LED Driver 19 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} leddriver19_cfg_t;

/**
 * @brief LED Driver 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDDRIVER19_OK = 0,
    LEDDRIVER19_ERROR = -1

} leddriver19_return_value_t;

/*!
 * @addtogroup leddriver19 LED Driver 19 Click Driver
 * @brief API for configuring and manipulating LED Driver 19 Click driver.
 * @{
 */

/**
 * @brief LED Driver 19 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #leddriver19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void leddriver19_cfg_setup ( leddriver19_cfg_t *cfg );

/**
 * @brief LED Driver 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #leddriver19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver19_init ( leddriver19_t *ctx, leddriver19_cfg_t *cfg );

/**
 * @brief LED Driver 19 default configuration function.
 * @details This function executes a default configuration of LED Driver 19
 * click board.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t leddriver19_default_cfg ( leddriver19_t *ctx );

/**
 * @brief LED Driver 19 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver19_generic_write ( leddriver19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LED Driver 19 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver19_generic_read ( leddriver19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LED Driver 19 get interrupt pin state function.
 * @details This function reads an interrupt pin state.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @return Interrupt pin state.
 * @note None.
 */
uint8_t leddriver19_get_int_pin ( leddriver19_t *ctx );

/**
 * @brief LED Driver 19 I2C register writing function.
 * @details This function writes a byte of data in 
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver19_write_reg ( leddriver19_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LED Driver 19 I2C register reading function.
 * @details This function reads bytes of data  from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver19_read_reg ( leddriver19_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LED Driver 19 software reset function.
 * @details This function is used to perform a software reset.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note All the set register values will be reset to factory values after using this function.
 */
err_t leddriver19_sw_reset ( leddriver19_t *ctx );

/**
 * @brief LED Driver 19 enables channels function.
 * @details This function is used to enable channel output.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @param[in] channels_en : Channels that will be enabled.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver19_enable_channels ( leddriver19_t *ctx, uint16_t channels_en );

/**
 * @brief LED Driver 19 disable channels function.
 * @details This function is used to disable channel output.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @param[in] channels_en : Channels that will be disabled.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver19_disable_channels ( leddriver19_t *ctx, uint16_t channels_dis );


/**
 * @brief LED Driver 19 set pattern PWM value function.
 * @details This function is used to set PWM values of the selected pattern and channel.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @param[in] pattern_sel : Pattern selection.
 * @param[in] channel_sel : Channel selection.
 * @param[in] pwm_value : PWM signal strength.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver19_set_pattern_pwm ( leddriver19_t *ctx, uint8_t pattern_sel, uint8_t channel_sel, 
                                    float pwm_value );

/**
 * @brief LED Driver 19 get channel current value function.
 * @details This function is used to get the current value of the selected channel.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @param[in] channel_sel : Channel selection.
 * @param[out] current_val : Current value in mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver19_get_ch_current ( leddriver19_t *ctx, uint8_t channel_sel, float *current_val );

/**
 * @brief LED Driver 19 set channel current value function.
 * @details This function is used to set the current value of the selected channel.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @param[in] channel_sel : Channel selection.
 * @param[in] current_val : Current value in mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver19_set_ch_current ( leddriver19_t *ctx, uint8_t channel_sel, float current_val );

/**
 * @brief LED Driver 19 get interrupt register data function.
 * @details This function is used to get interrupt flags data from the interrupt register.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @param[out] int_data : Interrupt register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver19_get_int_data ( leddriver19_t *ctx, uint8_t *int_data );

/**
 * @brief LED Driver 19 get LED open ( NC channels ) data function.
 * @details This function is used to check if all enabled channels are connected.
 * @param[in] ctx : Click context object.
 * See #leddriver19_t object definition for detailed explanation.
 * @param[out] led_data : Open LED channels data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver19_get_nc_led ( leddriver19_t *ctx, uint16_t *led_data );

#ifdef __cplusplus
}
#endif
#endif // LEDDRIVER19_H

/*! @} */ // leddriver19

// ------------------------------------------------------------------------ END
