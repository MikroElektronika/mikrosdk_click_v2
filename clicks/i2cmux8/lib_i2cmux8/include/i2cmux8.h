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
 * @file i2cmux8.h
 * @brief This file contains API for I2C MUX 8 Click Driver.
 */

#ifndef I2CMUX8_H
#define I2CMUX8_H

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
 * @addtogroup i2cmux8 I2C MUX 8 Click Driver
 * @brief API for configuring and manipulating I2C MUX 8 Click driver.
 * @{
 */

/**
 * @defgroup i2cmux8_set I2C MUX 8 Settings
 * @brief Settings of I2C MUX 8 Click driver.
 */

/**
 * @addtogroup i2cmux8_set
 * @{
 */

/**
 * @brief I2C MUX 8 channel selection values.
 * @details Specified channel selection values of I2C MUX 8 Click driver.
 */
#define I2CMUX8_CHANNEL_DISABLE                 0x00
#define I2CMUX8_CHANNEL_1                       0x01
#define I2CMUX8_CHANNEL_2                       0x02
#define I2CMUX8_CHANNEL_3                       0x04
#define I2CMUX8_CHANNEL_4                       0x08
#define I2CMUX8_CHANNEL_MASK                    0x0F

/**
 * @brief I2C MUX 8 device address setting.
 * @details Specified setting for device slave address selection of
 * I2C MUX 8 Click driver.
 */
#define I2CMUX8_DEVICE_ADDRESS_A2A1A0_000       0x70
#define I2CMUX8_DEVICE_ADDRESS_A2A1A0_001       0x71
#define I2CMUX8_DEVICE_ADDRESS_A2A1A0_010       0x72
#define I2CMUX8_DEVICE_ADDRESS_A2A1A0_011       0x73
#define I2CMUX8_DEVICE_ADDRESS_A2A1A0_100       0x74
#define I2CMUX8_DEVICE_ADDRESS_A2A1A0_101       0x75
#define I2CMUX8_DEVICE_ADDRESS_A2A1A0_110       0x76
#define I2CMUX8_DEVICE_ADDRESS_A2A1A0_111       0x77

/*! @} */ // i2cmux8_set

/**
 * @defgroup i2cmux8_map I2C MUX 8 MikroBUS Map
 * @brief MikroBUS pin mapping of I2C MUX 8 Click driver.
 */

/**
 * @addtogroup i2cmux8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C MUX 8 Click to the selected MikroBUS.
 */
#define I2CMUX8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // i2cmux8_map
/*! @} */ // i2cmux8

/**
 * @brief I2C MUX 8 Click context object.
 * @details Context object definition of I2C MUX 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    uint8_t ch_slave_address;       /**< Channel device slave address (used for I2C driver). */

} i2cmux8_t;

/**
 * @brief I2C MUX 8 Click configuration object.
 * @details Configuration object definition of I2C MUX 8 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;                 /**< Reset pin (active low). */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} i2cmux8_cfg_t;

/**
 * @brief I2C MUX 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    I2CMUX8_OK = 0,
    I2CMUX8_ERROR = -1

} i2cmux8_return_value_t;

/*!
 * @addtogroup i2cmux8 I2C MUX 8 Click Driver
 * @brief API for configuring and manipulating I2C MUX 8 Click driver.
 * @{
 */

/**
 * @brief I2C MUX 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2cmux8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void i2cmux8_cfg_setup ( i2cmux8_cfg_t *cfg );

/**
 * @brief I2C MUX 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #i2cmux8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2cmux8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cmux8_init ( i2cmux8_t *ctx, i2cmux8_cfg_t *cfg );

/**
 * @brief I2C MUX 8 set channel function.
 * @details This function sets the active channel and updates the slave address for communication.
 * @param[in] ctx : Click context object.
 * See #i2cmux8_t object definition for detailed explanation.
 * @param[in] ch_sel : Channel selection.
 * @param[in] ch_slave_addr : Slave address of the selected channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2cmux8_set_channel ( i2cmux8_t *ctx, uint8_t ch_sel, uint8_t ch_slave_addr );

/**
 * @brief I2C MUX 8 read channel function.
 * @details This function reads the currently selected channel.
 * @param[in] ctx : Click context object.
 * See #i2cmux8_t object definition for detailed explanation.
 * @param[out] ch_sel : Pointer to store the selected channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2cmux8_read_channel ( i2cmux8_t *ctx, uint8_t *ch_sel );

/**
 * @brief I2C MUX 8 set reset pin function.
 * @details This function sets the logic state of the reset (RST) pin.
 * @param[in] ctx : Click context object.
 * See #i2cmux8_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void i2cmux8_set_rst_pin ( i2cmux8_t *ctx, uint8_t state );

/**
 * @brief I2C MUX 8 reset device function.
 * @details This function resets the device by toggling the reset pin.
 * @param[in] ctx : Click context object.
 * See #i2cmux8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void i2cmux8_reset_device ( i2cmux8_t *ctx );

/**
 * @brief I2C MUX 8 write function.
 * @details This function writes data to the currently active I2C slave.
 * @param[in] ctx : Click context object.
 * See #i2cmux8_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2cmux8_i2c_write ( i2cmux8_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief I2C MUX 8 read function.
 * @details This function reads data from the currently active I2C slave.
 * @param[in] ctx : Click context object.
 * See #i2cmux8_t object definition for detailed explanation.
 * @param[out] data_out : Data buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2cmux8_i2c_read ( i2cmux8_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief I2C MUX 8 write then read function.
 * @details This function writes data to the currently active I2C slave, then reads the response.
 * @param[in] ctx : Click context object.
 * See #i2cmux8_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] in_len : Number of bytes to write.
 * @param[out] data_out : Data buffer to store read data.
 * @param[in] out_len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2cmux8_i2c_write_then_read ( i2cmux8_t *ctx, uint8_t *data_in, uint16_t in_len, 
                                                    uint8_t *data_out, uint8_t out_len );

/**
 * @brief I2C MUX 8 write register function.
 * @details This function writes data to a specific register of the currently active I2C slave.
 * @param[in] ctx : Click context object.
 * See #i2cmux8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2cmux8_i2c_write_reg ( i2cmux8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief I2C MUX 8 read register function.
 * @details This function reads data from a specific register of the currently active I2C slave.
 * @param[in] ctx : Click context object.
 * See #i2cmux8_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Data buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2cmux8_i2c_read_reg ( i2cmux8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif // I2CMUX8_H

/*! @} */ // i2cmux8

// ------------------------------------------------------------------------ END
