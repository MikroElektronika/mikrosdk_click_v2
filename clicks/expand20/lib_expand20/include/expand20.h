/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file expand20.h
 * @brief This file contains API for Expand 20 Click Driver.
 */

#ifndef EXPAND20_H
#define EXPAND20_H

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
 * @addtogroup expand20 Expand 20 Click Driver
 * @brief API for configuring and manipulating Expand 20 Click driver.
 * @{
 */

/**
 * @defgroup expand20_cmd Expand 20 Commands List
 * @brief List of commands of Expand 20 Click driver.
 */

/**
 * @addtogroup expand20_cmd
 * @{
 */

/**
 * @brief Expand 20 Commands list.
 * @details Specified Commands of Expand 20 Click driver.
 */
#define EXPAND20_CMD_INPUT_PORT_0               0x00
#define EXPAND20_CMD_INPUT_PORT_1               0x01
#define EXPAND20_CMD_OUTPUT_PORT_0              0x02
#define EXPAND20_CMD_OUTPUT_PORT_1              0x03
#define EXPAND20_CMD_POLARITY_INV_0             0x04
#define EXPAND20_CMD_POLARITY_INV_1             0x05
#define EXPAND20_CMD_CONFIG_0                   0x06
#define EXPAND20_CMD_CONFIG_1                   0x07

/*! @} */ // expand20_cmd

/**
 * @defgroup expand20_set Expand 20 Registers Settings
 * @brief Settings for registers of Expand 20 Click driver.
 */

/**
 * @addtogroup expand20_set
 * @{
 */

/**
 * @brief Expand 20 port selection setting.
 * @details Specified setting for port selection of Expand 20 Click driver.
 */
#define EXPAND20_PORT_0                         0x00
#define EXPAND20_PORT_1                         0x01

/**
 * @brief Expand 20 pin mask setting.
 * @details Specified setting for pin mask of Expand 20 Click driver.
 */
#define EXPAND20_NO_PIN_MASK                    0x00
#define EXPAND20_PIN_0_MASK                     0x01
#define EXPAND20_PIN_1_MASK                     0x02
#define EXPAND20_PIN_2_MASK                     0x04
#define EXPAND20_PIN_3_MASK                     0x08
#define EXPAND20_PIN_4_MASK                     0x10
#define EXPAND20_PIN_5_MASK                     0x20
#define EXPAND20_PIN_6_MASK                     0x40
#define EXPAND20_PIN_7_MASK                     0x80
#define EXPAND20_ALL_PINS_MASK                  0xFF

/**
 * @brief Expand 20 pin direction setting.
 * @details Specified setting for pin direction of Expand 20 Click driver.
 */
#define EXPAND20_OUTPUT_DIRECTION               0x00
#define EXPAND20_INPUT_DIRECTION                0x01
#define EXPAND20_OUTPUT_PINS                    0x00
#define EXPAND20_INPUT_PINS                     0xFF

/**
 * @brief Expand 20 pin logic level setting.
 * @details Specified setting for pin logic level of Expand 20 Click driver.
 */
#define EXPAND20_PIN_LOW_LEVEL                  0x00
#define EXPAND20_PIN_HIGH_LEVEL                 0x01
#define EXPAND20_PINS_LOW                       0x00
#define EXPAND20_PINS_HIGH                      0xFF

/**
 * @brief Expand 20 polarity inversion setting.
 * @details Specified setting for polarity inversion of Expand 20 Click driver.
 */
#define EXPAND20_POLARITY_NO_INVERT             0x00
#define EXPAND20_POLARITY_INVERT                0x01

/**
 * @brief Expand 20 device address setting.
 * @details Specified setting for device slave address selection of
 * Expand 20 Click driver.
 */
#define EXPAND20_DEVICE_ADDRESS_GND             0x20
#define EXPAND20_DEVICE_ADDRESS_VCC             0x21
#define EXPAND20_DEVICE_ADDRESS                 EXPAND20_DEVICE_ADDRESS_VCC

/*! @} */ // expand20_set

/**
 * @defgroup expand20_map Expand 20 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 20 Click driver.
 */

/**
 * @addtogroup expand20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 20 Click to the selected MikroBUS.
 */
#define EXPAND20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // expand20_map
/*! @} */ // expand20

/**
 * @brief Expand 20 Click context object.
 * @details Context object definition of Expand 20 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Reset pin ( active low ). */

    // Input pins
    digital_in_t int_pin;                       /**< Interrupt pin ( active low ). */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} expand20_t;

/**
 * @brief Expand 20 Click configuration object.
 * @details Configuration object definition of Expand 20 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;                             /**< Reset pin descriptor. */
    pin_name_t int_pin;                         /**< Interrupt pin descriptor. */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} expand20_cfg_t;

/**
 * @brief Expand 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EXPAND20_OK = 0,
    EXPAND20_ERROR = -1

} expand20_return_value_t;

/*!
 * @addtogroup expand20 Expand 20 Click Driver
 * @brief API for configuring and manipulating Expand 20 Click driver.
 * @{
 */

/**
 * @brief Expand 20 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand20_cfg_setup ( expand20_cfg_t *cfg );

/**
 * @brief Expand 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand20_init ( expand20_t *ctx, expand20_cfg_t *cfg );

/**
 * @brief Expand 20 default configuration function.
 * @details This function executes a default configuration of Expand 20
 * Click board.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t expand20_default_cfg ( expand20_t *ctx );

/**
 * @brief Expand 20 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @param[in] cmd : Command byte which selects the targeted register.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand20_write_reg ( expand20_t *ctx, uint8_t cmd, uint8_t data_in );

/**
 * @brief Expand 20 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @param[in] cmd : Command byte which selects the targeted register.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand20_write_regs ( expand20_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief Expand 20 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @param[in] cmd : Command byte which selects the targeted register.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand20_read_reg ( expand20_t *ctx, uint8_t cmd, uint8_t *data_out );

/**
 * @brief Expand 20 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @param[in] cmd : Command byte which selects the targeted register.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand20_read_regs ( expand20_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief Expand 20 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @param[in] state : RST pin logic state.
 * @return None.
 * @note None.
 */
void expand20_set_rst_pin ( expand20_t *ctx, uint8_t state );

/**
 * @brief Expand 20 reset device function.
 * @details This function resets the device by toggling the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void expand20_reset_device ( expand20_t *ctx );

/**
 * @brief Expand 20 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t expand20_get_int_pin ( expand20_t *ctx );

/**
 * @brief Expand 20 set pin direction function.
 * @details This function sets the direction of the selected pins on the
 * selected port.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @param[in] port : @li @c 0 - Port 0,
 *                   @li @c 1 - Port 1.
 * @param[in] direction : @li @c 0 - Output,
 *                        @li @c 1 - Input.
 * @param[in] pin_mask : Pin mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand20_set_pin_direction ( expand20_t *ctx, uint8_t port, uint8_t direction, uint8_t pin_mask );

/**
 * @brief Expand 20 set all pins direction function.
 * @details This function sets the direction of all pins on both ports.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @param[in] direction : @li @c 0 - Output,
 *                        @li @c 1 - Input.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand20_set_all_pins_direction ( expand20_t *ctx, uint8_t direction );

/**
 * @brief Expand 20 set pin value function.
 * @details This function sets the value of the selected pins on the selected
 * output port.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @param[in] port : @li @c 0 - Port 0,
 *                   @li @c 1 - Port 1.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand20_set_pin_value ( expand20_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask );

/**
 * @brief Expand 20 set port value function.
 * @details This function sets the value of all output pins on the selected port.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @param[in] port : @li @c 0 - Port 0,
 *                   @li @c 1 - Port 1.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand20_set_port_value ( expand20_t *ctx, uint8_t port, uint8_t set_mask );

/**
 * @brief Expand 20 read port value function.
 * @details This function reads the value of all input pins on the selected port.
 * @param[in] ctx : Click context object.
 * See #expand20_t object definition for detailed explanation.
 * @param[in] port : @li @c 0 - Port 0,
 *                   @li @c 1 - Port 1.
 * @param[out] data_out : Pointer to the read port value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand20_read_port_value ( expand20_t *ctx, uint8_t port, uint8_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // EXPAND20_H

/*! @} */ // expand20

// ------------------------------------------------------------------------ END
