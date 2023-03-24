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
 * @file uva.h
 * @brief This file contains API for UVA Click Driver.
 */

#ifndef UVA_H
#define UVA_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup uva UVA Click Driver
 * @brief API for configuring and manipulating UVA Click driver.
 * @{
 */

/**
 * @defgroup uva_reg UVA Registers List
 * @brief List of registers of UVA Click driver.
 */

/**
 * @addtogroup uva_reg
 * @{
 */

/**
 * @brief UVA Register Map.
 * @details Specified Register Map of UVA Click driver.
 */
#define UVA_REG_CHIP_ID                     0x00
#define UVA_REG_MODE                        0x01
#define UVA_REG_RES_UV                      0x04
#define UVA_REG_RANGE_UVA                   0x05
#define UVA_REG_MODE_CTRL                   0x0A
#define UVA_REG_SOFT_RESET                  0x0B
#define UVA_REG_UVA_LSB                     0x15
#define UVA_REG_UVA_MSB                     0x16
#define UVA_REG_NVM_READ_CTRL               0x30
#define UVA_REG_NVM_MSB                     0x31
#define UVA_REG_NVM_LSB                     0x32

/*! @} */ // uva_reg

/**
 * @defgroup uva_set UVA Registers Settings
 * @brief Settings for registers of UVA Click driver.
 */

/**
 * @addtogroup uva_set
 * @{
 */

/**
 * @brief UVA chip ID value.
 * @details Specified chip ID value of UVA Click driver.
 */
#define UVA_CHIP_ID                         0x62

/**
 * @brief UVA mode register setting.
 * @details Specified mode register setting of UVA Click driver.
 */
#define UVA_MODE_NO_OPERATION               0x00
#define UVA_MODE_UVA_OPERATION              0x10
#define UVA_MODE_NORMAL                     0x00
#define UVA_MODE_LOW_POWER                  0x01
#define UVA_MODE_AUTO_SHUTDOWN              0x02
#define UVA_MODE_SHUTDOWN                   0x03

/**
 * @brief UVA resolution register setting.
 * @details Specified resolution register setting of UVA Click driver.
 */
#define UVA_RESOLUTION_800MS                0x00
#define UVA_RESOLUTION_400MS                0x01
#define UVA_RESOLUTION_200MS                0x02
#define UVA_RESOLUTION_100MS                0x03

/**
 * @brief UVA range register setting.
 * @details Specified range register setting of UVA Click driver.
 */
#define UVA_RANGE_X1                        0x00
#define UVA_RANGE_X2                        0x01
#define UVA_RANGE_X4                        0x02
#define UVA_RANGE_X8                        0x03
#define UVA_RANGE_X16                       0x04
#define UVA_RANGE_X32                       0x05
#define UVA_RANGE_X64                       0x06
#define UVA_RANGE_X128                      0x07

/**
 * @brief UVA mode control register setting.
 * @details Specified mode control register setting of UVA Click driver.
 */
#define UVA_MODE_CTRL_SLEEP_2_TIMES         0x00
#define UVA_MODE_CTRL_SLEEP_4_TIMES         0x01
#define UVA_MODE_CTRL_SLEEP_8_TIMES         0x02
#define UVA_MODE_CTRL_SLEEP_16_TIMES        0x03
#define UVA_MODE_CTRL_SLEEP_32_TIMES        0x04
#define UVA_MODE_CTRL_SLEEP_64_TIMES        0x05
#define UVA_MODE_CTRL_SLEEP_128_TIMES       0x06
#define UVA_MODE_CTRL_SLEEP_256_TIMES       0x07

/**
 * @brief UVA Soft Reset value.
 * @details Specified Soft Reset value of UVA Click driver.
 */
#define UVA_SOFT_RESET                      0xA5

/**
 * @brief UVA NVM read address values.
 * @details Specified NVM read address values of UVA Click driver.
 */
#define UVA_NVM_READ_ADDRESS_OFFSET         0x0A
#define UVA_NVM_READ_ADDRESS_A_SCALE        0x0B

/**
 * @brief UVA device address setting.
 * @details Specified setting for device slave address selection of
 * UVA Click driver.
 */
#define UVA_SET_DEV_ADDR                    0x39

/*! @} */ // uva_set

/**
 * @defgroup uva_map UVA MikroBUS Map
 * @brief MikroBUS pin mapping of UVA Click driver.
 */

/**
 * @addtogroup uva_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UVA Click to the selected MikroBUS.
 */
#define UVA_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // uva_map
/*! @} */ // uva

/**
 * @brief UVA Click context object.
 * @details Context object definition of UVA Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} uva_t;

/**
 * @brief UVA Click configuration object.
 * @details Configuration object definition of UVA Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} uva_cfg_t;

/**
 * @brief UVA Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    UVA_OK = 0,
    UVA_ERROR = -1

} uva_return_value_t;

/*!
 * @addtogroup uva UVA Click Driver
 * @brief API for configuring and manipulating UVA Click driver.
 * @{
 */

/**
 * @brief UVA configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #uva_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void uva_cfg_setup ( uva_cfg_t *cfg );

/**
 * @brief UVA initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #uva_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #uva_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uva_init ( uva_t *ctx, uva_cfg_t *cfg );

/**
 * @brief UVA default configuration function.
 * @details This function executes a default configuration of UVA
 * click board.
 * @param[in] ctx : Click context object.
 * See #uva_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t uva_default_cfg ( uva_t *ctx );

/**
 * @brief UVA I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #uva_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uva_generic_write ( uva_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief UVA I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #uva_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uva_generic_read ( uva_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief UVA write register function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #uva_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uva_write_register ( uva_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief UVA read register function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #uva_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uva_read_register ( uva_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief UVA check communication function.
 * @details This function checks the communication by reading and verifying the chip ID.
 * @param[in] ctx : Click context object.
 * See #uva_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uva_check_communication ( uva_t *ctx );

/**
 * @brief UVA read data function.
 * @details This function reads the raw UVA data from registers.
 * @param[in] ctx : Click context object.
 * See #uva_t object definition for detailed explanation.
 * @param[out] uva_data : UVA data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uva_read_data ( uva_t *ctx, uint16_t *uva_data );

/**
 * @brief UVA soft reset function.
 * @details This function executes the soft reset command.
 * @param[in] ctx : Click context object.
 * See #uva_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uva_soft_reset ( uva_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // UVA_H

/*! @} */ // uva

// ------------------------------------------------------------------------ END
