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
 * @file remotetemp3.h
 * @brief This file contains API for Remote Temp 3 Click Driver.
 */

#ifndef REMOTETEMP3_H
#define REMOTETEMP3_H

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
 * @addtogroup remotetemp3 Remote Temp 3 Click Driver
 * @brief API for configuring and manipulating Remote Temp 3 Click driver.
 * @{
 */

/**
 * @defgroup remotetemp3_reg Remote Temp 3 Registers List
 * @brief List of registers of Remote Temp 3 Click driver.
 */

/**
 * @addtogroup remotetemp3_reg
 * @{
 */

/**
 * @brief Remote Temp 3 register list.
 * @details Specified register list of Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_REG_TEMP_LOCAL_HIGH             0x00
#define REMOTETEMP3_REG_TEMP_REMOTE_HIGH            0x01
#define REMOTETEMP3_REG_STATUS                      0x02
#define REMOTETEMP3_REG_CONFIGURATION_R             0x03
#define REMOTETEMP3_REG_CONFIGURATION_W             0x09
#define REMOTETEMP3_REG_CONV_RATE_R                 0x04
#define REMOTETEMP3_REG_CONV_RATE_W                 0x0A
#define REMOTETEMP3_REG_THIGH_LIMIT_LOCAL_R         0x05
#define REMOTETEMP3_REG_THIGH_LIMIT_LOCAL_W         0x0B
#define REMOTETEMP3_REG_TLOW_LIMIT_LOCAL_R          0x06
#define REMOTETEMP3_REG_TLOW_LIMIT_LOCAL_W          0x0C
#define REMOTETEMP3_REG_THIGH_LIMIT_REMOTE_HIGH_R   0x07
#define REMOTETEMP3_REG_THIGH_LIMIT_REMOTE_HIGH_W   0x0D
#define REMOTETEMP3_REG_TLOW_LIMIT_REMOTE_HIGH_R    0x08
#define REMOTETEMP3_REG_TLOW_LIMIT_REMOTE_HIGH_W    0x0E
#define REMOTETEMP3_REG_ONE_SHOT_W                  0x0F
#define REMOTETEMP3_REG_TEMP_REMOTE_LOW             0x10
#define REMOTETEMP3_REG_REMOTE_OFFSET_HIGH          0x11
#define REMOTETEMP3_REG_REMOTE_OFFSET_LOW           0x12
#define REMOTETEMP3_REG_THIGH_LIMIT_REMOTE_LOW      0x13
#define REMOTETEMP3_REG_TLOW_LIMIT_REMOTE_LOW       0x14
#define REMOTETEMP3_REG_TEMP_LOCAL_LOW              0x15
#define REMOTETEMP3_REG_CHANNEL_ENABLE              0x16
#define REMOTETEMP3_REG_THERM_LIMIT_REMOTE          0x19
#define REMOTETEMP3_REG_THERM_LIMIT_LOCAL           0x20
#define REMOTETEMP3_REG_THERM_HYSTERESIS            0x21
#define REMOTETEMP3_REG_CONSEC_ALERT                0x22
#define REMOTETEMP3_REG_ETA_FACTOR                  0x23
#define REMOTETEMP3_REG_DIGITAL_FILTER              0x24
#define REMOTETEMP3_REG_MANUFACTURER_ID             0xFE

/*! @} */ // remotetemp3_reg

/**
 * @defgroup remotetemp3_set Remote Temp 3 Registers Settings
 * @brief Settings for registers of Remote Temp 3 Click driver.
 */

/**
 * @addtogroup remotetemp3_set
 * @{
 */

/**
 * @brief Remote Temp 3 configuration register setting.
 * @details Specified setting for configuration register of Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_CFG_ALERT_MASK                  0x80
#define REMOTETEMP3_CFG_SHUTDOWN_MODE               0x40
#define REMOTETEMP3_CFG_CONTINUOUS_MODE             0x00
#define REMOTETEMP3_CFG_THERM2_MODE                 0x20
#define REMOTETEMP3_CFG_ALERT_MODE                  0x00
#define REMOTETEMP3_CFG_EXTENDED_RANGE              0x04
#define REMOTETEMP3_CFG_STANDARD_RANGE              0x00

/**
 * @brief Remote Temp 3 status register setting.
 * @details Specified setting for status register of Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_STATUS_BUSY                     0x80
#define REMOTETEMP3_STATUS_LHIGH                    0x40
#define REMOTETEMP3_STATUS_LLOW                     0x20
#define REMOTETEMP3_STATUS_RHIGH                    0x10
#define REMOTETEMP3_STATUS_RLOW                     0x08
#define REMOTETEMP3_STATUS_OPEN                     0x04
#define REMOTETEMP3_STATUS_RTHRM                    0x02
#define REMOTETEMP3_STATUS_LTHRM                    0x01

/**
 * @brief Remote Temp 3 channel enable register setting.
 * @details Specified setting for channel enable register of Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_CHANNEL_ENABLE_BOTH             0x03
#define REMOTETEMP3_CHANNEL_ENABLE_LOCAL_ONLY       0x01
#define REMOTETEMP3_CHANNEL_ENABLE_REMOTE_ONLY      0x02

/**
 * @brief Remote Temp 3 conversion rate register setting.
 * @details Specified setting for conversion rate register of Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_CONV_RATE_0_0625_CPS            0x00
#define REMOTETEMP3_CONV_RATE_0_125_CPS             0x01
#define REMOTETEMP3_CONV_RATE_0_25_CPS              0x02
#define REMOTETEMP3_CONV_RATE_0_5_CPS               0x03
#define REMOTETEMP3_CONV_RATE_1_CPS                 0x04
#define REMOTETEMP3_CONV_RATE_2_CPS                 0x05
#define REMOTETEMP3_CONV_RATE_4_CPS                 0x06
#define REMOTETEMP3_CONV_RATE_8_CPS                 0x07
#define REMOTETEMP3_CONV_RATE_16_CPS                0x08
#define REMOTETEMP3_CONV_RATE_32_CPS                0x09

/**
 * @brief Remote Temp 3 digital filter control register setting.
 * @details Specified setting for digital filter control register of Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_FILTER_DISABLE                  0x00
#define REMOTETEMP3_FILTER_LEVEL_1                  0x01
#define REMOTETEMP3_FILTER_LEVEL_2                  0x02

/**
 * @brief Remote Temp 3 THERM hysteresis register setting.
 * @details Specified setting for THERM hysteresis register of Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_HYSTERESIS_1_DEG_C              0x01

/**
 * @brief Remote Temp 3 temperature limits setting.
 * @details Specified setting for temperature limits of Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_THERM_LIMIT_30_DEG_C            30
#define REMOTETEMP3_LOCAL_HIGH_LIMIT_30_DEG_C       30
#define REMOTETEMP3_LOCAL_LOW_LIMIT_0_DEG_C         0
#define REMOTETEMP3_REMOTE_HIGH_LIMIT_30_DEG_C      30.0f
#define REMOTETEMP3_REMOTE_LOW_LIMIT_0_DEG_C        0.0f

/**
 * @brief Remote Temp 3 12-bit sign extension setting.
 * @details Specified setting for 12-bit sign extension of Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_SIGN_EXTENSION_12BIT            0x0800
#define REMOTETEMP3_SIGN_EXTENSION_MASK_12BIT       0xF000

/**
 * @brief Remote Temp 3 temperature calculation constant setting.
 * @details Specified setting for temperature calculation constant of Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_TEMP_LSB                        0.0625f

/**
 * @brief Remote Temp 3 byte mask setting.
 * @details Specified setting for byte mask of Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_BYTE_MASK                       0xFF
#define REMOTETEMP3_BYTE_MASK_4BIT                  0x0F

/**
 * @brief Remote Temp 3 manufacturer ID setting.
 * @details Specified setting for manufacturer ID of Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_MANUFACTURER_ID                 0x55

/**
 * @brief Remote Temp 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Remote Temp 3 Click driver.
 */
#define REMOTETEMP3_DEVICE_ADDRESS                  0x48

/*! @} */ // remotetemp3_set

/**
 * @defgroup remotetemp3_map Remote Temp 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Remote Temp 3 Click driver.
 */

/**
 * @addtogroup remotetemp3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Remote Temp 3 Click to the selected MikroBUS.
 */
#define REMOTETEMP3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.thm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // remotetemp3_map
/*! @} */ // remotetemp3

/**
 * @brief Remote Temp 3 Click context object.
 * @details Context object definition of Remote Temp 3 Click driver.
 */
typedef struct
{
    digital_in_t thm;                           /**< Thermal shutdown / fan-control pin (active low). */
    digital_in_t alr;                           /**< Temperature alert pin (active low). */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} remotetemp3_t;

/**
 * @brief Remote Temp 3 Click configuration object.
 * @details Configuration object definition of Remote Temp 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t thm;                             /**< Thermal shutdown / fan-control pin (active low). */
    pin_name_t alr;                             /**< Temperature alert pin (active low). */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} remotetemp3_cfg_t;

/**
 * @brief Remote Temp 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    REMOTETEMP3_OK = 0,
    REMOTETEMP3_ERROR = -1

} remotetemp3_return_value_t;

/*!
 * @addtogroup remotetemp3 Remote Temp 3 Click Driver
 * @brief API for configuring and manipulating Remote Temp 3 Click driver.
 * @{
 */

/**
 * @brief Remote Temp 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #remotetemp3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void remotetemp3_cfg_setup ( remotetemp3_cfg_t *cfg );

/**
 * @brief Remote Temp 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #remotetemp3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_init ( remotetemp3_t *ctx, remotetemp3_cfg_t *cfg );

/**
 * @brief Remote Temp 3 default configuration function.
 * @details This function executes a default configuration of Remote Temp 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t remotetemp3_default_cfg ( remotetemp3_t *ctx );

/**
 * @brief Remote Temp 3 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_write_reg ( remotetemp3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Remote Temp 3 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_write_regs ( remotetemp3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Remote Temp 3 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_read_reg ( remotetemp3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Remote Temp 3 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_read_regs ( remotetemp3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Remote Temp 3 get THM pin function.
 * @details This function returns the logic state of the THM pin.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @return THM pin logic state.
 * @note None.
 */
uint8_t remotetemp3_get_thm_pin ( remotetemp3_t *ctx );

/**
 * @brief Remote Temp 3 get ALR pin function.
 * @details This function returns the logic state of the ALR pin.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @return ALR pin logic state.
 * @note None.
 */
uint8_t remotetemp3_get_alr_pin ( remotetemp3_t *ctx );

/**
 * @brief Remote Temp 3 read local temperature function.
 * @details This function reads the local sensor temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to local temperature value in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_read_local_temp ( remotetemp3_t *ctx, float *temperature );

/**
 * @brief Remote Temp 3 read remote temperature function.
 * @details This function reads the remote sensor temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to remote temperature value in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_read_remote_temp ( remotetemp3_t *ctx, float *temperature );

/**
 * @brief Remote Temp 3 set temperature high local function.
 * @details This function sets the local temperature high ALERT limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[in] max_temperature : High limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_set_thigh_local ( remotetemp3_t *ctx, int8_t max_temperature );

/**
 * @brief Remote Temp 3 set temperature low local function.
 * @details This function sets the local temperature low ALERT limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[in] min_temperature : Low limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_set_tlow_local ( remotetemp3_t *ctx, int8_t min_temperature );

/**
 * @brief Remote Temp 3 set temperature high remote function.
 * @details This function sets the remote temperature high ALERT limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[in] max_temperature : High limit temperature in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_set_thigh_remote ( remotetemp3_t *ctx, float max_temperature );

/**
 * @brief Remote Temp 3 set temperature low remote function.
 * @details This function sets the remote temperature low ALERT limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[in] min_temperature : Low limit temperature in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_set_tlow_remote ( remotetemp3_t *ctx, float min_temperature );

/**
 * @brief Remote Temp 3 set THERM local function.
 * @details This function sets the local temperature THERM limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[in] max_temperature : THERM limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_set_therm_local ( remotetemp3_t *ctx, int8_t max_temperature );

/**
 * @brief Remote Temp 3 set THERM remote function.
 * @details This function sets the remote temperature THERM limit.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[in] max_temperature : THERM limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_set_therm_remote ( remotetemp3_t *ctx, int8_t max_temperature );

/**
 * @brief Remote Temp 3 get status function.
 * @details This function reads the status register of the device.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[out] status : Pointer to the stored status register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t remotetemp3_get_status ( remotetemp3_t *ctx, uint8_t *status );

#ifdef __cplusplus
}
#endif
#endif // REMOTETEMP3_H

/*! @} */ // remotetemp3

// ------------------------------------------------------------------------ END
