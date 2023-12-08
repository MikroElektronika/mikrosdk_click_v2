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
 * @file clockgen5.h
 * @brief This file contains API for Clock Gen 5 Click Driver.
 */

#ifndef CLOCKGEN5_H
#define CLOCKGEN5_H

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
 * @addtogroup clockgen5 Clock Gen 5 Click Driver
 * @brief API for configuring and manipulating Clock Gen 5 Click driver.
 * @{
 */

/**
 * @defgroup clockgen5_set Clock Gen 5 Registers Settings
 * @brief Settings for registers of Clock Gen 5 Click driver.
 */

/**
 * @addtogroup clockgen5_set
 * @{
 */

/**
 * @brief Clock Gen 5 description setting.
 * @details Specified setting for description of Clock Gen 5 Click driver.
 */
#define CLOCKGEN5_OCT_0                                           0
#define CLOCKGEN5_OCT_1                                           1
#define CLOCKGEN5_OCT_2                                           2
#define CLOCKGEN5_OCT_3                                           3
#define CLOCKGEN5_OCT_4                                           4
#define CLOCKGEN5_OCT_5                                           5
#define CLOCKGEN5_OCT_6                                           6
#define CLOCKGEN5_OCT_7                                           7
#define CLOCKGEN5_OCT_8                                           8
#define CLOCKGEN5_OCT_9                                           9
#define CLOCKGEN5_OCT_10                                          10
#define CLOCKGEN5_OCT_11                                          11
#define CLOCKGEN5_OCT_12                                          12
#define CLOCKGEN5_OCT_13                                          13
#define CLOCKGEN5_OCT_14                                          14
#define CLOCKGEN5_OCT_15                                          15

/**
 * @brief Clock Gen 5 output enable or fisable.
 * @details Specified setting for enabling or disabling output 
 * of Clock Gen 5 Click driver.
 */
#define CLOCKGEN5_OUTPUT_DISABLE                                  0x00
#define CLOCKGEN5_OUTPUT_ENABLE                                   0x01

/**
 * @brief Clock Gen 5 config settings.
 * @details Specified setting for configuring Clock Gen 5 Click driver.
 */
#define CLOCKGEN5_CFG_ON_CLK_180                                  0x00
#define CLOCKGEN5_CFG_OFF_ON                                      0x01
#define CLOCKGEN5_CFG_ON_OFF                                      0x02
#define CLOCKGEN5_CFG_POWER_DOWN                                  0x03

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b clockgen5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CLOCKGEN5_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define CLOCKGEN5_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // clockgen5_set

/**
 * @defgroup clockgen5_map Clock Gen 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Clock Gen 5 Click driver.
 */

/**
 * @addtogroup clockgen5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Clock Gen 5 Click to the selected MikroBUS.
 */
#define CLOCKGEN5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.oe = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // clockgen5_map
/*! @} */ // clockgen5

/**
 * @brief Clock Gen 5 Click context object.
 * @details Context object definition of Clock Gen 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  oe;                               /**< Asynchronous Enable. */

    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t dev_config;
    
} clockgen5_t;

/**
 * @brief Clock Gen 5 Click configuration object.
 * @details Configuration object definition of Clock Gen 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  oe;                                      /**< Asynchronous Enable. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */
    
} clockgen5_cfg_t;

/**
 * @brief Clock Gen 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   CLOCKGEN5_OK = 0,
   CLOCKGEN5_ERROR = -1

} clockgen5_return_value_t;

/*!
 * @addtogroup clockgen5 Clock Gen 5 Click Driver
 * @brief API for configuring and manipulating Clock Gen 5 Click driver.
 * @{
 */

/**
 * @brief Clock Gen 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #clockgen5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void clockgen5_cfg_setup ( clockgen5_cfg_t *cfg );

/**
 * @brief Clock Gen 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #clockgen5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #clockgen5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t clockgen5_init ( clockgen5_t *ctx, clockgen5_cfg_t *cfg );

/**
 * @brief Enable output function.
 * @details The function enable output
 * by sets the states of the OE ( RST ) pin.
 * @param[in] ctx : Click context object.
 * See #clockgen5_t object definition for detailed explanation.
 * @param[in] en_out : Output enabled or disabled.
 * @return Nothing.
 */
void clockgen5_out_enable ( clockgen5_t *ctx, uint8_t en_out );

/**
 * @brief Set configuration function.
 * @details The function set configuration.
 * @param[in] ctx : Click context object.
 * See #clockgen5_t object definition for detailed explanation.
 * @param[in] cfg : Config settings of Clock Gen 5 click.
 * @return Nothing.
 */
void clockgen5_set_config ( clockgen5_t *ctx, uint8_t cfg );

/**
 * @brief Set frequency function.
 * @details The function set frequency in range of 1.039 KHz to 68.03 MHz.
 * @param[in] ctx : Click context object.
 * See #clockgen5_t object definition for detailed explanation.
 * @param[in] freq : Frequency in KHz ( 1.039 KHz to 68.03 MHz )
 * @return Nothing.
 */
void clockgen5_set_freq ( clockgen5_t *ctx, float freq );

#ifdef __cplusplus
}
#endif
#endif // CLOCKGEN5_H

/*! @} */ // clockgen5

// ------------------------------------------------------------------------ END
