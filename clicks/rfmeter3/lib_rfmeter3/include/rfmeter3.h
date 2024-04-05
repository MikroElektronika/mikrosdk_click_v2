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
 * @file rfmeter3.h
 * @brief This file contains API for RF Meter 3 Click Driver.
 */

#ifndef RFMETER3_H
#define RFMETER3_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup rfmeter3 RF Meter 3 Click Driver
 * @brief API for configuring and manipulating RF Meter 3 Click driver.
 * @{
 */

/**
 * @defgroup rfmeter3_set RF Meter 3 Registers Settings
 * @brief Settings for registers of RF Meter 3 Click driver.
 */

/**
 * @addtogroup rfmeter3_set
 * @{
 */

/**
 * @brief RF Meter 3 description setting.
 * @details Specified setting for description of RF Meter 3 Click driver.
 */
#define RFMETER3_NO_SIGNAL_VOLTAGE      0.180
#define RFMETER3_OUTPUT_SLOPE           0.031
#define RFMETER3_DBM_OFFSET             40

/*! @} */ // rfmeter3_set

/**
 * @defgroup rfmeter3_map RF Meter 3 MikroBUS Map
 * @brief MikroBUS pin mapping of RF Meter 3 Click driver.
 */

/**
 * @addtogroup rfmeter3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RF Meter 3 Click to the selected MikroBUS.
 */
#define RFMETER3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // rfmeter3_map
/*! @} */ // rfmeter3

/**
 * @brief RF Meter 3 Click context object.
 * @details Context object definition of RF Meter 3 Click driver.
 */
typedef struct
{
    digital_out_t  en;      /**< Chip Enable. */

    analog_in_t    adc;     /**< ADC module object. */

} rfmeter3_t;

/**
 * @brief RF Meter 3 Click configuration object.
 * @details Configuration object definition of RF Meter 3 Click driver.
 */
typedef struct
{
    pin_name_t  an;     /**< Analog pin descriptor. */
    pin_name_t  en;     /**< Chip Enable. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} rfmeter3_cfg_t;

/**
 * @brief RF Meter 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RFMETER3_OK = 0,
    RFMETER3_ERROR = -1

} rfmeter3_return_value_t;

/*!
 * @addtogroup rfmeter3 RF Meter 3 Click Driver
 * @brief API for configuring and manipulating RF Meter 3 Click driver.
 * @{
 */

/**
 * @brief RF Meter 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rfmeter3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rfmeter3_cfg_setup ( rfmeter3_cfg_t *cfg );

/**
 * @brief RF Meter 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rfmeter3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rfmeter3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfmeter3_init ( rfmeter3_t *ctx, rfmeter3_cfg_t *cfg );

/**
 * @brief RF Meter 3 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #rfmeter3_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rfmeter3_read_an_pin_value ( rfmeter3_t *ctx, uint16_t *data_out );

/**
 * @brief RF Meter 3 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #rfmeter3_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t rfmeter3_read_an_pin_voltage ( rfmeter3_t *ctx, float *data_out );

/**
 * @brief RF Meter 3 enable device function.
 * @details This function enables device by setting EN pin to HIGH logic level.
 * @param[in] ctx : Click context object.
 * See #rfmeter3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rfmeter3_enable_device ( rfmeter3_t *ctx );

/**
 * @brief RF Meter 3 disable device function.
 * @details This function disables device by setting EN pin to LOW logic level.
 * @param[in] ctx : Click context object.
 * See #rfmeter3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rfmeter3_disable_device ( rfmeter3_t *ctx );

/**
 * @brief RF Meter 3 get rf input power function.
 * @details This function reads the voltage from AN pin and converts it to
 * RF input power in dBm.
 * @param[in] ctx : Click context object.
 * See #rfmeter3_t object definition for detailed explanation.
 * @param[out] data_out : RF Input Power [dBm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t rfmeter3_get_rf_input_power ( rfmeter3_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // RFMETER3_H

/*! @} */ // rfmeter3

// ------------------------------------------------------------------------ END
