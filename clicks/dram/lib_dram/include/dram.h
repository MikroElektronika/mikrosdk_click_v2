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
 * @file dram.h
 * @brief This file contains API for DRAM Click Driver.
 */

#ifndef DRAM_H
#define DRAM_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup dram DRAM Click Driver
 * @brief API for configuring and manipulating DRAM Click driver.
 * @{
 */

/**
 * @defgroup dram_reg DRAM Registers List
 * @brief List of registers of DRAM Click driver.
 */

/**
 * @addtogroup dram_reg
 * @{
 */

/**
 * @brief DRAM commands list.
 * @details Specified commands list of DRAM Click driver.
 */
#define DRAM_CMD_READ                   0x03
#define DRAM_CMD_FAST_READ              0x0B
#define DRAM_CMD_WRITE                  0x02
#define DRAM_CMD_RESET_ENABLE           0x66
#define DRAM_CMD_RESET                  0x99
#define DRAM_CMD_WRAP_BOUNDARY_TOGGLE   0xC0
#define DRAM_CMD_READ_ID                0x9F

/*! @} */ // dram_reg

/**
 * @defgroup dram_set DRAM Registers Settings
 * @brief Settings for registers of DRAM Click driver.
 */

/**
 * @addtogroup dram_set
 * @{
 */

/**
 * @brief DRAM memory address range.
 * @details Specified memory address range of DRAM Click driver.
 */
#define DRAM_MIN_ADDRESS                0x000000
#define DRAM_MAX_ADDRESS                0x7FFFFFul

/**
 * @brief DRAM manufacturer ID.
 * @details Specified manufacturer ID of DRAM Click driver.
 */
#define DRAM_MANUFACTURER_ID            0x0D

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dram_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DRAM_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define DRAM_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dram_set

/**
 * @defgroup dram_map DRAM MikroBUS Map
 * @brief MikroBUS pin mapping of DRAM Click driver.
 */

/**
 * @addtogroup dram_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DRAM Click to the selected MikroBUS.
 */
#define DRAM_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.io3 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.io2 = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // dram_map
/*! @} */ // dram

/**
 * @brief DRAM Click context object.
 * @details Context object definition of DRAM Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t io3;          /**< IO3 pin, used for QUAD SPI which is not supported. */
    digital_out_t io2;          /**< IO2 pin, used for QUAD SPI which is not supported. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} dram_t;

/**
 * @brief DRAM Click configuration object.
 * @details Configuration object definition of DRAM Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t io3;             /**< IO3 pin, used for QUAD SPI which is not supported. */
    pin_name_t io2;             /**< IO2 pin, used for QUAD SPI which is not supported. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} dram_cfg_t;

/**
 * @brief DRAM Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DRAM_OK = 0,
    DRAM_ERROR = -1

} dram_return_value_t;

/*!
 * @addtogroup dram DRAM Click Driver
 * @brief API for configuring and manipulating DRAM Click driver.
 * @{
 */

/**
 * @brief DRAM configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dram_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dram_cfg_setup ( dram_cfg_t *cfg );

/**
 * @brief DRAM initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dram_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dram_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dram_init ( dram_t *ctx, dram_cfg_t *cfg );

/**
 * @brief DRAM memory write function.
 * @details This function writes a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #dram_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x7FFFFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dram_memory_write ( dram_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len );

/**
 * @brief DRAM memory read function.
 * @details This function reads a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #dram_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x7FFFFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dram_memory_read ( dram_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );

/**
 * @brief DRAM memory read fast function.
 * @details This function reads a desired number of data bytes starting from the
 * selected memory address performing fast read feature.
 * @param[in] ctx : Click context object.
 * See #dram_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x7FFFFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dram_memory_read_fast ( dram_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );

/**
 * @brief DRAM reset function.
 * @details This function resets the device by putting the device in SPI standby mode which is
 * also the default mode after power-up.
 * @param[in] ctx : Click context object.
 * See #dram_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dram_reset ( dram_t *ctx );

/**
 * @brief DRAM toggle wrap boundary function.
 * @details This function switches the device’s wrapped boundary between Linear Burst which
 * crosses the 1K page boundary (CA[9:0]) and Wrap 32 (CA[4:0]) bytes. Default setting is Linear Burst.
 * @param[in] ctx : Click context object.
 * See #dram_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dram_toggle_wrap_boundary ( dram_t *ctx );

/**
 * @brief DRAM read id function.
 * @details This function reads the device ID (8 bytes).
 * @param[in] ctx : Click context object.
 * See #dram_t object definition for detailed explanation.
 * @param[out] device_id : Device ID (8 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dram_read_id ( dram_t *ctx, uint8_t *device_id );

/**
 * @brief DRAM check communication function.
 * @details This function checks the communication by reading the device ID bytes and
 * verifying the manufacturer ID.
 * @param[in] ctx : Click context object.
 * See #dram_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dram_check_communication ( dram_t *ctx );

/**
 * @brief DRAM set io3 pin function.
 * @details This function sets the IO3 pin logic state.
 * @param[in] ctx : Click context object.
 * See #dram_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note Used for QUAD SPI which is not supported by the driver.
 */
void dram_set_io3_pin ( dram_t *ctx, uint8_t state );

/**
 * @brief DRAM set io2 pin function.
 * @details This function sets the IO2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #dram_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note Used for QUAD SPI which is not supported by the driver.
 */
void dram_set_io2_pin ( dram_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // DRAM_H

/*! @} */ // dram

// ------------------------------------------------------------------------ END
