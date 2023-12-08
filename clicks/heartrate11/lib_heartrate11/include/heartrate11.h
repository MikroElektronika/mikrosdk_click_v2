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
 * @file heartrate11.h
 * @brief This file contains API for Heart Rate 11 Click Driver.
 */

#ifndef HEARTRATE11_H
#define HEARTRATE11_H

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
 * @addtogroup heartrate11 Heart Rate 11 Click Driver
 * @brief API for configuring and manipulating Heart Rate 11 Click driver.
 * @{
 */

/**
 * @defgroup heartrate11_reg Heart Rate 11 Registers List
 * @brief List of registers of Heart Rate 11 Click driver.
 */

/**
 * @addtogroup heartrate11_reg
 * @{
 */

/**
 * @brief Heart Rate 11 register map.
 * @details Specified register map of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_REG_STATUS_0                    0x00
#define HEARTRATE11_REG_STATUS_1                    0x01
#define HEARTRATE11_REG_PS_DATA_0                   0x02
#define HEARTRATE11_REG_PS_DATA_1                   0x03
#define HEARTRATE11_REG_LS_CLEAR_DATA_0             0x04
#define HEARTRATE11_REG_LS_CLEAR_DATA_1             0x05
#define HEARTRATE11_REG_LS_CLEAR_DATA_2             0x06
#define HEARTRATE11_REG_LS_GREEN_DATA_0             0x07
#define HEARTRATE11_REG_LS_GREEN_DATA_1             0x08
#define HEARTRATE11_REG_LS_GREEN_DATA_2             0x09
#define HEARTRATE11_REG_LS_BLUE_DATA_0              0x0A
#define HEARTRATE11_REG_LS_BLUE_DATA_1              0x0B
#define HEARTRATE11_REG_LS_BLUE_DATA_2              0x0C
#define HEARTRATE11_REG_LS_RED_DATA_0               0x0D
#define HEARTRATE11_REG_LS_RED_DATA_1               0x0E
#define HEARTRATE11_REG_LS_RED_DATA_2               0x0F
#define HEARTRATE11_REG_COMP_DATA_0                 0x10
#define HEARTRATE11_REG_COMP_DATA_1                 0x11
#define HEARTRATE11_REG_COMP_DATA_2                 0x12
#define HEARTRATE11_REG_MAIN_CTRL_0                 0x15
#define HEARTRATE11_REG_MAIN_CTRL_1                 0x16
#define HEARTRATE11_REG_PS_LED_CURR_0               0x17
#define HEARTRATE11_REG_PS_LED_CURR_1               0x18
#define HEARTRATE11_REG_PS_CAN_PULSES               0x19
#define HEARTRATE11_REG_PS_PWIDTH_PERIOD            0x1A
#define HEARTRATE11_REG_PS_CAN_DIG_0                0x1B
#define HEARTRATE11_REG_PS_CAN_DIG_1                0x1C
#define HEARTRATE11_REG_PS_MOV_AVG_HYS              0x1D
#define HEARTRATE11_REG_PS_THRES_UP_0               0x1E
#define HEARTRATE11_REG_PS_THRES_UP_1               0x1F
#define HEARTRATE11_REG_PS_THRES_LOW_0              0x20
#define HEARTRATE11_REG_PS_THRES_LOW_1              0x21
#define HEARTRATE11_REG_LS_RES_PERIOD               0x22
#define HEARTRATE11_REG_LS_GAIN                     0x23
#define HEARTRATE11_REG_LS_THRES_UP_0               0x24
#define HEARTRATE11_REG_LS_THRES_UP_1               0x25
#define HEARTRATE11_REG_LS_THRES_UP_2               0x26
#define HEARTRATE11_REG_LS_THRES_LOW_0              0x27
#define HEARTRATE11_REG_LS_THRES_LOW_1              0x28
#define HEARTRATE11_REG_LS_THRES_LOW_2              0x29
#define HEARTRATE11_REG_LS_THRES_VAR                0x2A
#define HEARTRATE11_REG_INT_CFG_0                   0x2B
#define HEARTRATE11_REG_INT_CFG_1                   0x2C
#define HEARTRATE11_REG_INT_PST                     0x2D
#define HEARTRATE11_REG_PPG_PS_GAIN                 0x2E
#define HEARTRATE11_REG_PPG_PS_CFG                  0x2F
#define HEARTRATE11_REG_PPG_IRLED_CURR_0            0x30
#define HEARTRATE11_REG_PPG_IRLED_CURR_1            0x31
#define HEARTRATE11_REG_PPG_RLED_CURR_0             0x32
#define HEARTRATE11_REG_PPG_RLED_CURR_1             0x33
#define HEARTRATE11_REG_PPG_CAN_ANA                 0x34
#define HEARTRATE11_REG_PPG_AVG                     0x35
#define HEARTRATE11_REG_PPG_PWIDTH_PERIOD           0x36
#define HEARTRATE11_REG_FIFO_CFG                    0x37
#define HEARTRATE11_REG_FIFO_WR_PTR                 0x38
#define HEARTRATE11_REG_FIFO_RD_PTR                 0x39
#define HEARTRATE11_REG_FIFO_OVF_CNT                0x3A
#define HEARTRATE11_REG_FIFO_DATA                   0x3B
#define HEARTRATE11_REG_PART_ID                     0x3D

/*! @} */ // heartrate11_reg

/**
 * @defgroup heartrate11_set Heart Rate 11 Registers Settings
 * @brief Settings for registers of Heart Rate 11 Click driver.
 */

/**
 * @addtogroup heartrate11_set
 * @{
 */

/**
 * @brief Heart Rate 11 STATUS_0 register settings.
 * @details Specified STATUS_0 register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_POR_STATUS                      0x80
#define HEARTRATE11_LS_INT_STATUS                   0x02
#define HEARTRATE11_LS_NEW_DATA                     0x01

/**
 * @brief Heart Rate 11 STATUS_1 register settings.
 * @details Specified STATUS_1 register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_TS_DATA_STATUS                  0x80
#define HEARTRATE11_FIFO_AFULL_STATUS               0x20
#define HEARTRATE11_PPG_DATA_STATUS                 0x10
#define HEARTRATE11_PS_LOGIC_STATUS                 0x04
#define HEARTRATE11_PS_INT_STATUS                   0x02
#define HEARTRATE11_PS_NEW_DATA                     0x01

/**
 * @brief Heart Rate 11 MAIN_CTRL_0 register settings.
 * @details Specified MAIN_CTRL_0 register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_SW_RESET                        0x80
#define HEARTRATE11_LS_SAI_ON                       0x08
#define HEARTRATE11_LS_SAI_OFF                      0x00
#define HEARTRATE11_ALS_MODE                        0x00
#define HEARTRATE11_RGB_MODE                        0x02
#define HEARTRATE11_LS_OFF                          0x00
#define HEARTRATE11_LS_ON                           0x01

/**
 * @brief Heart Rate 11 MAIN_CTRL_1 register settings.
 * @details Specified MAIN_CTRL_1 register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_PS_SAI_ON                       0x08
#define HEARTRATE11_PS_SAI_OFF                      0x00
#define HEARTRATE11_PS_MODE                         0x00
#define HEARTRATE11_HR_MODE                         0x02
#define HEARTRATE11_SPO2_MODE                       0x04
#define HEARTRATE11_PPG_PS_ON                       0x01
#define HEARTRATE11_PPG_PS_OFF                      0x00

/**
 * @brief Heart Rate 11 led current settings.
 * @details Specified led current of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_PS_LED                          0
#define HEARTRATE11_IR_LED                          1
#define HEARTRATE11_RED_LED                         2
#define HEARTRATE11_IR_LED_DEFAULT_CURRENT          50.0
#define HEARTRATE11_PS_IR_LED_MAX_CURRENT           250.0
#define HEARTRATE11_RED_LED_MAX_CURRENT             125.0
#define HEARTRATE11_PS_IR_LED_CURRENT_RES           0x03FF
#define HEARTRATE11_RED_LED_CURRENT_RES             0x01FF
#define HEARTRATE11_ROUND_TO_NEAREST_INT            0.5

/**
 * @brief Heart Rate 11 PS_CAN_PULSES register settings.
 * @details Specified PS_CAN_PULSES register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_PS_CAN_ANA_OFF                  0x00
#define HEARTRATE11_PS_CAN_ANA_ON                   0x40
#define HEARTRATE11_PS_PULSES( x )                  ( ( x ) & ( 0x07 ) ) << 3 ) // Where x = 0..5 and num pulses = 2^x
#define HEARTRATE11_PS_CAN_PULSES_RESERVED          0x02

/**
 * @brief Heart Rate 11 PS_PWIDTH_RATE register settings.
 * @details Specified PS_PWIDTH_RATE register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_PS_PWIDTH_26US                  0x00
#define HEARTRATE11_PS_PWIDTH_42US                  0x10
#define HEARTRATE11_PS_PWIDTH_71US                  0x20
#define HEARTRATE11_PS_RATE_3p125MS                 0x00
#define HEARTRATE11_PS_RATE_6p25MS                  0x01
#define HEARTRATE11_PS_RATE_12p5MS                  0x02
#define HEARTRATE11_PS_RATE_25MS                    0x03
#define HEARTRATE11_PS_RATE_50MS                    0x04
#define HEARTRATE11_PS_RATE_100MS                   0x05
#define HEARTRATE11_PS_RATE_200MS                   0x06
#define HEARTRATE11_PS_RATE_400MS                   0x07

/**
 * @brief Heart Rate 11 PS_MOV_AVG_HYS register settings.
 * @details Specified PS_MOV_AVG_HYS register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_PS_MOV_AVG_ON                   0x80
#define HEARTRATE11_PS_MOV_AVG_OFF                  0x00
#define HEARTRATE11_PS_HYS_LEVEL( x )               ( x >> 1 )  // Where x = 0..254

/**
 * @brief Heart Rate 11 LS_RES_RATE register settings.
 * @details Specified LS_RES_RATE register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_LS_RES_20BIT_400MS              0x00
#define HEARTRATE11_LS_RES_19BIT_200MS              0x10
#define HEARTRATE11_LS_RES_18BIT_100MS              0x20
#define HEARTRATE11_LS_RES_17BIT_50MS               0x30
#define HEARTRATE11_LS_RES_16BIT_25MS               0x40
#define HEARTRATE11_LS_RES_13BIT_3p125MS            0x50
#define HEARTRATE11_LS_RATE_25MS                    0x00
#define HEARTRATE11_LS_RATE_50MS                    0x01
#define HEARTRATE11_LS_RATE_100MS                   0x02
#define HEARTRATE11_LS_RATE_200MS                   0x03
#define HEARTRATE11_LS_RATE_500MS                   0x04
#define HEARTRATE11_LS_RATE_1000MS                  0x05
#define HEARTRATE11_LS_RATE_2000MS                  0x06

/**
 * @brief Heart Rate 11 LS_GAIN register settings.
 * @details Specified LS_GAIN register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_LS_GAIN_1                       0x00
#define HEARTRATE11_LS_GAIN_3                       0x01
#define HEARTRATE11_LS_GAIN_6                       0x02

/**
 * @brief Heart Rate 11 INT_CFG_0 register settings.
 * @details Specified INT_CFG_0 register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_LS_INT_SEL_C                    0x00
#define HEARTRATE11_LS_INT_SEL_G                    0x10
#define HEARTRATE11_LS_INT_SEL_R                    0x20
#define HEARTRATE11_LS_INT_SEL_B                    0x30
#define HEARTRATE11_LS_THRES_INT_MODE               0x00
#define HEARTRATE11_LS_VAR_INT_MODE                 0x02
#define HEARTRATE11_LS_INT_OFF                      0x00
#define HEARTRATE11_LS_INT_ON                       0x01

/**
 * @brief Heart Rate 11 INT_CFG_1 register settings.
 * @details Specified INT_CFG_1 register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_AFULL_INT_OFF                   0x00
#define HEARTRATE11_AFULL_INT_ON                    0x20
#define HEARTRATE11_PPG_INT_OFF                     0x00
#define HEARTRATE11_PPG_INT_ON                      0x10
#define HEARTRATE11_PS_INT_LOGIC                    0x02
#define HEARTRATE11_PS_INT_OFF                      0x00
#define HEARTRATE11_PS_INT_ON                       0x01

/**
 * @brief Heart Rate 11 INT_PST register settings.
 * @details Specified INT_PST register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_LS_PERSIST( x )                 ( ( x & 0x0F ) << 4 )
#define HEARTRATE11_PS_PERSIST( x )                 ( x & 0x0F)

/**
 * @brief Heart Rate 11 PPG_PS_GAIN register settings.
 * @details Specified PPG_PS_GAIN register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_PPG_PS_GAIN_1                   0x00
#define HEARTRATE11_PPG_PS_GAIN_1p5                 0x10
#define HEARTRATE11_PPG_PS_GAIN_2                   0x20
#define HEARTRATE11_PPG_PS_GAIN_4                   0x30
#define HEARTRATE11_PPG_PS_GAIN_RESERVED            0x09

/**
 * @brief Heart Rate 11 PPG_PS_CFG register settings.
 * @details Specified PPG_PS_CFG register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_PPG_POW_SAVE_OFF                0x00
#define HEARTRATE11_PPG_POW_SAVE_ON                 0x40
#define HEARTRATE11_LED_FLIP_OFF                    0x00
#define HEARTRATE11_LED_FLIP_ON                     0x08

/**
 * @brief Heart Rate 11 PPG_CAN_ANA register settings.
 * @details Specified PPG_CAN_ANA register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_PPG_CH1_CAN_ANA_OFF             0x00
#define HEARTRATE11_PPG_CH1_CAN_ANA_ON              0x04
#define HEARTRATE11_PPG_CH2_CAN_ANA_OFF             0x00
#define HEARTRATE11_PPG_CH2_CAN_ANA_ON              0x04

/**
 * @brief Heart Rate 11 PPG_AVG register settings.
 * @details Specified PPG_AVG register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_PPG_AVG_1                       0x00
#define HEARTRATE11_PPG_AVG_2                       0x10
#define HEARTRATE11_PPG_AVG_4                       0x20
#define HEARTRATE11_PPG_AVG_8                       0x30
#define HEARTRATE11_PPG_AVG_16                      0x40
#define HEARTRATE11_PPG_AVG_32                      0x50
#define HEARTRATE11_PPG_AVG_RESERVED                0x0A

/**
 * @brief Heart Rate 11 PPG_PWIDTH_RATE register settings.
 * @details Specified PPG_PWIDTH_RATE register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_PPG_PWIDTH_130US                0x30
#define HEARTRATE11_PPG_PWIDTH_247US                0x40
#define HEARTRATE11_PPG_PWIDTH_481US                0x50
#define HEARTRATE11_PPG_PWIDTH_949US                0x60
#define HEARTRATE11_PPG_RATE_0p3125MS               0x00
#define HEARTRATE11_PPG_RATE_0p625MS                0x01
#define HEARTRATE11_PPG_RATE_1MS                    0x02
#define HEARTRATE11_PPG_RATE_1p25MS                 0x03
#define HEARTRATE11_PPG_RATE_2p5MS                  0x04
#define HEARTRATE11_PPG_RATE_5MS                    0x05
#define HEARTRATE11_PPG_RATE_10MS                   0x06
#define HEARTRATE11_PPG_RATE_20MS                   0x07

/**
 * @brief Heart Rate 11 FIFO_CFG register settings.
 * @details Specified FIFO_CFG register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_FIFO_ROLL_OFF                   0x00
#define HEARTRATE11_FIFO_ROLL_ON                    0x10
#define HEARTRATE11_FIFO_AFULL_WARNING( x )         ( x & 0x0F )

/**
 * @brief Heart Rate 11 FIFO_WR_PTR register settings.
 * @details Specified FIFO_WR_PTR register settings of Heart Rate 11 Click driver.
 */
#define HEARTRATE11_FIFO_INDEX( x )                 ( x & 0x1F )

/**
 * @brief Heart Rate 11 device address setting.
 * @details Specified setting for device slave address selection of
 * Heart Rate 11 Click driver.
 */
#define HEARTRATE11_DEVICE_ADDRESS                  0x53

/*! @} */ // heartrate11_set

/**
 * @defgroup heartrate11_map Heart Rate 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Heart Rate 11 Click driver.
 */

/**
 * @addtogroup heartrate11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Heart Rate 11 Click to the selected MikroBUS.
 */
#define HEARTRATE11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // heartrate11_map
/*! @} */ // heartrate11

/**
 * @brief Heart Rate 11 Click context object.
 * @details Context object definition of Heart Rate 11 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;           /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} heartrate11_t;

/**
 * @brief Heart Rate 11 Click configuration object.
 * @details Configuration object definition of Heart Rate 11 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;            /**< Interrupt pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} heartrate11_cfg_t;

/**
 * @brief Heart Rate 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HEARTRATE11_OK = 0,
    HEARTRATE11_ERROR = -1

} heartrate11_return_value_t;

/*!
 * @addtogroup heartrate11 Heart Rate 11 Click Driver
 * @brief API for configuring and manipulating Heart Rate 11 Click driver.
 * @{
 */

/**
 * @brief Heart Rate 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #heartrate11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void heartrate11_cfg_setup ( heartrate11_cfg_t *cfg );

/**
 * @brief Heart Rate 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #heartrate11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #heartrate11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate11_init ( heartrate11_t *ctx, heartrate11_cfg_t *cfg );

/**
 * @brief Heart Rate 11 default configuration function.
 * @details This function executes a default configuration of Heart Rate 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #heartrate11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t heartrate11_default_cfg ( heartrate11_t *ctx );

/**
 * @brief Heart Rate 11 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #heartrate11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate11_generic_write ( heartrate11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Heart Rate 11 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #heartrate11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate11_generic_read ( heartrate11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Heart Rate 11 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #heartrate11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate11_write_register ( heartrate11_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Heart Rate 11 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #heartrate11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate11_read_register ( heartrate11_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Heart Rate 11 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #heartrate11_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
uint8_t heartrate11_get_int_pin ( heartrate11_t *ctx );

/**
 * @brief Heart Rate 11 reset device function.
 * @details This function performs the device software reset by setting the SW_RESET bit.
 * @param[in] ctx : Click context object.
 * See #heartrate11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate11_reset_device ( heartrate11_t *ctx );

/**
 * @brief Heart Rate 11 set led current function.
 * @details This function sets the maximal current of the selected LED.
 * @param[in] ctx : Click context object.
 * See #heartrate11_t object definition for detailed explanation.
 * @param[in] led : LED selection @li @c 0 - PS LED,
 *                                @li @c 1 - IR LED,
 *                                @li @c 2 - RED LED.
 * @param[in] current : Maximal current - up to 250mA (125mA for RED LED),
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate11_set_led_current ( heartrate11_t *ctx, uint8_t led, float current );

/**
 * @brief Heart Rate 11 read fifo function.
 * @details This function reads a 24-bit data from the FIFO.
 * @param[in] ctx : Click context object.
 * See #heartrate11_t object definition for detailed explanation.
 * @param[out] fifo_data : 24-bit FIFO data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t heartrate11_read_fifo ( heartrate11_t *ctx, uint32_t *fifo_data );

#ifdef __cplusplus
}
#endif
#endif // HEARTRATE11_H

/*! @} */ // heartrate11

// ------------------------------------------------------------------------ END
