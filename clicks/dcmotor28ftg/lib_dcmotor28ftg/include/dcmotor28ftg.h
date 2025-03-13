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
 * @file dcmotor28ftg.h
 * @brief This file contains API for DC Motor 28 FTG Click Driver.
 */

#ifndef DCMOTOR28FTG_H
#define DCMOTOR28FTG_H

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
 * @addtogroup dcmotor28ftg DC Motor 28 FTG Click Driver
 * @brief API for configuring and manipulating DC Motor 28 FTG Click driver.
 * @{
 */

/**
 * @defgroup dcmotor28ftg_set DC Motor 28 FTG Registers Settings
 * @brief Settings for registers of DC Motor 28 FTG Click driver.
 */

/**
 * @addtogroup dcmotor28ftg_set
 * @{
 */

/**
 * @brief DC Motor 28 FTG current calculation setting.
 * @details Specified setting for current calculation of DC Motor 28 FTG Click driver.
 */
#define DCMOTOR28FTG_RISENSE_V_TO_MA        1.0

/**
 * @brief DC Motor 28 FTG default ADC samples number for averaging.
 * @details Specified default ADC samples number for averaging of DC Motor 28 FTG Click driver.
 */
#define DCMOTOR28FTG_NUM_CONVERSIONS        200

/**
 * @brief DC Motor 28 FTG ADC setting.
 * @details Specified settings for ADC of DC Motor 28 FTG Click driver.
 */
#define DCMOTOR28FTG_VREF_3V3               3.3
#define DCMOTOR28FTG_VREF_5V                5.0
#define DCMOTOR28FTG_VREF_DEFAULT           DCMOTOR28FTG_VREF_3V3

/**
 * @brief DC Motor 28 FTG timeout setting.
 * @details Specified setting for timeout of DC Motor 28 FTG Click driver.
 */
#define DCMOTOR28FTG_TIMEOUT_MS             2000

/**
 * @brief DC Motor 28 FTG motor PWM control mode setting.
 * @details Specified setting for motor PWM control mode of DC Motor 28 FTG Click driver.
 */
#define DCMOTOR28FTG_MOTOR_COAST            0
#define DCMOTOR28FTG_MOTOR_FORWARD          1
#define DCMOTOR28FTG_MOTOR_REVERSE          2
#define DCMOTOR28FTG_MOTOR_BRAKE            3

/*! @} */ // dcmotor28ftg_set

/**
 * @defgroup dcmotor28ftg_map DC Motor 28 FTG MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 28 FTG Click driver.
 */

/**
 * @addtogroup dcmotor28ftg_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 28 FTG Click to the selected MikroBUS.
 */
#define DCMOTOR28FTG_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.isense = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sleep = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dcmotor28ftg_map
/*! @} */ // dcmotor28ftg

/**
 * @brief DC Motor 28 FTG Click context object.
 * @details Context object definition of DC Motor 28 FTG Click driver.
 */
typedef struct
{
    digital_out_t sleep;    /**< Sleep control pin (active low). */
    digital_out_t in1;      /**< H-Bridge control pin 1. */
    digital_out_t in2;      /**< H-Bridge control pin 2. */

    digital_in_t fault;     /**< Error detection pin. */

    analog_in_t adc;        /**< ADC module object. */

    float zero_curr_offset; /**< Voltage offset for zero current (COAST mode). */

} dcmotor28ftg_t;

/**
 * @brief DC Motor 28 FTG Click configuration object.
 * @details Configuration object definition of DC Motor 28 FTG Click driver.
 */
typedef struct
{
    pin_name_t isense;      /**< Current monitoring ADC pin. */
    pin_name_t sleep;       /**< Sleep control pin (active low). */
    pin_name_t in1;         /**< H-Bridge control pin 1. */
    pin_name_t in2;         /**< H-Bridge control pin 2. */
    pin_name_t fault;       /**< Error detection pin. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} dcmotor28ftg_cfg_t;

/**
 * @brief DC Motor 28 FTG Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR28FTG_OK = 0,
    DCMOTOR28FTG_ERROR = -1

} dcmotor28ftg_return_value_t;

/*!
 * @addtogroup dcmotor28ftg DC Motor 28 FTG Click Driver
 * @brief API for configuring and manipulating DC Motor 28 FTG Click driver.
 * @{
 */

/**
 * @brief DC Motor 28 FTG configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor28ftg_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor28ftg_cfg_setup ( dcmotor28ftg_cfg_t *cfg );

/**
 * @brief DC Motor 28 FTG initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor28ftg_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor28ftg_init ( dcmotor28ftg_t *ctx, dcmotor28ftg_cfg_t *cfg );

/**
 * @brief DC Motor 28 FTG read raw ISENSE ADC value function.
 * @details This function reads results of AD conversion of the ISENSE pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor28ftg_read_adc_raw ( dcmotor28ftg_t *ctx, uint16_t *data_out );

/**
 * @brief DC Motor 28 FTG read ISENSE pin voltage level function.
 * @details This function reads results of AD conversion of the ISENSE pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t dcmotor28ftg_read_adc_volt ( dcmotor28ftg_t *ctx, float *data_out );

/**
 * @brief DC Motor 28 FTG read ISENSE pin voltage level average function.
 * @details This function a desired number of ISENSE pin ADC voltage samples and averages it.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] volt_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t dcmotor28ftg_read_adc_volt_avg ( dcmotor28ftg_t *ctx, uint16_t num_conv, float *volt_avg );

/**
 * @brief DC Motor 28 FTG set vref function.
 * @details This function sets the ADC voltage reference for DC Motor 28 FTG Click driver.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b dcmotor28ftg_init is 3.3V.
 */
err_t dcmotor28ftg_set_adc_vref ( dcmotor28ftg_t *ctx, float vref );

/**
 * @brief DC Motor 28 FTG set IN1 pin function.
 * @details This function sets the IN1 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor28ftg_set_in1_pin ( dcmotor28ftg_t *ctx );

/**
 * @brief DC Motor 28 FTG clear IN1 pin function.
 * @details This function clears the IN1 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor28ftg_clear_in1_pin ( dcmotor28ftg_t *ctx );

/**
 * @brief DC Motor 28 FTG set IN2 pin function.
 * @details This function sets the IN2 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor28ftg_set_in2_pin ( dcmotor28ftg_t *ctx );

/**
 * @brief DC Motor 28 FTG clear IN2 pin function.
 * @details This function clears the IN2 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor28ftg_clear_in2_pin ( dcmotor28ftg_t *ctx );

/**
 * @brief DC Motor 28 FTG set SLEEP pin function.
 * @details This function sets the SLEEP pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor28ftg_set_sleep_pin ( dcmotor28ftg_t *ctx );

/**
 * @brief DC Motor 28 FTG clear SLEEP pin function.
 * @details This function clears the SLEEP pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor28ftg_clear_sleep_pin ( dcmotor28ftg_t *ctx );

/**
 * @brief DC Motor 28 FTG get FAULT pin function.
 * @details This function returns the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t dcmotor28ftg_get_fault_pin ( dcmotor28ftg_t *ctx );

/**
 * @brief DC Motor 28 FTG drive motor function.
 * @details This function drives the motor in the selected PWM control mode state.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Coast,
 *                    @li @c 1 - Forward,
 *                    @li @c 2 - Reverse,
 *                    @li @c 3 - Brake.
 * @return None.
 * @note This function is for the PMODE switch HIGH state setting only.
 */
void dcmotor28ftg_drive_motor ( dcmotor28ftg_t *ctx, uint8_t state );

/**
 * @brief DC Motor 28 FTG calib offset function.
 * @details This function calibrates the zero current offset value.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor28ftg_calib_offset ( dcmotor28ftg_t *ctx );

/**
 * @brief DC Motor 28 FTG get out current function.
 * @details This function reads the current output measurement in mA.
 * @param[in] ctx : Click context object.
 * See #dcmotor28ftg_t object definition for detailed explanation.
 * @param[out] current : Current output level [mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function relies on calibrated zero current offset, see dcmotor28ftg_calib_offset function.
 */
err_t dcmotor28ftg_get_out_current ( dcmotor28ftg_t *ctx, float *current );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR28FTG_H

/*! @} */ // dcmotor28ftg

// ------------------------------------------------------------------------ END
