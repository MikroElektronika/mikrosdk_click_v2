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
 * @file loadcell7.h
 * @brief This file contains API for Load Cell 7 Click Driver.
 */

#ifndef LOADCELL7_H
#define LOADCELL7_H

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
 * @addtogroup loadcell7 Load Cell 7 Click Driver
 * @brief API for configuring and manipulating Load Cell 7 Click driver.
 * @{
 */

/**
 * @defgroup loadcell7_set Load Cell 7 Registers Settings
 * @brief Settings for registers of Load Cell 7 Click driver.
 */

/**
 * @addtogroup loadcell7_set
 * @{
 */

/**
 * @brief Load Cell 7 number of AD conversions used in a single calculation.
 * @details Specified number of AD conversions used in a single calculation of Load Cell 7 Click driver.
 */
#define LOADCELL7_NUM_CONVERSIONS           80

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b loadcell7_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define LOADCELL7_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define LOADCELL7_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // loadcell7_set

/**
 * @defgroup loadcell7_map Load Cell 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Load Cell 7 Click driver.
 */

/**
 * @addtogroup loadcell7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Load Cell 7 Click to the selected MikroBUS.
 */
#define LOADCELL7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // loadcell7_map
/*! @} */ // loadcell7

/**
 * @brief Load Cell 7 Click context object.
 * @details Context object definition of Load Cell 7 Click driver.
 */
typedef struct
{
    digital_in_t miso;              /**< MISO as input data ready pin. */
    digital_out_t cs;               /**< Power down pin (Active Low). */
    
    // Modules
    spi_master_t spi;               /**< SPI driver object. */
    
    int32_t      tare_scale;        /**< Tare scale - ADC value of the empty container. */
    float        weight_scale;      /**< Calibrated weight scale. */

} loadcell7_t;

/**
 * @brief Load Cell 7 Click configuration object.
 * @details Configuration object definition of Load Cell 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Power down pin (Active Low). */

    // static variable
    uint32_t            spi_speed;  /**< SPI serial speed. */
    spi_master_mode_t   spi_mode;   /**< SPI master mode. */

} loadcell7_cfg_t;

/**
 * @brief Load Cell 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LOADCELL7_OK = 0,
    LOADCELL7_ERROR = -1

} loadcell7_return_value_t;

/*!
 * @addtogroup loadcell7 Load Cell 7 Click Driver
 * @brief API for configuring and manipulating Load Cell 7 Click driver.
 * @{
 */

/**
 * @brief Load Cell 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #loadcell7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void loadcell7_cfg_setup ( loadcell7_cfg_t *cfg );

/**
 * @brief Load Cell 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #loadcell7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #loadcell7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell7_init ( loadcell7_t *ctx, loadcell7_cfg_t *cfg );

/**
 * @brief Load Cell 7 enable device function.
 * @details This function enables the device by setting the CS (PWDN) pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #loadcell7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void loadcell7_enable_device ( loadcell7_t *ctx );

/**
 * @brief Load Cell 7 disable device function.
 * @details This function disables the device by setting the CS (PWDN) pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #loadcell7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void loadcell7_disable_device ( loadcell7_t *ctx );

/**
 * @brief Load Cell 7 read raw adc function.
 * @details This function reads raw ADC measurements using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #loadcell7_t object definition for detailed explanation.
 * @param[out] data_out : 24-bit ADC data out.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell7_read_raw_adc ( loadcell7_t *ctx, int32_t *data_out );

/**
 * @brief Load Cell 7 tare scale function.
 * @details This function calculates the @b ctx->tare_scale which is the raw ADC readings of 
 * the empty container.
 * @param[in] ctx : Click context object.
 * See #loadcell7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell7_tare_scale ( loadcell7_t *ctx );

/**
 * @brief Load Cell 7 calibrate weight function.
 * @details This function calibrates the weight by calculating the @b ctx->weight_scale 
 * for the input calibration weight.
 * @param[in] ctx : Click context object.
 * See #loadcell7_t object definition for detailed explanation.
 * @param[in] cal_weight : Calibration weight value in grams of the goods placed on the scale.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t loadcell7_calibrate_weight ( loadcell7_t *ctx, float cal_weight );

/**
 * @brief Load Cell 7 get weight function.
 * @details This function calculates the weight of the goods in grams.
 * @param[in] ctx : Click context object.
 * See #loadcell7_t object definition for detailed explanation.
 * @param[out] weight : The weight of the goods in grams.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on the @b loadcell7_tare_scale and @b loadcell7_calibrate_weight functions
 * calculation results.
 */
err_t loadcell7_get_weight ( loadcell7_t *ctx, float *weight );

#ifdef __cplusplus
}
#endif
#endif // LOADCELL7_H

/*! @} */ // loadcell7

// ------------------------------------------------------------------------ END
