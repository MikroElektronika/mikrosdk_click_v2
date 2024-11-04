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
 * @file i2ctocan.h
 * @brief This file contains API for I2C to CAN Click Driver.
 */

#ifndef I2CTOCAN_H
#define I2CTOCAN_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup i2ctocan I2C to CAN Click Driver
 * @brief API for configuring and manipulating I2C to CAN Click driver.
 * @{
 */

/**
 * @defgroup i2ctocan_set I2C to CAN Registers Settings
 * @brief Settings for registers of I2C to CAN Click driver.
 */

/**
 * @addtogroup i2ctocan_set
 * @{
 */

/**
 * @brief I2C to CAN device address setting.
 * @details Specified setting for device slave address selection of
 * I2C to CAN Click driver.
 */
#define I2CTOCAN_SET_DEV_ADDR         0x00

/*! @} */ // i2ctocan_set

/**
 * @defgroup i2ctocan_map I2C to CAN MikroBUS Map
 * @brief MikroBUS pin mapping of I2C to CAN Click driver.
 */

/**
 * @addtogroup i2ctocan_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C to CAN Click to the selected MikroBUS.
 */
#define I2CTOCAN_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.shd = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // i2ctocan_map
/*! @} */ // i2ctocan

/**
 * @brief I2C to CAN Click context object.
 * @details Context object definition of I2C to CAN Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  shd;       /**< Shutdown pin. */

    // Modules

    i2c_master_t i2c;         /**< I2C driver object. */
                              
    // I2C slave address      
                              
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} i2ctocan_t;

/**
 * @brief I2C to CAN Click configuration object.
 * @details Configuration object definition of I2C to CAN Click driver.
 */
typedef struct
{
    pin_name_t  scl;          /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;          /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  shd;          /**< Shutdown pin. */

    uint32_t  i2c_speed;      /**< I2C serial speed. */
    uint8_t   i2c_address;    /**< I2C slave address. */

} i2ctocan_cfg_t;

/**
 * @brief I2C to CAN Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   I2CTOCAN_OK = 0,
   I2CTOCAN_ERROR = -1

} i2ctocan_return_value_t;

/*!
 * @addtogroup i2ctocan I2C to CAN Click Driver
 * @brief API for configuring and manipulating I2C to CAN Click driver.
 * @{
 */

/**
 * @brief I2C to CAN configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2ctocan_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void i2ctocan_cfg_setup ( i2ctocan_cfg_t *cfg );

/**
 * @brief I2C to CAN initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #i2ctocan_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2ctocan_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t i2ctocan_init ( i2ctocan_t *ctx, i2ctocan_cfg_t *cfg );

/**
 * @brief I2C to CAN default configuration function.
 * @details This function executes a default configuration of I2C to CAN
 * Click board.
 * @param[in] ctx : Click context object.
 * See #i2ctocan_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t i2ctocan_default_cfg ( i2ctocan_t *ctx );

/**
 * @brief I2C to CAN enable the device function.
 * @details This function enable the LT3960, I2C to CAN-Physical Transceiver
 * on the I2C to CAN Click board™.
 * @param[in] ctx : Click context object.
 * See #i2ctocan_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t i2ctocan_enable_device ( i2ctocan_t *ctx );

/**
 * @brief I2C to CAN shutdown the device function.
 * @details This function turn off the LT3960, I2C to CAN-Physical Transceiver
 * on the I2C to CAN Click board™.
 * @param[in] ctx : Click context object.
 * See #i2ctocan_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t i2ctocan_shutdown ( i2ctocan_t *ctx );

/**
 * @brief Set I2C Slave address function.
 * @details Sets I2C address of the subordinate I2C device
 * to \p address which is targeted by read and write operations.
 * @param[in] ctx : Click context object.
 * See #i2ctocan_t object definition for detailed explanation.
 * @param[in] address Specified I2C slave address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note It is recommended to check return value for error.
 *
 * @endcode
 */
err_t i2ctocan_set_slave_address ( i2ctocan_t *ctx, uint8_t slave_addr );

/**
 * @brief I2C to CAN I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2ctocan_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t i2ctocan_generic_write ( i2ctocan_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief I2C to CAN I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2ctocan_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t i2ctocan_generic_read ( i2ctocan_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

#ifdef __cplusplus
}
#endif
#endif // I2CTOCAN_H

/*! @} */ // i2ctocan

// ------------------------------------------------------------------------ END
