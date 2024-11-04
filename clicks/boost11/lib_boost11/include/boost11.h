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
 * @file boost11.h
 * @brief This file contains API for Boost 11 Click Driver.
 */

#ifndef BOOST11_H
#define BOOST11_H

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
 * @addtogroup boost11 Boost 11 Click Driver
 * @brief API for configuring and manipulating Boost 11 Click driver.
 * @{
 */

/**
 * @defgroup boost11_reg Boost 11 Registers List
 * @brief List of registers of Boost 11 Click driver.
 */

/**
 * @defgroup boost11_set Boost 11 Registers Settings
 * @brief Settings for registers of Boost 11 Click driver.
 */

/**
 * @defgroup boost11_map Boost 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Boost 11 Click driver.
 */

/**
 * @addtogroup boost11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Boost 11 Click to the selected MikroBUS.
 */
#define BOOST11_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // boost11_map
/*! @} */ // boost11

/**
 * @brief Boost 11 Click context object.
 * @details Context object definition of Boost 11 Click driver.
 */
typedef struct
{
    digital_out_t en;    /**< Enable pin. */

    analog_in_t adc;     /**< ADC module object. */

    float vref;          /**< ADC reference voltage. */

} boost11_t;

/**
 * @brief Boost 11 Click configuration object.
 * @details Configuration object definition of Boost 11 Click driver.
 */
typedef struct
{
    pin_name_t an;    /**< Analog pin descriptor. */
    pin_name_t en;    /**< Enable pin. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} boost11_cfg_t;

/**
 * @brief Boost 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BOOST11_OK = 0,
    BOOST11_ERROR = -1

} boost11_return_value_t;

/*!
 * @addtogroup boost11 Boost 11 Click Driver
 * @brief API for configuring and manipulating Boost 11 Click driver.
 * @{
 */

/**
 * @brief Boost 11 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #boost11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void boost11_cfg_setup ( boost11_cfg_t *cfg );

/**
 * @brief Boost 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #boost11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #boost11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost11_init ( boost11_t *ctx, boost11_cfg_t *cfg );

/**
 * @brief Boost 11 enable function.
 * @details This function activates the boost operating mode.
 * @param[in] ctx : Click context object.
 * See #boost11_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void boost11_active_mode ( boost11_t *ctx );

/**
 * @brief Boost 11 disable function.
 * @details This function sets the standby operating mode.
 * @param[in] ctx : Click context object.
 * See #boost11_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void boost11_standby_mode ( boost11_t *ctx );

/**
 * @brief Boost 11 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #boost11_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost11_read_an_pin_value ( boost11_t *ctx, uint16_t *data_out );

/**
 * @brief Boost 11 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #boost11_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t boost11_read_an_pin_voltage ( boost11_t *ctx, float *data_out );

/**
 * @brief Boost 11 set vref function.
 * @details This function sets the voltage reference for Boost 11 Click driver.
 * @param[in] ctx : Click context object.
 * See #boost11_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b boost11_init is 3.3V.
 */
err_t boost11_set_vref ( boost11_t *ctx, float vref );

#ifdef __cplusplus
}
#endif
#endif // BOOST11_H

/*! @} */ // boost11

// ------------------------------------------------------------------------ END
