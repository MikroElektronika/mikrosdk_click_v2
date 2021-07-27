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
 * @file ultralowpress.h
 * @brief This file contains API for Ultra-Low Press Click Driver.
 */

#ifndef ULTRALOWPRESS_H
#define ULTRALOWPRESS_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup ultralowpress Ultra-Low Press Click Driver
 * @brief API for configuring and manipulating Ultra-Low Press Click driver.
 * @{
 */

/**
 * @defgroup ultralowpress_reg Ultra-Low Press Registers List
 * @brief List of registers of Ultra-Low Press Click driver.
 */

/**
 * @addtogroup ultralowpress_reg
 * @{
 */

/**
 * @brief Ultra-Low Press description register.
 * @details Specified register for description of Ultra-Low Press Click driver.
 */
#define ULTRALOWPRESS_REG_CMD           0x22
#define ULTRALOWPRESS_REG_TEMP          0x2E
#define ULTRALOWPRESS_REG_PRESS         0x30
#define ULTRALOWPRESS_REG_STATUS_SYNC   0x32
#define ULTRALOWPRESS_REG_STATUS        0x36
#define ULTRALOWPRESS_REG_SERIAL_NUM_L  0x50
#define ULTRALOWPRESS_REG_SERIAL_NUM_H  0x52

/*! @} */ // ultralowpress_reg

/**
 * @defgroup ultralowpress_set Ultra-Low Press Registers Settings
 * @brief Settings for registers of Ultra-Low Press Click driver.
 */

/**
 * @addtogroup ultralowpress_set
 * @{
 */

/**
 * @brief Ultra-Low Press description setting.
 * @details Specified setting for description of Ultra-Low Press Click driver.
 */
#define ULTRALOWPRESS_REG_CMD_SLEEP     0x6C32
#define ULTRALOWPRESS_REG_CMD_RESET     0xB169
#define ULTRALOWPRESS_STATUS_CLEAR      0xFFFF

/**
 * @brief Ultra-Low Press device address setting.
 * @details Specified setting for device slave address selection of
 * Ultra-Low Press Click driver.
 */
#define ULTRALOWPRESS_SET_DEV_ADDR      0x6C

/*! @} */ // ultralowpress_set

/**
 * @defgroup ultralowpress_map Ultra-Low Press MikroBUS Map
 * @brief MikroBUS pin mapping of Ultra-Low Press Click driver.
 */

/**
 * @addtogroup ultralowpress_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ultra-Low Press Click to the selected MikroBUS.
 */
#define ULTRALOWPRESS_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // ultralowpress_map
/*! @} */ // ultralowpress

/**
 * @brief Ultra-Low Press Click context object.
 * @details Context object definition of Ultra-Low Press Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} ultralowpress_t;

/**
 * @brief Ultra-Low Press Click configuration object.
 * @details Configuration object definition of Ultra-Low Press Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} ultralowpress_cfg_t;

/**
 * @brief Ultra-Low Press Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   ULTRALOWPRESS_OK = 0,
   ULTRALOWPRESS_ERROR = -1

} ultralowpress_return_value_t;

/*!
 * @addtogroup ultralowpress Ultra-Low Press Click Driver
 * @brief API for configuring and manipulating Ultra-Low Press Click driver.
 * @{
 */

/**
 * @brief Ultra-Low Press configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ultralowpress_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void ultralowpress_cfg_setup ( ultralowpress_cfg_t *cfg );

/**
 * @brief Ultra-Low Press initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ultralowpress_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ultralowpress_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ultralowpress_init ( ultralowpress_t *ctx, ultralowpress_cfg_t *cfg );

/**
 * @brief Writing function.
 * @details This function writes a data word to register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ultralowpress_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ultralowpress_generic_write ( ultralowpress_t *ctx, uint8_t reg, uint16_t tx_data );

/**
 * @brief Reading function.
 * @details This function reads data word from register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ultralowpress_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ultralowpress_generic_read ( ultralowpress_t *ctx, uint8_t reg, uint16_t *rx_data );

/**
 * @brief Clear status.
 * @details Clears status register by writing 0xFFFF to it.
 * @param[out] cfg : Click configuration structure.
 * See #ultralowpress_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void ultralowpress_clear_status ( ultralowpress_t *ctx );

/**
 * @brief Ready to read.
 * @details Reads status and checks if status bits for temperature and pressure data is ready.
 * @param[out] cfg : Click configuration structure.
 * See #ultralowpress_cfg_t object definition for detailed explanation.
 * @return @li @c 1 - Temperature and pressure data ready to read.
 *         @li @c 0 - Temperature and pressure data not ready to read.
 */
uint8_t ultralowpress_ready_to_read ( ultralowpress_t *ctx );

/**
 * @brief Read pressure.
 * @details Reads pressure from register and calculates and converts data to Pascal data.
 * @param[out] cfg : Click configuration structure.
 * See #ultralowpress_cfg_t object definition for detailed explanation.
 * @return Pressure data in Pascal.
 */
float ultralowpress_get_press ( ultralowpress_t *ctx );

/**
 * @brief Read temperature.
 * @details Reads temperature from register and calculates and converts data to Celzius data.
 * @param[out] cfg : Click configuration structure.
 * See #ultralowpress_cfg_t object definition for detailed explanation.
 * @return Temperature data in Celzius.
 */
float ultralowpress_get_temp ( ultralowpress_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ULTRALOWPRESS_H

/*! @} */ // ultralowpress

// ------------------------------------------------------------------------ END
