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
 * @file i2cisolator4.h
 * @brief This file contains API for I2C Isolator 4 Click Driver.
 */

#ifndef I2CISOLATOR4_H
#define I2CISOLATOR4_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup i2cisolator4 I2C Isolator 4 Click Driver
 * @brief API for configuring and manipulating I2C Isolator 4 Click driver.
 * @{
 */

/**
 * @defgroup i2cisolator4_reg I2C Isolator 4 Registers List
 * @brief List of registers of I2C Isolator 4 Click driver.
 */


/**
 * @defgroup i2cisolator4_set I2C Isolator 4 Registers Settings
 * @brief Settings for registers of I2C Isolator 4 Click driver.
 */

/**
 * @addtogroup i2cisolator4_set
 * @{
 */


/**
 * @brief I2C Isolator 4 device address setting.
 * @details Specified setting for device slave address selection of
 * I2C Isolator 4 Click driver.
 */
#define I2CISOLATOR4_SET_DEV_ADDR  0x00

/*! @} */ // i2cisolator4_set

/**
 * @defgroup i2cisolator4_map I2C Isolator 4 MikroBUS Map
 * @brief MikroBUS pin mapping of I2C Isolator 4 Click driver.
 */

/**
 * @addtogroup i2cisolator4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C Isolator 4 Click to the selected MikroBUS.
 */
#define I2CISOLATOR4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // i2cisolator4_map
/*! @} */ // i2cisolator4

/**
 * @brief I2C Isolator 4 Click context object.
 * @details Context object definition of I2C Isolator 4 Click driver.
 */
typedef struct
{
    // Modules

    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} i2cisolator4_t;

/**
 * @brief I2C Isolator 4 Click configuration object.
 * @details Configuration object definition of I2C Isolator 4 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */


    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} i2cisolator4_cfg_t;

/**
 * @brief I2C Isolator 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   I2CISOLATOR4_OK = 0,
   I2CISOLATOR4_ERROR = -1

} i2cisolator4_return_value_t;

/*!
 * @addtogroup i2cisolator4 I2C Isolator 4 Click Driver
 * @brief API for configuring and manipulating I2C Isolator 4 Click driver.
 * @{
 */

/**
 * @brief I2C Isolator 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2cisolator4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void i2cisolator4_cfg_setup ( i2cisolator4_cfg_t *cfg );

/**
 * @brief I2C Isolator 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #i2cisolator4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2cisolator4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t i2cisolator4_init ( i2cisolator4_t *ctx, i2cisolator4_cfg_t *cfg );

/**
 * @brief I2C Isolator 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cisolator4_t object definition for detailed explanation.
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
err_t i2cisolator4_generic_write ( i2cisolator4_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief I2C Isolator 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cisolator4_t object definition for detailed explanation.
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
err_t i2cisolator4_generic_read ( i2cisolator4_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief I2C Isolator 4 set I2C Slave address function.
 * @details This function sets I2C address of the subordinate I2C device
 * to \p address which is targeted by read and write operations.
 * @param[in] ctx : Click context object.
 * See #i2cisolator4_t object definition for detailed explanation.
 * @param[in] address : Specified I2C slave address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t i2cisolator4_set_slave_address ( i2cisolator4_t *ctx, uint8_t address );

#ifdef __cplusplus
}
#endif
#endif // I2CISOLATOR4_H

/*! @} */ // i2cisolator4

// ------------------------------------------------------------------------ END
