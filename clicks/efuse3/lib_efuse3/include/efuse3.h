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
 * @file efuse3.h
 * @brief This file contains API for e Fuse 3 Click Driver.
 */

#ifndef EFUSE3_H
#define EFUSE3_H

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
#include "drv_spi_master.h"

/*!
 * @addtogroup efuse3 e Fuse 3 Click Driver
 * @brief API for configuring and manipulating e Fuse 3 Click driver.
 * @{
 */

/**
 * @defgroup efuse3_set e Fuse 3 Registers Settings
 * @brief Settings for registers of e Fuse 3 Click driver.
 */

/**
 * @addtogroup efuse3_set
 * @{
 */

/**
 * @brief e Fuse 3 description setting.
 * @details Specified setting for description of e Fuse 3 Click driver.
 */
#define EFUSE3_OVERFLOW_LOW             2
#define EFUSE3_OVERFLOW_HIGH            1
#define EFUSE3_NO_OVERFLOW              0

/*! @} */ // efuse3_set

/**
 * @addtogroup vc_sel
 * @{
 */

/**
 * @brief e Fuse 3 Vclamp level setting.
 * @details Specified Vclamp level setting for description of e Fuse 3 Click driver.
 */
#define EFUSE3_VC_SEL_6_1_V             0
#define EFUSE3_VC_SEL_6_9_V             1

/*! @} */ // vc_sel

/**
 * @addtogroup efuse3_get
 * @{
 */

/**
 * @brief e Fuse 3 description flag status.
 * @details Specified flag status for description of e Fuse 3 Click driver.
 */
#define EFUSE3_FLAG_NORMAL_OPERATION    0
#define EFUSE3_FLAG_DEVICE_OFF          1

/*! @} */ // efuse3_get

/**
 * @defgroup efuse3_map e Fuse 3 MikroBUS Map
 * @brief MikroBUS pin mapping of e Fuse 3 Click driver.
 */

/**
 * @addtogroup efuse3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of e Fuse 3 Click to the selected MikroBUS.
 */
#define EFUSE3_MAP_MIKROBUS( cfg, mikrobus )        \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.vsel = MIKROBUS( mikrobus, MIKROBUS_RST );  \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.flag = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // efuse3_map
/*! @} */ // efuse3

/**
 * @brief e Fuse 3 Click context object.
 * @details Context object definition of e Fuse 3 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  vsel;      /**< Allows the overvoltage clamp to be set at either a 5.7 V or 6.5 V minimum. */
    digital_out_t  en;        /**< When this pin is pulled low the eFuse is turned off. */
                              
    // Input pins             
                              
    digital_in_t  flag;       /**< Monitoring circuit that the device is in thermal shutdown. */
   
    // Modules

    spi_master_t  spi;        /**< SPI driver object. */

    pin_name_t  chip_select;  /**< Chip select pin descriptor (used for SPI driver). */

} efuse3_t;

/**
 * @brief e Fuse 3 Click configuration object.
 * @details Configuration object definition of e Fuse 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;         /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;         /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;          /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;           /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins

    pin_name_t  vsel;         /**< Allows the overvoltage clamp to be set at either a 5.7 V or 6.5 V minimum. */
    pin_name_t  en;           /**< When this pin is pulled low the eFuse is turned off. */
    pin_name_t  flag;         /**< Monitoring circuit that the device is in thermal shutdown. */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} efuse3_cfg_t;

/**
 * @brief e Fuse 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EFUSE3_OK = 0,
    EFUSE3_ERROR = -1

} efuse3_return_value_t;

/*!
 * @addtogroup efuse3 e Fuse 3 Click Driver
 * @brief API for configuring and manipulating e Fuse 3 Click driver.
 * @{
 */

/**
 * @brief e Fuse 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #efuse3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void efuse3_cfg_setup ( efuse3_cfg_t *cfg );

/**
 * @brief e Fuse 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #efuse3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #efuse3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse3_init ( efuse3_t *ctx, efuse3_cfg_t *cfg );

/**
 * @brief e Fuse 3 default configuration function.
 * @details This function executes a default configuration of e Fuse 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #efuse3_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void efuse3_default_cfg ( efuse3_t *ctx );

/**
 * @brief e Fuse 3 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #efuse3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse3_generic_read ( efuse3_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief e Fuse 3 get monitor output function.
 * @details This function reads and monitoring an output voltage 
 * of the NIS6150 +5 Volt Electronic eFuse 
 * on the e Fuse 3 click board. 
 * @param[in] ctx : Click context object.
 * See #efuse3_t object definition for detailed explanation.
 * @param[out] voltage  : Output volatge [ V ].
 * @param[out] overflow : Overflow status.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse3_get_monitor_output ( efuse3_t *ctx, float *voltage, uint8_t *overflow );

/**
 * @brief e Fuse 3 get current function.
 * @details This function reads current of the NIS6150 +5 Volt Electronic eFuse 
 * on the e Fuse 3 click board. 
 * @param[in] ctx : Click context object.
 * See #efuse3_t object definition for detailed explanation.
 * @param[out] current  : Current [ V ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse3_get_current ( efuse3_t *ctx, float *current );

/**
 * @brief e Fuse 3 enable device function.
 * @details This function enable the the NIS6150 +5 Volt Electronic eFuse 
 * on the e Fuse 3 click board. 
 * @param[in] ctx : Click context object.
 * See #efuse3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void efuse3_enable_device ( efuse3_t *ctx );

/**
 * @brief e Fuse 3 reset function.
 * @details This function reset the the NIS6150 +5 Volt Electronic eFuse 
 * on the e Fuse 3 click board. 
 * @param[in] ctx : Click context object.
 * See #efuse3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void efuse3_reset ( efuse3_t *ctx );

/**
 * @brief e Fuse 3 disable device function.
 * @details This function idsble the the NIS6150 +5 Volt Electronic eFuse 
 * on the e Fuse 3 click board. 
 * @param[in] ctx : Click context object.
 * See #efuse3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void efuse3_disable_device ( efuse3_t *ctx );

/**
 * @brief e Fuse 3 set overvoltage clamp function.
 * @details This function set overvoltage clamp to be set at either a 5.7 V or 6.5 V minimum 
 * of the NIS6150 +5 Volt Electronic eFuse 
 * on the e Fuse 3 click board. 
 * @param[in] ctx : Click context object.
 * See #efuse3_t object definition for detailed explanation.
 * @param[in] vc_sel : 
 *         @li @c  0 ( EFUSE3_VC_SEL_6_1_V ) - Allows the overvoltage clamp to be set 6.1 V,
 *         @li @c  1 ( EFUSE3_VC_SEL_6_9_V ) - Allows the overvoltage clamp to be set 6.9 V.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void efuse3_set_overvoltage_clamp ( efuse3_t *ctx, uint8_t vc_sel );

/**
 * @brief e Fuse 3 get flag function.
 * @details This function get flag state
 * of the NIS6150 +5 Volt Electronic eFuse 
 * on the e Fuse 3 click board. 
 * @param[in] ctx : Click context object.
 * See #efuse3_t object definition for detailed explanation.
 * @return @li @c 0 ( EFUSE3_FLAG_NORMAL_OPERATION )- Normal operation,
 *         @li @c 1 ( EFUSE3_FLAG_DEVICE_OFF ) - device off when one of the following conditions occurs:
 *                    1. EN pin set to Logic Level Low (Output Disabled),
 *                    2. Thermal fault,
 *                    3. UVLO − Undervoltage Lockout,
 *                    4. Reverse current fault.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t efuse3_get_flag ( efuse3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EFUSE3_H

/*! @} */ // efuse3

// ------------------------------------------------------------------------ END
