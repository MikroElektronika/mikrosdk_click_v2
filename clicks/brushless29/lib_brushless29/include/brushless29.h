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
 * @file brushless29.h
 * @brief This file contains API for Brushless 29 Click Driver.
 */

#ifndef BRUSHLESS29_H
#define BRUSHLESS29_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "drv_pwm.h"

/*!
 * @addtogroup brushless29 Brushless 29 Click Driver
 * @brief API for configuring and manipulating Brushless 29 Click driver.
 * @{
 */

/**
 * @defgroup brushless29_reg Brushless 29 Registers List
 * @brief List of registers of Brushless 29 Click driver.
 */

/**
 * @addtogroup brushless29_reg
 * @{
 */

/**
 * @brief Brushless 29 serial commands list.
 * @details Specified serial commands list of Brushless 29 Click driver.
 */
#define BRUSHLESS29_CMD_SR_READ                         0x49
#define BRUSHLESS29_CMD_SR_WRITE                        0x4A
#define BRUSHLESS29_CMD_REG_READ                        0x51
#define BRUSHLESS29_CMD_REG_WRITE                       0x52
#define BRUSHLESS29_CMD_NVM_LOAD                        0x59
#define BRUSHLESS29_CMD_NVM_SAVE                        0x5A
#define BRUSHLESS29_CMD_NVM_ABORT                       0x5C

/**
 * @brief Brushless 29 TC78B043 register map.
 * @details Addresses of the 16-bit normal registers used for motor profile,
 * protection, output, direction, oscillator, and speed-command settings.
 */
#define BRUSHLESS29_REG_USER_ID                         0x00
#define BRUSHLESS29_REG_START_STOP_DUTY                 0x01
#define BRUSHLESS29_REG_PWM_MAX_DUTY                    0x02
#define BRUSHLESS29_REG_START_OUT_DUTY                  0x03
#define BRUSHLESS29_REG_DUTY_SLOPE                      0x04
#define BRUSHLESS29_REG_DUTY_CHANGE                     0x05
#define BRUSHLESS29_REG_SPEED_CTRL                      0x06
#define BRUSHLESS29_REG_LEAD_ANGLE                      0x07
#define BRUSHLESS29_REG_SPEED_OFFSET                    0x08
#define BRUSHLESS29_REG_HIGH_SPEED                      0x09
#define BRUSHLESS29_REG_OUTPUT_CONFIG                   0x0A
#define BRUSHLESS29_REG_PROTECT_CONFIG                  0x0B
#define BRUSHLESS29_REG_DIR_OSC_CONFIG                  0x0C
#define BRUSHLESS29_REG_SPEED_COMMAND                   0x0D

/**
 * @brief Brushless 29 PCA9538A registers.
 * @details Specified PCA9538A registers of Brushless 29 Click driver.
 */
#define BRUSHLESS29_EXP_REG_INPUT                       0x00
#define BRUSHLESS29_EXP_REG_OUTPUT                      0x01
#define BRUSHLESS29_EXP_REG_POLARITY                    0x02
#define BRUSHLESS29_EXP_REG_CONFIG                      0x03

/*! @} */ // brushless29_reg

/**
 * @defgroup brushless29_set Brushless 29 Registers Settings
 * @brief Settings for registers of Brushless 29 Click driver.
 */

/**
 * @addtogroup brushless29_set
 * @{
 */

/**
 * @brief Brushless 29 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Brushless 29 Click driver.
 */
#define BRUSHLESS29_EXP_PIN_RES                         0x01
#define BRUSHLESS29_EXP_PIN_SEL                         0x02
#define BRUSHLESS29_EXP_PIN_FAULT                       0x04
#define BRUSHLESS29_EXP_PIN_DIR                         0x08
#define BRUSHLESS29_EXP_PIN_PG                          0x40
#define BRUSHLESS29_EXP_PIN_EN                          0x80

/**
 * @brief Brushless 29 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Brushless 29 Click driver.
 */
#define BRUSHLESS29_EXP_DEFAULT_CONFIG                  0x74
#define BRUSHLESS29_EXP_DEFAULT_OUTPUT                  0x

/**
 * @brief Brushless 29 direction setting.
 * @details Specified setting for direction of Brushless 29 Click driver.
 */
#define BRUSHLESS29_DIR_CW                              0
#define BRUSHLESS29_DIR_CCW                             1

/**
 * @brief Brushless 29 pin logic state setting.
 * @details Specified setting for pin logic state of Brushless 29 Click driver.
 */
#define BRUSHLESS29_PIN_STATE_LOW                       0
#define BRUSHLESS29_PIN_STATE_HIGH                      1

/**
 * @brief Brushless 29 TC78B043 status register setting.
 * @details Defines the BUSY, serial-enable, and NVM-write status bits. Normal
 * mode restores VSP, RES, and FG motor-control operation; serial mode enables
 * access to the 16-bit normal register map.
 */
#define BRUSHLESS29_SR_BUSY_MASK                        0x01
#define BRUSHLESS29_SR_ENB_MASK                         0x02
#define BRUSHLESS29_SR_NVM_WR_MASK                      0x08
#define BRUSHLESS29_SR_VALID_MASK                       0x0B
#define BRUSHLESS29_SR_NORMAL_MODE                      0x00
#define BRUSHLESS29_SR_SERIAL_MODE                      BRUSHLESS29_SR_ENB_MASK

/**
 * @brief Brushless 29 TC78B043 startup and stopping duty settings.
 * @details Register 1 defines the input command thresholds that start and stop
 * the motor. The default profile uses an approximately 5 percent startup
 * threshold and an approximately 2 percent stopping threshold.
 */
#define BRUSHLESS29_START_DUTY_MASK                     0x00FF
#define BRUSHLESS29_STOP_DUTY_MASK                      0x7F00
#define BRUSHLESS29_START_DUTY_5_PERCENT                0x001A
#define BRUSHLESS29_STOP_DUTY_2_PERCENT                 0x0500

/**
 * @brief Brushless 29 TC78B043 waveform and maximum duty settings.
 * @details Register 2 selects the motor driving waveform and limits the
 * maximum output duty. The default profile uses forced sine-wave commutation
 * at startup and 60-degree reset sine-wave drive during normal rotation.
 */
#define BRUSHLESS29_PWM_MODE_MASK                       0xF000
#define BRUSHLESS29_MAX_DUTY_MASK                       0x00FF
#define BRUSHLESS29_PWM_MODE_SINE_60                    0x0000
#define BRUSHLESS29_MAX_DUTY_100_PERCENT                0x00FF

/**
 * @brief Brushless 29 TC78B043 minimum output duty settings.
 * @details Register 3 defines the initial output duty applied after the speed
 * command crosses the startup threshold. The default profile starts at
 * approximately 10 percent to limit motor inrush current.
 */
#define BRUSHLESS29_START_OUT_DUTY_MASK                 0x00FF
#define BRUSHLESS29_START_OUT_DUTY_10_PERCENT           0x0033
#define BRUSHLESS29_START_OUT_DUTY_20_PERCENT           0x0066
#define BRUSHLESS29_START_OUT_DUTY_50_PERCENT           0x00FF

/**
 * @brief Brushless 29 TC78B043 velocity curve slope settings.
 * @details Register 4 defines the ratio between speed command changes and
 * output duty changes. A value of 0x0400 selects a 1-to-1 ratio and allows the
 * reduced minimum output duty to reach full output at the maximum command.
 */
#define BRUSHLESS29_DUTY_SLOPE_MASK                     0x3FFF
#define BRUSHLESS29_DUTY_SLOPE_9_TO_16                  0x0240
#define BRUSHLESS29_DUTY_SLOPE_7_TO_8                   0x0380
#define BRUSHLESS29_DUTY_SLOPE_1_TO_1                   0x0400

/**
 * @brief Brushless 29 TC78B043 duty transition settings.
 * @details Register 5 controls startup acceleration, steady-state
 * acceleration, and deceleration. The default profile uses a reduced 6/8
 * startup rate and the faster 20/8 rate after startup.
 */
#define BRUSHLESS29_STOP_SEQUENCE_MASK                  0x8000
#define BRUSHLESS29_DWN_DUTY_LIMIT_MASK                 0x0F00
#define BRUSHLESS29_UP_DUTY_LIMIT_MASK                  0x00F0
#define BRUSHLESS29_SS_DUTY_LIMIT_MASK                  0x000F
#define BRUSHLESS29_DWN_DUTY_LIMIT_20_8                 0x0E00
#define BRUSHLESS29_UP_DUTY_LIMIT_20_8                  0x00E0
#define BRUSHLESS29_SS_DUTY_LIMIT_6_8                   0x000C
#define BRUSHLESS29_SS_DUTY_LIMIT_10_8                  0x000D
#define BRUSHLESS29_SS_DUTY_LIMIT_20_8                  0x000E

/**
 * @brief Brushless 29 TC78B043 speed control settings.
 * @details Register 6 selects analog, PWM, or SPI velocity-curve input and
 * configures idle-return frequency, sine-wave averaging, reset switching, and
 * the forced-commutation transition frequency.
 */
#define BRUSHLESS29_TRQ_SEL_MASK                        0xE000
#define BRUSHLESS29_HZ_RANGE_MASK                       0x00C0
#define BRUSHLESS29_AVE_SEL_MASK                        0x0030
#define BRUSHLESS29_SIN_SW_RATIO_MASK                   0x000C
#define BRUSHLESS29_START_FREQ_MASK                     0x0003
#define BRUSHLESS29_TRQ_SEL_ANALOG_A                    0x0000
#define BRUSHLESS29_TRQ_SEL_ANALOG_B                    0x2000
#define BRUSHLESS29_TRQ_SEL_ANALOG_CURVE                0x4000
#define BRUSHLESS29_TRQ_SEL_PWM_LOW                     0x6000
#define BRUSHLESS29_TRQ_SEL_PWM_HIGH                    0x8000
#define BRUSHLESS29_TRQ_SEL_SPI                         0xA000
#define BRUSHLESS29_HZ_RANGE_DISABLED                   0x0000
#define BRUSHLESS29_AVE_SEL_2_SAMPLES                   0x0000
#define BRUSHLESS29_SIN_SW_RATIO_6_25_PERCENT           0x0000
#define BRUSHLESS29_START_FREQ_2_HZ                     0x0000
#define BRUSHLESS29_START_FREQ_4_HZ                     0x0001
#define BRUSHLESS29_START_FREQ_8_HZ                     0x0003

/**
 * @brief Brushless 29 default TC78B043 motor profile.
 * @details These values configure a Hall-based sine-wave profile for the
 * 24 V 42BLF01. Values are written only to the normal registers; NVM is not
 * modified.
 */
#define BRUSHLESS29_CFG_START_STOP_DUTY                 ( BRUSHLESS29_STOP_DUTY_2_PERCENT | \
                                                          BRUSHLESS29_START_DUTY_5_PERCENT )
#define BRUSHLESS29_CFG_PWM_MAX_DUTY                    ( BRUSHLESS29_PWM_MODE_SINE_60 | \
                                                          BRUSHLESS29_MAX_DUTY_100_PERCENT )
#define BRUSHLESS29_CFG_START_OUT_DUTY                  BRUSHLESS29_START_OUT_DUTY_10_PERCENT
#define BRUSHLESS29_CFG_DUTY_SLOPE                      BRUSHLESS29_DUTY_SLOPE_1_TO_1
#define BRUSHLESS29_CFG_DUTY_CHANGE                     ( BRUSHLESS29_DWN_DUTY_LIMIT_20_8 | \
                                                          BRUSHLESS29_UP_DUTY_LIMIT_20_8 | \
                                                          BRUSHLESS29_SS_DUTY_LIMIT_6_8 )
#define BRUSHLESS29_CFG_SPEED_CTRL                      ( BRUSHLESS29_TRQ_SEL_SPI | \
                                                          BRUSHLESS29_HZ_RANGE_DISABLED | \
                                                          BRUSHLESS29_AVE_SEL_2_SAMPLES | \
                                                          BRUSHLESS29_SIN_SW_RATIO_6_25_PERCENT | \
                                                          BRUSHLESS29_START_FREQ_2_HZ )

/**
 * @brief Brushless 29 TC78B043 speed command setting.
 * @details Defines the register 13 command field and common 0-to-512 command
 * values used by both SPI and PWM speed-control paths.
 */
#define BRUSHLESS29_SPEED_MASK                          0xFFC0
#define BRUSHLESS29_SPEED_SHIFT                         6
#define BRUSHLESS29_SPEED_MIN                           0
#define BRUSHLESS29_SPEED_MAX                           512
#define BRUSHLESS29_SPEED_SLOW                          128
#define BRUSHLESS29_SPEED_MEDIUM                        320
#define BRUSHLESS29_SPEED_FAST                          512

/**
 * @brief Brushless 29 speed control mode settings.
 * @details Selects whether the common 0 to 512 speed command is applied
 * through the mikroBUS PWM/VSP signal or TC78B043 register 13 over SPI.
 */
#define BRUSHLESS29_SPEED_MODE_PWM                      0
#define BRUSHLESS29_SPEED_MODE_SPI                      1
#define BRUSHLESS29_SPEED_MODE                          BRUSHLESS29_SPEED_MODE_SPI

/**
 * @brief Brushless 29 device address setting.
 * @details Specified setting for device slave address selection of
 * Brushless 29 Click driver.
 */
#define BRUSHLESS29_DEVICE_ADDRESS_0                    0x70
#define BRUSHLESS29_DEVICE_ADDRESS_1                    0x71

/**
 * @brief Brushless 29 VSP PWM settings.
 * @details The TC78B043 accepts a PWM speed command from 1 kHz to 100 kHz.
 * A 20 kHz signal provides the maximum 512-step duty recognition at the
 * typical 10.24 MHz internal oscillation frequency.
 */
#define BRUSHLESS29_VSP_PWM_FREQ                        20000
#define BRUSHLESS29_VSP_DUTY_MIN                        0.0
#define BRUSHLESS29_VSP_DUTY_MAX                        1.0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b brushless29_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BRUSHLESS29_SET_DATA_SAMPLE_EDGE                SET_SPI_DATA_SAMPLE_EDGE
#define BRUSHLESS29_SET_DATA_SAMPLE_MIDDLE              SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // brushless29_set

/**
 * @defgroup brushless29_map Brushless 29 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 29 Click driver.
 */

/**
 * @addtogroup brushless29_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 29 Click to the selected MikroBUS.
 */
#define BRUSHLESS29_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.fg_pin = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.vsp = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // brushless29_map
/*! @} */ // brushless29

/**
 * @brief Brushless 29 Click context object.
 * @details Context object definition of Brushless 29 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< PCA9538A reset pin. */

    // Input pins
    digital_in_t fg_pin;        /**< Rotation Pulse Output pin. */
    digital_in_t int_pin;       /**< PCA9538A interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */
    spi_master_t spi;           /**< SPI driver object. */
    pwm_t pwm;                  /**< PWM driver object. */

    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */
    uint32_t pwm_freq;          /**< PWM frequency value. */
    uint8_t pwm_active;         /**< VSP PWM active state. */
    uint8_t speed_mode;         /**< Selected motor speed control mode. */

} brushless29_t;

/**
 * @brief Brushless 29 Click configuration object.
 * @details Configuration object definition of Brushless 29 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t fg_pin;          /**< Rotation Pulse Output pin. */
    pin_name_t rst;             /**< PCA9538A reset pin. */
    pin_name_t vsp;             /**< Speed Control Input pin. */
    pin_name_t int_pin;         /**< PCA9538A interrupt pin. */

    // static variable
    uint32_t i2c_speed;         /**< I2C serial speed. */
    uint8_t  i2c_address;       /**< I2C slave address. */
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    uint32_t dev_pwm_freq;      /**< PWM frequency value. */
    uint8_t speed_mode;         /**< Motor speed control mode. */

} brushless29_cfg_t;

/**
 * @brief Brushless 29 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS29_OK = 0,
    BRUSHLESS29_ERROR = -1

} brushless29_return_value_t;

/*!
 * @addtogroup brushless29 Brushless 29 Click Driver
 * @brief API for configuring and manipulating Brushless 29 Click driver.
 * @{
 */

/**
 * @brief Brushless 29 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless29_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless29_cfg_setup ( brushless29_cfg_t *cfg );

/**
 * @brief Brushless 29 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless29_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_init ( brushless29_t *ctx, brushless29_cfg_t *cfg );

/**
 * @brief Brushless 29 default configuration function.
 * @details This function executes a default configuration of Brushless 29
 * Click board.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless29_default_cfg ( brushless29_t *ctx );

/**
 * @brief Brushless 29 write register function.
 * @details This function writes data to the selected TC78B043 normal register.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] reg : TC78B043 normal register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note TC78B043 serial mode must be enabled before calling this function.
 * Avoid register access while the motor is running because RES, VSP, and FG
 * are temporarily switched to the serial interface.
 */
err_t brushless29_write_reg ( brushless29_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Brushless 29 read register function.
 * @details This function reads data from the selected TC78B043 normal register.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] reg : TC78B043 normal register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note TC78B043 serial mode must be enabled before calling this function.
 * Avoid register access while the motor is running because RES, VSP, and FG
 * are temporarily switched to the serial interface.
 */
err_t brushless29_read_reg ( brushless29_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Brushless 29 write expander reg function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_write_exp_reg ( brushless29_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Brushless 29 read expander reg function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_read_exp_reg ( brushless29_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Brushless 29 communication check function.
 * @details This function enables TC78B043 serial mode and verifies the status
 * register response. It then performs a reversible write and read test using
 * the USERID normal register to verify the complete SPI command and data path.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The original USERID value is restored and NVM is not modified.
 */
err_t brushless29_check_com ( brushless29_t *ctx );

/**
 * @brief Brushless 29 get RES pin function.
 * @details This function reads the RES pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_get_res_pin ( brushless29_t *ctx, uint8_t *state );

/**
 * @brief Brushless 29 set RES pin function.
 * @details This function sets the RES pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_set_res_pin ( brushless29_t *ctx, uint8_t state );

/**
 * @brief Brushless 29 get SEL pin function.
 * @details This function reads the SEL pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_get_sel_pin ( brushless29_t *ctx, uint8_t *state );

/**
 * @brief Brushless 29 set SEL pin function.
 * @details This function sets the SEL pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_set_sel_pin ( brushless29_t *ctx, uint8_t state );

/**
 * @brief Brushless 29 get FAULT pin function.
 * @details This function reads the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_get_fault_pin ( brushless29_t *ctx, uint8_t *state );

/**
 * @brief Brushless 29 get DIR pin function.
 * @details This function reads the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_get_dir_pin ( brushless29_t *ctx, uint8_t *state );

/**
 * @brief Brushless 29 set DIR pin function.
 * @details This function sets the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_set_dir_pin ( brushless29_t *ctx, uint8_t state );

/**
 * @brief Brushless 29 get PG pin function.
 * @details This function reads the PG pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_get_pg_pin ( brushless29_t *ctx, uint8_t *state );

/**
 * @brief Brushless 29 get EN pin function.
 * @details This function reads the EN pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_get_en_pin ( brushless29_t *ctx, uint8_t *state );

/**
 * @brief Brushless 29 set EN pin function.
 * @details This function sets the EN pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_set_en_pin ( brushless29_t *ctx, uint8_t state );

/**
 * @brief Brushless 29 enable output function.
 * @details This function enables the output by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_enable_output ( brushless29_t *ctx );

/**
 * @brief Brushless 29 disable output function.
 * @details This function disables the output by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_disable_output ( brushless29_t *ctx );

/**
 * @brief Brushless 29 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_set_direction ( brushless29_t *ctx, uint8_t dir );

/**
 * @brief Brushless 29 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless29_switch_direction ( brushless29_t *ctx );

/**
 * @brief Brushless 29 reset expander function.
 * @details This function resets the PCA9538A device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless29_reset_exp ( brushless29_t *ctx );

/**
 * @brief Brushless 29 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void brushless29_set_rst_pin ( brushless29_t *ctx, uint8_t state );

/**
 * @brief Brushless 29 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t brushless29_get_int_pin ( brushless29_t *ctx );

/**
 * @brief Brushless 29 set duty cycle function.
 * @details This function sets the duty cycle of the PWM speed command routed
 * from the mikroBUS PWM pin to the TC78B043 VSP input.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle from 0.0 to 1.0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Select #BRUSHLESS29_SPEED_MODE_PWM before using this function as a
 * motor speed command.
 */
err_t brushless29_set_duty_cycle ( brushless29_t *ctx, float duty_cycle );

/**
 * @brief Brushless 29 PWM start function.
 * @details This function selects the mikroBUS PWM route, exits TC78B043 serial
 * mode to restore the VSP input, and starts PWM signal generation.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The function sets the PCA9538 SEL output high before PWM is started.
 */
err_t brushless29_pwm_start ( brushless29_t *ctx );

/**
 * @brief Brushless 29 PWM stop function.
 * @details This function stops PWM signal generation on the mikroBUS PWM pin.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Set the duty cycle to zero before stopping PWM when the motor is
 * active.
 */
err_t brushless29_pwm_stop ( brushless29_t *ctx );

/**
 * @brief Brushless 29 read status register function.
 * @details This function reads the TC78B043 serial status register.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[out] status : Pointer to the output status byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The status register can be read in normal or serial mode. Avoid
 * repeated reads while the motor is running because RES, VSP, and FG are
 * temporarily switched to the serial interface.
 */
err_t brushless29_read_status ( brushless29_t *ctx, uint8_t *status );

/**
 * @brief Brushless 29 wait ready function.
 * @details This function waits for the TC78B043 register processing to finish.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Serial mode must be enabled before calling this function.
 */
err_t brushless29_wait_ready ( brushless29_t *ctx );

/**
 * @brief Brushless 29 set serial mode function.
 * @details This function enters or exits the TC78B043 serial mode and verifies
 * the requested state through the status register.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] mode : Status register serial mode setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use #BRUSHLESS29_SR_SERIAL_MODE to access normal registers and
 * #BRUSHLESS29_SR_NORMAL_MODE to restore the motor-control pin functions.
 */
err_t brushless29_set_serial_mode ( brushless29_t *ctx, uint8_t mode );

/**
 * @brief Brushless 29 set speed function.
 * @details This function writes the TC78B043 SPI speed command using one
 * continued normal-register write frame. A single frame minimizes disturbance
 * of the motor-control signals shared with the serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] speed : Motor speed command from 0 to 512.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Values above #BRUSHLESS29_SPEED_MAX are limited to the maximum value.
 */
err_t brushless29_set_speed ( brushless29_t *ctx, uint16_t speed );

/**
 * @brief Brushless 29 set speed control mode function.
 * @details This function updates the TC78B043 speed command source in
 * configuration register 6 without changing the other register settings.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] mode : Speed control mode setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use #BRUSHLESS29_SPEED_MODE_PWM or #BRUSHLESS29_SPEED_MODE_SPI.
 * The default PWM path uses the tested low-active VSP setting. Change the
 * speed control mode only while the motor is stopped.
 */
err_t brushless29_set_speed_mode ( brushless29_t *ctx, uint8_t mode );

/**
 * @brief Brushless 29 run motor function.
 * @details This function sets the rotation direction and applies a common
 * 0 to 512 speed command through the selected speed control mode, then enables
 * the motor gate driver. In PWM mode, the command is converted to a VSP duty
 * cycle. In SPI mode, it is written to TC78B043 register 13.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @param[in] direction : Motor direction setting.
 * @param[in] speed : Motor speed command from 0 to 512.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Select the mode with #brushless29_set_speed_mode or the
 * #brushless29_cfg_t speed_mode member. The gate driver is enabled before the
 * TC78B043 RES input is released, so commutation starts only after the power
 * stage is ready.
 */
err_t brushless29_run_motor ( brushless29_t *ctx, uint8_t direction, uint16_t speed );

/**
 * @brief Brushless 29 stop motor function.
 * @details This function clears the speed command and disables the motor gate driver.
 * @param[in] ctx : Click context object.
 * See #brushless29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The TC78B043 RES input is asserted before the gate driver is disabled.
 */
err_t brushless29_stop_motor ( brushless29_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS29_H

/*! @} */ // brushless29

// ------------------------------------------------------------------------ END
