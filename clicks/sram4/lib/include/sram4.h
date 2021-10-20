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
 * @file sram4.h
 * @brief This file contains API for SRAM 4 Click Driver.
 */

#ifndef SRAM4_H
#define SRAM4_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup sram4 SRAM 4 Click Driver
 * @brief API for configuring and manipulating SRAM 4 Click driver.
 * @{
 */

/**
 * @defgroup sram4_reg SRAM 4 Registers List
 * @brief List of registers of SRAM 4 Click driver.
 */

/**
 * @addtogroup sram4_reg
 * @{
 */

/**
 * @brief SRAM 4 description register.
 * @details Specified register for description of SRAM 4 Click driver.
 */
#define SRAM4_REG_RDSR          0x05/*< Read status register*/
#define SRAM4_REG_FAST_RDSR     0x09/*< Fast Read status register*/
#define SRAM4_REG_WRSR          0x01/*< Write status register*/
#define SRAM4_REG_WREN          0x06/*< Set write enable latch*/
#define SRAM4_REG_WRDI          0x04/*< Reset write enable latch*/
#define SRAM4_REG_READ          0x03/*< Read data from memory array*/
#define SRAM4_REG_FAST_READ     0x0B/*< Fast read data*/
#define SRAM4_REG_WRITE         0x02/*< Write data to memory array*/
#define SRAM4_REG_STORE         0x3C/*< Software STORE*/
#define SRAM4_REG_RECALL        0x60/*< Software RECALL*/
#define SRAM4_REG_ASENB         0x59/*< AutoStore Enable*/
#define SRAM4_REG_ASDISB        0x19/*< AutoStore Disable*/
#define SRAM4_REG_SLEEP         0xB9/*< Sleep mode enable*/
#define SRAM4_REG_WRSN          0xC2/*< Write serial number*/
#define SRAM4_REG_RDSN          0xC3/*< Read serial number*/
#define SRAM4_REG_FAST_RDSN     0xC9/*< Fast serial number read*/
#define SRAM4_REG_RDID          0x9F/*< Read ID's*/
#define SRAM4_REG_FAST_RDID     0x9E/*< Fast read ID's*/

/*! @} */ // sram4_reg

/**
 * @defgroup sram4_set SRAM 4 Registers Settings
 * @brief Settings for registers of SRAM 4 Click driver.
 */

/**
 * @addtogroup sram4_set
 * @{
 */

/**
 * @brief SRAM 4 ID value.
 * @details Specified ID value of SRAM 4 Click driver.
 */
#define SRAM4_DEVICE_ID 0x06818818

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b sram4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SRAM4_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define SRAM4_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // sram4_set

/**
 * @defgroup sram4_map SRAM 4 MikroBUS Map
 * @brief MikroBUS pin mapping of SRAM 4 Click driver.
 */

/**
 * @addtogroup sram4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SRAM 4 Click to the selected MikroBUS.
 */
#define SRAM4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.hold = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // sram4_map
/*! @} */ // sram4

/**
 * @brief SRAM 4 Click context object.
 * @details Context object definition of SRAM 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  hold;        /**< Hold. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    uint32_t device_id;         /**< CY14B512Q2A ID. */

} sram4_t;

/**
 * @brief SRAM 4 Click configuration object.
 * @details Configuration object definition of SRAM 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  hold;   /**< Hold. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} sram4_cfg_t;

/**
 * @brief SRAM 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   SRAM4_OK = 0,
   SRAM4_ERROR = -1

} sram4_return_value_t;

/*!
 * @addtogroup sram4 SRAM 4 Click Driver
 * @brief API for configuring and manipulating SRAM 4 Click driver.
 * @{
 */

/**
 * @brief SRAM 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #sram4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void sram4_cfg_setup ( sram4_cfg_t *cfg );

/**
 * @brief SRAM 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #sram4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #sram4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t sram4_init ( sram4_t *ctx, sram4_cfg_t *cfg );

/**
 * @brief SRAM 4 default configuration function.
 * @details This function executes a default configuration of SRAM 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #sram4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t sram4_default_cfg ( sram4_t *ctx );

/**
 * @brief SRAM 4 command writing function.
 * @details This function writes a data byte by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #sram4_t object definition for detailed explanation.
 * @param[in] cmd : Command to send.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t sram4_generic_command ( sram4_t *ctx, uint8_t cmd );

/**
 * @brief SRAM 4 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #sram4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t sram4_generic_write ( sram4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief SRAM 4 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #sram4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t sram4_generic_read ( sram4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief SRAM 4 data writing and reading function.
 * @details This function writes a desired number of data bytes, and then
 * reads a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #sram4_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] in_len : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[in] out_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t sram4_generic_write_then_read ( sram4_t *ctx, uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len );

/**
 * @brief Write data to memory.
 * @details This function writes a data starting from selected memory address.
 * @param[in] ctx : Click context object.
 * See #sram4_t object definition for detailed explanation.
 * @param[in] memory_adr : Memory address to start writeing data to.
 * @param[in] write_data : Data to write.
 * @param[in] write_len : Number of bytes to write starting from selected memory address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t sram4_memory_write ( sram4_t *ctx, uint16_t memory_adr, uint8_t *write_data, uint8_t write_len );

/**
 * @brief Read data from memory.
 * @details This function reads a data starting from selected memory address.
 * @param[in] ctx : Click context object.
 * See #sram4_t object definition for detailed explanation.
 * @param[in] memory_adr : Memory address to start reading data from.
 * @param[out] read_data : Read data.
 * @param[in] read_len : Number of bytes to read starting from selected memory address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t sram4_memory_read ( sram4_t *ctx, uint16_t memory_adr, uint8_t *read_data, uint8_t read_len );

/**
 * @brief Set HOLD pin state.
 * @details This function sets hold pin to selected state.
 * @param[in] ctx : Click context object.
 * See #sram4_t object definition for detailed explanation.
 * @param[in] state : Pin state to set.
 * @return Nothing
 */
void sram4_set_hold ( sram4_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // SRAM4_H

/*! @} */ // sram4

// ------------------------------------------------------------------------ END
