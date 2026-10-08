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
 * @file remotetemp4.h
 * @brief This file contains API for Remote Temp 4 Click Driver.
 */

#ifndef REMOTETEMP4_H
#define REMOTETEMP4_H

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
 * @addtogroup remotetemp4 Remote Temp 4 Click Driver
 * @brief API for configuring and manipulating Remote Temp 4 Click driver.
 * @{
 */

/**
 * @defgroup remotetemp4_reg Remote Temp 4 Registers List
 * @brief List of registers of Remote Temp 4 Click driver.
 */

/**
 * @addtogroup remotetemp4_reg
 * @{
 */

/**
 * @brief Remote Temp 4 register list.
 * @details Specified register list of Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_REG_TEMP_LOCAL_MSB              0x00
#define REMOTETEMP4_REG_TEMP_REMOTE_MSB             0x01
#define REMOTETEMP4_REG_ALERT_STATUS                0x02
#define REMOTETEMP4_REG_CONFIGURATION               0x03
#define REMOTETEMP4_REG_CONV_RATE                   0x04
#define REMOTETEMP4_REG_THIGH_LIMIT_LOCAL           0x05
#define REMOTETEMP4_REG_THIGH_LIMIT_REMOTE_MSB      0x07
#define REMOTETEMP4_REG_TLOW_LIMIT_REMOTE_MSB       0x08
#define REMOTETEMP4_REG_CONFIGURATION_ALT           0x09
#define REMOTETEMP4_REG_CONV_RATE_ALT               0x0A
#define REMOTETEMP4_REG_THIGH_LIMIT_LOCAL_ALT       0x0B
#define REMOTETEMP4_REG_THIGH_LIMIT_REMOTE_MSB_ALT  0x0D
#define REMOTETEMP4_REG_TLOW_LIMIT_REMOTE_MSB_ALT   0x0E
#define REMOTETEMP4_REG_ONE_SHOT                    0x0F
#define REMOTETEMP4_REG_TEMP_REMOTE_LSB             0x10
#define REMOTETEMP4_REG_REMOTE_OFFSET_MSB           0x11
#define REMOTETEMP4_REG_REMOTE_OFFSET_LSB           0x12
#define REMOTETEMP4_REG_THIGH_LIMIT_REMOTE_LSB      0x13
#define REMOTETEMP4_REG_TLOW_LIMIT_REMOTE_LSB       0x14
#define REMOTETEMP4_REG_TEMP_LOCAL_LSB              0x15
#define REMOTETEMP4_REG_ALERT_MASK                  0x16
#define REMOTETEMP4_REG_THERM_LIMIT_REMOTE          0x19
#define REMOTETEMP4_REG_THERM_LIMIT_LOCAL           0x20
#define REMOTETEMP4_REG_THERM_HYSTERESIS            0x21
#define REMOTETEMP4_REG_ALERT_MODE                  0xBF
#define REMOTETEMP4_REG_CHIP_ID                     0xFD
#define REMOTETEMP4_REG_MANUFACTURER_ID             0xFE
#define REMOTETEMP4_REG_DEVICE_ID                   0xFF

/*! @} */ // remotetemp4_reg

/**
 * @defgroup remotetemp4_set Remote Temp 4 Registers Settings
 * @brief Settings for registers of Remote Temp 4 Click driver.
 */

/**
 * @addtogroup remotetemp4_set
 * @{
 */

/**
 * @brief Remote Temp 4 configuration register setting.
 * @details Specified setting for configuration register of Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_CFG_ALERT_MASK_ENABLE           0x80
#define REMOTETEMP4_CFG_ALERT_MASK_DISABLE          0x00
#define REMOTETEMP4_CFG_STANDBY_MODE                0x40
#define REMOTETEMP4_CFG_CONTINUOUS_MODE             0x00
#define REMOTETEMP4_CFG_RESERVED_BIT                0x20
#define REMOTETEMP4_CFG_REMOTE_MONITOR_ENABLE       0x04
#define REMOTETEMP4_CFG_REMOTE_MONITOR_DISABLE      0x00
#define REMOTETEMP4_CFG_THERM_LIMIT_WRITE_ENABLE    0x02
#define REMOTETEMP4_CFG_THERM_LIMIT_WRITE_DISABLE   0x00
#define REMOTETEMP4_CFG_FAULT_QUEUE_ENABLE          0x01
#define REMOTETEMP4_CFG_FAULT_QUEUE_DISABLE         0x00

/**
 * @brief Remote Temp 4 alert status register setting.
 * @details Specified setting for alert status register of Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_STATUS_ADC_BUSY                 0x80
#define REMOTETEMP4_STATUS_LOCAL_HIGH               0x40
#define REMOTETEMP4_STATUS_REMOTE_HIGH              0x10
#define REMOTETEMP4_STATUS_REMOTE_LOW               0x08
#define REMOTETEMP4_STATUS_REMOTE_OPEN              0x04
#define REMOTETEMP4_STATUS_REMOTE_THERM             0x02
#define REMOTETEMP4_STATUS_LOCAL_THERM              0x01

/**
 * @brief Remote Temp 4 alert mask register setting.
 * @details Specified setting for alert mask register of Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_ALERT_MASK_LOCAL_HIGH           0x80
#define REMOTETEMP4_ALERT_MASK_REMOTE_HIGH          0x10
#define REMOTETEMP4_ALERT_MASK_REMOTE_LOW           0x08
#define REMOTETEMP4_ALERT_MASK_RESERVED_BITS        0x03
#define REMOTETEMP4_ALERT_MASK_NONE                 0x03

/**
 * @brief Remote Temp 4 conversion rate register setting.
 * @details Specified setting for conversion rate register of Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_CONV_RATE_0_0625_CPS            0x00
#define REMOTETEMP4_CONV_RATE_0_125_CPS             0x01
#define REMOTETEMP4_CONV_RATE_0_25_CPS              0x02
#define REMOTETEMP4_CONV_RATE_0_5_CPS               0x03
#define REMOTETEMP4_CONV_RATE_1_CPS                 0x04
#define REMOTETEMP4_CONV_RATE_2_CPS                 0x05
#define REMOTETEMP4_CONV_RATE_4_CPS                 0x06
#define REMOTETEMP4_CONV_RATE_8_CPS                 0x07
#define REMOTETEMP4_CONV_RATE_16_CPS                0x08
#define REMOTETEMP4_CONV_RATE_13_7_CPS              0x0B
#define REMOTETEMP4_CONV_RATE_MASK                  0x0F

/**
 * @brief Remote Temp 4 alert mode register setting.
 * @details Specified setting for alert mode register of Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_ALERT_MODE_INTERRUPT            0x00
#define REMOTETEMP4_ALERT_MODE_COMPARATOR           0x01

/**
 * @brief Remote Temp 4 THERM hysteresis register setting.
 * @details Specified setting for THERM hysteresis register of Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_HYSTERESIS_1_DEG_C              0x01
#define REMOTETEMP4_HYSTERESIS_MAX_DEG_C            31
#define REMOTETEMP4_HYSTERESIS_MASK                 0x1F

/**
 * @brief Remote Temp 4 temperature limits setting.
 * @details Specified setting for temperature limits of Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_THERM_LIMIT_30_DEG_C            30
#define REMOTETEMP4_LOCAL_HIGH_LIMIT_30_DEG_C       30
#define REMOTETEMP4_REMOTE_HIGH_LIMIT_30_DEG_C      30.0f
#define REMOTETEMP4_REMOTE_LOW_LIMIT_0_DEG_C        0.0f

/**
 * @brief Remote Temp 4 11-bit sign extension setting.
 * @details Specified setting for 11-bit sign extension of Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_SIGN_EXTENSION_11BIT            0x0400
#define REMOTETEMP4_SIGN_EXTENSION_MASK_11BIT       0xF800

/**
 * @brief Remote Temp 4 temperature calculation constant setting.
 * @details Specified setting for temperature calculation constant of Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_TEMP_LSB                        0.125f

/**
 * @brief Remote Temp 4 byte mask setting.
 * @details Specified setting for byte mask of Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_BYTE_MASK                       0xFF
#define REMOTETEMP4_BYTE_MASK_3BIT                  0x07

/**
 * @brief Remote Temp 4 device ID setting.
 * @details Specified setting for device ID of Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_CHIP_ID                         0x50
#define REMOTETEMP4_MANUFACTURER_ID                 0x59
#define REMOTETEMP4_DEVICE_ID                       0x8D

/**
 * @brief Remote Temp 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Remote Temp 4 Click driver.
 */
#define REMOTETEMP4_DEVICE_ADDRESS                  0x4D

/*! @} */ // remotetemp4_set

/**
 * @defgroup remotetemp4_map Remote Temp 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Remote Temp 4 Click driver.
 */

/**
 * @addtogroup remotetemp4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Remote Temp 4 Click to the selected MikroBUS.
 */
#define REMOTETEMP4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.thm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // remotetemp4_map
/*! @} */ // remotetemp4

/**
 * @brief Remote Temp 4 Click context object.
 * @details Context object definition of Remote Temp 4 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t thm;                           /**< THERM temperature alarm pin (active low). */
    digital_in_t alr;                           /**< ALERT temperature alarm pin (active low). */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} remotetemp4_t;

/**
 * @brief Remote Temp 4 Click configuration object.
 * @details Configuration object definition of Remote Temp 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t thm;                             /**< THERM temperature alarm pin descriptor. */
    pin_name_t alr;                             /**< ALERT temperature alarm pin descriptor. */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} remotetemp4_cfg_t;

/**
 * @brief Remote Temp 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    REMOTETEMP4_OK = 0,
    REMOTETEMP4_ERROR = -1

} remotetemp4_return_value_t;

/*!
 * @addtogroup remotetemp4 Remote Temp 4 Click Driver
 * @brief API for configuring and manipulating Remote Temp 4 Click driver.
 * @{
 */

/**
 * @brief Remote Temp 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #remotetemp4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void remotetemp4_cfg_setup ( remotetemp4_cfg_t *cfg );

/**
 * @brief Remote Temp 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #remotetemp4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_init ( remotetemp4_t *ctx, remotetemp4_cfg_t *cfg );

/**
 * @brief Remote Temp 4 default configuration function.
 * @details This function executes a default configuration of Remote Temp 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t remotetemp4_default_cfg ( remotetemp4_t *ctx );

/**
 * @brief Remote Temp 4 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_write_reg ( remotetemp4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Remote Temp 4 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_write_regs ( remotetemp4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Remote Temp 4 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_read_reg ( remotetemp4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Remote Temp 4 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_read_regs ( remotetemp4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Remote Temp 4 check communication function.
 * @details This function checks the communication by reading and verifying the
 * chip, manufacturer and device identification registers.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_check_communication ( remotetemp4_t *ctx );

/**
 * @brief Remote Temp 4 get THM pin function.
 * @details This function returns the logic state of the THM pin.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @return THM pin logic state.
 * @note None.
 */
uint8_t remotetemp4_get_thm_pin ( remotetemp4_t *ctx );

/**
 * @brief Remote Temp 4 get ALR pin function.
 * @details This function returns the logic state of the ALR pin.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @return ALR pin logic state.
 * @note None.
 */
uint8_t remotetemp4_get_alr_pin ( remotetemp4_t *ctx );

/**
 * @brief Remote Temp 4 read local temperature function.
 * @details This function reads the local sensor temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to local temperature value in degrees Celsius (0.125 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_read_local_temp ( remotetemp4_t *ctx, float *temperature );

/**
 * @brief Remote Temp 4 read remote temperature function.
 * @details This function reads the remote sensor temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to remote temperature value in degrees Celsius (0.125 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_read_remote_temp ( remotetemp4_t *ctx, float *temperature );

/**
 * @brief Remote Temp 4 set conversion rate function.
 * @details This function sets the ADC conversion rate.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] conv_rate : Conversion rate [0x00-0x0B].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_set_conv_rate ( remotetemp4_t *ctx, uint8_t conv_rate );

/**
 * @brief Remote Temp 4 set temperature high local function.
 * @details This function sets the local temperature high ALERT limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] max_temperature : High limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_set_thigh_local ( remotetemp4_t *ctx, int8_t max_temperature );

/**
 * @brief Remote Temp 4 set temperature high remote function.
 * @details This function sets the remote temperature high ALERT limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] max_temperature : High limit temperature in degrees Celsius (0.125 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_set_thigh_remote ( remotetemp4_t *ctx, float max_temperature );

/**
 * @brief Remote Temp 4 set temperature low remote function.
 * @details This function sets the remote temperature low ALERT limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] min_temperature : Low limit temperature in degrees Celsius (0.125 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_set_tlow_remote ( remotetemp4_t *ctx, float min_temperature );

/**
 * @brief Remote Temp 4 set THERM local function.
 * @details This function sets the local temperature THERM limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] max_temperature : THERM limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The THERM limit registers are write protected until the THERM limit write
 * enable bit of the configuration register (0x03) is set.
 */
err_t remotetemp4_set_therm_local ( remotetemp4_t *ctx, int8_t max_temperature );

/**
 * @brief Remote Temp 4 set THERM remote function.
 * @details This function sets the remote temperature THERM limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] max_temperature : THERM limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The THERM limit registers are write protected until the THERM limit write
 * enable bit of the configuration register (0x03) is set.
 */
err_t remotetemp4_set_therm_remote ( remotetemp4_t *ctx, int8_t max_temperature );

/**
 * @brief Remote Temp 4 set THERM hysteresis function.
 * @details This function sets the THERM hysteresis window applied to both channels.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] hysteresis : Hysteresis window in degrees Celsius [0-32].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_set_therm_hyst ( remotetemp4_t *ctx, uint8_t hysteresis );

/**
 * @brief Remote Temp 4 get status function.
 * @details This function reads the alert status register of the device.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[out] status : Pointer to the stored alert status register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp4_get_status ( remotetemp4_t *ctx, uint8_t *status );

#ifdef __cplusplus
}
#endif
#endif // REMOTETEMP4_H

/*! @} */ // remotetemp4

// ------------------------------------------------------------------------ END
