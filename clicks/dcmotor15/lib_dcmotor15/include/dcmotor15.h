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
 * @file dcmotor15.h
 * @brief This file contains API for DC Motor 15 Click Driver.
 */

#ifndef DCMOTOR15_H
#define DCMOTOR15_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup dcmotor15 DC Motor 15 Click Driver
 * @brief API for configuring and manipulating DC Motor 15 Click driver.
 * @{
 */

/**
 * @brief DC Motor 15 IPROPI values.
 * @details Specified IPROPI values of DC Motor 15 Click driver.
 */
#define DCMOTOR15_RIPROP_OHM            1500
#define DCMOTOR15_AIPROP_AMP            0.000455

/**
 * @defgroup dcmotor15_map DC Motor 15 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 15 Click driver.
 */

/**
 * @addtogroup dcmotor15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 15 Click to the selected MikroBUS.
 */
#define DCMOTOR15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.ipr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dcmotor15_map
/*! @} */ // dcmotor15

/**
 * @brief DC Motor 15 Click context object.
 * @details Context object definition of DC Motor 15 Click driver.
 */
typedef struct
{
    digital_out_t  slp;     /**< Sleep mode pin. */
    digital_out_t  in2;     /**< H-Bridge control 2. */
    digital_out_t  in1;     /**< H-Bridge control 1. */

    digital_in_t  flt;      /**< Fault indicator. */

    analog_in_t  adc;       /**< ADC module object. */

} dcmotor15_t;

/**
 * @brief DC Motor 15 Click configuration object.
 * @details Configuration object definition of DC Motor 15 Click driver.
 */
typedef struct
{
    pin_name_t  ipr;         /**< Analog pin descriptor. */
    pin_name_t  slp;        /**< Sleep mode pin. */
    pin_name_t  in2;        /**< H-Bridge control 2. */
    pin_name_t  in1;        /**< H-Bridge control 1. */
    pin_name_t  flt;        /**< Fault indicator. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} dcmotor15_cfg_t;

/**
 * @brief DC Motor 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR15_OK = 0,
    DCMOTOR15_ERROR = -1

} dcmotor15_return_value_t;

/**
 * @brief DC Motor 15 Click pin state value data.
 * @details Predefined enum values for driver pin state values.
 */
typedef enum
{
    DCMOTOR15_LOW = 0,
    DCMOTOR15_HIGH = 1

} dcmotor15_pin_state_value_t;

/*!
 * @addtogroup dcmotor15 DC Motor 15 Click Driver
 * @brief API for configuring and manipulating DC Motor 15 Click driver.
 * @{
 */

/**
 * @brief DC Motor 15 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor15_cfg_setup ( dcmotor15_cfg_t *cfg );

/**
 * @brief DC Motor 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor15_init ( dcmotor15_t *ctx, dcmotor15_cfg_t *cfg );

/**
 * @brief DC Motor 15 default configuration function.
 * @details This function executes a default configuration of DC Motor 15
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor15_t object definition for detailed explanation.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void dcmotor15_default_cfg ( dcmotor15_t *ctx );

/**
 * @brief DC Motor 15 read IPR pin value function.
 * @details This function reads results of AD conversion of the IPR pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor15_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor15_read_an_pin_value ( dcmotor15_t *ctx, uint16_t *data_out );

/**
 * @brief DC Motor 15 read IPR pin voltage level function.
 * @details This function reads results of AD conversion of the IPR pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #dcmotor15_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t dcmotor15_read_an_pin_voltage ( dcmotor15_t *ctx, float *data_out );

/**
 * @brief DC Motor 15 set SLP pin state function.
 * @details This function sets the SLP pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #dcmotor15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void dcmotor15_set_slp_pin_state ( dcmotor15_t *ctx, uint8_t state );

/**
 * @brief DC Motor 15 set IN1 pin state function.
 * @details This function sets the IN1 pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #dcmotor15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void dcmotor15_set_in1_pin_state ( dcmotor15_t *ctx, uint8_t state );

/**
 * @brief DC Motor 15 set IN2 pin state function.
 * @details This function sets the IN2 pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #dcmotor15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void dcmotor15_set_in2_pin_state ( dcmotor15_t *ctx, uint8_t state );

/**
 * @brief DC Motor 15 get FLT pin state function.
 * @details This function returns the FLT pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t dcmotor15_fault_check ( dcmotor15_t *ctx );

/**
 * @brief DC Motor 15 drive forward function.
 * @details This function drives the motor forward.
 * @param[in] ctx : Click context object.
 * See #dcmotor15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor15_forward ( dcmotor15_t *ctx );

/**
 * @brief DC Motor 15 drive reverse function.
 * @details This function drives the motor in reverse.
 * @param[in] ctx : Click context object.
 * See #dcmotor15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor15_reverse ( dcmotor15_t *ctx );

/**
 * @brief DC Motor 15 brake function.
 * @details This function pulls the motor brake.
 * @param[in] ctx : Click context object.
 * See #dcmotor15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor15_brake ( dcmotor15_t *ctx );

/**
 * @brief DC Motor 15 stop function.
 * @details This function stops the motor, the click goes to sleep mode, the motor is disconnected.
 * @param[in] ctx : Click context object.
 * See #dcmotor15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor15_stop ( dcmotor15_t *ctx );

/**
 * @brief DC Motor 15 get current function.
 * @details This function reads the motor current consumption by performing analog to digital read of IPR pin.
 * @param[in] ctx : Click context object.
 * @param[in] num_of_conv : Number of ADC conversions to be performed.
 * See #dcmotor15_t object definition for detailed explanation.
 * @return Current value in Amps.
 * @note None.
 */
float dcmotor15_get_current ( dcmotor15_t *ctx, uint16_t num_of_conv );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR15_H

/*! @} */ // dcmotor15

// ------------------------------------------------------------------------ END
