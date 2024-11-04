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
 * @file easypull.h
 * @brief This file contains API for EasyPull Click Driver.
 */

#ifndef EASYPULL_H
#define EASYPULL_H

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
 * @addtogroup easypull EasyPull Click Driver
 * @brief API for configuring and manipulating EasyPull Click driver.
 * @{
 */

/**
 * @addtogroup easypull_set
 * @{
 */

/**
 * @brief EasyPull description setting.
 * @details Specified setting for description of EasyPull Click driver.
 */
#define EASYPULL_PIN_STATE_HIGH             0x01
#define EASYPULL_PIN_STATE_LOW              0x00

/*! @} */ // easypull_set

/**
 * @defgroup easypull_map EasyPull MikroBUS Map
 * @brief MikroBUS pin mapping of EasyPull Click driver.
 */

/**
 * @addtogroup easypull_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EasyPull Click to the selected MikroBUS.
 */
#define EASYPULL_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // easypull_map
/*! @} */ // easypull

/**
 * @brief EasyPull Click context object.
 * @details Context object definition of EasyPull Click driver.
 */
typedef struct
{
    digital_in_t an;        /**< AN Pin. */
    digital_in_t rst;       /**< RST Pin. */
    digital_in_t cs;        /**< CS Pin. */
    digital_in_t pwm;       /**< PWM Pin. */
    digital_in_t int_pin;   /**< INT Pin. */

} easypull_t;

/**
 * @brief EasyPull Click configuration object.
 * @details Configuration object definition of EasyPull Click driver.
 */
typedef struct
{
    pin_name_t an;          /**< AN Pin. */
    pin_name_t rst;         /**< RST Pin. */
    pin_name_t cs;          /**< CS Pin. */
    pin_name_t pwm;         /**< PWM Pin. */
    pin_name_t int_pin;     /**< INT Pin. */

} easypull_cfg_t;

/**
 * @brief EasyPull Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EASYPULL_OK = 0,
    EASYPULL_ERROR = -1

} easypull_return_value_t;

/*!
 * @addtogroup easypull EasyPull Click Driver
 * @brief API for configuring and manipulating EasyPull Click driver.
 * @{
 */

/**
 * @brief EasyPull configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #easypull_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void easypull_cfg_setup ( easypull_cfg_t *cfg );

/**
 * @brief EasyPull initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #easypull_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #easypull_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t easypull_init ( easypull_t *ctx, easypull_cfg_t *cfg );

/**
 * @brief EasyPull AN pin reading function.
 * @details This function reads the state of the AN pin of EasyPull
 * Click board.
 * @param[in] ctx : Click context object.
 * See #easypull_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t easypull_get_an_pin ( easypull_t *ctx );

/**
 * @brief EasyPull RST pin reading function.
 * @details This function reads the state of the RST pin of EasyPull
 * Click board.
 * @param[in] ctx : Click context object.
 * See #easypull_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t easypull_get_rst_pin ( easypull_t *ctx );

/**
 * @brief EasyPull CS pin reading function.
 * @details This function reads the state of the CS pin of EasyPull
 * Click board.
 * @param[in] ctx : Click context object.
 * See #easypull_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t easypull_get_cs_pin ( easypull_t *ctx );

/**
 * @brief EasyPull PWM pin reading function.
 * @details This function reads the state of the PWM pin of EasyPull
 * Click board.
 * @param[in] ctx : Click context object.
 * See #easypull_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t easypull_get_pwm_pin ( easypull_t *ctx );

/**
 * @brief EasyPull INT pin reading function.
 * @details This function reads the state of the INT pin of EasyPull
 * Click board.
 * @param[in] ctx : Click context object.
 * See #easypull_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t easypull_get_int_pin ( easypull_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EASYPULL_H

/*! @} */ // easypull

// ------------------------------------------------------------------------ END
