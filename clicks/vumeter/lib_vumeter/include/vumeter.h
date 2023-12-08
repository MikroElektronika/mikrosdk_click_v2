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
 * @file vumeter.h
 * @brief This file contains API for VU Meter Click Driver.
 */

#ifndef VUMETER_H
#define VUMETER_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup vumeter VU Meter Click Driver
 * @brief API for configuring and manipulating VU Meter Click driver.
 * @{
 */

/**
 * @defgroup vumeter_set VU Meter Settings
 * @brief Settings of VU Meter Click driver.
 */

/**
 * @addtogroup vumeter_set
 * @{
 */

/**
 * @brief VU Meter gain level values.
 * @details Specified values for gain levels of VU Meter Click driver.
 */
#define VUMETER_GAIN_LEVEL_MAX              0xFF
#define VUMETER_GAIN_LEVEL_MID              0x80
#define VUMETER_GAIN_LEVEL_MIN              0x00

/**
 * @brief VU Meter VU level calculation constants.
 * @details Specified values for VU level calculation of VU Meter Click driver.
 */
#define VUMETER_DBU_VREF                    0.7746
#define VUMETER_DBU_TO_VU                   4.0
#define VUMETER_RMS_FOR_20VU                0.123
#define VUMETER_MIN_VU                      -20.0
#define VUMETER_VCC_3V3                     3.3
#define VUMETER_VCC_5V                      5.0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b vumeter_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define VUMETER_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define VUMETER_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // vumeter_set

/**
 * @defgroup vumeter_map VU Meter MikroBUS Map
 * @brief MikroBUS pin mapping of VU Meter Click driver.
 */

/**
 * @addtogroup vumeter_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of VU Meter Click to the selected MikroBUS.
 */
#define VUMETER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.an   = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // vumeter_map
/*! @} */ // vumeter

/**
 * @brief VU Meter Click context object.
 * @details Context object definition of VU Meter Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t    spi;            /**< SPI driver object. */
    analog_in_t     adc;            /**< ADC module object. */

    pin_name_t      chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} vumeter_t;

/**
 * @brief VU Meter Click configuration object.
 * @details Configuration object definition of VU Meter Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  an;             /**< Analog pin descriptor. */

    // static variable
    uint32_t                            spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                   spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t   cs_polarity;    /**< Chip select pin polarity. */
    
    analog_in_resolution_t              resolution;     /**< ADC resolution. */
    float                               vref;           /**< ADC reference voltage. */

} vumeter_cfg_t;

/**
 * @brief VU Meter Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    VUMETER_OK = 0,
    VUMETER_ERROR = -1

} vumeter_return_value_t;

/*!
 * @addtogroup vumeter VU Meter Click Driver
 * @brief API for configuring and manipulating VU Meter Click driver.
 * @{
 */

/**
 * @brief VU Meter configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vumeter_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vumeter_cfg_setup ( vumeter_cfg_t *cfg );

/**
 * @brief VU Meter initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #vumeter_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vumeter_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vumeter_init ( vumeter_t *ctx, vumeter_cfg_t *cfg );

/**
 * @brief VU Meter read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #vumeter_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vumeter_read_an_pin_value ( vumeter_t *ctx, uint16_t *data_out );

/**
 * @brief VU Meter read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #vumeter_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t vumeter_read_an_pin_voltage ( vumeter_t *ctx, float *data_out );

/**
 * @brief VU Meter set gain level function.
 * @details This function sets the input signal gain level (the microphone sensitivity).
 * @param[in] ctx : Click context object.
 * See #vumeter_t object definition for detailed explanation.
 * @param[in] gain_lvl : Gain level [0x00-0xFF].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vumeter_set_gain_level ( vumeter_t *ctx, uint8_t gain_lvl );

/**
 * @brief VU Meter calculate VU level function.
 * @details This function calculates VU level from the analog voltage input.
 * @param[in] ctx : Click context object.
 * See #vumeter_t object definition for detailed explanation.
 * @param[in] sample_rate_ms : Time in miliseconds for ADC samples ( ADC samples 10 times per milisecond ).
 * @return VU level value [-20.0,+3.0].
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
float vumeter_calculate_vu_level ( vumeter_t *ctx, uint16_t sample_rate_ms );

#ifdef __cplusplus
}
#endif
#endif // VUMETER_H

/*! @} */ // vumeter

// ------------------------------------------------------------------------ END
