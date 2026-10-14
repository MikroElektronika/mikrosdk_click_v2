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
 * @file unihall3.h
 * @brief This file contains API for UNI Hall 3 Click Driver.
 */

#ifndef UNIHALL3_H
#define UNIHALL3_H

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
 * @addtogroup unihall3 UNI Hall 3 Click Driver
 * @brief API for configuring and manipulating UNI Hall 3 Click driver.
 * @{
 */

/**
 * @defgroup unihall3_set UNI Hall 3 Settings
 * @brief Settings of UNI Hall 3 Click driver.
 */

/**
 * @addtogroup unihall3_set
 * @{
 */

/**
 * @brief UNI Hall 3 calculation values setting.
 * @details Specified settings for calculation values of UNI Hall 3 Click driver.
 */
#define UNIHALL3_QVO_3V3           0.33
#define UNIHALL3_SENS_3V3          0.0047

/**
 * @brief UNI Hall 3 ADC setting.
 * @details Specified settings for ADC of UNI Hall 3 Click driver.
 */
#define UNIHALL3_VREF_3V3          3.3

/**
 * @brief UNI Hall 3 measurement setting.
 * @details Specified settings for measurement of UNI Hall 3 Click driver.
 */
#define UNIHALL3_NUM_CONV          100
#define UNIHALL3_TIMEOUT_MS        1000

/*! @} */ // unihall3_set

/**
 * @defgroup unihall3_map UNI Hall 3 MikroBUS Map
 * @brief MikroBUS pin mapping of UNI Hall 3 Click driver.
 */

/**
 * @addtogroup unihall3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UNI Hall 3 Click to the selected MikroBUS.
 */
#define UNIHALL3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // unihall3_map
/*! @} */ // unihall3

/**
 * @brief UNI Hall 3 Click context object.
 * @details Context object definition of UNI Hall 3 Click driver.
 */
typedef struct
{
    digital_out_t en;                   /**< Enable pin(active high). */

    analog_in_t adc;                    /**< ADC module object. */
    float       vref;                   /**< ADC reference voltage. */

} unihall3_t;

/**
 * @brief UNI Hall 3 Click configuration object.
 * @details Configuration object definition of UNI Hall 3 Click driver.
 */
typedef struct
{
    pin_name_t an;                      /**< Analog pin descriptor. */
    pin_name_t en;                      /**< Enable pin descriptor. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} unihall3_cfg_t;

/**
 * @brief UNI Hall 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    UNIHALL3_OK = 0,
    UNIHALL3_ERROR = -1

} unihall3_return_value_t;

/*!
 * @addtogroup unihall3 UNI Hall 3 Click Driver
 * @brief API for configuring and manipulating UNI Hall 3 Click driver.
 * @{
 */

/**
 * @brief UNI Hall 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #unihall3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void unihall3_cfg_setup ( unihall3_cfg_t *cfg );

/**
 * @brief UNI Hall 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #unihall3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #unihall3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t unihall3_init ( unihall3_t *ctx, unihall3_cfg_t *cfg );

/**
 * @brief UNI Hall 3 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #unihall3_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t unihall3_read_raw_adc ( unihall3_t *ctx, uint16_t *raw_adc );

/**
 * @brief UNI Hall 3 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #unihall3_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t unihall3_read_voltage ( unihall3_t *ctx, float *voltage );

/**
 * @brief UNI Hall 3 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #unihall3_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t unihall3_read_voltage_avg ( unihall3_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief UNI Hall 3 set vref function.
 * @details This function sets the voltage reference for UNI Hall 3 Click driver.
 * @param[in] ctx : Click context object.
 * See #unihall3_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b unihall3_init is defined in UNIHALL3_VREF.
 */
err_t unihall3_set_vref ( unihall3_t *ctx, float vref );

/**
 * @brief UNI Hall 3 read field function.
 * @details This function reads the magnetic flux density measured by 
 * the sensor, in Gauss.
 * @param[in] ctx : Click context object.
 * See #unihall3_t object definition for detailed explanation.
 * @param[out] field : Magnetic flux density [G].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Calculation is calibrated for the A31015KEWALT-47SN variant at 3.3 V
 * supply.
 */
err_t unihall3_read_field ( unihall3_t *ctx, float *field );

/**
 * @brief UNI Hall 3 enable device function.
 * @details This function enables the device by setting the EN pin
 * to high logic state.
 * @param[in] ctx : Click context object.
 * See #unihall3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void unihall3_enable_device ( unihall3_t *ctx );

/**
 * @brief UNI Hall 3 disable device function.
 * @details This function disables the device by setting the EN pin
 * to low logic state.
 * @param[in] ctx : Click context object.
 * See #unihall3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void unihall3_disable_device ( unihall3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // UNIHALL3_H

/*! @} */ // unihall3

// ------------------------------------------------------------------------ END
