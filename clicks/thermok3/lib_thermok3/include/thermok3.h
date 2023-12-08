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
 * @file thermok3.h
 * @brief This file contains API for Thermo K 3 Click Driver.
 */

#ifndef THERMOK3_H
#define THERMOK3_H

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
 * @addtogroup thermok3 Thermo K 3 Click Driver
 * @brief API for configuring and manipulating Thermo K 3 Click driver.
 * @{
 */

/**
 * @defgroup thermok3_set Thermo K 3 Registers Settings
 * @brief Settings for registers of Thermo K 3 Click driver.
 */

/**
 * @addtogroup thermok3_set
 * @{
 */

/**
 * @brief Thermo K 3 output data setting.
 * @details Specified setting for output data of Thermo K 3 Click driver.
 */
#define THERMOK3_DUMMY_SIGN_BIT             0x80
#define THERMOK3_OPEN_THERMOCOUPLE_BIT      0x04
#define THERMOK3_DEVICE_ID_BIT              0x02

/**
 * @brief Thermo K 3 data resolution setting.
 * @details Specified setting for data resolution of Thermo K 3 Click driver.
 */
#define THERMOK3_DATA_RESOLUTION            0x0FFFu
#define THERMOK3_TEMP_RESOLUTION            0.25f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b thermok3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define THERMOK3_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define THERMOK3_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // thermok3_set

/**
 * @defgroup thermok3_map Thermo K 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo K 3 Click driver.
 */

/**
 * @addtogroup thermok3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo K 3 Click to the selected MikroBUS.
 */
#define THERMOK3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // thermok3_map
/*! @} */ // thermok3

/**
 * @brief Thermo K 3 Click context object.
 * @details Context object definition of Thermo K 3 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */

} thermok3_t;

/**
 * @brief Thermo K 3 Click configuration object.
 * @details Configuration object definition of Thermo K 3 Click driver.
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

} thermok3_cfg_t;

/**
 * @brief Thermo K 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMOK3_OK = 0,
    THERMOK3_ERROR = -1,
    THERMOK3_OPEN_THERMOCOUPLE = -2

} thermok3_return_value_t;

/*!
 * @addtogroup thermok3 Thermo K 3 Click Driver
 * @brief API for configuring and manipulating Thermo K 3 Click driver.
 * @{
 */

/**
 * @brief Thermo K 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermok3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermok3_cfg_setup ( thermok3_cfg_t *cfg );

/**
 * @brief Thermo K 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thermok3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermok3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermok3_init ( thermok3_t *ctx, thermok3_cfg_t *cfg );

/**
 * @brief Thermo K 3 read data function.
 * @details This function reads a raw data output by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #thermok3_t object definition for detailed explanation.
 * @param[out] data_out : 12-bit raw data output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - No thermocouple input.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermok3_read_data ( thermok3_t *ctx, uint16_t *data_out );

/**
 * @brief Thermo K 3 read temperature function.
 * @details This function reads a raw data output and converts it to temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #thermok3_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - No thermocouple input.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermok3_read_temperature ( thermok3_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // THERMOK3_H

/*! @} */ // thermok3

// ------------------------------------------------------------------------ END
