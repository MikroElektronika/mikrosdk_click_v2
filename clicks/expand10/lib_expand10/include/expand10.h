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
 * @file expand10.h
 * @brief This file contains API for Expand 10 Click Driver.
 */

#ifndef EXPAND10_H
#define EXPAND10_H

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
 * @addtogroup expand10 Expand 10 Click Driver
 * @brief API for configuring and manipulating Expand 10 Click driver.
 * @{
 */

/**
 * @defgroup expand10_reg Expand 10 Registers List
 * @brief List of registers of Expand 10 Click driver.
 */

/**
 * @addtogroup expand10_reg
 * @{
 */

/**
 * @brief Expand 10 register list.
 * @details Specified register list of Expand 10 Click driver.
 */
#define EXPAND10_REG_INPUT_P0               0x00
#define EXPAND10_REG_INPUT_P1               0x01
#define EXPAND10_REG_INPUT_P2               0x02
#define EXPAND10_REG_OUTPUT_P0              0x04
#define EXPAND10_REG_OUTPUT_P1              0x05
#define EXPAND10_REG_OUTPUT_P2              0x06
#define EXPAND10_REG_POLARITY_INV_P0        0x08
#define EXPAND10_REG_POLARITY_INV_P1        0x09
#define EXPAND10_REG_POLARITY_INV_P2        0x0A
#define EXPAND10_REG_CONFIG_P0              0x0C
#define EXPAND10_REG_CONFIG_P1              0x0D
#define EXPAND10_REG_CONFIG_P2              0x0E
#define EXPAND10_REG_OUTPUT_DRIVE_P0A       0x40
#define EXPAND10_REG_OUTPUT_DRIVE_P0B       0x41
#define EXPAND10_REG_OUTPUT_DRIVE_P1A       0x42
#define EXPAND10_REG_OUTPUT_DRIVE_P1B       0x43
#define EXPAND10_REG_OUTPUT_DRIVE_P2A       0x44
#define EXPAND10_REG_OUTPUT_DRIVE_P2B       0x45
#define EXPAND10_REG_INPUT_LAT_P0           0x48
#define EXPAND10_REG_INPUT_LAT_P1           0x49
#define EXPAND10_REG_INPUT_LAT_P2           0x4A
#define EXPAND10_REG_PULL_ENABLE_P0         0x4C
#define EXPAND10_REG_PULL_ENABLE_P1         0x4D
#define EXPAND10_REG_PULL_ENABLE_P2         0x4E
#define EXPAND10_REG_PULL_SELECTION_P0      0x50
#define EXPAND10_REG_PULL_SELECTION_P1      0x51
#define EXPAND10_REG_PULL_SELECTION_P2      0x52
#define EXPAND10_REG_INT_MASK_P0            0x54
#define EXPAND10_REG_INT_MASK_P1            0x55
#define EXPAND10_REG_INT_MASK_P2            0x56
#define EXPAND10_REG_INT_STATUS_P0          0x58
#define EXPAND10_REG_INT_STATUS_P1          0x59
#define EXPAND10_REG_INT_STATUS_P2          0x5A
#define EXPAND10_REG_OUTPUT_PORT_CONFIG     0x5C
#define EXPAND10_REG_INT_EDGE_P0A           0x60
#define EXPAND10_REG_INT_EDGE_P0B           0x61
#define EXPAND10_REG_INT_EDGE_P1A           0x62
#define EXPAND10_REG_INT_EDGE_P1B           0x63
#define EXPAND10_REG_INT_EDGE_P2A           0x64
#define EXPAND10_REG_INT_EDGE_P2B           0x65
#define EXPAND10_REG_INT_CLEAR_P0           0x68
#define EXPAND10_REG_INT_CLEAR_P1           0x69
#define EXPAND10_REG_INT_CLEAR_P2           0x6A
#define EXPAND10_REG_INPUT_STATUS_P0        0x6C
#define EXPAND10_REG_INPUT_STATUS_P1        0x6D
#define EXPAND10_REG_INPUT_STATUS_P2        0x6E
#define EXPAND10_REG_PIN_OUTPUT_P0_CONFIG   0x70
#define EXPAND10_REG_PIN_OUTPUT_P1_CONFIG   0x71
#define EXPAND10_REG_PIN_OUTPUT_P2_CONFIG   0x72
#define EXPAND10_REG_SWITCH_DEBOUNCE_EN_0   0x74
#define EXPAND10_REG_SWITCH_DEBOUNCE_EN_1   0x75
#define EXPAND10_REG_SWITCH_DEBOUNCE_CNT    0x76

/*! @} */ // expand10_reg

/**
 * @defgroup expand10_set Expand 10 Registers Settings
 * @brief Settings for registers of Expand 10 Click driver.
 */

/**
 * @addtogroup expand10_set
 * @{
 */

/**
 * @brief Expand 10 pin mask values.
 * @details Specified pin mask values of Expand 10 Click driver.
 */
#define EXPAND10_NO_PIN_MASK                0x00
#define EXPAND10_PIN_0_MASK                 0x01
#define EXPAND10_PIN_1_MASK                 0x02
#define EXPAND10_PIN_2_MASK                 0x04
#define EXPAND10_PIN_3_MASK                 0x08
#define EXPAND10_PIN_4_MASK                 0x10
#define EXPAND10_PIN_5_MASK                 0x20
#define EXPAND10_PIN_6_MASK                 0x40
#define EXPAND10_PIN_7_MASK                 0x80
#define EXPAND10_ALL_PINS_MASK              0xFF

/**
 * @brief Expand 10 port values.
 * @details Specified port values of Expand 10 Click driver.
 */
#define EXPAND10_PORT_0                     0x00
#define EXPAND10_PORT_1                     0x01
#define EXPAND10_PORT_2                     0x02

/**
 * @brief Expand 10 pin direction values.
 * @details Specified pin direction values of Expand 10 Click driver.
 */
#define EXPAND10_OUTPUT_DIRECTION           0x00
#define EXPAND10_INPUT_DIRECTION            0x01

/**
 * @brief Expand 10 pin logic level values.
 * @details Specified pin logic level values of Expand 10 Click driver.
 */
#define EXPAND10_PIN_LOW_LEVEL              0x00
#define EXPAND10_PIN_HIGH_LEVEL             0x01

/**
 * @brief Expand 10 auto increment bit mask.
 * @details Specified bit mask for auto increment of Expand 10 Click driver.
 */
#define EXPAND10_AUTO_INCREMENT_BIT         0x80

/**
 * @brief Expand 10 device ID value.
 * @details Device ID value 24bit (manufacturer 12 MSB, part identification 9bits, revision 3 LSB) of Expand 10 Click driver.
 */
#define EXPAND10_DEVICE_ID                  0x000830

/**
 * @brief Expand 10 software reset value.
 * @details Specified value for software reset of Expand 10 Click driver.
 */
#define EXPAND10_SOFTWARE_RESET             0x06

/**
 * @brief Expand 10 general call and device ID addresses.
 * @details Specified setting for general call and device ID addresses of Expand 10 Click driver.
 */
#define EXPAND10_GEN_CALL_ADDR              0x00
#define EXPAND10_DEV_ID_ADDR                0x7C

/**
 * @brief Expand 10 device address setting.
 * @details Specified setting for device slave address selection of
 * Expand 10 Click driver.
 */
#define EXPAND10_SET_DEV_ADDR_0             0x22
#define EXPAND10_SET_DEV_ADDR_1             0x23

/*! @} */ // expand10_set

/**
 * @defgroup expand10_map Expand 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 10 Click driver.
 */

/**
 * @addtogroup expand10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 10 Click to the selected MikroBUS.
 */
#define EXPAND10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // expand10_map
/*! @} */ // expand10

/**
 * @brief Expand 10 Click context object.
 * @details Context object definition of Expand 10 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;         /**< Reset pin. */

    // Input pins
    digital_in_t   int_pin;     /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} expand10_t;

/**
 * @brief Expand 10 Click configuration object.
 * @details Configuration object definition of Expand 10 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;            /**< Reset pin. */
    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} expand10_cfg_t;

/**
 * @brief Expand 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EXPAND10_OK = 0,
    EXPAND10_ERROR = -1

} expand10_return_value_t;

/*!
 * @addtogroup expand10 Expand 10 Click Driver
 * @brief API for configuring and manipulating Expand 10 Click driver.
 * @{
 */

/**
 * @brief Expand 10 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand10_cfg_setup ( expand10_cfg_t *cfg );

/**
 * @brief Expand 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand10_init ( expand10_t *ctx, expand10_cfg_t *cfg );

/**
 * @brief Expand 10 default configuration function.
 * @details This function executes a default configuration of Expand 10
 * Click board.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t expand10_default_cfg ( expand10_t *ctx );

/**
 * @brief Expand 10 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand10_generic_write ( expand10_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Expand 10 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand10_generic_read ( expand10_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Expand 10 set RST pin function.
 * @details This function sets the logic level of the RST pin.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @param[in] logic_level : Pin logic level.
 * @return None.
 * @note None.
 */
void expand10_set_rst_pin ( expand10_t *ctx, uint8_t logic_level );

/**
 * @brief Expand 10 get INT pin function.
 * @details This function returns the logic level of the INT pin.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @return Pin logic level.
 * @note None.
 */
uint8_t expand10_get_int_pin ( expand10_t *ctx );

/**
 * @brief Expand 10 write register function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand10_write_register ( expand10_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Expand 10 read register function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand10_read_register ( expand10_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Expand 10 check device ID function.
 * @details This function reads and verifies the device ID.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @return @li @c  0 - Correct device ID read,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand10_check_device_id ( expand10_t *ctx );

/**
 * @brief Expand 10 software reset function.
 * @details This function performs the software reset.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand10_software_reset ( expand10_t *ctx );

/**
 * @brief Expand 10 set pin direction function.
 * @details This function sets the direction of the selected pins.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @param[in] direction : @li @c  0 - Output,
 *                        @li @c  1 - Input.
 * @param[in] port : @li @c  0 - Port 0,
 *                   @li @c  1 - Port 1.
 *                   @li @c  2 - Port 2.
 * @param[in] pin_mask : Pin mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand10_set_pin_direction ( expand10_t *ctx, uint8_t direction, uint8_t port, uint8_t pin_mask );

/**
 * @brief Expand 10 set all pins direction function.
 * @details This function sets the direction of all pins.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @param[in] direction : @li @c  0 - Output,
 *                        @li @c  1 - Input.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand10_set_all_pins_direction ( expand10_t *ctx, uint8_t direction );

/**
 * @brief Expand 10 set all pins value function.
 * @details This function sets the value of all output pins.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand10_set_all_pins_value ( expand10_t *ctx, uint8_t set_mask );

/**
 * @brief Expand 10 set pin value function.
 * @details This function sets the value of the selected pins.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - Port 0,
 *                   @li @c  1 - Port 1.
 *                   @li @c  2 - Port 2.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand10_set_pin_value ( expand10_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask );

/**
 * @brief Expand 10 read port value function.
 * @details This function reads the value of the selected port input pins.
 * @param[in] ctx : Click context object.
 * See #expand10_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - Port 0,
 *                   @li @c  1 - Port 1.
 *                   @li @c  2 - Port 2.
 * @param[out] data_out : Port value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand10_read_port_value ( expand10_t *ctx, uint8_t port, uint8_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // EXPAND10_H

/*! @} */ // expand10

// ------------------------------------------------------------------------ END
