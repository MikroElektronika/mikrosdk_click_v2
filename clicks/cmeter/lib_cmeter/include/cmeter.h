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
 * @file cmeter.h
 * @brief This file contains API for C Meter Click Driver.
 */

#ifndef CMETER_H
#define CMETER_H

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

/*!
 * @addtogroup cmeter C Meter Click Driver
 * @brief API for configuring and manipulating C Meter Click driver.
 * @{
 */

/**
 * @defgroup cmeter_set C Meter Settings
 * @brief Settings of C Meter Click driver.
 */

/**
 * @addtogroup cmeter_set
 * @{
 */

/**
 * @brief C Meter measurement setting.
 * @details Specified setting for measurement of C Meter Click driver.
 */
#define CMETER_REF_CAPACITANCE_NF       0.47
#define CMETER_GATE_PASSES              50000
#define CMETER_TIMEOUT_PASSES           10000000ul

/*! @} */ // cmeter_set

/**
 * @defgroup cmeter_map C Meter MikroBUS Map
 * @brief MikroBUS pin mapping of C Meter Click driver.
 */

/**
 * @addtogroup cmeter_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of C Meter Click to the selected MikroBUS.
 */
#define CMETER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.reset = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.out = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // cmeter_map
/*! @} */ // cmeter

/**
 * @brief C Meter Click context object.
 * @details Context object definition of C Meter Click driver.
 */
typedef struct
{
    digital_out_t reset;     /**< Reset pin (active low). */

    digital_in_t out;        /**< Oscillator output pin (square wave). */

    float zero_period;       /**< Oscillator period with open input in loop passes. */

} cmeter_t;

/**
 * @brief C Meter Click configuration object.
 * @details Configuration object definition of C Meter Click driver.
 */
typedef struct
{
    pin_name_t reset;        /**< Reset pin descriptor. */
    pin_name_t out;          /**< Oscillator output pin descriptor. */

} cmeter_cfg_t;

/**
 * @brief C Meter Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CMETER_OK = 0,
    CMETER_ERROR = -1

} cmeter_return_value_t;

/*!
 * @addtogroup cmeter C Meter Click Driver
 * @brief API for configuring and manipulating C Meter Click driver.
 * @{
 */

/**
 * @brief C Meter configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #cmeter_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void cmeter_cfg_setup ( cmeter_cfg_t *cfg );

/**
 * @brief C Meter initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #cmeter_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #cmeter_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cmeter_init ( cmeter_t *ctx, cmeter_cfg_t *cfg );

/**
 * @brief C Meter measure period function.
 * @details This function measures the average period of the oscillator output signal.
 * @param[out] ctx : Click context object.
 * See #cmeter_t object definition for detailed explanation.
 * @param[out] period : Average oscillator period in loop passes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cmeter_measure_period ( cmeter_t *ctx, float *period );

/**
 * @brief C Meter calibrate function.
 * @details This function measures the oscillator period with nothing connected
 * to the measurement input and stores it as the zero reference.
 * @param[out] ctx : Click context object.
 * See #cmeter_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The measurement input must be left open during the calibration.
 */
err_t cmeter_calibrate ( cmeter_t *ctx );

/**
 * @brief C Meter get capacitance function.
 * @details This function measures the oscillator period and calculates the capacitance 
 * connected to the measurement input relative to the zero reference.
 * @param[out] ctx : Click context object.
 * See #cmeter_t object definition for detailed explanation.
 * @param[out] capacitance : Measured capacitance in nF.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t cmeter_get_capacitance ( cmeter_t *ctx, float *capacitance );

#ifdef __cplusplus
}
#endif
#endif // CMETER_H

/*! @} */ // cmeter

// ------------------------------------------------------------------------ END
