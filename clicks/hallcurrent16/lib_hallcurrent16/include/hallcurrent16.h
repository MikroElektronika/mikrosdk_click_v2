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
 * @file hallcurrent16.h
 * @brief This file contains API for Hall Current 16 Click Driver.
 */

#ifndef HALLCURRENT16_H
#define HALLCURRENT16_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup hallcurrent16 Hall Current 16 Click Driver
 * @brief API for configuring and manipulating Hall Current 16 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent16_set Hall Current 16 Registers Settings
 * @brief Settings for registers of Hall Current 16 Click driver.
 */

/**
 * @addtogroup hallcurrent16_set
 * @{
 */

/**
 * @brief Hall Current 16 input channel selection.
 * @details Specified input channel selection data values of Hall Current 16 Click driver.
 */
#define HALLCURRENT16_ADDR_IN_CH_SEL_1          0x00
#define HALLCURRENT16_ADDR_IN_CH_SEL_2          0x08

/**
 * @brief Hall Current 16 resolution and vref settings.
 * @details Specified resolution and vref data values of Hall Current 16 Click driver.
 */
#define HALLCURRENT16_RESOLUTION_12BIT          0x0FFFu
#define HALLCURRENT16_VREF_3V3                  3.3f
#define HALLCURRENT16_VREF_5V                   5.0f

/**
 * @brief Hall Current 16 sensitivity.
 * @details Specified sensitivity data values of Hall Current 16 Click driver.
 */
#define HALLCURRENT16_SENS_CALC_GAIN_0          26.4f
#define HALLCURRENT16_SENS_CALC_GAIN_1          33.0f
#define HALLCURRENT16_SENS_CALC_GAIN_2          39.6f
#define HALLCURRENT16_SENS_CALC_GAIN_3          19.8f

/**
 * @brief Hall Current 16 data values to calculate.
 * @details Specified data values to calculate of Hall Current 16 Click driver.
 */
#define HALLCURRENT16_ADC_NUM_OF_MEASURE        1000u
#define HALLCURRENT16_CONV_TO_MILI              1000.0f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hallcurrent16_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HALLCURRENT16_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define HALLCURRENT16_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hallcurrent16_set

/**
 * @defgroup hallcurrent16_map Hall Current 16 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 16 Click driver.
 */

/**
 * @addtogroup hallcurrent16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 16 Click to the selected MikroBUS.
 */
#define HALLCURRENT16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.ocf = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hallcurrent16_map
/*! @} */ // hallcurrent16

/**
 * @brief Hall Current 16 Click gain value data.
 * @details Predefined enum values for driver gain values.
 */
typedef enum
{
    HALLCURRENT16_GAIN_0 = 0,
    HALLCURRENT16_GAIN_1,
    HALLCURRENT16_GAIN_2,
    HALLCURRENT16_GAIN_3

} hallcurrent16_gain_t;

/**
 * @brief Hall Current 16 Click context object.
 * @details Context object definition of Hall Current 16 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t ocf;                /**< Overcurrent Fault pin. */

    // Modules
    spi_master_t spi;                /**< SPI driver object. */

    pin_name_t   chip_select;        /**< Chip select pin descriptor (used for SPI driver). */
    
    float                   vref;    /**< Voltage reference. */
    hallcurrent16_gain_t    gain;    /**< Gain Selection. */
    float                   sens;    /**< Sens Calculation value. */

} hallcurrent16_t;

/**
 * @brief Hall Current 16 Click configuration object.
 * @details Configuration object definition of Hall Current 16 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t ocf;    /**< Overcurrent Fault pin. */

    // static variable
    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */
    
    float                   vref;    /**< Voltage reference. */
    hallcurrent16_gain_t    gain;    /**< Gain Selection. */

} hallcurrent16_cfg_t;

/**
 * @brief Hall Current 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLCURRENT16_OK = 0,
    HALLCURRENT16_ERROR = -1

} hallcurrent16_return_value_t;

/*!
 * @addtogroup hallcurrent16 Hall Current 16 Click Driver
 * @brief API for configuring and manipulating Hall Current 16 Click driver.
 * @{
 */

/**
 * @brief Hall Current 16 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent16_cfg_setup ( hallcurrent16_cfg_t *cfg );

/**
 * @brief Hall Current 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent16_init ( hallcurrent16_t *ctx, hallcurrent16_cfg_t *cfg );

/**
 * @brief Hall Current 16 default configuration function.
 * @details This function executes a default configuration of Hall Current 16
 * click board.
 * @param[in] ctx : Click context object.
 * See #hallcurrent16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hallcurrent16_default_cfg ( hallcurrent16_t *ctx );

/**
 * @brief Hall Current 16 set vref function.
 * @details This function sets the voltage reference
 * of the ADC122S101, 2 Channel, 500 ksps to 1 Msps 12-Bit A/D Converter
 * on the Hall Current 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent16_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void hallcurrent16_set_vref ( hallcurrent16_t *ctx, float vref );

/**
 * @brief Hall Current 16 set sens function.
 * @details This function sets the sensitivity values 
 * for the calculation depending on the selected gain
 * of the ACS37002, 400 kHz, High Accuracy Current Sensor with Pin-Selectable Gains
 * on the Hall Current 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent16_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void hallcurrent16_set_sens ( hallcurrent16_t *ctx );

/**
 * @brief Hall Current 16 get voltage function.
 * @details This function reads raw ADC value and converts it to proportional voltage level
 * of the ADC122S101, 2 Channel, 500 ksps to 1 Msps 12-Bit A/D Converter
 * on the Hall Current 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent16_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent16_get_voltage ( hallcurrent16_t *ctx, float *voltage );

/**
 * @brief Hall Current 16 get vout function.
 * @details This function reads output voltage
 * of the ACS37002, 400 kHz, High Accuracy Current Sensor with Pin-Selectable Gains
 * on the Hall Current 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent16_t object definition for detailed explanation.
 * @param[out] adc_vout : ADC output voltage [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent16_get_vout ( hallcurrent16_t *ctx, float *adc_vout );

/**
 * @brief Hall Current 16 get vout function.
 * @details This function reads output voltage
 * of the ACS37002, 400 kHz, High Accuracy Current Sensor with Pin-Selectable Gains
 * on the Hall Current 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent16_t object definition for detailed explanation.
 * @param[out] adc_vref : ADC reference voltage [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent16_get_vref ( hallcurrent16_t *ctx, float *adc_vref );

/**
 * @brief Hall Current 16 get current function.
 * @details This function reads and calculate input current value
 * of the ACS37002, 400 kHz, High Accuracy Current Sensor with Pin-Selectable Gains
 * on the Hall Current 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent16_t object definition for detailed explanation.
 * @param[out] current : Current [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent16_get_current ( hallcurrent16_t *ctx, float *current );

/**
 * @brief Hall Current 16 get overcurrent fault function.
 * @details This function get states of the OCF ( Overcurrent Fault ) pin
 * of the ACS37002, 400 kHz, High Accuracy Current Sensor with Pin-Selectable Gains
 * on the Hall Current 16 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent16_t object definition for detailed explanation.
 * @return @li @c 0 - Overcurrent Fault state,
 *         @li @c 1 - OK state.
 * @note None.
 */
uint8_t hallcurrent16_get_ovc_fault ( hallcurrent16_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT16_H

/*! @} */ // hallcurrent16

// ------------------------------------------------------------------------ END
