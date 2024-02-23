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
 * @file isoadc.h
 * @brief This file contains API for ISO ADC Click Driver.
 */

#ifndef ISOADC_H
#define ISOADC_H

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
 * @addtogroup isoadc ISO ADC Click Driver
 * @brief API for configuring and manipulating ISO ADC Click driver.
 * @{
 */

/**
 * @defgroup isoadc_set ISO ADC Settings
 * @brief Settings of ISO ADC Click driver.
 */

/**
 * @addtogroup isoadc_set
 * @{
 */

/**
 * @brief ISO ADC measurement setting.
 * @details Specified setting for measurement of ISO ADC Click driver.
 */
#define ISOADC_VEXT_MIN                 4.5f
#define ISOADC_VEXT_5V                  5.0f
#define ISOADC_VEXT_MAX                 5.5f
#define ISOADC_ADC_RESOLUTION           65535
#define ISOADC_ADC_FSR                  320
#define ISOADC_ADC_2FSR                 ( ISOADC_ADC_FSR * 2 )
#define ISOADC_ADC_NUM_AVERAGES         65535
#define ISOADC_VOLTAGE_NUM_AVERAGES     10
#define ISOADC_TIMEOUT_COUNT            1000
#define ISOADC_VOLTAGE_TO_CURRENT       0.1f
#define ISOADC_MILLI_TO_ONE             1000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b isoadc_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ISOADC_SET_DATA_SAMPLE_EDGE     SET_SPI_DATA_SAMPLE_EDGE
#define ISOADC_SET_DATA_SAMPLE_MIDDLE   SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // isoadc_set

/**
 * @defgroup isoadc_map ISO ADC MikroBUS Map
 * @brief MikroBUS pin mapping of ISO ADC Click driver.
 */

/**
 * @addtogroup isoadc_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISO ADC Click to the selected MikroBUS.
 */
#define ISOADC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );

/*! @} */ // isoadc_map
/*! @} */ // isoadc

/**
 * @brief ISO ADC Click context object.
 * @details Context object definition of ISO ADC Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    float vext;                     /**< Vext setting, 5V by default. */

} isoadc_t;

/**
 * @brief ISO ADC Click configuration object.
 * @details Configuration object definition of ISO ADC Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */

    // static variable
    uint32_t            spi_speed;  /**< SPI serial speed. */
    spi_master_mode_t   spi_mode;   /**< SPI master mode. */

} isoadc_cfg_t;

/**
 * @brief ISO ADC Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ISOADC_OK = 0,
    ISOADC_ERROR = -1

} isoadc_return_value_t;

/*!
 * @addtogroup isoadc ISO ADC Click Driver
 * @brief API for configuring and manipulating ISO ADC Click driver.
 * @{
 */

/**
 * @brief ISO ADC configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #isoadc_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void isoadc_cfg_setup ( isoadc_cfg_t *cfg );

/**
 * @brief ISO ADC initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #isoadc_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #isoadc_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc_init ( isoadc_t *ctx, isoadc_cfg_t *cfg );

/**
 * @brief ISO ADC read raw ADC function.
 * @details This function reads a raw 16-bit ADC value by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc_t object definition for detailed explanation.
 * @param[out] data_out : 16-bit ADC raw value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc_read_raw_adc ( isoadc_t *ctx, uint16_t *data_out );

/**
 * @brief ISO ADC set vext function.
 * @details This function sets the external voltage reference (5V by default).
 * @param[in] ctx : Click context object.
 * See #isoadc_t object definition for detailed explanation.
 * @param[in] vext : Voltage reference to be set (4.5V to 5.5V).
 * @return None.
 * @note None.
 */
void isoadc_set_vext ( isoadc_t *ctx, float vext );

/**
 * @brief ISO ADC read voltage function.
 * @details This function reads a raw ADC in ISOADC_ADC_NUM_AVERAGES number of samples and converts
 * it to a shunt voltage in millivolts.
 * @param[in] ctx : Click context object.
 * See #isoadc_t object definition for detailed explanation.
 * @param[out] voltage : Voltage on a shunt resistor in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc_read_voltage ( isoadc_t *ctx, float *voltage );

/**
 * @brief ISO ADC get current function.
 * @details This function converts a shunt voltage input to a load current in milliampers.
 * @param[in] voltage : Voltage on a shunt resistor in millivolts.
 * @return Load current in milliampers.
 * @note None.
 */
float isoadc_get_current ( float voltage );

/**
 * @brief ISO ADC get power function.
 * @details This function converts a shunt voltage input to electrical power in watts.
 * @param[in] ctx : Click context object.
 * See #isoadc_t object definition for detailed explanation.
 * @param[in] voltage : Voltage on a shunt resistor in millivolts.
 * @return Electrical power in watts.
 * @note None.
 */
float isoadc_get_power ( isoadc_t *ctx, float voltage );

#ifdef __cplusplus
}
#endif
#endif // ISOADC_H

/*! @} */ // isoadc

// ------------------------------------------------------------------------ END
