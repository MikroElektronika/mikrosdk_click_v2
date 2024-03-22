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
 * @file adc24.h
 * @brief This file contains API for ADC 24 Click Driver.
 */

#ifndef ADC24_H
#define ADC24_H

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
 * @addtogroup adc24 ADC 24 Click Driver
 * @brief API for configuring and manipulating ADC 24 Click driver.
 * @{
 */

/**
 * @defgroup adc24_set ADC 24 Control Register Settings
 * @brief Settings for control register of ADC 24 Click driver.
 */

/**
 * @addtogroup adc24_set
 * @{
 */

/**
 * @brief ADC 24 control register setting.
 * @details Specified setting for control register of ADC 24 Click driver.
 */
#define ADC24_CTRL_SET_WRITE             0x0800u
#define ADC24_CTRL_SET_SEQ               0x0400u
#define ADC24_CTRL_SET_CH_0              0x0000u
#define ADC24_CTRL_SET_CH_1              0x0040u
#define ADC24_CTRL_SET_CH_2              0x0080u
#define ADC24_CTRL_SET_CH_3              0x00C0u
#define ADC24_CTRL_SET_CH_4              0x0100u
#define ADC24_CTRL_SET_CH_5              0x0140u
#define ADC24_CTRL_SET_CH_6              0x0180u
#define ADC24_CTRL_SET_CH_7              0x01C0u
#define ADC24_CTRL_SET_CH_8              0x0200u
#define ADC24_CTRL_SET_CH_9              0x0240u
#define ADC24_CTRL_SET_CH_10             0x0280u
#define ADC24_CTRL_SET_CH_11             0x02C0u
#define ADC24_CTRL_SET_CH_12             0x0300u
#define ADC24_CTRL_SET_CH_13             0x0340u
#define ADC24_CTRL_SET_CH_14             0x0380u
#define ADC24_CTRL_SET_CH_15             0x03C0u
#define ADC24_CTRL_SET_PM_NORMAL         0x0030u
#define ADC24_CTRL_SET_PM_FULL_SHDN      0x0020u
#define ADC24_CTRL_SET_PM_AUTO_SHDN      0x0010u
#define ADC24_CTRL_SET_PM_STANDBY        0x0000u
#define ADC24_CTRL_SET_SHADOW            0x0008u
#define ADC24_CTRL_SET_WEAK              0x0004u
#define ADC24_CTRL_SET_RANGE_5V          0x0000u
#define ADC24_CTRL_SET_RANGE_2_5V        0x0002u
#define ADC24_CTRL_SET_CODING_2C         0x0000u
#define ADC24_CTRL_SET_CODING_BIN        0x0001u

/**
 * @brief ADC 24 sequence selection setting.
 * @details Specified setting for sequence selection of ADC 24 Click driver.
 */
#define ADC24_SEQ_SHADOW_AN_INPUT        0
#define ADC24_SEQ_SHADOW_PROGRAMMING     1
#define ADC24_SEQ_SHADOW_ALTERED         2
#define ADC24_SEQ_SHADOW_ADDR_CONJ       3

/**
 * @brief ADC 24 channel selection setting.
 * @details Specified setting for channel selection of ADC 24 Click driver.
 */
#define ADC24_CH_SEL_IN_0                0
#define ADC24_CH_SEL_IN_1                1
#define ADC24_CH_SEL_IN_2                2
#define ADC24_CH_SEL_IN_3                3
#define ADC24_CH_SEL_IN_4                4
#define ADC24_CH_SEL_IN_5                5
#define ADC24_CH_SEL_IN_6                6
#define ADC24_CH_SEL_IN_7                7
#define ADC24_CH_SEL_IN_8                8
#define ADC24_CH_SEL_IN_9                9
#define ADC24_CH_SEL_IN_10               10
#define ADC24_CH_SEL_IN_11               11
#define ADC24_CH_SEL_IN_12               12
#define ADC24_CH_SEL_IN_13               13
#define ADC24_CH_SEL_IN_14               14
#define ADC24_CH_SEL_IN_15               15

/**
 * @brief ADC 24 power management selection setting.
 * @details Specified setting for power management selection of ADC 24 Click driver.
 */
#define ADC24_PM_STANDBY                 0
#define ADC24_PM_AUTO_SHDN               1
#define ADC24_PM_FULL_SHDN               2
#define ADC24_PM_NORMAL                  3

/**
 * @brief ADC 24 serial transfer setting.
 * @details Specified setting for end of the current serial transfer of ADC 24 Click driver.
 */
#define ADC24_WEAK_DOUT_THREE_STATE      0
#define ADC24_WEAK_DOUT_WEAKLY_DRIVEN    1

/**
 * @brief ADC 24 analog input range selection setting.
 * @details Specified setting for analog input range selection of ADC 24 Click driver.
 */
#define ADC24_RANGE_VREF_5V              0
#define ADC24_RANGE_VREF_2V5             1

/**
 * @brief ADC 24 selection of type of output coding.
 * @details Specified setting for selection of type of output coding of ADC 24 Click driver.
 */
#define ADC24_CODING_2C                  0
#define ADC24_CODING_BIN                 1

/**
 * @brief ADC 24 ADC resolution and voltage reference data value.
 * @details Specified setting for ADC resolution and voltage reference data of ADC 24 Click driver.
 */
#define ADC24_ADC_RESOLUTION             0x0FFF
#define ADC24_VREF_2V5                   2.5f
#define ADC24_VREF_5V                    5.0f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b adc24_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ADC24_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define ADC24_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // adc24_set

/**
 * @defgroup adc24_map ADC 24 MikroBUS Map
 * @brief MikroBUS pin mapping of ADC 24 Click driver.
 */

/**
 * @addtogroup adc24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ADC 24 Click to the selected MikroBUS.
 */
#define ADC24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // adc24_map
/*! @} */ // adc24

/**
 * @brief ADC 24 Click context object.
 * @details Context object definition of ADC 24 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} adc24_t;

/**
 * @brief ADC 24 Click configuration object.
 * @details Configuration object definition of ADC 24 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} adc24_cfg_t;

/**
 * @brief ADC 24 Click control object.
 * @details Control object definition of ADC 24 Click driver.
 */
typedef struct
{
    uint8_t ch_sel;        /**< Channel selection. */
    uint8_t pm;            /**< Power management selection. */
    uint8_t seq_shadow;    /**< Sequence type selection. */
    uint8_t weak;          /**< Serial transfer selection. */
    uint8_t range;         /**< Analog input range selection. */
    uint8_t coding;        /**< Type of output coding selection. */

} adc24_ctrl_t;

/**
 * @brief ADC 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ADC24_OK = 0,
    ADC24_ERROR = -1

} adc24_return_value_t;

/*!
 * @addtogroup adc24 ADC 24 Click Driver
 * @brief API for configuring and manipulating ADC 24 Click driver.
 * @{
 */

/**
 * @brief ADC 24 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #adc24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void adc24_cfg_setup ( adc24_cfg_t *cfg );

/**
 * @brief ADC 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #adc24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #adc24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc24_init ( adc24_t *ctx, adc24_cfg_t *cfg );

/**
 * @brief ADC 24 data writing function.
 * @details This function writes a desired control data by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc24_t object definition for detailed explanation.
 * @param[in] control : Control register bit mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc24_generic_write ( adc24_t *ctx, uint16_t control );

/**
 * @brief ADC 24 data reading function.
 * @details This function reads a output data by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc24_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc24_generic_read ( adc24_t *ctx, uint16_t *data_out );

/**
 * @brief ADC 24 get ADC data function.
 * @details This function reads a conversion result and selected channel by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc24_t object definition for detailed explanation.
 * @param[in] ctrl : Control register object.
 * See #adc24_ctrl_t object definition for detailed explanation.
 * @param[out] in_pos : Voltage input channel position [0-15].
 * @param[out] adc_data : 12-bit ADC raw data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc24_get_adc_data ( adc24_t *ctx, adc24_ctrl_t ctrl, uint8_t *in_pos, uint16_t *adc_data );

/**
 * @brief ADC 24 get voltage level function.
 * @details This function reads the results of 12-bit ADC raw data 
 * and converts them to proportional voltage levels by using the SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #adc24_t object definition for detailed explanation.
 * @param[in] ctrl : Control register object.
 * See #adc24_ctrl_t object definition for detailed explanation.
 * @param[out] in_pos : Voltage input channel position [0-15].
 * @param[out] voltage : Output voltage level [0-2.5] or [0-5.0].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t adc24_get_voltage ( adc24_t *ctx, adc24_ctrl_t ctrl, uint8_t *in_pos, float *voltage );

#ifdef __cplusplus
}
#endif
#endif // ADC24_H

/*! @} */ // adc24

// ------------------------------------------------------------------------ END
