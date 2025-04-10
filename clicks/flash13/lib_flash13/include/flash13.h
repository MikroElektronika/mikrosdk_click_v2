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
 * @file flash13.h
 * @brief This file contains API for Flash 13 Click Driver.
 */

#ifndef FLASH13_H
#define FLASH13_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup flash13 Flash 13 Click Driver
 * @brief API for configuring and manipulating Flash 13 Click driver.
 * @{
 */

/**
 * @defgroup flash13_reg Flash 13 Registers List
 * @brief List of registers of Flash 13 Click driver.
 */

/**
 * @addtogroup flash13_reg
 * @{
 */

/**
 * @brief Flash 13 Instruction Set Table 1 commands.
 * @details Specified commands for Instruction Set Table 1 of Flash 13 Click driver.
 */
#define FLASH13_CMD_WRITE_ENABLE                    0x06
#define FLASH13_CMD_VOLATILE_SR_WRITE_ENABLE        0x50
#define FLASH13_CMD_WRITE_DISABLE                   0x04
#define FLASH13_CMD_READ_STATUS_REG_1               0x05
#define FLASH13_CMD_WRITE_STATUS_REG_1              0x01
#define FLASH13_CMD_READ_STATUS_REG_2               0x35
#define FLASH13_CMD_WRITE_STATUS_REG_2              0x31
#define FLASH13_CMD_READ_STATUS_REG_3               0x15
#define FLASH13_CMD_WRITE_STATUS_REG_3              0x11
#define FLASH13_CMD_CHIP_ERASE                      0x60
#define FLASH13_CMD_ERASE_PROGRAM_SUSPEND           0x75
#define FLASH13_CMD_ERASE_PROGRAM_RESUME            0x7A
#define FLASH13_CMD_POWER_DOWN                      0xB9
#define FLASH13_CMD_RELEASE_POWER_DOWN              0xAB
#define FLASH13_CMD_MANUFACTURER_DEVICE_ID          0x90
#define FLASH13_CMD_JEDEC_ID                        0x9F
#define FLASH13_CMD_ENABLE_RESET                    0x66
#define FLASH13_CMD_RESET_DEVICE                    0x99
#define FLASH13_CMD_READ_SERIAL_FLASH_DISC_PAR      0x5A
#define FLASH13_CMD_READ_UNIQUE_ID                  0x4B

/**
 * @brief Flash 13 Instruction Set Table 2 commands.
 * @details Specified commands for Instruction Set Table 2 of Flash 13 Click driver.
 */
#define FLASH13_CMD_PAGE_PROGRAM                    0x02
#define FLASH13_CMD_SECTOR_ERASE_4KB                0x20
#define FLASH13_CMD_BLOCK_ERASE_32KB                0x52
#define FLASH13_CMD_BLOCK_ERASE_64KB                0xD8
#define FLASH13_CMD_READ_DATA                       0x03
#define FLASH13_CMD_FAST_READ                       0x0B
#define FLASH13_CMD_ERASE_SECURITY_REG              0x44
#define FLASH13_CMD_PROGRAM_SECURITY_REG            0x42
#define FLASH13_CMD_READ_SECURITY_REG               0x48
#define FLASH13_CMD_SET_BURST_WITH_WRAP             0x77

/*! @} */ // flash13_reg

/**
 * @defgroup flash13_set Flash 13 Registers Settings
 * @brief Settings for registers of Flash 13 Click driver.
 */

/**
 * @addtogroup flash13_set
 * @{
 */

/**
 * @brief Flash 13 status register settings.
 * @details Specified status register settings of Flash 13 Click driver.
 */
#define FLASH13_STATUS3_HOLD_RST                    0x80
#define FLASH13_STATUS3_DRV1                        0x40
#define FLASH13_STATUS3_DRV0                        0x20
#define FLASH13_STATUS3_DC                          0x10
#define FLASH13_STATUS2_SUS1                        0x80
#define FLASH13_STATUS2_CMP                         0x40
#define FLASH13_STATUS2_LB3                         0x20
#define FLASH13_STATUS2_LB2                         0x10
#define FLASH13_STATUS2_LB1                         0x08
#define FLASH13_STATUS2_SUS2                        0x04
#define FLASH13_STATUS2_QE                          0x02
#define FLASH13_STATUS2_SRP1                        0x01
#define FLASH13_STATUS1_SRP0                        0x80
#define FLASH13_STATUS1_BP4                         0x40
#define FLASH13_STATUS1_BP3                         0x20
#define FLASH13_STATUS1_BP2                         0x10
#define FLASH13_STATUS1_BP1                         0x08
#define FLASH13_STATUS1_BP0                         0x04
#define FLASH13_STATUS1_WEL                         0x02
#define FLASH13_STATUS1_WIP                         0x01

/**
 * @brief Flash 13 memory address range.
 * @details Specified memory address range of Flash 13 Click driver.
 */
#define FLASH13_MIN_ADDRESS                         0x000000ul
#define FLASH13_MAX_ADDRESS                         0x1FFFFFul
#define FLASH13_PAGE_SIZE                           256

/**
 * @brief Flash 13 device ID.
 * @details Specified device ID of Flash 13 Click driver.
 */
#define FLASH13_MANUFACTURER_ID                     0x68
#define FLASH13_DEVICE_ID                           0x14

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b flash13_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define FLASH13_SET_DATA_SAMPLE_EDGE                SET_SPI_DATA_SAMPLE_EDGE
#define FLASH13_SET_DATA_SAMPLE_MIDDLE              SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // flash13_set

/**
 * @defgroup flash13_map Flash 13 MikroBUS Map
 * @brief MikroBUS pin mapping of Flash 13 Click driver.
 */

/**
 * @addtogroup flash13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Flash 13 Click to the selected MikroBUS.
 */
#define FLASH13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wp   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.hold = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // flash13_map
/*! @} */ // flash13

/**
 * @brief Flash 13 Click context object.
 * @details Context object definition of Flash 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t hold;             /**< Hold/Reset pin (Active Low). */
    digital_out_t wp;               /**< Write protect pin (Active Low). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */

} flash13_t;

/**
 * @brief Flash 13 Click configuration object.
 * @details Configuration object definition of Flash 13 Click driver.
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

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} flash13_cfg_t;

/**
 * @brief Flash 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FLASH13_OK = 0,
    FLASH13_ERROR = -1

} flash13_return_value_t;

/*!
 * @addtogroup flash13 Flash 13 Click Driver
 * @brief API for configuring and manipulating Flash 13 Click driver.
 * @{
 */

/**
 * @brief Flash 13 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #flash13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void flash13_cfg_setup ( flash13_cfg_t *cfg );

/**
 * @brief Flash 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #flash13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash13_init ( flash13_t *ctx, flash13_cfg_t *cfg );

/**
 * @brief Flash 13 write cmd function.
 * @details This function writes a desired command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash13_write_cmd ( flash13_t *ctx, uint8_t cmd );

/**
 * @brief Flash 13 write cmd data function.
 * @details This function writes a desired number of data bytes to 
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written (up to 8).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash13_write_cmd_data ( flash13_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief Flash 13 read cmd data function.
 * @details This function reads a desired number of data bytes from
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read (up to 8).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash13_read_cmd_data ( flash13_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief Flash 13 write cmd address data function.
 * @details This function writes a desired number of data bytes starting from a desired address of
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] address : Memory address (up to 0x1FFFFF).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash13_write_cmd_address_data ( flash13_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_in, uint32_t len );

/**
 * @brief Flash 13 read cmd address data function.
 * @details This function reads a desired number of data bytes starting from a desired address of
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] address : Memory address (up to 0x1FFFFF).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash13_read_cmd_address_data ( flash13_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_out, uint32_t len );

/**
 * @brief Flash 13 memory write function.
 * @details This function writes a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x1FFFFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes (up to 256).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash13_memory_write ( flash13_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len );

/**
 * @brief Flash 13 memory read function.
 * @details This function reads a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x1FFFFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash13_memory_read ( flash13_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );

/**
 * @brief Flash 13 erase memory function.
 * @details This function erases the selected amount of memory which contains the selected address.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @param[in] erase_cmd : Erase command.
 * @param[in] address : The block of memory that contains this address will be erased. 
 * Ignored for FLASH13_CMD_CHIP_ERASE command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash13_erase_memory ( flash13_t *ctx, uint8_t erase_cmd, uint32_t address );

/**
 * @brief Flash 13 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash13_check_communication ( flash13_t *ctx );

/**
 * @brief Flash 13 write protect function.
 * @details This function write protects the entire memory via the WP pin and WRITE DISABLE command.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
err_t flash13_write_protect ( flash13_t *ctx );

/**
 * @brief Flash 13 write enable function.
 * @details This function disables memory write-protect via the WP pin and WRITE ENABLE command.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
err_t flash13_write_enable ( flash13_t *ctx );

/**
 * @brief Flash 13 soft reset function.
 * @details This function executes the soft reset command.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash13_soft_reset ( flash13_t *ctx );

/**
 * @brief Flash 13 set wp pin function.
 * @details This function sets the WP pin logic state.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void flash13_set_wp_pin ( flash13_t *ctx, uint8_t state );

/**
 * @brief Flash 13 set hold pin function.
 * @details This function sets the HOLD pin logic state.
 * @param[in] ctx : Click context object.
 * See #flash13_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void flash13_set_hold_pin ( flash13_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // FLASH13_H

/*! @} */ // flash13

// ------------------------------------------------------------------------ END
