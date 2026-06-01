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
 * @file opto8.h
 * @brief This file contains API for Opto 8 Click Driver.
 */

#ifndef OPTO8_H
#define OPTO8_H

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
 * @addtogroup opto8 Opto 8 Click Driver
 * @brief API for configuring and manipulating Opto 8 Click driver.
 * @{
 */

/**
 * @defgroup opto8_map Opto 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Opto 8 Click driver.
 */

/**
 * @addtogroup opto8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Opto 8 Click to the selected MikroBUS.
 */
#define OPTO8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.out1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.out2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // opto8_map
/*! @} */ // opto8

/**
 * @brief Opto 8 Click context object.
 * @details Context object definition of Opto 8 Click driver.
 */
typedef struct
{
    digital_out_t out1;         /**< Output 1 control pin. */
    digital_out_t out2;         /**< Output 2 control pin. */

    digital_in_t in1;           /**< Input 1 status pin. */
    digital_in_t in2;           /**< Input 2 status pin. */

} opto8_t;

/**
 * @brief Opto 8 Click configuration object.
 * @details Configuration object definition of Opto 8 Click driver.
 */
typedef struct
{
    pin_name_t in1;             /**< Input 1 status pin. */
    pin_name_t out1;            /**< Output 1 control pin. */
    pin_name_t out2;            /**< Output 2 control pin. */
    pin_name_t in2;             /**< Input 2 status pin. */

} opto8_cfg_t;

/**
 * @brief Opto 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    OPTO8_OK = 0,
    OPTO8_ERROR = -1

} opto8_return_value_t;

/*!
 * @addtogroup opto8 Opto 8 Click Driver
 * @brief API for configuring and manipulating Opto 8 Click driver.
 * @{
 */

/**
 * @brief Opto 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #opto8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void opto8_cfg_setup ( opto8_cfg_t *cfg );

/**
 * @brief Opto 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #opto8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #opto8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t opto8_init ( opto8_t *ctx, opto8_cfg_t *cfg );

/**
 * @brief Opto 8 set OUT1 function.
 * @details This function sets the output 1 control pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #opto8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void opto8_set_out1 ( opto8_t *ctx );

/**
 * @brief Opto 8 clear OUT1 function.
 * @details This function clears the output 1 control pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #opto8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void opto8_clear_out1 ( opto8_t *ctx );

/**
 * @brief Opto 8 toggle OUT1 function.
 * @details This function toggles the output 1 control pin logic state.
 * @param[in] ctx : Click context object.
 * See #opto8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void opto8_toggle_out1 ( opto8_t *ctx );

/**
 * @brief Opto 8 set OUT2 function.
 * @details This function sets the output 2 control pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #opto8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void opto8_set_out2 ( opto8_t *ctx );

/**
 * @brief Opto 8 clear OUT2 function.
 * @details This function clears the output 2 control pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #opto8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void opto8_clear_out2 ( opto8_t *ctx );

/**
 * @brief Opto 8 toggle OUT2 function.
 * @details This function toggles the output 2 control pin logic state.
 * @param[in] ctx : Click context object.
 * See #opto8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void opto8_toggle_out2 ( opto8_t *ctx );

/**
 * @brief Opto 8 get IN1 function.
 * @details This function reads the input 1 status pin logic state.
 * @param[in] ctx : Click context object.
 * See #opto8_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t opto8_get_in1 ( opto8_t *ctx );

/**
 * @brief Opto 8 get IN2 function.
 * @details This function reads the input 2 status pin logic state.
 * @param[in] ctx : Click context object.
 * See #opto8_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t opto8_get_in2 ( opto8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // OPTO8_H

/*! @} */ // opto8

// ------------------------------------------------------------------------ END
