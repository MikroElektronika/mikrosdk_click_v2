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
 * @file mram5.h
 * @brief This file contains API for MRAM 5 Click Driver.
 */

#ifndef MRAM5_H
#define MRAM5_H

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
 * @addtogroup mram5 MRAM 5 Click Driver
 * @brief API for configuring and manipulating MRAM 5 Click driver.
 * @{
 */

/**
 * @defgroup mram5_cmd MRAM 5 Commands List
 * @brief List of commands of MRAM 5 Click driver.
 */

/**
 * @addtogroup mram5_cmd
 * @{
 */

/**
 * @brief MRAM 5 command list.
 * @details Specified command list of MRAM 5 Click driver.
 */
#define MRAM5_CMD_WRSR                      0x01
#define MRAM5_CMD_WRITE                     0x02
#define MRAM5_CMD_READ                      0x03
#define MRAM5_CMD_WRDI                      0x04
#define MRAM5_CMD_RDSR                      0x05
#define MRAM5_CMD_WREN                      0x06
#define MRAM5_CMD_SLEEP                     0xB9
#define MRAM5_CMD_WAKE                      0xAB

/*! @} */ // mram5_cmd

/**
 * @defgroup mram5_set MRAM 5 Registers Settings
 * @brief Settings for registers of MRAM 5 Click driver.
 */

/**
 * @addtogroup mram5_set
 * @{
 */

/**
 * @brief MRAM 5 status register bit assignments setting.
 * @details Specified setting for status register bit assignments of MRAM 5 Click driver.
 */
#define MRAM5_STATUS_SRWD_BIT_MASK          0x80
#define MRAM5_STATUS_BP1_BIT_MASK           0x08
#define MRAM5_STATUS_BP0_BIT_MASK           0x04
#define MRAM5_STATUS_WEL_BIT_MASK           0x02

/**
 * @brief MRAM 5 block protection setting.
 * @details Specified setting for block protection of MRAM 5 Click driver.
 */
#define MRAM5_BLOCK_PROTECT_NONE            0x00
#define MRAM5_BLOCK_PROTECT_UPPER_QUARTER   0x04
#define MRAM5_BLOCK_PROTECT_UPPER_HALF      0x08
#define MRAM5_BLOCK_PROTECT_ALL             0x0C
#define MRAM5_BLOCK_PROTECT_BIT_MASK        0x0C

/**
 * @brief MRAM 5 address byte position setting.
 * @details Specified setting for address byte position of MRAM 5 Click driver.
 */
#define MRAM5_ADDRESS_BYTE_HIGH_SHIFT       16
#define MRAM5_ADDRESS_BYTE_MID_SHIFT        8
#define MRAM5_ADDRESS_FRAME_SIZE            4

/**
 * @brief MRAM 5 memory address range setting.
 * @details Specified setting for memory address range of MRAM 5 Click driver.
 */
#define MRAM5_MEMORY_ADDRESS_MIN            0x000000ul
#define MRAM5_MEMORY_ADDRESS_MAX            0x07FFFFul

/**
 * @brief MRAM 5 write protect and hold pin setting.
 * @details Specified setting for write protect and hold pin of MRAM 5 Click driver.
 */
#define MRAM5_WRITE_PROTECT_ENABLE          0
#define MRAM5_WRITE_PROTECT_DISABLE         1
#define MRAM5_HOLD_ENABLE                   0
#define MRAM5_HOLD_DISABLE                  1

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b mram5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MRAM5_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define MRAM5_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // mram5_set

/**
 * @defgroup mram5_map MRAM 5 MikroBUS Map
 * @brief MikroBUS pin mapping of MRAM 5 Click driver.
 */

/**
 * @addtogroup mram5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MRAM 5 Click to the selected MikroBUS.
 */
#define MRAM5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wp   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.hld  = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // mram5_map
/*! @} */ // mram5

/**
 * @brief MRAM 5 Click context object.
 * @details Context object definition of MRAM 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wp;                               /**< Write protect pin (active low). */
    digital_out_t hld;                              /**< Hold pin (active low). */

    // Modules
    spi_master_t spi;                               /**< SPI driver object. */

    pin_name_t   chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */

} mram5_t;

/**
 * @brief MRAM 5 Click configuration object.
 * @details Configuration object definition of MRAM 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  wp;                                 /**< Write protect pin descriptor. */
    pin_name_t hld;                                 /**< Hold pin descriptor. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} mram5_cfg_t;

/**
 * @brief MRAM 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MRAM5_OK = 0,
    MRAM5_ERROR = -1

} mram5_return_value_t;

/*!
 * @addtogroup mram5 MRAM 5 Click Driver
 * @brief API for configuring and manipulating MRAM 5 Click driver.
 * @{
 */

/**
 * @brief MRAM 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mram5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mram5_cfg_setup ( mram5_cfg_t *cfg );

/**
 * @brief MRAM 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mram5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_init ( mram5_t *ctx, mram5_cfg_t *cfg );

/**
 * @brief MRAM 5 default configuration function.
 * @details This function executes a default configuration of MRAM 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t mram5_default_cfg ( mram5_t *ctx );

/**
 * @brief MRAM 5 set command function.
 * @details This function writes a single command byte.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_set_command ( mram5_t *ctx, uint8_t cmd );

/**
 * @brief MRAM 5 generic write function.
 * @details This function writes a desired number of data bytes that follow the
 * selected command byte.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_generic_write ( mram5_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief MRAM 5 generic read function.
 * @details This function reads a desired number of data bytes that follow the
 * selected command byte.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_generic_read ( mram5_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief MRAM 5 write command address data function.
 * @details This function writes a desired number of data bytes starting from a
 * selected address of the selected command.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] mem_addr : Memory address (0x000000-0x07FFFF).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_write_cmd_addr_data ( mram5_t *ctx, uint8_t cmd, uint32_t mem_addr, uint8_t *data_in, uint32_t len );

/**
 * @brief MRAM 5 read command address data function.
 * @details This function reads a desired number of data bytes starting from a
 * selected address of the selected command.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] mem_addr : Memory address (0x000000-0x07FFFF).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_read_cmd_addr_data ( mram5_t *ctx, uint8_t cmd, uint32_t mem_addr, uint8_t *data_out, uint32_t len );

/**
 * @brief MRAM 5 memory write function.
 * @details This function writes a desired number of data bytes starting from
 * the selected memory address.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @param[in] mem_addr : Memory address (0x000000-0x07FFFF).
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_memory_write ( mram5_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint32_t len );

/**
 * @brief MRAM 5 memory read function.
 * @details This function reads a desired number of data bytes starting from
 * the selected memory address.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @param[in] mem_addr : Memory address (0x000000-0x07FFFF).
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_memory_read ( mram5_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint32_t len );

/**
 * @brief MRAM 5 write enable function.
 * @details This function sets the write enable latch bit in the status register.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_write_enable ( mram5_t *ctx );

/**
 * @brief MRAM 5 write disable function.
 * @details This function clears the write enable latch bit in the status register.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_write_disable ( mram5_t *ctx );

/**
 * @brief MRAM 5 get status function.
 * @details This function reads the status register.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @param[out] status : Status register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_get_status ( mram5_t *ctx, uint8_t *status );

/**
 * @brief MRAM 5 set status function.
 * @details This function writes the desired data byte to the status register.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @param[in] status : Status register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_set_status ( mram5_t *ctx, uint8_t status );

/**
 * @brief MRAM 5 enter sleep function.
 * @details This function turns off the internal power regulators of the MR25H40
 * in order to reduce the standby current of the memory chip.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_enter_sleep ( mram5_t *ctx );

/**
 * @brief MRAM 5 wake up function.
 * @details This function turns on the internal power regulators of the MR25H40.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mram5_wake_up ( mram5_t *ctx );

/**
 * @brief MRAM 5 set WP function.
 * @details This function sets the logic state of the WP pin.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @param[in] state : WP pin logic state.
 * @return Nothing.
 * @note None.
 */
void mram5_set_wp ( mram5_t *ctx, uint8_t state );

/**
 * @brief MRAM 5 set HLD function.
 * @details This function sets the logic state of the HLD pin.
 * @param[in] ctx : Click context object.
 * See #mram5_t object definition for detailed explanation.
 * @param[in] state : Hold pin logic state.
 * @return Nothing.
 * @note None.
 */
void mram5_set_hld ( mram5_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // MRAM5_H

/*! @} */ // mram5

// ------------------------------------------------------------------------ END
