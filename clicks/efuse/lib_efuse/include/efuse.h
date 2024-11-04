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
 * @file efuse.h
 * @brief This file contains API for eFuse Click Driver.
 */

#ifndef EFUSE_H
#define EFUSE_H

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
 * @addtogroup efuse eFuse Click Driver
 * @brief API for configuring and manipulating eFuse Click driver.
 * @{
 */

/**
 * @defgroup efuse_map eFuse MikroBUS Map
 * @brief MikroBUS pin mapping of eFuse Click driver.
 */

/**
 * @addtogroup efuse_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of eFuse Click to the selected MikroBUS.
 */
#define EFUSE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // efuse_map
/*! @} */ // efuse

/**
 * @brief eFuse Click context object.
 * @details Context object definition of eFuse Click driver.
 */
typedef struct
{
    digital_out_t  en;      /**< Enable pin. */
    digital_out_t  pwm;     /**< PWM pin.    */
    
} efuse_t;

/**
 * @brief eFuse Click configuration object.
 * @details Configuration object definition of eFuse Click driver.
 */
typedef struct
{
    pin_name_t  en;         /**< Enable pin. */
    pin_name_t  pwm;        /**< PWM pin.    */
    
} efuse_cfg_t;

/**
 * @brief eFuse Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   EFUSE_OK = 0,
   EFUSE_ERROR = -1

} efuse_return_value_t;

/*!
 * @addtogroup efuse eFuse Click Driver
 * @brief API for configuring and manipulating eFuse Click driver.
 * @{
 */

/**
 * @brief eFuse configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #efuse_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void efuse_cfg_setup ( efuse_cfg_t *cfg );

/**
 * @brief eFuse initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #efuse_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #efuse_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse_init ( efuse_t *ctx, efuse_cfg_t *cfg );

/**
 * @brief eFuse default configuration function.
 * @details This function executes a default configuration of eFuse
 * Click board.
 * @param[in] ctx : Click context object.
 * See #efuse_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t efuse_default_cfg ( efuse_t *ctx );

/**
 * @brief eFuse enable the device function.
 * @details This function performs enable the device by sets the EN pin on the high level of
 * eFuse Click board.
 * @param[in] ctx : Click context object.
 * See #efuse_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void efuse_enable_device ( efuse_t *ctx );

/**
 * @brief eFuse disable the device function.
 * @details This function performs disable the device by clears the EN pin on the low level of
 * eFuse Click board.
 * @param[in] ctx : Click context object.
 * See #efuse_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void efuse_disable_device ( efuse_t *ctx );

/**
 * @brief eFuse enable PWM function.
 * @details This function performs enable PWM by clears the PWM pin on the low level of
 * eFuse Click board.
 * @param[in] ctx : Click context object.
 * See #efuse_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void efuse_enable_pwm ( efuse_t *ctx );

/**
 * @brief eFuse disable the device function.
 * @details This function performs disable the device by sets the PWM pin on the high level of
 * eFuse Click board.
 * @param[in] ctx : Click context object.
 * See #efuse_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void efuse_disable_pwm ( efuse_t *ctx);

#ifdef __cplusplus
}
#endif
#endif // EFUSE_H

/*! @} */ // efuse

// ------------------------------------------------------------------------ END
