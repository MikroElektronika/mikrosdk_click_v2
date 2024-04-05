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
 * @file current5.h
 * @brief This file contains API for Current 5 Click Driver.
 */

#ifndef CURRENT5_H
#define CURRENT5_H

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
 * @addtogroup current5 Current 5 Click Driver
 * @brief API for configuring and manipulating Current 5 Click driver.
 * @{
 */

/**
 * @defgroup current5_set Current 5 Registers Settings
 * @brief Settings for registers of Current 5 Click driver.
 */

/**
 * @addtogroup current5_set
 * @{
 */

/**
 * @brief Current 5 current calculation values.
 * @details Specified current calculation values of Current 5 Click driver.
 */
#define CURRENT5_VOLTAGE_GAIN               200.0
#define CURRENT5_VREF_mV                    3300.0
#define CURRENT5_RESOLUTION                 4096.0
#define CURRENT5_RSHUNT_mOHM                2.0
#define CURRENT5_GAIN_ERROR_PERCENTS        6.0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b current5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CURRENT5_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define CURRENT5_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // current5_set

/**
 * @defgroup current5_map Current 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Current 5 Click driver.
 */

/**
 * @addtogroup current5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current 5 Click to the selected MikroBUS.
 */
#define CURRENT5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // current5_map
/*! @} */ // current5

/**
 * @brief Current 5 Click context object.
 * @details Context object definition of Current 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Mode selection. */

    // Input pins
    digital_in_t  alert;        /**< Alert. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} current5_t;

/**
 * @brief Current 5 Click configuration object.
 * @details Configuration object definition of Current 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;     /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  rst;    /**< Mode selection. */
    pin_name_t  alert;  /**< Alert. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} current5_cfg_t;

/**
 * @brief Current 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   CURRENT5_OK = 0,
   CURRENT5_ERROR = -1

} current5_return_value_t;

/*!
 * @addtogroup current5 Current 5 Click Driver
 * @brief API for configuring and manipulating Current 5 Click driver.
 * @{
 */

/**
 * @brief Current 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #current5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void current5_cfg_setup ( current5_cfg_t *cfg );

/**
 * @brief Current 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #current5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #current5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current5_init ( current5_t *ctx, current5_cfg_t *cfg );

/**
 * @brief Current 5 default configuration function.
 * @details This function executes a default configuration of Current 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #current5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t current5_default_cfg ( current5_t *ctx );

/**
 * @brief Current 5 data reading function.
 * @details This function reads a desired number of data bytes.
 * @param[in] ctx : Click context object.
 * See #current5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current5_generic_read ( current5_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief Get alert pin state.
 * @details This function reads a state of @b alert(int) pin.
 * @param[in] ctx : Click context object.
 * See #current5_t object definition for detailed explanation.
 * @return Alert pin state
 * @note Active low.
 */
uint8_t current5_get_alert ( current5_t *ctx );

/**
 * @brief Mode selection.
 * @details This function sets @b RESET pin state to set device mode.
 * @param[in] ctx : Click context object.
 * See #current5_t object definition for detailed explanation.
 * @param[in] state :   @li @c  0 - Transparent,
 *                      @li @c  1 - Latch.
 * @return Nothing
 */
void current5_set_rst ( current5_t *ctx, uint8_t state );

/**
 * @brief Read raw adc value.
 * @details This function reads raw adc data.
 * @param[in] ctx : Click context object.
 * See #current5_t object definition for detailed explanation.
 * @param[out] adc_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t current5_get_adc ( current5_t *ctx, uint16_t *adc_data );

/**
 * @brief Get voltage.
 * @details This function reads adc data on @b VOUT pin and converts it to voltage.
 * @param[in] ctx : Click context object.
 * See #current5_t object definition for detailed explanation.
 * @param[out] vout : Output voltage data in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t current5_get_voltage ( current5_t *ctx, float *vout );

/**
 * @brief Get current.
 * @details This function gets voltage data from @b VOUT and calculates input current from it.
 * @param[in] ctx : Click context object.
 * See #current5_t object definition for detailed explanation.
 * @param[out] current : Output current data in A.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t current5_get_current ( current5_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // CURRENT5_H

/*! @} */ // current5

// ------------------------------------------------------------------------ END
