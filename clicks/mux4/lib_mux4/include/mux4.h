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
 * @file mux4.h
 * @brief This file contains API for MUX 4 Click Driver.
 */

#ifndef MUX4_H
#define MUX4_H

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
 * @addtogroup mux4 MUX 4 Click Driver
 * @brief API for configuring and manipulating MUX 4 Click driver.
 * @{
 */

/**
 * @defgroup mux4_set MUX 4 setting.
 * @brief Specified settings for MUX 4 Click driver.
 */

/**
 * @addtogroup mux4_set
 * @{
 */

/**
 * @brief MUX 4 enable input flags.
 * @details Specified enable input flags of MUX 4 Click driver.
 */
#define MUX4_ENABLE_INPUT             0
#define MUX4_DISABLE_INPUT            1

/**
 * @brief MUX 4 select input flags.
 * @details Specified select input flags of MUX 4 Click driver.
 */
#define MUX4_SELECT_INPUT_1           1
#define MUX4_SELECT_INPUT_2           2
#define MUX4_SELECT_INPUT_3           3
#define MUX4_SELECT_INPUT_4           4
#define MUX4_SELECT_INPUT_5           5
#define MUX4_SELECT_INPUT_6           6
#define MUX4_SELECT_INPUT_7           7
#define MUX4_SELECT_INPUT_8           8

/*! @} */ // mux4_set

/**
 * @defgroup mux4_map MUX 4 MikroBUS Map
 * @brief MikroBUS pin mapping of MUX 4 Click driver.
 */

/**
 * @addtogroup mux4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MUX 4 Click to the selected MikroBUS.
 */
#define MUX4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.s2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.s0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.s1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // mux4_map
/*! @} */ // mux4

/**
 * @brief MUX 4 Click context object.
 * @details Context object definition of MUX 4 Click driver.
 */
typedef struct
{
    digital_out_t  s2;      /**< Select input bit 2. */
    digital_out_t  en;      /**< Enable input. */
    digital_out_t  s0;      /**< Select input bit 0. */
    digital_out_t  s1;      /**< Select input bit 1. */

    analog_in_t    adc;     /**< ADC module object. */

} mux4_t;

/**
 * @brief MUX 4 Click configuration object.
 * @details Configuration object definition of MUX 4 Click driver.
 */
typedef struct
{
    pin_name_t  an;         /**< Analog pin descriptor. */
    pin_name_t  s2;         /**< Select input bit 2. */
    pin_name_t  en;         /**< Enable input. */
    pin_name_t  s0;         /**< Select input bit 0. */
    pin_name_t  s1;         /**< Select input bit 1. */

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} mux4_cfg_t;

/**
 * @brief MUX 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MUX4_OK = 0,
    MUX4_ERROR = -1

} mux4_return_value_t;

/*!
 * @addtogroup mux4 MUX 4 Click Driver
 * @brief API for configuring and manipulating MUX 4 Click driver.
 * @{
 */

/**
 * @brief MUX 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mux4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mux4_cfg_setup ( mux4_cfg_t *cfg );

/**
 * @brief MUX 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #mux4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mux4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mux4_init ( mux4_t *ctx, mux4_cfg_t *cfg );

/**
 * @brief MUX 4 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #mux4_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mux4_read_an_pin_value ( mux4_t *ctx, uint16_t *data_out );

/**
 * @brief MUX 4 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #mux4_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t mux4_read_an_pin_voltage ( mux4_t *ctx, float *data_out );

/**
 * @brief MUX 4 enable input function.
 * @details This function enable or disables analog inputs.
 * @param[in] ctx : Click context object.
 * See #mux4_t object definition for detailed explanation.
 * @param[in] en_state : @li @c  0 - Enable inputs.
 *                       @li @c  1 - Disable inputs independed of S0 to S2 pin states.
 * @return None.
 * @note None.
 */
void mux4_enable_input ( mux4_t *ctx, uint8_t en_state );

/**
 * @brief MUX 4 select input function.
 * @details This function selects which input channel signal is being forwarded to the AN/EXT pin.
 * @param[in] ctx : Click context object.
 * See #mux4_t object definition for detailed explanation.
 * @param[in] input : Select input [1-8].
 * @return None.
 * @note None.
 */
void mux4_select_input ( mux4_t *ctx, uint8_t input );

#ifdef __cplusplus
}
#endif
#endif // MUX4_H

/*! @} */ // mux4

// ------------------------------------------------------------------------ END
