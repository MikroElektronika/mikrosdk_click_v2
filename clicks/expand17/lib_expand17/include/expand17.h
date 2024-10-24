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
 * @file expand17.h
 * @brief This file contains API for Expand 17 Click Driver.
 */

#ifndef EXPAND17_H
#define EXPAND17_H

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
 * @addtogroup expand17 Expand 17 Click Driver
 * @brief API for configuring and manipulating Expand 17 Click driver.
 * @{
 */

/**
 * @defgroup expand17_reg Expand 17 Registers List
 * @brief List of registers of Expand 17 Click driver.
 */

/**
 * @addtogroup expand17_reg
 * @{
 */

/**
 * @brief Expand 17 description register.
 * @details Specified register for description of Expand 17 Click driver.
 */
#define EXPAND17_REG_INPUT_PORT                 0x00
#define EXPAND17_REG_OUTPUT_PORT                0x01
#define EXPAND17_REG_POLARITY_INVERSION         0x02
#define EXPAND17_REG_CONFIGURATION              0x03
#define EXPAND17_REG_OUTPUT_STRENGTH_0          0x40
#define EXPAND17_REG_OUTPUT_STRENGTH_1          0x41
#define EXPAND17_REG_INPUT_LATCH                0x42
#define EXPAND17_REG_PULL_UP_DOWN_EN            0x43
#define EXPAND17_REG_PULL_UP_DOWN_SELECT        0x44
#define EXPAND17_REG_INTERRUPT_MASK             0x45
#define EXPAND17_REG_INTERRUPT_STATUS           0x46
#define EXPAND17_REG_OUTPUT_PORT_CFG            0x4F

/*! @} */ // expand17_reg

/**
 * @defgroup expand17_set Expand 17 Registers Settings
 * @brief Settings for registers of Expand 17 Click driver.
 */

/**
 * @addtogroup expand17_set
 * @{
 */

/**
 * @brief Expand 17 description setting.
 * @details Specified setting for description of Expand 17 Click driver.
 */
#define EXPAND17_IO_1_PIN_MASK                  0x01
#define EXPAND17_IO_2_PIN_MASK                  0x02
#define EXPAND17_IO_3_PIN_MASK                  0x04
#define EXPAND17_IO_4_PIN_MASK                  0x08
#define EXPAND17_IO_5_PIN_MASK                  0x10
#define EXPAND17_IO_6_PIN_MASK                  0x20
#define EXPAND17_IO_7_PIN_MASK                  0x40
#define EXPAND17_IO_8_PIN_MASK                  0x80
#define EXPAND17_ALL_IO_PIN_MASK                0xFF
#define EXPAND17_NO_IO_PIN_MASK                 0x00

/**
 * @brief Expand 17 output state strength  setting.
 * @details Specified setting for output state strength of Expand 17 Click driver.
 */
#define EXPAND17_OUTPUT_STRENGTH_FULL           0x03
#define EXPAND17_OUTPUT_STRENGTH_3_QUARTERS     0x02
#define EXPAND17_OUTPUT_STRENGTH_HALF           0x01
#define EXPAND17_OUTPUT_STRENGTH_1_QUARTER      0x00

/**
 * @brief Expand 17 output port configuration setting.
 * @details Specified setting for output port configuration of Expand 17 Click driver.
 */
#define EXPAND17_PORT_PUSH_PULL                 0x00
#define EXPAND17_PORT_OPEN_DRAIN                0x01

/**
 * @brief Expand 17 pin state setting.
 * @details Specified setting for pin state of Expand 17 Click driver.
 */
#define EXPAND17_PIN_STATE_HIGH                 0x01
#define EXPAND17_PIN_STATE_LOW                  0x00

/**
 * @brief Expand 17 device address setting.
 * @details Specified setting for device slave address selection of
 * Expand 17 Click driver.
 */
#define EXPAND17_DEVICE_ADDRESS_0               0x20
#define EXPAND17_DEVICE_ADDRESS_1               0x21

/*! @} */ // expand17_set

/**
 * @defgroup expand17_map Expand 17 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 17 Click driver.
 */

/**
 * @addtogroup expand17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 17 Click to the selected MikroBUS.
 */
#define EXPAND17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // expand17_map
/*! @} */ // expand17

/**
 * @brief Expand 17 Click context object.
 * @details Context object definition of Expand 17 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} expand17_t;

/**
 * @brief Expand 17 Click configuration object.
 * @details Configuration object definition of Expand 17 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} expand17_cfg_t;

/**
 * @brief Expand 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EXPAND17_OK = 0,
    EXPAND17_ERROR = -1

} expand17_return_value_t;

/*!
 * @addtogroup expand17 Expand 17 Click Driver
 * @brief API for configuring and manipulating Expand 17 Click driver.
 * @{
 */

/**
 * @brief Expand 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand17_cfg_setup ( expand17_cfg_t *cfg );

/**
 * @brief Expand 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #expand17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand17_init ( expand17_t *ctx, expand17_cfg_t *cfg );

/**
 * @brief Expand 17 default configuration function.
 * @details This function executes a default configuration of Expand 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #expand17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t expand17_default_cfg ( expand17_t *ctx );

/**
 * @brief Expand 17 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand17_generic_write ( expand17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Expand 17 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand17_generic_read ( expand17_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Expand 17 set reset pin state function.
 * @details This function is used to set state of the reset pin of Expand 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #expand17_t object definition for detailed explanation.
 * @param[in] pin_state : State of the reset pin.
 * @return Nothing.
 * @note None.
 */
void expand17_set_rst_pin ( expand17_t *ctx, uint8_t pin_state );

/**
 * @brief Expand 17 get interrupt pin state function.
 * @details This function is used to get state of the interrupt pin of Expand 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #expand17_t object definition for detailed explanation.
 * @return State of the INT pin.
 * @note None.
 */
uint8_t expand17_get_int_pin ( expand17_t *ctx );

/**
 * @brief Expand 17 hardware reset function.
 * @details This function is used to perform the hardware reset of Expand 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #expand17_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void expand17_hw_reset ( expand17_t *ctx );

/**
 * @brief Expand 17 set pin input or output direction function.
 * @details This function is used to set input or output direction of pins.
 * @param[in] ctx : Click context object.
 * See #expand17_t object definition for detailed explanation.
 * @param[in] input_pins : Selected pins will be set as input.
 * @param[in] output_pins : Selected pins will be set as output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand17_set_io_dir ( expand17_t *ctx, uint8_t input_pins, uint8_t output_pins );

/**
 * @brief Expand 17 set output pins state function.
 * @details This function is used to set output state of the pins.
 * @param[in] ctx : Click context object.
 * See #expand17_t object definition for detailed explanation.
 * @param[in] clr_mask : Output of the selected pins will be set as LOW.
 * @param[in] set_mask : Output of the selected pins will be set as HIGH.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand17_set_output_state ( expand17_t *ctx, uint8_t clr_mask, uint8_t set_mask );

/**
 * @brief Expand 17 get input pins state function.
 * @details This function is used to get state of the input pins.
 * @param[in] ctx : Click context object.
 * See #expand17_t object definition for detailed explanation.
 * @param[out] input_state : Input pins state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand17_get_input_state ( expand17_t *ctx, uint8_t *input_state );

#ifdef __cplusplus
}
#endif
#endif // EXPAND17_H

/*! @} */ // expand17

// ------------------------------------------------------------------------ END
