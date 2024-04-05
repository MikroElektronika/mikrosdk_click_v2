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
 * @file ecg5.h
 * @brief This file contains API for ECG 5 Click Driver.
 */

#ifndef ECG5_H
#define ECG5_H

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
 * @addtogroup ecg5 ECG 5 Click Driver
 * @brief API for configuring and manipulating ECG 5 Click driver.
 * @{
 */

/**
 * @defgroup ecg5_set ECG 5 Registers Settings
 * @brief Settings for registers of ECG 5 Click driver.
 */

/**
 * @addtogroup ecg5_set
 * @{
 */

/**
 * @brief ECG 5 description setting.
 * @details Specified setting for description of ECG 5 Click driver.
 */
#define ECG5_NORMAL_MODE                    0x01
#define ECG5_SHUTDOWN_MODE                  0x00

/*! @} */ // ecg5_set

/**
 * @defgroup ecg5_map ECG 5 MikroBUS Map
 * @brief MikroBUS pin mapping of ECG 5 Click driver.
 */

/**
 * @addtogroup ecg5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ECG 5 Click to the selected MikroBUS.
 */
#define ECG5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sdn = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.lon = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.lop = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ecg5_map
/*! @} */ // ecg5

/**
 * @brief ECG 5 Click context object.
 * @details Context object definition of ECG 5 Click driver.
 */
typedef struct
{
    digital_out_t  sdn;       /**< Chip Enable. */

    digital_in_t  lon;       /**< Lead-off detection for IN-. */
    digital_in_t  lop;       /**< Lead-off detection for IN+. */

    analog_in_t  adc;       /**< ADC module object. */

} ecg5_t;

/**
 * @brief ECG 5 Click configuration object.
 * @details Configuration object definition of ECG 5 Click driver.
 */
typedef struct
{
    pin_name_t  an;     /**< Analog pin descriptor. */
    pin_name_t  sdn;      /**< Chip Enable. */
    pin_name_t  lon;    /**< Lead-off detection for IN-. */
    pin_name_t  lop;    /**< Lead-off detection for IN+. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} ecg5_cfg_t;

/**
 * @brief ECG 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   ECG5_OK = 0,
   ECG5_ERROR = -1

} ecg5_return_value_t;

/*!
 * @addtogroup ecg5 ECG 5 Click Driver
 * @brief API for configuring and manipulating ECG 5 Click driver.
 * @{
 */

/**
 * @brief ECG 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ecg5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ecg5_cfg_setup ( ecg5_cfg_t *cfg );

/**
 * @brief ECG 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ecg5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ecg5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg5_init ( ecg5_t *ctx, ecg5_cfg_t *cfg );

/**
 * @brief ECG 5 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #ecg5_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg5_read_an_pin_value ( ecg5_t *ctx, uint16_t *data_out );

/**
 * @brief ECG 5 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #ecg5_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t ecg5_read_an_pin_voltage ( ecg5_t *ctx, float *data_out );

/**
 * @brief Mode Setting function.
 * @details Function performs a device mode setting.
 * @param[in] state : Mode of operation.
 * @param[out] ctx : Click context object.
 * See #ecg5_t object definition for detailed explanation.
 * @return Nothing.
 */
void ecg5_set_mode( ecg5_t *ctx, uint8_t state );

/**
 * @brief LOD- Checking function.
 * @details In DC Leads Off Detection Mode, LOD- is high when the electrode to -IN is disconnected, 
 * and it is low when connected. In AC Leads Off Detection Mode, LOD- is always low.
 * @param[in] ctx : Click context object.
 * See #ecg5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg5_check_lod_negative( ecg5_t *ctx );

/**
 * @brief LOD+ Checking function.
 * @details In DC Leads Off Detection Mode, LOD+ is high when the +IN electrode is disconnected,
 * and it is low when connected. In AC Leads Off Detection Mode, LOD+ is high when either the -IN 
 * or +IN electrode is disconnected, and it is low when both electrodes are connected.
 * @param[in] ctx : Click context object.
 * See #ecg5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ecg5_check_lod_positive( ecg5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ECG5_H

/*! @} */ // ecg5

// ------------------------------------------------------------------------ END
