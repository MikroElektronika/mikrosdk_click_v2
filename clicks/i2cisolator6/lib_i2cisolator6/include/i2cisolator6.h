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
 * @file i2cisolator6.h
 * @brief This file contains API for I2C Isolator 6 Click Driver.
 */

#ifndef I2CISOLATOR6_H
#define I2CISOLATOR6_H

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
 * @addtogroup i2cisolator6 I2C Isolator 6 Click Driver
 * @brief API for configuring and manipulating I2C Isolator 6 Click driver.
 * @{
 */

/**
 * @defgroup i2cisolator6_reg I2C Isolator 6 Registers List
 * @brief List of registers of I2C Isolator 6 Click driver.
 */

/**
 * @defgroup i2cisolator6_set I2C Isolator 6 Registers Settings
 * @brief Settings for registers of I2C Isolator 6 Click driver.
 */

/**
 * @addtogroup i2cisolator6_set
 * @{
 */

/**
 * @brief I2C Isolator 6 device address setting.
 * @details Specified setting for device slave address selection of
 * I2C Isolator 6 Click driver.
 */
#define I2CISOLATOR6_DEVICE_ADDRESS        0x00

/*! @} */ // i2cisolator6_set

/**
 * @defgroup i2cisolator6_map I2C Isolator 6 MikroBUS Map
 * @brief MikroBUS pin mapping of I2C Isolator 6 Click driver.
 */

/**
 * @addtogroup i2cisolator6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C Isolator 6 Click to the selected MikroBUS.
 */
#define I2CISOLATOR6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // i2cisolator6_map
/*! @} */ // i2cisolator6

/**
 * @brief I2C Isolator 6 Click context object.
 * @details Context object definition of I2C Isolator 6 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} i2cisolator6_t;

/**
 * @brief I2C Isolator 6 Click configuration object.
 * @details Configuration object definition of I2C Isolator 6 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} i2cisolator6_cfg_t;

/**
 * @brief I2C Isolator 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    I2CISOLATOR6_OK = 0,
    I2CISOLATOR6_ERROR = -1

} i2cisolator6_return_value_t;

/*!
 * @addtogroup i2cisolator6 I2C Isolator 6 Click Driver
 * @brief API for configuring and manipulating I2C Isolator 6 Click driver.
 * @{
 */

/**
 * @brief I2C Isolator 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2cisolator6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void i2cisolator6_cfg_setup ( i2cisolator6_cfg_t *cfg );

/**
 * @brief I2C Isolator 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #i2cisolator6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2cisolator6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cisolator6_init ( i2cisolator6_t *ctx, i2cisolator6_cfg_t *cfg );

/**
 * @brief I2C Isolator 6 I2C writing function.
 * @details Function shall generate a START signal,
 * followed by \p len number of writes
 * from \p data_in on the bus.
 * @param[in] ctx : Click context object.
 * See #i2cisolator6_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cisolator6_write ( i2cisolator6_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief I2C Isolator 6 I2C reading function.
 * @details Function shall generate a START signal,
 * followed by \p len number of reads
 * from the bus placing the data in \p data_out .
 * Ends with a STOP signal.
 * @param[in] ctx : Click context object.
 * See #i2cisolator6_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cisolator6_read ( i2cisolator6_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief I2C Isolator 6 I2C write then read function.
 * @details Function performs a write operation followed by a
 * read operation on the bus. The operation consists of a
 * start signal followed by \p len_write_data number of write operations
 * ( data from \p data_in ), a restart signal followed by
 * \p len_read_data number of read operations ( placed in \p data_out ),
 * finishing the operation with a stop signal.
 * @param[in] ctx : Click context object.
 * See #i2cisolator6_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len_write_data : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[in] len_read_data Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cisolator6_write_then_read ( i2cisolator6_t *ctx, uint8_t *data_in, uint8_t len_write_data, uint8_t *data_out, uint8_t len_read_data );

/**
 * @brief I2C Isolator 6 set I2C Slave address function.
 * @details This function sets I2C address of the subordinate I2C device
 * to address which is targeted by read and write operations.
 * @param[in] ctx : Click context object.
 * See #i2cisolator6_t object definition for detailed explanation.
 * @param[in] slave_address Specified I2C slave address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note It is recommended to check return value for error.
 */
err_t i2cisolator6_set_slave_address ( i2cisolator6_t *ctx, uint8_t slave_address );

#ifdef __cplusplus
}
#endif
#endif // I2CISOLATOR6_H

/*! @} */ // i2cisolator6

// ------------------------------------------------------------------------ END
