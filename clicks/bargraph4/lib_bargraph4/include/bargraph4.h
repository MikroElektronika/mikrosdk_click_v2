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
 * @file bargraph4.h
 * @brief This file contains API for BarGraph 4 Click Driver.
 */

#ifndef BARGRAPH4_H
#define BARGRAPH4_H

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
 * @addtogroup bargraph4 BarGraph 4 Click Driver
 * @brief API for configuring and manipulating BarGraph 4 Click driver.
 * @{
 */

/**
 * @defgroup bargraph4_set BarGraph 4 Settings
 * @brief Settings of BarGraph 4 Click driver.
 */

/**
 * @addtogroup bargraph4_set
 * @{
 */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b bargraph4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BARGRAPH4_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define BARGRAPH4_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // bargraph4_set

/**
 * @defgroup bargraph4_map BarGraph 4 MikroBUS Map
 * @brief MikroBUS pin mapping of BarGraph 4 Click driver.
 */

/**
 * @addtogroup bargraph4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BarGraph 4 Click to the selected MikroBUS.
 */
#define BARGRAPH4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // bargraph4_map
/*! @} */ // bargraph4

/**
 * @brief BarGraph 4 Click context object.
 * @details Context object definition of BarGraph 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;                                 /**< Reset pin. */

    // Modules
    spi_master_t  spi;                                  /**< SPI driver object. */

    pin_name_t  chip_select;                            /**< Chip select pin descriptor (used for SPI driver). */

} bargraph4_t;

/**
 * @brief BarGraph 4 Click configuration object.
 * @details Configuration object definition of BarGraph 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;                                     /**< Reset pin. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} bargraph4_cfg_t;

/**
 * @brief BarGraph 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BARGRAPH4_OK = 0,
    BARGRAPH4_ERROR = -1

} bargraph4_return_value_t;

/**
 * @brief BarGraph 4 Click select channel.
 * @details Enum values for channel selection.
 */
typedef enum
{
    BARGRAPH4_CHANNEL_A = 0,
    BARGRAPH4_CHANNEL_B,
    BARGRAPH4_CHANNEL_C,
    BARGRAPH4_CHANNEL_D

} bargraph4_sel_ch_t;

/**
 * @brief BarGraph 4 Click bar level.
 * @details Enum values for bar level.
 */
typedef enum
{
    BARGRAPH4_LEVEL_0 = 0,
    BARGRAPH4_LEVEL_1,
    BARGRAPH4_LEVEL_2,
    BARGRAPH4_LEVEL_3,
    BARGRAPH4_LEVEL_4

} bargraph4_level_t;

/*!
 * @addtogroup bargraph4 BarGraph 4 Click Driver
 * @brief API for configuring and manipulating BarGraph 4 Click driver.
 * @{
 */

/**
 * @brief BarGraph 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bargraph4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bargraph4_cfg_setup ( bargraph4_cfg_t *cfg );

/**
 * @brief BarGraph 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #bargraph4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bargraph4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bargraph4_init ( bargraph4_t *ctx, bargraph4_cfg_t *cfg );

/**
 * @brief BarGraph 4 set output function.
 * @details This function sets all outputs to desired value by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #bargraph4_t object definition for detailed explanation.
 * @param[in] ch_mask : Output write bit mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function affects all channel outputs.
 */
err_t bargraph4_set_output ( bargraph4_t *ctx, uint16_t ch_mask );

/**
 * @brief BarGraph 4 read output function.
 * @details This function reads the current state of all output by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #bargraph4_t object definition for detailed explanation.
 * @param[out] ch_mask : Output read bit mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function doesn't affect the channels output state.
 */
err_t bargraph4_read_output ( bargraph4_t *ctx, uint16_t *ch_mask );

/**
 * @brief BarGraph 4 disable output function.
 * @details This function disables all outputs.
 * @param[in] ctx : Click context object.
 * See #bargraph4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bargraph4_disable_output ( bargraph4_t *ctx );

/**
 * @brief BarGraph 4 enable output function.
 * @details This function enables all outputs.
 * @param[in] ctx : Click context object.
 * See #bargraph4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bargraph4_enable_output ( bargraph4_t *ctx );

/**
 * @brief BarGraph 4 set channel level function.
 * @details This function sets the level of a desired bar graph channel.
 * @param[in] ctx : Click context object.
 * See #bargraph4_t object definition for detailed explanation.
 * @param[in] channel : Channel selection.
 * See #bargraph4_sel_ch_t enum definition for detailed explanation.
 * @param[in] level : Level selection.
 * See #bargraph4_level_t enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function doesn't affect other channels output state.
 */
err_t bargraph4_set_channel_level ( bargraph4_t *ctx, bargraph4_sel_ch_t channel, bargraph4_level_t level );

#ifdef __cplusplus
}
#endif
#endif // BARGRAPH4_H

/*! @} */ // bargraph4

// ------------------------------------------------------------------------ END
