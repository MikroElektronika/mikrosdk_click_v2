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
 * @file tempalarm.h
 * @brief This file contains API for Temp Alarm Click Driver.
 */

#ifndef TEMPALARM_H
#define TEMPALARM_H

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
 * @addtogroup tempalarm Temp Alarm Click Driver
 * @brief API for configuring and manipulating Temp Alarm Click driver.
 * @{
 */

/**
 * @defgroup tempalarm_reg Temp Alarm Registers List
 * @brief List of registers of Temp Alarm Click driver.
 */

/**
 * @addtogroup tempalarm_reg
 * @{
 */

/**
 * @brief Temp Alarm description register.
 * @details Specified register for description of Temp Alarm Click driver.
 */
#define TEMPALARM_REG_TEMP_LOCAL                0x00
#define TEMPALARM_REG_TEMP_REMOTE_MSB           0x01
#define TEMPALARM_REG_ALERT_STATUS              0x02
#define TEMPALARM_REG_CONFIGURATION             0x03
#define TEMPALARM_REG_CONV_PERIOD               0x04
#define TEMPALARM_REG_THIGH_LIMIT_LOCAL         0x05
#define TEMPALARM_REG_THIGH_LIMIT_REMOTE_MSB    0x07
#define TEMPALARM_REG_TLOW_LIMIT_REMOTE_MSB     0x08
#define TEMPALARM_REG_ONE_SHOT                  0x0F
#define TEMPALARM_REG_TEMP_REMOTE_LSB           0x10
#define TEMPALARM_REG_REMOTE_OFFSET_MSB         0x11
#define TEMPALARM_REG_REMOTE_OFFSET_LSB         0x12
#define TEMPALARM_REG_THIGH_LIMIT_REMOTE_LSB    0x13
#define TEMPALARM_REG_TLOW_LIMIT_REMOTE_LSB     0x14
#define TEMPALARM_REG_ALERT_MASK                0x16
#define TEMPALARM_REG_THIGH_CRIT_REMOTE         0x19
#define TEMPALARM_REG_THIGH_CRIT_LOCAL          0x20
#define TEMPALARM_REG_CRIT_HYSTERESIS           0x21
#define TEMPALARM_REG_LOG1                      0x2D
#define TEMPALARM_REG_LOG2                      0x2E
#define TEMPALARM_REG_LOG3                      0x2F
#define TEMPALARM_REG_FILTER_ALERT_MODE         0xBF
#define TEMPALARM_REG_CHIP_ID                   0xFD
#define TEMPALARM_REG_VENDOR_ID                 0xFE
#define TEMPALARM_REG_DEVICE_REV_ID             0xFF

/*! @} */ // tempalarm_reg

/**
 * @defgroup tempalarm_set Temp Alarm Registers Settings
 * @brief Settings for registers of Temp Alarm Click driver.
 */

/**
 * @addtogroup tempalarm_set
 * @{
 */

/**
 * @brief Temp Alarm description setting.
 * @details Specified setting for description of Temp Alarm Click driver.
 */
#define TEMPALARM_THIGH_LA_ALERT_DIS_MASK       0x80
#define TEMPALARM_THIGH_LA_ALERT_ENABLE_MASK    0x80
#define TEMPALARM_THIGH_RA_ALERT_DIS_MASK       0x10
#define TEMPALARM_THIGH_RA_ALERT_ENABLE_MASK    0x00
#define TEMPALARM_TLOW_RA_ALERT_DIS_MASK        0x08
#define TEMPALARM_TLOW_RA_ALERT_ENABLE_MASK     0x00
#define TEMPALARM_TCRIT_R_ALERT_DIS_MASK        0x02
#define TEMPALARM_TCRIT_R_ALERT_ENABLE_MASK     0x00
#define TEMPALARM_TCRIT_L_ALERT_DIS_MASK        0x01
#define TEMPALARM_TCRIT_L_ALERT_ENABLE_MASK     0x00

/**
 * @brief Temp Alarm flags setting.
 * @details Specified setting for flags of Temp Alarm Click driver.
 */
#define TEMPALARM_ADC_BUSY_MASK                 0x80
#define TEMPALARM_THIGH_LA_MASK                 0x40
#define TEMPALARM_THIGH_RA_MASK                 0x10
#define TEMPALARM_TLOW_RA_MASK                  0x08
#define TEMPALARM_REMOTE_DC_MASK                0x04
#define TEMPALARM_TCRIT_R_MASK                  0x02
#define TEMPALARM_TCRIT_L_MASK                  0x01

/**
 * @brief Temp Alarm filter level setting.
 * @details Specified setting for filter level of Temp Alarm Click driver.
 */
#define TEMPALARM_FILTER_LEVEL_0_MASK           0x00
#define TEMPALARM_FILTER_LEVEL_4_MASK           0x02
#define TEMPALARM_FILTER_LEVEL_8_MASK           0x06
#define TEMPALARM_INTERRUPT_ALERT_MODE          0x00
#define TEMPALARM_COMPARATOR_MODE               0x01

/**
 * @brief Temp Alarm configuration setting.
 * @details Specified setting for configuration of Temp Alarm Click driver.
 */
#define TEMPALARM_ALERT_DISABLED                0x80
#define TEMPALARM_SHUTDOWN_MODE                 0x40
#define TEMPALARM_CONTINUOUS_MODE               0x00
#define TEMPALARM_REMOTE_EN                     0x04
#define TEMPALARM_REMOTE_DIS                    0x00
#define TEMPALARM_WTC_EN                        0x02
#define TEMPALARM_WTC_DIS                       0x00
#define TEMPALARM_FAULT_QUE_EN                  0x01
#define TEMPALARM_FAULT_QUE_DIS                 0x00

/**
 * @brief Temp Alarm configuration setting.
 * @details Specified setting for configuration of Temp Alarm Click driver.
 */
#define TEMPALARM_CONVERSION_PERIOD_16S         0x00
#define TEMPALARM_CONVERSION_PERIOD_8S          0x01
#define TEMPALARM_CONVERSION_PERIOD_4S          0x02
#define TEMPALARM_CONVERSION_PERIOD_2S          0x03
#define TEMPALARM_CONVERSION_PERIOD_1S          0x04
#define TEMPALARM_CONVERSION_PERIOD_500MS       0x05
#define TEMPALARM_CONVERSION_PERIOD_250MS       0x06
#define TEMPALARM_CONVERSION_PERIOD_125MS       0x07
#define TEMPALARM_CONVERSION_PERIOD_62MS5       0x08

/**
 * @brief Temp Alarm pin state setting.
 * @details Specified setting for pin state of Temp Alarm Click driver.
 */
#define TEMPALARM_PIN_STATE_HIGH                0x01
#define TEMPALARM_PIN_STATE_LOW                 0x00

/**
 * @brief Temp Alarm chip id setting.
 * @details Specified setting for chip id of Temp Alarm Click driver.
 */
#define TEMPALARM_CHIP_ID                       0x50
#define TEMPALARM_VENDOR_ID                     0x60

/**
 * @brief Temp Alarm temperature calculation setting.
 * @details Specified setting for temperature calculation of Temp Alarm Click driver.
 */
#define TEMPALARM_TEMP_CLC                      0.125f

/**
 * @brief Temp Alarm device address setting.
 * @details Specified setting for device slave address selection of
 * Temp Alarm Click driver.
 */
#define TEMPALARM_DEVICE_ADDRESS                0x4C

/*! @} */ // tempalarm_set

/**
 * @defgroup tempalarm_map Temp Alarm MikroBUS Map
 * @brief MikroBUS pin mapping of Temp Alarm Click driver.
 */

/**
 * @addtogroup tempalarm_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Temp Alarm Click to the selected MikroBUS.
 */
#define TEMPALARM_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tcr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.alr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // tempalarm_map
/*! @} */ // tempalarm

/**
 * @brief Temp Alarm Click context object.
 * @details Context object definition of Temp Alarm Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t tcr;           /**< Critical temperature alert pin. */
    digital_in_t alr;           /**< Alert pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} tempalarm_t;

/**
 * @brief Temp Alarm Click configuration object.
 * @details Configuration object definition of Temp Alarm Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t tcr;             /**< Critical temperature alert pin. */
    pin_name_t alr;             /**< Alert pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} tempalarm_cfg_t;

/**
 * @brief Temp Alarm Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPALARM_OK = 0,
    TEMPALARM_ERROR = -1

} tempalarm_return_value_t;

/*!
 * @addtogroup tempalarm Temp Alarm Click Driver
 * @brief API for configuring and manipulating Temp Alarm Click driver.
 * @{
 */

/**
 * @brief Temp Alarm configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tempalarm_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tempalarm_cfg_setup ( tempalarm_cfg_t *cfg );

/**
 * @brief Temp Alarm initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tempalarm_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm_init ( tempalarm_t *ctx, tempalarm_cfg_t *cfg );

/**
 * @brief Temp Alarm default configuration function.
 * @details This function executes a default configuration of Temp Alarm
 * click board.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t tempalarm_default_cfg ( tempalarm_t *ctx );

/**
 * @brief Temp Alarm I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm_generic_write ( tempalarm_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Temp Alarm I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm_generic_read ( tempalarm_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Temp Alarm get alarm pin state function.
 * @details This function is used to get alarm pin state.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @return @li @c 0 - Pin state low,
 *         @li @c 1 - Pin state high.
 * @note None.
 */
uint8_t tempalarm_get_alr_pin ( tempalarm_t *ctx );

/**
 * @brief Temp Alarm get critical temperature alert pin state function.
 * @details This function is used to get alarm critical temperature alert state.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @return @li @c 0 - Pin state low,
 *         @li @c 1 - Pin state high.
 * @note None.
 */
uint8_t tempalarm_get_tcr_pin ( tempalarm_t *ctx );

/**
 * @brief Temp Alarm register writing function.
 * @details This function writes data byte into
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm_write_reg ( tempalarm_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Temp Alarm register reading function.
 * @details This function reads a data byte from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm_read_reg ( tempalarm_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Temp Alarm local sensor read temperature function.
 * @details This function is used to read local sensor in degrees of Celsius.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @param[out] temperature : Temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm_read_temperature ( tempalarm_t *ctx, int8_t *temperature );

/**
 * @brief Temp Alarm remote sensor read temperature function.
 * @details This function is used to read remote sensor in degrees of Celsius.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @param[out] temperature : Temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm_read_remote_temp ( tempalarm_t *ctx, float *temperature );

/**
 * @brief Temp Alarm local sensor set critical high temperature function.
 * @details This function is used to set local sensor critical high temperature.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @param[in] max_temperature : Temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm_set_crit_thigh ( tempalarm_t *ctx, int8_t max_temperature );

/**
 * @brief Temp Alarm local sensor set limit high temperature function.
 * @details This function is used to set local sensor limit high temperature.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @param[in] max_temperature : Temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm_set_limit_thigh ( tempalarm_t *ctx, int8_t max_temperature );

/**
 * @brief Temp Alarm remote sensor set limit low temperature function.
 * @details This function is used to set remote sensor limit low temperature.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @param[in] min_temperature : Temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm_set_alarm_low_limit ( tempalarm_t *ctx, float min_temperature );

/**
 * @brief Temp Alarm remote sensor set limit high temperature function.
 * @details This function is used to set remote sensor limit high temperature.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @param[in] max_temperature : Temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm_set_alarm_high_limit ( tempalarm_t *ctx, float max_temperature );

/**
 * @brief Temp Alarm read alarms state function.
 * @details This function is used to read alarms state.
 * @param[in] ctx : Click context object.
 * See #tempalarm_t object definition for detailed explanation.
 * @param[in] alarms : Alarm state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempalarm_get_alarms ( tempalarm_t *ctx, uint8_t *alarms );

#ifdef __cplusplus
}
#endif
#endif // TEMPALARM_H

/*! @} */ // tempalarm

// ------------------------------------------------------------------------ END
