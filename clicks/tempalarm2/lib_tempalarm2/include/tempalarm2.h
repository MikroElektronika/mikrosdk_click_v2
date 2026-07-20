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
 * @file tempalarm2.h
 * @brief This file contains API for Temp Alarm 2 Click Driver.
 */

#ifndef TEMPALARM2_H
#define TEMPALARM2_H

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
 * @addtogroup tempalarm2 Temp Alarm 2 Click Driver
 * @brief API for configuring and manipulating Temp Alarm 2 Click driver.
 * @{
 */

/**
 * @defgroup tempalarm2_reg Temp Alarm 2 Registers List
 * @brief List of registers of Temp Alarm 2 Click driver.
 */

/**
 * @addtogroup tempalarm2_reg
 * @{
 */

/**
 * @brief Temp Alarm 2 register list.
 * @details Specified register list of Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_REG_TEMP_LOCAL_HIGH              0x00
#define TEMPALARM2_REG_TEMP_REMOTE_HIGH             0x01
#define TEMPALARM2_REG_STATUS                       0x02
#define TEMPALARM2_REG_CONFIGURATION_R              0x03
#define TEMPALARM2_REG_CONFIGURATION_W              0x09
#define TEMPALARM2_REG_CONV_RATE_R                  0x04
#define TEMPALARM2_REG_CONV_RATE_W                  0x0A
#define TEMPALARM2_REG_THIGH_LIMIT_LOCAL_R          0x05
#define TEMPALARM2_REG_THIGH_LIMIT_LOCAL_W          0x0B
#define TEMPALARM2_REG_TLOW_LIMIT_LOCAL_R           0x06
#define TEMPALARM2_REG_TLOW_LIMIT_LOCAL_W           0x0C
#define TEMPALARM2_REG_THIGH_LIMIT_REMOTE_HIGH_R    0x07
#define TEMPALARM2_REG_THIGH_LIMIT_REMOTE_HIGH_W    0x0D
#define TEMPALARM2_REG_TLOW_LIMIT_REMOTE_HIGH_R     0x08
#define TEMPALARM2_REG_TLOW_LIMIT_REMOTE_HIGH_W     0x0E
#define TEMPALARM2_REG_ONE_SHOT_W                   0x0F
#define TEMPALARM2_REG_TEMP_REMOTE_LOW              0x10
#define TEMPALARM2_REG_REMOTE_OFFSET_HIGH           0x11
#define TEMPALARM2_REG_REMOTE_OFFSET_LOW            0x12
#define TEMPALARM2_REG_THIGH_LIMIT_REMOTE_LOW       0x13
#define TEMPALARM2_REG_TLOW_LIMIT_REMOTE_LOW        0x14
#define TEMPALARM2_REG_TEMP_LOCAL_LOW               0x15
#define TEMPALARM2_REG_THIGH_LIMIT_LOCAL_LOW        0x16
#define TEMPALARM2_REG_TLOW_LIMIT_LOCAL_LOW         0x17
#define TEMPALARM2_REG_N_FACTOR_CORRECTION          0x18
#define TEMPALARM2_REG_THERM_LIMIT_REMOTE           0x19
#define TEMPALARM2_REG_THERM_LIMIT_LOCAL            0x20
#define TEMPALARM2_REG_THERM_HYSTERESIS             0x21
#define TEMPALARM2_REG_CONSEC_ALERT                 0x22
#define TEMPALARM2_REG_RESOLUTION                   0x1A
#define TEMPALARM2_REG_SOFTWARE_RESET_W             0xFC
#define TEMPALARM2_REG_MANUFACTURER_ID              0xFE
#define TEMPALARM2_REG_DEVICE_ID                    0xFF

/*! @} */ // tempalarm2_reg

/**
 * @defgroup tempalarm2_set Temp Alarm 2 Registers Settings
 * @brief Settings for registers of Temp Alarm 2 Click driver.
 */

/**
 * @addtogroup tempalarm2_set
 * @{
 */

/**
 * @brief Temp Alarm 2 configuration register setting.
 * @details Specified setting for configuration register of Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_CFG_ALERT_MASK                   0x80
#define TEMPALARM2_CFG_SHUTDOWN_MODE                0x40
#define TEMPALARM2_CFG_CONTINUOUS_MODE              0x00
#define TEMPALARM2_CFG_THERM2_MODE                  0x20
#define TEMPALARM2_CFG_ALERT_MODE                   0x00
#define TEMPALARM2_CFG_EXTENDED_RANGE               0x04
#define TEMPALARM2_CFG_STANDARD_RANGE               0x00

/**
 * @brief Temp Alarm 2 status register setting.
 * @details Specified setting for status register of Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_STATUS_BUSY                      0x80
#define TEMPALARM2_STATUS_LHIGH                     0x40
#define TEMPALARM2_STATUS_LLOW                      0x20
#define TEMPALARM2_STATUS_RHIGH                     0x10
#define TEMPALARM2_STATUS_RLOW                      0x08
#define TEMPALARM2_STATUS_OPEN                      0x04
#define TEMPALARM2_STATUS_RTHRM                     0x02
#define TEMPALARM2_STATUS_LTHRM                     0x01

/**
 * @brief Temp Alarm 2 software reset register setting.
 * @details Specified setting for software reset register of Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_SW_RESET_DUMMY                   0x00 

/**
 * @brief Temp Alarm 2 conversion rate register setting.
 * @details Specified setting for conversion rate register of Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_CONV_RATE_0_0625_CPS             0x00
#define TEMPALARM2_CONV_RATE_0_125_CPS              0x01
#define TEMPALARM2_CONV_RATE_0_25_CPS               0x02
#define TEMPALARM2_CONV_RATE_0_5_CPS                0x03
#define TEMPALARM2_CONV_RATE_1_CPS                  0x04
#define TEMPALARM2_CONV_RATE_2_CPS                  0x05
#define TEMPALARM2_CONV_RATE_4_CPS                  0x06
#define TEMPALARM2_CONV_RATE_8_CPS                  0x07

/**
 * @brief Temp Alarm 2 resolution register setting.
 * @details Specified setting for resolution register of Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_RESOLUTION_9BIT                  0x1C
#define TEMPALARM2_RESOLUTION_10BIT                 0x1D
#define TEMPALARM2_RESOLUTION_11BIT                 0x1E
#define TEMPALARM2_RESOLUTION_12BIT                 0x1F

/**
 * @brief Temp Alarm 2 THERM hysteresis register setting.
 * @details Specified setting for THERM hysteresis register of Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_HYSTERESIS_1_DEG_C               0x01

/**
 * @brief Temp Alarm 2 temperature limits setting.
 * @details Specified setting for temperature limits of Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_THERM_LIMIT_30_DEG_C             30
#define TEMPALARM2_LOCAL_HIGH_LIMIT_30_DEG_C        30
#define TEMPALARM2_LOCAL_HIGH_LIMIT_28_DEG_C        28
#define TEMPALARM2_LOCAL_LOW_LIMIT_0_DEG_C          0
#define TEMPALARM2_LOCAL_LOW_LIMIT_5_DEG_C          5
#define TEMPALARM2_REMOTE_HIGH_LIMIT_30_DEG_C       30.0f
#define TEMPALARM2_REMOTE_HIGH_LIMIT_28_DEG_C       28.0f
#define TEMPALARM2_REMOTE_LOW_LIMIT_0_DEG_C         0.0f
#define TEMPALARM2_REMOTE_LOW_LIMIT_5_DEG_C         5.0f

/**
 * @brief Temp Alarm 2 temperature calculation constant setting.
 * @details Specified setting for temperature calculation constant of Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_TEMP_LSB                         0.0625f

/**
 * @brief Temp Alarm 2 byte mask setting.
 * @details Specified setting for byte mask of Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_BYTE_MASK                        0xFF
#define TEMPALARM2_BYTE_MASK_4BIT                   0x0F

/**
 * @brief Temp Alarm 2 manufacturer and device ID setting.
 * @details Specified setting for manufacturer and device ID of Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_MANUFACTURER_ID                  0x55
#define TEMPALARM2_DEVICE_ID                        0x13

/**
 * @brief Temp Alarm 2 SMBus Alert Response Address setting.
 * @details Specified setting for SMBus Alert Response Address of Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_SMBUS_ALERT_RESPONSE_ADDR        0x0C

/**
 * @brief Temp Alarm 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Temp Alarm 2 Click driver.
 */
#define TEMPALARM2_DEVICE_ADDRESS                   0x4D

/*! @} */ // tempalarm2_set

/**
 * @defgroup tempalarm2_map Temp Alarm 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Temp Alarm 2 Click driver.
 */

/**
 * @addtogroup tempalarm2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Temp Alarm 2 Click to the selected MikroBUS.
 */
#define TEMPALARM2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // tempalarm2_map
/*! @} */ // tempalarm2

/**
 * @brief Temp Alarm 2 Click context object.
 * @details Context object definition of Temp Alarm 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t alt;                           /**< Alert pin (active low). */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} tempalarm2_t;

/**
 * @brief Temp Alarm 2 Click configuration object.
 * @details Configuration object definition of Temp Alarm 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t alt;                             /**< Alert pin (active low). */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} tempalarm2_cfg_t;

/**
 * @brief Temp Alarm 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPALARM2_OK = 0,
    TEMPALARM2_ERROR = -1

} tempalarm2_return_value_t;

/*!
 * @addtogroup tempalarm2 Temp Alarm 2 Click Driver
 * @brief API for configuring and manipulating Temp Alarm 2 Click driver.
 * @{
 */

/**
 * @brief Temp Alarm 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tempalarm2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tempalarm2_cfg_setup ( tempalarm2_cfg_t *cfg );

/**
 * @brief Temp Alarm 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tempalarm2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_init ( tempalarm2_t *ctx, tempalarm2_cfg_t *cfg );

/**
 * @brief Temp Alarm 2 default configuration function.
 * @details This function executes a default configuration of Temp Alarm 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t tempalarm2_default_cfg ( tempalarm2_t *ctx );

/**
 * @brief Temp Alarm 2 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_write_reg ( tempalarm2_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Temp Alarm 2 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_write_regs ( tempalarm2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Temp Alarm 2 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_read_reg ( tempalarm2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Temp Alarm 2 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_read_regs ( tempalarm2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Temp Alarm 2 get ALT pin function.
 * @details This function returns the logic state of the ALT pin.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @return ALT pin logic state.
 * @note None.
 */
uint8_t tempalarm2_get_alt_pin ( tempalarm2_t *ctx );

/**
 * @brief Temp Alarm 2 software reset function.
 * @details This function performs a software reset by writing to the software
 * reset register (0xFC).
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_sw_reset ( tempalarm2_t *ctx );

/**
 * @brief Temp Alarm 2 read local temperature function.
 * @details This function reads the local sensor temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to local temperature value in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_read_local_temp ( tempalarm2_t *ctx, float *temperature );

/**
 * @brief Temp Alarm 2 read remote temperature function.
 * @details This function reads the remote sensor temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to remote temperature value in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_read_remote_temp ( tempalarm2_t *ctx, float *temperature );

/**
 * @brief Temp Alarm 2 set temperature high local function.
 * @details This function sets the local channel high ALERT temperature limit.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[in] max_temperature : High limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_set_thigh_local ( tempalarm2_t *ctx, uint8_t max_temperature );

/**
 * @brief Temp Alarm 2 set temperature low local function.
 * @details This function sets the local channel low ALERT temperature limit.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[in] min_temperature : Low limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_set_tlow_local ( tempalarm2_t *ctx, uint8_t min_temperature );

/**
 * @brief Temp Alarm 2 set temperature high remote function.
 * @details This function sets the remote channel high ALERT temperature limit.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[in] max_temperature : High limit temperature in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_set_thigh_remote ( tempalarm2_t *ctx, float max_temperature );

/**
 * @brief Temp Alarm 2 set temperature low remote function.
 * @details This function sets the remote channel low ALERT temperature limit.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[in] min_temperature : Low limit temperature in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_set_tlow_remote ( tempalarm2_t *ctx, float min_temperature );

/**
 * @brief Temp Alarm 2 set THERM local function.
 * @details This function sets the local channel THERM temperature limit.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[in] max_temperature : THERM limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_set_therm_local ( tempalarm2_t *ctx, uint8_t max_temperature );

/**
 * @brief Temp Alarm 2 set THERM remote function.
 * @details This function sets the remote channel THERM temperature limit.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[in] max_temperature : THERM limit temperature in degrees Celsius (1 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_set_therm_remote ( tempalarm2_t *ctx, uint8_t max_temperature );

/**
 * @brief Temp Alarm 2 get status function.
 * @details This function reads the status register of the device.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[out] status : Pointer to the stored status register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_get_status ( tempalarm2_t *ctx, uint8_t *status );

/**
 * @brief Temp Alarm 2 clear alert function.
 * @details This function performs the SMBus Alert Response Address (ARA) command 
 * to reset the ALERT pin.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm2_clear_alert ( tempalarm2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // TEMPALARM2_H

/*! @} */ // tempalarm2

// ------------------------------------------------------------------------ END
