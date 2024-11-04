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
 * @file efuse7.h
 * @brief This file contains API for eFuse 7 Click Driver.
 */

#ifndef EFUSE7_H
#define EFUSE7_H

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
 * @addtogroup efuse7 eFuse 7 Click Driver
 * @brief API for configuring and manipulating eFuse 7 Click driver.
 * @{
 */

/**
 * @defgroup efuse7_set eFuse 7 Registers Settings
 * @brief Settings for registers of eFuse 7 Click driver.
 */

/**
 * @addtogroup efuse7_set
 * @{
 */

/**
 * @brief eFuse 7 description setting.
 * @details Specified setting for description of eFuse 7 Click driver.
 */
#define EFUSE7_CONVERSION_MUL               156.25f 
#define EFUSE7_MAX_RESISTANCE               12000 
#define EFUSE7_R5_RESISTANCE                2000 
#define EFUSE7_LIMIT_1A_RESISTANCE          10500
#define EFUSE7_LIMIT_2A_RESISTANCE          5200
#define EFUSE7_LIMIT_2A5_RESISTANCE         4200
#define EFUSE7_LIMIT_3A_RESISTANCE          3500
#define EFUSE7_LIMIT_3A5_RESISTANCE         3000
#define EFUSE7_LIMIT_4A_RESISTANCE          2700
#define EFUSE7_LIMIT_4A5_RESISTANCE         2400
#define EFUSE7_LIMIT_5A_RESISTANCE          2100
#define EFUSE7_POT_STEPS                    64 

/**
 * @brief eFuse 7 current limit setting.
 * @details Specified setting for current limit of eFuse 7 Click driver.
 */
#define EFUSE7_CURRENT_LIMIT_1A             0x00
#define EFUSE7_CURRENT_LIMIT_2A             0x01
#define EFUSE7_CURRENT_LIMIT_2A5            0x02
#define EFUSE7_CURRENT_LIMIT_3A             0x03
#define EFUSE7_CURRENT_LIMIT_3A5            0x04
#define EFUSE7_CURRENT_LIMIT_4A             0x05
#define EFUSE7_CURRENT_LIMIT_4A5            0x06
#define EFUSE7_CURRENT_LIMIT_5A             0x07


/*! @} */ // efuse7_set

/**
 * @defgroup efuse7_map eFuse 7 MikroBUS Map
 * @brief MikroBUS pin mapping of eFuse 7 Click driver.
 */

/**
 * @addtogroup efuse7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of eFuse 7 Click to the selected MikroBUS.
 */
#define EFUSE7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI )

/*! @} */ // efuse7_map
/*! @} */ // efuse7

/**
 * @brief eFuse 7 Click context object.
 * @details Context object definition of eFuse 7 Click driver.
 */
typedef struct
{

    digital_out_t rst;      /**< Output enable pin. */
    digital_out_t cs;       /**< Chip Select. */
    digital_out_t sck;      /**< Clock pin. */
    digital_out_t mosi;     /**< Wiper up/down select. */

} efuse7_t;

/**
 * @brief eFuse 7 Click configuration object.
 * @details Configuration object definition of eFuse 7 Click driver.
 */
typedef struct
{
    pin_name_t rst;     /**< Output enable pin. */
    pin_name_t cs;      /**< Chip Select. */
    pin_name_t sck;     /**< Clock pin. */
    pin_name_t mosi;    /**< Wiper up/down select. */

} efuse7_cfg_t;

/**
 * @brief eFuse 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EFUSE7_OK = 0,
    EFUSE7_ERROR = -1

} efuse7_return_value_t;

/*!
 * @addtogroup efuse7 eFuse 7 Click Driver
 * @brief API for configuring and manipulating eFuse 7 Click driver.
 * @{
 */

/**
 * @brief eFuse 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #efuse7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void efuse7_cfg_setup ( efuse7_cfg_t *cfg );

/**
 * @brief eFuse 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #efuse7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #efuse7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse7_init ( efuse7_t *ctx, efuse7_cfg_t *cfg );

/**
 * @brief eFuse 7 default configuration function.
 * @details This function executes a default configuration of eFuse 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #efuse7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t efuse7_default_cfg ( efuse7_t *ctx );

/**
 * @brief eFuse 7 output enable function.
 * @details This function enables output of eFuse 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #efuse7_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void efuse7_enable_output ( efuse7_t *ctx );

/**
 * @brief eFuse 7 output disable function.
 * @details This function disables output of eFuse 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #efuse7_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void efuse7_disable_output ( efuse7_t *ctx );

/**
 * @brief eFuse 7 wiper position increase function.
 * @details This function increases wiper position of eFuse 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #efuse7_t object definition for detailed explanation.
 * @param[in] inc_num : Wiper position increases.
 * @return Nothing.
 * @note None.
 */
void efuse7_wiper_inc ( efuse7_t *ctx, uint8_t inc_num );

/**
 * @brief eFuse 7 wiper position decrease function.
 * @details This function decreases wiper position of eFuse 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #efuse7_t object definition for detailed explanation.
 * @param[in] dec_num : Wiper position decreases.
 * @return Nothing.
 * @note None.
 */
void efuse7_wiper_dec ( efuse7_t *ctx, uint8_t dec_num );

/**
 * @brief eFuse 7 set digital potentiometer resistance function.
 * @details This function sets digital potentiometer resistance of eFuse 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #efuse7_t object definition for detailed explanation.
 * @param[in] resistance : Digital potentiometer resistance in ohms.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse7_set_resistance ( efuse7_t *ctx, uint16_t resistance );

/**
 * @brief eFuse 7 set current limit function.
 * @details This function sets current limit of eFuse 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #efuse7_t object definition for detailed explanation.
 * @param[in] set_current : Specific eFuse current limit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t efuse7_set_limit ( efuse7_t *ctx, uint8_t set_current );

#ifdef __cplusplus
}
#endif
#endif // EFUSE7_H

/*! @} */ // efuse7

// ------------------------------------------------------------------------ END
