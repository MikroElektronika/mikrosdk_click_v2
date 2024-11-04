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
#define BRUSHLESS23_REG_SPEED_SLOPE_MSB         0x08
#define BRUSHLESS23_REG_SPEED_SLOPE_LSB         0x09
#define BRUSHLESS23_REG_SPEED_SLOPE2_MSB        0x0A
#define BRUSHLESS23_REG_SPEED_SLOPE2_LSB        0x0B
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
 * @brief Brushless 23 NVM regs settings.
 * @details Specified NVM regs settings of Brushless 23 Click driver.
 */
#define BRUSHLESS23_NVM_WR_READ                 0x00
#define BRUSHLESS23_NVM_WR_WRITE                0x01
#define BRUSHLESS23_NVM_ST_END                  0x00
#define BRUSHLESS23_NVM_ST_START                0x01

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
#define BRUSHLESS23_START_RPM_MIN               0
#define BRUSHLESS23_START_RPM_500               500
#define BRUSHLESS23_START_RPM_MAX               4095
#define BRUSHLESS23_MAX_RPM_MIN                 3000
#define BRUSHLESS23_MAX_RPM_5000                5000
#define BRUSHLESS23_MAX_RPM_MAX                 50000
#define BRUSHLESS23_MIN_OUT_DUTY_MIN_PCT        0.0
#define BRUSHLESS23_MIN_OUT_DUTY_10_PCT         0.1
#define BRUSHLESS23_MIN_OUT_DUTY_MAX_PCT        0.498
#define BRUSHLESS23_MAX_OUT_DUTY_MIN_PCT        0.5
#define BRUSHLESS23_MAX_OUT_DUTY_95_PCT         0.95
#define BRUSHLESS23_MAX_OUT_DUTY_MAX_PCT        1.0
#define BRUSHLESS23_KIX_KI                      255
#define BRUSHLESS23_KPX_KP                      255
#define BRUSHLESS23_TSPSEL_PWM_DUTY             0x10
#define BRUSHLESS23_ALERT_INV_LOW               0x02
#define BRUSHLESS23_NO_STOP_BIT_MASK            0x80
#define BRUSHLESS23_CLEAR_REG                   0x00

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
#define BRUSHLESS23_DEVICE_ADDRESS_MIN          0x08
#define BRUSHLESS23_DEVICE_ADDRESS_MAX          0x77

/**
 * @brief Brushless 23 default PWM frequency.
 * @details Specified setting for default PWM frequency of Brushless 23 Click driver.
 */
#define BRUSHLESS23_DEF_FREQ                    5000

/**
 * @brief Brushless 23 options.
 * @details Specified options of Brushless 23 Click driver.
 */
#define BRUSHLESS23_CLOSED_LOOP_CONTROL         0
#define BRUSHLESS23_OPEN_LOOP_CONTROL           1
#define BRUSHLESS23_1ST_DC_EXC_0_0              0x00
#define BRUSHLESS23_1ST_DC_EXC_0_2              0x08
#define BRUSHLESS23_1ST_DC_EXC_0_5              0x10
#define BRUSHLESS23_1ST_DC_EXC_1_0              0x18
#define BRUSHLESS23_2ND_DC_EXC_0_1              0x00
#define BRUSHLESS23_2ND_DC_EXC_0_2              0x01
#define BRUSHLESS23_2ND_DC_EXC_0_4              0x02
#define BRUSHLESS23_2ND_DC_EXC_0_6              0x03
#define BRUSHLESS23_2ND_DC_EXC_0_8              0x04
#define BRUSHLESS23_2ND_DC_EXC_1_0              0x05
#define BRUSHLESS23_2ND_DC_EXC_1_5              0x06
#define BRUSHLESS23_2ND_DC_EXC_2_0              0x07
#define BRUSHLESS23_FORCE_FREQ_1_6              0x00
#define BRUSHLESS23_FORCE_FREQ_3_2              0x01
#define BRUSHLESS23_FORCE_FREQ_6_4              0x02
#define BRUSHLESS23_FORCE_FREQ_12_8             0x03
#define BRUSHLESS23_START_CURR_100              0x00
#define BRUSHLESS23_START_CURR_87               0x02
#define BRUSHLESS23_START_CURR_75               0x04
#define BRUSHLESS23_START_CURR_62               0x06
#define BRUSHLESS23_START_CURR_50               0x08
#define BRUSHLESS23_START_CURR_37               0x0A
#define BRUSHLESS23_START_CURR_25               0x0C
#define BRUSHLESS23_START_CURR_12               0x0E
#define BRUSHLESS23_SS_DUTY_CHG_LIM_64          0x00
#define BRUSHLESS23_SS_DUTY_CHG_LIM_2           0x02
#define BRUSHLESS23_SS_DUTY_CHG_LIM_3           0x04
#define BRUSHLESS23_SS_DUTY_CHG_LIM_4           0x06
#define BRUSHLESS23_SS_DUTY_CHG_LIM_6           0x08
#define BRUSHLESS23_SS_DUTY_CHG_LIM_10          0x0A
#define BRUSHLESS23_SS_DUTY_CHG_LIM_20          0x0C
#define BRUSHLESS23_SS_DUTY_CHG_LIM_56          0x0E
#define BRUSHLESS23_SS_ADD_SEL_00               0x00    // SS_ADD_SEL = Startup current limit +0%
#define BRUSHLESS23_SS_ADD_SEL_30               0x40    // SS_ADD_SEL = Startup current limit +30%
#define BRUSHLESS23_SS_ADD_SEL_40               0x80    // SS_ADD_SEL = Startup current limit +40%
#define BRUSHLESS23_SS_ADD_SEL_50               0xC0    // SS_ADD_SEL = Startup current limit +50%
#define BRUSHLESS23_SS_UP_SEL_1                 0x00    // SS_UP_SEL of 1%
#define BRUSHLESS23_SS_UP_SEL_2                 0x10    // SS_UP_SEL of 2%
#define BRUSHLESS23_SS_UP_SEL_5                 0x20    // SS_UP_SEL of 5%
#define BRUSHLESS23_SS_UP_SEL_10                0x30    // SS_UP_SEL of 10%
#define BRUSHLESS23_MAX_SPEED_4K                0x00    // Idle state, max speed 4096 rpm
#define BRUSHLESS23_MAX_SPEED_8K                0x02    // Idle state, max speed 8192 rpm
#define BRUSHLESS23_MAX_SPEED_16K               0x04    // Idle state, max speed 16384 rpm
#define BRUSHLESS23_MAX_SPEED_32K               0x06    // Idle state, max speed 32768 rpm
#define BRUSHLESS23_DUTY_UP_TIME_2_7            0x00    // Duty up time 2.7ms    
#define BRUSHLESS23_DUTY_UP_TIME_10_8           0x01    // Duty up time 10.8ms    
#define BRUSHLESS23_DUTY_CHG_LIM_64             0x00    // Duty change limit 64/8 (closed loop only)
#define BRUSHLESS23_DUTY_CHG_LIM_2              0x10    // Duty change limit 2/8
#define BRUSHLESS23_DUTY_CHG_LIM_3              0x20    // Duty change limit 3/8
#define BRUSHLESS23_DUTY_CHG_LIM_4              0x30    // Duty change limit 4/8
#define BRUSHLESS23_DUTY_CHG_LIM_6              0x40    // Duty change limit 6/8
#define BRUSHLESS23_DUTY_CHG_LIM_10             0x50    // Duty change limit 10/8
#define BRUSHLESS23_DUTY_CHG_LIM_20             0x60    // Duty change limit 20/8
#define BRUSHLESS23_DUTY_CHG_LIM_56             0x70    // Duty change limit 56/8
#define BRUSHLESS23_LEAD_ANGLE_0                0x00    // Lead angle index 0: 0°
#define BRUSHLESS23_LEAD_ANGLE_1                0x10    // Lead angle index 1: 0°
#define BRUSHLESS23_LEAD_ANGLE_2                0x20    // Lead angle index 2: 0°
#define BRUSHLESS23_LEAD_ANGLE_3                0x30    // Lead angle index 3: 0°
#define BRUSHLESS23_LEAD_ANGLE_4                0x40    // Lead angle index 4: 0°
#define BRUSHLESS23_LEAD_ANGLE_5                0x50    // Lead angle index 5: 0°
#define BRUSHLESS23_LEAD_ANGLE_6                0x60    // Lead angle index 6: 0°
#define BRUSHLESS23_LEAD_ANGLE_7                0x70    // Lead angle index 7: 26.25°
#define BRUSHLESS23_LEAD_ANGLE_8                0x80    // Lead angle index 8: 30°
#define BRUSHLESS23_LEAD_ANGLE_9                0x90    // Lead angle index 9: 0°
#define BRUSHLESS23_LEAD_ANGLE_10               0xA0    // Lead angle index 10: 0°
#define BRUSHLESS23_LEAD_ANGLE_11               0xB0    // Lead angle index 11: 0°
#define BRUSHLESS23_LEAD_ANGLE_12               0xC0    // Lead angle index 12: 0°
#define BRUSHLESS23_LEAD_ANGLE_13               0xD0    // Lead angle index 13: 0°
#define BRUSHLESS23_LEAD_ANGLE_14               0xE0    // Lead angle index 14: 0°
#define BRUSHLESS23_LEAD_ANGLE_15               0xF0    // Lead angle index 15: 0°
#define BRUSHLESS23_OUTPUT_PWM_0                0x00    // PWM index 0: 23.4kHz
#define BRUSHLESS23_OUTPUT_PWM_1                0x04    // PWM index 1: 46.9kHz
#define BRUSHLESS23_OUTPUT_PWM_2                0x08    // PWM index 2: 93.7kHz
#define BRUSHLESS23_OUTPUT_PWM_3                0x0C    // PWM index 3: 187.5kHz
#define BRUSHLESS23_OUTPUT_PWM_4                0x10    // PWM index 4: 46.9kHz - 187.5kHz
#define BRUSHLESS23_OUTPUT_PWM_5                0x14    // PWM index 5: 23.4kHz
#define BRUSHLESS23_OUTPUT_PWM_6                0x18    // PWM index 6: 23.4kHz
#define BRUSHLESS23_OUTPUT_PWM_7                0x1C    // PWM index 7: 23.4kHz
#define BRUSHLESS23_SOURCE_CURR_10              0x00    // Source current 10.0mA    
#define BRUSHLESS23_SOURCE_CURR_13              0x08    // Source current 13.9mA    
#define BRUSHLESS23_SOURCE_CURR_19              0x10    // Source current 19.3mA    
#define BRUSHLESS23_SOURCE_CURR_26              0x18    // Source current 26.8mA    
#define BRUSHLESS23_SOURCE_CURR_37              0x20    // Source current 37.3mA    
#define BRUSHLESS23_SOURCE_CURR_51              0x28    // Source current 51.8mA    
#define BRUSHLESS23_SOURCE_CURR_72              0x30    // Source current 72.0mA    
#define BRUSHLESS23_SOURCE_CURR_100             0x38    // Source current 100.0mA    
#define BRUSHLESS23_SINK_CURR_20                0x00    // Sink current 20.0mA
#define BRUSHLESS23_SINK_CURR_27                0x01    // Sink current 27.8mA
#define BRUSHLESS23_SINK_CURR_38                0x02    // Sink current 38.6mA
#define BRUSHLESS23_SINK_CURR_53                0x03    // Sink current 53.7mA
#define BRUSHLESS23_SINK_CURR_74                0x04    // Sink current 74.6mA
#define BRUSHLESS23_SINK_CURR_103               0x05    // Sink current 103.6mA
#define BRUSHLESS23_SINK_CURR_143               0x06    // Sink current 143.9mA
#define BRUSHLESS23_SINK_CURR_200               0x07    // Sink current 200.0mA
#define BRUSHLESS23_OCP_LVL_250                 0x00    // Current limitation (VOC) : 250mV
#define BRUSHLESS23_OCP_LVL_125                 0x40    // Current limitation (VOC) : 125mV
#define BRUSHLESS23_ANTI_THROUGH_ENA            0x00
#define BRUSHLESS23_ANTI_THROUGH_DIS            0x01
#define BRUSHLESS23_DEAD_TIME_250               0x00
#define BRUSHLESS23_DEAD_TIME_500               0x01
#define BRUSHLESS23_DEAD_TIME_1000              0x02
#define BRUSHLESS23_DEAD_TIME_1500              0x03
#define BRUSHLESS23_POLE_PAIRS_1                1
#define BRUSHLESS23_POLE_PAIRS_2                2
#define BRUSHLESS23_POLE_PAIRS_3                3
#define BRUSHLESS23_POLE_PAIRS_4                4
#define BRUSHLESS23_POLE_PAIRS_5                4
#define BRUSHLESS23_POLE_PAIRS_6                5
#define BRUSHLESS23_POLE_PAIRS_7                6
#define BRUSHLESS23_POLE_PAIRS_8                7
#define BRUSHLESS23_POLE_PAIRS_MSK              0x38

/**
 * @brief Brushless 23 config for the ACT 42BLF01 TBW motor.
 * @details Specified config for the ACT 42BLF01 TBW motor of Brushless 23 Click driver.
 */
#define BRUSHLESS23_MOTOR_OPERATION             BRUSHLESS23_CLOSED_LOOP_CONTROL
#define BRUSHLESS23_MOTOR_START_DUTY            0.20
#define BRUSHLESS23_MOTOR_STOP_DUTY             0.08
#define BRUSHLESS23_MOTOR_MAX_DUTY              0.95
#define BRUSHLESS23_MOTOR_CHANGE_DUTY           0.60
#define BRUSHLESS23_MOTOR_START_RPM             500
#define BRUSHLESS23_MOTOR_MAX_RPM               4005
#define BRUSHLESS23_MOTOR_CHANGE_RPM            1500
#define BRUSHLESS23_MOTOR_MIN_OUT_DUTY          0.10
#define BRUSHLESS23_MOTOR_MAX_OUT_DUTY          0.95
#define BRUSHLESS23_MOTOR_CHANGE_OUT_DUTY       0.40
#define BRUSHLESS23_MOTOR_1ST_DC_EXC            BRUSHLESS23_1ST_DC_EXC_0_0
#define BRUSHLESS23_MOTOR_2ND_DC_EXC            BRUSHLESS23_2ND_DC_EXC_0_4
#define BRUSHLESS23_MOTOR_FORCE_FREQ            BRUSHLESS23_FORCE_FREQ_1_6
#define BRUSHLESS23_MOTOR_START_CURR            BRUSHLESS23_START_CURR_75
#define BRUSHLESS23_MOTOR_SS_DUTY_CHG_LIM       BRUSHLESS23_SS_DUTY_CHG_LIM_2
#define BRUSHLESS23_MOTOR_SS_ADD_SEL            BRUSHLESS23_SS_ADD_SEL_30
#define BRUSHLESS23_MOTOR_SS_UP_SEL             BRUSHLESS23_SS_UP_SEL_1
#define BRUSHLESS23_MOTOR_MAX_SPEED             BRUSHLESS23_MAX_SPEED_8K
#define BRUSHLESS23_MOTOR_DUTY_UP_TIME          BRUSHLESS23_DUTY_UP_TIME_2_7
#define BRUSHLESS23_MOTOR_DUTY_CHG_LIM          BRUSHLESS23_DUTY_CHG_LIM_4
#define BRUSHLESS23_MOTOR_LEAD_ANGLE            BRUSHLESS23_LEAD_ANGLE_0
#define BRUSHLESS23_MOTOR_OUTPUT_PWM            BRUSHLESS23_OUTPUT_PWM_0
#define BRUSHLESS23_MOTOR_SOURCE_CURR           BRUSHLESS23_SOURCE_CURR_51
#define BRUSHLESS23_MOTOR_SINK_CURR             BRUSHLESS23_SINK_CURR_75
#define BRUSHLESS23_MOTOR_POLE_PAIRS            BRUSHLESS23_POLE_PAIRS_4

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
 * @brief Motor context object for Brushless 23 Click.
 * @details Context object definition of motor connected to Brushless 23 Click.
 */
typedef struct
{
    uint8_t  pole_pairs;            /**< Number of Pole Pairs : 1 to 8 */
    uint8_t  loop_control;          /**< Open loop operation = true  */
    // Parameteres for speed curve definition
    float    start_duty;            /**< Start Duty: 0.0 to 0.498 */
    float    stop_duty;             /**< Stop Duty: 0.0 to 0.496 */
    float    max_duty;              /**< Max in Duty: 0.502 to 1.0 */
    float    min_out;               /**< min out Duty: 0.0 to 0.498 */
    float    max_out;               /**< Max out Duty: 0.502 to 1.0 */
    float    change_duty;           /**< Change Duty: 0.0, 0.04 to 0.996 */
    float    change_out;            /**< Change out Duty: 0.0 to 1.0 */
    uint16_t start_rpm;
    uint16_t max_rpm;
    uint16_t change_rpm;
    uint16_t speed_slope;
    uint16_t speed_slope2;

} brushless23_motor_t;

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
    
    brushless23_motor_t motor;  /**< Motor config. */

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
 * @details This function initializes Click configuration structure to initial
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
 * for this Click board.
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
 * Click board.
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
 * @brief Brushless 23 get int pin function.
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
 * @details This function sets the start rpm value.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] start_rpm : Start RPM in range 0-4095.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_set_start_rpm ( brushless23_t *ctx, uint16_t start_rpm );

/**
 * @brief Brushless 23 set max rpm function.
 * @details This function sets the maximum rpm value, required for the speed slope calculation.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] max_rpm : Maximum rpm value in the range of 3000-50000.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The function brushless23_set_speed_slope() must be called afterwards.
 */
err_t brushless23_set_max_rpm ( brushless23_t *ctx, uint16_t max_rpm );

/**
 * @brief Brushless 23 set change rpm function.
 * @details This function sets the change rpm value, required for the speed slope calculation.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] change_rpm : Change RPM in range of start_rpm to max_rpm.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The function brushless23_set_speed_slope() must be called afterwards.
 */
err_t brushless23_set_change_rpm ( brushless23_t *ctx, uint16_t change_rpm );

/**
 * @brief Brushless 23 set min out duty function.
 * @details This function sets the minimum output duty cycle, required for the speed slope calculation.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] duty_cycle  : Duty cycle in range 0.0 - 0.498.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The function brushless23_set_speed_slope() must be called afterwards.
 */
err_t brushless23_set_min_out_duty ( brushless23_t *ctx, float duty_cycle );

/**
 * @brief Brushless 23 set max out duty function.
 * @details This function sets the maximum output duty value, required for the speed slope calculation.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] duty_cycle  : Duty cycle in range 0.5 - 1.0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The function brushless23_set_speed_slope() must be called afterwards.
 */
err_t brushless23_set_max_out_duty ( brushless23_t *ctx, float duty_cycle );

/**
 * @brief Brushless 23 set change out duty function.
 * @details This function sets the change output duty value, required for the speed slope calculation.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle in range of min_out to max_out.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The function brushless23_set_speed_slope() must be called afterwards.
 */
err_t brushless23_set_change_out_duty ( brushless23_t *ctx, float duty_cycle );

/**
 * @brief Brushless 23 set duty cycle function.
 * @details This function sets the duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] duty_cycle : Duty cycle in range 0.0 - 1.0.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can only be used when the Click SPD switch is configured in I2C mode.
 */
err_t brushless23_set_duty_cycle ( brushless23_t *ctx, float duty_cycle );

/**
 * @brief Brushless 23 set pole pairs function.
 * @details This function sets the number of pole pairs of motor.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] pole_pairs : Pole pairs in range 1-8.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_set_pole_pairs ( brushless23_t *ctx, uint8_t pole_pairs );

/**
 * @brief Brushless 23 set speed slope function.
 * @details This function calculates and sets the speed slope registers
 * for the specified motor settings.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] motor : Motor settings.
 * See #brushless23_motor_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_set_speed_slope ( brushless23_t *ctx, brushless23_motor_t *motor );

/**
 * @brief Brushless 23 set motor operation function.
 * @details This function sets the motor operation to open or closed loop.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] m_operation : @li @c 0 - Closed loop,
 *                          @li @c 1 - Open loop.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_set_motor_operation ( brushless23_t *ctx, uint8_t m_operation );

/**
 * @brief Brushless 23 set user id function.
 * @details This function sets the USER ID.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] user_id : User ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_set_user_id ( brushless23_t *ctx, uint8_t user_id );

/**
 * @brief Brushless 23 get user id function.
 * @details This function reads the USER ID.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[out] user_id : User ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_get_user_id ( brushless23_t *ctx, uint8_t *user_id );

/**
 * @brief Brushless 23 get status reg function.
 * @details This function reads the status register.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[out] status : Status register read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_get_status_reg ( brushless23_t *ctx, uint8_t *status );

/**
 * @brief Brushless 23 set i2c addr reg function.
 * @details This function sets the I2C address register.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] i2c_addr : I2C address to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_set_i2c_addr_reg ( brushless23_t *ctx, uint8_t i2c_addr );

/**
 * @brief Brushless 23 get i2c addr reg function.
 * @details This function reads the I2C address register.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[out] i2c_addr : I2C address read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_get_i2c_addr_reg ( brushless23_t *ctx, uint8_t *i2c_addr );

/**
 * @brief Brushless 23 read config regs function.
 * @details This function reads all config registers.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[out] data_out : Data buffer of at least 29 bytes where to store the registers content.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_read_config_regs ( brushless23_t *ctx, uint8_t *data_out );

/**
 * @brief Brushless 23 read nvm to regs function.
 * @details This function reads NVM to registers.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[out] data_out : Data buffer of at least 29 bytes where to store the registers content.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_read_nvm_to_regs ( brushless23_t *ctx, uint8_t *data_out );

/**
 * @brief Brushless 23 write regs to nvm function.
 * @details This function writes registers to NVM.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_write_regs_to_nvm ( brushless23_t *ctx );

/**
 * @brief Brushless 23 device is ready function.
 * @details This function checks if the device is ready by reading the I2C address register.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @return @li @c 0 - Device is not ready,
 *         @li @c 1 - Device is ready.
 * @note None.
 */
uint8_t brushless23_device_is_ready ( brushless23_t *ctx );

/**
 * @brief Brushless 23 set motor config function.
 * @details This function sets the motor configuration registers.
 * @param[in] ctx : Click context object.
 * See #brushless23_t object definition for detailed explanation.
 * @param[in] motor : Motor settings.
 * See #brushless23_motor_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless23_set_motor_config ( brushless23_t *ctx, brushless23_motor_t *motor );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS23_H

/*! @} */ // brushless23

// ------------------------------------------------------------------------ END
