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
 * @file spiisolator6.h
 * @brief This file contains API for SPI Isolator 6 Click Driver.
 */

#ifndef SPIISOLATOR6_H
#define SPIISOLATOR6_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup spiisolator6 SPI Isolator 6 Click Driver
 * @brief API for configuring and manipulating SPI Isolator 6 Click driver.
 * @{
 */

/**
 * @defgroup spiisolator6_set SPI Isolator 6 Registers Settings
 * @brief Settings for registers of SPI Isolator 6 Click driver.
 */

/**
 * @addtogroup spiisolator6_set
 * @{
 */

/**
 * @brief SPI Isolator 6 SPI settings.
 * @details Specified SPI settings of SPI Isolator 6 Click driver.
 */
#define SPIISOLATOR6_SPI_CLOCK_SPEED            100000
#define SPIISOLATOR6_SPI_MODE                   SPI_MASTER_MODE_0
#define SPIISOLATOR6_SPI_CS_POLARITY            SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW
#define SPIISOLATOR6_SPI_DUMMY_BYTE             0x00

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b spiisolator6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SPIISOLATOR6_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define SPIISOLATOR6_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // spiisolator6_set

/**
 * @defgroup spiisolator6_map SPI Isolator 6 MikroBUS Map
 * @brief MikroBUS pin mapping of SPI Isolator 6 Click driver.
 */

/**
 * @addtogroup spiisolator6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SPI Isolator 6 Click to the selected MikroBUS.
 */
#define SPIISOLATOR6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // spiisolator6_map
/*! @} */ // spiisolator6

/**
 * @brief SPI Isolator 6 Click context object.
 * @details Context object definition of SPI Isolator 6 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} spiisolator6_t;

/**
 * @brief SPI Isolator 6 Click configuration object.
 * @details Configuration object definition of SPI Isolator 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} spiisolator6_cfg_t;

/**
 * @brief SPI Isolator 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SPIISOLATOR6_OK = 0,
    SPIISOLATOR6_ERROR = -1

} spiisolator6_return_value_t;

/*!
 * @addtogroup spiisolator6 SPI Isolator 6 Click Driver
 * @brief API for configuring and manipulating SPI Isolator 6 Click driver.
 * @{
 */

/**
 * @brief SPI Isolator 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #spiisolator6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void spiisolator6_cfg_setup ( spiisolator6_cfg_t *cfg );

/**
 * @brief SPI Isolator 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #spiisolator6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #spiisolator6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator6_init ( spiisolator6_t *ctx, spiisolator6_cfg_t *cfg );

/**
 * @brief SPI Isolator 6 data writing function.
 * @details This function writes a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator6_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] in_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator6_generic_write ( spiisolator6_t *ctx, uint8_t *data_in, uint8_t in_len );

/**
 * @brief SPI Isolator 6 data reading function.
 * @details This function writes and then reads a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator6_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] in_len : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[in] out_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator6_generic_read ( spiisolator6_t *ctx, uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len );

#ifdef __cplusplus
}
#endif
#endif // SPIISOLATOR6_H

/*! @} */ // spiisolator6

// ------------------------------------------------------------------------ END
