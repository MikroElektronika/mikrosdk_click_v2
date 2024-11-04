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
 * @file expand19.h
 * @brief This file contains API for Expand 19 Click Driver.
 */

#ifndef EXPAND19_H
#define EXPAND19_H

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
 * @addtogroup expand19 Expand 19 Click Driver
 * @brief API for configuring and manipulating Expand 19 Click driver.
 * @{
 */

/**
 * @defgroup expand19_reg Expand 19 Registers List
 * @brief List of registers of Expand 19 Click driver.
 */

/**
 * @addtogroup expand19_reg
 * @{
 */

/**
 * @brief Expand 19 register list.
 * @details Specified register list of Expand 19 Click driver.
 */
#define EXPAND19_REG_INPUT_PORT                 0x00
#define EXPAND19_REG_OUTPUT_PORT                0x01
#define EXPAND19_REG_POLARITY_INV               0x02
#define EXPAND19_REG_CONFIG                     0x03
#define EXPAND19_REG_OUTPUT_DRIVE_0             0x40
#define EXPAND19_REG_OUTPUT_DRIVE_1             0x41
#define EXPAND19_REG_INPUT_LATCH                0x42
#define EXPAND19_REG_PULL_ENABLE                0x43
#define EXPAND19_REG_PULL_SELECTION             0x44
#define EXPAND19_REG_INT_MASK                   0x45
#define EXPAND19_REG_INT_STATUS                 0x46
#define EXPAND19_REG_OUTPUT_PORT_CONFIG         0x4F

/*! @} */ // expand19_reg

/**
 * @defgroup expand19_set Expand 19 Registers Settings
 * @brief Settings for registers of Expand 19 Click driver.
 */

/**
 * @addtogroup expand19_set
 * @{
 */

/**
 * @brief Expand 19 pin mask values.
 * @details Specified pin mask values of Expand 19 Click driver.
 */
#define EXPAND19_NO_PIN_MASK                    0x00
#define EXPAND19_PIN_0_MASK                     0x01
#define EXPAND19_PIN_1_MASK                     0x02
#define EXPAND19_PIN_2_MASK                     0x04
#define EXPAND19_PIN_3_MASK                     0x08
#define EXPAND19_PIN_4_MASK                     0x10
#define EXPAND19_PIN_5_MASK                     0x20
#define EXPAND19_PIN_6_MASK                     0x40
#define EXPAND19_PIN_7_MASK                     0x80
#define EXPAND19_ALL_PINS_MASK                  0xFF

/**
 * @brief Expand 19 pin direction values.
 * @details Specified pin direction values of Expand 19 Click driver.
 */
#define EXPAND19_OUTPUT_DIRECTION               0x00
#define EXPAND19_INPUT_DIRECTION                0x01

/**
 * @brief Expand 19 pin logic level values.
 * @details Specified pin logic level values of Expand 19 Click driver.
 */
#define EXPAND19_PIN_LOW_LEVEL                  0x00
#define EXPAND19_PIN_HIGH_LEVEL                 0x01

/**
 * @brief Expand 19 device address setting.
 * @details Specified setting for device slave address selection of
 * Expand 19 Click driver.
 */
#define EXPAND19_DEVICE_ADDRESS_A1A0_00         0x70
#define EXPAND19_DEVICE_ADDRESS_A1A0_01         0x71
#define EXPAND19_DEVICE_ADDRESS_A1A0_10         0x72
#define EXPAND19_DEVICE_ADDRESS_A1A0_11         0x73

/*! @} */ // expand19_set

/**
 * @defgroup expand19_map Expand 19 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 19 Click driver.
 */

/**
 * @addtogroup expand19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 19 Click to the selected MikroBUS.
 */
#define EXPAND19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // expand19_map
/*! @} */ // expand19

/**
 * @brief Expand 19 Click context object.
 * @details Context object definition of Expand 19 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (active low). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} expand19_t;

/**
 * @brief Expand 19 Click configuration object.
 * @details Configuration object definition of Expand 19 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} expand19_cfg_t;

/**
 * @brief Expand 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EXPAND19_OK = 0,
    EXPAND19_ERROR = -1

} expand19_return_value_t;

/*!
 * @addtogroup expand19 Expand 19 Click Driver
 * @brief API for configuring and manipulating Expand 19 Click driver.
 * @{
 */

/**
 * @brief Expand 19 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand19_cfg_setup ( expand19_cfg_t *cfg );

/**
 * @brief Expand 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #expand19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand19_init ( expand19_t *ctx, expand19_cfg_t *cfg );

/**
 * @brief Expand 19 default configuration function.
 * @details This function executes a default configuration of Expand 19
 * Click board.
 * @param[in] ctx : Click context object.
 * See #expand19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t expand19_default_cfg ( expand19_t *ctx );

/**
 * @brief Expand 19 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand19_write_register ( expand19_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Expand 19 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand19_read_register ( expand19_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Expand 19 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #expand19_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void expand19_set_rst_pin ( expand19_t *ctx, uint8_t state );

/**
 * @brief Expand 19 reset device function.
 * @details This function resets the device by toggling the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #expand19_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void expand19_reset_device ( expand19_t *ctx );

/**
 * @brief Expand 19 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #expand19_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t expand19_get_int_pin ( expand19_t *ctx );

/**
 * @brief Expand 19 set pin direction function.
 * @details This function sets the direction of the selected pins.
 * @param[in] ctx : Click context object.
 * See #expand19_t object definition for detailed explanation.
 * @param[in] direction : @li @c  0 - Output,
 *                        @li @c  1 - Input.
 * @param[in] pin_mask : Pin mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand19_set_pin_direction ( expand19_t *ctx, uint8_t direction, uint8_t pin_mask );

/**
 * @brief Expand 19 set all pins direction function.
 * @details This function sets the direction of all pins.
 * @param[in] ctx : Click context object.
 * See #expand19_t object definition for detailed explanation.
 * @param[in] direction : @li @c  0 - Output,
 *                        @li @c  1 - Input.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand19_set_all_pins_direction ( expand19_t *ctx, uint8_t direction );

/**
 * @brief Expand 19 set all pins value function.
 * @details This function sets the value of all output pins.
 * @param[in] ctx : Click context object.
 * See #expand19_t object definition for detailed explanation.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand19_set_all_pins_value ( expand19_t *ctx, uint8_t set_mask );

/**
 * @brief Expand 19 set pin value function.
 * @details This function sets the value of the selected pins.
 * @param[in] ctx : Click context object.
 * See #expand19_t object definition for detailed explanation.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand19_set_pin_value ( expand19_t *ctx, uint8_t clr_mask, uint8_t set_mask );

/**
 * @brief Expand 19 read port value function.
 * @details This function reads the value of all input pins.
 * @param[in] ctx : Click context object.
 * See #expand19_t object definition for detailed explanation.
 * @param[out] data_out : Port value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand19_read_port_value ( expand19_t *ctx, uint8_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // EXPAND19_H

/*! @} */ // expand19

// ------------------------------------------------------------------------ END
