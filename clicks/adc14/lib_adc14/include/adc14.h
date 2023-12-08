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
 * @file adc14.h
 * @brief This file contains API for ADC 14 Click Driver.
 */

#ifndef ADC14_H
#define ADC14_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup adc14 ADC 14 Click Driver
 * @brief API for configuring and manipulating ADC 14 Click driver.
 * @{
 */

/**
 * @defgroup adc14_set ADC 14 Registers Settings
 * @brief Settings for registers of ADC 14 Click driver.
 */

/**
 * @addtogroup adc14_set
 * @{
 */

/**
 * @brief ADC 14 default value of the internal voltage reference.
 * @details Specified setting for description of ADC 14 Click driver.
 */
#define ADC14_MEASURE_NUM           100
#define ADC14_RESOLUTION_12BIT      0x0FFFu
#define ADC14_RES_DIVIDER           4096.0f
#define ADC14_CONVERT_V_T_MV        1000.0f

/**
 * @brief ADC 14 default value of the internal voltage reference.
 * @details Default value of the internal voltage reference of ADC 14 Click driver.
 */
#define ADC14_INT_VREF_2_048V       2.048f

/**
 * @brief ADC 14 limits values of the external voltage reference.
 * @details Limits values of the external voltage reference of ADC 14 Click driver.
 */
#define ADC14_EXT_VREF_0V           0.0f
#define ADC14_EXT_VREF_3_3V         3.3f


/**
 * @brief ADC 14 description setting.
 * @details Specified setting for description of ADC 14 Click driver.
 */
#define ADC14_MEASURE_NUM           100

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adc14_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC14_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ADC14_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc14_set

/**
 * @defgroup adc14_map ADC 14 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 14 Click driver.
 */

/**
 * @addtogroup adc14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 14 Click to the selected MikroBUS.
 */
#define ADC14_MAP_MIKROBUS( cfg, mikrobus )         \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.shd  = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // adc14_map
/*! @} */ // adc14

/**
 * @brief ADC 14 Click context object.
 * @details Context object definition of ADC 14 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t shd;           /**< Shutdown Pin. */

    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    float vref;                  /**< Voltage reference. */

} adc14_t;

/**
 * @brief ADC 14 Click configuration object.
 * @details Configuration object definition of ADC 14 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t shd;             /**< Shutdown Pin. */

    // static variable
    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */
    
    float vref;    /**< Voltage reference. */

} adc14_cfg_t;

/**
 * @brief ADC 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC14_OK = 0,
    ADC14_ERROR = -1

} adc14_return_value_t;

/*!
 * @addtogroup adc14 ADC 14 Click Driver
 * @brief API for configuring and manipulating ADC 14 Click driver.
 * @{
 */

/**
 * @brief ADC 14 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc14_cfg_setup ( adc14_cfg_t *cfg );

/**
 * @brief ADC 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adc14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc14_init ( adc14_t *ctx, adc14_cfg_t *cfg );

/**
 * @brief ADC 14 device shutdown function.
 * @details This function is used for the device shutdown voltage reference
 * of the MCP1501, High-Precision Buffered Voltage Reference
 * on the ADC 14 Click board™.
 * @param[out] ctx : Click context object.
 * See #adc14_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void adc14_device_shutdown ( adc14_t *ctx );

/**
 * @brief ADC 14 device shutdown function.
 * @details This function is used for the device power up 
 * and enabled internal voltage reference [2.048V]
 * of the MCP1501, High-Precision Buffered Voltage Reference
 * on the ADC 14 Click board™.
 * @param[out] ctx : Click context object.
 * See #adc14_t object definition for detailed explanation.
 * @return Nothing.
 * @note Before using the Shutdown pin, the device should first be powered up. 
 * Once the device is fully powered up, the Shutdown pin can be used.
 */
void adc14_device_power_up ( adc14_t *ctx );

/**
 * @brief ADC 14 read conversion data function.
 * @details This function is used to reads 12-Bit ADC raw data value
 * of the MAX11108, Low-Power, Serial 12-Bit ADC
 * on the ADC 14 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc14_t object definition for detailed explanation.
 * @param[out] adc_data : 12-Bit ADC data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc14_read_conversion_data ( adc14_t *ctx, uint16_t *adc_data );

/**
 * @brief ADC 14 get voltage function.
 * @details This function reads results of 12-Bit ADC raw data 
 * and converts them to proportional voltage level [mV], 
 * of the MAX11108, Low-Power, Serial 12-Bit ADC
 * on the ADC 14 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc14_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc14_get_voltage ( adc14_t *ctx, float *voltage );

/**
 * @brief ADC 14 set voltage reference function.
 * @details This function sets external voltage reference
 * and converts them to proportional voltage level [mV], 
 * of the MAX11108, Low-Power, Serial 12-Bit ADC
 * on the ADC 14 Click board™.
 * @param[in] ctx : Click context object.
 * See #adc14_t object definition for detailed explanation.
 * @param[out] vref : External voltage reference [0-3.3V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc14_set_vref ( adc14_t *ctx, float vref );

#ifdef __cplusplus
}
#endif
#endif // ADC14_H

/*! @} */ // adc14

// ------------------------------------------------------------------------ END
