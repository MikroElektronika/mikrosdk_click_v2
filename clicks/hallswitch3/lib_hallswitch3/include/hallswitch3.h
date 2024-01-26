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
 * @file hallswitch3.h
 * @brief This file contains API for Hall Switch 3 Click Driver.
 */

#ifndef HALLSWITCH3_H
#define HALLSWITCH3_H

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
 * @addtogroup hallswitch3 Hall Switch 3 Click Driver
 * @brief API for configuring and manipulating Hall Switch 3 Click driver.
 * @{
 */

/**
 * @defgroup hallswitch3_reg Hall Switch 3 Registers List
 * @brief List of registers of Hall Switch 3 Click driver.
 */

/**
 * @addtogroup hallswitch3_reg
 * @{
 */

/**
 * @brief Hall Switch 3 description register.
 * @details Specified register for description of Hall Switch 3 Click driver.
 */
#define HALLSWITCH3_REG_STATUS                0x00
#define HALLSWITCH3_REG_CONTROL_REG1          0x01
#define HALLSWITCH3_REG_OUT_M_REG             0x03
#define HALLSWITCH3_REG_USER_ASSERT_THRESH    0x04
#define HALLSWITCH3_REG_USER_CLEAR_THRESH     0x05
#define HALLSWITCH3_REG_USER_ODR              0x06
#define HALLSWITCH3_REG_WHO_AM_I              0x08
#define HALLSWITCH3_REG_I2C_ADDR              0x09

/*! @} */ // hallswitch3_reg

/**
 * @defgroup hallswitch3_set Hall Switch 3 Registers Settings
 * @brief Settings for registers of Hall Switch 3 Click driver.
 */

/**
 * @addtogroup hallswitch3_set
 * @{
 */

/**
 * @brief Hall Switch 3 status reporting of modes and selections bit descriptions.
 * @details Status reporting of modes and selections bit descriptions of Hall Switch 3 Click driver.
 */
#define HALLSWITCH3_STATUS_OUT_B_CLEAR        0x00
#define HALLSWITCH3_STATUS_OUT_B_ASSERT       0x01
#define HALLSWITCH3_STATUS_RST_COMPLETE       0x00
#define HALLSWITCH3_STATUS_RST_NOT_COMPLETE   0x02
#define HALLSWITCH3_STATUS_OPMODE_SA          0x00
#define HALLSWITCH3_STATUS_OPMODE_I2C         0x08
#define HALLSWITCH3_STATUS_MDR_DATA_RDY       0x00
#define HALLSWITCH3_STATUS_MDR_DATA_NO_RDY    0x20
#define HALLSWITCH3_STATUS_MDO_DATA_OK        0x00
#define HALLSWITCH3_STATUS_MDO_DATA_FAULT     0x40
#define HALLSWITCH3_STATUS_VOUT_LOW           0x00
#define HALLSWITCH3_STATUS_VOUT_HIGH          0x80

/**
 * @brief Hall Switch 3 control of operations bit allocation.
 * @details Control of operations bit allocation of Hall Switch 3 Click driver.
 */
#define HALLSWITCH3_CONTROL_SW_RESET          0x01
#define HALLSWITCH3_CONTROL_ONE_SHOT          0x04
#define HALLSWITCH3_CONTROL_AUTO_STOP         0x00
#define HALLSWITCH3_CONTROL_AUTO_START        0x08
#define HALLSWITCH3_CONTROL_V_POL_ASSERT_H    0x00
#define HALLSWITCH3_CONTROL_V_POL_ASSERT_L    0x20

/**
 * @brief Hall Switch 3 threshold bitmask.
 * @details User selectable output threshold bitmask of Hall Switch 3 Click driver.
 */
#define HALLSWITCH3_ASSERT_THOLD_DEFAULT      0x10
#define HALLSWITCH3_CLEAR_THOLD_DEFAULT       0x15
#define HALLSWITCH3_THOLD_BITMASK             0x1F

/**
 * @brief Hall Switch 3 magnetic strength report bit description.
 * @details Magnetic strength report bit description of Hall Switch 3 Click driver.
 */
#define HALLSWITCH3_OUT_M_RES_RST             0x00
#define HALLSWITCH3_OUT_M_RES_LOWEST          0x01
#define HALLSWITCH3_OUT_M_RES_HIGHEST         0x1F

/**
 * @brief Hall Switch 3 output data rates bit description.
 * @details User selectable sleep sample output data rates bit description of Hall Switch 3 Click driver.
 */
#define HALLSWITCH3_USER_ODR_LSP              0x1F
#define HALLSWITCH3_USER_ODR_LSP              0x00
#define HALLSWITCH3_USER_ODR_LSP_X5           0x01
#define HALLSWITCH3_USER_ODR_MSP              0x02
#define HALLSWITCH3_USER_ODR_MSP_X5           0x03
#define HALLSWITCH3_USER_ODR_HSP              0x04
#define HALLSWITCH3_USER_ODR_HSP_X5           0x05
#define HALLSWITCH3_USER_ODR_HSP_X10          0x06
#define HALLSWITCH3_USER_ODR_CFG_ERR          0x07

/**
 * @brief Hall Switch 3 OUT pin states.
 * @details OUT pin states of Hall Switch 3 Click driver.
 */
#define HALLSWITCH3_OUT_STATE_LOW             0x00
#define HALLSWITCH3_OUT_STATE_HIGH            0x01

/**
 * @brief Hall Switch 3 threshold bitmask.
 * @details User selectable output threshold bitmask of Hall Switch 3 Click driver.
 */
#define HALLSWITCH3_WHO_AM_I                  0x01

/**
 * @brief Hall Switch 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Hall Switch 3 Click driver.
 */
#define HALLSWITCH3_DEVICE_ADDRESS            0x60

/*! @} */ // hallswitch3_set

/**
 * @defgroup hallswitch3_map Hall Switch 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Hall Switch 3 Click driver.
 */

/**
 * @addtogroup hallswitch3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Hall Switch 3 Click to the selected MikroBUS.
 */
#define HALLSWITCH3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.out = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hallswitch3_map
/*! @} */ // hallswitch3

/**
 * @brief Hall Switch 3 Click context object.
 * @details Context object definition of Hall Switch 3 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t out;       /**< Output indicating absence of field. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} hallswitch3_t;

/**
 * @brief Hall Switch 3 Click configuration object.
 * @details Configuration object definition of Hall Switch 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t out;    /**< Output indicating absence of field. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} hallswitch3_cfg_t;

/**
 * @brief Hall Switch 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HALLSWITCH3_OK = 0,
    HALLSWITCH3_ERROR = -1

} hallswitch3_return_value_t;

/*!
 * @addtogroup hallswitch3 Hall Switch 3 Click Driver
 * @brief API for configuring and manipulating Hall Switch 3 Click driver.
 * @{
 */

/**
 * @brief Hall Switch 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hallswitch3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hallswitch3_cfg_setup ( hallswitch3_cfg_t *cfg );

/**
 * @brief Hall Switch 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hallswitch3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch3_init ( hallswitch3_t *ctx, hallswitch3_cfg_t *cfg );

/**
 * @brief Hall Switch 3 default configuration function.
 * @details This function executes a default configuration of Hall Switch 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hallswitch3_default_cfg ( hallswitch3_t *ctx );

/**
 * @brief Hall Switch 3 I2C writing function.
 * @details This function writes a data byte to
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch3_reg_write ( hallswitch3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Hall Switch 3 I2C reading function.
 * @details This function reads a data byte from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch3_reg_read ( hallswitch3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Hall Switch 3 get status function.
 * @details This function reads a status reporting of modes and selections
 * of the NMH1000, Magnetic switch on the Hall Switch 3 Click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @param[out] status : Status reporting data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch3_get_status ( hallswitch3_t *ctx, uint8_t *status );

/**
 * @brief Hall Switch 3 software reset function.
 * @details This function performs the internal device reset is forced
 * of the NMH1000, Magnetic switch on the Hall Switch 3 Click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch3_reset ( hallswitch3_t *ctx );

/**
 * @brief Hall Switch 3 sets one-shot function.
 * @details This function provides control of the state machine 
 * to trigger a single sequence of compare 
 * of the NMH1000, Magnetic switch on the Hall Switch 3 Click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch3_set_one_shot ( hallswitch3_t *ctx );

/**
 * @brief Hall Switch 3 autonomous mode function.
 * @details This function starts the autonomous mode active 
 * to trigger a single sequence of compare 
 * of the NMH1000, Magnetic switch on the Hall Switch 3 Click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch3_autonomous_mode ( hallswitch3_t *ctx );

/**
 * @brief Hall Switch 3 set VPOL function.
 * @details This function provides control of the user-defined OUT pin 
 * and resultant bit assert or clear polarity
 * of the NMH1000, Magnetic switch on the Hall Switch 3 Click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @param[in] v_pol : VPOL assert or clear polarity.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch3_set_vpol ( hallswitch3_t *ctx, uint8_t v_pol );

/**
 * @brief Hall Switch 3 get mag data function.
 * @details This function is used to indicates a relative magnetic field strength
 * of the NMH1000, Magnetic switch on the Hall Switch 3 Click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @param[out] mag_data : Relative magnetic field strength data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch3_get_mag_data ( hallswitch3_t *ctx, int8_t *mag_data );

/**
 * @brief Hall Switch 3 sets assert and clear threshold function.
 * @details This function is used to sets the range of the magnetic field to assert/clear the output
 * of the NMH1000, Magnetic switch on the Hall Switch 3 Click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @param[in] assert_thold : Assert threshold data [0x00-0x1F].
 * @param[in] clear_thold : Clear threshold data [0x00-0x1F].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch3_set_threshold ( hallswitch3_t *ctx, uint8_t assert_thold, uint8_t clear_thold );

/**
 * @brief Hall Switch 3 sets output data rates function.
 * @details This function provides the capability for the user 
 * to override the fixed sample rate controlling the sleep-compare-Vout cycle time
 * of the NMH1000, Magnetic switch on the Hall Switch 3 Click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @param[in] odr : Output data rates [0x00-0x06].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch3_set_out_data_rate ( hallswitch3_t *ctx, uint8_t odr );

/**
 * @brief Hall Switch 3 get device ID function.
 * @details This function reads the device identification data
 * of the NMH1000, Magnetic switch on the Hall Switch 3 Click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @param[out] device_id : Device identification.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hallswitch3_get_device_id ( hallswitch3_t *ctx, uint8_t *device_id );

/**
 * @brief Hall Switch 3 check magnetic field function.
 * @details This function is used to indicate absence of magnetic field
 * of the NMH1000, Magnetic switch on the Hall Switch 3 Click board.
 * @param[in] ctx : Click context object.
 * See #hallswitch3_t object definition for detailed explanation.
 * @return @li @c 0 - Low state,
 *         @li @c 1 - High state.
 * @note None.
 */
uint8_t hallswitch3_check_mag_field ( hallswitch3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HALLSWITCH3_H

/*! @} */ // hallswitch3

// ------------------------------------------------------------------------ END
