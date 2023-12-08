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
 * \file fan2.h
 *
 * \brief This file contains API for Fan 2 Click driver.
 *
 * \addtogroup fan2 Fan 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef _FAN2_H_
#define _FAN2_H_

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup registers Registers
 * \{
 */

/**
 * \defgroup address Address
 * \{
 */
#define FAN2_REG_CTRL1                      0x0
#define FAN2_REG_CTRL2                      0x1
#define FAN2_REG_CTRL3                      0x2
#define FAN2_REG_FF_DUTY_CYCLE              0x3
#define FAN2_REG_ALERT_MASK                 0x4
#define FAN2_REG_IDEALITY_FACTOR            0x5
#define FAN2_REG_REMOTE_HIGH_SETPOINT       0x6
#define FAN2_REG_LOCAL_OVERTEMP_SETPOINT    0x8
#define FAN2_REG_REMOTE_OVERTEMP_SETPOINT   0xA
#define FAN2_REG_LOCAL_HIGH_SETPOINT        0xC
#define FAN2_REG_TACH_CNT_THRSH             0xE
#define FAN2_REG_GENERAL_PURPOSE_FIRST_MEM  0x10
#define FAN2_REG_GENERAL_PURPOSE_LAST_MEM   0x17
#define FAN2_REG_LUT_START                  0x20
#define FAN2_REG_LUT_END                    0x4F
#define FAN2_REG_DIRECT_DUTY_CYCLE_CTRL     0x50
#define FAN2_REG_CURRENT_PWM_DUTY_CYCLE     0x51
#define FAN2_REG_TACH1_CNT                  0x52
#define FAN2_REG_TACH2_CNT                  0x54
#define FAN2_REG_REMOTE_TEMP_READ           0x56
#define FAN2_REG_LOCAL_TEMP_READ            0x58
#define FAN2_REG_STATUS                     0x5A
#define FAN2_REG_EEPROM_TO_RAM              0x5B
/** \} */

/**
 * \defgroup settings Settings
 * \{
 */

/**
 * \defgroup ctrl1 CTRL1 Register
 * \{
 */
#define FAN2_CTRL1_MASK_TEMP_ALERTS     0x80
#define FAN2_CTRL1_SW_POR               0x40
#define FAN2_CTRL1_LUT_HYST_2_CELS      0x0
#define FAN2_CTRL1_LUT_HYST_4_CELS      0x20
#define FAN2_CTRL1_PWM_FREQ_33_HZ       0x0
#define FAN2_CTRL1_PWM_FREQ_150_HZ      0x8
#define FAN2_CTRL1_PWM_FREQ_1500_HZ     0x10
#define FAN2_CTRL1_PWM_FREQ_25_KHZ      0x18
#define FAN2_CTRL1_PWM_POL_POS          0x0
#define FAN2_CTRL1_PWM_POL_NEG          0x4
#define FAN2_CTRL1_TEMP_IDX_TIS         0x0
#define FAN2_CTRL1_TEMP_IDX_GREATER     0x2
#define FAN2_CTRL1_LUT_IDX_LOCAL_TEMP   0x0
#define FAN2_CTRL1_LUT_IDX_REMOTE_TEMP  0x1
/** \} */

/**
 * \defgroup ctrl2 CTRL2 Register
 * \{
 */
#define FAN2_CTRL2_NORMAL_MODE         0x0
#define FAN2_CTRL2_STANDBY_MODE        0x80
#define FAN2_CTRL2_ALERT_INTERR        0x0
#define FAN2_CTRL2_ALERT_COMP          0x40
#define FAN2_CTRL2_SPIN_UP_EN          0x20
#define FAN2_CTRL2_FF_OUTPUT_INTERR    0x0
#define FAN2_CTRL2_FF_OUTPUT_COMP      0x10
#define FAN2_CTRL2_FS_INPUT_EN         0x8
#define FAN2_CTRL2_RD_ACTIVE_LOW       0x0
#define FAN2_CTRL2_RD_ACTIVE_HIGH      0x4
#define FAN2_CTRL2_TACHO_SQUARE_WAVE   0x0
#define FAN2_CTRL2_TACHO_RD            0x2
#define FAN2_CTRL2_DIRECT_FAN_CTRL_EN  0x1
/** \} */

/**
 * \defgroup ctrl3 CTRL3 Register
 * \{
 */
#define FAN2_CTRL3_CLR_FAIL                   0x80
#define FAN2_CTRL3_FF_DETECT_EN               0x40
#define FAN2_CTRL3_PWM_RAMP_RATE_SLOW         0x0
#define FAN2_CTRL3_PWM_RAMP_RATE_SLOW_MEDIUM  0x10
#define FAN2_CTRL3_PWM_RAMP_RATE_MEDIUM_FAST  0x20
#define FAN2_CTRL3_PWM_RAMP_RATE_FAST         0x30
#define FAN2_CTRL3_TACHFULL_EN                0x8
#define FAN2_CTRL3_PULSE_STRETCH_EN           0x4
#define FAN2_CTRL3_TACH2_EN                   0x2
#define FAN2_CTRL3_TACH1_EN                   0x1
/** \} */

/**
 * \defgroup mask_alr Mask Alarm
 * \{
 */
#define FAN2_MASK_ALARM_LOCAL_TEMP_HIGH   0x20
#define FAN2_MASK_ALARM_LOCAL_OVERTEMP    0x10
#define FAN2_MASK_ALARM_REMOTE_TEMP_HIGH  0x8
#define FAN2_MASK_ALARM_REMOTE_OVERTEMP   0x4
#define FAN2_MASK_ALARM_TACH2             0x2
#define FAN2_MASK_ALARM_TACH1             0x1
#define FAN2_MASK_ALARM_RESERVED_BITS     0xC0
#define FAN2_MASK_ALARM_NONE              0x0
/** \} */

/**
 * \defgroup eeprom EEPROM
 * \{
 */
#define FAN2_EEPROM_WRITE       0x0
#define FAN2_EEPROM_LOAD        0x80
#define FAN2_EEPROM_40H_TO_4FH  0x10
#define FAN2_EEPROM_30H_TO_3FH  0x8
#define FAN2_EEPROM_20H_TO_2FH  0x4
#define FAN2_EEPROM_10H_TO_1FH  0x2
#define FAN2_EEPROM_00H_TO_0FH  0x1
/** \} */

/** \} */ //  End settings group

/**
 * \defgroup mem_org Memory Organization
 * \{
 */

/**
 * \defgroup temp_reg Temperature Register
 * \{
 */
#define FAN2_TEMP_DATA_OFFSET  5
#define FAN2_TEMP_DATA_MASK    0xFFE0
/** \} */

/** \} */ //  End mem_org group

/**
 * \defgroup status Status
 * \{
 */
#define FAN2_STAT_FLAG_PROGRAM_CORRUPT         0x80
#define FAN2_STAT_FLAG_REMOTE_DIODE_FAULT      0x40
#define FAN2_STAT_FLAG_LOCAL_HIGH_TEMP_ALARM   0x20
#define FAN2_STAT_FLAG_LOCAL_OVERTEMP_ALARM    0x10
#define FAN2_STAT_FLAG_REMOTE_HIGH_TEMP_ALARM  0x8
#define FAN2_STAT_FLAG_REMOTE_OVERTEMP_ALARM   0x4
#define FAN2_STAT_FLAG_TACH2_ALARM             0x2
#define FAN2_STAT_FLAG_TACH1_ALARM             0x1
/** \} */

/** \} */ //  End registers group

/**
 * \defgroup limits Limits
 * \{
 */

/**
 * \defgroup temp_data Temperature
 * \{
 */
#define FAN2_MAX_TEMP_CELS   125
#define FAN2_ZERO_TEMP_CELS  0
#define FAN2_MIN_TEMP_CELS   -55
/** \} */

/**
 * \defgroup speed_data Speed
 * \{
 */
#define FAN2_MAX_SPEED_PER   100
#define FAN2_HALF_SPEED_PER  50
#define FAN2_MIN_SPEED_PER   0
/** \} */

/**
 * \defgroup lut_table LUT Bytes Transfer
 * \{
 */
#define FAN2_LUT_NBYTES  48
/** \} */

/** \} */ //  End limits group

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define FAN2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alr     = MIKROBUS( mikrobus, MIKROBUS_AN  ); \
    cfg.shd     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ff      = MIKROBUS( mikrobus, MIKROBUS_CS  ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup types Types
 * \{
 */

/**
 * @brief Click error code definition.
 */
typedef enum
{
    FAN2_OK = 0x0,
    FAN2_ERR_INIT_DRV = 0xFA,
    FAN2_ERR_UNSUPPORTED_PIN,
    FAN2_ERR_REG_ADDR,
    FAN2_ERR_NDATA,
    FAN2_ERR_TEMP_RANGE,
    FAN2_ERR_PWM_DUTY_RANGE

} fan2_err_t;

/**
 * @brief Click I2C address selection.
 */
typedef enum
{
    FAN2_I2C_ADDR_000 = 0x50,
    FAN2_I2C_ADDR_001,
    FAN2_I2C_ADDR_010,
    FAN2_I2C_ADDR_011,
    FAN2_I2C_ADDR_100,
    FAN2_I2C_ADDR_101,
    FAN2_I2C_ADDR_110,
    FAN2_I2C_ADDR_111

} fan2_i2c_addr_t;

/**
 * @brief Click context object definition.
 */
typedef struct
{
    //  Event pins.
    digital_in_t  alr;
    digital_in_t  shd;
    digital_in_t  ff;
    digital_in_t  int_pin;

    //  Module.
    i2c_master_t  i2c;

    //  Device slave address.
    uint8_t  slave_addr;

} fan2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Communication gpio pins.
    pin_name_t  scl;
    pin_name_t  sda;

    //  Additional gpio pins.
    pin_name_t  alr;
    pin_name_t  shd;
    pin_name_t  ff;
    pin_name_t  int_pin;

    //  Configuration variables.
    uint32_t  i2c_speed;
    uint8_t  i2c_addr;

} fan2_cfg_t;

/** \} */ //  End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public Function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Configuration Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to
 * initial state.
 * @note All used pins will be set to unconnected state.
 */
void fan2_cfg_setup( fan2_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns 0x0 - Ok,
 *          0xFA - Driver init error,
 *          0xFB - Unsupported pin.
 *
 * @description This function initializes all necessary pins and peripherals
 * used for this click.
 */
fan2_err_t fan2_init( fan2_t *ctx, fan2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes a default configuration for Fan 2 click.
 */
void fan2_default_cfg( fan2_t *ctx );

/**
 * @brief Generic Byte Write function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_in  Data to be written.
 *
 * @returns 0x0 - Ok,
 *          0xFC - Invalid register address.
 *
 * @description This function writes one byte data to the desired register.
 */
fan2_err_t fan2_generic_write_byte( fan2_t *ctx, uint8_t reg_addr, uint8_t data_in );

/**
 * @brief Generic Byte Read function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_out  Memory where read data be stored.
 *
 * @returns 0x0 - Ok,
 *          0xFC - Invalid register address.
 *
 * @description This function reads one byte data from the desired register.
 */
fan2_err_t fan2_generic_read_byte( fan2_t *ctx, uint8_t reg_addr, uint8_t *data_out );

/**
 * @brief Generic Word Write function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_in  Data to be written.
 *
 * @returns 0x0 - Ok,
 *          0xFC - Invalid register address.
 *
 * @description This function writes 16-bit data to the desired register.
 */
fan2_err_t fan2_generic_write_word( fan2_t *ctx, uint8_t reg_addr, uint16_t data_in );

/**
 * @brief Generic Word Read function.
 *
 * @param ctx  Click object.
 * @param reg_addr  Register address.
 * @param data_out  Memory where read data be stored.
 *
 * @returns 0x0 - Ok,
 *          0xFC - Invalid register address.
 *
 * @description This function reads 16-bit data from the desired register.
 */
fan2_err_t fan2_generic_read_word( fan2_t *ctx, uint8_t reg_addr, uint16_t *data_out );

/**
 * @brief Temperature Read function.
 *
 * @param ctx  Click object.
 * @param temp_addr  Address of any temperature register.
 * @param temp_cels  Memory where temperature data be stored.
 *
 * @returns 0x0 - Ok,
 *          0xFC - Invalid register address.
 *
 * @description This function reads the temperature data from the selected
 * temperature register and converts this data to Celsius degrees.
 */
fan2_err_t fan2_read_temp( fan2_t *ctx, uint8_t temp_addr, float *temp_cels );

/**
 * @brief Temperature Write function.
 *
 * @param ctx  Click object.
 * @param temp_addr  Address of any temperature register.
 * @param temp_cels  Desired temperature in Celsius degrees [from 125 to -55].
 *
 * @returns 0x0 - Ok,
 *          0xFC - Invalid register address,
 *          0xFE - Temperature range error.
 *
 * @description This function writes the entered temperature [Celsius degrees]
 * to the selected temperature register.
 */
fan2_err_t fan2_write_temp( fan2_t *ctx, uint8_t temp_addr, float temp_cels );

/**
 * @brief Tachometer Read function.
 *
 * @param ctx  Click object.
 * @param tacho_addr  Address of any tachometer register.
 * @param tacho_rpm  Memory where tachometer data be stored.
 *
 * @returns 0x0 - Ok,
 *          0xFC - Invalid register address.
 *
 * @description This function reads the tachometer data from the selected
 * tachometer register and converts this data to rpm [rotation per minute].
 */
fan2_err_t fan2_read_tacho( fan2_t *ctx, uint8_t tacho_addr, uint16_t *tacho_rpm );

/**
 * @brief Tachometer Threshold Write function.
 *
 * @param ctx  Click object.
 * @param tacho_rpm  Desired tachometer data in rpm.
 *
 * @description This function writes the tachometer threshold value in rpm.
 */
void fan2_write_tacho_threshold( fan2_t *ctx, uint32_t tacho_rpm );

/**
 * @brief Direct Fan Speed Control function.
 *
 * @param ctx  Click object.
 * @param speed_per  Desired fan speed in percents [from 0 to 100].
 *
 * @returns 0x0 - Ok,
 *          0xFF - PWM duty range error.
 *
 * @description This function allows user to control fan speed directly by
 * changing the PWM duty cycle.
 */
fan2_err_t fan2_direct_speed_control( fan2_t *ctx, float speed_per );

/**
 * @brief Current Fan Speed Read function.
 *
 * @param ctx  Click object.
 *
 * @returns Current fan speed in percents.
 *
 * @description This function reads the current fan speed and converts this
 * data to percents.
 */
float fan2_read_current_speed( fan2_t *ctx );

/**
 * @brief Status Check function.
 *
 * @param ctx  Click object.
 * @param flag_mask  Selects a desired register bits to be checked.
 *
 * @returns Status byte.
 *
 * @description This function checks the selected status flag bits.
 */
uint8_t fan2_status( fan2_t *ctx, uint8_t flag_mask );

/**
 * @brief Lookup Table Write function.
 *
 * @param ctx  Click object.
 * @param lut_addr  Start LUT address.
 * @param lut_data  Data to be written.
 * @param n_data  Number of bytes to be written [from 1 to 48].
 *
 * @returns 0x0 - Ok,
 *          0xFC - Invalid LUT address,
 *          0xFD - Number of bytes is out of range.
 *
 * @description This function allows user to write the desired data to Lookup
 * table.
 */
fan2_err_t fan2_write_lut( fan2_t *ctx, uint8_t lut_addr, uint8_t *lut_data,
                uint8_t n_data );

/**
 * @brief Software Reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes a software reset and waits until reset
 * operation was done.
 */
void fan2_sw_reset( fan2_t *ctx );

/**
 * @brief Alert Pin Check function.
 *
 * @param ctx  Click object.
 *
 * @returns Pin state [bool].
 *
 * @description This function returns the ALR pin state.
 * @note Active-Low Alert Output. Open-drain fault output.
 *       ALERT is triggered when a measured temperature exceeds its programmed
 *       high limit.
 */
uint8_t fan2_get_alr_pin( fan2_t *ctx );

/**
 * @brief Shutdown Pin Check function.
 *
 * @param ctx  Click object.
 *
 * @returns Pin state [bool].
 *
 * @description This function returns the SHD pin state.
 * @note Active-Low Shutdown Output. Open-drain output for system shutdown when
 *       overtemperature is detected.
 */
uint8_t fan2_get_shd_pin( fan2_t *ctx );

/**
 * @brief Fan-Failure Pin Check function.
 *
 * @param ctx  Click object.
 *
 * @returns Pin state [bool].
 *
 * @description This function returns the FF pin state.
 * @note Active-Low Fan-Failure Output. The device pulls this output low if a
 *       fan failure is detected.
 */
uint8_t fan2_get_ff_pin( fan2_t *ctx );

/**
 * @brief Fault Pin Check function.
 *
 * @param ctx  Click object.
 *
 * @returns Pin state [bool].
 *
 * @description This function returns the INT (FAULT) pin state.
 */
uint8_t fan2_get_int_pin( fan2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  //  _FAN2_H_

/** \} */ //  End public_function group
/// \}    //  End fan2 group
/*! @} */
// ------------------------------------------------------------------------ END
