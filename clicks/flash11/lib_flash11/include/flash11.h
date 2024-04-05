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
 * @file flash11.h
 * @brief This file contains API for Flash 11 Click Driver.
 */

#ifndef FLASH11_H
#define FLASH11_H

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
 * @addtogroup flash11 Flash 11 Click Driver
 * @brief API for configuring and manipulating Flash 11 Click driver.
 * @{
 */

/**
 * @defgroup flash11_opcode Flash 11 command opcode list.
 * @brief List of command opcode of Flash 11 Click driver.
 */

/**
 * @addtogroup flash11_opcode
 * @{
 */

/**
 * @brief Flash 11 description system commands.
 * @details Specified system commands of Flash 11 Click driver.
 */
#define FLASH11_CMD_ENABLE_RESET            0x66
#define FLASH11_CMD_RESET_DEVICE            0x99
#define FLASH11_CMD_DEEP_POWER_DOWN         0xB9
#define FLASH11_CMD_RESUME_FROM_DPD         0xAB

/**
 * @brief Flash 11 description read commands.
 * @details Specified read commands of Flash 11 Click driver.
 */
#define FLASH11_CMD_READ_ARRAY              0x03
#define FLASH11_CMD_FAST_READ_ARRAY         0x0B

/**
 * @brief Flash 11 description read commands.
 * @details Specified read commands of Flash 11 Click driver.
 */
#define FLASH11_CMD_WRITE_ENABLE            0x06
#define FLASH11_CMD_VOLATILE_SR_WR_EN       0x50
#define FLASH11_CMD_WRITE_DISABLE           0x04

/**
 * @brief Flash 11 description program commands.
 * @details Specified program commands of Flash 11 Click driver.
 */
#define FLASH11_CMD_BYTE_PAGE_PROGRAM       0x02

/**
 * @brief Flash 11 description erase commands.
 * @details Specified erase commands of Flash 11 Click driver.
 */
#define FLASH11_CMD_BLOCK_ERASE_4KB         0x20
#define FLASH11_CMD_BLOCK_ERASE_32KB        0x52
#define FLASH11_CMD_BLOCK_ERASE_64KB        0xD8
#define FLASH11_CMD_CHIP_ERASE              0x60

/**
 * @brief Flash 11 description suspend/resume commands.
 * @details Specified suspend/resume commands of Flash 11 Click driver.
 */
#define FLASH11_CMD_ERASE_PROGRAM_SUSPEND   0x75
#define FLASH11_CMD_ERASE_PROGRAM_RESUME    0x7A

/**
 * @brief Flash 11 description status register commands.
 * @details Specified status register commands of Flash 11 Click driver.
 */
#define FLASH11_CMD_READ_STATUS_1           0x05
#define FLASH11_CMD_READ_STATUS_2           0x35
#define FLASH11_CMD_READ_STATUS_3           0x15
#define FLASH11_CMD_WRITE_STATUS_1          0x01
#define FLASH11_CMD_WRITE_STATUS_2          0x31
#define FLASH11_CMD_WRITE_STATUS_3          0x11

/**
 * @brief Flash 11 description device information commands.
 * @details Specified device information commands of Flash 11 Click driver.
 */
#define FLASH11_CMD_MANUFACTURER_ID         0x90
#define FLASH11_CMD_READ_JEDEC_ID           0x9F
#define FLASH11_CMD_READ_SERIAL_FLASH_DP    0x5A

/**
 * @brief Flash 11 description OTP commands.
 * @details Specified OTP commands of Flash 11 Click driver.
 */
#define FLASH11_CMD_ERASE_SECURITY_REG      0x44
#define FLASH11_CMD_PROGRAM_SECURITY_REG    0x42
#define FLASH11_CMD_READ_SECURITY_REG       0x48
#define FLASH11_CMD_READ_UNIQUE_ID_NUM      0x4B

/*! @} */ // flash11_opcode

/**
 * @defgroup flash11_set Flash 11 Registers Settings
 * @brief Settings for registers of Flash 11 Click driver.
 */

/**
 * @addtogroup flash11_set
 * @{
 */

/**
 * @brief Flash 11 description status register 1 bit assignments.
 * @details Specified status register 1 bit assignments of Flash 11 Click driver.
 */
#define FLASH11_STATUS1_SRP0_BIT_MASK       0x80
#define FLASH11_STATUS1_BP4_BIT_MASK        0x40
#define FLASH11_STATUS1_BP3_BIT_MASK        0x20
#define FLASH11_STATUS1_BP2_BIT_MASK        0x10
#define FLASH11_STATUS1_BP1_BIT_MASK        0x08
#define FLASH11_STATUS1_BP0_BIT_MASK        0x04
#define FLASH11_STATUS1_WEL_EN              0x02
#define FLASH11_STATUS1_WEL_DIS             0x00
#define FLASH11_STATUS1_BSY                 0x01
#define FLASH11_STATUS1_RDY                 0x00

/**
 * @brief Flash 11 description manufacturer and device ID.
 * @details Specified manufacturer and device ID of Flash 11 Click driver.
 */
#define FLASH11_MANUFACTURER_ID             0x1F
#define FLASH11_DEVICE_ID_0                 0x87
#define FLASH11_DEVICE_ID_1                 0x01

/**
 * @brief Flash 11 description status register 1 bit assignments.
 * @details Specified status register 1 bit assignments of Flash 11 Click driver.
 */
#define FLASH11_MIN_ADDRESS                 0x000000
#define FLASH11_MAX_ADDRESS                 0x3FFFFFul
#define FLASH11_PAGE_SIZE                   256

/**
 * @brief Flash 11 description of the write-protection pin logic state.
 * @details Specified write-protection pin logic state of Flash 11 Click driver.
 */
#define FLASH11_WRITE_PROTECT_ENABLE         0
#define FLASH11_WRITE_PROTECT_DISABLE        1

/**
 * @brief Flash 11 description of the hold pin logic state.
 * @details Specified hold pin logic state of Flash 11 Click driver.
 */
#define FLASH11_HOLD_ENABLE                  0
#define FLASH11_HOLD_DISABLE                 1

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b flash11_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define FLASH11_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define FLASH11_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // flash11_set

/**
 * @defgroup flash11_map Flash 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Flash 11 Click driver.
 */

/**
 * @addtogroup flash11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Flash 11 Click to the selected MikroBUS.
 */
#define FLASH11_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.hld = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // flash11_map
/*! @} */ // flash11

/**
 * @brief Flash 11 Click context object.
 * @details Context object definition of Flash 11 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wp;     /**< Write-protection pin. */
    digital_out_t hld;    /**< Hold pin. */

    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} flash11_t;

/**
 * @brief Flash 11 Click configuration object.
 * @details Configuration object definition of Flash 11 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t wp;     /**< Write-protection pin. */
    pin_name_t hld;    /**< Hold pin. */

    // static variable
    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */

} flash11_cfg_t;

/**
 * @brief Flash 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FLASH11_OK = 0,
    FLASH11_ERROR = -1

} flash11_return_value_t;

/*!
 * @addtogroup flash11 Flash 11 Click Driver
 * @brief API for configuring and manipulating Flash 11 Click driver.
 * @{
 */

/**
 * @brief Flash 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #flash11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void flash11_cfg_setup ( flash11_cfg_t *cfg );

/**
 * @brief Flash 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #flash11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_init ( flash11_t *ctx, flash11_cfg_t *cfg );

/**
 * @brief Flash 11 default configuration function.
 * @details This function executes a default configuration of Flash 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t flash11_default_cfg ( flash11_t *ctx );

/**
 * @brief Flash 11 data writing function.
 * @details This function writes a desired number of data bytes
 * of the selected 8-bit opcode by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] opcode : Command opcode.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_generic_write ( flash11_t *ctx, uint8_t opcode, uint8_t *data_in, uint8_t len );

/**
 * @brief Flash 11 data reading function.
 * @details This function reads a desired number of data bytes 
 * of the selected 8-bit opcode by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] opcode : Command opcode.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_generic_read ( flash11_t *ctx, uint8_t opcode, uint8_t *data_out, uint8_t len );

/**
 * @brief Flash 11 set the command function.
 * @details This function writes the desired command
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] opcode : Command opcode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_set_cmd ( flash11_t *ctx, uint8_t opcode );

/**
 * @brief Flash 11 write command adress data function.
 * @details This function writes a desired number of data bytes 
 * starting from a desired address of the selected command
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] opcode : Command opcode.
 * @param[in] mem_addr : Flash memory address (0x000000-0x3FFFFF).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_write_cmd_addr_data ( flash11_t *ctx, uint8_t opcode, uint32_t mem_addr, uint8_t *data_in, uint32_t len );

/**
 * @brief Flash 11 read command adress data function.
 * @details This function writes a desired number of data bytes 
 * starting from a desired address of the selected command
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] opcode : Command opcode.
 * @param[in] mem_addr : Flash memory address (0x000000-0x3FFFFF).
 * @param[in] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_read_cmd_addr_data ( flash11_t *ctx, uint8_t opcode, uint32_t mem_addr, uint8_t *data_out, uint32_t len );

/**
 * @brief Flash 11 sw reset function.
 * @details This function performs the software reset
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_sw_reset ( flash11_t *ctx );

/**
 * @brief Flash 11 memory write function.
 * @details This function writes a desired number of data bytes 
 * starting from the selected memory address
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] mem_addr : Flash memory address (0x000000-0x3FFFFF).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_memory_write ( flash11_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint32_t len );

/**
 * @brief Flash 11 memory read function.
 * @details This function reads a desired number of data bytes 
 * starting from the selected memory address
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] mem_addr : Flash memory address (0x000000-0x3FFFFF).
 * @param[in] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_memory_read ( flash11_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint32_t len );

/**
 * @brief Flash 11 write enable function.
 * @details This function write protects the entire memory and sets the write enable command
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_write_enable ( flash11_t *ctx );

/**
 * @brief Flash 11 write disable function.
 * @details This function disables memory write-protect and sets the write disable command
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_write_disable ( flash11_t *ctx );

/**
 * @brief Flash 11 block erase function.
 * @details This function erases the desired amount of memory 
 * starting from the selected memory address
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] cmd_block_erase : Block erase command
 *         @li @c 0x20 (FLASH11_CMD_BLOCK_ERASE_4KB)  - Erase a block of 4 kbytes,
 *         @li @c 0x52 (FLASH11_CMD_BLOCK_ERASE_32KB) - Erase a block of 32 kbytes,
 *         @li @c 0xD8 (FLASH11_CMD_BLOCK_ERASE_64KB) - Erase a block of 64 kbytes.
 * @param[in] mem_addr : Flash memory address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_block_erase ( flash11_t *ctx, uint8_t cmd_block_erase, uint32_t mem_addr );

/**
 * @brief Flash 11 chip erase function.
 * @details This function erases the entire memory array
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_chip_erase ( flash11_t *ctx );

/**
 * @brief Flash 11 set status function.
 * @details This function writes data to the desired status register
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] status_reg : Write status register command.
 * @param[in] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_set_status ( flash11_t *ctx, uint8_t status_reg, uint8_t status );

/**
 * @brief Flash 11 gets the status function.
 * @details This function reads data from the desired status register
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] status_reg : Read status register command.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_get_status ( flash11_t *ctx, uint8_t status_reg, uint8_t *status );

/**
 * @brief Flash 11 gets the device ID function.
 * @details This function reads a Manufacturer ID
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] status_reg : Read status register command.
 * @param[out] status : Status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash11_get_device_id ( flash11_t *ctx, uint8_t *device_id );

/**
 * @brief Flash 11 hardware write protect function.
 * @details This function is used for write-protection
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] en_wp 
 *         @li @c 0 (FLASH11_WRITE_PROTECT_ENABLE)  - Enable write-protection,
 *         @li @c 1 (FLASH11_WRITE_PROTECT_DISABLE) - Disable write-protection.
 * @return Nothing.
 * @note None.
 */
void flash11_hw_write_protect ( flash11_t *ctx, uint8_t en_wp );

/**
 * @brief Flash 11 enable hold function.
 * @details This function is used for pausing communication
 * of the AT25SF321B, 32-Mbit SPI Serial Flash Memory with Dual I/O and Quad I/O Support
 * on the Flash 11 Click board™.
 * @param[in] ctx : Click context object.
 * See #flash11_t object definition for detailed explanation.
 * @param[in] en_hold 
 *         @li @c 0 (FLASH11_HOLD_ENABLE)  - Enable pausing communication,
 *         @li @c 1 (FLASH11_HOLD_DISABLE) - Disable pausing communication.
 * @return Nothing.
 * @note None.
 */
void flash11_en_hold ( flash11_t *ctx, uint8_t en_hold );

#ifdef __cplusplus
}
#endif
#endif // FLASH11_H

/*! @} */ // flash11

// ------------------------------------------------------------------------ END
