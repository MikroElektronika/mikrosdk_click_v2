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
 * @file expand14.h
 * @brief This file contains API for Expand 14 Click Driver.
 */

#ifndef EXPAND14_H
#define EXPAND14_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup expand14 Expand 14 Click Driver
 * @brief API for configuring and manipulating Expand 14 Click driver.
 * @{
 */

/**
 * @defgroup expand14_reg Expand 14 Registers List
 * @brief List of registers of Expand 14 Click driver.
 */

/**
 * @addtogroup expand14_reg
 * @{
 */

/**
 * @brief Expand 14 register list.
 * @details Specified register list of Expand 14 Click driver.
 */
#define EXPAND14_REG_INPUT_PORT_0               0x00
#define EXPAND14_REG_INPUT_PORT_1               0x01
#define EXPAND14_REG_OUTPUT_PORT_0              0x02
#define EXPAND14_REG_OUTPUT_PORT_1              0x03
#define EXPAND14_REG_POLARITY_INV_PORT_0        0x04
#define EXPAND14_REG_POLARITY_INV_PORT_1        0x05
#define EXPAND14_REG_CONFIG_PORT_0              0x06
#define EXPAND14_REG_CONFIG_PORT_1              0x07

/*! @} */ // expand14_reg

/**
 * @defgroup expand14_set Expand 14 Registers Settings
 * @brief Settings for registers of Expand 14 Click driver.
 */

/**
 * @addtogroup expand14_set
 * @{
 */

/**
 * @brief Expand 14 pin mask values.
 * @details Specified pin mask values of Expand 14 Click driver.
 */
#define EXPAND14_NO_PIN_MASK                    0x00
#define EXPAND14_PIN_0_MASK                     0x01
#define EXPAND14_PIN_1_MASK                     0x02
#define EXPAND14_PIN_2_MASK                     0x04
#define EXPAND14_PIN_3_MASK                     0x08
#define EXPAND14_PIN_4_MASK                     0x10
#define EXPAND14_PIN_5_MASK                     0x20
#define EXPAND14_PIN_6_MASK                     0x40
#define EXPAND14_PIN_7_MASK                     0x80
#define EXPAND14_ALL_PINS_MASK                  0xFF

/**
 * @brief Expand 14 port values.
 * @details Specified port values of Expand 14 Click driver.
 */
#define EXPAND14_PORT_0                         0x00
#define EXPAND14_PORT_1                         0x01

/**
 * @brief Expand 14 pin direction values.
 * @details Specified pin direction values of Expand 14 Click driver.
 */
#define EXPAND14_OUTPUT_DIRECTION               0x00
#define EXPAND14_INPUT_DIRECTION                0x01

/**
 * @brief Expand 14 pin logic level values.
 * @details Specified pin logic level values of Expand 14 Click driver.
 */
#define EXPAND14_PIN_LOW_LEVEL                  0x00
#define EXPAND14_PIN_HIGH_LEVEL                 0x01

/**
 * @brief Expand 14 device address setting.
 * @details Specified setting for device slave address selection of
 * Expand 14 Click driver.
 */
#define EXPAND14_DEVICE_ADDRESS_A2A1A0_000      0x20
#define EXPAND14_DEVICE_ADDRESS_A2A1A0_001      0x21
#define EXPAND14_DEVICE_ADDRESS_A2A1A0_010      0x22
#define EXPAND14_DEVICE_ADDRESS_A2A1A0_011      0x23
#define EXPAND14_DEVICE_ADDRESS_A2A1A0_100      0x24
#define EXPAND14_DEVICE_ADDRESS_A2A1A0_101      0x25
#define EXPAND14_DEVICE_ADDRESS_A2A1A0_110      0x26
#define EXPAND14_DEVICE_ADDRESS_A2A1A0_111      0x27

/*! @} */ // expand14_set

/**
 * @defgroup expand14_map Expand 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 14 Click driver.
 */

/**
 * @addtogroup expand14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 14 Click to the selected MikroBUS.
 */
#define EXPAND14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // expand14_map
/*! @} */ // expand14

/**
 * @brief Expand 14 Click context object.
 * @details Context object definition of Expand 14 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;           /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} expand14_t;

/**
 * @brief Expand 14 Click configuration object.
 * @details Configuration object definition of Expand 14 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;            /**< Interrupt pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} expand14_cfg_t;

/**
 * @brief Expand 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EXPAND14_OK = 0,
    EXPAND14_ERROR = -1

} expand14_return_value_t;

/*!
 * @addtogroup expand14 Expand 14 Click Driver
 * @brief API for configuring and manipulating Expand 14 Click driver.
 * @{
 */

/**
 * @brief Expand 14 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand14_cfg_setup ( expand14_cfg_t *cfg );

/**
 * @brief Expand 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #expand14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand14_init ( expand14_t *ctx, expand14_cfg_t *cfg );

/**
 * @brief Expand 14 default configuration function.
 * @details This function executes a default configuration of Expand 14
 * click board.
 * @param[in] ctx : Click context object.
 * See #expand14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t expand14_default_cfg ( expand14_t *ctx );

/**
 * @brief Expand 14 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand14_generic_write ( expand14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Expand 14 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand14_generic_read ( expand14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Expand 14 write register function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand14_write_register ( expand14_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Expand 14 read register function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand14_read_register ( expand14_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Expand 14 set pin direction function.
 * @details This function sets the direction of the selected pins.
 * @param[in] ctx : Click context object.
 * See #expand14_t object definition for detailed explanation.
 * @param[in] direction : @li @c  0 - Output,
 *                        @li @c  1 - Input.
 * @param[in] port : @li @c  0 - Port 0,
 *                   @li @c  1 - Port 1.
 * @param[in] pin_mask : Pin mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand14_set_pin_direction ( expand14_t *ctx, uint8_t direction, uint8_t port, uint8_t pin_mask );

/**
 * @brief Expand 14 set all pins direction function.
 * @details This function sets the direction of all pins.
 * @param[in] ctx : Click context object.
 * See #expand14_t object definition for detailed explanation.
 * @param[in] direction : @li @c  0 - Output,
 *                        @li @c  1 - Input.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand14_set_all_pins_direction ( expand14_t *ctx, uint8_t direction );

/**
 * @brief Expand 14 set all pins value function.
 * @details This function sets the value of all output pins.
 * @param[in] ctx : Click context object.
 * See #expand14_t object definition for detailed explanation.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand14_set_all_pins_value ( expand14_t *ctx, uint8_t set_mask );

/**
 * @brief Expand 14 set pin value function.
 * @details This function sets the value of the selected pins.
 * @param[in] ctx : Click context object.
 * See #expand14_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - Port 0,
 *                   @li @c  1 - Port 1.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand14_set_pin_value ( expand14_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask );

/**
 * @brief Expand 14 read port value function.
 * @details This function reads the value of the selected port input pins.
 * @param[in] ctx : Click context object.
 * See #expand14_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - Port 0,
 *                   @li @c  1 - Port 1.
 * @param[out] data_out : Port value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand14_read_port_value ( expand14_t *ctx, uint8_t port, uint8_t *data_out );

/**
 * @brief Expand 14 get INT pin function.
 * @details This function returns the logic level of the INT pin.
 * @param[in] ctx : Click context object.
 * See #expand14_t object definition for detailed explanation.
 * @return Pin logic level.
 * @note None.
 */
uint8_t expand14_get_int_pin ( expand14_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EXPAND14_H

/*! @} */ // expand14

// ------------------------------------------------------------------------ END
