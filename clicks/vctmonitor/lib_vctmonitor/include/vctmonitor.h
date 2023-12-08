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
 * @file vctmonitor.h
 * @brief This file contains API for VCT Monitor Click Driver.
 */

#ifndef VCTMONITOR_H
#define VCTMONITOR_H

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
 * @addtogroup vctmonitor VCT Monitor Click Driver
 * @brief API for configuring and manipulating VCT Monitor Click driver.
 * @{
 */

/**
 * @defgroup vctmonitor_reg VCT Monitor Registers List
 * @brief List of registers of VCT Monitor Click driver.
 */

/**
 * @addtogroup vctmonitor_reg
 * @{
 */

/**
 * @brief VCT Monitor description register.
 * @details Specified register for description of VCT Monitor Click driver.
 */
#define VCTMONITOR_REG_STATUS            0x00
#define VCTMONITOR_REG_CONTROL           0x01
#define VCTMONITOR_REG_TRIGGER           0x02
#define VCTMONITOR_REG_AMB_TEMP_MSB      0x04
#define VCTMONITOR_REG_AMB_TEMP_LSB      0x05
#define VCTMONITOR_REG_V1_MSB            0x06
#define VCTMONITOR_REG_V1_LSB            0x07
#define VCTMONITOR_REG_V2_MSB            0x08
#define VCTMONITOR_REG_V2_LSB            0x09
#define VCTMONITOR_REG_V3_MSB            0x0A
#define VCTMONITOR_REG_V3_LSB            0x0B
#define VCTMONITOR_REG_V4_MSB            0x0C
#define VCTMONITOR_REG_V4_LSB            0x0D
#define VCTMONITOR_REG_VCC_MSB           0x0E
#define VCTMONITOR_REG_VCC_LSB           0x0F

/*! @} */ // vctmonitor_reg

/**
 * @defgroup vctmonitor_set VCT Monitor Registers Settings
 * @brief Settings for registers of VCT Monitor Click driver.
 */

/**
 * @addtogroup vctmonitor_set
 * @{
 */

/**
 * @brief VCT Monitor description setting.
 * @details Specified setting for description of VCT Monitor Click driver.
 */
#define VCTMONITOR_CTRL_TEMP_FORMAT_C    0x00
#define VCTMONITOR_CTRL_TEMP_FORMAT_K    0x80
#define VCTMONITOR_CTRL_REPEATED_MEAS    0x00
#define VCTMONITOR_CTRL_SINGLE_MEAS      0x40
#define VCTMONITOR_CTRL_MODE1_INT_TEMP   0x00
#define VCTMONITOR_CTRL_MODE1_V12        0x08
#define VCTMONITOR_CTRL_MODE1_V34        0x10
#define VCTMONITOR_CTRL_MODE1_ALL        0x18

#define VCTMONITOR_CTRL_MODE2_V12_TR2    0x00
#define VCTMONITOR_CTRL_MODE2_V1_2_TR2   0x01
#define VCTMONITOR_CTRL_MODE2_V1_2_V34   0x02
#define VCTMONITOR_CTRL_MODE2_V34_TR1    0x03
#define VCTMONITOR_CTRL_MODE2_V3_4_TR1   0x04
#define VCTMONITOR_CTRL_MODE2_TR2_TR1    0x05
#define VCTMONITOR_CTRL_MODE2_V1_2_V3_4  0x06
#define VCTMONITOR_CTRL_MODE2_V1234      0x07

#define VCTMONITOR_STATUS_VCC_READY      0x40
#define VCTMONITOR_STATUS_V4_READY       0x20
#define VCTMONITOR_STATUS_V3_READY       0x10
#define VCTMONITOR_STATUS_V2_READY       0x08
#define VCTMONITOR_STATUS_V1_READY       0x04
#define VCTMONITOR_STATUS_TINT_READY     0x02
#define VCTMONITOR_STATUS_BUSY           0x01


/**
 * @brief VCT Monitor device address setting.
 * @details Specified setting for device slave address selection of
 * VCT Monitor Click driver.
 */
#define VCTMONITOR_SLAVE_ADDR_GND_GND    0x4C
#define VCTMONITOR_SLAVE_ADDR_GND_VCC    0x4D
#define VCTMONITOR_SLAVE_ADDR_VCC_VCC    0x4F
#define VCTMONITOR_SLAVE_ADDR_VCC_GND    0x4E

/*! @} */ // vctmonitor_set

/**
 * @defgroup vctmonitor_map VCT Monitor MikroBUS Map
 * @brief MikroBUS pin mapping of VCT Monitor Click driver.
 */

/**
 * @addtogroup vctmonitor_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of VCT Monitor Click to the selected MikroBUS.
 */
#define VCTMONITOR_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // vctmonitor_map
/*! @} */ // vctmonitor

/**
 * @brief VCT Monitor Click context object.
 * @details Context object definition of VCT Monitor Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} vctmonitor_t;

/**
 * @brief VCT Monitor Click configuration object.
 * @details Configuration object definition of VCT Monitor Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} vctmonitor_cfg_t;

/**
 * @brief VCT Monitor Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   VCTMONITOR_OK = 0,
   VCTMONITOR_ERROR = -1

} vctmonitor_return_value_t;

/*!
 * @addtogroup vctmonitor VCT Monitor Click Driver
 * @brief API for configuring and manipulating VCT Monitor Click driver.
 * @{
 */

/**
 * @brief VCT Monitor configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vctmonitor_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vctmonitor_cfg_setup ( vctmonitor_cfg_t *cfg );

/**
 * @brief VCT Monitor initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #vctmonitor_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vctmonitor_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vctmonitor_init ( vctmonitor_t *ctx, vctmonitor_cfg_t *cfg );

/**
 * @brief VCT Monitor default configuration function.
 * @details This function executes a default configuration of VCT Monitor
 * click board.
 * @param[in] ctx : Click context object.
 * See #vctmonitor_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t vctmonitor_default_cfg ( vctmonitor_t *ctx );

/**
 * @brief VCT Monitor I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vctmonitor_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vctmonitor_generic_write ( vctmonitor_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief VCT Monitor I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vctmonitor_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vctmonitor_generic_read ( vctmonitor_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Gets status value.
 * @details This function reads status register value by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vctmonitor_t object definition for detailed explanation.
 * @return The status value read from the register
 */
uint8_t vctmonitor_get_status ( vctmonitor_t *ctx );

/**
 * @brief Configuration function
 * @details This function is used for configuration paramethers of VCT Monitor
 * click board.
 * @param[in] ctx : Click context object.
 * See #vctmonitor_t object definition for detailed explanation.
 * @param[in] cfg : Config data
 * @return Nothing.
 */
void vctmonitor_configuration ( vctmonitor_t *ctx, uint8_t cfg );

/**
 * @brief Get temperature function
 * @details This function reads temperature value by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vctmonitor_t object definition for detailed explanation.
 * @return External temperature value in C
 */
float vctmonitor_read_temperature ( vctmonitor_t *ctx );

/**
 * @brief Differential voltage function
 * @details This function reads differential voltage value by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vctmonitor_t object definition for detailed explanation.
 * @return Differential voltage on the terminal in mV
 * 
 * @note Differential voltages can have input
 *       values in the range of �0.300V to 0.300V.
 */
float vctmonitor_read_voltage_differential ( vctmonitor_t *ctx );

/**
 * @brief Single voltage function
 * @details This function reads single voltage value by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vctmonitor_t object definition for detailed explanation.
 * @param[in] channel : Channel V1 or V2 for a single measurement
 * @return Single voltage on the channel in mV
 * 
 * @note Single-ended voltages are limited to positive values in
 *       the range 0V to 3.5V.
 */
float vctmonitor_read_voltage_single ( vctmonitor_t *ctx, uint8_t channel );

/**
 * @brief Current function
 * @details This function reads current value by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vctmonitor_t object definition for detailed explanation.
 * @return Current value in mA
 */
float vctmonitor_read_current ( vctmonitor_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // VCTMONITOR_H

/*! @} */ // vctmonitor

// ------------------------------------------------------------------------ END
