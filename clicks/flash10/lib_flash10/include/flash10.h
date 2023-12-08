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
 * @file flash10.h
 * @brief This file contains API for Flash 10 Click Driver.
 */

#ifndef FLASH10_H
#define FLASH10_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup flash10 Flash 10 Click Driver
 * @brief API for configuring and manipulating Flash 10 Click driver.
 * @{
 */

/**
 * @defgroup flash10_reg Flash 10 Registers List
 * @brief List of registers of Flash 10 Click driver.
 */

/**
 * @addtogroup flash10_reg
 * @{
 */

/**
 * @brief Flash 10 read commands list.
 * @details Specified read commands list of Flash 10 Click driver.
 */
#define FLASH10_CMD_READ_ARRAY              0x03
#define FLASH10_CMD_FAST_READ_ARRAY         0x0B

/**
 * @brief Flash 10 program/erase commands list.
 * @details Specified program/erase commands list of Flash 10 Click driver.
 */
#define FLASH10_CMD_BLOCK_ERASE_4KB         0x20
#define FLASH10_CMD_BLOCK_ERASE_32KB        0x52
#define FLASH10_CMD_BLOCK_ERASE_64KB        0xD8
#define FLASH10_CMD_CHIP_ERASE              0x60
#define FLASH10_CMD_BYTE_PAGE_PROGRAM       0x02
#define FLASH10_CMD_SEQUENTIAL_PROGRAM      0xAD
#define FLASH10_CMD_ERASE_PROGRAM_SUSPEND   0x75
#define FLASH10_CMD_ERASE_PROGRAM_RESUME    0x7A

/**
 * @brief Flash 10 protection commands list.
 * @details Specified protection commands list of Flash 10 Click driver.
 */
#define FLASH10_CMD_WRITE_ENABLE            0x06
#define FLASH10_CMD_WRITE_DISABLE           0x04
#define FLASH10_CMD_VOLATILE_STATUS         0x50
#define FLASH10_CMD_INDIVIDUAL_BLOCK_LOCK   0x36
#define FLASH10_CMD_INDIVIDUAL_BLOCK_UNLOCK 0x39
#define FLASH10_CMD_READ_BLOCK_LOCK         0x3C
#define FLASH10_CMD_GLOBAL_BLOCK_LOCK       0x7E
#define FLASH10_CMD_GLOBAL_BLOCK_UNLOCK     0x98

/**
 * @brief Flash 10 security register commands list.
 * @details Specified security register commands list of Flash 10 Click driver.
 */
#define FLASH10_CMD_PROGRAM_OTP_SECURITY    0x9B
#define FLASH10_CMD_READ_OTP_SECURITY       0x4B

/**
 * @brief Flash 10 security register commands list.
 * @details Specified security register commands list of Flash 10 Click driver.
 */
#define FLASH10_CMD_READ_STATUS_1           0x05
#define FLASH10_CMD_READ_STATUS_2           0x35
#define FLASH10_CMD_READ_STATUS_3           0x15
#define FLASH10_CMD_READ_STATUS_4           0x65
#define FLASH10_CMD_READ_STATUS_5           0x65
#define FLASH10_CMD_WRITE_STATUS_1          0x01
#define FLASH10_CMD_WRITE_STATUS_2          0x31
#define FLASH10_CMD_WRITE_STATUS_3          0x11
#define FLASH10_CMD_WRITE_STATUS_4          0x71
#define FLASH10_CMD_WRITE_STATUS_5          0x71
#define FLASH10_CMD_READ_STATUS             0x65
#define FLASH10_CMD_WRITE_STATUS            0x71
#define FLASH10_CMD_STATUS_LOCK             0x6F

/**
 * @brief Flash 10 power down commands list.
 * @details Specified power down commands list of Flash 10 Click driver.
 */
#define FLASH10_CMD_DEEP_POWER_DOWN         0xB9
#define FLASH10_CMD_ULTRA_DEEP_POWER_DOWN   0x79
#define FLASH10_CMD_RESUME_FROM_DPD         0xAB

/**
 * @brief Flash 10 reset commands list.
 * @details Specified reset commands list of Flash 10 Click driver.
 */
#define FLASH10_CMD_ENABLE_RESET            0x66
#define FLASH10_CMD_RESET_DEVICE            0x99
#define FLASH10_CMD_TERMINATE               0xF0

/**
 * @brief Flash 10 manufacturer/device commands list.
 * @details Specified manufacturer/device commands list of Flash 10 Click driver.
 */
#define FLASH10_CMD_MANUFACTURER_ID         0x90
#define FLASH10_CMD_JEDEC_ID                0x9F

/**
 * @brief Flash 10 miscellaneous commands list.
 * @details Specified miscellaneous commands list of Flash 10 Click driver.
 */
#define FLASH10_CMD_READ_SFDP               0x5A

/*! @} */ // flash10_reg

/**
 * @defgroup flash10_set Flash 10 Registers Settings
 * @brief Settings for registers of Flash 10 Click driver.
 */

/**
 * @addtogroup flash10_set
 * @{
 */

/**
 * @brief Flash 10 status register numbers.
 * @details Specified status register numbers of Flash 10 Click driver.
 */
#define FLASH10_STATUS_REG_1                1
#define FLASH10_STATUS_REG_2                2
#define FLASH10_STATUS_REG_3                3
#define FLASH10_STATUS_REG_4                4
#define FLASH10_STATUS_REG_5                5

/**
 * @brief Flash 10 status register 1 settings.
 * @details Specified status register 1 settings of Flash 10 Click driver.
 */
#define FLASH10_STATUS1_SRP0                0x80
#define FLASH10_STATUS1_BPSIZE              0x40
#define FLASH10_STATUS1_TB                  0x20
#define FLASH10_STATUS1_WEL                 0x02
#define FLASH10_STATUS1_BSY                 0x01

/**
 * @brief Flash 10 memory address range.
 * @details Specified memory address range of Flash 10 Click driver.
 */
#define FLASH10_MIN_ADDRESS                 0x000000
#define FLASH10_MAX_ADDRESS                 0x3FFFFFul
#define FLASH10_PAGE_SIZE                   256

/**
 * @brief Flash 10 device ID.
 * @details Specified device ID of Flash 10 Click driver.
 */
#define FLASH10_MANUFACTURER_ID             0x1F
#define FLASH10_DEVICE_ID                   0x47

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b flash10_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define FLASH10_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define FLASH10_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // flash10_set

/**
 * @defgroup flash10_map Flash 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Flash 10 Click driver.
 */

/**
 * @addtogroup flash10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Flash 10 Click to the selected MikroBUS.
 */
#define FLASH10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // flash10_map
/*! @} */ // flash10

/**
 * @brief Flash 10 Click context object.
 * @details Context object definition of Flash 10 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Hold/Reset pin (Active Low). */
    digital_out_t wp;               /**< Write protect pin (Active Low). */

    // Modules
    spi_master_t  spi;              /**< SPI driver object. */

    pin_name_t    chip_select;      /**< Chip select pin descriptor (used for SPI driver). */

} flash10_t;

/**
 * @brief Flash 10 Click configuration object.
 * @details Configuration object definition of Flash 10 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Hold/Reset pin (Active Low). */
    pin_name_t wp;                  /**< Write protect pin (Active Low). */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} flash10_cfg_t;

/**
 * @brief Flash 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FLASH10_OK = 0,
    FLASH10_ERROR = -1

} flash10_return_value_t;

/*!
 * @addtogroup flash10 Flash 10 Click Driver
 * @brief API for configuring and manipulating Flash 10 Click driver.
 * @{
 */

/**
 * @brief Flash 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #flash10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void flash10_cfg_setup ( flash10_cfg_t *cfg );

/**
 * @brief Flash 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #flash10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_init ( flash10_t *ctx, flash10_cfg_t *cfg );

/**
 * @brief Flash 10 write cmd function.
 * @details This function writes a desired command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_write_cmd ( flash10_t *ctx, uint8_t cmd );

/**
 * @brief Flash 10 write cmd data function.
 * @details This function writes a desired number of data bytes to 
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written (up to 8).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_write_cmd_data ( flash10_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief Flash 10 read cmd data function.
 * @details This function reads a desired number of data bytes from
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read (up to 8).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_read_cmd_data ( flash10_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief Flash 10 write cmd address data function.
 * @details This function writes a desired number of data bytes starting from a desired address of
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] address : Memory address (up to 0x3FFFFF).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_write_cmd_address_data ( flash10_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_in, uint32_t len );

/**
 * @brief Flash 10 read cmd address data function.
 * @details This function reads a desired number of data bytes starting from a desired address of
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] address : Memory address (up to 0x3FFFFF).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_read_cmd_address_data ( flash10_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_out, uint32_t len );

/**
 * @brief Flash 10 memory write function.
 * @details This function writes a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x3FFFFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes (up to 256).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_memory_write ( flash10_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len );

/**
 * @brief Flash 10 memory read function.
 * @details This function reads a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x3FFFFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_memory_read ( flash10_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );

/**
 * @brief Flash 10 erase memory function.
 * @details This function erases the selected amount of memory which contains the selected address.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] erase_cmd : Erase command.
 * @param[in] address : The block of memory that contains this address will be erased. 
 * Ignored for FLASH10_CMD_CHIP_ERASE command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_erase_memory ( flash10_t *ctx, uint8_t erase_cmd, uint32_t address );

/**
 * @brief Flash 10 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_check_communication ( flash10_t *ctx );

/**
 * @brief Flash 10 write protect function.
 * @details This function write protects the entire memory via the WP pin and WRITE DISABLE command.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
err_t flash10_write_protect ( flash10_t *ctx );

/**
 * @brief Flash 10 write enable function.
 * @details This function disables memory write-protect via the WP pin and WRITE ENABLE command.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
err_t flash10_write_enable ( flash10_t *ctx );

/**
 * @brief Flash 10 soft reset function.
 * @details This function executes the soft reset command.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_soft_reset ( flash10_t *ctx );

/**
 * @brief Flash 10 write status function.
 * @details This function writes data to the selected status register.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] status_reg_num : Status register number (1-5).
 * @param[in] status : Status data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_write_status ( flash10_t *ctx, uint8_t status_reg_num, uint8_t status );

/**
 * @brief Flash 10 read status function.
 * @details This function reads data from the selected status register.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] status_reg_num : Status register number (1-5).
 * @param[out] status : Status data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash10_read_status ( flash10_t *ctx, uint8_t status_reg_num, uint8_t *status );

/**
 * @brief Flash 10 set wp pin function.
 * @details This function sets the WP pin logic state.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void flash10_set_wp_pin ( flash10_t *ctx, uint8_t state );

/**
 * @brief Flash 10 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #flash10_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void flash10_set_rst_pin ( flash10_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // FLASH10_H

/*! @} */ // flash10

// ------------------------------------------------------------------------ END
