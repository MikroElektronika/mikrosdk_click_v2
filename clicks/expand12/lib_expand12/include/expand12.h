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
 * @file expand12.h
 * @brief This file contains API for Expand 12 Click Driver.
 */

#ifndef EXPAND12_H
#define EXPAND12_H

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
 * @addtogroup expand12 Expand 12 Click Driver
 * @brief API for configuring and manipulating Expand 12 Click driver.
 * @{
 */

/**
 * @defgroup expand12_reg Expand 12 Registers List
 * @brief List of registers of Expand 12 Click driver.
 */

/**
 * @addtogroup expand12_reg
 * @{
 */

/**
 * @brief Expand 12 register map.
 * @details Specified register map of Expand 12 Click driver.
 */
#define EXPAND12_REG_NOP                        0x00
#define EXPAND12_REG_CONFIG                     0x04
#define EXPAND12_REG_TRANSITION_DETECT_MASK     0x06
#define EXPAND12_REG_RESERVED                   0x07
#define EXPAND12_REG_CONFIG_P7_4                0x09
#define EXPAND12_REG_CONFIG_P11_8               0x0A
#define EXPAND12_REG_CONFIG_P15_12              0x0B
#define EXPAND12_REG_CONFIG_P19_16              0x0C
#define EXPAND12_REG_CONFIG_P23_20              0x0D
#define EXPAND12_REG_CONFIG_P27_24              0x0E
#define EXPAND12_REG_CONFIG_P31_28              0x0F
#define EXPAND12_REG_P0                         0x20
#define EXPAND12_REG_P1                         0x21
#define EXPAND12_REG_P2                         0x22
#define EXPAND12_REG_P3                         0x23
#define EXPAND12_REG_P4                         0x24
#define EXPAND12_REG_P5                         0x25
#define EXPAND12_REG_P6                         0x26
#define EXPAND12_REG_P7                         0x27
#define EXPAND12_REG_P8                         0x28
#define EXPAND12_REG_P9                         0x29
#define EXPAND12_REG_P10                        0x2A
#define EXPAND12_REG_P11                        0x2B
#define EXPAND12_REG_P12                        0x2C
#define EXPAND12_REG_P13                        0x2D
#define EXPAND12_REG_P14                        0x2E
#define EXPAND12_REG_P15                        0x2F
#define EXPAND12_REG_P16                        0x30
#define EXPAND12_REG_P17                        0x31
#define EXPAND12_REG_P18                        0x32
#define EXPAND12_REG_P19                        0x33
#define EXPAND12_REG_P20                        0x34
#define EXPAND12_REG_P21                        0x35
#define EXPAND12_REG_P22                        0x36
#define EXPAND12_REG_P23                        0x37
#define EXPAND12_REG_P24                        0x38
#define EXPAND12_REG_P25                        0x39
#define EXPAND12_REG_P26                        0x3A
#define EXPAND12_REG_P27                        0x3B
#define EXPAND12_REG_P28                        0x3C
#define EXPAND12_REG_P29                        0x3D
#define EXPAND12_REG_P30                        0x3E
#define EXPAND12_REG_P31                        0x3F
#define EXPAND12_REG_P4_7                       0x40
#define EXPAND12_REG_P4_8                       0x41
#define EXPAND12_REG_P4_9                       0x42
#define EXPAND12_REG_P4_10                      0x43
#define EXPAND12_REG_P4_11                      0x44
#define EXPAND12_REG_P5_12                      0x45
#define EXPAND12_REG_P6_13                      0x46
#define EXPAND12_REG_P7_14                      0x47
#define EXPAND12_REG_P8_15                      0x48
#define EXPAND12_REG_P9_16                      0x49
#define EXPAND12_REG_P10_17                     0x4A
#define EXPAND12_REG_P11_18                     0x4B
#define EXPAND12_REG_P12_19                     0x4C
#define EXPAND12_REG_P13_20                     0x4D
#define EXPAND12_REG_P14_21                     0x4E
#define EXPAND12_REG_P15_22                     0x4F
#define EXPAND12_REG_P16_23                     0x50
#define EXPAND12_REG_P17_24                     0x51
#define EXPAND12_REG_P18_25                     0x52
#define EXPAND12_REG_P19_26                     0x53
#define EXPAND12_REG_P20_27                     0x54
#define EXPAND12_REG_P21_28                     0x55
#define EXPAND12_REG_P22_29                     0x56
#define EXPAND12_REG_P23_30                     0x57
#define EXPAND12_REG_P24_31                     0x58
#define EXPAND12_REG_P25_31                     0x59
#define EXPAND12_REG_P26_31                     0x5A
#define EXPAND12_REG_P27_31                     0x5B
#define EXPAND12_REG_P28_31                     0x5C
#define EXPAND12_REG_P29_31                     0x5D
#define EXPAND12_REG_P30_31                     0x5E
#define EXPAND12_REG_P31_ONLY                   0x5F

/*! @} */ // expand12_reg

/**
 * @defgroup expand12_set Expand 12 Registers Settings
 * @brief Settings for registers of Expand 12 Click driver.
 */

/**
 * @addtogroup expand12_set
 * @{
 */

/**
 * @brief Expand 12 pin and port selection values.
 * @details Specified pin and port selection values of Expand 12 Click driver.
 */
#define EXPAND12_PIN_4                          0x00
#define EXPAND12_PIN_5                          0x01
#define EXPAND12_PIN_6                          0x02
#define EXPAND12_PIN_7                          0x03
#define EXPAND12_PIN_8                          0x04
#define EXPAND12_PIN_9                          0x05
#define EXPAND12_PIN_10                         0x06
#define EXPAND12_PIN_11                         0x07
#define EXPAND12_PIN_12                         0x08
#define EXPAND12_PIN_13                         0x09
#define EXPAND12_PIN_14                         0x0A
#define EXPAND12_PIN_15                         0x0B
#define EXPAND12_PIN_16                         0x0C
#define EXPAND12_PIN_17                         0x0D
#define EXPAND12_PIN_18                         0x0E
#define EXPAND12_PIN_19                         0x0F
#define EXPAND12_PIN_20                         0x10
#define EXPAND12_PIN_21                         0x11
#define EXPAND12_PIN_22                         0x12
#define EXPAND12_PIN_23                         0x13
#define EXPAND12_PIN_24                         0x14
#define EXPAND12_PIN_25                         0x15
#define EXPAND12_PIN_26                         0x16
#define EXPAND12_PIN_27                         0x17
#define EXPAND12_PIN_28                         0x18
#define EXPAND12_PIN_29                         0x19
#define EXPAND12_PIN_30                         0x1A
#define EXPAND12_PIN_31                         0x1B
#define EXPAND12_ALL_PINS                       0xFF
#define EXPAND12_NO_PINS                        0x00
#define EXPAND12_PORT_4_7                       0x00
#define EXPAND12_PORT_8_15                      0x01
#define EXPAND12_PORT_16_23                     0x02
#define EXPAND12_PORT_24_31                     0x03

/**
 * @brief Expand 12 pin direction setting.
 * @details Specified setting for pin direction of Expand 12 Click driver.
 */
#define EXPAND12_DIR_OUTPUT                     0x01
#define EXPAND12_DIR_INPUT                      0x02
#define EXPAND12_DIR_INPUT_WITH_PULLUP          0x03

/**
 * @brief Expand 12 operating mode setting.
 * @details Specified setting for operating mode of Expand 12 Click driver.
 */
#define EXPAND12_OPMODE_SHUTDOWN                0x00
#define EXPAND12_OPMODE_NORMAL                  0x01

/**
 * @brief Expand 12 pin logic level values.
 * @details Specified pin logic level values of Expand 12 Click driver.
 */
#define EXPAND12_PIN_LOW_LEVEL                  0x00
#define EXPAND12_PIN_HIGH_LEVEL                 0x01

/**
 * @brief Expand 12 device address setting.
 * @details Specified setting for device slave address selection of
 * Expand 12 Click driver.
 */
#define EXPAND12_SET_DEV_ADDR_A1A0_00           0x40
#define EXPAND12_SET_DEV_ADDR_A1A0_01           0x41
#define EXPAND12_SET_DEV_ADDR_A1A0_10           0x44
#define EXPAND12_SET_DEV_ADDR_A1A0_11           0x45

/*! @} */ // expand12_set

/**
 * @defgroup expand12_map Expand 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 12 Click driver.
 */

/**
 * @addtogroup expand12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 12 Click to the selected MikroBUS.
 */
#define EXPAND12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // expand12_map
/*! @} */ // expand12

/**
 * @brief Expand 12 Click context object.
 * @details Context object definition of Expand 12 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} expand12_t;

/**
 * @brief Expand 12 Click configuration object.
 * @details Configuration object definition of Expand 12 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} expand12_cfg_t;

/**
 * @brief Expand 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EXPAND12_OK = 0,
    EXPAND12_ERROR = -1

} expand12_return_value_t;

/*!
 * @addtogroup expand12 Expand 12 Click Driver
 * @brief API for configuring and manipulating Expand 12 Click driver.
 * @{
 */

/**
 * @brief Expand 12 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand12_cfg_setup ( expand12_cfg_t *cfg );

/**
 * @brief Expand 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_init ( expand12_t *ctx, expand12_cfg_t *cfg );

/**
 * @brief Expand 12 default configuration function.
 * @details This function executes a default configuration of Expand 12
 * click board.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t expand12_default_cfg ( expand12_t *ctx );

/**
 * @brief Expand 12 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_generic_write ( expand12_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Expand 12 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_generic_read ( expand12_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Expand 12 write register function.
 * @details This function writes a desired data byte to
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_write_register ( expand12_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Expand 12 read register function.
 * @details This function reads a data byte from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_read_register ( expand12_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Expand 12 set operating mode function.
 * @details This function sets a device operating mode.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] state : @li @c  0 - Shutdown,
 *                    @li @c  1 - Normal operating mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_set_operating_mode ( expand12_t *ctx, uint8_t state );

/**
 * @brief Expand 12 set pin direction function.
 * @details This function sets the direction of the selected pin.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] pin : Pin selection value [0,27].
 * @param[in] direction : @li @c  1 - Output,
 *                        @li @c  2 - Input,
 *                        @li @c  3 - Input with pullup.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_set_pin_direction ( expand12_t *ctx, uint8_t pin, uint8_t direction );

/**
 * @brief Expand 12 set port direction function.
 * @details This function sets the direction of the selected port.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - Port 4-7,
 *                   @li @c  1 - Port 8-15,
 *                   @li @c  2 - Port 16-23,
 *                   @li @c  3 - Port 24-31.
 * @param[in] direction : @li @c  1 - Output,
 *                        @li @c  2 - Input,
 *                        @li @c  3 - Input with pullup.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_set_port_direction ( expand12_t *ctx, uint8_t port, uint8_t direction );

/**
 * @brief Expand 12 set all pins direction function.
 * @details This function sets the direction of all pins.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] direction : @li @c  1 - Output,
 *                        @li @c  2 - Input,
 *                        @li @c  3 - Input with pullup.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_set_all_pins_direction ( expand12_t *ctx, uint8_t direction );

/**
 * @brief Expand 12 set pin value function.
 * @details This function sets the logic level of the selected pin.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] pin : Pin selection value [0,27].
 * @param[in] pin_value : @li @c  0 - Low,
 *                        @li @c  1 - High.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_set_pin_value ( expand12_t *ctx, uint8_t pin, uint8_t pin_value );

/**
 * @brief Expand 12 set port value function.
 * @details This function sets the pins level value of the selected port.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - Port 4-7,
 *                   @li @c  1 - Port 8-15,
 *                   @li @c  2 - Port 16-23,
 *                   @li @c  3 - Port 24-31.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_set_port_value ( expand12_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask );

/**
 * @brief Expand 12 set all pins value function.
 * @details This function sets the logic level of all output pins.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] pin_value : @li @c  0 - Low,
 *                        @li @c  1 - High.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_set_all_pins_value ( expand12_t *ctx, uint8_t pin_value );

/**
 * @brief Expand 12 read pin value function.
 * @details This function reads the logic level of the selected pin.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] pin : Pin selection value [0,27].
 * @param[out] pin_value : @li @c  0 - Low,
 *                         @li @c  1 - High.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_read_pin_value ( expand12_t *ctx, uint8_t pin, uint8_t *pin_value );

/**
 * @brief Expand 12 read port value function.
 * @details This function reads the pins logic level of the selected port.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - Port 4-7,
 *                   @li @c  1 - Port 8-15,
 *                   @li @c  2 - Port 16-23,
 *                   @li @c  3 - Port 24-31.
 * @param[out] port_value : Port value (8-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_read_port_value ( expand12_t *ctx, uint8_t port, uint8_t *port_value );

/**
 * @brief Expand 12 read all pins value function.
 * @details This function reads all pins logic levels.
 * @param[in] ctx : Click context object.
 * See #expand12_t object definition for detailed explanation.
 * @param[out] pins_value : All pins value (32-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand12_read_all_pins_value ( expand12_t *ctx, uint32_t *pins_value );

#ifdef __cplusplus
}
#endif
#endif // EXPAND12_H

/*! @} */ // expand12

// ------------------------------------------------------------------------ END
