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
 * @file joystick4.h
 * @brief This file contains API for Joystick 4 Click Driver.
 */

#ifndef JOYSTICK4_H
#define JOYSTICK4_H

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
 * @addtogroup joystick4 Joystick 4 Click Driver
 * @brief API for configuring and manipulating Joystick 4 Click driver.
 * @{
 */

/**
 * @defgroup joystick4_reg Joystick 4 Registers List
 * @brief List of registers of Joystick 4 Click driver.
 */

/**
 * @addtogroup joystick4_reg
 * @{
 */

/**
 * @brief Joystick 4 registers.
 * @details Specified registers of Joystick 4 Click driver.
 */
#define JOYSTICK4_REG_INPUT                 0x00
#define JOYSTICK4_REG_OUTPUT                0x01
#define JOYSTICK4_REG_POLARITY              0x02
#define JOYSTICK4_REG_CONFIG                0x03

/*! @} */ // joystick4_reg

/**
 * @defgroup joystick4_set Joystick 4 Registers Settings
 * @brief Settings for registers of Joystick 4 Click driver.
 */

/**
 * @addtogroup joystick4_set
 * @{
 */

/**
 * @brief Joystick 4 pin mask.
 * @details Specified PCA9538A pin mask of Joystick 4 Click driver.
 */
#define JOYSTICK4_PIN_A                     0x20
#define JOYSTICK4_PIN_B                     0x08
#define JOYSTICK4_PIN_C                     0x80
#define JOYSTICK4_PIN_D                     0x10
#define JOYSTICK4_PIN_CE                    0x40

/**
 * @brief Joystick 4 pin direction config.
 * @details Specified pin direction config of Joystick 4 Click driver.
 */
#define JOYSTICK4_DEFAULT_PIN_CONFIG        0xFF

/**
 * @brief Joystick 4 pin logic state setting.
 * @details Specified setting for pin logic state of Joystick 4 Click driver.
 */
#define JOYSTICK4_PIN_STATE_LOW             0
#define JOYSTICK4_PIN_STATE_HIGH            1

/**
 * @brief Joystick 4 position values.
 * @details Specified position values of Joystick 4 Click driver.
 */
#define JOYSTICK4_POSITION_IDLE             0
#define JOYSTICK4_POSITION_CENTER           1
#define JOYSTICK4_POSITION_CENTER_UP        2
#define JOYSTICK4_POSITION_CENTER_RIGHT     3
#define JOYSTICK4_POSITION_CENTER_DOWN      4
#define JOYSTICK4_POSITION_CENTER_LEFT      5
#define JOYSTICK4_POSITION_UP               6
#define JOYSTICK4_POSITION_UPPER_RIGHT      7
#define JOYSTICK4_POSITION_RIGHT            8
#define JOYSTICK4_POSITION_LOWER_RIGHT      9
#define JOYSTICK4_POSITION_DOWN             10
#define JOYSTICK4_POSITION_LOWER_LEFT       11
#define JOYSTICK4_POSITION_LEFT             12
#define JOYSTICK4_POSITION_UPPER_LEFT       13

/**
 * @brief Joystick 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Joystick 4 Click driver.
 */
#define JOYSTICK4_DEVICE_ADDRESS_0          0x20
#define JOYSTICK4_DEVICE_ADDRESS_1          0x21

/*! @} */ // joystick4_set

/**
 * @defgroup joystick4_map Joystick 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Joystick 4 Click driver.
 */

/**
 * @addtogroup joystick4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Joystick 4 Click to the selected MikroBUS.
 */
#define JOYSTICK4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // joystick4_map
/*! @} */ // joystick4

/**
 * @brief Joystick 4 Click context object.
 * @details Context object definition of Joystick 4 Click driver.
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

} joystick4_t;

/**
 * @brief Joystick 4 Click configuration object.
 * @details Configuration object definition of Joystick 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} joystick4_cfg_t;

/**
 * @brief Joystick 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    JOYSTICK4_OK = 0,
    JOYSTICK4_ERROR = -1

} joystick4_return_value_t;

/*!
 * @addtogroup joystick4 Joystick 4 Click Driver
 * @brief API for configuring and manipulating Joystick 4 Click driver.
 * @{
 */

/**
 * @brief Joystick 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #joystick4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void joystick4_cfg_setup ( joystick4_cfg_t *cfg );

/**
 * @brief Joystick 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #joystick4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #joystick4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t joystick4_init ( joystick4_t *ctx, joystick4_cfg_t *cfg );

/**
 * @brief Joystick 4 default configuration function.
 * @details This function executes a default configuration of Joystick 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #joystick4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t joystick4_default_cfg ( joystick4_t *ctx );

/**
 * @brief Joystick 4 write reg function.
 * @details This function writes a desired data byte to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #joystick4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t joystick4_write_reg ( joystick4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Joystick 4 read reg function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #joystick4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t joystick4_read_reg ( joystick4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Joystick 4 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #joystick4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void joystick4_reset_device ( joystick4_t *ctx );

/**
 * @brief Joystick 4 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #joystick4_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void joystick4_set_rst_pin ( joystick4_t *ctx, uint8_t state );

/**
 * @brief Joystick 4 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #joystick4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t joystick4_get_int_pin ( joystick4_t *ctx );

/**
 * @brief Joystick 4 get pins function.
 * @details This function reads all input pins logic state.
 * @param[in] ctx : Click context object.
 * See #joystick4_t object definition for detailed explanation.
 * @param[out] pin_mask : Input pins read state mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t joystick4_get_pins ( joystick4_t *ctx, uint8_t *pin_mask );

/**
 * @brief Joystick 4 get position function.
 * @details This function returns the joystick position flag extracted from the input pins state mask.
 * @param[in] pin_mask : Input pins state mask.
 * @return Joystick position flag. Refer to the position values macro definitions.
 * @note None.
 */
uint8_t joystick4_get_position ( uint8_t pin_mask );

#ifdef __cplusplus
}
#endif
#endif // JOYSTICK4_H

/*! @} */ // joystick4

// ------------------------------------------------------------------------ END
