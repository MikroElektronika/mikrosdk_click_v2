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
 * @file serializer.h
 * @brief This file contains API for Serializer Click Driver.
 */

#ifndef SERIALIZER_H
#define SERIALIZER_H

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
 * @addtogroup serializer Serializer Click Driver
 * @brief API for configuring and manipulating Serializer Click driver.
 * @{
 */

/**
 * @defgroup serializer_set Serializer Settings
 * @brief Settings of Serializer Click driver.
 */

/**
 * @addtogroup serializer_set
 * @{
 */

/**
 * @brief Serializer status bits values.
 * @details Specified values for status bits of Serializer Click driver.
 */
#define SERIALIZER_STATUS_OVERTEMPERATURE   0x01
#define SERIALIZER_STATUS_UNDERVOLTAGE      0x02

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b serializer_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SERIALIZER_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define SERIALIZER_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // serializer_set

/**
 * @defgroup serializer_map Serializer MikroBUS Map
 * @brief MikroBUS pin mapping of Serializer Click driver.
 */

/**
 * @addtogroup serializer_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Serializer Click to the selected MikroBUS.
 */
#define SERIALIZER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // serializer_map
/*! @} */ // serializer

/**
 * @brief Serializer Click context object.
 * @details Context object definition of Serializer Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  flt;          /**< Fault indicator pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t    chip_select;  /**< Chip select pin descriptor (used for SPI driver). */

} serializer_t;

/**
 * @brief Serializer Click configuration object.
 * @details Configuration object definition of Serializer Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  flt;                                     /**< Fault indicator pin. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} serializer_cfg_t;

/**
 * @brief Serializer Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SERIALIZER_OK = 0,
    SERIALIZER_ERROR = -1

} serializer_return_value_t;

/*!
 * @addtogroup serializer Serializer Click Driver
 * @brief API for configuring and manipulating Serializer Click driver.
 * @{
 */

/**
 * @brief Serializer configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #serializer_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void serializer_cfg_setup ( serializer_cfg_t *cfg );

/**
 * @brief Serializer initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #serializer_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #serializer_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t serializer_init ( serializer_t *ctx, serializer_cfg_t *cfg );

/**
 * @brief Serializer get FLT pin function.
 * @details This function returns the fault pin logic state.
 * @param[out] ctx : Click context object.
 * See #serializer_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t serializer_get_flt_pin ( serializer_t *ctx );

/**
 * @brief Serializer read input function.
 * @details This function reads the input data by using SPI serial interface, and then checks 
 * the data integrity by verifying the CRC byte.
 * @param[in] ctx : Click context object.
 * See #serializer_t object definition for detailed explanation.
 * @param[out] data_out : Input data byte read.
 * @return @li @c >=0 - Success with status bits flag,
 *         @li @c -1  - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t serializer_read_input ( serializer_t *ctx, uint8_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // SERIALIZER_H

/*! @} */ // serializer

// ------------------------------------------------------------------------ END
