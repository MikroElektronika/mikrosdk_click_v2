/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for Brushless 3 Click driver.
 *
 * \addtogroup brushless3 Brushless 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BRUSHLESS3_H
#define BRUSHLESS3_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_pwm.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define BRUSHLESS3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.dir     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.pwm     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BRUSHLESS3_RETVAL  uint8_t

#define BRUSHLESS3_OK           0x00
#define BRUSHLESS3_INIT_ERROR   0xFF
/** \} */

#define BRUSHLESS3_I2C_ADDRESS                             0x52
#define BRUSHLESS3_MAX_SPEED                                0x1FF
#define BRUSHLESS3_DEF_FREQ                                  25000

/**
 * \defgroup motor_speed_and_control_reg  Motor speed and control device registers   
 * \{
 */
#define BRUSHLESS3_SPEED_CTRL_1                            0x00
#define BRUSHLESS3_SPEED_CTRL_2                            0x01
#define BRUSHLESS3_DEV_CTRL                                0x02
#define BRUSHLESS3_EE_CTRL                                 0x03
/** \} */

/**
 * \defgroup device_operation_status  Device operation status    
 * \{
 */
#define BRUSHLESS3_STATUS                                  0x10
#define BRUSHLESS3_MOTOR_SPEED_1                           0x11
#define BRUSHLESS3_MOTOR_SPEED_2                           0x12
#define BRUSHLESS3_MOTOR_PERIOD_1                          0x13
#define BRUSHLESS3_MOTOR_PERIOD_2                          0x14
#define BRUSHLESS3_MOTOR_KT_1                              0x15
#define BRUSHLESS3_MOTOR_KT_2                              0x16
#define BRUSHLESS3_IPD_POSITION                            0x19
#define BRUSHLESS3_SUPPLY_VOLTAGE                          0x1A
#define BRUSHLESS3_SPEED_CMD                               0x1B
#define BRUSHLESS3_SPD_CMD_BUFFER                          0x1C
#define BRUSHLESS3_FAULT_CODE                              0x1E
/** \} */

/**
 * \defgroup motor_parameters Motor parameters    
 * \{
 */
#define BRUSHLESS3_MOTOR_PARAM_1                           0x20
#define BRUSHLESS3_MOTOR_PARAM_2                           0x21
#define BRUSHLESS3_MOTOR_PARAM_3                           0x22
#define BRUSHLESS3_SYS_OPT_1                               0x23
#define BRUSHLESS3_SYS_OPT_2                               0x24
#define BRUSHLESS3_SYS_OPT_3                               0x25
#define BRUSHLESS3_SYS_OPT_4                               0x26
#define BRUSHLESS3_SYS_OPT_5                               0x27
#define BRUSHLESS3_SYS_OPT_6                               0x28
#define BRUSHLESS3_SYS_OPT_7                               0x29
#define BRUSHLESS3_SYS_OPT_8                               0x2A
#define BRUSHLESS3_SYS_OPT_9                               0x2B
/** \} */

/**
 * \defgroup other_macros Other macros   
 * \{
 */
#define BRUSHLESS3_PARAM_START_EE_CTRL                     0x40
#define BRUSHLESS3_PARAM_STOP_EE_CTRL                      0x50
#define BRUSHLESS3_PARAM_MOTOR_PARAM_1                     0x39
#define BRUSHLESS3_PARAM_MOTOR_PARAM_2                     0x1E
#define BRUSHLESS3_PARAM_MOTOR_PARAM_3                     0x3A
#define BRUSHLESS3_PARAM_SYS_OPT_1                         0x08
#define BRUSHLESS3_PARAM_SYS_OPT_2                         0x50
#define BRUSHLESS3_PARAM_SYS_OPT_3                         0xDA
#define BRUSHLESS3_PARAM_SYS_OPT_4                         0xB8
#define BRUSHLESS3_PARAM_SYS_OPT_5                         0x10
#define BRUSHLESS3_PARAM_SYS_OPT_6                         0x27
#define BRUSHLESS3_PARAM_SYS_OPT_7                         0x37
#define BRUSHLESS3_PARAM_SYS_OPT_8                         0x04
#define BRUSHLESS3_PARAM_SYS_OPT_9                         0x0C
#define BRUSHLESS3_PARAM_DEV_CTRL                          0xB6
/** \} */
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t dir;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    pwm_t pwm;

    // ctx variable 

    uint32_t pwm_freq;
    uint8_t slave_address;

} brushless3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t pwm;
    
    // Additional gpio pins 

    pin_name_t dir;
    pin_name_t int_pin;

    // static variable 

    uint32_t         dev_pwm_freq;
    uint32_t i2c_speed;
    uint8_t i2c_address;

} brushless3_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void brushless3_cfg_setup ( brushless3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param brushless3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BRUSHLESS3_RETVAL brushless3_init ( brushless3_t *ctx, brushless3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Brushless3 click.
 */
void brushless3_default_cfg ( brushless3_t *ctx );

/**
 * @brief Write function.
 *
 * @param ctx          Click object.
 * @param reg_addr     Register address.
 * @param write_data   Byte of data to be written.
 *
 * @description This function writes data to the desired register.
 */
void brushless3_write_data ( brushless3_t *ctx, uint8_t reg_addr, uint8_t write_data );

/**
 * @brief Read function.
 *
 * @param ctx          Click object.
 * @param reg_addr     Register address.
 * 
 * @returns  8-bit read data
 *
 * @description This function reads data from the desired register.
 */
uint8_t brushless3_read_data ( brushless3_t *ctx, uint8_t reg_addr );

/**
 * @brief Set default parameter function
 * 
 * @param ctx          Click object.
 *
 * @description Function set default parameter by write the default data to the
 * a few target 8-bit register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
void brushless3_set_default_param ( brushless3_t *ctx );

/**
 * @brief Set PWM mode function
 *
 * @param ctx          Click object.
 * 
 * @description Function set PWM mode by set bit1 to the
 * target SysOpt9 register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
void brushless3_set_pwm_mode ( brushless3_t *ctx );

/**
 * @brief Set Analog mode function
 *
 * @param ctx          Click object.
 * 
 * @description Function set Analog mode by clear bit1 to the
 * target SysOpt9 register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
void brushless3_set_an_mode ( brushless3_t *ctx );

/**
 * @brief Disable entering into sleep or standby mode function
 *
 * @param ctx          Click object.
 * 
 * @description Function set Analog mode by set bit7 to the
 * target EECtrl register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
void brushless3_disable_sleep_mode ( brushless3_t *ctx );

/**
 * @brief Enable the writing to the configuration registers function
 *
 * @param ctx          Click object.
 * 
 * @description Function enable the writing to the configuration registers by set bit6 to the
 * target EECtrl register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
void brushless3_enable_config ( brushless3_t *ctx );

/**
 * @brief Disable the writing to the configuration registers function
 *
 * @param ctx          Click object.
 * 
 * @description Function enable the writing to the configuration registers by clear bit6 to the
 * target EECtrl register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
void brushless3_disable_config ( brushless3_t *ctx );

/**
 * @brief Copy EEPROM data to register function
 *
 * @param ctx          Click object.
 * 
 * @description Function copy EEPROM data to register by set bit5 to the
 * target EECtrl register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
void brushless3_copy_eeprom ( brushless3_t *ctx );

/**
 * @brief Enable the writing to the EEPROM registers function
 *
 * @param ctx          Click object.
 * 
 * @description Function enable the writing to the EEPROM registers by set bit4 to the
 * target EECtrl register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
void brushless3_enable_write_eeprom ( brushless3_t *ctx );

/**
 * @brief Disable the writing to the EEPROM registers function
 *
 * @param ctx          Click object.
 * 
 * @description Function disable the writing to the EEPROM registers by clear bit4 to the
 * target EECtrl register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
void brushless3_disable_write_eeprom ( brushless3_t *ctx );

/**
 * @brief Check indicate device temperature is over its limits function
 *
 * @param ctx          Click object.
 * 
 * @returns 0 - OK;  1 - Temperature is over its limits;
 *
 * @description Function check indicate device temperature is over its limits by check bit7 
 * from the target Status register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
uint8_t brushless3_check_over_temp ( brushless3_t *ctx );

/**
 * @brief Check indicate that device went into sleep or standby mode function
 *
 * @param ctx          Click object.
 * 
 * @returns  0 - Device is operational; 1 - Device its into sleep or standby mode;
 *
 * @description Function check indicate device went into sleep or standby mode by check bit6 
 * from the target Status register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
uint8_t brushless3_check_sleep_mode ( brushless3_t *ctx );

/**
 * @brief Check indicate that the motor is locked function
 *
 * @param ctx          Click object.
 * 
 * @returns 0 - Device is operational; 1 - Device its into sleep or standby mode;
 *
 * @description Function check indicate that the motor is locked by check bit4 from the
 * target Status register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
uint8_t brushless3_check_motor_lock ( brushless3_t *ctx );

/**
 * @brief Get the supply voltage function
 *
 * @param ctx          Click object.
 * 
 * @returns float value of the supply voltage;
 *
 * @description Function get the supply voltage by read the value from the
 * target Supply Voltage register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
float brushless3_get_supply_voltage_value ( brushless3_t *ctx );

/**
 * @brief Get the speed command ( % ) based on analog or PWM or I2C function
 *
 * @param ctx          Click object.
 * 
 * @returns float speed command ( % );
 *
 * @description Function get the speed command ( % ) based on analog or PWM or I2C 
 *              by read the value from the target Speed CMD register address of DRV10983 
 *              sensorless BLDC motor driver on Brushless 3 click board.
 */
float brushless3_get_speed_cmd ( brushless3_t *ctx );

/**
 * @brief Check fault code function
 *
 * @param ctx          Click object.
 * 
 * @returns
 * <pre>
 * - bit[ 7:6 ] : N/A;
 * - bit[ 5 ]   : Stuck in closed loop;
 * - bit[ 4 ]   : Stuck in open loop;
 * - bit[ 3 ]   : No motor;
 * - bit[ 2 ]   : Kt abnormal;
 * - bit[ 1 ]   : Speed abnormal;
 * - bit[ 0 ]   : Lock detection current limit;
 * </pre>
 * 
 * @description Function check fault code by read 8-bit value from the
 * target Fault Code register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
uint8_t brushless3_check_fault_code ( brushless3_t *ctx );

/**
 * @brief Get speed function
 *
 * @param ctx          Click object.
 * 
 * @returns float value of motor speed ( Hz );
 *
 * @description Function get speed by read value from the
 * two target Motor Speed 1 and 2 register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
float brushless3_get_speed ( brushless3_t *ctx );

/**
 * @brief Set speed function
 *
 * @param ctx              Click object.
 * @param motor_speed_hz   Float value of motor speed ( Hz );
 *
 * @description Function set speed by write the desired value to the
 * two target Speed Ctrl 1 and 2 register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
void brushless3_set_speed ( brushless3_t *ctx, uint16_t motor_speed_hz );

/**
 * @brief Set speed PWM function
 *
 * @param ctx              Click object.
 * @param motor_speed_hz   Float value of motor speed ( Hz );
 *
 * @description Function set speed by write the desired value to the
 * two target Speed Ctrl 1 and 2 register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
void brushless3_set_speedPWM ( brushless3_t *ctx, uint16_t motor_speed_hz );

/**
 * @brief Get motor period function
 *
 * @param ctx              Click object.
 * 
 * @returns float value of motor period ( ms );
 *
 * @description Function get motor period by read value from the
 * two target Motor Period 1 and 2 register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
float brushless3_get_period ( brushless3_t *ctx );

/**
 * @brief Set prog key function
 *
 * @param ctx          Click object.
 * 
 * @description Function set prog key by write value of 0xB6 from the
 * target Dev CTRL register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
void brushless3_enable_programming_eeprom ( brushless3_t *ctx );

/**
 * @brief Get measured velocity constant function
 *
 * @param ctx              Click object.
 * 
 * @returns float value of velocity constant ( V/Hz );
 *
 * @description Function get measured velocity constant by read value from the
 * two target Motor KT 1 and 2 register address of DRV10983 sensorless BLDC motor driver
 * on Brushless 3 click board.
 */
float brushless3_get_velocity_constant ( brushless3_t *ctx );

/**
 * @brief Set the direction of rotation in the forward direction function
 *
 * @param ctx          Click object.
 * 
 * @description Function set the direction of rotation in the forward direction
 * by sets PWM and RST pin on Brushless 3 Click board.
 */
void brushless3_forward_direction ( brushless3_t *ctx );

/**
 * @brief Set the direction of rotation in the reverse direction function
 *
 * @param ctx          Click object.
 * 
 * @description Function set the direction of rotation in the reverse direction
 * by sets PWM and clear RST pin on Brushless 3 Click board.
 */
void brushless3_reverse_direction ( brushless3_t *ctx );

/**
 * @brief Get Interrupt pin state function
 *
 * @param ctx          Click object.
 * 
 * @returns Interrupt pin state     (0 - no active; 1 - active)
 *
 * @description Function get Interrupt ( INT ) pin state of Brushless 3 Click board.
 */
uint8_t brushless3_get_interrupt_status ( brushless3_t *ctx );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void brushless3_set_duty_cycle ( brushless3_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void brushless3_pwm_stop ( brushless3_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void brushless3_pwm_start ( brushless3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BRUSHLESS3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
