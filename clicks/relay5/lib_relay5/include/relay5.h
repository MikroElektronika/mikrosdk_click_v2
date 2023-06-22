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
 * @file relay5.h
 * @brief This file contains API for Relay 5 Click Driver.
 */

#ifndef RELAY5_H
#define RELAY5_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup relay5 Relay 5 Click Driver
 * @brief API for configuring and manipulating Relay 5 Click driver.
 * @{
 */

/**
 * @defgroup relay5_reg Relay 5 Registers List
 * @brief List of registers of Relay 5 Click driver.
 */

/**
 * @addtogroup relay5_reg
 * @{
 */

/**
 * @brief Relay 5 PCA9538A registers.
 * @details Specified PCA9538A registers of Relay 5 Click driver.
 */
#define RELAY5_REG_INPUT                    0x00
#define RELAY5_REG_OUTPUT                   0x01
#define RELAY5_REG_POLARITY                 0x02
#define RELAY5_REG_CONFIG                   0x03

/*! @} */ // relay5_reg

/**
 * @defgroup relay5_set Relay 5 Registers Settings
 * @brief Settings for registers of Relay 5 Click driver.
 */

/**
 * @addtogroup relay5_set
 * @{
 */

/**
 * @brief Relay 5 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Relay 5 Click driver.
 */
#define RELAY5_DEFAULT_CONFIG               0xF8

/**
 * @brief Relay 5 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Relay 5 Click driver.
 */
#define RELAY5_PIN_RL3                      0x01
#define RELAY5_PIN_RL2                      0x02
#define RELAY5_PIN_RL1                      0x04

/**
 * @brief Relay 5 pin logic state setting.
 * @details Specified setting for pin logic state of Relay 5 Click driver.
 */
#define RELAY5_PIN_STATE_LOW                0
#define RELAY5_PIN_STATE_HIGH               1

/**
 * @brief Relay 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Relay 5 Click driver.
 */
#define RELAY5_DEVICE_ADDRESS_A1A0_00       0x70
#define RELAY5_DEVICE_ADDRESS_A1A0_01       0x71
#define RELAY5_DEVICE_ADDRESS_A1A0_10       0x72
#define RELAY5_DEVICE_ADDRESS_A1A0_11       0x73

/*! @} */ // relay5_set

/**
 * @defgroup relay5_map Relay 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Relay 5 Click driver.
 */

/**
 * @addtogroup relay5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Relay 5 Click to the selected MikroBUS.
 */
#define RELAY5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // relay5_map
/*! @} */ // relay5

/**
 * @brief Relay 5 Click context object.
 * @details Context object definition of Relay 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< PCA9538A reset pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} relay5_t;

/**
 * @brief Relay 5 Click configuration object.
 * @details Configuration object definition of Relay 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< PCA9538A reset pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} relay5_cfg_t;

/**
 * @brief Relay 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RELAY5_OK = 0,
    RELAY5_ERROR = -1

} relay5_return_value_t;

/*!
 * @addtogroup relay5 Relay 5 Click Driver
 * @brief API for configuring and manipulating Relay 5 Click driver.
 * @{
 */

/**
 * @brief Relay 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #relay5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void relay5_cfg_setup ( relay5_cfg_t *cfg );

/**
 * @brief Relay 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #relay5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay5_init ( relay5_t *ctx, relay5_cfg_t *cfg );

/**
 * @brief Relay 5 default configuration function.
 * @details This function executes a default configuration of Relay 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t relay5_default_cfg ( relay5_t *ctx );

/**
 * @brief Relay 5 write register function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay5_write_register ( relay5_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Relay 5 read register function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay5_read_register ( relay5_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Relay 5 set relay 1 open function.
 * @details This function sets the relay 1 to normally open state by setting the RL1 pin to low logic level.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay5_set_relay1_open ( relay5_t *ctx );

/**
 * @brief Relay 5 set relay 1 close function.
 * @details This function sets the relay 1 to normally close state by setting the RL1 pin to high logic level.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay5_set_relay1_close ( relay5_t *ctx );

/**
 * @brief Relay 5 switch relay 1 function.
 * @details This function switches the relay 1 state by toggling the RL1 pin logic level.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay5_switch_relay1 ( relay5_t *ctx );

/**
 * @brief Relay 5 set relay 2 open function.
 * @details This function sets the relay 2 to normally open state by setting the RL2 pin to low logic level.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay5_set_relay2_open ( relay5_t *ctx );

/**
 * @brief Relay 5 set relay 2 close function.
 * @details This function sets the relay 2 to normally close state by setting the RL2 pin to high logic level.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay5_set_relay2_close ( relay5_t *ctx );

/**
 * @brief Relay 5 switch relay 2 function.
 * @details This function switches the relay 2 state by toggling the RL2 pin logic level.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay5_switch_relay2 ( relay5_t *ctx );

/**
 * @brief Relay 5 set relay 3 open function.
 * @details This function sets the relay 3 to normally open state by setting the RL3 pin to low logic level.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay5_set_relay3_open ( relay5_t *ctx );

/**
 * @brief Relay 5 set relay 3 close function.
 * @details This function sets the relay 3 to normally close state by setting the RL3 pin to high logic level.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay5_set_relay3_close ( relay5_t *ctx );

/**
 * @brief Relay 5 switch relay 3 function.
 * @details This function switches the relay 3 state by toggling the RL3 pin logic level.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay5_switch_relay3 ( relay5_t *ctx );

/**
 * @brief Relay 5 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void relay5_set_rst_pin ( relay5_t *ctx, uint8_t state );

/**
 * @brief Relay 5 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #relay5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void relay5_reset_device ( relay5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RELAY5_H

/*! @} */ // relay5

// ------------------------------------------------------------------------ END
