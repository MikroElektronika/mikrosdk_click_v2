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
 * @file bargraph5.h
 * @brief This file contains API for BarGraph 5 Click Driver.
 */

#ifndef BARGRAPH5_H
#define BARGRAPH5_H

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
 * @addtogroup bargraph5 BarGraph 5 Click Driver
 * @brief API for configuring and manipulating BarGraph 5 Click driver.
 * @{
 */

/**
 * @defgroup bargraph5_set BarGraph 5 Registers Settings
 * @brief Settings for registers of BarGraph 5 Click driver.
 */

/**
 * @addtogroup bargraph5_set
 * @{
 */

/**
 * @brief BarGraph 5 number of output channels.
 * @details Specified number of output channels of BarGraph 5 Click driver.
 */
#define BARGRAPH5_CHANNELS_NUM              24

/**
 * @brief BarGraph 5 default output brightness.
 * @details Specified default output brightness of BarGraph 5 Click driver.
 */
#define BARGRAPH5_BRIGHTNESS_MIN            0
#define BARGRAPH5_BRIGHTNESS_DEFAULT        3000
#define BARGRAPH5_BRIGHTNESS_MAX            4095

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b bargraph5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BARGRAPH5_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define BARGRAPH5_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // bargraph5_set

/**
 * @defgroup bargraph5_map BarGraph 5 MikroBUS Map
 * @brief MikroBUS pin mapping of BarGraph 5 Click driver.
 */

/**
 * @addtogroup bargraph5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BarGraph 5 Click to the selected MikroBUS.
 */
#define BARGRAPH5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.blank = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // bargraph5_map
/*! @} */ // bargraph5

/**
 * @brief BarGraph 5 Click context object.
 * @details Context object definition of BarGraph 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t blank;            /**< Output disable - Blank pin (Active high). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t chip_select;         /**< Chip select pin descriptor (used for SPI driver). */

    uint16_t channels[ BARGRAPH5_CHANNELS_NUM ];    /**< Output channels array. */
    
} bargraph5_t;

/**
 * @brief BarGraph 5 Click configuration object.
 * @details Configuration object definition of BarGraph 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t blank;               /**< Output disable - Blank pin (Active high). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} bargraph5_cfg_t;

/**
 * @brief BarGraph 5 Click select bar channel.
 * @details Enum values for bar channel selection.
 */
typedef enum
{
    BARGRAPH5_BAR_0 = 0,
    BARGRAPH5_BAR_1,
    BARGRAPH5_BAR_2,
    BARGRAPH5_BAR_3,
    BARGRAPH5_BAR_4,
    BARGRAPH5_BAR_5

} bargraph5_bar_sel_t;

/**
 * @brief BarGraph 5 Click bar level.
 * @details Enum values for bar level.
 */
typedef enum
{
    BARGRAPH5_LEVEL_0 = 0,
    BARGRAPH5_LEVEL_1,
    BARGRAPH5_LEVEL_2,
    BARGRAPH5_LEVEL_3,
    BARGRAPH5_LEVEL_4

} bargraph5_level_t;

/**
 * @brief BarGraph 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BARGRAPH5_OK = 0,
    BARGRAPH5_ERROR = -1

} bargraph5_return_value_t;

/*!
 * @addtogroup bargraph5 BarGraph 5 Click Driver
 * @brief API for configuring and manipulating BarGraph 5 Click driver.
 * @{
 */

/**
 * @brief BarGraph 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bargraph5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bargraph5_cfg_setup ( bargraph5_cfg_t *cfg );

/**
 * @brief BarGraph 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #bargraph5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bargraph5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bargraph5_init ( bargraph5_t *ctx, bargraph5_cfg_t *cfg );

/**
 * @brief BarGraph 5 default configuration function.
 * @details This function executes a default configuration of BarGraph 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #bargraph5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t bargraph5_default_cfg ( bargraph5_t *ctx );

/**
 * @brief BarGraph 5 write channels function.
 * @details This function writes all 24 output channels from the ctx->channels array
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #bargraph5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bargraph5_write_channels ( bargraph5_t *ctx );

/**
 * @brief BarGraph 5 read channels function.
 * @details This function reads all 24 output channels by using SPI serial interface
 * and stores the results in the ctx->channels array.
 * @param[in] ctx : Click context object.
 * See #bargraph5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The bargraph5_write_channels will be executed upon successful reading to preserve channels config.
 */
err_t bargraph5_read_channels ( bargraph5_t *ctx );

/**
 * @brief BarGraph 5 output enable function.
 * @details This function enables the BarGraph LEDs output by setting the BLANK pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #bargraph5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void bargraph5_output_enable ( bargraph5_t *ctx );

/**
 * @brief BarGraph 5 output disable function.
 * @details This function disables the BarGraph LEDs output by setting the BLANK pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #bargraph5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void bargraph5_output_disable ( bargraph5_t *ctx );

/**
 * @brief BarGraph 5 set bar level function.
 * @details This function sets the level of a selected BarGraph channel at the selected brightness.
 * @param[in] ctx : Click context object.
 * See #bargraph5_t object definition for detailed explanation.
 * @param[in] bar_num : Bar channel selection [0-5].
 * See #bargraph5_bar_sel_t enum definition for detailed explanation.
 * @param[in] level : Bar level selection [0-4].
 * See #bargraph5_level_t enum definition for detailed explanation.
 * @param[in] brightness : Bar level brightness [0-4095].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function does not affect other BarGraphs state.
 */
err_t bargraph5_set_bar_level ( bargraph5_t *ctx, bargraph5_bar_sel_t bar_num, 
                                bargraph5_level_t level, uint16_t brightness );

#ifdef __cplusplus
}
#endif
#endif // BARGRAPH5_H

/*! @} */ // bargraph5

// ------------------------------------------------------------------------ END
