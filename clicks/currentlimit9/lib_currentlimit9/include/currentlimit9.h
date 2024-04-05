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
 * @file currentlimit9.h
 * @brief This file contains API for Current Limit 9 Click Driver.
 */

#ifndef CURRENTLIMIT9_H
#define CURRENTLIMIT9_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup currentlimit9 Current Limit 9 Click Driver
 * @brief API for configuring and manipulating Current Limit 9 Click driver.
 * @{
 */

/**
 * @defgroup currentlimit9_reg Current Limit 9 Registers List
 * @brief List of registers of Current Limit 9 Click driver.
 */

/**
 * @addtogroup currentlimit9_reg
 * @{
 */

/**
 * @brief Current Limit 9 description register.
 * @details Specified register for description of Current Limit 9 Click driver.
 */
#define CURRENTLIMIT9_CMD_VREG              0x11
#define CURRENTLIMIT9_CMD_NVREG             0x21
#define CURRENTLIMIT9_CMD_VREGxNVREG        0x51
#define CURRENTLIMIT9_CMD_NVREGxVREG        0x61

/*! @} */ // currentlimit9_reg

/**
 * @defgroup currentlimit9_set Current Limit 9 Registers Settings
 * @brief Settings for registers of Current Limit 9 Click driver.
 */

/**
 * @addtogroup currentlimit9_set
 * @{
 */

/**
 * @brief Current Limit 9 wiper and resistance data values.
 * @details Specified wiper and resistance data values of Current Limit 9 Click driver.
 */
#define CURRENTLIMIT9_WIPER_POS_MIN         0
#define CURRENTLIMIT9_WIPER_POS_MIDDLE      127
#define CURRENTLIMIT9_WIPER_POS_MAX         255
#define CURRENTLIMIT9_RES_200_KOHM          200.0f

/**
 * @brief Current Limit 9 wiper and resistance data values.
 * @details Specified wiper and resistance data values of Current Limit 9 Click driver.
 */
#define CURRENTLIMIT9_FAULT_FLAG            0

/**
 * @brief Current Limit 9 description setting.
 * @details Specified setting for description of Current Limit 9 Click driver.
 */
#define CURRENTLIMIT9_RESISTANCE            200.0f, 39.9f, 10.0f, 5.0f, 2.7f, 2.2f, 1.5f

/**
 * @brief Current Limit 9 device address setting.
 * @details Specified setting for device slave address selection of
 * Current Limit 9 Click driver.
 */
#define CURRENTLIMIT9_DEVICE_ADDRESS        0x28

/*! @} */ // currentlimit9_set

/**
 * @defgroup currentlimit9_map Current Limit 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Current Limit 9 Click driver.
 */

/**
 * @addtogroup currentlimit9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current Limit 9 Click to the selected MikroBUS.
 */
#define CURRENTLIMIT9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );   \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );   \
    cfg.on  = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // currentlimit9_map
/*! @} */ // currentlimit9

/**
 * @brief Current Limit 9 Click context object.
 * @details Context object definition of Current Limit 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t on;    /**< Control signal to turn on/off the device. */

    // Input pins
    digital_in_t flt;    /**< Fault indicator. */

    // Modules
    i2c_master_t i2c;    /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} currentlimit9_t;

/**
 * @brief Current Limit 9 Click configuration object.
 * @details Configuration object definition of Current Limit 9 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */


    pin_name_t on;     /**< Control signal to turn on/off the device. */
    pin_name_t flt;    /**< Fault indicator. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} currentlimit9_cfg_t;

/**
 * @brief Current Limit 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENTLIMIT9_OK = 0,
    CURRENTLIMIT9_ERROR = -1

} currentlimit9_return_value_t;

/**
 * @brief Current Limit 9 current limit values.
 * @details Predefined enum values for current limits.
 */
typedef enum
{
    CURRENTLIMIT9_LIMIT_0_11_A = 0,
    CURRENTLIMIT9_LIMIT_0_46_A,
    CURRENTLIMIT9_LIMIT_1_17_A,
    CURRENTLIMIT9_LIMIT_1_55_A,
    CURRENTLIMIT9_LIMIT_1_67_A,
    CURRENTLIMIT9_LIMIT_1_84_A,
    CURRENTLIMIT9_LIMIT_1_90_A

} currentlimit9_limit_t;

/*!
 * @addtogroup currentlimit9 Current Limit 9 Click Driver
 * @brief API for configuring and manipulating Current Limit 9 Click driver.
 * @{
 */

/**
 * @brief Current Limit 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #currentlimit9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void currentlimit9_cfg_setup ( currentlimit9_cfg_t *cfg );

/**
 * @brief Current Limit 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #currentlimit9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #currentlimit9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit9_init ( currentlimit9_t *ctx, currentlimit9_cfg_t *cfg );

/**
 * @brief Current Limit 9 default configuration function.
 * @details This function executes a default configuration of Current Limit 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t currentlimit9_default_cfg ( currentlimit9_t *ctx );

/**
 * @brief Current Limit 9 enable the device function.
 * @details This function turns on the power switch and enables the current limit
 * of the NPS4053, 5.5 V, 55 mOhm load switch with precision adjustable current limit
 * on the Current Limit 9 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void currentlimit9_enable ( currentlimit9_t *ctx );

/**
 * @brief Current Limit 9 disable the device function.
 * @details This function turns off power switch and disable 
 * the NPS4053, 5.5 V, 55 mOhm load switch with precision adjustable current limit
 * on the Current Limit 9 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void currentlimit9_disable ( currentlimit9_t *ctx );

/**
 * @brief Current Limit 9 I2C writing function.
 * @details This function writes the desired byte of data using the selected command 
 * using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #currentlimit9_t object definition for detailed explanation.
 * @param[in] cmd : Desired command.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit9_write_data ( currentlimit9_t *ctx, uint8_t cmd, uint8_t data_in );

/**
 * @brief Current Limit 9 sets the wiper position function.
 * @details This function sets the wiper position
 * of the MAX5419LETA+T, 256-Tap, Nonvolatile, I2C-Interface,
 * Digital Potentiometers on the Current Limit 9 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit9_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position [0-255].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit9_set_wiper_pos ( currentlimit9_t *ctx, uint8_t wiper_pos );

/**
 * @brief Current Limit 9 sets the resistance function.
 * @details This function sets the resistance
 * of the MAX5419LETA+T, 256-Tap, Nonvolatile, I2C-Interface,
 * Digital Potentiometers on the Current Limit 9 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit9_t object definition for detailed explanation.
 * @param[in] res_kohm : Resistance [0-200kOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit9_set_resistance ( currentlimit9_t *ctx, float res_kohm );

/**
 * @brief Current Limit 9 sets the current limit function.
 * @details This function sets the desired current limit threshold
 * using the I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #currentlimit9_t object definition for detailed explanation.
 * @param[in] current_limit : Current limit.
 * See #currentlimit9_limit_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit9_set_limit ( currentlimit9_t *ctx, currentlimit9_limit_t current_limit );

/**
 * @brief Current Limit 9 get the fault flag function.
 * @details This function gets the state of the fault flag to indicate 
 * overcurrent, overtemperature, or reverse-voltage conditions
 * of the NPS4053, 5.5 V, 55 mOhm load switch with precision adjustable current limit
 * on the Current Limit 9 Click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit9_t object definition for detailed explanation.
 * @param[in] res_kohm : Resistance [0-200kOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t currentlimit9_get_fault ( currentlimit9_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CURRENTLIMIT9_H

/*! @} */ // currentlimit9

// ------------------------------------------------------------------------ END
