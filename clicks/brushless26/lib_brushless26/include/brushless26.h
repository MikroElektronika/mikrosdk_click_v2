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
 * @file brushless26.h
 * @brief This file contains API for Brushless 26 Click Driver.
 */

#ifndef BRUSHLESS26_H
#define BRUSHLESS26_H

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
 * @addtogroup brushless26 Brushless 26 Click Driver
 * @brief API for configuring and manipulating Brushless 26 Click driver.
 * @{
 */

/**
 * @defgroup brushless26_reg Brushless 26 Registers List
 * @brief List of registers of Brushless 26 Click driver.
 */

/**
 * @addtogroup brushless26_reg
 * @{
 */

/**
 * @brief Brushless 26 description register.
 * @details Specified register for description of Brushless 26 Click driver.
 */
#define BRUSHLESS26_REG_INPUT_PORT                  0x00
#define BRUSHLESS26_REG_OUTPUT_PORT                 0x01
#define BRUSHLESS26_REG_POLARITY_INV                0x02
#define BRUSHLESS26_REG_CONFIG                      0x03

/*! @} */ // brushless26_reg

/**
 * @defgroup brushless26_set Brushless 26 Registers Settings
 * @brief Settings for registers of Brushless 26 Click driver.
 */

/**
 * @addtogroup brushless26_set
 * @{
 */

/**
 * @brief Brushless 26 description setting.
 * @details Specified setting for description of Brushless 26 Click driver.
 */
#define BRUSHLESS26_TR_COM_STATE_COAST              0x00
#define BRUSHLESS26_TR_COM_STATE_1                  0x01
#define BRUSHLESS26_TR_COM_STATE_2                  0x02
#define BRUSHLESS26_TR_COM_STATE_3                  0x03
#define BRUSHLESS26_TR_COM_STATE_4                  0x04
#define BRUSHLESS26_TR_COM_STATE_5                  0x05
#define BRUSHLESS26_TR_COM_STATE_6                  0x06
#define BRUSHLESS26_TR_COM_STATE_BRAKE              0x07

/**
 * @brief Brushless 26 pin mask.
 * @details Specified pin mask of Brushless 26 Click driver.
 */
#define BRUSHLESS26_NONE_PIN                        0x00
#define BRUSHLESS26_INLC_PIN                        0x01
#define BRUSHLESS26_INHC_PIN                        0x02
#define BRUSHLESS26_INLB_PIN                        0x04
#define BRUSHLESS26_INHB_PIN                        0x08
#define BRUSHLESS26_INLA_PIN                        0x10
#define BRUSHLESS26_INHA_PIN                        0x20
#define BRUSHLESS26_SLP_PIN                         0x40
#define BRUSHLESS26_ALL_OUTPUT_PIN                  0x3F
#define BRUSHLESS26_ALL_PIN                         0x7F

/**
 * @brief Brushless 26 PWM mode setting.
 * @details Specified setting for PWM mode of Brushless 26 Click driver.
 */
#define BRUSHLESS26_MODE_6X_PWM                     0x01
#define BRUSHLESS26_MODE_3X_PWM                     0x00

/**
 * @brief Brushless 26 direction setting.
 * @details Specified setting for direction of Brushless 26 Click driver.
 */
#define BRUSHLESS26_DIR_CW                          0x01
#define BRUSHLESS26_DIR_CCW                         0x00

/**
 * @brief Brushless 26 pin logic level setting.
 * @details Specified setting for pin logic level of Brushless 26 Click driver.
 */
#define BRUSHLESS26_PIN_STATE_LOW                   0x00
#define BRUSHLESS26_PIN_STATE_HIGH                  0x01

/**
 * @brief Brushless 26 driving speed and time settings.
 * @details Specified driving speed and time settings of Brushless 26 Click driver.
 */
#define BRUSHLESS26_SPEED_MIN                       0
#define BRUSHLESS26_SPEED_MAX                       100
#define BRUSHLESS26_NUM_PIN_TOGGLE                  8
#define BRUSHLESS26_ROUND_TO_NEAREAST_INT           0.5

/**
 * @brief Brushless 26 commutation sequance duration settings.
 * @details Specified commutation sequance duration settings of Brushless 26 Click driver.
 * @note In order to improve driving time accuracy, measure and adjust the following macros for your setup.
 * Call brushless26_perform_com_seq for MAX and MAX-1 speed and measure the duration of each execution.
 * @b BRUSHLESS26_COM_SEQ_DURATION_FOR_SPEED_MAX = duration for a single commutation sequance in milliseconds for MAX speed.
 * @b BRUSHLESS26_COM_SEQ_DURATION_SPEED_STEP = duration for a single commutation sequance in milliseconds for MAX-1 speed - 
 *                                              @b BRUSHLESS26_COM_SEQ_DURATION_FOR_SPEED_MAX.
 */
#define BRUSHLESS26_COM_SEQ_DURATION_FOR_SPEED_MAX  20.293
#define BRUSHLESS26_COM_SEQ_DURATION_SPEED_STEP     ( 20.351 - BRUSHLESS26_COM_SEQ_DURATION_FOR_SPEED_MAX )

/**
 * @brief Brushless 26 device address setting.
 * @details Specified setting for device slave address selection of
 * Brushless 26 Click driver.
 */
#define BRUSHLESS26_DEVICE_ADDRESS_A1A0_00          0x70
#define BRUSHLESS26_DEVICE_ADDRESS_A1A0_01          0x71
#define BRUSHLESS26_DEVICE_ADDRESS_A1A0_10          0x72
#define BRUSHLESS26_DEVICE_ADDRESS_A1A0_11          0x73

/*! @} */ // brushless26_set

/**
 * @defgroup brushless26_map Brushless 26 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 26 Click driver.
 */

/**
 * @addtogroup brushless26_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 26 Click to the selected MikroBUS.
 */
#define BRUSHLESS26_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // brushless26_map
/*! @} */ // brushless26

/**
 * @brief Brushless 26 Click context object.
 * @details Context object definition of Brushless 26 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */

    // Input pins
    digital_in_t flt;           /**< Fault pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    uint8_t mode;               /**< PWM mode. */

} brushless26_t;

/**
 * @brief Brushless 26 Click configuration object.
 * @details Configuration object definition of Brushless 26 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin. */
    pin_name_t flt;             /**< Fault pin. */
    
    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} brushless26_cfg_t;

/**
 * @brief Brushless 26 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS26_OK = 0,
    BRUSHLESS26_ERROR = -1

} brushless26_return_value_t;

/*!
 * @addtogroup brushless26 Brushless 26 Click Driver
 * @brief API for configuring and manipulating Brushless 26 Click driver.
 * @{
 */

/**
 * @brief Brushless 26 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless26_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless26_cfg_setup ( brushless26_cfg_t *cfg );

/**
 * @brief Brushless 26 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless26_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless26_init ( brushless26_t *ctx, brushless26_cfg_t *cfg );

/**
 * @brief Brushless 26 default configuration function.
 * @details This function executes a default configuration of Brushless 26
 * click board.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless26_default_cfg ( brushless26_t *ctx );

/**
 * @brief Brushless 26 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless26_generic_write ( brushless26_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Brushless 26 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless26_generic_read ( brushless26_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Brushless 26 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @param[in] state : State of the RST pin.
 * @return None.
 * @note None.
 */
void brushless26_set_rst_pin ( brushless26_t *ctx, uint8_t pin_state );

/**
 * @brief Brushless 26 reset port expander function.
 * @details This function resets the port expander by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless26_reset_port_exp ( brushless26_t *ctx );

/**
 * @brief Brushless 26 get fault pin function.
 * @details This function returns the fault pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @return State of the FLT pin.
 * @note None.
 */
uint8_t brushless26_get_flt_pin ( brushless26_t *ctx );

/**
 * @brief Brushless 26 write register function.
 * @details This function writes a desired data byte to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless26_write_reg ( brushless26_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Brushless 26 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless26_read_reg ( brushless26_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Brushless 26 set pins function.
 * @details This function sets and clears the value of the selected pins of PCA9538A port expander.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless26_set_pins ( brushless26_t *ctx, uint8_t set_mask, uint8_t clr_mask );

/**
 * @brief Brushless 26 set trapezoidal com state function.
 * @details This function sets the pin state for the selected trapezoidal commutation state.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @param[in] state : Trapezoidal commutation state (0-7) - BRUSHLESS26_TR_COM_STATE_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless26_set_trap_com_state ( brushless26_t *ctx, uint8_t state );

/**
 * @brief Brushless 26 toggle pin function.
 * @details This function toggles the selected pin of port expander @b BRUSHLESS26_NUM_PIN_TOGGLE times
 * with a delay of (@b speed + 1) * 100us between each toggle.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @param[in] pin_mask : Pin to toggle mask.
 * @param[in] speed : Speed (0-100).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless26_toggle_pin ( brushless26_t *ctx, uint8_t pin_mask, uint8_t speed );

/**
 * @brief Brushless 26 perform com sequence function.
 * @details This function performs a single commutation sequence for the selected rotation direction at
 * a desired speed.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @param[in] dir : Rotation direction.
 * @param[in] speed : Speed (0-100).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless26_perform_com_seq ( brushless26_t *ctx, uint8_t dir, uint8_t speed );

/**
 * @brief Brushless 26 drive motor function.
 * @details This function drives the motor for a desired time by performing multiple commutation sequences 
 * for the selected rotation direction at a desired speed.
 * @param[in] ctx : Click context object.
 * See #brushless26_t object definition for detailed explanation.
 * @param[in] dir : Rotation direction.
 * @param[in] speed : Speed (0-100).
 * @param[in] time_ms : Driving time in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t brushless26_drive_motor ( brushless26_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS26_H

/*! @} */ // brushless26

// ------------------------------------------------------------------------ END
