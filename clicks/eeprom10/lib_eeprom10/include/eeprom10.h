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
 * @file eeprom10.h
 * @brief This file contains API for EEPROM 10 Click Driver.
 */

#ifndef EEPROM10_H
#define EEPROM10_H

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
 * @addtogroup eeprom10 EEPROM 10 Click Driver
 * @brief API for configuring and manipulating EEPROM 10 Click driver.
 * @{
 */

/**
 * @defgroup eeprom10_set EEPROM 10 Registers Settings
 * @brief Settings for registers of EEPROM 10 Click driver.
 */

/**
 * @addtogroup eeprom10_set
 * @{
 */

/**
 * @brief EEPROM 10 description setting.
 * @details Specified setting for description of EEPROM 10 Click driver.
 */
#define EEPROM10_NBYTES_PAGE                    32

/**
 * @brief EEPROM 10 memory address range.
 * @details Specified memory address range of EEPROM 10 Click driver.
 */
#define EEPROM10_BLOCK_ADDR_START               0x0000
#define EEPROM10_BLOCK_ADDR_END                 0x0FFFu

/**
 * @brief EEPROM 10 device address setting.
 * @details Specified setting for device slave address selection of
 * EEPROM 10 Click driver.
 */
#define EEPROM10_DEVICE_ADDRESS_0               0x50
#define EEPROM10_DEVICE_ADDRESS_1               0x51
#define EEPROM10_DEVICE_ADDRESS_2               0x52
#define EEPROM10_DEVICE_ADDRESS_3               0x53
#define EEPROM10_DEVICE_ADDRESS_4               0x54
#define EEPROM10_DEVICE_ADDRESS_5               0x55
#define EEPROM10_DEVICE_ADDRESS_6               0x56
#define EEPROM10_DEVICE_ADDRESS_7               0x57

/*! @} */ // eeprom10_set

/**
 * @defgroup eeprom10_map EEPROM 10 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 10 Click driver.
 */

/**
 * @addtogroup eeprom10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 10 Click to the selected MikroBUS.
 */
#define EEPROM10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // eeprom10_map
/*! @} */ // eeprom10

/**
 * @brief EEPROM 10 Click context object.
 * @details Context object definition of EEPROM 10 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wp;               /**< Write protection pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} eeprom10_t;

/**
 * @brief EEPROM 10 Click configuration object.
 * @details Configuration object definition of EEPROM 10 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t wp;              /**< Write protection pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} eeprom10_cfg_t;

/**
 * @brief EEPROM 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EEPROM10_OK = 0,
    EEPROM10_ERROR = -1

} eeprom10_return_value_t;

/*!
 * @addtogroup eeprom10 EEPROM 10 Click Driver
 * @brief API for configuring and manipulating EEPROM 10 Click driver.
 * @{
 */

/**
 * @brief EEPROM 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom10_cfg_setup ( eeprom10_cfg_t *cfg );

/**
 * @brief EEPROM 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #eeprom10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom10_init ( eeprom10_t *ctx, eeprom10_cfg_t *cfg );

/**
 * @brief EEPROM 10 write enable function.
 * @details This function enables write to the EEPROM.
 * @param[in] ctx : Click context object.
 * See #eeprom10_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void eeprom10_write_enable( eeprom10_t *ctx );

/**
 * @brief EEPROM 10 write protection enable function.
 * @details This function enables write protection to the EEPROM.
 * @param[in] ctx : Click context object.
 * See #eeprom10_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void eeprom10_write_protect( eeprom10_t *ctx );

/**
 * @brief EEPROM 10 write byte function.
 * @details This function is used to write a byte of data into selected address.
 * @param[in] ctx : Click context object.
 * See #eeprom10_t object definition for detailed explanation.
 * @param[in] address : Selected memory address.
 * @param[in] data_in : Byte of data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom10_write_byte ( eeprom10_t *ctx, uint16_t address, uint8_t data_in );

/**
 * @brief EEPROM 10 write page function.
 * @details This function is used to write a page of data into selected address.
 * @param[in] ctx : Click context object.
 * See #eeprom10_t object definition for detailed explanation.
 * @param[in] address : Selected memory address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom10_write_page ( eeprom10_t *ctx, uint8_t address, uint8_t *data_in );

/**
 * @brief EEPROM 10 write desired number of data function.
 * @details This function is used to write a desired number of data into selected address.
 * @param[in] ctx : Click context object.
 * See #eeprom10_t object definition for detailed explanation.
 * @param[in] address : Selected memory address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom10_write_n_byte ( eeprom10_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 10 read byte of data function.
 * @details This function is used to read a byte of data from selected address.
 * @param[in] ctx : Click context object.
 * See #eeprom10_t object definition for detailed explanation.
 * @param[in] address : Selected memory address.
 * @param[out] data_out : Read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom10_read_byte ( eeprom10_t *ctx, uint16_t address, uint8_t *data_out );

/**
 * @brief EEPROM 10 read page of data function.
 * @details This function is used to read a page of data from selected address.
 * @param[in] ctx : Click context object.
 * See #eeprom10_t object definition for detailed explanation.
 * @param[in] address : Selected memory address.
 * @param[out] data_out : Read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom10_read_page ( eeprom10_t *ctx, uint8_t address, uint8_t *data_out );

/**
 * @brief EEPROM 10 read desired number of data function.
 * @details This function is used to read a desired number of data from selected address.
 * @param[in] ctx : Click context object.
 * See #eeprom10_t object definition for detailed explanation.
 * @param[in] address : Selected memory address.
 * @param[out] data_out : Read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom10_read_n_byte ( eeprom10_t *ctx, uint16_t address, uint8_t *data_out, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif // EEPROM10_H

/*! @} */ // eeprom10

// ------------------------------------------------------------------------ END
