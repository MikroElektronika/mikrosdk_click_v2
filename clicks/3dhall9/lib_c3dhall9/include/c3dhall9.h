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
 * @file c3dhall9.h
 * @brief This file contains API for 3D Hall 9 Click Driver.
 */

#ifndef C3DHALL9_H
#define C3DHALL9_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup c3dhall9 3D Hall 9 Click Driver
 * @brief API for configuring and manipulating 3D Hall 9 Click driver.
 * @{
 */

/**
 * @defgroup c3dhall9_reg 3D Hall 9 Registers List
 * @brief List of registers of 3D Hall 9 Click driver.
 */

/**
 * @addtogroup c3dhall9_reg
 * @{
 */

/**
 * @brief 3D Hall 9 Register Map.
 * @details Specified register map of 3D Hall 9 Click driver.
 */
#define C3DHALL9_REG_EEPROM_02                  0x02
#define C3DHALL9_REG_EEPROM_03                  0x03
#define C3DHALL9_REG_EEPROM_0D                  0x0D
#define C3DHALL9_REG_EEPROM_0E                  0x0E
#define C3DHALL9_REG_EEPROM_0F                  0x0F
#define C3DHALL9_REG_VOLATILE_27                0x27
#define C3DHALL9_REG_VOLATILE_28                0x28
#define C3DHALL9_REG_VOLATILE_29                0x29

/*! @} */ // c3dhall9_reg

/**
 * @defgroup c3dhall9_set 3D Hall 9 Registers Settings
 * @brief Settings for registers of 3D Hall 9 Click driver.
 */

/**
 * @addtogroup c3dhall9_set
 * @{
 */

/**
 * @brief 3D Hall 9 register setting.
 * @details Specified setting for registers of 3D Hall 9 Click driver.
 */
#define C3DHALL9_EEPROM_02_ENABLE_Z             0x00000100ul
#define C3DHALL9_EEPROM_02_ENABLE_Y             0x00000080ul
#define C3DHALL9_EEPROM_02_ENABLE_X             0x00000040ul
#define C3DHALL9_VOLATILE_27_ACTIVE_MODE        0x00000000ul
#define C3DHALL9_VOLATILE_27_SLEEP_MODE         0x00000001ul
#define C3DHALL9_VOLATILE_27_LOW_POWER_MODE     0x00000002ul
#define C3DHALL9_VOLATILE_27_I2C_SINGLE         0x00000000ul
#define C3DHALL9_VOLATILE_27_I2C_FAST_LOOP      0x00000004ul
#define C3DHALL9_VOLATILE_27_I2C_FULL_LOOP      0x00000008ul

/**
 * @brief 3D Hall 9 measurements values.
 * @details Specified values for measurements of 3D Hall 9 Click driver.
 */
#define C3DHALL9_12BIT_RESOLUTION               0x1000
#define C3DHALL9_SIGN_BIT                       0x0800
#define C3DHALL9_DATA_READY_BIT                 0x0080
#define C3DHALL9_GAUSS_RESOLUTION               4
#define C3DHALL9_TEMPERATURE_MULTIPLIER         302
#define C3DHALL9_TEMPERATURE_SUBTRACTOR         1702
#define C3DHALL9_TEMPERATURE_SUBTRACTOR         1702
#define C3DHALL9_HALF_CICRLE_DEGREES            180.0

/**
 * @brief 3D Hall 9 device address setting.
 * @details Specified setting for device slave address selection of
 * 3D Hall 9 Click driver.
 */
#define C3DHALL9_SET_DEV_ADDR                   0x60

/*! @} */ // c3dhall9_set

/**
 * @defgroup c3dhall9_map 3D Hall 9 MikroBUS Map
 * @brief MikroBUS pin mapping of 3D Hall 9 Click driver.
 */

/**
 * @addtogroup c3dhall9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 3D Hall 9 Click to the selected MikroBUS.
 */
#define C3DHALL9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c3dhall9_map
/*! @} */ // c3dhall9

/**
 * @brief 3D Hall 9 Click context object.
 * @details Context object definition of 3D Hall 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en;              /**< Chip enable pin. */

    // Input pins
    digital_in_t  int_pin;          /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} c3dhall9_t;

/**
 * @brief 3D Hall 9 Click configuration object.
 * @details Configuration object definition of 3D Hall 9 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;                 /**< Chip enable pin. */
    pin_name_t  int_pin;            /**< Interrupt pin. */
    
    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} c3dhall9_cfg_t;

/**
 * @brief 3D Hall 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3DHALL9_OK = 0,
    C3DHALL9_ERROR = -1

} c3dhall9_return_value_t;

/**
 * @brief 3D Hall 9 Click data object.
 * @details Data object definition of 3D Hall 9 Click driver.
 */
typedef struct
{
    float x_axis;
    float y_axis;
    float z_axis;
    float angle_xy;
    float angle_xz;
    float angle_yz;
    float temperature;
    
} c3dhall9_data_t;

/*!
 * @addtogroup c3dhall9 3D Hall 9 Click Driver
 * @brief API for configuring and manipulating 3D Hall 9 Click driver.
 * @{
 */

/**
 * @brief 3D Hall 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c3dhall9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c3dhall9_cfg_setup ( c3dhall9_cfg_t *cfg );

/**
 * @brief 3D Hall 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c3dhall9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c3dhall9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall9_init ( c3dhall9_t *ctx, c3dhall9_cfg_t *cfg );

/**
 * @brief 3D Hall 9 default configuration function.
 * @details This function executes a default configuration of 3D Hall 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #c3dhall9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c3dhall9_default_cfg ( c3dhall9_t *ctx );

/**
 * @brief 3D Hall 9 I2C writing function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall9_write_register ( c3dhall9_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief 3D Hall 9 I2C reading function.
 * @details This function reads a desired data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall9_read_register ( c3dhall9_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief 3D Hall 9 enable chip function.
 * @details This function enables the chip by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #c3dhall9_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void c3dhall9_enable_chip ( c3dhall9_t *ctx );

/**
 * @brief 3D Hall 9 disable chip function.
 * @details This function disables the chip by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #c3dhall9_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void c3dhall9_disable_chip ( c3dhall9_t *ctx );

/**
 * @brief 3D Hall 9 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3dhall9_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3dhall9_get_int_pin ( c3dhall9_t *ctx );

/**
 * @brief 3D Hall 9 read data function.
 * @details This function reads new data which consists of X, Y, and Z axis values in Gauss, 
 * and temperature in Celsius. It also calculates the angles between all axes in Degrees 
 * based on the raw axes data read.
 * @param[in] ctx : Click context object.
 * See #c3dhall9_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * See #c3dhall9_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall9_read_data ( c3dhall9_t *ctx, c3dhall9_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // C3DHALL9_H

/*! @} */ // c3dhall9

// ------------------------------------------------------------------------ END
