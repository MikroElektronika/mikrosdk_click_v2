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
 * @file remotetemp2.h
 * @brief This file contains API for Remote Temp 2 Click Driver.
 */

#ifndef REMOTETEMP2_H
#define REMOTETEMP2_H

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

/*!
 * @addtogroup remotetemp2 Remote Temp 2 Click Driver
 * @brief API for configuring and manipulating Remote Temp 2 Click driver.
 * @{
 */

/**
 * @defgroup remotetemp2_reg Remote Temp 2 Registers List
 * @brief List of registers of Remote Temp 2 Click driver.
 */

/**
 * @addtogroup remotetemp2_reg
 * @{
 */

/**
 * @brief Remote Temp 2 register list.
 * @details Specified register list of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_REG_TEMP_LOCAL                      0x00
#define REMOTETEMP2_REG_TEMP_REMOTE_CH1_HIGH            0x01
#define REMOTETEMP2_REG_STATUS                          0x02
#define REMOTETEMP2_REG_CONFIGURATION                   0x03
#define REMOTETEMP2_REG_CONV_PERIOD                     0x04
#define REMOTETEMP2_REG_THIGH_LIMIT_LOCAL               0x05
#define REMOTETEMP2_REG_TLOW_LIMIT_LOCAL                0x06
#define REMOTETEMP2_REG_THIGH_LIMIT_REMOTE_CH1_HIGH     0x07
#define REMOTETEMP2_REG_TLOW_LIMIT_REMOTE_CH1_HIGH      0x08
#define REMOTETEMP2_REG_ONE_SHOT                        0x0F
#define REMOTETEMP2_REG_TEMP_REMOTE_CH1_LOW             0x10
#define REMOTETEMP2_REG_SCRATCHPAD1                     0x11
#define REMOTETEMP2_REG_SCRATCHPAD2                     0x12
#define REMOTETEMP2_REG_THIGH_LIMIT_REMOTE_CH1_LOW      0x13
#define REMOTETEMP2_REG_TLOW_LIMIT_REMOTE_CH1_LOW       0x14
#define REMOTETEMP2_REG_THIGH_LIMIT_REMOTE_CH2_HIGH     0x15
#define REMOTETEMP2_REG_TLOW_LIMIT_REMOTE_CH2_HIGH      0x16
#define REMOTETEMP2_REG_THIGH_LIMIT_REMOTE_CH2_LOW      0x17
#define REMOTETEMP2_REG_TLOW_LIMIT_REMOTE_CH2_LOW       0x18
#define REMOTETEMP2_REG_THIGH_CRIT_REMOTE_CH1           0x19
#define REMOTETEMP2_REG_THIGH_CRIT_REMOTE_CH2           0x1A
#define REMOTETEMP2_REG_DIODE_FAULT                     0x1B
#define REMOTETEMP2_REG_ALERT_MASK                      0x1F
#define REMOTETEMP2_REG_THIGH_CRIT_LOCAL                0x20
#define REMOTETEMP2_REG_HYSTERESIS                      0x21
#define REMOTETEMP2_REG_TEMP_REMOTE_CH2_HIGH            0x23
#define REMOTETEMP2_REG_TEMP_REMOTE_CH2_LOW             0x24
#define REMOTETEMP2_REG_ETA_FACTOR_CH1                  0x27
#define REMOTETEMP2_REG_ETA_FACTOR_CH2                  0x28
#define REMOTETEMP2_REG_HIGH_LIMIT_STATUS               0x35
#define REMOTETEMP2_REG_LOW_LIMIT_STATUS                0x36
#define REMOTETEMP2_REG_TCRIT_LIMIT_STATUS              0x37
#define REMOTETEMP2_REG_FILTER_CONTROL                  0x40
#define REMOTETEMP2_REG_CHIP_ID                         0xFD
#define REMOTETEMP2_REG_VENDOR_ID                       0xFE
#define REMOTETEMP2_REG_DEVICE_REV_ID                   0xFF

/*! @} */ // remotetemp2_reg

/**
 * @defgroup remotetemp2_set Remote Temp 2 Registers Settings
 * @brief Settings for registers of Remote Temp 2 Click driver.
 */

/**
 * @addtogroup remotetemp2_set
 * @{
 */

/**
 * @brief Remote Temp 2 configuration register setting.
 * @details Specified setting for configuration register of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_CFG_ALERT_MASK                      0x80
#define REMOTETEMP2_CFG_SHUTDOWN_MODE                   0x40
#define REMOTETEMP2_CFG_CONTINUOUS_MODE                 0x00
#define REMOTETEMP2_CFG_ALERT_COMPARATOR_MODE           0x20
#define REMOTETEMP2_CFG_ALERT_INTERRUPT_MODE            0x00

/**
 * @brief Remote Temp 2 status register setting.
 * @details Specified setting for status register of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_STATUS_ADC_BUSY                     0x80
#define REMOTETEMP2_STATUS_THIGH                        0x10
#define REMOTETEMP2_STATUS_TLOW                         0x08
#define REMOTETEMP2_STATUS_REMOTE_FAULT                 0x04
#define REMOTETEMP2_STATUS_TCRIT                        0x02

/**
 * @brief Remote Temp 2 alert mask register setting.
 * @details Specified setting for alert mask register of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_ALERT_MASK_CH2                      0x04
#define REMOTETEMP2_ALERT_MASK_CH1                      0x02
#define REMOTETEMP2_ALERT_MASK_LOCAL                    0x01
#define REMOTETEMP2_ALERT_MASK_ALL                      0x00

/**
 * @brief Remote Temp 2 diode fault register setting.
 * @details Specified setting for diode fault register of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_DIODE_FAULT_SHORT                   0x08
#define REMOTETEMP2_DIODE_FAULT_CH2_OPEN                0x04
#define REMOTETEMP2_DIODE_FAULT_CH1_OPEN                0x02

/**
 * @brief Remote Temp 2 hysteresis register setting.
 * @details Specified setting for hysteresis register of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_HYSTERESIS_1_DEG_C                  0x01

/**
 * @brief Remote Temp 2 temperature limits setting.
 * @details Specified setting for temperature limits of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_TCRIT_LIMIT_30_DEG_C               30
#define REMOTETEMP2_LOCAL_HIGH_LIMIT_30_DEG_C          30
#define REMOTETEMP2_HIGH_LIMIT_30_DEG_C                30.0f
#define REMOTETEMP2_LOW_LIMIT_0_DEG_C                  0.0f
#define REMOTETEMP2_LOCAL_LOW_LIMIT_0_DEG_C            0

/**
 * @brief Remote Temp 2 12-bit sign extension setting.
 * @details Specified setting for 12-bit sign extension of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_SIGN_EXTENSION_12BIT                0x0800
#define REMOTETEMP2_SIGN_EXTENSION_MASK_12BIT           0xF000

/**
 * @brief Remote Temp 2 Conv_Period register setting.
 * @details Specified setting for Conv_Period register of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_CONV_PERIOD_16S                     0x00
#define REMOTETEMP2_CONV_PERIOD_8S                      0x01
#define REMOTETEMP2_CONV_PERIOD_4S                      0x02
#define REMOTETEMP2_CONV_PERIOD_2S                      0x03
#define REMOTETEMP2_CONV_PERIOD_1S                      0x04
#define REMOTETEMP2_CONV_PERIOD_500MS                   0x05
#define REMOTETEMP2_CONV_PERIOD_250MS                   0x06
#define REMOTETEMP2_CONV_PERIOD_125MS                   0x07
#define REMOTETEMP2_CONV_PERIOD_62MS5                   0x08

/**
 * @brief Remote Temp 2 Filter_Control register setting.
 * @details Specified setting for Filter_Control register of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_FILTER_DISABLE                      0x00
#define REMOTETEMP2_FILTER_LEVEL_1                      0x01
#define REMOTETEMP2_FILTER_LEVEL_2                      0x03

/**
 * @brief Remote Temp 2 pin state setting.
 * @details Specified setting for pin state of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_PIN_STATE_HIGH                      0x01
#define REMOTETEMP2_PIN_STATE_LOW                       0x00

/**
 * @brief Remote Temp 2 chip and vendor ID setting.
 * @details Specified setting for chip and vendor ID of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_CHIP_ID                             0x21
#define REMOTETEMP2_VENDOR_ID                           0x60

/**
 * @brief Remote Temp 2 remote temperature calculation constant setting.
 * @details Specified setting for remote temperature calculation constant of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_TEMP_REMOTE_LSB                     0.0625f
#define REMOTETEMP2_TEMP_LOCAL_LSB                      1.0f

/**
 * @brief Remote Temp 2 byte mask setting.
 * @details Specified setting for byte mask of Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_BYTE_MASK                           0xFF
#define REMOTETEMP2_BYTE_MASK_4BIT                      0x0F

/**
 * @brief Remote Temp 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Remote Temp 2 Click driver.
 */
#define REMOTETEMP2_DEVICE_ADDRESS                      0x4D

/*! @} */ // remotetemp2_set

/**
 * @defgroup remotetemp2_map Remote Temp 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Remote Temp 2 Click driver.
 */

/**
 * @addtogroup remotetemp2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Remote Temp 2 Click to the selected MikroBUS.
 */
#define REMOTETEMP2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.tcr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // remotetemp2_map
/*! @} */ // remotetemp2

/**
 * @brief Remote Temp 2 Click context object.
 * @details Context object definition of Remote Temp 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t alr;                           /**< Temperature alert pin (active low). */
    digital_in_t tcr;                           /**< Critical temperature alert pin (active low). */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} remotetemp2_t;

/**
 * @brief Remote Temp 2 Click configuration object.
 * @details Configuration object definition of Remote Temp 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t alr;                             /**< Temperature alert pin (active low). */
    pin_name_t tcr;                             /**< Critical temperature alert pin (active low). */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} remotetemp2_cfg_t;

/**
 * @brief Remote Temp 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    REMOTETEMP2_OK = 0,
    REMOTETEMP2_ERROR = -1

} remotetemp2_return_value_t;

/*!
 * @addtogroup remotetemp2 Remote Temp 2 Click Driver
 * @brief API for configuring and manipulating Remote Temp 2 Click driver.
 * @{
 */

/**
 * @brief Remote Temp 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #remotetemp2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void remotetemp2_cfg_setup ( remotetemp2_cfg_t *cfg );

/**
 * @brief Remote Temp 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #remotetemp2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_init ( remotetemp2_t *ctx, remotetemp2_cfg_t *cfg );

/**
 * @brief Remote Temp 2 default configuration function.
 * @details This function executes a default configuration of Remote Temp 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t remotetemp2_default_cfg ( remotetemp2_t *ctx );

/**
 * @brief Remote Temp 2 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_write_reg ( remotetemp2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Remote Temp 2 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_write_regs ( remotetemp2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Remote Temp 2 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_read_reg ( remotetemp2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Remote Temp 2 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_read_regs ( remotetemp2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Remote Temp 2 get alert pin function.
 * @details This function returns the logic state of the ALR pin.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @return ALR pin logic state.
 * @note None.
 */
uint8_t remotetemp2_get_alr_pin ( remotetemp2_t *ctx );

/**
 * @brief Remote Temp 2 get critical temperature alert pin function.
 * @details This function returns the logic state of the TCR pin.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @return TCR pin logic state.
 * @note None.
 */
uint8_t remotetemp2_get_tcr_pin ( remotetemp2_t *ctx );

/**
 * @brief Remote Temp 2 read local temperature function.
 * @details This function reads the local sensor temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to local temperature value in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_read_local_temp ( remotetemp2_t *ctx, int8_t *temperature );

/**
 * @brief Remote Temp 2 read temperature channel 1 function.
 * @details This function reads the remote channel 1 temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to remote channel 1 temperature value in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_read_temp_ch1 ( remotetemp2_t *ctx, float *temperature );

/**
 * @brief Remote Temp 2 read temperature channel 2 function.
 * @details This function reads the remote channel 2 temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to remote channel 2 temperature value in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_read_temp_ch2 ( remotetemp2_t *ctx, float *temperature );

/**
 * @brief Remote Temp 2 set temperature high local function.
 * @details This function sets the local temperature high alert limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] max_temperature : High limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_set_thigh_local ( remotetemp2_t *ctx, int8_t max_temperature );

/**
 * @brief Remote Temp 2 set temperature low local function.
 * @details This function sets the local temperature low alert limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] min_temperature : Low limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_set_tlow_local ( remotetemp2_t *ctx, int8_t min_temperature );

/**
 * @brief Remote Temp 2 set temperature high channel 1 function.
 * @details This function sets the remote channel 1 temperature high alert limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] max_temperature : High limit temperature in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_set_thigh_ch1 ( remotetemp2_t *ctx, float max_temperature );

/**
 * @brief Remote Temp 2 set temperature low channel 1 function.
 * @details This function sets the remote channel 1 temperature low alert limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] min_temperature : Low limit temperature in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_set_tlow_ch1 ( remotetemp2_t *ctx, float min_temperature );

/**
 * @brief Remote Temp 2 set temperature high channel 2 function.
 * @details This function sets the remote channel 2 temperature high alert limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] max_temperature : High limit temperature in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_set_thigh_ch2 ( remotetemp2_t *ctx, float max_temperature );

/**
 * @brief Remote Temp 2 set temperature low channel 2 function.
 * @details This function sets the remote channel 2 temperature low alert limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] min_temperature : Low limit temperature in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_set_tlow_ch2 ( remotetemp2_t *ctx, float min_temperature );

/**
 * @brief Remote Temp 2 set temperature critical local function.
 * @details This function sets the local channel critical temperature limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] max_temperature : Critical limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_set_tcrit_local ( remotetemp2_t *ctx, int8_t max_temperature );

/**
 * @brief Remote Temp 2 set temperature critical channel 1 function.
 * @details This function sets the remote channel 1 critical temperature limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] max_temperature : Critical limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_set_tcrit_ch1 ( remotetemp2_t *ctx, int8_t max_temperature );

/**
 * @brief Remote Temp 2 set temperature critical channel 2 function.
 * @details This function sets the remote channel 2 critical temperature limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] max_temperature : Critical limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_set_tcrit_ch2 ( remotetemp2_t *ctx, int8_t max_temperature );

/**
 * @brief Remote Temp 2 get status function.
 * @details This function reads the status register of the device.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[out] status : Pointer to the stored status register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_get_status ( remotetemp2_t *ctx, uint8_t *status );

/**
 * @brief Remote Temp 2 get diode fault function.
 * @details This function reads the diode fault register of the device.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[out] fault : Pointer to the stored diode fault register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp2_get_diode_fault ( remotetemp2_t *ctx, uint8_t *fault );

#ifdef __cplusplus
}
#endif
#endif // REMOTETEMP2_H

/*! @} */ // remotetemp2

// ------------------------------------------------------------------------ END
