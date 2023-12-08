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
 * @file profet27a.h
 * @brief This file contains API for PROFET 2 7A Click Driver.
 */

#ifndef PROFET27A_H
#define PROFET27A_H

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
 * @addtogroup profet27a PROFET 2 7A Click Driver
 * @brief API for configuring and manipulating PROFET 2 7A Click driver.
 * @{
 */

/**
 * @defgroup profet27a_set PROFET 2 7A Registers Settings
 * @brief Settings for registers of PROFET 2 7A Click driver.
 */

/**
 * @addtogroup profet27a_set
 * @{
 */

/**
 * @brief PROFET mode settings.
 * @details Specified settings for mode of PROFET Click driver.
 */
#define PROFET27A_MODE_ON          1
#define PROFET27A_MODE_OFF         2
#define PROFET27A_DIAGNOSTIC_ON    3
#define PROFET27A_DIAGNOSTIC_OFF   4

/*! @} */ // profet27a_set

/**
 * @defgroup profet27a_map PROFET 2 7A MikroBUS Map
 * @brief MikroBUS pin mapping of PROFET 2 7A Click driver.
 */

/**
 * @addtogroup profet27a_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PROFET 2 7A Click to the selected MikroBUS.
 */
#define PROFET27A_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.dsl = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.den = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.in0 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // profet27a_map
/*! @} */ // profet27a

/**
 * @brief PROFET 2 7A Click context object.
 * @details Context object definition of PROFET 2 7A Click driver.
 */
typedef struct
{
    digital_out_t  dsl; /**< Diagnostic select. */
    digital_out_t  den; /**< Diagnostic enable. */
    digital_out_t  in1; /**< Channel 1 enable. */
    digital_out_t  in0; /**< Channel 0 enable. */

    analog_in_t  adc;   /**< ADC module object. */
    
    uint8_t mode;       /**< Device mode. */
    uint8_t channel;    /**< Device channel active. */
    uint16_t rsens;     /**< SENSE resistor. */
    uint16_t kilis;     /**< Current Sense. */

} profet27a_t;

/**
 * @brief PROFET 2 7A Click configuration object.
 * @details Configuration object definition of PROFET 2 7A Click driver.
 */
typedef struct
{
    pin_name_t  an;     /**< Analog pin descriptor. */
    pin_name_t  dsl;    /**< Diagnostic select. */
    pin_name_t  den;    /**< Diagnostic enable. */
    pin_name_t  in1;    /**< Channel 1 enable. */
    pin_name_t  in0;    /**< Channel 0 enable. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} profet27a_cfg_t;

/**
 * @brief PROFET 2 7A Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   PROFET27A_OK = 0,
   PROFET27A_ERROR = -1,
   PROFET27A_ERROR_CHANNEL = -2

} profet27a_return_value_t;

/**
 * @brief PROFET 2 7A channel select.
 * @details Specified setting for channel select of PROFET 2 7A Click driver.
 */
typedef enum
{
    PROFET27A_CHANNEL_0 = 0,
    PROFET27A_CHANNEL_1 = 1

} profet27a_channel_t;

/*!
 * @addtogroup profet27a PROFET 2 7A Click Driver
 * @brief API for configuring and manipulating PROFET 2 7A Click driver.
 * @{
 */

/**
 * @brief PROFET 2 7A configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #profet27a_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void profet27a_cfg_setup ( profet27a_cfg_t *cfg );

/**
 * @brief PROFET 2 7A initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #profet27a_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #profet27a_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t profet27a_init ( profet27a_t *ctx, profet27a_cfg_t *cfg );

/**
 * @brief PROFET 2 7A default configuration function.
 * @details This function executes a default configuration of PROFET 2 7A
 * click board.
 * @param[in] ctx : Click context object.
 * See #profet27a_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t profet27a_default_cfg ( profet27a_t *ctx );

/**
 * @brief Read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #profet27a_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t profet27a_read_an_pin_value ( profet27a_t *ctx, uint16_t *data_out );

/**
 * @brief Read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #profet27a_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t profet27a_read_an_pin_voltage ( profet27a_t *ctx, float *data_out );

/**
 * @brief Set diagnostic select pin state.
 * @details This function set @b dsl pin state.
 * @param[in] ctx : Click context object.
 * See #profet27a_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 * @return Nothing
 */
void profet27a_set_dsl ( profet27a_t *ctx, uint8_t state );

/**
 * @brief Set diagnostic enable pin state.
 * @details This function set @b den pin state.
 * @param[in] ctx : Click context object.
 * See #profet27a_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 * @return Nothing
 */
void profet27a_set_den ( profet27a_t *ctx, uint8_t state );

/**
 * @brief Set channel 1 enable pin state.
 * @details This function set @b in1 pin state.
 * @param[in] ctx : Click context object.
 * See #profet27a_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 * @return Nothing
 */
void profet27a_set_in1 ( profet27a_t *ctx, uint8_t state );

/**
 * @brief Set channel 0 enable pin state.
 * @details This function set @b in0 pin state.
 * @param[in] ctx : Click context object.
 * See #profet27a_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 * @return Nothing
 */
void profet27a_set_in0 ( profet27a_t *ctx, uint8_t state );

/**
 * @brief Set mode device mode for specific channel channel.
 * @details This function sets DEN, DSL INx pins state to set device 
 * in selected mode for selected channel.
 * @param[in] ctx : Click context object.
 * See #profet27a_t object definition for detailed explanation.
 * @param[in] channel : Channel to set.
 * @param[in] mode : Mode to set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Error Channel.
 *
 * See #err_t definition for detailed explanation.
 */
err_t profet27a_set_mode ( profet27a_t *ctx, profet27a_channel_t channel, uint8_t mode );

#ifdef __cplusplus
}
#endif
#endif // PROFET27A_H

/*! @} */ // profet27a

// ------------------------------------------------------------------------ END
