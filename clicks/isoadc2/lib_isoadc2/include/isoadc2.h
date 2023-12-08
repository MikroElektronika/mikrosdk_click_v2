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
 * @file isoadc2.h
 * @brief This file contains API for ISO ADC 2 Click Driver.
 */

#ifndef ISOADC2_H
#define ISOADC2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup isoadc2 ISO ADC 2 Click Driver
 * @brief API for configuring and manipulating ISO ADC 2 Click driver.
 * @{
 */

/**
 * @defgroup isoadc2_set ISO ADC 2 Registers Settings
 * @brief Settings for registers of ISO ADC 2 Click driver.
 */

/**
 * @addtogroup isoadc2_set
 * @{
 */

/**
 * @brief ISO ADC 2 description setting.
 * @details Specified setting for description of ISO ADC 2 Click driver.
 */
#define ADC_MASK    0x0FFF
#define ADC_RES     4095
#define VREF        2500

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b isoadc2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ISOADC2_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ISOADC2_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // isoadc2_set

/**
 * @defgroup isoadc2_map ISO ADC 2 MikroBUS Map
 * @brief MikroBUS pin mapping of ISO ADC 2 Click driver.
 */

/**
 * @addtogroup isoadc2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISO ADC 2 Click to the selected MikroBUS.
 */
#define ISOADC2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.crt = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // isoadc2_map
/*! @} */ // isoadc2

/**
 * @brief ISO ADC 2 Click context object.
 * @details Context object definition of ISO ADC 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  crt;     /**< Conversion Initialization. */

    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

} isoadc2_t;

/**
 * @brief ISO ADC 2 Click configuration object.
 * @details Configuration object definition of ISO ADC 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  crt;        /**< Conversion Initialization. */

    // Static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} isoadc2_cfg_t;

/**
 * @brief ISO ADC 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   ISOADC2_OK = 0,
   ISOADC2_ERROR = -1

} isoadc2_return_value_t;

/*!
 * @addtogroup isoadc2 ISO ADC 2 Click Driver
 * @brief API for configuring and manipulating ISO ADC 2 Click driver.
 * @{
 */

/**
 * @brief ISO ADC 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #isoadc2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void isoadc2_cfg_setup ( isoadc2_cfg_t *cfg );

/**
 * @brief ISO ADC 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #isoadc2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #isoadc2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t isoadc2_init ( isoadc2_t *ctx, isoadc2_cfg_t *cfg );

/**
 * @brief ISO ADC 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t isoadc2_generic_write ( isoadc2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ISO ADC 2 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t isoadc2_generic_read ( isoadc2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ISO ADC 2 ADC data reading function.
 * @details Generic function for reading 12bit ADC data from device
 * @param[in] ctx : Click context object.
 * See #isoadc2_t object definition for detailed explanation.
 * @param[out] adc_val : Raw ADC data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t isoadc2_read_adc ( isoadc2_t *ctx, uint16_t *adc_val );

/**
 * @brief ISO ADC 2 voltage data reading function.
 * @details Function converts data to mV value.
 * @param[in] ctx : Click context object.
 * See #isoadc2_t object definition for detailed explanation.
 * @param[out] voltage : Converted mV data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t isoadc2_get_mv ( isoadc2_t *ctx, uint16_t *voltage );

#ifdef __cplusplus
}
#endif
#endif // ISOADC2_H

/*! @} */ // isoadc2

// ------------------------------------------------------------------------ END
