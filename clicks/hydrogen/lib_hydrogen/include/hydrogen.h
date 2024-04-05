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
 * @file hydrogen.h
 * @brief This file contains API for Hydrogen Click Driver.
 */

#ifndef HYDROGEN_H
#define HYDROGEN_H

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

#include "drv_analog_in.h"

/*!
 * @addtogroup hydrogen Hydrogen Click Driver
 * @brief API for configuring and manipulating Hydrogen Click driver.
 * @{
 */

/**
 * @defgroup hydrogen_reg Hydrogen Registers List
 * @brief List of registers of Hydrogen Click driver.
 */

/**
 * @addtogroup hydrogen_reg
 * @{
 */

/**
 * @brief Hydrogen description register.
 * @details Specified register for description of Hydrogen Click driver.
 */
// TODO -- dodati makroe koji definisu adrese registara

/*! @} */ // hydrogen_reg

/**
 * @defgroup hydrogen_set Hydrogen Registers Settings
 * @brief Settings for registers of Hydrogen Click driver.
 */

/**
 * @addtogroup hydrogen_set
 * @{
 */

/**
 * @brief Hydrogen description setting.
 * @details Specified setting for description of Hydrogen Click driver.
 */
// TODO -- dodati makroe koji definisu komande/vrednosti koje se upisuju u registre

/*! @} */ // hydrogen_set

/**
 * @defgroup hydrogen_map Hydrogen MikroBUS Map
 * @brief MikroBUS pin mapping of Hydrogen Click driver.
 */

/**
 * @addtogroup hydrogen_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hydrogen Click to the selected MikroBUS.
 */
#define HYDROGEN_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \

/*! @} */ // hydrogen_map
/*! @} */ // hydrogen

/**
 * @brief Hydrogen Click context object.
 * @details Context object definition of Hydrogen Click driver.
 */
typedef struct
{
    analog_in_t  adc;       /**< ADC module object. */

} hydrogen_t;

/**
 * @brief Hydrogen Click configuration object.
 * @details Configuration object definition of Hydrogen Click driver.
 */
typedef struct
{
    pin_name_t  an;     /**< Analog pin descriptor. */

    // static variable 
    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} hydrogen_cfg_t;

/**
 * @brief Hydrogen Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   HYDROGEN_OK = 0,
   HYDROGEN_ERROR = -1

} hydrogen_return_value_t;

/*!
 * @addtogroup hydrogen Hydrogen Click Driver
 * @brief API for configuring and manipulating Hydrogen Click driver.
 * @{
 */

/**
 * @brief Hydrogen configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hydrogen_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hydrogen_cfg_setup ( hydrogen_cfg_t *cfg );

/**
 * @brief Hydrogen initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hydrogen_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hydrogen_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hydrogen_init ( hydrogen_t *ctx, hydrogen_cfg_t *cfg );

/**
 * @brief Hydrogen read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #hydrogen_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hydrogen_read_an_pin_value ( hydrogen_t *ctx, uint16_t *data_out );

/**
 * @brief Hydrogen read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #hydrogen_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t hydrogen_read_an_pin_voltage ( hydrogen_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // HYDROGEN_H

/*! @} */ // hydrogen

// ------------------------------------------------------------------------ END
