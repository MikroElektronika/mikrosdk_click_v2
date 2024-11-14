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
 * @file hallcurrent21.h
 * @brief This file contains API for Hall Current 21 Click Driver.
 */

#ifndef HALLCURRENT21_H
#define HALLCURRENT21_H

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
 * @addtogroup hallcurrent21 Hall Current 21 Click Driver
 * @brief API for configuring and manipulating Hall Current 21 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent21_reg Hall Current 21 Registers List
 * @brief List of registers of Hall Current 21 Click driver.
 */

/**
 * @addtogroup hallcurrent21_reg
 * @{
 */

/**
 * @brief Hall Current 21 description register.
 * @details Specified register for description of Hall Current 21 Click driver.
 */
// TODO -- dodati makroe koji definisu adrese registara

/*! @} */ // hallcurrent21_reg

/**
 * @defgroup hallcurrent21_set Hall Current 21 Registers Settings
 * @brief Settings for registers of Hall Current 21 Click driver.
 */

/**
 * @addtogroup hallcurrent21_set
 * @{
 */

/**
 * @brief Hall Current 21 input channel selection.
 * @details Specified input channel selection setting of Hall Current 21 Click driver.
 */
#define HALLCURRENT21_INPUT_CHANNEL_VREF        0
#define HALLCURRENT21_INPUT_CHANNEL_VOUT        1

/**
 * @brief Hall Current 21 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Hall Current 21 Click driver.
 */
#define HALLCURRENT21_NUM_CONVERSIONS           200

/**
 * @brief Hall Current 21 ADC setting.
 * @details Specified settings for ADC of Hall Current 21 Click driver.
 */
#define HALLCURRENT21_ADC_RESOLUTION            0x0FFF
#define HALLCURRENT21_VREF_3V3                  3.3
#define HALLCURRENT21_VREF_5V                   5.0

/**
 * @brief Hall Current 21 timeout setting.
 * @details Specified setting for timeout of Hall Current 21 Click driver.
 */
#define HALLCURRENT21_TIMEOUT_MS                2000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hallcurrent21_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HALLCURRENT21_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define HALLCURRENT21_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hallcurrent21_set

/**
 * @defgroup hallcurrent21_map Hall Current 21 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 21 Click driver.
 */

/**
 * @addtogroup hallcurrent21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 21 Click to the selected MikroBUS.
 */
#define HALLCURRENT21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // hallcurrent21_map
/*! @} */ // hallcurrent21

/**
 * @brief Hall Current 21 Click context object.
 * @details Context object definition of Hall Current 21 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    float        vref;              /**< ADC reference voltage. */
    float        sensor_vref;       /**< Sensor voltage reference - zero current voltage offset. */
    float        data_resolution;   /**< Calibrated data resolution. */

} hallcurrent21_t;

/**
 * @brief Hall Current 21 Click configuration object.
 * @details Configuration object definition of Hall Current 21 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    float vref;                     /**< ADC reference voltage. */

} hallcurrent21_cfg_t;

/**
 * @brief Hall Current 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLCURRENT21_OK = 0,
    HALLCURRENT21_ERROR = -1

} hallcurrent21_return_value_t;

/*!
 * @addtogroup hallcurrent21 Hall Current 21 Click Driver
 * @brief API for configuring and manipulating Hall Current 21 Click driver.
 * @{
 */

/**
 * @brief Hall Current 21 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent21_cfg_setup ( hallcurrent21_cfg_t *cfg );

/**
 * @brief Hall Current 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent21_init ( hallcurrent21_t *ctx, hallcurrent21_cfg_t *cfg );

/**
 * @brief Hall Current 21 read raw ADC value function.
 * @details This function reads raw ADC value of the selected input channel.
 * @param[in] ctx : Click context object.
 * See #hallcurrent21_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-VREF, 1-VOUT).
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent21_read_raw_adc ( hallcurrent21_t *ctx, uint8_t channel, uint16_t *raw_adc );

/**
 * @brief Hall Current 21 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level
 * of the selected input channel.
 * @param[in] ctx : Click context object.
 * See #hallcurrent21_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-VREF, 1-VOUT).
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t hallcurrent21_read_voltage ( hallcurrent21_t *ctx, uint8_t channel, float *voltage );

/**
 * @brief Hall Current 21 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level
 * of the selected input channel.
 * @param[in] ctx : Click context object.
 * See #hallcurrent21_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-VREF, 1-VOUT).
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t hallcurrent21_read_voltage_avg ( hallcurrent21_t *ctx, uint8_t channel, uint16_t num_conv, float *voltage_avg );

/**
 * @brief Hall Current 21 set vref function.
 * @details This function sets the voltage reference for Hall Current 21 Click driver.
 * @param[in] ctx : Click context object.
 * See #hallcurrent21_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return None.
 * @note The default voltage reference set with @b hallcurrent21_init is 3.3V.
 */
void hallcurrent21_set_vref ( hallcurrent21_t *ctx, float vref );

/**
 * @brief Hall Current 21 calib resolution function.
 * @details This function reads the sensor voltage reference and calibrates the data resolution
 * at a known load current.
 * @param[in] ctx : Click context object.
 * See #hallcurrent21_t object definition for detailed explanation.
 * @param[in] calib_current : The known load current used for calibrating data resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when a known amount of load current flows through the sensor.
 */
err_t hallcurrent21_calib_resolution ( hallcurrent21_t *ctx, float calib_current );

/**
 * @brief Hall Current 21 read current function.
 * @details This function reads the input current level [A].
 * @param[in] ctx : Click context object.
 * See #hallcurrent21_t object definition for detailed explanation.
 * @param[out] current : Input current level [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on sensor voltage reference and calibrated data resolution.
 * Refer to the hallcurrent21_calib_resolution function.
 */
err_t hallcurrent21_read_current ( hallcurrent21_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT21_H

/*! @} */ // hallcurrent21

// ------------------------------------------------------------------------ END
