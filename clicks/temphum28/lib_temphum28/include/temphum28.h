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
 * @file temphum28.h
 * @brief This file contains API for TempHum 28 Click Driver.
 */

#ifndef TEMPHUM28_H
#define TEMPHUM28_H

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
 * @addtogroup temphum28 TempHum 28 Click Driver
 * @brief API for configuring and manipulating TempHum 28 Click driver.
 * @{
 */

/**
 * @defgroup temphum28_set TempHum 28 Settings
 * @brief Settings of TempHum 28 Click driver.
 */

/**
 * @addtogroup temphum28_set
 * @{
 */

/**
 * @brief TempHum 28 input channel selection.
 * @details Specified input channel selection setting of TempHum 28 Click driver.
 */
#define TEMPHUM28_INPUT_CHANNEL_TEMP        0
#define TEMPHUM28_INPUT_CHANNEL_RH          1

/**
 * @brief TempHum 28 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of TempHum 28 Click driver.
 */
#define TEMPHUM28_NUM_CONVERSIONS           100

/**
 * @brief TempHum 28 ADC setting.
 * @details Specified settings for ADC of TempHum 28 Click driver.
 */
#define TEMPHUM28_ADC_RESOLUTION            0x0FFF
#define TEMPHUM28_VREF_3V3                  3.3
#define TEMPHUM28_VREF_5V                   5.0

/**
 * @brief TempHum 28 measurement setting.
 * @details Specified settings for measurement of TempHum 28 Click driver.
 */
#define TEMPHUM28_RH_OFFSET                 ( -12.5 )
#define TEMPHUM28_RH_RESOLUTION             125.0
#define TEMPHUM28_TEMP_OFFSET               ( -66.875 )
#define TEMPHUM28_TEMP_RESOLUTION           218.75

/**
 * @brief TempHum 28 timeout setting.
 * @details Specified setting for timeout of TempHum 28 Click driver.
 */
#define TEMPHUM28_TIMEOUT_MS                2000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b temphum28_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define TEMPHUM28_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define TEMPHUM28_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // temphum28_set

/**
 * @defgroup temphum28_map TempHum 28 MikroBUS Map
 * @brief MikroBUS pin mapping of TempHum 28 Click driver.
 */

/**
 * @addtogroup temphum28_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TempHum 28 Click to the selected MikroBUS.
 */
#define TEMPHUM28_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.hte  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rte  = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // temphum28_map
/*! @} */ // temphum28

/**
 * @brief TempHum 28 Click context object.
 * @details Context object definition of TempHum 28 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t hte;          /**< Heater enable pin (active high). */
    digital_out_t rte;          /**< Device enable pin (active high). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */
    float vref;                 /**< ADC reference voltage. */

} temphum28_t;

/**
 * @brief TempHum 28 Click configuration object.
 * @details Configuration object definition of TempHum 28 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t hte;             /**< Heater enable pin (active high). */
    pin_name_t rte;             /**< Device enable pin (active high). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    float vref;                 /**< ADC reference voltage. */

} temphum28_cfg_t;

/**
 * @brief TempHum 28 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPHUM28_OK = 0,
    TEMPHUM28_ERROR = -1

} temphum28_return_value_t;

/*!
 * @addtogroup temphum28 TempHum 28 Click Driver
 * @brief API for configuring and manipulating TempHum 28 Click driver.
 * @{
 */

/**
 * @brief TempHum 28 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #temphum28_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void temphum28_cfg_setup ( temphum28_cfg_t *cfg );

/**
 * @brief TempHum 28 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #temphum28_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #temphum28_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum28_init ( temphum28_t *ctx, temphum28_cfg_t *cfg );

/**
 * @brief TempHum 28 read raw ADC value function.
 * @details This function reads raw ADC value of the selected input channel.
 * @param[in] ctx : Click context object.
 * See #temphum28_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-TEMP, 1-RH).
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum28_read_raw_adc ( temphum28_t *ctx, uint8_t channel, uint16_t *raw_adc );

/**
 * @brief TempHum 28 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level
 * of the selected input channel.
 * @param[in] ctx : Click context object.
 * See #temphum28_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-TEMP, 1-RH).
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t temphum28_read_voltage ( temphum28_t *ctx, uint8_t channel, float *voltage );

/**
 * @brief TempHum 28 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level
 * of the selected input channel.
 * @param[in] ctx : Click context object.
 * See #temphum28_t object definition for detailed explanation.
 * @param[in] channel : Input channel selection (0-TEMP, 1-RH).
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t temphum28_read_voltage_avg ( temphum28_t *ctx, uint8_t channel, uint16_t num_conv, float *voltage_avg );

/**
 * @brief TempHum 28 set vref function.
 * @details This function sets the voltage reference for TempHum 28 Click driver.
 * @param[in] ctx : Click context object.
 * See #temphum28_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return None.
 * @note The default voltage reference set with @b temphum28_init is 3.3V.
 */
void temphum28_set_vref ( temphum28_t *ctx, float vref );

/**
 * @brief TempHum 28 heater enable function.
 * @details This function enables the internal heater by setting the heater enable pin
 * to a high logic level and applying the required stabilization delays.
 * @param[in] ctx : Click context object.
 * See #temphum28_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum28_heater_enable ( temphum28_t *ctx );

/**
 * @brief TempHum 28 heater disable function.
 * @details This function disables the internal heater by setting the heater enable pin
 * to a low logic level.
 * @param[in] ctx : Click context object.
 * See #temphum28_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum28_heater_disable ( temphum28_t *ctx );

/**
 * @brief TempHum 28 device enable function.
 * @details This function enables the device by setting the reset/enable pin
 * to a high logic level and applying the required startup delays.
 * @param[in] ctx : Click context object.
 * See #temphum28_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum28_device_enable ( temphum28_t *ctx );

/**
 * @brief TempHum 28 device disable function.
 * @details This function disables the device by setting the reset/enable pin
 * to a low logic level.
 * @param[in] ctx : Click context object.
 * See #temphum28_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum28_device_disable ( temphum28_t *ctx );

/**
 * @brief TempHum 28 read humidity function.
 * @details This function reads the averaged humidity sensor voltage and converts it
 * to relative humidity percentage using the reference voltage.
 * @param[in] ctx : Click context object.
 * See #temphum28_t object definition for detailed explanation.
 * @param[out] hum : Pointer to the output humidity value in percent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum28_read_humidity ( temphum28_t *ctx, float *hum );

/**
 * @brief TempHum 28 read temperature function.
 * @details This function reads the averaged temperature sensor voltage and converts it
 * to temperature value using the reference voltage.
 * @param[in] ctx : Click context object.
 * See #temphum28_t object definition for detailed explanation.
 * @param[out] temp : Pointer to the output temperature value in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum28_read_temperature ( temphum28_t *ctx, float *temp );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM28_H

/*! @} */ // temphum28

// ------------------------------------------------------------------------ END
