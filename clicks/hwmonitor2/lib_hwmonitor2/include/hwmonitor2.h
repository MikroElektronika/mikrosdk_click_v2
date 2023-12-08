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
 * @file hwmonitor2.h
 * @brief This file contains API for HW Monitor 2 Click Driver.
 */

#ifndef HWMONITOR2_H
#define HWMONITOR2_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup hwmonitor2 HW Monitor 2 Click Driver
 * @brief API for configuring and manipulating HW Monitor 2 Click driver.
 * @{
 */

/**
 * @defgroup hwmonitor2_reg HW Monitor 2 Registers List
 * @brief List of registers of HW Monitor 2 Click driver.
 */

/**
 * @addtogroup hwmonitor2_reg
 * @{
 */

/**
 * @brief HW Monitor 2 description register.
 * @details Specified register for description of HW Monitor 2 Click driver.
 */
#define HWMONITOR2_REG_CONFIGURATION            0x00
#define HWMONITOR2_REG_INT_STATUS_1             0x01
#define HWMONITOR2_REG_INT_STATUS_2             0x02
#define HWMONITOR2_REG_INT_MASK_1               0x03
#define HWMONITOR2_REG_INT_MASK_2               0x04
#define HWMONITOR2_REG_FAN_DIVISOR              0x05
#define HWMONITOR2_REG_OS_T_RES_CONFIG          0x06
#define HWMONITOR2_REG_CONVERSION_RATE          0x07
#define HWMONITOR2_REG_CHANNEL_DISABLE          0x08
#define HWMONITOR2_REG_INPUT_MODE               0x09
#define HWMONITOR2_REG_ADC_CONTROL              0x0A
#define HWMONITOR2_REG_CONVERS_RATE_CNT         0x0B
#define HWMONITOR2_REG_RAM_IN_0                 0x20
#define HWMONITOR2_REG_RAM_IN_1                 0x21
#define HWMONITOR2_REG_RAM_IN_2                 0x22
#define HWMONITOR2_REG_RAM_IN_3                 0x23
#define HWMONITOR2_REG_RAM_IN_4                 0x24
#define HWMONITOR2_REG_RAM_IN_5                 0x25
#define HWMONITOR2_REG_RAM_IN_6                 0x26
#define HWMONITOR2_REG_RAM_TEMPERATURE          0x27
#define HWMONITOR2_REG_RAM_FAN_1                0x28
#define HWMONITOR2_REG_RAM_FAN_2                0x29
#define HWMONITOR2_REG_RAM_LIM_IN_0_H           0x2A
#define HWMONITOR2_REG_RAM_LIM_IN_0_L           0x2B
#define HWMONITOR2_REG_RAM_LIM_IN_1_H           0x2C
#define HWMONITOR2_REG_RAM_LIM_IN_1_L           0x2D
#define HWMONITOR2_REG_RAM_LIM_IN_2_H           0x2E
#define HWMONITOR2_REG_RAM_LIM_IN_2_L           0x2F
#define HWMONITOR2_REG_RAM_LIM_IN_3_H           0x30
#define HWMONITOR2_REG_RAM_LIM_IN_3_L           0x31
#define HWMONITOR2_REG_RAM_LIM_IN_4_H           0x32
#define HWMONITOR2_REG_RAM_LIM_IN_4_L           0x33
#define HWMONITOR2_REG_RAM_LIM_IN_5_H           0x34
#define HWMONITOR2_REG_RAM_LIM_IN_5_L           0x35
#define HWMONITOR2_REG_RAM_LIM_IN_6_H           0x36
#define HWMONITOR2_REG_RAM_LIM_IN_6_L           0x37
#define HWMONITOR2_REG_RAM_LIM_HOT_H            0x38
#define HWMONITOR2_REG_RAM_LIM_HOT_L            0x39
#define HWMONITOR2_REG_RAM_LIM_TEMP_H           0x3A
#define HWMONITOR2_REG_RAM_LIM_TEMP_L           0x3B
#define HWMONITOR2_REG_RAM_CURRENT_LIM_FUN_1    0x3C
#define HWMONITOR2_REG_RAM_CURRENT_LIM_FUN_2    0x3D
#define HWMONITOR2_REG_RAM_MANUFACTURE_ID       0x3E
#define HWMONITOR2_REG_RAM_REVISION_ID          0x3F

/*! @} */ // hwmonitor2_reg

/**
 * @defgroup hwmonitor2_set HW Monitor 2 Registers Settings
 * @brief Settings for registers of HW Monitor 2 Click driver.
 */

/**
 * @addtogroup hwmonitor2_set
 * @{
 */

/**
 * @brief HW Monitor description HWMONITOR2_REG_CONFIGURATION register value.
 * @details Specified HWMONITOR2_REG_CONFIGURATION register value for description of HW Monitor Click driver.
 */
#define HWMONITOR2_SET_CONFIG_START_DIS         0x00
#define HWMONITOR2_SET_CONFIG_START_EN          0x01
#define HWMONITOR2_SET_CONFIG_INT_DIS           0x00
#define HWMONITOR2_SET_CONFIG_INT_EN            0x01
#define HWMONITOR2_SET_CONFIG_INT_OPEN_DRAIN    0x00
#define HWMONITOR2_SET_CONFIG_INT_ACT_LOW       0x01
#define HWMONITOR2_SET_CONFIG_INT_CLR_DIS       0x00
#define HWMONITOR2_SET_CONFIG_INT_CLR_EN        0x01
#define HWMONITOR2_SET_CONFIG_CHA_NCLR_GPI      0x00
#define HWMONITOR2_SET_CONFIG_CHA_GPI           0x01
#define HWMONITOR2_SET_CONFIG_GPO_LOW           0x00
#define HWMONITOR2_SET_CONFIG_GPO_HIGH          0x01
#define HWMONITOR2_SET_CONFIG_PWR_ON            0x00
#define HWMONITOR2_SET_CONFIG_PWR_DIS           0x01

/**
 * @brief HW Monitor description HWMONITOR2_REG_FAN_DIVISOR register value.
 * @details Specified HWMONITOR2_REG_FAN_DIVISOR register value for the description of HW Monitor Click driver.
 */
#define HWMONITOR2_SET_FAN1_MODE_COUNT          0x00
#define HWMONITOR2_SET_FAN1_MODE_SENS_INPUT     0x01
#define HWMONITOR2_SET_FAN2_MODE_COUNT          0x00
#define HWMONITOR2_SET_FAN2_MODE_SENS_INPUT     0x02
#define HWMONITOR2_SET_FAN1_CTRL_SPEED_DIV1     0x00
#define HWMONITOR2_SET_FAN1_CTRL_SPEED_DIV2     0x04
#define HWMONITOR2_SET_FAN1_CTRL_SPEED_DIV4     0x08
#define HWMONITOR2_SET_FAN1_CTRL_SPEED_DIV8     0x0C
#define HWMONITOR2_SET_FAN2_CTRL_SPEED_DIV1     0x00
#define HWMONITOR2_SET_FAN2_CTRL_SPEED_DIV2     0x10
#define HWMONITOR2_SET_FAN2_CTRL_SPEED_DIV4     0x20
#define HWMONITOR2_SET_FAN2_CTRL_SPEED_DIV8     0x30
#define HWMONITOR2_SET_MODE_OS_DISABLE          0x00
#define HWMONITOR2_SET_MODE_OS_ENABLE           0x01
#define HWMONITOR2_SET_MODE_RST_DISABLE         0x00
#define HWMONITOR2_SET_MODE_RST_ENABLE          0x01

/**
 * @brief HW Monitor description temperature resolution control data.
 * @details Specified temperature resolution control data for description of HW Monitor Click driver.
 */
#define HWMONITOR2_SET_TEMP_RES_8_bit           0x00
#define HWMONITOR2_SET_TEMP_RES_11_bit          0x01
#define HWMONITOR2_TEMP_RES_11_bit_BIT_MASK     0x08

/**
 * @brief HW Monitor description HWMONITOR2_REG_CHANNEL_DISABLE register value.
 * @details Specified HWMONITOR2_REG_CHANNEL_DISABLE register value for the description of HW Monitor Click driver.
 */
#define HWMONITOR2_SET_ALL_CH_ENABLE            0x00
#define HWMONITOR2_SET_ALL_CH_DISABLE           0xFF

/**
 * @brief HW Monitor description device ID data.
 * @details Specified device ID data for description of HW Monitor Click driver.
 */
#define HWMONITOR2_MANUFACTURERS_ID             0x80
#define HWMONITOR2_STEPPING_DIE_REVISION_ID     0x08

/**
 * @brief HW Monitor channel selection setting.
 * @details Specified setting for channel selection of HW Monitor Click driver.
 */
#define HWMONITOR2_CH_0                         0
#define HWMONITOR2_CH_1                         1
#define HWMONITOR2_CH_2                         2
#define HWMONITOR2_CH_3                         3
#define HWMONITOR2_CH_4                         4
#define HWMONITOR2_CH_5                         5
#define HWMONITOR2_CH_6                         6
#define HWMONITOR2_FAN_1                        0
#define HWMONITOR2_FAN_2                        1

/**
 * @brief HW Monitor 2 device address setting.
 * @details Specified setting for device slave address selection of
 * HW Monitor 2 Click driver.
 */
#define HWMONITOR2_DEVICE_ADDRESS_0             0x28
#define HWMONITOR2_DEVICE_ADDRESS_1             0x29
#define HWMONITOR2_DEVICE_ADDRESS_2             0x2A
#define HWMONITOR2_DEVICE_ADDRESS_3             0x2B
#define HWMONITOR2_DEVICE_ADDRESS_4             0x2C
#define HWMONITOR2_DEVICE_ADDRESS_5             0x2D
#define HWMONITOR2_DEVICE_ADDRESS_6             0x2E
#define HWMONITOR2_DEVICE_ADDRESS_7             0x2F

/*! @} */ // hwmonitor2_set

/**
 * @defgroup hwmonitor2_map HW Monitor 2 MikroBUS Map
 * @brief MikroBUS pin mapping of HW Monitor 2 Click driver.
 */

/**
 * @addtogroup hwmonitor2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of HW Monitor 2 Click to the selected MikroBUS.
 */
#define HWMONITOR2_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hwmonitor2_map
/*! @} */ // hwmonitor2

/**
 * @brief HW Monitor 2 Click context object.
 * @details Context object definition of HW Monitor 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;        /**< Reset pin. */

    // Input pins
    digital_in_t int_pin;     /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} hwmonitor2_t;

/**
 * @brief HW Monitor 2 Click configuration object.
 * @details Configuration object definition of HW Monitor 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;        /**< Reset pin. */
    pin_name_t int_pin;    /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} hwmonitor2_cfg_t;

/**
 * @brief HW Monitor 2 Click configuration object.
 * @details Configuration object definition of HW Monitor 2 Click driver.
 */
typedef struct
{
    uint8_t start;          /**< Enables startup of monitoring operations. */
    uint8_t int_enable;     /**< Enables the INT Interrupt output. */
    uint8_t int_pol_sel;    /**< Polarity select. */
    uint8_t int_clear;      /**< Clear the Interrupt. */
    uint8_t chas_clear;     /**< Chassis Clear. */
    uint8_t gpo;            /**< General Purpose Output. */
    uint8_t init;           /**< Restores power on the default value. */

} hwmonitor2_config_t;

/**
 * @brief HW Monitor 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HWMONITOR2_OK = 0,
    HWMONITOR2_ERROR = -1

} hwmonitor2_return_value_t;

/*!
 * @addtogroup hwmonitor2 HW Monitor 2 Click Driver
 * @brief API for configuring and manipulating HW Monitor 2 Click driver.
 * @{
 */

/**
 * @brief HW Monitor 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hwmonitor2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hwmonitor2_cfg_setup ( hwmonitor2_cfg_t *cfg );

/**
 * @brief HW Monitor 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hwmonitor2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor2_init ( hwmonitor2_t *ctx, hwmonitor2_cfg_t *cfg );

/**
 * @brief HW Monitor 2 default configuration function.
 * @details This function executes a default configuration of HW Monitor 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hwmonitor2_default_cfg ( hwmonitor2_t *ctx );

/**
 * @brief HW Monitor 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor2_generic_write ( hwmonitor2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief HW Monitor 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor2_generic_read ( hwmonitor2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief HW Monitor 2 reset function.
 * @details This function performs a hardware reset 
 * of the AMC80 System Hardware Monitor with Two-Wire and SMBus Serial Interface
 * on the HW Monitor 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void hwmonitor2_reset ( hwmonitor2_t *ctx );

/**
 * @brief HW Monitor 2 gets configuration function.
 * @details This function gets the device configuration data object
 * of the AMC80 System Hardware Monitor with Two-Wire and SMBus Serial Interface
 * on the HW Monitor 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @param[out] config : Device configuration object.
 * See #hwmonitor2_config_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor2_get_config ( hwmonitor2_t *ctx, hwmonitor2_config_t *config );

/**
 * @brief HW Monitor 2 set the configuration function.
 * @details This function set the device configuration data object
 * of the AMC80 System Hardware Monitor with Two-Wire and SMBus Serial Interface
 * on the HW Monitor 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @param[in] config : Device configuration object.
 * See #hwmonitor2_config_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor2_set_config ( hwmonitor2_t *ctx, hwmonitor2_config_t config );

/**
 * @brief HW Monitor 2 gets device ID function.
 * @details This function reads a manufacturers ID and device stepping/die revision ID
 * of the AMC80 System Hardware Monitor with Two-Wire and SMBus Serial Interface
 * on the HW Monitor 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @param[out] manufacture_id : Manufacturers ID.
 * @param[out] revision_id : Device stepping/die revision ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor2_get_device_id ( hwmonitor2_t *ctx, uint8_t *manufacture_id, uint8_t *revision_id );

/**
 * @brief HW Monitor 2 set temperature resolution function.
 * @details This function set temperature resolution
 * of the AMC80 System Hardware Monitor with Two-Wire and SMBus Serial Interface
 * on the HW Monitor 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @param[in] temp_res :
 *         @li @c 0x00 (HWMONITOR2_SET_TEMP_RES_8_bit)  - 8-bit temperature resolution,
 *         @li @c 0x01 (HWMONITOR2_SET_TEMP_RES_11_bit) - 11-bit temperature resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor2_set_temp_res ( hwmonitor2_t *ctx, uint8_t temp_res );

/**
 * @brief HW Monitor 2 set voltage/temperature channel function.
 * @details This function enables or disables voltage/temperature channel
 * of the AMC80 System Hardware Monitor with Two-Wire and SMBus Serial Interface
 * on the HW Monitor 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @param[in] ch_out : Voltage/temperature channe data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor2_set_ch_out ( hwmonitor2_t *ctx, uint8_t ch_out );

/**
 * @brief HW Monitor 2 gets temperature function.
 * @details This function reads temperature data in degrees Celsius
 * of the AMC80 System Hardware Monitor with Two-Wire and SMBus Serial Interface
 * on the HW Monitor 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @param[out] temperature : Temperature data [deg C].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor2_get_temperature ( hwmonitor2_t *ctx, float *temperature );

/**
 * @brief HW Monitor 2 gets analog inputs voltage function.
 * @details This function reads an analog inputs voltage
 * of the AMC80 System Hardware Monitor with Two-Wire and SMBus Serial Interface
 * on the HW Monitor 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @param[in] ch_pos : Analog inputs channel position [0-6].
 * @param[out] voltage : Analog inputs voltage [mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor2_get_analog_inputs ( hwmonitor2_t *ctx, uint8_t ch_pos, float *voltage );

/**
 * @brief HW Monitor 2 gets FAN output function.
 * @details This function reads a FAN tachometer output data
 * of the AMC80 System Hardware Monitor with Two-Wire and SMBus Serial Interface
 * on the HW Monitor 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @param[in] fan_pos : FAN tachometer inputs position [0-1].
 * @param[out] fan_output : FAN tachometer output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hwmonitor2_get_fan_output ( hwmonitor2_t *ctx, uint8_t fan_pos, uint8_t *fan_output );

/**
 * @brief HW Monitor 2 gets interrupt function.
 * @details This function gets states of the Interrupt ( INT ) pin
 * of the AMC80 System Hardware Monitor with Two-Wire and SMBus Serial Interface
 * on the HW Monitor 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #hwmonitor2_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t hwmonitor2_get_int_pin ( hwmonitor2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HWMONITOR2_H

/*! @} */ // hwmonitor2

// ------------------------------------------------------------------------ END
