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
 * @file eeprom8.h
 * @brief This file contains API for EEPROM 8 Click Driver.
 */

#ifndef EEPROM8_H
#define EEPROM8_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup eeprom8 EEPROM 8 Click Driver
 * @brief API for configuring and manipulating EEPROM 8 Click driver.
 * @{
 */

/**
 * @defgroup eeprom8_set EEPROM 8 Registers Settings
 * @brief Settings for registers of EEPROM 8 Click driver.
 */
#define EEPROM8_WRITE_ENABLE        0
#define EEPROM8_WRITE_PROTECT       1
/**
 * @addtogroup eeprom8_set
 * @{
 */

/**
 * @brief EEPROM 8 description setting.
 * @details Specified setting for description of EEPROM 8 Click driver.
 */

/**
 * \defgroup mem_block Memory Block
 * \{
 */

/**
 * @brief EEPROM 8 memory address range.
 * @details Specified memory address range of EEPROM 8 Click driver.
 */
#define EEPROM8_BLOCK_ADDR_START    0x0000
#define EEPROM8_BLOCK_ADDR_END      0xFFFFul

/** \} */

/**
 * \defgroup ndata_lim Data Transfer Limit
 * \{
 */

/**
 * @brief EEPROM 8 data transfer option.
 * @details Specified data transfer byte and page write options of EEPROM 8 Click driver.
 */
#define EEPROM8_NBYTES_MIN          1
#define EEPROM8_NBYTES_PAGE         128
/** \} */

/**
 * @brief EEPROM 8 device address setting.
 * @details Specified setting for device slave address selection of
 * EEPROM 8 Click driver.
 */
#define EEPROM8_SET_DEV_ADDR        0x50

/*! @} */ // eeprom8_set

/**
 * @defgroup eeprom8_map EEPROM 8 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 8 Click driver.
 */

/**
 * @addtogroup eeprom8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 8 Click to the selected MikroBUS.
 */
#define EEPROM8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM ); 


/*! @} */ // eeprom8_map
/*! @} */ // eeprom8

/**
 * @brief Click address (memory block) selection.
 * @details Memory block is defined by ADDR SEL switch.
 */
typedef enum
{
    EEPROM_I2C_ADDR_SEL_0 = 0,
    EEPROM_I2C_ADDR_SEL_1,
    EEPROM_I2C_ADDR_SEL_2,
    EEPROM_I2C_ADDR_SEL_3,
    EEPROM_I2C_ADDR_SEL_4,
    EEPROM_I2C_ADDR_SEL_5,
    EEPROM_I2C_ADDR_SEL_6,
    EEPROM_I2C_ADDR_SEL_7

} eeprom_i2c_address_selector_t;

/**
 * @brief EEPROM 8 Click context object.
 * @details Context object definition of EEPROM 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  wp;          /**< Write protection pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} eeprom8_t;

/**
 * @brief EEPROM 8 Click configuration object.
 * @details Configuration object definition of EEPROM 8 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  wp;             /**< Write protection pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} eeprom8_cfg_t;

/**
 * @brief EEPROM 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EEPROM8_OK = 0,
    EEPROM8_ERROR = -1

} eeprom8_return_value_t;

/*!
 * @addtogroup eeprom8 EEPROM 8 Click Driver
 * @brief API for configuring and manipulating EEPROM 8 Click driver.
 * @{
 */

/**
 * @brief EEPROM 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom8_cfg_setup ( eeprom8_cfg_t *cfg );

/**
 * @brief EEPROM 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #eeprom8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom8_init ( eeprom8_t *ctx, eeprom8_cfg_t *cfg );


/**
 * @brief Byte Write function.
 * @details This function writes one byte data to the desired register.
 * @param[in] ctx  Click object.
 * @param[in] reg_addr  Register address.
 * @param[in] data_in  Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation
 * @note None.
 */
err_t eeprom8_write_byte( eeprom8_t *ctx, uint16_t reg_addr, uint8_t data_in );

/**
 * @brief Page Write function.
 * @details This function writes up to 128 bytes of data starting from the selected register.
 * @param[in] ctx  Click object.
 * @param[in] reg_addr  Register address.
 * @param[in] data_in  Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom8_write_page( eeprom8_t *ctx, uint16_t reg_addr, uint8_t *data_in );

/**
 * @brief Random Byte Read function.
 * @details This function reads one byte data from the desired register.
 * @param[in] ctx  Click object.
 * @param[in] reg_addr  Register address.
 * @param[out] data_out Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom8_read_random_byte( eeprom8_t *ctx, uint16_t reg_addr, uint8_t *data_out );

/**
 * @brief Byte Read function.
 * @details This function reads one byte data based on internal address pointer.
 * @param[in] ctx  Click object.
 * @param[out] data_out Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom8_read_current_byte( eeprom8_t *ctx, uint8_t *data_out );

/**
 * @brief Sequential Read function.
 * @details This function reads the desired number of bytes starting from the selected register.
 * @param[in] ctx  Click object.
 * @param[in] reg_addr  Register address.
 * @param[in] n_bytes  Number of bytes to be read.
 * @param[out] data_out  Output read data buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom8_read_sequential( eeprom8_t *ctx, uint16_t reg_addr, uint16_t n_bytes, uint8_t *data_out );

/**
 * @brief Write Enable function.
 * @details This function allows data writing operation to the EEPROM8.
 * @param[in] ctx  Click object.
 * @return Nothing.
 * @note None.
 */
void eeprom8_write_enable( eeprom8_t *ctx );

/**
 * @brief Write Protect function.
 * @details This function prevents data writing operation to the EEPROM8.
 * @param[in] ctx  Click object.
 * @return Nothing.
 * @note None.
 */
void eeprom8_write_protect( eeprom8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EEPROM8_H

/*! @} */ // eeprom8

// ------------------------------------------------------------------------ END
