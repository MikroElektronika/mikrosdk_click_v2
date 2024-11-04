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
 * @file expand16.h
 * @brief This file contains API for Expand 16 Click Driver.
 */

#ifndef EXPAND16_H
#define EXPAND16_H

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
 * @addtogroup expand16 Expand 16 Click Driver
 * @brief API for configuring and manipulating Expand 16 Click driver.
 * @{
 */

/**
 * @defgroup expand16_reg Expand 16 Registers List
 * @brief List of registers of Expand 16 Click driver.
 */

/**
 * @addtogroup expand16_reg
 * @{
 */

/**
 * @brief Expand 16 description register.
 * @details Specified register for description of Expand 16 Click driver.
 */
#define EXPAND16_REG_DEV_ID_AND_CTRL            0x01
#define EXPAND16_REG_IO_DIRECTION               0x03
#define EXPAND16_REG_OUTPUT_STATE               0x05
#define EXPAND16_REG_OUTPUT_HIGH_Z              0x07
#define EXPAND16_REG_INPUT_DEF_STATE            0x09
#define EXPAND16_REG_PULL_ENABLE                0x0B
#define EXPAND16_REG_PULL_DOWN_UP               0x0D
#define EXPAND16_REG_INPUT_STATE                0x0F
#define EXPAND16_REG_INTERRUPT_MASK             0x11
#define EXPAND16_REG_INTERRUPT_STATUS           0x13

/*! @} */ // expand16_reg

/**
 * @defgroup expand16_set Expand 16 Registers Settings
 * @brief Settings for registers of Expand 16 Click driver.
 */

/**
 * @addtogroup expand16_set
 * @{
 */

/**
 * @brief Expand 16 description setting.
 * @details Specified setting for description of Expand 16 Click driver.
 */
#define EXPAND16_PIN_MASK_NONE                  0x00
#define EXPAND16_PIN_MASK_GPIO_0                0x01
#define EXPAND16_PIN_MASK_GPIO_1                0x02
#define EXPAND16_PIN_MASK_GPIO_2                0x04
#define EXPAND16_PIN_MASK_GPIO_3                0x08
#define EXPAND16_PIN_MASK_GPIO_4                0x10
#define EXPAND16_PIN_MASK_GPIO_5                0x20
#define EXPAND16_PIN_MASK_GPIO_6                0x40
#define EXPAND16_PIN_MASK_GPIO_7                0x80
#define EXPAND16_PIN_MASK_ALL                   0xFF

/**
 * @brief Expand 16 software reset command.
 * @details Specified software reset command of Expand 16 Click driver.
 */
#define EXPAND16_SW_RESET_CMD                   0x01

/**
 * @brief Expand 16 device ID.
 * @details Specified device ID of Expand 16 Click driver.
 */
#define EXPAND16_DEVICE_ID                      0xA0
#define EXPAND16_DEVICE_ID_MASK                 0xE0

/**
 * @brief Expand 16 pin state setting.
 * @details Specified setting for pin states of Expand 16 Click driver.
 */
#define EXPAND16_PIN_STATE_HIGH                 0x01
#define EXPAND16_PIN_STATE_LOW                  0x00

/**
 * @brief Expand 16 device address setting.
 * @details Specified setting for device slave address selection of
 * Expand 16 Click driver.
 */
#define EXPAND16_DEVICE_ADDRESS_GND             0x43
#define EXPAND16_DEVICE_ADDRESS_VCC             0x44

/*! @} */ // expand16_set

/**
 * @defgroup expand16_map Expand 16 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 16 Click driver.
 */

/**
 * @addtogroup expand16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 16 Click to the selected MikroBUS.
 */
#define EXPAND16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // expand16_map
/*! @} */ // expand16

/**
 * @brief Expand 16 Click context object.
 * @details Context object definition of Expand 16 Click driver.
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

} expand16_t;

/**
 * @brief Expand 16 Click configuration object.
 * @details Configuration object definition of Expand 16 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} expand16_cfg_t;

/**
 * @brief Expand 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EXPAND16_OK = 0,
    EXPAND16_ERROR = -1

} expand16_return_value_t;

/*!
 * @addtogroup expand16 Expand 16 Click Driver
 * @brief API for configuring and manipulating Expand 16 Click driver.
 * @{
 */

/**
 * @brief Expand 16 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand16_cfg_setup ( expand16_cfg_t *cfg );

/**
 * @brief Expand 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #expand16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand16_init ( expand16_t *ctx, expand16_cfg_t *cfg );

/**
 * @brief Expand 16 default configuration function.
 * @details This function executes a default configuration of Expand 16
 * Click board.
 * @param[in] ctx : Click context object.
 * See #expand16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t expand16_default_cfg ( expand16_t *ctx );

/**
 * @brief Expand 16 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand16_generic_write ( expand16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Expand 16 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand16_generic_read ( expand16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Expand 16 set RST pin state function.
 * @details This function is used to set RST pin state.
 * @param[in] ctx : Click context object.
 * See #expand16_t object definition for detailed explanation.
 * @param[in] pin_state : RST pin state.
 * @return Nothing.
 * @note None.
 */
void expand16_set_rst_pin ( expand16_t *ctx, uint8_t pin_state );

/**
 * @brief Expand 16 Hardware reset function.
 * @details This function is used to perform hardware reset.
 * @param[in] ctx : Click context object.
 * See #expand16_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void expand16_hw_reset ( expand16_t *ctx );

/**
 * @brief Expand 16 get INT pin function.
 * @details This function is used to read state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #expand16_t object definition for detailed explanation.
 * @return State of the INT pin.
 * @note None.
 */
uint8_t expand16_get_int_pin ( expand16_t *ctx );

/**
 * @brief Expand 16 register write function.
 * @details This function is to write data into the selected register.
 * @param[in] ctx : Click context object.
 * See #expand16_t object definition for detailed explanation.
 * @param[in] reg : Selected register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand16_write_reg ( expand16_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Expand 16 register read function.
 * @details This function is used to read data from the selected register.
 * @param[in] ctx : Click context object.
 * See #expand16_t object definition for detailed explanation.
 * @param[in] reg : Selected register address.
 * @param[out] data_out : Read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand16_read_reg ( expand16_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Expand 16 set pin input or output direction function.
 * @details This function is used to set input or output direction of pins.
 * @param[in] ctx : Click context object.
 * See #expand16_t object definition for detailed explanation.
 * @param[in] input_pins : Selected pins will be set as input.
 * @param[in] output_pins : Selected pins will be set as output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand16_set_io_dir ( expand16_t *ctx, uint8_t input_pins, uint8_t output_pins );

/**
 * @brief Expand 16 set output pins state function.
 * @details This function is used to set output state of the pins.
 * @param[in] ctx : Click context object.
 * See #expand16_t object definition for detailed explanation.
 * @param[in] clr_mask : Output of the selected pins will be set as LOW.
 * @param[in] set_mask : Output of the selected pins will be set as HIGH.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand16_set_output_state ( expand16_t *ctx, uint8_t clr_mask, uint8_t set_mask );

#ifdef __cplusplus
}
#endif
#endif // EXPAND16_H

/*! @} */ // expand16

// ------------------------------------------------------------------------ END
