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
 * @file fram6.h
 * @brief This file contains API for FRAM 6 Click Driver.
 */

#ifndef FRAM6_H
#define FRAM6_H

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
 * @addtogroup fram6 FRAM 6 Click Driver
 * @brief API for configuring and manipulating FRAM 6 Click driver.
 * @{
 */

/**
 * @defgroup fram6_reg FRAM 6 Opcode Commands List
 * @brief List of Opcode Commands of FRAM 6 Click driver.
 */

/**
 * @addtogroup fram6_reg
 * @{
 */

/**
 * @brief FRAM 6 Opcode Commands list.
 * @details Specified Opcode Commands of FRAM 6 Click driver.
 */
#define FRAM6_OPCODE_WREN                   0x06
#define FRAM6_OPCODE_WRDI                   0x04
#define FRAM6_OPCODE_RDSR                   0x05
#define FRAM6_OPCODE_WRSR                   0x01
#define FRAM6_OPCODE_READ                   0x03
#define FRAM6_OPCODE_FSTRD                  0x0B
#define FRAM6_OPCODE_WRITE                  0x02
#define FRAM6_OPCODE_SLEEP                  0xB9
#define FRAM6_OPCODE_RDID                   0x9F

/*! @} */ // fram6_reg

/**
 * @defgroup fram6_set FRAM 6 Registers Settings
 * @brief Settings for registers of FRAM 6 Click driver.
 */

/**
 * @addtogroup fram6_set
 * @{
 */

/**
 * @brief FRAM 6 status register bits mask.
 * @details Specified bits mask for status register of FRAM 6 Click driver.
 */
#define FRAM6_WEL_BIT_MASK                  0x02
#define FRAM6_BLOCK_PROTECT_BITS_MASK       0x0C
#define FRAM6_BLOCK_PROTECT_NONE            0x00
#define FRAM6_BLOCK_PROTECT_UPPER_QUARTER   0x04
#define FRAM6_BLOCK_PROTECT_UPPER_HALF      0x08
#define FRAM6_BLOCK_PROTECT_ALL             0x0C
#define FRAM6_WPEN_BIT_MASK                 0x80

/**
 * @brief FRAM 6 memory address range.
 * @details Specified memory address range of FRAM 6 Click driver.
 */
#define FRAM6_MIN_ADDRESS                   0x00000
#define FRAM6_MAX_ADDRESS                   0x3FFFF

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b fram6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define FRAM6_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define FRAM6_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // fram6_set

/**
 * @defgroup fram6_map FRAM 6 MikroBUS Map
 * @brief MikroBUS pin mapping of FRAM 6 Click driver.
 */

/**
 * @addtogroup fram6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of FRAM 6 Click to the selected MikroBUS.
 */
#define FRAM6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.hld = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // fram6_map
/*! @} */ // fram6

/**
 * @brief FRAM 6 Click context object.
 * @details Context object definition of FRAM 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  wp;          /**< Write Protect pin. */
    digital_out_t  hld;         /**< HOLD pin. */

    // Modules
    spi_master_t   spi;         /**< SPI driver object. */

    pin_name_t     chip_select; /**< Chip select pin descriptor (used for SPI driver). */

} fram6_t;

/**
 * @brief FRAM 6 Click configuration object.
 * @details Configuration object definition of FRAM 6 Click driver.
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
    pin_name_t  hld;                                    /**< HOLD pin. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} fram6_cfg_t;

/**
 * @brief FRAM 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FRAM6_OK = 0,
    FRAM6_ERROR = -1

} fram6_return_value_t;

/*!
 * @addtogroup fram6 FRAM 6 Click Driver
 * @brief API for configuring and manipulating FRAM 6 Click driver.
 * @{
 */

/**
 * @brief FRAM 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #fram6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void fram6_cfg_setup ( fram6_cfg_t *cfg );

/**
 * @brief FRAM 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #fram6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram6_init ( fram6_t *ctx, fram6_cfg_t *cfg );

/**
 * @brief FRAM 6 default configuration function.
 * @details This function executes a default configuration of FRAM 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t fram6_default_cfg ( fram6_t *ctx );

/**
 * @brief FRAM 6 write opcode function.
 * @details This function writes a desired opcode command byte by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @param[in] opcode : Opcode command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram6_write_opcode ( fram6_t *ctx, uint8_t opcode );

/**
 * @brief FRAM 6 read opcode function.
 * @details This function reads a desired number of data bytes from
 * the selected opcode by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @param[in] opcode : Opcode command.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram6_read_opcode ( fram6_t *ctx, uint8_t opcode, uint8_t *data_out, uint8_t len );

/**
 * @brief FRAM 6 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram6_check_communication ( fram6_t *ctx );

/**
 * @brief FRAM 6 set WP pin function.
 * @details This function sets the Write Protect (WP) pin logic state.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void fram6_set_wp_pin ( fram6_t *ctx, uint8_t state );

/**
 * @brief FRAM 6 set HLD pin function.
 * @details This function sets the HOLD (HLD) pin logic state.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void fram6_set_hld_pin ( fram6_t *ctx, uint8_t state );

/**
 * @brief FRAM 6 enable write function.
 * @details This function enables write by issuing the WREN command and checking the WEL bit.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram6_enable_write ( fram6_t *ctx );

/**
 * @brief FRAM 6 disable write function.
 * @details This function disables write by issuing the WRDI command and checking the WEL bit.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram6_disable_write ( fram6_t *ctx );

/**
 * @brief FRAM 6 set block protection function.
 * @details This function sets the block protection bits of the Status register.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
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
err_t fram6_set_block_protection ( fram6_t *ctx, uint8_t block_protect );

/**
 * @brief FRAM 6 write status function.
 * @details This function writes a desired data to the Status register.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @param[in] status : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram6_write_status ( fram6_t *ctx, uint8_t status );

/**
 * @brief FRAM 6 read status function.
 * @details This function reads the Status register.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @param[out] status : Read data output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram6_read_status ( fram6_t *ctx, uint8_t *status );

/**
 * @brief FRAM 6 enter sleep mode function.
 * @details This function enters to the sleep mode by issuing the SLEEP command.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram6_enter_sleep_mode ( fram6_t *ctx );

/**
 * @brief FRAM 6 wake up from sleep function.
 * @details This function wakes up from sleep mode by toggling the CS pin.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void fram6_wakeup_from_sleep ( fram6_t *ctx );

/**
 * @brief FRAM 6 memory write function.
 * @details This function writes a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x3FFFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram6_memory_write ( fram6_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len );

/**
 * @brief FRAM 6 memory read function.
 * @details This function reads a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x3FFFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram6_memory_read ( fram6_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len );

/**
 * @brief FRAM 6 memory read fast function.
 * @details This function fast reads a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #fram6_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x3FFFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram6_memory_read_fast ( fram6_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len );

#ifdef __cplusplus
}
#endif
#endif // FRAM6_H

/*! @} */ // fram6

// ------------------------------------------------------------------------ END
