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
 * @file hbridgedriver.h
 * @brief This file contains API for H-Bridge Driver Click Driver.
 */

#ifndef HBRIDGEDRIVER_H
#define HBRIDGEDRIVER_H

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

/*!
 * @addtogroup hbridgedriver H-Bridge Driver Click Driver
 * @brief API for configuring and manipulating H-Bridge Driver Click driver.
 * @{
 */

/**
 * @defgroup hbridgedriver_set H-Bridge Driver Registers Settings
 * @brief Settings for registers of H-Bridge Driver Click driver.
 */

/**
 * @addtogroup hbridgedriver_set
 * @{
 */

/**
 * @brief H-Bridge Driver description setting.
 * @details Specified setting for description of H-Bridge Driver Click driver.
 */
#define HBRIDGEDRIVER_PROP_DIS          0x00
#define HBRIDGEDRIVER_PROP_EN           0x01

/*! @} */ // hbridgedriver_set

/**
 * @defgroup hbridgedriver_map H-Bridge Driver MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge Driver Click driver.
 */

/**
 * @addtogroup hbridgedriver_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge Driver Click to the selected MikroBUS.
 */
#define HBRIDGEDRIVER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.il2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.ih2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gen = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.il1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ih1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridgedriver_map
/*! @} */ // hbridgedriver

/**
 * @brief H-Bridge Driver Click context object.
 * @details Context object definition of H-Bridge Driver Click driver.
 */
typedef struct
{
    digital_out_t  il2;         /**< Input Low Side 2. */
    digital_out_t  ih2;         /**< Input High Side 2. */
    digital_out_t  gen;         /**< Global Enable. */
    digital_out_t  il1;         /**< Input Low Side 1. */
    digital_out_t  ih1;         /**< Input High Side 1. */

} hbridgedriver_t;

/**
 * @brief H-Bridge Driver Click configuration object.
 * @details Configuration object definition of H-Bridge Driver Click driver.
 */
typedef struct
{
    pin_name_t  il2;        /**< Input Low Side 2. */
    pin_name_t  ih2;        /**< Input High Side 2. */
    pin_name_t  gen;        /**< Global Enable. */
    pin_name_t  il1;        /**< Input Low Side 1. */
    pin_name_t  ih1;        /**< Input High Side 1. */

} hbridgedriver_cfg_t;

/**
 * @brief H-Bridge Driver Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGEDRIVER_OK = 0,
    HBRIDGEDRIVER_ERROR = -1

} hbridgedriver_return_value_t;

/*!
 * @addtogroup hbridgedriver H-Bridge Driver Click Driver
 * @brief API for configuring and manipulating H-Bridge Driver Click driver.
 * @{
 */

/**
 * @brief H-Bridge Driver configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridgedriver_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridgedriver_cfg_setup ( hbridgedriver_cfg_t *cfg );

/**
 * @brief H-Bridge Driver initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridgedriver_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t hbridgedriver_init ( hbridgedriver_t *ctx, hbridgedriver_cfg_t *cfg );

/**
 * @brief Global enable function.
 * @details Function is used to turn the device on or off.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @param[in] state : Value thet defines the state of the device.
 * @return Nothing.
**/
void hbridgedriver_glo_enable ( hbridgedriver_t *ctx, uint8_t state );

/**
 * @brief Input Low Side 2 function.
 * @details Function is used to set the state of the 'IL2' pin.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @param[in] state : Value thet defines the state of the device.
 * @return Nothing.
**/
void hbridgedriver_in_ls_2 ( hbridgedriver_t *ctx, uint8_t state );

/**
 * @brief Input High Side 2 function.
 * @details Function is used to set the state of the 'IH2' pin.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @param[in] state : Value thet defines the state of the device.
 * @return Nothing.
**/
void hbridgedriver_in_hs_2 ( hbridgedriver_t *ctx, uint8_t state );

/**
 * @brief Input Low Side 1 function.
 * @details Function is used to set the state of the 'IL1' pin.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @param[in] state : Value thet defines the state of the device.
 * @return Nothing.
**/
void hbridgedriver_in_ls_1 ( hbridgedriver_t *ctx, uint8_t state );

/**
 * @brief Input High Side 1 function.
 * @details Function is used to set the state of the 'IH1' pin.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @param[in] state : Value thet defines the state of the device.
 * @return Nothing.
**/
void hbridgedriver_in_hs_1 ( hbridgedriver_t *ctx, uint8_t state );

/**
 * @brief Motor Connected to HS/LS 1 Foreward motion function.
 * @details Function is used to put Connected to HS/LS 1
 * into foreward motion.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @return Nothing. 
 */
void hbridgedriver_dc_fwd_1 ( hbridgedriver_t *ctx );

/**
 * @brief Motor Connected to HS/LS 1 Backward motion function.
 * @details Function is used to put the motor connected to HS/LS 1
 * into backward motion.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @return Nothing.
 */
void hbridgedriver_dc_bwd_1 ( hbridgedriver_t *ctx );

/**
 * @brief Motor Connected to HS/LS 1 Coasting function.
 * @details Function is used to put the motor connected to HS/LS 1
 * into coasting mode.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @return Nothing.
 */
void hbridgedriver_dc_coast_1 ( hbridgedriver_t *ctx );

/**
 * @brief Motor Connected to HS/LS 1 Braking function.
 * @details Function is used to put the motor connected to HS/LS 1
 * into braking mode.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @return Nothing.
 */
void hbridgedriver_dc_brake_1 ( hbridgedriver_t *ctx );

/**
 * @brief Motor Connected to HS/LS 2 Foreward motion function.
 * @details Function is used to put the motor connected to HS/LS 2
 * into foreward motion.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @return Nothing.
 */
void hbridgedriver_dc_fwd_2 ( hbridgedriver_t *ctx );

/**
 * @brief Motor Connected to HS/LS 2 Backward motion function.
 * @details Function is used to put the motor connected to HS/LS 2
 * into backward motion.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @return Nothing.
 */
void hbridgedriver_dc_bwd_2 ( hbridgedriver_t *ctx );

/**
 * @brief Motor Connected to HS/LS 2 Coasting function.
 * @details Function is used to put the motor connected to HS/LS 2
 * into coasting mode.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @return Nothing.
 */
void hbridgedriver_dc_coast_2 ( hbridgedriver_t *ctx );

/**
 * @brief Motor Connected to HS/LS 2 Braking function.
 * @details Function is used to put the motor connected to HS/LS 2
 * into braking mode.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @return Nothing.
 */
void hbridgedriver_dc_brake_2 ( hbridgedriver_t *ctx );

/**
 * @brief H-Bridge mode reverse function.
 * @details Function is used to put the motor connected to the click board
 * in reverse drive.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @return Nothing.
 */
void hbridgedriver_reverse ( hbridgedriver_t *ctx );

/**
 * @brief H-Bridge mode forward function.
 * @details Function is used to put the motor connected to the click board
 * in forward drive.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @return Nothing.
 */
void hbridgedriver_forward ( hbridgedriver_t *ctx );

/**
 * @brief H-Bridge mode braking function.
 * @details Function is used to brake the motor connected to the 
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @return Nothing.
 */
void hbridgedriver_braking ( hbridgedriver_t *ctx );

/**
 * @brief H-Bridge mode coasting function.
 * @details Function is used to put the motor connected to the click board
 * in coasting mode.
 * @param[in] ctx : Click context object.
 * See #hbridgedriver_t object definition for detailed e0xplanation.
 * @return Nothing.
 */
void hbridgedriver_coasting ( hbridgedriver_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGEDRIVER_H

/*! @} */ // hbridgedriver

// ------------------------------------------------------------------------ END
