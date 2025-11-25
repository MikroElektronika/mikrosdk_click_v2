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
 * @file flash14.h
 * @brief This file contains API for Flash 14 Click Driver.
 */

#ifndef FLASH14_H
#define FLASH14_H

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

/*!
 * @addtogroup flash14 Flash 14 Click Driver
 * @brief API for configuring and manipulating Flash 14 Click driver.
 * @{
 */

/**
 * @defgroup flash14_reg Flash 14 Registers List
 * @brief List of registers of Flash 14 Click driver.
 */

/**
 * @addtogroup flash14_reg
 * @{
 */

/**
 * @brief Flash 14 commands list.
 * @details Specified commands list of Flash 14 Click driver.
 */
#define FLASH14_CMD_READ_DATA                       0x03
#define FLASH14_CMD_FAST_READ                       0x0B
#define FLASH14_CMD_PAGE_PROGRAM                    0x02
#define FLASH14_CMD_SECTOR_ERASE_4KB                0x20
#define FLASH14_CMD_BLOCK_ERASE_32KB                0x52
#define FLASH14_CMD_BLOCK_ERASE_64KB                0xD8
#define FLASH14_CMD_CHIP_ERASE                      0x60
#define FLASH14_CMD_4B_READ_DATA                    0x13
#define FLASH14_CMD_4B_FAST_READ                    0x0C
#define FLASH14_CMD_4B_PAGE_PROGRAM                 0x12
#define FLASH14_CMD_4B_SECTOR_ERASE_4KB             0x21
#define FLASH14_CMD_4B_BLOCK_ERASE_32KB             0x5C
#define FLASH14_CMD_4B_BLOCK_ERASE_64KB             0xDC
#define FLASH14_CMD_WRITE_ENABLE                    0x06
#define FLASH14_CMD_WRITE_DISABLE                   0x04
#define FLASH14_CMD_FACTORY_MODE_ENABLE             0x41
#define FLASH14_CMD_READ_STATUS                     0x05
#define FLASH14_CMD_READ_CONFIG                     0x15
#define FLASH14_CMD_WRITE_STATUS                    0x01
#define FLASH14_CMD_READ_EXT_ADDRESS                0xC8
#define FLASH14_CMD_WRITE_EXT_ADDRESS               0xC5
#define FLASH14_CMD_WRITE_PROTECT_SEL               0x68
#define FLASH14_CMD_ENTER_4B_MODE                   0xB7
#define FLASH14_CMD_EXIT_4B_MODE                    0xE9
#define FLASH14_CMD_ERASE_PROGRAM_SUSPEND           0xB0
#define FLASH14_CMD_ERASE_PROGRAM_RESUME            0x30
#define FLASH14_CMD_POWER_DOWN                      0xB9
#define FLASH14_CMD_RELEASE_POWER_DOWN              0xAB
#define FLASH14_CMD_SET_BURST_LEN                   0xC0
#define FLASH14_CMD_JEDEC_ID                        0x9F
#define FLASH14_CMD_ELECTRONIC_ID                   0xAB
#define FLASH14_CMD_MANUFACTURER_DEVICE_ID          0x90
#define FLASH14_CMD_READ_SFDP_MODE                  0x5A
#define FLASH14_CMD_ENTER_SECURED_OTP               0xB1
#define FLASH14_CMD_EXIT_SECURED_OTP                0xC1
#define FLASH14_CMD_READ_SECURITY_REG               0x2B
#define FLASH14_CMD_WRITE_SECURITY_REG              0x2F
#define FLASH14_CMD_WRITE_SPB_BIT                   0xE3
#define FLASH14_CMD_ERASE_ALL_SPB_BIT               0xE4
#define FLASH14_CMD_READ_SPB_STATUS                 0xE2
#define FLASH14_CMD_GANG_BLOCK_LOCK                 0x7E
#define FLASH14_CMD_GANG_BLOCK_UNLOCK               0x98
#define FLASH14_CMD_WRITE_LOCK_REG                  0x2C
#define FLASH14_CMD_READ_LOCK_REG                   0x2D
#define FLASH14_CMD_WRITE_DPB_REG                   0xE1
#define FLASH14_CMD_READ_DPB_REG                    0xE0
#define FLASH14_CMD_ENABLE_RESET                    0x66
#define FLASH14_CMD_RESET_DEVICE                    0x99
#define FLASH14_CMD_NOP                             0x00

/*! @} */ // flash14_reg

/**
 * @defgroup flash14_set Flash 14 Registers Settings
 * @brief Settings for registers of Flash 14 Click driver.
 */

/**
 * @addtogroup flash14_set
 * @{
 */

/**
 * @brief Flash 14 status register settings.
 * @details Specified status register settings of Flash 14 Click driver.
 */
#define FLASH14_STATUS_QE                           0x80
#define FLASH14_STATUS_BP4                          0x40
#define FLASH14_STATUS_BP3                          0x20
#define FLASH14_STATUS_BP2                          0x10
#define FLASH14_STATUS_BP1                          0x08
#define FLASH14_STATUS_BP0                          0x04
#define FLASH14_STATUS_WEL                          0x02
#define FLASH14_STATUS_WIP                          0x01

/**
 * @brief Flash 14 memory address range.
 * @details Specified memory address range of Flash 14 Click driver.
 */
#define FLASH14_MIN_ADDRESS                         0x00000000ul
#define FLASH14_MAX_ADDRESS                         0x01FFFFFFul
#define FLASH14_PAGE_SIZE                           256

/**
 * @brief Flash 14 device ID.
 * @details Specified device ID of Flash 14 Click driver.
 */
#define FLASH14_MANUFACTURER_ID                     0xC2
#define FLASH14_DEVICE_ID                           0x18

/*! @} */ // flash14_set

/**
 * @defgroup flash14_map Flash 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Flash 14 Click driver.
 */

/**
 * @addtogroup flash14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Flash 14 Click to the selected MikroBUS.
 */
#define FLASH14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wp   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.hold = MIKROBUS( mikrobus, MIKROBUS_PWM ); \

/*! @} */ // flash14_map
/*! @} */ // flash14

/**
 * @brief Flash 14 Click context object.
 * @details Context object definition of Flash 14 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t mosi;             /**< Master output - slave input pin descriptor for SPI driver. */
    digital_out_t sck;              /**< Clock pin descriptor for SPI driver. */
    digital_out_t cs;               /**< Chip select pin descriptor for SPI driver. */
    digital_out_t hold;             /**< Hold/Reset pin (Active Low). */
    digital_out_t wp;               /**< Write protect pin (Active Low). */

    // Input pins
    digital_in_t miso;              /**< Master input - slave output pin descriptor for SPI driver. */

} flash14_t;

/**
 * @brief Flash 14 Click configuration object.
 * @details Configuration object definition of Flash 14 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t hold;                /**< Hold/Reset pin (Active Low). */
    pin_name_t wp;                  /**< Write protect pin (Active Low). */

} flash14_cfg_t;

/**
 * @brief Flash 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FLASH14_OK = 0,
    FLASH14_ERROR = -1

} flash14_return_value_t;

/*!
 * @addtogroup flash14 Flash 14 Click Driver
 * @brief API for configuring and manipulating Flash 14 Click driver.
 * @{
 */

/**
 * @brief Flash 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #flash14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void flash14_cfg_setup ( flash14_cfg_t *cfg );

/**
 * @brief Flash 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #flash14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash14_init ( flash14_t *ctx, flash14_cfg_t *cfg );

/**
 * @brief Flash 14 write cmd function.
 * @details This function writes a desired command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @return None.
 * @note None.
 */
void flash14_write_cmd ( flash14_t *ctx, uint8_t cmd );

/**
 * @brief Flash 14 write cmd data function.
 * @details This function writes a desired number of data bytes to 
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written (up to 8).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash14_write_cmd_data ( flash14_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief Flash 14 read cmd data function.
 * @details This function reads a desired number of data bytes from
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read (up to 8).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash14_read_cmd_data ( flash14_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief Flash 14 write cmd address data function.
 * @details This function writes a desired number of data bytes starting from a desired address of
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] address : Memory address (up to 0x01FFFFFF).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash14_write_cmd_address_data ( flash14_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_in, uint32_t len );

/**
 * @brief Flash 14 read cmd address data function.
 * @details This function reads a desired number of data bytes starting from a desired address of
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] address : Memory address (up to 0x01FFFFFF).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash14_read_cmd_address_data ( flash14_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_out, uint32_t len );

/**
 * @brief Flash 14 memory write function.
 * @details This function writes a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000000-0x01FFFFFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes (up to 256).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash14_memory_write ( flash14_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len );

/**
 * @brief Flash 14 memory read function.
 * @details This function reads a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000000-0x01FFFFFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash14_memory_read ( flash14_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );

/**
 * @brief Flash 14 erase memory function.
 * @details This function erases the selected amount of memory which contains the selected address.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[in] erase_cmd : Erase command.
 * @param[in] address : The block of memory that contains this address will be erased. 
 * Ignored for FLASH14_CMD_CHIP_ERASE command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash14_erase_memory ( flash14_t *ctx, uint8_t erase_cmd, uint32_t address );

/**
 * @brief Flash 14 check communication function.
 * @details This function checks the communication by reading and verifying the device ID and
 * if OK it enters the 4-byte mode.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash14_check_communication ( flash14_t *ctx );

/**
 * @brief Flash 14 write protect function.
 * @details This function write protects the entire memory via the WP pin and WRITE DISABLE command.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash14_write_protect ( flash14_t *ctx );

/**
 * @brief Flash 14 write enable function.
 * @details This function disables memory write-protect via the WP pin and WRITE ENABLE command.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash14_write_enable ( flash14_t *ctx );

/**
 * @brief Flash 14 soft reset function.
 * @details This function executes the soft reset command.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void flash14_soft_reset ( flash14_t *ctx );

/**
 * @brief Flash 14 set wp pin function.
 * @details This function sets the WP pin logic state.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void flash14_set_wp_pin ( flash14_t *ctx, uint8_t state );

/**
 * @brief Flash 14 set hold pin function.
 * @details This function sets the HOLD pin logic state.
 * @param[in] ctx : Click context object.
 * See #flash14_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void flash14_set_hold_pin ( flash14_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // FLASH14_H

/*! @} */ // flash14

// ------------------------------------------------------------------------ END
