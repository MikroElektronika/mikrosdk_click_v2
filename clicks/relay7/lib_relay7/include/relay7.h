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
 * @file relay7.h
 * @brief This file contains API for Relay 7 Click Driver.
 */

#ifndef RELAY7_H
#define RELAY7_H

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
 * @addtogroup relay7 Relay 7 Click Driver
 * @brief API for configuring and manipulating Relay 7 Click driver.
 * @{
 */

/**
 * @defgroup relay7_reg Relay 7 Registers List
 * @brief List of registers of Relay 7 Click driver.
 */

/**
 * @addtogroup relay7_reg
 * @{
 */

/**
 * @brief Relay 7 description register.
 * @details Specified register for description of Relay 7 Click driver.
 */
#define RELAY7_REG_INPUT_PORT            0x00
#define RELAY7_REG_OUTPUT_PORT           0x01
#define RELAY7_REG_POLARITY_INVERSION    0x02
#define RELAY7_REG_CONFIGURATION         0x03

/*! @} */ // relay7_reg

/**
 * @defgroup relay7_set Relay 7 Registers Settings
 * @brief Settings for registers of Relay 7 Click driver.
 */

/**
 * @addtogroup relay7_set
 * @{
 */

/**
 * @brief Relay 7 port expander default configuration data.
 * @details Specified default configuration data of Relay 7 Click driver.
 */
#define RELAY7_DEFAULT_CONFIG            0xF0

/**
 * @brief Relay 7 pin mask data values.
 * @details Specified pin mask data values of Relay 7 Click driver.
 */
#define RELAY7_PIN_MASK_NONE             0x00
#define RELAY7_PIN_MASK_P0               0x01
#define RELAY7_PIN_MASK_P1               0x02
#define RELAY7_PIN_MASK_P2               0x04
#define RELAY7_PIN_MASK_P3               0x08
#define RELAY7_ALL_PIN                   0x0F

/**
 * @brief Relay 7 pin logic state setting.
 * @details Specified pin logic state setting of Relay 7 Click driver.
 */
#define RELAY7_PIN_STATE_LOW             0x00
#define RELAY7_PIN_STATE_HIGH            0x01

/**
 * @brief Relay 7 pin bitmask data values.
 * @details Specified pin bitmask data values of Relay 7 Click driver.
 */
#define RELAY7_SEL_REL1                  1
#define RELAY7_SEL_REL2                  2
#define RELAY7_SEL_REL3                  3
#define RELAY7_SEL_REL4                  4

/**
 * @brief Relay 7 device address setting.
 * @details Specified setting for device slave address selection of
 * Relay 7 Click driver.
 */
#define RELAY7_DEVICE_ADDRESS_0          0x70
#define RELAY7_DEVICE_ADDRESS_1          0x71
#define RELAY7_DEVICE_ADDRESS_2          0x72
#define RELAY7_DEVICE_ADDRESS_3          0x73

/*! @} */ // relay7_set

/**
 * @defgroup relay7_map Relay 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Relay 7 Click driver.
 */

/**
 * @addtogroup relay7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Relay 7 Click to the selected MikroBUS.
 */
#define RELAY7_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // relay7_map
/*! @} */ // relay7

/**
 * @brief Relay 7 Click context object.
 * @details Context object definition of Relay 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;        /**< Reset pin. */

    // Input pins
    digital_in_t int_pin;     /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} relay7_t;

/**
 * @brief Relay 7 Click configuration object.
 * @details Configuration object definition of Relay 7 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;        /**< Reset pin. */
    pin_name_t int_pin;    /**< Interrupt pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} relay7_cfg_t;

/**
 * @brief Relay 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RELAY7_OK = 0,
    RELAY7_ERROR = -1

} relay7_return_value_t;

/**
 * @brief Relay 7 Click relay state value data.
 * @details Predefined enum values for relay state values.
 */
typedef enum
{
    RELAY7_STATE_OPEN = 0,
    RELAY7_STATE_CLOSE = 1

} relay7_relay_state_t;

/*!
 * @addtogroup relay7 Relay 7 Click Driver
 * @brief API for configuring and manipulating Relay 7 Click driver.
 * @{
 */

/**
 * @brief Relay 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #relay7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void relay7_cfg_setup ( relay7_cfg_t *cfg );

/**
 * @brief Relay 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #relay7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #relay7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay7_init ( relay7_t *ctx, relay7_cfg_t *cfg );

/**
 * @brief Relay 7 default configuration function.
 * @details This function executes a default configuration of Relay 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #relay7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t relay7_default_cfg ( relay7_t *ctx );

/**
 * @brief Relay 7 reset device function.
 * @details This function performs a hardware reset of the
 * of the PCA9538A, Low-voltage 8-bit I2C-bus I/O port with interrupt and reset
 * on the Relay 7 Click board.
 * @param[in] ctx : Click context object.
 * See #relay7_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void relay7_reset_device ( relay7_t *ctx );

/**
 * @brief Relay 7 I2C writing function.
 * @details This function writes a data byte to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #relay7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay7_generic_write ( relay7_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Relay 7 I2C reading function.
 * @details This function reads the data bytes from the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #relay7_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay7_generic_read ( relay7_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Relay 7 set port expander function.
 * @details This function sets the output logic levels of the pins
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #relay7_t object definition for detailed explanation.
 * @param[in] set_mask : Set pin mask.
 * @param[in] pin_state : Pin state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay7_set_port_expander ( relay7_t *ctx, uint8_t set_mask, uint8_t pin_state );

/**
 * @brief Relay 7 set relay function.
 * @details This function sets the desired state of the selected relay
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #relay7_t object definition for detailed explanation.
 * @param[in] relay_sel : Relay selection [1-4].
 * @param[in] state : Relay state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t relay7_set_relay ( relay7_t *ctx, uint8_t relay_sel, relay7_relay_state_t state );

/**
 * @brief Relay 7 get interrupt function.
 * @details This function returns the interrupt pin logic state.
 * @param[in] ctx : Click context object.
 * See #relay7_t object definition for detailed explanation.
 * @return Interrupt pin logic state.
 * @note None.
 */
uint8_t relay7_get_interrupt ( relay7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RELAY7_H

/*! @} */ // relay7

// ------------------------------------------------------------------------ END
