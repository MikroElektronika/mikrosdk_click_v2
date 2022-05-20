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
 * @file usbtoi2c2.h
 * @brief This file contains API for USB to I2C 2 Click Driver.
 */

#ifndef USBTOI2C2_H
#define USBTOI2C2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup usbtoi2c2 USB to I2C 2 Click Driver
 * @brief API for configuring and manipulating USB to I2C 2 Click driver.
 * @{
 */

/**
 * @defgroup usbtoi2c2_set USB to I2C 2 Registers Settings
 * @brief Settings for registers of USB to I2C 2 Click driver.
 */

/**
 * @addtogroup usbtoi2c2_set
 * @{
 */

/**
 * @brief USB to I2C 2 commands list.
 * @details Specified commands list of USB to I2C 2 Click driver.
 */
#define USBTOI2C2_CMD_SOFT_RESET                    0x06
#define USBTOI2C2_CMD_FLUSH_DATA                    0x0E

/**
 * @brief USB to I2C 2 device address setting.
 * @details Specified setting for device slave address selection of
 * USB to I2C 2 Click driver.
 */
#define USBTOI2C2_GENERAL_CALL_ADDRESS              0x00
#define USBTOI2C2_DEVICE_SLAVE_ADDRESS              0x22

/*! @} */ // usbtoi2c2_set

/**
 * @defgroup usbtoi2c2_map USB to I2C 2 MikroBUS Map
 * @brief MikroBUS pin mapping of USB to I2C 2 Click driver.
 */

/**
 * @addtogroup usbtoi2c2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB to I2C 2 Click to the selected MikroBUS.
 */
#define USBTOI2C2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.tx_ind = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rx_ind = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // usbtoi2c2_map
/*! @} */ // usbtoi2c2

/**
 * @brief USB to I2C 2 Click context object.
 * @details Context object definition of USB to I2C 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;             /**< Reset pin (active low). */
    
    // Input pins
    digital_in_t   tx_ind;          /**< TX indicator. */
    digital_in_t   rx_ind;          /**< RX indicator. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} usbtoi2c2_t;

/**
 * @brief USB to I2C 2 Click configuration object.
 * @details Configuration object definition of USB to I2C 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;                /**< Reset pin (active low). */
    
    pin_name_t  tx_ind;             /**< Tx indicator. */
    pin_name_t  rx_ind;             /**< Rx indicator. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} usbtoi2c2_cfg_t;

/**
 * @brief USB to I2C 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBTOI2C2_OK = 0,
    USBTOI2C2_ERROR = -1

} usbtoi2c2_return_value_t;

/*!
 * @addtogroup usbtoi2c2 USB to I2C 2 Click Driver
 * @brief API for configuring and manipulating USB to I2C 2 Click driver.
 * @{
 */

/**
 * @brief USB to I2C 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbtoi2c2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbtoi2c2_cfg_setup ( usbtoi2c2_cfg_t *cfg );

/**
 * @brief USB to I2C 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #usbtoi2c2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbtoi2c2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbtoi2c2_init ( usbtoi2c2_t *ctx, usbtoi2c2_cfg_t *cfg );

/**
 * @brief USB to I2C 2 default configuration function.
 * @details This function executes a default configuration of USB to I2C 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #usbtoi2c2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t usbtoi2c2_default_cfg ( usbtoi2c2_t *ctx );

/**
 * @brief USB to I2C 2 write data function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbtoi2c2_t object definition for detailed explanation.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note CBUS0 signal must be configured as I2C_RXF# via USB using FT PROG application.
 */
err_t usbtoi2c2_write_data ( usbtoi2c2_t *ctx, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief USB to I2C 2 read data function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #usbtoi2c2_t object definition for detailed explanation.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note CBUS1 signal must be configured as I2C_TXE# via USB using FT PROG application.
 */
err_t usbtoi2c2_read_data ( usbtoi2c2_t *ctx, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief USB to I2C 2 reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #usbtoi2c2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void usbtoi2c2_reset_device ( usbtoi2c2_t *ctx );

/**
 * @brief USB to I2C 2 soft reset function.
 * @details This function issues the soft reset command.
 * @param[in] ctx : Click context object.
 * See #usbtoi2c2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbtoi2c2_soft_reset ( usbtoi2c2_t *ctx );

/**
 * @brief USB to I2C 2 flush data function.
 * @details This function issues the flush data command.
 * @param[in] ctx : Click context object.
 * See #usbtoi2c2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbtoi2c2_flush_data ( usbtoi2c2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // USBTOI2C2_H

/*! @} */ // usbtoi2c2

// ------------------------------------------------------------------------ END
