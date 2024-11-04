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
 * @file optoencoder5.h
 * @brief This file contains API for Opto Encoder 5 Click Driver.
 */

#ifndef OPTOENCODER5_H
#define OPTOENCODER5_H

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
 * @addtogroup optoencoder5 Opto Encoder 5 Click Driver
 * @brief API for configuring and manipulating Opto Encoder 5 Click driver.
 * @{
 */

/**
 * @addtogroup optoencoder5_set
 * @{
 */

/**
 * @brief Opto Encoder 5 description setting.
 * @details Specified setting for description of Opto Encoder 5 Click driver.
 */
#define OPTOENCODER5_OUT_STATE_SWITCH_OPEN                0
#define OPTOENCODER5_OUT_STATE_SWITCH_CLOSED              1

/*! @} */ // optoencoder5_set

/**
 * @defgroup optoencoder5_map Opto Encoder 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Opto Encoder 5 Click driver.
 */

/**
 * @addtogroup optoencoder5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Opto Encoder 5 Click to the selected MikroBUS.
 */
#define OPTOENCODER5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.on  = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.out = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // optoencoder5_map
/*! @} */ // optoencoder5

/**
 * @brief Opto Encoder 5 Click context object.
 * @details Context object definition of Opto Encoder 5 Click driver.
 */
typedef struct
{
    digital_out_t on;     /**< Enable pin. */
    digital_in_t out;     /**< Slotted optical switch output pin. */

} optoencoder5_t;

/**
 * @brief Opto Encoder 5 Click configuration object.
 * @details Configuration object definition of Opto Encoder 5 Click driver.
 */
typedef struct
{
    pin_name_t on;     /**< Enable pin. */
    pin_name_t out;    /**< Slotted optical switch output pin. */

} optoencoder5_cfg_t;

/**
 * @brief Opto Encoder 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    OPTOENCODER5_OK = 0,
    OPTOENCODER5_ERROR = -1

} optoencoder5_return_value_t;

/*!
 * @addtogroup optoencoder5 Opto Encoder 5 Click Driver
 * @brief API for configuring and manipulating Opto Encoder 5 Click driver.
 * @{
 */

/**
 * @brief Opto Encoder 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #optoencoder5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void optoencoder5_cfg_setup ( optoencoder5_cfg_t *cfg );

/**
 * @brief Opto Encoder 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #optoencoder5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #optoencoder5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t optoencoder5_init ( optoencoder5_t *ctx, optoencoder5_cfg_t *cfg );

/**
 * @brief Opto Encoder 5 enable function.
 * @details This function enables the slotted optical switch
 * of Opto Encoder 5 Click board.
 * @param[in] ctx : Click context object.
 * See #optoencoder5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void optoencoder5_enable ( optoencoder5_t *ctx );

/**
 * @brief Opto Encoder 5 disable function.
 * @details This function disables the slotted optical switch
 * of Opto Encoder 5 Click board.
 * @param[in] ctx : Click context object.
 * See #optoencoder5_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void optoencoder5_disable ( optoencoder5_t *ctx );

/**
 * @brief Opto Encoder 5 get state function.
 * @details This function detecting slotted optical switch states
 * of Opto Encoder 5 Click board.
 * @param[in] ctx : Click context object.
 * See #optoencoder5_t object definition for detailed explanation.
 * @return @li @c 0 - Open,
 *         @li @c 1 - Closed.
 * @note None.
 */
uint8_t optoencoder5_get_out_state ( optoencoder5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // OPTOENCODER5_H

/*! @} */ // optoencoder5

// ------------------------------------------------------------------------ END
