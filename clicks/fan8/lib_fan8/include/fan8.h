/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file fan8.h
 * @brief This file contains API for FAN 8 Click Driver.
 */

#ifndef FAN8_H
#define FAN8_H

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
 * @addtogroup fan8 FAN 8 Click Driver
 * @brief API for configuring and manipulating FAN 8 Click driver.
 * @{
 */

/**
 * @defgroup fan8_reg FAN 8 Registers List
 * @brief List of registers of FAN 8 Click driver.
 */

/**
 * @addtogroup fan8_reg
 * @{
 */

/**
 * @brief FAN 8 Register Map.
 * @details Specified register map of FAN 8 Click driver.
 */
#define FAN8_REG_TEMP_CH1                       0x00
#define FAN8_REG_TEMP_CH2                       0x01
#define FAN8_REG_CONFIG_BYTE                    0x02
#define FAN8_REG_CH1_OT_LIMIT                   0x03
#define FAN8_REG_CH2_OT_LIMIT                   0x04
#define FAN8_REG_OT_STATUS                      0x05
#define FAN8_REG_OT_MASK                        0x06
#define FAN8_REG_PWM1_START_DC                  0x07
#define FAN8_REG_PWM2_START_DC                  0x08
#define FAN8_REG_PWM1_MAX_DC                    0x09
#define FAN8_REG_PWM2_MAX_DC                    0x0A
#define FAN8_REG_PWM1_TARGET_DC                 0x0B
#define FAN8_REG_PWM2_TARGET_DC                 0x0C
#define FAN8_REG_PWM1_INSTANTANEOUS_DC          0x0D
#define FAN8_REG_PWM2_INSTANTANEOUS_DC          0x0E
#define FAN8_REG_CH1_FAN_START_TEMP             0x0F
#define FAN8_REG_CH2_FAN_START_TEMP             0x10
#define FAN8_REG_FAN_CONFIGURATION              0x11
#define FAN8_REG_DC_ROC                         0x12
#define FAN8_REG_DC_STEP_SIZE                   0x13
#define FAN8_REG_PWM_FREQ_SEL                   0x14
#define FAN8_REG_THERMISTOR_OFFSET              0x17
#define FAN8_REG_TACH1_VALUE                    0x18
#define FAN8_REG_TACH2_VALUE                    0x19
#define FAN8_REG_TACH1_LIMIT                    0x1A
#define FAN8_REG_TACH2_LIMIT                    0x1B
#define FAN8_REG_FAN_STATUS_BYTE                0x1C
#define FAN8_REG_CH1_TEMP_LSB                   0x1E
#define FAN8_REG_CH2_TEMP_LSB                   0x1F
#define FAN8_REG_DEVICE_REV                     0xFD
#define FAN8_REG_DEVICE_ID                      0xFE
#define FAN8_REG_MANUFACTURER_ID                0xFF

/*! @} */ // fan8_reg

/**
 * @defgroup fan8_set FAN 8 Registers Settings
 * @brief Settings for registers of FAN 8 Click driver.
 */

/**
 * @addtogroup fan8_set
 * @{
 */

/**
 * @brief FAN 8 Device ID value.
 * @details Specified value for device ID of FAN 8 Click driver.
 */
#define FAN8_DEVICE_ID                          0x68

/**
 * @brief FAN 8 Reset value.
 * @details Specified value for reset of FAN 8 Click driver.
 */
#define FAN8_RESET                              0x40

/**
 * @brief FAN 8 fan channels value.
 * @details Specified value for fan channels of FAN 8 Click driver.
 */
#define FAN8_FAN_CHANNEL_1                      0x01
#define FAN8_FAN_CHANNEL_2                      0x02

/**
 * @brief FAN 8 fan channels value.
 * @details Specified value for fan channels of FAN 8 Click driver.
 */
#define FAN8_FAN_CHANNEL_1                      0x01
#define FAN8_FAN_CHANNEL_2                      0x02

/**
 * @brief FAN 8 temperature channels value.
 * @details Specified value for temperature channels of FAN 8 Click driver.
 */
#define FAN8_TEMP_CHANNEL_1                     0x01
#define FAN8_TEMP_CHANNEL_2                     0x02

/**
 * @brief FAN 8 temperature constants.
 * @details Specified constants for temperature calculations of FAN 8 Click driver.
 */
#define FAN8_TEMPERATURE_RESOLUTION             0.125

/**
 * @brief FAN 8 duty cycle values.
 * @details Specified values for duty cycle of FAN 8 Click driver.
 */
#define FAN8_MAX_DUTY_CYCLE                     240
#define FAN8_MIN_DUTY_CYCLE                     0
#define FAN8_DUTY_CYCLE_STEP_2                  2
#define FAN8_DUTY_CYCLE_STEP_4                  4
#define FAN8_DUTY_CYCLE_STEP_6                  6
#define FAN8_DUTY_CYCLE_STEP_8                  8
#define FAN8_DUTY_CYCLE_STEP_10                 10
#define FAN8_DUTY_CYCLE_STEP_12                 12
#define FAN8_DUTY_CYCLE_STEP_14                 14
#define FAN8_DUTY_CYCLE_STEP_16                 16

/**
 * @brief FAN 8 tachometer constants.
 * @details Specified constants for tachometer calculations of FAN 8 Click driver.
 */
#define FAN8_CLOCK_COUNTER_FREQ                 1950
#define FAN8_SEC_PER_MIN                        60
#define FAN8_2_PULSES_PER_REVOLUTION            2
#define FAN8_MAX_TACH_VALUE                     255

/**
 * @brief FAN 8 device address setting.
 * @details Specified setting for device slave address selection of
 * FAN 8 Click driver.
 */
#define FAN8_DEV_ADDR_ADD0_GND_ADD1_GND         0x18
#define FAN8_DEV_ADDR_ADD0_GND_ADD1_HIGH_Z      0x19
#define FAN8_DEV_ADDR_ADD0_GND_ADD1_VCC         0x1A
#define FAN8_DEV_ADDR_ADD0_HIGH_Z_ADD1_GND      0x29
#define FAN8_DEV_ADDR_ADD0_HIGH_Z_ADD1_HIGH_Z   0x2A
#define FAN8_DEV_ADDR_ADD0_HIGH_Z_ADD1_VCC      0x2B
#define FAN8_DEV_ADDR_ADD0_VCC_ADD1_GND         0x4C
#define FAN8_DEV_ADDR_ADD0_VCC_ADD1_HIGH_Z      0x4D
#define FAN8_DEV_ADDR_ADD0_VCC_ADD1_VCC         0x4E

/*! @} */ // fan8_set

/**
 * @defgroup fan8_map FAN 8 MikroBUS Map
 * @brief MikroBUS pin mapping of FAN 8 Click driver.
 */

/**
 * @addtogroup fan8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of FAN 8 Click to the selected MikroBUS.
 */
#define FAN8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ot = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.fan_fail = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // fan8_map
/*! @} */ // fan8

/**
 * @brief FAN 8 Click context object.
 * @details Context object definition of FAN 8 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  ot;          /**< Overtemperature indicator. */
    digital_in_t  fan_fail;    /**< Fan-Failure indicator. */
    digital_in_t  fault;       /**< Fault indicator. */

    // Modules
    i2c_master_t i2c;          /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;     /**< Device slave address (used for I2C driver). */

} fan8_t;

/**
 * @brief FAN 8 Click configuration object.
 * @details Configuration object definition of FAN 8 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  ot;         /**< Overtemperature indicator. */
    pin_name_t  fan_fail;   /**< Fan-Failure indicator. */
    pin_name_t  fault;      /**< Fault indicator. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} fan8_cfg_t;

/**
 * @brief FAN 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FAN8_OK = 0,
    FAN8_ERROR = -1

} fan8_return_value_t;

/*!
 * @addtogroup fan8 FAN 8 Click Driver
 * @brief API for configuring and manipulating FAN 8 Click driver.
 * @{
 */

/**
 * @brief FAN 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #fan8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void fan8_cfg_setup ( fan8_cfg_t *cfg );

/**
 * @brief FAN 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #fan8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #fan8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan8_init ( fan8_t *ctx, fan8_cfg_t *cfg );

/**
 * @brief FAN 8 default configuration function.
 * @details This function executes a default configuration of FAN 8
 * Click board.
 * @param[in] ctx : Click context object.
 * See #fan8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t fan8_default_cfg ( fan8_t *ctx );

/**
 * @brief FAN 8 write register function.
 * @details This function writes a desired data to the selected register.
 * @param[in] ctx : Click context object.
 * See #fan8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan8_write_register ( fan8_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief FAN 8 read register function.
 * @details This function reads the selected register.
 * @param[in] ctx : Click context object.
 * See #fan8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan8_read_register ( fan8_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief FAN 8 check overtemperature indicator function.
 * @details This function returns the OT pin state.
 * @param[in] ctx : Click context object.
 * See #fan8_t object definition for detailed explanation.
 * @return OT pin logic state.
 * @note None.
 */
uint8_t fan8_check_overtemperature_indicator ( fan8_t *ctx );

/**
 * @brief FAN 8 check fan fail indicator function.
 * @details This function returns the FF pin state.
 * @param[in] ctx : Click context object.
 * See #fan8_t object definition for detailed explanation.
 * @return FF pin logic state.
 * @note None.
 */
uint8_t fan8_check_fan_fail_indicator ( fan8_t *ctx );

/**
 * @brief FAN 8 check fault indicator function.
 * @details This function returns the FLT pin state.
 * @param[in] ctx : Click context object.
 * See #fan8_t object definition for detailed explanation.
 * @return FLT pin logic state.
 * @note None.
 */
uint8_t fan8_check_fault_indicator ( fan8_t *ctx );

/**
 * @brief FAN 8 check device ID function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #fan8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan8_check_device_id ( fan8_t *ctx );

/**
 * @brief FAN 8 set duty cycle function.
 * @details This function sets the duty cycle of the selected fan channel and waits until the 
 * duty cycle is set at the PWM output.
 * @param[in] ctx : Click context object.
 * See #fan8_t object definition for detailed explanation.
 * @param[in] fan_ch : Fan channel.
*                     @li @c  1 - Channel 1,
*                     @li @c  2 - Channel 2.
 * @param[in] duty_cycle : Duty cycle [0-240].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan8_set_duty_cycle ( fan8_t *ctx, uint8_t fan_ch, uint8_t duty_cycle );

/**
 * @brief FAN 8 measure fan RPM function.
 * @details This function measures the RPM of the selected fan channel.
 * @param[in] ctx : Click context object.
 * See #fan8_t object definition for detailed explanation.
 * @param[in] fan_ch : Fan channel.
*                     @li @c  1 - Channel 1,
*                     @li @c  2 - Channel 2.
 * @param[in] num_pulses : Number of fan pulses per revolution.
 * @param[out] fan_rpm : Fan RPM.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note The MAX6615 measures the tachometer signal every 67s, therefore 
 * the fan RPM value will be updated once per 67s.
 */
err_t fan8_measure_rpm ( fan8_t *ctx, uint8_t fan_ch, uint8_t num_pulses, uint16_t *fan_rpm );

/**
 * @brief FAN 8 read temperature function.
 * @details This function reads the temperature from the thermistor attached to 
 * the selected temperature channel.
 * @param[in] ctx : Click context object.
 * See #fan8_t object definition for detailed explanation.
 * @param[in] temp_ch : Temperature channel.
*                     @li @c  1 - Channel 1,
*                     @li @c  2 - Channel 2.
 * @param[in] num_pulses : Number of fan pulses per revolution.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note An NTC 10K3 thermistor is required for proper temperature measurements.
 */
err_t fan8_read_temperature ( fan8_t *ctx, uint8_t temp_ch, float *temperature );

/**
 * @brief FAN 8 reset function.
 * @details This function performs the device reset.
 * @param[in] ctx : Click context object.
 * See #fan8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * 
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fan8_reset ( fan8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // FAN8_H

/*! @} */ // fan8

// ------------------------------------------------------------------------ END
