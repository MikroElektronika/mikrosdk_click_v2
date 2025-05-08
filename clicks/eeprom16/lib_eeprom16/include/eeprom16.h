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
 * @file eeprom16.h
 * @brief This file contains API for EEPROM 16 Click Driver.
 */

#ifndef EEPROM16_H
#define EEPROM16_H

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
 * @addtogroup eeprom16 EEPROM 16 Click Driver
 * @brief API for configuring and manipulating EEPROM 16 Click driver.
 * @{
 */

/**
 * @defgroup eeprom16_reg EEPROM 16 Registers List
 * @brief List of registers of EEPROM 16 Click driver.
 */

/**
 * @addtogroup eeprom16_reg
 * @{
 */

/**
 * @brief EEPROM 16 Opcode Commands list.
 * @details Specified Opcode Commands of EEPROM 16 Click driver.
 */
#define EEPROM16_OPCODE_WREN                            0x06
#define EEPROM16_OPCODE_WRDI                            0x04
#define EEPROM16_OPCODE_RDSR                            0x05
#define EEPROM16_OPCODE_WRSR                            0x01
#define EEPROM16_OPCODE_READ                            0x03
#define EEPROM16_OPCODE_WRITE                           0x02

/*! @} */ // eeprom16_reg

/**
 * @defgroup eeprom16_set EEPROM 16 Registers Settings
 * @brief Settings for registers of EEPROM 16 Click driver.
 */

/**
 * @addtogroup eeprom16_set
 * @{
 */

/**
 * @brief EEPROM 16 status register bits mask.
 * @details Specified bits mask for status register of EEPROM 16 Click driver.
 */
#define EEPROM16_STATUS_WPEN_MASK                       0x80
#define EEPROM16_STATUS_IPL_MASK                        0x40
#define EEPROM16_STATUS_BLOCK_PROTECT_NONE              0x00
#define EEPROM16_STATUS_BLOCK_PROTECT_UPPER_QUARTER     0x04
#define EEPROM16_STATUS_BLOCK_PROTECT_UPPER_HALF        0x08
#define EEPROM16_STATUS_BLOCK_PROTECT_ALL               0x0C
#define EEPROM16_STATUS_BLOCK_PROTECT_MASK              0x0C
#define EEPROM16_STATUS_WEL_MASK                        0x02
#define EEPROM16_STATUS_RDY_MASK                        0x01

/**
 * @brief EEPROM 16 memory address range.
 * @details Specified memory address range of EEPROM 16 Click driver.
 */
#define EEPROM16_MIN_ADDRESS                            0x0000
#define EEPROM16_MAX_ADDRESS                            0x0FFF
#define EEPROM16_PAGE_SIZE                              32
#define EEPROM16_PAGE_MASK                              0x1F

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b eeprom16_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define EEPROM16_SET_DATA_SAMPLE_EDGE                   SET_SPI_DATA_SAMPLE_EDGE
#define EEPROM16_SET_DATA_SAMPLE_MIDDLE                 SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // eeprom16_set

/**
 * @defgroup eeprom16_map EEPROM 16 MikroBUS Map
 * @brief MikroBUS pin mapping of EEPROM 16 Click driver.
 */

/**
 * @addtogroup eeprom16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EEPROM 16 Click to the selected MikroBUS.
 */
#define EEPROM16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wp   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.hold = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // eeprom16_map
/*! @} */ // eeprom16

/**
 * @brief EEPROM 16 Click context object.
 * @details Context object definition of EEPROM 16 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wp;           /**< Write Protect pin (active low). */
    digital_out_t hold;         /**< HOLD pin (active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} eeprom16_t;

/**
 * @brief EEPROM 16 Click configuration object.
 * @details Configuration object definition of EEPROM 16 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t wp;              /**< Write Protect pin (active low). */
    pin_name_t hold;            /**< HOLD pin (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} eeprom16_cfg_t;

/**
 * @brief EEPROM 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EEPROM16_OK = 0,
    EEPROM16_ERROR = -1

} eeprom16_return_value_t;

/*!
 * @addtogroup eeprom16 EEPROM 16 Click Driver
 * @brief API for configuring and manipulating EEPROM 16 Click driver.
 * @{
 */

/**
 * @brief EEPROM 16 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeprom16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eeprom16_cfg_setup ( eeprom16_cfg_t *cfg );

/**
 * @brief EEPROM 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeprom16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom16_init ( eeprom16_t *ctx, eeprom16_cfg_t *cfg );

/**
 * @brief EEPROM 16 default configuration function.
 * @details This function executes a default configuration of EEPROM 16
 * Click board.
 * @param[in] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t eeprom16_default_cfg ( eeprom16_t *ctx );

/**
 * @brief EEPROM 16 write opcode function.
 * @details This function writes a desired opcode command byte by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @param[in] opcode : Opcode command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom16_write_opcode ( eeprom16_t *ctx, uint8_t opcode );

/**
 * @brief EEPROM 16 read opcode function.
 * @details This function reads a desired number of data bytes from
 * the selected opcode by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @param[in] opcode : Opcode command.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom16_read_opcode ( eeprom16_t *ctx, uint8_t opcode, uint8_t *data_out, uint8_t len );

/**
 * @brief EEPROM 16 set WP pin function.
 * @details This function sets the Write Protect (WP) pin logic state.
 * @param[in] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void eeprom16_set_wp_pin ( eeprom16_t *ctx, uint8_t state );

/**
 * @brief EEPROM 16 set HOLD pin function.
 * @details This function sets the HOLD pin logic state.
 * @param[in] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void eeprom16_set_hold_pin ( eeprom16_t *ctx, uint8_t state );

/**
 * @brief EEPROM 16 enable write function.
 * @details This function enables write by issuing the WREN command and checking the WEL bit.
 * @param[in] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom16_enable_write ( eeprom16_t *ctx );

/**
 * @brief EEPROM 16 disable write function.
 * @details This function disables write by issuing the WRDI command and checking the WEL bit.
 * @param[in] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom16_disable_write ( eeprom16_t *ctx );

/**
 * @brief EEPROM 16 set block protection function.
 * @details This function sets the block protection bits of the Status register.
 * @param[in] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @param[in] block_protect : @li @c 0x00 - None,
 *                            @li @c 0x04 - Upper quarter,
 *                            @li @c 0x08 - Upper half,
 *                            @li @c 0x0C - All.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom16_set_block_protection ( eeprom16_t *ctx, uint8_t block_protect );

/**
 * @brief EEPROM 16 write status function.
 * @details This function writes a desired data to the Status register.
 * @param[in] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @param[in] status : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom16_write_status ( eeprom16_t *ctx, uint8_t status );

/**
 * @brief EEPROM 16 read status function.
 * @details This function reads the Status register.
 * @param[in] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @param[out] status : Read data output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom16_read_status ( eeprom16_t *ctx, uint8_t *status );

/**
 * @brief EEPROM 16 memory write function.
 * @details This function writes a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x0000-0x0FFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes (up to 32 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom16_memory_write ( eeprom16_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len );

/**
 * @brief EEPROM 16 memory read function.
 * @details This function reads a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #eeprom16_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x0000-0x0FFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eeprom16_memory_read ( eeprom16_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );

#ifdef __cplusplus
}
#endif
#endif // EEPROM16_H

/*! @} */ // eeprom16

// ------------------------------------------------------------------------ END
