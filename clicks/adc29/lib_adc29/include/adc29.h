/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file adc29.h
 * @brief This file contains API for ADC 29 Click Driver.
 */

#ifndef ADC29_H
#define ADC29_H

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
 * @addtogroup adc29 ADC 29 Click Driver
 * @brief API for configuring and manipulating ADC 29 Click driver.
 * @{
 */

/**
 * @defgroup adc29_set ADC 29 Registers Settings
 * @brief Settings for registers of ADC 29 Click driver.
 */

/**
 * @addtogroup adc29_set
 * @{
 */

/**
 * @brief ADC 29 VREF voltage setting.
 * @details Specified setting for VREF voltage of ADC 29 Click driver.
 */
#define ADC29_VREF_3V0                  3.0f

/**
 * @brief ADC 29 data resolution setting.
 * @details Specified setting for data resolution of ADC 29 Click driver.
 */
#define ADC29_ADC_RESOLUTION            4095.0f

/**
 * @brief ADC 29 data calibration setting.
 * @details Specified setting for data calibration of ADC 29 Click driver.
 */
#define ADC29_RECALIB_NUM_CLOCKS        1024
#define ADC29_RECALIB_NUM_DATA          128

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adc29_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC29_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ADC29_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc29_set

/**
 * @defgroup adc29_map ADC 29 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 29 Click driver.
 */

/**
 * @addtogroup adc29_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 29 Click to the selected MikroBUS.
 */
#define ADC29_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // adc29_map
/*! @} */ // adc29

/**
 * @brief ADC 29 Click context object.
 * @details Context object definition of ADC 29 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;                               /**< SPI driver object. */

    pin_name_t   chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */
    
    // reference voltage
    float vref;                                     /**< Reference voltage in volts. */

} adc29_t;

/**
 * @brief ADC 29 Click configuration object.
 * @details Configuration object definition of ADC 29 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                                  /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} adc29_cfg_t;

/**
 * @brief ADC 29 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC29_OK = 0,
    ADC29_ERROR = -1

} adc29_return_value_t;

/*!
 * @addtogroup adc29 ADC 29 Click Driver
 * @brief API for configuring and manipulating ADC 29 Click driver.
 * @{
 */

/**
 * @brief ADC 29 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc29_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc29_cfg_setup ( adc29_cfg_t *cfg );

/**
 * @brief ADC 29 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #adc29_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc29_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc29_init ( adc29_t *ctx, adc29_cfg_t *cfg );

/**
 * @brief ADC 29 read raw ADC function.
 * @details This function triggers a single conversion and reads the raw 12-bit
 * ADC result by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc29_t object definition for detailed explanation.
 * @param[out] raw_adc : Pointer to the raw ADC result [0, 4095].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc29_read_raw_adc ( adc29_t *ctx, uint16_t *raw_adc );

/**
 * @brief ADC 29 read voltage function.
 * @details This function triggers a single conversion and reads the ADC result,
 * then converts it to a voltage in volts.
 * @param[in] ctx : Click context object.
 * See #adc29_t object definition for detailed explanation.
 * @param[out] voltage : Pointer to the output voltage in volts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc29_read_voltage ( adc29_t *ctx, float *voltage );

/**
 * @brief ADC 29 recalibrate function.
 * @details This function initiates a manual self-calibration of the ADC by
 * transmitting 1024 SCLK pulses while the device is in acquisition mode.
 * @param[in] ctx : Click context object.
 * See #adc29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Calibration takes approximately 500 ms to complete.
 */
err_t adc29_recalibrate ( adc29_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ADC29_H

/*! @} */ // adc29

// ------------------------------------------------------------------------ END
