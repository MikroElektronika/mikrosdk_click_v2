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
 * @file clickid.h
 * @brief This file contains API for ClickID Driver.
 */

#ifndef CLICKID_H
#define CLICKID_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_one_wire.h"

/*!
 * @addtogroup clickid ClickID Driver
 * @brief API for configuring and manipulating ClickID driver.
 * @{
 */

/**
 * @defgroup clickid_cmd ClickID Commands List
 * @brief List of commands of ClickID driver.
 */

/**
 * @addtogroup clickid_cmd
 * @{
 */

/**
 * @brief ClickID commands list.
 * @details Specified commands list of ClickID driver.
 */
#define CLICKID_CMD_WRITE_MEMORY            0x96
#define CLICKID_CMD_READ_MEMORY             0x69
#define CLICKID_CMD_RELEASE                 0xAA

/*! @} */ // clickid_cmd

/**
 * @defgroup clickid_set ClickID Settings
 * @brief Settings of ClickID driver.
 */

/**
 * @addtogroup clickid_set
 * @{
 */

/**
 * @brief ClickID memory access result list.
 * @details Specified memory access result list of ClickID driver.
 */
#define CLICKID_MEM_ACCESS_SUCCESS          0xAA
#define CLICKID_MEM_ACCESS_FAIL             0x55

/**
 * @brief ClickID memory map.
 * @details Specified memory map of ClickID driver.
 */
#define CLICKID_USER_EEPROM_START           0x0000
#define CLICKID_USER_EEPROM_END             0x01FF
#define CLICKID_PAGE_START                  0x00
#define CLICKID_PAGE_END                    0x1F
#define CLICKID_PAGE_SIZE                   32
#define CLICKID_MANIFEST_START_ADDRESS      0x0020

/**
 * @brief ClickID family code value.
 * @details Specified family code value of ClickID driver.
 */
#define CLICKID_FAMILY_CODE                 0xCC

/*! @} */ // clickid_set

/**
 * @defgroup clickid_map ClickID MikroBUS Map
 * @brief MikroBUS pin mapping of ClickID driver.
 */

/**
 * @addtogroup clickid_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ClickID to the selected MikroBUS.
 */
#define CLICKID_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // clickid_map
/*! @} */ // clickid

/**
 * @brief ClickID version.
 * @details ClickID version object definition of ClickID driver.
 */
typedef struct
{
    uint8_t major; 
    uint8_t minor;
    
} clickid_version_t;

/**
 * @brief ClickID information.
 * @details Permanent manifest - ClickID information object definition of ClickID driver.
 */
typedef struct
{
    clickid_version_t hw_rev;           /**< Click HW revision. */
    uint16_t serial;                    /**< Click serial (10-bit PID) from Product ID field. */
    uint16_t type;                      /**< Click type (10-bit) from Product ID field. */
    uint8_t custom;                     /**< Click custom (1-bit) from Product ID field. */
    uint8_t name[ 20 ];                 /**< Click name. */
    
} clickid_information_t;

/**
 * @brief ClickID context object.
 * @details Context object definition of ClickID driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                  /**< Multiplexer select pin. */

    // Modules
    one_wire_t ow;                      /**< One Wire driver object. */

    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */

} clickid_t;

/**
 * @brief ClickID configuration object.
 * @details Configuration object definition of ClickID driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t cs;                      /**< 1-wire I/O pin. */

    // Additional gpio pins
    pin_name_t rst;                     /**< Multiplexer select pin. */

} clickid_cfg_t;

/**
 * @brief ClickID return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CLICKID_OK = 0,
    CLICKID_ERROR = -1

} clickid_return_value_t;

/*!
 * @addtogroup clickid ClickID Driver
 * @brief API for configuring and manipulating ClickID driver.
 * @{
 */

/**
 * @brief ClickID configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : configuration structure.
 * See #clickid_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void clickid_cfg_setup ( clickid_cfg_t *cfg );

/**
 * @brief ClickID initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : context object.
 * See #clickid_t object definition for detailed explanation.
 * @param[in] cfg : configuration structure.
 * See #clickid_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clickid_init ( clickid_t *ctx, clickid_cfg_t *cfg );

/**
 * @brief ClickID de-initialization function.
 * @details This function de-initializes One Wire driver and sets the RST pin to HIGH logic state.
 * @param[out] ctx : context object.
 * See #clickid_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void clickid_deinit ( clickid_t *ctx );

/**
 * @brief ClickID check communication function.
 * @details This function checks the communication by reading the ROM address 
 * as well as verifying family code and CRC 8.
 * @param[in] ctx : context object.
 * See #clickid_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clickid_check_communication ( clickid_t *ctx );

/**
 * @brief ClickID read memory function.
 * @details This function reads a desired number of data bytes starting from the selected address of
 * the EEPROM memory using One Wire communication protocol.
 * @param[in] ctx : context object.
 * See #clickid_t object definition for detailed explanation.
 * @param[in] address : Starting address.
 * @param[out] data_out : Output data buffer.
 * @param[in] len : Number of data bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clickid_read_memory ( clickid_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );

/**
 * @brief ClickID write memory function.
 * @details This function writes a desired number of data bytes starting from the selected address of
 * the EEPROM memory using One Wire communication protocol.
 * @param[in] ctx : context object.
 * See #clickid_t object definition for detailed explanation.
 * @param[in] address : Starting address, must be aligned to the page start.
 * @param[in] data_in : Data input buffer.
 * @param[in] len : Number of data bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clickid_write_memory ( clickid_t *ctx, uint16_t address, uint8_t *data_in, uint16_t len );

/**
 * @brief ClickID read information function.
 * @details This function reads the click board information from the permanent data memory.
 * @param[in] ctx : context object.
 * See #clickid_t object definition for detailed explanation.
 * @param[out] info : Click board information.
 * See #clickid_information_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clickid_read_information ( clickid_t *ctx, clickid_information_t *info );

#ifdef __cplusplus
}
#endif
#endif // CLICKID_H

/*! @} */ // clickid

// ------------------------------------------------------------------------ END
