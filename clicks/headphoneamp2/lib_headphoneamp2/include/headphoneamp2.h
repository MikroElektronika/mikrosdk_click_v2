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
 * @brief This file contains API for Headphone AMP 2 Click Driver.
 */

#ifndef HEADPHONEAMP2_H
#define HEADPHONEAMP2_H

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
 * @addtogroup headphoneamp2 Headphone AMP 2 Click Driver
 * @brief API for configuring and manipulating Headphone AMP 2 Click driver.
 * @{
 */

/**
 * @defgroup headphoneamp2_set Headphone AMP 2 Registers Settings
 * @brief Settings for registers of Headphone AMP 2 Click driver.
 */

/**
 * @addtogroup headphoneamp2_set
 * @{
 */

/**
 * @brief Headphone AMP 2 volume level control.
 * @details Specified volume level control of Headphone AMP 2 Click driver.
 */
#define HEADPHONEAMP2_VOL_MUTE              0x00
#define HEADPHONEAMP2_VOL_LVL_1             0x01
#define HEADPHONEAMP2_VOL_LVL_2             0x02
#define HEADPHONEAMP2_VOL_LVL_3             0x03
#define HEADPHONEAMP2_VOL_LVL_4             0x04
#define HEADPHONEAMP2_VOL_LVL_5             0x05
#define HEADPHONEAMP2_VOL_LVL_6             0x06
#define HEADPHONEAMP2_VOL_LVL_7             0x07
#define HEADPHONEAMP2_VOL_LVL_8             0x08
#define HEADPHONEAMP2_VOL_LVL_9             0x09
#define HEADPHONEAMP2_VOL_LVL_10            0x0A
#define HEADPHONEAMP2_VOL_LVL_11            0x0B
#define HEADPHONEAMP2_VOL_LVL_12            0x0C
#define HEADPHONEAMP2_VOL_LVL_13            0x0D
#define HEADPHONEAMP2_VOL_LVL_14            0x0E
#define HEADPHONEAMP2_VOL_LVL_MAX           0x0F

/**
 * @brief Headphone AMP 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Headphone AMP 2 Click driver.
 */
#define HEADPHONEAMP2_DEVICE_ADDRESS        0x4C

/*! @} */ // headphoneamp2_set

/**
 * @defgroup headphoneamp2_map Headphone AMP 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Headphone AMP 2 Click driver.
 */

/**
 * @addtogroup headphoneamp2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Headphone AMP 2 Click to the selected MikroBUS.
 */
#define HEADPHONEAMP2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );   \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );   \
    cfg.shd = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // headphoneamp2_map
/*! @} */ // headphoneamp2

/**
 * @brief Headphone AMP 2 Click context object.
 * @details Context object definition of Headphone AMP 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t shd;        /**< Shutdown pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} headphoneamp2_t;

/**
 * @brief Headphone AMP 2 Click configuration object.
 * @details Configuration object definition of Headphone AMP 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t shd;            /**< Shutdown pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} headphoneamp2_cfg_t;

/**
 * @brief Headphone AMP 2 Click command mode control value data.
 * @details Predefined enum values for command mode control.
 */
typedef enum
{
    HEADPHONEAMP2_CMD_DISABLE = 0,
    HEADPHONEAMP2_CMD_ENABLE

} headphoneamp2_cmd_ctrl_value_t;

/**
 * @brief Headphone AMP 2 Click command object.
 * @details Command object definition of Headphone AMP 2 Click driver.
 */
typedef struct
{
    headphoneamp2_cmd_ctrl_value_t wakes_up;    /**< Wakes-up control. */
    headphoneamp2_cmd_ctrl_value_t bass_max;    /**< Bass control. */
    headphoneamp2_cmd_ctrl_value_t gain_max;    /**< Gain control. */
    uint8_t                        volume;      /**< Volume volume. */

} headphoneamp2_cmd_t;

/**
 * @brief Headphone AMP 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HEADPHONEAMP2_OK = 0,
    HEADPHONEAMP2_ERROR = -1

} headphoneamp2_return_value_t;

/*!
 * @addtogroup headphoneamp2 Headphone AMP 2 Click Driver
 * @brief API for configuring and manipulating Headphone AMP 2 Click driver.
 * @{
 */

/**
 * @brief Headphone AMP 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #headphoneamp2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void headphoneamp2_cfg_setup ( headphoneamp2_cfg_t *cfg );

/**
 * @brief Headphone AMP 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
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
 * @brief Headphone AMP 2 default configuration function.
 * @details This function executes a default configuration of Headphone AMP 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #headphoneamp2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t headphoneamp2_default_cfg ( headphoneamp2_t *ctx );

/**
 * @brief Headphone AMP 2 I2C writing function.
 * @details This function writes a desired data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #headphoneamp2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t headphoneamp2_write_data ( headphoneamp2_t *ctx, uint8_t data_in );

/**
 * @brief Headphone AMP 2 enable the device function.
 * @details This function enables the device by driving SHD pin to high state 
 * of the MAX9723, Stereo DirectDrive Headphone Amplifier with BassMax, Volume Control, and I2C
 * on the Headphone AMP 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #headphoneamp2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void headphoneamp2_enable ( headphoneamp2_t *ctx );

/**
 * @brief Headphone AMP 2 disable the device function.
 * @details This function disables the device by driving SHD pin to low state 
 * of the MAX9723, Stereo DirectDrive Headphone Amplifier with BassMax, Volume Control, and I2C
 * on the Headphone AMP 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #headphoneamp2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void headphoneamp2_disable ( headphoneamp2_t *ctx );

/**
 * @brief Headphone AMP 2 set the command function.
 * @details This function set the command 
 * of the MAX9723, Stereo DirectDrive Headphone Amplifier with BassMax, Volume Control, and I2C
 * on the Headphone AMP 2 Click board™.
 * @param[in] ctx : Click context object.
 * See #headphoneamp2_t object definition for detailed explanation.
 * @param[in] cmd_ctrl : Click command object.
 * See headphoneamp2_cmd_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t headphoneamp2_set_command ( headphoneamp2_t *ctx, headphoneamp2_cmd_t cmd_ctrl );

#ifdef __cplusplus
}
#endif
#endif // HEADPHONEAMP2_H

/*! @} */ // headphoneamp2

// ------------------------------------------------------------------------ END
