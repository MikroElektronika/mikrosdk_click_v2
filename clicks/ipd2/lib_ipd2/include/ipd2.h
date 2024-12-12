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
 * @file ipd2.h
 * @brief This file contains API for IPD 2 Click Driver.
 */

#ifndef IPD2_H
#define IPD2_H

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
 * @addtogroup ipd2 IPD 2 Click Driver
 * @brief API for configuring and manipulating IPD 2 Click driver.
 * @{
 */

/**
 * @defgroup ipd2_map IPD 2 MikroBUS Map
 * @brief MikroBUS pin mapping of IPD 2 Click driver.
 */

/**
 * @addtogroup ipd2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IPD 2 Click to the selected MikroBUS.
 */
#define IPD2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.st2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.st1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ipd2_map
/*! @} */ // ipd2

/**
 * @brief IPD 2 Click context object.
 * @details Context object definition of IPD 2 Click driver.
 */
typedef struct
{
    digital_out_t in2;          /**< IN2 pin, controls OUT2 state (active high). */
    digital_out_t in1;          /**< IN1 pin, controls OUT1 state (active high). */

    digital_in_t st2;           /**< Diagnostics pin for OUT2 (fault - active high). */
    digital_in_t st1;           /**< Diagnostics pin for OUT1 (fault - active high). */

} ipd2_t;

/**
 * @brief IPD 2 Click configuration object.
 * @details Configuration object definition of IPD 2 Click driver.
 */
typedef struct
{
    pin_name_t st2;             /**< Diagnostics pin for OUT2 (fault - active high). */
    pin_name_t in2;             /**< IN2 pin, controls OUT2 state (active high). */
    pin_name_t in1;             /**< IN1 pin, controls OUT1 state (active high). */
    pin_name_t st1;             /**< Diagnostics pin for OUT1 (fault - active high). */

} ipd2_cfg_t;

/**
 * @brief IPD 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IPD2_OK = 0,
    IPD2_ERROR = -1

} ipd2_return_value_t;

/*!
 * @addtogroup ipd2 IPD 2 Click Driver
 * @brief API for configuring and manipulating IPD 2 Click driver.
 * @{
 */

/**
 * @brief IPD 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ipd2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ipd2_cfg_setup ( ipd2_cfg_t *cfg );

/**
 * @brief IPD 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ipd2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ipd2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ipd2_init ( ipd2_t *ctx, ipd2_cfg_t *cfg );

/**
 * @brief IPD 2 enable OUT1 function.
 * @details This function enables OUT1 by setting the IN1 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ipd2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipd2_enable_out1 ( ipd2_t *ctx );

/**
 * @brief IPD 2 disable OUT1 function.
 * @details This function disables OUT1 by setting the IN1 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ipd2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipd2_disable_out1 ( ipd2_t *ctx );

/**
 * @brief IPD 2 enable OUT2 function.
 * @details This function enables OUT2 by setting the IN2 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ipd2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipd2_enable_out2 ( ipd2_t *ctx );

/**
 * @brief IPD 2 disable OUT2 function.
 * @details This function disables OUT2 by setting the IN2 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ipd2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ipd2_disable_out2 ( ipd2_t *ctx );

/**
 * @brief IPD 2 get ST1 pin function.
 * @details This function returns the ST1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #ipd2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ipd2_get_st1_pin ( ipd2_t *ctx );

/**
 * @brief IPD 2 get ST2 pin function.
 * @details This function returns the ST2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #ipd2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ipd2_get_st2_pin ( ipd2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // IPD2_H

/*! @} */ // ipd2

// ------------------------------------------------------------------------ END
