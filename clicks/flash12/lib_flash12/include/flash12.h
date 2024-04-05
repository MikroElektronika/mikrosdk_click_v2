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
 * @file flash12.h
 * @brief This file contains API for Flash 12 Click Driver.
 */

#ifndef FLASH12_H
#define FLASH12_H

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
 * @addtogroup flash12 Flash 12 Click Driver
 * @brief API for configuring and manipulating Flash 12 Click driver.
 * @{
 */

/**
 * @defgroup flash12_cmd Flash 12 Command List
 * @brief List of commands of Flash 12 Click driver.
 */

/**
 * @addtogroup flash12_cmd
 * @{
 */

/**
 * @brief Flash 12 read command list.
 * @details Specified read command list of Flash 12 Click driver.
 */
#define FLASH12_CMD_READ_ARRAY              0x03
#define FLASH12_CMD_FAST_READ_ARRAY         0x0B

/**
 * @brief Flash 12 program/erase and suspend command list.
 * @details Specified program/erase and suspend command list of Flash 12 Click driver.
 */
#define FLASH12_CMD_BYTE_PAGE_PROGRAM       0x02
#define FLASH12_CMD_PAGE_ERASE              0x81
#define FLASH12_CMD_BLOCK_ERASE_4KB         0x20
#define FLASH12_CMD_BLOCK_ERASE_32KB        0x52
#define FLASH12_CMD_BLOCK_ERASE_64KB        0xD8
#define FLASH12_CMD_CHIP_ERASE              0x60

/**
 * @brief Flash 12 security command list.
 * @details Specified security command list of Flash 12 Click driver.
 */
#define FLASH12_CMD_ERASE_SECURITY_REG      0x44
#define FLASH12_CMD_PROGRAM_SECURITY_REG    0x42
#define FLASH12_CMD_READ_SECURITY_REG       0x48
#define FLASH12_CMD_READ_SERIAL_FLASH       0x5A

/**
 * @brief Flash 12 configuration command list.
 * @details Specified configuration command list of Flash 12 Click driver.
 */
#define FLASH12_CMD_WRITE_ENABLE            0x06
#define FLASH12_CMD_VOLATILE_STATUS         0x50
#define FLASH12_CMD_WRITE_DISABLE           0x04

/**
 * @brief Flash 12 status register command list.
 * @details Specified status register command list of Flash 12 Click driver.
 */
#define FLASH12_CMD_READ_STATUS_1           0x05
#define FLASH12_CMD_WRITE_STATUS_1          0x01
#define FLASH12_CMD_READ_STATUS_2           0x35
#define FLASH12_CMD_ACT_STATUS_INT          0x25

/**
 * @brief Flash 12 ID and power command list.
 * @details Specified ID and power command list of Flash 12 Click driver.
 */
#define FLASH12_CMD_DEEP_POWER_DOWN         0xB9
#define FLASH12_CMD_RELEASE_PD_ID           0xAB
#define FLASH12_CMD_MANUFACTURER_ID         0x90
#define FLASH12_CMD_JEDEC_ID                0x9F
#define FLASH12_CMD_READ_UNIQUE_ID_NUM      0x4B

/**
 * @brief Flash 12 other command list.
 * @details Specified other command list of Flash 12 Click driver.
 */
#define FLASH12_CMD_ENABLE_RESET            0x66
#define FLASH12_CMD_RESET_DEVICE            0x99


/*! @} */ // flash12_cmd

/**
 * @defgroup flash12_set Flash 12 Registers Settings
 * @brief Settings for registers of Flash 12 Click driver.
 */

/**
 * @addtogroup flash12_set
 * @{
 */

/**
 * @brief Flash 12 description setting.
 * @details Specified setting for description of Flash 12 Click driver.
 */
#define FLASH12_MANUFACTURER_ID             0x1F
#define FLASH12_DEVICE_ID                   0x14

/**
 * @brief Flash 12 status register 1 settings.
 * @details Specified status register 1 settings of Flash 12 Click driver.
 */
#define FLASH12_STATUS1_SRP0                0x80
#define FLASH12_STATUS1_BPSIZE              0x40
#define FLASH12_STATUS1_TB                  0x20
#define FLASH12_STATUS1_WEL                 0x02
#define FLASH12_STATUS1_BSY                 0x01

/**
 * @brief Flash 12 memory address range.
 * @details Specified memory address range of Flash 12 Click driver.
 */
#define FLASH12_MIN_ADDRESS                 0x000000ul
#define FLASH12_MAX_ADDRESS                 0x07FFFFul
#define FLASH12_PAGE_SIZE                   256
#define FLASH12_CMD_MAX_LEN                 8

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b flash12_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define FLASH12_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define FLASH12_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // flash12_set

/**
 * @defgroup flash12_map Flash 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Flash 12 Click driver.
 */

/**
 * @addtogroup flash12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Flash 12 Click to the selected MikroBUS.
 */
#define FLASH12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.wp   = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.hld  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // flash12_map
/*! @} */ // flash12

/**
 * @brief Flash 12 Click context object.
 * @details Context object definition of Flash 12 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wp;     /**< Write protect pin. */
    digital_out_t hld;    /**< Hold pin. */

    // Modules
    spi_master_t spi;     /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} flash12_t;

/**
 * @brief Flash 12 Click configuration object.
 * @details Configuration object definition of Flash 12 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t wp;     /**< Write protect pin. */
    pin_name_t hld;    /**< Hold pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} flash12_cfg_t;

/**
 * @brief Flash 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FLASH12_OK = 0,
    FLASH12_ERROR = -1

} flash12_return_value_t;

/*!
 * @addtogroup flash12 Flash 12 Click Driver
 * @brief API for configuring and manipulating Flash 12 Click driver.
 * @{
 */

/**
 * @brief Flash 12 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #flash12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void flash12_cfg_setup ( flash12_cfg_t *cfg );

/**
 * @brief Flash 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #flash12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_init ( flash12_t *ctx, flash12_cfg_t *cfg );

/**
 * @brief Flash 12 default configuration function.
 * @details This function executes a default configuration of Flash 12
 * click board.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t flash12_default_cfg ( flash12_t *ctx );

/**
 * @brief Flash 12 hardware write enable function.
 * @details This function disabled hardware write protection of the entire memory 
 * of the AT25EU0041A, 4-Mbit, Ultra-Low Energy Serial Flash Memory 
 * on the Flash 12 Click board.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void flash12_hw_write_enable ( flash12_t *ctx );

/**
 * @brief Flash 12 hardware write disable function.
 * @details This function enabled hardware write protection of the entire memory 
 * of the AT25EU0041A, 4-Mbit, Ultra-Low Energy Serial Flash Memory 
 * on the Flash 12 Click board.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void flash12_hw_write_disable ( flash12_t *ctx );

/**
 * @brief Flash 12 hold disable function.
 * @details This function is used to disable SPI communication pause
 * of the AT25EU0041A, 4-Mbit, Ultra-Low Energy Serial Flash Memory 
 * on the Flash 12 Click board.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void flash12_hold_disable ( flash12_t *ctx );

/**
 * @brief Flash 12 hold enable function.
 * @details This function is used to enable SPI communication pauses
 * of the AT25EU0041A, 4-Mbit, Ultra-Low Energy Serial Flash Memory 
 * on the Flash 12 Click board.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void flash12_hold_enable ( flash12_t *ctx );

/**
 * @brief Flash 12 command writing function.
 * @details This function writes a desired command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @param[in] cmd : Command data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_write_cmd ( flash12_t *ctx, uint8_t cmd );

/**
 * @brief Flash 12 command data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @param[in] cmd : Command data.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_write_cmd_data ( flash12_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief Flash 12 command data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @param[in] cmd : Command data.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_read_cmd_data ( flash12_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief Flash 12 command address data writing function.
 * @details This function writes a desired number of data bytes starting from a desired address 
 * of the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] mem_addr : Memory address [0x000000-0x07FFFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_write_cmd_address_data ( flash12_t *ctx, uint8_t cmd, uint32_t mem_addr, uint8_t *data_in, uint32_t len );

/**
 * @brief Flash 12 command address data reading function.
 * @details This function reads a desired number of data bytes starting from a desired address
 * the selected command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] mem_addr : Memory address [0x000000-0x07FFFF].
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_read_cmd_address_data ( flash12_t *ctx, uint8_t cmd, uint32_t mem_addr, uint8_t *data_out, uint32_t len );

/**
 * @brief Flash 12 memory data writing function.
 * @details This function writes a desired number of data bytes starting 
 * to the selected memory address by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] mem_addr : Memory address [0x000000-0x07FFFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_memory_write ( flash12_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint32_t len );

/**
 * @brief Flash 12 memory data reading function.
 * @details This function reads a desired number of data bytes starting 
 * from the selected memory address by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] mem_addr : Memory address [0x000000-0x07FFFF].
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_memory_read ( flash12_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint32_t len );

/**
 * @brief Flash 12 soft reset function.
 * @details This function executes the soft reset command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_soft_reset ( flash12_t *ctx );

/**
 * @brief Flash 12 write disable function.
 * @details This function write disable the entire memory 
 * via the hardware write disable function and write disable command.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_write_disable ( flash12_t *ctx );

/**
 * @brief Flash 12 write enable function.
 * @details This function write enable the entire memory 
 * via the hardware write enable function and write enable command.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_write_enable ( flash12_t *ctx );

/**
 * @brief Flash 12 status reading function.
 * @details This function reads a desired status register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @param[in] reg_num : Status register number.
 * @param[out] status : Status output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_read_status ( flash12_t *ctx, uint8_t reg_num, uint8_t *status );

/**
 * @brief Flash 12 status writing function.
 * @details This function writes a desired data bytes to the write status register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @param[in] status : Status output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_write_status ( flash12_t *ctx, uint8_t status );

/**
 * @brief Flash 12 erase memory function.
 * @details This function erases the selected amount of memory which contains the selected address
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @param[in] erase_cmd : Erase command.
 * @param[in] mem_addr : The block of memory that contains this address will be erased. 
 * Ignored for FLASH12_CMD_CHIP_ERASE command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_erase_memory ( flash12_t *ctx, uint8_t erase_cmd, uint32_t mem_addr );

/**
 * @brief Flash 12 device ID reading function.
 * @details This function reads a manufacturer and device ID by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash12_t object definition for detailed explanation.
 * @param[out] mfr_id : Manufacturer ID.
 * @param[out] dev_id : Device ID. 
 * Ignored for FLASH12_CMD_CHIP_ERASE command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash12_get_device_id ( flash12_t *ctx, uint8_t *mfr_id, uint8_t *dev_id );

#ifdef __cplusplus
}
#endif
#endif // FLASH12_H

/*! @} */ // flash12

// ------------------------------------------------------------------------ END
