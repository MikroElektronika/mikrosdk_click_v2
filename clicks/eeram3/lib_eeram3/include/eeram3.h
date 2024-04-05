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
 * @file eeram3.h
 * @brief This file contains API for EERAM 3 Click Driver.
 */

#ifndef EERAM3_H
#define EERAM3_H

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
 * @addtogroup eeram3 EERAM 3 Click Driver
 * @brief API for configuring and manipulating EERAM 3 Click driver.
 * @{
 */

/**
 * @defgroup eeram3_reg EERAM 3 Opcode Commands List
 * @brief List of Opcode Commands of EERAM 3 Click driver.
 */

/**
 * @addtogroup eeram3_reg
 * @{
 */

/**
 * @brief EERAM 3 Opcode Commands list.
 * @details Specified Opcode Commands of EERAM 3 Click driver.
 */
#define EERAM3_OPCODE_WREN                   0x06
#define EERAM3_OPCODE_WRDI                   0x04
#define EERAM3_OPCODE_WRITE                  0x02
#define EERAM3_OPCODE_READ                   0x03
#define EERAM3_OPCODE_RDLSWA                 0x0A
#define EERAM3_OPCODE_SECURE_WRITE           0x12
#define EERAM3_OPCODE_SECURE_READ            0x13
#define EERAM3_OPCODE_WRSR                   0x01
#define EERAM3_OPCODE_RDSR                   0x05
#define EERAM3_OPCODE_STORE                  0x08
#define EERAM3_OPCODE_RECALL                 0x09
#define EERAM3_OPCODE_WRNUR                  0xC2
#define EERAM3_OPCODE_RDNUR                  0xC3
#define EERAM3_OPCODE_HIBERNATE              0xB9

/*! @} */ // eeram3_reg

/**
 * @defgroup eeram3_set EERAM 3 Registers Settings
 * @brief Settings for registers of EERAM 3 Click driver.
 */

/**
 * @addtogroup eeram3_set
 * @{
 */

/**
 * @brief EERAM 3 status register bits mask.
 * @details Specified bits mask for status register of EERAM 3 Click driver.
 */
#define EERAM3_RDY_BIT_MASK                  0x01
#define EERAM3_WEL_BIT_MASK                  0x02
#define EERAM3_BLOCK_PROTECT_BITS_MASK       0x0C
#define EERAM3_BLOCK_PROTECT_NONE            0x00
#define EERAM3_BLOCK_PROTECT_UPPER_QUARTER   0x04
#define EERAM3_BLOCK_PROTECT_UPPER_HALF      0x08
#define EERAM3_BLOCK_PROTECT_ALL             0x0C
#define EERAM3_SWM_BIT_MASK                  0x10
#define EERAM3_PRO_BIT_MASK                  0x20
#define EERAM3_ASE_BIT_MASK                  0x40

/**
 * @brief EERAM 3 memory address range.
 * @details Specified memory address range of EERAM 3 Click driver.
 */
#define EERAM3_MIN_ADDRESS                   0x0000
#define EERAM3_MAX_ADDRESS                   0x7FFF
#define EERAM3_MAX_PAGE_ADDRESS              0x3F

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b eeram3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define EERAM3_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define EERAM3_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // eeram3_set

/**
 * @defgroup eeram3_map EERAM 3 MikroBUS Map
 * @brief MikroBUS pin mapping of EERAM 3 Click driver.
 */

/**
 * @addtogroup eeram3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EERAM 3 Click to the selected MikroBUS.
 */
#define EERAM3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.hld = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // eeram3_map
/*! @} */ // eeram3

/**
 * @brief EERAM 3 Click context object.
 * @details Context object definition of EERAM 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t   hld;         /**< HOLD pin. */

    // Modules
    spi_master_t    spi;         /**< SPI driver object. */

    pin_name_t      chip_select; /**< Chip select pin descriptor (used for SPI driver). */

} eeram3_t;

/**
 * @brief EERAM 3 Click configuration object.
 * @details Configuration object definition of EERAM 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  hld;                                    /**< HOLD pin. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} eeram3_cfg_t;

/**
 * @brief EERAM 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EERAM3_OK = 0,
    EERAM3_ERROR = -1

} eeram3_return_value_t;

/*!
 * @addtogroup eeram3 EERAM 3 Click Driver
 * @brief API for configuring and manipulating EERAM 3 Click driver.
 * @{
 */

/**
 * @brief EERAM 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeram3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeram3_cfg_setup ( eeram3_cfg_t *cfg );

/**
 * @brief EERAM 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeram3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_init ( eeram3_t *ctx, eeram3_cfg_t *cfg );

/**
 * @brief EERAM 3 default configuration function.
 * @details This function executes a default configuration of EERAM 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void eeram3_default_cfg ( eeram3_t *ctx );

/**
 * @brief EERAM 3 write opcode function.
 * @details This function writes a desired opcode command byte by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[in] opcode : Opcode command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_write_opcode ( eeram3_t *ctx, uint8_t opcode );

/**
 * @brief EERAM 3 read opcode function.
 * @details This function reads a desired number of data bytes from
 * the selected opcode by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[in] opcode : Opcode command.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_read_opcode ( eeram3_t *ctx, uint8_t opcode, uint8_t *data_out, uint8_t len );

/**
 * @brief EERAM 3 set HLD pin function.
 * @details This function sets the HOLD (HLD) pin logic state.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void eeram3_set_hld_pin ( eeram3_t *ctx, uint8_t state );

/**
 * @brief EERAM 3 enable write function.
 * @details This function enables write by issuing the WREN command and checking the WEL bit.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_enable_write ( eeram3_t *ctx );

/**
 * @brief EERAM 3 disable write function.
 * @details This function disables write by issuing the WRDI command and checking the WEL bit.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_disable_write ( eeram3_t *ctx );

/**
 * @brief EERAM 3 set block protection function.
 * @details This function sets the block protection bits of the Status register.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[in] block_protect : @li @c  0x00 - None,
 *                            @li @c  0x04 - Upper quarter,
 *                            @li @c  0x08 - Upper half,
 *                            @li @c  0x0C - All.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_set_block_protection ( eeram3_t *ctx, uint8_t block_protect );

/**
 * @brief EERAM 3 write status function.
 * @details This function writes a desired data to the Status register.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[in] status : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_write_status ( eeram3_t *ctx, uint8_t status );

/**
 * @brief EERAM 3 read status function.
 * @details This function reads the Status register.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[out] status : Read data output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_read_status ( eeram3_t *ctx, uint8_t *status );

/**
 * @brief EERAM 3 enter hibernate mode function.
 * @details This function enters to the hibernate mode by issuing the HIBERNATE command.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_enter_hibernate_mode ( eeram3_t *ctx );

/**
 * @brief EERAM 3 wake up from hibernate function.
 * @details This function wakes up from hibernate mode by toggling the CS pin.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void eeram3_wakeup_from_hibernate ( eeram3_t *ctx );

/**
 * @brief EERAM 3 memory write function.
 * @details This function writes a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x0000-0x7FFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_memory_write ( eeram3_t *ctx, uint16_t address, uint8_t *data_in, uint16_t len );

/**
 * @brief EERAM 3 memory read function.
 * @details This function reads a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x0000-0x7FFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_memory_read ( eeram3_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );

/**
 * @brief EERAM 3 memory write function.
 * @details This function securely writes a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x0000-0x7FFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes [up to 64 bytes].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Address must be aligned to a 64-byte boundary.
 */
err_t eeram3_memory_secure_write ( eeram3_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len );

/**
 * @brief EERAM 3 memory secure read function.
 * @details This function securely reads a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x0000-0x7FFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes [up to 64 bytes].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Address must be aligned to a 64-byte boundary.
 */
err_t eeram3_memory_secure_read ( eeram3_t *ctx, uint16_t address, uint8_t *data_out, uint8_t len );

/**
 * @brief EERAM 3 read last written address function.
 * @details This function reads the last successfully written address.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[out] address : Last written memory address [0x0000-0x7FFF].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_read_last_written_address ( eeram3_t *ctx, uint16_t *address );

/**
 * @brief EERAM 3 nv user space write function.
 * @details This function writes two bytes of data to the
 * nonvolatile user space.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_nv_user_space_write ( eeram3_t *ctx, uint16_t data_in );

/**
 * @brief EERAM 3 nv user space read function.
 * @details This function reads two bytes of data from the
 * nonvolatile user space.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @param[out] data_out : Read data output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_nv_user_space_read ( eeram3_t *ctx, uint16_t *data_out );

/**
 * @brief EERAM 3 store data function.
 * @details This function executes the STORE command which stores SRAM data to EEPROM array.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_store_data ( eeram3_t *ctx );

/**
 * @brief EERAM 3 recall data function.
 * @details This function executes the RECALL command which copies EEPROM data to SRAM array.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_recall_data ( eeram3_t *ctx );

/**
 * @brief EERAM 3 autostore enable function.
 * @details This function enables Auto Store feature.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_autostore_enable ( eeram3_t *ctx );

/**
 * @brief EERAM 3 autostore disable function.
 * @details This function disables Auto Store feature.
 * @param[in] ctx : Click context object.
 * See #eeram3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeram3_autostore_disable ( eeram3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EERAM3_H

/*! @} */ // eeram3

// ------------------------------------------------------------------------ END
