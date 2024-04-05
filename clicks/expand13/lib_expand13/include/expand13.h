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
 * @file expand13.h
 * @brief This file contains API for Expand 13 Click Driver.
 */

#ifndef EXPAND13_H
#define EXPAND13_H

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
 * @addtogroup expand13 Expand 13 Click Driver
 * @brief API for configuring and manipulating Expand 13 Click driver.
 * @{
 */

/**
 * @defgroup expand13_set Expand 13 Settings
 * @brief Settings of Expand 13 Click driver.
 */

/**
 * @addtogroup expand13_set
 * @{
 */

/**
 * @brief Expand 13 pin mask values.
 * @details Specified pin mask values of Expand 13 Click driver.
 */
#define EXPAND13_NO_PIN_MASK                            0x00
#define EXPAND13_PIN_0_MASK                             0x01
#define EXPAND13_PIN_1_MASK                             0x02
#define EXPAND13_PIN_2_MASK                             0x04
#define EXPAND13_PIN_3_MASK                             0x08
#define EXPAND13_PIN_4_MASK                             0x10
#define EXPAND13_PIN_5_MASK                             0x20
#define EXPAND13_PIN_6_MASK                             0x40
#define EXPAND13_PIN_7_MASK                             0x80
#define EXPAND13_ALL_PINS_MASK                          0xFF

/**
 * @brief Expand 13 port values.
 * @details Specified port values of Expand 13 Click driver.
 */
#define EXPAND13_PORT_0                                 0x00
#define EXPAND13_PORT_1                                 0x01
#define EXPAND13_PORT_2                                 0x02
#define EXPAND13_PORT_3                                 0x03
#define EXPAND13_PORT_4                                 0x04
#define EXPAND13_PORT_5                                 0x05

/**
 * @brief Expand 13 device address setting.
 * @details Specified setting for device slave address selection of
 * Expand 13 Click driver.
 */
#define EXPAND13_SET_DEV_ADDR_A2A1A0_000                0x20
#define EXPAND13_SET_DEV_ADDR_A2A1A0_001                0x21
#define EXPAND13_SET_DEV_ADDR_A2A1A0_010                0x22
#define EXPAND13_SET_DEV_ADDR_A2A1A0_011                0x23
#define EXPAND13_SET_DEV_ADDR_A2A1A0_100                0x24
#define EXPAND13_SET_DEV_ADDR_A2A1A0_101                0x25
#define EXPAND13_SET_DEV_ADDR_A2A1A0_110                0x26
#define EXPAND13_SET_DEV_ADDR_A2A1A0_111                0x27

/*! @} */ // expand13_set

/**
 * @defgroup expand13_map Expand 13 MikroBUS Map
 * @brief MikroBUS pin mapping of Expand 13 Click driver.
 */

/**
 * @addtogroup expand13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Expand 13 Click to the selected MikroBUS.
 */
#define EXPAND13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // expand13_map
/*! @} */ // expand13

/**
 * @brief Expand 13 Click context object.
 * @details Context object definition of Expand 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t   rst;        /**< Reset pin. */

    // Input pins
    digital_in_t    int_pin;    /**< Interrupt pin. */

    // Modules
    i2c_master_t    i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} expand13_t;

/**
 * @brief Expand 13 Click configuration object.
 * @details Configuration object definition of Expand 13 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;        /**< Reset pin. */
    pin_name_t  int_pin;    /**< Interrupt pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} expand13_cfg_t;

/**
 * @brief Expand 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EXPAND13_OK = 0,
    EXPAND13_ERROR = -1

} expand13_return_value_t;

/*!
 * @addtogroup expand13 Expand 13 Click Driver
 * @brief API for configuring and manipulating Expand 13 Click driver.
 * @{
 */

/**
 * @brief Expand 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #expand13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void expand13_cfg_setup ( expand13_cfg_t *cfg );

/**
 * @brief Expand 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #expand13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #expand13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand13_init ( expand13_t *ctx, expand13_cfg_t *cfg );

/**
 * @brief Expand 13 enable device function.
 * @details This function enables the device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #expand13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void expand13_enable_device ( expand13_t *ctx );

/**
 * @brief Expand 13 disable device function.
 * @details This function disables the device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #expand13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void expand13_disable_device ( expand13_t *ctx );

/**
 * @brief Expand 13 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #expand13_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t expand13_get_int_pin ( expand13_t *ctx );

/**
 * @brief Expand 13 write all ports function.
 * @details This function writes a desired data to all 6 ports.
 * @param[in] ctx : Click context object.
 * See #expand13_t object definition for detailed explanation.
 * @param[in] ports : Ports array of 6 bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand13_write_all_ports ( expand13_t *ctx, uint8_t *ports );

/**
 * @brief Expand 13 read all ports function.
 * @details This function reads the state of all 6 ports.
 * @param[in] ctx : Click context object.
 * See #expand13_t object definition for detailed explanation.
 * @param[out] ports : Ports array of 6 bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand13_read_all_ports ( expand13_t *ctx, uint8_t *ports );

/**
 * @brief Expand 13 set port value function.
 * @details This function sets the value of the selected port.
 * @param[in] ctx : Click context object.
 * See #expand13_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - Port 0,
 *                   @li @c  1 - Port 1.
 *                   @li @c  2 - Port 2.
 *                   @li @c  3 - Port 3.
 *                   @li @c  4 - Port 4.
 *                   @li @c  5 - Port 5.
 * @param[in] clr_mask : Port clear mask.
 * @param[in] set_mask : Port set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand13_set_port_value ( expand13_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask );

/**
 * @brief Expand 13 read port value function.
 * @details This function reads the value of the selected port.
 * @param[in] ctx : Click context object.
 * See #expand13_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - Port 0,
 *                   @li @c  1 - Port 1.
 *                   @li @c  2 - Port 2.
 *                   @li @c  3 - Port 3.
 *                   @li @c  4 - Port 4.
 *                   @li @c  5 - Port 5.
 * @param[out] data_out : Port value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t expand13_read_port_value ( expand13_t *ctx, uint8_t port, uint8_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // EXPAND13_H

/*! @} */ // expand13

// ------------------------------------------------------------------------ END
