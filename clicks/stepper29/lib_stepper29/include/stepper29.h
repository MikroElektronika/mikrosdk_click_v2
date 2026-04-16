/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file stepper29.h
 * @brief This file contains API for Stepper 29 Click Driver.
 */

#ifndef STEPPER29_H
#define STEPPER29_H

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
#include "drv_i2c_master.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup stepper29 Stepper 29 Click Driver
 * @brief API for configuring and manipulating Stepper 29 Click driver.
 * @{
 */

/**
 * @defgroup stepper29_reg Stepper 29 Registers List
 * @brief List of registers of Stepper 29 Click driver.
 */

/**
 * @addtogroup stepper29_reg
 * @{
 */

/**
 * @brief Stepper 29 registers list.
 * @details Specified registers list of Stepper 29 Click driver.
 */
#define STEPPER29_REG_FAULT                     0x01
#define STEPPER29_REG_CTBLANK                   0x02
#define STEPPER29_REG_STBLANK                   0x03
#define STEPPER29_REG_FTBLANK                   0x04
#define STEPPER29_REG_MTBLANK                   0x05
#define STEPPER29_REG_VSP_MIN                   0x06
#define STEPPER29_REG_NF_HYS                    0x07
#define STEPPER29_REG_FREQ_MIN                  0x08
#define STEPPER29_REG_CALIB_WAIT                0x09
#define STEPPER29_REG_AGC_TIME                  0x0A
#define STEPPER29_REG_KI                        0x0B
#define STEPPER29_REG_KP                        0x0C
#define STEPPER29_REG_TARGET_ANGLE              0x0D
#define STEPPER29_REG_ERR_DELTA                 0x0E
#define STEPPER29_REG_KI_NANO                   0x0F
#define STEPPER29_REG_KP_NANO                   0x10
#define STEPPER29_REG_ODET_NANO                 0x11
#define STEPPER29_REG_WAIT_NANO                 0x12
#define STEPPER29_REG_AD_WAIT_NANO              0x13
#define STEPPER29_REG_BOOST_SEL                 0x14
#define STEPPER29_REG_RS                        0x15
#define STEPPER29_REG_TSD_AUTO                  0x16
#define STEPPER29_REG_ODET_MASK_M_DAC_SEL       0x17

/**
 * @brief Stepper 29 PCA9555A registers.
 * @details Specified PCA9555A registers of Stepper 29 Click driver.
 */
#define STEPPER29_EXP_REG_INPUT_0               0x00
#define STEPPER29_EXP_REG_INPUT_1               0x01
#define STEPPER29_EXP_REG_OUTPUT_0              0x02
#define STEPPER29_EXP_REG_OUTPUT_1              0x03
#define STEPPER29_EXP_REG_POLARITY_0            0x04
#define STEPPER29_EXP_REG_POLARITY_1            0x05
#define STEPPER29_EXP_REG_CONFIG_0              0x06
#define STEPPER29_EXP_REG_CONFIG_1              0x07

/*! @} */ // stepper29_reg

/**
 * @defgroup stepper29_set Stepper 29 Registers Settings
 * @brief Settings for registers of Stepper 29 Click driver.
 */

/**
 * @addtogroup stepper29_set
 * @{
 */

/**
 * @brief Stepper 29 PCA9555A pin mask.
 * @details Specified PCA9555A pin mask of Stepper 29 Click driver.
 */
#define STEPPER29_P0_DMODE2_PIN                 0x01
#define STEPPER29_P0_DMODE1_PIN                 0x02
#define STEPPER29_P0_DMODE0_PIN                 0x04
#define STEPPER29_P0_RST_PIN                    0x08
#define STEPPER29_P0_LO0_PIN                    0x40
#define STEPPER29_P0_LO1_PIN                    0x80
#define STEPPER29_P1_LO2_PIN                    0x01
#define STEPPER29_P1_MO_PIN                     0x02
#define STEPPER29_P1_SLEEP_PIN                  0x04
#define STEPPER29_P1_AWGS_PIN                   0x10
#define STEPPER29_P1_AGC_ON_PIN                 0x20
#define STEPPER29_P1_ADMD_PIN                   0x40
#define STEPPER29_P1_AGC_AUTO_PIN               0x80

/**
 * @brief Stepper 29 PCA9555A pin direction config.
 * @details Specified PCA9555A pin direction config of Stepper 29 Click driver.
 */
#define STEPPER29_P0_DEFAULT_CONFIG             0xF0
#define STEPPER29_P1_DEFAULT_CONFIG             0xF7

/**
 * @brief Stepper 29 direction setting.
 * @details Specified setting for direction of Stepper 29 Click driver.
 */
#define STEPPER29_DIR_CW                        1
#define STEPPER29_DIR_CCW                       0

/**
 * @brief Stepper 29 pin logic level setting.
 * @details Specified setting for pin logic level of Stepper 29 Click driver.
 */
#define STEPPER29_PIN_LOW_LEVEL                 0
#define STEPPER29_PIN_HIGH_LEVEL                1

/**
 * @brief Stepper 29 step resolution setting.
 * @details Specified setting for step resolution of Stepper 29 Click driver.
 */
#define STEPPER29_MODE_FULL_STEP                0x00
#define STEPPER29_MODE_HALF_STEP_TYPE_A         0x01
#define STEPPER29_MODE_HALF_STEP_TYPE_B         0x02
#define STEPPER29_MODE_QUARTER_STEP             0x03
#define STEPPER29_MODE_1_OVER_8                 0x04
#define STEPPER29_MODE_1_OVER_16                0x05
#define STEPPER29_MODE_1_OVER_32                0x06
#define STEPPER29_MODE_MASK                     0x07

/**
 * @brief Stepper 29 step function setting.
 * @details Specified setting for step function of Stepper 29 Click driver.
 */
#define STEPPER29_STEP_FUN_NORMAL_USTEP         0x00
#define STEPPER29_STEP_FUN_AWGS                 0x01
#define STEPPER29_STEP_FUN_NORMAL_USTEP_AGC     0x02
#define STEPPER29_STEP_FUN_CONTINUOUS_USTEP     0x03
#define STEPPER29_STEP_FUN_AUTO_DECAY_MODE      0x04
#define STEPPER29_STEP_FUN_AWGS_AUTO_DECAY_MODE 0x05
#define STEPPER29_STEP_FUN_AGC                  0x06
#define STEPPER29_STEP_FUN_AGC_AWGS             0x07
#define STEPPER29_STEP_FUN_AGC_INT_AUTO         0x0E
#define STEPPER29_STEP_FUN_AGC_AWGS_INT_AUTO    0x0F
#define STEPPER29_STEP_FUN_MASK                 0x0F

/**
 * @brief Stepper 29 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER29_SPEED_VERY_SLOW               0
#define STEPPER29_SPEED_SLOW                    1
#define STEPPER29_SPEED_MEDIUM                  2
#define STEPPER29_SPEED_FAST                    3
#define STEPPER29_SPEED_VERY_FAST               4

/**
 * @brief Stepper 29 output current calculation setting.
 * @details Specified setting for output current calculation of Stepper 29 Click driver.
 */
#define STEPPER29_VOLTAGE_TO_OUT_CURRENT        0.75

/**
 * @brief Stepper 29 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Stepper 29 Click driver.
 */
#define STEPPER29_NUM_CONVERSIONS               200

/**
 * @brief Stepper 29 ADC setting.
 * @details Specified settings for ADC of Stepper 29 Click driver.
 */
#define STEPPER29_VREF_3V3                      3.3
#define STEPPER29_VREF_5V                       5.0
#define STEPPER29_VREF_DEFAULT                  STEPPER29_VREF_3V3

/**
 * @brief Stepper 29 timeout setting.
 * @details Specified setting for timeout of Stepper 29 Click driver.
 */
#define STEPPER29_TIMEOUT_MS                    2000

/**
 * @brief Stepper 29 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 29 Click driver.
 */
#define STEPPER29_DEVICE_ADDRESS_A1A0_00        0x20
#define STEPPER29_DEVICE_ADDRESS_A1A0_01        0x21
#define STEPPER29_DEVICE_ADDRESS_A1A0_10        0x22
#define STEPPER29_DEVICE_ADDRESS_A1A0_11        0x23

/*! @} */ // stepper29_set

/**
 * @defgroup stepper29_map Stepper 29 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 29 Click driver.
 */

/**
 * @addtogroup stepper29_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 29 Click to the selected MikroBUS.
 */
#define STEPPER29_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.agc_out = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper29_map
/*! @} */ // stepper29

/**
 * @brief Stepper 29 Click context object.
 * @details Context object definition of Stepper 29 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t mosi;         /**< Serial device data input pin. */
    digital_out_t sck;          /**< Serial device clock input pin. */
    digital_out_t dir;          /**< Direction control pin (CW-high, CCW-low). */
    digital_out_t en;           /**< Enable output pin (active high). */
    digital_out_t clk;          /**< Clock signal pin. */

    // Input pins
    digital_in_t int_pin;       /**< PCA9555A interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */
    analog_in_t adc;            /**< ADC module object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} stepper29_t;

/**
 * @brief Stepper 29 Click configuration object.
 * @details Configuration object definition of Stepper 29 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t mosi;            /**< Serial device data input pin. */
    pin_name_t sck;             /**< Serial device clock input pin. */

    pin_name_t dir;             /**< Direction control pin (CW-high, CCW-low). */
    pin_name_t agc_out;         /**< AGC output pin for torque or position monitoring. */
    pin_name_t en;              /**< Enable output pin (active high). */
    pin_name_t clk;             /**< Clock signal pin. */
    pin_name_t int_pin;         /**< PCA9555A interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} stepper29_cfg_t;

/**
 * @brief Stepper 29 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER29_OK = 0,
    STEPPER29_ERROR = -1

} stepper29_return_value_t;

/*!
 * @addtogroup stepper29 Stepper 29 Click Driver
 * @brief API for configuring and manipulating Stepper 29 Click driver.
 * @{
 */

/**
 * @brief Stepper 29 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper29_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper29_cfg_setup ( stepper29_cfg_t *cfg );

/**
 * @brief Stepper 29 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper29_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_init ( stepper29_t *ctx, stepper29_cfg_t *cfg );

/**
 * @brief Stepper 29 default configuration function.
 * @details This function executes a default configuration of Stepper 29
 * Click board.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper29_default_cfg ( stepper29_t *ctx );

/**
 * @brief Stepper 29 write register function.
 * @details This function writes a desired data word to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_write_reg ( stepper29_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Stepper 29 write expander register function.
 * @details This function writes a desired data byte to the selected PCA9555A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_write_exp_reg ( stepper29_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 29 read expander register function.
 * @details This function reads data from the selected PCA9555A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_read_exp_reg ( stepper29_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 29 get step mode function.
 * @details This function reads the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[out] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_get_step_mode ( stepper29_t *ctx, uint8_t *mode );

/**
 * @brief Stepper 29 set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_set_step_mode ( stepper29_t *ctx, uint8_t mode );

/**
 * @brief Stepper 29 get step function function.
 * @details This function reads the step function settings.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[out] func : Step function mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_get_step_function ( stepper29_t *ctx, uint8_t *func );

/**
 * @brief Stepper 29 set step function function.
 * @details This function sets the step function settings.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] func : Step function mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_set_step_function ( stepper29_t *ctx, uint8_t func );

/**
 * @brief Stepper 29 get sleep pin function.
 * @details This function reads the sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_get_sleep_pin ( stepper29_t *ctx, uint8_t *state );

/**
 * @brief Stepper 29 set sleep pin function.
 * @details This function sets the sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_set_sleep_pin ( stepper29_t *ctx, uint8_t state );

/**
 * @brief Stepper 29 get LO0 pin function.
 * @details This function reads the LO0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_get_lo0_pin ( stepper29_t *ctx, uint8_t *state );

/**
 * @brief Stepper 29 get LO1 pin function.
 * @details This function reads the LO1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_get_lo1_pin ( stepper29_t *ctx, uint8_t *state );

/**
 * @brief Stepper 29 get LO2 pin function.
 * @details This function reads the LO2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_get_lo2_pin ( stepper29_t *ctx, uint8_t *state );

/**
 * @brief Stepper 29 get MO pin function.
 * @details This function reads the MO pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_get_mo_pin ( stepper29_t *ctx, uint8_t *state );

/**
 * @brief Stepper 29 get RST pin function.
 * @details This function reads the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_get_rst_pin ( stepper29_t *ctx, uint8_t *state );

/**
 * @brief Stepper 29 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_set_rst_pin ( stepper29_t *ctx, uint8_t state );

/**
 * @brief Stepper 29 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_reset_device ( stepper29_t *ctx );

/**
 * @brief Stepper 29 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast,
 * @return None.
 * @note None.
 */
void stepper29_drive_motor ( stepper29_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief Stepper 29 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper29_enable_device ( stepper29_t *ctx );

/**
 * @brief Stepper 29 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper29_disable_device ( stepper29_t *ctx );

/**
 * @brief Stepper 29 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Counter-Clockwise,
 *                  @li @c 1 - Clockwise.
 * @return None.
 * @note None.
 */
void stepper29_set_direction ( stepper29_t *ctx, uint8_t dir );

/**
 * @brief Stepper 29 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper29_switch_direction ( stepper29_t *ctx );

/**
 * @brief Stepper 29 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper29_get_int_pin ( stepper29_t *ctx );

/**
 * @brief Stepper 29 set CLK pin function.
 * @details This function sets the CLK pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper29_set_clk_pin ( stepper29_t *ctx, uint8_t state );

/**
 * @brief Stepper 29 read raw AGC OUT pin ADC value function.
 * @details This function reads results of AD conversion of the AGC OUT pin.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_read_adc_raw ( stepper29_t *ctx, uint16_t *data_out );

/**
 * @brief Stepper 29 read AGC OUT pin voltage level function.
 * @details This function reads results of AD conversion of the AGC OUT pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t stepper29_read_adc_volt ( stepper29_t *ctx, float *data_out );

/**
 * @brief Stepper 29 read AGC OUT pin voltage level average function.
 * @details This function a desired number of AGC OUT pin ADC voltage samples and averages it.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] volt_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t stepper29_read_adc_volt_avg ( stepper29_t *ctx, uint16_t num_conv, float *volt_avg );

/**
 * @brief Stepper 29 set vref function.
 * @details This function sets the ADC voltage reference for Stepper 29 Click driver.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b stepper29_init is 3.3V.
 */
err_t stepper29_set_adc_vref ( stepper29_t *ctx, float vref );

/**
 * @brief Stepper 29 get out current function.
 * @details This function reads the AGC output voltage and converts it to torque output current.
 * @param[in] ctx : Click context object.
 * See #stepper29_t object definition for detailed explanation.
 * @param[out] current : Output current.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper29_get_out_current ( stepper29_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // STEPPER29_H

/*! @} */ // stepper29

// ------------------------------------------------------------------------ END
