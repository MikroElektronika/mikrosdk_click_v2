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
 * @file dcmotor12.h
 * @brief This file contains API for DC Motor 12 Click Driver.
 */

#ifndef DCMOTOR12_H
#define DCMOTOR12_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"
#include "drv_i2c_master.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup dcmotor12 DC Motor 12 Click Driver
 * @brief API for configuring and manipulating DC Motor 12 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor12_reg DC Motor 12 Registers List
 * @brief List of registers of DC Motor 12 Click driver.
 */

/**
 * @addtogroup dcmotor12_reg
 * @{
 */

/**
 * @brief DC Motor 12 registers list.
 * @details Specified registers list of DC Motor 12 Click driver.
 */
#define DCMOTOR12_REG_STATUS1                   0x01
#define DCMOTOR12_REG_STATUS2                   0x02
#define DCMOTOR12_REG_STATUS3                   0x03
#define DCMOTOR12_REG_CONFIG1                   0x04
#define DCMOTOR12_REG_CONFIG2                   0x05
#define DCMOTOR12_REG_CONFIG3                   0x06
#define DCMOTOR12_REG_CONFIG4                   0x07
#define DCMOTOR12_REG_CONFIG5                   0x08
#define DCMOTOR12_REG_CONFIG6                   0x09
#define DCMOTOR12_REG_CONFIG7                   0x0A

/**
 * @brief DC Motor 12 PCA9538A registers.
 * @details Specified PCA9538A registers of DC Motor 12 Click driver.
 */
#define DCMOTOR12_REG_INPUT                     0x00
#define DCMOTOR12_REG_OUTPUT                    0x01
#define DCMOTOR12_REG_POLARITY                  0x02
#define DCMOTOR12_REG_CONFIG                    0x03

/*! @} */ // dcmotor12_reg

/**
 * @defgroup dcmotor12_set DC Motor 12 Registers Settings
 * @brief Settings for registers of DC Motor 12 Click driver.
 */

/**
 * @addtogroup dcmotor12_set
 * @{
 */

/**
 * @brief DC Motor 12 CONFIG1/2 register settings.
 * @details Specified CONFIG1/2 register settings for ADC of DC Motor 12 Click driver.
 */
#define DCMOTOR12_CONFIG12_OPEN_LOAD_NOP_100US  0x000000ul
#define DCMOTOR12_CONFIG12_OPEN_LOAD_NOP_50US   0x002000ul
#define DCMOTOR12_CONFIG12_OPEN_LOAD_NOP_500US  0x004000ul
#define DCMOTOR12_CONFIG12_OPEN_LOAD_NOP_MASK   0x006000ul
#define DCMOTOR12_CONFIG12_DUTY_OFF_LOW_SIDE    0x000000ul
#define DCMOTOR12_CONFIG12_DUTY_OFF_HIGH_SIDE   0x001000ul
#define DCMOTOR12_CONFIG12_DUTY_OFF_MASK        0x001000ul
#define DCMOTOR12_CONFIG12_VBAT_UVC_0US         0x000000ul
#define DCMOTOR12_CONFIG12_VBAT_UVC_100US       0x000800ul
#define DCMOTOR12_CONFIG12_VBAT_UVC_MASK        0x000800ul
#define DCMOTOR12_CONFIG12_CLIMIT_UP_6p5A       0x000000ul
#define DCMOTOR12_CONFIG12_CLIMIT_UP_4p6A       0x000400ul
#define DCMOTOR12_CONFIG12_CLIMIT_UP_MASK       0x000400ul
#define DCMOTOR12_CONFIG12_CLIMIT_LOW_0p25A     0x000000ul
#define DCMOTOR12_CONFIG12_CLIMIT_LOW_0p5A      0x000200ul
#define DCMOTOR12_CONFIG12_CLIMIT_LOW_MASK      0x000200ul
#define DCMOTOR12_CONFIG12_CLIMIT_LOW_0p25A     0x000000ul
#define DCMOTOR12_CONFIG12_CLIMIT_LOW_0p5A      0x000200ul
#define DCMOTOR12_CONFIG12_OPEN_LOAD_OP_200mA   0x000000ul
#define DCMOTOR12_CONFIG12_OPEN_LOAD_OP_100mA   0x000080ul
#define DCMOTOR12_CONFIG12_OPEN_LOAD_OP_300mA   0x000100ul
#define DCMOTOR12_CONFIG12_OPEN_LOAD_OP_MASK    0x000180ul
#define DCMOTOR12_CONFIG12_SR_MODE_NORMAL       0x000000ul
#define DCMOTOR12_CONFIG12_SR_MODE_SLOW1        0x000010ul
#define DCMOTOR12_CONFIG12_SR_MODE_SLOW2        0x000020ul
#define DCMOTOR12_CONFIG12_SR_MODE_SLOW3        0x000030ul
#define DCMOTOR12_CONFIG12_SR_MODE_SLOW4        0x000040ul
#define DCMOTOR12_CONFIG12_SR_MODE_FAST2        0x000050ul
#define DCMOTOR12_CONFIG12_SR_MODE_FAST1        0x000060ul
#define DCMOTOR12_CONFIG12_SR_MODE_MASK         0x000070ul
#define DCMOTOR12_CONFIG12_OC_LATCH             0x000000ul
#define DCMOTOR12_CONFIG12_OC_AUTO              0x000008ul
#define DCMOTOR12_CONFIG12_OC_MASK              0x000008ul
#define DCMOTOR12_CONFIG12_OC_LATCH             0x000000ul
#define DCMOTOR12_CONFIG12_OC_AUTO              0x000008ul
#define DCMOTOR12_CONFIG12_SPI_DISR_10mS        0x000000ul
#define DCMOTOR12_CONFIG12_SPI_DISR_100mS       0x000002ul
#define DCMOTOR12_CONFIG12_SPI_DISR_1S          0x000004ul
#define DCMOTOR12_CONFIG12_SPI_DISR_DISABLE     0x000006ul
#define DCMOTOR12_CONFIG12_SPI_DISR_MASK        0x000006ul
#define DCMOTOR12_CONFIG12_OPMODE_DISR_OFF      0x000000ul
#define DCMOTOR12_CONFIG12_OPMODE_DISR_CONTINUE 0x000001ul
#define DCMOTOR12_CONFIG12_OPMODE_DISR_MASK     0x000001ul

/**
 * @brief DC Motor 12 CONFIG5/6 register settings.
 * @details Specified CONFIG5/6 register settings for ADC of DC Motor 12 Click driver.
 */
#define DCMOTOR12_CONFIG56_MOTOR_OPMODE_MAX     3u
#define DCMOTOR12_CONFIG56_MOTOR_OPMODE_SHIFT   22ul
#define DCMOTOR12_CONFIG56_MOTOR_OPMODE_MASK    0xC00000ul
#define DCMOTOR12_CONFIG56_DRV_FREQ_MAX         2047u
#define DCMOTOR12_CONFIG56_DRV_FREQ_SHIFT       11ul
#define DCMOTOR12_CONFIG56_DRV_FREQ_MASK        0x3FF800ul
#define DCMOTOR12_CONFIG56_DUTY_PERIOD_MAX      2047u
#define DCMOTOR12_CONFIG56_DUTY_PERIOD_SHIFT    0ul
#define DCMOTOR12_CONFIG56_DUTY_PERIOD_MASK     0x0007FFul

/**
 * @brief DC Motor 12 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of DC Motor 12 Click driver.
 */
#define DCMOTOR12_DIAG1_PIN                     0x01
#define DCMOTOR12_DIAG2_PIN                     0x02
#define DCMOTOR12_EN1_PIN                       0x04
#define DCMOTOR12_EN2_PIN                       0x08
#define DCMOTOR12_CM_SEL_PIN                    0x10
#define DCMOTOR12_SLP_PIN                       0x20

/**
 * @brief DC Motor 12 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of DC Motor 12 Click driver.
 */
#define DCMOTOR12_DEFAULT_CONFIG                0xE3

/**
 * @brief DC Motor 12 channel operation mode settings.
 * @details Specified channel operation mode settings for ADC of DC Motor 12 Click driver.
 */
#define DCMOTOR12_MODE_OUTPUT_OFF               0x00
#define DCMOTOR12_MODE_FORWARD                  0x01
#define DCMOTOR12_MODE_REVERSE                  0x02
#define DCMOTOR12_MODE_BRAKE                    0x03

/**
 * @brief DC Motor 12 pin logic level setting.
 * @details Specified setting for pin logic level of DC Motor 12 Click driver.
 */
#define DCMOTOR12_PIN_LOW_LEVEL                 0
#define DCMOTOR12_PIN_HIGH_LEVEL                1

/**
 * @brief DC Motor 12 ADC setting.
 * @details Specified settings for ADC of DC Motor 12 Click driver.
 */
#define DCMOTOR12_VREF_3V3                      3.3
#define DCMOTOR12_VREF_5V                       5.0

/**
 * @brief DC Motor 12 current calculation values.
 * @details Specified current calculation values for ADC of DC Motor 12 Click driver.
 */
#define DCMOTOR12_NUM_CONVERSIONS               5000
#define DCMOTOR12_RSENSE                        220.0f
#define DCMOTOR12_VOLTAGE_TO_CURRENT            0.00238167f

/**
 * @brief DC Motor 12 device address setting.
 * @details Specified setting for device slave address selection of
 * DC Motor 12 Click driver.
 */
#define DCMOTOR12_DEVICE_ADDRESS_A1A0_00        0x70
#define DCMOTOR12_DEVICE_ADDRESS_A1A0_01        0x71
#define DCMOTOR12_DEVICE_ADDRESS_A1A0_10        0x72
#define DCMOTOR12_DEVICE_ADDRESS_A1A0_11        0x73

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dcmotor12_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DCMOTOR12_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define DCMOTOR12_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dcmotor12_set

/**
 * @defgroup dcmotor12_map DC Motor 12 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 12 Click driver.
 */

/**
 * @addtogroup dcmotor12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 12 Click to the selected MikroBUS.
 */
#define DCMOTOR12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cm = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dcmotor12_map
/*! @} */ // dcmotor12

/**
 * @brief DC Motor 12 Click context object.
 * @details Context object definition of DC Motor 12 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t clk;          /**< PWM clock pin. */
    digital_out_t slp;          /**< Sleep pin (Active low). */

    // Input pins
    digital_in_t int_pin;       /**< PCA9538A interrupt pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */
    i2c_master_t i2c;           /**< I2C driver object. */
    analog_in_t  adc;           /**< ADC module object. */

    uint8_t      slave_address; /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} dcmotor12_t;

/**
 * @brief DC Motor 12 Click configuration object.
 * @details Configuration object definition of DC Motor 12 Click driver.
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
    pin_name_t cm;              /**< Current monitor pin. */

    // Additional gpio pins
    pin_name_t clk;             /**< PWM clock pin. */
    pin_name_t slp;             /**< Sleep pin (Active low). */
    pin_name_t int_pin;         /**< PCA9538A interrupt pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    
    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */
    
    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} dcmotor12_cfg_t;

/**
 * @brief DC Motor 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR12_OK = 0,
    DCMOTOR12_ERROR = -1

} dcmotor12_return_value_t;

/*!
 * @addtogroup dcmotor12 DC Motor 12 Click Driver
 * @brief API for configuring and manipulating DC Motor 12 Click driver.
 * @{
 */

/**
 * @brief DC Motor 12 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor12_cfg_setup ( dcmotor12_cfg_t *cfg );

/**
 * @brief DC Motor 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_init ( dcmotor12_t *ctx, dcmotor12_cfg_t *cfg );

/**
 * @brief DC Motor 12 default configuration function.
 * @details This function executes a default configuration of DC Motor 12
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor12_default_cfg ( dcmotor12_t *ctx );

/**
 * @brief DC Motor 12 write register function.
 * @details This function writes a 24-bit data to the selected register by using SPI serial interface
 * and checks if it is written correctly.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 24-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_write_register ( dcmotor12_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief DC Motor 12 read register function.
 * @details This function reads a 24-bit data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_read_register ( dcmotor12_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief DC Motor 12 pca9538a write register function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_pca9538a_write_register ( dcmotor12_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DC Motor 12 pca9538a read register function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_pca9538a_read_register ( dcmotor12_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DC Motor 12 enter sleep mode function.
 * @details This function sets the device to sleep mode by setting the SLP pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor12_enter_sleep_mode ( dcmotor12_t *ctx );

/**
 * @brief DC Motor 12 wake up device function.
 * @details This function wakes up the device from sleep by setting the SLP pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor12_wake_up_device ( dcmotor12_t *ctx );

/**
 * @brief DC Motor 12 get int pin function.
 * @details This function returns the PCA9538A INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t dcmotor12_get_int_pin ( dcmotor12_t *ctx );

/**
 * @brief DC Motor 12 set clk pin function.
 * @details This function sets the CLK pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void dcmotor12_set_clk_pin ( dcmotor12_t *ctx, uint8_t state );

/**
 * @brief DC Motor 12 set en1 pin function.
 * @details This function sets the en1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_set_en1_pin ( dcmotor12_t *ctx, uint8_t state );

/**
 * @brief DC Motor 12 get en1 pin function.
 * @details This function reads the en1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_get_en1_pin ( dcmotor12_t *ctx, uint8_t *state );

/**
 * @brief DC Motor 12 set en2 pin function.
 * @details This function sets the en2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_set_en2_pin ( dcmotor12_t *ctx, uint8_t state );

/**
 * @brief DC Motor 12 get en2 pin function.
 * @details This function reads the en2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_get_en2_pin ( dcmotor12_t *ctx, uint8_t *state );

/**
 * @brief DC Motor 12 set cm sel pin function.
 * @details This function sets the cm sel pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_set_cm_sel_pin ( dcmotor12_t *ctx, uint8_t state );

/**
 * @brief DC Motor 12 get cm sel pin function.
 * @details This function reads the cm sel pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_get_cm_sel_pin ( dcmotor12_t *ctx, uint8_t *state );

/**
 * @brief DC Motor 12 get diag1 pin function.
 * @details This function reads the diag1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_get_diag1_pin ( dcmotor12_t *ctx, uint8_t *state );

/**
 * @brief DC Motor 12 get diag2 pin function.
 * @details This function reads the diag2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_get_diag2_pin ( dcmotor12_t *ctx, uint8_t *state );

/**
 * @brief DC Motor 12 get sleep pin function.
 * @details This function reads the sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_get_sleep_pin ( dcmotor12_t *ctx, uint8_t *state );

/**
 * @brief DC Motor 12 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_read_an_pin_value ( dcmotor12_t *ctx, uint16_t *data_out );

/**
 * @brief DC Motor 12 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t dcmotor12_read_an_pin_voltage ( dcmotor12_t *ctx, float *data_out );

/**
 * @brief DC Motor 12 get motor current function.
 * @details This function reads the motor current consumption.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[out] current : Current value [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Make sure the CM sel pin state is set properly.
 */
err_t dcmotor12_get_motor_current ( dcmotor12_t *ctx, float *current );

/**
 * @brief DC Motor 12 set ch1 operation mode function.
 * @details This function sets the operation mode of the channel 1.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - OFF,
 *                   @li @c 1 - FORWARD,
 *                   @li @c 2 - REVERSE,
 *                   @li @c 3 - BRAKE.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_set_ch1_operation_mode ( dcmotor12_t *ctx, uint8_t mode );

/**
 * @brief DC Motor 12 set ch2 operation mode function.
 * @details This function sets the operation mode of the channel 2.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - OFF,
 *                   @li @c 1 - FORWARD,
 *                   @li @c 2 - REVERSE,
 *                   @li @c 3 - BRAKE.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Ineffective for Combined-Channel Mode (LARGE Mode) (OSEL1 = L and OSEL2 = L).
 */
err_t dcmotor12_set_ch2_operation_mode ( dcmotor12_t *ctx, uint8_t mode );

/**
 * @brief DC Motor 12 set ch1 drive frequency function.
 * @details This function sets the raw drive frequency of the channel 1.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] drv_freq : Raw drive frequency (0-2047).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_set_ch1_drive_frequency ( dcmotor12_t *ctx, uint16_t drv_freq );

/**
 * @brief DC Motor 12 set ch2 drive frequency function.
 * @details This function sets the raw drive frequency of the channel 2.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] drv_freq : Raw drive frequency (0-2047).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Ineffective for Combined-Channel Mode (LARGE Mode) (OSEL1 = L and OSEL2 = L).
 */
err_t dcmotor12_set_ch2_drive_frequency ( dcmotor12_t *ctx, uint16_t drv_freq );

/**
 * @brief DC Motor 12 set ch1 duty period function.
 * @details This function sets the duty period of the channel 1.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] duty_period : Duty period (0-2047).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor12_set_ch1_duty_period ( dcmotor12_t *ctx, uint16_t duty_period );

/**
 * @brief DC Motor 12 set ch1 duty period function.
 * @details This function sets the duty period of the channel 1.
 * @param[in] ctx : Click context object.
 * See #dcmotor12_t object definition for detailed explanation.
 * @param[in] duty_period : Duty period (0-2047).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Ineffective for Combined-Channel Mode (LARGE Mode) (OSEL1 = L and OSEL2 = L).
 */
err_t dcmotor12_set_ch2_duty_period ( dcmotor12_t *ctx, uint16_t duty_period );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR12_H

/*! @} */ // dcmotor12

// ------------------------------------------------------------------------ END
