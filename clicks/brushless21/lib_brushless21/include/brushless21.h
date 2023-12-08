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
 * @file brushless21.h
 * @brief This file contains API for Brushless 21 Click Driver.
 */

#ifndef BRUSHLESS21_H
#define BRUSHLESS21_H

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
#include "drv_pwm.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup brushless21 Brushless 21 Click Driver
 * @brief API for configuring and manipulating Brushless 21 Click driver.
 * @{
 */

/**
 * @defgroup brushless21_reg Brushless 21 Registers List
 * @brief List of registers of Brushless 21 Click driver.
 */

/**
 * @addtogroup brushless21_reg
 * @{
 */

/**
 * @brief Brushless 21 EEPROM Map.
 * @details Specified EEPROM Map of Brushless 21 Click driver.
 */
#define BRUSHLESS21_EEPROM_USER_0                       0x06
#define BRUSHLESS21_EEPROM_USER_1                       0x07
#define BRUSHLESS21_EEPROM_RATED_SPEED_DIR              0x08
#define BRUSHLESS21_EEPROM_ACCELERATION_AND_RES         0x09
#define BRUSHLESS21_EEPROM_CURRENT                      0x0A
#define BRUSHLESS21_EEPROM_MODE                         0x0B
#define BRUSHLESS21_EEPROM_PID_P_AND_INDUCTANCE         0x0C
#define BRUSHLESS21_EEPROM_PID_I_AND_DELAY              0x0D
#define BRUSHLESS21_EEPROM_LOCK_AND_SOFT_CTRL           0x0F
#define BRUSHLESS21_EEPROM_OCP_FCSPEED_ACDEC_BUF_FLT    0x10
#define BRUSHLESS21_EEPROM_SPEED_AND_FG                 0x11
#define BRUSHLESS21_EEPROM_IPD_CURRENT_THR              0x12
#define BRUSHLESS21_EEPROM_RATED_VOLTAGE                0x14
#define BRUSHLESS21_EEPROM_SLIGHT_MOVE_LOW_DUTY_THR     0x15
#define BRUSHLESS21_EEPROM_CLOSED_LOOP_TIME             0x16
#define BRUSHLESS21_EEPROM_CONTROL                      0xA1
#define BRUSHLESS21_EEPROM_ADDRESS                      0xA2
#define BRUSHLESS21_EEPROM_DATA_IN                      0xA3

/**
 * @brief Brushless 21 Register Map.
 * @details Specified Register Map of Brushless 21 Click driver.
 */
#define BRUSHLESS21_REG_RATED_SPEED_DIR                 0x48
#define BRUSHLESS21_REG_ACCELERATION_AND_RES            0x49
#define BRUSHLESS21_REG_CURRENT                         0x4A
#define BRUSHLESS21_REG_MODE                            0x4B
#define BRUSHLESS21_REG_PID_P_AND_INDUCTANCE            0x4C
#define BRUSHLESS21_REG_PID_I_AND_DELAY                 0x4D
#define BRUSHLESS21_REG_LOCK_AND_SOFT_CTRL              0x4F
#define BRUSHLESS21_REG_OCP_FCSPEED_ACDEC_BUF_FLT       0x50
#define BRUSHLESS21_REG_SPEED_AND_FG                    0x51
#define BRUSHLESS21_REG_IPD_CURRENT_THR                 0x52
#define BRUSHLESS21_REG_RATED_VOLTAGE                   0x54
#define BRUSHLESS21_REG_SLIGHT_MOVE_LOW_DUTY_THR        0x55
#define BRUSHLESS21_REG_CLOSED_LOOP_TIME                0x56
#define BRUSHLESS21_REG_READBACK_MOTOR_SPEED            0x78
#define BRUSHLESS21_REG_READBACK_BUS_CURRENT            0x79
#define BRUSHLESS21_REG_READBACK_Q_AXIS_CURRENT         0x7A
#define BRUSHLESS21_REG_READBACK_VBB                    0x7B
#define BRUSHLESS21_REG_READBACK_TEMPERATURE            0x7C
#define BRUSHLESS21_REG_READBACK_CONTROL_DEMAND         0x7D
#define BRUSHLESS21_REG_READBACK_CONTROL_COMMAND        0x7E

/*! @} */ // brushless21_reg


/**
 * @defgroup brushless21_set Brushless 21 Settings
 * @brief Settings for configuration of Brushless 21 Click driver.
 */

/**
 * @addtogroup brushless21_set
 * @{
 */

/**
 * @brief Brushless 21 direction setting.
 * @details Specified setting for direction of Brushless 21 Click driver.
 */
#define BRUSHLESS21_DIR_REVERSE                         0
#define BRUSHLESS21_DIR_FORWARD                         1

/**
 * @brief Brushless 21 calculation values.
 * @details Specified calculation values of Brushless 21 Click driver.
 */
#define BRUSHLESS21_MOTOR_SPEED_HZ                      0.530
#define BRUSHLESS21_VBB_MAX                             20
#define BRUSHLESS21_VBB_RESOLUTION                      0xFF
#define BRUSHLESS21_TEMPERATURE_OFFSET                  73
#define BRUSHLESS21_I2C_DUTY_RESOLUTION                 0x01FF
#define BRUSHLESS21_DUTY_CONTROLLED_BY_I2C_BIT          0x0200

/**
 * @brief Brushless 21 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Brushless 21 Click driver.
 */
#define BRUSHLESS21_DEF_FREQ                            5000

/**
 * @brief Brushless 21 device address setting.
 * @details Specified setting for device slave address selection of
 * Brushless 21 Click driver.
 */
#define BRUSHLESS21_SET_DEV_ADDR                        0x55

/*! @} */ // brushless21_cfg

/**
 * @defgroup brushless21_map Brushless 21 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 21 Click driver.
 */

/**
 * @addtogroup brushless21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 21 Click to the selected MikroBUS.
 */
#define BRUSHLESS21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.fg = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // brushless21_map
/*! @} */ // brushless21

/**
 * @brief Brushless 21 Click driver selector.
 * @details Selects target driver interface of Brushless 21 Click driver.
 */
typedef enum
{
    BRUSHLESS21_DRV_SEL_GPIO,      /**< GPIO driver descriptor. */
    BRUSHLESS21_DRV_SEL_I2C        /**< I2C driver descriptor. */

} brushless21_drv_t;

/**
 * @brief Brushless 21 Click context object.
 * @details Context object definition of Brushless 21 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;       /**< Enable chip pin. */

    // Input pins
    digital_in_t fg;        /**< FG pin provides motor speed information. */

    // Modules
    pwm_t pwm;              /**< PWM driver object. */
    i2c_master_t i2c;       /**< I2C driver object. */

    uint32_t pwm_freq;      /**< PWM frequency value. */
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */
    
    brushless21_drv_t drv_sel;  /**< Master driver interface selector. */

} brushless21_t;

/**
 * @brief Brushless 21 Click configuration object.
 * @details Configuration object definition of Brushless 21 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;         /**< PWM pin. */
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */

    // Additional gpio pins
    pin_name_t en;          /**< Enable chip pin. */
    pin_name_t fg;          /**< FG pin provides motor speed information. */

    // Static variable
    uint32_t dev_pwm_freq;  /**< PWM frequency value. */
    uint32_t i2c_speed;     /**< I2C serial speed. */
    uint8_t  i2c_address;   /**< I2C slave address. */
    
    brushless21_drv_t drv_sel;  /**< Master driver interface selector. */

} brushless21_cfg_t;

/**
 * @brief Brushless 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS21_OK = 0,
    BRUSHLESS21_ERROR = -1

} brushless21_return_value_t;

/*!
 * @addtogroup brushless21 Brushless 21 Click Driver
 * @brief API for configuring and manipulating Brushless 21 Click driver.
 * @{
 */

/**
 * @brief Brushless 21 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless21_cfg_setup ( brushless21_cfg_t *cfg );

/**
 * @brief Brushless 21 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #brushless21_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #brushless21_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void brushless21_drv_interface_selection ( brushless21_cfg_t *cfg, brushless21_drv_t drv_sel );

/**
 * @brief Brushless 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless21_init ( brushless21_t *ctx, brushless21_cfg_t *cfg );

/**
 * @brief Brushless 21 default configuration function.
 * @details This function executes a default configuration of Brushless 21
 * click board.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless21_default_cfg ( brushless21_t *ctx );

/**
 * @brief Brushless 21 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can only be used when the click is configured in GPIO mode.
 */
err_t brushless21_pwm_stop ( brushless21_t *ctx );

/**
 * @brief Brushless 21 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can only be used when the click is configured in GPIO mode.
 */
err_t brushless21_pwm_start ( brushless21_t *ctx );

/**
 * @brief Brushless 21 set duty cycle function.
 * @details This function sets the duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless21_set_duty_cycle ( brushless21_t *ctx, float duty_cycle );

/**
 * @brief Brushless 21 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written (16-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can only be used when the click is configured in I2C mode.
 */
err_t brushless21_write_register ( brushless21_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Brushless 21 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data (16-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can only be used when the click is configured in I2C mode.
 */
err_t brushless21_read_register ( brushless21_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Brushless 21 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless21_enable_device ( brushless21_t *ctx );

/**
 * @brief Brushless 21 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless21_disable_device ( brushless21_t *ctx );

/**
 * @brief Brushless 21 get fg pin function.
 * @details This function returns the FG pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note This function can only be used when the click is configured in GPIO mode.
 */
uint8_t brushless21_get_fg_pin ( brushless21_t *ctx );

/**
 * @brief Brushless 21 get temperature function.
 * @details This function reads the chip internal temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can only be used when the click is configured in I2C mode.
 */
err_t brushless21_get_temperature ( brushless21_t *ctx, int8_t *temperature );

/**
 * @brief Brushless 21 get motor speed function.
 * @details This function reads the motor speed in Hz.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @param[out] motor_speed_hz : Motor speed in Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can only be used when the click is configured in I2C mode.
 */
err_t brushless21_get_motor_speed ( brushless21_t *ctx, float *motor_speed_hz );

/**
 * @brief Brushless 21 get vbb voltage function.
 * @details This function reads the VBB voltage.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @param[out] vbb_voltage : VBB voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can only be used when the click is configured in I2C mode.
 */
err_t brushless21_get_vbb_voltage ( brushless21_t *ctx, float *vbb_voltage );

/**
 * @brief Brushless 21 set direction function.
 * @details This function sets the motor direction.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @param[in] direction : @li @c 0 - Reverse,
 *                        @li @c 1 - Forward.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can only be used when the click is configured in I2C mode.
 */
err_t brushless21_set_direction ( brushless21_t *ctx, uint8_t direction );

/**
 * @brief Brushless 21 switch direction function.
 * @details This function switches the motor direction by toggling the DIR bit.
 * @param[in] ctx : Click context object.
 * See #brushless21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can only be used when the click is configured in I2C mode.
 */
err_t brushless21_switch_direction ( brushless21_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS21_H

/*! @} */ // brushless21

// ------------------------------------------------------------------------ END
