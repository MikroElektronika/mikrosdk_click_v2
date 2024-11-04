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
 * @file powermonitor2.h
 * @brief This file contains API for Power Monitor 2 Click Driver.
 */

#ifndef POWERMONITOR2_H
#define POWERMONITOR2_H

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
 * @addtogroup powermonitor2 Power Monitor 2 Click Driver
 * @brief API for configuring and manipulating Power Monitor 2 Click driver.
 * @{
 */

/**
 * @defgroup powermonitor2_reg Power Monitor 2 Registers List
 * @brief List of registers of Power Monitor 2 Click driver.
 */

/**
 * @addtogroup powermonitor2_reg
 * @{
 */

/**
 * @brief Power Monitor 2 register list.
 * @details Specified register list of Power Monitor 2 Click driver.
 */
#define POWERMONITOR2_REG_CONFIGURATION                 0x00
#define POWERMONITOR2_REG_SHUNT_VOLTAGE                 0x01
#define POWERMONITOR2_REG_BUS_VOLTAGE                   0x02
#define POWERMONITOR2_REG_POWER                         0x03
#define POWERMONITOR2_REG_CURRENT                       0x04
#define POWERMONITOR2_REG_CALIBRATION                   0x05

/*! @} */ // powermonitor2_reg

/**
 * @defgroup powermonitor2_set Power Monitor 2 Registers Settings
 * @brief Settings for registers of Power Monitor 2 Click driver.
 */

/**
 * @addtogroup powermonitor2_set
 * @{
 */

/**
 * @brief Power Monitor 2 CONFIGURATION register setting.
 * @details Specified setting for CONFIGURATION register of Power Monitor 2 Click driver.
 */
#define POWERMONITOR2_CONFIGURATION_RST                 0x8000
#define POWERMONITOR2_CONFIGURATION_BRNG_16V            0x0000
#define POWERMONITOR2_CONFIGURATION_BRNG_32V            0x2000
#define POWERMONITOR2_CONFIGURATION_BRNG_MASK           0x2000
#define POWERMONITOR2_CONFIGURATION_PGA_DIV_1           0x0000
#define POWERMONITOR2_CONFIGURATION_PGA_DIV_2           0x0800
#define POWERMONITOR2_CONFIGURATION_PGA_DIV_4           0x1000
#define POWERMONITOR2_CONFIGURATION_PGA_DIV_8           0x1800
#define POWERMONITOR2_CONFIGURATION_PGA_MASK            0x1800
#define POWERMONITOR2_CONFIGURATION_BADC_84_US          0x0000
#define POWERMONITOR2_CONFIGURATION_BADC_148_US         0x0080
#define POWERMONITOR2_CONFIGURATION_BADC_276_US         0x0100
#define POWERMONITOR2_CONFIGURATION_BADC_532_US         0x0180
#define POWERMONITOR2_CONFIGURATION_BADC_1_06_MS        0x0480
#define POWERMONITOR2_CONFIGURATION_BADC_2_13_MS        0x0500
#define POWERMONITOR2_CONFIGURATION_BADC_4_26_MS        0x0580
#define POWERMONITOR2_CONFIGURATION_BADC_8_51_MS        0x0600
#define POWERMONITOR2_CONFIGURATION_BADC_17_02_MS       0x0680
#define POWERMONITOR2_CONFIGURATION_BADC_34_05_MS       0x0700
#define POWERMONITOR2_CONFIGURATION_BADC_68_10_MS       0x0780
#define POWERMONITOR2_CONFIGURATION_BADC_MASK           0x0780
#define POWERMONITOR2_CONFIGURATION_SADC_84_US          0x0000
#define POWERMONITOR2_CONFIGURATION_SADC_148_US         0x0008
#define POWERMONITOR2_CONFIGURATION_SADC_276_US         0x0010
#define POWERMONITOR2_CONFIGURATION_SADC_532_US         0x0018
#define POWERMONITOR2_CONFIGURATION_SADC_1_06_MS        0x0048
#define POWERMONITOR2_CONFIGURATION_SADC_2_13_MS        0x0050
#define POWERMONITOR2_CONFIGURATION_SADC_4_26_MS        0x0058
#define POWERMONITOR2_CONFIGURATION_SADC_8_51_MS        0x0060
#define POWERMONITOR2_CONFIGURATION_SADC_17_02_MS       0x0068
#define POWERMONITOR2_CONFIGURATION_SADC_34_05_MS       0x0070
#define POWERMONITOR2_CONFIGURATION_SADC_68_10_MS       0x0078
#define POWERMONITOR2_CONFIGURATION_SADC_MASK           0x0078
#define POWERMONITOR2_CONFIGURATION_MODE_PDOWN          0x0000
#define POWERMONITOR2_CONFIGURATION_MODE_SHT_V_TRG      0x0001
#define POWERMONITOR2_CONFIGURATION_MODE_BUS_V_TRG      0x0002
#define POWERMONITOR2_CONFIGURATION_MODE_SHT_BUS_V_TRG  0x0003
#define POWERMONITOR2_CONFIGURATION_MODE_ADC_OFF        0x0004
#define POWERMONITOR2_CONFIGURATION_MODE_SHT_V_CONT     0x0005
#define POWERMONITOR2_CONFIGURATION_MODE_BUS_V_CONT     0x0006
#define POWERMONITOR2_CONFIGURATION_MODE_SHT_BUS_V_CONT 0x0007
#define POWERMONITOR2_CONFIGURATION_MODE_MASK           0x0007

/**
 * @brief Power Monitor 2 BUS_VOLTAGE register setting.
 * @details Specified setting for BUS_VOLTAGE register of Power Monitor 2 Click driver.
 */
#define POWERMONITOR2_BUS_VOLTAGE_CNVR                  0x0002
#define POWERMONITOR2_BUS_VOLTAGE_OVF                   0x0001

/**
 * @brief Power Monitor 2 calculation setting.
 * @details Specified setting for calculation of Power Monitor 2 Click driver.
 */
#define POWERMONITOR2_SHUNT_LSB_MV                      0.01f
#define POWERMONITOR2_BUS_V_LSB_V                       0.004f
#define POWERMONITOR2_POWER_LSB_W                       0.02f
#define POWERMONITOR2_CURRENT_LSB_A                     0.001f
#define POWERMONITOR2_CALIBRATION_FOR_SHUNT_0_01_OHM    4096
#define POWERMONITOR2_DEFAULT_NUM_CONV                  20

/**
 * @brief Power Monitor 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Power Monitor 2 Click driver.
 */
#define POWERMONITOR2_DEVICE_ADDRESS_3V3_0              0x40
#define POWERMONITOR2_DEVICE_ADDRESS_3V3_1              0x44
#define POWERMONITOR2_DEVICE_ADDRESS_5V_0               0x41
#define POWERMONITOR2_DEVICE_ADDRESS_5V_1               0x45

/*! @} */ // powermonitor2_set

/**
 * @defgroup powermonitor2_map Power Monitor 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Power Monitor 2 Click driver.
 */

/**
 * @addtogroup powermonitor2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Power Monitor 2 Click to the selected MikroBUS.
 */
#define POWERMONITOR2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // powermonitor2_map
/*! @} */ // powermonitor2

/**
 * @brief Power Monitor 2 Click data object.
 * @details Data object definition of Power Monitor 2 Click driver.
 */
typedef struct
{
    float shunt_mv;             /**< Shunt voltage in mV. */
    float bus_v;                /**< Bus voltage. */
    float current;              /**< Current. */
    float power;                /**< Power. */

} powermonitor2_data_t;

/**
 * @brief Power Monitor 2 Click context object.
 * @details Context object definition of Power Monitor 2 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint8_t address_3v3;        /**< 3v3 device slave address. */
    uint8_t address_5v;         /**< 5v device slave address. */

} powermonitor2_t;

/**
 * @brief Power Monitor 2 Click configuration object.
 * @details Configuration object definition of Power Monitor 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address_3v3; /**< 3v3 I2C slave address. */
    uint8_t    i2c_address_5v;  /**< 5v I2C slave address. */

} powermonitor2_cfg_t;

/**
 * @brief Power Monitor 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    POWERMONITOR2_OK = 0,
    POWERMONITOR2_ERROR = -1

} powermonitor2_return_value_t;

/*!
 * @addtogroup powermonitor2 Power Monitor 2 Click Driver
 * @brief API for configuring and manipulating Power Monitor 2 Click driver.
 * @{
 */

/**
 * @brief Power Monitor 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #powermonitor2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void powermonitor2_cfg_setup ( powermonitor2_cfg_t *cfg );

/**
 * @brief Power Monitor 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #powermonitor2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #powermonitor2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powermonitor2_init ( powermonitor2_t *ctx, powermonitor2_cfg_t *cfg );

/**
 * @brief Power Monitor 2 default configuration function.
 * @details This function executes a default configuration of Power Monitor 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #powermonitor2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t powermonitor2_default_cfg ( powermonitor2_t *ctx );

/**
 * @brief Power Monitor 2 set slave address function.
 * @details This function sets the device slave address.
 * @param[in] ctx : Click context object.
 * See #powermonitor2_t object definition for detailed explanation.
 * @param[in] slave_address : I2C device slave address, should be ctx->address_3v3 or ctx->address_5v.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powermonitor2_set_address ( powermonitor2_t *ctx, uint8_t slave_address );

/**
 * @brief Power Monitor 2 write reg function.
 * @details This function writes a data word to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #powermonitor2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powermonitor2_write_reg ( powermonitor2_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Power Monitor 2 read reg function.
 * @details This function reads a data word from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #powermonitor2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : 16-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powermonitor2_read_reg ( powermonitor2_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Power Monitor 2 read data function.
 * @details This function reads the shunt voltage, bus voltage, current, and power data measurements.
 * @param[in] ctx : Click context object.
 * See #powermonitor2_t object definition for detailed explanation.
 * @param[out] data_out : Power monitor data measurements.
 * See #powermonitor2_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powermonitor2_read_data ( powermonitor2_t *ctx, powermonitor2_data_t *data_out );

/**
 * @brief Power Monitor 2 read data avg function.
 * @details This function reads the shunt voltage, bus voltage, current, and power data measurements
 * averaged from num_conv samples.
 * @param[in] ctx : Click context object.
 * See #powermonitor2_t object definition for detailed explanation.
 * @param[in] num_conv : Number of conversion samples.
 * @param[out] data_out : Power monitor data measurements.
 * See #powermonitor2_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powermonitor2_read_data_avg ( powermonitor2_t *ctx, uint16_t num_conv, powermonitor2_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // POWERMONITOR2_H

/*! @} */ // powermonitor2

// ------------------------------------------------------------------------ END
