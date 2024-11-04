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
 * @file thermo21.h
 * @brief This file contains API for Thermo 21 Click Driver.
 */

#ifndef THERMO21_H
#define THERMO21_H

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
 * @addtogroup thermo21 Thermo 21 Click Driver
 * @brief API for configuring and manipulating Thermo 21 Click driver.
 * @{
 */

/**
 * @defgroup thermo21_set Thermo 21 Registers Settings
 * @brief Settings for registers of Thermo 21 Click driver.
 */

/**
 * @addtogroup thermo21_set
 * @{
 */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b thermo21_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define THERMO21_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define THERMO21_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // thermo21_set

/**
 * @defgroup thermo21_map Thermo 21 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 21 Click driver.
 */

/**
 * @addtogroup thermo21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 21 Click to the selected MikroBUS.
 */
#define THERMO21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); 

/*! @} */ // thermo21_map
/*! @} */ // thermo21

/**
 * @brief Thermo 21 Click context object.
 * @details Context object definition of Thermo 21 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t  spi;          /**< SPI driver object. */
    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} thermo21_t;

/**
 * @brief Thermo 21 Click configuration object.
 * @details Configuration object definition of Thermo 21 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} thermo21_cfg_t;

/**
 * @brief Thermo 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO21_OK = 0,
    THERMO21_ERROR = -1

} thermo21_return_value_t;

/*!
 * @addtogroup thermo21 Thermo 21 Click Driver
 * @brief API for configuring and manipulating Thermo 21 Click driver.
 * @{
 */

/**
 * @brief Thermo 21 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo21_cfg_setup ( thermo21_cfg_t *cfg );

/**
 * @brief Thermo 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thermo21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo21_init ( thermo21_t *ctx, thermo21_cfg_t *cfg );

/**
 * @brief Data reading function.
 * @details This function reads a desired number of data bytes from
 * the device by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo21_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo21_generic_read ( thermo21_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief Temperature reading function.
 * @details This function reads a 2 bytes and calculates temperature from device.
 * @param[in] ctx : Click context object.
 * See #thermo21_t object definition for detailed explanation.
 * @param[out] data_out : Output temperature data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Output temperature in Celisus degrees .
 */
err_t thermo21_temperature_read ( thermo21_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // THERMO21_H

/*! @} */ // thermo21

// ------------------------------------------------------------------------ END
