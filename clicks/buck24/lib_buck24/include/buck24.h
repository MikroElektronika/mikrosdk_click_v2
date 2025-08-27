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
 * @file buck24.h
 * @brief This file contains API for Buck 24 Click Driver.
 */

#ifndef BUCK24_H
#define BUCK24_H

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
 * @addtogroup buck24 Buck 24 Click Driver
 * @brief API for configuring and manipulating Buck 24 Click driver.
 * @{
 */

/**
 * @defgroup buck24_reg Buck 24 Registers List
 * @brief List of registers of Buck 24 Click driver.
 */

/**
 * @addtogroup buck24_reg
 * @{
 */

/**
 * @brief Buck 24 register list.
 * @details Specified register list of Buck 24 Click driver.
 */
#define BUCK24_REG_CONFIGURATION                    0x00
#define BUCK24_REG_SHUNT_VOLTAGE                    0x01
#define BUCK24_REG_BUS_VOLTAGE                      0x02
#define BUCK24_REG_POWER                            0x03
#define BUCK24_REG_CURRENT                          0x04
#define BUCK24_REG_CALIBRATION                      0x05

/*! @} */ // buck24_reg

/**
 * @defgroup buck24_set Buck 24 Registers Settings
 * @brief Settings for registers of Buck 24 Click driver.
 */

/**
 * @addtogroup buck24_set
 * @{
 */

/**
 * @brief Buck 24 CONFIGURATION register setting.
 * @details Specified setting for CONFIGURATION register of Buck 24 Click driver.
 */
#define BUCK24_CONFIGURATION_RST                    0x8000
#define BUCK24_CONFIGURATION_BRNG_16V               0x0000
#define BUCK24_CONFIGURATION_BRNG_32V               0x2000
#define BUCK24_CONFIGURATION_BRNG_MASK              0x2000
#define BUCK24_CONFIGURATION_PGA_DIV_1              0x0000
#define BUCK24_CONFIGURATION_PGA_DIV_2              0x0800
#define BUCK24_CONFIGURATION_PGA_DIV_4              0x1000
#define BUCK24_CONFIGURATION_PGA_DIV_8              0x1800
#define BUCK24_CONFIGURATION_PGA_MASK               0x1800
#define BUCK24_CONFIGURATION_BADC_84_US             0x0000
#define BUCK24_CONFIGURATION_BADC_148_US            0x0080
#define BUCK24_CONFIGURATION_BADC_276_US            0x0100
#define BUCK24_CONFIGURATION_BADC_532_US            0x0180
#define BUCK24_CONFIGURATION_BADC_1_06_MS           0x0480
#define BUCK24_CONFIGURATION_BADC_2_13_MS           0x0500
#define BUCK24_CONFIGURATION_BADC_4_26_MS           0x0580
#define BUCK24_CONFIGURATION_BADC_8_51_MS           0x0600
#define BUCK24_CONFIGURATION_BADC_17_02_MS          0x0680
#define BUCK24_CONFIGURATION_BADC_34_05_MS          0x0700
#define BUCK24_CONFIGURATION_BADC_68_10_MS          0x0780
#define BUCK24_CONFIGURATION_BADC_MASK              0x0780
#define BUCK24_CONFIGURATION_SADC_84_US             0x0000
#define BUCK24_CONFIGURATION_SADC_148_US            0x0008
#define BUCK24_CONFIGURATION_SADC_276_US            0x0010
#define BUCK24_CONFIGURATION_SADC_532_US            0x0018
#define BUCK24_CONFIGURATION_SADC_1_06_MS           0x0048
#define BUCK24_CONFIGURATION_SADC_2_13_MS           0x0050
#define BUCK24_CONFIGURATION_SADC_4_26_MS           0x0058
#define BUCK24_CONFIGURATION_SADC_8_51_MS           0x0060
#define BUCK24_CONFIGURATION_SADC_17_02_MS          0x0068
#define BUCK24_CONFIGURATION_SADC_34_05_MS          0x0070
#define BUCK24_CONFIGURATION_SADC_68_10_MS          0x0078
#define BUCK24_CONFIGURATION_SADC_MASK              0x0078
#define BUCK24_CONFIGURATION_MODE_PDOWN             0x0000
#define BUCK24_CONFIGURATION_MODE_SHT_V_TRG         0x0001
#define BUCK24_CONFIGURATION_MODE_BUS_V_TRG         0x0002
#define BUCK24_CONFIGURATION_MODE_SHT_BUS_V_TRG     0x0003
#define BUCK24_CONFIGURATION_MODE_ADC_OFF           0x0004
#define BUCK24_CONFIGURATION_MODE_SHT_V_CONT        0x0005
#define BUCK24_CONFIGURATION_MODE_BUS_V_CONT        0x0006
#define BUCK24_CONFIGURATION_MODE_SHT_BUS_V_CONT    0x0007
#define BUCK24_CONFIGURATION_MODE_MASK              0x0007

/**
 * @brief Buck 24 BUS_VOLTAGE register setting.
 * @details Specified setting for BUS_VOLTAGE register of Buck 24 Click driver.
 */
#define BUCK24_BUS_VOLTAGE_CNVR                     0x0002
#define BUCK24_BUS_VOLTAGE_OVF                      0x0001

/**
 * @brief Buck 24 calculation setting.
 * @details Specified setting for calculation of Buck 24 Click driver.
 */
#define BUCK24_SHUNT_LSB_MV                         0.01f
#define BUCK24_BUS_V_LSB_V                          0.004f
#define BUCK24_POWER_LSB_W                          0.02f
#define BUCK24_CURRENT_LSB_A                        0.001f
#define BUCK24_CALIBRATION_FOR_SHUNT_0_01_OHM       4096
#define BUCK24_DEFAULT_NUM_CONV                     20

/**
 * @brief Buck 24 device address setting.
 * @details Specified setting for device slave address selection of
 * Buck 24 Click driver.
 */
#define BUCK24_DEVICE_ADDRESS_0                     0x40
#define BUCK24_DEVICE_ADDRESS_1                     0x41

/*! @} */ // buck24_set

/**
 * @defgroup buck24_map Buck 24 MikroBUS Map
 * @brief MikroBUS pin mapping of Buck 24 Click driver.
 */

/**
 * @addtogroup buck24_map
 * @{
 */

/**
 * @brief Buck 24 Click data object.
 * @details Data object definition of Buck 24 Click driver.
 */
typedef struct
{
    float shunt_mv;             /**< Shunt voltage in mV. */
    float bus_v;                /**< Bus voltage. */
    float current;              /**< Current. */
    float power;                /**< Power. */

} buck24_data_t;

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buck 24 Click to the selected MikroBUS.
 */
#define BUCK24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // buck24_map
/*! @} */ // buck24

/**
 * @brief Buck 24 Click context object.
 * @details Context object definition of Buck 24 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset/Disable pin (active low). */

    // Input pins
    digital_in_t pg;            /**< Power good indication pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} buck24_t;

/**
 * @brief Buck 24 Click configuration object.
 * @details Configuration object definition of Buck 24 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset/Disable pin (active low). */
    pin_name_t pg;              /**< Power good indication pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} buck24_cfg_t;

/**
 * @brief Buck 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUCK24_OK = 0,
    BUCK24_ERROR = -1

} buck24_return_value_t;

/*!
 * @addtogroup buck24 Buck 24 Click Driver
 * @brief API for configuring and manipulating Buck 24 Click driver.
 * @{
 */

/**
 * @brief Buck 24 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buck24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buck24_cfg_setup ( buck24_cfg_t *cfg );

/**
 * @brief Buck 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #buck24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buck24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck24_init ( buck24_t *ctx, buck24_cfg_t *cfg );

/**
 * @brief Buck 24 default configuration function.
 * @details This function executes a default configuration of Buck 24
 * Click board.
 * @param[in] ctx : Click context object.
 * See #buck24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t buck24_default_cfg ( buck24_t *ctx );

/**
 * @brief Buck 24 enable device function.
 * @details This function sets the RST pin to high logic level to enable the device.
 * @param[in] ctx : Click context object.
 * See #buck24_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void buck24_enable_device ( buck24_t *ctx );

/**
 * @brief Buck 24 disable device function.
 * @details This function sets the RST pin to low logic level to disable the device.
 * @param[in] ctx : Click context object.
 * See #buck24_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void buck24_disable_device ( buck24_t *ctx );

/**
 * @brief Buck 24 get power-good pin function.
 * @details This function reads the logic level of the PG (power-good) pin.
 * @param[in] ctx : Click context object.
 * See #buck24_t object definition for detailed explanation.
 * @return Logic state of the PG pin.
 * @note None.
 */
uint8_t buck24_get_pg_pin ( buck24_t *ctx );

/**
 * @brief Buck 24 write register function.
 * @details This function writes a 16-bit data value to the specified register.
 * @param[in] ctx : Click context object.
 * See #buck24_t object definition for detailed explanation.
 * @param[in] reg : Register address (valid range: 0x00 to 0x05).
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t buck24_write_reg ( buck24_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Buck 24 read register function.
 * @details This function reads a 16-bit data value from the specified register.
 * @param[in] ctx : Click context object.
 * See #buck24_t object definition for detailed explanation.
 * @param[in] reg : Register address (valid range: 0x00 to 0x05).
 * @param[out] data_out : Pointer to 16-bit variable where read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t buck24_read_reg ( buck24_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Buck 24 read measurement data function.
 * @details This function reads shunt voltage, bus voltage, current, and power measurements from the device.
 * @param[in] ctx : Click context object.
 * See #buck24_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to structure where measurement data will be stored.
 * See #buck24_data_t structure definition.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t buck24_read_data ( buck24_t *ctx, buck24_data_t *data_out );

/**
 * @brief Buck 24 read averaged measurement data function.
 * @details This function reads multiple samples of measurement data and returns their average values.
 * @param[in] ctx : Click context object.
 * See #buck24_t object definition for detailed explanation.
 * @param[in] num_conv : Number of measurement conversions to average.
 * @param[out] data_out : Pointer to structure where averaged data will be stored.
 * See #buck24_data_t structure definition.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t buck24_read_data_avg ( buck24_t *ctx, uint16_t num_conv, buck24_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // BUCK24_H

/*! @} */ // buck24

// ------------------------------------------------------------------------ END
