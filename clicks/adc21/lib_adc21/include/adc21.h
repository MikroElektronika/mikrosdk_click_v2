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
 * @file adc21.h
 * @brief This file contains API for ADC 21 Click Driver.
 */

#ifndef ADC21_H
#define ADC21_H

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
 * @addtogroup adc21 ADC 21 Click Driver
 * @brief API for configuring and manipulating ADC 21 Click driver.
 * @{
 */

/**
 * @defgroup adc21_set ADC 21 Settings
 * @brief Settings of ADC 21 Click driver.
 */

/**
 * @addtogroup adc21_set
 * @{
 */

/**
 * @brief ADC 21 channel selection setting.
 * @details Specified setting for channel selection of ADC 21 Click driver.
 */
#define ADC21_CHANNEL_0                 0
#define ADC21_CHANNEL_1                 1
#define ADC21_CHANNEL_2                 2
#define ADC21_CHANNEL_3                 3
#define ADC21_CHANNEL_4                 4
#define ADC21_CHANNEL_5                 5
#define ADC21_CHANNEL_6                 6
#define ADC21_CHANNEL_7                 7

/**
 * @brief ADC 21 data setting.
 * @details Specified data settings of ADC 21 Click driver.
 */
#define ADC21_DATA_RESOLUTION           0x0FFF
#define ADC21_AVCC_3V3                  3.3
#define ADC21_AVCC_5V                   5.0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adc21_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC21_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ADC21_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc21_set

/**
 * @defgroup adc21_map ADC 21 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 21 Click driver.
 */

/**
 * @addtogroup adc21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 21 Click to the selected MikroBUS.
 */
#define ADC21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // adc21_map
/*! @} */ // adc21

/**
 * @brief ADC 21 Click context object.
 * @details Context object definition of ADC 21 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */

} adc21_t;

/**
 * @brief ADC 21 Click configuration object.
 * @details Configuration object definition of ADC 21 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} adc21_cfg_t;

/**
 * @brief ADC 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC21_OK = 0,
    ADC21_ERROR = -1

} adc21_return_value_t;

/*!
 * @addtogroup adc21 ADC 21 Click Driver
 * @brief API for configuring and manipulating ADC 21 Click driver.
 * @{
 */

/**
 * @brief ADC 21 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc21_cfg_setup ( adc21_cfg_t *cfg );

/**
 * @brief ADC 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adc21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc21_init ( adc21_t *ctx, adc21_cfg_t *cfg );

/**
 * @brief ADC 21 read raw adc function.
 * @details This function reads raw ADC value from the selected channel by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc21_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-7).
 * @param[out] raw_adc : 12-bit raw ADC value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc21_read_raw_adc ( adc21_t *ctx, uint8_t channel, uint16_t *raw_adc );

/**
 * @brief ADC 21 read voltage function.
 * @details This function reads raw ADC value from the selected channel and converts it to proportional
 * voltage level depending on the avcc selection.
 * @param[in] ctx : Click context object.
 * See #adc21_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-7).
 * @param[in] avcc : Voltage on AVCC (3.3V by default).
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc21_read_voltage ( adc21_t *ctx, uint8_t channel, float avcc, float *voltage );

#ifdef __cplusplus
}
#endif
#endif // ADC21_H

/*! @} */ // adc21

// ------------------------------------------------------------------------ END
