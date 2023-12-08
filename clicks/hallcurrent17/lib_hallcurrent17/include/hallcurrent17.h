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
 * @file hallcurrent17.h
 * @brief This file contains API for Hall Current 17 Click Driver.
 */

#ifndef HALLCURRENT17_H
#define HALLCURRENT17_H

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
 * @addtogroup hallcurrent17 Hall Current 17 Click Driver
 * @brief API for configuring and manipulating Hall Current 17 Click driver.
 * @{
 */

/**
 * @defgroup hallcurrent17_addr Hall Current 17 Registers List
 * @brief List of registers of Hall Current 17 Click driver.
 */

/**
 * @addtogroup hallcurrent17_addr
 * @{
 */

/**
 * @brief Hall Current 17 input channel address selection.
 * @details Specified input channel address selection of Hall Current 17 Click driver.
 */
#define HALLCURRENT17_ADDR_IN_CH_SEL_1          0x00
#define HALLCURRENT17_ADDR_IN_CH_SEL_2          0x08


/*! @} */ // hallcurrent17_addr

/**
 * @defgroup hallcurrent17_set Hall Current 17 Registers Settings
 * @brief Settings for registers of Hall Current 17 Click driver.
 */

/**
 * @addtogroup hallcurrent17_set
 * @{
 */

/**
 * @brief Hall Current 17 description setting.
 * @details Specified setting for description of Hall Current 17 Click driver.
 */
#define HALLCURRENT17_RESOLUTION_12BIT          0x0FFFu

/**
 * @brief Hall Current 17 voltage reference selection.
 * @details Specified voltage reference selection of Hall Current 17 Click driver.
 */
#define HALLCURRENT17_VREF_3V3                  3.3f
#define HALLCURRENT17_VREF_5V                   5.0f

/**
 * @brief Hall Current 17 resistance value (voltage divider calculation).
 * @details Specified resistance value of Hall Current 17 Click driver.
 */
#define HALLCURRENT17_RES_R5_R7_100_KOHM        100.0f
#define HALLCURRENT17_RES_R6_R8_100_KOHM        100.0f

/**
 * @brief Hall Current 17 data values to calculate.
 * @details Specified data values to calculate of Hall Current 17 Click driver.
 */
#define HALLCURRENT17_NUM_OF_MEASURE            1000u
#define HALLCURRENT17_CONV_V_TO_MV              1000.0f

/**
 * @brief Hall Current 17 sensitivity (mV/A) value.
 * @details Specified sensitivity value of Hall Current 17 Click driver.
 */
#define HALLCURRENT17_SENSITIVITY_MV_A          40.0f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b hallcurrent17_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define HALLCURRENT17_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define HALLCURRENT17_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // hallcurrent17_set

/**
 * @defgroup hallcurrent17_map Hall Current 17 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Current 17 Click driver.
 */

/**
 * @addtogroup hallcurrent17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Current 17 Click to the selected MikroBUS.
 */
#define HALLCURRENT17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // hallcurrent17_map
/*! @} */ // hallcurrent17

/**
 * @brief Hall Current 17 Click context object.
 * @details Context object definition of Hall Current 17 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    float  vref;                 /**< Voltage reference. */

} hallcurrent17_t;

/**
 * @brief Hall Current 17 Click configuration object.
 * @details Configuration object definition of Hall Current 17 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */

} hallcurrent17_cfg_t;

/**
 * @brief Hall Current 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLCURRENT17_OK = 0,
    HALLCURRENT17_ERROR = -1

} hallcurrent17_return_value_t;

/*!
 * @addtogroup hallcurrent17 Hall Current 17 Click Driver
 * @brief API for configuring and manipulating Hall Current 17 Click driver.
 * @{
 */

/**
 * @brief Hall Current 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallcurrent17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallcurrent17_cfg_setup ( hallcurrent17_cfg_t *cfg );

/**
 * @brief Hall Current 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hallcurrent17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallcurrent17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent17_init ( hallcurrent17_t *ctx, hallcurrent17_cfg_t *cfg );

/**
 * @brief Hall Current 17 default configuration function.
 * @details This function executes a default configuration of Hall Current 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #hallcurrent17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hallcurrent17_default_cfg ( hallcurrent17_t *ctx );

/**
 * @brief Hall Current 17 set voltage reference function.
 * @details This function sets the voltage reference
 * of the ADC122S101, 2 Channel, 500 ksps to 1 Msps 12-Bit A/D Converter
 * on the Hall Current 17 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent17_t object definition for detailed explanation.
 * @param[in] vref : Voltage reference.
 * @return Nothing.
 * @note None.
 */
void hallcurrent17_set_adc_vref ( hallcurrent17_t *ctx, float vref );

/**
 * @brief Hall Current 17 get voltage function.
 * @details This function reads raw ADC value and converts it to proportional voltage level
 * of the ADC122S101, 2 Channel, 500 ksps to 1 Msps 12-Bit A/D Converter
 * on the Hall Current 17 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent17_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent17_get_voltage ( hallcurrent17_t *ctx, float *voltage );

/**
 * @brief Hall Current 17 get Vref function.
 * @details This function reads raw ADC value of the inputs IN2 
 * and converts it to proportional voltage reference level
 * of the ACS37010LLZA-050B5, High Accuracy Current Sensor
 * on the Hall Current 17 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent17_t object definition for detailed explanation.
 * @param[out] adc_vref : Voltage reference level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent17_get_vref ( hallcurrent17_t *ctx, float *adc_vref );

/**
 * @brief Hall Current 17 get Vout function.
 * @details This function reads raw ADC value of the inputs IN1 
 * and converts it to proportional output voltage level
 * of the ACS37010LLZA-050B5, High Accuracy Current Sensor
 * on the Hall Current 17 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent17_t object definition for detailed explanation.
 * @param[out] adc_vout : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent17_get_vout ( hallcurrent17_t *ctx, float *adc_vout );

/**
 * @brief Hall Current 17 get current function.
 * @details This function reads and calculate input current value
 * of the ACS37010LLZA-050B5, High Accuracy Current Sensor
 * on the Hall Current 17 Click board™.
 * @param[in] ctx : Click context object.
 * See #hallcurrent17_t object definition for detailed explanation.
 * @param[out] current : Current [A].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallcurrent17_get_current ( hallcurrent17_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // HALLCURRENT17_H

/*! @} */ // hallcurrent17

// ------------------------------------------------------------------------ END
