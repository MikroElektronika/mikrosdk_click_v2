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
 * @file i2cmux7.h
 * @brief This file contains API for I2C MUX 7 Click Driver.
 */

#ifndef I2CMUX7_H
#define I2CMUX7_H

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
 * @addtogroup i2cmux7 I2C MUX 7 Click Driver
 * @brief API for configuring and manipulating I2C MUX 7 Click driver.
 * @{
 */

/**
 * @defgroup i2cmux7_set I2C MUX 7 Settings
 * @brief Settings of I2C MUX 7 Click driver.
 */

/**
 * @addtogroup i2cmux7_set
 * @{
 */

/**
 * @brief I2C MUX 7 channel selection values.
 * @details Specified channel selection values of I2C MUX 7 Click driver.
 */
#define I2CMUX7_CHANNEL_DISABLE             0x00
#define I2CMUX7_CHANNEL_0                   0x08
#define I2CMUX7_CHANNEL_1                   0x09
#define I2CMUX7_CHANNEL_2                   0x0A
#define I2CMUX7_CHANNEL_3                   0x0B
#define I2CMUX7_CHANNEL_4                   0x0C
#define I2CMUX7_CHANNEL_5                   0x0D
#define I2CMUX7_CHANNEL_6                   0x0E
#define I2CMUX7_CHANNEL_7                   0x0F
#define I2CMUX7_CHANNEL_NUM_MASK            0x07

/**
 * @brief I2C MUX 7 device address setting.
 * @details Specified setting for device slave address selection of
 * I2C MUX 7 Click driver.
 */
#define I2CMUX7_DEV_ADDR_A2A1A0_000         0x70
#define I2CMUX7_DEV_ADDR_A2A1A0_001         0x71
#define I2CMUX7_DEV_ADDR_A2A1A0_010         0x72
#define I2CMUX7_DEV_ADDR_A2A1A0_011         0x73
#define I2CMUX7_DEV_ADDR_A2A1A0_100         0x74
#define I2CMUX7_DEV_ADDR_A2A1A0_101         0x75
#define I2CMUX7_DEV_ADDR_A2A1A0_110         0x76
#define I2CMUX7_DEV_ADDR_A2A1A0_111         0x77

/*! @} */ // i2cmux7_set

/**
 * @defgroup i2cmux7_map I2C MUX 7 MikroBUS Map
 * @brief MikroBUS pin mapping of I2C MUX 7 Click driver.
 */

/**
 * @addtogroup i2cmux7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C MUX 7 Click to the selected MikroBUS.
 */
#define I2CMUX7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // i2cmux7_map
/*! @} */ // i2cmux7

/**
 * @brief I2C MUX 7 Click context object.
 * @details Context object definition of I2C MUX 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Reset pin (Active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    uint8_t ch_slave_address;   /**< Channel device slave address (used for I2C driver). */

} i2cmux7_t;

/**
 * @brief I2C MUX 7 Click configuration object.
 * @details Configuration object definition of I2C MUX 7 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;            /**< Reset pin (Active low). */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} i2cmux7_cfg_t;

/**
 * @brief I2C MUX 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    I2CMUX7_OK = 0,
    I2CMUX7_ERROR = -1

} i2cmux7_return_value_t;

/*!
 * @addtogroup i2cmux7 I2C MUX 7 Click Driver
 * @brief API for configuring and manipulating I2C MUX 7 Click driver.
 * @{
 */

/**
 * @brief I2C MUX 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2cmux7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void i2cmux7_cfg_setup ( i2cmux7_cfg_t *cfg );

/**
 * @brief I2C MUX 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #i2cmux7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2cmux7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cmux7_init ( i2cmux7_t *ctx, i2cmux7_cfg_t *cfg );

/**
 * @brief I2C MUX 7 set channel function.
 * @details This function sets the desired channel active and configures its slave address.
 * @param[in] ctx : Click context object.
 * See #i2cmux7_t object definition for detailed explanation.
 * @param[in] ch_sel : Channel selection bit mask.
 * @param[in] ch_slave_addr : 7-bit slave address of the device connected to the channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cmux7_set_channel ( i2cmux7_t *ctx, uint8_t ch_sel, uint8_t ch_slave_addr );

/**
 * @brief I2C MUX 7 read channel function.
 * @details This function reads the currently selected channel value.
 * @param[in] ctx : Click context object.
 * See #i2cmux7_t object definition for detailed explanation.
 * @param[out] ch_sel : Channel selection bit mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cmux7_read_channel ( i2cmux7_t *ctx, uint8_t *ch_sel );

/**
 * @brief I2C MUX 7 reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #i2cmux7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void i2cmux7_reset_device ( i2cmux7_t *ctx );

/**
 * @brief I2C MUX 7 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cmux7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The device channel and slave address must be configured previously using @b i2cmux7_set_channel function.
 */
err_t i2cmux7_generic_write ( i2cmux7_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief I2C MUX 7 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cmux7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The device channel and slave address must be configured previously using @b i2cmux7_set_channel function.
 */
err_t i2cmux7_generic_read ( i2cmux7_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

#ifdef __cplusplus
}
#endif
#endif // I2CMUX7_H

/*! @} */ // i2cmux7

// ------------------------------------------------------------------------ END
