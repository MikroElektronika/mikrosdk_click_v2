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
 * @file currentlimit10.h
 * @brief This file contains API for Current Limit 10 Click Driver.
 */

#ifndef CURRENTLIMIT10_H
#define CURRENTLIMIT10_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup currentlimit10 Current Limit 10 Click Driver
 * @brief API for configuring and manipulating Current Limit 10 Click driver.
 * @{
 */

/**
 * @defgroup currentlimit10_reg Current Limit 10 Registers List
 * @brief List of registers of Current Limit 10 Click driver.
 */

/**
 * @addtogroup currentlimit10_reg
 * @{
 */

/**
 * @brief Current Limit 10 description register.
 * @details Specified register for description of Current Limit 10 Click driver.
 */
#define CURRENTLIMIT10_CMD_VREG              0x11
#define CURRENTLIMIT10_CMD_NVREG             0x21
#define CURRENTLIMIT10_CMD_VREGxNVREG        0x51
#define CURRENTLIMIT10_CMD_NVREGxVREG        0x61

/*! @} */ // currentlimit10_reg

/**
 * @defgroup currentlimit10_set Current Limit 10 Registers Settings
 * @brief Settings for registers of Current Limit 10 Click driver.
 */

/**
 * @addtogroup currentlimit10_set
 * @{
 */

/**
 * @brief Current Limit 10 wiper and resistance data values.
 * @details Specified wiper and resistance data values of Current Limit 10 Click driver.
 */
#define CURRENTLIMIT10_WIPER_POS_MIN         0
#define CURRENTLIMIT10_WIPER_POS_MIDDLE      127
#define CURRENTLIMIT10_WIPER_POS_MAX         255
#define CURRENTLIMIT10_RES_200_KOHM          200.0f

/**
 * @brief Current Limit 10 wiper and resistance data values.
 * @details Specified wiper and resistance data values of Current Limit 10 Click driver.
 */
#define CURRENTLIMIT10_FAULT_FLAG            0

/**
 * @brief Current Limit 10 current limit data values.
 * @details Current limit data values of Current Limit 10 Click driver.
 */
#define CURRENTLIMIT10_COEFF_MULTI           0.37f
#define CURRENTLIMIT10_TYP_V_ILIM_MV         289.0f
#define CURRENTLIMIT10_RES_L_20_KOHM         20.0f
#define CURRENTLIMIT10_LIMIT_MIN             0.5f
#define CURRENTLIMIT10_LIMIT_MAX             5.5f

/**
 * @brief Current Limit 10 device address setting.
 * @details Specified setting for device slave address selection of
 * Current Limit 10 Click driver.
 */
#define CURRENTLIMIT10_DEVICE_ADDRESS        0x28

/*! @} */ // currentlimit10_set

/**
 * @defgroup currentlimit10_map Current Limit 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Current Limit 10 Click driver.
 */

/**
 * @addtogroup currentlimit10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current Limit 10 Click to the selected MikroBUS.
 */
#define CURRENTLIMIT10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );    \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );    \
    cfg.on  = MIKROBUS( mikrobus, MIKROBUS_RST );    \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // currentlimit10_map
/*! @} */ // currentlimit10

/**
 * @brief Current Limit 10 Click context object.
 * @details Context object definition of Current Limit 10 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t on;    /**< Enable pin. */

    // Input pins
    digital_in_t flt;    /**< Fault indicator. */

    float offset;        /**< ILIM voltage offset (percent). */

    // Modules
    i2c_master_t i2c;    /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} currentlimit10_t;

/**
 * @brief Current Limit 10 Click configuration object.
 * @details Configuration object definition of Current Limit 10 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t on;     /**< Enable pin. */
    pin_name_t flt;    /**< Fault indicator. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} currentlimit10_cfg_t;

/**
 * @brief Current Limit 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENTLIMIT10_OK = 0,
    CURRENTLIMIT10_ERROR = -1

} currentlimit10_return_value_t;

/*!
 * @addtogroup currentlimit10 Current Limit 10 Click Driver
 * @brief API for configuring and manipulating Current Limit 10 Click driver.
 * @{
 */

/**
 * @brief Current Limit 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #currentlimit10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void currentlimit10_cfg_setup ( currentlimit10_cfg_t *cfg );

/**
 * @brief Current Limit 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #currentlimit10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #currentlimit10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit10_init ( currentlimit10_t *ctx, currentlimit10_cfg_t *cfg );

/**
 * @brief Current Limit 10 default configuration function.
 * @details This function executes a default configuration of Current Limit 10
 * click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t currentlimit10_default_cfg ( currentlimit10_t *ctx );

/**
 * @brief Current Limit 10 enable the device function.
 * @details This function turns on the power switch and enables the internal MOSFET
 * of the HS2950P, 29V 5A Load Protection HotSwitch with Adjustable OVP, OCP and SS
 * on the Current Limit 10 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit10_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void currentlimit10_enable ( currentlimit10_t *ctx );

/**
 * @brief Current Limit 10 disable the device function.
 * @details This function turns off power switch and disable 
 * of the HS2950P, 29V 5A Load Protection HotSwitch with Adjustable OVP, OCP and SS
 * on the Current Limit 10 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit10_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void currentlimit10_disable ( currentlimit10_t *ctx );

/**
 * @brief Current Limit 10 I2C writing function.
 * @details This function writes the desired byte of data using the selected command 
 * using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #currentlimit10_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit10_write_data ( currentlimit10_t *ctx, uint8_t cmd, uint8_t data_in );

/**
 * @brief Current Limit 10 sets the wiper position function.
 * @details This function sets the wiper position
 * of the MAX5419LETA+T, 256-Tap, Nonvolatile, I2C-Interface,
 * Digital Potentiometers on the Current Limit 10 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit10_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position [0-255].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit10_set_wiper_pos ( currentlimit10_t *ctx, uint8_t wiper_pos );

/**
 * @brief Current Limit 10 sets the resistance function.
 * @details This function sets the resistance
 * of the MAX5419LETA+T, 256-Tap, Nonvolatile, I2C-Interface,
 * Digital Potentiometers on the Current Limit 10 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit10_t object definition for detailed explanation.
 * @param[in] res_kohm : Resistance [0-200kOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit10_set_resistance ( currentlimit10_t *ctx, float res_kohm );

/**
 * @brief Current Limit 10 sets the current limit function.
 * @details This function sets the desired current limit threshold
 * using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #currentlimit10_t object definition for detailed explanation.
 * @param[in] current_limit : Current limit [0.5mA-5.5mA]
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit10_set_limit ( currentlimit10_t *ctx, float current_limit );

/**
 * @brief Current Limit 10 get the fault flag function.
 * @details This function gets the state of the fault flag to indicate 
 * overcurrent, overtemperature, or reverse-voltage conditions
 * of the HS2950P, 29V 5A Load Protection HotSwitch with Adjustable OVP, OCP and SS
 * on the Current Limit 10 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit10_t object definition for detailed explanation.
 * @param[in] current_limit : Current limit [0.5mA-5.5mA]
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t currentlimit10_get_fault ( currentlimit10_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CURRENTLIMIT10_H

/*! @} */ // currentlimit10

// ------------------------------------------------------------------------ END
