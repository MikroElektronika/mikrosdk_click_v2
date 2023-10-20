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
 * @file spiisolator5.h
 * @brief This file contains API for SPI Isolator 5 Click Driver.
 */

#ifndef SPIISOLATOR5_H
#define SPIISOLATOR5_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup spiisolator5 SPI Isolator 5 Click Driver
 * @brief API for configuring and manipulating SPI Isolator 5 Click driver.
 * @{
 */

/**
 * @defgroup spiisolator5_set SPI Isolator 5 Settings
 * @brief Settings of SPI Isolator 5 Click driver.
 */

/**
 * @addtogroup spiisolator5_set
 * @{
 */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b spiisolator5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SPIISOLATOR5_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define SPIISOLATOR5_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // spiisolator5_set

/**
 * @defgroup spiisolator5_map SPI Isolator 5 MikroBUS Map
 * @brief MikroBUS pin mapping of SPI Isolator 5 Click driver.
 */

/**
 * @addtogroup spiisolator5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SPI Isolator 5 Click to the selected MikroBUS.
 */
#define SPIISOLATOR5_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ) 

/*! @} */ // spiisolator5_map
/*! @} */ // spiisolator5

/**
 * @brief SPI Isolator 5 Click context object.
 * @details Context object definition of SPI Isolator 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;            /**< Enable pin. */

    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} spiisolator5_t;

/**
 * @brief SPI Isolator 5 Click configuration object.
 * @details Configuration object definition of SPI Isolator 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t en;              /**< Enable pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} spiisolator5_cfg_t;

/**
 * @brief SPI Isolator 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SPIISOLATOR5_OK = 0,
    SPIISOLATOR5_ERROR = -1

} spiisolator5_return_value_t;

/*!
 * @addtogroup spiisolator5 SPI Isolator 5 Click Driver
 * @brief API for configuring and manipulating SPI Isolator 5 Click driver.
 * @{
 */

/**
 * @brief SPI Isolator 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #spiisolator5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void spiisolator5_cfg_setup ( spiisolator5_cfg_t *cfg );

/**
 * @brief SPI Isolator 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #spiisolator5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #spiisolator5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator5_init ( spiisolator5_t *ctx, spiisolator5_cfg_t *cfg );

/**
 * @brief SPI Isolator 5 enable function.
 * @details This function performs enabling a device 
 * the DCL541A01, High Speed Quad Channel Digital Isolators
 * on the SPI Isolator 5 Click board™.
 * @param[out] ctx : Click context object.
 * See #spiisolator5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void spiisolator5_enable ( spiisolator5_t *ctx );

/**
 * @brief SPI Isolator 5 disable function.
 * @details This function performs disabling  
 * the DCL541A01, High Speed Quad Channel Digital Isolators
 * on the SPI Isolator 5 Click board™.
 * @param[out] ctx : Click context object.
 * See #spiisolator5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void spiisolator5_disable ( spiisolator5_t *ctx );

/**
 * @brief SPI Isolator 5 data writing function.
 * @details This function writes a desired number of data bytes 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator5_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator5_write ( spiisolator5_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief SPI Isolator 5 data reading function.
 * @details This function reads a desired number of data bytes
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator5_read ( spiisolator5_t *ctx, uint8_t *data_out, uint8_t len_out );

/**
 * @brief SPI Isolator 5 write then read function.
 * @details This function writes and then reads a desired number of data bytes 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator5_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len_in : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[in] len_out : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator5_write_then_read ( spiisolator5_t *ctx, uint8_t *data_in, uint8_t len_in, uint8_t *data_out, uint8_t len_out );

/**
 * @brief SPI Isolator 5 transfer function.
 * @details This function writes and reads a desired number of data bytes 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator5_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be transferred (written/read).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator5_transfer ( spiisolator5_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif // SPIISOLATOR5_H

/*! @} */ // spiisolator5

// ------------------------------------------------------------------------ END
