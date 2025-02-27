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
 * @file boost5.h
 * @brief This file contains API for Boost 5 Click Driver.
 */

#ifndef BOOST5_H
#define BOOST5_H

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
 * @addtogroup boost5 Boost 5 Click Driver
 * @brief API for configuring and manipulating Boost 5 Click driver.
 * @{
 */

/**
 * @defgroup boost5_set Boost 5 Settings
 * @brief Settings of Boost 5 Click driver.
 */

/**
 * @addtogroup boost5_set
 * @{
 */

/**
 * @brief Boost 5 voltage calculation setting.
 * @details Specified setting for voltage calculation of Boost 5 Click driver.
 */
#define BOOST5_R15_KOHM                 200.0
#define BOOST5_R16_KOHM                 30.0
#define BOOST5_VOUT_MIN                 8.0
#define BOOST5_VOUT_MAX                 14.0
#define BOOST5_VOUT_OFFSET              1.0

/**
 * @brief Boost 5 default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Boost 5 Click driver.
 */
#define BOOST5_NUM_CONVERSIONS          200

/**
 * @brief Boost 5 ADC setting.
 * @details Specified settings for ADC of Boost 5 Click driver.
 */
#define BOOST5_VREF_3V3                 3.3
#define BOOST5_VREF_5V                  5.0
#define BOOST5_VREF_DEFAULT             BOOST5_VREF_3V3

/**
 * @brief Boost 5 timeout setting.
 * @details Specified setting for timeout of Boost 5 Click driver.
 */
#define BOOST5_TIMEOUT_MS               2000

/*! @} */ // boost5_set

/**
 * @defgroup boost5_map Boost 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Boost 5 Click driver.
 */

/**
 * @addtogroup boost5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Boost 5 Click to the selected MikroBUS.
 */
#define BOOST5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // boost5_map
/*! @} */ // boost5

/**
 * @brief Boost 5 Click context object.
 * @details Context object definition of Boost 5 Click driver.
 */
typedef struct
{
    digital_out_t en;       /**< Enable pin (active high). */

    analog_in_t adc;        /**< ADC module object. */

} boost5_t;

/**
 * @brief Boost 5 Click configuration object.
 * @details Configuration object definition of Boost 5 Click driver.
 */
typedef struct
{
    pin_name_t an;          /**< Analog pin descriptor. */
    pin_name_t en;          /**< Enable pin (active high). */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} boost5_cfg_t;

/**
 * @brief Boost 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BOOST5_OK = 0,
    BOOST5_ERROR = -1

} boost5_return_value_t;

/*!
 * @addtogroup boost5 Boost 5 Click Driver
 * @brief API for configuring and manipulating Boost 5 Click driver.
 * @{
 */

/**
 * @brief Boost 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #boost5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void boost5_cfg_setup ( boost5_cfg_t *cfg );

/**
 * @brief Boost 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #boost5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #boost5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost5_init ( boost5_t *ctx, boost5_cfg_t *cfg );

/**
 * @brief Boost 5 read raw AN pin ADC value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #boost5_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost5_read_adc_raw ( boost5_t *ctx, uint16_t *data_out );

/**
 * @brief Boost 5 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #boost5_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t boost5_read_adc_volt ( boost5_t *ctx, float *data_out );

/**
 * @brief Boost 5 read AN pin voltage level average function.
 * @details This function a desired number of AN pin ADC voltage samples and averages it.
 * @param[in] ctx : Click context object.
 * See #boost5_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] volt_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t boost5_read_adc_volt_avg ( boost5_t *ctx, uint16_t num_conv, float *volt_avg );

/**
 * @brief Boost 5 enable device function.
 * @details This function enables device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #boost5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void boost5_enable_device ( boost5_t *ctx );

/**
 * @brief Boost 5 disable device function.
 * @details This function disables device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #boost5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void boost5_disable_device ( boost5_t *ctx );

/**
 * @brief Boost 5 reset device function.
 * @details This function resets device by toggling the EN pin logic state.
 * @param[in] ctx : Click context object.
 * See #boost5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void boost5_reset_device ( boost5_t *ctx );

/**
 * @brief Boost 5 read VOUT function.
 * @details This function reads the boost output voltage level.
 * @param[in] ctx : Click context object.
 * See #dcmotor28fng_t object definition for detailed explanation.
 * @param[out] vout : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost5_read_vout ( boost5_t *ctx, float *vout );

#ifdef __cplusplus
}
#endif
#endif // BOOST5_H

/*! @} */ // boost5

// ------------------------------------------------------------------------ END
