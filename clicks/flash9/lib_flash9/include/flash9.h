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
 * @file flash9.h
 * @brief This file contains API for Flash 9 Click Driver.
 */

#ifndef FLASH9_H
#define FLASH9_H

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
 * @addtogroup flash9 Flash 9 Click Driver
 * @brief API for configuring and manipulating Flash 9 Click driver.
 * @{
 */

/**
 * @defgroup flash9_reg Flash 9 Instructions List
 * @brief List of instructions of Flash 9 Click driver.
 */

/**
 * @addtogroup flash9_reg
 * @{
 */

/**
 * @brief Flash 9 Following Upper/Lower Die Instruction.
 * @details Following Upper/Lower Die Instruction of Flash 9 Click driver.
 */
#define FLASH9_CMD_READ_STATUS_REGISTER_1                   0x05
#define FLASH9_CMD_READ_STATUS_REGISTER_2                   0x35
#define FLASH9_CMD_READ_STATUS_REGISTER_3                   0x15
#define FLASH9_CMD_READ_SFDP_REGISTER                       0x5A
#define FLASH9_CMD_ERASE_PROGRAM_SUSPEND                    0x75
#define FLASH9_CMD_ERASE_PROGRAM_RESUME                     0x7A

/**
 * @brief Flash 9 Con-Current Instruction.
 * @details Con-Current Instruction of Flash 9 Click driver.
 */
#define FLASH9_CMD_WRITE_ENABLE                             0x06
#define FLASH9_CMD_VOLATILE_SR_WRITE_ENABLE                 0x50
#define FLASH9_CMD_WRITE_DISABLE                            0x04
#define FLASH9_CMD_READ_UNIQUE_ID                           0x4B
#define FLASH9_CMD_RELEASE_POWER_DOWN_ID                    0xAB
#define FLASH9_CMD_MANUFACTURER_DEVICE_ID                   0x90
#define FLASH9_CMD_JEDEC_ID                                 0x9F
#define FLASH9_CMD_CHIP_ERASE                               0xC7
#define FLASH9_CMD_WRITE_STATUS_REGISTER_1                  0x01
#define FLASH9_CMD_WRITE_STATUS_REGISTER_2                  0x31
#define FLASH9_CMD_WRITE_STATUS_REGISTER_3                  0x11
#define FLASH9_CMD_GLOBAL_BLOCK_LOCK                        0x7E
#define FLASH9_CMD_GLOBAL_BLOCK_UNLOCK                      0x98
#define FLASH9_CMD_POWER_DOWN                               0xB9
#define FLASH9_CMD_ENTER_4BYTE_ADDRESS_MODE                 0xB7
#define FLASH9_CMD_EXIT_4BYTE_ADDRESS_MODE                  0xE9
#define FLASH9_CMD_ENABLE_RESET                             0x66
#define FLASH9_CMD_RESET_DEVICE                             0x99
#define FLASH9_CMD_SOFTWARE_DIE_SELECT                      0xC2

/**
 * @brief Flash 9 Linear Address Instruction.
 * @details Linear Address Instruction of Flash 9 Click driver.
 */
#define FLASH9_CMD_READ_DATA                                0x03
#define FLASH9_CMD_READ_DATA_WITH_4BYTE_ADDRESS             0x13
#define FLASH9_CMD_FAST_READ                                0x0B
#define FLASH9_CMD_FAST_READ_WITH_4BYTE_ADDRESS             0x0C
#define FLASH9_CMD_PAGE_PROGRAM                             0x02
#define FLASH9_CMD_PAGE_PROGRAM_WITH_4BYTE_ADDRESS          0x12
#define FLASH9_CMD_SECTOR_ERASE                             0x20
#define FLASH9_CMD_SECTOR_ERASE_WITH_4BYTE_ADDRESS          0x21
#define FLASH9_CMD_BLOCK_ERASE_32KB                         0x52
#define FLASH9_CMD_BLOCK_ERASE_64KB                         0xD8
#define FLASH9_CMD_BLOCK_ERASE_64KB_WITH_4BYTE_ADDRESS      0xDC
#define FLASH9_CMD_ERASE_SECURITY_REGISTER                  0x44
#define FLASH9_CMD_PROGRAM_SECURITY_REGISTER                0x42
#define FLASH9_CMD_READ_SECURITY_REGISTER                   0x48
#define FLASH9_CMD_READ_BLOCK_LOCK                          0x3D
#define FLASH9_CMD_INDIVIDUAL_BLOCK_LOCK                    0x36
#define FLASH9_CMD_INDIVIDUAL_BLOCK_UNLOCK                  0x39

/*! @} */ // flash9_reg

/**
 * @defgroup flash9_set Flash 9 Registers Settings
 * @brief Settings for registers of Flash 9 Click driver.
 */

/**
 * @addtogroup flash9_set
 * @{
 */

/**
 * @brief Flash 9 JEDEC ID values.
 * @details Specified JEDEC ID values of Flash 9 Click driver.
 */
#define FLASH9_JEDEC_MANUFACTURER_ID                        0xEF
#define FLASH9_JEDEC_MEMORY_TYPE                            0x70
#define FLASH9_JEDEC_CAPACITY                               0x22

/**
 * @brief Flash 9 memory address range.
 * @details Specified memory address range of Flash 9 Click driver.
 */
#define FLASH9_MIN_ADDRESS                                  0x00000000
#define FLASH9_MAX_ADDRESS                                  0x0FFFFFFFul

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b flash9_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define FLASH9_SET_DATA_SAMPLE_EDGE                         SET_SPI_DATA_SAMPLE_EDGE
#define FLASH9_SET_DATA_SAMPLE_MIDDLE                       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // flash9_set

/**
 * @defgroup flash9_map Flash 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Flash 9 Click driver.
 */

/**
 * @addtogroup flash9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Flash 9 Click to the selected MikroBUS.
 */
#define FLASH9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.hld = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // flash9_map
/*! @} */ // flash9

/**
 * @brief Flash 9 Click context object.
 * @details Context object definition of Flash 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  wp;          /**< Write Protect pin. */
    digital_out_t  rst;         /**< Reset pin. */
    digital_out_t  hld;         /**< Hold pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} flash9_t;

/**
 * @brief Flash 9 Click configuration object.
 * @details Configuration object definition of Flash 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  wp;                                     /**< Write Protect pin. */
    pin_name_t  rst;                                    /**< Reset pin. */
    pin_name_t  hld;                                    /**< Hold pin. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} flash9_cfg_t;

/**
 * @brief Flash 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FLASH9_OK = 0,
    FLASH9_ERROR = -1

} flash9_return_value_t;

/*!
 * @addtogroup flash9 Flash 9 Click Driver
 * @brief API for configuring and manipulating Flash 9 Click driver.
 * @{
 */

/**
 * @brief Flash 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #flash9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void flash9_cfg_setup ( flash9_cfg_t *cfg );

/**
 * @brief Flash 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #flash9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_init ( flash9_t *ctx, flash9_cfg_t *cfg );

/**
 * @brief Flash 9 default configuration function.
 * @details This function executes a default configuration of Flash 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t flash9_default_cfg ( flash9_t *ctx );

/**
 * @brief Flash 9 generic write function.
 * @details This function writes a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] in_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_generic_write ( flash9_t *ctx, uint8_t *data_in, uint16_t in_len );

/**
 * @brief Flash 9 generic read function.
 * @details This function writes and then reads a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] in_len : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[in] out_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_generic_read ( flash9_t *ctx, uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint16_t out_len ) ;

/**
 * @brief Flash 9 write register function.
 * @details This function writes a desired number of data bytes to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @param[in] in_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_write_register ( flash9_t *ctx, uint8_t reg, uint8_t *data_in, uint16_t in_len );

/**
 * @brief Flash 9 read register function.
 * @details This function reads a desired number of data bytes from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @param[in] out_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_read_register ( flash9_t *ctx, uint8_t reg, uint8_t *data_out, uint16_t out_len );

/**
 * @brief Flash 9 write command function.
 * @details This function writes a desired command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_write_command ( flash9_t *ctx, uint8_t cmd );

/**
 * @brief Flash 9 set wp pin function.
 * @details This function sets the WP pin logic state.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void flash9_set_wp_pin ( flash9_t *ctx, uint8_t state );

/**
 * @brief Flash 9 set hld pin function.
 * @details This function sets the HLD pin logic state.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void flash9_set_hld_pin ( flash9_t *ctx, uint8_t state );

/**
 * @brief Flash 9 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void flash9_set_rst_pin ( flash9_t *ctx, uint8_t state );

/**
 * @brief Flash 9 check communication function.
 * @details This function checks the communication by reading and verifying the JEDEC ID.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_check_communication ( flash9_t *ctx );

/**
 * @brief Flash 9 erase memory function.
 * @details This function erases the selected amount of memory which contains the selected address.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] erase_cmd : Erase command (32-bit or 24-bit).
 * @param[in] address : The sector or block of memory that contains this address will be erased.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_erase_memory ( flash9_t *ctx, uint8_t erase_cmd, uint32_t address );

/**
 * @brief Flash 9 read status function.
 * @details This function reads the selected status.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] status_cmd : Status command.
 * @param[out] status : Status byte read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_read_status ( flash9_t *ctx, uint8_t status_cmd, uint8_t *status );

/**
 * @brief Flash 9 write status function.
 * @details This function writes the selected status.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] status_cmd : Status command.
 * @param[in] status : Status byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_write_status ( flash9_t *ctx, uint8_t status_cmd, uint8_t status );

/**
 * @brief Flash 9 memory write function.
 * @details This function writes a desired number of data bytes to the memory starting from
 * the selected address.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] address : Starting address (32-bit).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes (up to 256).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_memory_write ( flash9_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len );

/**
 * @brief Flash 9 memory read function.
 * @details This function reads a desired number of data bytes from the memory starting from
 * the selected address.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] address : Starting address (32-bit).
 * @param[in] data_out : Output data read.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_memory_read ( flash9_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len );

/**
 * @brief Flash 9 memory read fast function.
 * @details This function reads a desired number of data bytes from the memory starting from
 * the selected address performing the fast read command.
 * @param[in] ctx : Click context object.
 * See #flash9_t object definition for detailed explanation.
 * @param[in] address : Starting address (32-bit).
 * @param[in] data_out : Output data read.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t flash9_memory_read_fast ( flash9_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len );

#ifdef __cplusplus
}
#endif
#endif // FLASH9_H

/*! @} */ // flash9

// ------------------------------------------------------------------------ END
