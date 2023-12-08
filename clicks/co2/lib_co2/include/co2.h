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
 * @file co2.h
 * @brief This file contains API for CO2 Click Driver.
 */

#ifndef CO2_H
#define CO2_H

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
 * @addtogroup co2 CO2 Click Driver
 * @brief API for configuring and manipulating CO2 Click driver.
 * @{
 */

/**
 * @defgroup co2_reg CO2 Registers List
 * @brief List of registers of CO2 Click driver.
 */

/**
 * @addtogroup co2_reg
 * @{
 */

/**
 * @brief CO2 description register.
 * @details Specified register for description of CO2 Click driver.
 */
#define CO2_REG_DISABLE_CRC                 0x3768
#define CO2_REG_SET_BINARY_GAS              0x3615
#define CO2_REG_SET_RELATIVE_HUMIDITY       0x3624
#define CO2_REG_SET_TEMPERATURE             0x361E
#define CO2_REG_SET_PRESSURE                0x362F
#define CO2_REG_MEASURE_GAS_CONCENTRATION   0x3639
#define CO2_REG_FORCED_RECALIBRATION        0x3661
#define CO2_REG_ENABLE_AUTO_SELF_CALIB      0x3FEF
#define CO2_REG_DISABLE_AUTO_SELF_CALIB     0x3F6E
#define CO2_REG_PREPARE_READ_STATE          0x3752
#define CO2_REG_READ_STATE                  0xE133
#define CO2_REG_WRITE_STATE                 0xE133
#define CO2_REG_APPLY_STATE                 0x3650
#define CO2_REG_SELF_TEST                   0x365B
#define CO2_REG_RESET                       0x0006
#define CO2_REG_ENTER_SLEEP_MODE            0x3677

/*! @} */ // co2_reg

/**
 * @defgroup co2_set CO2 Registers Settings
 * @brief Settings for registers of CO2 Click driver.
 */

/**
 * @addtogroup co2_set
 * @{
 */

/**
 * @brief CO2 description setting.
 * @details Specified setting for description of CO2 Click driver.
 */
#define CO2_SET_BINARY_GAS_IN_N2_100PCT     0x0000
#define CO2_SET_BINARY_GAS_IN_AIR_100PCT    0x0001
#define CO2_SET_BINARY_GAS_IN_N2_25PCT      0x0002
#define CO2_SET_BINARY_GAS_IN_AIR_25PCT     0x0003

#define CO2_DEVICE_ID                       0x08010301

/**
 * @brief CO2 device address setting.
 * @details Specified setting for device slave address selection of
 * CO2 Click driver.
 */
#define CO2_SET_DEV_ADDR_GND                0x29
#define CO2_SET_DEV_ADDR_1KOHMS             0x2C
#define CO2_SET_DEV_ADDR_3p3KOHMS           0x2B
#define CO2_SET_DEV_ADDR_10KOHMS            0x2A

/*! @} */ // co2_set

/**
 * @defgroup co2_map CO2 MikroBUS Map
 * @brief MikroBUS pin mapping of CO2 Click driver.
 */

/**
 * @addtogroup co2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of CO2 Click to the selected MikroBUS.
 */
#define CO2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); 

/*! @} */ // co2_map
/*! @} */ // co2

/**
 * @brief CO2 Click context object.
 * @details Context object definition of CO2 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */
    
    // Device & serial IDs
    uint32_t device_id;
    uint32_t serial_id[ 2 ];
    uint8_t crc_enabled;

} co2_t;

/**
 * @brief CO2 Click configuration object.
 * @details Configuration object definition of CO2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} co2_cfg_t;

/**
 * @brief CO2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   CO2_OK = 0,
   CO2_ERROR = -1,
   CO2_ERROR_SELF_TEST = -2,
   CO2_ERROR_CRC = -3

} co2_return_value_t;

/*!
 * @addtogroup co2 CO2 Click Driver
 * @brief API for configuring and manipulating CO2 Click driver.
 * @{
 */

/**
 * @brief CO2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #co2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void co2_cfg_setup ( co2_cfg_t *cfg );

/**
 * @brief CO2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #co2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #co2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co2_init ( co2_t *ctx, co2_cfg_t *cfg );

/**
 * @brief CO2 default configuration function.
 * @details This function executes a default configuration of CO2
 * click board.
 * @param[in] ctx : Click context object.
 * See #co2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *         @li @c -2 - Error self-test.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t co2_default_cfg ( co2_t *ctx );

/**
 * @brief CO2 I2C writing function.
 * @details This function writes a desired number of data starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #co2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of words to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co2_generic_write ( co2_t *ctx, uint16_t reg, uint16_t *tx_buf, uint8_t tx_len );

/**
 * @brief CO2 I2C reading function.
 * @details This function reads a desired number of data starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #co2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of words to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -3 - CRC Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t co2_generic_read ( co2_t *ctx, uint16_t reg, uint16_t *rx_buf, uint8_t rx_len );

/**
 * @brief Reset device.
 * @details This function sends command to reset device.
 * @param[in] ctx : Click context object.
 * See #co2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t co2_reset ( co2_t *ctx );

/**
 * @brief Read device and serial ID's.
 * @details This function reads device and serial ID's and set 
 * places that data in the context object.
 * @param[in,out] ctx : Click context object.
 * See #co2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t co2_get_id ( co2_t *ctx );

/**
 * @brief Set device refrence values for gas calculation.
 * @details This function set reference values for device to calculate gas 
 * concetration. If reference values aren't set device will look at them like 0.
 * @param[in] ctx : Click context object.
 * See #co2_t object definition for detailed explanation.
 * @param[in] humidity : Humidity value in %.
 * @param[in] pressure : Pressure value in mBar.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t co2_set_reference ( co2_t *ctx, uint16_t humidity, uint16_t pressure );

/**
 * @brief Read CO2 concentration and temperature value.
 * @details This function reads CO2 gas concentration and temperature from device.
 * @param[in] ctx : Click context object.
 * See #co2_t object definition for detailed explanation.
 * @param[out] gas_concentration : CO2 concentartion data in %.
 * @param[out] temperature : Temperature data in degC.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t co2_read_gas ( co2_t *ctx, float *gas_concentration, float *temperature );

/**
 * @brief Disable use of CRC.
 * @details This function sends command to disable crc data for device.
 * @param[in] ctx : Click context object.
 * See #co2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note For safety related applications it is strongly recommended 
 * to not disable the CRC.
 */
err_t co2_disable_crc ( co2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CO2_H

/*! @} */ // co2

// ------------------------------------------------------------------------ END
