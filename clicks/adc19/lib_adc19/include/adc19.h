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
 * @file adc19.h
 * @brief This file contains API for ADC 19 Click Driver.
 */

#ifndef ADC19_H
#define ADC19_H

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
 * @addtogroup adc19 ADC 19 Click Driver
 * @brief API for configuring and manipulating ADC 19 Click driver.
 * @{
 */

/**
 * @defgroup adc19_set ADC 19 Settings
 * @brief Settings of ADC 19 Click driver.
 */

/**
 * @addtogroup adc19_set
 * @{
 */

/**
 * @brief ADC 19 input channel selection.
 * @details Specified input channel selection setting of ADC 19 Click driver.
 */
#define ADC19_INPUT_CHANNEL_1                   1
#define ADC19_INPUT_CHANNEL_2                   2

/**
 * @brief ADC 19 resolution and vref settings.
 * @details Specified resolution and vref settings of ADC 19 Click driver.
 */
#define ADC19_RESOLUTION_12BIT                  0x0FFF
#define ADC19_VREF_3V3                          3.3
#define ADC19_VREF_5V                           5.0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adc19_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC19_SET_DATA_SAMPLE_EDGE              SET_SPI_DATA_SAMPLE_EDGE
#define ADC19_SET_DATA_SAMPLE_MIDDLE            SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc19_set

/**
 * @defgroup adc19_map ADC 19 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 19 Click driver.
 */

/**
 * @addtogroup adc19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 19 Click to the selected MikroBUS.
 */
#define ADC19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // adc19_map
/*! @} */ // adc19

/**
 * @brief ADC 19 Click context object.
 * @details Context object definition of ADC 19 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;                               /**< SPI driver object. */

    pin_name_t   chip_select;                       /**< Chip select pin descriptor (used for SPI driver). */
    
    float        vref;                              /**< Voltage reference. */

} adc19_t;

/**
 * @brief ADC 19 Click configuration object.
 * @details Configuration object definition of ADC 19 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                               /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                               /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                 /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                           spi_speed;   /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;    /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity; /**< Chip select pin polarity. */

} adc19_cfg_t;

/**
 * @brief ADC 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC19_OK = 0,
    ADC19_ERROR = -1

} adc19_return_value_t;

/*!
 * @addtogroup adc19 ADC 19 Click Driver
 * @brief API for configuring and manipulating ADC 19 Click driver.
 * @{
 */

/**
 * @brief ADC 19 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc19_cfg_setup ( adc19_cfg_t *cfg );

/**
 * @brief ADC 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #adc19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc19_init ( adc19_t *ctx, adc19_cfg_t *cfg );

/**
 * @brief ADC 19 set vref function.
 * @details This function sets the voltage reference value that will be used for voltage calculation.
 * @param[in] ctx : Click context object.
 * See #adc19_t object definition for detailed explanation.
 * @param[in] vref : Voltage reference 3.3V or 5.0V.
 * @return None.
 * @note None.
 */
void adc19_set_vref ( adc19_t *ctx, float vref );

/**
 * @brief ADC 19 set input channel function.
 * @details This function sets the selected input channel active by modifying the control register.
 * @param[in] ctx : Click context object.
 * See #adc19_t object definition for detailed explanation.
 * @param[in] input_ch : Input channel number (1-2).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc19_set_input_channel ( adc19_t *ctx, uint8_t input_ch );

/**
 * @brief ADC 19 get voltage function.
 * @details This function reads the voltage from the previously selected channel 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc19_t object definition for detailed explanation.
 * @param[out] voltage : Voltage value [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc19_get_voltage ( adc19_t *ctx, float *voltage );

#ifdef __cplusplus
}
#endif
#endif // ADC19_H

/*! @} */ // adc19

// ------------------------------------------------------------------------ END
