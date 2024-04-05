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
 * @file clockgen6.h
 * @brief This file contains API for Clock Gen 6 Click Driver.
 */

#ifndef CLOCKGEN6_H
#define CLOCKGEN6_H

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
 * @addtogroup clockgen6 Clock Gen 6 Click Driver
 * @brief API for configuring and manipulating Clock Gen 6 Click driver.
 * @{
 */

/**
 * @defgroup clockgen6_set Clock Gen 6 Registers Settings
 * @brief Settings for registers of Clock Gen 6 Click driver.
 */

/**
 * @addtogroup clockgen6_set
 * @{
 */

/**
 * @brief Clock Gen 6 digipot settings.
 * @details Specified setting for digipot of Clock Gen 6 Click driver.
 */
#define CLOCKGEN6_DIGIPOT_POSITION_MAX  255
#define CLOCKGEN6_DIGIPOT_POSITION_MIN  0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b clockgen6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CLOCKGEN6_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define CLOCKGEN6_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // clockgen6_set

/**
 * @defgroup clockgen6_map Clock Gen 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Clock Gen 6 Click driver.
 */

/**
 * @addtogroup clockgen6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Clock Gen 6 Click to the selected MikroBUS.
 */
#define CLOCKGEN6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en   = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // clockgen6_map
/*! @} */ // clockgen6

/**
 * @brief Clock Gen 6 Click context object.
 * @details Context object definition of Clock Gen 6 Click driver.
 */
typedef struct
{
    digital_out_t en;       /**< Enable output pin. */
    
    // Modules
    spi_master_t spi;       /**< SPI driver object. */

    pin_name_t chip_select; /**< Chip select pin descriptor (used for SPI driver). */

} clockgen6_t;

/**
 * @brief Clock Gen 6 Click configuration object.
 * @details Configuration object definition of Clock Gen 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;        /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;        /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;         /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;          /**< Chip select pin descriptor for SPI driver. */
    pin_name_t en;          /**< Enable output pin. */
    
    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} clockgen6_cfg_t;

/**
 * @brief Clock Gen 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CLOCKGEN6_OK = 0,
    CLOCKGEN6_ERROR = -1

} clockgen6_return_value_t;

/*!
 * @addtogroup clockgen6 Clock Gen 6 Click Driver
 * @brief API for configuring and manipulating Clock Gen 6 Click driver.
 * @{
 */

/**
 * @brief Clock Gen 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #clockgen6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void clockgen6_cfg_setup ( clockgen6_cfg_t *cfg );

/**
 * @brief Clock Gen 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #clockgen6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #clockgen6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen6_init ( clockgen6_t *ctx, clockgen6_cfg_t *cfg );

/**
 * @brief Clock Gen 6 default configuration function.
 * @details This function executes a default configuration of Clock Gen 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #clockgen6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t clockgen6_default_cfg ( clockgen6_t *ctx );

/**
 * @brief Clock Gen 6 set digipot function.
 * @details This function sets the digital potentiometer position by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #clockgen6_t object definition for detailed explanation.
 * @param[in] position : Digital potentiometer position (0-255).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t clockgen6_set_digipot ( clockgen6_t *ctx, uint8_t position );

/**
 * @brief Clock Gen 6 enable output function.
 * @details This function enables the output by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #clockgen6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void clockgen6_enable_output ( clockgen6_t *ctx );

/**
 * @brief Clock Gen 6 disable output function.
 * @details This function disables the output by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #clockgen6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void clockgen6_disable_output ( clockgen6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CLOCKGEN6_H

/*! @} */ // clockgen6

// ------------------------------------------------------------------------ END
