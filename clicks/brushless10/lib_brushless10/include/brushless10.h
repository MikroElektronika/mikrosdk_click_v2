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
 * @file brushless10.h
 * @brief This file contains API for Brushless 10 Click Driver.
 */

#ifndef BRUSHLESS10_H
#define BRUSHLESS10_H

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
#include "drv_pwm.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup brushless10 Brushless 10 Click Driver
 * @brief API for configuring and manipulating Brushless 10 Click driver.
 * @{
 */

/**
 * @defgroup brushless10_reg Brushless 10 Registers List
 * @brief List of registers of Brushless 10 Click driver.
 */

/**
 * @addtogroup brushless10_reg
 * @{
 */

/**
 * @brief Brushless 10 DAC register list.
 * @details Specified DAC register list of Brushless 10 Click driver.
 */
#define BRUSHLESS10_DAC_REG_DEVICE_CONFIG           0x01
#define BRUSHLESS10_DAC_REG_STATUS_TRIGGER          0x02
#define BRUSHLESS10_DAC_REG_BRDCAST                 0x03
#define BRUSHLESS10_DAC_REG_DACA_DATA_LA            0x08
#define BRUSHLESS10_DAC_REG_DACB_DATA_MIN_SP        0x09
#define BRUSHLESS10_DAC_REG_DACC_DATA_SEL_LD        0x0A
#define BRUSHLESS10_DAC_REG_DACD_DATA_FPWM          0x0B
#define BRUSHLESS10_DAC_REG_DACE_DATA_SEL_LA        0x0C
#define BRUSHLESS10_DAC_REG_DACF_DATA_SEL_FG        0x0D
#define BRUSHLESS10_DAC_REG_DACG_DATA_SEL_SP        0x0E
#define BRUSHLESS10_DAC_REG_DACH_DATA_CW_CCW        0x0F

/*! @} */ // brushless10_reg

/**
 * @defgroup brushless10_set Brushless 10 Registers Settings
 * @brief Settings for registers of Brushless 10 Click driver.
 */

/**
 * @addtogroup brushless10_set
 * @{
 */

/**
 * @brief Brushless 10 DAC channel setting.
 * @details Specified setting for DAC channel of Brushless 10 Click driver.
 */
#define BRUSHLESS10_DAC_CHA_LA                      0
#define BRUSHLESS10_DAC_CHB_MIN_SP                  1
#define BRUSHLESS10_DAC_CHC_SEL_LD                  2
#define BRUSHLESS10_DAC_CHD_FPWM                    3
#define BRUSHLESS10_DAC_CHE_SEL_LA                  4
#define BRUSHLESS10_DAC_CHF_SEL_FG                  5
#define BRUSHLESS10_DAC_CHG_SEL_SP                  6
#define BRUSHLESS10_DAC_CHH_CW_CCW                  7

/**
 * @brief Brushless 10 lead angle steps, LA channel setting.
 * @details Specified setting for lead angle steps, LA channel of Brushless 10 Click driver.
 */
#define BRUSHLESS10_LA0_STEP_0                      88
#define BRUSHLESS10_LA0_STEP_1                      234
#define BRUSHLESS10_LA0_STEP_2                      332
#define BRUSHLESS10_LA0_STEP_3                      430
#define BRUSHLESS10_LA0_STEP_4                      527
#define BRUSHLESS10_LA0_STEP_5                      625
#define BRUSHLESS10_LA0_STEP_6                      723
#define BRUSHLESS10_LA0_STEP_7                      820
#define BRUSHLESS10_LA0_STEP_8                      918
#define BRUSHLESS10_LA0_STEP_9                      1016
#define BRUSHLESS10_LA0_STEP_10                     1113
#define BRUSHLESS10_LA0_STEP_11                     1211
#define BRUSHLESS10_LA0_STEP_12                     1309
#define BRUSHLESS10_LA0_STEP_13                     1406
#define BRUSHLESS10_LA0_STEP_14                     1504
#define BRUSHLESS10_LA0_STEP_15                     1602
#define BRUSHLESS10_LA0_STEP_16                     1699
#define BRUSHLESS10_LA0_STEP_17                     1797
#define BRUSHLESS10_LA0_STEP_18                     1894
#define BRUSHLESS10_LA0_STEP_19                     1992
#define BRUSHLESS10_LA0_STEP_20                     2090
#define BRUSHLESS10_LA0_STEP_21                     2187
#define BRUSHLESS10_LA0_STEP_22                     2285
#define BRUSHLESS10_LA0_STEP_23                     2383
#define BRUSHLESS10_LA0_STEP_24                     2480
#define BRUSHLESS10_LA0_STEP_25                     2578
#define BRUSHLESS10_LA0_STEP_26                     2676
#define BRUSHLESS10_LA0_STEP_27                     2773
#define BRUSHLESS10_LA0_STEP_28                     2871
#define BRUSHLESS10_LA0_STEP_29                     2969
#define BRUSHLESS10_LA0_STEP_30                     3066
#define BRUSHLESS10_LA0_STEP_31                     4062
#define BRUSHLESS10_LA1_STEP_0                      234
#define BRUSHLESS10_LA1_STEP_1                      673
#define BRUSHLESS10_LA1_STEP_2                      1064
#define BRUSHLESS10_LA1_STEP_3                      1455
#define BRUSHLESS10_LA1_STEP_4                      1845
#define BRUSHLESS10_LA1_STEP_5                      2236
#define BRUSHLESS10_LA1_STEP_6                      2627
#define BRUSHLESS10_LA1_STEP_7                      3916

/**
 * @brief Brushless 10 minimum output duty steps, MIN_SP channel setting.
 * @details Specified setting for minimum output duty steps, MIN_SP channel of Brushless 10 Click driver.
 */
#define BRUSHLESS10_MIN_SP_STEP_0                   136
#define BRUSHLESS10_MIN_SP_STEP_1                   478
#define BRUSHLESS10_MIN_SP_STEP_2                   869
#define BRUSHLESS10_MIN_SP_STEP_3                   1259
#define BRUSHLESS10_MIN_SP_STEP_4                   1650
#define BRUSHLESS10_MIN_SP_STEP_5                   2041
#define BRUSHLESS10_MIN_SP_STEP_6                   2431
#define BRUSHLESS10_MIN_SP_STEP_7                   2822
#define BRUSHLESS10_MIN_SP_STEP_8                   3916

/**
 * @brief Brushless 10 FPWM channel setting.
 * @details Specified setting for FPWM channel of Brushless 10 Click driver.
 */
#define BRUSHLESS10_FPWM_STEP_0                     478
#define BRUSHLESS10_FPWM_STEP_1                     1455
#define BRUSHLESS10_FPWM_STEP_2                     2431
#define BRUSHLESS10_FPWM_STEP_3                     3965

/**
 * @brief Brushless 10 SEL_LD channel setting.
 * @details Specified setting for SEL_LD channel of Brushless 10 Click driver.
 */
#define BRUSHLESS10_SEL_LD_STEP_0                   478
#define BRUSHLESS10_SEL_LD_STEP_1                   1455
#define BRUSHLESS10_SEL_LD_STEP_2                   2431
#define BRUSHLESS10_SEL_LD_STEP_3                   3965

/**
 * @brief Brushless 10 SEL_FG channel setting.
 * @details Specified setting for SEL_FG channel of Brushless 10 Click driver.
 */
#define BRUSHLESS10_SEL_FG_STEP_0                   967
#define BRUSHLESS10_SEL_FG_STEP_1                   3476

/**
 * @brief Brushless 10 SEL_SP channel setting.
 * @details Specified setting for SEL_SP channel of Brushless 10 Click driver.
 */
#define BRUSHLESS10_SEL_SP_STEP_0                   478
#define BRUSHLESS10_SEL_SP_STEP_1                   1943
#define BRUSHLESS10_SEL_SP_STEP_2                   3965

/**
 * @brief Brushless 10 SEL_LA channel setting.
 * @details Specified setting for SEL_LA channel of Brushless 10 Click driver.
 */
#define BRUSHLESS10_SEL_LA_STEP_0                   478
#define BRUSHLESS10_SEL_LA_STEP_1                   1943
#define BRUSHLESS10_SEL_LA_STEP_2                   3965

/**
 * @brief Brushless 10 CW_CCW channel setting.
 * @details Specified setting for CW_CCW channel of Brushless 10 Click driver.
 */
#define BRUSHLESS10_CW_CCW_0                        0
#define BRUSHLESS10_CW_CCW_1                        5000

/**
 * @brief Brushless 10 DAC vout setting.
 * @details Specified setting for DAC vout of Brushless 10 Click driver.
 */
#define BRUSHLESS10_DAC_VREF                        5000
#define BRUSHLESS10_DAC_RESOLUTION                  256
#define BRUSHLESS10_DAC_ROUND_TO_INT                0.5f

/**
 * @brief Brushless 10 DAC DEVICE_CONFIG register setting.
 * @details Specified setting for DAC DEVICE_CONFIG register of Brushless 10 Click driver.
 */
#define BRUSHLESS10_DAC_CONFIG_PDN_ALL              0x0100
#define BRUSHLESS10_DAC_CONFIG_PDN_CHA              0x0001
#define BRUSHLESS10_DAC_CONFIG_PDN_CHB              0x0002
#define BRUSHLESS10_DAC_CONFIG_PDN_CHC              0x0004
#define BRUSHLESS10_DAC_CONFIG_PDN_CHD              0x0008
#define BRUSHLESS10_DAC_CONFIG_PDN_CHE              0x0010
#define BRUSHLESS10_DAC_CONFIG_PDN_CHF              0x0020
#define BRUSHLESS10_DAC_CONFIG_PDN_CHG              0x0040
#define BRUSHLESS10_DAC_CONFIG_PDN_CHH              0x0080
#define BRUSHLESS10_DAC_CONFIG_ENABLE_ALL_CH        0x0000

/**
 * @brief Brushless 10 DAC STATUS/TRIGGER register setting.
 * @details Specified setting for DAC STATUS/TRIGGER register of Brushless 10 Click driver.
 */
#define BRUSHLESS10_DAC_DEVICE_ID                   0x0500
#define BRUSHLESS10_DAC_DEVICE_ID_MASK              0x0FC0
#define BRUSHLESS10_DAC_SW_RESET                    0x000A

/**
 * @brief Brushless 10 default PWM frequency.
 * @details Specified setting for default PWM frequency of Brushless 10 Click driver.
 */
#define BRUSHLESS10_DEF_FREQ                        50000

/**
 * @brief Brushless 10 device address setting.
 * @details Specified setting for device slave address selection of
 * Brushless 10 Click driver.
 */
#define BRUSHLESS10_DAC_DEVICE_ADDRESS_BROADCAST    0x47
#define BRUSHLESS10_DAC_DEVICE_ADDRESS_0            0x48
#define BRUSHLESS10_DAC_DEVICE_ADDRESS_1            0x49

/*! @} */ // brushless10_set

/**
 * @defgroup brushless10_map Brushless 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 10 Click driver.
 */

/**
 * @addtogroup brushless10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 10 Click to the selected MikroBUS.
 */
#define BRUSHLESS10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fg_out = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.brake = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ld_out = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // brushless10_map
/*! @} */ // brushless10

/**
 * @brief Brushless 10 Click context object.
 * @details Context object definition of Brushless 10 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t brake;    /**< Brake control (active high). */

    // Input pins
    digital_in_t fg_out;    /**< Rotation frequency output signal. */
    digital_in_t ld_out;    /**< Lock detection output signal. */

    // Modules
    pwm_t pwm;              /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;      /**< PWM frequency value. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} brushless10_t;

/**
 * @brief Brushless 10 Click configuration object.
 * @details Configuration object definition of Brushless 10 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t pwm;         /**< PWM pin. */

    // Additional gpio pins
    pin_name_t fg_out;      /**< Rotation frequency output signal. */
    pin_name_t brake;       /**< Brake control (active high). */
    pin_name_t ld_out;      /**< Lock detection output signal. */

    // Static variable
    uint32_t dev_pwm_freq;  /**< PWM frequency value. */
    uint32_t i2c_speed;     /**< I2C serial speed. */
    uint8_t  i2c_address;   /**< I2C slave address. */

} brushless10_cfg_t;

/**
 * @brief Brushless 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS10_OK = 0,
    BRUSHLESS10_ERROR = -1

} brushless10_return_value_t;

/*!
 * @addtogroup brushless10 Brushless 10 Click Driver
 * @brief API for configuring and manipulating Brushless 10 Click driver.
 * @{
 */

/**
 * @brief Brushless 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless10_cfg_setup ( brushless10_cfg_t *cfg );

/**
 * @brief Brushless 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless10_init ( brushless10_t *ctx, brushless10_cfg_t *cfg );

/**
 * @brief Brushless 10 default configuration function.
 * @details This function executes a default configuration of Brushless 10
 * click board.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless10_default_cfg ( brushless10_t *ctx );

/**
 * @brief Brushless 10 DAC write function.
 * @details This function writes a data word to the selected DAC register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @param[in] reg : DAC register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless10_dac_write ( brushless10_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Brushless 10 DAC read function.
 * @details This function reads a data word from the selected DAC register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @param[in] reg : DAC register address.
 * @param[out] data_out : 16-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless10_dac_read ( brushless10_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Brushless 10 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless10_set_duty_cycle ( brushless10_t *ctx, float duty_cycle );

/**
 * @brief Brushless 10 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless10_pwm_stop ( brushless10_t *ctx );

/**
 * @brief Brushless 10 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless10_pwm_start ( brushless10_t *ctx );

/**
 * @brief Brushless 10 get fg out pin function.
 * @details This function returns the FG_OUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t brushless10_get_fg_out_pin ( brushless10_t *ctx );

/**
 * @brief Brushless 10 get ld out pin function.
 * @details This function returns the LD_OUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t brushless10_get_ld_out_pin ( brushless10_t *ctx );

/**
 * @brief Brushless 10 pull brake function.
 * @details This function pulls brake by setting the BRAKE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless10_pull_brake ( brushless10_t *ctx );

/**
 * @brief Brushless 10 release brake function.
 * @details This function releases brake by setting the BRAKE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless10_release_brake ( brushless10_t *ctx );

/**
 * @brief Brushless 10 DAC check com function.
 * @details This function checks the communication with a DAC by reading and verifying the DAC device ID.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless10_dac_check_com ( brushless10_t *ctx );

/**
 * @brief Brushless 10 DAC sw reset function.
 * @details This function performs the DAC software reset.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless10_dac_sw_reset ( brushless10_t *ctx );

/**
 * @brief Brushless 10 DAC set data function.
 * @details This function writes the raw data value to the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @param[in] channel : DAC channel.
 *                      @li @c 0 - LA,
 *                      @li @c 1 - MIN_SP,
 *                      @li @c 2 - SEL_LD,
 *                      @li @c 3 - FPWM,
 *                      @li @c 4 - SEL_LA,
 *                      @li @c 5 - SEL_FG,
 *                      @li @c 6 - SEL_SP,
 *                      @li @c 7 - CW_CCW.
 * @param[in] data_in : 8-bit RAW DAC data to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The channels 4-7 are disconnected by default on the click board. Refer to the click board schematic.
 */
err_t brushless10_dac_set_data ( brushless10_t *ctx, uint8_t channel, uint8_t data_in );

/**
 * @brief Brushless 10 DAC set vout function.
 * @details This function sets the voltage output at the selected DAC channel.
 * @param[in] ctx : Click context object.
 * See #brushless10_t object definition for detailed explanation.
 * @param[in] channel : DAC channel.
 *                      @li @c 0 - LA,
 *                      @li @c 1 - MIN_SP,
 *                      @li @c 2 - SEL_LD,
 *                      @li @c 3 - FPWM,
 *                      @li @c 4 - SEL_LA,
 *                      @li @c 5 - SEL_FG,
 *                      @li @c 6 - SEL_SP,
 *                      @li @c 7 - CW_CCW.
 * @param[in] vout_mv : Voltage output in millivolts to be set [0-5000mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The channels 4-7 are disconnected by default on the click board. Refer to the click board schematic.
 */
err_t brushless10_dac_set_vout ( brushless10_t *ctx, uint8_t channel, uint16_t vout_mv );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS10_H

/*! @} */ // brushless10

// ------------------------------------------------------------------------ END
