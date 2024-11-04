/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file pressure13.h
 * @brief This file contains API for Pressure 13 Click Driver.
 */

#ifndef PRESSURE13_H
#define PRESSURE13_H

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
 * @addtogroup pressure13 Pressure 13 Click Driver
 * @brief API for configuring and manipulating Pressure 13 Click driver.
 * @{
 */

/**
 * @defgroup pressure13_set Pressure 13 Registers Settings
 * @brief Settings for registers of Pressure 13 Click driver.
 */

/**
 * @addtogroup pressure13_set
 * @{
 */

/**
 * @brief Pressure 13 description setting.
 * @details Specified setting for description of Pressure 13 Click driver.
 */
#define PRESSURE13_V_REF_2_048_mV                                 2.04800
#define PRESSURE13_V_REF_3_0_mV                                   3.00000
#define PRESSURE13_V_REF_3_3_mV                                   3.30000
#define PRESSURE13_V_REF_CALC_FACT                                0.86987

#define PRESSURE13_V_DD_3_3_mV                                    3.30000
#define PRESSURE13_V_DD_5_0_mV                                    5.00000

#define PRESSURE13_ADC_RES_10_BIT                                 1024.00
#define PRESSURE13_ADC_RES_12_BIT                                 4096.00
#define PRESSURE13_ADC_RES_14_BIT                                 16383.0

#define PRESSURE13_GAIN_AND_OFFSET_SYMBOL_A                       0.00293
#define PRESSURE13_GAIN_AND_OFFSET_SYMBOL_B                       0.05069

#define PRESSURE13_CONVERT_KPAS_TO_MBAR                           10.0000

/*! @} */ // pressure13_set

/**
 * @defgroup pressure13_map Pressure 13 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 13 Click driver.
 */

/**
 * @addtogroup pressure13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 13 Click to the selected MikroBUS.
 */
#define PRESSURE13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // pressure13_map
/*! @} */ // pressure13

/**
 * @brief Pressure 13 Click context object.
 * @details Context object definition of Pressure 13 Click driver.
 */
typedef struct
{
    analog_in_t  adc;       /**< ADC module object. */

} pressure13_t;

/**
 * @brief Pressure 13 Click configuration object.
 * @details Configuration object definition of Pressure 13 Click driver.
 */
typedef struct
{
    pin_name_t  an;     /**< Analog pin descriptor. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} pressure13_cfg_t;

/**
 * @brief Pressure 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   PRESSURE13_OK = 0,
   PRESSURE13_ERROR = -1

} pressure13_return_value_t;

/*!
 * @addtogroup pressure13 Pressure 13 Click Driver
 * @brief API for configuring and manipulating Pressure 13 Click driver.
 * @{
 */

/**
 * @brief Pressure 13 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure13_cfg_setup ( pressure13_cfg_t *cfg );

/**
 * @brief Pressure 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pressure13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t pressure13_init ( pressure13_t *ctx, pressure13_cfg_t *cfg );

/**
 * @brief Pressure 13 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #pressure13_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t pressure13_read_an_pin_value ( pressure13_t *ctx, uint16_t *data_out );

/**
 * @brief Pressure 13 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #pressure13_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t pressure13_read_an_pin_voltage ( pressure13_t *ctx, float *data_out );

/**
 * @brief Pressure 13 get pressure function.
 * @details This function reads voltage levels and converts them to proportional pressure in mBar.
 * @param[in] ctx : Click context object.
 * See #pressure13_t object definition for detailed explanation.
 * @param[out] data_out : Output pressure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t pressure13_get_pressure ( pressure13_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE13_H

/*! @} */ // pressure13

// ------------------------------------------------------------------------ END
