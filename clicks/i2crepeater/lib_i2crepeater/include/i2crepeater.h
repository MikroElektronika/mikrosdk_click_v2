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
 * @file i2crepeater.h
 * @brief This file contains API for I2C Repeater Click Driver.
 */

#ifndef I2CREPEATER_H
#define I2CREPEATER_H

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
 * @addtogroup i2crepeater I2C Repeater Click Driver
 * @brief API for configuring and manipulating I2C Repeater Click driver.
 * @{
 */

/**
 * @defgroup i2crepeater_set I2C Repeater Registers Settings
 * @brief Settings for registers of I2C Repeater Click driver.
 */

/**
 * @addtogroup i2crepeater_set
 * @{
 */

/**
 * @brief I2C Repeater device address setting.
 * @details Specified setting for device slave address selection of
 * I2C Repeater Click driver.
 */
#define I2CREPEATER_DEVICE_ADDRESS          0x00

/*! @} */ // i2crepeater_set

/**
 * @defgroup i2crepeater_map I2C Repeater MikroBUS Map
 * @brief MikroBUS pin mapping of I2C Repeater Click driver.
 */

/**
 * @addtogroup i2crepeater_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C Repeater Click to the selected MikroBUS.
 */
#define I2CREPEATER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // i2crepeater_map
/*! @} */ // i2crepeater

/**
 * @brief I2C Repeater Click context object.
 * @details Context object definition of I2C Repeater Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable repeater pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} i2crepeater_t;

/**
 * @brief I2C Repeater Click configuration object.
 * @details Configuration object definition of I2C Repeater Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable repeater pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} i2crepeater_cfg_t;

/**
 * @brief I2C Repeater Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    I2CREPEATER_OK = 0,
    I2CREPEATER_ERROR = -1

} i2crepeater_return_value_t;

/*!
 * @addtogroup i2crepeater I2C Repeater Click Driver
 * @brief API for configuring and manipulating I2C Repeater Click driver.
 * @{
 */

/**
 * @brief I2C Repeater configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2crepeater_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void i2crepeater_cfg_setup ( i2crepeater_cfg_t *cfg );

/**
 * @brief I2C Repeater initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #i2crepeater_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2crepeater_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2crepeater_init ( i2crepeater_t *ctx, i2crepeater_cfg_t *cfg );

/**
 * @brief I2C Repeater enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #i2crepeater_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void i2crepeater_enable_device ( i2crepeater_t *ctx );

/**
 * @brief I2C Repeater disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #i2crepeater_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void i2crepeater_disable_device ( i2crepeater_t *ctx );

/**
 * @brief I2C Repeater set I2C address function.
 * @details This function sets the slave address for I2C communication.
 * @param[in] ctx : Click context object.
 * See #i2crepeater_t object definition for detailed explanation.
 * @param[in] slave_addr : I2C slave address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2crepeater_set_i2c_address ( i2crepeater_t *ctx, uint8_t slave_addr );

/**
 * @brief I2C Repeater write function.
 * @details This function writes data to the I2C slave.
 * @param[in] ctx : Click context object.
 * See #i2crepeater_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2crepeater_i2c_write ( i2crepeater_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief I2C Repeater read function.
 * @details This function reads data from the I2C slave.
 * @param[in] ctx : Click context object.
 * See #i2crepeater_t object definition for detailed explanation.
 * @param[out] data_out : Data buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2crepeater_i2c_read ( i2crepeater_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief I2C Repeater write then read function.
 * @details This function writes data to the I2C slave, then reads the response.
 * @param[in] ctx : Click context object.
 * See #i2crepeater_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] in_len : Number of bytes to write.
 * @param[out] data_out : Data buffer to store read data.
 * @param[in] out_len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2crepeater_i2c_write_then_read ( i2crepeater_t *ctx, uint8_t *data_in, uint16_t in_len, 
                                                            uint8_t *data_out, uint8_t out_len );

/**
 * @brief I2C Repeater write register function.
 * @details This function writes data to a specific register of the I2C slave.
 * @param[in] ctx : Click context object.
 * See #i2crepeater_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2crepeater_i2c_write_reg ( i2crepeater_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief I2C Repeater read register function.
 * @details This function reads data from a specific register of the I2C slave.
 * @param[in] ctx : Click context object.
 * See #i2crepeater_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Data buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t i2crepeater_i2c_read_reg ( i2crepeater_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif // I2CREPEATER_H

/*! @} */ // i2crepeater

// ------------------------------------------------------------------------ END
