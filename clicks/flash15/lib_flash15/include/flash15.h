/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file flash15.h
 * @brief This file contains API for Flash 15 Click Driver.
 */

#ifndef FLASH15_H
#define FLASH15_H

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
 * @addtogroup flash15 Flash 15 Click Driver
 * @brief API for configuring and manipulating Flash 15 Click driver.
 * @{
 */

/**
 * @defgroup flash15_reg Flash 15 Registers List
 * @brief List of registers of Flash 15 Click driver.
 */

/**
 * @addtogroup flash15_reg
 * @{
 */

/**
 * @brief Flash 15 commands list.
 * @details Specified commands list of Flash 15 Click driver.
 */
#define FLASH15_CMD_SOFT_RESET                      0xFF
#define FLASH15_CMD_READ_JEDEC_ID                   0x9F
#define FLASH15_CMD_GET_FEATURE                     0x0F
#define FLASH15_CMD_SET_FEATURE                     0x1F
#define FLASH15_CMD_WRITE_ENABLE                    0x06
#define FLASH15_CMD_WRITE_DISABLE                   0x04
#define FLASH15_CMD_BLOCK_ERASE                     0xD8
#define FLASH15_CMD_PROGRAM_DATA_LOAD               0x02
#define FLASH15_CMD_RANDOM_PROGRAM_DATA_LOAD        0x84
#define FLASH15_CMD_QUAD_PROGRAM_DATA_LOAD          0x32
#define FLASH15_CMD_RANDOM_QUAD_PROGRAM_DATA_LOAD   0x34
#define FLASH15_CMD_PROGRAM_EXECUTE                 0x10
#define FLASH15_CMD_PAGE_READ                       0x13
#define FLASH15_CMD_READ_FROM_CACHE                 0x03
#define FLASH15_CMD_FAST_READ_FROM_CACHE            0x0B
#define FLASH15_CMD_READ_FROM_CACHE_X2              0x3B
#define FLASH15_CMD_READ_FROM_CACHE_X4              0x6B

/**
 * @brief Flash 15 status registers list.
 * @details Specified status registers list of Flash 15 Click driver.
 */
#define FLASH15_REG_PROTECTION                      0xA0
#define FLASH15_REG_CONFIGURATION                   0xB0
#define FLASH15_REG_STATUS                          0xC0
#define FLASH15_REG_SECTOR0_ECC_STATUS              0x80
#define FLASH15_REG_SECTOR1_ECC_STATUS              0x84
#define FLASH15_REG_SECTOR2_ECC_STATUS              0x88
#define FLASH15_REG_SECTOR3_ECC_STATUS              0x8C

/*! @} */ // flash15_reg

/**
 * @defgroup flash15_set Flash 15 Registers Settings
 * @brief Settings for registers of Flash 15 Click driver.
 */

/**
 * @addtogroup flash15_set
 * @{
 */

/**
 * @brief Flash 15 protection register settings.
 * @details Specified protection register settings of Flash 15 Click driver.
 */
#define FLASH15_PROTECTION_NONE                     0x00
#define FLASH15_PROTECTION_UPPER_1_OF_512           0x08
#define FLASH15_PROTECTION_UPPER_1_OF_256           0x10
#define FLASH15_PROTECTION_UPPER_1_OF_128           0x18
#define FLASH15_PROTECTION_UPPER_1_OF_64            0x20
#define FLASH15_PROTECTION_UPPER_1_OF_32            0x28
#define FLASH15_PROTECTION_UPPER_1_OF_16            0x30
#define FLASH15_PROTECTION_UPPER_1_OF_8             0x38
#define FLASH15_PROTECTION_UPPER_1_OF_4             0x40
#define FLASH15_PROTECTION_UPPER_1_OF_2             0x48
#define FLASH15_PROTECTION_LOWER_1_OF_512           0x0C
#define FLASH15_PROTECTION_LOWER_1_OF_256           0x14
#define FLASH15_PROTECTION_LOWER_1_OF_128           0x1C
#define FLASH15_PROTECTION_LOWER_1_OF_64            0x24
#define FLASH15_PROTECTION_LOWER_1_OF_32            0x2C
#define FLASH15_PROTECTION_LOWER_1_OF_16            0x34
#define FLASH15_PROTECTION_LOWER_1_OF_8             0x3C
#define FLASH15_PROTECTION_LOWER_1_OF_4             0x44
#define FLASH15_PROTECTION_ALL                      0x7C

/**
 * @brief Flash 15 status register settings.
 * @details Specified status register settings of Flash 15 Click driver.
 */
#define FLASH15_STATUS_ECCS1                        0x20
#define FLASH15_STATUS_ECCS0                        0x10
#define FLASH15_STATUS_P_FAIL                       0x08
#define FLASH15_STATUS_E_FAIL                       0x04
#define FLASH15_STATUS_WEL                          0x02
#define FLASH15_STATUS_OIP                          0x01

/**
 * @brief Flash 15 memory address range.
 * @details Specified memory address range of Flash 15 Click driver.
 */
#define FLASH15_COLUMN_ADDRESS_MIN                  0x0000
#define FLASH15_COLUMN_ADDRESS_MAX                  0x0FFF
#define FLASH15_PAGE_ADDRESS_MIN                    0x0000
#define FLASH15_PAGE_ADDRESS_MAX                    0x7FFF
#define FLASH15_PAGE_SIZE                           2048

/**
 * @brief Flash 15 device ID.
 * @details Specified device ID of Flash 15 Click driver.
 */
#define FLASH15_MANUFACTURER_ID                     0xCD
#define FLASH15_DEVICE_ID                           0x70

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b flash15_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define FLASH15_SET_DATA_SAMPLE_EDGE                SET_SPI_DATA_SAMPLE_EDGE
#define FLASH15_SET_DATA_SAMPLE_MIDDLE              SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // flash15_set

/**
 * @defgroup flash15_map Flash 15 MikroBUS Map
 * @brief MikroBUS pin mapping of Flash 15 Click driver.
 */

/**
 * @addtogroup flash15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Flash 15 Click to the selected MikroBUS.
 */
#define FLASH15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wp   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.hold = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // flash15_map
/*! @} */ // flash15

/**
 * @brief Flash 15 Click context object.
 * @details Context object definition of Flash 15 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wp;               /**< Write protect pin (Active Low). */
    digital_out_t hold;             /**< Hold/Reset pin (Active Low). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */

} flash15_t;

/**
 * @brief Flash 15 Click configuration object.
 * @details Configuration object definition of Flash 15 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t wp;                  /**< Write protect pin (Active Low). */
    pin_name_t hold;                /**< Hold/Reset pin (Active Low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} flash15_cfg_t;

/**
 * @brief Flash 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FLASH15_OK = 0,
    FLASH15_ERROR = -1

} flash15_return_value_t;

/*!
 * @addtogroup flash15 Flash 15 Click Driver
 * @brief API for configuring and manipulating Flash 15 Click driver.
 * @{
 */

/**
 * @brief Flash 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #flash15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void flash15_cfg_setup ( flash15_cfg_t *cfg );

/**
 * @brief Flash 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #flash15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_init ( flash15_t *ctx, flash15_cfg_t *cfg );

/**
 * @brief Flash 15 write cmd function.
 * @details This function writes a desired command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_write_cmd ( flash15_t *ctx, uint8_t cmd );

/**
 * @brief Flash 15 write cmd data function.
 * @details This function writes a desired number of data bytes to 
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written (up to 8).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_write_cmd_data ( flash15_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief Flash 15 read cmd data function.
 * @details This function reads a desired number of data bytes from
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read (up to 8).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_read_cmd_data ( flash15_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief Flash 15 get feature function.
 * @details This function reads a feature register value from the device.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @param[in] reg : Feature register address.
 * @param[out] data_out : Output data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_get_feature ( flash15_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Flash 15 set feature function.
 * @details This function writes a value to the selected feature register.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @param[in] reg : Feature register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_set_feature ( flash15_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Flash 15 memory write function.
 * @details This function writes a desired number of data bytes starting from the
 * selected memory page and column.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @param[in] page : The memory page that contains column to be written. 
 * @param[in] column : Starting memory address from page column (up to FLASH15_COLUMN_ADDRESS_MAX).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes (up to FLASH15_COLUMN_ADDRESS_MAX + 64 + 1).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_memory_write ( flash15_t *ctx, uint16_t page, uint16_t column, uint8_t *data_in, uint16_t len );

/**
 * @brief Flash 15 memory read function.
 * @details This function reads a desired number of data bytes starting from the
 * selected memory page and column.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @param[in] page : The memory page that contains column to be read. 
 * @param[in] column : Starting memory address from page column (up to FLASH15_COLUMN_ADDRESS_MAX).
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes (up to FLASH15_COLUMN_ADDRESS_MAX + 64 + 1).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_memory_read ( flash15_t *ctx, uint16_t page, uint16_t column, uint8_t *data_out, uint16_t len );

/**
 * @brief Flash 15 erase memory function.
 * @details This function erases the memory block which contains the selected page address.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @param[in] page : The block of memory that contains this page will be erased. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_erase_memory ( flash15_t *ctx, uint16_t page );

/**
 * @brief Flash 15 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_check_communication ( flash15_t *ctx );

/**
 * @brief Flash 15 write protect function.
 * @details This function write protects the entire memory via the WP pin and WRITE DISABLE command.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_write_protect ( flash15_t *ctx );

/**
 * @brief Flash 15 write enable function.
 * @details This function disables memory write-protect via the WP pin and WRITE ENABLE command.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_write_enable ( flash15_t *ctx );

/**
 * @brief Flash 15 soft reset function.
 * @details This function executes the soft reset command.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash15_soft_reset ( flash15_t *ctx );

/**
 * @brief Flash 15 set wp pin function.
 * @details This function sets the WP pin logic state.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void flash15_set_wp_pin ( flash15_t *ctx, uint8_t state );

/**
 * @brief Flash 15 set hold pin function.
 * @details This function sets the HOLD pin logic state.
 * @param[in] ctx : Click context object.
 * See #flash15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void flash15_set_hold_pin ( flash15_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // FLASH15_H

/*! @} */ // flash15

// ------------------------------------------------------------------------ END
