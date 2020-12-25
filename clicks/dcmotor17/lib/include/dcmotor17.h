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
 * @file dcmotor17.h
 * @brief This file contains API for DC Motor 17 Click Driver.
 */

#ifndef DCMOTOR17_H
#define DCMOTOR17_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"

/*!
 * @addtogroup dcmotor17 DC Motor 17 Click Driver
 * @brief API for configuring and manipulating DC Motor 17 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor17_set DC Motor 17 Settings
 * @brief Settings of DC Motor 17 Click driver.
 */

/**
 * @addtogroup retval_flag
 * @{
 */

/**
 * @brief DC Motor 17 error code settings.
 * @details Specified setting for error code of DC Motor 17 Click driver.
 */
#define dcmotor17_retval_t  uint8_t

#define DCMOTOR17_OK                     0x00
#define DCMOTOR17_ERROR                  0xFF

/*! @} */ // retval_flag

/**
 * @addtogroup sel_out
 * @{
 */

/**
 * @brief DC Motor 17 select channel motor output settings.
 * @details Specified setting for select channel motor output of DC Motor 17 Click driver.
 */
#define DCMOTOR17_SEL_OUT_A              0
#define DCMOTOR17_SEL_OUT_B              1

/*! @} */ // sel_out

/**
 * @addtogroup mode
 * @{
 */

/**
 * @brief DC Motor 17 control mode select.
 * @details Specified setting for control mode select of DC Motor 17 Click driver.
 */
#define DCMOTOR17_SEL_MODE_STANDBY       0
#define DCMOTOR17_SEL_MODE_NORMAL        1

/*! @} */ // mode

/**
 * @defgroup dcmotor17_map DC Motor 17 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 17 Click driver.
 */

/**
 * @addtogroup dcmotor17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 17 Click to the selected MikroBUS.
 */
#define DCMOTOR17_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.i1a = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.i2a = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.stby = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.i1b = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.i2b = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dcmotor17_map
/*! @} */ // dcmotor17

/**
 * @brief DC Motor 17 Click context object.
 * @details Context object definition of DC Motor 17 Click driver.
 */
typedef struct
{
    digital_out_t  i1a;     /**< Phase A output pin.  */
    digital_out_t  i2a;     /**< Phase B output pin.  */
    digital_out_t  stby;    /**< Standby output pin.  */
    digital_out_t  i1b;     /**< Enable A output pin. */
    digital_out_t  i2b;     /**< Enable B output pin. */
} dcmotor17_t;

/**
 * @brief DC Motor 17 Click configuration object.
 * @details Configuration object definition of DC Motor 17 Click driver.
 */
typedef struct
{
    pin_name_t  i1a;    /**< Phase A output pin.  */
    pin_name_t  i2a;    /**< Phase B output pin.  */
    pin_name_t  stby;   /**< Standby output pin.  */
    pin_name_t  i1b;    /**< Enable A output pin. */
    pin_name_t  i2b;    /**< Enable B output pin. */

} dcmotor17_cfg_t;

/*!
 * @addtogroup dcmotor17 DC Motor 17 Click Driver
 * @brief API for configuring and manipulating DC Motor 17 Click driver.
 * @{
 */

/**
 * @brief DC Motor 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor17_cfg_setup ( dcmotor17_cfg_t *cfg );

/**
 * @brief DC Motor 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor17_init ( dcmotor17_t *ctx, dcmotor17_cfg_t *cfg );

/**
 * @brief DC Motor 17 default configuration function.
 * @details This function executes a default configuration of DC Motor 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor17_t object definition for detailed explanation.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void dcmotor17_default_cfg ( dcmotor17_t *ctx );

/**
 * @brief DC Motor 17 set to standby operating mode function.
 * @details This function sets the standby operating mode of
 * DC Motor 17 click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void dcmotor17_standby_mode ( dcmotor17_t *ctx );

/**
 * @brief DC Motor 17 set to normal operating mode function.
 * @details This function sets the normal operating mode of
 * DC Motor 17 click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void dcmotor17_normal_mode ( dcmotor17_t *ctx );

/**
 * @brief DC Motor 17 set operating mode function.
 * @details This function sets the desired operating mode of
 * DC Motor 17 click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor17_t object definition for detailed explanation.
 * @param[in] op_mode : Operating mode.
 *            @li @c 0 ( DCMOTOR17_SEL_MODE_STANDBY ) - Standby operating mode,
 *            @li @c 1 ( DCMOTOR17_SEL_MODE_NORMAL ) - Normal operating mode.
 * @return @li @c 0x00 ( DCMOTOR17_OK )    - Ok,
 *         @li @c 0xFF ( DCMOTOR17_ERROR ) - Error.
 * @note None.
 */
dcmotor17_retval_t dcmotor17_set_mode ( dcmotor17_t *ctx, uint8_t op_mode );

/**
 * @brief DC Motor 17 stop motor function.
 * @details This function is used to stop the motor of
 * DC Motor 17 click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor17_t object definition for detailed explanation.
 * @param[in] sel_out : Select channel motor output.
 *            @li @c 0 ( DCMOTOR17_SEL_OUT_A ) - A channel motor output,
 *            @li @c 1 ( DCMOTOR17_SEL_OUT_B ) - B channel motor output.
 * @return @li @c 0x00 ( DCMOTOR17_OK )    - Ok,
 *         @li @c 0xFF ( DCMOTOR17_ERROR ) - Error.
 * @note None.
 */
dcmotor17_retval_t dcmotor17_stop ( dcmotor17_t *ctx, uint8_t sel_out );

/**
 * @brief DC Motor 17 forward function.
 * @details This function is used to drive the motor forward of
 * DC Motor 17 click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor17_t object definition for detailed explanation.
 * @param[in] sel_out : Select channel motor output.
 *            @li @c 0 ( DCMOTOR17_SEL_OUT_A ) - A channel motor output,
 *            @li @c 1 ( DCMOTOR17_SEL_OUT_B ) - B channel motor output.
 * @return @li @c 0x00 ( DCMOTOR17_OK )    - Ok,
 *         @li @c 0xFF ( DCMOTOR17_ERROR ) - Error.
 * @note None.
 */
dcmotor17_retval_t dcmotor17_forward ( dcmotor17_t *ctx, uint8_t sel_out );

/**
 * @brief DC Motor 17 reverse function.
 * @details This function is used to drive the motor reverse of
 * DC Motor 17 click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor17_t object definition for detailed explanation.
 * @return @li @c 0x00 ( DCMOTOR17_OK )    - Ok,
 *         @li @c 0xFF ( DCMOTOR17_ERROR ) - Error.
 * @note None.
 */
dcmotor17_retval_t dcmotor17_reverse ( dcmotor17_t *ctx, uint8_t sel_out );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR17_H

/*! @} */ // dcmotor17

// ------------------------------------------------------------------------ END
