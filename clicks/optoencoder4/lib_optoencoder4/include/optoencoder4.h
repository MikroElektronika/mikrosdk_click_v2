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
 * @file optoencoder4.h
 * @brief This file contains API for Opto Encoder 4 Click Driver.
 */

#ifndef OPTOENCODER4_H
#define OPTOENCODER4_H

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
 * @addtogroup optoencoder4 Opto Encoder 4 Click Driver
 * @brief API for configuring and manipulating Opto Encoder 4 Click driver.
 * @{
 */

/**
 * @defgroup optoencoder4_map Opto Encoder 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Opto Encoder 4 Click driver.
 */

/**
 * @addtogroup optoencoder4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Opto Encoder 4 Click to the selected MikroBUS.
 */
#define OPTOENCODER4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.out = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.our = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // optoencoder4_map
/*! @} */ // optoencoder4

/**
 * @brief Opto Encoder 4 Click context object.
 * @details Context object definition of Opto Encoder 4 Click driver.
 */
typedef struct
{
    digital_in_t out;       /**< Output pin. */
    digital_in_t our;       /**< Output reverse pin. */

} optoencoder4_t;

/**
 * @brief Opto Encoder 4 Click configuration object.
 * @details Configuration object definition of Opto Encoder 4 Click driver.
 */
typedef struct
{
    pin_name_t out;         /**< Output pin. */
    pin_name_t our;         /**< Output reverse pin. */

} optoencoder4_cfg_t;

/**
 * @brief Opto Encoder 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    OPTOENCODER4_OK = 0,
    OPTOENCODER4_ERROR = -1

} optoencoder4_return_value_t;

/*!
 * @addtogroup optoencoder4 Opto Encoder 4 Click Driver
 * @brief API for configuring and manipulating Opto Encoder 4 Click driver.
 * @{
 */

/**
 * @brief Opto Encoder 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #optoencoder4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void optoencoder4_cfg_setup ( optoencoder4_cfg_t *cfg );

/**
 * @brief Opto Encoder 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #optoencoder4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #optoencoder4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t optoencoder4_init ( optoencoder4_t *ctx, optoencoder4_cfg_t *cfg );

/**
 * @brief Opto Encoder 4 get out pin function.
 * @details This function returns the output pin logic state.
 * @param[in] ctx : Click context object.
 * See #optoencoder4_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t optoencoder4_get_out_pin ( optoencoder4_t *ctx );

/**
 * @brief Opto Encoder 4 get our pin function.
 * @details This function returns the output pin reversed logic state.
 * @param[in] ctx : Click context object.
 * See #optoencoder4_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t optoencoder4_get_our_pin ( optoencoder4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // OPTOENCODER4_H

/*! @} */ // optoencoder4

// ------------------------------------------------------------------------ END
