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
 * @file speaker.h
 * @brief This file contains API for Speaker Click Driver.
 */

#ifndef SPEAKER_H
#define SPEAKER_H

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
 * @addtogroup speaker Speaker Click Driver
 * @brief API for configuring and manipulating Speaker Click driver.
 * @{
 */

/**
 * @defgroup speaker_map Speaker MikroBUS Map
 * @brief MikroBUS pin mapping of Speaker Click driver.
 */

/**
 * @addtogroup speaker_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Speaker Click to the selected MikroBUS.
 */
#define SPEAKER_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_INT ); \
    cfg.sb = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // speaker_map
/*! @} */ // speaker

/**
 * @brief Speaker Click context object.
 * @details Context object definition of Speaker Click driver.
 */
typedef struct
{
    digital_out_t  pwr;    /**< Shutdown Mode pin. */
    digital_out_t  sb;     /**< BTL/SE Control pin. */
    
} speaker_t;

/**
 * @brief Speaker Click configuration object.
 * @details Configuration object definition of Speaker Click driver.
 */
typedef struct
{
    pin_name_t  pwr;      /**< Shutdown Mode pin. */
    pin_name_t  sb;       /**< BTL/SE Control pin. */

} speaker_cfg_t;

/**
 * @brief Speaker Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   SPEAKER_OK = 0,
   SPEAKER_ERROR = -1

} speaker_return_value_t;

/*!
 * @addtogroup speaker Speaker Click Driver
 * @brief API for configuring and manipulating Speaker Click driver.
 * @{
 */

/**
 * @brief Speaker configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #speaker_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void speaker_cfg_setup ( speaker_cfg_t *cfg );

/**
 * @brief Speaker initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #speaker_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #speaker_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speaker_init ( speaker_t *ctx, speaker_cfg_t *cfg );

/**
 * @brief Speaker default configuration function.
 * @details This function executes a default configuration of Speaker
 * click board.
 * @param[in] ctx : Click context object.
 * See #speaker_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t speaker_default_cfg ( speaker_t *ctx );

/**
 * @brief Speaker enables the slave amplifier function.
 * @details This function enables the slave amplifier by 
 * clears the SB ( INT ) pin on the low level 
 * of the Speaker click board™.
 * @param[in] ctx : Click context object.
 * See #speaker_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * @note None.
 */
err_t speaker_enable_slave_amp ( speaker_t *ctx );

/**
 * @brief Speaker disables the slave amplifier function.
 * @details This function disables the slave amplifier by 
 * sets the SB ( INT ) pin on the high level 
 * of the Speaker click board™.
 * @param[in] ctx : Click context object.
 * See #speaker_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * @note None.
 */
err_t speaker_disable_slave_amp ( speaker_t *ctx );

/**
 * @brief Speaker shutdown mode function.
 * @details This function enables the shutdown mode by 
 * clears the PWR ( PWM ) pin on the low level 
 * of the Speaker click board™.
 * @param[in] ctx : Click context object.
 * See #speaker_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * @note None.
 */
err_t speaker_shutdown ( speaker_t *ctx );

/**
 * @brief Speaker normal operation mode function.
 * @details This function enables the shutdown mode by 
 * sets the PWR ( PWM ) pin on the high level 
 * of the Speaker click board™.
 * @param[in] ctx : Click context object.
 * See #speaker_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * @note None.
 */
err_t speaker_normal_operation ( speaker_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SPEAKER_H

/*! @} */ // speaker

// ------------------------------------------------------------------------ END
