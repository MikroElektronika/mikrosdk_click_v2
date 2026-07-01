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
 * @file hallcurrent25.h
 * @brief This file contains API for Hall Current 25 Click Driver.
 */

#ifndef HALLCURRENT25_H
#define HALLCURRENT25_H

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
 * @addtogroup hallcurrent25 Hall Current 25 Click Driver
 * @brief API for configuring and manipulating Hall Current 25 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent25_set Hall Current 25 Settings
 * @brief Settings of Hall Current 25 Click driver.
 */

/**
 * @addtogroup hallcurrent25_set
 * @{
 */

/**
 * @brief Hall Current 25 input channel selection.
 * @details Specified input channel selection setting of Hall Current 25 Click driver.
 */
#define HALLCURRENT25_INPUT_CHANNEL_VOUT        0
#define HALLCURRENT25_INPUT_CHANNEL_VOC         1

/**
 * @brief Hall Current 25 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Hall Current 25 Click driver.
 */
#define HALLCURRENT25_NUM_CONVERSIONS           200

/**
 * @brief Hall Current 25 ADC setting.
 * @details Specified settings for ADC of Hall Current 25 Click driver.
 */
#define HALLCURRENT25_ADC_RESOLUTION            0x0FFF
#define HALLCURRENT25_VREF_3V3                  3.3
#define HALLCURRENT25_VREF_5V                   5.0
#define HALLCURRENT25_VREF                      HALLCURRENT25_VREF_3V3

/**
 * @brief Hall Current 25 timeout setting.
 * @details Specified setting for timeout of Hall Current 25 Click driver.
 */
#define HALLCURRENT25_TIMEOUT_MS                2000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hallcurrent25_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HALLCURRENT25_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define HALLCURRENT25_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hallcurrent25_set

/**
 * @defgroup hallcurrent25_map Hall Current 25 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 25 Click driver.
 */

/**
 * @addtogroup hallcurrent25_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 25 Click to the selected MikroBUS.
 */
#define HALLCURRENT25_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hallcurrent25_map
/*! @} */ // hallcurrent25

/**
 * @brief Hall Current 25 Click context object.
 * @details Context object definition of Hall Current 25 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t fault;             /**< Overcurrent fault pin (active low). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    float        zero_curr_offset;  /**< Voltage offset for zero current value. */
    float        data_resolution;   /**< Calibrated data resolution. */

} hallcurrent25_t;

/**
 * @brief Hall Current 25 Click configuration object.
 * @details Configuration object definition of Hall Current 25 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t fault;               /**< Overcurrent fault pin (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} hallcurrent25_cfg_t;

/**
 * @brief Hall Current 25 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLCURRENT25_OK = 0,
    HALLCURRENT25_ERROR = -1

} hallcurrent25_return_value_t;

/*!
 * @addtogroup hallcurrent25 Hall Current 25 Click Driver
 * @brief API for configuring and manipulating Hall Current 25 Click driver.
 * @{
 */

/**
 * @brief Hall Current 25 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent25_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent25_cfg_setup ( hallcurrent25_cfg_t *cfg );

/**
 * @brief Hall Current 25 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent25_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent25_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent25_init ( hallcurrent25_t *ctx, hallcurrent25_cfg_t *cfg );

/**
 * @brief Hall Current 25 read raw ADC value function.
 * @details This function reads raw ADC value of the selected input channel.
 * @param[in] ctx : Click context object.
 * See #hallcurrent25_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-VOUT, 1-VOC).
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent25_read_raw_adc ( hallcurrent25_t *ctx, uint8_t channel, uint16_t *raw_adc );

/**
 * @brief Hall Current 25 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level
 * of the selected input channel.
 * @param[in] ctx : Click context object.
 * See #hallcurrent25_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-VOUT, 1-VOC).
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t hallcurrent25_read_voltage ( hallcurrent25_t *ctx, uint8_t channel, float *voltage );

/**
 * @brief Hall Current 25 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level
 * of the selected input channel.
 * @param[in] ctx : Click context object.
 * See #hallcurrent25_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-VOUT, 1-VOC).
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t hallcurrent25_read_voltage_avg ( hallcurrent25_t *ctx, uint8_t channel, uint16_t num_conv, float *voltage_avg );

/**
 * @brief Hall Current 25 get FAULT pin function.
 * @details This function returns the overcurrent fault (FAULT) pin logic state.
 * @param[in] ctx : Click context object.
 * See #hallcurrent25_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t hallcurrent25_get_fault_pin ( hallcurrent25_t *ctx );

/**
 * @brief Hall Current 25 calib offset function.
 * @details This function calibrates the zero current offset value.
 * @param[in] ctx : Click context object.
 * See #hallcurrent25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when no current flows through the sensor.
 */
err_t hallcurrent25_calib_offset ( hallcurrent25_t *ctx );

/**
 * @brief Hall Current 25 calib resolution function.
 * @details This function calibrates the data resolution at a known load current.
 * @param[in] ctx : Click context object.
 * See #hallcurrent25_t object definition for detailed explanation.
 * @param[in] calib_current : The known load current used for calibrating data resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function should only be called when a known amount of load current flows through the sensor.
 */
err_t hallcurrent25_calib_resolution ( hallcurrent25_t *ctx, float calib_current );

/**
 * @brief Hall Current 25 read current function.
 * @details This function reads the input current level [A].
 * @param[in] ctx : Click context object.
 * See #hallcurrent25_t object definition for detailed explanation.
 * @param[out] current : Input current level [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on calibrated zero current offset and data resolution.
 * Refer to hallcurrent25_calib_offset and hallcurrent25_calib_resolution functions.
 */
err_t hallcurrent25_read_current ( hallcurrent25_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT25_H

/*! @} */ // hallcurrent25

// ------------------------------------------------------------------------ END
