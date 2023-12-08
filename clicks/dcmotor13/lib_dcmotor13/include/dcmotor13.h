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
 * @file dcmotor13.h
 * @brief This file contains API for DC Motor 13 Click Driver.
 */

#ifndef DCMOTOR13_H
#define DCMOTOR13_H

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
 * @addtogroup dcmotor13 DC Motor 13 Click Driver
 * @brief API for configuring and manipulating DC Motor 13 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor13_reg DC Motor 13 Registers List
 * @brief List of registers of DC Motor 13 Click driver.
 */

/**
 * @addtogroup dcmotor13_reg
 * @{
 */

/**
 * @brief DC Motor 13 PCA9538A registers.
 * @details Specified PCA9538A registers of DC Motor 13 Click driver.
 */
#define DCMOTOR13_REG_INPUT                 0x00
#define DCMOTOR13_REG_OUTPUT                0x01
#define DCMOTOR13_REG_POLARITY              0x02
#define DCMOTOR13_REG_CONFIG                0x03

/*! @} */ // dcmotor13_reg

/**
 * @defgroup dcmotor13_set DC Motor 13 Registers Settings
 * @brief Settings for registers of DC Motor 13 Click driver.
 */

/**
 * @addtogroup dcmotor13_set
 * @{
 */

/**
 * @brief DC Motor 13 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of DC Motor 13 Click driver.
 */
#define DCMOTOR13_LO_PIN                    0x01
#define DCMOTOR13_AI2_PIN                   0x02
#define DCMOTOR13_BI2_PIN                   0x04
#define DCMOTOR13_TA1_PIN                   0x08
#define DCMOTOR13_TA2_PIN                   0x10
#define DCMOTOR13_TB1_PIN                   0x20
#define DCMOTOR13_TB2_PIN                   0x40

/**
 * @brief DC Motor 13 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of DC Motor 13 Click driver.
 */
#define DCMOTOR13_DEFAULT_CONFIG            0x81

/**
 * @brief DC Motor 13 pin logic level setting.
 * @details Specified setting for pin logic level of DC Motor 13 Click driver.
 */
#define DCMOTOR13_PIN_LOW_LEVEL             0
#define DCMOTOR13_PIN_HIGH_LEVEL            1

/**
 * @brief DC Motor 13 output mode setting.
 * @details Specified setting for output mode of DC Motor 13 Click driver.
 */
#define DCMOTOR13_MODE_SHORT_BRAKE          0x00
#define DCMOTOR13_MODE_CCW                  0x01
#define DCMOTOR13_MODE_CW                   0x02

/**
 * @brief DC Motor 13 output torque setting.
 * @details Specified setting for output torque of DC Motor 13 Click driver.
 */
#define DCMOTOR13_TORQUE_0                  0x00
#define DCMOTOR13_TORQUE_38                 0x01
#define DCMOTOR13_TORQUE_71                 0x02
#define DCMOTOR13_TORQUE_100                0x03

/**
 * @brief DC Motor 13 device address setting.
 * @details Specified setting for device slave address selection of
 * DC Motor 13 Click driver.
 */
#define DCMOTOR13_DEVICE_ADDRESS_A1A0_00    0x70
#define DCMOTOR13_DEVICE_ADDRESS_A1A0_01    0x71
#define DCMOTOR13_DEVICE_ADDRESS_A1A0_10    0x72
#define DCMOTOR13_DEVICE_ADDRESS_A1A0_11    0x73

/*! @} */ // dcmotor13_set

/**
 * @defgroup dcmotor13_map DC Motor 13 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 13 Click driver.
 */

/**
 * @addtogroup dcmotor13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 13 Click to the selected MikroBUS.
 */
#define DCMOTOR13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ai1 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.bi1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dcmotor13_map
/*! @} */ // dcmotor13

/**
 * @brief DC Motor 13 Click context object.
 * @details Context object definition of DC Motor 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ai1;              /**< Motor Ach IN1 pin. */
    digital_out_t slp;              /**< Sleep pin. */
    digital_out_t rst;              /**< Reset pin. */
    digital_out_t bi1;              /**< Motor Bch IN1 pin. */

    // Input pins
    digital_in_t  int_pin;          /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} dcmotor13_t;

/**
 * @brief DC Motor 13 Click configuration object.
 * @details Configuration object definition of DC Motor 13 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  ai1;                /**< Motor Ach IN1 pin. */
    pin_name_t  slp;                /**< Sleep pin. */
    pin_name_t  rst;                /**< Reset pin. */
    pin_name_t  bi1;                /**< Motor Bch IN1 pin. */
    pin_name_t  int_pin;            /**< Interrupt pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} dcmotor13_cfg_t;

/**
 * @brief DC Motor 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR13_OK = 0,
    DCMOTOR13_ERROR = -1

} dcmotor13_return_value_t;

/*!
 * @addtogroup dcmotor13 DC Motor 13 Click Driver
 * @brief API for configuring and manipulating DC Motor 13 Click driver.
 * @{
 */

/**
 * @brief DC Motor 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor13_cfg_setup ( dcmotor13_cfg_t *cfg );

/**
 * @brief DC Motor 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor13_init ( dcmotor13_t *ctx, dcmotor13_cfg_t *cfg );

/**
 * @brief DC Motor 13 default configuration function.
 * @details This function executes a default configuration of DC Motor 13
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor13_default_cfg ( dcmotor13_t *ctx );

/**
 * @brief DC Motor 13 write register function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor13_write_register ( dcmotor13_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief DC Motor 13 read register function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor13_read_register ( dcmotor13_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief DC Motor 13 enable device function.
 * @details This function enables the device by setting the SLP pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor13_enable_device ( dcmotor13_t *ctx );

/**
 * @brief DC Motor 13 disable device function.
 * @details This function disables the device by setting the SLP pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor13_disable_device ( dcmotor13_t *ctx );

/**
 * @brief DC Motor 13 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dcmotor13_reset_device ( dcmotor13_t *ctx );

/**
 * @brief DC Motor 13 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t dcmotor13_get_int_pin ( dcmotor13_t *ctx );

/**
 * @brief DC Motor 13 set AI1 pin function.
 * @details This function sets the AI1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void dcmotor13_set_ai1_pin ( dcmotor13_t *ctx, uint8_t state );

/**
 * @brief DC Motor 13 set BI1 pin function.
 * @details This function sets the BI1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void dcmotor13_set_bi1_pin ( dcmotor13_t *ctx, uint8_t state );

/**
 * @brief DC Motor 13 get LO pin function.
 * @details This function reads the LO pin logic state.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @param[out] pin_state : LO pin logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor13_get_lo_pin ( dcmotor13_t *ctx, uint8_t *pin_state );

/**
 * @brief DC Motor 13 set OUTA mode function.
 * @details This function sets the OUTA mode.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - Short brake,
 *                   @li @c 1 - Counter-Clockwise,
 *                   @li @c 2 - Clockwise.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor13_set_outa_mode ( dcmotor13_t *ctx, uint8_t mode );

/**
 * @brief DC Motor 13 set OUTB mode function.
 * @details This function sets the OUTB mode.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - Short brake,
 *                   @li @c 1 - Counter-Clockwise,
 *                   @li @c 2 - Clockwise.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor13_set_outb_mode ( dcmotor13_t *ctx, uint8_t mode );

/**
 * @brief DC Motor 13 set OUTA torque function.
 * @details This function sets the OUTA torque.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @param[in] torque : @li @c 0 - Torque: 0% (Output OFF),
 *                     @li @c 1 - Torque: 38%,
 *                     @li @c 2 - Torque: 71%,
 *                     @li @c 3 - Torque: 100%.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor13_set_outa_torque ( dcmotor13_t *ctx, uint8_t torque );

/**
 * @brief DC Motor 13 set OUTB torque function.
 * @details This function sets the OUTB torque.
 * @param[in] ctx : Click context object.
 * See #dcmotor13_t object definition for detailed explanation.
 * @param[in] torque : @li @c 0 - Torque: 0% (Output OFF),
 *                     @li @c 1 - Torque: 38%,
 *                     @li @c 2 - Torque: 71%,
 *                     @li @c 3 - Torque: 100%.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor13_set_outb_torque ( dcmotor13_t *ctx, uint8_t torque );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR13_H

/*! @} */ // dcmotor13

// ------------------------------------------------------------------------ END
