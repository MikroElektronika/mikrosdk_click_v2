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
 * @file i2cmux6.h
 * @brief This file contains API for I2C MUX 6 Click Driver.
 */

#ifndef I2CMUX6_H
#define I2CMUX6_H

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
 * @addtogroup i2cmux6 I2C MUX 6 Click Driver
 * @brief API for configuring and manipulating I2C MUX 6 Click driver.
 * @{
 */

/**
 * @defgroup i2cmux6_set I2C MUX 6 Registers Settings
 * @brief Settings for registers of I2C MUX 6 Click driver.
 */

/**
 * @addtogroup i2cmux6_set
 * @{
 */

/**
 * @brief I2C MUX 6 channel selection values.
 * @details Specified channel selection values of I2C MUX 6 Click driver.
 */
#define I2CMUX6_CHANNEL_DISABLE             0x00
#define I2CMUX6_CHANNEL_1                   0x01
#define I2CMUX6_CHANNEL_2                   0x02
#define I2CMUX6_CHANNEL_3                   0x04
#define I2CMUX6_CHANNEL_4                   0x08
#define I2CMUX6_CHANNEL_ALL                 0x0F

/**
 * @brief I2C MUX 6 device address setting.
 * @details Specified setting for device slave address selection of
 * I2C MUX 6 Click driver.
 */
#define I2CMUX6_DEVICE_ADDRESS              0x00

/*! @} */ // i2cmux6_set

/**
 * @defgroup i2cmux6_map I2C MUX 6 MikroBUS Map
 * @brief MikroBUS pin mapping of I2C MUX 6 Click driver.
 */

/**
 * @addtogroup i2cmux6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C MUX 6 Click to the selected MikroBUS.
 */
#define I2CMUX6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en3 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en4 = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // i2cmux6_map
/*! @} */ // i2cmux6

/**
 * @brief I2C MUX 6 Click context object.
 * @details Context object definition of I2C MUX 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en1;      /**< Enable channel 1 pin. */
    digital_out_t en2;      /**< Enable channel 2 pin. */
    digital_out_t en3;      /**< Enable channel 3 pin. */
    digital_out_t en4;      /**< Enable channel 4 pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} i2cmux6_t;

/**
 * @brief I2C MUX 6 Click configuration object.
 * @details Configuration object definition of I2C MUX 6 Click driver.
 */
typedef struct
{
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en1;         /**< Enable channel 1 pin. */
    pin_name_t en2;         /**< Enable channel 2 pin. */
    pin_name_t en3;         /**< Enable channel 3 pin. */
    pin_name_t en4;         /**< Enable channel 4 pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} i2cmux6_cfg_t;

/**
 * @brief I2C MUX 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    I2CMUX6_OK = 0,
    I2CMUX6_ERROR = -1

} i2cmux6_return_value_t;

/*!
 * @addtogroup i2cmux6 I2C MUX 6 Click Driver
 * @brief API for configuring and manipulating I2C MUX 6 Click driver.
 * @{
 */

/**
 * @brief I2C MUX 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2cmux6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void i2cmux6_cfg_setup ( i2cmux6_cfg_t *cfg );

/**
 * @brief I2C MUX 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #i2cmux6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2cmux6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cmux6_init ( i2cmux6_t *ctx, i2cmux6_cfg_t *cfg );

/**
 * @brief I2C MUX 6 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cmux6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cmux6_generic_write ( i2cmux6_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief I2C MUX 6 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cmux6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cmux6_generic_read ( i2cmux6_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief I2C MUX 6 set channel function.
 * @details This function sets the desired channel active and configures its slave address.
 * @param[in] ctx : Click context object.
 * See #i2cmux6_t object definition for detailed explanation.
 * @param[in] ch_sel : Channel selection bit mask.
 * @param[in] ch_slave_addr : 7-bit slave address of the device connected to the channel.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cmux6_set_channel ( i2cmux6_t *ctx, uint8_t ch_sel, uint8_t ch_slave_addr );

#ifdef __cplusplus
}
#endif
#endif // I2CMUX6_H

/*! @} */ // i2cmux6

// ------------------------------------------------------------------------ END
