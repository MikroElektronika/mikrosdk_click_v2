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
 * @file hbridge16.h
 * @brief This file contains API for H-Bridge 16 Click Driver.
 */

#ifndef HBRIDGE16_H
#define HBRIDGE16_H

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
 * @addtogroup hbridge16 H-Bridge 16 Click Driver
 * @brief API for configuring and manipulating H-Bridge 16 Click driver.
 * @{
 */

/**
 * @defgroup hbridge16_reg H-Bridge 16 Registers List
 * @brief List of registers of H-Bridge 16 Click driver.
 */

/**
 * @addtogroup hbridge16_reg
 * @{
 */

/**
 * @brief H-Bridge 16 description register.
 * @details Specified register for description of H-Bridge 16 Click driver.
 */
#define HBRIDGE16_REG_INPUT_PORT                    0x00
#define HBRIDGE16_REG_OUTPUT_PORT                   0x01
#define HBRIDGE16_REG_POLARITY_INV                  0x02
#define HBRIDGE16_REG_CONFIG                        0x03

/*! @} */ // hbridge16_reg

/**
 * @defgroup hbridge16_set H-Bridge 16 Registers Settings
 * @brief Settings for registers of H-Bridge 16 Click driver.
 */

/**
 * @addtogroup hbridge16_set
 * @{
 */

/**
 * @brief H-Bridge 16 pin mask.
 * @details Specified pin mask of H-Bridge 16 Click driver.
 */
#define HBRIDGE16_NONE_PIN                          0x00
#define HBRIDGE16_IN1_PIN                           0x01
#define HBRIDGE16_IN2_PIN                           0x02
#define HBRIDGE16_IN3_PIN                           0x04
#define HBRIDGE16_IN4_PIN                           0x08
#define HBRIDGE16_DECAY_PIN                         0x10
#define HBRIDGE16_MD_PIN                            0x20
#define HBRIDGE16_OCPM_PIN                          0x40
#define HBRIDGE16_FLT_PIN                           0x80
#define HBRIDGE16_ALL_OUTPUT_PIN                    0x7F
#define HBRIDGE16_ALL_PIN                           0xFF

/**
 * @brief H-Bridge 16 motor states setting.
 * @details Specified setting for motor states of H-Bridge 15 Click driver.
 */
#define HBRIDGE16_DRIVE_MOTOR_REVERSE               0x00
#define HBRIDGE16_DRIVE_MOTOR_FORWARD               0x01
#define HBRIDGE16_DRIVE_MOTOR_FREEWHEEL             0x02
#define HBRIDGE16_DRIVE_MOTOR_BRAKE                 0x03

/**
 * @brief H-Bridge 16 mode setting.
 * @details Specified setting for mode of H-Bridge 15 Click driver.
 */
#define HBRIDGE16_PWM_MODE                          0x01
#define HBRIDGE16_PH_EN_MODE                        0x00

/**
 * @brief H-Bridge 16 sleep mode setting.
 * @details Specified setting for sleep mode of H-Bridge 15 Click driver.
 */
#define HBRIDGE16_SLEEP_MODE_OFF                    0x01
#define HBRIDGE16_SLEEP_MODE_ON                     0x00

/**
 * @brief H-Bridge 16 device address setting.
 * @details Specified setting for device slave address selection of
 * H-Bridge 16 Click driver.
 */
#define HBRIDGE16_DEVICE_ADDRESS_A1A0_00            0x70
#define HBRIDGE16_DEVICE_ADDRESS_A1A0_01            0x71
#define HBRIDGE16_DEVICE_ADDRESS_A1A0_10            0x72
#define HBRIDGE16_DEVICE_ADDRESS_A1A0_11            0x73

/*! @} */ // hbridge16_set

/**
 * @defgroup hbridge16_map H-Bridge 16 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 16 Click driver.
 */

/**
 * @addtogroup hbridge16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 16 Click to the selected MikroBUS.
 */
#define HBRIDGE16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridge16_map
/*! @} */ // hbridge16

/**
 * @brief H-Bridge 16 Click context object.
 * @details Context object definition of H-Bridge 16 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin. */
    digital_out_t slp;              /**< Sleep pin. */

    // Input pins
    digital_in_t int_pin;           /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} hbridge16_t;

/**
 * @brief H-Bridge 16 Click configuration object.
 * @details Configuration object definition of H-Bridge 16 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;                 /**< Reset pin. */
    pin_name_t slp;                 /**< Sleep pin. */
    pin_name_t int_pin;             /**< Interrupt pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} hbridge16_cfg_t;

/**
 * @brief H-Bridge 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE16_OK = 0,
    HBRIDGE16_ERROR = -1

} hbridge16_return_value_t;

/*!
 * @addtogroup hbridge16 H-Bridge 16 Click Driver
 * @brief API for configuring and manipulating H-Bridge 16 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 16 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge16_cfg_setup ( hbridge16_cfg_t *cfg );

/**
 * @brief H-Bridge 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hbridge16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge16_init ( hbridge16_t *ctx, hbridge16_cfg_t *cfg );

/**
 * @brief H-Bridge 16 default configuration function.
 * @details This function executes a default configuration of H-Bridge 16
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridge16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge16_default_cfg ( hbridge16_t *ctx );

/**
 * @brief H-Bridge 16 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge16_generic_write ( hbridge16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief H-Bridge 16 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge16_generic_read ( hbridge16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );


/**
 * @brief H-Bridge 16 reset port expander function.
 * @details This function resets the port expander by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #hbridge16_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge16_reset_port_exp ( hbridge16_t *ctx );

/**
 * @brief H-Bridge 16 get Interrupt pin function.
 * @details This function is used to get Interrupt pin state.
 * @param[in] ctx : Click context object.
 * See #hbridge16_t object definition for detailed explanation.
 * @return @li @c 0 - Pin state low,
 *         @li @c 1 - Pin state high.
 * @note None.
 */
uint8_t hbridge16_get_int_pin ( hbridge16_t *ctx );

/**
 * @brief H-Bridge 15 set Sleep pin function.
 * @details This function is used to set state of the Sleep pin.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return None.
 * @note None.
 */
void hbridge16_set_slp_pin ( hbridge16_t *ctx, uint8_t pin_state );

/**
 * @brief H-Bridge 16 write register function.
 * @details This function writes a desired data byte to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge16_write_reg ( hbridge16_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief H-Bridge 16 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge16_read_reg ( hbridge16_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief H-Bridge 16 set pins function.
 * @details This function sets and clears the value of the selected pins of PCA9538A port expander.
 * @param[in] ctx : Click context object.
 * See #hbridge16_t object definition for detailed explanation.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge16_set_pins ( hbridge16_t *ctx, uint8_t set_mask, uint8_t clr_mask );

/**
 * @brief H-Bridge 16 set mode function.
 * @details This function sets interface mode.
 * @param[in] ctx : Click context object.
 * See #hbridge16_t object definition for detailed explanation.
 * @param[in] mode_sel : Mode selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge16_set_mode ( hbridge16_t *ctx, uint8_t mode_sel );

/**
 * @brief H-Bridge 16 set output function.
 * @details This function is used to set output state of the H-Bridge 16
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridge16_t object definition for detailed explanation.
 * @param[in] out_state : Output state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge16_set_out_state ( hbridge16_t *ctx, uint8_t out_state );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE16_H

/*! @} */ // hbridge16

// ------------------------------------------------------------------------ END
