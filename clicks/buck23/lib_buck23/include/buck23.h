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
 * @file buck23.h
 * @brief This file contains API for Buck 23 Click Driver.
 */

#ifndef BUCK23_H
#define BUCK23_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup buck23 Buck 23 Click Driver
 * @brief API for configuring and manipulating Buck 23 Click driver.
 * @{
 */

/**
 * @defgroup buck23_reg Buck 23 Registers List
 * @brief List of registers of Buck 23 Click driver.
 */

/**
 * @addtogroup buck23_reg
 * @{
 */

/**
 * @brief Buck 23 register map.
 * @details Specified register map of Buck 23 Click driver.
 */
#define BUCK23_REG_ID                       0x00
#define BUCK23_REG_VIDMAX                   0x02
#define BUCK23_REG_STATUS                   0x04
#define BUCK23_REG_CONFIG                   0x05
#define BUCK23_REG_SLEW                     0x06
#define BUCK23_REG_VID                      0x07

/*! @} */ // buck23_reg

/**
 * @defgroup buck23_set Buck 23 Registers Settings
 * @brief Settings for registers of Buck 23 Click driver.
 */

/**
 * @addtogroup buck23_set
 * @{
 */

/**
 * @brief Buck 23 device ID setting.
 * @details Specified setting for device ID of Buck 23 Click driver.
 */
#define BUCK23_DEVICE_ID                    0x03

/**
 * @brief Buck 23 VIDMAX register setting.
 * @details Specified setting for VIDMAX register of Buck 23 Click driver.
 */
#define BUCK23_VIDMAX_UNCAPPED              0x4E

/**
 * @brief Buck 23 CONFIG register setting.
 * @details Specified setting for CONFIG register of Buck 23 Click driver.
 */
#define BUCK23_CONFIG_VSTEP_10              0x00
#define BUCK23_CONFIG_VSTEP_12_5            0x80
#define BUCK23_CONFIG_VSTEP_MASK            0x80
#define BUCK23_CONFIG_MODE_SYNC             0x00
#define BUCK23_CONFIG_MODE_FPWM             0x08
#define BUCK23_CONFIG_MODE_MASK             0x08
#define BUCK23_CONFIG_SS_DIS                0x00
#define BUCK23_CONFIG_SS_3_PCT_SPREAD       0x04
#define BUCK23_CONFIG_SS_MASK               0x04
#define BUCK23_CONFIG_SYNC_IO_IN_RISE       0x00
#define BUCK23_CONFIG_SYNC_IO_IN_FALL       0x01
#define BUCK23_CONFIG_SYNC_IO_OUT_FALL      0x02
#define BUCK23_CONFIG_SYNC_IO_MASK          0x03

/**
 * @brief Buck 23 STATUS register setting.
 * @details Specified setting for STATUS register of Buck 23 Click driver.
 */
#define BUCK23_STATUS_INTERR                0x80
#define BUCK23_STATUS_VRHOT                 0x20
#define BUCK23_STATUS_UV                    0x10
#define BUCK23_STATUS_OV                    0x08
#define BUCK23_STATUS_OC                    0x04
#define BUCK23_STATUS_VMERR                 0x02

/**
 * @brief Buck 23 SLEW register setting.
 * @details Specified setting for SLEW register of Buck 23 Click driver.
 */
#define BUCK23_SLEW_SS_22_DVS_22            0x00
#define BUCK23_SLEW_SS_11_DVS_22            0x01
#define BUCK23_SLEW_SS_5_5_DVS_22           0x02
#define BUCK23_SLEW_SS_11_DVS_11            0x03
#define BUCK23_SLEW_SS_5_5_DVS_11           0x04
#define BUCK23_SLEW_SS_44_DVS_44            0x05
#define BUCK23_SLEW_SS_22_DVS_44            0x06
#define BUCK23_SLEW_SS_11_DVS_44            0x07
#define BUCK23_SLEW_SS_5_5_DVS_44           0x08
#define BUCK23_SLEW_SS_5_5_DVS_5_5          0x09
#define BUCK23_SLEW_MASK                    0x0F

/**
 * @brief Buck 23 voltage output step setting.
 * @details Specified setting for voltage output step of Buck 23 Click driver.
 */
#define BUCK23_VSTEP_10                     0
#define BUCK23_VSTEP_12_5                   1

/**
 * @brief Buck 23 voltage output setting.
 * @details Specified setting for voltage output of Buck 23 Click driver.
 */
#define BUCK23_VID_MIN                      0x01
#define BUCK23_VID_MAX                      0x4E
#define BUCK23_VOUT_MIN_VSTEP_10            500u
#define BUCK23_VOUT_MAX_VSTEP_10            1270u
#define BUCK23_VOUT_MIN_VSTEP_12_5          625u
#define BUCK23_VOUT_MAX_VSTEP_12_5          1587u
#define BUCK23_VOUT_RES_VSTEP_10            10.0f
#define BUCK23_VOUT_RES_VSTEP_12_5          12.5f

/**
 * @brief Buck 23 device address setting.
 * @details Specified setting for device slave address selection of
 * Buck 23 Click driver.
 */
#define BUCK23_DEVICE_ADDRESS_0             0x38
#define BUCK23_DEVICE_ADDRESS_1             0x39

/*! @} */ // buck23_set

/**
 * @defgroup buck23_map Buck 23 MikroBUS Map
 * @brief MikroBUS pin mapping of Buck 23 Click driver.
 */

/**
 * @addtogroup buck23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buck 23 Click to the selected MikroBUS.
 */
#define BUCK23_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sync = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // buck23_map
/*! @} */ // buck23

/**
 * @brief Buck 23 Click context object.
 * @details Context object definition of Buck 23 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;       /**< Enable pin (Active High). */
    digital_out_t sync;     /**< Sync pin (Default: Low). */

    // Input pins
    digital_in_t pg;        /**< Power good pin (Active High). */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */
    
    uint8_t vstep;          /**< Voltage output step settings. */

} buck23_t;

/**
 * @brief Buck 23 Click configuration object.
 * @details Configuration object definition of Buck 23 Click driver.
 */
typedef struct
{
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;          /**< Enable pin (Active High). */
    pin_name_t sync;        /**< Sync pin (Default: Low). */
    pin_name_t pg;          /**< Power good pin (Active High). */

    uint32_t   i2c_speed;   /**< I2C serial speed. */
    uint8_t    i2c_address; /**< I2C slave address. */

} buck23_cfg_t;

/**
 * @brief Buck 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUCK23_OK = 0,
    BUCK23_ERROR = -1

} buck23_return_value_t;

/*!
 * @addtogroup buck23 Buck 23 Click Driver
 * @brief API for configuring and manipulating Buck 23 Click driver.
 * @{
 */

/**
 * @brief Buck 23 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buck23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buck23_cfg_setup ( buck23_cfg_t *cfg );

/**
 * @brief Buck 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buck23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buck23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck23_init ( buck23_t *ctx, buck23_cfg_t *cfg );

/**
 * @brief Buck 23 default configuration function.
 * @details This function executes a default configuration of Buck 23
 * click board.
 * @param[in] ctx : Click context object.
 * See #buck23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t buck23_default_cfg ( buck23_t *ctx );

/**
 * @brief Buck 23 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck23_write_register ( buck23_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Buck 23 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck23_read_register ( buck23_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Buck 23 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #buck23_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void buck23_enable_device ( buck23_t *ctx );

/**
 * @brief Buck 23 disable device function.
 * @details This function disables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #buck23_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void buck23_disable_device ( buck23_t *ctx );

/**
 * @brief Buck 23 restart device function.
 * @details This function restarts the device by toggling the EN pin logic state.
 * @param[in] ctx : Click context object.
 * See #buck23_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void buck23_restart_device ( buck23_t *ctx );

/**
 * @brief Buck 23 set sync pin function.
 * @details This function sets the SYNC pin logic state.
 * @param[in] ctx : Click context object.
 * See #buck23_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void buck23_set_sync_pin ( buck23_t *ctx, uint8_t state );

/**
 * @brief Buck 23 get pg pin function.
 * @details This function returns the PG (power good) pin logic state.
 * @param[in] ctx : Click context object.
 * See #buck23_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t buck23_get_pg_pin ( buck23_t *ctx );

/**
 * @brief Buck 23 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #buck23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The device ID value contains the device revision number, so make sure that the device revision
 * number mathes the value defined in the BUCK23_DEVICE_ID macro.
 */
err_t buck23_check_communication ( buck23_t *ctx );

/**
 * @brief Buck 23 set vstep function.
 * @details This function sets the voltage output step to 10mV or 12.5mV.
 * @param[in] ctx : Click context object.
 * See #buck23_t object definition for detailed explanation.
 * @param[in] vstep : @li @c 0 - 10mV voltage output step - VOUT range: 500mV to 1270mV,
 *                    @li @c 1 - 12.5mV voltage output step - VOUT range: 625mV to 1587.5mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck23_set_vstep ( buck23_t *ctx, uint8_t vstep );

/**
 * @brief Buck 23 set vout function.
 * @details This function sets the voltage output.
 * @param[in] ctx : Click context object.
 * See #buck23_t object definition for detailed explanation.
 * @param[in] vout_mv : Voltage output in millivolts. 
 * Depending on the vstep settings the voltage output ranges from 500mV to 1270mV or from 625mV to 1587.5mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck23_set_vout ( buck23_t *ctx, uint16_t vout_mv );

#ifdef __cplusplus
}
#endif
#endif // BUCK23_H

/*! @} */ // buck23

// ------------------------------------------------------------------------ END
