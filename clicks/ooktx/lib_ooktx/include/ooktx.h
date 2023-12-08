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
 * @file ooktx.h
 * @brief This file contains API for OOK TX Click Driver.
 */

#ifndef OOKTX_H
#define OOKTX_H

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
 * @addtogroup ooktx OOK TX Click Driver
 * @brief API for configuring and manipulating OOK TX Click driver.
 * @{
 */

/**
 * @defgroup ooktx_cfg OOK TX Settings
 * @brief Settings for configuration of OOK TX Click driver.
 */

/**
 * @addtogroup ooktx_cfg
 * @{
 */

/**
 * @brief OOK TX default settings.
 * @details Specified setting for default training bytes, manchester settings, data length,
 * and communication start settings of OOK TX Click driver.
 */
#define OOKTX_TRAINING_BYTES      { 0xAA, 0xAA, 0xAA, 0xAA }
#define OOKTX_MAN_MSB               0x8000
#define OOKTX_MAN_BIT_LEN_US        2000
#define OOKTX_MAX_DATA_LEN          255
#define OOKTX_CALIB_ENABLE          0x01
#define OOKTX_CALIB_DISABLE         0x00
#define OOKTX_CFG_ENABLE            0x01
#define OOKTX_CFG_DISABLE           0x00
#define OOKTX_CFG_DEFAULT           0xF6F0
#define OOKTX_CFG_F_433MHZ          0xF000
#define OOKTX_CFG_CX_18PF           0x0600
#define OOKTX_CFG_P_13DB            0x00F0
#define OOKTX_CFG_P_10DB            0x00C0
#define OOKTX_CFG_P_7DB             0x0090
#define OOKTX_CFG_P_3DB             0x0050
#define OOKTX_CFG_P_0DB             0x0020
#define OOKTX_CFG_CT_0PF            0x0000

/*! @} */ // ooktx_cfg

/**
 * @defgroup ooktx_map OOK TX MikroBUS Map
 * @brief MikroBUS pin mapping of OOK TX Click driver.
 */

/**
 * @addtogroup ooktx_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of OOK TX Click to the selected MikroBUS.
 */
#define OOKTX_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // ooktx_map
/*! @} */ // ooktx

/**
 * @brief OOK TX Click context object.
 * @details Context object definition of OOK TX Click driver.
 */
typedef struct
{
    digital_out_t sda;      /**< Data pin. */
    digital_out_t sck;      /**< Clock pin. */

} ooktx_t;

/**
 * @brief OOK TX Click configuration object.
 * @details Configuration object definition of OOK TX Click driver.
 */
typedef struct
{
    pin_name_t sda;         /**< Data pin. */
    pin_name_t sck;         /**< Clock pin. */

} ooktx_cfg_t;

/**
 * @brief OOK TX Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    OOKTX_OK = 0,
    OOKTX_ERROR = -1

} ooktx_return_value_t;

/*!
 * @addtogroup ooktx OOK TX Click Driver
 * @brief API for configuring and manipulating OOK TX Click driver.
 * @{
 */

/**
 * @brief OOK TX configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ooktx_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ooktx_cfg_setup ( ooktx_cfg_t *cfg );

/**
 * @brief OOK TX initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ooktx_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ooktx_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ooktx_init ( ooktx_t *ctx, ooktx_cfg_t *cfg );

/**
 * @brief OOK TX set data pin function.
 * @details This function sets the data pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ooktx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ooktx_set_data_pin ( ooktx_t *ctx );

/**
 * @brief OOK TX clear data pin function.
 * @details This function clears the data pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ooktx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ooktx_clear_data_pin ( ooktx_t *ctx );

/**
 * @brief OOK TX set clock pin function.
 * @details This function sets the clock pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ooktx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ooktx_set_clock_pin ( ooktx_t *ctx );

/**
 * @brief OOK TX clear clock pin function.
 * @details This function clears the clock pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ooktx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ooktx_clear_clock_pin ( ooktx_t *ctx );

/**
 * @brief OOK TX start function.
 * @details This function starts transmit with the selected settings.
 * @param[in] ctx : Click context object.
 * See #ooktx_t object definition for detailed explanation.
 * @param[in] calib_en : Calibration enable flag.
 * @param[in] cfg_en : Configuration enable flag.
 * @param[in] cfg : Configuration word.
 * @return None.
 * @note None.
 */
void ooktx_start ( ooktx_t *ctx, uint8_t calib_en, uint8_t cfg_en, uint16_t cfg );

/**
 * @brief OOK TX stop function.
 * @details This function stops transmit.
 * @param[in] ctx : Click context object.
 * See #ooktx_t object definition for detailed explanation.
 * @param[in] calib_en : Calibration enable flag.
 * @param[in] cfg_en : Configuration enable flag.
 * @param[in] cfg : Configuration word.
 * @return None.
 * @note None.
 */
void ooktx_stop ( ooktx_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // OOKTX_H

/*! @} */ // ooktx

// ------------------------------------------------------------------------ END
