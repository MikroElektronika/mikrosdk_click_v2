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
 * @file thermocouple.h
 * @brief This file contains API for Thermocouple Click Driver.
 */

#ifndef THERMOCOUPLE_H
#define THERMOCOUPLE_H

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

/*!
 * @addtogroup thermocouple Thermocouple Click Driver
 * @brief API for configuring and manipulating Thermocouple Click driver.
 * @{
 */

/**
 * @defgroup thermocouple_reg Thermocouple Registers List
 * @brief List of registers of Thermocouple Click driver.
 */

/**
 * @addtogroup thermocouple_reg
 * @{
 */

/**
 * @brief Thermocouple register map.
 * @details Specified register map of Thermocouple Click driver.
 */
#define THERMOCOUPLE_REG_HOT_JUNCTION_TEMP              0x00
#define THERMOCOUPLE_REG_JUNCTION_TEMP_DELTA            0x01
#define THERMOCOUPLE_REG_COLD_JUNCTION_TEMP             0x02
#define THERMOCOUPLE_REG_RAW_ADC_DATA                   0x03
#define THERMOCOUPLE_REG_STATUS                         0x04
#define THERMOCOUPLE_REG_SENSOR_CONFIG                  0x05
#define THERMOCOUPLE_REG_DEVICE_CONFIG                  0x06
#define THERMOCOUPLE_REG_ALERT1_CONFIG                  0x08
#define THERMOCOUPLE_REG_ALERT2_CONFIG                  0x09
#define THERMOCOUPLE_REG_ALERT3_CONFIG                  0x0A
#define THERMOCOUPLE_REG_ALERT4_CONFIG                  0x0B
#define THERMOCOUPLE_REG_ALERT1_HYSTERESIS              0x0C
#define THERMOCOUPLE_REG_ALERT2_HYSTERESIS              0x0D
#define THERMOCOUPLE_REG_ALERT3_HYSTERESIS              0x0E
#define THERMOCOUPLE_REG_ALERT4_HYSTERESIS              0x0F
#define THERMOCOUPLE_REG_ALERT1_LIMIT                   0x10
#define THERMOCOUPLE_REG_ALERT2_LIMIT                   0x11
#define THERMOCOUPLE_REG_ALERT3_LIMIT                   0x12
#define THERMOCOUPLE_REG_ALERT4_LIMIT                   0x13
#define THERMOCOUPLE_REG_DEVICE_ID_REVISION             0x20

/*! @} */ // thermocouple_reg

/**
 * @defgroup thermocouple_set Thermocouple Registers Settings
 * @brief Settings for registers of Thermocouple Click driver.
 */

/**
 * @addtogroup thermocouple_set
 * @{
 */

/**
 * @brief Thermocouple STATUS register setting.
 * @details Specified setting for STATUS register of Thermocouple Click driver.
 */
#define THERMOCOUPLE_STATUS_BURST_COMPLETE               0x80
#define THERMOCOUPLE_STATUS_TH_UPDATE                    0x40
#define THERMOCOUPLE_STATUS_SHORT_CIRCUIT                0x20
#define THERMOCOUPLE_STATUS_INPUT_RANGE                  0x10
#define THERMOCOUPLE_STATUS_ALERT4                       0x08
#define THERMOCOUPLE_STATUS_ALERT3                       0x04
#define THERMOCOUPLE_STATUS_ALERT2                       0x02
#define THERMOCOUPLE_STATUS_ALERT1                       0x01

/**
 * @brief Thermocouple SENSOR_CONFIG register setting.
 * @details Specified setting for SENSOR_CONFIG register of Thermocouple Click driver.
 */
#define THERMOCOUPLE_SENSOR_CONFIG_TYPE_MASK             0x70
#define THERMOCOUPLE_SENSOR_CONFIG_TYPE_K                0x00
#define THERMOCOUPLE_SENSOR_CONFIG_TYPE_J                0x10
#define THERMOCOUPLE_SENSOR_CONFIG_TYPE_T                0x20
#define THERMOCOUPLE_SENSOR_CONFIG_TYPE_N                0x30
#define THERMOCOUPLE_SENSOR_CONFIG_TYPE_S                0x40
#define THERMOCOUPLE_SENSOR_CONFIG_TYPE_E                0x50
#define THERMOCOUPLE_SENSOR_CONFIG_TYPE_B                0x60
#define THERMOCOUPLE_SENSOR_CONFIG_TYPE_R                0x70
#define THERMOCOUPLE_SENSOR_CONFIG_FILTER_MASK           0x07
#define THERMOCOUPLE_SENSOR_CONFIG_FILTER_OFF            0x00
#define THERMOCOUPLE_SENSOR_CONFIG_FILTER_MIN            0x01
#define THERMOCOUPLE_SENSOR_CONFIG_FILTER_MID            0x04
#define THERMOCOUPLE_SENSOR_CONFIG_FILTER_MAX            0x07
#define THERMOCOUPLE_SENSOR_CONFIG_CHANNEL_0             0x08
#define THERMOCOUPLE_SENSOR_CONFIG_CHANNEL_1             0x00
#define THERMOCOUPLE_SENSOR_CONFIG_CHANNEL_2             0x88
#define THERMOCOUPLE_SENSOR_CONFIG_CHANNEL_3             0x80

/**
 * @brief Thermocouple DEVICE_CONFIG register setting.
 * @details Specified setting for DEVICE_CONFIG register of Thermocouple Click driver.
 */
#define THERMOCOUPLE_DEVICE_CONFIG_COLD_JUNC_RES         0x80
#define THERMOCOUPLE_DEVICE_CONFIG_ADC_RES_MASK          0x60
#define THERMOCOUPLE_DEVICE_CONFIG_ADC_RES_18BIT         0x00
#define THERMOCOUPLE_DEVICE_CONFIG_ADC_RES_16BIT         0x20
#define THERMOCOUPLE_DEVICE_CONFIG_ADC_RES_14BIT         0x40
#define THERMOCOUPLE_DEVICE_CONFIG_ADC_RES_12BIT         0x60
#define THERMOCOUPLE_DEVICE_CONFIG_BURST_SAMPLES_MASK    0x1C
#define THERMOCOUPLE_DEVICE_CONFIG_BURST_1_SAMPLE        0x00
#define THERMOCOUPLE_DEVICE_CONFIG_BURST_2_SAMPLES       0x04
#define THERMOCOUPLE_DEVICE_CONFIG_BURST_4_SAMPLES       0x08
#define THERMOCOUPLE_DEVICE_CONFIG_BURST_8_SAMPLES       0x0C
#define THERMOCOUPLE_DEVICE_CONFIG_BURST_16_SAMPLES      0x10
#define THERMOCOUPLE_DEVICE_CONFIG_BURST_32_SAMPLES      0x14
#define THERMOCOUPLE_DEVICE_CONFIG_BURST_64_SAMPLES      0x18
#define THERMOCOUPLE_DEVICE_CONFIG_BURST_128_SAMPLES     0x1C
#define THERMOCOUPLE_DEVICE_CONFIG_MODE_MASK             0x03
#define THERMOCOUPLE_DEVICE_CONFIG_MODE_NORMAL           0x00
#define THERMOCOUPLE_DEVICE_CONFIG_MODE_SHUTDOWN         0x01
#define THERMOCOUPLE_DEVICE_CONFIG_MODE_BURST            0x02
#define THERMOCOUPLE_DEVICE_CONFIG_MODE_SCAN             0x03

/**
 * @brief Thermocouple ALERT_CONFIG register setting.
 * @details Specified setting for ALERT_CONFIG register of Thermocouple Click driver.
 */
#define THERMOCOUPLE_ALERT_CONFIG_INT_CLEAR              0x80
#define THERMOCOUPLE_ALERT_CONFIG_CHANNEL_MASK           0x60
#define THERMOCOUPLE_ALERT_CONFIG_CHANNEL_0              0x00
#define THERMOCOUPLE_ALERT_CONFIG_CHANNEL_1              0x20
#define THERMOCOUPLE_ALERT_CONFIG_CHANNEL_2              0x40
#define THERMOCOUPLE_ALERT_CONFIG_CHANNEL_3              0x60
#define THERMOCOUPLE_ALERT_CONFIG_MONITOR_TC             0x10
#define THERMOCOUPLE_ALERT_CONFIG_FALLING                0x08
#define THERMOCOUPLE_ALERT_CONFIG_ACTIVE_HIGH            0x04
#define THERMOCOUPLE_ALERT_CONFIG_INTERRUPT_MODE         0x02
#define THERMOCOUPLE_ALERT_CONFIG_ENABLE                 0x01

/**
 * @brief Thermocouple DEVICE_ID register setting.
 * @details Specified setting for DEVICE_ID register of Thermocouple Click driver.
 */
#define THERMOCOUPLE_DEVICE_ID_MCP9604                  0x4400
#define THERMOCOUPLE_DEVICE_ID_MASK                     0xFF00
#define THERMOCOUPLE_DEVICE_ID_REV_MAJOR_MASK           0x00F0
#define THERMOCOUPLE_DEVICE_ID_REV_MINOR_MASK           0x000F

/**
 * @brief Thermocouple channel selection setting.
 * @details Specified setting for channel selection of Thermocouple Click driver.
 */
#define THERMOCOUPLE_CHANNEL_1                          0x01
#define THERMOCOUPLE_CHANNEL_2                          0x02
#define THERMOCOUPLE_CHANNEL_3                          0x03
#define THERMOCOUPLE_CHANNEL_4                          0x04

/**
 * @brief Thermocouple type selection setting.
 * @details Specified setting for type selection of Thermocouple Click driver.
 */
#define THERMOCOUPLE_TYPE_K                             0x00
#define THERMOCOUPLE_TYPE_J                             0x01
#define THERMOCOUPLE_TYPE_T                             0x02
#define THERMOCOUPLE_TYPE_N                             0x03
#define THERMOCOUPLE_TYPE_S                             0x04
#define THERMOCOUPLE_TYPE_E                             0x05
#define THERMOCOUPLE_TYPE_B                             0x06
#define THERMOCOUPLE_TYPE_R                             0x07

/**
 * @brief Thermocouple filter selection setting.
 * @details Specified setting for filter selection of Thermocouple Click driver.
 */
#define THERMOCOUPLE_FILTER_OFF                         0x00
#define THERMOCOUPLE_FILTER_MIN                         0x01
#define THERMOCOUPLE_FILTER_MID                         0x04
#define THERMOCOUPLE_FILTER_MAX                         0x07

/**
 * @brief Thermocouple timeout setting.
 * @details Specified setting for timeout of Thermocouple driver.
 */
#define THERMOCOUPLE_I2C_TIMEOUT                        100000ul
#define THERMOCOUPLE_STATUS_TIMEOUT                     1000ul
#define THERMOCOUPLE_I2C_RELEASE_TIMEOUT                100ul

/**
 * @brief Thermocouple device address setting.
 * @details Specified setting for device slave address selection of
 * Thermocouple Click driver.
 */
#define THERMOCOUPLE_DEVICE_ADDRESS_0                   0x60
#define THERMOCOUPLE_DEVICE_ADDRESS_1                   0x67

/*! @} */ // thermocouple_set

/**
 * @defgroup thermocouple_map Thermocouple MikroBUS Map
 * @brief MikroBUS pin mapping of Thermocouple Click driver.
 */

/**
 * @addtogroup thermocouple_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermocouple Click to the selected MikroBUS.
 */
#define THERMOCOUPLE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.oca = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sca = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // thermocouple_map
/*! @} */ // thermocouple

/**
 * @brief Thermocouple Click context object.
 * @details Context object definition of Thermocouple Click driver.
 */
typedef struct
{
    digital_in_t oca;           /**< Open-circuit alert pin. */
    digital_in_t sca;           /**< Short-circuit alert pin. */

    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint8_t i2c_started;        /**< I2C started flag. */

    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} thermocouple_t;

/**
 * @brief Thermocouple Click configuration object.
 * @details Configuration object definition of Thermocouple Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t oca;             /**< Open-circuit alert pin. */
    pin_name_t sca;             /**< Short-circuit alert pin. */

    uint8_t    i2c_address;     /**< I2C slave address. */

} thermocouple_cfg_t;

/**
 * @brief Thermocouple Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMOCOUPLE_OK = 0,
    THERMOCOUPLE_ERROR = -1

} thermocouple_return_value_t;

/*!
 * @addtogroup thermocouple Thermocouple Click Driver
 * @brief API for configuring and manipulating Thermocouple Click driver.
 * @{
 */

/**
 * @brief Thermocouple configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermocouple_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermocouple_cfg_setup ( thermocouple_cfg_t *cfg );

/**
 * @brief Thermocouple initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermocouple_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermocouple_init ( thermocouple_t *ctx, thermocouple_cfg_t *cfg );

/**
 * @brief Thermocouple default configuration function.
 * @details This function executes a default configuration of Thermocouple
 * Click board.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermocouple_default_cfg ( thermocouple_t *ctx );

/**
 * @brief Thermocouple write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermocouple_write_reg ( thermocouple_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Thermocouple write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermocouple_write_regs ( thermocouple_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Thermocouple read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermocouple_read_reg ( thermocouple_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Thermocouple read register word function.
 * @details This function reads a data word from the selected register.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data word.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermocouple_read_reg_word ( thermocouple_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Thermocouple read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermocouple_read_regs ( thermocouple_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Thermocouple get OCA pin function.
 * @details This function returns the open-circuit alert (OCA) pin logic state.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t thermocouple_get_oca_pin ( thermocouple_t *ctx );

/**
 * @brief Thermocouple get SCA pin function.
 * @details This function returns the short-circuit alert (SCA) pin logic state.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t thermocouple_get_sca_pin ( thermocouple_t *ctx );

/**
 * @brief Thermocouple check com function.
 * @details This function checks the communication by reading and verifying the device ID register.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermocouple_check_com ( thermocouple_t *ctx );

/**
 * @brief Thermocouple set sensor configuration function.
 * @details This function sets thermocouple type, channel, and filter configuration.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[in] channel : Channel selection.
 * @param[in] type : Thermocouple type selection.
 * @param[in] filter : Digital filter setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t thermocouple_set_sensor_cfg ( thermocouple_t *ctx, uint8_t channel, uint8_t type, uint8_t filter );

/**
 * @brief Thermocouple set device configuration function.
 * @details This function sets ADC resolution, burst samples, and operating mode.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[in] adc_res : ADC resolution setting.
 * @param[in] burst : Burst sample setting.
 * @param[in] mode : Operating mode setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t thermocouple_set_device_cfg ( thermocouple_t *ctx, uint8_t adc_res, uint8_t burst, uint8_t mode );

/**
 * @brief Thermocouple get status function.
 * @details This function reads the status register.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[out] status : Pointer to memory location where status data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t thermocouple_get_status ( thermocouple_t *ctx, uint8_t *status );

/**
 * @brief Thermocouple clear status function.
 * @details This function clears the status register.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t thermocouple_clear_status ( thermocouple_t *ctx );

/**
 * @brief Thermocouple get hot junction temperature function.
 * @details This function reads the hot junction (thermocouple) temperature register.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[out] temp : Pointer to memory location where floating point temperature data in Celsius will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t thermocouple_get_hot_junction ( thermocouple_t *ctx, float *temp );

/**
 * @brief Thermocouple get cold junction temperature function.
 * @details This function reads the cold junction (ambient) temperature register.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[out] temp : Pointer to memory location where floating point temperature data in Celsius will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t thermocouple_get_cold_junction ( thermocouple_t *ctx, float *temp );

/**
 * @brief Thermocouple get delta temperature function.
 * @details This function reads the junction delta temperature register.
 * @param[in] ctx : Click context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[out] temp : Pointer to memory location where floating point temperature data in Celsius will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t thermocouple_get_delta_temp ( thermocouple_t *ctx, float *temp );

#ifdef __cplusplus
}
#endif
#endif // THERMOCOUPLE_H

/*! @} */ // thermocouple

// ------------------------------------------------------------------------ END
