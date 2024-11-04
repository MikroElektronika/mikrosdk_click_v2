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
 * @file audioamp12.h
 * @brief This file contains API for AudioAMP 12 Click Driver.
 */

#ifndef AUDIOAMP12_H
#define AUDIOAMP12_H

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

/*!
 * @addtogroup audioamp12 AudioAMP 12 Click Driver
 * @brief API for configuring and manipulating AudioAMP 12 Click driver.
 * @{
 */

/**
 * @defgroup audioamp12_map AudioAMP 12 MikroBUS Map
 * @brief MikroBUS pin mapping of AudioAMP 12 Click driver.
 */

/**
 * @addtogroup audioamp12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of AudioAMP 12 Click to the selected MikroBUS.
 */
#define AUDIOAMP12_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gs = MIKROBUS( mikrobus, MIKROBUS_PWM ) 

/*! @} */ // audioamp12_map
/*! @} */ // audioamp12

/**
 * @brief AudioAMP 12 Click context object.
 * @details Context object definition of AudioAMP 12 Click driver.
 */
typedef struct
{
    digital_out_t stb;    /**< Standby pin. */
    digital_out_t gs;     /**< Gain select pin. */

} audioamp12_t;

/**
 * @brief AudioAMP 12 Click configuration object.
 * @details Configuration object definition of AudioAMP 12 Click driver.
 */
typedef struct
{
    pin_name_t stb;    /**< Standby pin. */
    pin_name_t gs;     /**< Gain select pin. */

} audioamp12_cfg_t;

/**
 * @brief AudioAMP 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AUDIOAMP12_OK = 0,
    AUDIOAMP12_ERROR = -1

} audioamp12_return_value_t;

/**
 * @brief AudioAMP 12 Click gain selection value data.
 * @details Predefined enum values for driver gain selection values.
 */
typedef enum
{
    AUDIOAMP12_GAIN_6_DB,
    AUDIOAMP12_GAIN_12_DB

} audioamp12_gain_select_t;

/*!
 * @addtogroup audioamp12 AudioAMP 12 Click Driver
 * @brief API for configuring and manipulating AudioAMP 12 Click driver.
 * @{
 */

/**
 * @brief AudioAMP 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #audioamp12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void audioamp12_cfg_setup ( audioamp12_cfg_t *cfg );

/**
 * @brief AudioAMP 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #audioamp12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #audioamp12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t audioamp12_init ( audioamp12_t *ctx, audioamp12_cfg_t *cfg );

/**
 * @brief AudioAMP 12 default configuration function.
 * @details This function executes a default configuration of AudioAMP 12
 * Click board.
 * @param[in] ctx : Click context object.
 * See #audioamp12_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void audioamp12_default_cfg ( audioamp12_t *ctx );

/**
 * @brief AudioAMP 12 set standby mode function.
 * @details This function sets the standby mode 
 * of the TS2007EIJT, 3 W, filter-free, class-D audio power amplifier 
 * with 6 or 12 dB fixed gain select on the AudioAMP 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp12_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void audioamp12_set_mode_standby ( audioamp12_t *ctx );

/**
 * @brief AudioAMP 12 set operation mode function.
 * @details This function sets the device operation mode
 * of the TS2007EIJT, 3 W, filter-free, class-D audio power amplifier 
 * with 6 or 12 dB fixed gain select on the AudioAMP 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp12_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void audioamp12_set_mode_operation ( audioamp12_t *ctx );

/**
 * @brief AudioAMP 12 select gain level function.
 * @details This function selects the gain level
 * of the TS2007EIJT, 3 W, filter-free, class-D audio power amplifier 
 * with 6 or 12 dB fixed gain select on the AudioAMP 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp12_t object definition for detailed explanation.
 * @param[in] sel_gain : Gain selection value.
 * See #audioamp12_gain_select_t definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void audioamp12_gain_select ( audioamp12_t *ctx, audioamp12_gain_select_t sel_gain );

/**
 * @brief AudioAMP 12 changes the gain function.
 * @details This function switch between two gain settings, 6 dB or 12 dB, 
 * of the TS2007EIJT, 3 W, filter-free, class-D audio power amplifier 
 * with 6 or 12 dB fixed gain select on the AudioAMP 12 Click board™.
 * @param[in] ctx : Click context object.
 * See #audioamp12_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void audioamp12_change_gain ( audioamp12_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // AUDIOAMP12_H

/*! @} */ // audioamp12

// ------------------------------------------------------------------------ END
