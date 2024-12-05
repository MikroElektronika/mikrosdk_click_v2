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
 * @file tempiso.h
 * @brief This file contains API for Temp ISO Click Driver.
 */

#ifndef TEMPISO_H
#define TEMPISO_H

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
 * @addtogroup tempiso Temp ISO Click Driver
 * @brief API for configuring and manipulating Temp ISO Click driver.
 * @{
 */

/**
 * @defgroup tempiso_set Temp ISO Registers Settings
 * @brief Settings for registers of Temp ISO Click driver.
 */

/**
 * @addtogroup tempiso_set
 * @{
 */

/**
 * @brief Temp ISO default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Temp ISO Click driver.
 */
#define TEMPISO_NUM_CONVERSIONS         100

/**
 * @brief Temp ISO ADC setting.
 * @details Specified settings for ADC of Temp ISO Click driver.
 */
#define TEMPISO_VREF_3V3                3.3
#define TEMPISO_VREF_5V                 5.0

/**
 * @brief Temp ISO timeout setting.
 * @details Specified setting for timeout of Temp ISO Click driver.
 */
#define TEMPISO_TIMEOUT_MS              2000

/**
 * @brief Temp ISO temperature calculation setting.
 * @details Specified setting for temperature calculation of Temp ISO Click driver.
 */
#define TEMPISO_TEMP_SENS_V_PER_C       0.01f
#define TEMPISO_TEMP_ZERO_OFFSET_V      0.5f

/*! @} */ // tempiso_set

/**
 * @defgroup tempiso_map Temp ISO MikroBUS Map
 * @brief MikroBUS pin mapping of Temp ISO Click driver.
 */

/**
 * @addtogroup tempiso_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Temp ISO Click to the selected MikroBUS.
 */
#define TEMPISO_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // tempiso_map
/*! @} */ // tempiso

/**
 * @brief Temp ISO Click context object.
 * @details Context object definition of Temp ISO Click driver.
 */
typedef struct
{
    analog_in_t adc;        /**< ADC module object. */

} tempiso_t;

/**
 * @brief Temp ISO Click configuration object.
 * @details Configuration object definition of Temp ISO Click driver.
 */
typedef struct
{
    pin_name_t an;          /**< Analog pin descriptor. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} tempiso_cfg_t;

/**
 * @brief Temp ISO Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPISO_OK = 0,
    TEMPISO_ERROR = -1

} tempiso_return_value_t;

/*!
 * @addtogroup tempiso Temp ISO Click Driver
 * @brief API for configuring and manipulating Temp ISO Click driver.
 * @{
 */

/**
 * @brief Temp ISO configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tempiso_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tempiso_cfg_setup ( tempiso_cfg_t *cfg );

/**
 * @brief Temp ISO initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #tempiso_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tempiso_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempiso_init ( tempiso_t *ctx, tempiso_cfg_t *cfg );

/**
 * @brief Temp ISO read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #tempiso_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempiso_read_raw_adc ( tempiso_t *ctx, uint16_t *raw_adc );

/**
 * @brief Temp ISO read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #tempiso_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t tempiso_read_voltage ( tempiso_t *ctx, float *voltage );

/**
 * @brief Temp ISO read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #tempiso_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t tempiso_read_voltage_avg ( tempiso_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief Temp ISO set vref function.
 * @details This function sets the voltage reference for Temp ISO Click driver.
 * @param[in] ctx : Click context object.
 * See #tempiso_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b tempiso_init is 3.3V.
 */
err_t tempiso_set_vref ( tempiso_t *ctx, float vref );

/**
 * @brief Temp ISO read temperature function.
 * @details This function reads the voltage level from AN pin and
 * converts it to temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #tempiso_t object definition for detailed explanation.
 * @param[out] data_out : Temperature measurement [degC].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tempiso_read_temperature ( tempiso_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // TEMPISO_H

/*! @} */ // tempiso

// ------------------------------------------------------------------------ END
