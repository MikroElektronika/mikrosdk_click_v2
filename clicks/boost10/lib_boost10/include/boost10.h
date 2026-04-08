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
 * @file boost10.h
 * @brief This file contains API for Boost 10 Click Driver.
 */

#ifndef BOOST10_H
#define BOOST10_H

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
 * @addtogroup boost10 Boost 10 Click Driver
 * @brief API for configuring and manipulating Boost 10 Click driver.
 * @{
 */

/**
 * @defgroup boost10_set Boost 10 Registers Settings
 * @brief Settings for registers of Boost 10 Click driver.
 */

/**
 * @addtogroup boost10_set
 * @{
 */

/**
 * @brief Boost 10 wiper setting.
 * @details Specified setting for wiper of Boost 10 Click driver.
 */
#define BOOST10_WIPER_MAX                   0xFF
#define BOOST10_WIPER_MIN                   0x00
#define BOOST10_WIPER_POS                   256

/**
 * @brief Boost 10 vout calculation setting.
 * @details Specified setting for vout calculation of Boost 10 Click driver.
 */
#define BOOST10_DIGIPOT_RES_KOHM            100.0
#define BOOST10_R7_RES_KOHM                 620.0
#define BOOST10_R8_RES_KOHM                 56.0
#define BOOST10_VOUT_OFFSET                 1.0
#define BOOST10_VOUT_MIN                    5.0
#define BOOST10_VOUT_MAX                    12.0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b boost10_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BOOST10_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define BOOST10_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // boost10_set

/**
 * @defgroup boost10_map Boost 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Boost 10 Click driver.
 */

/**
 * @addtogroup boost10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Boost 10 Click to the selected MikroBUS.
 */
#define BOOST10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pg   = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // boost10_map
/*! @} */ // boost10

/**
 * @brief Boost 10 Click context object.
 * @details Context object definition of Boost 10 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t pg;            /**< Power good pin indication (active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} boost10_t;

/**
 * @brief Boost 10 Click configuration object.
 * @details Configuration object definition of Boost 10 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t pg;              /**< Power good pin indication (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} boost10_cfg_t;

/**
 * @brief Boost 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BOOST10_OK = 0,
    BOOST10_ERROR = -1

} boost10_return_value_t;

/*!
 * @addtogroup boost10 Boost 10 Click Driver
 * @brief API for configuring and manipulating Boost 10 Click driver.
 * @{
 */

/**
 * @brief Boost 10 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #boost10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void boost10_cfg_setup ( boost10_cfg_t *cfg );

/**
 * @brief Boost 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #boost10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #boost10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost10_init ( boost10_t *ctx, boost10_cfg_t *cfg );

/**
 * @brief Boost 10 set wiper function.
 * @details This function sets the digital potentiometer wiper position by writing
 * a single byte over the SPI interface.
 * @param[in] ctx : Click context object.
 * See #boost10_t object definition for detailed explanation.
 * @param[in] wiper : Wiper position value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost10_set_wiper ( boost10_t *ctx, uint8_t wiper );

/**
 * @brief Boost 10 get PG pin function.
 * @details This function reads and returns the logic state of the PG pin.
 * @param[in] ctx : Click context object.
 * See #boost10_t object definition for detailed explanation.
 * @return PG pin logic state.
 * @note None.
 */
uint8_t boost10_get_pg_pin ( boost10_t *ctx );

/**
 * @brief Boost 10 set resistance function.
 * @details This function calculates the appropriate digital potentiometer wiper
 * position for the requested resistance value and updates the potentiometer.
 * @param[in] ctx : Click context object.
 * See #boost10_t object definition for detailed explanation.
 * @param[in] res_kohm : Desired resistance value in kOhms.
                         Range: from BOOST10_R8_RES_KOHM to (BOOST10_R8_RES_KOHM + BOOST10_DIGIPOT_RES_KOHM)
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost10_set_resistance ( boost10_t *ctx, float res_kohm );

/**
 * @brief Boost 10 set output voltage function.
 * @details This function calculates the required feedback resistance for the
 * requested output voltage and updates the digital potentiometer accordingly.
 * @param[in] ctx : Click context object.
 * See #boost10_t object definition for detailed explanation.
 * @param[in] vout : Desired output voltage value from BOOST10_VOUT_MIN to BOOST10_VOUT_MAX.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost10_set_vout ( boost10_t *ctx, float vout );

#ifdef __cplusplus
}
#endif
#endif // BOOST10_H

/*! @} */ // boost10

// ------------------------------------------------------------------------ END
