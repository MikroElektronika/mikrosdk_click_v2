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
 * @file stepper17.h
 * @brief This file contains API for Stepper 17 Click Driver.
 */

#ifndef STEPPER17_H
#define STEPPER17_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_pwm.h"

/*!
 * @addtogroup stepper17 Stepper 17 Click Driver
 * @brief API for configuring and manipulating Stepper 17 Click driver.
 * @{
 */

/**
 * @defgroup stepper17_reg Stepper 17 Registers List
 * @brief List of registers of Stepper 17 Click driver.
 */

/**
 * @addtogroup stepper17_reg
 * @{
 */

/**
 * @brief Stepper 17 description register.
 * @details Specified register for description of Stepper 17 Click driver.
 */
#define STEPPER17_REG_INPUT_PORT0               0x00
#define STEPPER17_REG_INPUT_PORT1               0x01
#define STEPPER17_REG_OUTPUT_PORT0              0x02
#define STEPPER17_REG_OUTPUT_PORT1              0x03
#define STEPPER17_REG_POLARITY_INVERSION_PORT0  0x04
#define STEPPER17_REG_POLARITY_INVERSION_PORT1  0x05
#define STEPPER17_REG_CONFIGUARTION_PORT0       0x06
#define STEPPER17_REG_CONFIGUARTION_PORT1       0x07

/*! @} */ // stepper17_reg

/**
 * @defgroup stepper17_set Stepper 17 Registers Settings
 * @brief Settings for registers of Stepper 17 Click driver.
 */

/**
 * @addtogroup stepper17_set
 * @{
 */

/**
 * @brief Stepper 17 mode settings.
 * @details Specified settings for mode of Stepper 17 Click driver.
 */
#define STEPPER17_MODE_SLEEP                    0x00
#define STEPPER17_MODE_NORMAL                   0x80

/**
 * @brief Stepper 17 step resolution settings.
 * @details Specified settings for step resolution of Stepper 17 Click driver.
 */
#define STEPPER17_STEP_FULL                     0x00
#define STEPPER17_STEP_HALF_A                   0x04
#define STEPPER17_STEP_HALF_B                   0x02
#define STEPPER17_STEP_QUARTER                  0x06
#define STEPPER17_STEP_1DIV8                    0x01
#define STEPPER17_STEP_1DIV16                   0x05
#define STEPPER17_STEP_1DIV32                   0x07

/**
 * @brief Stepper 17 decay settings.
 * @details Specified settings for decay of Stepper 17 Click driver.
 */
#define STEPPER17_DECAY_MIXED                   0x00
#define STEPPER17_DECAY_SLOW                    0x08
#define STEPPER17_DECAY_FAST                    0x10
#define STEPPER17_DECAY_ADMD                    0x18

/**
 * @brief Stepper 17 torque settings.
 * @details Specified settings for torque of Stepper 17 Click driver.
 */
#define STEPPER17_TORQUE_100PCT                 0x00
#define STEPPER17_TORQUE_75PCT                  0x20  
#define STEPPER17_TORQUE_50PCT                  0x40
#define STEPPER17_TORQUE_25PCT                  0x60

/**
 * @brief Stepper 17 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 17 Click driver.
 */
#define STEPPER17_SET_DEV_ADDR                  0x20


/**
 * @brief Stepper 17 default frequency value.
 * @details Specified setting for frequency value of Stepper 17 Click driver.
 */
#define STEPPER17_DEF_FREQ                      1500

/*! @} */ // stepper17_set

/**
 * @defgroup stepper17_map Stepper 17 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 17 Click driver.
 */

/**
 * @addtogroup stepper17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 17 Click to the selected MikroBUS.
 */
#define STEPPER17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper17_map
/*! @} */ // stepper17

/**
 * @brief Stepper 17 Click context object.
 * @details Context object definition of Stepper 17 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  en;       /**< Description. */
    digital_out_t  dir;       /**< Description. */
    digital_out_t  rst;     /**< Description. */

    // Input pins

    digital_in_t  int_pin;       /**< Description. */

    // Modules

    i2c_master_t i2c;                                /**< I2C driver object. */
    pwm_t pwm;

    // I2C slave address

    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */
    uint32_t  pwm_freq;

} stepper17_t;

/**
 * @brief Stepper 17 Click configuration object.
 * @details Configuration object definition of Stepper 17 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;             /**< Description. */
    pin_name_t  dir;            /**< Description. */
    pin_name_t  rst;            /**< Description. */
    pin_name_t  clk;            /**< Description. */
    pin_name_t  int_pin;        /**< Description. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */
    uint32_t  dev_pwm_freq;

} stepper17_cfg_t;

/**
 * @brief Stepper 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   STEPPER17_OK     = 0,
   STEPPER17_ERROR  = -1

} stepper17_return_value_t;

/*!
 * @addtogroup stepper17 Stepper 17 Click Driver
 * @brief API for configuring and manipulating Stepper 17 Click driver.
 * @{
 */

/**
 * @brief Stepper 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void stepper17_cfg_setup ( stepper17_cfg_t *cfg );

/**
 * @brief Stepper 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t stepper17_init ( stepper17_t *ctx, stepper17_cfg_t *cfg );

/**
 * @brief Stepper 17 default configuration function.
 * @details This function executes a default configuration of Stepper 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t stepper17_default_cfg ( stepper17_t *ctx );

/**
 * @brief Stepper 17 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t stepper17_generic_write ( stepper17_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Stepper 17 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t stepper17_generic_read ( stepper17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Stepper 17 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t stepper17_set_duty_cycle ( stepper17_t *ctx, float duty_cycle );

/**
 * @brief Stepper 17 stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t stepper17_pwm_stop ( stepper17_t *ctx );

/**
 * @brief Stepper 17 start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t stepper17_pwm_start ( stepper17_t *ctx );

/**
 * @brief Direction control.
 * @details This function sets pin that controls direction of motor rotating.
 * @param[out] ctx : Click context object.
 * @param[in] state : Logic pin state.
 * See #stepper17_t object definition for detailed explanation.
 * @return Nothing.
 */
void stepper17_set_dir_state ( stepper17_t *ctx, uint8_t state );

/**
 * @brief Set reset pin state.
 * @details This function sets pin that resets electrical angle to inital state.
 * @param[out] ctx : Click context object.
 * @param[in] state : Logic pin state.
 * See #stepper17_t object definition for detailed explanation.
 * @return Nothing.
 */
void stepper17_set_rst_state ( stepper17_t *ctx, uint8_t state );

/**
 * @brief Enable stepping motor output.
 * @details This function sets pin that contols stepping motor output.
 * @param[out] ctx : Click context object.
 * @param[in] state : Logic pin state.
 * See #stepper17_t object definition for detailed explanation.
 * @return Nothing.
 */
void stepper17_set_en_state ( stepper17_t *ctx, uint8_t state );

/**
 * @brief Gets interrupt state.
 * @details This function gets interrupt pin state. Interrupt state 
 * goes low whenever input pins change from port 1( MO, LO1, LO2 ).
 * @param[out] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @return @li @c  0 - Interrupt,
 *         @li @c  1 - Idle.
 */
uint8_t stepper17_get_int_state ( stepper17_t *ctx );

/**
 * @brief Step resolution setting.
 * @details This function sets step resolution.
 * @param[out] ctx : Click context object.
 * @param[in] resolution : Step resolution data.
 * See #stepper17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t stepper17_step_resolution ( stepper17_t *ctx, uint8_t resolution );

/**
 * @brief Torque setting.
 * @details This function sets torque.
 * @param[out] ctx : Click context object.
 * @param[in] torque : Torque data.
 * See #stepper17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t stepper17_torque_setting ( stepper17_t *ctx, uint8_t torque );

/**
 * @brief Decay period setting.
 * @details This function sets decay period.
 * @param[out] ctx : Click context object.
 * @param[in] decay : Torque data.
 * See #stepper17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t stepper17_decay_function ( stepper17_t *ctx, uint8_t decay );

/**
 * @brief Mode setting.
 * @details This function sets mode.
 * @param[out] ctx : Click context object.
 * @param[in] mode : Mode data.
 * See #stepper17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t stepper17_mode ( stepper17_t *ctx, uint8_t mode );

/**
 * @brief Reads error output.
 * @details This function gets error output.
 * @param[out] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @return @li @c  3 - No Error,
 *         @li @c  2 - Over-current Error,
 *         @li @c  1 - Over-temperature Error,
 *         @li @c  0 - Over-current and over-temperature Error.
 */
uint8_t stepper17_get_error ( stepper17_t *ctx );

/**
 * @brief Reads MO pin state.
 * @details This function reads internal electrical angles 
 *          that MO pin indicates.
 * @param[out] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @return @li @c  4 - Except inital value,
 *         @li @c  0 - Initial value.
 */
uint8_t stepper17_get_electrical_angle( stepper17_t *ctx );

/**
 * @brief Reset electrical angle to initial state.
 * @details This function toggles rst pin state to reset 
 *          electrical angle to initial state.
 * @param[out] ctx : Click context object.
 * @param[in] state : Logic pin state.
 * See #stepper17_t object definition for detailed explanation.
 * @return Nothing.
 */
void stepper17_reset_electrical_angle ( stepper17_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // STEPPER17_H

/*! @} */ // stepper17

// ------------------------------------------------------------------------ END
