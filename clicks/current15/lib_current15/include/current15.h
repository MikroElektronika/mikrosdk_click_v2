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
 * @file current15.h
 * @brief This file contains API for Current 15 Click Driver.
 */

#ifndef CURRENT15_H
#define CURRENT15_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup current15 Current 15 Click Driver
 * @brief API for configuring and manipulating Current 15 Click driver.
 * @{
 */

/**
 * @defgroup current15_set Current 15 Settings
 * @brief Settings of Current 15 Click driver.
 */

/**
 * @addtogroup current15_set
 * @{
 */

/**
 * @brief Current 15 input channel selection.
 * @details Specified input channel selection setting of Current 15 Click driver.
 */
#define CURRENT15_INPUT_CHANNEL_VREF            0
#define CURRENT15_INPUT_CHANNEL_VOUT            1

/**
 * @brief Current 15 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Current 15 Click driver.
 */
#define CURRENT15_NUM_CONVERSIONS               200

/**
 * @brief Current 15 ADC setting.
 * @details Specified settings for ADC of Current 15 Click driver.
 */
#define CURRENT15_ADC_RESOLUTION                0x0FFF
#define CURRENT15_VREF_3V3                      3.3
#define CURRENT15_VOUT_SEL_AN_PIN               0
#define CURRENT15_VOUT_SEL_SPI                  1
#define CURRENT15_VOUT_SEL                      CURRENT15_VOUT_SEL_SPI

/**
 * @brief Current 15 timeout setting.
 * @details Specified setting for timeout of Current 15 Click driver.
 */
#define CURRENT15_TIMEOUT_MS                    2000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b current15_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CURRENT15_SET_DATA_SAMPLE_EDGE          SET_SPI_DATA_SAMPLE_EDGE
#define CURRENT15_SET_DATA_SAMPLE_MIDDLE        SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // current15_set

/**
 * @defgroup current15_map Current 15 MikroBUS Map
 * @brief MikroBUS pin mapping of Current 15 Click driver.
 */

/**
 * @addtogroup current15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current 15 Click to the selected MikroBUS.
 */
#define CURRENT15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an   = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // current15_map
/*! @} */ // current15

/**
 * @brief Current 15 Click context object.
 * @details Context object definition of Current 15 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t fault;         /**< Overcurrent fault pin (active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */
    analog_in_t adc;            /**< ADC module object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    float sensor_vref;          /**< Sensor voltage reference - zero current voltage offset. */
    float data_resolution;      /**< Calibrated data resolution. */

} current15_t;

/**
 * @brief Current 15 Click configuration object.
 * @details Configuration object definition of Current 15 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t an;              /**< Analog pin descriptor. */

    // Additional gpio pins
    pin_name_t fault;           /**< Overcurrent fault pin (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} current15_cfg_t;

/**
 * @brief Current 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENT15_OK = 0,
    CURRENT15_ERROR = -1

} current15_return_value_t;

/*!
 * @addtogroup current15 Current 15 Click Driver
 * @brief API for configuring and manipulating Current 15 Click driver.
 * @{
 */

/**
 * @brief Current 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #current15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void current15_cfg_setup ( current15_cfg_t *cfg );

/**
 * @brief Current 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #current15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #current15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current15_init ( current15_t *ctx, current15_cfg_t *cfg );

/**
 * @brief Current 15 read raw ADC value function.
 * @details This function reads raw ADC value of the selected input channel.
 * @param[in] ctx : Click context object.
 * See #current15_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-VREF, 1-VOUT).
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t current15_read_raw_adc ( current15_t *ctx, uint8_t channel, uint16_t *raw_adc );

/**
 * @brief Current 15 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level
 * of the selected input channel.
 * @param[in] ctx : Click context object.
 * See #current15_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-VREF, 1-VOUT).
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t current15_read_voltage ( current15_t *ctx, uint8_t channel, float *voltage );

/**
 * @brief Current 15 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level
 * of the selected input channel.
 * @param[in] ctx : Click context object.
 * See #current15_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-VREF, 1-VOUT).
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t current15_read_voltage_avg ( current15_t *ctx, uint8_t channel, uint16_t num_conv, float *voltage_avg );

/**
 * @brief Current 15 get FAULT pin function.
 * @details This function returns the overcurrent fault (FAULT) pin logic state.
 * @param[in] ctx : Click context object.
 * See #current15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t current15_get_fault_pin ( current15_t *ctx );

/**
 * @brief Current 15 calib resolution function.
 * @details This function reads the sensor voltage reference and calibrates the data resolution
 * at a known load current.
 * @param[in] ctx : Click context object.
 * See #current15_t object definition for detailed explanation.
 * @param[in] calib_current : The known load current used for calibrating data resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when a known amount of load current flows through the sensor.
 */
err_t current15_calib_resolution ( current15_t *ctx, float calib_current );

/**
 * @brief Current 15 read current function.
 * @details This function reads the input current level [A].
 * @param[in] ctx : Click context object.
 * See #current15_t object definition for detailed explanation.
 * @param[out] current : Input current level [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on sensor voltage reference and calibrated data resolution.
 * Refer to the current15_calib_resolution function.
 */
err_t current15_read_current ( current15_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // CURRENT15_H

/*! @} */ // current15

// ------------------------------------------------------------------------ END
