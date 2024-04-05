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
 * @file expand15.h
 * @brief This file contains API for Expand 15 Click Driver.
 */

#ifndef EXPAND15_H
#define EXPAND15_H

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
 * @addtogroup expand15 Expand 15 Click Driver
 * @brief API for configuring and manipulating Expand 15 Click driver.
 * @{
 */

/**
 * @defgroup expand15_reg Expand 15 Registers List
 * @brief List of registers of Expand 15 Click driver.
 */

/**
 * @addtogroup expand15_reg
 * @{
 */

/**
 * @brief Expand 15 description register.
 * @details Specified register for description of Expand 15 Click driver.
 */
#define EXPAND15_REG_INPUT_PORT_0               0x00
#define EXPAND15_REG_INPUT_PORT_1               0x01
#define EXPAND15_REG_OUTPUT_PORT_0              0x02
#define EXPAND15_REG_OUTPUT_PORT_1              0x03
#define EXPAND15_REG_POLARITY_INVERSION_0       0x04
#define EXPAND15_REG_POLARITY_INVERSION_1       0x05
#define EXPAND15_REG_CONFIGURATION_0            0x06
#define EXPAND15_REG_CONFIGURATION_1            0x07
#define EXPAND15_REG_OUTPUT_DRV_STRENGTH_0_0    0x40
#define EXPAND15_REG_OUTPUT_DRV_STRENGTH_0_1    0x41
#define EXPAND15_REG_OUTPUT_DRV_STRENGTH_1_0    0x42
#define EXPAND15_REG_OUTPUT_DRV_STRENGTH_1_1    0x43
#define EXPAND15_REG_INPUT_LATCH_0              0x44
#define EXPAND15_REG_INPUT_LATCH_1              0x45
#define EXPAND15_REG_PULL_UP_DOWN_EN_0          0x46
#define EXPAND15_REG_PULL_UP_DOWN_EN_1          0x47
#define EXPAND15_REG_PULL_UP_DOWN_SELECT_0      0x48
#define EXPAND15_REG_PULL_UP_DOWN_SELECT_1      0x49
#define EXPAND15_REG_INTERRUPT_MASK_0           0x4A
#define EXPAND15_REG_INTERRUPT_MASK_1           0x4B
#define EXPAND15_REG_INTERRUPT_STATUS_0         0x4C
#define EXPAND15_REG_INTERRUPT_STATUS_1         0x4D
#define EXPAND15_REG_OUTPUT_PORT_CFG            0x4F


/*! @} */ // expand15_reg

/**
 * @defgroup expand15_set Expand 15 Registers Settings
 * @brief Settings for registers of Expand 15 Click driver.
 */

/**
 * @addtogroup expand15_set
 * @{
 */

/**
 * @brief Expand 15 description setting.
 * @details Specified setting for description of Expand 15 Click driver.
 */
#define EXPAND15_PIN_00_MASK                    0x01
#define EXPAND15_PIN_01_MASK                    0x02
#define EXPAND15_PIN_02_MASK                    0x04
#define EXPAND15_PIN_03_MASK                    0x08
#define EXPAND15_PIN_04_MASK                    0x10
#define EXPAND15_PIN_05_MASK                    0x20
#define EXPAND15_PIN_06_MASK                    0x40
#define EXPAND15_PIN_07_MASK                    0x80
#define EXPAND15_PIN_10_MASK                    0x01
#define EXPAND15_PIN_11_MASK                    0x02
#define EXPAND15_PIN_12_MASK                    0x04
#define EXPAND15_PIN_13_MASK                    0x08
#define EXPAND15_PIN_14_MASK                    0x10
#define EXPAND15_PIN_15_MASK                    0x20
#define EXPAND15_PIN_16_MASK                    0x40
#define EXPAND15_PIN_17_MASK                    0x80

/**
 * @brief Expand 15 port selection setting.
 * @details Specified setting for port selection of Expand 15 Click driver.
 */
#define EXPAND15_PORT_0                         0x00
#define EXPAND15_PORT_1                         0x01

/**
 * @brief Expand 15 output pins strength setting.
 * @details Specified setting for output pins strengt of Expand 15 Click driver.
 */
#define EXPAND15_OUTPUT_STRENGTH_FULL           0x03
#define EXPAND15_OUTPUT_STRENGTH_3_QUARTERS     0x02
#define EXPAND15_OUTPUT_STRENGTH_HALF           0x01
#define EXPAND15_OUTPUT_STRENGTH_1_QUARTER      0x00

/**
 * @brief Expand 15 output port configuration setting.
 * @details Specified setting for output port configuration of Expand 15 Click driver.
 */
#define EXPAND15_PORT_PUSH_PULL                 0x00
#define EXPAND15_PORT_OPEN_DRAIN                0x01

/**
 * @brief Expand 15 pin selection setting.
 * @details Specified setting for pin selection of Expand 15 Click driver.
 */
#define EXPAND15_ALL_PINS_ON                    0xFF
#define EXPAND15_ALL_PINS_OFF                   0x00

/**
 * @brief Expand 15 device address setting.
 * @details Specified setting for device slave address selection of
 * Expand 15 Click driver.
 */
#define EXPAND15_DEVICE_ADDRESS_GND             0x20
#define EXPAND15_DEVICE_ADDRESS_VCC             0x21

/*! @} */ // expand15_set

/**
 * @defgroup expand15_map Expand 15 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 15 Click driver.
 */

/**
 * @addtogroup expand15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 15 Click to the selected MikroBUS.
 */
#define EXPAND15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // expand15_map
/*! @} */ // expand15

/**
 * @brief Expand 15 Click context object.
 * @details Context object definition of Expand 15 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;  /**< Reset pin. */

    // Input pins
    digital_in_t int_pin;    /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} expand15_t;

/**
 * @brief Expand 15 Click configuration object.
 * @details Configuration object definition of Expand 15 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} expand15_cfg_t;

/**
 * @brief Expand 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EXPAND15_OK = 0,
    EXPAND15_ERROR = -1

} expand15_return_value_t;

/*!
 * @addtogroup expand15 Expand 15 Click Driver
 * @brief API for configuring and manipulating Expand 15 Click driver.
 * @{
 */

/**
 * @brief Expand 15 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand15_cfg_setup ( expand15_cfg_t *cfg );

/**
 * @brief Expand 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_init ( expand15_t *ctx, expand15_cfg_t *cfg );

/**
 * @brief Expand 15 default configuration function.
 * @details This function executes a default configuration of Expand 15
 * click board.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t expand15_default_cfg ( expand15_t *ctx );

/**
 * @brief Expand 15 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_generic_write ( expand15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Expand 15 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_generic_read ( expand15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Expand 15 get interrupt function.
 * @details This function reads a state of the interrupt pin.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @return State of the INT pin.
 * @note None.
 */
uint8_t expand15_get_int_pin_state ( expand15_t *ctx );

/**
 * @brief Expand 15 hardware reset function.
 * @details This function is used to perform hardware reset of the click board.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void expand15_hw_reset ( expand15_t *ctx );

/**
 * @brief Expand 15 get input pin state function.
 * @details This function reads a state of the pins defined as input.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[out] pin_state : Pin state of the selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_get_in_pin_state ( expand15_t *ctx, uint8_t port, uint8_t *pin_state );

/**
 * @brief Expand 15 get output pin state function.
 * @details This function reads a state of the pins defined as output.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[out] pin_state : Pin state of the selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_get_out_pin_state ( expand15_t *ctx, uint8_t port, uint8_t *pin_state );

/**
 * @brief Expand 15 set output pin state function.
 * @details This function writes a state of the pins defined as output.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[in] pin_state : Pin state of the selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_set_out_pin_state ( expand15_t *ctx, uint8_t port, uint8_t pin_state );

/**
 * @brief Expand 15 get input pin polarity function.
 * @details This function reads a polarity of the pins defined as input.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[out] pin_polarity : Pin polarity of the selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_get_in_pin_polarity ( expand15_t *ctx, uint8_t port, uint8_t *pin_polarity );

/**
 * @brief Expand 15 set input pin polarity function.
 * @details This function write a polarity of the pins defined as input.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[in] pin_polarity : Pin polarity of the selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_set_in_pin_polarity ( expand15_t *ctx, uint8_t port, uint8_t pin_polarity );

/**
 * @brief Expand 15 get pin configuration function.
 * @details This function reads a configuration of pins of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[out] pin_config : Pin configuration of the selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_get_pin_config ( expand15_t *ctx, uint8_t port, uint8_t *pin_config );

/**
 * @brief Expand 15 set pin as input function.
 * @details This function writes a input pin configuration of pins of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[in] pin_config : Pin configuration of the selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_set_pin_as_in ( expand15_t *ctx, uint8_t port, uint8_t pin_config );

/**
 * @brief Expand 15 set pin as output function.
 * @details This function writes a output pin configuration of pins of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[in] pin_config : Pin configuration of the selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_set_pin_as_out ( expand15_t *ctx, uint8_t port, uint8_t pin_config );

/**
 * @brief Expand 15 get output level function.
 * @details This function reads a output level of pins of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[out] pin_output_level : Pin output level of the selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_get_out_level ( expand15_t *ctx, uint8_t port, uint16_t *pin_output_level );

/**
 * @brief Expand 15 set output level function.
 * @details This function writes a output level of pins of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[in] pin_output_level : Pin output level of the selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_set_out_level ( expand15_t *ctx, uint8_t port, uint16_t pin_output_level );

/**
 * @brief Expand 15 set pin output strength function.
 * @details This function writes a set pin output strength of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[in] pin : Selected pin.
 * @param[in] strength : Strength of pin output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_set_out_pin_strength( expand15_t *ctx, uint8_t port, uint8_t pin, uint8_t strength );

/**
 * @brief Expand 15 set enable pull up/down function.
 * @details This function enables pull up/down of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[in] port_config : Port config to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_set_en_pull_up_down ( expand15_t *ctx, uint8_t port, uint8_t port_config );

/**
 * @brief Expand 15 get enable pull up/down function.
 * @details This function reads pull up/down enables of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[out] port_config : Port config to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_get_en_pull_up_down ( expand15_t *ctx, uint8_t port, uint8_t *port_config );

/**
 * @brief Expand 15 set pull up/down function.
 * @details This function writes pull up/down pin state of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[in] pin_config : Pins where pull up/down is active.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_set_pull_up_down ( expand15_t *ctx, uint8_t port, uint8_t pin_config );

/**
 * @brief Expand 15 get pull up/down function.
 * @details This function reads pull up/down pin state of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[out] pin_config : Pins where pull up/down is active.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_get_pull_up_down ( expand15_t *ctx, uint8_t port, uint8_t *pin_config );

/**
 * @brief Expand 15 set interrupt mask function.
 * @details This function writes interrupt mask value of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[in] int_config : Pin interrupt mask of selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_set_int_mask ( expand15_t *ctx, uint8_t port, uint8_t int_config );

/**
 * @brief Expand 15 get interrupt mask function.
 * @details This function read interrupt mask value of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[out] int_config : Pin interrupt mask of selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_get_int_mask ( expand15_t *ctx, uint8_t port, uint8_t *int_config );

/**
 * @brief Expand 15 get interrupt status function.
 * @details This function read interrupt status value of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port : Selected port.
 * @param[out] int_status : Pin interrupt status of selected port.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_get_int_status ( expand15_t *ctx, uint8_t port, uint8_t *int_status );

/**
 * @brief Expand 15 get output port configuration function.
 * @details This function reads port output configuration value of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[out] port0_cfg : Port 0 configuration.
 * @param[out] port1_cfg : Port 1 configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_get_out_port_config ( expand15_t *ctx, uint8_t *port0_cfg, uint8_t *port1_cfg );

/**
 * @brief Expand 15 set output port configuration function.
 * @details This function writes port output configuration value of selected port.
 * @param[in] ctx : Click context object.
 * See #expand15_t object definition for detailed explanation.
 * @param[in] port0_cfg : Port 0 configuration.
 * @param[in] port1_cfg : Port 1 configuration.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand15_set_out_port_config ( expand15_t *ctx, uint8_t port0_cfg, uint8_t port1_cfg );

#ifdef __cplusplus
}
#endif
#endif // EXPAND15_H

/*! @} */ // expand15

// ------------------------------------------------------------------------ END
