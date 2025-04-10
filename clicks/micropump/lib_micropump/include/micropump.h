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
 * @file micropump.h
 * @brief This file contains API for Micro Pump Click Driver.
 */

#ifndef MICROPUMP_H
#define MICROPUMP_H

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
 * @addtogroup micropump Micro Pump Click Driver
 * @brief API for configuring and manipulating Micro Pump Click driver.
 * @{
 */

/**
 * @defgroup micropump_set Micro Pump Settings
 * @brief Settings of Micro Pump Click driver.
 */

/**
 * @addtogroup micropump_set
 * @{
 */

/**
 * @brief Micro Pump current calculation setting.
 * @details Specified setting for current calculation of Micro Pump Click driver.
 */
#define MICROPUMP_V_TO_MA               1.5

/**
 * @brief Micro Pump default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of Micro Pump Click driver.
 */
#define MICROPUMP_NUM_CONVERSIONS       200

/**
 * @brief Micro Pump timeout setting.
 * @details Specified setting for timeout of Micro Pump Click driver.
 */
#define MICROPUMP_TIMEOUT_MS            2000

/**
 * @brief Micro Pump motor control setting.
 * @details Specified setting for motor control of Micro Pump Click driver.
 */
#define MICROPUMP_MOTOR_COAST           0
#define MICROPUMP_MOTOR_FORWARD         1
#define MICROPUMP_MOTOR_REVERSE         2
#define MICROPUMP_MOTOR_BRAKE           3

/*! @} */ // micropump_set

/**
 * @defgroup micropump_map Micro Pump MikroBUS Map
 * @brief MikroBUS pin mapping of Micro Pump Click driver.
 */

/**
 * @addtogroup micropump_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Micro Pump Click to the selected MikroBUS.
 */
#define MICROPUMP_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // micropump_map
/*! @} */ // micropump

/**
 * @brief Micro Pump Click context object.
 * @details Context object definition of Micro Pump Click driver.
 */
typedef struct
{
    digital_out_t in2;      /**< Control pin 2. */
    digital_out_t in1;      /**< Control pin 1. */

    analog_in_t adc;        /**< ADC module object. */

    float zero_curr_offset; /**< Voltage offset for zero current (COAST mode). */

} micropump_t;

/**
 * @brief Micro Pump Click configuration object.
 * @details Configuration object definition of Micro Pump Click driver.
 */
typedef struct
{
    pin_name_t an;          /**< Analog pin descriptor. */
    pin_name_t in2;         /**< Control pin 2. */
    pin_name_t in1;         /**< Control pin 1. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} micropump_cfg_t;

/**
 * @brief Micro Pump Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MICROPUMP_OK = 0,
    MICROPUMP_ERROR = -1

} micropump_return_value_t;

/*!
 * @addtogroup micropump Micro Pump Click Driver
 * @brief API for configuring and manipulating Micro Pump Click driver.
 * @{
 */

/**
 * @brief Micro Pump configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #micropump_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void micropump_cfg_setup ( micropump_cfg_t *cfg );

/**
 * @brief Micro Pump initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #micropump_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #micropump_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t micropump_init ( micropump_t *ctx, micropump_cfg_t *cfg );

/**
 * @brief Micro Pump read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #micropump_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t micropump_read_adc_raw ( micropump_t *ctx, uint16_t *data_out );

/**
 * @brief Micro Pump read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #micropump_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t micropump_read_adc_voltage ( micropump_t *ctx, float *data_out );

/**
 * @brief Micro Pump read AN pin voltage level average function.
 * @details This function a desired number of ADC voltage samples and averages it.
 * @param[in] ctx : Click context object.
 * See #micropump_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t micropump_read_adc_voltage_avg ( micropump_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief Micro Pump set vref function.
 * @details This function sets the voltage reference for Micro Pump Click driver.
 * @param[in] ctx : Click context object.
 * See #micropump_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b micropump_init is 3.3V.
 */
err_t micropump_set_vref ( micropump_t *ctx, float vref );

/**
 * @brief Micro Pump set IN1 pin function.
 * @details This function sets the IN1 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #micropump_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micropump_set_in1_pin ( micropump_t *ctx );

/**
 * @brief Micro Pump clear IN1 pin function.
 * @details This function clears the IN1 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #micropump_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micropump_clear_in1_pin ( micropump_t *ctx );

/**
 * @brief Micro Pump set IN2 pin function.
 * @details This function sets the IN2 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #micropump_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micropump_set_in2_pin ( micropump_t *ctx );

/**
 * @brief Micro Pump clear IN2 pin function.
 * @details This function clears the IN2 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #micropump_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micropump_clear_in2_pin ( micropump_t *ctx );

/**
 * @brief Micro Pump drive motor function.
 * @details This function drives the micro pump motor in the selected state.
 * @param[in] ctx : Click context object.
 * See #micropump_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Coast,
 *                    @li @c 1 - Forward,
 *                    @li @c 2 - Reverse,
 *                    @li @c 3 - Brake.
 * @return None.
 * @note None.
 */
void micropump_drive_motor ( micropump_t *ctx, uint8_t state );

/**
 * @brief Micro Pump calib offset function.
 * @details This function calibrates the zero current offset value.
 * @param[in] ctx : Click context object.
 * See #micropump_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t micropump_calib_offset ( micropump_t *ctx );

/**
 * @brief Micro Pump get out current function.
 * @details This function reads the current output measurement in mA.
 * @param[in] ctx : Click context object.
 * See #micropump_t object definition for detailed explanation.
 * @param[out] current : Current output level [mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on calibrated zero current offset, see micropump_calib_offset function.
 */
err_t micropump_get_out_current ( micropump_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // MICROPUMP_H

/*! @} */ // micropump

// ------------------------------------------------------------------------ END
