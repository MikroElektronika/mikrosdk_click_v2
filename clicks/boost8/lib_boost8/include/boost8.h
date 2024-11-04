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
 * @file boost8.h
 * @brief This file contains API for Boost 8 Click Driver.
 */

#ifndef BOOST8_H
#define BOOST8_H

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
 * @addtogroup boost8 Boost 8 Click Driver
 * @brief API for configuring and manipulating Boost 8 Click driver.
 * @{
 */

/**
 * @defgroup boost8_map Boost 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Boost 8 Click driver.
 */

/**
 * @addtogroup boost8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Boost 8 Click to the selected MikroBUS.
 */
#define BOOST8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en_p = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en_n = MIKROBUS( mikrobus, MIKROBUS_PWM ); 

/*! @} */ // boost8_map
/*! @} */ // boost8

/**
 * @brief Boost 8 Click context object.
 * @details Context object definition of Boost 8 Click driver.
 */
typedef struct
{
    digital_out_t en_p;     /**< Enable positive output. */
    digital_out_t en_n;     /**< Enable negative output. */

} boost8_t;

/**
 * @brief Boost 8 Click configuration object.
 * @details Configuration object definition of Boost 8 Click driver.
 */
typedef struct
{
    pin_name_t en_p;    /**< Enable positive output. */
    pin_name_t en_n;    /**< Enable negative output. */

} boost8_cfg_t;

/**
 * @brief Boost 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BOOST8_OK = 0,
    BOOST8_ERROR = -1

} boost8_return_value_t;

/*!
 * @addtogroup boost8 Boost 8 Click Driver
 * @brief API for configuring and manipulating Boost 8 Click driver.
 * @{
 */

/**
 * @brief Boost 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #boost8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void boost8_cfg_setup ( boost8_cfg_t *cfg );

/**
 * @brief Boost 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #boost8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #boost8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost8_init ( boost8_t *ctx, boost8_cfg_t *cfg );

/**
 * @brief Boost 8 default configuration function.
 * @details This function executes a default configuration of Boost 8
 * Click board.
 * @param[in] ctx : Click context object.
 * See #boost8_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void boost8_default_cfg ( boost8_t *ctx );

/**
 * @brief Boost 8 enable positive voltage output function.
 * @details This function enables positive output of Boost 8 Click board.
 * @param[in] ctx : Click context object.
 * See #boost8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void boost8_enable_positive_voltage( boost8_t *ctx );

/**
 * @brief Boost 8 disable positive voltage output function.
 * @details This function disables positive output of Boost 8 Click board.
 * @param[in] ctx : Click context object.
 * See #boost8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void boost8_disable_positive_voltage( boost8_t *ctx );

/**
 * @brief Boost 8 enable negative voltage output function.
 * @details This function enables negative output of Boost 8 Click board.
 * @param[in] ctx : Click context object.
 * See #boost8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void boost8_enable_negative_voltage( boost8_t *ctx );

/**
 * @brief Boost 8 disable negative voltage output function.
 * @details This function disables negative output of Boost 8 Click board.
 * @param[in] ctx : Click context object.
 * See #boost8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void boost8_disable_negative_voltage( boost8_t *ctx );

/**
 * @brief Boost 8 enable both voltage outputs function.
 * @details This function enables both outputs of Boost 8 Click board.
 * @param[in] ctx : Click context object.
 * See #boost8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void boost8_enable_both_outputs ( boost8_t *ctx );

/**
 * @brief Boost 8 disable both voltage outputs function.
 * @details This function disables both outputs of Boost 8 Click board.
 * @param[in] ctx : Click context object.
 * See #boost8_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void boost8_disable_both_outputs ( boost8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BOOST8_H

/*! @} */ // boost8

// ------------------------------------------------------------------------ END
