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
 * @file relay6.h
 * @brief This file contains API for Relay 6 Click Driver.
 */

#ifndef RELAY6_H
#define RELAY6_H

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
 * @addtogroup relay6 Relay 6 Click Driver
 * @brief API for configuring and manipulating Relay 6 Click driver.
 * @{
 */

/**
 * @defgroup relay6_reg Relay 6 Registers List
 * @brief List of registers of Relay 6 Click driver.
 */

/**
 * @addtogroup relay6_reg
 * @{
 */

/**
 * @brief Relay 6 description register.
 * @details Specified register for description of Relay 6 Click driver.
 */
#define RELAY6_REG_INPUT_PORT                   0x00
#define RELAY6_REG_OUTPUT_PORT                  0x01
#define RELAY6_REG_POLARITY_INV                 0x02
#define RELAY6_REG_CONFIG                       0x03

/*! @} */ // relay6_reg

/**
 * @defgroup relay6_set Relay 6 Registers Settings
 * @brief Settings for registers of Relay 6 Click driver.
 */

/**
 * @addtogroup relay6_set
 * @{
 */

/**
 * @brief Relay 6 description setting.
 * @details Specified setting for description of Relay 6 Click driver.
 */
#define RELAY6_NONE_PIN                         0x00
#define RELAY6_RELAY1_PIN                       0x01
#define RELAY6_RELAY2_PIN                       0x02
#define RELAY6_RELAY3_PIN                       0x04
#define RELAY6_RELAY4_PIN                       0x08
#define RELAY6_ALL_PIN                          0x0F

/**
 * @brief Relay 6 pin setting.
 * @details Specified setting for pin selection of
 * Relay 6 Click driver.
 */
#define RELAY6_PIN_STATE_HIGH                   0x01
#define RELAY6_PIN_STATE_LOW                    0x00

/**
 * @brief Relay 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Relay 6 Click driver.
 */
#define RELAY6_DEVICE_ADDRESS_A1A0_00           0x70
#define RELAY6_DEVICE_ADDRESS_A1A0_01           0x71
#define RELAY6_DEVICE_ADDRESS_A1A0_10           0x72
#define RELAY6_DEVICE_ADDRESS_A1A0_11           0x73

/*! @} */ // relay6_set

/**
 * @defgroup relay6_map Relay 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Relay 6 Click driver.
 */

/**
 * @addtogroup relay6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Relay 6 Click to the selected MikroBUS.
 */
#define RELAY6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // relay6_map
/*! @} */ // relay6

/**
 * @brief Relay 6 Click context object.
 * @details Context object definition of Relay 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} relay6_t;

/**
 * @brief Relay 6 Click configuration object.
 * @details Configuration object definition of Relay 6 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} relay6_cfg_t;

/**
 * @brief Relay 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RELAY6_OK = 0,
    RELAY6_ERROR = -1

} relay6_return_value_t;

/*!
 * @addtogroup relay6 Relay 6 Click Driver
 * @brief API for configuring and manipulating Relay 6 Click driver.
 * @{
 */

/**
 * @brief Relay 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #relay6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void relay6_cfg_setup ( relay6_cfg_t *cfg );

/**
 * @brief Relay 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #relay6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #relay6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay6_init ( relay6_t *ctx, relay6_cfg_t *cfg );

/**
 * @brief Relay 6 default configuration function.
 * @details This function executes a default configuration of Relay 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #relay6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t relay6_default_cfg ( relay6_t *ctx );

/**
 * @brief Relay 6 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #relay6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay6_generic_write ( relay6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Relay 6 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #relay6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay6_generic_read ( relay6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Relay 6 set RST pin function.
 * @details This function is used to set state of the RST pin.
 * @param[in] ctx : Click context object.
 * See #relay6_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return Nothing.
 * @note None.
 */
void relay6_set_rst_pin ( relay6_t *ctx, uint8_t pin_state );

/**
 * @brief Relay 6 reset port expander function.
 * @details This function is used to reset port expander.
 * @param[in] ctx : Click context object.
 * See #relay6_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void relay6_reset_port_expander ( relay6_t *ctx );

/**
 * @brief Relay 6 port expander write register function.
 * @details This function writes a data byte into
 * the selected register of the port expander.
 * @param[in] ctx : Click context object.
 * See #relay6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay6_port_expander_write ( relay6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Relay 6 port expander read register function.
 * @details This function reads a data byte from
 * the selected register of the port expander.
 * @param[in] ctx : Click context object.
 * See #relay6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay6_port_expander_read ( relay6_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Relay 6 set relay state function.
 * @details This function sets and clears the value of the selected relay outputs.
 * @param[in] ctx : Click context object.
 * See #relay6_t object definition for detailed explanation.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay6_set_relay ( relay6_t *ctx, uint8_t on_relay, uint8_t off_relay );

#ifdef __cplusplus
}
#endif
#endif // RELAY6_H

/*! @} */ // relay6

// ------------------------------------------------------------------------ END
