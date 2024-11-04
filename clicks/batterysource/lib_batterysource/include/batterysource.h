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
 * @file batterysource.h
 * @brief This file contains API for Battery Source Click Driver.
 */

#ifndef BATTERYSOURCE_H
#define BATTERYSOURCE_H

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
 * @addtogroup batterysource Battery Source Click Driver
 * @brief API for configuring and manipulating Battery Source Click driver.
 * @{
 */

/**
 * @defgroup batterysource_set Battery Source Registers Settings
 * @brief Settings for registers of Battery Source Click driver.
 */

/**
 * @addtogroup batterysource_set
 * @{
 */

/**
 * @brief Battery Source description setting.
 * @details Specified setting for description of Battery Source Click driver.
 */
#define BATTERYSOURCE_ENABLE_OUTPUT    0x01
#define BATTERYSOURCE_DISABLE_OUTPUT   0x00

/*! @} */ // batterysource_set

/**
 * @defgroup batterysource_map Battery Source MikroBUS Map
 * @brief MikroBUS pin mapping of Battery Source Click driver.
 */

/**
 * @addtogroup batterysource_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Battery Source Click to the selected MikroBUS.
 */
#define BATTERYSOURCE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // batterysource_map
/*! @} */ // batterysource

/**
 * @brief Battery Source Click context object.
 * @details Context object definition of Battery Source Click driver.
 */
typedef struct
{
    digital_out_t en;      /**< Enable output pin. */

} batterysource_t;

/**
 * @brief Battery Source Click configuration object.
 * @details Configuration object definition of Battery Source Click driver.
 */
typedef struct
{
    pin_name_t en;         /**< Enable output pin. */

} batterysource_cfg_t;

/**
 * @brief Battery Source Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BATTERYSOURCE_OK = 0,
    BATTERYSOURCE_ERROR = -1

} batterysource_return_value_t;

/*!
 * @addtogroup batterysource Battery Source Click Driver
 * @brief API for configuring and manipulating Battery Source Click driver.
 * @{
 */

/**
 * @brief Battery Source configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #batterysource_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void batterysource_cfg_setup ( batterysource_cfg_t *cfg );

/**
 * @brief Battery Source initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #batterysource_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #batterysource_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t batterysource_init ( batterysource_t *ctx, batterysource_cfg_t *cfg );

/**
 * @brief Battery Source set output state function.
 * @details This function is used to set output state of
 * Battery Source Click board.
 * @param[in] ctx : Click context object.
 * See #batterysource_t object definition for detailed explanation.
 * @param[in] output_state : State of the output.
 * @return Nothing.
 * @note None.
 */
void batterysource_set_output ( batterysource_t *ctx, uint8_t output_state );


#ifdef __cplusplus
}
#endif
#endif // BATTERYSOURCE_H

/*! @} */ // batterysource

// ------------------------------------------------------------------------ END
