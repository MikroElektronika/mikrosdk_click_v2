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
 * @file optoencoder6.h
 * @brief This file contains API for Opto Encoder 6 Click Driver.
 */

#ifndef OPTOENCODER6_H
#define OPTOENCODER6_H

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
 * @addtogroup optoencoder6 Opto Encoder 6 Click Driver
 * @brief API for configuring and manipulating Opto Encoder 6 Click driver.
 * @{
 */

/**
 * @defgroup optoencoder6_map Opto Encoder 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Opto Encoder 6 Click driver.
 */

/**
 * @addtogroup optoencoder6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Opto Encoder 6 Click to the selected MikroBUS.
 */
#define OPTOENCODER6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.out = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // optoencoder6_map
/*! @} */ // optoencoder6

/**
 * @brief Opto Encoder 6 Click context object.
 * @details Context object definition of Opto Encoder 6 Click driver.
 */
typedef struct
{
    digital_out_t en;           /**< Enable pin (active high). */

    digital_in_t out;           /**< Sensor output pin. */

} optoencoder6_t;

/**
 * @brief Opto Encoder 6 Click configuration object.
 * @details Configuration object definition of Opto Encoder 6 Click driver.
 */
typedef struct
{
    pin_name_t en;              /**< Enable pin (active high). */
    pin_name_t out;             /**< Sensor output pin. */

} optoencoder6_cfg_t;

/**
 * @brief Opto Encoder 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    OPTOENCODER6_OK = 0,
    OPTOENCODER6_ERROR = -1

} optoencoder6_return_value_t;

/*!
 * @addtogroup optoencoder6 Opto Encoder 6 Click Driver
 * @brief API for configuring and manipulating Opto Encoder 6 Click driver.
 * @{
 */

/**
 * @brief Opto Encoder 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #optoencoder6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void optoencoder6_cfg_setup ( optoencoder6_cfg_t *cfg );

/**
 * @brief Opto Encoder 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #optoencoder6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #optoencoder6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t optoencoder6_init ( optoencoder6_t *ctx, optoencoder6_cfg_t *cfg );

/**
 * @brief Opto Encoder 6 enable output function.
 * @details This function enables output by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #optoencoder6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void optoencoder6_enable_output ( optoencoder6_t *ctx );

/**
 * @brief Opto Encoder 6 disable output function.
 * @details This function disables output by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #optoencoder6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void optoencoder6_disable_output ( optoencoder6_t *ctx );

/**
 * @brief Opto Encoder 6 get OUT pin function.
 * @details This function returns the OUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #optoencoder6_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t optoencoder6_get_out_pin ( optoencoder6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // OPTOENCODER6_H

/*! @} */ // optoencoder6

// ------------------------------------------------------------------------ END
