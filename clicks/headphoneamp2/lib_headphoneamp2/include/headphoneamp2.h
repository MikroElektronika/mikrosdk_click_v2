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
 * @file headphoneamp2.h
 * @brief This file contains API for Headphone Amp 2 Click Driver.
 */

#ifndef HEADPHONEAMP2_H
#define HEADPHONEAMP2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/*!
 * @addtogroup headphoneamp2 Headphone Amp 2 Click Driver
 * @brief API for configuring and manipulating Headphone Amp 2 Click driver.
 * @{
 */

/**
 * @defgroup headphoneamp2_map Headphone Amp 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Headphone Amp 2 Click driver.
 */

/**
 * @addtogroup headphoneamp2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Headphone Amp 2 Click to the selected MikroBUS.
 */
#define HEADPHONEAMP2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.gs = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // headphoneamp2_map
/*! @} */ // headphoneamp2

/**
 * @brief Headphone Amp 2 Click context object.
 * @details Context object definition of Headphone Amp 2 Click driver.
 */
typedef struct
{
    digital_out_t stb;   /**< Standby pin. */
    digital_out_t gs;    /**<  Gain select  pin. */

} headphoneamp2_t;

/**
 * @brief Headphone Amp 2 Click configuration object.
 * @details Configuration object definition of Headphone Amp 2 Click driver.
 */
typedef struct
{
    pin_name_t stb;   /**< Standby pin. */
    pin_name_t gs;    /**<  Gain select  pin. */

} headphoneamp2_cfg_t;

/**
 * @brief Headphone Amp 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HEADPHONEAMP2_OK = 0,
    HEADPHONEAMP2_ERROR = -1

} headphoneamp2_return_value_t;

/**
 * @brief Headphone Amp 2 Click gain selection value data.
 * @details Predefined enum values for driver gain selection values.
 */
typedef enum
{
    HEADPHONEAMP2_GAIN_6_DB,
    HEADPHONEAMP2_GAIN_12_DB

} headphoneamp2_gain_select_value_t;

/*!
 * @addtogroup headphoneamp2 Headphone Amp 2 Click Driver
 * @brief API for configuring and manipulating Headphone Amp 2 Click driver.
 * @{
 */

/**
 * @brief Headphone Amp 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #headphoneamp2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void headphoneamp2_cfg_setup ( headphoneamp2_cfg_t *cfg );

/**
 * @brief Headphone Amp 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board™.
 * @param[out] ctx : Click context object.
 * See #headphoneamp2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #headphoneamp2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t headphoneamp2_init ( headphoneamp2_t *ctx, headphoneamp2_cfg_t *cfg );

/**
 * @brief Headphone Amp 2 default configuration function.
 * @details This function executes a default configuration of Headphone Amp 2
 * click board™.
 * @param[in] ctx : Click context object.
 * See #headphoneamp2_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void headphoneamp2_default_cfg ( headphoneamp2_t *ctx );

/**
 * @brief Headphone Amp 2 set standby mode function.
 * @details This function sets the standby mode of the 
 * TS2007FC, 3 W, filter-free, class-D audio power amplifier
 * with 6 or 12 dB fixed gain select on the
 * Headphone Amp 2 click board™.
 * @param[in] ctx : Click context object.
 * See #headphoneamp2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void headphoneamp2_standby_mode ( headphoneamp2_t *ctx );

/**
 * @brief Headphone Amp 2 set device on function.
 * @details This function sets the device ON of the 
 * TS2007FC, 3 W, filter-free, class-D audio power amplifier
 * with 6 or 12 dB fixed gain select on the
 * Headphone Amp 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #headphoneamp2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void headphoneamp2_set_device_on ( headphoneamp2_t *ctx );

/**
 * @brief Headphone Amp 2 select gain level function.
 * @details This function selects the gain level of the 
 * TS2007FC, 3 W, filter-free, class-D audio power amplifier
 * with 6 or 12 dB fixed gain select on the
 * Headphone Amp 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #headphoneamp2_t object definition for detailed explanation.
 * @param[in] sel_gain : Gain selection value.
 * See #headphoneamp2_gain_select_value_t definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void headphoneamp2_gain_select ( headphoneamp2_t *ctx, headphoneamp2_gain_select_value_t sel_gain );

/**
 * @brief Headphone Amp 2 change gain function.
 * @details This function switch between two gain settings of the 
 * TS2007FC, 3 W, filter-free, class-D audio power amplifier
 * with 6 or 12 dB fixed gain select on the
 * Headphone Amp 2 click board™. 
 * @param[in] ctx : Click context object.
 * See #headphoneamp2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void headphoneamp2_change_gain ( headphoneamp2_t *ctx ); 


#ifdef __cplusplus
}
#endif
#endif // HEADPHONEAMP2_H

/*! @} */ // headphoneamp2

// ------------------------------------------------------------------------ END
