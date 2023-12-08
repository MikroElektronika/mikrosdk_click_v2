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
 * @file dcmotor20.h
 * @brief This file contains API for DC Motor 20 Click Driver.
 */

#ifndef DCMOTOR20_H
#define DCMOTOR20_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup dcmotor20 DC Motor 20 Click Driver
 * @brief API for configuring and manipulating DC Motor 20 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor20_set DC Motor 20 Settings
 * @brief Settings of DC Motor 20 Click driver.
 */

/**
 * @addtogroup dcmotor20_set
 * @{
 */

/**
 * @brief DC Motor 20 channel setting.
 * @details Specified setting for channel of DC Motor 20 Click driver.
 */
#define DCMOTOR20_CHANNEL_1             0x01
#define DCMOTOR20_CHANNEL_2             0x02

/**
 * @brief DC Motor 20 mode setting.
 * @details Specified setting for mode of DC Motor 20 Click driver.
 */
#define DCMOTOR20_MODE_STOP         0x00
#define DCMOTOR20_MODE_FORWARD      0x01
#define DCMOTOR20_MODE_REVERSE      0x02

/**
 * @brief DC Motor 20 speed and time setting.
 * @details Specified setting for speed and time of DC Motor 20 Click driver.
 */
#define DCMOTOR20_SPEED_MAX             100
#define DCMOTOR20_SPEED_DEFAULT         10
#define DCMOTOR20_SPEED_MIN             1
#define DCMOTOR20_MS_TIME_STEP          10

/*! @} */ // dcmotor20_set

/**
 * @defgroup dcmotor20_map DC Motor 20 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 20 Click driver.
 */

/**
 * @addtogroup dcmotor20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 20 Click to the selected MikroBUS.
 */
#define DCMOTOR20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.in1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in3 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.in4 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dcmotor20_map
/*! @} */ // dcmotor20

/**
 * @brief DC Motor 20 Click context object.
 * @details Context object definition of DC Motor 20 Click driver.
 */
typedef struct
{
    digital_out_t  in1;         /**< Control input pin 1. */
    digital_out_t  in2;         /**< Control input pin 2. */
    digital_out_t  in3;         /**< Control input pin 3. */
    digital_out_t  in4;         /**< Control input pin 4. */
    
    uint8_t        active_ch;   /**< Active channel indicator. */
    uint8_t        mode;        /**< Motor control mode. */

} dcmotor20_t;

/**
 * @brief DC Motor 20 Click configuration object.
 * @details Configuration object definition of DC Motor 20 Click driver.
 */
typedef struct
{
    pin_name_t  in1;            /**< Control input pin 1. */
    pin_name_t  in2;            /**< Control input pin 2. */
    pin_name_t  in3;            /**< Control input pin 3. */
    pin_name_t  in4;            /**< Control input pin 4. */

} dcmotor20_cfg_t;

/**
 * @brief DC Motor 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR20_OK = 0,
    DCMOTOR20_ERROR = -1

} dcmotor20_return_value_t;

/*!
 * @addtogroup dcmotor20 DC Motor 20 Click Driver
 * @brief API for configuring and manipulating DC Motor 20 Click driver.
 * @{
 */

/**
 * @brief DC Motor 20 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor20_cfg_setup ( dcmotor20_cfg_t *cfg );

/**
 * @brief DC Motor 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor20_init ( dcmotor20_t *ctx, dcmotor20_cfg_t *cfg );

/**
 * @brief DC Motor 20 drive motor function.
 * @details This function drives the motor for a certian time specified by @a time_ms 
 * at the desired speed. The motor channel and mode must be previously selected using the 
 * @b dcmotor20_set_channel_mode function.
 * @param[out] ctx : Click context object.
 * See #dcmotor20_t object definition for detailed explanation.
 * @param[in] speed : Motor speed level [1-100].
 * @param[in] time_ms : Driving time in miliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor20_drive_motor ( dcmotor20_t *ctx, uint8_t speed, uint32_t time_ms );

/**
 * @brief DC Motor 20 set channel mode function.
 * @details This function sets the active channel and mode which will be used by
 * the @b dcmotor20_drive_motor function.
 * @param[out] ctx : Click context object.
 * See #dcmotor20_t object definition for detailed explanation.
 * @param[in] channel : Active channel selection [1-3].
 * @param[in] mode : Mode selection [0-2].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor20_set_channel_mode ( dcmotor20_t *ctx, uint8_t channel, uint8_t mode );

/**
 * @brief DC Motor 20 set standby mode function.
 * @details This function sets the chip to the standby mode which affects both channels.
 * @param[out] ctx : Click context object.
 * See #dcmotor20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor20_set_standby_mode ( dcmotor20_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR20_H

/*! @} */ // dcmotor20

// ------------------------------------------------------------------------ END
