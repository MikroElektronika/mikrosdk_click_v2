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
 * @file expand11.h
 * @brief This file contains API for Expand 11 Click Driver.
 */

#ifndef EXPAND11_H
#define EXPAND11_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup expand11 Expand 11 Click Driver
 * @brief API for configuring and manipulating Expand 11 Click driver.
 * @{
 */

/**
 * @defgroup expand11_reg Expand 11 Registers List
 * @brief List of registers of Expand 11 Click driver.
 */

/**
 * @addtogroup expand11_reg
 * @{
 */

/**
 * @brief Expand 11 register list.
 * @details Specified register list of Expand 11 Click driver.
 */
#define EXPAND11_REG_INPUT_PORT             0x00
#define EXPAND11_REG_OUTPUT_PORT            0x01
#define EXPAND11_REG_POLARITY_INV           0x02
#define EXPAND11_REG_CONFIG                 0x03
#define EXPAND11_REG_SPECIAL_FUNC           0x50

/*! @} */ // expand11_reg

/**
 * @defgroup expand11_set Expand 11 Registers Settings
 * @brief Settings for registers of Expand 11 Click driver.
 */

/**
 * @addtogroup expand11_set
 * @{
 */

/**
 * @brief Expand 11 pin mask values.
 * @details Specified pin mask values of Expand 11 Click driver.
 */
#define EXPAND11_NO_PIN_MASK                0x00
#define EXPAND11_PIN_0_MASK                 0x01
#define EXPAND11_PIN_1_MASK                 0x02
#define EXPAND11_PIN_2_MASK                 0x04
#define EXPAND11_PIN_3_MASK                 0x08
#define EXPAND11_ALL_PINS_MASK              0x0F

/**
 * @brief Expand 11 pin direction values.
 * @details Specified pin direction values of Expand 11 Click driver.
 */
#define EXPAND11_OUTPUT_DIRECTION           0x00
#define EXPAND11_INPUT_DIRECTION            0x01

/**
 * @brief Expand 11 pin polarity values.
 * @details Specified pin polarity values of Expand 11 Click driver.
 */
#define EXPAND11_POLARITY_NO_INV            0x00
#define EXPAND11_POLARITY_INV               0x01

/**
 * @brief Expand 11 special function register values.
 * @details Specified special function register values of Expand 11 Click driver.
 */
#define EXPAND11_SPECIAL_FUNC_P3_AS_INT     0x80
#define EXPAND11_SPECIAL_FUNC_PU_DISABLED   0x40

/**
 * @brief Expand 11 P3 function settings.
 * @details Specified P3 function settings of Expand 11 Click driver.
 */
#define EXPAND11_P3_AS_P3                   0x00
#define EXPAND11_P3_AS_INT                  0x01

/**
 * @brief Expand 11 device address setting.
 * @details Specified setting for device slave address selection of
 * Expand 11 Click driver.
 */
#define EXPAND11_DEVICE_ADDRESS             0x41

/*! @} */ // expand11_set

/**
 * @defgroup expand11_map Expand 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 11 Click driver.
 */

/**
 * @addtogroup expand11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 11 Click to the selected MikroBUS.
 */
#define EXPAND11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // expand11_map
/*! @} */ // expand11

/**
 * @brief Expand 11 Click context object.
 * @details Context object definition of Expand 11 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} expand11_t;

/**
 * @brief Expand 11 Click configuration object.
 * @details Configuration object definition of Expand 11 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} expand11_cfg_t;

/**
 * @brief Expand 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EXPAND11_OK = 0,
    EXPAND11_ERROR = -1

} expand11_return_value_t;

/*!
 * @addtogroup expand11 Expand 11 Click Driver
 * @brief API for configuring and manipulating Expand 11 Click driver.
 * @{
 */

/**
 * @brief Expand 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand11_cfg_setup ( expand11_cfg_t *cfg );

/**
 * @brief Expand 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_init ( expand11_t *ctx, expand11_cfg_t *cfg );

/**
 * @brief Expand 11 default configuration function.
 * @details This function executes a default configuration of Expand 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t expand11_default_cfg ( expand11_t *ctx );

/**
 * @brief Expand 11 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_write_register ( expand11_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Expand 11 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_read_register ( expand11_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Expand 11 set pin direction function.
 * @details This function sets the direction of the selected pins.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @param[in] direction : @li @c  0 - Output,
 *                        @li @c  1 - Input.
 * @param[in] pin_mask : Pin mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_set_pin_direction ( expand11_t *ctx, uint8_t direction, uint8_t pin_mask );

/**
 * @brief Expand 11 set all pins direction function.
 * @details This function sets the direction of all pins.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @param[in] direction : @li @c  0 - Output,
 *                        @li @c  1 - Input.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_set_all_pins_direction ( expand11_t *ctx, uint8_t direction );

/**
 * @brief Expand 11 set pin polarity function.
 * @details This function sets the polarity of the selected pins.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @param[in] polarity : @li @c  0 - Non-Inverted,
 *                       @li @c  1 - Inverted.
 * @param[in] pin_mask : Pin mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_set_pin_polarity ( expand11_t *ctx, uint8_t polarity, uint8_t pin_mask );

/**
 * @brief Expand 11 set all pins polarity function.
 * @details This function sets the polarity of all pins.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @param[in] polarity : @li @c  0 - Non-Inverted,
 *                       @li @c  1 - Inverted.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_set_all_pins_polarity ( expand11_t *ctx, uint8_t polarity );

/**
 * @brief Expand 11 set pin value function.
 * @details This function sets the value of the selected pins.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_set_pin_value ( expand11_t *ctx, uint8_t clr_mask, uint8_t set_mask );

/**
 * @brief Expand 11 set all pins value function.
 * @details This function sets the value of all output pins.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_set_all_pins_value ( expand11_t *ctx, uint8_t set_mask );

/**
 * @brief Expand 11 read port value function.
 * @details This function reads the value of the port input pins.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @param[out] data_out : Port value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_read_port_value ( expand11_t *ctx, uint8_t *data_out );

/**
 * @brief Expand 11 set p3 function function.
 * @details This function sets the P3 pin function to P3 or INT pin.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @param[in] p3_func : @li @c  0 - P3,
 *                      @li @c  1 - INT.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_set_p3_function ( expand11_t *ctx, uint8_t p3_func );

/**
 * @brief Expand 11 disable pull up function.
 * @details This function disables internal pull-ups for input pins.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_disable_pull_up ( expand11_t *ctx );

/**
 * @brief Expand 11 enable pull up function.
 * @details This function enables internal pull-ups for input pins.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand11_enable_pull_up ( expand11_t *ctx );

/**
 * @brief Expand 11 get int pin function.
 * @details This function returns the logic level of the INT pin.
 * @param[in] ctx : Click context object.
 * See #expand11_t object definition for detailed explanation.
 * @return Pin logic level.
 * @note This pin must be selected by with the PS SEL jumper and enabled in the special function register.
 */
uint8_t expand11_get_int_pin ( expand11_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EXPAND11_H

/*! @} */ // expand11

// ------------------------------------------------------------------------ END
