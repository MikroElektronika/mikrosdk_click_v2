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
 * @file lmeter.h
 * @brief This file contains API for L meter Click Driver.
 */

#ifndef LMETER_H
#define LMETER_H

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
 * @addtogroup lmeter L meter Click Driver
 * @brief API for configuring and manipulating L meter Click driver.
 * @{
 */

/**
 * @defgroup lmeter_set L meter Settings
 * @brief Settings of L meter Click driver.
 */

/**
 * @addtogroup lmeter_set
 * @{
 */

/**
 * @brief L meter measurement gate setting.
 * @details Specified setting for measurement window of L meter Click driver.
 */
#define LMETER_GATE_SAMPLES                 50000
#define LMETER_MIN_VALID_COUNT              100

/**
 * @brief L meter reference inductance setting.
 * @details Specified setting for reference inductance of L meter Click driver.
 */
#define LMETER_REF_INDUCTANCE_UH            100.0

/**
 * @brief L meter calibration capacitor setting.
 * @details Specified setting for calibration capacitor of L meter Click driver.
 */
#define LMETER_CAL_CAP_DISABLE              0
#define LMETER_CAL_CAP_ENABLE               1

/**
 * @brief L meter settling time setting.
 * @details Specified setting for settling time of L meter Click driver.
 */
#define LMETER_STARTUP_DELAY_MS             2000
#define LMETER_CAP_SETTLE_DELAY_MS          50

/*! @} */ // lmeter_set

/**
 * @defgroup lmeter_map L meter MikroBUS Map
 * @brief MikroBUS pin mapping of L meter Click driver.
 */

/**
 * @addtogroup lmeter_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of L meter Click to the selected MikroBUS.
 */
#define LMETER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.t_sw = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.f_out = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lmeter_map
/*! @} */ // lmeter

/**
 * @brief L meter Click context object.
 * @details Context object definition of L meter Click driver.
 */
typedef struct
{
    digital_out_t t_sw;       /**< Trigger switch pin. */

    digital_in_t f_out;       /**< Oscillator frequency output pin (square wave). */

    uint32_t zero_count;      /**< Edge count measured with the measurement input shorted, used as the zero reference. */

} lmeter_t;

/**
 * @brief L meter Click configuration object.
 * @details Configuration object definition of L meter Click driver.
 */
typedef struct
{
    pin_name_t t_sw;          /**< Trigger switch pin descriptor. */
    pin_name_t f_out;         /**< Oscillator frequency output pin descriptor. */

} lmeter_cfg_t;

/**
 * @brief L meter Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LMETER_OK = 0,
    LMETER_ERROR = -1

} lmeter_return_value_t;

/*!
 * @addtogroup lmeter L meter Click Driver
 * @brief API for configuring and manipulating L meter Click driver.
 * @{
 */

/**
 * @brief L meter configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lmeter_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lmeter_cfg_setup ( lmeter_cfg_t *cfg );

/**
 * @brief L meter initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lmeter_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lmeter_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lmeter_init ( lmeter_t *ctx, lmeter_cfg_t *cfg );

/**
 * @brief L meter set cal cap function.
 * @details This function connects or disconnects the on-board calibration capacitor C2
 * to the LC tank by setting the logic state of the T_SW pin.
 * @param[in] ctx : Click context object.
 * See #lmeter_t object definition for detailed explanation.
 * @param[in] state : Calibration capacitor state ( 0 - disconnected, 1 - connected ).
 * @return Nothing.
 * @note The function waits for the oscillator to settle after the capacitance step.
 */
void lmeter_set_cal_cap ( lmeter_t *ctx, uint8_t state );

/**
 * @brief L meter measure counts function.
 * @details This function counts the rising edges of the oscillator output signal
 * during a measurement gate of a fixed number of samples.
 * @param[in] ctx : Click context object.
 * See #lmeter_t object definition for detailed explanation.
 * @param[out] count : Number of rising edges counted during the gate.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lmeter_measure_counts ( lmeter_t *ctx, uint32_t *count );

/**
 * @brief L meter calibrate function.
 * @details This function measures and stores the zero reference count, which
 * corresponds to the LC tank loaded with the on-board coil L1 only.
 * @param[in] ctx : Click context object.
 * See #lmeter_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The measurement input must be shorted while this function is running.
 */
err_t lmeter_calibrate ( lmeter_t *ctx );

/**
 * @brief L meter get inductance function.
 * @details This function measures the oscillator output and calculates the inductance
 * of the connected coil in microhenries.
 * @param[in] ctx : Click context object.
 * See #lmeter_t object definition for detailed explanation.
 * @param[out] inductance : Coil inductance in uH.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The lmeter_calibrate function must be executed before this function.
 */
err_t lmeter_get_inductance ( lmeter_t *ctx, float *inductance );

#ifdef __cplusplus
}
#endif
#endif // LMETER_H

/*! @} */ // lmeter

// ------------------------------------------------------------------------ END
