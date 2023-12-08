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
 * @file powermux2.h
 * @brief This file contains API for Power MUX 2 Click Driver.
 */

#ifndef POWERMUX2_H
#define POWERMUX2_H

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


/**
 * @defgroup powermux2_map Power MUX 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Power MUX 2 Click driver.
 */

/**
 * @addtogroup powermux2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Power MUX 2 Click to the selected MikroBUS.
 */
#define POWERMUX2_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )
/*! @} */ // powermux2_map
/*! @} */ // powermux2

/**
 * @brief Power MUX 2 Click context object.
 * @details Context object definition of Power MUX 2 Click driver.
 */
typedef struct
{
    // Modules

    spi_master_t  spi;          /**< SPI driver object. */
                              
    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} powermux2_t;

/**
 * @brief Power MUX 2 Click configuration object.
 * @details Configuration object definition of Power MUX 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} powermux2_cfg_t;

/**
 * @brief Power MUX 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    POWERMUX2_OK = 0,
    POWERMUX2_ERROR = -1

} powermux2_return_value_t;

/*!
 * @addtogroup powermux2 Power MUX 2 Click Driver
 * @brief API for configuring and manipulating Power MUX 2 Click driver.
 * @{
 */

/**
 * @brief Power MUX 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #powermux2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void powermux2_cfg_setup ( powermux2_cfg_t *cfg );

/**
 * @brief Power MUX 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #powermux2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #powermux2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powermux2_init ( powermux2_t *ctx, powermux2_cfg_t *cfg );

/**
 * @brief Power MUX 2 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #powermux2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powermux2_generic_write ( powermux2_t *ctx, uint8_t data_in );

/**
 * @brief Power MUX 2 set resistance function.
 * @details This function set resistance for the desired current limit 
 * of the TPS212x 2.8-V to 22-V Priority Power MUX with Seamless Switchover
 * on the the Power MUX 2 click board™.
 * @param[in] ctx : Click context object.
 * See #powermux2_t object definition for detailed explanation.
 * @param[in] resistance : Resistance [ kOhm ] from 18 kOhm to 100 kOhm.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powermux2_set_resistance ( powermux2_t *ctx, float resistance );

#ifdef __cplusplus
}
#endif
#endif // POWERMUX2_H

/*! @} */ // powermux2

// ------------------------------------------------------------------------ END
