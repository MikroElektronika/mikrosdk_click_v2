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
 * @file brushless23.h
 * @brief This file contains API for Brushless 23 Click Driver.
 */

#ifndef BRUSHLESS23_H
#define BRUSHLESS23_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_pwm.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup brushless23 Brushless 23 Click Driver
 * @brief API for configuring and manipulating Brushless 23 Click driver.
 * @{
 */

/**
 * @defgroup brushless23_reg Brushless 23 Registers List
 * @brief List of registers of Brushless 23 Click driver.
 */

/**
 * @addtogroup brushless23_reg
 * @{
 */

/**
 * @brief Brushless 23 register map.
 * @details Specified register map of Brushless 23 Click driver.
 */
#define BRUSHLESS23_REG_STATUS                  0x00
#define BRUSHLESS23_REG_USER_ID                 0x01
#define BRUSHLESS23_REG_STOP_DUTY               0x02
#define BRUSHLESS23_REG_START_DUTY              0x03
#define BRUSHLESS23_REG_CHANGE_DUTY             0x04
#define BRUSHLESS23_REG_MAX_DUTY                0x05
#define BRUSHLESS23_REG_START_RPM_MSB           0x06
#define BRUSHLESS23_REG_START_RPM_LSB           0x07
#define BRUSHLESS23_REG_8                       0x08
#define BRUSHLESS23_REG_9                       0x09
#define BRUSHLESS23_REG_10                      0x0A
#define BRUSHLESS23_REG_11                      0x0B
#define BRUSHLESS23_REG_KIX_KI                  0x0C
#define BRUSHLESS23_REG_KPX_KP                  0x0D
#define BRUSHLESS23_REG_14                      0x0E
#define BRUSHLESS23_REG_15                      0x0F
#define BRUSHLESS23_REG_16                      0x10
#define BRUSHLESS23_REG_17                      0x11
#define BRUSHLESS23_REG_18                      0x12
#define BRUSHLESS23_REG_19                      0x13
#define BRUSHLESS23_REG_TRE_PRETIP_TIP          0x14
#define BRUSHLESS23_REG_LA_FMAX_FST             0x15
#define BRUSHLESS23_REG_FPWM_DEADTIME           0x16
#define BRUSHLESS23_REG_ISD_OCP_SRC_SINK        0x17
#define BRUSHLESS23_REG_COMP_HYS                0x18
#define BRUSHLESS23_REG_SLAVE_ADRS              0x19
#define BRUSHLESS23_REG_SPD_MSB                 0x1B
#define BRUSHLESS23_REG_SPD_LSB                 0x1C
#define BRUSHLESS23_REG_HZ_CNT_MSB              0x1D
#define BRUSHLESS23_REG_HZ_CNT_LSB              0x1E
#define BRUSHLESS23_REG_NVM_W_R                 0x56
#define BRUSHLESS23_REG_NVM_ST                  0x57

/*! @} */ // brushless23_reg

/**
 * @defgroup brushless23_set Brushless 23 Registers Settings
 * @brief Settings for registers of Brushless 23 Click driver.
 */

/**
 * @addtogroup brushless23_set
 * @{
 */

/**
 * @brief Brushless 23 open loop setting for option 3.
 * @details Specified open loop setting for option 3 of Brushless 23 Click driver.
 */
#define BRUSHLESS23_DUTY_CYCLE_MIN_PCT          0.0
#define BRUSHLESS23_DUTY_CYCLE_MAX_PCT          1.0
#define BRUSHLESS23_START_DUTY_MIN_PCT          0.0
#define BRUSHLESS23_START_DUTY_20_PCT           0.2
#define BRUSHLESS23_START_DUTY_MAX_PCT          0.498
#define BRUSHLESS23_STOP_DUTY_MIN_PCT           0.0
#define BRUSHLESS23_STOP_DUTY_18_PCT            0.18
#define BRUSHLESS23_STOP_DUTY_MAX_PCT           0.496
#define BRUSHLESS23_MAX_DUTY_MIN_PCT            0.502
#define BRUSHLESS23_MAX_DUTY_90_PCT             0.9
#define BRUSHLESS23_MAX_DUTY_MAX_PCT            1.0
#define BRUSHLESS23_CHANGE_DUTY_MIN_PCT         0.004
#define BRUSHLESS23_CHANGE_DUTY_90_PCT          0.9
#define BRUSHLESS23_CHANGE_DUTY_MAX_PCT         0.996
#define BRUSHLESS23_START_RPM_MIN_PCT           0.0
#define BRUSHLESS23_START_RPM_10_PCT            0.1
#define BRUSHLESS23_START_RPM_MAX_PCT           0.498
#define BRUSHLESS23_SPEED_SLOP_1_MSB            0x0F
#define BRUSHLESS23_SPEED_SLOP_1_LSB            0xF8
#define BRUSHLESS23_SPEED_SLOP_2_MSB            0x15
#define BRUSHLESS23_SPEED_SLOP_2_LSB            0xF0
#define BRUSHLESS23_OPEN_LOOP                   0x01
#define BRUSHLESS23_TSPSEL_PWM_DUTY             0x10
#define BRUSHLESS23_ALERTINV_LOW                0x02
#define BRUSHLESS23_NO_STOP_BIT_MASK            0x80

/**
 * @brief Brushless 23 direction setting.
 * @details Specified setting for direction of Brushless 23 Click driver.
 */
#define BRUSHLESS23_DIR_CW                      0
#define BRUSHLESS23_DIR_CCW                     1

/**
 * @brief Brushless 23 standby pin setting.
 * @details Specified setting for standby pin of Brushless 23 Click driver.
 */
#define BRUSHLESS23_SBY_STANDBY                 0
#define BRUSHLESS23_SBY_NORMAL_OPERATION        1

/**
 * @brief Brushless 23 motor speed frequency calculation.
 * @details Specified motor speed frequency calculation of Brushless 23 Click driver.
 */
#define BRUSHLESS23_SPEED_FREQUENCY             250000.0

/**
 * @brief Brushless 23 device address setting.
 * @details Specified setting for device slave address selection of
 * Brushless 23 Click driver.
 */
#define BRUSHLESS23_DEVICE_ADDRESS_ID2ID1_00    0x29
#define BRUSHLESS23_DEVICE_ADDRESS_ID2ID1_01    0x29
#define BRUSHLESS23_DEVICE_ADDRESS_ID2ID1_10    0x2D
#define BRUSHLESS23_DEVICE_ADDRESS_ID2ID1_11    0x32

/**
 * @brief Brushless 23 default PWM frequency.
 * @details Specified setting for default PWM frequency of Brushless 23 Click driver.
 */
#define BRUSHLESS23_DEF_FREQ                    5000

/*! @} */ // brushless23_set

/**
 * @defgroup brushless23_map Brushless 23 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 23 Click driver.
 */

/**
 * @addtogroup brushless23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 23 Click to the selected MikroBUS.
 */
#define BRUSHLESS23_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.sby = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cmo = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.spd = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // brushless23_map
/*! @} */ // brushless23

/**
 * @brief Brushless 23 Click context object.
 * @details Context object definition of Brushless 23 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t sby;          /**< Standby pin (Active-Low). */
    digital_out_t dir;          /**< Direction pin. */

    // Input pins
    digital_in_t  int_pin;      /**< Alert or rotation speed (FG) pin. */

    // Modules
    i2c_master_t  i2c;          /**< I2C driver object. */
    pwm_t         pwm;          /**< PWM driver object. */
    analog_in_t   adc;          /**< ADC module object. */

    // ctx variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} brushless23_t;

/**
 * @brief Brushless 23 Click configuration object.
 * @details Configuration object definition of Brushless 23 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  sby;            /**< Standby pin (Active-Low). */
    pin_name_t  cmo;            /**< Current monitor output pin. */
    pin_name_t  dir;            /**< Direction pin. */
    pin_name_t  spd;            /**< Speed control PWM pin. */
    pin_name_t  int_pin;        /**< Alert or rotation speed (FG) pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */
    uint32_t  dev_pwm_freq;     /**< PWM frequency value. */
    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float                   vref;           /**< ADC reference voltage. */

} brushless23_cfg_t;

/**
 * @brief Brushless 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS23_OK = 0,
    BRUSHLESS23_ERROR = -1

} brushless23_return_value_t;

/*!
 * @addtogroup brushless23 Brushless 23 Click Driver
 * @brief API for configuring and manipulating Brushless 23 Click driver.
 * @{
 */

/**
 * @brief Brushless 23 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless23_cfg_setup ( brushless23_cfg_t *cfg );

/**
 * @brief Brushless 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_init ( brushless23_t *ctx, brushless23_cfg_t *cfg );

/**
 * @brief Brushless 23 default configuration function.
 * @details This function executes a default configuration of Brushless 23
 * click board.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless23_default_cfg ( brushless23_t *ctx );

/**
 * @brief Brushless 23 write register function.
 * @details This function writes a desired data byte to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_write_register ( brushless23_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Brushless 23 read register function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_read_register ( brushless23_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Brushless 23 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_pwm_set_duty_cycle ( brushless23_t *ctx, float duty_cycle );

/**
 * @brief Brushless 23 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_pwm_stop ( brushless23_t *ctx );

/**
 * @brief Brushless 23 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_pwm_start ( brushless23_t *ctx );

/**
 * @brief Brushless 23 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_read_an_pin_value ( brushless23_t *ctx, uint16_t *data_out );

/**
 * @brief Brushless 23 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t brushless23_read_an_pin_voltage ( brushless23_t *ctx, float *data_out );

/**
 * @brief Brushless 23 set sby pin function.
 * @details This function sets the SBY pin state.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] state @li @c 0 - Standby,
 *                  @li @c 1 - Normal operation.
 * @return None.
 * @note None.
 */
void brushless23_set_sby_pin ( brushless23_t *ctx, uint8_t state );

/**
 * @brief Brushless 23 set direction function.
 * @details This function sets the motor direction.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] dir @li @c 0 - Clockwise,
 *                @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void brushless23_set_direction ( brushless23_t *ctx, uint8_t dir );

/**
 * @brief Brushless 23 switch direction function.
 * @details This function switches the direction by toggling the DIR pin state.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless23_switch_direction ( brushless23_t *ctx );

/**
 * @brief Brushless 22 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t brushless23_get_int_pin ( brushless23_t *ctx );

/**
 * @brief Brushless 23 get motor speed function.
 * @details This function reads the motor speed in Hz.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[out] motor_speed_hz : Motor speed in Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_get_motor_speed ( brushless23_t *ctx, float *motor_speed_hz );

/**
 * @brief Brushless 23 set start duty function.
 * @details This function sets the start duty cycle.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle in range 0.0 - 0.498.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_set_start_duty ( brushless23_t *ctx, float duty_cycle );

/**
 * @brief Brushless 23 set stop duty function.
 * @details This function sets the stop duty cycle.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle in range 0.0 - 0.496.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_set_stop_duty ( brushless23_t *ctx, float duty_cycle );

/**
 * @brief Brushless 23 set max duty function.
 * @details This function sets the max duty cycle.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle in range 0.502 - 1.0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_set_max_duty ( brushless23_t *ctx, float duty_cycle );

/**
 * @brief Brushless 23 set change duty function.
 * @details This function sets the change duty cycle.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle in range 0.004 - 0.996.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_set_change_duty ( brushless23_t *ctx, float duty_cycle );

/**
 * @brief Brushless 23 set start rpm function.
 * @details This function sets the start rpm duty cycle.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle in range 0.0 - 0.498.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_set_start_rpm ( brushless23_t *ctx, float duty_cycle );

/**
 * @brief Brushless 23 set duty cycle function.
 * @details This function sets the duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle in range 0.0 - 1.0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can only be used when the click SPD switch is configured in I2C mode.
 */
err_t brushless23_set_duty_cycle ( brushless23_t *ctx, float duty_cycle );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS23_H

/*! @} */ // brushless23

// ------------------------------------------------------------------------ END
