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
 * @file eeprom14.h
 * @brief This file contains API for EEPROM 14 Click Driver.
 */

#ifndef EEPROM14_H
#define EEPROM14_H

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
 * @addtogroup eeprom14 EEPROM 14 Click Driver
 * @brief API for configuring and manipulating EEPROM 14 Click driver.
 * @{
 */

/**
 * @defgroup eeprom14_set EEPROM 14 Settings
 * @brief Settings of EEPROM 14 Click driver.
 */

/**
 * @addtogroup eeprom14_set
 * @{
 */

/**
 * @brief EEPROM 14 memory size setting.
 * @details Specified setting for memory size of EEPROM 14 Click driver.
 */
#define EEPROM14_MEM_ADDR_START                     0x0000
#define EEPROM14_MEM_ADDR_END                       0xFFFF
#define EEPROM14_MEM_PAGE_SIZE                      128

/**
 * @brief EEPROM 14 device address setting.
 * @details Specified setting for device slave address selection of
 * EEPROM 14 Click driver.
 */
#define EEPROM14_DEVICE_ADDRESS_A2A1A0_000          0x50
#define EEPROM14_DEVICE_ADDRESS_A2A1A0_001          0x51
#define EEPROM14_DEVICE_ADDRESS_A2A1A0_010          0x52
#define EEPROM14_DEVICE_ADDRESS_A2A1A0_011          0x53
#define EEPROM14_DEVICE_ADDRESS_A2A1A0_100          0x54
#define EEPROM14_DEVICE_ADDRESS_A2A1A0_101          0x55
#define EEPROM14_DEVICE_ADDRESS_A2A1A0_110          0x56
#define EEPROM14_DEVICE_ADDRESS_A2A1A0_111          0x57

/*! @} */ // eeprom14_set

/**
 * @defgroup eeprom14_map EEPROM 14 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 14 Click driver.
 */

/**
 * @addtogroup eeprom14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 14 Click to the selected MikroBUS.
 */
#define EEPROM14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // eeprom14_map
/*! @} */ // eeprom14

/**
 * @brief EEPROM 14 Click context object.
 * @details Context object definition of EEPROM 14 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wp;           /**< Write protect pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} eeprom14_t;

/**
 * @brief EEPROM 14 Click configuration object.
 * @details Configuration object definition of EEPROM 14 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t wp;              /**< Write protect pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} eeprom14_cfg_t;

/**
 * @brief EEPROM 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EEPROM14_OK = 0,
    EEPROM14_ERROR = -1

} eeprom14_return_value_t;

/*!
 * @addtogroup eeprom14 EEPROM 14 Click Driver
 * @brief API for configuring and manipulating EEPROM 14 Click driver.
 * @{
 */

/**
 * @brief EEPROM 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom14_cfg_setup ( eeprom14_cfg_t *cfg );

/**
 * @brief EEPROM 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #eeprom14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom14_init ( eeprom14_t *ctx, eeprom14_cfg_t *cfg );

/**
 * @brief EEPROM 14 write memory function.
 * @details This function writes a sequence of bytes to the device memory over I2C,
 * starting at the selected 16-bit address. The write length must not exceed the
 * page size and the transfer must not cross the device end address.
 * @param[in] ctx : Click context object.
 * See #eeprom14_t object definition for detailed explanation.
 * @param[in] address : Start memory address (16-bit).
 * @param[in] data_in : Pointer to input data buffer.
 * @param[in] len : Number of bytes to write (max page size).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom14_write_memory ( eeprom14_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 14 read memory function.
 * @details This function reads a sequence of bytes from the device memory over I2C,
 * starting at the selected 16-bit address. The read length must not exceed the
 * page size and the transfer must not cross the device end address.
 * @param[in] ctx : Click context object.
 * See #eeprom14_t object definition for detailed explanation.
 * @param[in] address : Start memory address (16-bit).
 * @param[out] data_out : Pointer to output data buffer.
 * @param[in] len : Number of bytes to read (max page size).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom14_read_memory ( eeprom14_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );

/**
 * @brief EEPROM 14 write-enable function.
 * @details This function enables write operations by driving the WP pin low.
 * @param[in] ctx : Click context object.
 * See #eeprom14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void eeprom14_write_enable ( eeprom14_t *ctx );

/**
 * @brief EEPROM 14 write-protect function.
 * @details This function disables write operations by driving the WP pin high.
 * @param[in] ctx : Click context object.
 * See #eeprom14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void eeprom14_write_protect ( eeprom14_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EEPROM14_H

/*! @} */ // eeprom14

// ------------------------------------------------------------------------ END
