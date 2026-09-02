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
 * @file eeprom18.h
 * @brief This file contains API for EEPROM 18 Click Driver.
 */

#ifndef EEPROM18_H
#define EEPROM18_H

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
 * @addtogroup eeprom18 EEPROM 18 Click Driver
 * @brief API for configuring and manipulating EEPROM 18 Click driver.
 * @{
 */

/**
 * @defgroup eeprom18_cmd EEPROM 18 Commands List
 * @brief List of commands of EEPROM 18 Click driver.
 */

/**
 * @addtogroup eeprom18_cmd
 * @{
 */

/**
 * @brief EEPROM 18 Commands list.
 * @details Specified Commands of EEPROM 18 Click driver.
 */
#define EEPROM18_CMD_WREN                   0x06
#define EEPROM18_CMD_WRDI                   0x04
#define EEPROM18_CMD_RDSR                   0x05
#define EEPROM18_CMD_WRSR                   0x01
#define EEPROM18_CMD_READ                   0x03
#define EEPROM18_CMD_WRITE                  0x02
#define EEPROM18_CMD_RDID                   0x83
#define EEPROM18_CMD_WRID                   0x82
#define EEPROM18_CMD_RDLS                   0x83
#define EEPROM18_CMD_LID                    0x82

/*! @} */ // eeprom18_cmd

/**
 * @defgroup eeprom18_set EEPROM 18 Registers Settings
 * @brief Settings for registers of EEPROM 18 Click driver.
 */

/**
 * @addtogroup eeprom18_set
 * @{
 */

/**
 * @brief EEPROM 18 status register setting.
 * @details Specified setting for status register of EEPROM 18 Click driver.
 */
#define EEPROM18_STATUS_WIP                 0x01
#define EEPROM18_STATUS_WEL                 0x02
#define EEPROM18_STATUS_BP0                 0x04
#define EEPROM18_STATUS_BP1                 0x08
#define EEPROM18_STATUS_SRWD                0x80

/**
 * @brief EEPROM 18 block protection setting.
 * @details Specified setting for block protection of EEPROM 18 Click driver.
 */
#define EEPROM18_BP_NONE                    0x00
#define EEPROM18_BP_UPPER_QUARTER           0x04
#define EEPROM18_BP_UPPER_HALF              0x08
#define EEPROM18_BP_ALL                     0x0C

/**
 * @brief EEPROM 18 identification page setting.
 * @details Specified setting for identification page of EEPROM 18 Click driver.
 */
#define EEPROM18_ID_PAGE_A10_BIT            0x04
#define EEPROM18_ID_PAGE_LOCK_BYTE          0x02

/**
 * @brief EEPROM 18 memory size setting.
 * @details Specified setting for memory size of EEPROM 18 Click driver.
 */
#define EEPROM18_PAGE_SIZE                  256
#define EEPROM18_MEMORY_SIZE                131072

/**
 * @brief EEPROM 18 memory offset setting.
 * @details Specified setting for memory offset of EEPROM 18 Click driver.
 */
#define EEPROM18_PAGE_OFFSET_MASK           0xFF

/**
 * @brief EEPROM 18 timeout in milliseconds setting.
 * @details Specified setting for timeout in milliseconds of EEPROM 18 Click driver.
 */
#define EEPROM18_WRITE_TIMEOUT_MS           10

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b eeprom18_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define EEPROM18_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define EEPROM18_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // eeprom18_set

/**
 * @defgroup eeprom18_map EEPROM 18 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 18 Click driver.
 */

/**
 * @addtogroup eeprom18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 18 Click to the selected MikroBUS.
 */
#define EEPROM18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wp   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.hld  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // eeprom18_map
/*! @} */ // eeprom18

/**
 * @brief EEPROM 18 Click context object.
 * @details Context object definition of EEPROM 18 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wp;                               /**< Write protect pin (active low). */
    digital_out_t hld;                              /**< Hold pin (active low). */

    // Modules
    spi_master_t spi;                               /**< SPI driver object. */

    pin_name_t   chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */

} eeprom18_t;

/**
 * @brief EEPROM 18 Click configuration object.
 * @details Configuration object definition of EEPROM 18 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t wp;                                  /**< Write protect pin descriptor. */
    pin_name_t hld;                                 /**< Hold pin descriptor. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} eeprom18_cfg_t;

/**
 * @brief EEPROM 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EEPROM18_OK = 0,
    EEPROM18_ERROR = -1

} eeprom18_return_value_t;

/*!
 * @addtogroup eeprom18 EEPROM 18 Click Driver
 * @brief API for configuring and manipulating EEPROM 18 Click driver.
 * @{
 */

/**
 * @brief EEPROM 18 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom18_cfg_setup ( eeprom18_cfg_t *cfg );

/**
 * @brief EEPROM 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom18_init ( eeprom18_t *ctx, eeprom18_cfg_t *cfg );

/**
 * @brief EEPROM 18 write memory function.
 * @details This function writes a desired number of data bytes to the EEPROM memory
 * starting from the selected address.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @param[in] address : Start address in memory [0x00000-0x1FFFF].
 * @param[in] data_in : Pointer to the data to be written.
 * @param[in] len : Number of bytes to write (up to one page, 256 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The write should not cross a page boundary.
 */
err_t eeprom18_write_memory ( eeprom18_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len );

/**
 * @brief EEPROM 18 read memory function.
 * @details This function reads a desired number of data bytes from the EEPROM memory
 * starting from the selected address.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @param[in] address : Start address in memory [0x00000-0x1FFFF].
 * @param[out] data_out : Pointer to the buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom18_read_memory ( eeprom18_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );

/**
 * @brief EEPROM 18 write enable function.
 * @details This function sets the WEL latch bit by sending the write
 * enable command.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note A write enable must precede every memory, status, or identification
 * page write.
 */
err_t eeprom18_write_enable ( eeprom18_t *ctx );

/**
 * @brief EEPROM 18 write disable function.
 * @details This function resets the WEL latch bit by sending the write
 * disable command.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom18_write_disable ( eeprom18_t *ctx );

/**
 * @brief EEPROM 18 read status function.
 * @details This function reads the status register byte.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @param[out] status : Status register byte read from the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom18_read_status ( eeprom18_t *ctx, uint8_t *status );

/**
 * @brief EEPROM 18 write status function.
 * @details This function writes a byte to the status register.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @param[in] status : Status register byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom18_write_status ( eeprom18_t *ctx, uint8_t status );

/**
 * @brief EEPROM 18 write id page function.
 * @details This function writes a desired number of data bytes to the identification
 * page starting from the selected byte offset within the page.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @param[in] offset : Byte offset within the identification page [0x00-0xFF].
 * @param[in] data_in : Pointer to the data to be written.
 * @param[in] len : Number of bytes to write (up to one page, 256 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The identification page cannot be written once it has been
 * permanently locked with @b eeprom18_lock_id_page.
 */
err_t eeprom18_write_id_page ( eeprom18_t *ctx, uint8_t offset, uint8_t *data_in, uint16_t len );

/**
 * @brief EEPROM 18 read id page function.
 * @details This function reads a desired number of data bytes from the identification
 * page starting from the selected byte offset within the page.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @param[in] offset : Byte offset within the identification page [0x00-0xFF].
 * @param[out] data_out : Pointer to the buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom18_read_id_page ( eeprom18_t *ctx, uint8_t offset, uint8_t *data_out, uint16_t len );

/**
 * @brief EEPROM 18 lock id page function.
 * @details This function permanently locks the identification page against further writes
 * by sending the LID instruction.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This operation is permanent and irreversible. Once the identification
 * page is locked, it can never be written to again.
 */
err_t eeprom18_lock_id_page ( eeprom18_t *ctx );

/**
 * @brief EEPROM 18 read lock status function.
 * @details This function reads the lock status byte of the identification page.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @param[out] lock_status : Lock status byte read from the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom18_read_lock_status ( eeprom18_t *ctx, uint8_t *lock_status );

/**
 * @brief EEPROM 18 set WP pin function.
 * @details This function sets the logic state of the write protect pin.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @param[in] state : WP pin logic state.
 * @return Nothing.
 * @note None.
 */
void eeprom18_set_wp_pin ( eeprom18_t *ctx, uint8_t state );

/**
 * @brief EEPROM 18 set HLD function.
 * @details This function sets the logic state of the hold pin.
 * @param[in] ctx : Click context object.
 * See #eeprom18_t object definition for detailed explanation.
 * @param[in] state : HLD pin logic state.
 * @return Nothing.
 * @note None.
 */
void eeprom18_set_hold_pin ( eeprom18_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // EEPROM18_H

/*! @} */ // eeprom18

// ------------------------------------------------------------------------ END
