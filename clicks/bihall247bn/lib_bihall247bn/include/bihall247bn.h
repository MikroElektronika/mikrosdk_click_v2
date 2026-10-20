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
 * @file bihall247bn.h
 * @brief This file contains API for BI Hall 2 47BN Click Driver.
 */

#ifndef BIHALL247BN_H
#define BIHALL247BN_H

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
 * @addtogroup bihall247bn BI Hall 2 47BN Click Driver
 * @brief API for configuring and manipulating BI Hall 2 47BN Click driver.
 * @{
 */

/**
 * @defgroup bihall247bn_set BI Hall 2 47BN Settings
 * @brief Settings of BI Hall 2 47BN Click driver.
 */

/**
 * @addtogroup bihall247bn_set
 * @{
 */

/**
 * @brief BI Hall 2 47BN default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of BI Hall 2 47BN Click driver.
 */
#define BIHALL247BN_NUM_CONVERSIONS     200

/**
 * @brief BI Hall 2 47BN ADC setting.
 * @details Specified settings for ADC of BI Hall 2 47BN Click driver.
 */
#define BIHALL247BN_ADC_RESOLUTION      0x0FFF
#define BIHALL247BN_VREF_3V3            3.3
#define BIHALL247BN_VREF_5V             5.0
#define BIHALL247BN_VREF                BIHALL247BN_VREF_3V3

/**
 * @brief BI Hall 2 47BN timeout setting.
 * @details Specified settings for timeout of BI Hall 2 47BN Click driver.
 */
#define BIHALL247BN_TIMEOUT_MS          2000

/**
 * @brief BI Hall 2 47BN voltage to magnetic field strength setting.
 * @details Specified settings for voltage to magnetic field strength of BI Hall 2 47BN Click driver.
 */
#define BIHALL247BN_VOLTAGE_PER_GAUSS   0.0047

/*! @} */ // bihall247bn_set

/**
 * @defgroup bihall247bn_map BI Hall 2 47BN MikroBUS Map
 * @brief MikroBUS pin mapping of BI Hall 2 47BN Click driver.
 */

/**
 * @addtogroup bihall247bn_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BI Hall 2 47BN Click to the selected MikroBUS.
 */
#define BIHALL247BN_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // bihall247bn_map
/*! @} */ // bihall247bn

/**
 * @brief BI Hall 2 47BN Click context object.
 * @details Context object definition of BI Hall 2 47BN Click driver.
 */
typedef struct
{
    digital_out_t en;           /**< Device enable pin (active high). */

    analog_in_t adc;            /**< ADC module object. */
    float       vref;           /**< ADC reference voltage. */

} bihall247bn_t;

/**
 * @brief BI Hall 2 47BN Click configuration object.
 * @details Configuration object definition of BI Hall 2 47BN Click driver.
 */
typedef struct
{
    pin_name_t an;              /**< Analog pin descriptor. */
    pin_name_t en;              /**< Device enable pin (active high). */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} bihall247bn_cfg_t;

/**
 * @brief BI Hall 2 47BN Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BIHALL247BN_OK = 0,
    BIHALL247BN_ERROR = -1

} bihall247bn_return_value_t;

/*!
 * @addtogroup bihall247bn BI Hall 2 47BN Click Driver
 * @brief API for configuring and manipulating BI Hall 2 47BN Click driver.
 * @{
 */

/**
 * @brief BI Hall 2 47BN configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bihall247bn_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bihall247bn_cfg_setup ( bihall247bn_cfg_t *cfg );

/**
 * @brief BI Hall 2 47BN initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #bihall247bn_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bihall247bn_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bihall247bn_init ( bihall247bn_t *ctx, bihall247bn_cfg_t *cfg );

/**
 * @brief BI Hall 2 47BN read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #bihall247bn_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bihall247bn_read_raw_adc ( bihall247bn_t *ctx, uint16_t *raw_adc );

/**
 * @brief BI Hall 2 47BN read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #bihall247bn_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t bihall247bn_read_voltage ( bihall247bn_t *ctx, float *voltage );

/**
 * @brief BI Hall 2 47BN read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #bihall247bn_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t bihall247bn_read_voltage_avg ( bihall247bn_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief BI Hall 2 47BN set vref function.
 * @details This function sets the voltage reference for BI Hall 2 47BN Click driver.
 * @param[in] ctx : Click context object.
 * See #bihall247bn_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b bihall247bn_init is defined in BIHALL247BN_VREF.
 */
err_t bihall247bn_set_vref ( bihall247bn_t *ctx, float vref );

/**
 * @brief BI Hall 2 47BN enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #bihall247bn_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bihall247bn_enable_device ( bihall247bn_t *ctx );

/**
 * @brief BI Hall 2 47BN disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #bihall247bn_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bihall247bn_disable_device ( bihall247bn_t *ctx );

/**
 * @brief BI Hall 2 47BN get output function.
 * @details This function reads the OUT pin voltage level and calculates magnetic field strength in Gauss.
 * @param[in] ctx : Click context object.
 * See #bihall247bn_t object definition for detailed explanation.
 * @param[out] output : Magnetic field strength in Gauss.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t bihall247bn_get_output ( bihall247bn_t *ctx, float *output );

#ifdef __cplusplus
}
#endif
#endif // BIHALL247BN_H

/*! @} */ // bihall247bn

// ------------------------------------------------------------------------ END
