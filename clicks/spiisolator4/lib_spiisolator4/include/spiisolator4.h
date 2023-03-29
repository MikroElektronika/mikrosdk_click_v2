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
 * @file spiisolator4.h
 * @brief This file contains API for SPI Isolator 4 Click Driver.
 */

#ifndef SPIISOLATOR4_H
#define SPIISOLATOR4_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup spiisolator4 SPI Isolator 4 Click Driver
 * @brief API for configuring and manipulating SPI Isolator 4 Click driver.
 * @{
 */

/**
 * @defgroup spiisolator4_set SPI Isolator 4 Registers Settings
 * @brief Settings for registers of SPI Isolator 4 Click driver.
 */

/**
 * @addtogroup spiisolator4_set
 * @{
 */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b spiisolator4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SPIISOLATOR4_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define SPIISOLATOR4_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // spiisolator4_set

/**
 * @defgroup spiisolator4_map SPI Isolator 4 MikroBUS Map
 * @brief MikroBUS pin mapping of SPI Isolator 4 Click driver.
 */

/**
 * @addtogroup spiisolator4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SPI Isolator 4 Click to the selected MikroBUS.
 */
#define SPIISOLATOR4_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.en1 = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // spiisolator4_map
/*! @} */ // spiisolator4

/**
 * @brief SPI Isolator 4 Click context object.
 * @details Context object definition of SPI Isolator 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en1;         /**< Enable pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} spiisolator4_t;

/**
 * @brief SPI Isolator 4 Click configuration object.
 * @details Configuration object definition of SPI Isolator 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  en1;        /**< Enable pin. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} spiisolator4_cfg_t;

/**
 * @brief SPI Isolator 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   SPIISOLATOR4_OK = 0,
   SPIISOLATOR4_ERROR = -1

} spiisolator4_return_value_t;

/**
 * @brief SPI Isolator 4 Click enable mode value data.
 * @details Predefined enum values for driver enable mode values.
 */
typedef enum
{
   SPIISOLATOR4_DISABLE = 0,
   SPIISOLATOR4_ENABLE = 1

} spiisolator4_enable_mode_t;

/*!
 * @addtogroup spiisolator4 SPI Isolator 4 Click Driver
 * @brief API for configuring and manipulating SPI Isolator 4 Click driver.
 * @{
 */

/**
 * @brief SPI Isolator 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #spiisolator4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void spiisolator4_cfg_setup ( spiisolator4_cfg_t *cfg );

/**
 * @brief SPI Isolator 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #spiisolator4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #spiisolator4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator4_init ( spiisolator4_t *ctx, spiisolator4_cfg_t *cfg );

/**
 * @brief SPI Isolator 4 default configuration function.
 * @details This function executes a default configuration of SPI Isolator 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #spiisolator4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t spiisolator4_default_cfg ( spiisolator4_t *ctx );

/**
 * @brief SPI Isolator 4 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator4_generic_write ( spiisolator4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief SPI Isolator 4 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #spiisolator4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spiisolator4_generic_read ( spiisolator4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief SPI Isolator 4 enable isolator function.
 * @details This function enable or disable ADuM341E quad-channel digital isolators
 * on the SPI Isolator 4 click board™.
 * @param[in] ctx : Click context object.
 * See #spiisolator4_t object definition for detailed explanation.
 * @param[in] en_mode 
 *         @li @c  0 ( SPIISOLATOR4_DISABLE )- Disable isolator,
 *         @li @c  1 ( SPIISOLATOR4_ENABLE  )- Enable isolator.
 * @return @li @c  0 - Success.
 *
 * @note None.
 */
err_t spiisolator4_set_enable ( spiisolator4_t *ctx, spiisolator4_enable_mode_t en_mode );

#ifdef __cplusplus
}
#endif
#endif // SPIISOLATOR4_H

/*! @} */ // spiisolator4

// ------------------------------------------------------------------------ END
